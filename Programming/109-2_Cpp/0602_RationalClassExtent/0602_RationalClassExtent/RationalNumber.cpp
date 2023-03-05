//
//  Rational.cpp
//  Rational
//
//  Created by 蔡易妏 on 2021/5/6.
//

#include "RationalNumber.hpp"
#include <iostream>
using namespace std;

double RationalNumber::gcd( double x, double y){
    return (y==0 ? x : gcd(y,(int)x%(int)y));
}

double RationalNumber::lcm( double x, double y){
    return (x*( y/(gcd(x,y)) ));
}

RationalNumber::RationalNumber( double num, double den ){
    
    structRational.numerator = num/ gcd(num,den);           // 有理化
    structRational.denominator = (den==0)? 1: den/ gcd(num,den);
    if (structRational.denominator<0){
        structRational.numerator *= -1;
        structRational.denominator *= -1;
    }
}

void RationalNumber::printRational(){
    cout << structRational.numerator << "/" << structRational.denominator << endl;
}

void RationalNumber::printRationalAsDouble(){
    cout << structRational.numerator/structRational.denominator;
    
}


ostream &operator<<( ostream &output, const RationalNumber &r ){
    output << "(" << r.structRational.numerator << "/" << r.structRational.denominator;
    return output;
}

istream &operator>>( istream &input, const RationalNumber &r ){
    input.ignore(); 
    input >> r.structRational.numerator >>  r.structRational.denominator ;
    return input;
}


RationalNumber RationalNumber::operator+( const RationalNumber &r){
    int L = gcd(structRational.denominator,r.structRational.denominator)==1? (structRational.denominator*r.structRational.denominator) : gcd(structRational.denominator,r.structRational.denominator);
    return  RationalNumber( (structRational.numerator*(L/structRational.denominator) + r.structRational.numerator*(L/r.structRational.denominator)), L );
}

RationalNumber RationalNumber::operator-( const RationalNumber &r){
    RationalNumber x = RationalNumber(-r.structRational.numerator, r.structRational.denominator);
    return RationalNumber(structRational.numerator,structRational.denominator) + ( x );
}

RationalNumber RationalNumber::operator*( const RationalNumber &r){           //用交叉相乘比較不會溢位
    RationalNumber r1 = RationalNumber( structRational.numerator, r.structRational.denominator );
    RationalNumber r2 = RationalNumber( r.structRational.numerator, structRational.denominator );
    return  RationalNumber( r1.structRational.numerator*r2.structRational.numerator, r1.structRational.denominator*r2.structRational.denominator );
}

RationalNumber RationalNumber::operator/( const RationalNumber &r){
    RationalNumber x = RationalNumber(r.structRational.denominator,r.structRational.numerator);
    return RationalNumber(structRational.numerator, structRational.denominator) * ( x );
}



bool RationalNumber::operator==(const RationalNumber &r){
    if (structRational.numerator==r.structRational.numerator && structRational.denominator == r.structRational.denominator)
        return true;
    return false;
}

bool RationalNumber::operator!=(const RationalNumber &r){
    return !(*this==r);
}

bool RationalNumber::operator>(const RationalNumber &r){
    int L = gcd(structRational.denominator,r.structRational.denominator)==1? (structRational.denominator*r.structRational.denominator) : gcd(structRational.denominator,r.structRational.denominator);
    int temp_n = structRational.numerator*(L/structRational.denominator);
    int temp_rn = r.structRational.numerator*(L/r.structRational.denominator);
    if (temp_n>temp_rn)
        return true;
    return false;
}

bool RationalNumber::operator>=(const RationalNumber &r){
    return !(*this < r);
}

bool RationalNumber::operator<(const RationalNumber &r){
    int L = gcd(structRational.denominator,r.structRational.denominator)==1? (structRational.denominator*r.structRational.denominator) : gcd(structRational.denominator,r.structRational.denominator);
    int temp_n = structRational.numerator*(L/structRational.denominator);
    int temp_rn = r.structRational.numerator*(L/r.structRational.denominator);
    if (temp_n<temp_rn)
        return true;
    return false;
    
}

bool RationalNumber::operator<=(const RationalNumber &r){
    return !(*this > r);
}

