/*
* orbit.cpp
*
* Program to demonstrate how to use a local
* coordinate method to position parts of a
* model in relation to other model parts.
*
* Draws a simple solar system, with a sun, planet and moon.
* Based on sample code from the OpenGL programming guide
* by Woo, Neider, Davis.  Addison-Wesley.
*
* Author: Samuel R. Buss
*
* Software accompanying the book
* 3D Computer Graphics: A Mathematical Introduction with OpenGL,
* by S. Buss, Cambridge University Press, 2003.
*
* Software is "as-is" and carries no warranty.  It may be used without
* restriction, but if you modify it, please change the filenames to
* prevent confusion between different versions.
*
* Bug reports: Sam Buss, sbuss@ucsd.edu.
* Web page: http://math.ucsd.edu/~sbuss/MathCG
*
* USAGE:
*    Press "r" key to toggle (off and on) running the animation
*    Press "s" key to single-step animation
*    The up and down array keys control the time step used in the animation rate.
*    Each key press multiplies or divides the times by a factor of two.
*    Press ESCAPE to exit.
*/

// JMW: Minor modifications for CSC433/533 Computer Graphics, Fall 2016.

#include <cstdlib>
#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include "Planet.h"
#include "globals.h"

using namespace std;


void DrawPlanet(Planet *planet);

// global variables
GLenum spinMode = GL_TRUE;
GLenum singleStep = GL_TRUE;

float HourOfDay = 0.0;
float DayOfYear = 0.0;
float MercuryHour = 0.0;
float MercuryDay = 0.0;
float AnimateIncrement = 24.0;  // Time step for animation (hours)
float Xpan = 0.0;
float Ypan = 0.0;
float Zpan = -20.0;
float Xrot = 1.0;
float Yrot = 0.0;
float Zrot = 0.0;

// glutKeyboardFunc is called to set this function to handle normal key presses.
void KeyPressFunc( unsigned char Key, int x, int y )
{
	static bool light = true, shade = false, wire = true;

    switch ( Key )
    {
		case 'l':
		    ( light = !light ) ? glEnable( GL_LIGHTING ) : glDisable( GL_LIGHTING );
			break;
		
        case 'R':
        case 'r':
            Key_r();
            break;
        case 't': glDisable( GL_LIGHTING ); glEnable( GL_TEXTURE_2D );  break;
        case 'T': glEnable( GL_LIGHTING );  glEnable( GL_TEXTURE_2D );  break;
        case 's':
        case 'S':
            Key_s();
            break;
	    case 'q':
		    ( shade = !shade ) ? glShadeModel( GL_FLAT ) : glShadeModel( GL_SMOOTH );
			break;

		case 'w':
		    ( wire = !wire ) ? glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ) : glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			break;
        case '1':
            Xrot = Xrot + 1;
            break;
        case '2':
            Xrot = Xrot - 1;
            break;
        case 'a':
            Key_up();
            break;
        case 'A':
            Key_down();
            break;
        case 'x':
            Xpan = Xpan - 0.1;
            break;
        case 'X':
            Xpan = Xpan + 0.1;
            break;
        case 'y':
            Ypan = Ypan - 0.1;
            break;
        case 'Y':
            Ypan = Ypan + 0.1;
            break;
        case 'z':
            Zpan = Zpan - 0.5;
            break;
        case 'Z':
            Zpan = Zpan + 0.5;
            break;
        case 27: 	// Escape key
            exit( 1 );
    }
}

// glutSpecialFunc is called to set this function to handle all special key presses
// See glut.h for the names of special keys.
void SpecialKeyFunc( int Key, int x, int y )
{
    switch ( Key )
    {
        case GLUT_KEY_UP:
            Zrot = Zrot + 1;
            break;
        case GLUT_KEY_DOWN:
            Zrot = Zrot - 1;
            break;
        case GLUT_KEY_LEFT:
            Yrot = Yrot - 1;
            break;
        case GLUT_KEY_RIGHT:
            Yrot = Yrot + 1;
            break;
    }
}

void HandleRotate()
{
        glRotatef( Xrot, 1.0, 0.0, 0.0);
        glRotatef( Yrot, 0.0, 1.0, 0.0);
        glRotatef( Zrot, 0.0, 0.0, 1.0);
}
// restart animation
void Key_r( void )
{
    if ( singleStep )
    {			// If ending single step mode
        singleStep = GL_FALSE;
        spinMode = GL_TRUE;		// Restart animation
    }
    else
    {
        spinMode = !spinMode;	// Toggle animation on and off.
    }
}

