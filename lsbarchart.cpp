#include "lsbarchart.h"

//const QColor colorOne = QColor(Qt::green);
//const QColor colorTwo = QColor(Qt::cyan);
//const QColor colorThree = QColor(Qt::blue);
//const QColor colorFour = QColor(Qt::red);
const QColor colorOne = QColor(238, 64, 0);
const QColor colorTwo = QColor(255, 130, 71);
const QColor colorThree = QColor(244, 164, 96);
const QColor colorFour = QColor(227, 168, 105);
const QColor cursorColor = QColor(209, 209, 209);

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
    colors.push_back(colorTwo);
    colors.push_back(colorThree);
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
}

void LSBarChart::drawChart(std::vector<DataSet> data)
{
    dataSets = data;
    unsigned long int dataPoints = dataSets[0].getData().size();
    gap = 72/dataPoints;
    if (gap < 1) gap = 0.0;
    if ( dataPoints >= 15 && dataPoints <= 36 ) gap = 2.0;
    if ( dataPoints < 15 ) gap = 3.0;
    if ( dataPoints > 36) gap = 0.0;
    barWidth = (canvasWidth - 8 - (dataPoints - 1) * gap)/dataPoints;
    double maxAxisValue;

    //set max value for axis
    maxAxisValue = calculateMaxAxisValue(calculateMaxDataValue(data));

    clear();

    drawXAxis(dataPoints);
    drawYAxis(maxAxisValue);
    drawLegend();

    cursorLine = this->addLine(0, canvasHeight-2, 0, canvasHeight-1, QPen(cursorColor));
    cursorLine->setZValue(1);
    infoBox = new InfoBox();
    this->addItem(infoBox);
    infoBox->setVisible(false);

    infoText = new QGraphicsTextItem();
    infoText->setZValue(infoBox->zValue() + 1);
    infoText->setPos(QPoint(infoBox->pos().x() + 20, infoBox->pos().y() + 2));
    this->addItem(infoText);

    unitHeight = (canvasHeight - 8)/maxAxisValue;

    //Draw stacked bars
    //number of bars
    for (unsigned long int i = 0; i < dataSets[0].getData().size(); i++)
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

void LSBarChart::drawLegend()
{
    int rectSize = 10;
    int y = canvasHeight + 25;
    int x = 30;
    QGraphicsTextItem *text;
    for ( uint i = 0; i < dataSets.size(); i++ )
    {
        this->addRect(x, y, rectSize, rectSize, QPen(Qt::black), QBrush(colors.at(i)) );
        x += rectSize +3;
        y -= rectSize-3;
        text = this->addText(QString("%1").arg(dataSets[i].getName()));
        text->setPos(x, y);
        x += text->boundingRect().width() + 5;
        y += rectSize-3;

    }
}

void LSBarChart::drawBar(double x, double y, double height, double width, QColor color)
{
    this->addRect(x, canvasHeight-y - height, width, height, Qt::NoPen, QBrush(color));
}
void LSBarChart::drawBarWithColor(double position, double height, double width, QColor color)
{
    this->addRect(position, canvasHeight-height, width, height, Qt::NoPen, QBrush(color) );
}
void LSBarChart::drawStackedBarWithColor(double position, double height, double width, QColor color)
{
    this->addRect(position, canvasHeight-height, width, height, Qt::NoPen, QBrush(color) );
}

void LSBarChart::addInfoText(QString text)
{
    infoText->setPlainText(text);
    infoText->setPos(QPoint(infoBox->pos().x() + 20, infoBox->pos().y() + 2));
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
        maxValue = (unsigned long int ) maxValue * 1000;
    }
    if(value >= 100000 && value < 1000000)
    {
        maxValue = ceil(value+10000)/10000;
        maxValue = (unsigned long int ) maxValue * 10000;
    }
    if(value >= 1000000 && value < 10000000)
    {
        maxValue = ceil(value+100000)/100000;
        maxValue = (unsigned long int ) maxValue * 100000;
    }
    if(value >= 10000000 && value < 100000000)
    {
        maxValue = ceil(value+1000000)/1000000;
        maxValue = (unsigned long int ) maxValue * 1000000;
    }
    if(value >= 100000000)
    {
        maxValue = ceil(value+10000000)/10000000;
        maxValue = (unsigned long int ) maxValue * 10000000;
    }

    return maxValue;
}


void LSBarChart::drawCursorLine(double x, double y)
{
   double cX = x;
   double cY = canvasHeight - y;
   QPoint *p = new QPoint((int)cX,(int)cY);
   if (canvasHeight - 1 - y - 20 > 0)
   {
       cursorLine->setLine(x, canvasHeight - 1 - y - 20, x, canvasHeight-1);
   }
   else
   {
       cursorLine->setLine(x, 0, x, canvasHeight-1);
   }
   infoBox->moveToPoint(p);
   infoBox->setVisible(true);
}

double LSBarChart::calculateMaxDataValue(std::vector<DataSet> data)
{
    double maxValue = 0.0;
    vector<int> posMaxValue;
    //get max value to adjust the scale
    for (uint i=0; i< data.size(); i++)
    {
        vector<double> values = data[i].getData();
        int mPos = distance(values.begin(), max_element(values.begin(), values.end()));
        posMaxValue.push_back(mPos);
    }
    for (uint i = 0; i< posMaxValue.size(); i++)
    {
        double maxTest = 0.0;
        for (uint j=0; j< data.size(); j++)
        {
            vector<double> values = data[j].getData();
            maxTest += values.at(posMaxValue.at(i));
        }
        if(maxTest > maxValue) maxValue = maxTest;
    }
    return maxValue;
}

void LSBarChart::mouseMoveEvent(QGraphicsSceneMouseEvent * e)//(QGraphicsSceneHoverEvent *e)
{
    int x = 0;
    if (e->scenePos().x() > 6 && e->scenePos().x() < canvasWidth + leftMargin)
    {
        x =  (int)(((e->scenePos().x() - leftMargin))/(barWidth + gap));
        if (x < 0) x = 0;
        if (x < (int)dataSets[0].getData().size())
        {
            double y = (dataSets[0].getData().at(x)
                      + dataSets[1].getData().at(x)
                      + dataSets[2].getData().at(x))
                      * unitHeight;
            drawCursorLine(e->scenePos().x(), y);
//            qDebug() << QString("x: %1, y: %2, height: %3").arg(e->scenePos().x()).arg(e->scenePos().y()).arg(y);
            addInfoText(QString("%1: %2\n"
                                "%3: %4\n"
                                "%5: %6")
                                .arg(dataSets[0].getName())
                                .arg(dataSets[0].getData().at(x), 0, 'f', 0)
                                .arg(dataSets[1].getName())
                                .arg(dataSets[1].getData().at(x), 0, 'f', 0)
                                .arg(dataSets[2].getName())
                                .arg(dataSets[2].getData().at(x), 0, 'f', 0));
        }
    }
}
