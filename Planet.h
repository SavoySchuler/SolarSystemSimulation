#ifndef _TANK_H_
#define _TANK_H_

#include <GL/freeglut.h>
#include <string>

using namespace std;

typedef unsigned char byte;

class Planet
{
    public:
    
	/// Constructors and Destructor
	Planet();
	Planet(string name, int hours, int days, int radius, int distance, int nrow, int cols, byte* image);
	~Planet();
	
	/// Get/Set functions
    string getName();
    float getHoursPerDay();
    float getDaysPerYear();
    int getRadius();
    int getDistance();
    float getHourOfDay();
    void setHourOfDay(float hour);
    float getDayOfYear();
    void setDayOfYear(float day);
	int getRows();
	int getCols();
	byte* getImage();
	
	
	/// Hit box functions


    private:
    string Name;
    float HoursPerDay;
    float DaysPerYear;
    int Radius;
    int Distance;
    float HourOfDay;
    float DayOfYear;
	string Texture;
    int Rows; 
    int Col;
    byte* Image;
   
};

#endif
