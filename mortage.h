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

#ifndef MORTAGE_H
#define MORTAGE_H
#include <vector>
#include <cmath>
#include <QDebug>

//! Mortage class.
/*!
  This class contains information about the mortage and calculates the monthly
  mortage cost based on how fast loan shall be paid off (in years).
*/
class Mortage
{
public:
    //! Constructor for the class.
    /*!
    */
    Mortage();

    //! A method to calculate the monthly payment for the mortage.
    /*!
      \param yRate double value containing the yearly interest rate for mortage.
      \param principal double for total amount of mortage.
      \param years int value for amount of years to pay off the mortage.
      \return double montly payment for the mortage.
      \sa Mortage()
    */
    double MonthlyPayment(double yRate, double principal, int years);

    //! A method to calculate the monthly payments for the mortage.
    /*!
      \param yRate double value containing the yearly interest rate for mortage.
      \param principal double for total amount of mortage.
      \param years int value for amount of years to pay off the mortage.
      \param loanType int value for amortization type (fixed, annuity).
      \return vector< vector<double> > yearly values for amount of principal left, total paid
              interest rate and total payments made.
      \sa Mortage()
    */
    std::vector < std::vector<double> > GetPayments(double yRate, double principal,
                                                    int years, int loanType);

private:
    //! A method to calculate the monthly payment for the mortage with annuity.
    /*!
      \param yRate double value containing the yearly interest rate for mortage.
      \param principal double for total amount of mortage.
      \param years int value for amount of years to pay off the mortage.
      \return vector< vector<double> > monthly values for amount of principal left, total paid
              interest rate and total payments made.
      \sa Mortage()
    */
    std::vector < std::vector<double> > GetPayments(double yRate, double principal, int years);

    //! A method to calculate the monthly payment for the mortage with fixed payments towards principal.
    /*!
      \param yRate double value containing the yearly interest rate for mortage.
      \param principal double for total amount of mortage.
      \param years int value for amount of years to pay off the mortage.
      \return vector< vector<double> > monthly values for amount of principal left, total paid
              interest rate and total payments made.
      \sa Mortage()
    */
    std::vector < std::vector<double> > GetFixedAmortizationPayments(double yRate, double principal, int years);

    //! A method to calculate the yearly payment for the mortage based on the monthly values.
    /*!
      \param monthlyData vector< vector<double> > monthly values for amount of principal left, total paid
              interest rate and total payments made
      \return vector< vector<double> > yearly values for amount of principal left, total paid
              interest rate and total payments made.
      \sa Mortage()
    */
    std::vector< std::vector <double> > yearlyPayments( std::vector< std::vector <double> > monthlyData);

    //! A method to calculate the monthly payment for the mortage.
    /*!
      \param eRate double monhly interest rate (yearlyrate/12).
      \param principal double for total amount of mortage.
      \param months int value for amount of months to pay off the mortage.
      \return double monhly payment for the mortage.
      \sa Mortage()
    */
    double CalculateMonthlyPayment(double eRate, double principal, int months);
};

#endif // MORTAGE_H
