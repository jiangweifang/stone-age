#ifndef _PC_H_ 
#define _PC_H_

#include "action.h"
#ifdef _MORECHARACTERS_
#define MAXCHARACTER			4
#else
#define MAXCHARACTER			2
#endif
#define CHAR_NAME_LEN			16
#define CHAR_FREENAME_LEN		32
#define MAGIC_NAME_LEN			28
#define MAGIC_MEMO_LEN			72
#define ITEM_NAME_LEN			28
#define ITEM_NAME2_LEN			16
#define ITEM_MEMO_LEN			84
#define PET_NAME_LEN			16
#define PET_FREENAME_LEN		32
#define CHAR_FMNAME_LEN			33      // ��������

#ifdef _CHAR_PROFESSION			// WON ADD ����ְҵ
#define PROFESSION_MEMO_LEN		84
#endif

#ifdef _GM_IDENTIFY		// Rog ADD GMʶ��
#define GM_NAME_LEN		        32
#endif

//#define CHARNAMELEN				256		// ???????

#define MAX_PET					5

#define MAX_MAGIC				9

#define MAX_PARTY				5

#define	MAX_ADR_BOOK_COUNT		4
#ifdef _EXTEND_AB
	#define	MAX_ADR_BOOK_PAGE		20//20  //10   20050214 cyg 10 add to 20
#else
	#define	MAX_ADR_BOOK_PAGE		10
#endif
#define MAX_ADR_BOOK			(MAX_ADR_BOOK_COUNT*MAX_ADR_BOOK_PAGE)

#ifdef _ITEM_EQUITSPACE
typedef enum
{
    CHAR_HEAD,               
    CHAR_BODY, 
    CHAR_ARM,
    CHAR_DECORATION1,
    CHAR_DECORATION2,

#ifdef _ITEM_EQUITSPACE
	CHAR_EQBELT,
	CHAR_EQSHIELD,
	CHAR_EQSHOES,
#endif

#ifdef _EQUIT_NEWGLOVE
	CHAR_EQGLOVE,
#endif
    CHAR_EQUIPPLACENUM,
#ifdef _PET_ITEM
	PET_HEAD = 0,	// ͷ
	PET_WING,		// ��
	PET_TOOTH,		// ��
	PET_PLATE,		// ����
	PET_BACK,		// ��
	PET_CLAW,		// צ
	PET_FOOT,		// ��(��)
	PET_EQUIPNUM
#endif
}CHAR_EquipPlace;

#ifdef _PET_ITEM
typedef enum
{
// �������,������
	ITEM_PET_HEAD = 29,		// ͷ
	ITEM_PET_WING,			// ��
	ITEM_PET_TOOTH,			// ��
	ITEM_PET_PLATE,			// ���廤��
	ITEM_PET_BACK,			// ��������
	ITEM_PET_CLAW,			// צ
	ITEM_PET_1_FOOT,		// �Ų�,˫��
	ITEM_PET_2_FOOT,		// �Ų�,����
	ITEM_PET_FIN,			// �Ų�,��
	ITEM_CATEGORYNUM  
}ITEM_CATEGORY;
#define MAX_PET_ITEM	7
#endif

#define MAX_ITEMSTART CHAR_EQUIPPLACENUM
#define MAX_MAXHAVEITEM	15
#ifdef _NEW_ITEM_
#define MAX_ITEM (MAX_ITEMSTART+MAX_MAXHAVEITEM*3)
int �ж���ҵ�������();
#else
#define MAX_ITEM (MAX_ITEMSTART+MAX_MAXHAVEITEM)
#endif
#else
#define MAX_ITEMSTART 5
#define MAX_ITEM				20
#endif

#define RESULT_ITEM_COUNT		3
#define RESULT_ITEM_NAME_LEN	24
//#define RESULT_CHR_EXP			4
#define RESULT_CHR_EXP			5

