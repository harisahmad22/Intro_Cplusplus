/********************************************************************************
 * Name: Haris Ahmad
 * Email: hahma485@mtroyal.ca
 * Course: COMP 1631
 * Assignment: Assignment #3
 * Due Date: October 21st, 2020
 * Instructor Name: Paul Pospisil
 * File Name: asg3.cpp

 * Purpose: To compute the multiplication of a 6-digit multiplicand with a
            2-digit multiplier in base 16 or less, using the multiplication
            in base-10 as verification.

 * Details: The program takes in a user inputted base between 1-16 and a user-
            inputted multiplicand/multiplier. The program then ouptputs the
            multiplication for the ones digit of the multiplier times the
            multiplicand's digits, followed by the tens digit of the multiplier
            times the multiplicand's digits. The sum of the rows is then added
            together and as verification the user inputted base/multipler/-
            multiplicand are shown in base-10 along with the product of their
            multiplication.           

 * Assumptions/ Limiations: The base that the user enters must be a positive
                            integer between 0-16. The digits entered for the
                            multiplicand and multiplier will be valid numbers 
                            for the given base.
 *******************************************************************************/
#include "utility.h"
#include <iostream>
using namespace std;

int multiplyProduct (int multiplicand, int multiplier, int carry_in, int base);
int multiplyCarry (int multiplicand, int multiplier, int carry_in, int base);
int addSum (int augend, int addend, int carry_in, int base);
int addCarry (int augend, int addend, int carry_in, int base);
int expand (int digit, int base, int position);

