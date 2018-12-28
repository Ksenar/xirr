#include "xirr.h"

Xirr::Xirr(QList<double> payments, QList<QDate> dateDiapazon,double rate):
    values(payments),
    dates(dateDiapazon),
    Rate(rate){
    setRate();

}

double Xirr::getRate(){
    return Rate;
}

double Xirr::disc(QDate d, double &v, double &rate) {
    double  exp, coef;
    exp = (d.toJulianDay() - dates[0].toJulianDay()) / dayInYear;
    coef = pow(1 + rate / 100,exp);
    return  v / coef;
}

double Xirr::CalcValue(double &rate) {
    double out = 0;

    for (int i = 0; i <= dates.size()-1; i++) {
        out = out + disc(dates[i],values[i],rate);
    }
    return out;
}

void Xirr::setRate(){

    assert(dates.size() == values.size());
    assert(values.size() >= 2);

    Rate1 = Rate;
    Rate2 = ++Rate;

    F1 = CalcValue(Rate1);
    F2 = CalcValue(Rate2);

    while (Quit == false) {
        if((fabs(F2 - F1) <= EPSILON) || (fabs(Rate2-Rate1) <= EPSILON)) {
            Quit = true;
            result = false;
        } else {
            dF = (F2 - F1) / (Rate2 - Rate1);
            RateN = Rate1 + (0 - F1) / dF / Scale;
            N = N + 1;

            if(RateN > -100){
                FN = CalcValue(RateN);
            };

            if(fabs(RateN - Rate1) / ((fabs(Rate1) + fabs(Rate2)) / 2) <= 0.0000005) {
                Quit = true;
            } else

                if(N >= MAX_STEPS){
                    Quit = true;
                    result = false;
                } else

                    if((RateN > -100) == false){
                        Scale = Scale * 2;
                    } else {
                        Scale = 1;
                        Rate2 = Rate1;
                        F2 = F1;
                        Rate1 = RateN;
                        F1 = FN;
                    }
        }

        if(result){
            Rate = RateN;
        } else {
            Rate = 0;

        }
    }
}
