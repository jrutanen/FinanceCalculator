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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsScene>
#include <vector>
#include <QDebug>
#include <QtGui>
#include <QGraphicsRectItem>
#include <QTreeWidgetItem>
#include <algorithm>
#include <QTreeWidgetItemIterator>
#include <QDateTime>
#include <QMessageBox>
#include <QLocale>
#include "lsbarchart.h"
#include "dataset.h"
#include "ui_mainwindow.h"
#include "investment.h"
#include "mortage.h"
#include "dataset.h"
#include "dbmanager.h"
#include "budgetmodel.h"
#include "comboboxdelegate.h"

using namespace std;

namespace Ui {

//! MainWindow class.
/*!
    Main Window for the application.
*/

class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addRoot(QTreeWidget *widget, QString name, double amount);
    void addChild(QTreeWidgetItem *parent, QString name, double amount);
    void addChildFromDB(QTreeWidgetItem *parent, QString name, QString amount, QString id);

private:
    BudgetModel* mBudgetedCost;
    BudgetModel* mActualCost;
    BudgetModel* mIncome;
    BudgetModel* mLoans;
    BudgetModel* mSavings;
    void initializeView(BudgetModel* model, QTableView *view, QItemSelectionModel *selectionModel);

protected:

private slots:
    void handleCalculateInvestment();
    void on_pbCalculateInvestmentValue_clicked();
    void on_pbCalculateMortagePayment_clicked();
    void on_cbInvestmentType_currentIndexChanged(int index);
    void on_pbAddCost_clicked();
    void on_pbRemoveCost_clicked();
    void on_pbAddIncome_clicked();
    void on_pbRemoveIncome_clicked();
    void on_pbAddLoan_clicked();
    void on_pbRemoveLoan_clicked();
    void on_pbAddSavings_clicked();
    void on_pbRemoveSavings_clicked();
    void on_pbSave_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_cbMonth_currentIndexChanged(int index);
    void on_cbYear_currentIndexChanged(const QString &year);
    void on_pbCopyPreviousMonth_clicked();
    void on_pbAddCostActual_clicked();
    void on_pbRemoveCostActual_clicked();
    void on_cbMonthActual_currentIndexChanged(int index);
    void on_cbYearActual_currentIndexChanged(const QString &year);
    void on_modelDataChanged();

private:
    Ui::MainWindow *ui;
    QPushButton *pbCalculateInvestmentValue;
    void drawGraph(QGraphicsView*, vector<DataSet>);
    void setComboToCurrentMonth();
    void setComboToCurrentYear();
    void updateActualCostLabels();

signals:
    void addCostRow();
    void removeCostRow(int);
    void addActualCostRow();
    void removeActualCostRow(int);
    void addIncomeRow();
    void removeIncomeRow(int);
    void addLoanRow();
    void removeLoanRow(int);
    void addSavingsRow();
    void removeSavingsRow(int);
    void monthChanged(int);
    void yearChanged(QString);
    void copyPreviousMonth(QDate);
};

#endif // MAINWINDOW_H
