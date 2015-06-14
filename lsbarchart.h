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

#ifndef LSBARCHART_H
#define LSBARCHART_H

#include <QtGui>
#include <QGraphicsScene>
#include <vector>
#include <QPen>
#include <QString>
#include <QGraphicsTextItem>
#include <algorithm>
#include <QColor>
#include <math.h>
#include <QLocale>
#include <QPainter>
#include <numeric>
#include <QDebug>
#include <QGraphicsSceneHoverEvent>
#include <iterator>
#include "dataset.h"
#include "infobox.h"

#define LEFT 0
#define RIGHT 1
#define CENTER 2
#define BOTTOM 3
#define TOP 4
#define MIDDLE 5

using namespace std;

//! LSBarChart class.
/*!
  This class is a custom scene inherited from QGraphicsScene. This class draws
  barchart from a vector of dataSet.
*/
class LSBarChart : public QGraphicsScene
{
public:
    //! A constructor.
    /*!
      Constructor for LSBarChart class.
    */
    LSBarChart();

    //! Constructor for the class LSBarChar.
    /*!
      \param width double value for width of the scene.
      \param height double value for height of the scene.
    */
    LSBarChart(double width, double height);
    ~ LSBarChart(void);

    //! A method to draw bar chart from the data.
    /*!
      \param data vector<DataSet> containing the series for data to be presented.
      \sa LSBarChart()
    */
    void drawChart(std::vector<DataSet> data);

    //! A method that draws infobox and line to the chart when mouse is moved over it.
    /*!
      \param e QGraphicsEvent containing the mouse pointer coordinates.
      \sa LSBarChart()
    */
    void mouseMoveEvent(QGraphicsSceneMouseEvent* e);

private:
    //! A method that draws xAxis for the barchart.
    /*!
      \param max int for the maximum x-value in the data series.
      \sa LSBarChart()
    */
    void drawXAxis(int max);

    //! A method that draws yAxis for the barchart.
    /*!
      \param max int for the maximum y-value in the data series.
      \sa LSBarChart()
    */
    void drawYAxis(double max);

    //! A method that draws Legend (colored boxes and name of the series) under the bar chart.
    /*!
      \sa LSBarChart()
    */
    void drawLegend();

    //! A method that draws a box into the barchart.
    /*!
      \param x int x position for the top left corner of the box.
      \param y int y position for the top left corner of the box.
      \param height double height of the box.
      \param width double width of the box.
      \param color QColor value for the color of the box.
      \sa LSBarChart()
    */
    void drawBar(double x, double y, double height, double width, QColor color);

    //! A method that shows information of the current bar in the infobox.
    /*!
      \param text QString value of the text to be displayed.
      \sa LSBarChart()
    */
    void addInfoText(QString text);

    //! A method that calculates extra buffer for the maximum value for the Axis.
    /*!
      \brief This method adds small buffer to the maximum value to make the chart look nicer.
      \param value double value that the buffer will be added to
      \return double maximum value for the axis
      \sa LSBarChart()
    */
    double calculateMaxAxisValue(double value);

    std::vector<DataSet> dataSets;

    //! A method that calculates extra buffer for the maximum value for the Axis.
    /*!
      \brief This method adds small buffer to the maximum value to make the chart look nicer.
      \param value double value that the buffer will be added to
      \return double maximum value for the axis
      \sa LSBarChart()
    */
    void drawCursorLine(double x, double y);

    //! pointer to a cursoline shown at position of the mouse pointer
    QGraphicsLineItem *cursorLine;

    //! pointer to the infotext in the callout shown when mouse pointer is hovering above the chart
    QGraphicsTextItem *infoText;

    //! pointer to the infobox callout shown when mouse pointer is hovering above the chart
    InfoBox *infoBox;

    //! Describes how many pixels each data point in the dataset is
    double unitHeight;

    //! A method that calculates the maximum value for axis from the dataset.
    /*!
      This calculates the maximum value through all datasets. This calculation
      makes sure that the chart can be fitted to the area of the scene.
      \param data vector<DataSet> dataset that will be analysed for max value.
      \return double maximum value for the axis.
      \sa LSBarChart()
    */
    double calculateMaxDataValue(std::vector<DataSet> data);

protected:
    //! bool to select if animation for barchart is used or not (currently not in use).
    bool animation;

    //! Width of the scene.
    double width;

    //! Height of the scene.
    double height;

    //! Widht of the are where barchart is drawn.
    double canvasWidth;

    //! Height of the are where barchart is drawn.
    double canvasHeight;

    //! left margin for the barchart
    double leftMargin;

    //! widht of individual bars
    double barWidth;

    //! width of the gap between bars
    double gap;

    //! \struct Axis
    /*!
      \brief This struct contains information about the axis.
      Axis contain pixel position (int) for the axis, length and width of the axis line and label for the axis (QString).
    */
    struct Axis {
        int position;
        double length;
        double width;
        QString label;
    };

    //! xAxis parameters
    Axis xAxis;

    //! yAxis parameters
    Axis yAxis;
};

#endif // LSBARCHART_H