#define SKILL_NAME_LEN			24
#define SKILL_MEMO_LEN			72
#define MAX_SKILL				7



#define MAX_GOLD				1000000
#define MAX_BANKGOLD			10000000
#define MAX_FMBANKGOLD			100000000


#define MAX_PERSONAL_BANKGOLD 50000000

#ifdef _FMVER21
#define FAMILY_MAXMEMBER                100     // ��������
#else
#define FAMILY_MAXMEMBER                50     // ��������
#endif

enum
{
	PC_ETCFLAG_PARTY		= (1 << 0),
	PC_ETCFLAG_DUEL			= (1 << 1),
	PC_ETCFLAG_CHAT_MODE	= (1 << 2),		//����Ƶ������
	PC_ETCFLAG_MAIL			= (1 << 3),       //��ƬƵ��
	PC_ETCFLAG_TRADE		= (1 << 4)
#ifdef _CHANNEL_MODIFY
	,PC_ETCFLAG_CHAT_TELL = (1 << 5)			//����Ƶ������
	,PC_ETCFLAG_CHAT_FM		= (1 << 6)			//����Ƶ������
#ifdef _CHAR_PROFESSION
	,PC_ETCFLAG_CHAT_OCC	= (1 << 7)			//ְҵƵ������
#endif
	,PC_ETCFLAG_CHAT_SAVE	=	(1 << 8)			//�Ի����濪��
#ifdef _CHATROOMPROTOCOL
	,PC_ETCFLAG_CHAT_CHAT	=	(1 << 9)			//�����ҿ���
#endif
#endif
#ifdef _CHANNEL_WORLD
	,PC_ETCFLAG_CHAT_WORLD	=	(1 << 10)			//����Ƶ������
#endif
#ifdef _CHANNEL_ALL_SERV
	,PC_ETCFLAG_ALL_SERV	=	(1 << 11)			//����Ƶ������
#endif
	,PC_AI_MOD = (1 << 12)
};

enum
{
	PC_ETCFLAG_CHAT_MODE_ID = 0
	
#ifdef _CHANNEL_MODIFY
	,PC_ETCFLAG_CHAT_TELL_ID		//����Ƶ��
	,PC_ETCFLAG_CHAT_PARTY_ID		//����Ƶ��
	,PC_ETCFLAG_CHAT_FM_ID			//����Ƶ��
#ifdef _CHAR_PROFESSION
	,PC_ETCFLAG_CHAT_OCC_ID			//ְҵƵ��
#endif
#ifdef _CHATROOMPROTOCOL
	,PC_ETCFLAG_CHAT_CHAT_ID		//������
#endif
#else
	,PC_ETCFLAG_CHAT_PARTY_ID		//����Ƶ��
#endif
#ifdef _CHANNEL_WORLD
	,PC_ETCFLAG_CHAT_WORLD_ID			//����Ƶ��
#endif
#ifdef _CHANNEL_ALL_SERV
	,PC_ETCFLAG_ALL_SERV_ID			//����Ƶ������
#endif
	,PC_ETCFLAG_CHAT_WORLD_NUM
};

#define ITEM_FLAG_PET_MAIL		( 1 << 0 )
#define ITEM_FLAG_MIX			( 1 << 1 )
#define ITEM_FLAG_COOKING_MIX	( 1 << 2 )
#define ITEM_FLAG_METAL_MIX		( 1 << 3 )	//����
#define ITEM_FLAG_JEWEL_MIX		( 1 << 4 )	//��ʯ
#define ITEM_FLAG_FIX_MIX		( 1 << 5 )	//�޸�
#ifdef _ITEM_INTENSIFY
#define ITEM_FLAG_INTENSIFY_MIX ( 1 << 6 )	//ǿ��
#endif
#ifdef _ITEM_UPINSLAY
#define ITEM_FLAG_UPINSLAY_MIX ( 1 << 7 )	//���
#endif

