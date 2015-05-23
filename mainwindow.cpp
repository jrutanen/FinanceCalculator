#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //mouse tracking turned on for the gprahics view
    ui->gvInvestments->setMouseTracking(true);

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
    vector<DataSet> *dataset = new vector<DataSet>;
    QString name;
    QString unit = "SEK";
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

    for (uint i = 0; i< values.size(); i++)
    {
        switch ( i )
        {
            case 0:
                name = "Payment";
                break;
            case 1:
                name = "Savings";
                break;
            case 3:
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
    scene = new LSBarChart(view->size().width()-2,
                           view->size().height()-2);

    scene->setBackgroundBrush(Qt::white);

    view->setScene( scene );

    scene->drawChart(data);
//    scene->addSummary(values);
}

void MainWindow::on_pbCalculateMortagePayment_clicked()
{
    vector<DataSet> *dataset = new vector<DataSet>;
    QString name;
    QString unit = "SEK";
    vector< vector<double> > values;
    double payment = 0.0;
    //rate, balance, monthlyPayment, paymentTime, savingsTime
    Mortage *m = new Mortage();
    payment = m->MonthlyPayment(ui->leTopLoanInterest->text().toDouble(),
                                ui->leTopLoan->text().toDouble()+ui->leBottomLoan->text().toDouble(),
                                ui->leMortageYears->text().toDouble());

    ui->leMonthlyMortagePayment->setText(QString("%1").arg(payment, 0, 'f', 0));

    values = m->GetPayments(ui->leTopLoanInterest->text().toDouble(),
                ui->leTopLoan->text().toDouble()+ui->leBottomLoan->text().toDouble(),
                ui->leMortageYears->text().toDouble());

    for (uint i = 0; i< values.size(); i++)
    {
        switch ( i )
        {
            case 0:
                name = "Payment";
                break;
            case 1:
                name = "Savings";
                break;
            case 3:
                name = "Interest";
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
