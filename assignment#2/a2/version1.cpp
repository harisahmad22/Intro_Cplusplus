// Haris Ahmad
// hahma485@mtroyal.ca
// COMP 1631
// Assignment #2
// October 2nd, 2020
// Paul Pospisil
// version1.cpp
/* Purpose: To calculate and compute the different components used in
            calculating the overall in-are distance travelled and
            travelling time.
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
// The integer names that are going to be user inputted.
    double ground_distance;
    double flying_altitude;
    double takeoff_angle;

// Welcomes the user to the program and asks them to input values that are used 
// in calcuating the converted rates, in-air distance, and travelling time.

    cout << "Welcome to the Air Cha–Cha Distance Finder. Ready to calculate... "
    << endl;
    
    cout << "Enter ground distance (in kilometers): ";
    cin >> ground_distance;

    cout << "Enter flying-altitude (in feet): "; 
    cin >> flying_altitude;

    cout << "Enter angle for take-off (in degrees): ";
    cin >> takeoff_angle;

    cout << endl;

// The double values that are converted to km and radians respectively from the
// original input that the user made in feet and degrees.    
    double converted_altitude;
    double converted_angle;

// The double values that are used in calculating the in-air distance and hence
// the travelling time as well. 
    double takeoff_distance;
    double horizontal_distance;
    double altitude_distance;

// These are the double values which are outputted using the takeoff distance,
// horizontal distance, and altitude distance.
    double in_air_distance;
    double travelling_time;
    double velocity;

// Converts the altitude from feet to km and the angle from degrees to radians.    
    converted_altitude = flying_altitude * 0.0003048;
    converted_angle = (takeoff_angle * (2 * M_PI)) / 360;

// The calculations used to find out the takeoff distance, horizontal distance,
// and altitude distance.
    takeoff_distance = converted_altitude / sin(converted_angle);
    horizontal_distance = converted_altitude / tan(converted_angle);
    altitude_distance = ground_distance - (2 * horizontal_distance);

// The final calculations used to calculate the desired output based off of
// the users input.
    in_air_distance = altitude_distance + (takeoff_distance * 2);
    travelling_time = in_air_distance / 400;
    velocity = in_air_distance / travelling_time;

// The output given to the user (trip data).
    cout << "Trip data:" << endl;

    cout << "Ground distance = " << ground_distance << " km" << endl;

    cout << "Altitude = " << flying_altitude << " feet (";
    cout << converted_altitude << " km)" << endl;

    cout << "Take-off angle = " << takeoff_angle << " degrees (";
    cout << converted_angle << " radians)" << endl;

    cout << "Default velocity = " << velocity << " km/hr" << endl << endl;

    cout << "In-air distance = " << in_air_distance << " km" << endl;

    cout << "Travelling time = " << travelling_time << " hours" << endl;

    
 return 0;

}
