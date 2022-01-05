/*
Name:        Haris Ahmad
E-mail:      hahma485@mtroyal.ca
Course:      COMP 1631 - 002
Assignment:  4, Part 1
Due Date:    November 16th, 2020
Instructor:  Paul Pospisil
Source File: a4p1.cpp

//=============================================================================

Purpose:
    This program prepares the monthly bill for a single customer of the wCubed 
    Web Hosting company.

Details:
  Input - 
    A customer account consists of two components. 
    
    The first being the header record and the second being the customer's 
    transaction records. The header record consists of four seperate values being
    the account number, base monthly charge, disk use limit, and amount of disk 
    space in MB at the beginning of the month. 

    The amount of monthly transaction records varies
    depending on how much the customer's disk increases or decreases. The values
    in each line of the transaction records respectively are an account number, 
    a character which represents whether the disk space was increased or 
    decreased, and the actual amount increased or decreased. 

  Output - 
    If the records had no errors the program returns a customers disk usage info 
    which includes: account number, allotedMB, maxMB, endMB, disk surcharge, 
    penalty surcharge, gst amount, and the amount due. 
    
    If the records do have errors they will be read and ignored and an error
    message will appear that describes the type of error and the line that the
    error occurred on. At the end of the read 3 sentences will be printed out
    stating the total # of processed lines, the total # of processed accounts,
    and the total # of processed errors.
*/

#include <iostream>
#include <iomanip>
using namespace std;

void read_and_process (int account_number, double beginMB, double& maxMB_used, 
                       double& endMB, bool& errors_detected, int& lines,
		       int& num_errors);

bool is_valid_account_number (int account_number);

void calculate_bill (double base_charge, double allottedMB, double maxMB, 
                     double endMB, double &disk_surcharge, 
                     double &penalty_surcharge, double &gst_amount, 
                     double &amount_due);
    
void print_bill (int account_number, double allottedMB, double beginMB, 
                 double maxMB, double endMB, double base_charge, 
                 double disk_surcharge, double penalty_surcharge, 
                 double gst_amount, double amount_due);

void read_and_total (int account_number, double starting_disk_usage,
		     double& max_disk_usage, double& end_disk_usage,
		     bool& errors_detected, int& lines, int& num_errors);

void read_and_ignore(int& lines);
    

// GST rate
const double GST_RATE = 0.05;

// digit precision values
const int MONEY_PRECISION = 2;
const int DISK_PRECISION = 3;

// monetary value tolerance value
const double CENTS_TOLERANCE = 0.005;

// output field widths
const int NUMERIC_WIDTH = 8;
const int ACCOUNT_LABEL_WIDTH = 22;
const int BILL_LABEL_WIDTH = 22;
const int MB_WIDTH = 3;

int main ()
{
  bool errors_detected;       // true if any errors were detected in a
                              // customer's disk transactions

  int account_number,         // customer account number
      lines,                  // the amount of lines in the input 
      num_errors,             // the number of errors in the input
      total_accounts;         // the total number of accounts that are processed
  
  double allotted_disk_space, // disk space allotment in MB for customer's plan
         starting_disk_usage, // disk space in MB in use at beginning of month
         max_disk_usage,      // maximum amount of disk space used during month
         end_disk_usage,      // disk space in use at end of month

         base_charge,         // base monthly charge for the customer's plan
         disk_surcharge,      // surcharge for extra disk space used during month
         penalty_surcharge,   // surcharge for extra disk space used at end of month
         gst_amount,          // total gst for the bill
         amount_due;          // total amount owed by customer, including GST

  lines = 0;                  // the count at which the lines start out at
  num_errors = 0;             // the count at which the errors start out at
  total_accounts = 0;         // the count at which the total amount of accounts
                              // starts out at
  
  cin >> account_number;
  
  while (!cin.eof())
  {
      cin >> base_charge >> allotted_disk_space >> starting_disk_usage;

      total_accounts++;
      lines++;
      
      errors_detected = false;

      read_and_process(account_number, starting_disk_usage, max_disk_usage,
		       end_disk_usage, errors_detected, lines, num_errors);

      if (!errors_detected)
      {
	  calculate_bill(base_charge, allotted_disk_space, max_disk_usage, 
			 end_disk_usage, disk_surcharge, penalty_surcharge,
			 gst_amount, amount_due);
	  
	  print_bill(account_number, allotted_disk_space, starting_disk_usage, 
		     max_disk_usage, end_disk_usage, base_charge,
		     disk_surcharge, penalty_surcharge, gst_amount, amount_due);
      }

      cin >> account_number;
  }

  cout << "Processed #" << lines << " total lines. "
       << "Processed #" << total_accounts << " accounts. "
       << "Processed #" << num_errors << " errors." << endl;
  
  return 0;
}

