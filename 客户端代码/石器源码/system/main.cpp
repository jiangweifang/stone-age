/**** SYSTEM INCLUDE ****/

#include "../systeminc/version.h"
#include "../systeminc/system.h"
#include <winnls32.h>
#include <ime.h>
#include <imm.h>
#include <tlhelp32.h>
#include "../other/caryIme.h"
#include "../resource.h"
#include "../systeminc/netmain.h"
#include "../systeminc/battleMap.h"
#include "../systeminc/battleProc.h"
#include "../systeminc/netmain.h"
#include "../systeminc/login.h"
#include "../systeminc/map.h"
#ifdef _REMAKE_20
#include "../MMOGprotect.h"
#endif
#ifdef _TALK_WINDOW
#include "../systeminc/talkwindow.h"
#endif
#include "../wgs/message.h"
#ifdef _STONDEBUG_
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif
#include "../systeminc/VMProtectSDK.h"
#ifdef _SAHOOK //Syu ADD Hook��ʽ
#include "..\Sa_Hk.h"
#include "../sahook.h"
#define UM_KEYEVENT (WM_APP + 0)
#endif
#include "../systeminc/pc.h"
#include <io.h>
#include <direct.h>
#include   <Nb30.h> 
#pragma comment(lib,"netapi32.lib")
#include  <dbghelp.h> 
#pragma comment(lib,  "dbghelp.lib")

#include <Psapi.h>
#pragma comment(lib,"psapi.lib")


#ifdef _NEWDEBUG_
#include "../cguixmain.h"
#pragma comment(lib,"xcgui_115.lib")
#endif


#ifdef _AIDENGLU_
Landed PcLanded;
int �Ƿ��ص� = FALSE;
int �Ƿ��ص�ս���� = FALSE;
int �Ƿ��ص�AIģʽ = FALSE;
int �Ƿ��ص���� = FALSE;
int �Ƿ��صǺ��� = FALSE;
int �Ƿ��ص����﷽�� = FALSE;
int �Ƿ��ؿ������ = FALSE;
int �Զ���½�Ƿ��� = 0;
#endif
int DISPLACEMENT_X = 160;
int DISPLACEMENT_Y = 120;
int DEF_APPSIZEX = 800;
int DEF_APPSIZEY = 600;

int SCREEN_WIDTH_CENTER = DEF_APPSIZEX / 2;
int SCREEN_HEIGHT_CENTER = DEF_APPSIZEY / 2;

#define REALBIN_DIR		"data\\real_136.bin" 		// REAL.BIN?��? 
#define ADRNBIN_DIR		"data\\adrn_136.bin" 		// ADRN.BIN?��?
#define SPRBIN_DIR		"data\\spr_115.bin" 		// SPR.BIN?��?
#define SPRADRNBIN_DIR	"data\\spradrn_115.bin" 	// SPRADRN.BIN?��?


