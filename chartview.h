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

#ifndef CHARTVIEW_H
#define CHARTVIEW_H
#include<QGraphicsView>
#include<QDebug>
#include<QResizeEvent>

//!  ChartView class.
/*!
  This class is custom QGraphicsView. resizeEvent method is overriden in this
  class, otherwise it's regular QGraphicsView.
*/
class ChartView : public QGraphicsView
{
    Q_OBJECT

public:
    //! A constructor.
    /*!
      Constructor for ChartView class.
    */
    ChartView(QWidget *parent = 0);

protected:
    //! A overriden method taking one argument.
    /*!
      \brief this method updates the size of the graphicsview and the scene that it contains.
      \param *event a QResizeEvent.
      \sa ChartView()
    */
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:

};

#endif // CHARTVIEW_H

