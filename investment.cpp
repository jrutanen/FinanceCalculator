#include "investment.h"
#include <vector>

using namespace std;

Investment::Investment(double rate, double balance, double monthlyPayment, int paymentTime, int savingsTime)
{
    this->rate = rate;
    this->balance = balance;
    this->monthlyPayment = monthlyPayment;
    this->paymentTime = paymentTime;
    this->savingsTime = savingsTime;
}
vector< vector<double> > Investment :: CalculateValue (double rate, double balance, double monthlyPayment, int paymentTime, int savingsTime) {
    int i = 1;
    int savingsTimeInMonths = savingsTime * 12;
    double monthlyRate = rate/12/100; //input is percent
    double totalValue = 0.0;
    double interest = 0.0;
    double payments = 0.0;
    std::vector<double> moneyPaid;
    std::vector<double> interestReceived;
    std::vector<double> valueOfInvestment;

    totalValue = totalValue + balance;

    for ( i = 1; i <= savingsTimeInMonths; i++ ) {
        interest = monthlyRate * totalValue;
        if ( i <= paymentTime) {
            payments += monthlyPayment;
            totalValue += monthlyPayment;
        }
        totalValue += interest;
        moneyPaid.push_back(payments);
        interestReceived.push_back(interest);
        valueOfInvestment.push_back(totalValue);
    }

    std::vector< std::vector<double> > value;
    value.push_back(moneyPaid);
    value.push_back(interestReceived);
    value.push_back(valueOfInvestment);
    return value;
}
