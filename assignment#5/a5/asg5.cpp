
/********************************************************************************                                                    

Name:        Haris Ahmad                                                                                                                 
E-mail:      hahma485@mtroyal.ca
Course:      COMP 1631 - 002                                                                                                                                                        
Assignment:  5                                                                                                                                                              
Due Date:    November 30th, 2020                                                                                                                                                    
Instructor:  Paul Pospisil                                                                                                                                                          
Source File: asg5.cpp                                                                                                                                                               

=================================================================================
                                                                        
Purpose:                                                                                                                                                                            
  To calculate a polynomial operation from 5 given choices. Those choices being:
  evaluate, differentiate, addition, multiply, and root(s). A sixth option is 
  also listed as 'q' on the menu but it does not perform a specific operation 
  and it exits the user from the program. If a choice that is not listed on the 
  menu is selected, the user will be promted to select another choice.
                                                                                                                                                                                    
Details:                                                                                                                                                                            
  Input - The user will be prompted with a menu that lists the various possible                                                                                                     
          polynomial operations. Based on the character that the user selected,                                                                                                    
          a specific operation will be performed.

              - Input for "evaluate" operation:
	          ~ The program takes in a user inputted character 'e'.
                  ~ It then takes in a single polynomial based on user inputs
                    in the form of coeffecient ' ' exponent and it will stop 
                    gathering input when the user enters "CTRL-D".
	      - Input for "differentiate" operation:
                  ~ The program takes in a user inputted character 'd'.
                  ~ It then takes in a single polynomial based on user inputs                                                                                                       
                    in the form of coeffecient ' ' exponent and it will stop                                                                                                       
                    gathering input when the user enters "CTRL-D".
	      - Input for "addition" operation:    
                  ~ The program takes in a user inputted character 'a'.
                  ~ It then takes in two polynomials based on user inputs                                                                                                       
                    in the form of coeffecient ' ' exponent and it will stop                                                                                                       
                    gathering input when the user enters "CTRL-D".
	      - Input for "multiply" operation:
                  ~ The program takes in a user inputted character 'm'.
                  ~ It then takes in two polynomials based on user inputs                                                                                                       
                    in the form of coeffecient ' ' exponent and it will stop                                                                                                       
                    gathering input when the user enters "CTRL-D".
              - Input for "root(s)" operation:
	          ~ The program takes in a user inputted character 'r'.
                  ~ 
		    
  Output - The user will be prompted with a menu that lists the various possible
           polynomial operations. Based on the character that the user selected, 
           a specific operation will be performed.
              - Output for 'e':
                  ~ The polynomial printed out in the form: 
                    "number"; "x^", or "x", or nothing; and then the exponent.
                  ~  The final evaluated value of the polynomial.
              - Output for 'd':
                  ~ The polynomial printed out in the form:
                    "number"; "x^", or "x", or nothing; and then the exponent.
                  ~ The polynomial after it has been differentiated in the same
                    form listed above.
              - Output for 'a':
                  ~ The first polynomial printed out in the form:                                                                                                       
                    "number"; "x^", or "x", or nothing; and then the exponent.
                  ~ The second polynomial printed out in the form:
                    "number"; "x^", or "x", or nothing; and then the exponent.
                  ~ The final polynomial.

********************************************************************************/

#include <iostream>
#include <cmath>
#include "reset.h"
using namespace std;

typedef int poly;     // Changes type "int" to "poly" for clarification purposes


void readPoly (poly polynomial [], bool& success);

void printPoly (const poly polynomial []);

void clearPoly (poly polynomial []);



void evaluate (const poly polynomial [], int x, int& polynomialValue);

void differentiate (const poly polynomial [], poly diff_poly []);

void sumPoly (const poly poly1 [], const poly poly2 [], poly polySum []);

void multiplyPolys (const poly poly1 [], const poly poly2 [], poly product [],
		    bool& productFound);

void rootsPoly(const poly polynomial [], int& numRealRoots, double& root1,
	       double& root2, bool& rootsFound);



void process_evaluate ();

void process_differentiate ();

void process_addition ();

void process_multiply ();

void process_roots ();


const int MAX_SIZE = 21;          // The max permissible size of an exponent


