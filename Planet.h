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

#ifndef _TANK_H_
#define _TANK_H_

/**************************** Library Includes *******************************/

#include <GL/freeglut.h>
#include <string>

/******************************* Name Space **********************************/

using namespace std;

/******************************** Type Def ***********************************/

typedef unsigned char byte;



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
class Planet
{
public:

    /// Constructors and Destructor
    Planet();
    Planet(string name, int hours, int days, int radius, int distance, int nrow, int cols, byte* image, GLfloat r, GLfloat g, GLfloat b);
    ~Planet();

    /// Get/Set functions
    string getName();
    float getHoursPerDay();
    float getDaysPerYear();
    int getRadius();
    int getDistance();
    void setDayOfYear(float day);
    float getDayOfYear();
    void setHourOfDay(float hour);
    float getHourOfDay();
    int getRows();
    int getCols();
    byte* getImage();
    GLfloat getR();
    GLfloat getG();
    GLfloat getB();



    /// Hit box functions

private:
    string Name;
    float DayOfYear;
    float HourOfDay;
    float HoursPerDay;
    float DaysPerYear;
    int Radius;
    int Distance;
    float HoursOfYear;
    string Texture;
    int Rows;
    int Col;
    byte* Image;
    GLfloat R;
    GLfloat G;
    GLfloat B;
};

#endif