int main()
{

// The user inputted values required for the program

    int base;

    int multiplicandDg1;
    int multiplicandDg2;
    int multiplicandDg3;
    int multiplicandDg4;
    int multiplicandDg5;
    int multiplicandDg6;

    int multiplierDg1;
    int multiplierDg2;

// The remaining values necessary to complete the calculations in the program
    
    int carry_in;
    
    int augendDg1;
    int augendDg2;
    int augendDg3;
    int augendDg4;
    int augendDg5;
    int augendDg6;
    int augendDg7;
    
    int addendDg1;
    int addendDg2;
    int addendDg3;
    int addendDg4;
    int addendDg5;
    int addendDg6;
    int addendDg7;
    
    int sum1;
    int sum2;
    int sum3;
    int sum4;
    int sum5;
    int sum6;
    int sum7;
    int sum8;

    int expandedMultiplicand;
    int expandedMultiplier;
    int expandedSum;
    
    carry_in = 0;

// Introductory message to welcome the user to the program
    
    cout << "Welcome to the multiplication tutor. Ready to calculate..." << endl;

    cout << "Enter the base: ";
    cin >> base;

    cout << "Enter six digits of multiplicand (separated by whitespace): ";
    cin >> multiplicandDg1 >> multiplicandDg2 >> multiplicandDg3;
    cin >> multiplicandDg4 >> multiplicandDg5 >> multiplicandDg6; 

    cout << "Enter two digits of multiplier (separated by whitespace): ";
    cin >> multiplierDg1 >> multiplierDg2;
	
    cout << endl;

    cout << "for base ";
    prettyPrint (2, base);
    cout << ':';

// Outputs the multiplicand digits in a table like structure
    
    prettyPrint (18, multiplicandDg1);
    prettyPrint (5, multiplicandDg2);
    prettyPrint (5, multiplicandDg3);
    prettyPrint (5, multiplicandDg4);
    prettyPrint (5, multiplicandDg5);
    prettyPrint (5, multiplicandDg6);

    cout << endl;

    cout << "                                            *";

// Outputs the multiplier digits in a table like structure
    
    prettyPrint (5, multiplierDg1);
    prettyPrint (5, multiplierDg2);
    
    cout << endl;
    cout << "                 ";
    cout << "======================================" << endl;

/* The calculations used to determine the first row of the multiplication values
   using the second digit of the multiplier and all of the multiplicand digits */
    
    augendDg7 = multiplyProduct (multiplicandDg6, multiplierDg2, carry_in, base);
    carry_in = multiplyCarry (multiplicandDg6, multiplierDg2, carry_in, base);

    augendDg6 = multiplyProduct (multiplicandDg5, multiplierDg2, carry_in, base);
    carry_in = multiplyCarry (multiplicandDg5, multiplierDg2, carry_in, base);
    
    augendDg5 = multiplyProduct (multiplicandDg4, multiplierDg2, carry_in, base);
    carry_in = multiplyCarry (multiplicandDg4, multiplierDg2, carry_in, base);
    
    augendDg4 = multiplyProduct (multiplicandDg3, multiplierDg2, carry_in, base);
    carry_in = multiplyCarry (multiplicandDg3, multiplierDg2, carry_in, base);

    augendDg3 = multiplyProduct (multiplicandDg2, multiplierDg2, carry_in, base);
    carry_in = multiplyCarry (multiplicandDg2, multiplierDg2, carry_in, base);
    
    augendDg2 = multiplyProduct (multiplicandDg1, multiplierDg2, carry_in, base);
    carry_in = multiplyCarry (multiplicandDg1, multiplierDg2, carry_in, base);
    
    augendDg1 = carry_in;
    
    prettyPrint (25, augendDg1);
    prettyPrint (5, augendDg2);
    prettyPrint (5, augendDg3);
    prettyPrint (5, augendDg4);
    prettyPrint (5, augendDg5);
    prettyPrint (5, augendDg6);
    prettyPrint (5, augendDg7);

    cout << endl;

/* The calculations used to determine the second row of the multiplication values
   using the first digit of the multiplier and all of the multiplicand digits */
    
    carry_in = 0;
    
    addendDg7 = multiplyProduct (multiplicandDg6, multiplierDg1, carry_in, base);
    carry_in = multiplyCarry (multiplicandDg6, multiplierDg1, carry_in, base);

    addendDg6 = multiplyProduct (multiplicandDg5, multiplierDg1, carry_in, base);
    carry_in = multiplyCarry (multiplicandDg5, multiplierDg1, carry_in, base);   

    addendDg5 = multiplyProduct (multiplicandDg4, multiplierDg1, carry_in, base);
    carry_in = multiplyCarry (multiplicandDg4, multiplierDg1, carry_in, base);    

    addendDg4 = multiplyProduct (multiplicandDg3, multiplierDg1, carry_in, base);
    carry_in = multiplyCarry (multiplicandDg3, multiplierDg1, carry_in, base);

    addendDg3 = multiplyProduct (multiplicandDg2, multiplierDg1, carry_in, base);
    carry_in = multiplyCarry (multiplicandDg2, multiplierDg1, carry_in, base);

    addendDg2 = multiplyProduct (multiplicandDg1, multiplierDg1, carry_in, base);
    carry_in = multiplyCarry (multiplicandDg1, multiplierDg1, carry_in, base);

    addendDg1 = carry_in;

    prettyPrint (20, addendDg1);
    prettyPrint (5, addendDg2);
    prettyPrint (5, addendDg3);
    prettyPrint (5, addendDg4);
    prettyPrint (5, addendDg5);
    prettyPrint (5, addendDg6);
    prettyPrint (5, addendDg7);

    cout << endl;
    cout << "                 ";
    cout << "======================================" << endl;

    carry_in = 0;

/* The calculations used to determine the final product for the multiplication
   of the mulitplicand and multiplier */
    
    sum8 = addSum (augendDg7, 0, carry_in, base);

    sum7 = addSum (augendDg6, addendDg7, carry_in, base);
    carry_in = addCarry (augendDg6, addendDg7, carry_in, base);
     
    sum6 = addSum (augendDg5, addendDg6, carry_in, base);
    carry_in = addCarry (augendDg5, addendDg6, carry_in, base);

    sum5 = addSum (augendDg4, addendDg5, carry_in, base);
    carry_in = addCarry (augendDg4, addendDg5, carry_in, base);
    
    sum4 = addSum (augendDg3, addendDg4, carry_in, base);
    carry_in = addCarry (augendDg3, addendDg4, carry_in, base);

    sum3 = addSum (augendDg2, addendDg3, carry_in, base);
    carry_in = addCarry (augendDg2, addendDg3, carry_in, base);
    
    sum2 = addSum (augendDg1, addendDg2, carry_in, base);
    carry_in = addCarry (augendDg1, addendDg2, carry_in, base);

    sum1 = carry_in + addendDg1; 
    
    prettyPrint (20, sum1);
    prettyPrint	(5, sum2);
    prettyPrint	(5, sum3);
    prettyPrint	(5, sum4);
    prettyPrint	(5, sum5);
    prettyPrint	(5, sum6);
    prettyPrint	(5, sum7);
    prettyPrint	(5, sum8);

    cout << endl;
    cout << endl;

/* The calculations used to verify the program by converting the multiplicand,
   multiplier, and the product to base 10 */
    
    expandedMultiplicand = expand (multiplicandDg1, base, 5)
    + expand(multiplicandDg2, base, 4)
    + expand(multiplicandDg3, base, 3) + expand (multiplicandDg4, base, 2)
    + expand(multiplicandDg5, base, 1) + expand (multiplicandDg6, base, 0);

    expandedMultiplier = expand (multiplierDg1, base, 1)
    + expand (multiplierDg2, base, 0);

    expandedSum = expandedMultiplicand * expandedMultiplier;

// The format for the final output given to the user involving verification
    
    cout << "Verification:" << endl;
    cout << "The multiplicand in base 10 is: " << expandedMultiplicand << endl;
    cout << "The multiplier in base 10 is: " << expandedMultiplier << endl;
    cout << endl;
    cout << expandedMultiplicand << " * " << expandedMultiplier;
    cout << " is equal to: " << expandedSum << endl << endl;
    cout << "The tutor's product in base 10 is: " << expandedSum << endl;

    cout << endl;
    
    return 0;
}

