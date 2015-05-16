#ifndef INVESTMENT_H
#define INVESTMENT_H
#include <vector>


class Investment
{
    private :
        double rate;
        double balance;
        double monthlyPayment;
        int paymentTime;
        int savingsTime;
    public :
        Investment(double, double, double, int, int);
        std::vector< std::vector<double> > CalculateValue(double, double, double, int, int);
};

#endif // INVESTMENT_H
