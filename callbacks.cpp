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
float Xrot = -15.0;
float Yrot = 0.0;
float Zrot = 0.0;



// glutKeyboardFunc is called to set this function to handle normal key presses.
void KeyPressFunc( unsigned char Key, int x, int y )
{
	static bool light = true, shade = false, wire = false, texture = true;

    switch ( Key )
    {
		case 'l':
		    ( light = !light ) ? glEnable( GL_LIGHTING ) : glDisable( GL_LIGHTING );
			break;
		
        case 'R':
        case 'r':
            Key_r();
            break;
        case 't': 
        	 ( texture = !texture ) ? glEnable( GL_TEXTURE_2D ) : glDisable( GL_TEXTURE_2D );
        	break;
        case 'T': 
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
    static Planet *Sun;

    if(firstTime == true)
    {
    	int nrows, ncols;
    	byte* image;
		char * filename;
		
		filename = stringToChar("mercury.bmp");
    	LoadBmpFile( filename, nrows, ncols, image );
        Mercury = new Planet("Mercury",1416,88,   2439, 58, nrows, ncols, image);
        
        
		filename = stringToChar("venus.bmp");
    	LoadBmpFile( filename, nrows, ncols, image );
        Venus = new Planet("Venus",    5832,225,  6052, 108, nrows, ncols, image);

		filename = stringToChar("earth.bmp");
    	LoadBmpFile( filename, nrows, ncols, image );
        Earth = new Planet("Earth",    24,  365,  6378, 150, nrows, ncols, image);

		filename = stringToChar("mars.bmp");
    	LoadBmpFile( filename, nrows, ncols, image );
        Mars = new Planet("Mars",      24.6,687,  3394, 228, nrows, ncols, image);


		filename = stringToChar("jupiter.bmp");
    	LoadBmpFile( filename, nrows, ncols, image );
        Jupiter = new Planet("Jupiter",9.8, 4332, 71398,779, nrows, ncols, image);


		filename = stringToChar("saturn.bmp");
    	LoadBmpFile( filename, nrows, ncols, image );
        Saturn = new Planet("Saturn",  10.2,10761,60270,1424, nrows, ncols, image);


		filename = stringToChar("uranus.bmp");
    	LoadBmpFile( filename, nrows, ncols, image );
        Uranus = new Planet("Uranus",  15.5,30682,25550,2867, nrows, ncols, image);

		filename = stringToChar("neptune.bmp");
    	LoadBmpFile( filename, nrows, ncols, image );
        Neptune = new Planet("Neptune",15.8,60195,24750,4492, nrows, ncols, image);
        
        
        filename = stringToChar("sun.bmp");
    	LoadBmpFile( filename, nrows, ncols, image );
        Sun = new Planet("Sun", 25, 0, 0, 0, nrows, ncols, image);
        
        firstTime = false;
    }
    // Clear the redering window
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


    DrawSun(Sun);
    DrawPlanet(Mercury);
    DrawPlanet(Venus);
    DrawPlanet(Earth);
    DrawPlanet(Mars);
    DrawPlanet(Jupiter);
    DrawPlanet(Saturn);
    DrawPlanet(Uranus);
    DrawPlanet(Neptune);
    glLoadIdentity();  
    glTranslatef ( Xpan, Ypan, Zpan );
	HandleRotate();

    glColor3f( 0.3, 0.7, 0.3 );
    GLUquadric *quad = gluNewQuadric();
    gluCylinder(quad,0.5,0.5,0.5,0.5,0.5);


    // Flush the pipeline, and swap the buffers
    glFlush();
    glutSwapBuffers();

    if ( singleStep )
    {
        spinMode = GL_FALSE;
    }

    glutPostRedisplay();		// Request a re-draw for animation purposes
}



// Initialize OpenGL's rendering modes
void OpenGLInit( void )
{
    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glClearDepth( 1.0 );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_TEXTURE_2D );
    glEnable( GL_LIGHTING );

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