#ifdef _READ16BITBMP
#define REALTRUEBIN_DIR "data/realtrue_13.bin"
#define ADRNTRUEBIN_DIR "data/adrntrue_5.bin"
#endif
//-------------------------------------------END------------------------
extern int ����;
extern char* GB2312ToBIG5(const char* szGBString);
int MessageBoxNew(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
{
	if (���� == 950){
		char ����[1024] = { 0 };
		char ����1[1024] = { 0 };
		LCMapString(0x804, 0x4000000, lpText, strlen(lpText), ����, 1024);
		LCMapString(0x804, 0x4000000, lpCaption, strlen(lpCaption), ����1, 1024);
		return MessageBox(hWnd, GB2312ToBIG5((const char *)����), GB2312ToBIG5((const char *)����1), uType);
	}
	else{
		return MessageBox(hWnd, lpText, lpCaption, uType);
	}
}

//---------------------------------------------------------------------------//
// ?? ��?????��?�e?                                                 //
//---------------------------------------------------------------------------//
HINSTANCE	hInst;			// ??????????�e?
HWND hWnd;					// ?????????
int	CmdShow;				// WinMain??????????????
LPSTR CmdLine;				// WinMain?????????????????????
HANDLE hMutex;				// �i??�h???????????????
HANDLE hCheckMutex = NULL;	// �����³�ʽ����õ�

//BOOL WindowMode = TRUE;		// ????????
BOOL WindowMode = TRUE;	// ??????????
//	TRUE  : WindowMode
//	FALSE : FullScreen
BOOL NoDelay = FALSE;		// TCP_NODELAY ?��??????add by ringo
#ifdef _NEW_RESOMODE
//������ģʽ( 0 : 640 * 480 , 1 : 320 * 240 ,2 : 640 * 480,  3 : 800 * 600 , 4 : 1024 * 768 ) 
int ResoMode = 3;
#else
int ResoMode = 0;			
#endif
int LowResoCmdFlag = 0;		// ??�T��????????

RECT 	g_clientRect;
POINT g_clientPoint;
RECT 	g_moveRect;


BOOL offlineFlag = FALSE;	// ????????
char DebugKey0[256];		// ???????
char DebugKey1[256];		// ???????
char DebugKey2[256];		// ???????
int g_iMallocCount = 0;


char realBinName[256];
char adrnBinName[256];
char sprBinName[256];
char sprAdrnBinName[256];
#ifdef _READ16BITBMP
char realtrueBinName[256];
char adrntrueBinName[256];
extern BOOL g_bUseAlpha;
#endif
#ifdef _TALK_WINDOW
extern int MouseCursorFlag;
#endif

void GetSettings();
/* ????????�� */
void AnalyzeCmdLine(void);
// ????????��?�v???�L?
void ChangeWindowMode(void);
// ??�T???�@�e??
void SetResoMode(int Mode);

// ?????????�B�l
WNDCLASS wndclass;

HANDLE	hProcessSnap = NULL, hParentProcess = NULL;
DWORD	dwPID;
PROCESSENTRY32 pe32;

#ifdef _TIME_GET_TIME
extern LARGE_INTEGER tickCount;
extern LARGE_INTEGER CurrentTick;
#endif

#ifdef _TALK_WINDOW
CTalkWindow TalkWindow;
#endif


char ������[256];
int getMAC(char * mac)
{
	NCB ncb;
	typedef struct _ASTAT_
	{
		ADAPTER_STATUS   adapt;
		NAME_BUFFER   NameBuff[30];
	}ASTAT, *PASTAT;

	ASTAT Adapter;

	typedef struct _LANA_ENUM
	{
		UCHAR   length;
		UCHAR   lana[MAX_LANA];
	}LANA_ENUM;

	LANA_ENUM lana_enum;
	UCHAR uRetCode;
	memset(&ncb, 0, sizeof(ncb));
	memset(&lana_enum, 0, sizeof(lana_enum));
	ncb.ncb_command = NCBENUM;
	ncb.ncb_buffer = (unsigned char *)&lana_enum;
	ncb.ncb_length = sizeof(LANA_ENUM);
	uRetCode = Netbios(&ncb);

	if (uRetCode != NRC_GOODRET)
		return uRetCode;

	for (int lana = 0; lana < lana_enum.length; lana++)
	{
		ncb.ncb_command = NCBRESET;
		ncb.ncb_lana_num = lana_enum.lana[lana];
		uRetCode = Netbios(&ncb);
		if (uRetCode == NRC_GOODRET)
			break;
	}

	if (uRetCode != NRC_GOODRET)
		return uRetCode;

	memset(&ncb, 0, sizeof(ncb));
	ncb.ncb_command = NCBASTAT;
	ncb.ncb_lana_num = lana_enum.lana[0];
	strcpy((char*)ncb.ncb_callname, "*");
	ncb.ncb_buffer = (unsigned char *)&Adapter;
	ncb.ncb_length = sizeof(Adapter);
	uRetCode = Netbios(&ncb);

	if (uRetCode != NRC_GOODRET)
		return uRetCode;

	sprintf(mac, "%02X-%02X-%02X-%02X-%02X-%02X",
		Adapter.adapt.adapter_address[0],
		Adapter.adapt.adapter_address[1],
		Adapter.adapt.adapter_address[2],
		Adapter.adapt.adapter_address[3],
		Adapter.adapt.adapter_address[4],
		Adapter.adapt.adapter_address[5]);

	return 0;
}

char ��������[512];

void ��ȡ������()
{
	HANDLE m_hMapFile = OpenFileMapping( //��ù����ڴ���
		FILE_MAP_READ | FILE_MAP_WRITE,
		FALSE,
#ifdef _SA_VERSION_25
		"shiqies");
#endif

	if (m_hMapFile == NULL){
		HANDLE m_hMapFile = CreateFileMapping(  //����һ�������Ĺ����ڴ�
			(HANDLE)0xFFFFFFFF, //0xFFFFFFFF��ʾ����һ�����̼乲��Ķ���
			NULL,
			PAGE_READWRITE,  //��д����
			0,
			1032,       //���������С4096
#ifdef _SA_VERSION_25
		"shiqies");
#endif

		char *str = (char *)MapViewOfFile( //ӳ�䵽�����̵ĵ�ַ�ռ�
			m_hMapFile,
			FILE_MAP_ALL_ACCESS,
			0,
			0,
			0);
		memset(str, 0, 1032);
		memset(��������, 0, 512);
		char userName[MAX_PATH];
		DWORD size = MAX_PATH;
		char mac[64];
		GetComputerName(userName, &size);
		getMAC(mac);
		sprintf_s(��������, "%s%s", mac, userName);
		memcpy(str, ��������, 512);
	}
	else{
		char *str = (char *)MapViewOfFile( //ӳ�䵽�����̵ĵ�ַ�ռ�
			m_hMapFile,
			FILE_MAP_ALL_ACCESS,
			0,
			0,
			0);
		memcpy(��������, str, 512);
	}
}

BOOL �ļ��ж�(char * path,char * name)
{
	char �ļ�·��[256];
	sprintf(�ļ�·��,"%s%s",path,name);
	BOOL ret = (access(�ļ�·��,0)==0?TRUE:FALSE);
	if(ret){
		;//MessageBox(NULL,�ļ�·��,"ʯ��ʱ��",0);
	}
	return ret;
}


BOOL ��ⰴ��(char *path)
{
	if(�ļ��ж�(path,"QMScript") ||
		�ļ��ж�(path,"Recorder.exe") ||
		�ļ��ж�(path,"QMColorActionCtl.ocx") ||
		�ļ��ж�(path,"ShieldModule.dat") ||
		�ļ��ж�(path,"qmacro.ini") ||
		�ļ��ж�(path,"wqm.exe") || 
		�ļ��ж�(path,"Fairy_Ape")||
		�ļ��ж�(path,"LAScriptX.dll")||
		�ļ��ж�(path,"mly.dll")||�ļ��ж�(path,"v5_hook.dll")||�ļ��ж�(path,"v5_Log.dll")||�ļ��ж�(path,"v5_Process_Manager.dll")
		){
		return TRUE;
	}else{
		return FALSE;
	}
}



void �������()
{
	char szProcessName[MAX_PATH];
	HMODULE hMods[4096];
	HANDLE hProcess;
	DWORD aProcesses[4096], cbNeeded, cbMNeeded;
	char ·��[256];
	int j;
	if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) ) return;

	for(int i=0; i< (int) (cbNeeded / sizeof(DWORD)); i++)
	{
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, aProcesses[i]);
		BOOL   bret=EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbMNeeded);
		if(bret){
			DWORD dwret=GetModuleFileNameEx( hProcess, hMods[0], szProcessName,sizeof(szProcessName));  
			CloseHandle(hProcess); 
			if(dwret==0){
				break;
			}else{
				int i=strlen(szProcessName);
				for(i;i>=0;i--){
					if(szProcessName[i]== '\\' ){
						break;
					}
				}
				memcpy(·��,szProcessName,i+1);
				·��[i+1]=0;
				if(��ⰴ��(·��)){
					ExitProcess(NULL);
				}
			}
		}
	}
	return;
}

BOOL IsContainsProcess(char* strProName, BOOL �ж� = 1)
{
	PROCESSENTRY32  pe32;   //����ṹ�������������̵���Ϣ
	pe32.dwSize = sizeof(pe32);   //����С

	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//��������

	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		//MessageBox("���̿���ʧ��","��ʾ",MB_OK);
		exit(1);
	}

	//�������п���
	BOOL bMore = ::Process32First(hProcessSnap, &pe32);
	while (bMore)
	{
		if (�ж� == 1){
			if (strcmp(strProName, pe32.szExeFile) == 0)
			{
				return TRUE;  //������ڸý��̣��򷵻�TRUE
				bMore = FALSE;//ֹͣѭ��
			}
			else
			{
				bMore = ::Process32Next(hProcessSnap, &pe32);
			}
		}
		else{
			if (strstr(pe32.szExeFile, strProName))
			{
				return TRUE;  //������ڸý��̣��򷵻�TRUE
				bMore = FALSE;//ֹͣѭ��
			}
			else
			{
				bMore = ::Process32Next(hProcessSnap, &pe32);
			}
		}
	}
	//ɨβ
	CloseHandle(hProcessSnap);
	return FALSE;
}
DWORD __forceinline IsInsideVPC_exceptionFilter(LPEXCEPTION_POINTERS ep)
{
	PCONTEXT ctx = ep->ContextRecord;

	ctx->Ebx = -1; // Not running VPC
	ctx->Eip += 4; // skip past the "call VPC" opcodes
	return EXCEPTION_CONTINUE_EXECUTION; // we can safely resume execution since we skipped faulty instruction
}

