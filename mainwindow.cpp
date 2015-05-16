#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "investment.h"
#include <QDebug>
#include <QtGui>
#include <QGraphicsRectItem>
#include <algorithm>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene* scene = new QGraphicsScene(0, 0,
                                              ui->gvInvestments->size().width()-2,
                                              ui->gvInvestments->size().height()-2);
    scene->setBackgroundBrush(Qt::white);

    ui->gvInvestments->setScene( scene );
}

void MainWindow::handleCalculateInvestment() {

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbCalculateInvestmentValue_clicked()
{
    vector< vector<double> > values;
    //rate, balance, monthlyPayment, paymentTime, savingsTime
    Investment inv( ui->leRate->text().toDouble(),
                    ui->leStartBalance->text().toDouble(),
                    ui->leMonthlyPayment->text().toDouble(),
                    ui->lePayments->text().toInt(),
                    ui->leSavingsTime->text().toInt());

    values = inv.CalculateValue( ui->leRate->text().toDouble(),
                         ui->leStartBalance->text().toDouble(),
                         ui->leMonthlyPayment->text().toDouble(),
                         ui->lePayments->text().toInt(),
                         ui->leSavingsTime->text().toInt() );

    drawGraph(values);
    //  delete inv;
}
void MainWindow::drawGraph( vector < vector<double> > data)
{
    double barWidth = 0.0;
    double x = 0.0;
    uint i = 0, j = 0;
    double xAxisMarks = 20.0;
    double ceiling = 20.0;
    double yAxisMarks = 80.0;
    double yAxis = ui->gvInvestments->scene()->height();
    double maxValue = *max_element(data[2].begin(),data[2].end());
    double multiplier = (yAxis-xAxisMarks-ceiling)/maxValue;
    double sHeight = 0.0;

    ui->gvInvestments->scene()->clear();

    //calculate width of the bar
    barWidth = (ui->gvInvestments->scene()->width()-yAxisMarks)/data[1].size();
    qDebug() << barWidth;

    //Draw axis and add marks
    QGraphicsTextItem* value = new QGraphicsTextItem;
    value->setPlainText(QString::number(maxValue));
    value->setPos(ui->gvInvestments->scene()->width()-value->boundingRect().width(),0);
    ui->gvInvestments->scene()->addItem(value);
    yAxisMarks = value->boundingRect().width();

    for(vector<double>::iterator it = data[1].begin(); it != data[1].end(); ++it)
    {
        QGraphicsRectItem* total = new QGraphicsRectItem(x,
                                      yAxis - data[2][i]*multiplier-xAxisMarks,
                                      barWidth,
                                      data[2][i]*multiplier);
        total->setBrush(QBrush(Qt::darkCyan));
        total->setPen(QPen(Qt::NoPen));
        ui->gvInvestments->scene()->addItem(total);

        if ( i < data[0].size()-1 )
        {
            sHeight = data[0][j]*multiplier;
            j++;
        } else {
            sHeight = data[0][j]*multiplier;
        }

        QGraphicsRectItem* savings = new QGraphicsRectItem(x,
                                     yAxis-sHeight-xAxisMarks,
                                     barWidth,
                                     sHeight);

        savings->setBrush(QBrush(Qt::blue));
        savings->setPen(QPen(Qt::NoPen));
        ui->gvInvestments->scene()->addItem(savings);
/*
        QGraphicsRectItem* interest = new QGraphicsRectItem(x,
                                      yAxis - sHeight - data[1][i]*multiplier,
                                      barWidth,
                                      data[1][i]*multiplier);
        interest->setBrush(QBrush(Qt::green));
        interest->setPen(QPen(Qt::NoPen));
        ui->gvInvestments->scene()->addItem(interest);
*/
        x += barWidth;
        i++;
    }

}
