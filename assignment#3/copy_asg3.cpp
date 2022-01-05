/********************************************************************************
 * Name: Haris Ahmad
 * Email: hahma485@mtroyal.ca
 * Course: COMP 1631
 * Assignment: Assignment #3
 * Due Date: October 21st, 2020
 * Instructor Name: Paul Pospisil
 * File Name: asg3.cpp

 *Purpose:
 *Details:
 *Assumptions:
 *******************************************************************************/
#include "utility.h"
#include <iostream>
using namespace std;

int multiplyProduct (int multiplicandDigit1, int multiplicandDigit2, int multiplicandDigit3, int multiplicandDigit4, int multiplicandDigit5, int multiplicandDigit6, int multiplierDigit1, int multiplierDigit2, int carry_in, int base);
int multiplyCarry (int augendDigit1, int augendDigit2, int augendDigit3, int augendDigit4, int augendDigit5, int augendDigit6, int augendDigit7, int addendDigit1, int addendDigit2, int addendDigit3, int addendDigit4, int addendDigit5, int addendDigit6, int addendDigit7, int first_carry_in1, int first_carry_in2, int first_carry_in3, int first_carry_in4, int first_carry_in5, int first_carry_in6, int first_carry_in7, int second_carry_in1, int second_carry_in2, int second_carry_in3, int second_carry_in4, int second_carry_in5, int second_carry_in6, int second_carry_in7);
int addSum (int augendDigit1, int augendDigit2, int augendDigit3, int augendDigit4, int augendDigit5, int augendDigit6, int augendDigit7, int addendDigit1, int addendDigit2, int addendDigit3, int addendDigit4, int addendDigit5, int addendDigit6, int addendDigit7);
int addCarry (int augendDigit2, int augendDigit3, int augendDigit4, int augendDigit5, int augendDigit6, int augendDigit7, int addendDigit1, int addendDigit2, int addendDigit3, int addendDigit4, int addendDigit5, int addendDigit6, int add_carry1, int add_carry2, int add_carry3, int add_carry4, int add_carry5, int add_carry6);
int expand (int multiplicandDigit1, int multiplicandDigit2, int multiplicandDigit3, int multiplicandDigit4, int multiplicandDigit5, int multiplicandDigit6, int multiplierDigit1, int multiplierDigit2, int base);

int main()
{

    int base;
    
    int multiplicandDigit1;
    int multiplicandDigit2;
    int multiplicandDigit3;
    int multiplicandDigit4;
    int multiplicandDigit5;
    int multiplicandDigit6;

    int multiplierDigit1;
    int multiplierDigit2;                                   ;
    
    cout << "Welcome to the multiplication tutor. Ready to calculate..." << endl;

    cout << "Enter the base: ";
    cin >> base;

    cout << "Enter six digits of multiplicand (seperated by whitespace): ";
    cin >> multiplicandDigit1;
    cin >> multiplicandDigit2;
    cin >> multiplicandDigit3;
    cin >> multiplicandDigit4;
    cin >> multiplicandDigit5;
    cin >> multiplicandDigit6;

    cout << "Enter two digits of multiplier (seperated by whitespace): ";
    cin >> multiplierDigit1;
    cin >> multiplierDigit2;
	
    cout << endl;

    multiplyProduct(multiplicandDigit1, multiplicandDigit2, multiplicandDigit3, multiplicandDigit4, );
    multiplyCarry();
    addSum();
    addCarry();
    expand();
    
    return 0;
}

