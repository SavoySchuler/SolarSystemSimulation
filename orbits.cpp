/******************************************************************************
*	File: orbits.cpp
*
*	Authors: Savoy Schuler and Daniel Hodgin
*
*	Date: 11-17-16
*
*	Description:
*
*		This file contains all of the draw function for the planets. It handles
*       setting lighting and light source location as well as material 
*       properties. 
*        
*       This file includes functions for handling transforms, rotations, as well
*       as setting the planets in the proper places around the sun.
*
*	File Order and Structure:
*
*       - Create auxiliary planet objects Rings and Moon.
*       - Set light source.
*       - Set object material properties. 
*       - Draw objects.
*       - Set up texture map. 
*       - Helper functions
*
*	Modified: 
*
*		none - Original
*
*	Functions Included:
*		
*           //Create auxiliary planet objects Rings and Moon.
*       
*       void SetRingsandMoon();
*
*           //Set light source.
*
*       void SetLightModel();
*
*           //Set object material properties. 
*
*       void SetSunMatProp(Planet *sun);
*       void SetPlanetMatProps(Planet *plant);
*       void SetMoonMatProps(Planet *Moon);
*       void SetRingsMatProps(Planet *Rings);
*       void SetOrbitMatProps();
*
*           //Draw objects.
*    
*       void DrawSpace(Planet *space);
*       void DrawSun(Planet *sun);
*       void DrawPlanet(Planet *plant);
*       void DrawMoon(int DayOfYear);
*       void DrawTextString( string str, double radius);
*
*           //Set up texture map. 
*        
*       int SetTexture( byte* image, int rows, int ncols );
*
*           //Handle user view.
*
*       void HandleRotate();
*
*           //Convert image string files names to character arrays). 
*
*       char* stringToChar (string str);
*
******************************************************************************/

/**************************** Library Includes *******************************/
#include <cstdlib>
#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include "Planet.h"
#include "globals.h"

/********************************* Globals ***********************************/

//Global pointers to auxiliary planet objects.

Planet *Moon;
Planet *Rings;



/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function: setCelestialBodies
*
* Description:
*
*	This function creates planet objects for Saturn's rings and Earth's moon and
*   sets the fields for each. Each planet object is addressed by its 
*   corresponding global pointer declared at the top of this file. 
*   SetRingsandMoon also handles calling functions for reading and storing each 
*   objects texure map.
* 
*	The planet object has the following fields in order:
*	
*		name	- planet name
*		hours	- planet's hours in a day
*		days	- planet's days in a year
*		radius	- planet's raduis
*		row 	- number of rows in planet's texture .bmp image
*		cols	- number of columns in planet's texture .bmp image
*		image	- pointer to location in memory of planet's stored texture map 
*					read in from .bmp image
*		r		- planet's red value (used for color when no texture map)
*		g		- planet's green value (used for color when no texture map)
*		b		- planet's blue value (used for color when no texture map)
*
* Parameters:
*
*		void	- No input parameters needed.
*
******************************************************************************/
void SetRingsandMoon()
{

	/*Variables needed for storing a pointer to and dimensions of a planet's 
	texture map. */ 
    int nrows, ncols;
    byte* image;
    char * filename;

							/*Set up each planet*/

	//Convert a texture map's string name into a character array.
	//Load a planet's texure map into memory.
	//Construct a planet object pointed to by a global pointer (planet's name).

    filename = StringToChar("moon.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Moon = new Planet("Moon", 0, 0, 0, 0, nrows, ncols, image, 1.0, 1.0, 1.0 );

    filename = StringToChar("saturnrings.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Rings = new Planet("Saturn Rings", 0, 0, 0, 0, nrows, ncols, image, 1.0, 0.75, 0.0 );
}



/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function: SetLightModel
*
* Description:
*
*   Set the position and properties of the point light source.
*
* Parameters:
*
*		void	- No input parameters needed.
*
******************************************************************************/
void SetLightModel()
{
    //Reset position.
    glLoadIdentity();
    
    //Handle rotion based on user view.
    HandleRotate();

    //Handle translation based on user view.
    glTranslatef ( Xpan, Ypan, Zpan );

    /*Set value arrays for ambient, diffuse, and specular light properties and 
    position.*/
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };

    //Set the lighting properties.
    glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular );

    //Enable light.
    glEnable( GL_LIGHT0 );

   
    //glColor3f ( 0.5, 0.5, 0.5 );
    glEnable( GL_NORMALIZE );    // automatic normalization of normals
    glEnable( GL_CULL_FACE );    // eliminate backfacing polygons
    glCullFace( GL_BACK );
}

















