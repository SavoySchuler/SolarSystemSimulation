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
void DrawPlanet(Planet *plant);
void DrawSun();

int loadTextureFromFile( char *filename );
void initTextureMap( char *filename );
void makeTexture( GLubyte image[64][64][3] );

// global variables
GLenum spinMode = GL_TRUE;
GLenum singleStep = GL_TRUE;

// these three variables control the animation's state and speed.
const float DistScale = 1.0/37.5;
const float SizeScale = 1.0/15945.0;
float HourOfDay = 0.0;
float DayOfYear = 0.0;
float MercuryHour = 0.0;
float MercuryDay = 0.0;
float AnimateIncrement = 24.0;  // Time step for animation (hours)

typedef unsigned char byte;

bool LoadBmpFile( const char* filename, int &nrows, int &ncols, byte* &image );
void skipChars( FILE* infile, int numChars );
short readShort( FILE* infile );
static inline int GetNumBytesPerRow( int NumCols );
