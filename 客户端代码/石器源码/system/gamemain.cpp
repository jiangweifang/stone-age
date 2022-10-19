/************************/
/*	gamemain.cpp		*/
/************************/
#include "../systeminc/version.h"
#include "../systeminc/system.h"
#include <winuser.h>
#include <winbase.h>
#include "../systeminc/loadrealbin.h"
#include "../systeminc/loadsprbin.h"
#include "../oft/sys2.h"
#include "../other/caryIme.h"
#include "../systeminc/ime_sa.h"
#include "../systeminc/anim_tbl.h"
#include "../systeminc/battleMap.h"
#include "../systeminc/netmain.h"
#include "../systeminc/savedata.h"
#include "../systeminc/produce.h"
#include "../systeminc/battleProc.h"
#include "../systeminc/t_music.h"
#include "../systeminc/menu.h"
#include "../systeminc/handletime.h"
#include "../systeminc/battleMenu.h"
#include "../systeminc/character.h"
#include "../systeminc/login.h"
#include "../systeminc/pc.h"
#include "../systeminc/map.h"
#include "../NewProto/autil.h"
#include "../NewProto/protocol.h"
#include "../systeminc/field.h"
#include "../systeminc/VMProtectSDK.h"
#include <tlhelp32.h>
#ifdef _OPTIMIZATIONFLIP_
#include <thread> 
#include <chrono>
#endif
#ifdef _CMD_MODE
#include <io.h>
#include <fcntl.h>
#endif
#ifdef _REMAKE_20
#include "../MMOGprotect.h"
#endif
#ifdef _TALK_WINDOW
#include "../systeminc/talkwindow.h"
#endif
#ifdef _PTTERN_SEPARATION_BIN
#include "../other/PtternSeparationBin.h"
#endif
#ifdef _AIDENGLU_
#include "../systeminc/pc.h"
extern Landed PcLanded;
#endif

int �Ƿ��ؿ������_1;
int ����;
int MessageBoxNew(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType);

#ifdef _OPTIMIZATIONFLIP_
#define NO_DRAW_MAX_CNT 5	// ��?????��?????
#else
#define NO_DRAW_MAX_CNT 6	// ��?????��?????
//#define FRAME_SKIP	1		// ???????? ??��?  ???��?
#endif

// ????????��?�v???�L?
void ChangeWindowMode(void);
// ??�T???�@�e??
void SetResoMode(int Mode);
void StrToNowStrBuffer(char *str);
void StrToNowStrBuffer1(char *str);

//#ifndef _STONDEBUG_
//	#define _STONDEBUG_	// ????????????
//#endif
#define _BATTLESLEPP_ 0
int testCnt;
static char no_wait_cnt = 0;
int debug_info_flag = 0;

//---------------------------------------------------------------------------//
// ?????��?�e?                                                        //
//---------------------------------------------------------------------------//

// ????????��?
int	  FrameRate;
int	  DrawFrameCnt;
DWORD DrawFrameTime;
#ifdef _STONDEBUG_
static int palNo = 0;
static int fontNo = 0;
#endif

int	GameState;

#ifdef _OPTIMIZATIONFLIP_
//����ʱ��
DWORD ProcTime = 8;
//ѭ��ʱ�� 
DWORD SystemTime = 16;
#else
//����ʱ��
DWORD ProcTime = 14;
//ѭ��ʱ�� 
#ifdef _SYSTEM_SLEEP_
DWORD SystemTime = _SYSTEM_SLEEP_;
#else
DWORD SystemTime = 6;
#endif
#endif


#ifdef _NEW_SPEED_
BOOL GameSpeedFlag = FALSE;
#endif
DWORD NowTime;
int	  NoDrawCnt = 1;
int BackBufferDrawType;
#ifdef _READ16BITBMP
bool	g_bMMXMode;	// CPU �Ƿ���MMXָ�
#endif
#ifdef _REMAKE_20
static DWORD dwDisableInputScriptTime = 0;	// ÿ�����ִ��һ��DisableInputScriptTime()
#endif

//DWORD WINAPI CheckTickCount(LPVOID lpParam);
#ifdef _CMD_MODE 
void InitConsoleWindow(void);
void ConsoleThread(void);
#endif

#ifdef _CHECK_GAMESPEED
void HighSpeedCheck( void )
{
#define HIGH_SPEED_CHECK_INTERVAL 60*60
	static int SpeedCnt=0;
	static float delays=0;
	if( init_net == FALSE ) return;
	SpeedCnt++;
	if( SpeedCnt >= HIGH_SPEED_CHECK_INTERVAL ){
		int delaytimes = lssproto_getdelaytimes();
		if( delaytimes > 0 ){
			lssproto_setdelaytimes( 0);
			delays += delaytimes*10;
		}else{
			if( delays > 0 ) delays--;
		}
		SpeedCnt = 0;
		lssproto_CS_send( sockfd);	//��̽���server
	}
	if( (int)delays > 0 ){
		for( int i=0; i<((int)delays+1000); i++){}
	}
}
#endif

DWORD WINAPI TestThreadProc(PVOID pParam)
{
	DWORD dwStart = GetTickCount();
	Sleep(3000);
	DWORD endstart = GetTickCount() - dwStart;
	if (endstart >= 3500){
		ExitProcess(0);
	}
	return 0;
}

DWORD WINAPI TestThreadProc1(PVOID pParam)
{
	if (VMProtectIsDebuggerPresent(true)) ExitProcess(NULL);
	if (VMProtectIsVirtualMachinePresent()) ExitProcess(NULL);
	extern BOOL IsContainsProcess(char* strProName, BOOL �ж� = 1);
	if (IsContainsProcess("�ര��", 0) || IsContainsProcess("ͬ��", 0) ||
		IsContainsProcess("SbieSvc.exe")||IsContainsProcess("SbieCtrl.exe"))  ExitProcess(NULL);
	extern void �������();
	�������();
	return 0;
}

