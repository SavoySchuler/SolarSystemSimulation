/*************************************************************************//**
 * @file solar.cpp
 *
 * @mainpage Programming Assignment #3: Solar System Simulation
 *
 * @author  Savoy Schuler, Daniel Hodgin
 *
 * @date  November 17, 2016
 *
 * @par Professor: Dr. John Weiss
 *
 * @par Course: CSC 433 Computer Graphics - M001 -  9:00 am
 *
 * @par Location:  McLaury - 205
 *
 * @par System Requirements:
 *		system: Unix Lab Computer
 *		requirements: OpenGL
 *		os: Fedora, CentOS
 *		compiler: c++11
 *
 * @par Compiling Instructions:
 *
 *		make
 *
 * @par Usage Instructions:
 *
 *		solar
 *
 * @par Input:
 *
 *		<none>
 *
 * @par Output:
 *
 *		<none>
 *
 * @details:
 *      This program is intended to be an exploration into the solar system
 *      as well as applying computer graphics in 3D space. It also is an
 *      application in lighting and texture mapping.
 *
 *      The planets are sized, move, and placed based of scaled version
 *      of the planets attributes.
 *  
 *      The user is put into the program as a first person camera that
 *      is allowed to move through the space and see the planets in
 *      motion.
 *
 *      Extra features:
 *      
 *      Changing user view by right click and drag.
 *      Pop-up menus on left click
 *      Default views.(Top Down and Suns Point of view)
 *      Toggling Names and orbit paths
 *      
 *
 * @par Modifications:
 *
 *		None	- Original Version
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @bugs <none>
 *
 * @todo <none>
 *
 *****************************************************************************/

/**************************** Library Includes *******************************/
#include <cstdlib>
#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include <cstring>
#include "globals.h"


/******************************************************************************
* Author: Savoy Schuler and Daniel Hodgin
*
* Function: main
*
* Description:
*       Sets up the viewing screen and sets the callback function
*
*
* Parameters:
*
*	argc	- number of command line parameters
*
*	argv	- array of command line parameters
*
******************************************************************************/
// Main routine
// Set up OpenGL, hook up callbacks, and start the main loop
int main( int argc, char** argv )
{
    char *filename = argc > 1 ? strdup( argv[1] ) : NULL;


    // Need to double buffer for animation
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

    // Create and position the graphics window
    glutInitWindowPosition( 0, 0 );
    glutInitWindowSize( 1000, 1000 );
    glutCreateWindow( "Solar System Simulation <Right Click for Controls>" );

    // Initialize OpenGL.
    OpenGLInit();

    // Set up the callback function for resizing windows
    glutReshapeFunc( ResizeWindow );

    // Set up callback functions for key presses
    glutKeyboardFunc( KeyPressFunc );
    glutSpecialFunc( SpecialKeyFunc );
    glutMouseFunc( MouseFunc );
    glutMotionFunc( MouseDragFunc );
    // Callback for graphics image redrawing
    glutDisplayFunc( Animate );

    CreateMenus();

    glClearColor( 0.0, 0.0, 0.0, 1.0 );

    // Start the main loop.  glutMainLoop never returns.
    glutMainLoop( );

    return 0;
}
