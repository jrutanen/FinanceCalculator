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
#include "lsbarchart.h"
#include "dataset.h"
#include "ui_mainwindow.h"
#include "investment.h"
#include "mortage.h"
#include "dataset.h"
#include <QDebug>
#include <QtGui>
#include <QGraphicsRectItem>
#include <algorithm>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void handleCalculateInvestment();
    void on_pbCalculateInvestmentValue_clicked();

    void on_pbCalculateMortagePayment_clicked();

    void on_cbInvestmentType_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    QPushButton *pbCalculateInvestmentValue;
//    LSBarChart *scene;
    void drawGraph(QGraphicsView*, vector<DataSet>);
    void skipUserInput();
};

#endif // MAINWINDOW_H
