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
    double scaleX = newX/oldX;
    double oldY = event->oldSize().height();
    double newY = event->size().height();
    double scaleY = newY/oldY;
//    qDebug() << QString("scaleX: %1, scaleY: %2").arg(scaleX).arg(scaleY);
    //this->scale(scaleX, scaleY);
    if (this->scene() != 0)
    {
        this->scale(scaleX, scaleY);
    }
    //this->scale(event->oldSize().width()/event->size().width(), event->oldSize().height()/event->size().height());
//    qDebug() << QString("x: %1, y: %2, height: %3").arg(e->scenePos().x()).arg(e->scenePos().y()).arg(y);
}