// single step animation
void Key_s( void )
{
    singleStep = GL_TRUE;
    spinMode = GL_TRUE;
}

// animation speed
void Key_up( void )
{
    AnimateIncrement *= 2.0;			// Double the animation time step
}

// animation speed
void Key_down( void )
{
    AnimateIncrement /= 2.0;			// Halve the animation time step
}

// Animate() handles the animation and the redrawing of the graphics window contents.
void Animate( void )
{
    static bool firstTime = true;
    static Planet *Mercury;
    static Planet *Venus;
    static Planet *Earth;
    static Planet *Mars;
    static Planet *Jupiter;
    static Planet *Saturn;
    static Planet *Uranus;
    static Planet *Neptune;

    if(firstTime == true)
    {
        Mercury = new Planet("Mercury",1416,88,   2439, 58, "mercury.bmp");
        Venus = new Planet("Venus",    5832,225,  6052, 108, "venus.bmp");
        Earth = new Planet("Earth",    24,  365,  6378, 150, "earth.bmp");
        Mars = new Planet("Mars",      24.6,687,  3394, 228, "mars.bmp");
        Jupiter = new Planet("Jupiter",9.8, 4332, 71398,779, "jupiter.bmp");
        Saturn = new Planet("Saturn",  10.2,10761,60270,1424, "saturn.bmp");
        Uranus = new Planet("Uranus",  15.5,30682,25550,2867, "uranus.bmp");
        Neptune = new Planet("Neptune",15.8,60195,24750,4492, "neptune.bmp");
        firstTime = false;
    }
    // Clear the redering window
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


    DrawSun();
    DrawPlanet(Mercury);
    DrawPlanet(Venus);
    DrawPlanet(Earth);
    DrawPlanet(Mars);
    DrawPlanet(Jupiter);
    DrawPlanet(Saturn);
    DrawPlanet(Uranus);
    DrawPlanet(Neptune);


    /* Draw the moon. Use DayOfYear to control its rotation around the earth
    glRotatef( 360.0 * 12.0 * DayOfYear / 365.0, 0.0, 1.0, 0.0 );
    glTranslatef( 0.7, 0.0, 0.0 );
    glColor3f( 0.3, 0.7, 0.3 );
    glutWireSphere( 0.1, 5, 5 );*/

    // Flush the pipeline, and swap the buffers
    glFlush();
    glutSwapBuffers();

    if ( singleStep )
    {
        spinMode = GL_FALSE;
    }

    glutPostRedisplay();		// Request a re-draw for animation purposes
}

void DrawPlanet(Planet *plant)
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 0.0, 0.8, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.3, 0.3, 0., 1.0 };
    GLfloat mat_shininess = { 100.0 };
   	GLfloat mat_emission[] = {0.0, 0.0, 0.0, 1.0};

    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
    glMaterialf( GL_FRONT, GL_SHININESS, mat_shininess );
	glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, mat_emission );

    float HourOfDay = plant->getHourOfDay();
    float DayOfYear = plant->getDayOfYear();
    float HoursPerDay = plant->getHoursPerDay();
    float DaysPerYear = plant->getDaysPerYear();
    int Radius = plant->getRadius();
    int Distance = plant->getDistance();
	string Texture = plant->getTexture();

	char * filename = new char[Texture.size() + 1];
	std::copy(Texture.begin(), Texture.end(), filename);
	filename[Texture.size()] = '\0'; // don't forget the terminating 0
	initTextureMap( filename );
	delete[] filename;

    if ( spinMode )
    {
        // Update the animation state
        HourOfDay += AnimateIncrement;
        DayOfYear += AnimateIncrement / 24.0;

        HourOfDay = HourOfDay - ( ( int ) ( HourOfDay / HoursPerDay ) ) * HoursPerDay;
        DayOfYear = DayOfYear - ( ( int ) ( DayOfYear / DaysPerYear ) ) * DaysPerYear;  

        plant->setHourOfDay(HourOfDay);
        plant->setDayOfYear(DayOfYear);
    }


    glLoadIdentity();
    glTranslatef ( Xpan, Ypan, Zpan );
    HandleRotate();
    glRotatef( 15.0, 1.0, 0.0, 0.0);

    // Draw the Mecury
    // First position it around the sun. Use MecuryYear to determine its position.
    glRotatef( 360.0 * DayOfYear / DaysPerYear, 0.0, 1.0, 0.0 );
    glTranslatef( Distance*DistScale, 0.0, 0.0 );
    glPushMatrix();						// Save matrix state
    // Second, rotate the earth on its axis. Use MecuryHour to determine its rotation.
    glRotatef( DaysPerYear * HourOfDay / HoursPerDay, 0.0, 1.0, 0.0 );
    // Third, draw the earth as a wireframe sphere.
    glColor3f( 0.2, 0.7, 0.2 );
    
    
    
    GLUquadric *quad;
	quad = gluNewQuadric();
	gluQuadricTexture(quad,1);
	gluSphere(quad, Radius*SizeScale, 100, 100);
    
    


    glPopMatrix();	
					// Restore matrix state
	
}

