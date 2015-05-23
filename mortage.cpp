#include "mortage.h"


Mortage::Mortage()
{

}
double Mortage::MonthlyPayment()
{
    double yRate = 5.00;
    double principal = 5000000;
    int years = 15;

    return CalculateMonthlyPayment(yRate/100/12, principal, years * 12);;
}

double Mortage::MonthlyPayment(double yRate, double principal, int years)
{
    return CalculateMonthlyPayment(yRate/100/12, principal, years * 12);
}

std::vector < std::vector<double> > Mortage::GetPayments(double yRate, double principal, int years)
{
    std::vector<double> mInterest;
    std::vector<double> mPrincipal;
    std::vector<double> mPayment;
    std::vector< std::vector <double> > mPayments;


    double eRate = yRate/100/12;
    int months = years * 12;

    double payment = MonthlyPayment(yRate, principal, years);
    double paymentTowardsPrincipal = 0.0;
    double interest = 0.0;
    for ( int i = 0; i < months; i++ )
    {
        interest = principal * eRate;
        paymentTowardsPrincipal = payment - interest;

        if ( i > 0)
        {
            mInterest.push_back(interest + mInterest.at(i-1));
            mPayment.push_back(paymentTowardsPrincipal + mPayment.at(i-1));
        }
        else
        {
            mInterest.push_back(interest);
            mPayment.push_back(paymentTowardsPrincipal);
        }

        principal -= paymentTowardsPrincipal;
//        if (principal < 0 ) principal = 0;
        mPrincipal.push_back(principal);
    }

    mPayments.push_back(mPayment);
    mPayments.push_back(mInterest);
    mPayments.push_back(mPrincipal);

    return mPayments;
}

double Mortage::CalculateMonthlyPayment(double eRate, double principal, int months)
{
    /*
     * The formula to use when calculating loan payments is
     *payment = principal * ( eRate / (1 - (1 + eRate)^-n))
    */
    return principal * ( eRate / (1 - pow((1 + eRate), -months)));

}
