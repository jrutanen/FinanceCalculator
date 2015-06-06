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

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //mouse tracking turned on for the gprahics view
    ui->gvInvestments->setMouseTracking(true);
    ui->tw_cost->setColumnCount(2);
    ui->tw_income->setColumnCount(2);

    addRoot("Monthly Expences", 0.0);

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

void MainWindow::addRoot(QString name, double amount)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->tw_cost);
    item->setText(0, name);
    item->setText(1, QString::number(amount));
    ui->tw_cost->addTopLevelItem(item);
    ui->tw_cost->setHeaderLabels(QStringList() << "Expense Name" << "Amount");

    addChild(item, "Food", 0.0);
    addChild(item, "Utilities", 0.0);
    addChild(item, "Rent", 0.0);

    QTreeWidgetItem *itemIncome = new QTreeWidgetItem(ui->tw_income);
    itemIncome->setText(0, name);
    itemIncome->setText(1, QString::number(amount));
    ui->tw_income->addTopLevelItem(itemIncome);
    ui->tw_income->setHeaderLabels(QStringList() << "income" << "Amount");

    addChild(itemIncome, "Salary", 0.0);
    addChild(itemIncome, "Child Support", 0.0);
    addChild(itemIncome, "Investments", 0.0);
    addChild(itemIncome, "Bonus", 0.0);

}

void MainWindow::addChild(QTreeWidgetItem *parent, QString name, double amount)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, name);
    item->setText(1, QString::number(amount));
    parent->addChild(item);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
}

void MainWindow::on_pbCalculateInvestmentValue_clicked()
{
    vector< vector<double> > values;
    vector<DataSet> *dataset = new vector<DataSet>;
    QString name;
    QString unit = "SEK";
    ui->gvInvestments->resetTransform();
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

    ui->leTotal->setText(QString("%1").arg(values[0].back()+values[1].back()+values[2].back(), 0, 'f', 0));

    for (uint i = 0; i < values.size(); i++)
    {
        switch ( i )
        {
            case 0:
                name = "Payment";
                break;
            case 1:
                name = "Savings";
                break;
            case 2:
                name = "Interest";
                break;
            default:
                name = "N/A";
                break;
        }
        DataSet *data = new DataSet(values.at(i), name, unit);
        dataset->push_back(*data);
    }

    drawGraph(ui->gvInvestments, *dataset);
}
void MainWindow::drawGraph( QGraphicsView *view, vector<DataSet> data)
{
    LSBarChart *scene = new LSBarChart(view->size().width()-2,
                           view->size().height()-2);

    scene->setBackgroundBrush(Qt::white);
    view->setScene( scene );
    view->matrix().reset();
    scene->drawChart(data);
}

void MainWindow::on_pbCalculateMortagePayment_clicked()
{
    vector<DataSet> *dataset = new vector<DataSet>;
    QString name;
    QString unit = "SEK";
    vector< vector<double> > values;
    ui->gvInvestments->resetTransform();
    double payment = 0.0;
    //rate, balance, monthlyPayment, paymentTime, savingsTime
    Mortage *m = new Mortage();
    payment = m->MonthlyPayment(ui->leTopLoanInterest->text().toDouble(),
                                ui->leTopLoan->text().toDouble()+ui->leBottomLoan->text().toDouble(),
                                ui->leMortageYears->text().toDouble());

    ui->leMonthlyMortagePayment->setText(QString("%1").arg(payment, 0, 'f', 0));

    values = m->GetPayments(ui->leTopLoanInterest->text().toDouble(),
                ui->leTopLoan->text().toDouble()+ui->leBottomLoan->text().toDouble(),
                ui->leMortageYears->text().toDouble(), ui->cbPaymentPlan->currentIndex());

    for (uint i = 0; i < values.size(); i++)
    {
        switch ( i )
        {
            case 0:
                name = "Paid";
                break;
            case 1:
                name = "Interest";
                break;
            case 2:
                name = "Principal";
                break;
            default:
                name = "N/A";
                break;
        }

        DataSet *data = new DataSet(values.at(i), name, unit);
        dataset->push_back(*data);
    }
    drawGraph(ui->gvMortage, *dataset);
}

void MainWindow::on_cbInvestmentType_currentIndexChanged(int index)
{
    //Geometric rate of return
    double rate = 0.0;
    switch (index)
    {
        //own choice, do nothing
        case 0:
            rate = 0.0;
            break;
         //S&P 500 1925-2014
        case 1:
            rate = 9.60;
            break;
        //S&P 500 1965-2014
        case 2:
            rate = 9.84;
            break;
        //S&P 500 2005-2014
        case 3:
            rate = 7.60;
            break;
        //US T.Bill 3 Months 1925-2014
        case 4:
            rate = 3.49;
            break;
        //US T.Bill 3 Months 1965-2014
        case 5:
            rate = 4.99;
            break;
        //US T.Bill 3 Months 2005-2014
        case 6:
            rate = 1.42;
            break;
        //US T.Bond 10 Years 1925-2014
        case 7:
            rate = 5.00;
            break;
        //US T.Bond 10 Years 1965-2014
        case 8:
            rate = 6.70;
            break;
        //US T.Bond 10 Years 2005-2014
        case 9:
            rate = 4.88;
            break;
        default:
            break;
    }
    ui->leRate->setText(QString("%1").arg(rate));
}

void MainWindow::on_tw_cost_itemChanged(QTreeWidgetItem *item, int column)
{
    updateAmount(item, column);
}

void MainWindow::on_tw_income_itemChanged(QTreeWidgetItem *item, int column)
{
    updateAmount(item, column);
}

void MainWindow::updateAmount(QTreeWidgetItem *item, int column)
{
    double totalCost = 0.0;
    if (column == 1)
    {
        if (item->parent())
        {
            for (int i = 0; i < item->parent()->childCount(); i++)
            {
//                qDebug() << QString("I'm child nbr %1").arg(i);
                totalCost += item->parent()->child(i)->text(1).toDouble();
            }
            item->parent()->setText(1, QString::number(totalCost));
        }
    }
}



