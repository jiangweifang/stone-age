#include "../systeminc/version.h"
#include "../systeminc/system.h"
#include "../systeminc/Turntable.h"
#include "../newproto/autil.h"
#include "../systeminc/menu.h"
#include "../systeminc/shop.h"
#include "../systeminc/t_music.h"
#include "../newproto/protocol.h"
#include "../other/caryIme.h"
#include "../systeminc/field.h"
#include "../systeminc/netmain.h"
char ������������[1024];
#ifdef _ICONBUTTONS_
extern unsigned int sockfd;
extern int nowGx, nowGy;
extern int indexWN;
extern int idWN;
ACTION* ת�̶�����ַ=0;

typedef struct {
	int ����;
	char ��[64];
	char ����[512];
}ת�̵��߽ṹ;

typedef struct {
	int x;
	int y;
}ת������ṹ;

int ת�̵���λ��[10][2]={
						{0x0,-0x74},
						{0x53,-0x5B},
						{0x86,-0x13},
						{0x86,0x43},
						{0x57,0x8A},
						{0x2,0xA6},
						{-0x51,0x8A},
						{-0x84,0x46},
						{-0x85,-0x10},
						{-0x52,-0x58},
						};

ת������ṹ ת������[10];

typedef struct {
	int x;
	int y;
	int ѡ������;
	BOOL ��������;
	int ת��;//(0δת�� 1ת���� 2ת������)
	int ָ��λ��;
	int ָ�����;
	int ָ��Ȧ��;
	ת�̵��߽ṹ ����[10];
}ת�̴��ڽṹ;

ת�̴��ڽṹ ת�̴���;

void ת�̴��ڳ�ʼ��(char * ����)
{
	ת������[0].x=0;
	ת������[0].y=-0x30;
	ת������[1].x=0x2C;
	ת������[1].y=-0x21;
	ת������[2].x=0x49;
	ת������[2].y=0x7;
	ת������[3].x=0x48;
	ת������[3].y=0x2F;
	ת������[4].x=0x2D;
	ת������[4].y=0x57;
	ת������[5].x=0x4;
	ת������[5].y=0x66;
	ת������[6].x=-0x27;
	ת������[6].y=0x5A;
	ת������[7].x=-0x48;
	ת������[7].y=0x32;
	ת������[8].x=-0x47;
	ת������[8].y=0x8;
	ת������[9].x=-0x2A;
	ת������[9].y=-0x20;
	memset(&ת�̴���,0,sizeof(ת�̴��ڽṹ));
	memset(������������,0,1024);
	if(ת�̶�����ַ) DeathAction(ת�̶�����ַ);
	ת�̶�����ַ=0;
	char *��ʱ=new char [513];
	char *��ʱ1=new char [513];
	int i;
	for(i=0;i<10;i++){
		memset(��ʱ,0,512);
		memset(��ʱ1,0,20);
		getStringFromIndexWithDelim_body((char *) ����,(char *)"#@",i+1,��ʱ,512);
		getStringFromIndexWithDelim_body((char *) ��ʱ,(char *)"|",1,��ʱ1,512);
		ת�̴���.����[i].���� = atoi(��ʱ1);
		getStringFromIndexWithDelim_body((char *) ��ʱ,(char *)"|",2,ת�̴���.����[i].��,64);
		getStringFromIndexWithDelim_body((char *) ��ʱ,(char *)"|",3,ת�̴���.����[i].����,512);
	}
	delete ��ʱ;
	delete ��ʱ1;
	int ���ڿ�=424;
	int ���ڸ�=424;
	ת�̴���.x=(800-���ڿ�)/2+���ڿ�/2;
	ת�̴���.y=(600-���ڸ�)/2-40+���ڸ�/2;
}

ACTION* ����ת�̴���()
{
	if(ת�̶�����ַ) DeathAction(ת�̶�����ַ);
	ת�̶�����ַ=0;
	ת�̶�����ַ = MakeWindowDisp(ת�̴���.x,ת�̴���.y,0,0,40166,0,FALSE);
	play_se(202,320,240);
	return ת�̶�����ַ;
}

void ת����û������()
{
	if(ת�̴���.ת��==1){
		ת�̴���.ת��=2;
		lssproto_WN_send(sockfd,nowGx,nowGy,indexWN,idWN,0,"2");
	}
}
extern short wnCloseFlag;
extern int windowTypeWN;
void ���ת�̶���()
{
	if(ת�̶�����ַ) DeathAction(ת�̶�����ַ);
	ת����û������();
	ת�̶�����ַ=0;
	wnCloseFlag=0;
	windowTypeWN = -1;
	wnCloseFlag = 1;
}
extern int cloasewindows;