typedef struct
{
	int color;						// ���q?��
	int graNo;						// ??�k?
	int level;						// ???????
#ifdef _ITEM_PILENUMS
	int pile;
#endif
#ifdef _ALCHEMIST //#ifdef _ITEMSET7_TXT
	char alch[4+200];
#endif
	short useFlag;					// ��????
	short field;					// ��????��?
	short target;					// �n��
	short deadTargetFlag;			// ???????�n��???
	short sendFlag;					// ????????��?�u?
	char name[ITEM_NAME_LEN*2+1];		// ????��
	char name2[ITEM_NAME2_LEN*2+1];	// ????��?
	char memo[ITEM_MEMO_LEN*2+1];		// ??
	char damage[20];
#ifdef _PET_ITEM
	char type;
#endif
#ifdef _ITEM_JIGSAW
	char jigsaw[50];
#endif
#ifdef _NPC_ITEMUP
	int itemup;
#endif
#ifdef _ITEM_COUNTDOWN
	int counttime;
#endif
#ifdef _MAGIC_ITEM_
	int ��������;
#endif
} ITEM;

typedef struct
{
	int graNo;
	int faceGraNo;
	int id;
	int dir;
	int hp, maxHp;
	int mp, maxMp;
	int vital;
	int str, tgh, dex;
	int exp, maxExp;
	int level;
	int atk, def;
	int quick, charm, luck;
	int earth, water, fire, wind;
	int gold;
#ifdef _NEW_MANOR_LAW
	int fame;
#endif
	int titleNo;
	int dp;
	char name[CHAR_NAME_LEN+1];
	char freeName[CHAR_FREENAME_LEN+1];
	short nameColor;
#ifdef _ANGEL_SUMMON
	unsigned status;
#else
	unsigned short status;
#endif
	unsigned short etcFlag;
	short battlePetNo;
	short selectPetNo[MAX_PET];
	short mailPetNo;
#ifdef _STANDBYPET
	short standbyPet;
#endif
	int battleNo;
	short sideNo;
	short helpMode;
	ITEM item[MAX_ITEM];
	ACTION *ptAct;
	int pcNameColor;
	short transmigration;
	char chusheng[61];
	char familyName[CHAR_NAME_LEN+1];
	int familyleader;
	int channel;
	int quickChannel;
	int personal_bankgold;
	int ridePetNo;//��������
	int learnride;
	unsigned int lowsride;
	char ridePetName[CHAR_FREENAME_LEN+1];
	int ridePetLevel;
	int familySprite;
	int baseGraNo;
	ITEM itempool[MAX_ITEM];
	int big4fm;
	int trade_confirm;         // 1 -> ��ʼֵ
	                           // 2 -> �[�ҷ�����ȷ����
	                           // 3 -> ���Է�����ȷ����
	                           // 4 -> ˫���԰���ȷ����

#ifdef _CHAR_PROFESSION			// WON ADD ����ְҵ
	int profession_class;
	int profession_level;
//	int profession_exp;
	int profession_skill_point;	
	char profession_class_name[32];
#endif	
#ifdef _ALLDOMAN // (���ɿ�) Syu ADD ���а�NPC
	int herofloor;
#endif

#ifdef _GM_IDENTIFY		// Rog ADD GMʶ��
	char gm_name[GM_NAME_LEN+1];
#endif

#ifdef _FRIENDCHANNEL  // ROG ADD ����Ƶ��
	char  chatRoomNum[4];
#endif
#ifdef _STREET_VENDOR
	int iOnStreetVendor;		// ��̯ģʽ
#endif
	int skywalker; // GM������??
#ifdef _MOVE_SCREEN
	BOOL	bMoveScreenMode;	// �ƶ�ӫĻģʽ
	BOOL	bCanUseMouse;		// �Ƿ����ʹ�û����ƶ�
	int		iDestX;				// Ŀ��� X ����
	int		iDestY;				// Ŀ��� Y ����
#endif
#ifdef _THEATER
	int		iTheaterMode;		// �糡ģʽ
	int		iSceneryNumber;		// ��¼��Ժ����ͼ��
	ACTION	*pActNPC[5];		// ��¼�糡����ʱ����������NPC
#endif
#ifdef _NPC_DANCE
	int     iDanceMode;			// ��һ��ģʽ
#endif
#ifdef _EVIL_KILL
	int     newfame; // �ַ�ħ������
	short   ftype;
#endif

	int debugmode;
#ifdef _SFUMATO
	int sfumato;		// ������Ⱦͼ��ɫ��
#endif
#ifdef _NEW_ITEM_
	int ������״̬;
#endif
#ifdef _CHARSIGNADY_NO_
	int ǩ�����;
#endif
#ifdef _MAGIC_ITEM_
	int ��������״̬;
	int ���߹⻷Ч��;
#endif
} PC;

