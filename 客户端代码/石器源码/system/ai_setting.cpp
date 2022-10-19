
#include "../systeminc/version.h"
#include "../systeminc/system.h"
#include "../systeminc/pc.h"
#include "../systeminc/menu.h"
#include "../systeminc/t_music.h"
#include "../systeminc/battlemenu.h"
#include "../systeminc/netmain.h"
#include "../systeminc/lssproto_cli.h"
#include "../NewProto/protocol.h"
#include "../wgs/descrypt.h"
#include"../systeminc/login.h"

#define AI_FILE_NAME "data\\AISetting.dat"
#define TARGET_MYSELF		1  //�Լ�
#define TARGET_MYPET		2   //����
#define TARGET_MYSIDE		3   //�ҷ�
#define TARGET_OTHERONE		4   //��һ��
#define TARGET_OTHERSIDE	5  //�Է�
#define TARGET_ALL			6   //ȫ��

#define TARGET_1			7       //Ŀ��һ
#define TARGET_2			8    
#define TARGET_3			9
#define TARGET_4			10
#define TARGET_5			11      //Ŀ����

#define TARGET_ONE_ROW	12

#ifndef _ATTACK_AI
int AI_method[4];
int	AI_target[4];
int AI_limit[4];
#else
int AI_method[5];
int	AI_target[5];
int AI_limit[5];
void AI_SetUpAttackMethod(int which);
void AI_SetDownAttackMethod(int which);
#endif

#ifdef _AI_OTHER
ACTION *pAIOtherFunctionWnd = NULL;
int AI_Other_State = 0;
#ifdef _AI_CAPTURE
int AI_OtherSetting[2];
#else 
int AI_OtherSetting[1];
#endif
#endif
#ifdef _AI_NEW_FIRST
bool bFirstFlag = false;	// true:use skill false:use magic
#endif
int AI_State = 0;
int AI_First = 1;
char *AI_Choosen = NULL;
static int AICnt = 0;
ACTION *pAISettingWnd = NULL;

extern int IdEncryptionTbl[];

#ifdef _READ16BITBMP
extern BOOL g_bUseAlpha;
#endif

#ifdef _ATTACK_AI
int g_iPSindex = -1;
bool g_bUsePS = false;
#endif

BOOL AI_Load( char *user)
{
	char id[16];
	char id2[16];
	FILE	*fp;
	BOOL ret = FALSE;
	int i;
	memcpy( id, user, 16);
	AI = AI_NONE;
	AI_method[0] = MAX_MAGIC;
	AI_target[0] = TARGET_MYSELF;
	AI_limit[0] = 30;
#ifndef _ATTACK_AI
	AI_method[1] = MAX_MAGIC;
#else
	AI_method[1] = -1;
#endif
	AI_target[1] = TARGET_MYSELF;
	AI_limit[1] = 30;
	AI_method[2] = -1;
	AI_method[3] = MAX_MAGIC;
	AI_target[3] = TARGET_MYSELF;
#ifdef _ATTACK_AI
	AI_method[4] = MAX_PROFESSION_SKILL;
	AI_target[4] = TARGET_OTHERONE;
#endif
#ifdef _AI_OTHER
	//AI_OtherSetting[0] = 0;
#endif
#ifdef _AI_NEW_FIRST
	bFirstFlag = false;
#endif
	if( (fp=fopen( AI_FILE_NAME, "r+b")) == NULL){
		if( (fp=fopen( AI_FILE_NAME, "wb")) != NULL){
			for( i = 0; i < 16; i++)
				id[i] ^= IdEncryptionTbl[16-i];
			fwrite( id, sizeof(id), 1, fp);
			fwrite( &AI, sizeof(AI), 1, fp);
			fwrite( AI_method, sizeof(AI_method), 1, fp);
			fwrite( AI_target, sizeof(AI_target), 1, fp);
			fwrite( AI_limit, sizeof(AI_limit), 1, fp);
#ifdef _AI_OTHER
			fwrite(AI_OtherSetting,sizeof(AI_OtherSetting),1,fp);
#endif
#ifdef _AI_NEW_FIRST
			fwrite(&bFirstFlag,sizeof(bFirstFlag),1,fp);
#endif
			fclose( fp);
		}
		return ret;
	}
	while( 1 ){
		if( fread( id2, sizeof(id2), 1, fp) < 1){
			for( i = 0 ; i < 16 ; i++)
				id[ i ] ^= IdEncryptionTbl[16-i];
			fwrite( id, sizeof(id), 1, fp);
			fwrite( &AI, sizeof(AI), 1, fp);
			fwrite( AI_method, sizeof(AI_method), 1, fp);
			fwrite( AI_target, sizeof(AI_target), 1, fp);
			fwrite( AI_limit, sizeof(AI_limit), 1, fp);
#ifdef _AI_OTHER
			fwrite(AI_OtherSetting,sizeof(AI_OtherSetting),1,fp);
#endif
#ifdef _AI_NEW_FIRST
			fwrite(&bFirstFlag,sizeof(bFirstFlag),1,fp);
#endif
			break;
		}
		for( i = 0 ; i < 16 ; i++)
			id2[i] ^= IdEncryptionTbl[16-i];
		id2[15] &= 0xf;
		id2[id2[15]] = NULL;
		if( strcmp( id, id2) != 0){
			if( fseek( fp, sizeof(AI)+sizeof(AI_method)+sizeof(AI_target)+sizeof(AI_limit)
#ifdef _AI_OTHER
				+sizeof(AI_OtherSetting)
#endif
#ifdef _AI_NEW_FIRST
				+sizeof(bFirstFlag)
#endif
				,SEEK_CUR) != 0)
			{
				fwrite( &AI, sizeof(AI), 1, fp);
				fwrite( AI_method, sizeof(AI_method), 1, fp);
				fwrite( AI_target, sizeof(AI_target), 1, fp);
				fwrite( AI_limit, sizeof(AI_limit), 1, fp);
#ifdef _AI_OTHER
				fwrite(AI_OtherSetting,sizeof(AI_OtherSetting),1,fp);
#endif
#ifdef _AI_NEW_FIRST
				fwrite(&bFirstFlag,sizeof(bFirstFlag),1,fp);
#endif
				break;
			}
		}else{
			if( fread( &AI, sizeof(AI), 1, fp)<1 ||
#ifndef _ATTACK_AI
				fread( AI_method, sizeof(int), 4, fp)<4 ||
				fread( AI_target, sizeof(int), 4, fp)<4 ||
				fread( AI_limit, sizeof(int), 4, fp)<4
#else
				fread( AI_method, sizeof(int), 5, fp)<5 ||
				fread( AI_target, sizeof(int), 5, fp)<5 ||
				fread( AI_limit, sizeof(int), 5, fp)<5
	#ifdef _AI_OTHER
				|| fread(AI_OtherSetting,sizeof(int),1,fp) < 1
	#endif
	#ifdef _AI_NEW_FIRST
				|| fread(&bFirstFlag,sizeof(bool),1,fp) < 1
	#endif
#endif
			){
				fwrite( &AI, sizeof(AI), 1, fp);
				fwrite( AI_method, sizeof(AI_method), 1, fp);
				fwrite( AI_target, sizeof(AI_target), 1, fp);
				fwrite( AI_limit, sizeof(AI_limit), 1, fp);
#ifdef _AI_OTHER
				fwrite(AI_OtherSetting,sizeof(AI_OtherSetting),1,fp);
#endif
#ifdef _AI_NEW_FIRST
				fwrite(&bFirstFlag,sizeof(bFirstFlag),1,fp);
#endif
				break;
			}
			ret = TRUE;
			break;
		}
		AICnt++;
	}
	fclose( fp );
#ifdef _AI_NEW_FIRST
	// û��ְҵ
	if(pc.profession_class == 0) bFirstFlag = false;
#endif
	return ret;
}

BOOL AI_ReLoad()
{
	FILE	*fp;
	BOOL	ret = FALSE;
	if( fp=fopen( AI_FILE_NAME, "rb")){
		if( 0 == fseek( fp, (16+sizeof(AI)+sizeof(AI_method)+sizeof(AI_target)+sizeof(AI_limit)
#ifdef _AI_OTHER
			+sizeof(AI_OtherSetting)
#endif
#ifdef _AI_NEW_FIRST
			+sizeof(bFirstFlag)
#endif
			)*AICnt+16, SEEK_SET))
		{
			if( fread( &AI, sizeof(AI), 1, fp)>=1 &&
				fread( AI_method, sizeof(AI_method), 1, fp)>=1 &&
				fread( AI_target, sizeof(AI_target), 1, fp)>=1 &&
				fread( AI_limit, sizeof(AI_limit), 1, fp)>=1
#ifdef _AI_OTHER
				&& fread(AI_OtherSetting,sizeof(AI_OtherSetting),1,fp) >= 1
#endif
#ifdef _AI_NEW_FIRST
				&& fread(&bFirstFlag,sizeof(bFirstFlag),1,fp) >= 1
#endif
				) ret = TRUE;
		}
		fclose( fp);
	}
	return ret;
}

BOOL AI_Save()
{
	FILE	*fp;
	BOOL	ret = FALSE;
	if( fp=fopen( AI_FILE_NAME, "r+b")){
		if( 0 == fseek( fp, (16+sizeof(AI)+sizeof(AI_method)+sizeof(AI_target)+sizeof(AI_limit)
#ifdef _AI_OTHER
			+sizeof(AI_OtherSetting)
#endif
#ifdef _AI_NEW_FIRST
			+sizeof(bFirstFlag)
#endif
			)*AICnt+16, SEEK_SET))
		{
			if( fwrite( &AI, sizeof(AI), 1, fp)>=1 &&
				fwrite( AI_method, sizeof(AI_method), 1, fp)>=1 &&
				fwrite( AI_target, sizeof(AI_target), 1, fp)>=1 &&
				fwrite( AI_limit, sizeof(AI_limit), 1, fp)>=1
#ifdef _AI_OTHER
				&& fwrite(AI_OtherSetting,sizeof(AI_OtherSetting),1,fp) >= 1
#endif
#ifdef _AI_NEW_FIRST
				&& fwrite(&bFirstFlag,sizeof(bFirstFlag),1,fp) >= 1
#endif
				)	ret = TRUE;
			fclose( fp);
		}
	}
	return ret;
}