// high level language friendly version of IsInsideVPC()
bool IsInsideVPC()
{
	bool rc = false;

	__try
	{
		_asm push ebx
		_asm mov  ebx, 0 // Flag
		_asm mov  eax, 1

		_asm __emit 0Fh
		_asm __emit 3Fh
		_asm __emit 07h
		_asm __emit 0Bh

		_asm test ebx, ebx
		_asm setz[rc]
			_asm pop ebx
	}
	__except (IsInsideVPC_exceptionFilter(GetExceptionInformation()))
	{
	}

	return rc;
}

BOOL ���WARE()
{
	HKEY key;
	unsigned char buffer[512];
	DWORD len;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\ControlSet001\\Services\\Disk\\Enum", 0, KEY_READ, &key) == ERROR_SUCCESS){
		memset(buffer, 0, 512);
		len = 512;
		DWORD lpReserved = 0;
		DWORD lpType = REG_SZ;
		if (RegQueryValueEx(key, "0", NULL, &lpType, buffer, &len) == 0){
			extern int strncmpi(char *s1, char *s2, int len);
			_strlwr_s((char *)buffer, strlen((char *)buffer) + 1);
			if (strstr((char *)buffer, "virtual") || strstr((char *)buffer, "vmware") || strstr((char *)buffer, "vbox")){
				return TRUE;
			}
		}
		RegCloseKey(key);
	}
	return FALSE;
}

class A;

void fcn(A*);

class A
{
public:
	virtual void f() = 0;
	A() { fcn(this); }
};

class B : A
{
	void f() { }
};

void fcn(A* p)
{
	p->f();
}

int PureVirtualFunc()
{
	B b;
	int n = 0;
	return 0;
}

BOOL IsTheSelfRun(char *str)
{
	HANDLE m_hMutex = CreateMutex(NULL,FALSE, str);
	if(m_hMutex)
	{
		if(GetLastError() == ERROR_ALREADY_EXISTS)
		{
			CloseHandle(m_hMutex);
			return TRUE;
		}
	}
	return FALSE;
}

void CreateCompatibleDEVMODE(DEVMODE* pdm, DWORD BitsPerPixel, DWORD Width, DWORD Height, DWORD Frequency)
{
  ZeroMemory(pdm, sizeof(DEVMODE));
  pdm->dmSize = sizeof(DEVMODE);

  if (BitsPerPixel)
  {
    pdm->dmBitsPerPel = BitsPerPixel;
    pdm->dmFields |= DM_BITSPERPEL;
  }

  if (Width)
  {
    pdm->dmPelsWidth = Width;
    pdm->dmFields |= DM_PELSWIDTH;
  }

  if (Height)
  {
    pdm->dmPelsHeight = Height;
    pdm->dmFields |= DM_PELSHEIGHT;
  }

  if (Frequency)
  {
    pdm->dmDisplayFrequency = Frequency;
    pdm->dmFields |= DM_DISPLAYFREQUENCY;
  }
}



int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _NEWDEBUG_

	HMODULE hMod ;
	hMod = GetModuleHandle("xcgui_115.dll");
	if(!hMod)
	{
		hMod= LoadLibrary("xcgui_115.dll");
		if(!hMod){
			exit(0);
		}
	}
	cguixmain("cmdstrtw",123);
#endif
#ifdef _NEWFONT_
	AddFontResource("./data/font/msjh.ttf");
#else 
//	AddFontResource("./data/font/msjh.ttf");
#endif
#ifdef _CMD_MODE
	extern void InitConsoleWindow(void)  ;
	InitConsoleWindow();
#endif
	
#ifndef SWITCH_MODE
	extern int displayBpp;
	HDC hDcDest = GetDC(hWnd);
	displayBpp = GetDeviceCaps(hDcDest, BITSPIXEL);
	ReleaseDC(hWnd, hDcDest);
	if(displayBpp != 32){
		DEVMODE dm;
		CreateCompatibleDEVMODE(&dm, 32, GetDeviceCaps(hDcDest, HORZRES),GetDeviceCaps(hDcDest, VERTRES), GetDeviceCaps(hDcDest, VREFRESH));
		ChangeDisplaySettings(&dm, 0);
		char buf[256];
		GetModuleFileName(NULL,buf,sizeof(buf));
		STARTUPINFO StartInfo;
		PROCESS_INFORMATION procStruct;
		memset(&StartInfo, 0, sizeof(STARTUPINFO));
		StartInfo.cb = sizeof(STARTUPINFO);
		CreateProcess(buf," OpenClient",NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&StartInfo,&procStruct);
		Sleep(3000);
		return FALSE;
	}
#endif
	SetErrorMode(SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
	CreateMutex(NULL,FALSE, SA_MUTE);

#ifdef _SA_VERSION_25
	if (_access(".\\data", 6) == -1)
		_mkdir(".\\data");
	if (_access(".\\data\\chardata", 6) == -1)
		_mkdir(".\\data\\chardata");
#endif

#ifdef _NODEBUG_
	VMProtectBegin("jiance111");
	extern void �������();
	�������();
	if (
		(IsContainsProcess("VBoxTray.exe")) ||
		(IsContainsProcess("SbieSvc.exe")) ||
		(IsContainsProcess("SbieCtrl.exe")) ||
		(IsContainsProcess("VBoxService.exe")) ||
		(IsContainsProcess("VMwareUser.exe")) ||
		(IsContainsProcess("VMwareTray.exe")) ||
		(IsContainsProcess("VMUpgradeHelper.exe"))||
		(IsContainsProcess("vmtoolsd.exe")) ||
		(IsContainsProcess("vmacthlp.exe")) || 
		IsInsideVPC()|| 
		IsContainsProcess("�ര��", 0) ||
		IsContainsProcess("����", 0)||
		IsContainsProcess("����", 0)
		){
		return FALSE;
	}
	if (���WARE()){
		return FALSE;
	}
	VMProtectEnd();
#endif
	���� = GetACP();
	if (���� == 950)
	{
		strcpy(������, GB2312ToBIG5(DEF_APPNAME));
	}
	��ȡ������();
	hInst = hInstance;
	CmdShow = nCmdShow;
	CmdLine = lpCmdLine;
#ifdef _REMAKE_20
#ifndef _STONDEBUG_
	if(����==950)
		hMutex = CreateMutex( NULL, TRUE, ������ );
	else
		hMutex = CreateMutex( NULL, TRUE, DEF_APPNAME );
	if(GetLastError() == ERROR_ALREADY_EXISTS){
		MessageBoxNew(hWnd,"StoneAge�Ѿ����ˣ�","ȷ��",MB_OK | MB_ICONSTOP);
		return FALSE;
	}
#endif
#endif
	// ����һ���������,�ø��³�ʽ�����ж��Ƿ���ʯ������ִ��
	hCheckMutex = CreateMutex(NULL, FALSE, "CheckForUpdate");

#ifdef _STONDEBUG_
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

#ifdef __NEW_CLIENT
	dwPID = GetCurrentProcessId();
	if( INVALID_HANDLE_VALUE == (hProcessSnap=CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, NULL)))
		return 0;
	{
		pe32.dwSize = sizeof(PROCESSENTRY32);
		if( Process32First( hProcessSnap, &pe32)){ 
			do{
				if( pe32.th32ProcessID == dwPID){
					dwPID = pe32.th32ParentProcessID;
					break;
				}
			}while( Process32Next( hProcessSnap, &pe32));
		}
	}
