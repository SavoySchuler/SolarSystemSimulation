#include <cstdlib>
#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include "Planet.h"
#include "globals.h"


void HandleRotate()
{
        glRotatef( Xrot, 1.0, 0.0, 0.0);
        glRotatef( Yrot, 0.0, 1.0, 0.0);
        glRotatef( Zrot, 0.0, 0.0, 1.0);
}

char * stringToChar (string str)
{
    	char * filename = new char[str.size() + 1];
		std::copy(str.begin(), str.end(), filename);
		filename[str.size()] = '\0'; // don't forget the terminating 0
		return filename;
}

void DrawRings(double planetRadius)
{
	glDisable( GL_CULL_FACE );
	static bool firstTimeSaturn = true;
	static Planet *Rings;
	int nrows, ncols;
	byte* image;
	
	
	if ( firstTimeSaturn = true);
	{
		char * filename;
	    filename = stringToChar("saturnrings.bmp");
    	LoadBmpFile( filename, nrows, ncols, image );
        Rings = new Planet("Saturn Rings", 0, 0, 0, 0, nrows, ncols, image);
		firstTimeSaturn = false;
	}
	

	nrows = Rings->getRows();
	ncols = Rings->getCols();
	image = Rings->getImage();


	setTexture(image, nrows, ncols);
	glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );	


	 
    glColor3f( 1.0, 1.0, 1.0 );
	GLUquadric *quad;
	quad = gluNewQuadric();
    
	gluQuadricTexture(quad, GL_TRUE);
	gluCylinder(quad, planetRadius * SizeScale, planetRadius * SizeScale + 0.5 ,0, 100, 100);
	gluDeleteQuadric( quad );
	glEnable( GL_CULL_FACE ); 
}

void DrawMoon(int DayOfYear)
{
	static bool firstTimeMoon = true;
	static Planet *Moon;
	int nrows, ncols;
	byte* image;
	
	
	if ( firstTimeMoon = true);
	{
		char * filename;
	    filename = stringToChar("moon.bmp");
    	LoadBmpFile( filename, nrows, ncols, image );
        Moon = new Planet("Moon", 0, 0, 0, 0, nrows, ncols, image);
		firstTimeMoon = false;
	}
	

	nrows = Moon->getRows();
	ncols = Moon->getCols();
	image = Moon->getImage();


	setTexture(image, nrows, ncols);
	glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );	


    //Draw the moon. Use DayOfYear to control its rotation around the earth
    glRotatef( 360.0 * 12.0 * DayOfYear / 365.0, 0.0, 0.0, 1.0 );
    glTranslatef( 0.7, 0.0, 0.0 );
    glColor3f( 1.0, 1.0, 1.0 );
    
    GLUquadric *quad;
	quad = gluNewQuadric();
	gluQuadricTexture(quad, GL_TRUE);
	gluSphere(quad, 0.1, 5, 5 );
	gluDeleteQuadric( quad );
    
}

void DrawOrbit(double planetDistance)
{
	glDisable( GL_CULL_FACE ); 
   	GLfloat mat_emission[] = {1.0, 1.0, 1.0, 1.0};

	glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, mat_emission );

    glColor3f( 1.0, 1.0, 1.0 );
	GLUquadric *quad;
	quad = gluNewQuadric();
    
	gluQuadricTexture(quad, GL_TRUE);
    gluPartialDisk(quad,planetDistance*DistScale, planetDistance*DistScale+0.05,100,100,0,360);
	gluDeleteQuadric( quad );
	glEnable( GL_CULL_FACE ); 
}

