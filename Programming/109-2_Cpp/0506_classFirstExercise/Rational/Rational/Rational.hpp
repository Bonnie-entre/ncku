//
//  Rational.hpp
//  Rational
//
//  Created by 蔡易妏 on 2021/5/6.
//

#ifndef Rational_hpp
#define Rational_hpp

#include <stdio.h>
#include <string>
using namespace std;

class Rational{
    public:
        Rational( double =0, double =1 );     // Default Constructor     //不確定

        void printRational();
        void printRationalAsDouble();

        Rational addition( Rational &r );
        Rational subtraction( Rational &r );
        Rational multiplication( Rational &r );
        Rational division( Rational &r );

    private:
    double numerator;    //分子
    double denominator;  //分母
    int numerator_int;
    int denominator_int;
    double gcd( double, double );
    double lcm( double, double );
    Rational Rational＿Int( double num, double den );
};

#endif /* Rational_hpp */
