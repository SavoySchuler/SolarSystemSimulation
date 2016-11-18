/******************************************************************************
*	File: callbacks.cpp
*
*	Authors: Savoy Schuler and Daniel Hodgin
*
*	Date: 11-17-16
*
*	Description:
*
*		This file contains all callback and associated event handling functions
*		used by openGL. This includes calls and functions for keyboard, mouse,
*		and special user input as well as redisplay callbacks and the main
*		animation loop.
*
*
*	File Order and Structure:
*
*		- Window functions
*		- Animation cycle functions
*		- Key press functions and handling
*		- Special key press functions and handling
*		- Mouse click functions and handling
*		- Drop-down menu and handling
*
*	Modified:
*
*		none - Original
*
*	Functions Included:
*
*			//Window functions
*
*		void OpenGLInit( void );
*		void ResizeWindow( int w, int h );
*
*			//Cycle functions
*
*		void Animate( void );
*		void SetCelestialBodies();
*
*			//Key press functions and handling
*
*		void KeyPressFunc( unsigned char Key, int x, int y );
*		void MoveBackward();
*		void MoveForward();
*		void MoveLeft();
*		void MoveRight();
*		void MoveToStartView();
*		void MoveToTopDownView();
*		void ResetPlanets();
*		void SpeedUp( void );
*		void SpeedDown( void );
*		void StartStopAnimation( void );
*		void StepAnimation( void );
*
*			//Special key press functions and handling
*
*		void SpecialKeyFunc( int Key, int x, int y );
*
*			//Mouse click functions and handling
*
*		void MouseFunc(int button, int state, int x, int y);
*		void MouseDragFunc(int x, int y);
*
*			//Drop-down menu and handling
*
*		void CreateMenus();
*		void MainMenuHandler( int item );
*		void SubMenuHandlerControls ( int item );
*		void SubMenuHandlerOptions ( int item );
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

/********************************* Globals ***********************************/

//Globals for animate style.
GLenum spinMode = GL_TRUE;
GLenum singleStep = GL_TRUE;

//Binary globals for mode toggling.
bool light = true;
bool shade = false;
bool wire = false;
bool paths = true;
bool planetNames = true;
bool textureToggle = true;

//Global Earth times used for Earth moon animation.
float HourOfDay = 0.0;
float DayOfYear = 0.0;

//Global time step for animation (in Earth hours).
float AnimateIncrement = 0.5;

//Globals for camera control.
float Xpan = 1.6;
float Ypan = 9.0;
float Zpan = -5.0;
float Xrot = -69.0;
float Yrot = 0.0;
float Zrot = 64.0;
int Resolution = 100;

//Globals for mouse control.
int ScreenHeight = 0;
bool MouseClicked = false;

//Global pointers to planet objects.
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
* Author: Savoy Schuler and Daniel Hodgin
*
* Function: OpenGLInit
*
* Description:
*
*	Set and enable run parameters for openGP, e.g. lighting, textures, shade
*	model, clear color, and depth tests.
*
* Parameters:
*
*		void	- No input parameters needed.
*
******************************************************************************/
void OpenGLInit( void )
{
    glEnable( GL_LIGHTING );
    glEnable( GL_TEXTURE_2D );
    glEnable( GL_DEPTH_TEST );
    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );		//Keep space dark.
    glClearDepth( 1.0 );
}



