/************************/
/*	sprdisp.h			*/
/************************/
#ifndef _SPRDISP_H_
#define _SPRDISP_H_

#include "version.h"
#define DISP_BUFFER_SIZE 4096 	// ����???????
enum{
	DISP_PRIO_BG 			= 0,	//����
	DISP_PRIO_TILE 		= 1,	//�ر�// ????????��????????
	DISP_PRIO_CHAR 		= 10,	//����// ???
	DISP_PRIO_PARTS 	= 10,	//����// ?????��??
	DISP_PRIO_RESERVE = 20,	//Ԥ��
	DISP_PRIO_JIKI 		= 30,	/* ��? 	*/
	DISP_PRIO_GRID 		= 100,	// ????????
	DISP_PRIO_BOX,				/* ???? */
	DISP_PRIO_IME1,				/* ????????????  ?��? */
	DISP_PRIO_IME2,				/* ????????????  ����? */
								/* ??????? */
	DISP_PRIO_MENU,				//ѡ��/* ???? */
	DISP_PRIO_IME3,				/* ?????????????  ?��? */
	DISP_PRIO_IME4,				/* ?????????????  ����? */
	DISP_PRIO_BOX2,				/* ????? */
	DISP_PRIO_ITEM,				/* ???? */
								/* ???????? */
	DISP_PRIO_YES_NO_WND,		/* ?�_????? */
	DISP_PRIO_YES_NO_BTN,		/* ?�_??? */
	DISP_PRIO_BOX3,				/* ????? */
	DISP_PRIO_DRAG,				/* ????? */
	DISP_PRIO_MOUSE,			/* ??????? 	*/
	DISP_PRIO_TOP = 255			/* ??�I 	*/
};

typedef struct {
	int x, y;				//��ͼʱ������// ����?��
	int bmpNo;			//ͼ���
	ACTION *pAct;		// ����
	BOOL hitFlag;		// ʮλ��Ϊ 1:Ҫ��ʾalpha 2:���ʹ��� 3:ʯ�� 4:�ж�	
	char DrawEffect;	// 0:���ر��� 1:alpha 2:���ʹ��� 3:ʯ�� 4:�ж�
#ifdef _READ16BITBMP
	char DrawEffect;	// 0:���ر��� 1:alpha 2:���ʹ��� 3:ʯ�� 4:�ж�
#endif
#ifdef _SFUMATO
	int sfumato;		// ������Ⱦͼ��ɫ��
#endif
}DISP_INFO;

typedef struct {
	short no;	//����ͼ��DISP_INFO��λ��// ?????�t??�k?
	UCHAR dispPrio; 	//��ʾʱ������˳��// ����??�I??
}DISP_SORT;

typedef struct{
	DISP_INFO DispInfo[ DISP_BUFFER_SIZE ];
	DISP_SORT DispSort[ DISP_BUFFER_SIZE ];
	short 		DispCnt;	//Ŀǰ��������//
}DISP_BUFFER;
extern DISP_BUFFER 	DispBuffer;

extern char *pRealBinBits;
extern int RealBinWidth, RealBinHeight;
#ifdef _READ16BITBMP
extern BYTE *pRealBinAlpha;
#endif

void DrawAlpha32(
	unsigned long*   lpDst,			// Ŀ�껺��
	unsigned long    iDstX,			// Ŀ��λ��
	unsigned long    iDstY,			// Ŀ��λ��
	unsigned long    iDstPitch,		// Ŀ�껺���pitch
	unsigned long*   lpSrc,			// ԭɫ�ʻ���
	unsigned long    iSrcX,			// ԭɫ��λ��
	unsigned long    iSrcY,			// ԭɫ��λ��
	unsigned long    iSrcW,			// ԭ����ĳߴ�
	unsigned long    iSrcH,			// ԭ����ĳߴ�
	unsigned long    iSrcPitch		// ԭɫ��pitch
	);

void ablend_565(unsigned char *lpAlpha, unsigned int iAlpPitch,
	unsigned char *lpSrc, unsigned int iSrcX, unsigned int iSrcY,
	unsigned int iSrcPitch, unsigned char *lpDst,
	unsigned int iDstX, unsigned int iDstY,
	unsigned int iDstW, unsigned int iDstH,
	unsigned int iDstPitch);
extern int SurfaceBusyFlag;
void SortDispBuffer( void );
BOOL ��ȡ�����ߴ�(ACTION* a0,short* wx,short* wy);
void PutBmp( void );
int StockDispBuffer( int x, int y, UCHAR prio, int bmpNo, BOOL hitFlag );
#ifdef _SFUMATO
int StockDispBuffer2( int x, int y, UCHAR dispPrio, int bmpNo, BOOL hitFlag, int sfumato/* = 0*/);
#else
int StockDispBuffer2( int x, int y, UCHAR dispPrio, int bmpNo, BOOL hitFlag );
#endif
void StockTaskDispBuffer( void );
void StockTaskDispBuffer2( int prio1, int prio2 );
void StockBoxDispBuffer( int x1, int y1, int x2, int y2, UCHAR dispPrio, int color, BOOL fill );

#endif
