/******************************************************************************
*	File: gpgpuPrimes.cu
*
*	Authors: Savoy Schuler
*
*	Date: November 2, 2016
*
*	Functions Included:
*
*		gpuProperties
*		countPrimes	<kernel>
*		isPrime		<kernal>
*		gpgpuSearch
*
*	Description:
*
*		This files contains all functions needed for parallelizing a range
*		inclusive prime number count using GPGPU, Cuda, and an Nvidia graphics
*		card. Thie file contains one hose function that calls two kernels on the
*		device; one to check if a number is a prime (storing a 1 on an
*		associative array if true) and one to count the number of 1's in an
*		array in parallel.
*
*	Modified: Original
*
*
******************************************************************************/

/**************************** Library Includes *******************************/
#include <cstdlib>
#include <cmath>
#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include "Planet.h"
#include "globals.h"

/******************************* Name Space **********************************/

using namespace std;

// global variables
GLenum spinMode = GL_TRUE;
GLenum singleStep = GL_TRUE;

bool light = true, shade = false, wire = false, paths = true, planetNames = true;

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
int ScreenHeight = 0;
bool MouseClicked = false;

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
void OpenGLInit( void )
{
    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glClearDepth( 1.0 );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_TEXTURE_2D );
    glEnable( GL_LIGHTING );
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
// ResizeWindow is called when the window is resized
void ResizeWindow( int w, int h )
{
    float aspectRatio;
    h = ( h == 0 ) ? 1 : h;
    w = ( w == 0 ) ? 1 : w;
    glViewport( 0, 0, w, h );	// View port uses whole window
    aspectRatio = ( float ) w / ( float ) h;
    ScreenHeight = h;
    // Set up the projection view matrix (not very well!)
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    gluPerspective( 60.0, aspectRatio, 1.0, 600.0 );
    
    gluLookAt (0,0,2,0,0,0,0,1,0);

    // Select the Modelview matrix
    glMatrixMode( GL_MODELVIEW );
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
void setCelestialBodies()
{
	int nrows, ncols;
    byte* image;
	char * filename;
		
		
	filename = stringToChar("mercury.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Mercury = new Planet("Mercury",1416,88,   2439, 58, nrows, ncols, image, 0.5, 0.25, 0.0 );
        
         
	filename = stringToChar("venus.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Venus = new Planet("Venus",    5832,225,  6052, 108, nrows, ncols, image, 0.7, 0.4, 0.0  );


	filename = stringToChar("earth.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Earth = new Planet("Earth",    24,  365,  6378, 150, nrows, ncols, image, 0.0, 0.45, 0.1  );


	filename = stringToChar("mars.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Mars = new Planet("Mars",      24.6,687,  3394, 228, nrows, ncols, image, 0.75, 0.0, 0.0  );


	filename = stringToChar("jupiter.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Jupiter = new Planet("Jupiter",9.8, 4332, 71398/2.0,779, nrows, ncols, image, 0.75, 0.75, 0.0  );

	
	filename = stringToChar("saturn.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Saturn = new Planet("Saturn",  10.2,10761,60270/2.0,1424, nrows, ncols, image, 1.0, 0.75, 0.0  );

	
	filename = stringToChar("uranus.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Uranus = new Planet("Uranus",  15.5,30682,25550,2867, nrows, ncols, image, 0.0, 0.5, 0.5  );


	filename = stringToChar("neptune.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Neptune = new Planet("Neptune",15.8,60195.0,24750,4492, nrows, ncols, image, 0.0, 1.0, 1.0   );
        
      
    filename = stringToChar("sun.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Sun = new Planet("Sun", 25, 0, 696000.0/10.0 * SizeScale, 0, nrows, ncols, image, 1.0, 1.0, 0.0  );
        
     
    filename = stringToChar("space.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Space = new Planet("Space", 0, 0, 100, 0, nrows, ncols, image, 1.0, 0.5, 0.0  );
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
// glutKeyboardFunc is called to set this function to handle normal key presses.
void KeyPressFunc( unsigned char Key, int x, int y )
{
    switch ( Key )
    {
    	case '1':
            speedDown();
            break;
        case '2':
            speedUp();
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
        case '7':
            moveToStartView();
            break;
        case '8':
            moveToTopDownView();
            break;
        case '9':
            resetPlanets();
            break;
      	case '0':
            paths = !paths;
            break;
      	case 'p':
            planetNames = !planetNames;
            break;            
        case '=':
        	if (Resolution <= 9)
        		Resolution += 1;
        	else if (Resolution <= 145)
        		Resolution += 5;
            break;
        case '-':
        	if (Resolution >= 15)
            	Resolution -= 5;
            else if (Resolution >= 4)
            	Resolution -= 1;	
            break;
        case 'r':
            startStopAnimation();
            break;
        case 'f':
            stepAnimation();  
            break;
		case 'w':
        	moveForward();
            break;
        case 's':
        	moveBackward();
            break;
        case 'a':
            moveLeft();
            break;
        case 'd':
        	moveRight();
            break;
        case 'q':
        	if (Zpan < 290.0)
           		Zpan = Zpan + .5;
            break;          
        case 'e':
            if (Zpan > -290.0)
            	Zpan = Zpan - .5;
	    	break;
        case 27: 	// Escape key
            exit( 1 );
    }
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
void moveBackward()
{
    Ypan = Ypan + 0.5 * cos(Zrot * PI / 180);
    Xpan = Xpan + 0.5 * sin(Zrot * PI / 180);

    if(Xpan > 290)
    {
        Xpan = 290;
    }
    else if(Xpan < -290)
    {
        Xpan = -290;
    }

    if(Ypan > 290)
    {
        Ypan = 290;
    }
    else if(Ypan < -290)
    {
        Ypan = -290;
    }
	
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
void moveForward()
{
    Ypan = Ypan - 0.5 * cos(Zrot * PI / 180);
    Xpan = Xpan - 0.5 * sin(Zrot * PI / 180);

    if(Xpan > 290)
    {
        Xpan = 290;
    }
    else if(Xpan < -290)
    {
        Xpan = -290;
    }

    if(Ypan > 290)
    {
        Ypan = 290;
    }
    else if(Ypan < -290)
    {
        Ypan = -290;
    }
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
void moveLeft()
{
    float rotation = Zrot + 90;
    Ypan = Ypan + 0.5 * cos(rotation * PI / 180);
    Xpan = Xpan + 0.5 * sin(rotation * PI / 180);

    if(Xpan > 290)
    {
        Xpan = 290;
    }
    else if(Xpan < -290)
    {
        Xpan = -290;
    }

    if(Ypan > 290)
    {
        Ypan = 290;
    }
    else if(Ypan < -290)
    {
        Ypan = -290;
    }
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
void moveRight()
{
    float rotation = Zrot - 90;
    Ypan = Ypan + 0.5 * cos(rotation * PI / 180);
    Xpan = Xpan + 0.5 * sin(rotation * PI / 180);

    if(Xpan > 290)
    {
        Xpan = 290;
    }
    else if(Xpan < -290)
    {
        Xpan = -290;
    }

    if(Ypan > 290)
    {
        Ypan = 290;
    }
    else if(Ypan < -290)
    {
        Ypan = -290;
    }
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
void moveToStartView()
{
    Xpan = 1.6;
    Ypan = 9.0;
    Zpan = -5.0;
    Xrot = -69.0;
    Yrot = 0.0;
    Zrot = 64.0;
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
void moveToTopDownView()
{
    Xpan = 0.0;
    Ypan = 0.0;
    Zpan = -250;
    Xrot = 0.0;
    Yrot = 0.0;
    Zrot = 90.0;
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
void resetPlanets()
{
    Mercury->setHourOfDay(0.0);
    Mercury->setDayOfYear(0.0);

    Venus->setHourOfDay(0.0);
    Venus->setDayOfYear(0.0);

    Earth->setHourOfDay(0.0);
    Earth->setDayOfYear(0.0);

    Mars->setHourOfDay(0.0);
    Mars->setDayOfYear(0.0);

    Jupiter->setHourOfDay(0.0);
    Jupiter->setDayOfYear(0.0);

    Saturn->setHourOfDay(0.0);
    Saturn->setDayOfYear(0.0);

    Uranus->setHourOfDay(0.0);
    Uranus->setDayOfYear(0.0);

    Neptune->setHourOfDay(0.0);
    Neptune->setDayOfYear(0.0);
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
// animation speed
void speedUp( void )
{	
	if (AnimateIncrement < 4380.0)
   		AnimateIncrement *= 2.0;			// Double the animation time step
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
// animation speed
void speedDown( void )
{
	if (AnimateIncrement > 0.0125)
    	AnimateIncrement /= 2.0;			// Halve the animation time step
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
// single step animation
void stepAnimation( void )
{
    singleStep = GL_TRUE;
    spinMode = GL_TRUE;
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
void MouseFunc(int button, int state, int x, int y)
{
	MouseClicked = !MouseClicked;
    if(!MouseClicked)
        MouseDragFunc(x,y);
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
void MouseDragFunc(int x, int y)
{
	static int lastX = 10000;
    static int lastY = 10000;
    int xDiff;
    int yDiff;
    y = ScreenHeight - y;
    if(lastX == 10000)
    {
        lastX = x;
        lastY = y;
    }

    xDiff = x - lastX;
    yDiff = y - lastY;

    Zrot -= xDiff/10;
    Xrot -= yDiff/10;

    if(MouseClicked)
    {
        lastX = x;
        lastY = y;
    }
    else
    {
        lastX = 10000;
        lastY = 10000;
    }
    
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
void CreateMenus()
{
    //create main menu
    int value = 1;
    int mainmenu = glutCreateMenu( MainMenuHandler );
    
	glutAddMenuEntry(	"Camera Controls:", value++ );
	glutAddMenuEntry(	"Up Arrow       -  Rotate up", value++ );
	glutAddMenuEntry(	"Down Arrow  - Rotate down", value++ );
	glutAddMenuEntry(	"Left Arrow     - Rotate left", value++ );
	glutAddMenuEntry(	"Right Arrow   - Rotate right", value++ );
	glutAddMenuEntry(	"a             - Pan left in X direction", value++ );
	glutAddMenuEntry(	"d             - Pan right in Y direction", value++ );
	glutAddMenuEntry(	"w            - Pan forward in Y direction", value++ );
	glutAddMenuEntry(	"s             - Pan backward in Y direction", value++ );
	glutAddMenuEntry(	"q             - Pan down in Z direction", value++ );
	glutAddMenuEntry(	"e             - Pan up in Z direction", value++ );
	glutAddMenuEntry(	"                                   ", value++ );
	glutAddMenuEntry(	"Options:                                   ", value++ );
	glutAddMenuEntry(	"r              - Start/suspend animation", value++ );
	glutAddMenuEntry(	"f              - Single step animation", value++ );
	glutAddMenuEntry(	"1             - Speed Down Animation", value++ );
	glutAddMenuEntry(	"2             - Speed Up Animation", value++ );
	glutAddMenuEntry(	"3             - Smooth/Flat Shading", value++ );
	glutAddMenuEntry(	"4             - Wireframe/Polygon Rendering", value++ );
	glutAddMenuEntry(	"5             - Texture Mapping", value++ );
	glutAddMenuEntry(	"6             - Lighting", value++ );
	glutAddMenuEntry(	"7             - Default view", value++ );
	glutAddMenuEntry(	"8             - Top-down view", value++ );
	glutAddMenuEntry(	"9             - Reset planets", value++ );
	glutAddMenuEntry(	"0             - Toggle orbital paths", value++ );
	glutAddMenuEntry(	"p             - Toggle planet names", value++ );
	glutAddMenuEntry(	"+ (=)        - Increase Resolution", value++ );
	glutAddMenuEntry(	"-             - Decrease Resolution", value++ );
	glutAddMenuEntry(	"                                   ", value++ );
	glutAddMenuEntry(	"Esc         - Quit", value++ );

	//trivial fix to supress unused variable warnings	
	mainmenu = mainmenu;
	
    //open menu with right click
    glutAttachMenu( GLUT_RIGHT_BUTTON );
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
void MainMenuHandler( int item )
{
	//for casing user input
    switch ( item )
    {
        case 1:
        	break;
        case 2:
            Xrot = Xrot - 1;
	        if(Xrot < -180)
		        Xrot = -180;
        	break;        
        case 3:
			Xrot = Xrot + 1;
	        if(Xrot > 0)
		        Xrot = 0; 
            break;
        case 4:
			Zrot = Zrot - 1;
        	break;
        case 5:
			Zrot = Zrot + 1;
        case 6:
			moveLeft();
        	break;        
        case 7:
			moveRight();
            break;
        case 8:
			moveForward();
        	break;
        case 9:
			moveBackward();
        	break;        
        case 10:
       		if (Zpan < 290.0)
           		Zpan = Zpan + 0.5;
            break;    
        case 11:
            if (Zpan > -290.0)
            	Zpan = Zpan - 0.5;
        	break;        
        
        case 12:		//Separator
        	break;
        case 13:		//Options:
        	break;
        case 14:
			startStopAnimation();
        	break;        
        case 15:
			stepAnimation();  
            break;
        case 16:
			speedDown();
            break;
        case 17:
			speedUp();
        	break;
        case 18:
			( shade = !shade ) ? glShadeModel( GL_FLAT ) : glShadeModel( GL_SMOOTH );
        	break;        
        case 19:
		    ( wire = !wire ) ? glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ) : glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
            break;              
        case 20:
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
        case 21:
		    ( light = !light ) ? glEnable( GL_LIGHTING ) : glDisable( GL_LIGHTING );

            break;    
        case 22:
			moveToStartView();

        	break;        
        case 23:
			moveToTopDownView();
        	break;   
        case 24:
       		resetPlanets();
        	break;
        case 25:
            paths = !paths;
            break;
      	case 26:
            planetNames = !planetNames;
            break;  	
        case 27:
        	if (Resolution <= 9)
        		Resolution += 1;
        	else if (Resolution <= 145)
        		Resolution += 5;

        	break;   
        case 28:
        	if (Resolution >= 15)
            	Resolution -= 5;
            else if (Resolution >= 4)
            	Resolution -= 1;	
        	break;           	
        case 29:
        	break;
        case 30:
			exit( 1 );
            break; 
        default:
            //Should not be reached, error catching.
            cout << "invalid main menu item " << item << endl;
            break;
    }
}
