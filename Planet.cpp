#include <iostream>
#include "Planet.h"

using namespace std;

Planet::Planet()
{

}

Planet::Planet(string name, int hours, int days, int radius, int distance, string texture)
{
    Name = name;
    HoursPerDay = hours;
    DaysPerYear = days;
    Radius = radius;
    Distance = distance;
    HourOfDay = 0.0;
    DayOfYear = 0.0;
	Texture = texture;

}

string Planet::getName()
{
    return Name;
}

float Planet::getHoursPerDay()
{
    return HoursPerDay;
}

float Planet::getDaysPerYear()
{
    return DaysPerYear;
}

int Planet::getRadius()
{
    return Radius;
}

int Planet::getDistance()
{
    return Distance;
}

float Planet::getHourOfDay()
{
    return HourOfDay;
}

void Planet::setHourOfDay(float hour)
{
    HourOfDay = hour;
}

float Planet::getDayOfYear()
{
    return DayOfYear;
}

void Planet::setDayOfYear(float day)
{
    DayOfYear = day;
}

string Planet::getTexture()
{
    return Texture;
}	
