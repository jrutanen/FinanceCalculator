#include "lsbarchart.h"
#include <QGraphicsSceneHoverEvent>

const QColor colorOne = QColor(Qt::green);
const QColor colorTwo = QColor(Qt::cyan);
const QColor colorThree = QColor(Qt::blue);
const QColor colorFour = QColor(Qt::red);
const QColor cursorColor = QColor(238, 224, 229);
std::vector<QColor> colors;
//QLineF *cursorLine = new QLineF(0, 0, 0, 50);;

LSBarChart::LSBarChart() : QGraphicsScene()
{

}

LSBarChart::LSBarChart(double width, double height) : QGraphicsScene()
{
    this->width = width;
    this->height = height;
    xAxis.width = 75.0;
    xAxis.position = BOTTOM;
    yAxis.width = 75.0;
    yAxis.position = RIGHT;
    canvasHeight = height-xAxis.width;
    canvasWidth = width-yAxis.width;
    leftMargin = 6.0;
    xAxis.length = canvasWidth;
    yAxis.length = canvasHeight;
    xAxis.label.append("Years");
    yAxis.label.append("Value");
    colors.push_back(colorOne);
    colors.push_back(colorThree);
    colors.push_back(colorTwo);
    colors.push_back(colorFour);
}
LSBarChart::~LSBarChart(void)
{

}

void LSBarChart::addSummary( std::vector<DataSet> data)
{
    std::vector<double> values;

    for ( uint i = 0; i < data.size(); i++)
    {
        values.push_back((std::accumulate(data[i].getData().begin(), data[i].getData().end(), 0)));
    }

    drawSummaryBox(values.at(0), values.at(1), values.at(0)+values.at(1), data[0].getData().size());
}

void LSBarChart::drawChart(std::vector<DataSet> data)
{
    dataSets = data;
    int dataPoints = dataSets[0].getData().size();
    gap = 72/dataPoints;
    if (gap < 1) gap = 0.0;
    if ( dataPoints >= 15 && dataPoints <= 36 ) gap = 2.0;
    if ( dataPoints < 15 ) gap = 3.0;
    if ( dataPoints > 36) gap = 0.0;
    barWidth = (canvasWidth - 8 - (dataPoints - 1) * gap)/dataPoints;
    double unitHeight;
    double maxValue = 0.0;
    double maxAxisValue;

    //get max value to adjust the scale
    for (uint i=0; i< dataSets.size(); i++)
    {
        vector<double> values = dataSets[i].getData();
        double max = *max_element(values.begin(), values.end());
        maxValue += max;
    }
    //set max value for axis
    maxAxisValue = calculateMaxAxisValue(maxValue);

    clear();

    drawXAxis(dataPoints);
    drawYAxis(maxAxisValue);

//    cursorLine->setP2(QPoint(0, canvasHeight - 1));
    cursorLine = this->addLine(0, 0, 0, canvasHeight-1, QPen(cursorColor));

    unitHeight = (canvasHeight - 8)/maxAxisValue;

    //Draw stacked bars
    //number of bars
    for (uint i = 0; i < dataSets[0].getData().size(); i++)
    {
        double currentY = 0.0;
        //number of datasets
        for (uint j = 0; j < dataSets.size(); j++)
        {
            drawBar(8 + i*(barWidth + gap), currentY, dataSets[j].getData().at(i)*unitHeight, barWidth, colors.at(j));
            currentY += dataSets[j].getData().at(i)*unitHeight;
        }
    }
}

void LSBarChart::drawXAxis(int max)
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
    this->addLine(leftMargin, y, xAxis.length, y, QPen(Qt::black));
    this->addLine(xAxis.length/2, yAxis.length, xAxis.length/2, yAxis.length + 8, QPen(Qt::black));
    this->addLine(xAxis.length, yAxis.length, xAxis.length, yAxis.length + 8, QPen(Qt::black));
    this->addText(QString("%1 years").arg(max))->setPos(xAxis.length, yAxis.length);
    this->addText(QString("%1 years").arg(floor(max/2)))->setPos(xAxis.length/2, yAxis.length);
    this->addText(xAxis.label)->setPos(0, y);
}