void DrawPlanet(Planet *plant)
{    
	glLoadIdentity();
    glTranslatef ( Xpan, Ypan, Zpan );
	HandleRotate();
    DrawOrbit(plant->getDistance());


    float HoursPerDay = plant->getHoursPerDay();
    float DaysPerYear = plant->getDaysPerYear();
	float DayOfYear = plant->getDayOfYear();
	float HourOfDay = plant->getHourOfDay();
	float DayIncrement;
	float hourIncrement;
    int Radius = plant->getRadius();
    int Distance = plant->getDistance();
	int nrows = plant->getRows();
	int ncols = plant->getCols();
	byte* image = plant->getImage();


	setTexture(image, nrows, ncols);
	glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    if ( spinMode )
    {
        // Update the animation state
        DayIncrement = AnimateIncrement / 24.0;
		hourIncrement = AnimateIncrement -(int)DayIncrement * 24;
		
		DayOfYear += DayIncrement;
		HourOfDay += hourIncrement;

		plant->setDayOfYear(DayOfYear);
		plant->setHourOfDay(HourOfDay);
    }
	
	DayOfYear = plant->getDayOfYear();
	HourOfDay = plant->getHourOfDay();


    // Draw the Mecury
    // First position it around the sun. Use MecuryYear to determine its position.
    glRotatef( 360.0 * DayOfYear / DaysPerYear, 0.0, 0.0, 1.0 );
    glTranslatef( Distance*DistScale, 0.0, 0.0 );
    glPushMatrix();						// Save matrix state
    // Second, rotate the earth on its axis. Use MecuryHour to determine its rotation.
    glRotatef( 360.0 * HourOfDay/HoursPerDay, 0.0, 0.0, 1.0 );
    // Third, draw the earth as a wireframe sphere.
    glColor3f( 0.8, 0.8, 0.0 );
    
    DrawTextString(plant->getName(), plant->getRadius());

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
    
    
    GLUquadric *quad;
	quad = gluNewQuadric();
//	gluQuadricDrawStyle( quad, GLU_FILL );
//	gluQuadricOrientation( quad, GLU_OUTSIDE );
	gluQuadricTexture(quad, GL_TRUE);
	
	gluSphere(quad, Radius*SizeScale, 100, 100);
    gluDeleteQuadric( quad );
    
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

void DrawSun(Planet *sun)
{
	SetLightModel();
    static float hours = 0.0;
    if ( spinMode )
        hours += AnimateIncrement;
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
	glPushMatrix();
	
	
	int nrows = sun->getRows();
	int ncols = sun->getCols();
	byte* image = sun->getImage();


	setTexture(image, nrows, ncols);
	glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	
	
	// Clear the current matrix (Modelview)
    glLoadIdentity();
    // Back off eight units to be able to view from the origin.
    glTranslatef ( Xpan, Ypan, Zpan );
    HandleRotate();
    // Rotate the plane of the elliptic
    // (rotate the model's plane about the x axis by fifteen degrees)

    //calculate rotation.
	glRotatef(360.0 * hours/25.0, 0.0, 0.0, 1.0 );
    // Draw the sun	-- as a yellow, wireframe sphere
    glColor3f( 1.0, 1.0, 1.0 );
   
   //glutSolidSphere



	GLUquadric *quad;
	quad = gluNewQuadric();
	gluQuadricTexture(quad, GL_TRUE);
	gluSphere(quad, 1.0, 15, 15 );
	gluDeleteQuadric( quad );
	
}



// set up light and material properties
void SetLightModel()
{
	glLoadIdentity();    
	
    glTranslatef ( Xpan, Ypan, Zpan );
    HandleRotate();

    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };

    glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular );
    
    glEnable( GL_LIGHT0 );

   // glEnable( GL_DEPTH_TEST );
    glColor3f ( 0.5, 0.5, 0.5 );
    glEnable( GL_NORMALIZE );    // automatic normalization of normals
    glEnable( GL_CULL_FACE );    // eliminate backfacing polygons
    glCullFace( GL_BACK );
}



void DrawSpace(Planet *space)
{
	glDisable( GL_CULL_FACE );  


    GLfloat mat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_emission[] = {0.0, 0.0, 0.0, 1.0};
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
    glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, mat_emission );
	glPushMatrix();
	glColor3f( 0.0, 0.0, 0.0 );
	
	int nrows = space->getRows();
	int ncols = space->getCols();
	byte* image = space->getImage();


    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, ncols, nrows, GL_RGB, GL_UNSIGNED_BYTE, image );
	glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
	
	
	// Clear the current matrix (Modelview)
    glLoadIdentity();
    // Back off eight units to be able to view from the origin.
    glTranslatef ( Xpan, Ypan, Zpan );
    HandleRotate();


    // Draw the sun	-- as a yellow, wireframe sphere
    glColor3f( 0.0, 0.0, 0.0 );
   
   //glutSolidSphere


	GLUquadric *quad;
	quad = gluNewQuadric();
	gluQuadricTexture(quad, GL_TRUE);
	gluSphere(quad, 300.0, 50, 50 );
	gluDeleteQuadric( quad );
	glEnable( GL_CULL_FACE );  
}


// read texture map from BMP file
// Ref: Buss, 3D Computer Graphics, 2003.
int setTexture( byte* image, int nrows, int ncols )
{
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, ncols, nrows, GL_RGB, GL_UNSIGNED_BYTE, image );
   
    return 0;
}




void DrawTextString( string str, double radius)
{
   	GLfloat mat_emission[] = {1.0, 1.0, 1.0, 1.0};
	glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, mat_emission );
    GLfloat textColor[] = { 1.0, 1.0, 1.0 };
    glColor3fv( textColor );
    glRasterPos3i( 0,0, radius * SizeScale + 1 );

    for (int i = 0; i < str.length(); i++)
    {
        glutBitmapCharacter( GLUT_BITMAP_9_BY_15, str[i] );
    }
}
