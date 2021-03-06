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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Financial Calculator.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TESTINTERESTCALC_H
#define TESTINTERESTCALC_H
#include <QtTest/QtTest>
#include <vector>
#include "investment.h"


class TestInterestCalc : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void oneMonth();

protected:
    double rate, balance, monthlyPayment;
    int paymentTime, savingsTime;
};

#endif // TESTINTERESTCALC_H

