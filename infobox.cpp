#include "infobox.h"

InfoBox::InfoBox()
{

}

QRectF InfoBox::boundingRect() const
{
    return QRectF(0, 0, 80, 150);
}

void InfoBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF re = boundingRect();
    QBrush brush(Qt::red);
    QPen pen(Qt::black);

    painter->fillRect(re, brush);
    painter->setPen(pen);
    painter->drawRect(re);
}