#ifdef _FMVER21
enum
{
	FMMEMBER_NONE   = -1,  // δ�����κμ���
    FMMEMBER_MEMBER = 1,   // һ���Ա
	FMMEMBER_APPLY,        // ����������
    FMMEMBER_LEADER,       // �����峤        
	FMMEMBER_ELDER,        // ����
    //FMMEMBER_INVITE,     // ��˾
    //FMMEMBER_BAILEE,     // ����
    //FMMEMBER_VICELEADER, // ���峤
	FMMEMBER_NUMBER,
};
#endif

enum
{
	MAGIC_FIELD_ALL,
	MAGIC_FIELD_BATTLE,
	MAGIC_FIELD_MAP
};

enum
{
	MAGIC_TARGET_MYSELF,
	MAGIC_TARGET_OTHER,
	MAGIC_TARGET_ALLMYSIDE,
	MAGIC_TARGET_ALLOTHERSIDE,
	MAGIC_TARGET_ALL,
	MAGIC_TARGET_NONE,
	MAGIC_TARGET_OTHERWITHOUTMYSELF,
	MAGIC_TARGET_WITHOUTMYSELFANDPET,
	MAGIC_TARGET_WHOLEOTHERSIDE,
	#ifdef __ATTACK_MAGIC
	MAGIC_TARGET_SINGLE,				// ��Եз�ĳһ��
	MAGIC_TARGET_ONE_ROW,				// ��Եз�ĳһ��
	MAGIC_TARGET_ALL_ROWS,				// ��Եз�������
	#endif
};

enum
{
	PETSKILL_FIELD_ALL,
	PETSKILL_FIELD_BATTLE,
	PETSKILL_FIELD_MAP
};

enum
{
	PETSKILL_TARGET_MYSELF,
	PETSKILL_TARGET_OTHER,
	PETSKILL_TARGET_ALLMYSIDE,
	PETSKILL_TARGET_ALLOTHERSIDE,
	PETSKILL_TARGET_ALL,
	PETSKILL_TARGET_NONE,
	PETSKILL_TARGET_OTHERWITHOUTMYSELF,
	PETSKILL_TARGET_WITHOUTMYSELFANDPET
#ifdef _BATTLESKILL				// (���ɿ�) Syu ADD ս�����ܽ���
	,PETSKILL_TARGET_ONE_ROW
	,PETSKILL_TARGET_ONE_LINE
	,PETSKILL_TARGER_DEATH
#endif
#ifdef _SKILL_ADDBARRIER
	,PETSKILL_TARGET_ONE_ROW_ALL //ѡ�ҷ��ĵ���
#endif
};

enum
{
	ITEM_FIELD_ALL,
	ITEM_FIELD_BATTLE,
	ITEM_FIELD_MAP,
};