/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function: HandleRotate
*
* Description:
*	This function handles the x,y,z rotation based off of globals that are
*   set by our user control functions
*
* Parameters:
*   void            -no parameters
*
******************************************************************************/
void HandleRotate()
{
    //Rotate on x axis.
    glRotatef( Xrot, 1.0, 0.0, 0.0);

    //Rotate on y axis.
    glRotatef( Yrot, 0.0, 1.0, 0.0);

    //Rotate on z axis.
    glRotatef( Zrot, 0.0, 0.0, 1.0);
}



/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function: StringToChar
*
* Description:
*   This function converts a string into a * char
*
* Parameters:
*   str         -string to convert to a char *
******************************************************************************/
char * StringToChar (string str)
{
    //Allocate memory.
    char * filename = new char[str.size() + 1];
    
    //Copy data to the char * array.
    std::copy(str.begin(), str.end(), filename);

    //Add null terminator.
    filename[str.size()] = '\0'; // don't forget the terminating 0
    return filename;
}



/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function: Draw Rings
*
* Description:
*   This function draws the rings of saturn. It uses the gluCylinder to draw
*   the rings. It takes in saturns radius and sets the outside and inside
*   radii by offsetting that value. A bmp is also mapped to the rings.
*
* Parameters:
*   planetRadius        -the radius of saturn
*
******************************************************************************/
void DrawRings(double planetRadius)
{       
    int nrows = Rings->getRows();
    int ncols = Rings->getCols();
    byte* image = Rings->getImage();

    //Enable drawing the back side of polygons
    glDisable( GL_CULL_FACE );

    //Set the rings lighting properties.
    SetRingsMatProps(Rings);

    //Set the rings texture properties.
    SetTexture(image, nrows, ncols);

    //Combine texture mapping with lighting material properties.
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );


    //Create glu quadric object. 
    GLUquadric *quad;
    quad = gluNewQuadric();

    //Enable textures on the object.
    gluQuadricTexture(quad, GL_TRUE);
    
    //Draw the rings using gluCylinder.
    gluCylinder(quad, planetRadius * SizeScale + 0.5, 
                planetRadius * SizeScale + 2 ,0.1, Resolution, Resolution);

    //delete the quadric object
    gluDeleteQuadric( quad );

    //disable drawing backside of polygons
    glEnable( GL_CULL_FACE );
}



/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
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
void SetRingsMatProps(Planet *Rings)
{
    glColor3f( 1.0, 1.0, 1.0 );

    if ( textureToggle == false )
    {
        GLfloat mat_shininess = { 100.0 };
        GLfloat mat_emission[] = {0.0, 0.0, 0.0, 1.0};
        GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
        
        GLfloat color[] = {Rings->getR(), Rings->getG(), Rings->getB()};        //##SAVOY
        glColor3f( Rings->getR(), Rings->getG(), Rings->getB() );

        glMaterialfv( GL_FRONT, GL_SPECULAR, color  );
        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
        glMaterialfv( GL_FRONT, GL_DIFFUSE, color );
        glMaterialf( GL_FRONT, GL_SHININESS, mat_shininess );
        glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, mat_emission );
    }

    else
    {
        GLfloat mat_specular[] = { 0.8, 0.8, 0.0, 1.0 };
        GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
        GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat mat_shininess = { 100.0 };
        GLfloat mat_emission[] = {0.2, 0.2, 0.2, 1.0};

        glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
        glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
        glMaterialf( GL_FRONT, GL_SHININESS, mat_shininess );
        glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, mat_emission );
    }
}