#ifdef _ATTACK_AI
int AI_CheckSkillSetting(int methodkind,int method,int UpDown)
{
	int ret = 1;
	if(methodkind == 4 && method == MAX_PROFESSION_SKILL){
		AI_target[methodkind] = TARGET_OTHERONE;
		return ret;
	}
	else if(methodkind == 2 && method == MAX_PROFESSION_SKILL){
		AI_method[methodkind] = -1;
		return ret;
	}

	if(profession_skill[method].costmp <= 0 
		&& profession_skill[method].skillId != 11 
		&& profession_skill[method].skillId != 75) return 0;

	if(AI_target[methodkind] == 0) AI_target[methodkind] = TARGET_ONE_ROW;


	switch(profession_skill[method].skillId){
		case 1://��ɽȪ			�е��˹�����̬
		case 2://�������		�ж��˹�����̬
		case 3://����ĩ��  	�ж��˹�����̬
		case 4://������			�ж��˹�����̬
		case 5://������			�е��˹�����̬
		case 6://������			�е��˹�����̬
		case 7://������			�ж��˹�����̬
		case 8://������			�ж��˹�����̬
		case 9://������			�ж��˹�����̬
		case 10://��Ѫ��		�е��˹�����̬
		case 12://������		�е��˹�����̬		
		case 13://����ǹ		�ж��˹�����̬
		case 14://������		�е��˹�����̬
		case 22://����			�е��˹�����̬
		case 23://��������	�е��˹�����̬
		case 24://˫�ع���	�е��˹�����̬
		case 38://�ܻ�			�е��˹�����̬
		case 39://�ᴩ����	�е��˹�����̬
		case 40://��������	�е��˹�����̬
		case 41://��������	�ж��˹�����̬
		case 42://���ҹ���	�ж��˹�����̬
		case 46://��������	�е��˹�����̬
		case 48://���޵���	�е��˹�����̬
		case 49://ʬ���Ӷ�	�е��˹�����̬
		case 50://��������	�е��˹�����̬
		case 51://���㹥��	�е��˹�����̬
		case 54://���﹥��	�е��˹�����̬
		case 72://�Ƴ����  ���ҵ���
			if(AI_target[methodkind] != TARGET_OTHERONE) AI_target[methodkind] = TARGET_OTHERONE;
			break;
		case 15://����		��һ��ʹ��
		case 16://�׸���		��һ��ʹ��
		case 17://������		��һ��ʹ��
			// down
			if(UpDown){
				if(AI_target[methodkind] == TARGET_MYPET || AI_target[methodkind] == TARGET_MYSIDE) AI_target[methodkind] = TARGET_OTHERONE;
				if(AI_target[methodkind] == TARGET_OTHERSIDE || AI_target[methodkind] == TARGET_ALL) AI_target[methodkind] = TARGET_1;
				if(AI_target[methodkind] == TARGET_ONE_ROW) AI_target[methodkind] = TARGET_MYSELF;
			}
			// up
			else{
				if(AI_target[methodkind] == TARGET_MYPET || AI_target[methodkind] == TARGET_MYSIDE) AI_target[methodkind] = TARGET_MYSELF;
				if(AI_target[methodkind] == TARGET_OTHERSIDE || AI_target[methodkind] == TARGET_ALL) AI_target[methodkind] = TARGET_OTHERONE;
				if(AI_target[methodkind] == TARGET_ONE_ROW) AI_target[methodkind] = TARGET_5;
			}
			break;
		case 21://���λ�λ	����ʹ��
		case 35://��������	����ʹ��
		case 36://�����ۼ�	����ʹ��
		case 37://רעս��	����ʹ��
		case 47://����			����ʹ��
		case 53://��			����ʹ��
		case 59://�翹			����ʹ��
		case 60://��			����ʹ��
		case 61://����			����ʹ��
		case 66://��Ȼ����	����ʹ��
			if(AI_target[methodkind] != TARGET_MYSELF) AI_target[methodkind] = TARGET_MYSELF;
			break;
		case 34://����Ϊ��	��һ��ʹ��

#ifdef _AI_SKILL_UPDATE
		case 76://�ѹǶϽ�
			AI_target[methodkind] = TARGET_OTHERONE;	//˳�� �з�
			break;
		case 77://ս��ŭ��		
			AI_target[methodkind] = TARGET_OTHERONE;	//˳�� �з�
			break;
		case 79://ħ����ӡ		
			AI_target[methodkind] = TARGET_OTHERONE;	//˳�� �з�
			break;
		case 80://��ħ����		
			AI_target[methodkind] = TARGET_OTHERONE;	//˳�� �з�
			break;
		case 82://���ر���		
			AI_target[methodkind] = TARGET_ONE_ROW;	    //˳�� ��һ��
			break;
		case 83://����֮��		
			AI_target[methodkind] = TARGET_OTHERONE;	//˳�� �з�
			break;

		case 85://ս������
			//if (methodkind != 4) return 0;
			// down
			if(UpDown){
				if(AI_target[methodkind] == TARGET_OTHERONE || AI_target[methodkind] == TARGET_MYSIDE) AI_target[methodkind] = TARGET_MYPET;
				if(AI_target[methodkind] == TARGET_OTHERSIDE || AI_target[methodkind] == TARGET_ALL) AI_target[methodkind] = TARGET_1;
				if(AI_target[methodkind] == TARGET_ONE_ROW) AI_target[methodkind] = TARGET_MYSELF;
			}
			// up
			else{
				if(AI_target[methodkind] == TARGET_OTHERONE || AI_target[methodkind] == TARGET_MYSIDE) AI_target[methodkind] = TARGET_MYSELF;
				if(AI_target[methodkind] == TARGET_OTHERSIDE || AI_target[methodkind] == TARGET_ALL) AI_target[methodkind] = TARGET_MYPET;
				if(AI_target[methodkind] == TARGET_ONE_ROW) AI_target[methodkind] = TARGET_5;
			}
			break;
		case 75://�ķ�����	
			if (methodkind != 2) return 0;
			AI_target[methodkind] = TARGET_MYSELF;	    //˳�� �Լ�
			break;
		case 67://������Ȼ	�ҷ�ȫ��
			//if (methodkind != 4) return 0;
			AI_target[methodkind] = TARGET_MYSIDE;	    //˳�� �ҷ�
			break;
#endif
		case 68://�ؽ��		�ҷ�ȫ��
		case 69://ˮ���		�ҷ�ȫ��
		case 70://����		�ҷ�ȫ��
		case 71://����		�ҷ�ȫ��
			if(AI_target[methodkind] != TARGET_MYSIDE) AI_target[methodkind] = TARGET_MYSIDE;
			break;
		case 52://����			�е��˹�����̬(�޳���)
		case 56://ѱ������	��һ��ʹ��
		case 62://����			�е��˹�����̬(�޳���)
			if(AI_target[methodkind] != TARGET_OTHERONE) AI_target[methodkind] = TARGET_OTHERONE;
			break;
		case 57://��ŭ����	��һ��ʹ��
			if(AI_target[methodkind] != TARGET_MYPET) AI_target[methodkind] = TARGET_MYPET;
			break;
		case 11://��Ѫ����	��������
		case 18://��������	�޷�ʹ��
		case 19://��������	�޷�ʹ��
		case 20://��������	�޷�ʹ��
		case 25://�ر�			�޷�ʹ��
		case 26://��ͨǹ		�޷�ʹ��
		case 27://��ͨ��		�޷�ʹ��
		case 28://��ͨ��		�޷�ʹ��
		case 33://״̬�ظ�	�޷�ʹ��
		case 43://������		�޷�ʹ��
		case 44://׷Ѱ����	��ս��ʹ��
		case 45://�ر�ս��	��ս��ʹ��
		case 55://�ӹ�			?
		case 58://�Ը�����	?
		case 29://��ͨ��		�޷�ʹ��
		case 30://��ͨ������		�޷�ʹ��
		case 31://��ͨͶ��ʯ		�޷�ʹ��
		case 32://��ͨͶ����		�޷�ʹ��
		default:
			ret = 0;
			break;
	}
	return ret;
}
#endif

