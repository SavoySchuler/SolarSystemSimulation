/******************************************************************************
*	File: Planet.cpp
*
*	Authors: Daniel Hodgin and Savoy Schuler
*
*	Date: 11-18-2016
*
*	Functions Included:
*
*       string getName();
*       float getHoursPerDay();
*       float getDaysPerYear();
*       int getRadius();
*       int getDistance();
*       void setDayOfYear(float day);
*       float getDayOfYear();
*       void setHourOfDay(float hour);
*       float getHourOfDay();
*       int getRows();
*       int getCols();
*       byte* getImage();
*       GLfloat getR();
*       GLfloat getG();
*       GLfloat getB();
*
*	Description:
*       This class contains all of the size and positional information
*       for the planet. Its a series of getters and setters abstract
*       the data for the planets
*       
*
*	Modified: Original
*
*
******************************************************************************/

/**************************** Library Includes *******************************/
#include <iostream>
#include <cmath>
#include "Planet.h"

/******************************* Name Space **********************************/

using namespace std;


/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function:Planet
*
* Description:
*       Constructor. Reads in the data for planet
*
*
* Parameters:
*
*   name        -Name of planet
*
*   hours       -Hours Per Day
*
*   days        -Days per year
*   
*   radius      -Radius of the planet
*
*   distance    -distance from the suns surface
*
*   nrow        -rows of the image
*
*   cols        -number of columns of image
*
*   image       -byte array of image information
*
*   r           -Red value
*
*   g           -Green value
*
*   b           -Blue value
*
******************************************************************************/
Planet::Planet(string name, int hours, int days, int radius, int distance, int nrow, int cols, byte* image, GLfloat r, GLfloat g, GLfloat b)
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
    R = r;
    G = g;
    B = b;

}


/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function:getName
*
* Description:
*       returns name
*
*
* Parameters:
*   
*   void        -no parameter
*
******************************************************************************/
string Planet::getName()
{
    return Name;
}



/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function:getHoursPerDay
*
* Description:
*       returns HoursPerDay
*
*
* Parameters:
*   
*   void        -no parameter
*
******************************************************************************/
float Planet::getHoursPerDay()
{
    return HoursPerDay;
}



/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function:getDaysPerYear
*
* Description:
*       returns DaysPerYear
*
*
* Parameters:
*   
*   void        -no parameter
*
******************************************************************************/
float Planet::getDaysPerYear()
{
    return DaysPerYear;
}


/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function:getRadius
*
* Description:
*       returns Radius
*
*
* Parameters:
*   
*   void        -no parameter
*
******************************************************************************/
int Planet::getRadius()
{
    return Radius;
}


/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function:getDistance
*
* Description:
*       returns Distance
*
*
* Parameters:
*   
*   void        -no parameter
*
******************************************************************************/
int Planet::getDistance()
{
    return Distance;
}



/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function:setDayOfYear
*
* Description:
*       Sets DayOfYear.
*
*
* Parameters:
*
*   day        -current day of year
*
******************************************************************************/
void Planet::setDayOfYear(float day)
{
    DayOfYear = day;
}



/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function:getDayOfYear
*
* Description:
*       returns DayOfYear
*
*
* Parameters:
*   
*   void        -no parameter
*
******************************************************************************/
float Planet::getDayOfYear()
{
    return fmod(DayOfYear,DaysPerYear);
}



/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function:setHourOfDay
*
* Description:
*       Sets HourOfDay.
*
*
* Parameters:
*
*   hour        -current hour of the day
*
******************************************************************************/
void Planet::setHourOfDay(float hour)
{
    HourOfDay = hour;
}



/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function:getHourOfDay
*
* Description:
*       returns HourOfDay
*
*
* Parameters:
*   
*   void        -no parameter
*
******************************************************************************/
float Planet::getHourOfDay()
{
    return fmod(HourOfDay,HoursPerDay);
}


/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function:getRows
*
* Description:
*       returns Rows
*
*
* Parameters:
*   
*   void        -no parameter
*
******************************************************************************/
int Planet::getRows()
{
    return Rows;
}


/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function:getCols
*
* Description:
*       returns Col
*
*
* Parameters:
*   
*   void        -no parameter
*
******************************************************************************/
int Planet::getCols()
{
    return Col;
}



/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function:getImage
*
* Description:
*       returns Image
*
*
* Parameters:
*   
*   void        -no parameter
*
******************************************************************************/
byte* Planet::getImage()
{
    return Image;
}



/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function:getR
*
* Description:
*       returns R
*
*
* Parameters:
*   
*   void        -no parameter
*
******************************************************************************/
GLfloat Planet::getR()
{
    return R;
}



/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function:getG
*
* Description:
*       returns G
*
*
* Parameters:
*   
*   void        -no parameter
*
******************************************************************************/
GLfloat Planet::getG()
{
    return G;
}



/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function:getB
*
* Description:
*       returns B
*
*
* Parameters:
*   
*   void        -no parameter
*
******************************************************************************/
GLfloat Planet::getB()
{
    return B;
}
