/******************************************************************************
*	File:
*
*	Authors:
*
*	Date:
*
*	Functions Included:
*
*
*	Description:
*
*
*	Modified: Original
*
*
******************************************************************************/

/***************************** File Includes *********************************/

#include "Planet.h"

/******************************** Type Def ***********************************/

typedef unsigned char byte;



/******************************* Constants **********************************/

//These three variables control the animation's state and speed.
const float DistScale = 1.0/37.5;
const float SizeScale = 1.0/15945.0;
const float PI = 3.14159265358979323846264;



/*************************** Global Variables *****************************/


/* Externs defined in callbacks.cpp: */
//Mode booleans
extern GLenum spinMode;
extern GLenum singleStep;
extern bool light, shade, wire, paths, planetNames, textureToggle;

//Planet variables
extern float HourOfDay;
extern float DayOfYear;
extern float MercuryHour;
extern float MercuryDay;

// Time step for animation (hours)
extern float AnimateIncrement;

//Camera controls
extern float Xpan;
extern float Ypan;
extern float Zpan;
extern float Xrot;
extern float Yrot;
extern float Zrot;
extern int ScreenHeight;
extern bool MouseClicked;


//Resolution toggling
extern int Resolution;



/*************************** Function Prototypes *****************************/


                    /* Located in callbacks.cpp in order: */

//Window functions
void OpenGLInit( void );
void ResizeWindow( int w, int h );

//Cycle functions
void Animate( void );
void SetCelestialBodies();

//Key press functions and handling
void KeyPressFunc( unsigned char Key, int x, int y );
void MoveBackward();
void MoveForward();
void MoveLeft();
void MoveRight();
void MoveToStartView();
void MoveToTopDownView();
void ResetPlanets();
void SpeedUp( void );
void SpeedDown( void );
void StartStopAnimation( void );
void StepAnimation( void );

//Special key press functions and handling
void SpecialKeyFunc( int Key, int x, int y );

//Mouse click functions and handling
void MouseFunc(int button, int state, int x, int y);
void MouseDragFunc(int x, int y);

//Drop-down menu and handling
void CreateMenus();
void MainMenuHandler( int item );
void SubMenuHandlerControls ( int item );
void SubMenuHandlerOptions ( int item );



                    /* Located in orbits.cpp in order: */

    //Main functions. 

//Create auxiliary planet objects Rings and Moon.
void SetRingsandMoon();

//Set light source.
void SetLightModel();

//Set object material properties. 
void SetSunMatProp(Planet *sun);
void SetPlanetMatProps(Planet *plant);
void SetMoonMatProps(Planet *Moon);
void SetRingsMatProps(Planet *Rings);
void SetOrbitMatProps();

//Draw objects.
void DrawSpace(Planet *space);
void DrawSun(Planet *sun);
void DrawPlanet(Planet *plant);
void DrawMoon(int DayOfYear);
void DrawTextString( string str, double radius);

//Set up texture map. 
int SetTexture( byte* image, int rows, int ncols );

    //Helper functions

//Handle user view.
void HandleRotate();

//Convert image string files names to character arrays). 
char* StringToChar (string str);


                    /* Located in bmpRead.cpp in order: */

bool LoadBmpFile( const char* filename, int &nrows, int &ncols, byte* &image );