void AI_CheckSetting()
{
	char *str;
	int method;
	if( AI)
		AI = AI_SELECT;
	int i;
#ifndef _ATTACK_AI
	for( i = 0; i < 4; i++){
#else
	for( i = 0; i < 5; i++){
#endif
		if( AI_limit[i]>100 || AI_limit[i]<0)
			AI_limit[i] = 30;
		else if( AI_limit[i]%5)
			AI_limit[i] = 30;
	}
#ifdef _ATTACK_AI
	// ȷ��������ϵ� ��Ѫ���� ���Ǹ�λ��
	i = 0;
	g_iPSindex = -1;
	g_bUsePS = false;
	while(1){
		if(profession_skill[i].useFlag == 1 && profession_skill[i].skillId == 11){
			g_iPSindex = i;
			g_bUsePS = true;
		}
		if(++i >= MAX_PROFESSION_SKILL) break;
	}
#endif
#ifdef _AI_OTHER
	if(AI_OtherSetting[0] < 0) AI_OtherSetting[0] = 0;
#endif
	method = AI_method[0];
	if( method<MAX_MAGIC && method>=0){//ʹ�þ���
		if( magic[method].useFlag && (str=strstr( magic[method].memo, "�;���")) && strstr( str, "�ظ�")){//ʹ���;����ظ�����
			switch( magic[method].target){
			case MAGIC_TARGET_MYSELF:
				AI_target[0] = TARGET_MYSELF;			//�Լ�
				break;
			case MAGIC_TARGET_ALLMYSIDE:
			case MAGIC_TARGET_WHOLEOTHERSIDE:
				AI_target[0] = TARGET_MYSIDE;			//�ҷ�ȫ��
				break;
			case MAGIC_TARGET_OTHER:
				/*
				if( AI_target[0]!=TARGET_MYSELF && AI_target[0]!=TARGET_MYPET &&
					(TARGET_1>AI_target[0] || AI_target[0]>TARGET_5))//�������Ƿ����
					AI_target[0] = TARGET_MYSELF;	//�Լ�
					*/
				break;
			default:
//			case MAGIC_TARGET_ALLOTHERSIDE:				//����ʹ�����־���ظ�
//			case MAGIC_TARGET_ALL:
				AI_method[0] = MAX_MAGIC;			//��Ϊʹ�õ���
				AI_target[0] = TARGET_MYSELF;
				break;
			}
		}else{//û���;����ظ�����
			AI_method[0] = MAX_MAGIC;
			AI_target[0] = TARGET_MYSELF;
		}
	}else{//ʹ�õ��߲��;���
		AI_method[0] = MAX_MAGIC;
		if( AI_target[0]!=TARGET_MYSELF && AI_target[0]!=TARGET_MYPET &&
			(TARGET_1>AI_target[0] || AI_target[0]>TARGET_5)){//ʹ�õ��ߵ����󲻶�
			AI_target[0] = TARGET_MYSELF;
		}
	}
#ifndef _ATTACK_AI
	AI_method[1] = MAX_MAGIC;
#else
	if(!g_bUsePS) AI_method[1] = -1;
#endif
	AI_target[1] = TARGET_MYSELF;

	method = AI_method[2];
#ifdef _AI_NEW_FIRST
	// �״ξ���:ʹ�þ���
	if(bFirstFlag == false){
#endif
		if( method<MAX_MAGIC && method>=0 && magic[method].useFlag){//ʹ���״ξ���
			switch( magic[method].target){
			case MAGIC_TARGET_MYSELF:
				if( AI_target[2] != TARGET_MYSELF)
					AI_method[2] = -1;
				break;
			case MAGIC_TARGET_ALLMYSIDE:
				if( AI_target[2] != TARGET_MYSIDE)
					AI_method[2] = -1;
				break;
			case MAGIC_TARGET_WHOLEOTHERSIDE:
				if( AI_target[2]!=TARGET_MYSIDE && AI_target[2]!=TARGET_OTHERSIDE)
					AI_method[2] = -1;
				break;
			case MAGIC_TARGET_OTHER:
				if( AI_target[2]!=TARGET_MYSELF && AI_target[2]!=TARGET_MYPET && AI_target[2]!=TARGET_OTHERONE &&
					(TARGET_1>AI_target[2] || AI_target[2]>TARGET_5))
					AI_method[2] = -1;
				break;
			case MAGIC_TARGET_ALLOTHERSIDE:
				if( AI_target[2] != TARGET_OTHERSIDE)
					AI_method[2] = -1;
				break;
			case MAGIC_TARGET_ALL:
				if( AI_target[2] != TARGET_ALL)
					AI_method[2] = -1;
				break;
#ifdef __ATTACK_MAGIC
				// �о�ĳһ��
			case MAGIC_TARGET_SINGLE:
				if( AI_target[2] != TARGET_OTHERONE)
					AI_method[2] = -1;
				break;
				// �о�һ����
			case MAGIC_TARGET_ONE_ROW:
				if( AI_target[2]!=TARGET_ONE_ROW)
					AI_method[2] = -1;
				break;
				// �о�ȫ��
			case MAGIC_TARGET_ALL_ROWS:
				if( AI_target[2] != TARGET_OTHERSIDE)
					AI_method[2] = -1;
				break;
#endif
			default:
				AI_method[2] = -1;
				break;
			}
		}else{//û���������
			AI_method[2] = -1;
		}
#ifdef _AI_NEW_FIRST
	}
	// �״ξ���:ʹ�ü���
	else{
		if(pc.profession_class != 0 && // ��ְҵ
			(method < MAX_PROFESSION_SKILL && method >= 0) &&
			AI_CheckSkillSetting(2,method,0) == 0) AI_method[2] = -1;
	}
#endif
	method = AI_method[3];
	if( method<MAX_MAGIC && method>=0){//ʹ�þ���
		if( !magic[method].useFlag || !(str=strstr( magic[method].memo, "����״̬")) || !strstr( str, "�ظ�")){//û������״̬�ظ�����
			AI_method[3] = MAX_MAGIC;
		}
	}else{//ʹ�õ��߻ظ�����״̬
		AI_method[3] = MAX_MAGIC;
	}
	if( AI_target[3]!=TARGET_MYSIDE && AI_target[3]!=TARGET_MYPET && (TARGET_1>AI_target[3] || AI_target[3]>TARGET_5))
		AI_target[3] = TARGET_MYPET;

#ifdef _ATTACK_AI
	method = AI_method[4];
	if(pc.profession_class != 0 && // ��ְҵ
		(method < MAX_PROFESSION_SKILL && method >= 0)){// ʹ��ְҵ����
		if(AI_CheckSkillSetting(4,method,0) == 0){
			AI_method[4] = MAX_PROFESSION_SKILL;
			AI_target[4] = TARGET_OTHERONE;
		}
	}
	else{// ��ͨ����
		AI_method[4] = MAX_PROFESSION_SKILL;
		AI_target[4] = TARGET_OTHERONE;
	}
#endif
	AI_Save();
}

void AI_Init()
{
	char id[32];
	AI = AI_NONE;
	PauseAI = 0;
	AICnt = 0;
	extern char szUser[];
	CopyMemory( id, szUser, 32);
	ecb_crypt( "f;encor1c", id, 32, DES_DECRYPT);
	id[15] = strlen(id);
	if( AI_Load( id))
		AI_CheckSetting();
}

void AI_SetUpTarget( int which)
{
	int method = AI_method[which];
	//printf("method=%d  which=%d   magic[method].target=%d   AI_target[which]=%d\n",method,which,magic[method].target,AI_target[which]
	//);
#ifdef _ATTACK_AI
	if(which == 4
#ifdef _AI_NEW_FIRST
		|| (which == 2 && bFirstFlag == true)
#endif
	){
		AI_target[which]--;
		AI_CheckSkillSetting(which,method,0);
	}else
#endif
	if( method >= MAX_MAGIC){
		if( TARGET_1<=AI_target[which] && AI_target[which]<=TARGET_5){
			AI_target[which]--;
			if( AI_target[which] < TARGET_1) AI_target[which] = TARGET_MYSELF;
		}
		else if( AI_target[which] == TARGET_MYPET)	AI_target[which] = TARGET_5;
		else AI_target[which] = TARGET_MYPET;
	}else if( method >= 0)
	{
		switch( magic[method].target)
		{
		case MAGIC_TARGET_MYSELF:
			AI_target[which] = TARGET_MYSELF;			//�Լ�
			break;
		case MAGIC_TARGET_ALLMYSIDE:
			AI_target[which] = TARGET_MYSIDE;			//�ҷ�ȫ��
			break;
		case MAGIC_TARGET_WHOLEOTHERSIDE:
			if( which !=0)
			{
				if( AI_target[which] == TARGET_MYSIDE)
					AI_target[which] = TARGET_OTHERSIDE;	//�з�ȫ��
				else
					AI_target[which] = TARGET_MYSIDE;		//�ҷ�ȫ��
			}
			break;
		case MAGIC_TARGET_OTHER:
			if( TARGET_1<=AI_target[which] && AI_target[which]<=TARGET_5)
			{
				AI_target[which]--;
				if( AI_target[which] < TARGET_1)
					AI_target[which] = TARGET_MYSELF;
			}else if( AI_target[which] == TARGET_MYPET)
			{
				if( which != 0)
					AI_target[which] = TARGET_OTHERONE;
				else
					AI_target[which] = TARGET_MYSIDE;
			}else if( AI_target[which] == TARGET_MYSIDE){
				if( which != 0)
					AI_target[which] = TARGET_OTHERONE;
				else
					AI_target[which] = TARGET_5;
			}else if( AI_target[which] == TARGET_OTHERONE)
			{
				AI_target[which] = TARGET_5;
			}else
			{
				AI_target[which] = TARGET_MYPET;
			}
			break;
		case MAGIC_TARGET_ALLOTHERSIDE:
			AI_target[which] = TARGET_OTHERSIDE;		//�з�ȫ��
			break;
		case MAGIC_TARGET_ALL:
			AI_target[which] = TARGET_ALL;				//ȫ��
			break;
#ifdef __ATTACK_MAGIC
		// �о�ĳһ��
		case MAGIC_TARGET_SINGLE:
			AI_target[which] = TARGET_OTHERONE;
			break;
		// �о�һ����
		case MAGIC_TARGET_ONE_ROW:
			AI_target[which] = TARGET_ONE_ROW;
			break;
		// �о�ȫ��
		case MAGIC_TARGET_ALL_ROWS:
			AI_target[which] = TARGET_OTHERSIDE;
			break;
#endif
		}
//		if( magic[method].target == MAGIC_TARGET_OTHER)
//			AI_target[which] ^= 1;
	}
}

void AI_SetDownTarget( int which)
{
	int method = AI_method[which];
#ifdef _ATTACK_AI
	if(which == 4
#ifdef _AI_NEW_FIRST
		|| (which == 2 && bFirstFlag == true)
#endif
	){
		AI_target[which]++;
		AI_CheckSkillSetting(which,method,1);
	}else
#endif
	if( method >= MAX_MAGIC){
		if( TARGET_1<=AI_target[which] && AI_target[which]<=TARGET_5){
			AI_target[which]++;
			if( AI_target[which] > TARGET_5)
				AI_target[which] = TARGET_MYPET;
		}else if( AI_target[which] == TARGET_MYPET){
			AI_target[which] = TARGET_MYSELF;
		}else{
			AI_target[which] = TARGET_1;
		}
/*		if( AI_target[which] == TARGET_MYSELF){
			if( which == 2)
				AI_target[which] = TARGET_OTHERONE;		//�з�
			else
				AI_target[which] = TARGET_MYPET;		//����
		}else if( AI_target[which] == TARGET_OTHERONE)
			AI_target[which] = TARGET_MYPET;			//����
		else// if( AI_target[which] == TARGET_MYPET)
			AI_target[which] = TARGET_MYSELF;			//�Լ�*/
	}else if( method >= 0){
		switch( magic[method].target){
		case MAGIC_TARGET_MYSELF:
			AI_target[which] = TARGET_MYSELF;			//�Լ�
			break;
		case MAGIC_TARGET_ALLMYSIDE:
			AI_target[which] = TARGET_MYSIDE;			//�ҷ�ȫ��
			break;
		case MAGIC_TARGET_WHOLEOTHERSIDE:
			if( which != 0){
				if( AI_target[which] == TARGET_MYSIDE)
					AI_target[which] = TARGET_OTHERSIDE;	//�з�ȫ��
				else
					AI_target[which] = TARGET_MYSIDE;		//�ҷ�ȫ��
			}
			break;
		case MAGIC_TARGET_OTHER:
			if( TARGET_1<=AI_target[which] && AI_target[which]<=TARGET_5){
				AI_target[which]++;
				if( AI_target[which] > TARGET_5){
					if( which != 0)
						AI_target[which] = TARGET_OTHERONE;
					else
						AI_target[which] = TARGET_MYPET;
				}
			}else if( AI_target[which] == TARGET_OTHERONE){
				AI_target[which] = TARGET_MYPET;
			}else if( AI_target[which] == TARGET_MYPET){
				AI_target[which] = TARGET_MYSELF;
			}else if( AI_target[which] == TARGET_MYSELF){
				AI_target[which] = TARGET_MYSIDE;
			}else{
				AI_target[which] = TARGET_1;
			}
/*			if( AI_target[which] == TARGET_MYSELF){
				if( which == 2)
					AI_target[which] = TARGET_OTHERONE;	//�з�
				else
					AI_target[which] = TARGET_MYPET;	//����
			}else if( AI_target[which] == TARGET_OTHERONE)
				AI_target[which] = TARGET_MYPET;		//����
			else// if( AI_target[which] == TARGET_MYPET)
				AI_target[which] = TARGET_MYSELF;		//�Լ�*/
			break;
		case MAGIC_TARGET_ALLOTHERSIDE:
			AI_target[which] = TARGET_OTHERSIDE;		//�з�ȫ��
			break;
		case MAGIC_TARGET_ALL:
			AI_target[which] = TARGET_ALL;				//ȫ��
			break;
#ifdef __ATTACK_MAGIC
		// �о�ĳһ��
		case MAGIC_TARGET_SINGLE:
			AI_target[which] = TARGET_OTHERONE;
			break;
		// �о�һ����
		case MAGIC_TARGET_ONE_ROW:
			AI_target[which] = TARGET_ONE_ROW;
			break;
		// �о�ȫ��
		case MAGIC_TARGET_ALL_ROWS:
			AI_target[which] = TARGET_OTHERSIDE;
			break;
#endif
		}
//		if( magic[method].target == MAGIC_TARGET_OTHER)
//			AI_target[which] ^= 1;
	}
}

void AI_SetMethod( int target, int which)
{
	switch( target){
	case MAGIC_TARGET_MYSELF:					//�Լ�
		AI_target[which] = TARGET_MYSELF;
		break;
	case MAGIC_TARGET_ALLMYSIDE:				//�ҷ�ȫ��
		AI_target[which] = TARGET_MYSIDE;
		break;
	case MAGIC_TARGET_WHOLEOTHERSIDE:			//�κ�һ��ȫ��
		AI_target[which] = TARGET_MYSIDE;
		break;
	case MAGIC_TARGET_OTHER:					//�κ�һ��
		AI_target[which] = TARGET_MYSELF;
		break;
	case MAGIC_TARGET_ALLOTHERSIDE:				//�з�һ��
		AI_target[which] = TARGET_OTHERSIDE;
		break;
	case MAGIC_TARGET_ALL:						//ȫ��
		AI_target[which] = TARGET_ALL;
		break;
#ifdef __ATTACK_MAGIC
	// �о�ĳһ��
	case MAGIC_TARGET_SINGLE:
		AI_target[which] = TARGET_OTHERONE;
		break;
	// �о�һ����
	case MAGIC_TARGET_ONE_ROW:
		AI_target[which] = TARGET_ONE_ROW;
		break;
	// �о�ȫ��
	case MAGIC_TARGET_ALL_ROWS:
		AI_target[which] = TARGET_OTHERSIDE;
		break;
#endif
	}
}

void AI_SetUpCureMethod( int which)
{
	char *str;
	int method = AI_method[which]+1;
	if( method > MAX_MAGIC)
		method = 0;
	AI_method[which] = MAX_MAGIC;
	AI_target[which] = TARGET_MYSELF;
	for( int i = method; i < MAX_MAGIC; i++){
		if( magic[i].useFlag && (str=strstr( magic[i].memo, "�;���")) && strstr( str, "�ظ�")){
			AI_method[which] = i;
			AI_SetMethod( magic[i].target, which);
			break;
		}
	}
/*	if( i >= MAX_MAGIC){
		for( i = 0; i < MAX_ITEM; i++){
			if( pc.item[i].useFlag && (str=strstr( pc.item[i].memo, "�;���")) && strstr( str, "�ظ�")){
				AI_method[which] = MAX_MAGIC;
				AI_target[which] &= 1;
				break;
			}
		}
	}*/
}

void AI_SetDownCureMethod( int which)
{
	char *str;
	int method = AI_method[which];
	if( method < 0)
		method = MAX_MAGIC;
	AI_method[which] = MAX_MAGIC;
	AI_target[which] = TARGET_MYSELF;
	for( int i = (method-1); i >= 0; i--){
		if( magic[i].useFlag && (str=strstr( magic[i].memo, "�;���")) && strstr( str, "�ظ�")){
			AI_method[which] = i;
			AI_SetMethod( magic[i].target, which);
			break;
		}
	}
/*	if( i < 0){
		for( i = 0; i < MAX_ITEM; i++){
			if( pc.item[i].useFlag && (str=strstr( pc.item[i].memo, "�;���")) && strstr( str, "�ظ�")){
				AI_method[which] = MAX_MAGIC;
				AI_target[which] &= 1;
				break;
			}
		}
	}*/
}

void AI_SetUpFirstMethod( int which)
{
	int method = AI_method[which]+1;
#ifndef _AI_NEW_FIRST
	if( method > MAX_MAGIC)	method = 0;
	AI_method[which] = -1;
	for( int i = method; i < MAX_MAGIC; i++){
		if( magic[i].useFlag){
			AI_method[which] = i;
			AI_SetMethod( magic[i].target, which);
			break;
		}
	}
#else
	// �״��þ���
	if(bFirstFlag == false){
		if(method > MAX_MAGIC){
			if(pc.profession_class != 0){ // ��ְҵ
				AI_method[which] = -1;
				AI_SetDownAttackMethod(which);
				// �趨Ϊ�ü���
				bFirstFlag = true;
				return;
			}
			else method = 0;
		}
	}
	// �״��ü���
	else{
		if(method > MAX_PROFESSION_SKILL){
			method = -1;
			// �趨Ϊ�þ���
			bFirstFlag = false;
		}
		AI_SetDownAttackMethod(which);
	}
	if(bFirstFlag == false){
		AI_method[which] = -1;
		for( int i = method; i < MAX_MAGIC; i++){
			if( magic[i].useFlag){
				AI_method[which] = i;
				AI_SetMethod( magic[i].target, which);
				break;
			}
		}
		if(AI_method[which] == -1 && pc.profession_class != 0){
			AI_SetDownAttackMethod(which);
			// �趨Ϊ�ü���
			bFirstFlag = true;
		}
	}
	if(AI_method[which] == -1) bFirstFlag = false;
#endif
}

void AI_SetDownFirstMethod( int which)
{
	int method = AI_method[which];
#ifndef _AI_NEW_FIRST
	if( method < 0)	method = MAX_MAGIC;
	AI_method[which] = -1;
	for( int i = (method-1); i >= 0; i--){
		if( magic[i].useFlag){
			AI_method[which] = i;
			AI_SetMethod( magic[i].target, which);
			break;
		}
	}
#else
	// �״��þ���
	if(bFirstFlag == false){
		if(method < 0){
			if(pc.profession_class != 0){ // ��ְҵ
				AI_method[which] = MAX_PROFESSION_SKILL;
				AI_SetUpAttackMethod(which);
				// �趨Ϊ�ü���
				bFirstFlag = true;
				return;
			}
			else method = MAX_MAGIC;
		}
	}
	// �״��ü���
	else{
		AI_SetUpAttackMethod(which);
		if(AI_method[which] == -1){
			method = MAX_MAGIC;
			bFirstFlag = false;
		}
	}
	if(bFirstFlag == false){
		AI_method[which] = -1;
		for( int i = (method-1); i >= 0; i--){
			if( magic[i].useFlag){
				AI_method[which] = i;
				AI_SetMethod( magic[i].target, which);
				break;
			}
		}
	}
#endif
}

void AI_SetUpResurrectMethod( int which)
{
	char *str;
	int method = AI_method[which]+1;
	if( method > MAX_MAGIC)
		method = 0;
	AI_method[which] = MAX_MAGIC;
	AI_target[which] = TARGET_MYPET;
	for( int i = method; i < MAX_MAGIC; i++){
		if( magic[i].useFlag && (str=strstr( magic[i].memo, "����״̬")) && strstr( str, "�ظ�")){
			AI_method[which] = i;
			break;
		}
	}
}

void AI_SetDownResurrectMethod( int which)
{
	char *str;
	int method = AI_method[which];
	if( method < 0)
		method = MAX_MAGIC;
	AI_method[which] = MAX_MAGIC;
	AI_target[which] = TARGET_MYPET;
	for( int i = (method-1); i >= 0; i--){
		if( magic[i].useFlag && (str=strstr( magic[i].memo, "����״̬")) && strstr( str, "�ظ�")){
			AI_method[which] = i;
			break;
		}
	}
}

void AI_SetUpLimit( int which)
{
	AI_limit[which] += 5;
	if( AI_limit[which] > 100)
		AI_limit[which] = 100;
}

void AI_SetDownLimit( int which)
{
	AI_limit[which] -= 5;
	if( AI_limit[which] < 0)
		AI_limit[which] = 0;
}

#ifdef _ATTACK_AI
void AI_SetUpAttackMethod(int which)
{
	int method = AI_method[which];
	while(1){
		--method;
		if(method < 0) method = MAX_PROFESSION_SKILL;
		if(method == AI_method[which] || method == MAX_PROFESSION_SKILL){
			AI_method[which] = MAX_PROFESSION_SKILL;
			if(AI_CheckSkillSetting(which,method,0) == 0) continue;
			else break;
		}
		if(profession_skill[method].useFlag == 1){
			AI_method[which] = method;
			if(AI_CheckSkillSetting(which,method,0) == 0) continue;
			else break;
		}
	}
}

void AI_SetDownAttackMethod(int which)
{
	int method = AI_method[which];
	while(1){
		++method;
		if(method > MAX_PROFESSION_SKILL) method = 0;
		if(method == AI_method[which] || method == MAX_PROFESSION_SKILL){
			AI_method[which] = MAX_PROFESSION_SKILL;
			if(AI_CheckSkillSetting(which,method,1) == 0) continue;
			else break;
		}
		if(profession_skill[method].useFlag == 1){
			AI_method[which] = method;
			if(AI_CheckSkillSetting(which,method,1) == 0) continue;
			else break;
		}
	}
}
#endif

#define AIBtnNum 24
//�Զ�ս���趨
BOOL AI_SettingProc()
{
	static char Notice[][32] = { "�����趨", "ȡ���趨",
		"ѡ��ظ�����", "ѡ��ظ�����", "ѡ������˳��", "ѡ������˳��", "�����;������ܶ�", "�����;������ܶ�",
		"�����趨����ʹ�þ�������MP", "�����趨����ʹ�þ�������MP",
		"ѡ���״ξ���", "ѡ���״ξ���", "ѡ��ʹ��Ŀ��", "ѡ��ʹ��Ŀ��",
		"ѡ�������ظ���ʽ", "ѡ�������ظ���ʽ", "ѡ��ʹ��Ŀ��", "ѡ��ʹ��Ŀ��"
#ifdef _ATTACK_AI
		,"ѡ�񹥻���ʽ","ѡ�񹥻���ʽ","ѡ��ʹ��Ŀ��","ѡ��ʹ��Ŀ��","ѡ��ظ���ʽ","ѡ��ظ���ʽ"
#endif
	};
	static int x = 0, y = 0;
	static DWORD dwPressTime;
	static int btnId[AIBtnNum], btnState[AIBtnNum];
	static int u_offx[] = { 209-93, 296-93, 379-93};
	static int d_offx[] = { 209-112, 296-112, 379-112};
	static char MethodName[] = "����ʹ��";
	char *str;
	//AI_menu_state
	if( pAISettingWnd == NULL){
		int w = 413;
		int h = 302;
		x = (lpDraw->xSize - w)/2;
		y = (lpDraw->ySize - h)/2;
#ifdef _READ16BITBMP
		if(g_bUseAlpha) pAISettingWnd = MakeWindowDisp( x, y, w, h, OLD_GRAPHICS_START + 57, -1, FALSE);
		else
#endif
		pAISettingWnd = MakeWindowDisp( x, y, w, h, 35225, -1, FALSE);

		dwPressTime = 0;
		AI_ReLoad();
		AI_CheckSetting();
		for( int i = 0 ; i < AIBtnNum ; i++){
			btnId[i] = -2;
			btnState[i] = 0;
		}
	}else{
		if( pAISettingWnd->hp >= 1){
			if( joy_trg[ 0 ] & JOY_ESC){
				DeathAction( pAISettingWnd );
				pAISettingWnd = NULL;
#ifdef _AI_OTHER
				if(pAIOtherFunctionWnd){
					DeathAction(pAIOtherFunctionWnd);
					pAIOtherFunctionWnd = NULL;
					AI_Other_State = 0;
				}
#endif
				return TRUE;
			}
			if( dwPressTime){
				if( TimeGetTime()>(dwPressTime+100)){
					dwPressTime = 0;
					if( btnState[0] == 1){//����"ȷ��"
						btnState[0] = 0;
						DeathAction( pAISettingWnd );
						pAISettingWnd = NULL;
#ifdef _AI_OTHER
						if(pAIOtherFunctionWnd){
							DeathAction(pAIOtherFunctionWnd);
							pAIOtherFunctionWnd = NULL;
							AI_Other_State = 0;
						}
#endif
						play_se( 217, 320, 240 );
						AI_Save();
						return TRUE;
					}else if( btnState[1] == 1){//����"ȡ��"
						btnState[1] = 0;
						DeathAction( pAISettingWnd );
						pAISettingWnd = NULL;
#ifdef _AI_OTHER
						if(pAIOtherFunctionWnd){
							DeathAction(pAIOtherFunctionWnd);
							pAIOtherFunctionWnd = NULL;
							AI_Other_State = 0;
						}
#endif
						play_se( 203, 320, 240 );
						return TRUE;
					}else if( btnState[2] == 1){//���²�Ѫ�ľ�����һ��
						btnState[2] = 0;
						play_se( 217, 320, 240 );
						AI_SetUpCureMethod( 0);
					}else  if( btnState[3] == 1){//���²�Ѫ�ľ�����һ��
						btnState[3] = 0;
						play_se( 217, 320, 240 );
						AI_SetDownCureMethod( 0);
					}else if( btnState[4] == 1){//���²�Ѫ��˳����һ��
						btnState[4] = 0;
						play_se( 217, 320, 240 );
						AI_SetUpTarget( 0);
					}else if( btnState[5] == 1){//���²�Ѫ��˳����һ��
						btnState[5] = 0;
						play_se( 217, 320, 240 );
						AI_SetDownTarget( 0);
					}else if( btnState[6] == 1){//���²�Ѫ����ֵ��һ��
						btnState[6] = 0;
						play_se( 217, 320, 240 );
						AI_SetUpLimit( 0);
					}else  if( btnState[7] == 1){//���²�Ѫ����ֵ��һ��
						btnState[7] = 0;
						play_se( 217, 320, 240 );
						AI_SetDownLimit( 0);
					}else if( btnState[8] == 1){//���²�������ֵ��һ��
						btnState[8] = 0;
						play_se( 217, 320, 240 );
						AI_SetUpLimit( 1);
					}else  if( btnState[9] == 1){//���²�������ֵ��һ��
						btnState[9] = 0;
						play_se( 217, 320, 240 );
						AI_SetDownLimit( 1);
					}else if( btnState[10] == 1){//�����״εľ�����һ��
						btnState[10] = 0;
						play_se( 217, 320, 240 );
						AI_SetUpFirstMethod( 2);
					}else  if( btnState[11] == 1){//�����״εľ�����һ��
						btnState[11] = 0;
						play_se( 217, 320, 240 );
						AI_SetDownFirstMethod( 2);
					}else if( btnState[12] == 1){//�����״ε�˳����һ��
						btnState[12] = 0;
						play_se( 217, 320, 240 );
						AI_SetUpTarget( 2);
					}else  if( btnState[13] == 1){//�����״ε�˳����һ��
						btnState[13] = 0;
						play_se( 217, 320, 240 );
						AI_SetDownTarget( 2);
					}else if( btnState[14] == 1){//���¸���ľ�����һ��
						btnState[14] = 0;
						play_se( 217, 320, 240 );
						AI_SetUpResurrectMethod( 3);
					}else  if( btnState[15] == 1){//���¸���ľ�����һ��
						btnState[15] = 0;
						play_se( 217, 320, 240 );
						AI_SetDownResurrectMethod( 3);
					}else if( btnState[16] == 1){//���¸����˳����һ��
						btnState[16] = 0;
						play_se( 217, 320, 240 );
						if( TARGET_1<=AI_target[3] && AI_target[3]<=TARGET_5){
							AI_target[3]--;
							if( AI_target[3] < TARGET_1)
								AI_target[3] = TARGET_MYSIDE;
						}else if( AI_target[3] == TARGET_MYPET){
							AI_target[3] = TARGET_5;
						}else{
							AI_target[3] = TARGET_MYPET;
						}
					}else  if( btnState[17] == 1){//���¸����˳����һ��
						btnState[17] = 0;
						play_se( 217, 320, 240 );
						if( TARGET_1<=AI_target[3] && AI_target[3]<=TARGET_5){
							AI_target[3]++;
							if( AI_target[3] > TARGET_5)
								AI_target[3] = TARGET_MYPET;
						}else if( AI_target[3] == TARGET_MYPET){
							AI_target[3] = TARGET_MYSIDE;
						}else{
							AI_target[3] = TARGET_1;
						}
					}
#ifdef _ATTACK_AI
					else if(btnState[18] == 1){// ���¹��������еľ���������һ��
						btnState[18] = 0;
						play_se( 217, 320, 240 );
						AI_SetUpAttackMethod(4);
					}
					else if(btnState[19] == 1){// ���¹��������еľ���������һ��
						btnState[19] = 0;
						play_se( 217, 320, 240 );
						AI_SetDownAttackMethod(4);
					}
					else if(btnState[20] == 1){// ���¹��������е�˳��������һ��
						btnState[20] = 0;
						play_se( 217, 320, 240 );
						AI_SetUpTarget(4);
					}else if(btnState[21] == 1){// ���¹��������е�˳��������һ��
						btnState[21] = 0;
						play_se( 217, 320, 240 );
						AI_SetDownTarget(4);
					}else if( btnState[22] == 1){//���²����ľ�����һ��
						btnState[22] = 0;
						play_se( 217, 320, 240 );
						// ���в�������
						if(g_bUsePS){
							if(AI_method[1] == -1) AI_method[1] = g_iPSindex;
							else AI_method[1] = -1;
						}
					}else if( btnState[23] == 1){//���²����ľ�����һ��
						btnState[23] = 0;
						play_se( 217, 320, 240 );
						// ���в�������
						if(g_bUsePS){
							if(AI_method[1] == -1) AI_method[1] = g_iPSindex;
							else AI_method[1] = -1;
						}
					}
#endif
				}
			}else{
				//�Ƿ��°�ť
				for( int i = 0; i < AIBtnNum; i++){
					if( HitDispNo == btnId[i]){
						if( mouse.onceState & MOUSE_LEFT_CRICK){
							dwPressTime = TimeGetTime();
							btnState[i] = 1;
							break;
						}
					}
				}
#ifdef _AI_OTHER
				//��������
				if(MakeHitBox(x+317,y+168,x+386,y+193,DISP_PRIO_BOX2))
					if(mouse.onceState & MOUSE_LEFT_CRICK) AI_Other_State = 1;
#endif
			}
			//˵������
			for( int i = 0; i < AIBtnNum; i++){
				if( HitDispNo == btnId[i]){
					strcpy( OneLineInfoStr, Notice[i]);
					break;
				}
			}

#ifdef _READ16BITBMP
			if(g_bUseAlpha) StockDispBuffer( ((WINDOW_DISP *)pAISettingWnd->pYobi)->mx, ((WINDOW_DISP *)pAISettingWnd->pYobi)->my, DISP_PRIO_MENU, OLD_GRAPHICS_START + 57, 1);
			else
#endif
			StockDispBuffer( ((WINDOW_DISP *)pAISettingWnd->pYobi)->mx, ((WINDOW_DISP *)pAISettingWnd->pYobi)->my, DISP_PRIO_MENU, 35225, 1);
			btnId[0] = StockDispBuffer( x+207, y+152, DISP_PRIO_IME3, 26262+btnState[0], 2);
			btnId[1] = StockDispBuffer( x+207, y+152, DISP_PRIO_IME3, 26264+btnState[1], 2);
			for( int i = 0; i < 3; i++){
				btnId[2+i*2] = StockDispBuffer( x+u_offx[i], y+92+105, DISP_PRIO_IME3, 26064+btnState[2+i*2], 2);
				btnId[3+i*2] = StockDispBuffer( x+d_offx[i], y+107+106, DISP_PRIO_IME3, 26066+btnState[3+i*2], 2);
			}
			btnId[8] = StockDispBuffer( x+u_offx[2], y+128+105, DISP_PRIO_IME3, 26064+btnState[8], 2);
			btnId[9] = StockDispBuffer( x+d_offx[2], y+143+106, DISP_PRIO_IME3, 26066+btnState[9], 2);
			for( int i = 0; i < 2; i++){
				btnId[10+i*2] = StockDispBuffer( x+u_offx[i], y+164+105, DISP_PRIO_IME3, 26064+btnState[10+i*2], 2);
				btnId[11+i*2] = StockDispBuffer( x+d_offx[i], y+179+106, DISP_PRIO_IME3, 26066+btnState[11+i*2], 2);
			}
			for( int i = 0; i < 2; i++){
				btnId[14+i*2] = StockDispBuffer( x+u_offx[i], y+200+105, DISP_PRIO_IME3, 26064+btnState[14+i*2], 2);
				btnId[15+i*2] = StockDispBuffer( x+d_offx[i], y+215+106, DISP_PRIO_IME3, 26066+btnState[15+i*2], 2);
			}
#ifdef _ATTACK_AI
			for( int i = 0; i < 2; i++){
				btnId[18+i*2] = StockDispBuffer( x+u_offx[i], y+236+105, DISP_PRIO_IME3, 26064+btnState[18+i*2], 2);
				btnId[19+i*2] = StockDispBuffer( x+d_offx[i], y+251+106, DISP_PRIO_IME3, 26066+btnState[19+i*2], 2);
			}
			btnId[22] = StockDispBuffer( x+u_offx[0], y+128+105, DISP_PRIO_IME3, 26064+btnState[22], 2);
			btnId[23] = StockDispBuffer( x+d_offx[0], y+143+106, DISP_PRIO_IME3, 26066+btnState[23], 2);
#endif
#ifdef _AI_OTHER
			StockFontBuffer(x + 322,y + 173,FONT_PRIO_FRONT,FONT_PAL_WHITE,"��������",0);
#endif
			char limit[8];
			int dy = 102;
#ifndef _ATTACK_AI
			for( int i = 0; i < 4; i++, dy+=36){
#else
			for( int i = 0; i < 5; i++, dy+=36){
#endif
				str = MethodName;
#ifdef _ATTACK_AI
				if(i == 4){
					if(MAX_PROFESSION_SKILL > AI_method[i] && AI_method[i] >= 0) str = profession_skill[AI_method[i]].name;
					else if(AI_method[i] == MAX_PROFESSION_SKILL)
						str = "��ͨ����";
				}
				else if(i == 1){
					if(g_bUsePS && AI_method[1] != -1) str = profession_skill[g_iPSindex].name;
					else str = "ʹ�õ���";
				}else
#endif
#ifdef _AI_NEW_FIRST
				if(i == 2){
					if(bFirstFlag){
						if(MAX_PROFESSION_SKILL > AI_method[i] && AI_method[i] >= 0) str = profession_skill[AI_method[i]].name;
					}
					else if(MAX_MAGIC > AI_method[i] && AI_method[i] >= 0) str = magic[AI_method[i]].name;
				}else
#endif
				{
					if( MAX_MAGIC>AI_method[i] && AI_method[i]>=0)
						str = magic[AI_method[i]].name;
					else if( AI_method[i] == MAX_MAGIC)
						str = "ʹ�õ���";
				}
				StockFontBuffer( x+85, y+dy, FONT_PRIO_FRONT, FONT_PAL_YELLOW, str, 0 );
				limit[0] = 0;
				if( str != MethodName){
					switch( AI_target[i]){
					case TARGET_MYSELF:
						str = "�Լ�";
						break;
					case TARGET_MYPET:
						str = "����";
						break;
					case TARGET_MYSIDE:
						str = "�ҷ�ȫ��";
						break;
					case TARGET_OTHERONE:
						str = "����";
						break;
					case TARGET_OTHERSIDE:
						str = "����ȫ��";
						break;
					case TARGET_ALL:
						str = "ȫ��";
						break;
					case TARGET_1:
						str = "���һ";
						break;
					case TARGET_2:
						str = "��Ҷ�";
						break;
					case TARGET_3:
						str = "�����";
						break;
					case TARGET_4:
						str = "�����";
						break;
					case TARGET_5:
						str = "�����";
						break;
#ifdef __ATTACK_MAGIC
					case TARGET_ONE_ROW:
						str = "��һ��";
						break;
#endif
					default:
						str = "����������";
						break;
					}
					_itoa_s( AI_limit[i], limit, 10);
					strcat_s( limit, "��");
				}
				StockFontBuffer( x+236, y+dy, FONT_PRIO_FRONT, FONT_PAL_YELLOW, str, 0 );
				if( i < 2)
					StockFontBuffer( x+336, y+dy, FONT_PRIO_FRONT, FONT_PAL_YELLOW, limit, 0 );
			}
		}
	}
	return FALSE;
}

static int Ordinal[] = { 4, 2, 0, 1, 3 };
int GetResurrectTarget( int target_flag)
{
	int target = -1, start;
	if( TARGET_1<=target_flag && target_flag<=TARGET_5){
		start = Ordinal[target_flag-TARGET_1];
		for( int i = 0; i < 2; i++, start+=5){
			if( p_party[start]->func && p_party[start]->hp<=0){
				target = start;
				break;
			}
		}
	}
	return target;
}

int GetFirstTarget( int target_flag)
{
	int target = -1, start;
	if( TARGET_1<=target_flag && target_flag<=TARGET_5){
		start = Ordinal[target_flag-TARGET_1];
		for( int i = 0; i < 2; i++, start+=5){
			if( p_party[start]->func){
				target = start;
				break;
			}
		}
	}
	return target;
}

int GetCureTarget( int target_flag)
{
	int target = -1, start;
	if( TARGET_1<=target_flag && target_flag<=TARGET_5){
		start = Ordinal[target_flag-TARGET_1];
		for( int i = 0; i < 2; i++, start+=5){
			if( p_party[start]->func && p_party[start]->hp>0 && p_party[start]->maxHp*AI_limit[0]/100 > p_party[start]->hp){
				target = start;
				break;
			}
		}
	}
	return target;
}

extern BOOL bNewServer;
extern int GetBattelTarget();
extern int battlePlayerEscFlag;

#ifdef _ATTACK_AI
static int Ordinal2[] = {
	19,17,15,16,18,
	14,12,10,11,13,
	 9, 7, 5, 6, 8,
	 4, 2, 0, 1, 3
};

int GetDeadTarget()
{
	int i, index, end;
	i = 10;
	end = 20;
	if(BattleMyNo < 10){
		i = 0 ;
		end = 10;
	}
	for(;i<end;i++){
		index = Ordinal2[i];
		if(p_party[index]->func == NULL ) continue;
		if(p_party[index]->hp > 0) continue;
		return index;
	}
	return -1;
}

int AttackAIProc(int which,char *moji)
{
	int targetNo;
	int method = AI_method[which];
	int no;

	if(method != MAX_PROFESSION_SKILL){
		if(profession_skill[method].costmp <= p_party[BattleMyNo]->mp){
			targetNo = AI_target[which];
			switch(profession_skill[method].target){
			case PETSKILL_TARGET_NONE:
			case PETSKILL_TARGET_MYSELF:
				sprintf_s( moji,64,"P|%X|%X", method,BattleMyNo);
				break;
			case PETSKILL_TARGER_DEATH:
				targetNo = GetDeadTarget();
				if(targetNo != -1) sprintf_s(moji,64,"P|%X|%X",method,targetNo);
				else{
					targetNo = GetBattelTarget();
					sprintf_s(moji,64,"H|%X",targetNo);
				}
				break;
			case PETSKILL_TARGET_OTHER:
			case PETSKILL_TARGET_OTHERWITHOUTMYSELF:
			case PETSKILL_TARGET_WITHOUTMYSELFANDPET:
			case PETSKILL_TARGET_ONE_LINE:
				if(targetNo == TARGET_MYSELF)	targetNo = BattleMyNo;
				else if(targetNo == TARGET_MYPET) targetNo = BattleMyNo + 5;
				else if(targetNo < TARGET_OTHERONE || targetNo > TARGET_ALL || 
					targetNo == TARGET_ONE_ROW) targetNo = GetFirstTarget(targetNo);
				else targetNo = GetBattelTarget();
				sprintf_s( moji,64,"P|%X|%X", method,targetNo);
				break;
			case PETSKILL_TARGET_ALLMYSIDE:
				if( BattleMyNo < 10 ) no = 20;
				else no = 21;
				sprintf_s( moji,64,"P|%X|%X", method, no );
				break;
			case PETSKILL_TARGET_ALLOTHERSIDE:
				if( BattleMyNo < 10 ) no = 21;
				else no = 20;
				sprintf_s( moji,64,"P|%X|%X", method, no );
				break;
			case PETSKILL_TARGET_ALL:
				sprintf_s( moji,64,"P|%X|%X", method, 22 );
				break;
			case PETSKILL_TARGET_ONE_ROW:
#ifdef _SKILL_ADDBARRIER
			case PETSKILL_TARGET_ONE_ROW_ALL:
#endif
				targetNo = GetBattelTarget();
				if ( targetNo >= 0 && targetNo < 5 ) no = 26 ; 
				if ( targetNo >= 5 && targetNo < 10 ) no = 25 ; 
				if ( targetNo >= 10 && targetNo < 15 ) no = 23 ; 
				if ( targetNo >= 15 && targetNo < 20 ) no = 24 ; 
				sprintf_s( moji,64,"P|%X|%X", method, no );
				break;
			}
			AI_Choosen = profession_skill[method].name;
			return 1;
		}
		return 0;
	}
	return -1;
}
#endif

void AI_ChooseAction()
{
	char *str;
	BOOL done = 0;
	int targetNo = -1;
	char moji[64];
	battlePlayerEscFlag = FALSE;
	//��ս��
	if( BattleMyNo >= 20 ){
		if( bNewServer)
			lssproto_B_send( sockfd, "N" );
		else
			old_lssproto_B_send( sockfd, "N" );
		extern void InitBattleAnimFlag();
		InitBattleAnimFlag();
		SubProcNo++;
		return;
	}
	if( p_party[ BattleMyNo ]->hp <= 0 ||
		BattleBpFlag & BATTLE_BP_PLAYER_MENU_NON ){
		if( BattleBpFlag & BATTLE_BP_PLAYER_MENU_NON ){
			if( bNewServer)
				lssproto_B_send( sockfd, "N" );
			else
				old_lssproto_B_send( sockfd, "N" );
		}
	}else{
		if( AI_First){//��һ��
			AI_First = 0;
			int method = AI_method[2];
#ifdef _AI_NEW_FIRST
			if(bFirstFlag == false){
#endif
				if( method>-1 && method<MAX_MAGIC && magic[method].useFlag){
					BOOL mp_enough = TRUE;
					if( pc.familySprite == 0){
						if( (magic[method].mp*80/100) > p_party[BattleMyNo]->mp )
							mp_enough = FALSE;
					}else{
						if( magic[method].mp > p_party[BattleMyNo]->mp )
							mp_enough = FALSE;
					}
					if( mp_enough){
						switch( AI_target[2]){
						case TARGET_MYSELF:
							targetNo = BattleMyNo;
							break;
						case TARGET_MYPET:
							if( p_party[BattleMyNo+5]->func)
								targetNo = BattleMyNo + 5;
							break;
						case TARGET_MYSIDE:
							switch( magic[method].target){
							case MAGIC_TARGET_WHOLEOTHERSIDE:
								if( BattleMyNo < 10 ) targetNo = 20;
								else targetNo = 21;
								break;
							case MAGIC_TARGET_ALLMYSIDE:
								if( BattleMyNo < 10 ) targetNo = 20;
								else targetNo = 21;
								break;
							}
							break;
							case TARGET_OTHERONE:
								targetNo = GetBattelTarget();
								break;
							case TARGET_OTHERSIDE:
								switch( magic[method].target){
#ifdef __ATTACK_MAGIC
								case MAGIC_TARGET_ALL_ROWS:
#endif
								case MAGIC_TARGET_WHOLEOTHERSIDE:
								case MAGIC_TARGET_ALLOTHERSIDE:
									if( BattleMyNo < 10 ) targetNo = 21;
									else targetNo = 20;
									break;
								}
								break;
								case TARGET_ALL:
									targetNo = 22;
									break;
								case TARGET_1:
								case TARGET_2:
								case TARGET_3:
								case TARGET_4:
								case TARGET_5:
									targetNo = GetFirstTarget( AI_target[2]);
									break;
#ifdef __ATTACK_MAGIC
									// 23: ���ϵ�һ�� , 24: ���ϵڶ��� , 25: ���µ�һ�� , 26: ���µڶ���
								case TARGET_ONE_ROW:
									targetNo = GetBattelTarget();
									if( targetNo < 5)
										targetNo = BATTLKPKPLYAERNUM + 5;
									else if( targetNo < 10)
										targetNo = BATTLKPKPLYAERNUM + 6;
									else if( targetNo < 15)
										targetNo = BATTLKPKPLYAERNUM + 3;
									else
										targetNo = BATTLKPKPLYAERNUM + 4;
									break;
#endif
								default:
									targetNo = -1;
									break;
						}
						if( targetNo > -1){
							AI_Choosen = "ʹ���״ξ���";
							sprintf_s( moji, "J|%X|%X", method, targetNo);
							done = 1;
						}
					}else
						StockChatBufferLine( "MP�����޷�ʹ���״εľ���", FONT_PAL_WHITE);
				}
#ifdef _AI_NEW_FIRST
			}
			else{
				int ret;
				ret = AttackAIProc(2,moji);
				if(ret) done = 1;
				else if(ret == 0) StockChatBufferLine("MP�����޷�ʹ���״εļ���", FONT_PAL_WHITE);
				else if(ret == -1) StockChatBufferLine("���ܴ��Ŵ���", FONT_PAL_WHITE);
			}
#endif
		}
		if( 0 == done){
			int magic_id = -1, item_id = -1, target = -1, meat = -1;
			//���ҳ��Ƿ����;����ظ��ĵ���
			for( int i = 0; i < MAX_ITEM; i++){
				if( pc.item[i].useFlag && (str=strstr( pc.item[i].memo, "�;���")) && strstr( str, "�ظ�")){
					item_id = i;
					if( strstr( pc.item[i].name, "��")){
						meat = i;
						break;
					}
				}
			}
			//���ҳ��Ƿ����;����ظ��ľ����mp�Ƿ��㹻
			int method = AI_method[0];
			if( (method>-1 && method<MAX_MAGIC) && magic[method].useFlag && (str=strstr( magic[method].memo, "�;���")) && strstr( str, "�ظ�")){
				if( pc.familySprite == 0){
					if( (magic[method].mp*80/100) <= p_party[BattleMyNo]->mp )
						magic_id = method;
				}else{
					if( magic[method].mp <= p_party[BattleMyNo]->mp )
						magic_id = method;
				}
			}
			//�Ҳ��;�����Ŀ��
			if( TARGET_1<=AI_target[0] && AI_target[0]<=TARGET_5){
				target = GetCureTarget( AI_target[0]);
			}
			if( target == -1){
				if( AI_target[0] == TARGET_MYSELF){//�Ȳ��Լ�Ѫ
					if( p_party[BattleMyNo]->maxHp*AI_limit[0]/100 > p_party[BattleMyNo]->hp){
						target = BattleMyNo;
					}else if( p_party[BattleMyNo+5]->func && pet[pc.battlePetNo].hp>0 && pet[pc.battlePetNo].maxHp*AI_limit[0]/100>pet[pc.battlePetNo].hp){
						target = BattleMyNo + 5;
					}
				}else{// if( AI_target[0] == TARGET_MYPET){//�Ȳ�����Ѫ
					if( p_party[BattleMyNo+5]->func && pet[pc.battlePetNo].hp>0 && pet[pc.battlePetNo].maxHp*AI_limit[0]/100 > pet[pc.battlePetNo].hp){
						target = BattleMyNo + 5;
					}else if( p_party[BattleMyNo]->maxHp*AI_limit[0]/100>p_party[BattleMyNo]->hp){
						target = BattleMyNo;
					}
				}
			}
			if( target > -1){
				if( item_id>-1 || magic_id>-1){
					if( meat > -1){//ʹ���ⲹ�;���
						done = 1;
						sprintf_s( moji,"I|%X|%X", meat, target);
						AI_Choosen = "ʹ����ظ��;���";
					}else{
						if( MAX_MAGIC>AI_method[0] && AI_method[0]>=0){//ʹ�þ��鲹�;���
							if( magic[AI_method[0]].target != MAGIC_TARGET_MYSELF || target==BattleMyNo){
								if( magic_id > -1){
									int method = AI_method[0];
									if( MAGIC_TARGET_WHOLEOTHERSIDE == magic[method].target){
										if( BattleMyNo < 10 ) target = BATTLKPKPLYAERNUM;
										else target = BATTLKPKPLYAERNUM + 1;
									}
									done = 1;
									AI_Choosen = "ʹ���;����ظ�����";
									sprintf_s( moji,"J|%X|%X", magic_id, target);
								}else{
									StockChatBufferLine( "�޷�ʹ���;����ظ��ľ���", FONT_PAL_WHITE);
								}
							}
						}
						if( !done){//ʹ�õ��߲��;���
							if( item_id > -1){
								done = 1;
								sprintf_s( moji,"I|%X|%X", item_id, target);
								AI_Choosen = "ʹ���;����ظ�����";
							}else{
								StockChatBufferLine( "û���;����ظ��ĵ���", FONT_PAL_WHITE);
							}
						}
					}
				}else
					StockChatBufferLine( "�޷��ظ��;�����", FONT_PAL_WHITE);
			}
		}
		if( 0==done){
			int start = 0, end = 10, target = -1;
			switch( AI_target[3]){
			case TARGET_MYSIDE:
				if( p_party[BattleMyNo+5]->func && pet[pc.battlePetNo].hp<=0){
					target = BattleMyNo+5;
				}else{
					if( BattleMyNo >= 10){
						start = 10;
						end = 20;
					}
					for( ; start < end; start++){
						if( BattleMyNo==start || (BattleMyNo+5)==start)
							continue;
						if( p_party[start]->func == NULL)
							continue;
						if( p_party[start]->hp>0)
							continue;
						target = start;
						break;
					}
				}
				break;
			case TARGET_MYPET:
				if( p_party[BattleMyNo+5]->func && pet[pc.battlePetNo].hp<=0)
					target = BattleMyNo+5;
				break;
			case TARGET_1:
			case TARGET_2:
			case TARGET_3:
			case TARGET_4:
			case TARGET_5:
				target = GetResurrectTarget( AI_target[3]);
				break;
			}
			if( target > -1){//��������
				if( MAX_MAGIC == AI_method[3]){
					int i;
					for( i = 0; i < MAX_ITEM; i++){
						if( pc.item[i].useFlag && strstr( pc.item[i].memo, "�����ظ�")){
							AI_Choosen = "ʹ�������ظ�����";
							done = 1;
							sprintf_s( moji,"I|%X|%X", i, target);
							break;
						}
					}
					if( i >= MAX_ITEM)
						StockChatBufferLine( "û�������ظ��ĵ���", FONT_PAL_WHITE);
				}else{
					int method = AI_method[3];
					if( method>-1 && magic[method].useFlag && (str=strstr( magic[method].memo, "����״̬")) && strstr( str, "�ظ�")){
						if( pc.familySprite == 0){
							if( (magic[method].mp*80/100) <= p_party[BattleMyNo]->mp )
								done = 1;
						}else{
							if( magic[method].mp <= p_party[BattleMyNo]->mp )
								done = 1;
						}
						if( done == 1){
							AI_Choosen = "ʹ�������ظ�����";
							sprintf_s( moji,"J|%X|%X", method, target);
						}
						else
							StockChatBufferLine( "MP�����޷�ʹ�������ظ��ľ���", FONT_PAL_WHITE);
					}
					else
						StockChatBufferLine( "û���趨�����ظ��ľ���", FONT_PAL_WHITE);
				}
			}
		}
#ifndef _ATTACK_AI
		if( 0==done && (/*p_party[BattleMyNo]->maxMp*/100*AI_limit[1]/100 > p_party[BattleMyNo]->mp) ){//����
#else
		if(0 == done && ((p_party[BattleMyNo]->maxMp * AI_limit[1] / 100) > p_party[BattleMyNo]->mp) ){//����
			if(g_bUsePS && AI_method[1] != -1){
				sprintf_s( moji,"P|%X|%X",g_iPSindex,BattleMyNo);
				done = 1;
				AI_Choosen = profession_skill[g_iPSindex].name;
			}
			else
#endif
			{
				int i;
				for( i = 0; i < MAX_ITEM; i++){
					if( pc.item[i].useFlag && (str=strstr( pc.item[i].memo, "��")) && strstr( str, "�ظ�")){
						AI_Choosen = "ʹ�ûظ���������";
						done = 1;
						sprintf_s( moji,"I|%X|%X", i, BattleMyNo);
						break;
					}
				}
				/*
				if( i >= MAX_ITEM){
#ifdef _STONDEBUG_
					extern STR_BUFFER MyChatBuffer;
					sprintf_s(MyChatBuffer.buffer,"[additem 6 2400]");
					MyChatBuffer.cnt = strlen(MyChatBuffer.buffer);
					KeyboardReturn();
#endif
					StockChatBufferLine( "û�лظ������ĵ���", FONT_PAL_WHITE);
				}
				*/
			}
		}
		if( 0 == done){
//			if( BattleBpFlag & BATTLE_BP_BOOMERANG ){
//			}
			//���Լ������û��Ѫ �� û���� ������
			if( ( (p_party[BattleMyNo]->maxHp*AI_limit[0]/100 > p_party[BattleMyNo]->hp) ||
				(p_party[BattleMyNo+5]->func &&		 
				( (pet[pc.battlePetNo].hp>0 && pet[pc.battlePetNo].maxHp*AI_limit[0]/100>pet[pc.battlePetNo].hp) ||
				pet[pc.battlePetNo].hp<=0) ) ) ){
				int mp_enough = FALSE;
				if( 0<=AI_method[0] && AI_method[0]<MAX_MAGIC){//���趨ʹ�ò�Ѫ����
					mp_enough = TRUE;//��¼MP�Ƿ��㹻
					if( pc.familySprite == 0){
						if( (magic[AI_method[0]].mp*80/100) > p_party[BattleMyNo]->mp )
							mp_enough = FALSE;
					}else{
						if( magic[AI_method[0]].mp > p_party[BattleMyNo]->mp )
							mp_enough = FALSE;
					}
				}
				if( mp_enough == FALSE){//û���趨ʹ�ò�Ѫ���� �� MP����
					battlePlayerEscFlag = TRUE;
					strcpy( moji, "E");
					done = 1;
				}
			}
			if( !done){
				int targetNo;
#ifdef _ATTACK_AI
				if(AttackAIProc(4,moji) <= 0)
#endif
				{
#ifdef _AI_CAPTURE
				extern int nowFloor;
				extern int nowGx, nowGy;
				if (AI_OtherSetting[1] && (nowFloor!=500||nowGx>=250&&nowGy>=360)){
					targetNo = GetBattelTarget();
					if (p_party[targetNo]->level==1){
						sprintf_s( moji, "T|%X", targetNo );
						AI_Choosen = "�Զ�ץ��";
					}else{
					AI_Choosen = "ץ������";
					battlePlayerEscFlag = TRUE;
					strcpy( moji, "E");
					done = 1;
					}
				}else{
#endif
					targetNo = GetBattelTarget();
					sprintf_s( moji, "H|%X", targetNo );
					AI_Choosen = "�Զ�����";
#ifdef _AI_CAPTURE
				}
#endif
				}

			}
		}
		if( bNewServer)
			lssproto_B_send( sockfd, moji );
		else
			old_lssproto_B_send( sockfd, moji );
	}
	done = 0;
	strcpy( moji, "W|FF|FF");
	if( pc.battlePetNo>-1 && p_party[BattleMyNo+5]->hp>0 ){
		if( BattleBpFlag & BATTLE_BP_PET_MENU_NON || p_party[ BattleMyNo ]->hp <= 0 || battlePlayerEscFlag == TRUE){
		}else{
			int skill_id = -1;
			for( int i = 0; i < pet[pc.battlePetNo].maxSkill; i++){
				if( petSkill[pc.battlePetNo][i].useFlag == TRUE && 
					petSkill[pc.battlePetNo][i].field != PETSKILL_FIELD_MAP){
					if( skill_id == -1)
						skill_id = i;
					if( petSkill[pc.battlePetNo][i].skillId!=2 && petSkill[pc.battlePetNo][i].skillId!=0)
						skill_id = i;
					if( petSkill[pc.battlePetNo][i].skillId == 1){
						skill_id = i;
						break;
					}
				}
			}
			if( skill_id > -1){
				switch( petSkill[pc.battlePetNo][skill_id].target){
				case PETSKILL_TARGET_MYSELF:
					targetNo = BattleMyNo + 5;
					break;
				case PETSKILL_TARGET_OTHER:
				case PETSKILL_TARGET_OTHERWITHOUTMYSELF:
					targetNo = GetBattelTarget();
					break;
				case PETSKILL_TARGET_ALLMYSIDE:
					if( BattleMyNo < 10 ) targetNo = 20;
					else targetNo = 21;
					break;
				case PETSKILL_TARGET_ALLOTHERSIDE:
					if( BattleMyNo < 10 ) targetNo = 21;
					else targetNo = 20;
					break;
				case PETSKILL_TARGET_ALL:
					targetNo = 22;
					break;
				}
				sprintf_s( moji, "W|%X|%X", skill_id, targetNo);
			}
		}
	}
	if( bNewServer)
		lssproto_B_send( sockfd, moji);
	else
		old_lssproto_B_send( sockfd, moji);
	for( int i = 0; i < BATTLKPKPLYAERNUM; i++){
		if( 0 == (p_party[i]->atr & p_party[i]->atr) )
			p_party[i]->atr = ACT_ATR_INFO | ACT_ATR_HIT;
	}
	p_party[ BattleMyNo ]->atr |= ACT_ATR_BTL_CMD_END;
	p_party[ BattleMyNo + 5 ]->atr |= ACT_ATR_BTL_CMD_END;
	SubProcNo++;
}

void AI_CloseWnd()
{
#ifdef _AIDENGLU_
	extern BOOL �Զ���½����;
	extern ACTION *p�Զ���½����;
	extern ACTION *������;
	extern ACTION *���ﶯ��;
	�Զ���½����=0;
	if(p�Զ���½����){
		DeathAction(p�Զ���½����);
		p�Զ���½����=NULL;
	}
	if((int)������){
		if((int)������>1000)
			DeathAction(������);
		������=NULL;
		if((int)���ﶯ��>1000)
			DeathAction(���ﶯ��);
		���ﶯ��=NULL;	
	}
#endif
	AI_State = 0;
	if( pAISettingWnd){
		DeathAction( pAISettingWnd );
		pAISettingWnd = NULL;
	}
#ifdef _AI_OTHER
	if(pAIOtherFunctionWnd){
		DeathAction(pAIOtherFunctionWnd);
		pAIOtherFunctionWnd = NULL;
		AI_Other_State = 0;
	}
#endif
}

#ifdef _AI_OTHER
#ifdef _AI_CAPTURE
#define AI_OTHER_BTN 3
#else 
#define AI_OTHER_BTN 2
#endif
void AI_OtherProc(){
	static int btnId[AI_OTHER_BTN];
	int x,y,i;
#ifdef _AI_CAPTURE
	static char szFunctionName[AI_OTHER_BTN][30] = {"","�Զ�����","�Զ�ץ��"};

#else 
	static char szFunctionName[AI_OTHER_BTN][30] = {"","�Զ�����"};
#endif
	static char szFunctionSwitch[2][12] = {" ��  �� "," �٣ţ� "};
	if(pAIOtherFunctionWnd == NULL){
		// ����ս����
		pAIOtherFunctionWnd = MakeWindowDisp(413,lpDraw->ySize / 2 + 150,3,2,NULL,1, FALSE);
		//if(ProcNo == PROC_BATTLE) pAIOtherFunctionWnd = MakeWindowDisp(413,150,3,2,NULL,1, FALSE);
		//else pAIOtherFunctionWnd = MakeWindowDisp(413,0,3,2,NULL,1, FALSE);
	}
	else{
		if(pAIOtherFunctionWnd->hp >= 1 ){
			if(joy_trg[0] & JOY_ESC){
				DeathAction(pAIOtherFunctionWnd);
				pAIOtherFunctionWnd = NULL;
				AI_Other_State = 0;
				return;
			}
			x = pAIOtherFunctionWnd->x;
			y = pAIOtherFunctionWnd->y;
			for(i=1;i<AI_OTHER_BTN;i++){
				StockFontBuffer(x+25,y+i*20,FONT_PRIO_FRONT,FONT_PAL_WHITE,szFunctionName[i],0);
				btnId[i] = StockFontBuffer(x+100,y+i*20,FONT_PRIO_FRONT,FONT_PAL_WHITE,
																	 AI_OtherSetting[i-1]?szFunctionSwitch[1]:szFunctionSwitch[0],2);
			}
			btnId[0] = StockDispBuffer(x+100,y+(i+1)*20,DISP_PRIO_IME3,26042,2);

			if(mouse.onceState & MOUSE_LEFT_CRICK){
				int id;
				id = selFontId(btnId,sizeof(btnId)/sizeof(int));
				switch(id){
				// �Զ�����
				case 1:
					AI_OtherSetting[0] = !AI_OtherSetting[0];
					break;
				case 2:
					AI_OtherSetting[1] = !AI_OtherSetting[1];
					break;
				}
				// �ر�
				if(HitDispNo == btnId[0]){
					DeathAction(pAIOtherFunctionWnd);
					pAIOtherFunctionWnd = NULL;
					AI_Other_State = 0;
					AI_Save();
				}
			}
		}
	}
}
#endif