/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function: DrawMoon
*
* Description:
*   This function draw the moon in the proper place around the earth.
*   It reads in the day of the year and sets the location based of that value.
*   This function uses the gluSphere function to draw the moon and texture
*   map to it.
*
* Parameters:
*   DayOfYear       - the time of year to set the location of the moon
******************************************************************************/
void DrawMoon(int DayOfYear)
{    
    int nrows = Moon->getRows();
    int ncols = Moon->getCols();
    byte* image = Moon->getImage();

    //Rotate the location of the moon around the based of the time.
    glRotatef( 360.0 * 12.0 * DayOfYear / 365.0, 0.0, 0.0, 1.0 );

    //Translate the moon away from the earth.
    glTranslatef( 0.7, 0.0, 0.0 );

    //Set the moons lighting properties.
    SetMoonMatProps(Moon);

    //Set the moons textures properties.
    SetTexture(image, nrows, ncols);

    //Combine texture and lighting properties.
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    //Draw name if names toggel is set to true.
    if (planetNames == true)
        DrawTextString(Moon->getName(), Moon->getRadius());
   
    //Create quadric object
    GLUquadric *quad;
    quad = gluNewQuadric();
    
    //Enable texture.
    gluQuadricTexture(quad, GL_TRUE);

    //Draw moon.
    gluSphere(quad, 0.1, Resolution, Resolution );
    gluDeleteQuadric( quad );
}



/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function: SetMoonMatProps
*
* Description:
*
*
*
* Parameters:
*
******************************************************************************/
void SetMoonMatProps(Planet *Moon)
{
    glColor3f( 1.0, 1.0, 1.0 );

    if ( textureToggle == false )
    {
        GLfloat mat_shininess = { 100.0 };
        GLfloat mat_emission[] = {0.0, 0.0, 0.0, 1.0};

        GLfloat color[] = {Moon->getR(), Moon->getG(), Moon->getB()};           //##SAVOY
        glColor3f(Moon->getR(), Moon->getG(), Moon->getB());

        glMaterialfv( GL_FRONT, GL_SPECULAR, color  );
        glMaterialfv( GL_FRONT, GL_AMBIENT, color );
        glMaterialfv( GL_FRONT, GL_DIFFUSE, color );
        glMaterialf( GL_FRONT, GL_SHININESS, mat_shininess );
        glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, mat_emission );
    }

    else
    {
        GLfloat mat_specular[] = { 0.8, 0.8, 0.0, 1.0 };
        GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
        GLfloat mat_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
        GLfloat mat_shininess = { 100.0 };
        GLfloat mat_emission[] = {0.0, 0.0, 0.0, 1.0};

        glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
        glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
        glMaterialf( GL_FRONT, GL_SHININESS, mat_shininess );
        glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, mat_emission );
    }

}



/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function: DrawOrbit
*
* Description:
*   This function draws the orbit path for the planet. It takes in the planet
*   distance to the surface and draws a circle centered at the sun.
*
* Parameters:
*   planetDistance      -distance of planet to the surface of the sun
******************************************************************************/
void DrawOrbit(double planetDistance)
{
    //Have opengl draw backs of objects.
    glDisable( GL_CULL_FACE );

    //If textures toggle is off disable textures.
    if ( textureToggle == true )
        glDisable( GL_TEXTURE_2D );

    //Set orbits light properties.
    SetOrbitMatProps();

    //Set color to blue.
    glColor3f( 0.0, 0.0, 1.0 );

    //Create quadric object
    GLUquadric *quad;
    quad = gluNewQuadric();

    //Enable texture
    gluQuadricTexture(quad, GL_TRUE);

    //draw orbit uti
    gluPartialDisk(quad,planetDistance, planetDistance+0.05,50,50,0,360);
    gluDeleteQuadric( quad );
    
    //Reenable textures if were disabled.
    if ( textureToggle == true )
        glEnable( GL_TEXTURE_2D );

    //Disable of drawing the back of objects
    glEnable( GL_CULL_FACE );
}