#endif

#ifdef _DEFENSETOOENNUM_
#ifdef _VMP_
	VMProtectBegin("xiankai");
#endif
	FILE* tempfile=NULL;
	int ds=0;
	char strname[128];
	
	BOOL checkclientflg=FALSE;
	char *pathvar;
	pathvar = getenv("TEMP");
	for(ds=0;ds<_DEFENSETOOENNUM_;ds++){
#ifdef _SA_VERSION_25
		sprintf(strname,"%s\\Etemp%d",pathvar,ds);
#endif
		tempfile = fopen(strname,"w");
		if(tempfile) fclose(tempfile);
		HANDLE file_handle;
		file_handle = CreateFile(strname,
					  GENERIC_READ,  
					  0,  
					  NULL,  
					  OPEN_EXISTING,  
					  NULL,  
					  NULL);  
		if(INVALID_HANDLE_VALUE != file_handle){
			if(INVALID_FILE_SIZE != (DWORD)file_handle){
				checkclientflg=TRUE;
				break;
			}
		} 
	}
//	int xiangeshu=0;
//	int ds=0;
//	char strname[127];
//	for(ds=0;ds <_DEFENSETOOENNUM_ ;ds++){
//		sprintf(strname,"%s%d",SA_MUTE,ds);
//		if(IsTheSelfRun(strname)) xiangeshu++;
//		else break;
//	}
	if(!checkclientflg) {
	//	sprintf_s(strname, "��Ϸ����%d����", _DEFENSETOOENNUM_);
		sprintf_s(strname, "��Ϸ����2����");
#ifdef _VMP_
		MessageBoxNew(NULL,VMProtectDecryptStringA(strname), DEF_APPNAME, MB_OK | MB_ICONSTOP);
#else
		MessageBoxNew(NULL,strname, DEF_APPNAME, MB_OK | MB_ICONSTOP);
#endif
		return FALSE;
	}
#ifdef _VMP_
	VMProtectEnd();
#endif
#endif

	if (!hPrevInstance){
		wndclass.style = CS_BYTEALIGNCLIENT | CS_DBLCLKS;
		wndclass.lpfnWndProc = WindMsgProc;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hInstance = hInstance;
		wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(SA_ICON));
		wndclass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(SA_MOUSE1));
		wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wndclass.lpszMenuName = NULL;
		if (���� == 950)
			wndclass.lpszClassName = ������;
		else
			wndclass.lpszClassName = DEF_APPNAME;
		if (!RegisterClass(&wndclass)){
			MessageBoxNew(NULL, "��ʼ���Ӵ�ʧ�ܣ�\n����ִ�����°�װ��Ǣѯ�ͷ���Ա��",
				"ȷ��", MB_OK | MB_ICONSTOP);
			return FALSE;
		}
	}
#ifdef _TIME_GET_TIME
	QueryPerformanceFrequency(&tickCount);
	tickCount.QuadPart = tickCount.QuadPart / 1000;
#endif
	strcpy(realBinName, REALBIN_DIR);
	strcpy(adrnBinName, ADRNBIN_DIR);
	strcpy(sprBinName, SPRBIN_DIR);
	strcpy(sprAdrnBinName, SPRADRNBIN_DIR);
#ifdef _READ16BITBMP
	strcpy(realtrueBinName,REALTRUEBIN_DIR);
	strcpy(adrntrueBinName,ADRNTRUEBIN_DIR);
#endif
	AnalyzeCmdLine();
	memset(lpCmdLine, 0, strlen(lpCmdLine));
	SetResoMode(ResoMode);
	ChangeWindowMode();
#ifdef _TALK_WINDOW
	TalkWindow.Init(hWnd,hInstance);
	if(g_bTalkWindow) TalkWindow.Create();
#endif

#ifdef _NEWSHOP_
	extern void �̳ǳ�ʼ��();
	�̳ǳ�ʼ��();
#endif
#ifdef _AIDENGLU_
	PcLanded.���� = PcLanded.���� = PcLanded.С�� = PcLanded.��ģ = -1;
	PcLanded.�Ƿ��Զ����� = PcLanded.�Ƿ��Զ����� = PcLanded.���﷽�� = PcLanded.��½��ʱʱ�� = FALSE;
	memset(PcLanded.��½��������, 0, 4 * 32);
#endif


	GameMain();

#ifdef __NEW_CLIENT
	CloseHandle( hProcessSnap);
#endif

#ifdef SWITCH_MODE
	extern DEVMODE g_OriginalMode;
	if( g_OriginalMode.dmSize != 0){
		DEVMODE	DevMode;
		DevMode.dmSize = sizeof(DEVMODE);
		EnumDisplaySettings( NULL, ENUM_CURRENT_SETTINGS, &DevMode);
		if( DevMode.dmPelsWidth!=g_OriginalMode.dmPelsWidth || DevMode.dmPelsHeight!=g_OriginalMode.dmPelsHeight || DevMode.dmBitsPerPel!=g_OriginalMode.dmBitsPerPel){
			g_OriginalMode.dmFields = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
			ChangeDisplaySettingsEx( NULL, &g_OriginalMode, NULL, CDS_UPDATEREGISTRY, NULL);
		}
	}
#endif
#ifdef _REMAKE_20
#ifndef _STONDEBUG_
	QuitingInputScript();
#endif
	QuitRestore();
#endif
#ifdef _STONDEBUG_
	if(g_iMallocCount != 0){
		char MSG[256];
		sprintf_s(MSG,"g_iMallocCount = %d",g_iMallocCount);
		MessageBoxNew( NULL,MSG,"ȷ��", MB_OK | MB_ICONSTOP );
	}
#endif

	ReleaseMutex(hCheckMutex);
	return FALSE;
}