int multiplyProduct (int multiplicandDigit1, int multiplicandDigit2, int multiplicandDigit3, int multiplicandDigit4, int multiplicandDigit5, int multiplicandDigit6, int multiplierDigit1, int multiplierDigit2, int carry_in, int base)
{

    cout << "for base " << base << ':' << endl << endl;
 multiplyProduct(multiplicandDigit1, multiplicandDigit2, multiplicandDigit3, multiplicandDigit4, );                                 |Digit5, int multiplicandDigit6, int multiplierDigit1, int multiplierDigit2, int carry_in, int base);
    multiplyCarry();    
    int augendDigit1;
    int augendDigit2;
    int augendDigit3;
    int augendDigit4;
    int augendDigit5;
    int augendDigit6;
    int augendDigit7;
    
    int first_carry_in1;
    int first_carry_in2;
    int first_carry_in3;
    int first_carry_in4;
    int first_carry_in5;
    int first_carry_in6;

    int addendDigit1;
    int addendDigit2;
    int addendDigit3;
    int addendDigit4;
    int addendDigit5;
    int addendDigit6;
    int addendDigit7;

    int second_carry_in1;
    int second_carry_in2;
    int second_carry_in3;
    int second_carry_in4;
    int second_carry_in5;
    int second_carry_in6;

    
    augendDigit1 = (multiplierDigit1 * multiplicandDigit1) % 10;
    augendDigit2 = ((multiplierDigit1 * multiplicandDigit2) % 10) + first_carry_in1;
    augendDigit3 = ((multiplierDigit1 * multiplicandDigit3) % 10) + first_carry_in2;
    augendDigit4 = ((multiplierDigit1 * multiplicandDigit4) % 10) + first_carry_in3;
    augendDigit5 = ((multiplierDigit1 * multiplicandDigit5) % 10) + first_carry_in4;
    augendDigit6 = ((multiplierDigit1 * multiplicandDigit6) % 10) + first_carry_in5;
    augendDigit7 = first_carry_in6;

    addendDigit1 = (multiplierDigit2 * multiplicandDigit1) % 10;
    addendDigit2 = ((multiplierDigit2 * multiplicandDigit2) % 10) + second_carry_in1; 
    addendDigit2 = ((multiplierDigit2 * multiplicandDigit3) % 10) + second_carry_in2;
    addendDigit2 = ((multiplierDigit2 * multiplicandDigit4) % 10) + second_carry_in3;
    addendDigit2 = ((multiplierDigit2 * multiplicandDigit5) % 10) + second_carry_in4;
    addendDigit2 = ((multiplierDigit2 * multiplicandDigit6) % 10) + second_carry_in5;
    addendDigit7 = second_carry_in6
    
	prettyPrint (3, multiplicandDigit1);
    prettyPrint (3, multiplicandDigit2);
    prettyPrint (3, multiplicandDigit3);
    prettyPrint (3, multiplicandDigit4);
    prettyPrint (3, multiplicandDigit5);
    prettyPrint (3, multiplicandDigit6);

    prettyPrint (3, multiplierDigit1);
    prettyPrint (3, multiplierDigit2);

    cout << "======================================" << endl;
    
    prettyPrint (3, augendDigit1);
    prettyPrint (3, augendDigit2);
    prettyPrint (3, augendDigit3);
    prettyPrint (3, augendDigit4);
    prettyPrint (3, augendDigit5);
    prettyPrint (3, augendDigit6);
    prettyPrint (3, augendDigit7);

    prettyPrint (6, addendDigit1);
    prettyprint (3, addendDigit2);
    prettyPrint (3, addendDigit3);
    prettyPrint (3, addendDigit4);
    prettyPrint (3, addendDigit5);
    prettyPrint (3, addendDigit6);
    prettyPrint (3, addendDigit7);
    
    cout << "======================================" << endl;
    
    return;
}

int multiplyCarry (int augendDigit1, int augendDigit2, int augendDigit3, int augendDigit4, int augendDigit5, int augendDigit6, int augendDigit7, int addendDigit1, int addendDigit2, int addendDigit3, int addendDigit4, int addendDigit5, int addendDigit6, int addendDigit7, int first_carry_in1, int first_carry_in2, int first_carry_in3, int first_carry_in4, int first_carry_in5, int first_carry_in6, int first_carry_in7, int second_carry_in1, int second_carry_in2, int second_carry_in3, int second_carry_in4, int second_carry_in5, int second_carry_in6, int second_carry_in7)
{

    first_carry_in1 = augendDigit1 / 10;
    first_carry_in2 = augendDigit2 / 10;
    first_carry_in3 = augendDigit3 / 10;
    first_carry_in4 = augendDigit4 / 10;
    first_carry_in5 = augendDigit5 / 10;
    first_carry_in6 = augendDigit6 / 10;

    second_carry_in1 = addendDigit1 / 10;
    second_carry_in2 = addendDigit2 / 10;
    second_carry_in3 = addendDigit3 / 10;
    second_carry_in4 = addendDigit4 / 10;
    second_carry_in5 = addendDigit5 / 10;
    second_carry_in6 = addendDigit6 / 10;
    second_carry_in7 = addendDigit7 / 10;
    
    return;
}

