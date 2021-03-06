/********************************************************************************

Name: Haris Ahmad

Email: hahma485@mtroyal.ca

Course: COMP 1631

Assignment: 6

Due Date: December 9th

Instructor: Paul Pospisil

Source File: asg6_start.cpp

=================================================================================

Purpose: The purpose of this program is to identify or narrow down 
         the potential license number, owner, make, and model of a car based on 
         what the user remembers.

Details: The program narrows down the car or potentially identifies it through
         the use of several different functions. This includes several void
         functions and a bool function. The void functions build off of each
         other to perform various tasks such as listing all the licenses, 
         matching the license plates, listing the menu options, reading the car 
         data base, and printing the licenses to the user. The program makes
         use of the boolean function to determine whether the car data base
         has a carLicense structure with similar or the same information.
   
  Input: The input is first a valid character from the menu screen (L,S,Q),
         and further input is required if the user selects 'S'. If they do,
         then they are required to put 'y' or 'n' in response to a series of
         questions regarding the license plate, model, and make of the car.
         if the user answer's 'y' to knowing any of these they are then
         prompted to input either/and the license plate, model, and make.

  Output: The program will output the list of cars from the carDB if the user 
          selects 'L'. If they select 'S' it will output the cars from the carDB 
          that match their search results. and if the user selects 'Q' the
          program will terminate and output "Have a nice day!".

Assumptions/Limitations:
         - The name length for the owner, model, and make must be less than 27..
         - The license plate must be between 6-7 characters.
         - The input (excluding initial menu screen) is case sensitive.

********************************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

using namespace std;

const int MAX_SIZE = 100;
const int PLATE_LENGTH = 7;
const int NAME_LENGTH = 25;
const char LIST_CHOICE = 'L';
const char SEARCH_CHOICE = 'S';
const char QUIT_CHOICE = 'Q';

// A structure with 4 variable arrays of type char
struct CarLicense
{
  char licensePlate[PLATE_LENGTH + 1];
  char owner[NAME_LENGTH + 1];
  char make[NAME_LENGTH + 1];
  char model[NAME_LENGTH + 1];
};

void readDatabase (CarLicense carDB[], int & fillLevel, bool & success);
void showMenuAndPrompt ();
void listAllLicenses (const CarLicense carDB[], int fillLevel);
void printLicense (CarLicense);
CarLicense getSearchData ();
void searchForLicense (const CarLicense carDB[], int fillLevel,
                       CarLicense searchData);
bool doPlatesMatch (const char plate[], const char pattern[]);


//Paul made this, don't comment.
int main ()
{
  CarLicense carDB[MAX_SIZE];
  int fillLevel;
  char choice;
  CarLicense searchData;
  bool readSuccess;
	
  readDatabase (carDB, fillLevel, readSuccess);
	
  if (readSuccess)
  {
    do {
      showMenuAndPrompt ();
      cin >> choice;
      cout << endl;
      choice = static_cast <char> (toupper(choice));
			
      switch (choice)
      {
      case LIST_CHOICE:
        listAllLicenses (carDB, fillLevel);
        break;
      case SEARCH_CHOICE:
        searchData = getSearchData();
        searchForLicense (carDB, fillLevel, searchData);
        break;
      case QUIT_CHOICE:
        // avoid erroring on quit choice
        break;
      default:
        cout << "** Invalid choice, try again." << endl << endl;
      }
    } while (choice != QUIT_CHOICE);
		
    cout << "Have a nice day!" << endl << endl;
  }
  else
  {
    cout << "** Unable to read database file; quitting." << endl << endl;
  }
	
  return 0;
}


//Paul made this, don't comment.
void readDatabase (CarLicense carDB[], int & fillLevel, bool & success)
{
  ifstream fileIn;
  const char filename[] = "carDB.txt";

  // assume success until a problem occurs
  success = true;
  fillLevel = 0;
  fileIn.open(filename);
	
  if (fileIn.fail())
  {
    success = false;
  }
  else
  {
    fileIn >> carDB[fillLevel].licensePlate;
    while (! fileIn.eof() && fillLevel < MAX_SIZE)
    {
      fileIn >> carDB[fillLevel].owner;
      fileIn >> carDB[fillLevel].make;
      fileIn >> carDB[fillLevel].model;
      fillLevel++;
			
      fileIn >> carDB[fillLevel].licensePlate;
    }
    fileIn.close();
  }

  return;
}


//Paul made this, don't comment.
void showMenuAndPrompt ()
{
  cout << "Welcome to the car license search system." << endl;
  cout << "Your options are:" << endl;
  cout << "    (L)ist all licenses." << endl;
  cout << "    (S)earch for a car." << endl;
  cout << "    (Q)uit" << endl;
  cout << endl;
  cout << "Please enter your selection: ";

  return;
}


/********************************************************************************

Name:    listAllLicenses

Purpose: To list the licences based off of the users input to the screen.

Details: Uses a while loop to increment every time a CarLicense structure is
         looked at by the program and calls the printLicense command to print
         out the car's information from the car database.

Input Parameters: 
         CarLicense carDB []
         
         int fillLevel        

Returns: Nothing.

********************************************************************************/
void listAllLicenses (const CarLicense carDB[], int fillLevel)
{
    int index = 0; //The structure being looked at in the carDB

/*While the fill level has not been reached by the index, keep printing out the 
  license */    
    while (index < fillLevel)
    {
	printLicense (carDB[index]);
	index++; //Increase the index by 1 every time the loop repeats
    }

    return;
}


