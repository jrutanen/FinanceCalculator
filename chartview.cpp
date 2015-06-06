/* Copyright (C) 2015 Finance Calculator
 * (Jani Rutanen)
 *
 * This file is part of Financial Calculator.
 *
 * Financial Calculator is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Financial Calculator is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Financial Calculator.  If not, see <http://www.gnu.org/licenses/>.
 */

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

