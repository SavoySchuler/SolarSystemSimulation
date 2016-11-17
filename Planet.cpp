/******************************************************************************
*	File:
*
*	Authors:
*
*	Date:
*
*	Functions Included:
*
*
*	Description:
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
* Author:
*
* Function:
*
* Description:
*
*
*
* Parameters:
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
* Author:
*
* Function:
*
* Description:
*
*
*
* Parameters:
*
******************************************************************************/
string Planet::getName()
{
    return Name;
}



/******************************************************************************
* Author:
*
* Function:
*
* Description:
*
*
*
* Parameters:
*
******************************************************************************/
float Planet::getHoursPerDay()
{
    return HoursPerDay;
}



/******************************************************************************
* Author:
*
* Function:
*
* Description:
*
*
*
* Parameters:
*
******************************************************************************/
float Planet::getDaysPerYear()
{
    return DaysPerYear;
}


/******************************************************************************
* Author:
*
* Function:
*
* Description:
*
*
*
* Parameters:
*
******************************************************************************/
int Planet::getRadius()
{
    return Radius;
}


/******************************************************************************
* Author:
*
* Function:
*
* Description:
*
*
*
* Parameters:
*
******************************************************************************/
int Planet::getDistance()
{
    return Distance;
}



/******************************************************************************
* Author:
*
* Function:
*
* Description:
*
*
*
* Parameters:
*
******************************************************************************/
void Planet::setDayOfYear(float day)
{
    DayOfYear = day;
}



/******************************************************************************
* Author:
*
* Function:
*
* Description:
*
*
*
* Parameters:
*
******************************************************************************/
float Planet::getDayOfYear()
{
    return fmod(DayOfYear,DaysPerYear);
}



/******************************************************************************
* Author:
*
* Function:
*
* Description:
*
*
*
* Parameters:
*
******************************************************************************/
void Planet::setHourOfDay(float hour)
{
    HourOfDay = hour;
}



/******************************************************************************
* Author:
*
* Function:
*
* Description:
*
*
*
* Parameters:
*
******************************************************************************/
float Planet::getHourOfDay()
{
    return fmod(HourOfDay,HoursPerDay);
}


/******************************************************************************
* Author:
*
* Function:
*
* Description:
*
*
*
* Parameters:
*
******************************************************************************/
int Planet::getRows()
{
    return Rows;
}


/******************************************************************************
* Author:
*
* Function:
*
* Description:
*
*
*
* Parameters:
*
******************************************************************************/
int Planet::getCols()
{
    return Col;
}



/******************************************************************************
* Author:
*
* Function:
*
* Description:
*
*
*
* Parameters:
*
******************************************************************************/
byte* Planet::getImage()
{
    return Image;
}



/******************************************************************************
* Author:
*
* Function:
*
* Description:
*
*
*
* Parameters:
*
******************************************************************************/
GLfloat Planet::getR()
{
    return R;
}



/******************************************************************************
* Author:
*
* Function:
*
* Description:
*
*
*
* Parameters:
*
******************************************************************************/
GLfloat Planet::getG()
{
    return G;
}



/******************************************************************************
* Author:
*
* Function:
*
* Description:
*
*
*
* Parameters:
*
******************************************************************************/
GLfloat Planet::getB()
{
    return B;
}
