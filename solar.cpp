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
 *
 *      This program is intended to be an exploration into the solar system
 *      as well as in applying computer graphics in 3D space, lighting and
 *      texture mapping.
 *
 *      Planetary orbits are scaled by a constant factor of 1.0/37.5 to maintain
 *      a ratio of relative distance. All planets, except the Sun, Jupiter, and
 *      Saturn, are scaled by a constant factor of 1.0/15945.0. The Sun is
 *      displayed at 1/10 its actual size. Jupiter and Saturn are displayed at
 *      half their actual size.
 *
 *      The user views the program through a first person camera that
 *      is allowed to move through the space and see the planets in
 *      motion.
 *
 *      Full controls are specified in the program with right clicking and in
 *      the included readme.txt.
 *
 *      Extra features:
 *
 *      Changing user view by left click and drag.
 *      Pop-up menus on right click
 *      Default views: top-down and Sun's point of view.
 *      Toggling planet names and orbit paths
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
*
*   Main function of the program. Sets up the viewing screen and sets the
*   callback function before permenantly entering the glut main loop, never to
*   return.
*
* Parameters:
*
*	argc	- number of command line parameters
*
*	argv	- array of command line parameters
*
******************************************************************************/
int main( int argc, char** argv )
{
    //Set double buffer for animation.
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

    //Create and position the graphics window
    glutInitWindowPosition( 0, 0 );
    glutInitWindowSize( 1000, 1000 );
    glutCreateWindow( "Solar System Simulation <Right Click for Controls>" );

    //Initialize OpenGL.
    OpenGLInit();

    //Set up callback function for resizing the window.
    glutReshapeFunc( ResizeWindow );

    //Set up callback functions for key presses.
    glutKeyboardFunc( KeyPressFunc );
    glutSpecialFunc( SpecialKeyFunc );
    glutMouseFunc( MouseFunc );
    glutMotionFunc( MouseDragFunc );

    //Callback for graphics image redrawing.
    glutDisplayFunc( Animate );

    //Create pop-up menus.
    CreateMenus();

    //Set clear color. Keep space black.
    glClearColor( 0.0, 0.0, 0.0, 1.0 );

    //Enter glut main loop. Should never return from it.
    glutMainLoop( );

    //Supress compiler warnings.
    return 0;
}
