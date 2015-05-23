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
#include "dataset.h"

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

private:
    void drawXAxis(int);
    void drawYAxis(double);
    void drawBar(double, double, double, double, QColor);
    void drawBarWithColor(double, double, double, QColor);
    void drawStackedBarWithColor(double, double, double, QColor);
    void drawSummaryBox(double, double, double, int);

protected:
    bool animation;
    double width;
    double height;
    double canvasWidth;
    double canvasHeight;
    double barWidth;
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
