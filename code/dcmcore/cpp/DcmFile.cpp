#include <QFile>
#include "DcmStream.h"
#include "DcmReader.h"
#include "DcmWriter.h"
#include "DcmTagUI.h"
#include "DcmFile.h"

DcmFile::DcmFile(const QString &path)
    : m_path(path),
      m_error(false),
      m_errorText()
{
}

QString DcmFile::path() const
{
    return m_path;
}

bool DcmFile::exists() const
{
    return QFile(m_path).exists();
}

DcmDataset DcmFile::read(DcmDictionary *dictionaryPtr)
{
    setError();
    DcmDictionary *dict = (dictionaryPtr) ? dictionaryPtr : DcmDictionary::getInstancePtr();

    bool isHeader = hasHeader(m_path);
    DcmTransferSyntax transferSyntax = guessTransferSyntax(m_path, isHeader, dict);
    if (!transferSyntax.isValid()) {
        setError(QObject::tr("Unable to guess transfer syntax to decode the file."));
        return DcmDataset();
    }

    QFile file(m_path);
    if (!file.open(QFile::ReadOnly)) {
        setError(QObject::tr("Unable to open the file for reading."));
        return DcmDataset();
    }

    DcmStream stream(&file, transferSyntax);
    if (isHeader) {
        stream.dataStream().skipRawData(132);
    }

    DcmReader reader(&stream, dict);
    DcmDataset dataset = reader.readDataset();

    file.close();

    if (reader.isError()) {
        setError(reader.errorText());
        return DcmDataset();
    }

    return dataset;
}

void DcmFile::write(DcmDataset &dataset, const DcmTransferSyntax &transferSyntax)
{
    setError();

    QFile file(m_path);
    if (!file.open(QFile::WriteOnly)) {
        setError(QObject::tr("Unable to open file for writing"));
        return;
    }

    // Injecting transfer syntax to meta information header
    DcmTagUI tag(DcmTagKey::TransferSyntaxUID);
    tag.setString(transferSyntax.uid());
    dataset.insert(tag);

    DcmStream ds(&file, transferSyntax);
    char *header = new char[132];
    memset(header, 0, 132);
    header[128] = 'D';
    header[129] = 'I';
    header[130] = 'C';
    header[131] = 'M';

    ds.dataStream().writeRawData(header, 132);

    delete[] header;

    DcmWriter writer(&ds);
    writer.writeDataset(dataset);

    file.close();
}

bool DcmFile::isError() const
{
    return m_error;
}

QString DcmFile::errorText() const
{
    return m_errorText;
}

void DcmFile::setError(const QString &text)
{
    m_error = !text.isEmpty();
    m_errorText = text;
}

bool DcmFile::hasHeader(const QString &path)
{
    QFile file(path);
    if (!file.open(QFile::ReadOnly)) {
        return false;
    }

    QDataStream ds(&file);
    int s = ds.skipRawData(128);
    if (s != 128) {
        file.close();
        return false;
    }

    char signature[4];
    s = ds.readRawData(signature, 4);
    if (s != 4) {
        file.close();
        return false;
    }

    file.close();

    if (signature[0] == 'D' && signature[1] == 'I' && signature[2] == 'C' && signature[3] == 'M') {
        return true;
    }

    return false;
}

bool DcmFile::probeTransferSyntax(const QString &path,
                                  const DcmTransferSyntax &transferSyntax,
                                  bool skipHeader,
                                  DcmDictionary *dictionaryPtr)
{
    QFile file(path);
    if (!file.open(QFile::ReadOnly)) {
        return false;
    }

    DcmDictionary *dict = (dictionaryPtr) ? dictionaryPtr : DcmDictionary::getInstancePtr();

    DcmStream ds(&file, transferSyntax);
    DcmReader reader(&ds, dict);

    if (skipHeader) {
        ds.dataStream().skipRawData(132);
    }

    DcmTag *tag = reader.readTag();

    file.close();

    if (tag && !reader.isError()) {
        delete tag;
        return true;
    }

    delete tag;
    return false;
}

DcmTransferSyntax DcmFile::guessTransferSyntax(const QString &path, bool skipHeader, DcmDictionary *dictionaryPtr)
{
    DcmDictionary *dict = (dictionaryPtr) ? dictionaryPtr : DcmDictionary::getInstancePtr();
    QList<DcmTransferSyntax> syntaxes = QList<DcmTransferSyntax>()
            << DcmTransferSyntax::ExplicitLittleEndian
            << DcmTransferSyntax::ImplicitLittleEndian
            << DcmTransferSyntax::ExplicitBigEndian;

    foreach (DcmTransferSyntax syntax, syntaxes) {
        if (probeTransferSyntax(path, syntax, skipHeader, dict)) {
            return syntax;
        }
    }

    return DcmTransferSyntax::Invalid;
}
