#ifndef DICOMTREEMODEL_H
#define DICOMTREEMODEL_H

#include <QList>
#include <QStandardItem>
#include <QStandardItemModel>
#include "DcmDataset.h"

/*! Model for a tree view to represent DICOM dataset structire.
 */
class DicomTreeModel : public QStandardItemModel
{
    Q_OBJECT

public:

    DicomTreeModel(DcmDataset *dataset, QObject *parent = 0);

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:

    /// Create table row for a single tag.
    static QList<QStandardItem *> createRowForTag(DcmTag *tag);

    /// Attach list of tags to tree model item.
    static void attachTagList(QStandardItem *item, DcmTagList &tagList);

};

#endif // DICOMTREEMODEL_H
