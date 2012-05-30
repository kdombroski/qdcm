#include "DcmPDUItem.h"

DcmPDUItem::DcmPDUItem(DcmPDUType pduItemType)
    : m_type(pduItemType)
{
}

DcmPDUItem::DcmPDUItem(const DcmPDUItem &item)
    : m_type(item.m_type)
{
}

DcmPDUItem& DcmPDUItem::operator =(const DcmPDUItem &item)
{
    if (this != &item) {
        m_type = item.m_type;
    }
    return *this;
}

DcmPDUItem* DcmPDUItem::clone() const
{
    return new DcmPDUItem(*this);
}

DcmPDUItem::~DcmPDUItem()
{
}

DcmPDUType DcmPDUItem::type() const
{
    return m_type;
}

bool DcmPDUItem::isAssociationLevel() const
{
    return m_type == DcmPDUType_AAssociateRq
            || m_type == DcmPDUType_AAssociateAc
            || m_type == DcmPDUType_AAssociateRj
            || m_type == DcmPDUType_AReleaseRq
            || m_type == DcmPDUType_AReleaseRp
            || m_type == DcmPDUType_AAbort
            || m_type == DcmPDUType_PData;
}

DcmSize DcmPDUItem::size() const
{
    // DcmPDUType, 00, content length (2 bytes), ...content...
    return 4 + contentSize();
}

DcmSize DcmPDUItem::contentSize() const
{
    return 0;
}

bool DcmPDUItem::isValid() const
{
    return m_type != DcmPDUType_Invalid;
}
