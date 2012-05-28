#include <QDebug>
#include "DcmAbstractSyntax.h"
#include "DcmTransferSyntax.h"
#include "DcmApplicationContext.h"
#include "DcmPresentationContext.h"
#include "DcmAcceptedPresentationContext.h"
#include "DcmPDUUserInfo.h"
#include "DcmPDUMaxLength.h"
#include "DcmPDUImplementationClassUID.h"
#include "DcmPDUImplementationVersionName.h"
#include "DcmAAssociateRequest.h"
#include "DcmAAssociateAccept.h"
#include "DcmAAbort.h"
#include "DcmNetStream.h"

DcmNetStream::DcmNetStream(DcmStream &stream)
{
    m_streamPtr = &stream;
}

void DcmNetStream::writePDUItem(const DcmPDUItem &item)
{
    DcmPDUType type = item.type();

#define CASE(t,c)   \
    case t: {   \
        const c pdu = dynamic_cast<const c&>(item); \
        *m_streamPtr << pdu;    \
        break;  \
    }

    switch(type) {
    CASE(DcmPDUType_AbstractSyntax, DcmAbstractSyntax);
    CASE(DcmPDUType_TransferSyntax, DcmTransferSyntax);
    CASE(DcmPDUType_ApplicationContext, DcmApplicationContext);
    CASE(DcmPDUType_PresentationContext, DcmPresentationContext);
    CASE(DcmPDUType_AcceptedPresentationContext, DcmAcceptedPresentationContext);
    CASE(DcmPDUType_UserInfo, DcmPDUUserInfo);
    CASE(DcmPDUType_PDUMaxLength, DcmPDUMaxLength);
    CASE(DcmPDUType_ImplementationClassUID, DcmPDUImplementationClassUID);
    CASE(DcmPDUType_ImplementationVersionName, DcmPDUImplementationVersionName);
    CASE(DcmPDUType_AAssociateRq, DcmAAssociateRequest);
    CASE(DcmPDUType_AAssociateAc, DcmAAssociateAccept);
    CASE(DcmPDUType_AAbort, DcmAAbort);
    default:
        qWarning() << "Unknown PDU type" << type;
        break;
    }

#undef CASE
}

DcmPDUItem* DcmNetStream::readPDUItem()
{
    DcmPDUType type = DcmPDUType_Invalid;

    // Peek one byte
    if (m_streamPtr->dataStream().device()->peek((char*)&type, 1) != 1) {
        return 0;
    }

    DcmPDUItem *item = 0;

#define CASE(t,c)   \
    case t: {   \
        c pdu;  \
        *m_streamPtr >> pdu;    \
        item = pdu.clone(); \
    }

    switch (type) {
    CASE(DcmPDUType_AbstractSyntax, DcmAbstractSyntax);
    CASE(DcmPDUType_TransferSyntax, DcmTransferSyntax);
    CASE(DcmPDUType_ApplicationContext, DcmApplicationContext);
    CASE(DcmPDUType_PresentationContext, DcmPresentationContext);
    CASE(DcmPDUType_AcceptedPresentationContext, DcmAcceptedPresentationContext);
    CASE(DcmPDUType_UserInfo, DcmPDUUserInfo);
    CASE(DcmPDUType_PDUMaxLength, DcmPDUMaxLength);
    CASE(DcmPDUType_ImplementationClassUID, DcmPDUImplementationClassUID);
    CASE(DcmPDUType_ImplementationVersionName, DcmPDUImplementationVersionName);
    CASE(DcmPDUType_AAssociateRq, DcmAAssociateRequest);
    CASE(DcmPDUType_AAssociateAc, DcmAAssociateAccept);
    CASE(DcmPDUType_AAbort, DcmAAbort);
    default:
        qWarning() << "Unknown PDU type" << type;
        break;
    }

#undef CASE

    return item;
}