/******************************************************************************
* Author: Dr. John Weiss
*
* Function: ResizeWindow
*
* Description:
*
*	ResizeWindow is called when the window is resized. This function ensures
*	the program behaves well with the window manager and different window sizes.
*
* Modified by: Savoy Schuler and Daniel Hodgin
*
* Modifications:
*
*   Added screen height update for use with mouse callbacks.
*
* Parameters:
*
*	int w	- window width
*
*	int h	- window height
*
******************************************************************************/
void ResizeWindow( int w, int h )
{
    //Local variable for aspec ratio.
    float aspectRatio;

    //Avoid errors by ensuring a mininum window width and height.
    h = ( h == 0 ) ? 1 : h;
    w = ( w == 0 ) ? 1 : w;

    //View port uses whole window.
    glViewport( 0, 0, w, h );
    aspectRatio = ( float ) w / ( float ) h;

    //Update screen height global used for mouse location and mouse events.
    ScreenHeight = h;

    //Set up the projection view matrix.
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 60.0, aspectRatio, 1.0, 600.0 );
    gluLookAt (0,0,2,0,0,0,0,1,0);

    //Select the Model View matrix.
    glMatrixMode( GL_MODELVIEW );
}



/******************************************************************************
* Author: Savoy Schuler and Daniel Hodgin
*
* Function: Animate
*
* Description:
*
*	This is the main animation loop of the program. It handles calling functions
*	for creating (only on the first pass) and drawing all celestial objects.
*
* Parameters:
*
*		void	- No input parameters needed.
*
******************************************************************************/
void Animate( void )
{
    //Will want to create planet objects the first iteration only.
    static bool firstTime = true;

    /*If this is the first pass, call set up function to create all celestial
    objects.*/
    if(firstTime == true)
    {
        SetCelestialBodies();
        SetRingsandMoon();
        firstTime = false;
    }

    //Clear the redering window.
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /*Redraw all celestial objects at updated coordinates each iteration of the
    main animation loop.*/
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

    //Clear matrix, handle camera movements.
    glLoadIdentity();
    glTranslatef ( Xpan, Ypan, Zpan );
    HandleRotate();

    //Flush the pipeline, and swap the buffers.
    glFlush();
    glutSwapBuffers();

    /*If single step animation mode enabled, stop animation loop after each
    iteration.*/
    if ( singleStep )
    {
        spinMode = GL_FALSE;
    }

    /*Always ensure a redraw for mode toggling and etc. they may not be updated
    otherwise.*/
    glutPostRedisplay();
}



