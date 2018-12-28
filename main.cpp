//https://stackoverflow.com/questions/5179866/xirr-calculation
#include <QCoreApplication>
#include "xirr.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QList<double> payments = {-5000, 6350}; // payments

    QList<QDate> dates;
    dates << QDate(2017,12,10)
        << QDate(2017,12,25);
    double rate = 0.0;

    Xirr *objXirr = new Xirr(payments,dates,rate);
    rate = objXirr->getRate();
    delete objXirr;
    objXirr = nullptr;

    qDebug() << QString::number(rate, 'f', 8);

    return 0;


}