int main()
{
    char choice;
    
    cout << endl;
    cout << "Welcome to the polynomial calculator, "
         << "What operation would you like to do: " << endl;
    cout << "     e  -  evaluate a polynomial" << endl;
    cout << "     d  -  differentiate a polynomial" << endl;
    cout << "     a  -  add two polynomials" << endl;
    cout << "     m  -  multiply two polynomials" << endl;
    cout << "     r  -  find the root(s) of a quadratic polynomial" << endl;
    cout << "     q  -  quit" << endl;

    cout << "Please input your choice: ";
    cin >> choice;
    cout << endl;
    
    while (choice != 'q')
    {
	switch (choice)
	{
	case 'e':
	    process_evaluate ();
	    
	    break;

	case 'd':
	    process_differentiate ();
	    
	    break;

	case 'a':
	    process_addition ();
	    
	    break;

	case 'm':
	    process_multiply ();
	   
	    break;

	case 'r':
	    process_roots ();
	    
	    break;

	default:
	    cout << "You chose an invalid choice, ";
	    cout << "please select a valid entry - \n";

	    break;
	}
	cout << endl << endl << endl;
	cout << "Enter another choice. " << endl;
	cout << "What operation would you like to do: " << endl;
	cout << "     e  -  evaluate a polynomial" << endl;
	cout << "     d  -  differentiate a polynomial" << endl;
	cout << "     a  -  add two polynomials" << endl;
	cout << "     m  -  multiply two polynomials" << endl;
	cout << "     r  -  find the root(s) of a quadratic polynomial" << endl;
	cout << "     q  -  quit" << endl;
	cout << endl << "Enter a new choice please: ";
	cin >> choice;
    }

    switch (choice)
    {
    case 'q':
	return 0;
    }
    
    return 0;
}


/********************************************************************************                                                                                                   
Name:     readPoly                                                                                                                   

Purpose:  To generate the input for the user in the form of "coefficient"
          followed by the "exponent" until the pre-defined function "reset()" is
          called which ends the the users input.

Details:  Calls upon the clearPoly function to clear any previous arrays and
          then uses a while loop so that as long as the polynomial is still
          in correspondence with the guidelines (exponent between -1 and 21)
          and the file has not reached the end, the read will continue.
          This function also calls upon the pre-defined "reset" function so
          that the input is terminated by the user when they are finished
          entering values for the polynomial.
                                          
Input Parameters:
          poly polynomial []
          bool success

Returns:  Nothing.                                                                                                                                                                 
********************************************************************************/
void readPoly (poly polynomial [], bool& success)
{
    int index = 0;         // The exponent(s) value (to be user inputted)
    int coefficient = 0;   // The coefficient(s) value (to be user inputted)

    bool repeat = false;
    
    success = true;

    clearPoly (polynomial);
    
    cout << endl;
    cout << "Enter a base and an exponent with only one corresponding base "
         << "for every exponent: " << endl;

    cin >> coefficient;
    cin >> index;
    
    while (!cin.eof() && success == true)
    {
	if (polynomial [index] != 0 || index >= 21 || index < 0)
	{
	    success = false;
	    return;
	}
	else
	{
	    success = true;
	    repeat = true;
	    polynomial[index] = coefficient;
	}
	if (success == true)
	{
	    cin >> coefficient;
	    cin >> index;
	}
    }
    if (!repeat || !success)
    {
	success = false;
	repeat = true;
	reset();
	return;
    }
    else
    {
	success = true;
	reset();
    }
    
   
    return;
} 