//*****************************************************************************
/*
Name:     read_and_process

Purpose:  1) processes transaction records
          2) handles errors in the transaction records (calls read_and_total)
          3) ignores transaction records (calls read_and_ignore)

Details:
          Calls in either read_and_ignore or read_and_total depending on
          whether or not the account number is valid. It does so by processing
          the is_valid_account function and if found to be invalid it will call
          read_and_ignore and if the account number is valid it will call
          read_and_total.

Input Parameters: int (customer account number)
                      (amount of lines in transaction records)
                      (the number of errors in the transactionrecords)
		  double (customer's starting disk usage)
                         (customer's maximum disk usage in the month)
                         (customer's disk usage at the end of the month)
                  bool (any transaction errors detected in the read)

Returns:  Nothing.
*/
void read_and_process
  (int account_number,           // customer account number
   double starting_disk_usage,   // disk space in use at beginning of month
   double& max_disk_usage,       // maximum disk space used during month
   double& end_disk_usage,       // disk space in use at end of month
   bool& errors_detected,        // true if any transaction errors were detected
   int& lines,                   // number of lines in customer's transactions   
   int& num_errors)              // amount of errors in customer's transcations
{
  if (!is_valid_account_number (account_number))
  {
    read_and_ignore (lines);
  } 
  else
  {  
      read_and_total (account_number, starting_disk_usage, max_disk_usage,
		      end_disk_usage, errors_detected, lines, num_errors);
  }

  lines++;
  
  return;

}  // end read_and_process

//*****************************************************************************
/*
Name:     read_and_total

Purpose:  Processes a series of valid transaction errors and passes back the
          maximum/end of month disk usage until the sentinel record is
          encountered.

Details:
          Has a series of if statements nestled within a while loop. three of
          the if statements will elaborate upon what kind of error the
          transaction record encountered and the other three determine the 
          max/end disk usage and the increase/decrease in disk space for a
          customer throughout the month.

Input Parameters: int (customer account number)
                      (amount of lines in transaction records)
                      (the number of errors in the transactionrecords)
		  double (customer's starting disk usage)
                         (customer's maximum disk usage in the month)
                         (customer's disk usage at the end of the month)
                  bool (any transaction errors detected in the read)
Returns:  Nothing.
*/
void read_and_total
  (int account_number,           // customer account number
   double starting_disk_usage,   // disk space in use at beginning of month
   double& max_disk_usage,       // maximum disk space used during month
   double& end_disk_usage,       // disk space in use at end of month
   bool& errors_detected,        // true if any transaction errors were detected
   int& lines,                   // number of lines in customer's transactions   
   int& num_errors)              // amount of errors in customer's transcations 
{
    int new_account_number;      // the account number in the transaction record

    char transaction_code;       // the transaction code signifying an increase or
                                 // decrease in disk space

    double new_usage;            // the usage added or subtracted from the
                                 //  initial usage

    cin >> new_account_number >> transaction_code >> new_usage;

    end_disk_usage = starting_disk_usage;
    max_disk_usage = starting_disk_usage;
    
    while (new_account_number != -1 || transaction_code != 'X'
	   || new_usage != -1)
    {
	lines++;
	
	if (new_usage < 0)
	{
	    errors_detected = true;
	    num_errors++;
	    cout << "Error in line #" << lines
		 << " - invalid transaction amount "
		 << new_usage << endl;
	}
	if (transaction_code != 'C' && transaction_code != 'D')
	{
	    errors_detected = true;
	    num_errors++;
	    cout << "Error in line #" << lines
		 << " - invalid transaction code '"
		 << transaction_code << "'" << endl;
	}
       	if (transaction_code == 'C')
	{
	    end_disk_usage = end_disk_usage + new_usage;
	}
	if (transaction_code == 'D')
	{
	    end_disk_usage = end_disk_usage - new_usage;
	}
	if (account_number != new_account_number)
	{
	    errors_detected = true;
	    num_errors++;
	    cout << "Error in line #" << lines
		 << " - non-matching account number "
		 << new_account_number <<  endl;
	}
	if (end_disk_usage > max_disk_usage)
	{
	    max_disk_usage = end_disk_usage;
	}
	
	cin >> new_account_number >> transaction_code >> new_usage;
    }       
    
    return;
} // end read_and_total

