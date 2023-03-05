//
//  Rational.hpp
//  Rational
//
//  Created by 蔡易妏 on 2021/5/6.
//

#ifndef RationalNumber_hpp
#define RationalNumber_hpp

#include <stdio.h>
#include <string>
using namespace std;

typedef struct
{
    int numerator;
    int denominator;
}RationalStruct;

class RationalNumber{
    friend ostream &operator<<( ostream &, const RationalNumber & );
    friend istream &operator>>( istream &, const RationalNumber & );
    public:
        RationalNumber( double =0, double =1 );     // Default Constructor     //不確定

        void printRational();
        void printRationalAsDouble();

        RationalNumber operator+( const RationalNumber &r );
        RationalNumber operator-( const RationalNumber &r );
        RationalNumber operator*( const  RationalNumber &r );
        RationalNumber operator/( const  RationalNumber &r );
        bool operator==(const RationalNumber &);
        bool operator!=(const RationalNumber &);
        bool operator>(const RationalNumber &);
        bool operator>=(const RationalNumber &);
        bool operator<(const RationalNumber &);
        bool operator<=(const RationalNumber &);
    
        explicit operator double(){
            return static_cast <double> (this->structRational.numerator) / (this->structRational.denominator);
        }

    private:
        RationalStruct structRational;
        double gcd( double, double );
        double lcm( double, double );
};

#endif /* Rational_hpp */