/********************************************************************************                                                    
Name:     printPoly

Purpose:  To print out the polynomial that the user entered in an exponential
          form (if necessary) using 'x' as the value for the unknown.

Details:  Uses a series of loops and decision statements to narrow down possible
          situations for the output. These take in whether or not the base is
          negative, the value of the exponent, and the value of the base.                                                                                                                                                                                

Input Parameters:                                                                                                                              
          poly polynomial []

Returns:  Nothing.                                                                                                                                                                  
********************************************************************************/
void printPoly (const poly polynomial [])
{
    int index;               // The exponent value for the polynomial
    int max_exponent = -1;   // The maximum exponent value permissible in the poly

    for (index = (MAX_SIZE - 1); index >= 0; index--)
    {
        if (polynomial[index] != 0)
        {
            if (max_exponent < index)
	    {
		if (polynomial[index] == -1)
		{
		    max_exponent = index;
		    cout << "-";
		}
		else if (polynomial[index] == 1)
		{
		    max_exponent = index;
		}
		else
		{
		    max_exponent = index;
		    cout << polynomial[max_exponent];
		}
            }
            else if (polynomial[index] == 1)
            {
                cout << " + ";
            }
            else if (polynomial[index] == -1)
            {
                cout << " - ";
            }
            else if (polynomial[index] > 0)
            {
                cout << " + " << polynomial[index];
            }
            else if (polynomial[index] < 0)
            {
                cout << " - " << (polynomial[index] * -1);
            }
            if (index > 1 && index < 21)
            {
                cout << "x^" << index;
            }
            if (index == 1)
            {
                cout << "x";
            }
            if (index == 0 && polynomial[index] == (-1))
            {
                cout << polynomial[index] * -1;
            }
            if (index == 0 && polynomial[index] == 1)
            {
                cout << polynomial[index];
            }
        }
	else if (max_exponent < index && index == 0)
	{
	    cout << "0";
	}
    }
    cout << endl;

    return;
}


/********************************************************************************                                                    
Name:     clearPoly                                                                                                                      

Purpose:  To clear the previous polynomial values if their are any and set the
          array to 0.                                                                                                                                           

Details:  The exponent starts off at 0 and increases until it reaches the
          permitted exponent value and so the exponent goes through all the
          numbers between 0 and 20. For each of these values between the numbers
          the array is set to 0, so overall the array is reset.                                                                                     

Input Parameters:                                                                                                                              
          poly polynomial []
                                                                       
Returns:  Nothing.                                                                                                                                                                  
********************************************************************************/
void clearPoly (poly polynomial [])
{
    int index;       // The exponent value of the polynomial

    for (index = 0; index < MAX_SIZE; index ++)
    {
	polynomial [index] = 0;
    }
    
    return;
}


/********************************************************************************                                                    
Name:     evaluate                                                                                              
                                                                                                                                    
Purpose:  To calculate the overall value of the polynomial by substituting a
          value for the unknown.
                                                                                                                                     
Details:  For every value in the index (all exponent values from 0-20), the array
          at that specific value multiplies itself by the unknown to the power of
          the index at that given position.                                                                                                                                     

Input Parameters: 
          poly poly []
          
          int x,
              poly1Value                                                                                                                                                                  
Returns:  Nothing.                                                                                                                                                                  
********************************************************************************/
void evaluate (const poly poly1 [], int x, int& poly1Value)
{
    int index;           // The polynomial's exponent value
    double storage = 0;  // The storage value (essentially poly1Value)
    
    cin >> x;

    for (index = (MAX_SIZE - 1); index >= 0; index --)
    {
	storage += poly1 [index] * pow(x, index);	
	poly1Value = static_cast <int> (storage);
    }

    cout << "The polynomial evaluates to: " << poly1Value << endl;
    
    return;
}


/********************************************************************************                                                    
Name:     differentiate                                                                                                                  

Purpose:  To differentiate a polynomial.                                                                                             

Details:  Brings down the polynomials index value for each value in the index and
          multiplies it by the polynomials value at that specific index. It then
          takes the index value (exponent) and subtracts 1. The function repeats
          this process in a loop until all index values are covered between 0-20.                                                                                                   

Input Parameters:                                               
          poly polynomial [],
               diff_poly []

Returns:  Nothing.                                           
********************************************************************************/
void differentiate (const poly polynomial [], poly diff_poly [])
{
    int index;         // The polynomial's exponent value
    int bring_down;    /* The exponent value that is being brought down and 
                          multiplied with the coefficient. */
    int new_exponent;  /* The new exponent value after the previous the previous
                          was brought down/multiplied with the coefficient. */
  
    for (index = (MAX_SIZE - 1); index >= 0; index --)
    {
	bring_down = (polynomial[index] * index);
	new_exponent = (index - 1);

	diff_poly [new_exponent] = bring_down;
    }

    return;
}


