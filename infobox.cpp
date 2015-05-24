#include "infobox.h"

InfoBox::InfoBox()
{
    cornerRadius = 20.0;
    boxWidth = 150;
    boxHeight = 100;
    this->setZValue(5);
    leftPoint = false;

    //this->setTransformOriginPoint();
}

QRectF InfoBox::boundingRect() const
{
    return QRectF(0, 0, boxWidth, boxHeight);
}

void InfoBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush(QColor(245, 245, 245));
    QPen pen(Qt::white);

//    QString *jee = new QString("Jee!");

    QPainterPath *textbox = new QPainterPath();
    textbox->addPath(callout(QPoint( 10, 10)));
    painter->fillPath(*textbox, brush);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawPath(*textbox);

    QPen *fontPen = new QPen(Qt::black);
    QBrush *fontBrush = new QBrush(Qt::black);
    QPainterPath *test = new QPainterPath();
    test->addPath(infoText(this->text));
    painter->fillPath(*test, *fontBrush);
    painter->setPen(*fontPen);
    painter->drawPath(*test);
}

void InfoBox::moveToPoint(QPoint *point)
{
    double cX, cY;
    if(point->x() > boxWidth)
    {
        cX = point->x() - boxWidth;
        cY = point->y() - boxHeight/2;
        if ( cY < 0 ) cY = 0;
        leftPoint = false;
    }
    else
    {
        cX = point->x();
        cY = point->y() - boxHeight/1.5;
        if ( cY < 0 ) cY = 0;
        leftPoint = true;
    }
    if( 250 - cY < 0 ) cY = 250;
    this->setPos(QPointF(cX, cY));
}

void InfoBox::setText(QString text)
{
    this->text = text;
}
QPainterPath InfoBox::callout(QPoint p)
{
    QPainterPath callout;
    double cornerSize = cornerRadius;
    double pointLength = 15.0;
    double pointHeight = 17.0;
    double calloutWidth = boxWidth - cornerSize*2 - pointLength;
    double calloutHeight = boxHeight - cornerSize*2 - pointHeight;
    double pointPos = calloutHeight/2-pointHeight/2 - 5;

    if(leftPoint)
    {
        callout.moveTo(pointLength, cornerRadius);
    }
    else
    {
         callout.moveTo(pointLength - 2, cornerRadius);
    }
    callout.arcTo(QRect(callout.currentPosition().x(), callout.currentPosition().y() - cornerSize, cornerSize, cornerSize), 180.0, -90);
    callout.lineTo(callout.currentPosition().x() + calloutWidth, callout.currentPosition().y());
    callout.arcTo(QRect(callout.currentPosition().x(), callout.currentPosition().y(), cornerSize, cornerSize), 90, -90);
    if(!this->leftPoint)
    {
        callout.lineTo(callout.currentPosition().x(), callout.currentPosition().y() + pointPos);
        callout.lineTo(callout.currentPosition().x() + pointLength, callout.currentPosition().y() + pointHeight/2);
        callout.lineTo(callout.currentPosition().x() - pointLength, callout.currentPosition().y() + pointHeight/2);
        callout.lineTo(callout.currentPosition().x(), callout.currentPosition().y() + calloutHeight - pointHeight - pointPos);
    }
    else
    {
        callout.lineTo(callout.currentPosition().x(), callout.currentPosition().y() + calloutHeight);
    }
    callout.arcTo(QRect(callout.currentPosition().x() - cornerSize, callout.currentPosition().y(), cornerSize, cornerSize), 0, -90);
    callout.lineTo(callout.currentPosition().x() - calloutWidth, callout.currentPosition().y());
    callout.arcTo(QRect(callout.currentPosition().x() - cornerSize, callout.currentPosition().y() - cornerSize, cornerSize, cornerSize), 270, -90);
    if(leftPoint)
    {
        callout.lineTo(callout.currentPosition().x(), callout.currentPosition().y() - pointPos);
        callout.lineTo(callout.currentPosition().x() - pointLength, callout.currentPosition().y() - pointHeight/2);
        callout.lineTo(callout.currentPosition().x() + pointLength, callout.currentPosition().y() - pointHeight/2);
    }
    callout.closeSubpath();
    //    callout.translate(100, 100);
    return callout;
}

QPainterPath InfoBox::infoText(QString text)
{
    QPainterPath textPath;
    QFont timesFont("Helvetica", 12);
    timesFont.setStyleStrategy(QFont::NoAntialias);
    timesFont.setStyleStrategy(QFont::PreferQuality);
    textPath.addText(10, 15, timesFont, text);
    return textPath;
}