ACTION* ת��������ʾ()
{
	//��ͼ
	StockDispBuffer(ת�̴���.x,ת�̴���.y+28,104,40166,1);

	//�ر�
	if(MakeHitBox(ת�̴���.x+0x61,ת�̴���.y-0x99,ת�̴���.x+0x80,ת�̴���.y-0x7D,1)==1){
		StockDispBuffer(ת�̴���.x+0x71-2,ת�̴���.y-0x8B,105,40165,1);
		if( (mouse.onceState & MOUSE_LEFT_CRICK)  && !ת�̴���.��������){
			windowTypeWN = -1;
			wnCloseFlag = 1;
		}
	}
	//��ʼ��ť
	if(ת�̴���.ת��)
		StockDispBuffer(ת�̴���.x,ת�̴���.y+0x1B+1,105,40164,1);
	else{
		if(MakeHitBox(ת�̴���.x-0x30,ת�̴���.y-0x14,ת�̴���.x+0x30,ת�̴���.y+0x4A,1)==1){
			StockDispBuffer(ת�̴���.x,ת�̴���.y+0x1B+1,105,40164,1);
			if( (mouse.onceState & MOUSE_LEFT_CRICK) && !ת�̴���.��������){
				lssproto_WN_send(sockfd,nowGx,nowGy,indexWN,idWN,0,"1");
			}
		}
	}
	if(ת�̴���.ת��==1){
		if(ת�̴���.ָ�����>2){
			ת�̴���.ָ����� = 0;
			if(ת�̴���.ָ��λ��==9) {
				ת�̴���.ָ��Ȧ��++;
				ת�̴���.ָ��λ��=0;
			}
			else ת�̴���.ָ��λ��++;
		}else ת�̴���.ָ�����++;
		if(ת�̴���.ָ��Ȧ�� == 8 && ת�̴���.ָ��λ��==(ת�̴���.ѡ������-1)) {
			ת�̴���.ת��=2;
			ת�̴���.��������=TRUE;
			lssproto_WN_send(sockfd,nowGx,nowGy,indexWN,idWN,0,"2");
		}
	}
	StockDispBuffer(ת�̴���.x+ת������[ת�̴���.ָ��λ��].x,ת�̴���.y+ת������[ת�̴���.ָ��λ��].y,106,40153+ת�̴���.ָ��λ��,1);
	//������ʾ
	int i;
	for(i=0;i<10;i++){
		StockDispBuffer(ת�̴���.x+ת�̵���λ��[i][0],ת�̴���.y+ת�̵���λ��[i][1],106,ת�̴���.����[i].����,1);
		if(!ת�̴���.��������)
		if(MakeHitBox(ת�̴���.x+ת�̵���λ��[i][0]-30,ת�̴���.y+ת�̵���λ��[i][1]-30,ת�̴���.x+ת�̵���λ��[i][0]+30,ת�̴���.y+ת�̵���λ��[i][1]+30,1)==1){
			//extern void ��ʾ��������(short x,short y,UCHAR ���,char* ����,int ���� ,char*����);
			��ʾ��������(ת�̴���.x+ת�̵���λ��[i][0],ת�̴���.y+ת�̵���λ��[i][1],107,ת�̴���.����[i].����,0,ת�̴���.����[i].��);
		}
	}
	//������ʾ
	if(ת�̴���.��������){
		StockDispBuffer(ת�̴���.x-0xC1,ת�̴���.y-0x32,107,40088,1);
		extern int getTextLength(char * str);
		StockFontBuffer(ת�̴���.x-getTextLength(������������)/2,ת�̴���.y+5,2,0,������������,1);
		int ��ťID = StockDispBuffer(ת�̴���.x,ת�̴���.y+50,109,26042,2);
		if( mouse.onceState & MOUSE_LEFT_CRICK ){
			if( HitDispNo == ��ťID ){
				ת�̴���.��������=0;
				windowTypeWN = -1;
				wnCloseFlag = 1;
				memset(������������,0,1024);			
			}
		}
	}
	if(CheckMenuFlag()
		|| ((joy_trg[ 0 ] & JOY_ESC) && GetImeString() == NULL)
		|| actBtn == 1
		|| menuBtn == 1
		|| disconnectServerFlag == TRUE
		|| wnCloseFlag == 1 
		|| cloasewindows == 1) ���ת�̶���();
	return ת�̶�����ַ;
}

void ��ת������(int ѡ������)
{
	ת�̴���.ת��=1;
	ת�̴���.ѡ������=ѡ������;
}
#endif





