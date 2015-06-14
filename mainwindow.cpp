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
    dbManager = new DBManager();
    ui->setupUi(this);
    //Set current month to the cbMonth combobox
    setComboToCurrentMonth();
    //mouse tracking turned on for the gprahics view
    ui->gvInvestments->setMouseTracking(true);

    //connect table view cost to the ´budget model
    mBudgetedCost = new BudgetModel(0);
    //update month to the data model
    mBudgetedCost->setMonth(ui->cbMonth->currentIndex() + 1);
    //select the type of data to fetch
    mBudgetedCost->setDataType(QString("budgetedExpenses"));
    // set selection model
    QItemSelectionModel *selectionModel = new QItemSelectionModel(mBudgetedCost);

    //connect model to the tableview
    ui->tableViewCost->setModel(mBudgetedCost);
    ui->tableViewCost->setSelectionModel(selectionModel);
    ui->tableViewCost->setColumnWidth(0, 230);
    ui->tableViewCost->setColumnWidth(1, ui->tableViewCost->width() - 240);
    ui->tableViewCost->verticalHeader()->sectionResizeMode(QHeaderView::Fixed);
    ui->tableViewCost->verticalHeader()->setDefaultSectionSize(20);
    ui->tableViewCost->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QObject::connect(this, SIGNAL(addCostRow()),
                     mBudgetedCost, SLOT(addRow()));
    QObject::connect(this, SIGNAL(monthChanged(int)),
                     mBudgetedCost, SLOT(changeMonth(int)));
    QObject::connect(this, SIGNAL(removeCostRow(int)),
                     mBudgetedCost, SLOT(removeRow(int)));

    mActualCost = new BudgetModel(0);

    //connect table view income to the budget model
    mIncome = new BudgetModel(0);
    //update month to the data model
    mIncome->setMonth(ui->cbMonth->currentIndex() + 1);
    //select the type of data to fetch
    mIncome->setDataType(QString("income"));
    // set selection model
//    QItemSelectionModel *selectionModelIncome = new QItemSelectionModel(mIncome);

    QObject::connect(this, SIGNAL(addIncomeRow()),
                     mIncome, SLOT(addRow()));
    QObject::connect(this, SIGNAL(monthChanged(int)),
                     mIncome, SLOT(changeMonth(int)));
    QObject::connect(this, SIGNAL(removeIncomeRow(int)),
                     mIncome, SLOT(removeRow(int)));

    //connect model to the tableview
    ui->tableViewIncome->setModel(mIncome);
    ui->tableViewIncome->setSelectionModel(selectionModel);
    ui->tableViewIncome->setColumnWidth(0, 230);
    ui->tableViewIncome->setColumnWidth(1, ui->tableViewIncome->width() - 240);
    ui->tableViewIncome->verticalHeader()->sectionResizeMode(QHeaderView::Fixed);
    ui->tableViewIncome->verticalHeader()->setDefaultSectionSize(20);
    ui->tableViewIncome->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //one extra hidden column for id
    ui->twLoan->setColumnCount(3);
    ui->twLoan->hideColumn(2);
    ui->twSavings->setColumnCount(3);
    ui->twSavings->hideColumn(2);

    addRoot(ui->twLoan, "Creditor", 0.0);
    addRoot(ui->twSavings, "Investment", 0.0);
}

void MainWindow::handleCalculateInvestment() {

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addRoot(QTreeWidget *widget, QString name, double amount)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(widget);
    //Format header
    widget->setHeaderLabels(QStringList() << name << "Amount");
    widget->header()->resizeSection(0, 230);

    item->setText(0, "Total");
    item->setText(1, QString::number(amount));
    widget->addTopLevelItem(item);
}

void MainWindow::addChild(QTreeWidgetItem *parent, QString name, double amount)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, name);
    item->setText(1, QString::number(amount));
    parent->addChild(item);
    item->setFlags(item->flags() | Qt::ItemIsEditable);

    if(!parent->isExpanded())
    {
        parent->setExpanded(true);
    }
}

void MainWindow::addChildFromDB(QTreeWidgetItem *parent, QString name, QString amount, QString id)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, name);
    item->setText(1, amount);
    item->setText(2, id);
    parent->addChild(item);
    item->setFlags(item->flags() | Qt::ItemIsEditable);

    if(!parent->isExpanded())
    {
        parent->setExpanded(true);
    }
}

