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