/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function: SetOrbitMatProps
*
* Description:
*
*
*
* Parameters:
*
******************************************************************************/
void SetOrbitMatProps()
{
    GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_diffuse[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_shininess = { 0.0 };
    GLfloat mat_emission[] = {0.0, 0.0, 1.0, 1.0};


    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
    glMaterialf( GL_FRONT, GL_SHININESS, mat_shininess );
    glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, mat_emission );               //##SAVOY
}



/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function: DrawPlanet
*
* Description:
*   This function will draw the planet. It sets the position of the planet by
*   a geometric rotation and then a geometric translation. It takes in a planet
*   object and uses that data for the drawing information.
*
* Parameters:
*   plant    -Planet object that contains all the information needed for drawing
*
******************************************************************************/
void DrawPlanet(Planet *plant)
{    
    float HoursPerDay = plant->getHoursPerDay();
    float DaysPerYear = plant->getDaysPerYear();
    float DayOfYear = plant->getDayOfYear();
    float HourOfDay = plant->getHourOfDay();
    float DayIncrement;
    float hourIncrement;
    int Radius = plant->getRadius();
    float Distance = plant->getDistance()*DistScale + 69600*SizeScale;

    //Recenter drawing location
    glLoadIdentity();
    
    //Rotate to the correct spot.
    HandleRotate();

    //Translate to the correct spot.
    glTranslatef ( Xpan, Ypan, Zpan );

    //if orbits are on then draw orbits
    if(paths == true)
        DrawOrbit(Distance);

    //if animation is on than increment the times of the planet
    if ( spinMode )
    {
        // Update the animation state
        DayIncrement = AnimateIncrement / 24.0;
        hourIncrement = AnimateIncrement -(int)DayIncrement * 24;

        //Increment the DayOfYear and HourOfDay
        DayOfYear += DayIncrement;
        HourOfDay += hourIncrement;
    
        //Save new times in planet object
        plant->setDayOfYear(DayOfYear);
        plant->setHourOfDay(HourOfDay);
    }

    //Get Day and Hour.
    DayOfYear = plant->getDayOfYear();
    HourOfDay = plant->getHourOfDay();


    //Draw the Planet
    
    /*First position it around the sun. Use DayOfYear and DaysPerYear
      calculate positions*/   
    glRotatef( 360.0 * DayOfYear / DaysPerYear, 0.0, 0.0, 1.0 );

    //Then position it away from the sun.
    glTranslatef( Distance, 0.0, 0.0 );
    
    // Save matrix state
    glPushMatrix();						
    
    /* Second, rotate the earth on its axis. Use HourOfDay and HoursPerDay
       to determine its rotation*/
    glRotatef( 360.0 * HourOfDay/HoursPerDay, 0.0, 0.0, 1.0 );
    
    //Draw names if names are on.
    if (planetNames == true)
        DrawTextString(plant->getName(), plant->getRadius());

    //Set planets light properties.
    SetPlanetMatProps(plant);

    //Get the image and the rows and columns of the image.
    int nrows = plant->getRows();
    int ncols = plant->getCols();
    byte* image = plant->getImage();
    
    //Set the texture of the planet.
    SetTexture(image, nrows, ncols);

    //Combine the texture and lighting propertites
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    //Create the quadric object.
    GLUquadric *quad;
    quad = gluNewQuadric();
    
    //Enable texturing on the object
    gluQuadricTexture(quad, GL_TRUE);

    //Draw the planet
    gluSphere(quad, Radius*SizeScale, Resolution, Resolution);

    //Delete the Quadric
    gluDeleteQuadric( quad );

    /*special cases for Saturn and Earth. If Earth draw moon. 
      If Saturn draw rings*/
    if(plant->getName() == "Earth")
    {
        DrawMoon(DayOfYear);
    }
    else if(plant->getName() == "Saturn")
    {
        DrawRings(Radius);
    }


    glPopMatrix();
    // Restore matrix state
}



