#ifndef INFOBOX_H
#define INFOBOX_H
#include <QGraphicsItem>
#include <QPainter>
#include <QPainterPath>
#include <QPainterPathStroker>
#include <QPoint>
#include <QFont>

class InfoBox : public QGraphicsItem
{
public:
    InfoBox();
    InfoBox(QPoint *p, QString *text);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void moveToPoint(QPoint *point);
    void setText(QString text);
private:
    QPainterPath box;
    QString text;
    QPainterPath callout(QPoint);
    QPainterPath infoText(QString text);
    double cornerRadius;
    int boxWidth;
    int boxHeight;
    bool leftPoint;
};

#endif // INFOBOX_H
