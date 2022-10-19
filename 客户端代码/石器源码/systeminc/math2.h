/************************/
/*	math2.h				*/
/************************/
#ifndef _MATH2_H_
#define _MATH2_H_

#define PAI	3.1415926535897932384626433832795

#define ABS(a)	( ( (a)<0 ) ?  -(a) : (a) )

/* ?�T���� ? ?? ??? ??? ?*******************************************************/
void AdjustDir( float *dir );
void AdjustDir( int *dir );

/* ??????��??????? ***********************************************************/
float SinT( float theat );

/* ??????��??????? ***********************************************************/
float CosT( float theat );

/* ????????? *********************************************************************/
float Atan( float x, float y );

/* ?????�D�� *************************************************************************/
int	Rnd( int min, int max );

void initRand2( void );
int rand2( void );

/* ?��???????? *******************************************************************/
float pointLen( float x1, float y1, float x2, float y2 );
float pointLen2( float x1, float y1, float x2, float y2 );

#endif

