/************************/
/*	action.h			*/
/************************/
#ifndef _ACTION_H_
#define _ACTION_H_

#include "version.h"
#include "../newproto/autil.h"
//��������˳��
enum{
	PRIO_TOP,			//������

	PRIO_CHR,			//ͬChar

	PRIO_BG,			/* ?? 	*/
	PRIO_JIKI,			/* ��? 	*/
	PRIO_ENEMY,			/* �� 		*/
	PRIO_ENEMY_TAMA,	/* ���d 	*/
	PRIO_JIKI_TAMA,		/* ��?�d 	*/
	PRIO_ITEM,			/* ????	*/
	PRIO_BOSS,			/* ??		*/
	PRIO_GAME_OVER,		/* GAME OVER */
	PRIO_BTM = 255		/* ??�� 	*/
};

//Action״̬
enum{
	ACT_STATE_ACT = 0,	//ͨ��״̬
	ACT_STATE_DEAD		//����״̬
};
//����
#define ACT_ATR_HIDE 			( 1 <<  1 )	// ����ʾ/* ������ */
#define ACT_ATR_HIT 			( 1 <<  2 )	// ���Ա���ѡ/* ???�R�e?? */
#define ACT_ATR_HIT_BOX 		( 1 <<  3 )	// ���Ա���ѡ�����/* ???�R�e + ????���� */
#define ACT_ATR_INFO 			( 1 <<  4 )	// ��ʾ�����ѶϢ/* ??????���� */
#define ACT_ATR_HIDE2 			( 1 <<  5 )	// ����ʾ + ���Ա���ѡ/* ������+???�R�e?? */
#define ACT_ATR_BTL_CMD_END 	( 1 <<  6 )	// ս��ָ������������,δ����������һᶯ,����򲻻ᶯ/* �P�f????�V?��???? */
#define ACT_ATR_TYPE_PC 		( 1 <<  7 )	// ���/* ?? */
#define ACT_ATR_TYPE_OTHER_PC 	( 1 <<  8 )	// ������/* �\??? */
#define ACT_ATR_TYPE_PET 		( 1 <<  9 )	/* ??? */
#define ACT_ATR_TYPE_ITEM 		( 1 << 10 )	/* ???? */
#define ACT_ATR_TYPE_GOLD 		( 1 << 11 )	/* ?? */
#define ACT_ATR_TYPE_OTHER 		( 1 << 12 )	/* ??�\????��?��??�Y? */
#define ACT_ATR_HIT_BOX_ALL1 	( 1 << 13 )	// ���Ա���ѡ + �����ʾ1
#define ACT_ATR_HIT_BOX_ALL2 	( 1 << 14 )	// ���Ա���ѡ + �����ʾ2
#define ACT_ATR_HIT_BOX_ALL3 	( 1 << 15 )	// ���Ա���ѡ + �����ʾ3
#define ACT_ATR_HIT_BOX_ALL4 	( 1 << 16 )	// ���Ա���ѡ + �����ʾ3
#define ACT_ATR_TRAVEL 			( 1 << 17 )	/* ??? */

#define ACT_ATR_HIT_BOX_COL1	( 1 << 18 )	// ���ϵ�һ��
#define ACT_ATR_HIT_BOX_COL2	( 1 << 19 ) // ���ϵڶ���
#define ACT_ATR_HIT_BOX_COL3	( 1 << 20 ) // ���µ�һ��
#define ACT_ATR_HIT_BOX_COL4	( 1 << 21 ) // ���µڶ���
#define ACT_ATR_HIT_BOX_COL5	( 1 << 22 )	// ���ϵ�һ��
#define ACT_ATR_HIT_BOX_COL6	( 1 << 23 ) // ���ϵڶ���
#define ACT_ATR_HIT_BOX_COL7	( 1 << 24 ) // ���µ�һ��
#define ACT_ATR_HIT_BOX_COL8	( 1 << 25 ) // ���µڶ���




/* ??????�B�l **********************************************************/
struct action{
	struct 	action *pPrev, *pNext;			//��һ������һ��actionָ��
	void 	( *func )( struct action * );	//action��ִ�е�function��ָ��
	void 	*pYobi;							//���õ�structָ��
	void 	*pOther;						//������;structָ��
	UCHAR 	prio;							//action����ʱ������˳��
	UCHAR 	dispPrio;						//��ͼʱ������˳��	
	int 	x, y;							//ͼ������
	int		hitDispNo;						//�Ƿ�����Ŀ����
	BOOL	deathFlag;						//��action�Ƿ��������	
	int 	dx, dy;							//��ͼ����λ����
	int 	dir;							//����
	int 	delta;  						//�ϳ�����
	
	char 	name[ 29 ];						//����
	char 	freeName[ 33 ];					//free name
	int 	hp;		
#ifdef _PET_ITEM
	int		iOldHp;
#endif
	int 	maxHp;						
	int 	mp;							
	int 	maxMp;						
	int 	level;						
	int 	status;						
	int 	itemNameColor;					/* ?????���q?�� */
	int		charNameColor;					// ??????����??????���q?��
	
