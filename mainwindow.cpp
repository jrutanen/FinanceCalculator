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
    //initialize db
    ui->setupUi(this);

    //mouse tracking turned on for the gprahics view
    ui->gvInvestments->setMouseTracking(true);

    //connect table view cost to the ´budget model
    mBudgetedCost = new BudgetModel(0);
    //select the type of data to fetch
    mBudgetedCost->setDataType(QString("budgetedExpenses"));
    //add extra column for category data
    mBudgetedCost->setCols(3);
    // set selection model
    QItemSelectionModel *costSelectionModel = new QItemSelectionModel(mBudgetedCost);
    //connect model to the cost tableview
    initializeView(mBudgetedCost, ui->tableViewCost, costSelectionModel);

    //add category combox to the third column
    ComboBoxDelegate *cbDelegate = new ComboBoxDelegate();
    ui->tableViewCost->setItemDelegateForColumn(2, cbDelegate);
    ui->tableViewCost->setColumnWidth(2, 105);

    //connect signals for the cost tableview
    QObject::connect(this, SIGNAL(addCostRow()),
                     mBudgetedCost, SLOT(addRow()));
    QObject::connect(this, SIGNAL(removeCostRow(int)),
                     mBudgetedCost, SLOT(removeRow(int)));
    QObject::connect(this, SIGNAL(monthChanged(int)),
                     mBudgetedCost, SLOT(changeMonth(int)));
    QObject::connect(this, SIGNAL(yearChanged(QString)),
                     mBudgetedCost, SLOT(changeYear(QString)));
    QObject::connect(this, SIGNAL(copyPreviousMonth(QDate)),
                     mBudgetedCost, SLOT(copyFromPreviousMonth(QDate)));
    //copyPreviousMonth(currentMonth)

    //connect table view income to the budget model
    mIncome = new BudgetModel(0);
    //select the type of data to fetch
    mIncome->setDataType(QString("income"));
    // set selection model
    QItemSelectionModel *incomeSelectionModel = new QItemSelectionModel(mIncome);
    //connect model to the tableview
    initializeView(mIncome, ui->tableViewIncome, incomeSelectionModel);

    //connect signals for the cost tableview
    QObject::connect(this, SIGNAL(addIncomeRow()),
                     mIncome, SLOT(addRow()));
    QObject::connect(this, SIGNAL(removeIncomeRow(int)),
                     mIncome, SLOT(removeRow(int)));
    QObject::connect(this, SIGNAL(monthChanged(int)),
                     mIncome, SLOT(changeMonth(int)));
    QObject::connect(this, SIGNAL(yearChanged(QString)),
                     mIncome, SLOT(changeYear(QString)));

    //connect table view loan to the budget model
    mLoans = new BudgetModel(0);
    //select the type of data to fetch
    mLoans->setDataType(QString("loan"));
    // set selection model
    QItemSelectionModel *loanSelectionModel = new QItemSelectionModel(mLoans);
    //connect model to the cost tableview
    initializeView(mLoans, ui->tableViewLoan, loanSelectionModel);

    //connect signals for the cost tableview
    QObject::connect(this, SIGNAL(addLoanRow()),
                     mLoans, SLOT(addRow()));
    QObject::connect(this, SIGNAL(removeLoanRow(int)),
                     mLoans, SLOT(removeRow(int)));
    QObject::connect(this, SIGNAL(monthChanged(int)),
                     mLoans, SLOT(changeMonth(int)));
    QObject::connect(this, SIGNAL(yearChanged(QString)),
                     mLoans, SLOT(changeYear(QString)));

    //connect table view savings to the budget model
    mSavings = new BudgetModel(0);
    //select the type of data to fetch
    mSavings->setDataType(QString("savings"));
    // set selection model
    QItemSelectionModel *savingsSelectionModel = new QItemSelectionModel(mSavings);
    initializeView(mSavings, ui->tableViewSavings, savingsSelectionModel);

    //connect signals for the cost tableview
    QObject::connect(this, SIGNAL(addSavingsRow()),
                     mSavings, SLOT(addRow()));
    QObject::connect(this, SIGNAL(removeSavingsRow(int)),
                     mSavings, SLOT(removeRow(int)));
    QObject::connect(this, SIGNAL(monthChanged(int)),
                     mSavings, SLOT(changeMonth(int)));
    QObject::connect(this, SIGNAL(yearChanged(QString)),
                     mSavings, SLOT(changeYear(QString)));

    mActualCost = new BudgetModel(0);
    //select the type of data to fetch
    mActualCost->setDataType(QString("actualExpenses"));
    //add extra column for category data
    mActualCost->setCols(3);
    // set selection model
    QItemSelectionModel *actualCostSelectionModel = new QItemSelectionModel(mActualCost);
    initializeView(mActualCost, ui->tableViewCostActual, actualCostSelectionModel);

    //add category combox to the third column
    ComboBoxDelegate *cbActualDelegate = new ComboBoxDelegate();
    ui->tableViewCostActual->setItemDelegateForColumn(2, cbActualDelegate);
    ui->tableViewCostActual->setColumnWidth(2, 105);

    //connect signals for the cost tableview
    QObject::connect(this, SIGNAL(addActualCostRow()),
                     mActualCost, SLOT(addRow()));
    QObject::connect(this, SIGNAL(removeActualCostRow(int)),
                     mActualCost, SLOT(removeRow(int)));
    QObject::connect(this, SIGNAL(monthChanged(int)),
                     mActualCost, SLOT(changeMonth(int)));
    QObject::connect(this, SIGNAL(yearChanged(QString)),
                     mActualCost, SLOT(changeYear(QString)));

    //set validators for the lineedits
    QDoubleValidator *vDouble = new QDoubleValidator(0);
    QIntValidator *vInt = new QIntValidator(0);
    ui->leTopLoan->setValidator(vDouble);
    ui->leTopLoanInterest->setValidator(vDouble);
    ui->leRate->setValidator(vDouble);
    ui->leStartBalance->setValidator(vDouble);
    ui->leTotal->setValidator(vDouble);
    ui->leMonthlyPayment->setValidator(vDouble);
    ui->leMortageYears->setValidator(vInt);
    ui->leSavingsTime->setValidator(vInt);
    ui->lePayments->setValidator(vInt);

    //Set current month to the cbMonth combobox
    setComboToCurrentMonth();
    //Set current year to the cbYear combobox
    setComboToCurrentYear();
    //calculate actuals
    updateActualCostLabels();

    //connect model updates to summary update
    QObject::connect(mBudgetedCost, SIGNAL(modelDataUpdated()),
                     this, SLOT(on_modelDataChanged()));
    QObject::connect(mActualCost, SIGNAL(modelDataUpdated()),
                     this, SLOT(on_modelDataChanged()));
}