/******************************************************************************
* Author: Savoy Schuler and Daniel Hodgin
*
* Function: SetCelestialBodies
*
* Description:
*
*	This function creates planet objects for each of the 8 planets, the sun, and
*	the space backdrop and sets the fields for each. Each planet object is
*	addressed by its corresponding global pointer declared at the top of this
*	file.
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
void SetCelestialBodies()
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

    filename = StringToChar("mercury.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Mercury = new Planet( "Mercury", 1416, 88, 2439, 58, nrows, ncols, image, 0.5, 0.25, 0.0 );


    filename = StringToChar("venus.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Venus = new Planet( "Venus", 5832, 225, 6052, 108, nrows, ncols, image, 0.7, 0.4, 0.0 );


    filename = StringToChar("earth.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Earth = new Planet( "Earth", 24, 365,  6378, 150, nrows, ncols, image, 0.0, 0.45, 0.1  );


    filename = StringToChar("mars.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Mars = new Planet( "Mars", 24.6, 687, 3394, 228, nrows, ncols, image, 0.75, 0.0, 0.0  );


    filename = StringToChar("jupiter.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Jupiter = new Planet( "Jupiter", 9.8, 4332, 71398/2.0, 779, nrows, ncols, image, 0.75, 0.75, 0.0  );


    filename = StringToChar("saturn.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Saturn = new Planet( "Saturn", 10.2, 10761, 60270/2.0, 1424, nrows, ncols, image, 1.0, 0.75, 0.0  );


    filename = StringToChar("uranus.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Uranus = new Planet( "Uranus", 15.5, 30682, 25550, 2867, nrows, ncols, image, 0.0, 0.5, 0.5  );


    filename = StringToChar("neptune.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Neptune = new Planet( "Neptune", 15.8, 60195.0, 24750, 4492, nrows, ncols, image, 0.0, 1.0, 1.0   );


    filename = StringToChar("sun.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Sun = new Planet( "Sun", 25, 0, 696000.0/10.0 * SizeScale, 0, nrows, ncols, image, 1.0, 1.0, 0.0  );


    filename = StringToChar("space.bmp");
    LoadBmpFile( filename, nrows, ncols, image );
    Space = new Planet( "Space", 0, 0, 100, 0, nrows, ncols, image, 1.0, 0.5, 0.0  );
}



/******************************************************************************
* Author: Savoy Schuler and Daniel Hodgin
*
* Function: KeyPressFunc
*
* Description:
*
*	This is the keyboard callback function used for handeling keyboard events.
*
*							   Key Assignments:
*					(complete list available in readme.txt)
*
*		Camera Controls:
*
*		a             - Pan left in X direction
*		d             - Pan right in Y direction
*		w             - Pan forward in Y direction
*		s             - Pan backward in Y direction
*		e             - Pan up in Z direction
*		q             - Pan down in Z direction
*
*		Options:
*
*		r             - Start/suspend animation
*		f             - Single step animation
*		1             - Slow down animation
*		2             - Speed up animation
*		3             - Smooth/flat shading
*		4             - Wireframe/polygon rendering
*		5             - Texture mapping
*		6             - Lighting
*		7             - Default view
*		8             - Top-down view
*		9             - Reset planets
*		0             - Toggle orbital paths
*		p             - Toggle planet names
*		+ (=)         - Increase Resolution
*		-             - Decrease Resolution
*
*		Esc           - Quit
*
* Parameters:
*
*		key	- the key pressed that caused the callback
*
*		x	- the x screen coordinate of the mouse at time of key press
*
*		y	- the y screen coordinate of the mouse at time of key press
*
******************************************************************************/
// glutKeyboardFunc is called to set this function to handle normal key presses.
void KeyPressFunc( unsigned char Key, int x, int y )
{

    //Case user input using switch statement.
    switch ( Key )
    {

    //Slow down animation.
    case '1':
        SpeedDown();
        break;

    //Speed up animation.
    case '2':
        SpeedUp();
        break;

    //Toggle flat or smooth shading.
    case '3':
        ( shade = !shade ) ? glShadeModel( GL_FLAT ) : glShadeModel( GL_SMOOTH );
        break;

    //Toffle wireframe or polygon rendering mode.
    case '4':
        ( wire = !wire ) ? glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ) : glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        break;

    //Toggle texture mapping on or off.
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

    //Toggle light source on or off.
    case '6':
        ( light = !light ) ? glEnable( GL_LIGHTING ) : glDisable( GL_LIGHTING );
        break;

    //Reset camera to original position.
    case '7':
        MoveToStartView();
        break;

    //Set camera to top-down view.
    case '8':
        MoveToTopDownView();
        break;

    //Reset planet's to original position.
    case '9':
        ResetPlanets();
        break;

    //Toggle drawing of orbital paths.
    case '0':
        paths = !paths;
        break;

    //Toggle display of planet and moon names.
    case 'p':
        planetNames = !planetNames;
        break;

    //Increase resolution (number of slices and stacks) of planets, sun, and moon.
    case '=':
        if (Resolution <= 9)
            Resolution += 1;
        else if (Resolution <= 145)
            Resolution += 5;
        break;

    //Decrease resolution (number of slices and stacks) of planets, sun, and moon.
    case '-':
        if (Resolution >= 15)
            Resolution -= 5;
        else if (Resolution >= 4)
            Resolution -= 1;
        break;

    //Start or stop animation.
    case 'r':
        StartStopAnimation();
        break;

    //Step animation forward one iteration.
    case 'f':
        StepAnimation();
        break;

    //Pan view forward  (Y direction).
    case 'w':
        MoveForward();
        break;

    //Pan view backward (Y direction).
    case 's':
        MoveBackward();
        break;

    //Pan view left (X direction).
    case 'a':
        MoveLeft();
        break;

    //Pan view right (X direction).
    case 'd':
        MoveRight();
        break;

    //Pan view down (Z direction), bound position to within cutoff & backdrop.
    case 'q':
        if (Zpan < 290.0)
            Zpan = Zpan + .5;
        break;

    //Pan view up (Z direction), bound position to within cutoff & backdrop.
    case 'e':
        if (Zpan > -290.0)
            Zpan = Zpan - .5;
        break;

    //Close program.
    case 27: 	// Escape key
        exit( 1 );

    }
}



