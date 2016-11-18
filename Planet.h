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
*       This class contains all of the prototypes and attributes for a planet
*       class.
*
*	Modified: Original
*
******************************************************************************/

#ifndef _PLANET_H_
#define _PLANET_H_

/**************************** Library Includes *******************************/

#include <GL/freeglut.h>
#include <string>

/******************************* Name Space **********************************/

using namespace std;

/******************************** Type Def ***********************************/

typedef unsigned char byte;



/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Class: Planet
*
* Description:
*
*       This class contains all of the size and positional information
*       for the planet. Its a series of getters and setters abstract
*       the data for the planets.
*
******************************************************************************/
class Planet
{
public:

    /// Constructors and Destructor
    Planet();
    Planet(string name, int hours, int days, int radius, int distance, int nrow, int cols, byte* image, GLfloat r, GLfloat g, GLfloat b);
    ~Planet();

    /// Get/Set functions
    string getName();               //returns name
    float getHoursPerDay();         //return hours per year
    float getDaysPerYear();         //returns days per year
    int getRadius();                //returns radius
    int getDistance();              //returns distance to sun
    void setDayOfYear(float day);   //sets the day of year
    float getDayOfYear();           //returns the day of year
    void setHourOfDay(float hour);  //set the hour of day
    float getHourOfDay();           //returns the hour of day
    int getRows();                  //returns rows
    int getCols();                  //returns columns
    byte* getImage();               //returns pointer to texture map
    GLfloat getR();                 //returns red value
    GLfloat getG();                 //returns green value
    GLfloat getB();                 //returns blue value

private:
    string Name;        //planet name
    float DayOfYear;    //day of the year
    float HourOfDay;    //hour of the day
    float HoursPerDay;  //planet's hours in a day
    float DaysPerYear;  //planet's days in a year
    int Radius;         //planet's raduis
    int Distance;       //distance from the suns surface
    int Rows;           //number of rows in planet's texture .bmp image
    int Col;            //number of columns in planet's texture .bmp image
    byte* Image;        //pointer to location in memory of planet's stored texture map 
       					//read in from .bmp image
    GLfloat R;          //planet's red value (used for color when no texture map)
    GLfloat G;          //planet's green value (used for color when no texture map)
    GLfloat B;          //planet's blue value (used for color when no texture map)
};

#endif
