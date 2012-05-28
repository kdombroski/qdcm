#include "DcmTagSQ.h"

DcmTagSQ::DcmTagSQ()
    : DcmTag(DcmTagKey(), DcmVr::SQ),
      m_items()
{
}

DcmTagSQ::DcmTagSQ(const DcmTagKey &tagKey)
    : DcmTag(tagKey, DcmVr::SQ),
      m_items()
{
}

DcmTagSQ::DcmTagSQ(const DcmTagSQ &tagSq)
    : DcmTag(tagSq),
      m_items(tagSq.m_items)
{
}

DcmTagSQ& DcmTagSQ::operator =(const DcmTagSQ &tagSq)
{
    if (this != &tagSq) {
        DcmTag::operator =(tagSq);
        m_items = tagSq.m_items;
    }
    return *this;
}

DcmTag* DcmTagSQ::clone() const
{
    return new DcmTagSQ(*this);
}

DcmTagSQ::~DcmTagSQ()
{
}

DcmSize DcmTagSQ::contentSize(const DcmTransferSyntax &transferSyntax) const
{
    return m_items.size(transferSyntax);
}

DcmSize DcmTagSQ::size(const DcmTransferSyntax &transferSyntax) const
{
    DcmSize s = contentSize(transferSyntax);
    if (s != DcmSize_Undefined) {
        if (transferSyntax.encoding() == DcmEncoding_Explicit) {
            // Explicit: gg gg ee ee S Q 00 00 <content size, 4 bytes>
            s += 12;
        } else {
            // Implicit: gg gg ee ee <content size, 4 bytes>
            s += 8;
        }
    }
    return s;
}

DcmTagList& DcmTagSQ::items()
{
    return m_items;
}

void DcmTagSQ::insert(const DcmTagItem &item)
{
    m_items.insert(item);
}

void DcmTagSQ::insertAndRetain(DcmTagItem *itemPtr)
{
    Q_ASSERT(itemPtr);
    if (itemPtr) {
        m_items.insertAndRetain(itemPtr);
    }
}
