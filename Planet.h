#ifndef _TANK_H_
#define _TANK_H_



#include <GL/freeglut.h>
#include <string>
using namespace std;
class Planet
{
    public:
    
	/// Constructors and Destructor
	Planet();
	Planet(string name, int hours, int days, int radius, int distance, string texture);
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
	string getTexture();
	
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
    
   
};

#endif
