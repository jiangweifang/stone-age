#ifndef _NETPROC_H_
#define _NETPROC_H_

#ifdef _THEATER
enum
{
    E_DATA_TYPE_PLAYER,		// ���
    E_DATA_TYPE_TALK,		// ̨�� 
    E_DATA_TYPE_ASIDE,		// �԰�
    E_DATA_TYPE_ACTION,		// ����
    E_DATA_TYPE_MOVE,		// �ƶ�
    E_DATA_TYPE_SCENERY,	// ����
    E_DATA_TYPE_CHANGE,		// ����
    E_DATA_TYPE_DIR,		// ����
    E_DATA_TYPE_EFFECT,		// ��Ч
    E_DATA_TYPE_FACE,		// ����
    E_DATA_TYPE_NOTE,		// ע��
    E_DATA_TYPE_BGM,		// ��������
	E_DATA_TYPE_NPC,		// NPC
    E_DATA_TYPE_END
};

// lssproto_TheaterData_recv ʹ��
enum
{
	E_THEATER_SEND_DATA_THEATER_MODE = E_DATA_TYPE_END + 1,	// ��Ժģʽ ����: 0:ȡ���糡ģʽ 1:���� 2:������
	E_THEATER_SEND_DATA_DISPLAY_SCORE,						// ��ʾ���� ����: ����
	E_THEATER_SEND_DATA_END
};
#endif

extern short selectServerIndex;
extern short clientLoginStatus;
extern short charListStatus;
extern short charDelStatus;

#ifdef _NPC_MAGICCARD
extern bool bShowflag[20];
extern int iPosition[20];	
extern int iShowdamage[20];
extern int iOffsetY[20];
extern int ioffsetsx;
extern int ioffsetsy;
extern unsigned int inextexet ;
#endif

extern char gamestate_chooseserver_name[];
extern char gamestate_login_charname[];
extern char gamestate_deletechar_charname[];

extern char netprocErrmsg[];

extern int connectServer2Counter;
/*
#ifdef _TELLCHANNEL				// (���ɿ�) ROG ADD ����Ƶ��
extern char ReTellName[];
#endif
*/
void initConnectServer( void );
int ConnectWGS();
int connectServer( void );

void charListStart( void );
int  charListProc( void );
void charLoginStart( void );
int charLoginProc( void );

void createNewCharStart( void );
int createNewCharProc( void );

void charLogoutStart( void );
int charLogoutProc( void );

void walkSendForServer( int, int, char * );
void noChecksumWalkSendForServer( int, int, char * );

void chatStrSendForServer( char *, int );

void delCharStart( void );
int delCharProc( void );

#ifdef _PK2007
void pkListStart( void );
int  pkListProc( void );
#endif

#endif  /* ifndef _NETPROC_H_ */
