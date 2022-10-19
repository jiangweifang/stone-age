/************************/
/*	battleMenu.h		*/
/************************/
#ifndef _BATTLE_MENU_H_
#define _BATTLE_MENU_H_

#define AI_NONE		0
#define AI_ATTACK	1
#define AI_GUARD	2
#define AI_SELECT	3
#define AI_ESCAPE	4

extern int AI;
extern DWORD PauseAI;

// BattleBpFlag????�ѩ�
#define BATTLE_BP_JOIN				( 1 << 0 )		// �ӡP
#define BATTLE_BP_PLAYER_MENU_NON	( 1 << 1 )		// ???????????
#define BATTLE_BP_BOOMERANG			( 1 << 2 )		// ?????
#define BATTLE_BP_PET_MENU_NON		( 1 << 3 )		// ?????????
#define BATTLE_BP_ENEMY_SURPRISAL	( 1 << 4 )		// ��?��?�e?????��???????
#define BATTLE_BP_PLAYER_SURPRISAL	( 1 << 5 )		// ??????��?�e?????

// ??????????
#define BATTLE_BUF_SIZE	4
#define BATTLE_COMMAND_SIZE			4096
// ???????��??
extern char BattleCmd[ BATTLE_COMMAND_SIZE ];
extern char BattleCmdBak[ BATTLE_BUF_SIZE ][ BATTLE_COMMAND_SIZE ];
// ???????��???????
extern int BattleCmdReadPointer;
extern int BattleCmdWritePointer;
// ???????��????????
//extern char BattleCmdBak[];
// ???�֢t��??
extern char BattleStatus[ BATTLE_COMMAND_SIZE ];
extern char BattleStatusBak[ BATTLE_BUF_SIZE ][ BATTLE_COMMAND_SIZE ];
// ???�֢t��???????
extern int BattleStatusReadPointer;
extern int BattleStatusWritePointer;

// ???�֢t��????????
//extern char BattleStatusBak[];
// ???�֢t��????????
//extern char BattleStatusBak2[];
// ??????????
extern int battleMenuFlag2;
// ����?��?�k?
extern int BattleMyNo;
// �P�f??����???
extern int BattleMyMp;
// �P�f?����????
extern int BattleEscFlag;
// ????????????
extern int BattlePetStMenCnt;
// �ӡP???�k???????
extern int battlePetNoBak;
// �ӡP???�k????????
extern int battlePetNoBak2;

// ?????
extern int BattleBpFlag;
// ????�V??????
extern int BattleAnimFlag;
// ???����???
extern BOOL BattleTurnReceiveFlag;
#ifdef PK_SYSTEM_TIMER_BY_ZHU
extern BOOL BattleCntDownRest;
extern BOOL SendToServer;
extern DWORD BattleCntDown;
#define BATTLE_CNT_DOWN_TIME 30000
#endif
extern int BattleCliTurnNo;
// ??????????�k?
extern int BattleSvTurnNo;

// �P�f??????????
extern BOOL BattleResultWndFlag;

#ifdef	_HUNDRED_KILL
extern BOOL BattleHundredFlag;
#endif

// ????????? *********************************************************/
void BattleMenuProc( void );
// ??????�u???  *****************************************************/
void ClearBattleButton( void );
// ?????????? ********************************************************/
void InitBattleMenu( void );
// ????�V??????????? ********************************************/
void CheckBattleAnimFlag( void );
// ?��??�K��?????? ********************************************/
int CheckBattle1P2P( void );
// �o??????���� ***********************************************************/
void HpMeterDisp( int no );
// ���q?���� ************************************************************************/
void BattleNameDisp( void );
#ifdef _BATTLESKILL				// (���ɿ�) Syu ADD ս�����ܽ���
void BattleSetWazaHitBox( int no , int typeflag ) ;
#endif
#ifdef PK_SYSTEM_TIMER_BY_ZHU
void BattleDown();
#endif
void battleMenuFix(void);		// �޸�ս��AIת����BUG

#endif