//*****************************************************************************
/*
Name:     read_and_ignore

Purpose:  To read the transaction records and increment the amount of lines
          everytime a new transaction record line is read in by the program. 

Details:  Has 3 variables for each item in a single transaction record line
          and adds a line in the total line count using a while loop until the
          sentinel record is encountered.

Input Parameters: int (the amount of lines)

Returns:  Nothing.
*/
void read_and_ignore
  (int& lines)           //the amount of lines in the overall transaction record.
{
    int new_account_number;    // the account number in the transaction record

    char transaction_code;     // the transaction code signifying an increase or
                               // decrease in disk space

    double new_usage;          // the usage added or subtracted from the
                               //  initial usage

    cin >> new_account_number >> transaction_code >> new_usage;

    while (new_account_number != -1 || transaction_code != 'X'
	   || new_usage != -1)
	{ 
	    lines++;
	    
	    cin >> new_account_number >> transaction_code >> new_usage;
	}

    return;
} // end read_and_ignore
	
//*****************************************************************************
/*
Name:     is_valid_account_number

Purpose:  Determines whether an account number is valid. 

Details:
         To be valid:
          - it must be exactly six digits in length
          - its rightmost digit must be equal to the units digit of the sum of
	    the other five digits weighted by their digit position, starting
	    at 1 for the units digit

Input Parameters:  the account number to be validated

Returns:  true if the account number is valid, false if it is not
*/

bool is_valid_account_number (int account_number)          // the account number
{
  int quotient,   // the quotient on repeated division of the account number,
                  // by 10, eventually the check digit
      position,   // position of currently extracted digit 
      sum;        // the weighted sum

  bool valid;     // true if the account number is valid, false if not
  const int MIN_VALID_ACCOUNT = 100000;
  const int MAX_VALID_ACCOUNT = 999999;
  const int FIRST_POSITION = 1;
  const int LAST_POSITION = 5;
 
  if (account_number < MIN_VALID_ACCOUNT 
      || account_number > MAX_VALID_ACCOUNT)
    valid = false;
  else
  {
    sum = 0;
    quotient = account_number;
    for (position = FIRST_POSITION; position <= LAST_POSITION; position++)
    {
      sum = sum + position * (quotient % 10);
      quotient = quotient / 10;
    }
    valid = (quotient == sum % 10);
  }

  return valid;
}  // end is_valid_account_number

//******************************************************************************
// Name:  calculate_bill
//
// Oops - no doc, but needed to describe the way the bill is calculated with
//        the basic charge plus any surcharges. The details of the surcharges
//        need to be specified.

void calculate_bill
  (double base_charge,         // base monthly charge for plan
   double allotted_disk_space, // disk space allotment for plan
   double max_disk_usage,      // maximum disk space used during month
   double end_disk_usage,      // disk space in use at end of month
   double& disk_surcharge,     // surcharge for extra disk space used during month
   double& penalty_surcharge,  // surcharge for extra disk space used at end of month
   double& gst_amount,         // gst owed for bill
   double& amount_due)         // amount owed by customer
{
  double over;
  const double PENALTY_SURCHARGE_COST = 0.05;
  const double MIN_PENALTY_SURCHARGE = 5.00;
  const double OVER_LIMIT_1 = 50.0;
  const double OVER_LIMIT_2 = 250.0;
  const double OVER_LIMIT_3 = 500.0;
  const double OVER_LIMIT_COST_1 = 0.15;
  const double OVER_LIMIT_COST_2 = 0.26;
  const double OVER_LIMIT_COST_3 = 0.37;
  const double OVER_LIMIT_COST_4 = 0.48;
  const double OVER_LIMIT_FULL_COST_1 = OVER_LIMIT_1 * OVER_LIMIT_COST_1;
  const double OVER_LIMIT_FULL_COST_2 = (OVER_LIMIT_2 - OVER_LIMIT_1)
                                            * OVER_LIMIT_COST_2;
  const double OVER_LIMIT_FULL_COST_3 = (OVER_LIMIT_3 - OVER_LIMIT_2)
                                         * OVER_LIMIT_COST_3;

  disk_surcharge = 0.0;
  penalty_surcharge = 0;
  if (max_disk_usage > allotted_disk_space)
  {
    over = max_disk_usage - allotted_disk_space;
    if (over <= OVER_LIMIT_1)
      disk_surcharge = OVER_LIMIT_COST_1 * over;
    else if (over <= OVER_LIMIT_2)
      disk_surcharge = OVER_LIMIT_FULL_COST_1 + 
        OVER_LIMIT_COST_2 * (over - OVER_LIMIT_1);
    else if (over <= OVER_LIMIT_3)
      disk_surcharge = OVER_LIMIT_FULL_COST_1 + OVER_LIMIT_FULL_COST_2 
                       + OVER_LIMIT_COST_3 * (over - OVER_LIMIT_2);
    else
      disk_surcharge = OVER_LIMIT_FULL_COST_1 + OVER_LIMIT_FULL_COST_2 
                       + OVER_LIMIT_FULL_COST_3 
                       + OVER_LIMIT_COST_4 * (over - OVER_LIMIT_3);

    if (end_disk_usage > allotted_disk_space)
    {
      penalty_surcharge = (end_disk_usage - allotted_disk_space) 
                            * PENALTY_SURCHARGE_COST;

      if (penalty_surcharge < MIN_PENALTY_SURCHARGE)
      {
        penalty_surcharge = MIN_PENALTY_SURCHARGE;
      }
    }
  }

  gst_amount = (base_charge + disk_surcharge + penalty_surcharge) * GST_RATE;
  amount_due = base_charge + disk_surcharge + penalty_surcharge + gst_amount;

  return;
}  // end calculate_bill

