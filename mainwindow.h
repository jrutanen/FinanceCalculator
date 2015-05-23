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

private:
    Ui::MainWindow *ui;
    QPushButton *pbCalculateInvestmentValue;
//    LSBarChart *scene;
    void drawGraph(QGraphicsView*, vector<DataSet>);
    void skipUserInput();
};

#endif // MAINWINDOW_H
