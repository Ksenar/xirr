#ifndef XIRR_H
#define XIRR_H

#include <QDate>
#include <cmath>
#include <QtDebug>

class Xirr
{
public:
    Xirr(QList<double> payments,QList<QDate> dateDiapazon,double rate);
    ~Xirr(){}

    double getRate();

private:
    const int MAX_STEPS = {100};
    const double EPSILON = {0.0000001};
    const double dayInYear = {365.0};

    QList<double> values;
    QList<QDate> dates;
    double Rate;
    double Rate1;
    double Rate2;
    double RateN = {0};
    double F1;
    double F2;
    double FN = {0};
    double dF;
    double Scale = {1};
    bool Quit = false;
    int N = {0};
    bool result = true;

    double disc(QDate d, double &v,double &rate);
    double CalcValue(double &rate);
    void setRate();
};

#endif // XIRR_H
