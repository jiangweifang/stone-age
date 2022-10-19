#ifndef _LOADREALBIN_H_
#define _LOADREALBIN_H_
#include "directdraw.h"
void initAutoMapColor( char * );
void makeAutoMapColor( void );
int writeAutoMapColor( char *, char * );
int readAutoMapColor( char *, char * );

int initRealbinFileOpen(char *realbinfilename, char *addrbinfilename);
#ifdef _READ16BITBMP
int InitRealTruebinFileOpen(char *szRealTrueBinFileName,char *szAdrnTruebinFileName);
#endif
void cleanupRealbin(void);

extern unsigned char autoMapColorTbl[];

#include <stdio.h>
typedef unsigned char MOJI;
typedef unsigned char U1;
typedef          char S1;
typedef unsigned short U2;
typedef          short S2;
typedef unsigned long U4;
typedef          long S4;
typedef float  F4;
typedef double F8;
#ifdef _READ16BITBMP
BOOL Read16BMP(int BmpNo,unsigned char **BmpData,int *width,int *height,BYTE **AlphaData,BOOL *useAlpha);
#endif
int realGetImage(int graphicNo, unsigned char **bmpdata, int *width, int *height);
int realGetPos(U4 GraphicNo , S2 *x , S2 *y);
int realGetWH(U4 GraphicNo , S2 *w , S2 *h);
int realGetHitPoints(U4 GraphicNo , S2 *HitX , S2 *HitY);
int realGetHitFlag(U4 GraphicNo , S2 *Hit);
BOOL realGetPrioType(U4 GraphicNo , S2 *prioType);
int realGetHeightFlag(U4 GraphicNo , S2 *Height);
int realGetNo( U4 CharAction , U4 *GraphicNo );
int realGetSoundEffect(U4 GraphicNo);
int realGetWalkSoundEffect(U4 GraphicNo);
int realGetBitmapNo( int num );
typedef struct {
	unsigned char atari_x,atari_y;	//��??
	unsigned short hit;				// �ɷ����� //��???
	short height;				//?????
	short broken;				//????
	short indamage;				//�VHP????
	short outdamage;			//��????
	short inpoison;				//�V��
	short innumb;				//�V???
	short inquiet;				//�V��?
	short instone;				//�V��?
	short indark;				//�V??
	short inconfuse;			//�V??
	short outpoison;			//�ҥ�
	short outnumb;				//��??
	short outquiet;				//�ң�?
	short outstone;				//����?
	short outdark;				//��??
	short outconfuse;			//��??
	short effect1;				//?????1??��????????��?????
	short effect2;				//?????2?�V???????��?????
	unsigned short damy_a;
	unsigned short damy_b;
	unsigned short damy_c;
	unsigned int bmpnumber;		//??�k?
} MAP_ATTR;

struct ADRNBIN{
	unsigned long	bitmapno;
	unsigned long	adder;
	unsigned long	size;
	int	xoffset;
	int	yoffset;
	unsigned int width;
	unsigned int height;
	MAP_ATTR attr;
};

#ifdef _READ16BITBMP
struct AddressBin_s{
	unsigned int bitmapno;			// ͼ��
	unsigned int adder;					// ������ͼ�ص������ʼλַ
	unsigned int palSize;				// ɫ�����ϴ�С
	unsigned int size;					// һ�����ϵĴ�С
	unsigned int alpha_size;		// alpha_size��Ϊ0��ʾ��ͼ�����Ϻ�������alpha����,alpha_size����alpha���ϵĴ�С
															// ���alpha_sizeΪ0��ʾû�д�alpha����
	int	xoffset;
	int	yoffset;
	unsigned int width;					// ͼ��
	unsigned int height;				// ͼ��
	unsigned int staturated;		// �Ƿ��ñ���Ч��
};
#endif