// ???????�� ***********************************************************/
void DebugKey(char *str)
{
	char *work;
	int i = 0;

	// ????????????? key0: ?????
	if ((work = strstr(str, "KEY0:")))
	{
		work += 5;	// ��??????????????��??
		// : ????????
		while (*work != ':'){
			DebugKey0[i] = *work++;
			i++;
			if (i == 255){
				i = 0;
				break;
			}
		}
	}
	DebugKey0[i] = NULL;	// ���Z??
	i = 0;
	// ????????????? key1: ?????
	if ((work = strstr(str, "KEY1:")))
	{
		work += 5;	// ��??????????????��??
		// : ????????
		while (*work != ':'){
			DebugKey1[i] = *work++;
			i++;
			if (i == 255){
				i = 0;
				break;
			}
		}
	}
	DebugKey1[i] = NULL;	// ���Z??
	i = 0;
	// ????????????? key1: ?????
	if ((work = strstr(str, "KEY2:")))
	{
		work += 5;	// ��??????????????��??
		// : ????????
		while (*work != ':'){
			DebugKey2[i] = *work++;
			i++;
			if (i == 255){
				i = 0;
				break;
			}
		}
	}
	DebugKey2[i] = NULL;	// ���Z??
}


void AnalyzeCmdLine(void)
{
	char *addr;
#ifdef _ZHENGSHIKAIFU_
#ifdef _VMP_
	VMProtectBegin("AnalyzeCmdLine");
#endif
	if (!(addr = strstr(CmdLine, "OpenClient"))){
		MessageBoxNew(NULL, "��ʹ����������½��Ϸ", "ȷ��", MB_OK | MB_ICONSTOP);
		exit(0);
	}
#ifdef _VMP_
	VMProtectEnd();
#endif
#endif
	if (addr = strstr(CmdLine, "realbin:"))
		sprintf_s(realBinName, "data\\real_%d.bin", atoi(addr + strlen("realbin:")));
	if (addr = strstr(CmdLine, "adrnbin:"))
		sprintf_s(adrnBinName, "data\\adrn_%d.bin", atoi(addr + strlen("adrnbin:")));
	if (addr = strstr(CmdLine, "sprbin:"))
		sprintf_s(sprBinName, "data\\spr_%d.bin", atoi(addr + strlen("sprbin:")));
	if (addr = strstr(CmdLine, "spradrnbin:"))
		sprintf_s(sprAdrnBinName, "data\\spradrn_%d.bin", atoi(addr + strlen("spradrnbin:")));
#ifdef _READ16BITBMP
	if(addr = strstr(CmdLine,"realtrue:"))
		sprintf_s(realtrueBinName,"data\\realtrue_%d.bin",atoi(addr+strlen("realtrue:")));
	if(addr = strstr(CmdLine,"adrntrue:"))
		sprintf_s(adrntrueBinName, "data\\adrntrue_%d.bin", atoi(addr+strlen("adrntrue:")) );
	if(strstr(CmdLine,"usealpha")) g_bUseAlpha = TRUE;
#endif
#ifdef _REMAKE_20
#ifdef _STONDEBUG_
	if( strstr( CmdLine, "windowmode" ) ) WindowMode = TRUE;
#endif
#else
	if (strstr(CmdLine, "windowmode")) WindowMode = TRUE;
#endif
	if (strstr(CmdLine, "nodelay"))
		NoDelay = FALSE;

	if (strstr(CmdLine, "offline")){
		ProcNo = PROC_GAME;
		offlineFlag = TRUE;
	}
	else{
#ifndef _80_LOGIN_PLAY
		ProcNo = PROC_ID_PASSWORD;
#else
		ProcNo = PROC_80_LOGIN;
#endif
		offlineFlag = FALSE;
	}
	if (strstr(CmdLine, "PROC_OHTA_TEST")){
		ProcNo = PROC_OHTA_TEST;
		offlineFlag = TRUE;
	}
	if (strstr(CmdLine, "PROC_TAKE_TEST")){
		ProcNo = PROC_TAKE_TEST;
		offlineFlag = TRUE;
	}
	if (strstr(CmdLine, "PROC_DWAF_TEST")){
		ProcNo = PROC_DWAF_TEST;
		offlineFlag = TRUE;
	}
	if (strstr(CmdLine, "PROC_BATTLE")){
		ProcNo = PROC_BATTLE;
		offlineFlag = TRUE;
	}
	if (strstr(CmdLine, "sprview")){
		ProcNo = PROC_SPR_VIEW;
		offlineFlag = TRUE;
	}
	if (strstr(CmdLine, "animview")){
		ProcNo = PROC_ANIM_VIEW;
		offlineFlag = TRUE;
	}
	if (strstr(CmdLine, "setest")){
		ProcNo = PROC_SE_TEST;
		offlineFlag = TRUE;
	}
	//	if( strstr( CmdLine, "encountoff" ) ){
	//		EncountOffFlag = TRUE;
	//	}
	if (strstr(CmdLine, "lowreso")){
		ResoMode = 1;
	}

#ifdef _LOG_MSG
	if( strstr( CmdLine, "RECVDATA:" ) ){
		char *pt = strstr( CmdLine, "RECVDATA:" )+9;
		char *name;
		int i;
		name = debugLogFileName;
		for( i = 0; i < 255; i++ ){
			if( *pt != ' ' && *pt != '\0' && *pt != '\t' )
				*name++ = *pt++;
			else
				break;
		}
		*name = '\0';
	}
#endif
	DebugKey(CmdLine);
}

void ChangeWindowMode(void)
{
	RECT clientRect;
	DWORD windowStyle;
	ChangeMode(WindowMode);
	if (WindowMode){
		windowStyle = WS_MINIMIZEBOX | WS_SYSMENU |
			//WS_THICKFRAME |
			WS_CAPTION | WS_OVERLAPPED;
	}
	else{
		windowStyle = WS_VISIBLE | WS_POPUP;
	}
	SetRect(&clientRect, 0, 0, lpDraw->xSize, lpDraw->ySize);
	AdjustWindowRectEx(&clientRect, windowStyle, FALSE, NULL);
	if (hWnd == NULL){
		if (���� == 950)
			hWnd = CreateWindowEx(NULL,
			������,
			������,
			windowStyle,
			//CW_USEDEFAULT, 
			//CW_USEDEFAULT, 
			0,
			0,
			clientRect.right - clientRect.left,
			clientRect.bottom - clientRect.top,
			NULL,
			NULL,
			hInst,
			NULL);

		else
			hWnd = CreateWindowEx(NULL,
			DEF_APPNAME,
			DEF_APPNAME,
			windowStyle,
			//CW_USEDEFAULT, 
			//CW_USEDEFAULT, 
			0,
			0,
			clientRect.right - clientRect.left,
			clientRect.bottom - clientRect.top,
			NULL,
			NULL,
			hInst,
			NULL);
	}
	else{
		// ??????????��?
		SetWindowLong(hWnd, GWL_STYLE, windowStyle);
		// ?��????????����
		ShowWindow(hWnd, CmdShow);
		// ???????�t?????��?
		SetWindowPos(hWnd,
			HWND_NOTOPMOST,
			0,
			0,
			clientRect.right - clientRect.left,
			clientRect.bottom - clientRect.top,
			//SWP_SHOWWINDOW );
			SWP_FRAMECHANGED);
	}
	// ?��????????����
	ShowWindow(hWnd, CmdShow);
	// ??????����?��
	UpdateWindow(hWnd);
}

