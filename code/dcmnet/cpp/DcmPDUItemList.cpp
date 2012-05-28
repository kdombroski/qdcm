#include "DcmPDUItemList.h"

DcmPDUItemList::DcmPDUItemList()
    : m_pduItems()
{
}

DcmPDUItemList::DcmPDUItemList(const DcmPDUItemList &list)
    : m_pduItems()
{
    foreach (DcmPDUItem *item, list.m_pduItems) {
        m_pduItems.append(item->clone());
    }
}

DcmPDUItemList& DcmPDUItemList::operator =(const DcmPDUItemList &list)
{
    if (this != &list) {
        clear();
        foreach (DcmPDUItem *item, list.m_pduItems) {
            m_pduItems.append(item->clone());
        }
    }
    return *this;
}

DcmPDUItemList::~DcmPDUItemList()
{
    clear();
}

int DcmPDUItemList::count() const
{
    return m_pduItems.count();
}

DcmPDUItem* DcmPDUItemList::at(int index) const
{
    return m_pduItems.at(index);
}

void DcmPDUItemList::append(const DcmPDUItem &pdu)
{
    m_pduItems.append(pdu.clone());
}

void DcmPDUItemList::appendAndRetain(DcmPDUItem *pduPtr)
{
    Q_ASSERT(pduPtr);
    if (pduPtr) {
        m_pduItems.append(pduPtr);
    }
}

void DcmPDUItemList::clear()
{
    QMutableListIterator<DcmPDUItem*> iterator(m_pduItems);
    while (iterator.hasNext()) {
        DcmPDUItem *item = iterator.next();
        iterator.remove();
        delete item;
    }
}

DcmSize DcmPDUItemList::size() const
{
    DcmSize s = 0;
    foreach (DcmPDUItem *item, m_pduItems) {
        s += item->size();
    }
    return s;
}