HANDLE hThread = NULL;
HANDLE hThread1 = NULL;
void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
{
	if (hThread) CloseHandle(hThread);
	hThread = CreateThread(NULL, 0, TestThreadProc, 0, 0, NULL);
}
void CALLBACK TimerProc1(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
{
	if (hThread1) CloseHandle(hThread1);
	hThread1 = CreateThread(NULL, 0, TestThreadProc1, 0, 0, NULL);
}



#ifdef _ANNOUNCEMENT_
int �������� = 0;
char ��������[512];
int ������ɫ = -1;
int ����ʱ�� = 0;

void announce()
{
	if (�������� == 0) return;
	int showcolor;
	����ʱ�� += 4;
	int left = ((����ʱ�� / 25) % (800 + (strlen(��������) * 8)));
	if (left == 0){
		��������--;
		if (������ɫ == -1){
			showcolor = rand() % 10;
		}
		else{
			showcolor = ������ɫ;
		}
	}
	StockFontBuffer(800 - left, 60, 1, showcolor, ��������, 0);
}
#endif


BOOL GameMain(void)
{
	if (InitGame() == FALSE){
		MessageBoxNew(hWnd, "��Ϸ�趨��ʼ��ʧ�ܣ�", "ȷ��", MB_OK | MB_ICONSTOP);
		return FALSE;
	}
	char sz[32];
	DWORD nowtime;
	DWORD nowttime1 = TimeGetTime();
	DWORD nowttime3 = TimeGetTime();
	//_itoa_s( nowttime1^0xffffbcde, sz, 10);

#ifdef	_OPTIMIZATIONFLIP_
	BOOL finishLoop = TRUE;
	unsigned int startloopTime = TimeGetTime();
	unsigned int endloopTime;
	unsigned int endProcTime;

	unsigned int loopAmend = 0;
	unsigned int skipAmend = 0;
	extern BOOL  isXP();
	BOOL isXPSystem = isXP();
#endif


	CreatFontHdc();

#ifdef _NODEBUG_
	SetTimer(0, 0, 6000, &TimerProc);
	SetTimer(0, 0, 60000, &TimerProc1);
#endif
	while (1){

		if (SystemTask() == FALSE){
			EndGame();
			return FALSE;
		}

#ifdef	_OPTIMIZATIONFLIP_
		if (finishLoop)
		{
			startloopTime = TimeGetTime();
			endloopTime = startloopTime + SystemTime;
			endProcTime = startloopTime + ProcTime;
			finishLoop = FALSE;
		}
#endif


#ifdef _CHECK_GAMESPEED
		HighSpeedCheck();
#endif
#ifdef _REMAKE_20
#ifndef _STONDEBUG_
		if(dwDisableInputScriptTime + 300000 < TimeGetTime()){
			DisableInputScript();
			dwDisableInputScriptTime = TimeGetTime();
		}
#endif
#endif

			RealTimeToSATime(&SaTime);
		DispBuffer.DispCnt = 0;
		FontCnt = 0;

		if (!offlineFlag)
			networkLoop();
		
		cdda_play(cdda_no);
		joy_read();
#if 1
		if (joy_trg[1] & JOY_F12){
			static unsigned int prePushTime = 0;
			if (prePushTime + 500 <= TimeGetTime()){
				snapShot();
				prePushTime = TimeGetTime();
			}
		}
#endif
		if (joy_trg[1] & JOY_F11)
			nameOverTheHeadFlag = !nameOverTheHeadFlag;

		Process();

		MouseProc();
#ifdef _SURFACE_ANIM
		AniProc();
#endif
#ifdef _ANNOUNCEMENT_
		if (ProcNo == PROC_GAME){
			if (!actBtn){
				announce();
			}
		}
#endif
		SortDispBuffer();
		HitMouseCursor();
		PaletteProc();
#ifdef _AIDENGLU_
		static int ���µ�½ԭ�ؿ�ʼʱ�� = 0;
		static int ���µ�½AI��ʼʱ�� = 0;
		static int ���µ�½����ʼʱ�� = 0;
		static int ���µ�½��ӿ�ʼʱ�� = 0;
		static int ���µ�½������ʼʱ�� = 0;
		extern int �Ƿ��ص�ս����;
		extern int �Ƿ��ص����﷽��;
		extern int �Ƿ��ص�AIģʽ;
		extern int �Ƿ��ص����;
		extern int �Ƿ��صǺ���;
		static int ����ӿ�ʼʱ�� = 0;

		if (ProcNo == PROC_GAME){
			if (PcLanded.��ģ == 0){
				if (�Ƿ��ص�AIģʽ){
					if (�Ƿ��ؿ������_1){
						�Ƿ��ؿ������_1 = FALSE;
						����ӿ�ʼʱ�� = TimeGetTime();
					}
				}
				if (partyModeFlag){//��һ�˵�ʱ�����½
					if (�Ƿ��ص�ս����){
						�Ƿ��ص�ս���� = FALSE;
						���µ�½ԭ�ؿ�ʼʱ�� = TimeGetTime();
					}
				}
			}
			else{
				if (�Ƿ��ص�ս����){
					�Ƿ��ص�ս���� = FALSE;
					���µ�½ԭ�ؿ�ʼʱ�� = TimeGetTime();
				}
			}
			if (����ӿ�ʼʱ��){
				if (TimeGetTime() > ����ӿ�ʼʱ�� + 500){
					extern unsigned int sockfd;
					if(!pc.etcFlag &PC_ETCFLAG_PARTY){
						pc.etcFlag |= PC_ETCFLAG_PARTY;
						lssproto_FS_send(sockfd, pc.etcFlag);
					}
				}
			}
			if (���µ�½ԭ�ؿ�ʼʱ��){
				if (TimeGetTime() > ���µ�½ԭ�ؿ�ʼʱ�� + 2000){
					���µ�½ԭ�ؿ�ʼʱ�� = 0;
					extern unsigned int sockfd;
					lssproto_SaMenu_send(sockfd, 11);
				}
			}
			if (�Ƿ��ص�AIģʽ){
				���µ�½AI��ʼʱ�� = TimeGetTime();
				�Ƿ��ص�AIģʽ = FALSE;
			}
			if (���µ�½AI��ʼʱ��){
				if (TimeGetTime() > ���µ�½AI��ʼʱ�� + 500){
					���µ�½AI��ʼʱ�� = 0;
					AI = AI_SELECT;
					StockChatBufferLine("��������ģʽ��", FONT_PAL_RED);
					pc.etcFlag |= PC_AI_MOD;
					lssproto_FS_send(sockfd, pc.etcFlag);
				}
			}
			if (�Ƿ��ص����﷽��){
				�Ƿ��ص����﷽�� = FALSE;
				���µ�½����ʼʱ�� = TimeGetTime();
			}
			if (���µ�½����ʼʱ��){
				if (TimeGetTime() > ���µ�½����ʼʱ�� + 500){
					���µ�½����ʼʱ�� = 0;
					char dir2[2];
					setPcDir(PcLanded.���﷽��);
					dir2[0] = cnvServDir(PcLanded.���﷽��, 1);
					dir2[1] = '\0';
					walkSendForServer(nowGx, nowGy, dir2);
				}
			}
			extern int �Զ���½�Ƿ���;
			if (�Ƿ��ص����&&!�Ƿ��ص����﷽��&&!���µ�½����ʼʱ��&&!partyModeFlag){
				if (!���µ�½��ӿ�ʼʱ��){
					���µ�½��ӿ�ʼʱ�� = TimeGetTime();
				}
				else{
					if (TimeGetTime() > ���µ�½��ӿ�ʼʱ�� + FIELD_BTN_PUSH_WAIT){
						���µ�½��ӿ�ʼʱ�� = 0;
						lssproto_PR_send(sockfd, nowGx, nowGy, 1);
					}
				}
				if (�Ƿ��صǺ���){
					if (!���µ�½������ʼʱ��){
						���µ�½������ʼʱ�� = TimeGetTime();
					}
					else{
						if (TimeGetTime() > ���µ�½������ʼʱ�� + 1000 * 60){
							���µ�½������ʼʱ�� = 0;
							char m[1024];
							sprintf_s(m, "P|��λ�������ܴ�������Ӵ���յ������µ�½���������վ����ǰ����������λ��(%d,%d)", nowGx, nowGy);
							lssproto_TK_send(sockfd, nowGx, nowGy, m, 0, NowMaxVoice);
						}
					}
				}
			}
			else{
				���µ�½��ӿ�ʼʱ�� = 0;
				���µ�½������ʼʱ�� = 0;
			}
		}
		extern int �Զ���½�Ƿ���;
		if (ProcNo >= 1 && ProcNo <= 3){
			if (PcLanded.���� != -1 && PcLanded.С�� != -1 && PcLanded.���� != -1){
				if (�Զ���½�Ƿ���)
					StockFontBuffer(10, 550, FONT_PRIO_FRONT, FONT_PAL_RED, "�����Զ���½��,��F9��ֹͣ�Զ���½��", 0);
				else
					StockFontBuffer(10, 550, FONT_PRIO_FRONT, FONT_PAL_RED, "��F9���Զ���½��Ϸ��", 0);
			}
		}
		if (joy_trg[1] & JOY_F9&&ProcNo >= 1 && ProcNo <= 3)
		{
			if (�Զ���½�Ƿ���) �Զ���½�Ƿ��� = !�Զ���½�Ƿ���;
			else{
				if (PcLanded.���� != -1 && PcLanded.С�� != -1 && PcLanded.���� != -1)
					�Զ���½�Ƿ��� = TRUE;
			}
		}
#endif
#ifdef _STONDEBUG_
		if (joy_trg[1] & JOY_F9  && WindowMode){
#else			
		if (joy_trg[1] & JOY_F9  && WindowMode && LowResoCmdFlag){
#endif

			if (BackBufferDrawType != DRAW_BACK_PRODUCE){
				if (lpDraw != NULL){
					// DirectDraw ?��
					ReleaseDirectDraw();
					DeleteObject(hFont);
					SetResoMode(((ResoMode + 1) % 5));
					InitDirectDraw();
					InitOffScreenSurface();
					InitFont(0);
					ChangeWindowMode();
					if (InitPalette() == FALSE){
						PostMessage(hWnd, WM_CLOSE, 0, 0L);
					}
					if (ProcNo == PROC_BATTLE){
						DispBuffer.DispCnt = 0;
						FontCnt = 0;
						ReadBattleMap(BattleMapNo);
						ClearBackSurface();
#ifdef __SKYISLAND
						fastDrawTileFlag = 0;
						PutBmp();
						fastDrawTileFlag = 1;
#else
						PutBmp();
						lpBattleSurface->BltFast(0, 0, lpDraw->lpBACKBUFFER, NULL, DDBLTFAST_WAIT);
#endif
						DispBuffer.DispCnt = 0;
						FontCnt = 0;
						NowTime = TimeGetTime();
					}
					else
					if (fastDrawTile && ProcNo == PROC_GAME){
						repairMap();
					}
				}
			}
		}


#ifdef _STONDEBUG_
		if( joy_trg[ 0 ] & JOY_HOME ){
			strcpy( MyChatBuffer.buffer + MyChatBuffer.cnt, DebugKey0 );
			MyChatBuffer.cnt += strlen( DebugKey0 );
		}
		if( joy_trg[ 0 ] & JOY_END ){
			strcpy( MyChatBuffer.buffer + MyChatBuffer.cnt, DebugKey1 );
			MyChatBuffer.cnt += strlen( DebugKey1 );
		}
		if( joy_trg[ 0 ] & JOY_INS ){
			strcpy( MyChatBuffer.buffer + MyChatBuffer.cnt, DebugKey2 );
			MyChatBuffer.cnt += strlen( DebugKey2 );
		}
		DisplayFrameRate();
		{
			if( di_key[ DIK_PRIOR ] & 0x80 ){ 
				if( debug_info_flag == 0 ) debug_info_flag = 1;
				if( debug_info_flag == 2 ) debug_info_flag = 3;
			}else{
				if( debug_info_flag == 1 ) debug_info_flag = 2;
				if( debug_info_flag == 3 ) debug_info_flag = 0;
			}
			if (debug_info_flag == 1 || debug_info_flag == 2) InfoDisp();
		}
#endif	

#ifdef __NEW_CLIENT_MEM
#ifndef __NEW_CLIENT_ONLY_WRITE
		static DWORD reset = TimeGetTime() + 120000;
		static DWORD flip = 1;
		DWORD oldprotect;
		if (reset < TimeGetTime()){
			char *newread, *newwrite;
			reset += 120000;
			flip = (flip + 1) & 1;
			if (flip == 1){
				if ((newread = (char*)VirtualAlloc(NULL, NETBUFSIZ, MEM_COMMIT, PAGE_READWRITE))){
					if (net_readbuflen){
						VirtualProtect(net_readbuf, NETBUFSIZ, PAGE_READWRITE, &oldprotect);
						CopyMemory(newread, net_readbuf, net_readbuflen);
					}
					VirtualFree(net_readbuf, NULL, MEM_RELEASE);
					net_readbuf = newread;
					VirtualProtect(net_readbuf, NETBUFSIZ, PAGE_NOACCESS, &oldprotect);
				}
			}
			else{
				if ((newwrite = (char*)VirtualAlloc(NULL, NETBUFSIZ, MEM_COMMIT, PAGE_READWRITE))){
					if (net_writebuflen){
						VirtualProtect(net_writebuf, NETBUFSIZ, PAGE_READWRITE, &oldprotect);
						CopyMemory(newwrite, net_writebuf, net_writebuflen);
					}
					VirtualFree(net_writebuf, NULL, MEM_RELEASE);
					net_writebuf = newwrite;
					VirtualProtect(net_writebuf, NETBUFSIZ, PAGE_NOACCESS, &oldprotect);
				}
			}
		}
#else
		static DWORD reset = TimeGetTime() + 120000;
		DWORD oldprotect;
		if( reset < TimeGetTime()){
			char *newwrite;
			reset += 120000;
			if( (newwrite=(char*)VirtualAlloc( NULL, NETBUFSIZ, MEM_COMMIT, PAGE_READWRITE))){
				VirtualProtect( net_writebuf, NETBUFSIZ, PAGE_READWRITE, &oldprotect);
				CopyMemory( newwrite, net_writebuf, net_writebuflen);
				VirtualFree( net_writebuf, NULL, MEM_RELEASE); 
				net_writebuf = newwrite;
				VirtualProtect( net_writebuf, NETBUFSIZ, PAGE_NOACCESS, &oldprotect);
				newwrite = NULL;
			}
		}
#endif
#endif

#ifdef _STONEAGE_NG

#else

#ifdef _OPTIMIZATIONFLIP_
		if (endProcTime > TimeGetTime())
		{
			//���������֡��
			if (NoDrawCnt < NO_DRAW_MAX_CNT + skipAmend)
			{
				NoDrawCnt++;
				continue;
			}
			else
			{
				while (endProcTime > TimeGetTime())
				{
					std::this_thread::sleep_for(std::chrono::microseconds(10));
				}
			}
		}
#ifdef _MO_SHOW_FPS
		sprintf(sz, "skip frames: %d", skipAmend);
		StockFontBuffer(380, 10, 1, 1, sz, false);	
#endif

#else
		NowTime = TimeGetTime();//��ȡ��ǰ��ʱ�� ����
		nowtime = nowttime1;
		//nowtime ^= 0xffffbcde;
		static DWORD OldTime = nowttime1;
		if (NowTime > (nowtime + ProcTime)){
			//OldTime^= 0x855ff55f;
			if (OldTime != nowtime){
				OldTime = nowtime;
				if (NoDrawCnt < NO_DRAW_MAX_CNT){
					if (NowTime>nowttime3 + 2000){
						nowttime3 = NowTime;
						nowtime = NowTime + SystemTime;
					}
					else
						nowtime += (SystemTime);
					nowttime1 = nowtime;
					//_itoa_s( nowtime^0xffffbcde, sz, 10);
					nowtime = 0;
					NoDrawCnt++;
					Sleep(0);
					continue;
				}
			}//else
			//OldTime^= 0x855ff55f;
		}
#endif
#endif
		nowtime = 0;
		//cary AI���л�
		if (di_key[DIK_NEXT] & 0x80){
			di_key[DIK_NEXT] &= ~0x80;
			static DWORD switchmodetime = TimeGetTime();
			if ((switchmodetime + 500) < NowTime){
				switchmodetime = NowTime;
#ifdef __AI
				if (AI == AI_SELECT){
					AI = AI_NONE;
					pc.etcFlag &= (~PC_AI_MOD);
					lssproto_FS_send(sockfd, pc.etcFlag);
					// �޸�ս��AIת����BUG  AI->���
#ifdef _FIX_BATTLE_AI
					battleMenuFix();
#endif
				}
				else{
					AI = AI_SELECT;
					pc.etcFlag |= PC_AI_MOD;
					lssproto_FS_send(sockfd, pc.etcFlag);
				}
				extern BOOL AI_Save();
				AI_Save();
#else
				extern int battleWazaTargetBak;
				if (PROC_BATTLE != ProcNo || BATTLE_SUBPROC_CMD_INPUT != SubProcNo){
					battleWazaTargetBak = -1;
					AI++;
					if (AI > AI_SELECT)
						AI = AI_NONE;
				}
				else{
					if (AI == AI_NONE){
						battleWazaTargetBak = -1;
						AI = AI_ATTACK;
					}
				}
#endif
			}
		}
		else if (di_key[DIK_PRIOR] & 0x80){
			di_key[DIK_PRIOR] &= ~0x80;
			static DWORD switchmodetime = TimeGetTime();
			if ((switchmodetime + 500) < NowTime){
				switchmodetime = NowTime;
#ifdef __AI
				if (AI == AI_SELECT){
					AI = AI_NONE;
					// �޸�ս��AIת����BUG  ���->AI
#ifdef _FIX_BATTLE_AI
					battleMenuFix();
#endif
					pc.etcFlag &= (~PC_AI_MOD);
					lssproto_FS_send(sockfd, pc.etcFlag);
				}
				else{
					AI = AI_SELECT;
					pc.etcFlag |= PC_AI_MOD;
					lssproto_FS_send(sockfd, pc.etcFlag);
				}
				extern BOOL AI_Save();
				AI_Save();
#else
				extern int battleWazaTargetBak;
				if (PROC_BATTLE != ProcNo || BATTLE_SUBPROC_CMD_INPUT != SubProcNo){
					battleWazaTargetBak = -1;
					AI--;
					if( AI < AI_NONE)
						AI = AI_SELECT;
				}else{
					if( AI == AI_NONE){
						battleWazaTargetBak = -1;
						AI = AI_SELECT;
					}
				}
#endif
			}
		}

#ifdef _STONDEBUG_		
		SurfaceDispCnt = 0;
		//		DrawDebugLine( 250 ); 
#endif		
#ifndef __SKYISLAND
		switch( BackBufferDrawType ){

		case DRAW_BACK_NON:
			break;

		case DRAW_BACK_NORMAL:
			ClearBackSurface();
			break;

		case DRAW_BACK_PRODUCE:
			break;

		case DRAW_BACK_BATTLE:	// ??????��?

			DrawBattleMap();
			break;

		}
#else
		if (BackBufferDrawType != DRAW_BACK_PRODUCE){
#endif
#ifdef _STONDEBUG_
			no_wait_cnt++;
			if( GetAsyncKeyState( 0x10 ) & 0x8000 )
				no_wait_cnt &= 7;
			else
				no_wait_cnt &= 3;
			if( GetAsyncKeyState( 0x10 ) & 0x8000 ){		//???????????
				if(!no_wait_cnt){
					PutBmp();	// ????????????????
					// dwaf ????��??�L???
					baseXFastDraw = nowXFastDraw;
					baseYFastDraw = nowYFastDraw;
					baseXFastDraw2 = nowXFastDraw2;
					baseYFastDraw2 = nowYFastDraw2;
				}
			}
			else {
				PutBmp();	// ????????????????
				baseXFastDraw = nowXFastDraw;
				baseYFastDraw = nowYFastDraw;
				baseXFastDraw2 = nowXFastDraw2;
				baseYFastDraw2 = nowYFastDraw2;
			}
#else
#ifdef _NEW_SPEED_
			no_wait_cnt++;
			no_wait_cnt &= 3;
#ifdef _OPTIMIZATIONFLIP_
			loopAmend = TimeGetTime();
#endif
			PutBmp();
#ifdef _OPTIMIZATIONFLIP_
			loopAmend = TimeGetTime() - loopAmend;
			if (loopAmend < 8)
			{
				skipAmend = 0;
			}
			else if (loopAmend >=8)
			{
				skipAmend = 1;
			}		
#endif
			baseXFastDraw = nowXFastDraw;
			baseYFastDraw = nowYFastDraw;
			baseXFastDraw2 = nowXFastDraw2;
			baseYFastDraw2 = nowYFastDraw2;

#else
			PutBmp();
			baseXFastDraw = nowXFastDraw;
			baseYFastDraw = nowYFastDraw;
			baseXFastDraw2 = nowXFastDraw2;
			baseYFastDraw2 = nowYFastDraw2;

#endif //_SPEED
#endif	
#ifdef __SKYISLAND
		}
#endif

#ifdef _STONDEBUG_		
		DrawDebugLine(0);
#endif		

#ifdef _STONDEBUG_	
		if (GetAsyncKeyState(0x10) & 0x8000){		//???????????
			if (!no_wait_cnt){
				Flip();	// ?���i?�_??��?�v???
			}
		}
		else {
			Flip();	// ?���i?�_??��?�v???
		}
#else
		Flip();	// ?���i?�_??��?�v???
#endif		

#ifdef _STONDEBUG_		
		DrawDebugLine(249);
#endif

#ifdef _STONDEBUG_	
		if (GetAsyncKeyState(0x10) & 0x8000){		//???????????
			nowtime = TimeGetTime();
			_itoa_s(nowtime ^ 0xffffbcde, sz, 10);
		} else {
			nowtime = atoi( sz);
			nowtime ^= 0xffffbcde;
			while( nowtime >= TimeGetTime() ){
				if( WindowMode ){
					Sleep(1);
				}
			}
		}
#else
#ifdef _NEW_SPEED_
		//nowtime = atoi( sz);
		//nowtime ^= 0xffffbcde;
#ifndef _OPTIMIZATIONFLIP_
		nowtime = nowttime1;
		while (nowtime >= TimeGetTime()){
			Sleep(1);
		}
		nowtime = 0;
#endif
#else
		nowtime = atoi( sz);
		nowtime ^= 0xffffbcde;
		while( nowtime >= TimeGetTime() ){
			Sleep(1);
		}
		nowtime = 0;

#endif
#endif

		if (PalChangeFlag == TRUE){

#ifdef __NEW_CLIENT
			extern HANDLE hProcessSnap, hParentProcess;
			extern DWORD dwPID;
			extern PROCESSENTRY32 pe32;
			if( dwPID){
				pe32.dwSize = sizeof(PROCESSENTRY32);
				if( Process32First( hProcessSnap, &pe32)){ 
					do{
						if (pe32.th32ProcessID == dwPID){
							if (!strstr(pe32.szExeFile, "explorer.exe") && (hParentProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID))){
#ifndef NO_TERMINATER
								TerminateProcess(hParentProcess, 0);
#endif
								CloseHandle(hParentProcess);
							}
							break;
						}
					}while (Process32Next(hProcessSnap, &pe32));
				}
				dwPID = 0;
			}
#endif
			extern int displayBpp;
			extern int rBitLShift, gBitLShift, bBitLShift;
			extern int rBitRShift, gBitRShift, bBitRShift;
			if (displayBpp >= 16){
#ifdef _HI_COLOR_32
				if (displayBpp == 32){
					extern unsigned int highColor32Palette[256];
					for (int i = 1; i < 256; i++){
						highColor32Palette[i] =
							//cary 2001 10 16
							((Palette[i].peBlue >> bBitRShift) << bBitLShift)
							+ ((Palette[i].peGreen >> gBitRShift) << gBitLShift)
							+ ((Palette[i].peRed >> rBitRShift) << rBitLShift);
					}
				}
				else
#endif
				if (displayBpp == 16){
					extern unsigned short highColorPalette[256];
					for (int i = 1; i < 256; i++){
						highColorPalette[i] =
							((Palette[i].peBlue >> bBitRShift) << bBitLShift)
							+ (((Palette[i].peGreen >> gBitRShift) | 1) << gBitLShift)
							+ ((Palette[i].peRed >> rBitRShift) << rBitLShift);
					}
				}
#ifdef __HI_COLOR
				InitSpriteInfo();
				InitSurfaceInfo();
				extern int BackBufferDrawType;
				if (BackBufferDrawType == DRAW_BACK_BATTLE){
#ifdef _NEW_RESOMODE
					//drawMap();
					ReadBattleMap(BattleMapNo);
#else
					ReadBattleMap(BattleMapNo);
#endif
					SortDispBuffer();
					ClearBackSurface();
					fastDrawTileFlag = 0;
					PutBmp();
					fastDrawTileFlag = 1;
				}
				else repairMap();
#endif
#ifdef __CARYTEST
				extern LPREALBIN	g_lpRealHead;
				LPREALBIN node = g_lpRealHead;
				while (node){
					node->state = 0;
				}
#endif
			}
			else if (displayBpp == 8){
				lpDraw->lpPALETTE->SetEntries(0, 0, 256, Palette);
			}
			PalChangeFlag = FALSE;
		}
#ifdef _NEW_SPEED_
		if (GameSpeedFlag){
			nowtime = TimeGetTime();
			nowttime1 = nowtime;
			//_itoa_s( nowtime^0xffffbcde, sz, 10);
			GameSpeedFlag = FALSE;
		}
#endif
		//nowtime = atoi( sz);
		//nowtime ^= 0xffffbcde;

#ifdef	_OPTIMIZATIONFLIP_
		finishLoop = TRUE;
		NoDrawCnt = 1;

		while (endloopTime > TimeGetTime()){
			std::this_thread::sleep_for(std::chrono::microseconds(10));
		}

#else
		nowttime1 += SystemTime;
		nowtime = 0;
		Sleep(1);
		NoDrawCnt = 1;
#endif

#ifdef _STONDEBUG_		
		// ?��??��??????????
		DrawFrameCnt++;
#endif
		SurfaceDate++;
	}

	return FALSE;
}

#ifdef _STONDEBUG_		
unsigned int iTotalUseTime;
unsigned int iTotalProcTime;
unsigned int iTotalRunCount;
unsigned int iShowCount;
LARGE_INTEGER tf;
extern bool g_bMMXMode;
// �ѩ����� *******************************************************************/
void InfoDisp( void )
{
	char szMoji[ 256 ];
	int x = lpDraw->xSize - 200;
	int y = 64;
	char c = 0;

	sprintf_s( szMoji,"ActionCnt        = %d", ActCnt );
	// ????�ѩ�?????????
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	sprintf_s( szMoji,"DispCnt          = %d", DispBuffer.DispCnt );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	sprintf_s( szMoji,"SurfaceCnt       = %d",SurfaceCnt );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	sprintf_s( szMoji,"SearchPoint      = %d",SurfaceSearchPoint );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	sprintf_s( szMoji,"SysramSurfaceCnt = %d",SysramSurfaceCnt );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	sprintf_s( szMoji,"VramSurfaceCnt   = %d",VramSurfaceCnt );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	sprintf_s( szMoji,"SurfaceUseCnt    = %d",SurfaceUseCnt );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	sprintf_s( szMoji,"SurfaceDispCnt   = %d",SurfaceDispCnt );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	sprintf_s( szMoji,"SurfaceDate      = %d",SurfaceDate );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	sprintf_s( szMoji,"FrameRate        = %d",FrameRate );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	sprintf_s( szMoji,"HitDispNo        = %d",HitDispNo );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	sprintf_s( szMoji,"HitFontNo        = %d",HitFontNo );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	sprintf_s( szMoji,"MouseLevel       = %d",mouse.level );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	sprintf_s( szMoji,"ProcNo           = %d",ProcNo );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	sprintf_s( szMoji,"SubProcNo        = %d",SubProcNo );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	sprintf_s( szMoji,"ActionSize       = %d",sizeof( ACTION ) );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	sprintf_s( szMoji,"MouseX           = %d",mouse.nowPoint.x );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	sprintf_s( szMoji,"MouseY           = %d",mouse.nowPoint.y );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	sprintf_s( szMoji,"TimeZone         = %d",SaTime.hour );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	c = 0;

	sprintf_s( szMoji,"PalNo            = %d",PalState.palNo );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	sprintf_s( szMoji,"BattleMapNo      = %d",BattleMapNo );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	sprintf_s( szMoji,"HogeCnt          = %d",testCnt );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	sprintf_s( szMoji,"EventEnemyFlag   = %d",eventEnemyFlag );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	// ?�P??
	if( BattleMyNo >= 20 ){
		sprintf_s( szMoji,"BattleTurnNo     = %d",BattleCliTurnNo );
	}else{
		sprintf_s( szMoji,"BattleTurnNo     = %d",BattleCliTurnNo + 1 );
	}
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	sprintf_s( szMoji,"BattleDebTurnNo   = %d",BattleDebTurnNo );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;
#ifdef _READ16BITBMP
#ifdef _STONDEBUG_
	if(iTotalRunCount % 100){
		iShowCount = iTotalUseTime/iTotalRunCount;
		//		iTotalUseTime = 0;
		//		iTotalRunCount = 0;
	}
	sprintf_s( szMoji,"TestProcUseTime = %d",iShowCount);
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;
	sprintf_s( szMoji,"TestRunTimes = %d",iTotalRunCount);
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;
#endif
#ifdef _TALK_WINDOW
	sprintf_s(szMoji,"g_iCursorCount = %d",g_iCursorCount);
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;
#endif
#endif

	sprintf_s( szMoji,"selectPetNo[ 0 ] = %d",pc.selectPetNo[ 0 ] );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	sprintf_s( szMoji,"selectPetNo[ 1 ] = %d",pc.selectPetNo[ 1 ] );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	sprintf_s( szMoji,"selectPetNo[ 2 ] = %d",pc.selectPetNo[ 2 ] );
	StockFontBuffer( x, y, FONT_PRIO_FRONT, c++, szMoji, 0 );y += 16;

	sprintf_s(szMoji, "selectPetNo[ 3 ] = %d", pc.selectPetNo[3]);
	StockFontBuffer(x, y, FONT_PRIO_FRONT, c++, szMoji, 0); y += 16;

	sprintf_s(szMoji, "selectPetNo[ 4 ] = %d", pc.selectPetNo[4]);
	StockFontBuffer(x, y, FONT_PRIO_FRONT, c++, szMoji, 0); y += 16;

	sprintf_s(szMoji, "BattlePetStMenCnt= %d", BattlePetStMenCnt);
	StockFontBuffer(x, y, FONT_PRIO_FRONT, c++, szMoji, 0); y += 16;

	sprintf_s(szMoji, "BattlePetReceiveFlag= %d", BattlePetReceiveFlag);
	StockFontBuffer(x, y, FONT_PRIO_FRONT, c++, szMoji, 0); y += 16;

}
#endif		

// ?????????��??��??��?
void DisplayFrameRate(void)
{
	// ?��?????��
	if (TimeGetTime() - DrawFrameTime >= 1000){

		// ??????????
		FrameRate = DrawFrameCnt;
		// ???????
		DrawFrameTime = TimeGetTime();
		// ?��??��?????????
		DrawFrameCnt = 0;
	}
}
// ???���� *****************************************************************/
void PutLogo(void)
{
	DispBuffer.DispCnt = 0;
	StockDispBuffer(400, 300, DISP_PRIO_TOP, CG_LOGO, 0);
	ClearBackSurface();	// ???????????????
	PutBmp();			// ????????????????
	Flip();				//
}

void GameErrorMessage(char *buf)
{
#ifdef _STONDEBUG_
	FILE *fp = NULL;

	if( ( fopen_s(&fp, "err.log","a+"))!=NULL ) return;
	if (buf != NULL)
		fprintf(fp, "%s\n", buf);
	fclose(fp);
#endif
}

BOOL InitGame(void)
{
	InitDInput();
#ifdef _REMAKE_20
	DisableCheated();
#ifndef _STONDEBUG_
	RegisterHotKey(hWnd,0,MOD_ALT,VK_TAB);
	RegisterHotKey(hWnd,1,MOD_ALT,VK_ESCAPE);
	InitialInputScript();
	DisableInputScript();
#endif
	RestoreLibrary();
	InitRestore();
	SetTimer(hWnd,0,55,NULL);
#endif
#ifdef _READ16BITBMP
	unsigned int testMMX = 0;
	// ����cpu�Ƿ���MMXָ�
	__asm{
		push eax
			mov eax,1
			CPUID
			mov testMMX, edx
			pop eax
	}
	// ��23��λԪ��Ϊ1��ʾ��MMX
	if (testMMX & 0x00800000) g_bMMXMode = true;
	else g_bMMXMode = false;
#endif
#ifdef _STONDEBUG_
#ifdef _READ16BITBMP
	QueryPerformanceFrequency(&tf);
	iTotalProcTime = 0;
	iTotalRunCount = 0;
#endif
#endif
	util_Init();
	if (InitDirectDraw() == FALSE){
		MessageBoxNew(hWnd, "��ʼ��DirectDrawʧ�ܣ�", "ȷ��", MB_OK | MB_ICONSTOP);
		return FALSE;
	}
	if (InitOffScreenSurface() == FALSE){
		MessageBoxNew(hWnd, "��ʼ��Off Screan Surfaceʧ�ܣ�", "ȷ��", MB_OK | MB_ICONSTOP);
		return FALSE;
	}
	if (InitPalette() == FALSE)
		return FALSE;
	if (initRealbinFileOpen(realBinName, adrnBinName) == FALSE) {
		MessageBoxNew(hWnd, "����Real.binʧ�ܣ�", "ȷ��", MB_OK | MB_ICONSTOP);
		return FALSE;
	}
	//PutLogo();
	initAutoMapColor(adrnBinName);
	if (InitSprBinFileOpen(sprBinName, sprAdrnBinName) == FALSE){
		MessageBoxNew(hWnd, "����Spr.binʧ�ܣ�", "ȷ��", MB_OK | MB_ICONSTOP);
		return FALSE;
	}
#ifdef _READ16BITBMP
	int ref;
	if ((ref = InitRealTruebinFileOpen(realtrueBinName, adrntrueBinName)) < 0){
		if (ref == -1) MessageBoxNew(hWnd, "���� adrntrue.bin ʧ�ܣ�", "ȷ��", MB_OK | MB_ICONSTOP);
		else if (ref == -2) MessageBoxNew(hWnd, "���� realtrue.bin ʧ�ܣ�", "ȷ��", MB_OK | MB_ICONSTOP);
		return FALSE;
	}
#endif

#ifdef _PTTERN_SEPARATION_BIN
#ifdef _SA_VERSION_25
	InitPteernSeparationBin(".//path");
#endif
#endif

#ifdef _WIN_LUAJIT_
	memset(gmsv, 0, sizeof(gameserver)*MAX_GMSV);
	memset(gmgroup, 0, sizeof(gamegroup)*MAX_GMGROUP);
	extern void LoadStoneAgeLUA(char *path);
	LoadStoneAgeLUA(_LUA_PATCH_);
#endif
	InitAction();
	InitFont(0);
	srand(TimeGetTime());
	initRand2();
	t_music_init();

	if (!InitIme(hWnd, StrToNowStrBuffer)){
		MessageBoxNew(hWnd, "��ʼ�����뷨ʧ�ܣ�", "ȷ��", MB_OK | MB_ICONSTOP);
		return FALSE;
	}
	MouseInit();
	if (loadUserSetting() == FALSE){
		char msg[1024];
		sprintf_s(msg, SAVE_ERRMSG_loadNowState, savedataErrorCode);
		MessageBoxNew(hWnd, msg, "ȷ��", MB_OK | MB_ICONSTOP);
		return FALSE;
	}
	LoadChatRegistyStr();
	NowTime = TimeGetTime();
	DrawFrameTime = TimeGetTime();
	if (MouseCursorFlag == FALSE){
#ifdef _TALK_WINDOW
		g_iCursorCount = ShowCursor(FALSE);
#else
		ShowCursor(FALSE);
#endif
	}

	ProcNo2 = -1;
#ifdef __NEW_CLIENT_MEM
#ifndef __NEW_CLIENT_ONLY_WRITE
	if (!net_readbuf){
		if (!(net_readbuf = (char*)VirtualAlloc(NULL, NETBUFSIZ, MEM_COMMIT, PAGE_READWRITE))){
			MessageBoxNew(hWnd, "net_readbuf Init ʧ��!", "ȷ��", MB_OK | MB_ICONSTOP);
			return FALSE;
		}
	}
#else
	if( !net_readbuf){
		if( !(net_readbuf=(char*)VirtualAlloc( NULL, NETBUFSIZ, MEM_COMMIT, PAGE_NOACCESS))){
			MessageBoxNew( hWnd, "net_readbuf Init ʧ��!", "ȷ��", MB_OK | MB_ICONSTOP );
			return FALSE;
		}
	}
#endif
	if (!net_writebuf){
		if (!(net_writebuf = (char*)VirtualAlloc(NULL, NETBUFSIZ, MEM_COMMIT, PAGE_NOACCESS))){
			MessageBoxNew(hWnd, "net_writebuf Init ʧ��!", "ȷ��", MB_OK | MB_ICONSTOP);
			return FALSE;
		}
	}
#else
	if (!net_readbuf){
		if (!(net_readbuf = (char*)VirtualAlloc(NULL, NETBUFSIZ, MEM_COMMIT, PAGE_READWRITE))){
			MessageBoxNew(hWnd, "net_readbuf Init ʧ��!", "ȷ��", MB_OK | MB_ICONSTOP);
			return FALSE;
		}
	}
	if (!net_writebuf){
		if (!(net_writebuf = (char*)VirtualAlloc(NULL, NETBUFSIZ, MEM_COMMIT, PAGE_READWRITE))){
			MessageBoxNew(hWnd, "net_writebuf Init ʧ��!", "ȷ��", MB_OK | MB_ICONSTOP);
			return FALSE;
		}
	}
#endif
#ifdef _CHANNEL_MODIFY
	CreateDirectory("chat\\", NULL);
#endif
	return TRUE;
}

#ifdef _CHANNEL_MODIFY
void SaveChatData(char *msg, char KindOfChannel, bool bCloseFile);
#endif

void EndGame(void)
{
#ifdef __NEW_CLIENT
	extern HANDLE hPing;
	extern SOCKET sockRaw;
	if (hPing){
		closesocket(sockRaw);
		sockRaw = INVALID_SOCKET;
		TerminateThread(hPing, 0);
		CloseHandle(hPing);
		hPing = NULL;
	}
#endif
	if (net_readbuf){
		VirtualFree(net_readbuf, NULL, MEM_RELEASE);
		net_readbuf = NULL;
	}
	if (net_writebuf){
		VirtualFree(net_writebuf, NULL, MEM_RELEASE);
		net_writebuf = NULL;
	}
	//DirectDraw ?��
	ReleaseDirectDraw();
	// ???????????��
	EndDInput();
	// DirectSound ?��
	t_music_end();
	// ????�_��
	cdda_stop();
	// Rialbin ��??
	cleanupRealbin();
	// ????????????��
	DeleteObject(hFont);
	// ????��?
	EndIme();
	// ?????��???
	EndAction();
	// ??????��???
	cleanupNetwork();
	// �i??�h???????????��
	ReleaseMutex(hMutex);
	// ????????
	saveUserSetting();
	// ?????�K?��??��V
	SaveChatRegistyStr();

	// ????��?
	//	timeKillEvent(timerId);

	//{
	// ALT+TAB ?????
	//	int nOldVal;
	//	SystemParametersInfo (SPI_SCREENSAVERRUNNING, FALSE, &nOldVal, 0);
	//}
#ifdef _CHANNEL_MODIFY
	SaveChatData(NULL, 0, true);
#endif
#ifdef _REMAKE_20
#ifndef _STONDEBUG_
	UnregisterHotKey(hWnd, 0);
	UnregisterHotKey(hWnd, 1);
#endif
#endif
	util_Release();
}
#ifdef _CMD_MODE


HANDLE hConsoleThread;
DWORD ConsoleThreadID;
volatile BOOL m_bRun;

void ConsoleThread(void)
{
	char cmd[256];
	memset(cmd,0,sizeof(cmd));
	int c,i;

	while(m_bRun)
	{
		printf("\nʯ��ʱ��>");
		i = 0;
		while( (c = getchar()) != '\n')
		{
			cmd[i] = c;
			i++;
		}
		//cmd[i] = '\0';
		fflush(stdin);

		if( strcmp(cmd,"q") == 0)
		{
			m_bRun = FALSE;
			FreeConsole();
			ExitThread(ConsoleThreadID);
			return;
		}
		if( cmd[0] == 'a' && cmd[1] == ' ')
		{
			int level;
			sscanf_s(cmd,"a %i",&level);
			if( level >= 0 && level <= 14)
			{
				//Patch_Accelerate(level);
				printf("SUCCESS: Acceleration level has been switched to %i.", level);
				continue;
			}
			else
			{
				printf("ERROR: Acceleration level out of range(0-14).");
				continue;
			}
		}
		if( cmd[0] == 'l' && cmd[1] == ' ')
		{
			char addr[32];
			char port[6];
			char* p,*next_p;
			p = NULL;
			next_p = NULL;
			p = strtok_s(cmd," ",&next_p);
			if(p)
			{
				p = strtok_s(NULL," ",&next_p);
				if(p)
				{
					sprintf_s(addr,sizeof(addr),p);
					p = strtok_s(NULL," ",&next_p);
					if(p)
					{
						if(strtok_s(NULL," ",&next_p))
						{
							continue;
						}
						else
						{
							sprintf_s(port,sizeof(port),p);
							printf("%s %s",addr,port);
							continue;
						}
					}
					else
					{
						continue;
					}
				}
				else
				{
					continue;
				}
			}
		}
	}
}


void InitConsoleWindow(void)  
{  
	int hCrt;
	FILE *hf;


	AllocConsole();
	SetConsoleTitle("ʯ��ʱ��");

	hCrt = _open_osfhandle(
		(long)GetStdHandle(STD_OUTPUT_HANDLE),O_TEXT );
	hf = _fdopen( hCrt, "w" );

	*stdout = *hf;
	setvbuf( stdout, NULL, _IONBF, 0 );

	hCrt = _open_osfhandle(
		(long)GetStdHandle(STD_INPUT_HANDLE),
		_O_TEXT );
	hf = _fdopen( hCrt, "r" );

	*stdin = *hf;
	setvbuf( stdin, NULL, _IONBF, 0 );


	printf("\
		   		   		   		   		   		   ===================================\n\
												   										   								   						   				   		   ====  Console for StoneAge     ====\n\
																																										   																														   																				   												   						   		   ====      USE \"h\" FOR HELP     ====\n\
																																																																																																																   																																																																						   																																								   																				   								   		   ===================================\n\
																																																																																																																																																																																																																																																												   																																																																																																																																												   																																																																						   																														   										   		   /*----------COMMAND LINE---------*/");

	hConsoleThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ConsoleThread, NULL, 0, &ConsoleThreadID);
	if (hConsoleThread != NULL)
		m_bRun = TRUE;
}

#endif