void MainWindow::handleCalculateInvestment() {

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeView(BudgetModel *model, QTableView *view, QItemSelectionModel *selectionModel)
{
    //connect model to the cost tableview
    view->setModel(model);
    view->setSelectionModel(selectionModel);
    view->setColumnWidth(0, 140);
    view->setColumnWidth(1, 60);
    view->verticalHeader()->sectionResizeMode(QHeaderView::Fixed);
    view->verticalHeader()->setDefaultSectionSize(20);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MainWindow::on_pbCalculateInvestmentValue_clicked()
{
    bool ok;
    QLocale *locale = new QLocale();
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
        Investment inv( locale->toDouble(ui->leRate->text(), &ok),
                        locale->toDouble(ui->leStartBalance->text(), &ok),
                        locale->toDouble(ui->leMonthlyPayment->text(), &ok),
                        ui->lePayments->text().toInt(),
                        ui->leSavingsTime->text().toInt());

        values = inv.CalculateValue( locale->toDouble(ui->leRate->text(), &ok),
                             locale->toDouble(ui->leStartBalance->text(), &ok),
                             locale->toDouble(ui->leMonthlyPayment->text(), &ok),
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
    ui->cbMonthActual->setCurrentIndex(index);
}

void MainWindow::setComboToCurrentYear()
{
    QString date = QDateTime::currentDateTime().toString("yyyy");
    ui->cbYear->setCurrentText(date); //setCurrent(index);
    ui->cbYearActual->setCurrentText(date); //setCurrent(index);
}

void MainWindow::updateActualCostLabels()
{
    vector<double> budgetedCosts;
    vector<double> actualCosts;
    //Food(0), Housing(1), Utilities(2), Transportation(3), Clothing(4),
    //Personal(5), Saving(6), Total(7)
    budgetedCosts = mBudgetedCost->getCategorySummary();
    actualCosts = mActualCost->getCategorySummary();
    //Food
    ui->lbFoodBudget->setText(QString::number(budgetedCosts.at(0)));
    ui->lbFoodCost->setText(QString::number(actualCosts.at(0)));
    ui->lbFoodLeft->setText(QString::number(budgetedCosts.at(0)-actualCosts.at(0)));
    //Housing
    ui->lbHousingBudget->setText(QString::number(budgetedCosts.at(1)));
    ui->lbHousingCost->setText(QString::number(actualCosts.at(1)));
    ui->lbHousingLeft->setText(QString::number(budgetedCosts.at(1)-actualCosts.at(1)));
    //Utilities
    ui->lbUtilitiesBudget->setText(QString::number(budgetedCosts.at(2)));
    ui->lbUtilitiesCost->setText(QString::number(actualCosts.at(2)));
    ui->lbUtilitiesLeft->setText(QString::number(budgetedCosts.at(2)-actualCosts.at(2)));
    //Transportation
    ui->lbTransportationBudget->setText(QString::number(budgetedCosts.at(3)));
    ui->lbTransportationCost->setText(QString::number(actualCosts.at(3)));
    ui->lbTransportationLeft->setText(QString::number(budgetedCosts.at(3)-actualCosts.at(3)));
    //Clothing
    ui->lbClothingBudget->setText(QString::number(budgetedCosts.at(4)));
    ui->lbClothingCost->setText(QString::number(actualCosts.at(4)));
    ui->lbClothingLeft->setText(QString::number(budgetedCosts.at(4)-actualCosts.at(4)));
    //Personal
    ui->lbPersonalBudget->setText(QString::number(budgetedCosts.at(5)));
    ui->lbPersonalCost->setText(QString::number(actualCosts.at(5)));
    ui->lbPersonalLeft->setText(QString::number(budgetedCosts.at(5)-actualCosts.at(5)));
    //Saving
    ui->lbSavingBudget->setText(QString::number(budgetedCosts.at(6)));
    ui->lbSavingCost->setText(QString::number(actualCosts.at(6)));
    ui->lbSavingLeft->setText(QString::number(budgetedCosts.at(6)-actualCosts.at(6)));
    //Total
    ui->lbTotalBudget->setText(QString::number(budgetedCosts.at(7)));
    ui->lbTotalCost->setText(QString::number(actualCosts.at(7)));
    ui->lbTotalLeft->setText(QString::number(budgetedCosts.at(7)-actualCosts.at(7)));

}

void MainWindow::on_pbCalculateMortagePayment_clicked()
{
    bool ok;
    QLocale *locale = new QLocale();
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

        payment = m->MonthlyPayment(locale->toDouble(ui->leTopLoanInterest->text(), &ok),
                                    locale->toDouble(ui->leTopLoan->text(), &ok),
                                    ui->leMortageYears->text().toInt());

        ui->leMonthlyMortagePayment->setText(QString("%1").arg(payment, 0, 'f', 0));

        values = m->GetPayments(locale->toDouble(ui->leTopLoanInterest->text(), &ok),
                                locale->toDouble(ui->leTopLoan->text(), &ok),
                                ui->leMortageYears->text().toInt(),
                                ui->cbPaymentPlan->currentIndex());

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
    emit addLoanRow();
}

void MainWindow::on_pbRemoveLoan_clicked()
{
    emit removeLoanRow(ui->tableViewLoan->selectionModel()->currentIndex().row());
}

void MainWindow::on_pbAddSavings_clicked()
{
    emit addSavingsRow();
}

void MainWindow::on_pbRemoveSavings_clicked()
{
    emit removeSavingsRow(ui->tableViewSavings->selectionModel()->currentIndex().row());
}

void MainWindow::on_pbSave_clicked()
{
    qDebug() << QString("save button clicked");
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
}

void MainWindow::on_cbMonth_currentIndexChanged(int index)
{
    emit monthChanged(index + 1);
    ui->cbMonthActual->setCurrentIndex(index);
}

void MainWindow::on_cbYear_currentIndexChanged(const QString &year)
{
    emit yearChanged(year);
    ui->cbYearActual->setCurrentText(year);
}

void MainWindow::on_pbCopyPreviousMonth_clicked()
{
    QDate currentMonth = QDate(ui->cbYear->currentText().toInt(),
                               ui->cbMonth->currentIndex() + 1,
                               1);
    emit copyPreviousMonth(currentMonth);
}

void MainWindow::on_pbAddCostActual_clicked()
{
    emit addActualCostRow();
}

void MainWindow::on_pbRemoveCostActual_clicked()
{
    emit removeActualCostRow(ui->tableViewCostActual->selectionModel()->currentIndex().row());
}

void MainWindow::on_cbMonthActual_currentIndexChanged(int index)
{
    emit monthChanged(index + 1);
    ui->cbMonth->setCurrentIndex(index);
    updateActualCostLabels();
}

void MainWindow::on_cbYearActual_currentIndexChanged(const QString &year)
{
    emit yearChanged(year);
    ui->cbYear->setCurrentText(year);
    updateActualCostLabels();
}

void MainWindow::on_modelDataChanged()
{
    updateActualCostLabels();
}
