#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsScene>
#include <vector>
#include "lsbarchart.h"

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

private:
    Ui::MainWindow *ui;
    QPushButton *pbCalculateInvestmentValue;
    LSBarChart *scene;
    void drawGraph(vector < vector<double> >);
};

#endif // MAINWINDOW_H