	int		bmpNo;							//ͼ��
	int		bmpNo_bak;							//����ͼ��
	int		atr;							//����
	int		state;							//״̬
	int		actNo;							//�ж����
	int		damage;						

	int		gx, gy;							//��Ŀǰ�ĵ�ͼ�ϵ�����
	int		nextGx, nextGy;					//��һ������
	int		bufGx[10], bufGy[10];			//��Ŀǰ���굽��һ������֮�������buffer
	short	bufCount;						//�趨ĿǰҪ�ߵ���һ������
	short	walkFlag;						// ��????????????��?�v?????????
	float	mx, my;							//��ͼ����
	float	vx, vy;							// ?�h?��

//����
	short 	earth;							// �� �N��
	short 	water;							// ? �N��
	short 	fire;							// ? �N��
	short 	wind;							// ? �N��
//raderʹ��
	int		dirCnt;							// ��?��??????
//geminiʹ��
	int		spd;							//�ƶ����ٶ�(0~63)( ?????? )
	int		crs;							//����(0~31)(���Ϸ�Ϊ0,˳ʱ�ӷ���) ��?( ???? )( ��?????? )
	int		h_mini;							// ��?��?
	int		v_mini;							// ��?����
//patternʹ��
	int		anim_chr_no;					//����ı��(anim_tbl.h�ı��)
	int		anim_chr_no_bak;				//��һ�ε�������
	int		anim_no;						//����Ķ������
	int		anim_no_bak;					//��һ�ε�������
	int		anim_ang;						//�����ķ���(0~7)(��0)
	int		anim_ang_bak;					//��һ�εķ���
	int		anim_cnt;						//�ڼ���frame
	int		anim_frame_cnt;					//����frameͣ��ʱ��
	int		anim_x;							//X����(Sprbin+Adrnbin)
	int		anim_y;							//Y����(Sprbin+Adrnbin)
	int		anim_hit;						// ???�R�e
	// shan add +1
	char    fmname[33];			            // ��������
	// Robin 0728 ride Pet
	int		onRide;
	char	petName[16+1];
	int		petLevel;
	int		petHp;
	int		petMaxHp;
	int		petDamage;
	int		petFall;
#ifdef _MIND_ICON
	unsigned int sMindIcon;
#endif
#ifdef _SHOWFAMILYBADGE_
	unsigned int sFamilyIcon;
#endif
#ifdef FAMILY_MANOR_
	unsigned int mFamilyIcon;
#endif
#ifdef _CHAR_MANOR_
	unsigned int mManorIcon;
#endif
#ifdef _CHARTITLE_STR_
	TITLE_STR TitleText;
#endif
#ifdef _CHARTITLE_
	unsigned int TitleIcon;
#endif
#ifdef _NPC_EVENT_NOTICE
	int noticeNo;
#endif

#ifdef _SKILL_ROAR  
	int		petRoar;		//���(������)
#endif 
#ifdef _SKILL_SELFEXPLODE //�Ա�
	int		petSelfExplode;		
#endif 
#ifdef _MAGIC_DEEPPOISION   //�綾
	int		petDeepPoision;		 
#endif 

#ifdef _CHAR_PROFESSION			// WON ADD ����ְҵ
	int		profession_class;
#endif
//#ifdef _BATTLESKILL				// (���ɿ�) Syu ADD ս�����ܽ���
	int		warrioreffect; 
//#endif
#ifdef _GM_IDENTIFY		// Rog ADD GMʶ��
	char gm_name[33];
#endif
#ifdef _STREET_VENDOR
	char szStreetVendorTitle[64];
#endif
#ifdef _NPC_PICTURE
	int picture;
	int picturetemp;
#endif
#ifdef _PETSKILL_RIDE
	int saveride;
#endif
#ifdef _MOUSE_DBL_CLICK
	int index;	// ����!! Server�е�charaindex
#endif

#ifdef _SFUMATO
	int sfumato;		// ������Ⱦͼ��ɫ��
#endif
};

typedef struct action ACTION;

/* ?????????????????? */
extern ACTION *pActTop;
extern ACTION *pActBtm;

/* ��?????? */
extern ACTION *pJiki;

#ifdef _STONDEBUG_		
/* ?????????? */
extern int ActCnt;
#endif

/* ?????????�K? *****************************************************/
ACTION *GetAction( UCHAR prio, UINT yobiSize );

/* ??????????? *****************************************************/
void InitAction( void );

/* ????????? *********************************************************/
void RunAction( void );

/* ???????????��?��************************************************/
void DeathAction( ACTION *pAct );

/* �u??????��?�� *******************************************************/
void DeathAllAction( void );

/* ???????????�u?�� ***********************************************/
void ClearAction( ACTION *pAct );

/* ?????��??? *********************************************************/
void EndAction( void );

#endif
