#include "DcmImageTransferFunction.h"

DcmImageTransferFunction::DcmImageTransferFunction()
    : m_referencePoints(),
      m_minPixelValue(0.0),
      m_maxPixelValue(0.0)
{
}

DcmImageTransferFunction::DcmImageTransferFunction(const DcmImageTransferFunction &tf)
    : m_referencePoints(tf.m_referencePoints),
      m_minPixelValue(tf.m_minPixelValue),
      m_maxPixelValue(tf.m_maxPixelValue)
{
}

DcmImageTransferFunction& DcmImageTransferFunction::operator =(const DcmImageTransferFunction &tf)
{
    if (this != &tf) {
        m_referencePoints = tf.m_referencePoints;
        m_minPixelValue = tf.m_minPixelValue;
        m_maxPixelValue = tf.m_maxPixelValue;
    }
    return *this;
}

void DcmImageTransferFunction::addReferencePoint(double pixelValue, const QColor &color)
{
    DcmImageTransferFunction::ReferencePoint refPoint;
    refPoint.pixelValue = pixelValue;
    refPoint.color = color;
    addReferencePoint(refPoint);
}

void DcmImageTransferFunction::addReferencePoint(const ReferencePoint &refPoint)
{
    if (m_referencePoints.count() == 0) {
        m_referencePoints.append(refPoint);
        m_minPixelValue = refPoint.pixelValue;
        m_maxPixelValue = m_minPixelValue;
    } else {
        for (int i = 0; i < m_referencePoints.count(); i++) {
            if (m_referencePoints.at(i).pixelValue > refPoint.pixelValue) {
                m_referencePoints.insert(i, refPoint);
                if (i == 0) {
                    m_minPixelValue = refPoint.pixelValue;
                }
                return;
            }
        }
        m_referencePoints.append(refPoint);
        m_maxPixelValue = refPoint.pixelValue;
    }
}

int DcmImageTransferFunction::numberOfReferencePoints() const
{
    return m_referencePoints.count();
}

DcmImageTransferFunction::ReferencePoint DcmImageTransferFunction::referencePointAt(int index) const
{
    return m_referencePoints.at(index);
}

void DcmImageTransferFunction::setReferencePoint(int index, const QColor &color)
{
    ReferencePoint rp;
    rp.pixelValue = m_referencePoints.at(index).pixelValue;
    rp.color = color;
    m_referencePoints.replace(index, rp);
}

QColor DcmImageTransferFunction::colorForPixelValue(double value) const
{
    QColor color(0, 0, 0);
    if (value < m_minPixelValue || value > m_maxPixelValue || m_referencePoints.count() < 2) {
        return color;
    }

    int i = 0;
    while (m_referencePoints.at(i).pixelValue < value) {
        i++;
    }

    Q_ASSERT(i > 0);

    if (i == 0) {
        return color;
    }

    ReferencePoint rpA = m_referencePoints.at(i - 1);
    ReferencePoint rpB = m_referencePoints.at(i);

    double length = rpB.pixelValue - rpA.pixelValue;
    Q_ASSERT(length > 0.0);

    if (length <= 0.0) {
        return color;
    }

    return DcmImageTransferFunction::intermediateColor(rpA.color, rpB.color, (value - rpA.pixelValue) / length);
}

QColor DcmImageTransferFunction::intermediateColor(const QColor &colorA, const QColor &colorB, double fraction)
{
    if (fraction <= 0.0) {
        return colorA;
    }
    if (fraction >= 1.0) {
        return colorB;
    }

    return QColor((colorA.red() + colorB.red()) * fraction,
                  (colorA.green() + colorB.green()) * fraction,
                  (colorA.blue() + colorB.blue()) * fraction);
}
