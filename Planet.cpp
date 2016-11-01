#include <iostream>
#include "Planet.h"

using namespace std;

Planet::Planet()
{

}

Planet::Planet(string name, int hours, int days, int radius, int distance)
{
    Name = name;
    HoursPerDay = hours;
    DaysPerYear = days;
    Radius = radius;
    Distance = distance;
    HourOfDay = 0.0;
    DayOfYear = 0.0;

}

string Planet::getName()
{
    return Name;
}

int Planet::getHoursPerDay()
{
    return HoursPerDay;
}

int Planet::getDaysPerYear()
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

	
