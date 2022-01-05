/********************************************************************************
 * Name: Haris Ahmad
 * Email: hahma485@mtroyal.ca
 * Course: COMP 1631
 * Assignment: Assignment #4
 * Due Date: November 2nd, 2020
 * Instructor Name: Paul Pospisil
 * File Name: asg4.cpp

 * Purpose: To print out a customer bill at the end of the month that processes
            the monthly transaction record which includes the users disk usage
            and fees for an online web hosting service.

 * Details: The program takes in the header record and monthly transaction 
            record. The header record contains the account number, base monthly
            charge, usage limit, and the disk usage at the beginning of the 
            month. The monthly transaction record contains the maximum disk space
            used during the month, the amount in use at the end of the month, and
            a value which indidcates whether the transaction data is valid. After
            receiving all of these values it will output a print statement to the
            screen that contains the account number, disk allotment, beginning of
            month usage, maximum usage in the month, usage at the end of the 
            month, base charge fees, the surcharge fees, additional penalty 
            surcharge fees, GST fees, and lastly the final amount due. However,
            if there is an error a respective error message will appear on the
            output.
 
 * Assumptions/ Limiations: The program only processes a single customers monthly 
                            disk usage. 
 *******************************************************************************/
#include <iostream>
#include <iomanip>
using namespace std;

bool is_valid_account_number(int);
void read_and_process(int, double, double&, double&, bool&);
void calculate_bill(double, double, double, double, double&, double&,
                    double&, double&);
void print_bill(int, double, double, double, double, double, double,
                double, double, double);

int main()
{
    int account_num;

    double usage_limit;
    double initial_usage;
    double max_usage;
    double end_usage;

    double base_charge;
    double surcharge;
    double gst;
    double total_bill;

    double penalty;
    bool no_errors;
    
    surcharge = 0;
    
    cin >> account_num >> base_charge >> usage_limit >> initial_usage;

    read_and_process (account_num, initial_usage, max_usage, end_usage, no_errors); 

    if (no_errors == true)
    {
      	calculate_bill (base_charge, usage_limit, max_usage, end_usage, surcharge,
			penalty, gst, total_bill);
	print_bill (account_num, usage_limit, initial_usage, max_usage, end_usage,
                    base_charge, surcharge, penalty, gst, total_bill);	
    }
    else
    {
	cout << "***Account " << account_num << " not processed due to errors ***" << endl;
    }
    
    return 0;
}

/********************************************************************************
 *Name: is_valid_account_number
 *
 *Purpose: To validate a customer's account number.
 *
 *Details: Uses a check digit to verify if the account number is valid and if it
           is valid it outputs a boolean value = true. Otherwise the boolean
           value = false and the account is not validated.
 *
 *Input: takes in the account number from the header record.
 *******************************************************************************/
bool is_valid_account_number (int account_num)
{
    // The 6 digits of account_num 
    int dig6;
    int dig5;
    int dig4;
    int dig3;
    int dig2;
    int dig1;

    // The check digit which validates the account_num
    int check_dig;

    bool authorize;
    
    // The calculations that extract each digit of the account number
    dig6 = account_num / 100000;
    dig5 = (account_num / 10000) % 10;
    dig4 = (account_num / 1000) % 10;
    dig3 = (account_num / 100) % 10;
    dig2 = (account_num / 10) % 10;
    dig1 = account_num % 10;

    // The calulation of the check digit
    check_dig = (dig5 * 5) + (dig4 * 4) + (dig3 * 3) + (dig2 * 2) + dig1;
    check_dig = check_dig % 10;
    
    // A decision that decides whether or not the account number is authorized
    if (dig6 == check_dig)
    {
        authorize = true;
    }
    else
    {
        authorize = false;
    }

    return authorize;
}

/********************************************************************************
 *Name: read_and_process
 *
 *Purpose: This function prints out an appropriate error message based off the
           validity of the account number and the error value in the monthly 
           tranaction record 
 *
 *Details: Three different if statements and each one corresponds to the type of
           processing error.
 *
 *Input: The function takes in the account number and the disk usage at the start
         of the month.
 *******************************************************************************/
void read_and_process (int account_num, double initial_usage, double& max_usage,
                       double& end_usage, bool& no_errors)
{
    char error_value;

    // The monthly transaction record values
    cin >> max_usage >> end_usage >> error_value;

    // Various decision options that can be outputted based on the account number
    // validation and error_value that was user inputted.

    no_errors = true;

    if (is_valid_account_number(account_num) == false && error_value == 'F')
    {
	cout << "Invalid account number " << account_num << " found" << endl;
	cout << "Bad monthly transaction record" << endl;
	no_errors = false;
    }
    if (is_valid_account_number(account_num) == false && error_value == 'T')
    {
	cout << "Invalid account number " << account_num << " found" << endl;;
	no_errors = false;
    }
    if (is_valid_account_number(account_num) == true && error_value == 'F')
    {
	cout << "Bad monthly transaction record" << endl;
	no_errors = false;
    }
           
    return;
}