/********************************************************************************                                                    
Name:     sumPoly                                     

Purpose:  To add two polynomials together and provide their sum.                                                                                                         

Details:  The index (exponent) decreases from 20 until it reaches zero and
          everytime it does so the polynomial array values for the two arrays
          are added up and placed into an array containing their sums.
               
Input Parameters:                                                                                                                                                                   
          poly poly1 [],
               poly2 [],
               polySum []
                                                                                                                                     
Returns:  Nothing.                     
********************************************************************************/
void sumPoly (const poly poly1 [], const poly poly2 [], poly polySum [])
{
    int index; // The polynomial's exponent value
    
    for (index = (MAX_SIZE - 1); index >= 0; index --)
    {
        polySum [index] = poly1 [index] + poly2 [index];
    }
      
    return;
}


/********************************************************************************
Name:     multiplyPolys

Purpose:  To multiply two polynomials together and provide thier product

Details:  The function has two indexes and they both increment upwards by 1 from
          0 to 20. As long as the added values of the two indexes are less than
          or equal to 20, the product at the sum of those two added indexes is
          calculated. If the combined indexes are greater than 20 then the
          product is not calculated.

Input Parameters:
          poly poly1 [],
               poly2 [],
               product []

          bool productFound
********************************************************************************/
void multiplyPolys (const poly poly1 [], const poly poly2 [], poly product [],
		    bool& productFound)
{
    int index1;         // The exponent value for the first polynomial
    int index2;         // The exponent value for the second polynomial
    
    clearPoly (product);
    
    productFound = true;
   
    for (index2 = 0; index2 < MAX_SIZE && productFound == true; index2++)
    {
	if (poly2 [index2] != 0)
	{
	    for (index1 = 0; index1 < MAX_SIZE && productFound == true; index1++)
	    {
		if (poly1 [index1] != 0)
		{
		    if ((index1 + index2) >= 21 || (index1 + index2) <= -1)
		    {
			productFound = false;
		    }
		    else
		    {
			productFound = true;
			product [index1 + index2] += (poly1[index1] * poly2[index2]);
		    }
		}
	    }
	}	
    }

    return;
}


/********************************************************************************
Name:     rootsPoly

Purpose:  To calculate the root or roots of a polynomial if there are any

Details:  Calculates the root(s) of a polynomial if there are any using
          nested if statements to determine the differential value.
          There are also two different sets of polynomial arrays, one is for
          if the user inputted a quadratic polynomial and one is for if the user
          inputted a linear polynomial.

Input Parameters:
          poly polynomial
               
          int numRealRoots
               
          double root1,
                 root2
                 
          bool rootsFound

Returns:  Nothing.
********************************************************************************/
void rootsPoly (const poly polynomial [], int& numRealRoots, double& root1,
		double& root2, bool& rootsFound)
{
    int index = 0;                    // exponent value
    int max_index = -1;               // maximum exponent value
    
    double a_quad = polynomial[2];    /* the x^2 coefficient value in a quadratic
					 polynomial */
    double b_quad = polynomial[1];    /* the x^1 coefficient value in a quadratic
					 polynomial */
    double c_quad = polynomial[0];    /* the x^0 coefficient value in a quadratic
					 polynomial */

    double a_linear = polynomial [1]; /* the x^1 coefficient value in a linear
					 polynomial */
    double b_linear = polynomial [0]; /* the x^0 coefficient value in a linear
					 polynomial */
    
    double d = 0;                     // the differential

    rootsFound = false;               
    
    d = (pow(b_quad,2) - (4 * a_quad * c_quad));

    for (index = (MAX_SIZE - 1); index >= 0; index--)
    {
	if (max_index < index && polynomial[index] != 0)
	{
	    max_index = index;
	}
    }
	    
    if (max_index == 1)
    {
	root1 = (b_linear * -1) / a_linear;
	numRealRoots = 1;
	
	rootsFound = true;
    }
    else if (max_index == 2)
    {
	if (d > 0)
	{
	    root1 = (((-b_quad) + sqrt(d)) / (2 * a_quad));
	    root2 = (((-b_quad) - sqrt(d)) / (2 * a_quad));
	    numRealRoots = 2;
	    
	    rootsFound = true;
	}
	else if (d == 0)
	{
	    root1 = ((-b_quad) / (2 * a_quad));
	    numRealRoots = 1;
	    
	    rootsFound = true;
	}
	else if (d < 0)
	{
	    numRealRoots = 0;

	    rootsFound = true;
	}
    }    

    return;
}


