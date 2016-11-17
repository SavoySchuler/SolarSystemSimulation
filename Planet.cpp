#include <iostream>
#include <cmath>
#include "Planet.h"

using namespace std;

Planet::Planet()
{

}

Planet::Planet(string name, int hours, int days, int radius, int distance, int nrow, int cols, byte* image)
{
    Name = name;
    HoursPerDay = hours;
    DaysPerYear = days;
    Radius = radius;
    Distance = distance;
    HourOfDay = 0.0;
    DayOfYear = 0.0;
	Rows = nrow;
	Col = cols;
	Image = image;

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

void Planet::setDayOfYear(float day)
{
	DayOfYear = day;
}

float Planet::getDayOfYear()
{
	return fmod(DayOfYear,DaysPerYear);
}

void Planet::setHourOfDay(float hour)
{
	HourOfDay = hour;
}

float Planet::getHourOfDay()
{
	return fmod(HourOfDay,HoursPerDay);
}

int Planet::getRows()
{
    return Rows;
}

int Planet::getCols()
{
    return Col;
}

byte* Planet::getImage()
{
    return Image;
}
