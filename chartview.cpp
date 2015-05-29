#include "chartview.h"

ChartView::ChartView(QWidget *parent) : QGraphicsView(parent)
{

}

void ChartView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    //qDebug() << QString("Resize Event %1").arg(event->oldSize().width());
    double oldX = event->oldSize().width();
    double newX = event->size().width();
    double oldY = event->oldSize().height();
    double newY = event->size().height();
    double scaleX = newX/oldX;
    double scaleY = newY/oldY;
    //this->scale(scaleX, scaleY);
    if (this->scene() != 0)
    {
        this->scene()->sceneRect().setWidth(this->width());
        this->scene()->sceneRect().setHeight(this->height());

//    qDebug() << QString("scaleX: %1, scaleY: %2").arg(scaleX).arg(scaleY);
        this->scale(scaleX, scaleY);
    }
}

