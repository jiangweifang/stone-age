#ifndef _FIELD_H_ 
#define _FIELD_H_

#include<time.h>

// ?��????��?��????
#define FIELD_BTN_PUSH_WAIT			500		// 0.5��

// ???????����??
#define FIELD_MAIL_LAMP_FLASH_TIME	1000	// 1��??

enum
{
	FIELD_FUNC_MENU,
	FIELD_FUNC_CARD,
	FIELD_FUNC_PARTY,
	FIELD_FUNC_JOIN_BATTLE,
	FIELD_FUNC_DUEL,
	FIELD_FUNC_ACT,
	FIELD_FUNC_TRADE,	// Robin 04/12 trade
	FIELD_FUNC_CHANNEL,
#ifdef __HELP
	FIELD_FUNC_HELP,	//CARY
#endif
#ifdef __PHONEMESSAGE
	FIELD_FUNC_MSG,     //LeiBoy
#endif
#ifdef _STREET_VENDOR
	FIELD_FUNC_STREET_VENDOR,
#else
	#ifdef _TABLEOFSKILL
	FIELD_FUNC_SKILL,
	#endif
#endif

#ifdef _FRIENDCHANNEL			//ROG ADD ����Ƶ��
	FIELD_FUNC_CHATROOM,
#endif

#ifdef _ANGEL_SUMMON
	FIELD_FUNC_ANGEL,
#endif

#ifdef _TEACHER_SYSTEM
	FIELD_FUNC_TEACHER,
#endif
#ifdef _MO_SIGN_IN
	FIELD_FUNC_SIGNIN,						
#endif 
#ifdef _NEWSHOP_
	FIELD_FUNC_MARKET,					
#endif
#ifdef _CHANGETEAM_ 
	FIELD_FUNC_CHANGETEAM,
#endif
#ifdef _RED_MEMOY_
	FIELD_FUNC_RED_MEMOY,
#endif
	FIELD_FUNC_END
};

#ifdef _PET_ITEM
typedef struct SPetItemInfo
{
	int bmpNo;										// ͼ��
	int color;										// ������ɫ
	char memo[ITEM_MEMO_LEN+1];						// ˵��
	char name[ITEM_NAME_LEN+1];						// ����
	char damage[16];								// �;ö�
}PetItemInfo;
#endif

#ifdef _STREET_VENDOR
#define MAX_SELL_ITEM 20							// ���߼ӳ��ﹲ������ʮ��
typedef struct _Show_Sell_Item{
	int index;										// ����
	int pile;										// ����
	int price;										// �۸�
	bool needGetPrice;								// �Ƿ�Ҫ�õ��۸�
	bool usage;										// �Ƿ�ʹ����
	char name[ITEM_NAME_LEN+1];						// ����
	char freeName[ITEM_NAME_LEN+1];					// ����
	char kind;										// ���߻��ǳ��� 0:���� 1:����
}Show_Sell_Item;

typedef struct _Show_Vendor_Item{
	int bmpNo;										// ͼ��
	int pile;										// ����
	int price;										// �۸�
	int color;										// ������ɫ
	int level;										// �ȼ�
	int maxhp,attack,defence,dex;					// ��Χ
	int earth,water,fire,wind,fidelity;				// �����Լ��ҳ϶�
	int maxSkill;									// �輼����
	int index;										// ��server�Ĵ���λ��
	bool usage;										// �Ƿ�ʹ����
	bool bBuy;										// �Ƿ�Ҫ��
	bool bGetData;									// �Ƿ��ѽ��յ���ϸ����
	char name[ITEM_NAME_LEN+1];						// ����
	char freeName[ITEM_NAME_LEN+1];					// ����
	char memo[ITEM_MEMO_LEN+1];						// ˵��
	char damage[20];								// �;ö�
	char skillname[MAX_SKILL][SKILL_NAME_LEN+1];	// �輼����
	char kind;										// ���߻��ǳ��� 0:���� 1:����
	char trans;										// ת����
#ifdef _PET_ITEM
	PetItemInfo oPetItemInfo[MAX_PET_ITEM];			// �������ϵĵ���
#endif
#ifdef _NPC_ITEMUP
	int itemup;
#endif
#ifdef _PETCOM_
	int ylv,yhp,yack,ydef,ydex;				            //��ʼ��Χ
#endif
}Show_Vendor_Item;

#endif

#ifdef _JOBDAILY

#define MAXMISSION	300 
typedef struct _JOBDAILY{
	int JobId;								// ������
	char explain[200];						// ����˵��
	char state[10];							// ״̬
}JOBDAILY;

#endif

#ifdef _FRIENDCHANNEL			//ROG ADD ����Ƶ��
	extern short chatRoomBtn;
	extern short SelRoomBtn;
#endif

#ifdef _ANGEL_SUMMON
extern int angelFlag;
extern int angelRecvType;
extern int angelRecvButton;
extern char angelMsg[];
#endif

extern short drawTimeAnimeFlag;

extern short etcSendFlag;

extern short actBtn;
extern short menuBtn;
extern short mailLamp;

extern unsigned int fieldInfoTime;

extern struct tm serverAliveTime;
extern time_t serverAliveLongTime;


void initFieldProc( void );
void resetFieldProc( void );
void fieldProc( void );
void fieldProc2( void );
void drawField( void );

BOOL checkFieldMenuFlag( void );

void closeCharActionAnimeChange( void );
void closeEtcSwitch( void );
void closeJoinChannelWN( void );

int disconnectServer( void );

void drawFieldInfoWin( void );

void actionShortCutKeyProc( void );

#ifdef _SPECIALSPACEANIM	// Syu ADD ���ⳡ����������
	#ifdef _SURFACE_ANIM        //��̬��������ʾ
//#define TOTAL_ANIM 5 //��������
#ifdef _SA_VERSION_25
		#define MAX_ANIM   256 //ͬһ��floor�޶������������
#endif

	#else
		#ifdef _MOON_FAIRYLAND       // ROG ADD ��֮�ɾ�
			#define TOTAL_ANIM 5 //��������
			#define MAX_ANIM   4 //ͬһ��floor���ִ������Anim
		#else
			#define TOTAL_ANIM 1 //��������
			#define MAX_ANIM  1  //ͬһ��floor���ִ������Anim
	#endif
#endif

void SpecAnim ( int ) ; 
void ReleaseSpecAnim( void );

#endif
#endif
