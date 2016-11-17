#include "Planet.h"

// function prototypes
void OpenGLInit( void );
void Animate( void );
void startStopAnimation( void );
void stepAnimation( void );
void speedUp( void );
void speedDown( void );
void ResizeWindow( int w, int h );
void KeyPressFunc( unsigned char Key, int x, int y );
void SpecialKeyFunc( int Key, int x, int y );
void MouseFunc(int button, int state, int x, int y);
void MouseDragFunc(int x, int y);
void DrawSun();
void SetLightModel();
void HandleRotate();
void DrawMoon(int DayOfYear);
void DrawPlanet(Planet *plant);
void DrawSun(Planet *sun);
void moveForward();
void moveBackward();
void moveLeft();
void moveRight();
void moveToStartView();
void moveToTopDownView();
void resetPlanets();

int loadTextureFromFile( char *filename );
void initTextureMap( char *filename );
void makeTexture( GLubyte image[64][64][3] );
void DrawTextString( string str, double radius);
char * stringToChar (string str);

// these three variables control the animation's state and speed.
const float DistScale = 1.0/37.5;
const float SizeScale = 1.0/15945.0;
const float PI = 3.14159265358979323846264;


typedef unsigned char byte;

bool LoadBmpFile( const char* filename, int &nrows, int &ncols, byte* &image );
void skipChars( FILE* infile, int numChars );
short readShort( FILE* infile );
static inline int GetNumBytesPerRow( int NumCols );
int setTexture( byte* image, int rows, int ncols );
void CreateMenus();
void DrawSpace(Planet *space);
void setCelestialBodies();
void MainMenuHandler( int item );

// global variables
extern GLenum spinMode;
extern GLenum singleStep;

extern float HourOfDay;
extern float DayOfYear;
extern float MercuryHour;
extern float MercuryDay;
extern float AnimateIncrement;  // Time step for animation (hours)
extern float Xpan;
extern float Ypan;
extern float Zpan;
extern float Xrot;
extern float Yrot;
extern float Zrot;
extern int Resolution;
extern int ScreenHeight;
extern bool textureToggle, light, shade, wire;
extern bool MouseClicked;

