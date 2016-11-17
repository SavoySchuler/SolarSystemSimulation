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
*    Press ESCAPE to exit.r
*/

// JMW: Minor modifications for CSC433/533 Computer Graphics, Fall 2016.

#include <cstdlib>
#include <cmath>
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
float AnimateIncrement = 0.5;  // Time step for animation (hours)
float Xpan = 1.6;
float Ypan = 9.0;
float Zpan = -5.0;
float Xrot = -69.0;
float Yrot = 0.0;
float Zrot = 64.0;
bool textureToggle = true;
int Resolution = 100;

Planet *Mercury;
Planet *Venus;
Planet *Earth;
Planet *Mars;
Planet *Jupiter;
Planet *Saturn;
Planet *Uranus;
Planet *Neptune;
Planet *Sun;
Planet *Space;

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
    
    gluPerspective( 60.0, aspectRatio, 1.0, 600.0 );
    
    gluLookAt (0,0,2,0,0,0,0,1,0);

    // Select the Modelview matrix
    glMatrixMode( GL_MODELVIEW );
}


// Animate() handles the animation and the redrawing of the graphics window contents.
void Animate( void )
{
    static bool firstTime = true;


    if(firstTime == true)
    {
    	setCelestialBodies();
        
        firstTime = false;
    }
    // Clear the redering window
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	DrawSpace(Space);
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



void setCelestialBodies()
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
    Jupiter = new Planet("Jupiter",9.8, 4332, 71398/2.0,779, nrows, ncols, image);


	filename = stringToChar("saturn.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Saturn = new Planet("Saturn",  10.2,10761,60270/2.0,1424, nrows, ncols, image);


	filename = stringToChar("uranus.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Uranus = new Planet("Uranus",  15.5,30682,25550,2867, nrows, ncols, image);

	filename = stringToChar("neptune.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Neptune = new Planet("Neptune",15.8,60195.0,24750,4492, nrows, ncols, image);
        
        
    filename = stringToChar("sun.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Sun = new Planet("Sun", 25, 0, 696000.0/10.0 * SizeScale, 0, nrows, ncols, image);
        
        
    filename = stringToChar("space.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Space = new Planet("Space", 0, 0, 100, 0, nrows, ncols, image);
}



// glutKeyboardFunc is called to set this function to handle normal key presses.
void KeyPressFunc( unsigned char Key, int x, int y )
{
	static bool light = true, shade = true, wire = false;

    switch ( Key )
    {
    	case '1':
            speedUp();
            break;
        case '2':
            speedDown();
            break;
		case '3':
		    ( shade = !shade ) ? glShadeModel( GL_FLAT ) : glShadeModel( GL_SMOOTH );
			break;
		case '4':
		    ( wire = !wire ) ? glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ) : glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
			break;
		case '5': 
        	if (textureToggle == false)
			{
				glEnable( GL_TEXTURE_2D );
        		textureToggle = true;
        	}
        	else 
        	{
				glDisable( GL_TEXTURE_2D );
        		textureToggle = false;
        	}
        	break;
		case '6':
		    ( light = !light ) ? glEnable( GL_LIGHTING ) : glDisable( GL_LIGHTING );
			break;
        case '+':
        	if (Resolution <= 195)
        		Resolution += 5;
            break;
        case '-':
        	if (Resolution >= 10)
            	Resolution -= 5;
        case 'r':
            startStopAnimation();
            break;
        case 'f':
            stepAnimation();  
            break;
		case 'w':
        	moveBackward();
            break;
        case 's':
        	moveForward();
            break;
        case 'a':
            moveLeft();
            break;
        case 'd':
        	moveRight();
            break;
        case 'q':
        	if (Zpan > -290.0)
            	Zpan = Zpan - 0.5;
            break;
        case 'e':
        	if (Zpan < 290.0)
           		Zpan = Zpan + 0.5;
	    	break;
        case 27: 	// Escape key
            exit( 1 );
    }
}

void moveForward()
{
    cerr << Zrot << endl;
    Ypan = Ypan + 0.1 * cos(Zrot * PI / 180);
    Xpan = Xpan + 0.1 * sin(Zrot * PI / 180);
}

void moveBackward()
{
    Ypan = Ypan - 0.1 * cos(Zrot * PI / 180);
    Xpan = Xpan - 0.1 * sin(Zrot * PI / 180);
}

void moveLeft()
{
    float rotation = Zrot + 90;
    Ypan = Ypan + 0.1 * cos(rotation * PI / 180);
    Xpan = Xpan + 0.1 * sin(rotation * PI / 180);
}

void moveRight()
{
    float rotation = Zrot - 90;
    Ypan = Ypan + 0.1 * cos(rotation * PI / 180);
    Xpan = Xpan + 0.1 * sin(rotation * PI / 180);
}

// animation speed
void speedUp( void )
{
    AnimateIncrement *= 2.0;			// Double the animation time step
}

// animation speed
void speedDown( void )
{
    AnimateIncrement /= 2.0;			// Halve the animation time step
}


// restart animation
void startStopAnimation( void )
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
void stepAnimation( void )
{
    singleStep = GL_TRUE;
    spinMode = GL_TRUE;
}

// glutSpecialFunc is called to set this function to handle all special key presses
// See glut.h for the names of special keys.
void SpecialKeyFunc( int Key, int x, int y )
{
    switch ( Key )
    {
        case GLUT_KEY_UP:
            Xrot = Xrot - 1;
	        if(Xrot < -180)
		        Xrot = -180;
            break;
        case GLUT_KEY_DOWN:
            Xrot = Xrot + 1;
	        if(Xrot > 0)
		        Xrot = 0;
            break;
        case GLUT_KEY_LEFT:
        	Zrot = Zrot - 1;
            break;
        case GLUT_KEY_RIGHT:
        	Zrot = Zrot + 1;
            break;
    }
}



void CreateMenus()
{
    //create main menu
    int value = 1;
    int mainmenu = glutCreateMenu( 0 );
    
	glutAddMenuEntry(	"Controls:", value++ );
	glutAddMenuEntry(	"r              - Start/Suspend Animation", value++ );
	glutAddMenuEntry(	"Up Arrow       -  Rotate Up", value++ );
	glutAddMenuEntry(	"Down Arrow  - Rotate Down", value++ );
	glutAddMenuEntry(	"Left Arrow     - Rotate Left", value++ );
	glutAddMenuEntry(	"Right Arrow   - Rotate Right", value++ );
	glutAddMenuEntry(	"a/d           - Pan in X direction", value++ );
	glutAddMenuEntry(	"w/s          - Pan in Y direction", value++ );
	glutAddMenuEntry(	"q/e           - Zoom (Pan in Z direction)", value++ );
	glutAddMenuEntry(	"1/2          - Speed of Animation", value++ );
	glutAddMenuEntry(	"3             - Smooth/Flat Shading", value++ );
	glutAddMenuEntry(	"4             - Wireframe/Polygon Rendering", value++ );
	glutAddMenuEntry(	"5             - Texture Mapping", value++ );
	glutAddMenuEntry(	"6             - Lighting", value++ );
	glutAddMenuEntry(	"f              - Single Step Animation", value++ );
	glutAddMenuEntry(	"+/-          - Inc/Dec Resolution", value++ );
	glutAddMenuEntry(	"Esc         - Quit", value++ );

	//trivial fix to supress unused variable warnings	
	mainmenu = mainmenu;
	
    //open menu with right click
    glutAttachMenu( GLUT_RIGHT_BUTTON );
}