// ?????????????? **********************************************************/
void RecoverDirectDraw(void)
{
	// DirectDraw ?��
	ReleaseDirectDraw();
	// ??�T???�@�e
	SetResoMode(ResoMode);
	// DirectDraw ???
	if (InitDirectDraw() == FALSE){
		MessageBoxNew(hWnd, "Direct ��ʼ��ʧ�ܣ�", "ȷ��", MB_OK | MB_ICONSTOP);
		// ???????? WM_CLOSE ??????????
		PostMessage(hWnd, WM_CLOSE, 0, 0L);
	}
	// ????????��?�v?
	//ChangeWindowMode();
	// ??????????????�� 
	InitOffScreenSurface();
	// ???????
	if (InitPalette() == FALSE){
		MessageBoxNew(hWnd, "ɫ�� ��ʼ��ʧ�ܣ�", "ȷ��", MB_OK | MB_ICONSTOP);
		PostMessage(hWnd, WM_CLOSE, 0, 0L);
	}
	// ??????��????????????????��
	if (ProcNo == PROC_BATTLE){
		// ???????
		DispBuffer.DispCnt = 0;
		FontCnt = 0;
#ifdef _NEW_RESOMODE
		//drawMap();
		ReadBattleMap(BattleMapNo);
#else
		ReadBattleMap( BattleMapNo );
#endif
		// ???????????????
		ClearBackSurface();
		// ????????????????
#ifdef __SKYISLAND
		fastDrawTileFlag = 0;
		PutBmp();
		fastDrawTileFlag = 1;
#else
		PutBmp();	
		// ??????????????????????
		lpBattleSurface->BltFast( 0, 0, lpDraw->lpBACKBUFFER, NULL, DDBLTFAST_WAIT );
#endif
		// ???????
		DispBuffer.DispCnt = 0;
		FontCnt = 0;
		// ????????
		NowTime = TimeGetTime();
	}
	else
	if (fastDrawTile && ProcNo == PROC_GAME)
	{
		repairMap();	// ????��?��?
	}
	// ??????????????
	if (lpDraw->lpPALETTE != NULL){
		// ??????????
		if (WindowMode){
			// ?��??????????��??
			lpDraw->lpPALETTE->SetEntries(0, 0, 256, Palette);
		}
	}
	// ???????�V?????
	mouse.state = MOUSE_NO_CRICK;
	mouse.onceState = MOUSE_NO_CRICK;
	// ???�w?��????
	NowTime = TimeGetTime();
}
//---------------------------------------------------------------------------//
// ?? ��????????????                                                     //
// ?? ��??                                                               //
//---------------------------------------------------------------------------//
BOOL SystemTask(void)
{
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
		if (msg.message == WM_QUIT)
			return FALSE;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return TRUE;
}