void MainWindow::on_pbCalculateInvestmentValue_clicked()
{
    bool fieldsNotEmpty = false;
    vector< vector<double> > values;
    vector<DataSet> *dataset = new vector<DataSet>;
    QString name;
    QString unit = "SEK";
    ui->gvInvestments->resetTransform();

    fieldsNotEmpty = (ui->leRate->text() != "" && ui->leMonthlyPayment->text() != "" && ui->lePayments->text() != "");
    if (fieldsNotEmpty)
    {
        if (ui->leSavingsTime->text() == "")
        {
            ui->leSavingsTime->setText(ui->lePayments->text());
        }

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
    } //if (fieldsNotEmpty)
    else
    {
        //show message box
        QMessageBox msgBox;
        msgBox.setText("Please fill in the required information.");
        msgBox.setStandardButtons(QMessageBox::Close);
        int ret = msgBox.exec();
    }
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

void MainWindow::setComboToCurrentMonth()
{
    QString date = QDateTime::currentDateTime().toString("M");
    int index = date.toInt() - 1;
    ui->cbMonth->setCurrentIndex(index);
}

void MainWindow::on_pbCalculateMortagePayment_clicked()
{
    bool fieldsNotEmpty = false;
    vector<DataSet> *dataset = new vector<DataSet>;
    QString name;
    QString unit = "SEK";
    vector< vector<double> > values;
    ui->gvInvestments->resetTransform();
    double payment = 0.0;
    //rate, balance, monthlyPayment, paymentTime, savingsTime
    Mortage *m = new Mortage();

    fieldsNotEmpty = (ui->leTopLoanInterest->text() != "" && ui->leTopLoan->text() != "" && ui->leMortageYears->text() != "");

    if (fieldsNotEmpty)
    {

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
    else
    {
        //show message box
        QMessageBox msgBox;
        msgBox.setText("Please fill in the required information.");
        msgBox.setStandardButtons(QMessageBox::Close);
        int ret = msgBox.exec();
    }
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

void MainWindow::on_twCost_itemChanged(QTreeWidgetItem *item, int column)
{
    updateAmount(item, column);
}

void MainWindow::on_twIncome_itemChanged(QTreeWidgetItem *item, int column)
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
                totalCost += item->parent()->child(i)->text(1).toDouble();
            }
            item->parent()->setText(1, QString::number(totalCost));
        }
    }
}

void MainWindow::on_pbAddCost_clicked()
{
    emit addCostRow();
}

void MainWindow::on_pbRemoveCost_clicked()
{
    emit removeCostRow(ui->tableViewCost->selectionModel()->currentIndex().row());
}

void MainWindow::on_pbAddIncome_clicked()
{
    emit addIncomeRow();
}

void MainWindow::on_pbRemoveIncome_clicked()
{
    emit removeIncomeRow(ui->tableViewIncome->selectionModel()->currentIndex().row());
}

void MainWindow::on_pbAddLoan_clicked()
{
    addChild(ui->twLoan->topLevelItem(0), "Creditor", 0.0);
}

void MainWindow::on_pbRemoveLoan_clicked()
{
    QList<QTreeWidgetItem *> itemList = ui->twLoan->selectedItems();
    for (int i = 0; i < itemList.size(); i++)
    {
        itemList.at(i)->~QTreeWidgetItem();
    }
}

void MainWindow::on_pbAddSavings_clicked()
{
    addChild(ui->twSavings->topLevelItem(0), "Investment", 0.0);
}

void MainWindow::on_pbRemoveSavings_clicked()
{
    QList<QTreeWidgetItem *> itemList = ui->twSavings->selectedItems();
    for (int i = 0; i < itemList.size(); i++)
    {
        itemList.at(i)->~QTreeWidgetItem();
    }
}

void MainWindow::on_pbSave_clicked()
{
    qDebug() << QString("save button clicked");
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 2)
    {
        //Set current month to the cbMonth combobox
        setComboToCurrentMonth();
    }
}

void MainWindow::on_cbMonth_currentIndexChanged(int index)
{
    emit monthChanged(index + 1);
}