/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function: SetPlanetMatProps
*
* Description:
*
*
*
* Parameters:
*
******************************************************************************/
void SetPlanetMatProps(Planet *plant)
{
    glColor3f( 1.0, 1.0, 1.0 );

    if ( textureToggle == false )
    {
        GLfloat mat_shininess = { 100.0 };
        GLfloat mat_emission[] = {0.0, 0.0, 0.0, 1.0};

        GLfloat color[] = {plant->getR(), plant->getG(), plant->getB()};        //##SAVOY
        glColor3f( plant->getR(), plant->getG(), plant->getB() );

        glMaterialfv( GL_FRONT, GL_SPECULAR, color  );
        glMaterialfv( GL_FRONT, GL_AMBIENT, color );
        glMaterialfv( GL_FRONT, GL_DIFFUSE, color );
        glMaterialf( GL_FRONT, GL_SHININESS, mat_shininess );
        glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, mat_emission );
    }

    else
    {
        GLfloat mat_specular[] = { 0.8, 0.8, 0.0, 1.0 };
        GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
        GLfloat mat_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
        GLfloat mat_shininess = { 100.0 };
        GLfloat mat_emission[] = {0.0, 0.0, 0.0, 1.0};

        glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
        glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
        glMaterialf( GL_FRONT, GL_SHININESS, mat_shininess );
        glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, mat_emission );
    }
}



/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function: DrawSun
*
* Description: 
*   This function draws the sun. It takes in the sun as a planet object.
*   This function also set the lighting and texture properties and sets
*   a point light source for the entire field
*
* Parameters:
*   sun     -Planet class that holds the drawing information for the sun
******************************************************************************/
void DrawSun(Planet *sun)
{    
    float radius = sun->getRadius();
    int nrows = sun->getRows();
    int ncols = sun->getCols();
    byte* image = sun->getImage();

    //Set the lighting model.
    SetLightModel();

    //Variable to keep track sun rotation.
    static float hours = 0.0;

    //If animation is on increment time.
    if ( spinMode )
    {
        hours += AnimateIncrement;
        hours = hours;
    }
    
    //Set suns lighting properties.
    SetSunMatProp(sun);

    //Set the suns textures.
    SetTexture(image, nrows, ncols);
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    // Clear the current matrix (Modelview)
    glLoadIdentity();

    //Handle rotation by users view.
    HandleRotate();
    
    //Handle translation from user view.
    glTranslatef ( Xpan, Ypan, Zpan );



    //Calculate rotation.
    glRotatef(360.0 * hours/25.0, 0.0, 0.0, 1.0 );

    //Make quadric object.
    GLUquadric *quad;
    quad = gluNewQuadric();
    
    //Enable object textures.
    gluQuadricTexture(quad, GL_TRUE);

    //Draw the sun.
    gluSphere(quad, radius, Resolution, Resolution );
    gluDeleteQuadric( quad );

}



/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function: SetSunLMatProp
*
* Description:
*
*
*
* Parameters:
*
******************************************************************************/
void SetSunMatProp(Planet *sun)
{
    glColor3f( 1.0, 1.0, 1.0 );

    if ( textureToggle == false )
    {
        GLfloat mat_shininess = { 100.0 };
        GLfloat mat_emission[] = {1.0, 1.0, 0.0, 1.0};

        GLfloat color[] = {sun->getR(), sun->getG(), sun->getB()};              //##SAVOY
        glColor3f( sun->getR(), sun->getG(), sun->getB() );

        glMaterialfv( GL_FRONT, GL_SPECULAR, color  );
        glMaterialfv( GL_FRONT, GL_AMBIENT, color );
        glMaterialfv( GL_FRONT, GL_DIFFUSE, color );
        glMaterialf( GL_FRONT, GL_SHININESS, mat_shininess );
        glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, mat_emission );
    }

    else
    {
        GLfloat mat_specular[] = { 0.0, 1.0, 0.0, 1.0 };
        GLfloat mat_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
        GLfloat mat_ambient[] = { 0.5, 1.0, 0.0, 1.0 };
        GLfloat mat_shininess = { 100.0 };
        GLfloat mat_emission[] = {1.0, 1.0, 0.0, 1.0};

        glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
        glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
        glMaterialf( GL_FRONT, GL_SHININESS, mat_shininess );
        glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, mat_emission );
    }
}







