#include "../systeminc/version.h"
#include "../systeminc/system.h"
#include "../systeminc/CharSignDay.h"
#include "../newproto/autil.h"
#include "../systeminc/menu.h"
#include "../systeminc/shop.h"
#include "../systeminc/t_music.h"
#include "../newproto/protocol.h"
#include "../other/caryIme.h"
#include "../systeminc/field.h"
#include "../systeminc/netmain.h"
#ifdef _CHARSIGNDAY_
extern unsigned int sockfd;
extern int nowGx, nowGy;
extern int indexWN;
extern int idWN;
extern short wnCloseFlag;
extern int cloasewindows;
extern int windowTypeWN;
ACTION * ǩ��������ַ=0;
int ǩ������X,ǩ������Y;
extern char ������������[1024];
int ǩ����������;

typedef struct {
	int ID;
	char ������[64];
	char ����[512];
}ǩ�����߽ṹ;

typedef struct {
	int ���߿�;
	int ״̬;
	int ��������;
	int ���켸��;
	ǩ�����߽ṹ ����[30];
}ǩ���ṹ;

ǩ���ṹ ǩ������;
short ǩ��������������[][2]={
							{0,3},
							{1,6},
							{2,8},
							{3,11},
							{4,13},
							{5,16}
						 };
int ǩ�����ڿ�=588;
int ǩ�����ڸ�=396;

void ǩ�����ڳ�ʼ��(char * ����)
{
	memset(&ǩ������,0,sizeof(ǩ���ṹ));
	memset(������������,0,1024);
	if(ǩ��������ַ) DeathAction(ǩ��������ַ);
	ǩ��������ַ=0;
	char *��ʱ=new char [512];
	char *��ʱ����=new char [512];
	memset(��ʱ,0,512);
	memset(��ʱ����,0,512);
	getStringFromIndexWithDelim_body((char *) ����,(char *)"|",1,��ʱ,10);
	ǩ������.���߿�=atoi(��ʱ);
	memset(��ʱ,0,10);
	getStringFromIndexWithDelim_body((char *) ����,(char *)"|",2,��ʱ,10);
	ǩ������.��������=atoi(��ʱ);
	memset(��ʱ,0,10);
	getStringFromIndexWithDelim_body((char *) ����,(char *)"|",3,��ʱ,10);
	ǩ������.���켸��=atoi(��ʱ);
	memset(��ʱ,0,10);
	getStringFromIndexWithDelim_body((char *) ����,(char *)"|",4,��ʱ,30);
	ǩ������.״̬=atoi(��ʱ);
	memset(��ʱ,0,512);
	memset(��ʱ����,0,512);
	int i;
	for(i=0;i<ǩ������.��������;i++){
		getStringFromIndexWithDelim_body((char *) ����,(char *)"#@",2+i,��ʱ,512);
		getStringFromIndexWithDelim_body((char *) ��ʱ,(char *)"|",1,��ʱ����,10);
		ǩ������.����[i].ID=atoi(��ʱ����);
		memset(��ʱ����,0,10);
		getStringFromIndexWithDelim_body((char *) ��ʱ,(char *)"|",2,��ʱ����,64);
		sprintf(ǩ������.����[i].������,"%s",��ʱ����);
		memset(��ʱ����,0,64);
		getStringFromIndexWithDelim_body((char *) ��ʱ,(char *)"|",3,��ʱ����,512);
		sprintf(ǩ������.����[i].����,"%s",��ʱ����);
		memset(��ʱ,0,512);
		memset(��ʱ����,0,512);
	}
	delete ��ʱ;
	delete ��ʱ����;
	ǩ����������=0;
	ǩ������X=(800-ǩ�����ڿ�)/2+ǩ�����ڿ�/2;
	ǩ������Y=(600-ǩ�����ڸ�)/2-40+ǩ�����ڸ�/2;
}

ACTION* ����ǩ������()
{
	if(ǩ��������ַ) DeathAction(ǩ��������ַ);
	ǩ��������ַ = MakeWindowDisp(ǩ������X,ǩ������Y,0,0,55217,0,FALSE);
	play_se(202,320,240);
	return ǩ��������ַ;
}

void ���ǩ������()
{
	if(ǩ��������ַ) DeathAction(ǩ��������ַ);
	ǩ��������ַ=0;
	wnCloseFlag=0;
	windowTypeWN = -1;
	wnCloseFlag = 1;
}

ACTION* ǩ��������ʾ()
{
	int ����X=55;
	int ����Y=58;
	int ��ǰ��������=0;
	int i,b;
	for(i=0;i<5;++i){
		for(b=0;b<6;++b){
			��ǰ��������++;
			StockDispBuffer(ǩ������X-225+b*����X,ǩ������Y-65+i*����Y,106,ǩ������.����[��ǰ��������-1].ID,1);//����
			if(MakeHitBox(ǩ������X-225+b*����X-26,ǩ������Y-65+i*����Y-26,ǩ������X-225+b*����X+26,ǩ������Y-65+i*����Y+26,1)==1){
				if(!ǩ����������) ��ʾ��������(ǩ������X-225+b*����X,ǩ������Y-65+i*����Y,112,ǩ������.����[��ǰ��������-1].����,0,ǩ������.����[��ǰ��������-1].������);
			}
			if((ǩ������.״̬&(1<<��ǰ��������)))
			//	StockDispBuffer(400, 288, DISP_PRIO_MENU-1, 55256, 0);
				StockDispBuffer(ǩ������X-225+b*����X,ǩ������Y-65+i*����Y,107,55269,1);//ǩ���ɹ�
			if(��ǰ�������� >= ǩ������.��������) break;
		}
	}
//��ͼ
	StockDispBuffer(ǩ������X,ǩ������Y+28,104,55217,1);
//ǩ��
	int ��ťID = StockDispBuffer(ǩ������X+200,ǩ������Y+207,105,55216,2);
	if( mouse.onceState & MOUSE_LEFT_CRICK ){
		if( HitDispNo == ��ťID ){
			lssproto_WN_send(sockfd,nowGx,nowGy,indexWN,idWN,0,"1");
			ǩ����������=1;		
		}
	
	}
	
//�ر�
	if(MakeHitBox(ǩ������X+253,ǩ������Y-175,ǩ������X+283,ǩ������Y-149,1)==1){
		StockDispBuffer(ǩ������X+270,ǩ������Y-160,105,40165,1);
		if(mouse.onceState & MOUSE_LEFT_CRICK  && !ǩ����������){
			windowTypeWN = -1;
			wnCloseFlag = 1;
		}
	}
	
	if(ǩ����������){
		StockDispBuffer(ǩ������X-186,ǩ������Y-58,111,40088,1);
		StockFontBuffer(ǩ������X-138,ǩ������Y-16,2,0,������������,0);
		��ťID = StockDispBuffer(ǩ������X+5,ǩ������Y+37,112,26042,2);
		if( mouse.onceState & MOUSE_LEFT_CRICK ){
			if( HitDispNo == ��ťID ){
				ǩ����������=0;
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
		|| cloasewindows == 1) ���ǩ������();
	return ǩ��������ַ;
}

void ��ǩ��״̬(int ״̬)
{
	ǩ������.״̬=״̬;
}



#endif



