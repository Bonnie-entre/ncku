//
//  main.cpp
//  Rational
//
//  Created by 蔡易妏 on 2021/5/6.
//

// Exercise 9.15 Solution: Ex09_15.cpp
#include <iostream>
#include "Rational.hpp" // include definition of class Rational
using namespace std;

int main()
{
   Rational c( 2, 6 ), d( 7, 8 ), x; // creates three rational objects

   c.printRational(); // prints rational object c
   cout << " + ";
   d.printRational(); // prints rational object d
   x = c.addition( d ); // adds object c and d; sets the value to x

   cout << " = ";
   x.printRational(); // prints rational object x
   cout << '\n';
   x.printRational(); // prints rational object x
   cout << " = ";
   x.printRationalAsDouble(); // prints rational object x as double
   cout << "\n\n";

   c.printRational(); // prints rational object c
   cout << " - ";
   d.printRational(); // prints rational object d
   x = c.subtraction( d ); // subtracts object c and d
           
   cout << " = ";
   x.printRational(); // prints rational object x
   cout << '\n';
   x.printRational(); // prints rational object x
   cout << " = ";
   x.printRationalAsDouble(); // prints rational object x as double
   cout << "\n\n";

   c.printRational(); // prints rational object c
   cout << " x ";
   d.printRational(); // prints rational object d
   x = c.multiplication( d ); // multiplies object c and d
                            
   cout << " = ";
   x.printRational(); // prints rational object x
   cout << '\n';
   x.printRational(); // prints rational object x
   cout << " = ";
   x.printRationalAsDouble(); // prints rational object x as double
   cout << "\n\n";

   c.printRational(); // prints rational object c
   cout << " / ";
   d.printRational(); // prints rational object d
   x = c.division( d ); // divides object c and d
                            
   cout << " = ";
   x.printRational(); // prints rational object x
   cout << '\n';
   x.printRational(); // prints rational object x
   cout << " = ";
   x.printRationalAsDouble(); // prints rational object x as double
   cout << endl;
} // end main