/********************************************************************************
 *Name: multiplyProduct
 *
 *Purpose: To return the one's digit of the mulitplication.
 *
 *Details: Add's a carry in value to the multiplication of a digit from the
           multiplier with a digit from the multiplicand and then mod's that 
           value by the base to extract the one's digit of the multiplication.
 *
 *Input: Takes in 4 integers including a user inputted multplicand digit,
         multiplier digit, and base value, and then generated carry in value.
 *******************************************************************************/

int multiplyProduct (int multiplicand, int multiplier, int carry_in, int base)
{
    int multiplication_ones_digit;

    multiplication_ones_digit = (carry_in + (multiplicand * multiplier)) % base;

    return multiplication_ones_digit;
}

/********************************************************************************
 *Name: multiplyCarry
 *
 *Purpose: To return the carry out value of the multiplication.
 *
 *Details: Add's a carry in value from the multiplication of a digit from the
           mulitplier with a digit from the multiplicand and then div's that
           value by the base to extract the ten's digit of the multiplication.
 *
 *Input: Takes in 4 integers including a user inputted multiplicand digit,
         multiplier digit, and base value, and then a generated carry in value.
 *******************************************************************************/

int multiplyCarry (int multiplicand, int multiplier, int carry_in, int base)
{
    int multiplication_carry_out;

    multiplication_carry_out = (carry_in + (multiplicand * multiplier)) / base;

    return multiplication_carry_out;
}

/********************************************************************************
 *Name: addSum
 *
 *Purpose: To return the one's digit of the addition. 
 *
 *Details: Add's a carry in value when adding the multiplication from the 
           multiplier's first digit * the multiplicand, with the multiplication
           from the multiplier's second digit * the multiplicand. It then mod's
           the given value by the base to extract the one's digit of the 
           addition. 
 *
 *Input: Takes in 4 integers including a single augend digit's integer value, 
         addend digit's integer value, a carry_in value, and the user inputted
         base value.
 *******************************************************************************/

int addSum (int augend, int addend, int carry_in, int base)
{
    int addition_ones_digit;

    addition_ones_digit = (carry_in + (augend + addend)) % base;
 
    return addition_ones_digit;
}

/********************************************************************************
 *Name: addCarry
 *
 *Purpose: To return the carry out value from the addition.
 *
 *Details: Add's a carry in value from the adition of a single column's augend
           and addend digit's. The value then div's itself by the base to return
           the ten's diigt of the addition.
 *
 *Input: Takes in 4 integers including a single augend digit's integer value,
         addend digit's integer value, a carry_in value, and the user inputted
         base value.
 *******************************************************************************/

int addCarry (int augend, int addend, int carry_in, int base)
{
    int addition_carry_out;

    addition_carry_out = (carry_in + (augend + addend)) / base;

    return addition_carry_out;
}

/********************************************************************************
 *Name: expand
 *
 *Purpose: To return the value of a number to a certain power with a
           certain base value.
 *
 *Details: Takes a certain digit and multiplies it by the base value to a
           specific power.
 *
 *Input: Takes in 3 values including a desired integer base value, an integer
         digit value, and an integer position value.
 *******************************************************************************/

int expand (int digit, int base, int position)
{
    int expand_digit;
    
    expand_digit = digit * intPower (base, position);
	
    return expand_digit;
}
