#include "testinterestcalc.h"

void TestInterestCalc::initTestCase()
{
    rate = 0.0;
    balance = 0.0;
    monthlyPayment = 0.0;
    paymentTime = 0;
    savingsTime = 12;
/*
    inv =  new Investment( rate,
                              balance,
                              monthlyPayment,
                              paymentTime,
                              savingsTime);
*/
}

void TestInterestCalc::oneMonth()
{
    Investment *inv = new Investment( rate,
                              balance,
                              monthlyPayment,
                              paymentTime,
                              savingsTime);

    std::vector< std::vector<double> > values = inv->CalculateValue( rate,
                                 balance,
                                 monthlyPayment,
                                 paymentTime,
                                 savingsTime );

    QVERIFY(values[0].size() == savingsTime * 12);
}
//Not working needs to be fixed, maybe move to Google Test???
//QTEST_MAIN(TestInterestCalc)
//#include "testinterestcalc.moc"

