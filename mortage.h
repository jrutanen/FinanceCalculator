#ifndef MORTAGE_H
#define MORTAGE_H
#include <vector>
#include <cmath>
#include <QDebug>

class Mortage
{
public:
    Mortage();
    double MonthlyPayment();
    double MonthlyPayment(double, double, int);
    std::vector < std::vector<double> > GetPayments(double, double, int, int);
private:
    std::vector < std::vector<double> > GetPayments(double, double, int);
    std::vector < std::vector<double> > GetFixedAmortizationPayments(double, double, int);
    double CalculateMonthlyPayment(double, double, int);
};

#endif // MORTAGE_H