//*****************************************************************************
/*
Name:     print_bill

Purpose:  Prints a customer bill.

Details:  Each bill item is printed on a separate line with an
          appropriate label and then value.
          The label field is 22 characters wide
          The data field is 8 characters wide, 
            the exception is the last record, the total amount due,
            which has one fewer character due to printing the '$'.
          Numeric values are output with a fixed number of decimal places:
            3 for disk usage
            2 for monetary values

Input Parameters:
          int    the customer's account number
          double disk space allowed by plan
                 disk used at start of month
                 maximum disk used during month
                 disk usage at end of month
                 basic charge for plan
                 surcharge for exceeding disk allotment
                 total amount of bill

Returns:  nothing
*/
      
void print_bill
  (int account_number,         // customer account number
   double allotted_disk_space, // disk space allotment for the plan
   double starting_disk_usage, // disk space in use at beginning of month
   double max_disk_usage,      // maximum disk space used during month
   double end_disk_usage,      // disk space in use at end of month
   double base_charge,         // base monthly charge for plan
   double disk_surcharge,      // surcharge for extra disk space used
   double penalty_surcharge,   // surcharge for extra disk space used at end of month
   double gst_amount,          // gst owed for bill
   double amount_due)          // amount owed by customer

{
  cout << fixed;              // set output form to fixed point notation

  cout << endl
       << left << setw(ACCOUNT_LABEL_WIDTH) << "Account Number:" 
       << right << account_number << endl << endl;

  cout << setprecision (DISK_PRECISION);
  cout << left << setw(BILL_LABEL_WIDTH) << "Disk Allotment:" 
       << right << setw(NUMERIC_WIDTH) << allotted_disk_space 
       << setw(MB_WIDTH) << "MB" << endl;
  cout << left << setw(BILL_LABEL_WIDTH) << "Beginning of Month:" 
       << right << setw(NUMERIC_WIDTH) << starting_disk_usage
       << setw(MB_WIDTH) << "MB" << endl;
  cout << left << setw(BILL_LABEL_WIDTH) << "Maximum during Month:" 
       << right << setw(NUMERIC_WIDTH) << max_disk_usage 
       << setw(MB_WIDTH) << "MB" << endl;
  cout << left << setw(BILL_LABEL_WIDTH) << "End of Month:" 
       << right << setw(NUMERIC_WIDTH) << end_disk_usage 
       << setw(MB_WIDTH) << "MB" << endl << endl;

  cout << setprecision (MONEY_PRECISION);
  cout << left << setw(BILL_LABEL_WIDTH) << "Base Charge:" 
       << right << setw(NUMERIC_WIDTH) << base_charge << endl;

  if (disk_surcharge >= CENTS_TOLERANCE)
  {
    cout << left << setw(BILL_LABEL_WIDTH) << "Over-limit Surcharge:" 
         << right << setw(NUMERIC_WIDTH) << disk_surcharge << endl;
  }

  if (penalty_surcharge >= CENTS_TOLERANCE)
  {
    cout << left << setw(BILL_LABEL_WIDTH) << "Penalty Surcharge:" 
         << right << setw(NUMERIC_WIDTH) << penalty_surcharge << endl;
  }

  cout << left << setw(BILL_LABEL_WIDTH) << "GST:" 
       << right << setw(NUMERIC_WIDTH) << gst_amount << endl;
  cout << left << setw(BILL_LABEL_WIDTH) << "Amount Due:" << '$'
       << right << setw(NUMERIC_WIDTH-1) << amount_due << endl << endl;

  return;
}  // end print_bill
