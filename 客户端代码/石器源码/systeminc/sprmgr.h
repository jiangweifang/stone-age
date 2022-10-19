/************************/
/*	sprmgr.h			*/
/************************/
#ifndef _SPRMGR_H_
#define _SPRMGR_H_
#include <ddraw.h>
#ifndef _READ16BITBMP
	//�غ��� _READ16BITBMPVARIABLES �Ĳ���������
	#define OLD_GRAPHICS_START	1000000		// ԭ��realbinͼ�������
	#define MAX_GRAPHICS	 	OLD_GRAPHICS_START	// ���ͼ��// ????��?
#else
	#define MAX_GRAPHICS_24		50000		// �߲�ͼ���ͼ��
	#define OLD_GRAPHICS_START	1000000		// ԭ��realbinͼ�������
	#define MAX_GRAPHICS	 	OLD_GRAPHICS_START + MAX_GRAPHICS_24  // ���ͼ��// ????��?
	#define MAX_GRAPHICS_ALPHA	50000		// �߲�ͼalphaͨ�����ͼ��
#endif

#ifdef _READ16BITBMPVARIABLES					//�� _READ16BITBMP ����Ҫ�Ĳ���
	#define MAX_GRAPHICS_24		50000		// �߲�ͼ���ͼ��
	#define OLD_GRAPHICS_START	500000		// ԭ��realbinͼ�������
	#define MAX_GRAPHICS	 	OLD_GRAPHICS_START + MAX_GRAPHICS_24  // ���ͼ��// ??
#endif

#define	DEF_COLORKEY		0				//Ԥ��͸��ɫ// �a����???��k?

#define SURFACE_WIDTH   64 			//��ͼ�õ�source face��//
#define SURFACE_HEIGHT  48			//��ͼ�õ�source face��//

extern LPDIRECTDRAWSURFACE lpBattleSurface;
#ifdef _READ16BITBMP
extern LPDIRECTDRAWSURFACE lpBattleSurfaceSys;
#endif
extern int SurfaceDispCnt;
extern int SurfaceSizeX;
extern int SurfaceSizeY;
extern UINT SurfaceDate;
struct surfaceInfo{
	LPDIRECTDRAWSURFACE lpSurface;
#ifdef _CACHE_SURFACE_
	char *lpCacheData;				//��������
	int palNo;						//��ǰ��ɫ��
	int sizeX;						//���ƿ��
	int sizeY;						//���Ƹ߶�
	BOOL colordepth;					//ʹ�õ�ɫ��
#endif
#ifdef _READ16BITBMP
	BYTE *lpAlphaData;
	BOOL useAlpha;
#endif
#ifdef _NEW_COLOR_
	BOOL useAlpha;
	BYTE *lpAlphaData;				//16λ�ֱ����±����͸������
#endif
	int	bmpNo;						//ͼ�ı��,-1 ����source faceΪ�յ�// ??????�k?
	UINT date;						//��¼���source faceʹ�õ�����
	short offsetX;					
	short offsetY;					
	surfaceInfo	*pNext;				
};

typedef struct surfaceInfo SURFACE_INFO;
typedef struct{
	SURFACE_INFO *lpSurfaceInfo;
#ifdef _READ16BITBMP
	SURFACE_INFO *lpSurfaceInfoSys;
#endif
	short width,height;
	int AlphaFlg;
}SPRITE_INFO;

extern SPRITE_INFO SpriteInfo[];
extern SURFACE_INFO SurfaceInfo[];
#ifdef _READ16BITBMP
extern SURFACE_INFO SurfaceInfoSys[];
#endif
extern int SurfaceCnt;
extern int VramSurfaceCnt;
extern int SysramSurfaceCnt;
extern int SurfaceSearchPoint;
#ifdef _READ16BITBMP
	#ifdef _STONDEBUG_
	extern unsigned int iTotalUseTime;
	extern unsigned int iTotalProcTime;
	extern unsigned int iTotalRunCount;
	extern LARGE_INTEGER tf;
	#endif
#endif

#ifdef _STONDEBUG_		
extern int SurfaceUseCnt;
#endif

BOOL InitOffScreenSurface( void );
void InitSurfaceInfo( void );
void InitSpriteInfo( void );
BOOL LoadBmp( int bmpNo );


#endif