// ????????
static DWORD FontPal[FONT_PAL_NUM]={
#ifdef _SA_VERSION_25
	RGB(0xff ,0xff, 0xff ), // 0:FONT_PAL_WHITE
	RGB(0x00 ,0xff, 0xff ), // 1:FONT_PAL_AQUA
	RGB(0xff ,0x00, 0xff ), // 2:FONT_PAL_PURPLE
	RGB(0x48 ,0x48, 0xfa ), // 3:FONT_PAL_BLUE
	RGB(0xff ,0xea, 0x39 ), // 4:FONT_PAL_YELLOW
	RGB(0xa0 ,0xf4, 0x3a ), // 5:FONT_PAL_GREEN  a0f43a
	RGB(0xB5 ,0x38, 0x17 ), // 6:FONT_PAL_RED
	RGB(0xa0 ,0xa0, 0xa4 ), // 7:FONT_PAL_GRAY
	RGB(0xa6 ,0xca, 0xf0 ), // 8:FONT_PAL_BLUE2
	RGB(0xc0 ,0xdc, 0xc0 ), // 9:FONT_PAL_GREEN
#endif


#ifdef _EXTEND_FONT_PAL
	RGB(0xff ,0x80, 0x00 ), // 10
	RGB(0x6f ,0xc6, 0x6f ), // 11
	RGB(0x98 ,0x3d, 0xf3 ), // 12
	RGB(0xff ,0x80, 0xff ), // 13
	RGB(0x4a ,0x9f, 0xf4 ), // 14
	RGB(0xb4 ,0x0e, 0xb4 ), // 15
	RGB(0xbf ,0xbf, 0x19 ), // 16
	RGB(0xff ,0x00, 0x80 ), // 17
	RGB(0xff ,0x80, 0x80 ), // 18
	RGB(0x80 ,0x80, 0x80 ), // 19

	RGB(0xff ,0xff, 0x80 ), // 20
	RGB(0x80 ,0xff, 0xff ), // 21
	RGB(0x80 ,0xff, 0x00 ), // 22
	RGB(0x00 ,0x80, 0xff ), // 23
	RGB(0xd0 ,0x2a, 0x7d ), // 24
	RGB(0x8d ,0x56, 0x8d ), // 25
#endif
};

/*
BOOL InitRealbinFileOpen( char *realbinfilename, char *addrbinfilename);	//��ʼ��realbin�����ϲ�������صļ�����
//void SetCurFrame();									//�ۼ�CurFrame��counter����ÿ��frameִ��һ��
void CacheRLU( int howlong);							//�ͷ�̫��ûʹ�õ�ͼ��������
BOOL realGetNo( DWORD CharAction, DWORD *GraphicNo);	//��char actionת��ͼ�����
DWORD realGetNo2( DWORD bnum);							//��bnumת��ͼ�����
BOOL realIsValid( DWORD CharAction);					//���ͼ���Ƿ���Ч
DWORD realGetBitmapNo( DWORD num);						//��ͼ�����ת��bnum
BOOL realGetPos( DWORD GraphicNo, short *x, short *y);	//ȡ��GraphicNo��x��y offset
BOOL realGetWH( DWORD GraphicNo, short *w, short *h);	//ȡ��GraphicNo�Ŀ�͸�
BOOL realGetHitPoints( DWORD GraphicNo, short *HitX, short *HitY);	//ȡ��GraphicNo��ʵ�ʿ�͸�
BOOL realGetPrioType( DWORD GraphicNo , short *prioType);	//ȡ��GraphicNo������Ȩ����
BOOL realGetHitFlag( DWORD GraphicNo, short *Hit);			//ȡ��GraphicNo��Hit
BOOL realGetHeightFlag( DWORD GraphicNo, short *Height);	//ȡ��GraphicNo�Ƿ��и߶�
int realGetSoundEffect( DWORD GraphicNo);					//ȡ��GraphicNo�Ļ�����
int realGetWalkSoundEffect( DWORD GraphicNo);				//ȡ��GraphicNo�ĽŲ���
LPBYTE ReadRealBin( DWORD GraphicNo);
//����realbin
BOOL DrawScaleImage( DWORD GraphicNo, int screenx, int screeny, int screenw, int screenh, LPWORD dest,
					int destw, int desth, int pitch, LPWORD pal);
*/
#endif /*_LOADREALBIN_H_*/
