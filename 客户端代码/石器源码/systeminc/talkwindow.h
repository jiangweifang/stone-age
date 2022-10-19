#ifndef _TALKWINDOW_H_
#define _TALKWINDOW_H_
#include <windows.h>
#include "../systeminc/chat.h"

#define WM_UPDATE_SKIN 0x8000
#define MAX_TALK_WINDOW_LINE 6
#define TALK_WINDOW_SXO	12				// �Ի��Ӵ�������ֵ���ʼx����
#define TALK_WINDOW_SYO 10				// �Ի��Ӵ�������ֵ���ʼy����
#define TALK_WINDOW_SXI	30				// �Ի��Ӵ��������ֵ���ʼx����
#define TALK_WINDOW_SYI 128				// �Ի��Ӵ��������ֵ���ʼy����
#define SKIN_WIDTH 645
#define SKIN_HEIGHT 155
#define SKIN_KIND 5
#define TALK_WINDOW_MAX_CHAT_LINE 40 // �������buffer
#ifdef _STONDEBUG_
#define FACE_SYMBOL_NUM 20				// �����������
#define STORE_SYMBOL_NUM 200			// ��¼����λ������
#define LINE_HEIGHT 20						// �������ʱ���о�
#define SYMBOL_WIDTH 19						// �������ͼ��
#define SYMBOL_HEIGHT 19					// �������ͼ��
#endif

extern BOOL g_bTalkWindow;
extern int g_iCursorCount;

#ifdef _STONDEBUG_
typedef struct _tsFaceSymbol{				// �������
	HDC hDraw;
	HDC hDrawMask;
	HBITMAP hbmpMaskBMP;
	HANDLE hLoadBMP;
	HANDLE hOldLoadBMP;
	HANDLE hOldMaskBMP;
	BOOL bUse;
	char szSymbol[8];					// ����( :) :( :D ...etc)
	char szFaceName[32];			// ����
}FaceSymbol;

typedef struct _tsStoreSymbol{				// ��¼��������ʾ����
	BOOL bUse;
	HDC hDraw;
	HDC hDrawMask;
	int x;
	int y;
}StoreSymbol;
#endif

typedef struct _tsChatBufferLink{
	CHAT_BUFFER ChatBuffer;
	_tsChatBufferLink *prev;
	_tsChatBufferLink *next;
	BOOL bUse;
}ChatBufferLink;

LRESULT CALLBACK TalkWindowProc(HWND hWnd,UINT Message,WPARAM wParam,LPARAM lParam);

class CTalkWindow
{
private:
	HWND m_hWnd;											// ���Ӵ��� HWND
	HWND m_hTalkWindow;								// �Լ��� HWND
	HINSTANCE m_hInstance;						// ���Ӵ��� HINSTANCE
	HANDLE m_hSkin[SKIN_KIND];				// SKIN_KIND->0:base 1:up arrow 2:up arrow hit 3:down arrow 4:down arrow hit
	HANDLE m_hOldSkin[SKIN_KIND];
	HDC m_hdcSkin[SKIN_KIND];					// SKIN_KIND->0:base 1:up arrow 2:up arrow hit 3:down arrow 4:down arrow hit
	HDC m_hdcBackBuffer;							// backbuffer dc for draw
	HBITMAP m_hbmpBackBuffer;					// backbuffer of memory for draw
	HANDLE m_hbmpOldBackBuffer;
	BOOL m_bUpArrowHit;								// �Ͼ�ť�Ƿ���
	BOOL m_bDownArrowHit;							// �¾�ť�Ƿ���
	BOOL m_bScroll;										// �����Ƿ������ھ���
	BOOL m_bInit;											// ��ʼ���ɹ���ʧ��
	ChatBufferLink *m_pCBLHead;				// ָ��Ի�link��һ��link��ָ��
	ChatBufferLink *m_pCBLTail;				// ָ��Ի�link���һ��link��ָ��
	ChatBufferLink *m_pCBLString;			// ָ��Ի�link׼���������ִ���link��ָ��
	ChatBufferLink *m_pCBLView;				// ָ��Ҫ��ʾ�ڻ����ϵ�һ�е��ִ���linkָ��
	ChatBufferLink *m_pCBLViewBottom;	// ָ��Ҫ��ʾ�ڻ��������һ�е��ִ���linkָ��
#ifdef _STONDEBUG_
	FaceSymbol m_fsFaceSymbol[FACE_SYMBOL_NUM];			// �������
	StoreSymbol m_ssStoreSymbol[STORE_SYMBOL_NUM];	// ��¼���Ǳ���ʾ����
	int m_iSymbolCount;
#endif
	int m_iline;
public:
	CTalkWindow(void);
	~CTalkWindow(void);

	void Create();
	void Update(void);
	void LoadSkin(char *szSkinPath);
	void DrawSkin(BOOL bShowCursor);
	void AddString(char *szString,int color);
	HWND GetTalkWindowWND(void) { return m_hTalkWindow;};
	void UpArrowHit(BOOL bHit);
	void DownArrowHit(BOOL bHit);
	void ClearChatBuffer(void);
	void Init(HWND hWnd,HINSTANCE hInstance);
	void Visible(BOOL flag);
	void Release(void);
#ifdef _STONDEBUG_
	void ReadFaceSymbolFile(void);
	void InitFaceSymbol(COLORREF MaskColor);
	void ReleaseFaceSymbol(void);
	void SetToFaceSymbolString(char *szDestString,ChatBufferLink *pCBL,int x,int y);
	void ShowFaceSymbol(void);
#endif
};

extern CTalkWindow TalkWindow;

#endif