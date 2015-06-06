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
    double yearlyRate = rate/100; //input is percent
    double totalValue = 0.0;
    double interest = 0.0;
    double payments = 0.0;
    std::vector<double> moneyPaid;
    std::vector<double> interestReceived;
    std::vector<double> savings;

    totalValue += balance;

    for ( i = 1; i <= savingsTime; i++ ) {
        if( paymentTime >= i ) {
            payments = monthlyPayment * 12;
        }
        else
        {
            payments = 0.0;
        }

        interest = yearlyRate * (totalValue + payments);

        moneyPaid.push_back(payments);
        interestReceived.push_back(interest);
        savings.push_back(totalValue);
        totalValue += payments + interest;
    }

    std::vector< std::vector<double> > value;
    value.push_back(moneyPaid);
    value.push_back(savings);
    value.push_back(interestReceived);
    return value;
}
