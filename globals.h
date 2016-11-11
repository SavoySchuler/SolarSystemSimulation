#include "Planet.h"

// function prototypes
void OpenGLInit( void );
void Animate( void );
void Key_r( void );
void Key_s( void );
void Key_up( void );
void Key_down( void );
void ResizeWindow( int w, int h );
void KeyPressFunc( unsigned char Key, int x, int y );
void SpecialKeyFunc( int Key, int x, int y );
void DrawSun();
void SetLightModel();

int loadTextureFromFile( char *filename );
void initTextureMap( char *filename );
void makeTexture( GLubyte image[64][64][3] );


// these three variables control the animation's state and speed.
const float DistScale = 1.0/37.5;
const float SizeScale = 1.0/15945.0;


typedef unsigned char byte;

bool LoadBmpFile( const char* filename, int &nrows, int &ncols, byte* &image );
void skipChars( FILE* infile, int numChars );
short readShort( FILE* infile );
static inline int GetNumBytesPerRow( int NumCols );

