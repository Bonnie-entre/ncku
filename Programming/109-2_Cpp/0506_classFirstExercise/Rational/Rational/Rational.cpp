//
//  Rational.cpp
//  Rational
//
//  Created by 蔡易妏 on 2021/5/6.
//

#include "Rational.hpp"
#include <iostream>
using namespace std;

double Rational::gcd( double x, double y){
    return (y==0 ? x : gcd(y,(int)x%(int)y));
}

double Rational::lcm( double x, double y){
    return (x*( y/(gcd(x,y)) ));
}

Rational::Rational( double num, double den ){
    numerator = num/ gcd(num,den);           // 有理化
    denominator = den/ gcd(num,den);
}

void Rational::printRational(){
    cout << numerator << "/" << denominator << endl;
}

void Rational::printRationalAsDouble(){
    cout << numerator/denominator;
    
}

Rational Rational::addition(Rational &r){   // 請注意有理化
    int L = gcd(denominator,r.denominator)==1? (denominator*r.denominator) : gcd(denominator,r.denominator);
    return  Rational( (numerator*(L/denominator) + r.numerator*(L/r.denominator)), L );
}

Rational Rational::subtraction(Rational &r){
    Rational x = Rational(-r.numerator, r.denominator);
    return Rational(numerator,denominator).addition( x );
}

Rational Rational::multiplication(Rational &r){           //用交叉相乘比較不會溢位
    Rational r1 = Rational( numerator, r.denominator );
    Rational r2 = Rational( r.numerator, denominator );
    return  Rational( r1.numerator*r2.numerator, r1.denominator*r2.denominator );
}

Rational Rational::division(Rational &r){
    Rational x = Rational(r.denominator,r.numerator);
    return Rational(numerator, denominator).multiplication( x );
}