void DrawSun()
{
	string Texture = "sun.bmp";

	char * filename = new char[Texture.size() + 1];
	std::copy(Texture.begin(), Texture.end(), filename);
	filename[Texture.size()] = '\0'; // don't forget the terminating 0
	initTextureMap( filename );
	delete[] filename;


    static float hours = 0.0;
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
	
	// Clear the current matrix (Modelview)
    glLoadIdentity();
    // Back off eight units to be able to view from the origin.
    glTranslatef ( Xpan, Ypan, Zpan );
    HandleRotate();
    // Rotate the plane of the elliptic
    // (rotate the model's plane about the x axis by fifteen degrees)
    glRotatef( 15.0, 1.0, 0.0, 0.0);
    
    //calculate rotation.
	glRotatef( hours / 25.0, 0.0, 1.0, 0.0 );
    // Draw the sun	-- as a yellow, wireframe sphere
    glColor3f( 1.0, 1.0, 0.0 );
   
   //glutSolidSphere



	GLUquadric *quad;
	quad = gluNewQuadric();
	gluSphere(quad, 1.0, 15, 15 );
	
}



// set up light and material properties
void SetLightModel()
{
	glLoadIdentity();
    glTranslatef ( Xpan, Ypan, Zpan );
    HandleRotate();
    glRotatef( 15.0, 1.0, 0.0, 0.0);


    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };

    glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular );

    glShadeModel( GL_SMOOTH );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    glEnable( GL_DEPTH_TEST );
    glColor3f ( 0.5, 0.5, 0.5 );
    glEnable( GL_NORMALIZE );    // automatic normalization of normals
    glEnable( GL_CULL_FACE );    // eliminate backfacing polygons
    glCullFace( GL_BACK );
}





// Initialize OpenGL's rendering modes
void OpenGLInit( void )
{
    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glClearDepth( 1.0 );
    glEnable( GL_DEPTH_TEST );
}

// ResizeWindow is called when the window is resized
void ResizeWindow( int w, int h )
{
    float aspectRatio;
    h = ( h == 0 ) ? 1 : h;
    w = ( w == 0 ) ? 1 : w;
    glViewport( 0, 0, w, h );	// View port uses whole window
    aspectRatio = ( float ) w / ( float ) h;
   
    // Set up the projection view matrix (not very well!)
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    gluPerspective( 60.0, aspectRatio, 1.0, 300.0 );
    
    gluLookAt (0,0,2,0,0,0,0,1,0);

    // Select the Modelview matrix
    glMatrixMode( GL_MODELVIEW );
}






// read texture map from BMP file
// Ref: Buss, 3D Computer Graphics, 2003.
int loadTextureFromFile( char *filename )
{
    int nrows, ncols;
    byte* image;
    if ( !LoadBmpFile( filename, nrows, ncols, image ) )
    {
        std::cerr << "Error: unable to load " << filename << std::endl;
        return -1;
    }

    // Pixel alignment: each row is word aligned (aligned to a 4 byte boundary)
    // Therefore, no need to call glPixelStore( GL_UNPACK_ALIGNMENT, ... );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, ncols, nrows, GL_RGB, GL_UNSIGNED_BYTE, image );
    
    delete [] image;

    return 0;
}

// set up texture map
void initTextureMap( char *filename )
{
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_TEXTURE_2D );
    if ( loadTextureFromFile( filename ) == 0 )
        glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
}