int addSum (int augendDigit1, int augendDigit2, int augendDigit3, int augendDigit4, int augendDigit5, int augendDigit6, int augendDigit7, int addendDigit1, int addendDigit2, int addendDigit3, int addendDigit4, int addendDigit5, int addendDigit6, int addendDigit7)
{

    int sum1;
    int sum2;
    int sum3;
    int sum4;
    int sum5;
    int sum6;
    int sum7;
    int sum8;

    int add_carry1;
    int add_carry2;
    int add_carry3;
    int add_carry4;
    int add_carry5;
    int add_carry6;
    
    sum1 = augendDigit1;
    sum2 = ((augendDigit2 + addendDigit1) % 10);
    sum3 = ((augendDigit3 + addendDigit2) % 10) + add_carry1;
    sum4 = ((augendDigit4 + addendDigit3) % 10) + add_carry2;
    sum5 = ((augendDigit5 + addendDigit4) % 10) + add_carry3;
    sum6 = ((augendDigit6 + addendDigit5) % 10) + add_carry4;
    sum7 = ((augendDigit7 + addendDigit6) % 10) + add_carry5;
    sum8 = addendDigit7 + add_carry6;
    
    prettyPrint (3, sum1);
    prettyPrint (3, sum2);
    prettyPrint (3, sum3);
    prettyPrint (3, sum4);
    prettyPrint (3, sum5);
    prettyPrint (3, sum6);
    prettyPrint (3, sum7);
    prettyPrint (3, sum8);
    
    return;
}

int addCarry (int augendDigit2, int augendDigit3, int augendDigit4, int augendDigit5, int augendDigit6, int augendDigit7, int addendDigit1, int addendDigit2, int addendDigit3, int addendDigit4, int addendDigit5, int addendDigit6, int add_carry1, int add_carry2, int add_carry3, int add_carry4, int add_carry5, int add_carry6)
{
    
    add_carry1 = (augendDigit2 + addendDigit1) / 10;
    add_carry2 = (augendDigit3 + addendDigit2) / 10;
    add_carry3 = (augendDigit4 + addendDigit3) / 10;
    add_carry4 = (augendDigit5 + addendDigit4) / 10;
    add_carry5 = (augendDigit6 + addendDigit5) / 10;
    add_carry6 = (augendDigit7 + addendDigit6) / 10;
    
    return;
}

int expand (int multiplicandDigit1, int multiplicandDigit2, int multiplicandDigit3, int multiplicandDigit4, int multiplicandDigit5, int multiplicandDigit6, int multiplierDigit1, int multiplierDigit2, int base)
{
    int multiplicandDigit1_base10;
    int multiplicandDigit2_base10;
    int multiplicandDigit3_base10;
    int multiplicandDigit4_base10;
    int multiplicandDigit5_base10;
    int multiplicandDigit6_base10;

    int multiplicandTotal_base10;

    multiplicandDigit1_base10 = intPower(base, 5) * multiplicandDigit1;
    multiplicandDigit2_base10 = intPower(base, 4) * multiplicandDigit2;
    multiplicandDigit3_base10 = intPower(base, 3) * multiplicandDigit3;
    multiplicandDigit4_base10 = intPower(base, 2) * multiplicandDigit4;
    multiplicandDigit5_base10 = intPower(base, 1) * multiplicandDigit5;
    multiplicandDigit6_base10 = intPower(base, 0) * multiplicandDigit6;

    multiplicandTotal_base10 = multiplicandDigit1_base10 + multiplicandDigit2_base10 + multiplicandDigit3_base10 + multiplicandDigit4_base10 + multiplicandDigit5_base10 + multiplicandDigit6_base10;
    
    int multiplierDigit1_base10;
    int multiplierDigit2_base10;

    int multiplierTotal_base10;
    
    multiplierDigit1_base10 = intPower(base, 1) * multiplierDigit1;
    multiplierDigit2_base10 = intPower(base, 0) * multiplierDigit2;

    multiplierTotal_base10 = multiplierDigit1_base10 + multiplierDigit2_base10;

    int product_base10;

    product_base10 = multiplicandTotal_base10 * multiplierTotal_base10;
    
    cout << "Verification:" << endl << endl;
    cout << "The multiplicand in base 10 is: " << multiplicandTotal_base10 << endl;
    cout << "The multiplier in base 10 is: " << multiplierTotal_base10 << endl << endl;
    cout << multiplicandTotal_base10 << '*' << multiplierTotal_base10 << "is equal to: " << product_base10 << endl << endl;
    cout << "The tutor's product in base 10 is: " << product_base10 << endl;

    return;
}