//---------------------------------------------------------------------------//
// ?? ��??????????????                                       //
// ?? ��HWND hWnd:     ??????����????                            //
//        UINT Message:  ????��??????                              //
//        WPARAM wParam: ????��??????���K�ѩ�?                    //
//        LPARAM lParam: ????��??????���K�ѩ�?                    //
//---------------------------------------------------------------------------//
#ifdef _REMAKE_20
extern short mouseCursorMode;
#endif
LRESULT CALLBACK WindMsgProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message){
#ifdef _REMAKE_20
	case WM_TIMER:
		// ����8253��Ƭ��clock 
		RestoreCounter(1196);
		break;
#endif
		/** ??????????? *****************************************************/
	case WM_ACTIVATE:	// ??????????????????��??????????
#ifdef SA_25
		static BOOL bInactive = FALSE;
		if( bInactive && (LOWORD(wParam) == WA_ACTIVE || LOWORD(wParam) == WA_CLICKACTIVE)){
			SetWindowPos( hWnd, NULL, 0, -100, 0, 0, NULL);
			ShowWindow( hWnd, SW_MINIMIZE);
			if( lpDraw && lpDraw->lpDD2){
				lpDraw->lpDD2->SetCooperativeLevel( hWnd ,DDSCL_NORMAL);
				ReleaseDirectDraw();
			}
		}
		if( LOWORD(wParam) == WA_INACTIVE){
			bInactive = TRUE;
			cleanupNetwork();
			PostQuitMessage( 0);
		}
		break;
#endif
		// ?????????????????
		if ((wParam == WA_ACTIVE || wParam == WA_CLICKACTIVE) && lpDraw != NULL){

			// ?????? LOST ?????
			if (CheckSurfaceLost() == TRUE){
				// ??????????????
				RecoverDirectDraw();
			}
			// ??????????????
			if (lpDraw->lpPALETTE != NULL){
				// ??????????
				if (WindowMode){
					// ?��??????????��??
					lpDraw->lpPALETTE->SetEntries(0, 0, 256, Palette);
				}
			}
		}
		//???????????����
		//?????�ϣ�??
		if (keyboad_flg == TRUE){		//?????�ϣ�??
			// ????????????????
			if (pDInputDevice != NULL){
				// ??????��???????????
				if (wParam == WA_INACTIVE){
					// DInput �_��
					DInputActiveFlag = FALSE;
					// ??????????
					for (int i = 0; i < 256; i++) di_key[i] = 0;
					pDInputDevice->Unacquire();
				}
				else{
					// DInput ??
					DInputActiveFlag = TRUE;
					pDInputDevice->Acquire();
				}
			}
		}

		//????????�ϣ�??
		if (joy_flg == TRUE){
			// ???????????????????
			if (pDInputDevice2 == NULL)
				break;

			// ??????��???????????
			if (wParam == WA_INACTIVE){
				// DInput �_��
				DInputActiveFlag = FALSE;
				pDInputDevice2->Unacquire();
			}
			else{
				// DInput ??
				DInputActiveFlag = TRUE;
				pDInputDevice2->Acquire();
			}
		}
		break;
	case WM_CLOSE:				// ?????��????
		DestroyWindow(hWnd);	// ??????��????�i??
		// WM_DESTROY ??????????
		break;
	case WM_DESTROY:			// ??????��??????

		PostQuitMessage(0);	// WM_QUIT ???????? ( ???��? )
		break;
#ifdef _REMAKE_20		
#ifndef _STONDEBUG_			
	case WM_ACTIVATEAPP:
		// ������е�����Ӵ�,�뿪��Ϸ
		if(!wParam){
			SendMessage(hWnd,WM_CLOSE,0,0);
		}
		break;
#endif
#endif

#if 0			
	case WM_PALETTECHANGED:		// ?????��??????
		// DirectDraw??????????
		if( lpDraw == NULL ) break;
		// ??????????????
		if( lpDraw->lpPALETTE == NULL ) break;
		// ??????????
		//if( WindowMode ){
		// ?��??????????��??
		lpDraw->lpPALETTE->SetEntries( 0, 0, 256, Palette );
		//}
		break;
		//if( (HWND)wParam == hWnd )  break;

	case WM_PALETTEISCHANGING:		// ?????��??????
		// DirectDraw??????????
		if( lpDraw == NULL ) break;
		// ??????????????
		if( lpDraw->lpPALETTE == NULL ) break;
		// ??????????
		//if( WindowMode ){
		// ?��??????????��??
		lpDraw->lpPALETTE->SetEntries( 0, 0, 256, Palette );
		//}
		break;

	case WM_QUERYNEWPALETTE:	// ????��????????????????????

		// DirectDraw??????????
		if( lpDraw == NULL ) break;
		// ??????????????
		if( lpDraw->lpPALETTE == NULL ) break;

		// ??????????
		//if( WindowMode ){
		// ?��??????????��??
		lpDraw->lpPALETTE->SetEntries( 0, 0, 256, Palette );
		//}

		break;
#endif			

		/** ??�V?????? *****************************************************/

	case WM_KEYDOWN:	// ??�V???

		if (SurfaceBusyFlag == TRUE){
			SurfaceBusyFlag = FALSE;
			RecoverDirectDraw();
		}

		switch (wParam){
		case VK_LEFT:
			KeyboardLeft();
			break;

		case VK_RIGHT:
			KeyboardRight();
			break;

		case VK_RETURN:
			KeyboardReturn();
			break;

		case VK_BACK:
			if (joy_con[1] & JOY_RSHIFT || joy_con[1] & JOY_LSHIFT){
				if (pNowStrBuffer != NULL){
					pNowStrBuffer->cnt = 0;
					pNowStrBuffer->buffer[0] = NULL;
				}
			}
			else{
				KeyboardBackSpace();
			}

			break;

		case VK_DELETE:	
			ClearChatBuffer();
#ifdef _TALK_WINDOW
			TalkWindow.ClearChatBuffer();
			TalkWindow.Update();
#endif
			break;

		case VK_ESCAPE: 
			break;
		}
#ifdef _TALK_WINDOW
		if(g_bTalkWindow) TalkWindow.Update();
#endif
		break;
#ifdef _REMAKE_20
	case WM_HOTKEY:
		// ������е�����Ӵ�,�뿪��Ϸ
		SendMessage(hWnd,WM_CLOSE,0,0);	
		break;
#endif			
	case WM_SYSKEYDOWN:	// ALT????????
		// ???????????
		if (SurfaceBusyFlag == TRUE){
			SurfaceBusyFlag = FALSE;
			MessageBoxNew(hWnd, "SurfaceBusyFlag error!", "ȷ��", MB_OK | MB_ICONSTOP);
			RecoverDirectDraw();
		}
		switch (wParam){
		case VK_RETURN:
#ifdef _REMAKE_20
#ifndef _STONDEBUG_
			// �����Ӵ�ģʽ�뿪��Ϸ
			SendMessage(hWnd,WM_CLOSE,0,0);
			break;
#endif
#else
			// ?��??�I??
			if (BackBufferDrawType == DRAW_BACK_PRODUCE) break;

			// DirectDraw??????????
			if (lpDraw == NULL) break;

			// ???????????��?
			if (WindowMode == TRUE) WindowMode = FALSE;
			else WindowMode = TRUE;
#ifdef _TALK_WINDOW
			if(g_bTalkWindow){
				g_bTalkWindow = FALSE;
				TalkWindow.Visible(FALSE);
			}
#endif
			ChangeMode(WindowMode);

			// DirectDraw ?��
			ReleaseDirectDraw();

			// ??�T???�@�e
			SetResoMode(ResoMode);

			// DirectDraw ???
			InitDirectDraw();
			// ??????????????�� 
			InitOffScreenSurface();
			// ????????��?�v?
			ChangeWindowMode();
			// �u???????��???
			//SendMessage( HWND_BROADCAST, WM_PAINT, NULL, NULL );

			// ???????
			if (InitPalette() == FALSE){
				//PostMessage( hWnd, WM_CLOSE, 0, 0L );
				PostMessage(hWnd, WM_SYSKEYDOWN, VK_RETURN, 0L);
			}
			// ??????��????????????????��
			if (ProcNo == PROC_BATTLE){
				// ???????
				DispBuffer.DispCnt = 0;
				FontCnt = 0;
#ifdef _NEW_RESOMODE
				//drawMap();
				ReadBattleMap(BattleMapNo);
#else
				ReadBattleMap( BattleMapNo );
#endif
				// ???????????????
				ClearBackSurface();
				// ????????????????
#ifdef __SKYISLAND
				fastDrawTileFlag = 0;
				PutBmp();
				fastDrawTileFlag = 1;
#else
				PutBmp();	
				// ??????????????????????
				lpBattleSurface->BltFast( 0, 0, lpDraw->lpBACKBUFFER, NULL, DDBLTFAST_WAIT );
#endif
				// ???????
				DispBuffer.DispCnt = 0;
				FontCnt = 0;
				// ????????
				NowTime = TimeGetTime();
			}
			else
			if (fastDrawTile && ProcNo == PROC_GAME)
			{
				repairMap();	// ????��?��?
			}
			// ??????????????
			if (lpDraw->lpPALETTE != NULL){
				// ??????????
				if (WindowMode){
					// ?��??????????��??
					lpDraw->lpPALETTE->SetEntries(0, 0, 256, Palette);
				}
			}
			// ???????�V?????
			mouse.state = MOUSE_NO_CRICK;
			mouse.onceState = MOUSE_NO_CRICK;
			// ???�w?��????
			NowTime = TimeGetTime();
			break;
#endif
			break;
		default:
			if (wParam != VK_F10){
				return DefWindowProc(hWnd, Message, wParam, lParam);
			}
			break;
		}
		break;
	case WM_CHAR:	// ��?�V???
		// ��?????????
		StockStrBufferChar((char)wParam);
		break;
	case WM_MOUSEMOVE:		// ????�h????
		//SetCursor( wndclass.hCursor );
		// ????????�t?????
		MouseNowPoint(LOWORD(lParam), HIWORD(lParam));
#ifndef _TALK_WINDOW
		if (mouse.flag == TRUE){
			ShowCursor(FALSE); // ????????��?
			mouse.flag = FALSE;
		}
#else
		if(MouseCursorFlag == FALSE && g_iCursorCount > -1){
			while(g_iCursorCount > -1) g_iCursorCount = ShowCursor( FALSE );
			mouse.flag = FALSE;
		}
		else if(MouseCursorFlag == TRUE && g_iCursorCount < 0){
			while(g_iCursorCount < 0) g_iCursorCount = ShowCursor( TRUE );
		}
#endif
		// ???????????
		if (SurfaceBusyFlag == TRUE){
			SurfaceBusyFlag = FALSE;
			// ??????????????
			RecoverDirectDraw();
		}
		break;
	case WM_NCMOUSEMOVE:	// ?????????????��??
		// ???????�V?????
		mouse.state = MOUSE_NO_CRICK;
		mouse.onceState = MOUSE_NO_CRICK;
		if (mouse.flag == FALSE){
#ifdef _TALK_WINDOW
			g_iCursorCount = ShowCursor( TRUE );
#else
			ShowCursor(TRUE); // ????????����
#endif
			mouse.flag = TRUE;
		}
		break;
	case WM_LBUTTONDOWN:	// ?????(????)
#ifdef _80_LOGIN_PLAY
		if (ProcNo == PROC_80_LOGIN)
			break;
#endif

#ifdef _REMAKE_20
		// ���ʹ�����Ƿ���İ��»���
		if(!IsLMouseButtonDown()) mouseCursorMode = 0;
		else
#endif
			// ???????????????�t?????
			MouseCrickLeftDownPoint(LOWORD(lParam), HIWORD(lParam));

		break;
	case WM_LBUTTONUP:		// ?????(????)
		// ???????????????�t?????
		MouseCrickLeftUpPoint(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_LBUTTONDBLCLK:		// ????????
#ifdef _80_LOGIN_PLAY
		if (ProcNo == PROC_80_LOGIN)
			break;
#endif
		// ??????????????????�t?????
		MouseDblCrickLeftUpPoint(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_RBUTTONDOWN:	// ?????(????)
#ifdef _REMAKE_20
		// ���ʹ�����Ƿ���İ��»���
		if(!IsRMouseButtonDown()) mouseCursorMode = 0;
		else 
#endif				
			// ???????????????�t?????
			MouseCrickRightDownPoint(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_RBUTTONUP:		// ?????(????)
		// ???????????????�t?????
		MouseCrickRightUpPoint(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_RBUTTONDBLCLK:		// ????????
		// ??????????????????�t?????
		MouseDblCrickRightUpPoint(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_MBUTTONDOWN:	// ?????(????)
		break;
	case WM_MOVE:
	{
					g_clientPoint.x = g_clientPoint.y = 0;
					GetClientRect(hWnd, &g_clientRect);
					ClientToScreen(hWnd, &g_clientPoint);
					OffsetRect(&g_clientRect, g_clientPoint.x, g_clientPoint.y);
					SetRect(&g_moveRect, 0, 0, lpDraw->xSize, lpDraw->ySize);
#ifdef _TALK_WINDOW
					if(g_bTalkWindow) SendMessage(TalkWindow.GetTalkWindowWND(),WM_MOVE,0,0);
#endif
	}
		break;

		//�Զ�Hook Msg����Type
#ifdef _SAHOOK //Syu ADD Hook��ʽ
	case UM_KEYEVENT: 
		TCHAR ac[2];
		BYTE bKeyState[256];		
		GetKeyboardState(bKeyState);
		if (ToAscii(wParam, (HIWORD(lParam) & (0x00FF | KF_UP)), bKeyState, (PWORD) ac, 0) == 1) 
		{
			extern int HOOK_PASSWD_NUM;
			if((HOOK_PASSWD_NUM < 12) && (wParam != 13) && (wParam != 9) && (wParam != 27))
				HOOK_PASSWD_NUM++;
		}
		if (wParam == 8 )
		if(HOOK_PASSWD_NUM >0 )
			HOOK_PASSWD_NUM--;
#endif
	default:
		if (ImeMessage(Message, wParam, lParam))
			return 0;
		return DefWindowProc(hWnd, Message, wParam, lParam);
	}


	return 0;
}

void SetResoMode(int Mode){
	ResoMode = Mode;
	lpDraw = (DIRECT_DRAW *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (DWORD)sizeof(DIRECT_DRAW));
	if (lpDraw == NULL){
		MessageBoxNew(hWnd, "HeapAlloc Error ( DIRECT_DRAW )", "ȷ��", MB_OK | MB_ICONSTOP);
		return;
	}
	switch (Mode){
	case 0:
		//460*480
		lpDraw->xSize = 640;
		lpDraw->ySize = 480;
		SurfaceSizeX = 64;
		SurfaceSizeY = 48;
		DISPLACEMENT_X = 0;
		DISPLACEMENT_Y = 0;
		break;
	case 1:
		//320*240
		lpDraw->xSize = 320;
		lpDraw->ySize = 240;
		SurfaceSizeX = 64;
		SurfaceSizeY = 48;
		DISPLACEMENT_X = 0;
		DISPLACEMENT_Y = 0;
		break;
	case 2:
		//�ɱ�
		lpDraw->xSize = 640;
		lpDraw->ySize = 480;
		SurfaceSizeX = 64;
		SurfaceSizeY = 48;
		DISPLACEMENT_X = 0;
		DISPLACEMENT_Y = 0;
		break;
#ifdef _NEW_RESOMODE
	case 3:
		lpDraw->xSize = 800;
		lpDraw->ySize = 600;
		SurfaceSizeX = 64;
		SurfaceSizeY = 48;
		DISPLACEMENT_X = 160;
		DISPLACEMENT_Y = 120;
		break;
	case 4:
		lpDraw->xSize = 1024;
		lpDraw->ySize = 768;
		SurfaceSizeX = 64;
		SurfaceSizeY = 48;
		DISPLACEMENT_X = 384;
		DISPLACEMENT_Y = 288;
		break;
#endif
	}

	DEF_APPSIZEX = lpDraw->xSize;
	DEF_APPSIZEY = lpDraw->ySize;
	SCREEN_WIDTH_CENTER = DEF_APPSIZEX / 2;
	SCREEN_HEIGHT_CENTER = DEF_APPSIZEY / 2;
	viewOffsetX = SCREEN_WIDTH_CENTER;
	viewOffsetY = SCREEN_HEIGHT_CENTER;
	PostMessage(hWnd, WM_MOVE, 0, 0L);
}