/********************************************************************************
Name:     process_evaluate

Purpose:  To output all the prompts and handle the decisions if the input from
          the user is 'e'.

Details:  Displays what prompt you chose and then asks the user to enter a
          valid polynomial. The function then calls the functions readPoly and
          printPoly and if the inputted polynomial follows program guidelines
          the success statement will equate to true and the user will
          receive the evaluated polynomial value.

Input Parameters: 
          None.

Returns:  Nothing.
********************************************************************************/
void process_evaluate()
{
    poly poly1[MAX_SIZE];     // the first polynomial (only one in this case)
    bool success;             // success flag from the polynomial read in
    int x = 0;                // the value for the unknowns in a polynomial
    int polynomial1Value;     // the final value of the evaluated polynomial
    
    cout << "You chose evaluate" << endl;
    cout << "Please input a polynomial with the highest exponent being "
	 << "less than or equal to 20. Once done, press *CTRL-D* "
	 << "to terminate input screen." << endl;
    
    readPoly (poly1, success);
    printPoly (poly1);
    
    if (success == true)
    {
	cout << "Enter value for the unknown: ";
    
	evaluate (poly1, x, polynomial1Value);	    
    }
    else
    {
	cout << "Exponent Error - max exponent was greater than 20"
	     << endl;
    }
    
    return;
}


/********************************************************************************
Name:     process_differentiate

Purpose:  To output all the appropriate prompts and handle the decisions if the
          choice selected by the user is 'd'.

Details:  Uses decisions to determine whether the user input is valid (follows
          assignment guidelines for a valid input) and then outputs the
          users chosen polynomial if the read was successful using the readPoly
          and printPoly commands. After that, this function calls the 
          differentiate function and then calls print again to ouput the final
          differentiated polynomial.

Input Parameters:
          None.

Returns:  Nothing.
********************************************************************************/
void process_differentiate()
{
    poly poly1 [MAX_SIZE];      // first polynomial array (only one in this case)
    poly diff_poly [MAX_SIZE];  // the differentiated polynomial array
    bool success;               // success flag for the polynomial read in

    cout << "You chose differentiate" << endl;
    cout << "Please input a polynomial with the highest exponent being "
	 << "less than or equal to 20. Once done, press *CTRL-D* "
	 << "to terminate input screen." << endl;
    
    readPoly (poly1, success);
    printPoly (poly1);
    
    if (success == true)
    {
	clearPoly (diff_poly);
	
	cout << "Differentiated polynomial equals: ";
	
	differentiate (poly1, diff_poly);
	printPoly (diff_poly);
    }
    else if (success == false)
    {
	cout << "Error - polynomial could not be differentiated" << endl;
     }
    
    return;
}


/********************************************************************************
Name:     process_addition

Purpose:  To output all the appropriate prompts and handle the decisions if the
          choice selected by the user is 'a'.

Details:  Uses decisions to determine if the success statement returned from the 
          readPoly evaluates to true. If it is then the program prints out the
          two polynomials, followed by a line of "=" signs, followed by the
          sum of the two polynomials.

Input Parameters:
          None.

Returns:  Nothing.
********************************************************************************/
void process_addition()
{
    poly poly1 [MAX_SIZE];       // the first polynomial array
    poly poly2 [MAX_SIZE];       // the second polynomial array
    poly polySum [MAX_SIZE];     /* the polynomial's sum resulting from the
                                    addition of the first and second arrays */
    bool success;                // success flag for teh read in

    cout << "You chose add" << endl;
    cout << "Please input a polynomial with the highest exponent being "
	 << "less than or equal to 20. Once done, press *CTRL-D* "
	 << "to terminate input screen for the first polynomial."
	 << endl;

    readPoly (poly1, success);
    
    if (success == true)
    {
	cout << "Please input another polynomial with the highest exponent "
	     << "being less than or equal to 20. Once done, press *CTRL-D* "
	     << "to terminate input screen for the second polynomial."
	     << endl;
	
	if (success == true)
	{
	    readPoly (poly2, success);
	    
	    cout << endl;
	    
	    printPoly (poly1);
	    
	    cout << "[+] ";
    
	    printPoly (poly2);
    
	    cout << "==============================" << endl;
	    
	    sumPoly (poly1, poly2, polySum);
	    printPoly (polySum);	    
	}
    }
    else
    {
	cout << "Error - Polynomial addition could not be processed" << endl;
    }
    
    return;
}


