#ifndef INFOBOX_H
#define INFOBOX_H
#include <QGraphicsItem>
#include <QPainter>

class InfoBox : public QGraphicsItem
{
public:
    InfoBox();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // INFOBOX_H
