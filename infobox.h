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