/********************************************************************************
Name:     process_multiply

Purpose:  To output all the appropriate prompts and handle the decisions if the
          choice entered by the user is 'm'.

Details:  This function calls clearPoly to clear the contents of the first
          polynomial array, the second polynomial array, and then the final
          product's polynomial array. It then "couts" a prompt and if the read
          is successful for the first polynomial array, it will output the
          read option for the second polynomial array. If the read for that is
          also successful the program will print out the product of the
          two polynomials multiplication. If at any point a read is
          unsuccessful the program will print out the appropriate error message.

Input Parameters:
          None.

Returns:  Nothing.
********************************************************************************/
void process_multiply()
{
    poly poly1 [MAX_SIZE];      // the first polynomial array
    poly poly2 [MAX_SIZE];      // the second polynomial array
    poly product [MAX_SIZE];    // the array for the product after multiplication
    bool success;               // the success flag for the polynomial read in
    bool productFound;          /* the success flag for if a polynomial
				   product is valid */

    clearPoly (poly1);
    clearPoly (poly2);
    clearPoly (product);
    
    cout << "You chose multiply" << endl;
    cout << "Please input a polynomial with the highest exponent being "
	 << "less than or equal to 20. Once done, press *CTRL-D* "
	 << "to terminate input screen for the first polynomial.";
    
    readPoly (poly1, success);

    if (success == false)
    {
	cout << "Error - exponent error detected" << endl;
    }
    else if (success == true)
    {
	cout << "Please input another polynomial with the highest exponent "
	     << "being less than or equal to 20. Once done, press *CTRL-D* "
	     << "to terminate input screen for the second polynomial.";
    
	readPoly (poly2, success);
	
	cout << endl;

	if (success == false)
	{
	    cout << "Error - exponent error detected" << endl;
	}
	else if (success == true)
	{
	    multiplyPolys (poly1, poly2, product, productFound);
	
	    if (productFound == false)
	    {

		cout << "Error - The product has a max exponent value greater"
		     << " than 20" << endl;
	    }
	    else if (productFound == true)
	    {
		cout << "Performing multiplication on the polynomials";

		printPoly (poly1);
		
		cout << "[*] ";
		
		printPoly (poly2);
		
		cout << "==============================" << endl;

		printPoly (product);
	    }
	}
    }

    return;
}


/********************************************************************************
Name:     process_roots

Purpose:  To output the appropriate prompts and handle the decisions if the
          user's choice is 'r'.  

Details:  The function reads the polynomial by calling readPoly and then prints
          out the displayed polynomial using printPoly. The rootsPoly command
          is then called to determine if the polynomial has 1, 2, or no real
          roots. It does so by using decision statements and if rootsFound is
          equal to false, the program will print out the appropriate error 
          message.

Input Parameters:
          None.

Returns:  Nothing.
********************************************************************************/
void process_roots()
{
    poly poly1 [MAX_SIZE];  // the first polynomial (only one in this case)
    bool success;           // success flag for the polynomial read in
    bool rootsFound;        // success flag for the polynomials roots
    int numRealRoots;       // amount of roots in the polynomial
    double root1;           // value of the first root
    double root2;           // value of the second root

    cout << "You chose root(s)" << endl;
    cout << "Please input a polynomial with the highest exponent being "
	 << "less than or equal to 20. Once done, press *CTRL-D* "
	 << "to terminate input screen for the first polynomial.";
    
    readPoly (poly1, success);
    
    cout << endl << "The polynomial ";

    printPoly (poly1);

    cout << "has:";
    cout << endl;

    rootsPoly (poly1, numRealRoots, root1, root2, rootsFound);
    
    if (numRealRoots == 1)
    {
	cout << "Value of x1 = " << root1 << endl;
	cout << "There are " << numRealRoots
	     << " roots in this polynomial" << endl;	
    }
    else if (numRealRoots == 2)
    {
	cout << "Value of x1 = " << root1 << endl;
	cout << "Value of x2 = " << root2 << endl;
	cout << "There are " << numRealRoots
	     << " roots in this polynomial" << endl;
    }
    else if (numRealRoots == 0)
    {
	cout << "No real roots found" << endl;
    }
    else if (rootsFound == false)
    {
	cout << "Error - "
	     << "The polynomial entered is neither linear nor quadratic"
	     << endl;
    }
    
    return;
}
