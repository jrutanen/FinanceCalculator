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

#include "mortage.h"


Mortage::Mortage()
{

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

        if ( i > 0 )
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
        if (principal < 0 ) principal = 0;
        mPrincipal.push_back(principal);
    }

    mPayments.push_back(mPayment);
    mPayments.push_back(mInterest);
    mPayments.push_back(mPrincipal);

    return mPayments;
}

std::vector<std::vector<double> > Mortage::GetFixedAmortizationPayments(double yRate, double principal, int years)
{
    std::vector<double> mInterest;
    std::vector<double> mPrincipal;
    std::vector<double> mPayment;
    std::vector< std::vector <double> > mPayments;

    double eRate = yRate/100/12;
    int months = years * 12;

    double paymentTowardsPrincipal = principal/months;
    double interest = 0.0;
    for ( int i = 0; i < months; i++ )
    {
        interest = principal * eRate;

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


    return mPayments;
}

std::vector<std::vector<double> > Mortage::yearlyPayments(std::vector<std::vector<double> > monthlyData)
{
    std::vector<std::vector<double> > yearlyData;

    for (uint i = 0; i < monthlyData.size(); i++)
    {
        std::vector <double> data;
        for (uint j = 0; j < monthlyData.at(i).size(); j++)
        {
            if ( j == monthlyData.at(i).size() - 1 )
            {
                data.push_back(monthlyData.at(i).at(j));
            }
            else if ((j + 1) % 12 == 0 && j > 0)
            {
                data.push_back(monthlyData.at(i).at(j));
            }
        }
        yearlyData.push_back(data);
    }

    return yearlyData;

}

std::vector < std::vector<double> > Mortage::GetPayments(double yRate, double principal, int years, int loanType)
{
    std::vector< std::vector <double> > mPayments;

    switch(loanType)
    {
        //Fized amortization
        case 1:
            mPayments = GetFixedAmortizationPayments(yRate, principal, years);
            break;
        //Annuity (default)
        default:
            mPayments = GetPayments(yRate, principal, years);
            break;
    }

    return yearlyPayments(mPayments);//mPayments;
}

double Mortage::CalculateMonthlyPayment(double eRate, double principal, int months)
{
    /*
     * The formula to use when calculating loan payments is
     *payment = principal * ( eRate / (1 - (1 + eRate)^-n))
    */
    return principal * ( eRate / (1 - pow((1 + eRate), -months)));

}
