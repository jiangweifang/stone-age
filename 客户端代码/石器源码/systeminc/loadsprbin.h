#ifndef _SPRITE_H_
#define _SPRITE_H_

//??????��????�e??????
#define mxSPRITE	40000

#define maxBUFFER	1024*1024*6



typedef unsigned char MOJI;
typedef unsigned char U1;
typedef          char S1;
typedef unsigned short U2;
typedef          short S2;
typedef unsigned long U4;
typedef          long S4;
typedef float  F4;
typedef double F8;

typedef enum {
	ANIM_ATTACK, //����
	ANIM_DAMAGE, //����
	ANIM_DEAD,  //����
	ANIM_STAND, //վ��
	ANIM_WALK, //����
	ANIM_SIT, //����
	ANIM_HAND, //����
	ANIM_HAPPY, //����
	ANIM_ANGRY, //����
	ANIM_SAD, //����
	ANIM_GUARD, //����
	ANIM_NOD, //��ͷ
	ANIM_THROW, //Ͷ��
	ANIM_LIST_
} ANIM_LIST;


// 1?????�ѩ�
typedef struct
{
	U4 BmpNo;				//AdrnͼƬ���
	S2 PosX,PosY;			//ͼƬ��ʾʱ��x��yƫ��
	U2 SoundNo;				// С��10000������Ч���,��ʾҪ����Ч;���ڵ���10000С��10100����Ҫ��ʾ�˺�Ч��,���ֻ�����Ч��
							// ���ڵ���10100��������????�k?
} FRAMELIST;//һ֡�����ľ�����Ϣ

typedef struct
{
	U2 dir;	// ��������(0-8)
	U2 no;	// �����ķ���������ANIM_LIST�Ķ���
	U4 dtAnim;	// �ζ���ѭ���ĺ�ʱ
	U4 frameCnt; // FRAMELIST������
	FRAMELIST *ptFramelist;	
} ANIMLIST;


// SPR??�t�ѩ�
typedef struct
{
	U4 sprNo;	// Spr���
	U4 offset;	// ָ����spr.bin�еĵ�ַ
	U2 animSize;	// ��ɫ�ж��ٸ������Ķ���
} SPRADRN;


typedef struct
{
	U2 animSize;
	ANIMLIST	*ptAnimlist;
} SPRITEDATA;


typedef struct {
	U2			dtz;
	U2			noSpritedata;
	U2			mdAnim;
	U2			mdAnim2;
	U2			dir;
	U2			ctLoop;
	float		ctAnim;
	float		dtAnim;
} SPRITE;


typedef struct
{
	U2 dir;		// ��������(0-8)
	U2 no;		// �����ķ���������ANIM_LIST�Ķ���
	U4 dtAnim;	// һ�ζ���ѭ���ĺ�ʱ
	U4 frameCnt;	// �����������
} ANIM_HEADER;


extern SPRITEDATA SpriteData[mxSPRITE];


BOOL InitSprBinFileOpen( char *, char * );


#endif
