#include "qtimespan.h"

QTimeSpan QTimeSpan::operator+(const QTimeSpan& d)const{
///Opérateur d'addition permettant d'additionner deux QTimeSpan et leurs attributs respectifs.
    return this->addSecs(QTimeSpan(0,0).secsTo(d));
}

QTimeSpan& QTimeSpan::operator+=(const QTimeSpan& d){
///Opérateur d'addition permettant d'additionner deux QTimeSpan et leurs attributs respectifs.

    return *this = *this+d;
}

QTimeSpan QTimeSpan::operator-(const QTimeSpan& d)const{
///Opérateur de soustraction permettant de soustraire deux QTimeSpan et leurs attributs respectifs.

    return this->addSecs(-QTimeSpan(0,0).secsTo(d));
}

QTimeSpan& QTimeSpan::operator-=(const QTimeSpan& d){
///Opérateur de soustraction permettant de soustraire deux QTimeSpan et leurs attributs respectifs.
    return *this = *this-d;
}

