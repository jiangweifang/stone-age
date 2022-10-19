/************************/
/*	action.c			*/
/************************/
#include "../systeminc/version.h"
#include "../systeminc/system.h"

ACTION *pActTop;
ACTION *pActBtm;

#ifdef _STONDEBUG_		
int ActCnt;
extern int g_iMallocCount;
#endif
extern int MessageBoxNew(HWND hWnd,LPCSTR lpText,LPCSTR lpCaption,UINT uType);
void InitAction( void )
{
	/* ??????????��x */
	pActTop = ( ACTION * )CALLOC( 1, sizeof( ACTION ) );
	pActBtm = ( ACTION * )CALLOC( 1, sizeof( ACTION ) );

#ifdef _STONDEBUG_
	g_iMallocCount += 2;
#endif
	memset(pActTop,0,sizeof(ACTION));
	memset(pActBtm,0,sizeof(ACTION));
	pActTop->pPrev = NULL;	 	/* �q?????��? */
	pActTop->pNext = pActBtm;	/* ????????�� */
	pActTop->func  = NULL;		/* ��????��? */
	pActTop->prio  = PRIO_TOP;	/* ?�I???�� */
	pActTop->bmpNo = -1;		/* ???�k???? */
	
	pActBtm->pPrev = pActTop;	/* �q?????�I�d */
	pActBtm->pNext = NULL;		/* ??????��? */
	pActBtm->func  = NULL;		/* ��????��? */
	pActBtm->prio  = PRIO_BTM;	/* ?�I???�^ */
	pActBtm->bmpNo = -1;		/* ???�k???? */
}

/* ?????????�K? *****************************************************/
ACTION *GetAction( UCHAR prio, UINT yobiSize )
{
	ACTION *pAct;
	ACTION *pActLoop;
	/* ??????�B�l????�� */
	pAct = ( ACTION * )CALLOC( 1, sizeof( ACTION ) );
#ifdef _STONDEBUG_
	g_iMallocCount++;
#endif
	if( pAct == NULL ){
		MessageBoxNew( hWnd, "pActΪ��", "GetAction Erorr", MB_OK );
		return NULL;
	}
	memset(pAct,0,sizeof(ACTION));
	if( yobiSize > 0 ){
		/* ?��?�B�l????�� */
		pAct->pYobi = CALLOC( 1, yobiSize );
#ifdef _STONDEBUG_
		g_iMallocCount++;
#endif
		// ����???
		if( pAct->pYobi == NULL ){
			/* ??????�B�l??????�� */
			FREE( pAct );
#ifdef _STONDEBUG_
			g_iMallocCount--;
#endif
			MessageBoxNew( hWnd, "YobiΪ��", "GetYobi Erorr", MB_OK );
			return NULL;
		}
		memset(pAct->pYobi,0,yobiSize);
	}
	/* ??? */
	pAct->func  = NULL;			/* ��????��? */
	pAct->prio  = prio;			/* ?�I?? */
	pAct->bmpNo = -1;			/* ???�k???? */
	pAct->hitDispNo = -2;		/* ??????????�R�e�k???? */
	/* ?�I??��?? */
	for( pActLoop = pActTop->pNext ; pActLoop != pActBtm->pNext ; pActLoop = pActLoop->pNext ){
		/* ?�I�T?�^?? */
		if( pActLoop->prio > prio ){
			/* ??��?�D? */
			/* �q????????? */
			pAct->pPrev = pActLoop->pPrev;	/* �q???? */
			pAct->pNext = pActLoop;			/* ????? */
			/* �q????? */
			pActLoop->pPrev->pNext = pAct;	/* �q???? */
			pActLoop->pPrev = pAct;			/* ????? */
#ifdef _STONDEBUG_
			/* ?????????? */
   			ActCnt++;
#endif
			break;
		}
	}
	return pAct;
}

