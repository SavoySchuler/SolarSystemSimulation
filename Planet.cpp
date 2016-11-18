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
*
*       This class contains all of the information for the planet objects. It is
*       a series of getters and setters for planet specific data.
*       
*	Modified: Original
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
*
*       Returns planet name.
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
*
*       Returns hours per planet's day.
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
*
*       Returns days per planet's year.
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
*
*   Returns planet's radius.
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
*       
*   Returns planet's distance from surface of the sun.
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
*       
*   Set's planet's day of year.
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
*       
*   Returns planet's current day of the year.
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
*       
*   Sets planet's hour of the day.
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
*       
*   Return's planets current hour of the day.
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
*       
*   Returns number of rows in planet's texture map.
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
*       
*   Returns number of columns in planet's texture map.
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
*       
*   *   Returns pointer planet's texture map stored in memory.
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
*       
*   Returns planet's R value (RGB).
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
*       
*   Returns planet's G value (RGB).
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
*       
*   Returns planet's B value (RGB).
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
