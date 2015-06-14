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

//!  InfoBox class.
/*!
  This class is inherited from QGraphicsItem and draws a customized callout box with arrow on left
  or right side of the callout.
*/
class InfoBox : public QGraphicsItem
{
public:
    //! A constructor.
    /*!
      Constructor for InfoBox class.
    */
    InfoBox();

    //! Overriden virtual method for setting BoundingRect of the item.
    /*!
      \sa InfoBox()
    */
    QRectF boundingRect() const;

    //! Overriden virtual method to paint the customized item.
    /*!
      \param *painter pointer to the QPainter object.
      \param *option pointer to the QStyleOptionGraphicsItem.
      \param *widget pointer to the parent widget.
      \sa InfoBox()
    */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //! Method to move the customized item to the requested point.
    /*!
      \param *point pointer to the QPoint object. Infobox is redrawn to this point.
      \sa InfoBox()
    */
    void moveToPoint(QPoint *point);

    //! Method to set the text for the customized item.
    /*!
      \brief Currently the text field is not used when the InfoBox is drawn.
      \param text QString.
      \sa InfoBox()
    */
    void setText(QString text);

private:
    //! QPainterPath of the InfoBox.
    /*!
      This variable is painter path for the InfoBox.
    */
    QPainterPath box;

    //! Text inside of the InfoBox.
    QString text;

    //! Method to draw the QPainterPath of the callout.
    /*!
      \param QPoint to define the current top left corner of the callout.
      \return QPainterPath of the callout to be drawn.
      \sa InfoBox()
    */
    QPainterPath callout(QPoint);

    //! Method to draw the QPainterPath of the text inside the callout.
    /*!
      \param text QString text to be placed inside the callout.
      \return QPainterPath of the text to be drawn.
      \sa InfoBox()
    */
    QPainterPath infoText(QString text);

    //! Corner radius of the callout rectangle.
    double cornerRadius;

    //! Width of the callout rectangle.
    int boxWidth;

    //! Height of the callout rectangle.
    int boxHeight;

    //! Bool to define if callout arrow is drawn to the left side of the callout or not.
    bool leftPoint;
};

#endif // INFOBOX_H
