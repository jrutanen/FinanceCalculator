#include "lsbarchart.h"
#include <QDebug>

LSBarChart::LSBarChart() : QGraphicsScene()
{

}

LSBarChart::LSBarChart(double width, double height) : QGraphicsScene()
{
    this->width = width;
    this->height = height;
    xAxis.width = 22.0;
    xAxis.position = BOTTOM;
    yAxis.width = 70.0;
    yAxis.position = RIGHT;
    canvasHeight = height-xAxis.width;
    canvasWidth = width-yAxis.width;
    xAxis.length = canvasWidth;
    yAxis.length = canvasHeight;
    xAxis.label.append("Months");
    yAxis.label.append("Value");
}
LSBarChart::~LSBarChart(void)
{

}

void LSBarChart::drawChart(std::vector<std::vector<double> > data)
{
    int dataPoints = data[0].size();
    double gap;
    if ( dataPoints < 15 ) gap = 3.0;
    if ( dataPoints >= 15 && dataPoints <= 36 ) gap = 2.0;
    if ( dataPoints > 36) gap = 0.0;
    double barWidth = (canvasWidth - (dataPoints - 1) * gap)/dataPoints;
    double unitHeight;
    double maxValue = 0.0;

    for (int i=0; i< data.size(); i++)
    {
        double max = *max_element(data[i].begin(), data[i].end());
        if ( max > maxValue )
        {
            maxValue = max;
        }
    }

    clear();
    drawXAxis();
    drawYAxis();

    unitHeight = canvasHeight/maxValue;

    for (int i = 0; i < data[0].size(); i++)
    {
        drawBarWithColor(0 + i*(barWidth + gap), data[2][i]*unitHeight, barWidth, QColor(Qt::cyan));
        //drawBar(0+i*barWidth, (data[0][i] + data[1][i])*unitHeight, barWidth);
        drawBarWithColor(0 + i*(barWidth + gap), data[0][i]*unitHeight, barWidth, QColor(Qt::green));
    }
}

void LSBarChart::drawXAxis()
{
    double y = 0.0;
    switch ( xAxis.position )
    {
        case BOTTOM:
            y = canvasHeight;
            break;
        case TOP:
            y = 0.0;
            break;
        case MIDDLE:
            y = canvasHeight/2;
            break;
        default:
            y = canvasHeight;
            break;
    }
    this->addLine(0, y, xAxis.length, y, QPen(Qt::black));
    this->addText(xAxis.label)->setPos(0, y);
}

void LSBarChart::drawYAxis()
{
    double x = 0.0;
    switch (yAxis.position)
    {
        case LEFT:
            x = 0.0;
            break;
        case RIGHT:
            x = canvasWidth;
            break;
        case CENTER:
            x = canvasWidth/2;
            break;
        default:
            x = 0.0;
            break;
    }
    this->addLine(x, 0, x, yAxis.length, QPen(Qt::black));
    this->addText(yAxis.label)->setPos(canvasWidth, 0);
}

void LSBarChart::drawBar(double position, double height, double width) {
    this->addRect(position, canvasHeight-height, width, height);
}
void LSBarChart::drawBarWithColor(double position, double height, double width, QColor color) {
    this->addRect(position, canvasHeight-height, width, height, Qt::NoPen, QBrush(color) );
//    const QPen & pen = QPen(), const QBrush & brush = QBrush()
}

