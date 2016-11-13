#include <cstdlib>
#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include <cstring>
#include "globals.h"

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
    glutCreateWindow( "Solar System Demo" );

    // Initialize OpenGL.
    OpenGLInit();

	// Set up the callback function for resizing windows
    glutReshapeFunc( ResizeWindow );

    // Set up callback functions for key presses
    glutKeyboardFunc( KeyPressFunc );
    glutSpecialFunc( SpecialKeyFunc );

    // Callback for graphics image redrawing   
	glutDisplayFunc( Animate );

	glClearColor( 0.0, 0.0, 0.0, 1.0 );	

    // Start the main loop.  glutMainLoop never returns.
    glutMainLoop( );

    return 0;
}