enum
{
	ITEM_TARGET_MYSELF,
	ITEM_TARGET_OTHER,
	ITEM_TARGET_ALLMYSIDE,
	ITEM_TARGET_ALLOTHERSIDE,
	ITEM_TARGET_ALL,
	ITEM_TARGET_NONE,
	ITEM_TARGET_OTHERWITHOUTMYSELF,
	ITEM_TARGET_WITHOUTMYSELFANDPET,
#ifdef _PET_ITEM
	ITEM_TARGET_PET
#endif
};

typedef struct
{
	int index;						//λ��
	int graNo;						// ??�k?
	int hp, maxHp;					// ????��??
	int mp, maxMp;					// ????��??
	int exp, maxExp;				// ??�k???????��????�k
	int level;						// ???
	int atk, def;					// ????????�\??
	int quick;						// �զ�?
	int ai;							// ?�ߥT
	int earth, water, fire, wind;	// ��???
	int maxSkill;					// ?��????
	int trn;						// ����ת����
#ifdef _SHOW_FUSION
	int fusion;						// low word: �走���, hi word: ���ֱ���
#endif
#ifdef _ANGEL_SUMMON
	unsigned status;
#else
	unsigned short status;			// ?????(??????)
#endif
	char name[CHAR_NAME_LEN+1];		// ��?��
	char freeName[PET_NAME_LEN+1];	// ???????���q
	short useFlag;					// ??????????????
	short changeNameFlag;			// ���q?????????
#ifdef _PET_ITEM
	ITEM item[MAX_PET_ITEM];		// �������
#endif
#ifdef _PETCOM_
	int oldlevel,oldhp,oldatk,oldquick,olddef;
#endif
#ifdef _RIDEPET_
	int rideflg;
#endif
#ifdef _PETBLESS_
	int blessflg;
	int blesshp;
	int blessatk;
	int blessquick;
	int blessdef;
#endif
} PET;


typedef struct
{
	short useFlag;
	int mp;
	short field;
	short target;
	short deadTargetFlag;
	char name[MAGIC_NAME_LEN+1];
	char memo[MAGIC_MEMO_LEN+1];
} MAGIC;


typedef struct
{
	short useFlag;
	int id;
	int level;
	int maxHp;
	int hp;
	int mp;
	char name[CHAR_NAME_LEN+1];
	ACTION *ptAct;
} PARTY;


typedef struct
{
	short useFlag;
	short onlineFlag;
	int level;
	short transmigration;
	int dp;
	int graNo;
	char name[CHAR_NAME_LEN+1];
#ifdef _MAILSHOWPLANET				// (�ɿ���) Syu ADD ��ʾ��Ƭ����
	char planetname[64];
#endif
} ADDRESS_BOOK;


typedef struct
{
	short petNo;
	short levelUp;
	int exp;
} BATTLE_RESULT_CHR;

typedef struct
{
	short useFlag;
	BATTLE_RESULT_CHR resChr[RESULT_CHR_EXP];
	char item[RESULT_ITEM_COUNT][RESULT_ITEM_NAME_LEN+1];
} BATTLE_RESULT_MSG;


typedef struct
{
	short useFlag;
	short skillId;
	short field;
	short target;
	char name[SKILL_NAME_LEN+1];
	char memo[SKILL_MEMO_LEN+1];
} PET_SKILL;

#ifdef _CHAR_PROFESSION			// WON ADD ����ְҵ
typedef struct
{
	short useFlag;
	short skillId;
	short target;
	short kind;
	char name[PROFESSION_MEMO_LEN+1];
	char memo[PROFESSION_MEMO_LEN+1];
	int icon;
	int costmp;
	int skill_level;
#ifdef _PRO3_ADDSKILL
	int cooltime;
#endif
} PROFESSION_SKILL;
#endif


