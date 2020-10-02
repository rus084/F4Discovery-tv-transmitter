#ifndef _3d_H
#define _3d_H

#include "stdint.h"

//#include "mem.h"
//#include "c_types.h"
//#include "user_interface.h"
//#include "ets_sys.h"
//#include "ntsc_broadcast.h"

#define FBW 464 //Must be divisible by 8.  These are actually "double-pixels" used for double-resolution monochrome width.
#define FBW2 (FBW/2) //Actual width in true pixels.
#define FBH 220

extern int gframe;
extern uint8_t * frontframe;
extern int16_t ProjectionMatrix[16];
extern int16_t ModelviewMatrix[16];
extern int CNFGPenX, CNFGPenY;
extern uint8_t CNFGBGColor;
extern uint8_t CNFGLastColor;
extern uint8_t CNFGDialogColor; //background for boxes

void CNFGTackSegment( int x0, int y0, int x1, int y1 );
int LABS( int x );

//#define CNFGTackPixelFAST( x, y ) { frontframe[(x+y*FBW)>>2] |= 2<<( (x&3)<<1 ); }  //Store in 4 bits per byte.
void LocalToScreenspace( int16_t * coords_3v, int16_t * o1, int16_t * o2 );
int16_t tdSIN( uint8_t iv );
int16_t tdCOS( uint8_t iv );

/* Colors:
    0 .. 15 = standard-density colors
	16: Black, Double-Density
	17: White, Double-Density
*/
void CNFGColor( uint8_t col ); 

void tdTranslate( int16_t * f, int16_t x, int16_t y, int16_t z );		//Operates ON f
void tdScale( int16_t * f, int16_t x, int16_t y, int16_t z );			//Operates ON f
void tdRotateEA( int16_t * f, int16_t x, int16_t y, int16_t z );		//Operates ON f

void CNFGDrawText( const char * text, int scale );
void CNFGDrawBox(  int x1, int y1, int x2, int y2 );
void CNFGTackRectangle( short x1, short y1, short x2, short y2 );
void tdMultiply( int16_t * fin1, int16_t * fin2, int16_t * fout );
void tdPTransform( int16_t * pin, int16_t * f, int16_t * pout );
void  td4Transform( int16_t * pin, int16_t * f, int16_t * pout );
void MakeTranslate( int x, int y, int z, int16_t * out );
void Perspective( int fovx, int aspect, int zNear, int zFar, int16_t * out );
void tdIdentity( int16_t * matrix );
void MakeYRotationMatrix( uint8_t angle, int16_t * f );
void MakeXRotationMatrix( uint8_t angle, int16_t * f );
void DrawGeoSphere();
void Draw3DSegment( int16_t * c1, int16_t * c2 );

int16_t tdPerlin2D( int16_t x, int16_t y );
int16_t tdFLerp( int16_t a, int16_t b, int16_t t );
int16_t tdNoiseAt( int16_t x, int16_t y );

#endif

