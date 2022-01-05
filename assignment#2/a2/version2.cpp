// Haris Ahmad
// hahma485@mtroyal.ca
// COMP 1631
// Assignment #2
// October 2nd, 2020
// Paul Pospisil
// version2.cpp
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
    double landing_angle;
    double velocity;
    
/* Welcomes the user to the program and asks them to input values that are used 
   in calcuating the converted rates, in-air distance, velocity, and travelling
   time.
*/
    cout << "Welcome to the Air Cha–Cha Distance Finder. Ready to calculate... "
    << endl;
    
    cout << "Enter ground distance (in kilometers): ";
    cin >> ground_distance;

    cout << "Enter flying-altitude (in feet): "; 
    cin >> flying_altitude;

    cout << "Enter angle for take-off (in degrees): ";
    cin >> takeoff_angle;

    cout << "Enter angle for landing (in degrees): ";
    cin >> landing_angle;

    cout << "Enter flight velocity (in km/hr): ";
    cin >> velocity;
    
    cout << endl;

// The double values that are converted to km and radian(s) respectively
// from the original input that the user made in feet and degrees.      
    double converted_altitude;
    double converted_takeoff_angle;
    double converted_descent_angle;
    
// The double values that are used in calculating the in-air distance,
// velocity, and landing time.
    double takeoff_distance;
    double descent_distance;
    double initial_horizontal_distance;
    double final_horizontal_distance;
    double altitude_distance;

// These are the double values which are outputted using the takeoff/descent
// distances, horizontal distances, and altitude distance.
    double in_air_distance;
    double travelling_time;

// Converts the altitude from feet to km and the takeoff/descent angles
// from degrees to radians.    
    converted_altitude = flying_altitude * 0.0003048;
    converted_takeoff_angle = (takeoff_angle * (2 * M_PI)) / 360;
    converted_descent_angle = (landing_angle * (2 * M_PI)) / 360;
    
// The calculations used to find out the takeoff/descent distance, the
// initial and final horizontal distances, and altitude distance.
    takeoff_distance = converted_altitude / sin(converted_takeoff_angle);
    initial_horizontal_distance = converted_altitude /
	tan(converted_takeoff_angle);
    descent_distance = converted_altitude / sin(converted_descent_angle);
    final_horizontal_distance = converted_altitude /
	tan(converted_descent_angle);
    altitude_distance = ground_distance - initial_horizontal_distance -
	final_horizontal_distance;

// The final calculations used to calculate the desired output based off of
// the users input and the varying distances at different points in the flight.
    in_air_distance = altitude_distance + takeoff_distance + descent_distance;
    travelling_time = in_air_distance / velocity;

// The output given to the user (trip data).
    cout << "Trip data:" << endl;

    cout << "Ground distance = " << ground_distance << " km" << endl;

    cout << "Altitude = " << flying_altitude << " feet (";
    cout << converted_altitude << " km)" << endl;

    cout << "Take-off angle = " << takeoff_angle << " degrees (";
    cout << converted_takeoff_angle << " radians)" << endl;

    cout << "Landing angle = " << landing_angle << " degrees (";
    cout << converted_descent_angle << " radians)" << endl;
    
    cout << "Flight velocity = " << velocity << " km/hr" << endl << endl;

    cout << "In-air distance = " << in_air_distance << " km" << endl;

    cout << "Travelling time = " << travelling_time << " hours" << endl;

    
 return 0;

}