/********************************************************************************
 *Name: calculate_bill
 *
 *Purpose: To calculate the fees that are printed out at the end of the month
           on the final disk usage statement.
 *
 *Details: Calculates the base charge, over-limit surcharge, gst, and total bill
           using various if-else statements. The bill calculation is based off of
           the maximum amount of disk space used during the month and the disk
           usage at the end of the month. Extra fees are taxed on based on the
           if the user goes over his disk-usage limit.
 *
 *Input: The maximum disk usage during the month and the disk usage at the end of
         the month. 
 *******************************************************************************/
void calculate_bill (double base_charge, double usage_limit, double max_usage,
                     double end_usage, double& surcharge, double& penalty,
                     double& gst, double& total_bill)
{
    double overage = max_usage - usage_limit;

    // If the overage is above the (max_usage - usage_limit) the user will be
    // charged based on how much over the limit they went and the surcharge for
    // the overage fee increases exponentially.
    if (overage > 0 && overage <= 50)
    {
	surcharge = overage * 0.15;
    }
    else if (overage > 50 && overage <= 250.0)
	surcharge = (50 * 0.15) + ((overage - 50) * 0.26);
    else if (max_usage > 250.0 && max_usage <= 500.0)
	surcharge = (50 * 0.15) + (200 * 0.26) + ((overage - 250 ) * 0.37);
    else if (max_usage > 500)
	surcharge = (50 * 0.15) + (200 * 0.26) + (250 * 0.37) + ((overage - 500) * 0.48); 

    // determines the penalty fee using a decision statement   

    penalty = (end_usage - usage_limit) * 0.05; 
    if (end_usage < usage_limit)
	penalty = 0;
 
    if (penalty > 0 && penalty < 5)
	penalty = 5;
    if (penalty > 0)
	penalty = penalty;

    // The gst is 5% of the base_charge + surcharge + penalty
    gst = (base_charge + surcharge + penalty) * 0.05;

    // The total bill is the gst + base_charge + surcharge + penalty
    total_bill = gst + base_charge + surcharge + penalty;
    
    return;
}

/********************************************************************************
 *Name: print_bill
 *
 *Purpose: To return the account number, various types of user's disk usage, and
           the fees they have to pay.
 *
 *Details: Outputs all the values to the screen in a specific allignment using
           the #include <iomanip>. There is also an if-else statement which does
           not show the penalty fee if it is equal to $0.00.
 *
 *Input: Takes in the account number, usage at the beginning of the month, the
         maximum usage during the month, the usage-limit, the usage at the end of
         the month, the base charge fee, the surchage fee, the penalty fee, 
         gst fee, and total bill .
 *******************************************************************************/
void print_bill(int account_num, double initial_usage, double max_usage,
		double usage_limit, double end_usage, double base_charge,
		double surcharge, double penalty, double gst, double total_bill)
{
    cout << "Account Number:    " << account_num << endl << endl;

    // sets the precision point of the outputted numbers in the bill statement.
    cout.setf(ios::fixed);
    cout << setprecision(3);

    // The cout statements of the numbers that have a precision of 3
    // (3 decimal places).
    cout << left << setw(22) << "Disk Allotment: " << right << setw(10)
	 << initial_usage << " MB" << endl;
    cout << left << setw(22) << "Beginning of Month: " << right << setw(10)
	 << max_usage << " MB"
	 << endl;
    cout << left << setw(22) << "Maximum during month: " << right << setw(10)
	 << usage_limit << " MB" << endl;
    cout << left << setw(22) << "End of Month: " << right << setw(10) << end_usage
	 << " MB" << endl << endl;

    cout << setprecision(2);

    // The cout statements of teh numbers that have a precision of 2
    // (2 decimal places).
    cout << left << setw(22) << "Base Charge: " << right << setw(10)
	 << base_charge << endl;
    cout << left << setw(22) << "Over-limit Surcharge: " << right << setw(10)
	 << surcharge << endl;

    // An if statement that outputs the penalty if it is above $0.00 and if
    // it is not then the penalty is not included at all in the final print
    // bill.
    if (penalty > 0)
    {
	cout << left << setw(22) << "Penalty Surcharge: " << right << setw(10)
	     <<  penalty << endl;
	cout << left << setw(22) << "GST: " << right << setw(10) << gst << endl;
	cout << left << setw(21) << "Amount Due: " << "$" << right << setw(10)
	     << total_bill << endl << endl;
    }
    else
    {
	cout << left << setw(22) << "GST: " << right << setw(10) << gst << endl;
	cout << left << setw(21) << "Amount Due: " << "$" << right << setw(10)
	     << total_bill << endl << endl;
    }
  
    return;
}