void LSBarChart::drawYAxis(double max)
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
    this->addLine(x, 8, x, yAxis.length, QPen(Qt::black));
    this->addLine(xAxis.length, 8, xAxis.length + 8, 8, QPen(Qt::black));
    this->addLine(xAxis.length, (canvasHeight-8)/2, xAxis.length + 8, (canvasHeight-8)/2, QPen(Qt::black));
    this->addText(QString("%1").arg(max, 0, 'f', 0))->setPos(canvasWidth, 8);
    this->addText(QString("%1").arg(max/2, 0, 'f', 0))->setPos(canvasWidth, (canvasHeight-8)/2);
}

void LSBarChart::drawBar(double x, double y, double height, double width, QColor color)
{
    this->addRect(x, canvasHeight-y - height, width, height, Qt::NoPen, QBrush(color));
}
void LSBarChart::drawBarWithColor(double position, double height, double width, QColor color)
{
    this->addRect(position, canvasHeight-height, width, height, Qt::NoPen, QBrush(color) );
//    const QPen & pen = QPen(), const QBrush & brush = QBrush()
}
void LSBarChart::drawStackedBarWithColor(double position, double height, double width, QColor color)
{
    this->addRect(position, canvasHeight-height, width, height, Qt::NoPen, QBrush(color) );
//    const QPen & pen = QPen(), const QBrush & brush = QBrush()
}
void LSBarChart::drawSummaryBox(double savings, double interest, double total, int years)
{
    int x = 8;
    int y = 8;
    int width = 160;
    int height = 80;
    QRect *bg = new QRect(x, y, width, height);
    QPainter *painter = new QPainter();
    painter->drawRoundedRect(*bg, 40, 40);
   // this->addItem(*bg);
    this->addRect(*bg, Qt::NoPen, QBrush(Qt::cyan));
    this->addText(QString("Total Invested %1\n"
                          "Total Interest %2\n"
                          "Total Value  %3\n"
                          "After %4 years."
                          ).arg(savings,0,'f',0).arg(interest, 0, 'f', 0).arg(total, 0, 'f', 0).arg(years))
                          ->setPos(x+3, y+3);
}
double LSBarChart::calculateMaxAxisValue(double value)
{
    double maxValue = 0.0;
    if(value < 100)
    {
        maxValue = ceil(value + 10)/10;
        maxValue = (int) maxValue * 10;
    }
    if(value >= 100 && value < 1000)
    {
        maxValue = ceil(value + 10)/10;
        maxValue = (int) maxValue * 10;
    }
    if(value >= 1000 && value < 10000)
    {
        maxValue = ceil(value + 100)/100;
        maxValue = (int) maxValue * 100;
    }
    if(value >= 10000 && value < 100000)
    {
        maxValue = ceil(value+1000)/1000;
        maxValue = (int) maxValue * 1000;
    }
    if(value >= 100000 && value < 1000000)
    {
        maxValue = ceil(value+10000)/10000;
        maxValue = (int) maxValue * 10000;
    }
    if(value >= 1000000 && value < 10000000)
    {
        maxValue = ceil(value+100000)/100000;
        maxValue = (int) maxValue * 100000;
    }
    if(value >= 10000000 && value < 100000000)
    {
        maxValue = ceil((value*1.1/1000000)*1000000);maxValue = (int) maxValue * 10;
    }
    if(value >= 100000000)
    {
        maxValue = ceil((value*1.1/10000000)*10000000);maxValue = (int) maxValue * 10;
    }

    return maxValue;
}
void LSBarChart::drawCursorLine(double x)
{
   double dx = x - cursorLine->line().x1();
//   cursorLine->line().setP1(QPoint(x, 0));
//   cursorLine->line().setP2(QPoint(x, canvasHeight-1));
   cursorLine->setPos(x, 0);
//   cursorLine->moveBy(dx, 0);
}

void LSBarChart::mouseMoveEvent(QGraphicsSceneMouseEvent * e)//(QGraphicsSceneHoverEvent *e)
{
    qDebug() << QString("x: %1, y: %2").arg(e->scenePos().x()).arg(e->scenePos().y());
    int x = 0;
    if (e->scenePos().x() > 6 && e->scenePos().x() < canvasWidth + leftMargin)
    {
        x =  (int)(((e->scenePos().x() - leftMargin))/(barWidth + gap));
        if (x < 0) x = 0;
        if (x < (int)dataSets[0].getData().size())
        {
            drawCursorLine(e->scenePos().x());
            drawSummaryBox(dataSets[0].getData().at(x), dataSets[1].getData().at(x), dataSets[2].getData().at(x), x + 1);
        }
    }
}
