#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "investment.h"
#include <QDebug>
#include <QtGui>
#include <QGraphicsRectItem>
#include <algorithm>

#define NO_USER_INPUT

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new LSBarChart(ui->gvInvestments->size().width()-2,
                                       ui->gvInvestments->size().height()-2);
    scene->setBackgroundBrush(Qt::white);

    ui->gvInvestments->setScene( scene );

#ifdef NO_USER_INPUT
    skipUserInput();
#endif
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

    ui->leTotal->setText(QString("%1").arg(values[2].back(), 0, 'f', 0));

    scene->drawChart( values );
    //  delete inv;
}
void MainWindow::drawGraph( vector < vector<double> > data)
{
}
void MainWindow::skipUserInput()
{
    vector< vector<double> > values;
    //rate, balance, monthlyPayment, paymentTime, savingsTime
    Investment inv( 10.0,
                    0.0,
                    1000,
                    24,
                    10);

    values = inv.CalculateValue( 10.0,
                                 0.0,
                                 1000,
                                 24,
                                 10 );

    scene->drawChart( values );
}
