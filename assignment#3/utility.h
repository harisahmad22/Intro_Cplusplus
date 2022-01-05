// Function Name:  prettyprint
// Input::  an integer representing the field width
//          an integer representing the number to be outputted
// Action:  the number is outputted to the standard output right-justified
//          in the specified width (leading blanks are printed if necessary)
//
//          e.g. prettyprint (5, 2);   would produce the output
//                        2            where    represents a leading blank
//                    ^^^^                   ^ 
//
//               prettyprint (4, -8);   would produce the output
//                      -8           
//                    ^^            
//
//               prettyprint (4, 2);
//               prettyprint (4, -8);   would produce the output
//                       2  -8
//                    ^^^ ^^

void prettyPrint (int, int);

// Function Name:  intPower (value, exp)
// Input:   an integer representing the base value
//          an integer representing exponent value
// Return:  the base value raised to the exponent
//   e.g.  intPower (5, 2); would return the value 5^2 or 25
//         intPower (2, 5); would return the value 2^5 or 32
//         intPower (-5, 3); would return the value (-5)^3 or -125
//         intPower (5, –8); is invalid since the result is not 
//                   an integer value and will return the value of 0

int intPower (int base, int exp);