typedef struct
{
	char name[CHAR_NAME_LEN+1];		// SJIS?���q????
	short level;					// ???
	int login;						// ??????

	int faceGraNo;					// ???�k?
	int hp;							// ??
	int str;						// ???
	int def;						// �\??
	int agi;						// ����?
	int app;						// �u?
	int attr[4];					// �N��?��???????
	int dp;							// ????????
} CHARLISTTABLE;
#ifdef _AIDENGLU_
typedef struct
{
	int ����;
	int ��ģ;
	int С��;
	int ����;
	int �Ƿ��Զ�����;
	int �Ƿ��Զ�����;
	int ���﷽��;
	char ��½��������[4][32];
	int ��½��ʱʱ��;
}Landed;
#endif

extern PC pc;
extern short maxPcNo;
extern short selectPcNo;
extern short prSendMode;
extern short prSendFlag;
extern short jbSendFlag;
extern short duelSendFlag;

extern int loginDp;

extern short helpFlag;

extern short tradeFlag;
extern short tradeStatus;

//extern short channel;

extern MAGIC magic[];

extern PET pet[];

extern PARTY party[];
extern short partyModeFlag;

extern ADDRESS_BOOK addressBook[];
extern BOOL addressBookFlag;


extern BATTLE_RESULT_MSG battleResultMsg;

extern PET_SKILL petSkill[][MAX_SKILL];

extern CHARLISTTABLE chartable[];

extern char newCharacterName[];
extern int newCharacterGraNo;
extern int newCharacterFaceGraNo;
extern int newCharacterVit;
extern int newCharacterStr;
extern int newCharacterTgh;
extern int newCharacterDex;
extern int newCharacterEarth;
extern int newCharacterWater;
extern int newCharacterFire;
extern int newCharacterWind;
extern int newCharacterHomeTown;

void initPcAll( void );
void initPc( void );
void createPc( int, int, int, int );
void resetPc( void );
void setPcWarpPoint( int, int );
void setPcPoint( void );
void setPcGraNo( int, int );
void setPcId( int );
void setPcDir( int );
void setPcAction( int );
#ifdef __EMOTION
	void setPcEmotion( int emotion );
#endif
int getPcAction( void );

#ifdef _CHAR_PROFESSION			// WON ADD ����ְҵ
#ifdef _PRO3_ADDSKILL
    #define MAX_PROFESSION_SKILL	30
#else
    #define MAX_PROFESSION_SKILL	26
#endif
    extern PROFESSION_SKILL profession_skill[];
//    #ifdef _GM_IDENTIFY		// Rog ADD GMʶ��
//      void setPcParam( char *, char *, int, char *, int, int, int, int, int, int, int, int, char *);
//        void setPcParam( char *, char *, int, char *, int, int, int, int, int, int, int, char *);    
//	#else
//      void setPcParam( char *, char *, int, char *, int, int, int, int, int, int, int, int );
#ifdef _ALLDOMAN // (���ɿ�) Syu ADD ���а�NPC
	void setPcParam( char *, char *, int, char *, int, int, int, int, int, int, int , int );
#else
    void setPcParam( char *, char *, int, char *, int, int, int, int, int, int, int );
#endif
//    #endif
#else
    void setPcParam( char *, char *, int, char *, int, int, int, int );
#endif

void updataPcAct( void );
void setPcLeader( void );
void delPcLeader( void );
void setPcParty( void );
void delPcParty( void );
void setPcWatch( void );
void delPcWatch( void );
void changePcAct( int, int, int, int, int, int, int );
void setPcWalkFlag( void );
void delPcWalkFlag( void );
int checkPcWalkFlag( void );
void setPcUseMagic( void );
void delPcUseMagic( void );
void setPcFukidashi( unsigned int );
void setPcNameColor( int );

void clearPartyParam( void );
void clearPtActPartyParam( void );

int existCharacterListEntry( int );
int cmpNameCharacterList( char * );
int setCharacterList( char *, char * );
int resetCharacterList( int );

void getItem( void );
void swapItem( int, int );

BOOL lookAtAround( void );


void initAddressBook( void );
void addressBookProc( void );

int CHAR_getMaxHaveGold( void);

#endif


