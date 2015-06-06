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

class LSBarChart : public QGraphicsScene
{
public:
    LSBarChart();
    LSBarChart(double, double);
    ~ LSBarChart(void);
    void drawChart(std::vector<DataSet>);
    void addSummary(std::vector<DataSet>);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);

private:
    void drawXAxis(int);
    void drawYAxis(double);
    void drawLegend();
    void drawBar(double, double, double, double, QColor);
    void drawBarWithColor(double, double, double, QColor);
    void drawStackedBarWithColor(double, double, double, QColor);
    void addInfoText(QString text);
    double calculateMaxAxisValue(double);
    std::vector<DataSet> dataSets;
    void drawCursorLine(double x, double y);
    QGraphicsLineItem *cursorLine;
    QGraphicsTextItem *infoText;
    InfoBox *infoBox;
    double unitHeight;
    double calculateMaxDataValue(std::vector<DataSet>);
//    QLineF cursorLine;
protected:
    bool animation;
    double width;
    double height;
    double canvasWidth;
    double canvasHeight;
    double leftMargin;
    double barWidth;
    double gap;
    struct Axis {
        int position;
        double length;
        double width;
        QString label;
    };
    Axis xAxis;
    Axis yAxis;

};

#endif // LSBARCHART_H
