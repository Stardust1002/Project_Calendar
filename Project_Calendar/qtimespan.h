#ifndef QTIMESPAN
#define QTIMESPAN

#include <QTime>

///Classe permettant de manipuler les temps/durées en implémentant l'addition et la soustraction manquantes à classe QTime.
class QTimeSpan : public QTime{
public:
    QTimeSpan():QTime(){}
    QTimeSpan(const QTime& horaire):QTime(horaire){}
    QTimeSpan(int h, int m, int s = 0, int ms = 0):QTime(h,m,s,ms){}

    QTimeSpan operator+(const QTimeSpan& d)const;
    QTimeSpan& operator+=(const QTimeSpan& d);
    QTimeSpan operator-(const QTimeSpan& d)const;
    QTimeSpan& operator-=(const QTimeSpan& d);
};


#endif // QTIMESPAN

