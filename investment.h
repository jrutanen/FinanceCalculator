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

#ifndef INVESTMENT_H
#define INVESTMENT_H
#include <vector>

//!  Investment class.
/*!
  This class contains information about the investments and savings and calculate future
  growth for the investment.
*/

class Investment
{
public :
    //! Constructor for the class.
    /*!
      \param rate double value containing the yearly growth rate for the investment.
      \param balance double current amount of investments.
      \param monthlyPayment double value for monhly saving.
      \param paymentTime int value for years of added monthly savings.
      \param savingsTime int value for total time of savings.
    */
    Investment(double rate, double balance, double monthlyPayment, int paymentTime, int savingsTime);

    //! A method to calculate the compouded interest for the investments.
    /*!
      \param rate double value containing the yearly growth rate for the investment.
      \param balance double current amount of investments.
      \param monthlyPayment double value for monhly saving.
      \param paymentTime int value for years of added monthly savings.
      \param savingsTime int value for total time of savings.
      \return vector<double> with yearly values for added savings, added interest and savings from previous year.
      \sa Investment()
    */
    std::vector< std::vector<double> > CalculateValue(double rate, double balance, double monthlyPayment, int paymentTime, int savingsTime);
private :
    //! Yearly rate of return for the investment
    double rate;

    //! Starting balance in the investments account
    double balance;

    //! Monthly savings
    double monthlyPayment;

    //! Amount of years for monthly additions to the savings
    int paymentTime;

    //! Amount of years the investment is compounding
    int savingsTime;
};

#endif // INVESTMENT_H