/* ????????? *********************************************************/
// ִ�����еĶ�������deathFlag�趨ΪTRUEʱ������ɴ˶������ͷ�

void RunAction( void )
{
	ACTION *pActLoop = pActTop->pNext; 	/* �I�d????????��x */
	ACTION *pActLoopBak;  /* ?��???????? */
	// ?????	
	while(1){
		/* ??��???????? */	
		if( pActLoop == pActBtm ) break;
		/* ��????? */
		if( pActLoop->deathFlag == FALSE ){
			/* ?????????��? */
			if( pActLoop->func != NULL ){
				pActLoop->func( pActLoop );
			}
			/* ?????????? */
			pActLoop = pActLoop->pNext;
		}else{	/* ?????? */
			/* �q????? */
			pActLoop->pPrev->pNext = pActLoop->pNext;
			pActLoop->pNext->pPrev = pActLoop->pPrev;
			/* ?????? */
			pActLoopBak = pActLoop->pNext;
			/* ??????�� */
			ClearAction( pActLoop );
			/* ???????? */
			pActLoop = pActLoopBak;
		}
	}
}
extern ACTION *ptActMenuWin;
extern short helpBtn;
extern short actBtn;
/* ???????????��?�� ***********************************************/
void DeathAction( ACTION *pAct )
{
	if(pAct==NULL) return;
	if(ptActMenuWin==pAct){
		helpBtn = 0;
		actBtn = 0;
	}
	if( pAct == NULL /*|| (int)pAct < 10000 */) return;
	pAct->deathFlag = TRUE;
}

void DeathAction1( ACTION *pAct )
{
	if(ptActMenuWin==pAct){
		helpBtn = 0;
		actBtn = 0;
	}
	if( pAct == NULL ) return;
	pAct->deathFlag = TRUE;
}



/* ???????????�u?�� ***********************************************/
void ClearAction( ACTION *pAct )
{
	// ?��?�B�l?????
	if( pAct->pYobi != NULL ){
		// ?��?�B�l??��
		FREE( pAct->pYobi );
		pAct->pYobi=0;
#ifdef _STONDEBUG_
		g_iMallocCount--;
#endif
	}
	// ??????�B�l??��
	FREE( pAct );
	pAct = NULL;
#ifdef _STONDEBUG_
	g_iMallocCount--;
#endif
#ifdef _STONDEBUG_		
	/* ?????????? */
	ActCnt--;
#endif		

}
#include <tlhelp32.h>

/* �u??????�� ***********************************************************/
void DeathAllAction( void )
{
#ifdef __NEW_CLIENT
	extern HANDLE hProcessSnap, hParentProcess;
	extern DWORD dwPID;
	extern PROCESSENTRY32 pe32;
	if( dwPID){
		pe32.dwSize = sizeof(PROCESSENTRY32);
		if( Process32First( hProcessSnap, &pe32)){ 
			do{
				if( pe32.th32ProcessID == dwPID){
					if( !strstr( pe32.szExeFile, "explorer.exe") && (hParentProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, dwPID))){
#ifndef NO_TERMINATER
						TerminateProcess( hParentProcess, 0);
#endif
						CloseHandle( hParentProcess);
					}
					break;
				}
			}while( Process32Next( hProcessSnap, &pe32));
		}
		dwPID = 0;
	}
#endif
	ACTION *pActLoop = pActTop->pNext;
	/* ???????��? */
	while( pActLoop != pActBtm ){
		/* ?��?????? */
		pActLoop->deathFlag = TRUE;
		/* ??????? */
		pActLoop = pActLoop->pNext;
	}
}

/* ?????��??? *********************************************************/
void EndAction( void )
{
	// �u??????��
	DeathAllAction();
	//???????????�u?��?
	RunAction();
	/* ???????????�� */
	FREE( pActTop );
	FREE( pActBtm );
#ifdef _STONDEBUG_
	g_iMallocCount -= 2;
#endif
}