/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function: DrawSpace
*
* Description:
*   This function draws the stars in the background by drawing a sphere
*   around the entire solar system and texture maping stars to that.
*
* Parameters:
*   space       -space as a Planet object with drawing details
*
******************************************************************************/
void DrawSpace(Planet *space)
{
    //Draw back side of objects.
    glDisable( GL_CULL_FACE );

    //Set abient and emmison values of the space.
    GLfloat mat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_emission[] = {0.0, 0.0, 0.0, 1.0};

    //Set ambient and emmision of the space
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
    glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, mat_emission );
    
    //save the matrix
    glPushMatrix();
    glColor3f( 0.0, 0.0, 0.0 );

    //get image and rows and cols
    int nrows = space->getRows();
    int ncols = space->getCols();
    byte* image = space->getImage();

    //set texture
    SetTexture(image, nrows, ncols);

    //combine and light and texture properties
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );


    // Clear the current matrix (Modelview)
    glLoadIdentity();
    HandleRotate();
    // Back off eight units to be able to view from the origin.
    glTranslatef ( Xpan, Ypan, Zpan );



    // Draw the sun	-- as a yellow, wireframe sphere
    glColor3f( 0.0, 0.0, 0.0 );

    //make quadric object.
    GLUquadric *quad;
    quad = gluNewQuadric();
    
    //Enable texture
    gluQuadricTexture(quad, GL_TRUE);

    //Draw Sphere
    gluSphere(quad, 300.0, 100, 100 );
    gluDeleteQuadric( quad );

    //Disable drawing background
    glEnable( GL_CULL_FACE );
}



/******************************************************************************
* Author: Daniel Hodgin and Savoy Schuler
*
* Function: SetTexture
*
* Description:
*
*
*
* Parameters:
*
******************************************************************************/
// read texture map from BMP file
// Ref: Buss, 3D Computer Graphics, 2003.
int SetTexture( byte* image, int nrows, int ncols )
{
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );             //##SAVOY
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, ncols, nrows, GL_RGB, GL_UNSIGNED_BYTE, image );

    return 0;
}



/******************************************************************************
* Author:Dr. Weiss, Daniel Hodgin and Savoy Schuler
*
* Function: DrawTextString
*
* Description:
*   This draws a string in the glut window based on x and y components.
*   This function was taken from an example from Dr. Weiss and modified
*   to fit our needs
*
*
* Parameters:
*   str         -text that needs to be displayed
*   radius      -radius of the planet
*
******************************************************************************/
void DrawTextString( string str, double radius)
{
    //Disable the textures if they are off.
    if ( textureToggle == true )
        glDisable( GL_TEXTURE_2D );

    //Set emission value.
    GLfloat mat_emission[] = {1.0, 1.0, 1.0, 1.0};

    //Enable emission.
    glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, mat_emission );

    //Set the text color
    GLfloat textColor[] = { 1.0, 1.0, 1.0 };
    glColor3fv( textColor );

    //Special case for moon. Draw it below earth. everything else above the planet
    if(str == "Moon")
        glRasterPos3i( 0,0, radius * SizeScale - 1 );
    else
        glRasterPos3i( 0,0, radius * SizeScale + 1 );

    //draw the text
    for (int i = 0; i < str.length(); i++)
    {
        glutBitmapCharacter( GLUT_BITMAP_9_BY_15, str[i] );
    }

    //renable texture if turned off
    if ( textureToggle == true )
        glEnable( GL_TEXTURE_2D );

}
