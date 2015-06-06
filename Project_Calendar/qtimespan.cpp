#include "qtimespan.h"

QTimeSpan QTimeSpan::operator+(const QTimeSpan& d)const{
    return this->addSecs(QTimeSpan(0,0).secsTo(d));
}

QTimeSpan& QTimeSpan::operator+=(const QTimeSpan& d){
    return *this = *this+d;
}