/******************************************************************************
* Author: Savoy Schuler and Daniel Hodgin
*
* Function: moveBackward
*
* Description:
*
*	This function is used for moving the camera backward (Y direction),
*	accounting for the current camera angle. Positional bounds are implented to
*	ensure that the camera remains within the the cutoff window and inside the
*	space backdrop.
*
* Parameters:
*
*		void	- No input parameters needed.
*
******************************************************************************/
void MoveBackward()
{
    //Move camera backwards, accounting for camera angle.
    Ypan = Ypan + 0.5 * cos(Zrot * PI / 180);
    Xpan = Xpan + 0.5 * sin(Zrot * PI / 180);

    /*Bound x,y camera position to remain within cutoff window and space
    backdrop.*/

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
* Author: Savoy Schuler and Daniel Hodgin
*
* Function: moveForward
*
* Description:
*
*	This function is used for moving the camera forward (Y direction),
*	accounting for the current camera angle. Positional bounds are implented to
*	ensure that the camera remains within the the cutoff window and inside the
*	space backdrop.
*
* Parameters:
*
*		void	- No input parameters needed.
*
******************************************************************************/
void MoveForward()
{
    //Move camera forward, accounting for camera angle.
    Ypan = Ypan - 0.5 * cos(Zrot * PI / 180);
    Xpan = Xpan - 0.5 * sin(Zrot * PI / 180);

    /*Bound x,y camera position to remain within cutoff window and space
    backdrop.*/

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
* Author: Savoy Schuler and Daniel Hodgin
*
* Function: moveLeft
*
* Description:
*
*	This function is used for moving the camera left (X direction),
*	accounting for the current camera angle. Positional bounds are implented to
*	ensure that the camera remains within the the cutoff window and inside the
*	space backdrop.
*
* Parameters:
*
*		void	- No input parameters needed.
*
******************************************************************************/
void MoveLeft()
{
    //Move camera left, accounting for camera angle.

    float rotation = Zrot + 90;
    Ypan = Ypan + 0.5 * cos(rotation * PI / 180);
    Xpan = Xpan + 0.5 * sin(rotation * PI / 180);

    /*Bound x,y camera position to remain within cutoff window and space
    backdrop.*/

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
* Author: Savoy Schuler and Daniel Hodgin
*
* Function: moveRight
*
* Description:
*
*	This function is used for moving the camera right (X direction),
*	accounting for the current camera angle. Positional bounds are implented to
*	ensure that the camera remains within the the cutoff window and inside the
*	space backdrop.
*
* Parameters:
*
*		void	- No input parameters needed.
*
******************************************************************************/
void MoveRight()
{
    //Move camera right, accounting for camera angle.
    float rotation = Zrot - 90;
    Ypan = Ypan + 0.5 * cos(rotation * PI / 180);
    Xpan = Xpan + 0.5 * sin(rotation * PI / 180);

    /*Bound x,y camera position to remain within cutoff window and space
    backdrop.*/

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
* Author: Savoy Schuler and Daniel Hodgin
*
* Function: moveToStartView
*
* Description:
*
*	This function is used to reset the camera view to its original position.
*
* Parameters:
*
*		void	- No input parameters needed.
*
******************************************************************************/
void MoveToStartView()
{
    Xpan = 1.6;
    Ypan = 9.0;
    Zpan = -5.0;
    Xrot = -69.0;
    Yrot = 0.0;
    Zrot = 64.0;
}



/******************************************************************************
* Author: Savoy Schuler and Daniel Hodgin
*
* Function: moveToTopDownView
*
* Description:
*
*	This function is used to set the camera view to a top-down position.
*
* Parameters:
*
*		void	- No input parameters needed.
*
******************************************************************************/
void MoveToTopDownView()
{
    Xpan = 0.0;
    Ypan = 0.0;
    Zpan = -250;
    Xrot = 0.0;
    Yrot = 0.0;
    Zrot = 90.0;
}



/******************************************************************************
* Author: Savoy Schuler and Daniel Hodgin
*
* Function: resetPlanets
*
* Description:
*
*	This function is used to reset the position of the planets. The moon's
	position is dependent on Earth's and will be reset implicitly.
*
* Parameters:
*
*		void	- No input parameters needed.
*
******************************************************************************/
void ResetPlanets()
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
* Author: Savoy Schuler and Daniel Hodgin
*
* Function: speedUp
*
* Description:
*
*	This function is used speed up animation by adjusting the animation time
*	step (the amount of time passed between frames). Presently, each press will
*	double the time step. A reasonable bound is set to avoid approaching
*	infinitely.
*
* Parameters:
*
*		void	- No input parameters needed.
*
******************************************************************************/
void SpeedUp( void )
{
    //Bound the animation speed to avoid implicitly setting it to infinity.
    if (AnimateIncrement < 4380.0)
    {

        //Double the animation time step.
        AnimateIncrement *= 2.0;
    }
}



/******************************************************************************
* Author: Savoy Schuler and Daniel Hodgin
*
* Function: speedDown
*
* Description:
*
*	This function is used slow down animation by adjusting the animation time
*	step (the amount of time passed between frames). Presently, each press will
*	halve the time step. A bound is set to avoid reducing the time step to zero
*	from which it cannot be brought back up due to the multiplicative nature
*	of the SpeedUp() function.
*
* Parameters:
*
*		void	- No input parameters needed.
*
******************************************************************************/
void SpeedDown( void )
{
    //Bound the animation speed to avoid accidentally setting it to zero.
    if (AnimateIncrement > 0.0125)
    {

        //Halve the animation time step.
        AnimateIncrement /= 2.0;
    }
}



/******************************************************************************
* Author: Savoy Schuler and Daniel Hodgin
*
* Function: startStopAnimation
*
* Description:
*
*	This function is used to start or stop the animation loop. Essentially,
*	allows the user to pause animation.
*
* Parameters:
*
*		void	- No input parameters needed.
*
******************************************************************************/
void StartStopAnimation( void )
{

    /*If single step mode is enabled, it must first be disabled before allowing
    the animation loop to proceed. */

    if ( singleStep )
    {
        //End single step mode.
        singleStep = GL_FALSE;

        //Enable animation to continue.
        spinMode = GL_TRUE;
    }
    else
    {
        //Toggle continuous run of the animation loop on or off.
        spinMode = !spinMode;
    }
}



/******************************************************************************
* Author: Savoy Schuler and Daniel Hodgin
*
* Function: stepAnimation
*
* Description:
*
*	This function allows the user to stop continuous animation and rather
*	advance the animation loop by one iteration at a time.
*
* Parameters:
*
*		void	- No input parameters needed.
*
******************************************************************************/
void StepAnimation( void )
{
    //Enable single stepping through animation.
    singleStep = GL_TRUE;

    //Enable planets spinning.
    spinMode = GL_TRUE;
}



/******************************************************************************
* Author: Savoy Schuler and Daniel Hodgin
*
* Function: KeyPressFunc
*
* Description:
*
*	This is the special key callback function used for handeling special
*   keyboard (arrow key) events. All arrow key events are used to rotate the
*   viewing angle in the direction of the corresponding arrow key.
*
*   Vertical rotations are capped at 180 to avoid the user inverting their view-
*   relative axis of movement.
*
* Parameters:
*
*		key	- the key pressed that caused the callback
*
*		x	- the x screen coordinate of the mouse at time of key press
*
*		y	- the y screen coordinate of the mouse at time of key press
*
******************************************************************************/
void SpecialKeyFunc( int Key, int x, int y )
{

    //Case user input using switch statement.
    switch ( Key )
    {
    //Rotate view up, bound rotation.
    case GLUT_KEY_UP:
        Xrot = Xrot - 3;
        if(Xrot < -180)
            Xrot = -180;
        break;

    //Rotate view down, bound rotation.
    case GLUT_KEY_DOWN:
        Xrot = Xrot + 3;
        if(Xrot > 0)
            Xrot = 0;
        break;

    //Rotate view left, no bound.
    case GLUT_KEY_LEFT:
        Zrot = Zrot - 3;
        break;

    //Rotate view right, no bound.
    case GLUT_KEY_RIGHT:
        Zrot = Zrot + 3;
        break;
    }
}



/******************************************************************************
* Author: Savoy Schuler and Daniel Hodgin
*
* Function: MouseFunc
*
* Description:
*       This function toggles a IsClicked boolean that is used in the
*       mousedrag function. It also calls the mouse dragged function
*       one last time on mouse release. That resets the mousedrag function
*
*
* Parameters:
*
*		button  - mouse butten clicked
*
*		state	- specifies press or release state of mouse button
*
*		x	- x screen coordinate of the mouse at the time of the button click
*
*		y	- y screen coordinate of the mouse at the time of the button click
*
******************************************************************************/
void MouseFunc(int button, int state, int x, int y)
{
    //Check that left button has been clicked (avoid conflict with pop-up menu).
    if(button == 0)
    {
        //Check that button is in pressed down state
        if(state == 0)
        {
            MouseClicked = true;

        }
        else
        {
            MouseClicked = false;

            //Call mouse drag to reset x and y coordinates on mouse release.
            MouseDragFunc(x,y);

        }
    }
}



/******************************************************************************
* Author: Savoy Schuler and Daniel Hodgin
*
* Function: MouseDragFunc
*
* Description:
*       This function handles looking around in the program by mouse movements
*       It uses two static ints to keep last x and y positions.
*       The function works by calculating the difference in x's and y's
*       then subtracting that (divided by ten) from the rotation value.
*       then save the x and y value that just came in.
*       10000 is used as dummy value to denote that it is the first time that
*       the function is call after a mouse is pressed down. If this function
*       is called when MouseClicked is false it sets x and y to the dummy
*       values
*
*
* Parameters:
*
*   	x	- the x screen coordinate of the mouse
*
*		y	- the y screen coordinate of the mouse
*
******************************************************************************/
void MouseDragFunc(int x, int y)
{
    //Initialize statics.
    static int lastX = 10000;
    static int lastY = 10000;
    int xDiff;
    int yDiff;

    //Invert screen height to be bottom to top.
    y = ScreenHeight - y;

    //If previous x and y contain dummy value set to x and y passed in.
    if(lastX == 10000)
    {
        lastX = x;
        lastY = y;
    }

    //Calculate x and y differences
    xDiff = x - lastX;
    yDiff = y - lastY;

    //Subrtacted values (divided by 10) from rotation values.
    Zrot -= xDiff/10;
    Xrot -= yDiff/10;

    //If MouseClicked is true save x and y else set the dummy values.
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
* Author: Savoy Schuler and Daniel Hodgin
*
* Function: CreateMenus
*
* Description:
*
*   This function is used to create, populate, and set handling for a pop-up
*   menu/submenus that list the movement, options, and program exit
*   controls for the user.
*
*   The pop-up menu acts as a control list, but also allows click-use of all
*   the entries of the menu and submenus.
*
* Parameters:
*
*		void	- No input parameters needed.
*
******************************************************************************/
void CreateMenus()
{
    //Create a useable submenu for view controls.
    int value = 1;
    int submenu1 = glutCreateMenu( SubMenuHandlerControls );
    glutAddMenuEntry(	"mouse click & drag - Rotate view", value++ );
    glutAddMenuEntry(	"Up Arrow       -  Rotate up", value++ );
    glutAddMenuEntry(	"Down Arrow  - Rotate down", value++ );
    glutAddMenuEntry(	"Left Arrow     - Rotate left", value++ );
    glutAddMenuEntry(	"Right Arrow   - Rotate right", value++ );
    glutAddMenuEntry(	"a             - Pan left in X direction", value++ );
    glutAddMenuEntry(	"d             - Pan right in X direction", value++ );
    glutAddMenuEntry(	"w            - Pan forward in Y direction", value++ );
    glutAddMenuEntry(	"s             - Pan backward in Y direction", value++ );
    glutAddMenuEntry(	"e             - Pan up in Z direction", value++ );
    glutAddMenuEntry(	"q             - Pan down in Z direction", value++ );




    //Create a useable submenu for simulation options.
    value = 1;
    int submenu2 = glutCreateMenu( SubMenuHandlerOptions );
    glutAddMenuEntry(	"r              - Start/suspend animation", value++ );
    glutAddMenuEntry(	"f              - Single step animation", value++ );
    glutAddMenuEntry(	"1             - Slow down animation", value++ );
    glutAddMenuEntry(	"2             - Speed up animation", value++ );
    glutAddMenuEntry(	"3             - Smooth/flat shading", value++ );
    glutAddMenuEntry(	"4             - Wireframe/polygon rendering", value++ );
    glutAddMenuEntry(	"5             - Texture mapping", value++ );
    glutAddMenuEntry(	"6             - Lighting", value++ );
    glutAddMenuEntry(	"7             - Default view", value++ );
    glutAddMenuEntry(	"8             - Top-down view", value++ );
    glutAddMenuEntry(	"9             - Reset planets", value++ );
    glutAddMenuEntry(	"0             - Toggle orbital paths", value++ );
    glutAddMenuEntry(	"p             - Toggle planet names", value++ );
    glutAddMenuEntry(	"+ (=)        - Increase Resolution", value++ );
    glutAddMenuEntry(	"-             - Decrease Resolution", value++ );


    //Create a main menu to dispaly submenus and the program exit control.
    value = 1;
    int mainmenu = glutCreateMenu( MainMenuHandler );
    glutAddSubMenu( "Controls", submenu1 );
    glutAddSubMenu( "Options", submenu2 );
    glutAddMenuEntry( "Exit (Esc)", value++ );

    //Trivial fix to supress warnings for what appears to be an unused variable.
    mainmenu = mainmenu;

    //Open menu with right click.
    glutAttachMenu( GLUT_RIGHT_BUTTON );
}



/******************************************************************************
* Author: Savoy Schuler and Daniel Hodgin
*
* Function: MainMenuHandler
*
* Description:
*
*   This function is designed to handle user selection in the main pop-up menu.
*   In this case, the only option is exiting the program.
*
* Parameters:
*
*		void	- No input parameters needed.
*
******************************************************************************/
void MainMenuHandler( int item )
{
    //Switch statement for casing user input.
    switch ( item )
    {
    //Exit program if "Exit" is selected.
    case 1:
        exit( 1 );
        break;


    default:
        cout << "invalid main menu item " << item << endl;
        break;
    }
}



/******************************************************************************
* Author: Savoy Schuler and Daniel Hodgin
*
* Function: SubMenuHandlerControls
*
* Description:
*
*   This function is designed to handle user selection in the "Controls" submenu.
*   All submenu options are useable, except the first, and apply to view
*   position controls.
*
*   The first option is a read-only option that informs the user of left mouse
*   click-and-drag view rotatation.
*
* Parameters:
*
*		item	- the selected option
*
******************************************************************************/
void SubMenuHandlerControls ( int item )
{
    //Switch statement for casing user input.
    switch ( item )
    {
    //Read-only control for left mouse click-and-drag view rotatation.
    case 1:
        break;

    //Rotate view up, bound to avoid control inversion.
    case 2:
        Xrot = Xrot - 3;
        if(Xrot < -180)
            Xrot = -180;
        break;

    //Rotate view down, bound to avoid control inversion.
    case 3:
        Xrot = Xrot + 3;
        if(Xrot > 0)
            Xrot = 0;
        break;

    //Rotate view left.
    case 4:
        Zrot = Zrot - 3;
        break;

    //Rotate the view right.
    case 5:
        Zrot = Zrot + 3;
        break;
    //Pan view left (X direction).
    case 6:
        MoveLeft();
        break;

    //Pan view right (X direction).
    case 7:
        MoveRight();
        break;

    //Pan view forward (Y direction).
    case 8:
        MoveForward();
        break;

    //Pan view backward (Y direction).
    case 9:
        MoveBackward();
        break;

    //Pan view up (Z direction).
    case 10:
        if (Zpan > -290.0)
            Zpan = Zpan - 0.5;
        break;

    //Pan view down (Z direction).
    case 11:
        if (Zpan < 290.0)
            Zpan = Zpan + 0.5;
        break;

    //For good practice and error catching. Should not be reached.
    default:
        cout << "invalid main menu item " << item << endl;
        break;
    }
}



/******************************************************************************
* Author: Savoy Schuler and Daniel Hodgin
*
* Function: SubMenuHandlerOptions
*
* Description:
*
*   This function is designed to handle user selection in the "Options" submenu.
*   This submenu provides options that apply to objects drawn in the program.
*
* Parameters:
*
*		item	- the selected option
*
******************************************************************************/
void SubMenuHandlerOptions ( int item )
{
    //Switch statement for casing user input.
    switch ( item )
    {
    //Start/suspend animation.
    case 1:
        StartStopAnimation();
        break;

    //Single step animation.
    case 2:
        StepAnimation();
        break;

    //Slow down animation.
    case 3:
        SpeedDown();
        break;

    //Speed up animation.
    case 4:
        SpeedUp();
        break;

    //Toggle between smooth and flat shading.
    case 5:
        ( shade = !shade ) ? glShadeModel( GL_FLAT ) : glShadeModel( GL_SMOOTH );
        break;

    //Toggle between wireframe and polygon rendering.
    case 6:
        ( wire = !wire ) ? glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ) : glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        break;

    //Texture mapping.
    case 7:
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

    //Toggle lighting.
    case 8:
        ( light = !light ) ? glEnable( GL_LIGHTING ) : glDisable( GL_LIGHTING );

        break;

    //Reset to default view position.
    case 9:
        MoveToStartView();
        break;

    //Set to top-down view.
    case 10:
        MoveToTopDownView();
        break;

    //Reset position of planets.
    case 11:
        ResetPlanets();
        break;

    //Toggle drawing of orbital paths.
    case 12:
        paths = !paths;
        break;

    //Toggle planet name display.
    case 13:
        planetNames = !planetNames;
        break;

    //Increase resolution of planet, moon, and sun.
    case 14:
        if (Resolution <= 9)
            Resolution += 1;
        else if (Resolution <= 145)
            Resolution += 5;
        break;

    //Decrease resolution of planet, moon, and sun.
    case 15:
        if (Resolution >= 15)
            Resolution -= 5;
        else if (Resolution >= 4)
            Resolution -= 1;
        break;

    //For good practice and error catching. Should not be reached.
    default:
        cout << "invalid main menu item " << item << endl;
        break;
    }
}
