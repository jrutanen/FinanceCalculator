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