/********************************************************************************

Name:    printLicense

Purpose: To print the car's license, owner, make, and model to the user.

Details: Uses many "cout" statements to print out the correct format and
         corresponding values to the user.

Input Parameters: 
         Takes in the CarLicense structure.

Returns: Nothing.

********************************************************************************/
void printLicense (CarLicense license)
{
/*A list of cout statements to print out data to the user in an
  organized manner */  
    cout << "License Plate: ";
    cout << license.licensePlate << endl;
    cout << "Owner: ";
    cout << license.owner << endl;
    cout << "Make: ";
    cout << license.make << endl;
    cout << "Model: ";
    cout << license.model << endl << endl << endl;

    return;
}


//Paul made this, don't comment.
CarLicense getSearchData ()
{
  char yesNo;
  CarLicense searchData,
             backup = { "???????", "ignore", "ignore", "ignore" };
  bool reRead = false;
  int length;
  
  searchData = backup;
	
  cout << "Did you see some or all of the license plate? (y/n): ";
  cin >> yesNo;
  if (yesNo == 'y' || yesNo == 'Y')
  {
    cout << "Enter the license plate (you can use ?s for wildcards): ";
    do
    {
      reRead = false;
      cin >> searchData.licensePlate;
      length = static_cast<int> (strlen(searchData.licensePlate));
      if (length < PLATE_LENGTH -1 || length > PLATE_LENGTH)
      {
        searchData = backup;
        reRead = true;
        cout << "** Length of entered plate is invalid -- please re-enter: ";
      }
    } while (reRead);
  }

  cout << "Did you see the make? (y/n): ";
  cin >> yesNo;
  if (yesNo == 'y' || yesNo == 'Y')
  {
    backup = searchData;
    cout << "Enter the make (case sensitive): ";
    do
    {
      reRead = false;
      cin >> searchData.make;
      length = static_cast<int> (strlen(searchData.make));
      if (length > NAME_LENGTH)
      {
        searchData = backup;
        reRead = true;
        cout << "** Length of make too long -- please re-enter: ";
      }
    } while (reRead);
  }

  cout << "Did you see the model? (y/n): ";
  cin >> yesNo;
  if (yesNo == 'y' || yesNo == 'Y')
  {
    backup = searchData;
    cout << "Enter the model (case sensitive): ";
    do
    {
      reRead = false;
      cin >> searchData.model;		
      length = static_cast<int> (strlen(searchData.model));
      if (length > NAME_LENGTH)
      {
        searchData = backup;
        reRead = true;
        cout << "** Length of model too long -- please re-enter: ";
      }
    } while (reRead);
  }
	
  return searchData;
}


/********************************************************************************

Name:    searchForLicense

Purpose: To search for the corresponding license based off the users input

Details: Uses a for loop to increment up every time and read the next possible
         match from the carDB. Inside the loop it calls the doPLatesMatch
         function and if that function equates to true it will call the
         printLicense function to output the matching information from the
         car database to the screen. 

Input Parameters:
         CarLicense carDB [],
                    searchData

         int fillLevel

Returns: Nothing.

*******************************************************************************/
void searchForLicense (const CarLicense carDB[], int fillLevel, 
                       CarLicense searchData)
{
    int index = 0; //The structure being looked at in the carDB

/*While loop which keeps going until the fill level is reached, upon which
  the loop will terminate */    
    while (index < fillLevel)
    {
	//If the license plates from the carDB and searchData match, continue
	if (doPlatesMatch(carDB[index].licensePlate, searchData.licensePlate))
	{
	    //If the make from the carDB and searchData match, continue
	    if (strcmp (carDB[index].make, searchData.make) == 0 || strcmp
		(searchData.make, "ignore") == 0)
	    {
		//If the model from the carDB and searchData match, continue
		if (strcmp (carDB[index].model, searchData.model) == 0 ||
		    strcmp (searchData.model, "ignore") == 0)
		{
		    cout << endl;
		    printLicense (carDB[index]); /*Print the license if these
						   evalute to true */
		}
	    }
	}
	
	index ++; /*Index counter increases by 1 every time the while loop
                    cycles through */
    }
	
    return;
}

    
/********************************************************************************

Name:    doPlatesMatch

Purpose: Compare the two plates character-by-character to see if they match.

Details: Takes in the user inputted inputted license plate characters and 
         compares them to patterns which are similar to the input by using a
         while loop to increment and move onto the next structure. Inside, a
         boolean value will be determined and set to true two ways being: if a
         pattern matches the license plate, or if a license plate resembles
         a pattern. If neither of these are true then the boolean value is set
         to false.

Input Parameters:
         char plate [],
              pattern []

Returns: platesMatch
         (a boolean value that determines if the enterred plates matches
          any patterns).

********************************************************************************/
bool doPlatesMatch (const char plate[], const char pattern[])
{
    int index = 0; //The structure being looked at in the carDB
    bool platesMatch = true; // The success flag for if the plates match

/*A while loop to determine if the plates match a pattern.
  The loop ends upon the plates not matching or the null terminator being reached
*/
    while (platesMatch == true && plate[index] != '\0')
    {
	if (plate [index] == pattern [index])
	{
	    platesMatch = true;
	}
	else if (pattern [index] == '?')
	{
	    platesMatch = true;
	}
	else
	{
	    platesMatch = false;
	}

	index ++; /*Index counter increases by 1 every time the while loop
                    cycles through */
    }	    
    
    return platesMatch; //Function returns the final boolean value of platesMatch
}
