#include "../systeminc/version.h"
#include "../systeminc/system.h"
#include "../systeminc/font.h"
#include "../systeminc/action.h"
#include "systeminc\sprdisp.h"
#include "systeminc\menu.h"
#include "systeminc\mouse.h"
#include "newproto\autil.h"
#include "newproto\protocol.h"
#ifdef _CHARTITLE_STR_
extern unsigned int sockfd;
typedef struct{
	BOOL ������ʾ;
	BOOL ȷ��������ʾ;
	int ��ǰҳ��;
	int ȷ��ͼ������;
	char ����[100][32];
	int �ƺ�����[100];
	TITLE_STR title;//��ǰ�ƺ�
	TITLE_STR titledata[100];//�ƺ�����
	BOOL �رմ���;
}�ƺ����ݽṹ;
extern int play_se(int tone, int x, int y);
�ƺ����ݽṹ �ƺ�;

void �򿪳ƺŴ��ڳ�ʼ��()
{
	if(�ƺ�.������ʾ){
		�ƺ�.������ʾ=FALSE;
		�ƺ�.ȷ��������ʾ=FALSE;
	}else{
		�ƺ�.��ǰҳ��=0;
		�ƺ�.������ʾ=TRUE;
		�ƺ�.ȷ��������ʾ=FALSE;
	}
}

extern void PutTitleText(int x,int y,char fontPrio,TITLE_STR str,BOOL hitFlag);

BOOL ��ȡ�ƺ�ȡ������()
{
	return �ƺ�.�رմ���;
}

void ���óƺ�ȡ������()
{
	if(�ƺ�.�رմ���) �ƺ�.�رմ���=FALSE;
	else �ƺ�.�رմ���=TRUE;
}

BOOL ��ȡ��ǰ�ƺ��Ƿ����()
{
	return �ƺ�.title.flg;
}

void �ƺ�չʾ()
{
	if(�ƺ�.title.flg){
		PutTitleText(78-�ƺ�.title.len/2,49,FONT_PRIO_FRONT,�ƺ�.title,0);
	}
	int bnt;
	bnt = StockFontBuffer(18,49,1,FONT_PAL_GREEN,"                             ",2);
	if(mouse.onceState & MOUSE_LEFT_CRICK>0){
		if(HitFontNo == bnt){
			if(�ƺ�.�رմ���) �ƺ�.�رմ���=FALSE;
			else �ƺ�.�رմ���=TRUE;
			play_se(203, 320, 240);
		}
	}
}

BOOL ����ƺŴ���(ACTION * pct)
{
	int x,y;
	x = pct->x;
	y = pct->y + 133;
	int ��ť��=-1;
	int ��ť��=-1;
	int ��ť�ر�=-1;
	int ��ťID;
	��ť�� = StockDispBuffer( x -55, y + 7, DISP_PRIO_IME3, 55250, 2 );
	��ť�� = StockDispBuffer( x -20, y + 7, DISP_PRIO_IME3, 55251, 2 );
	��ť�ر� = StockDispBuffer( x+40, y + 7, DISP_PRIO_IME3, 55252, 2 );
	if( mouse.onceState & MOUSE_LEFT_CRICK ){
		if(!�ƺ�.ȷ��������ʾ){
			if(��ť�� == HitDispNo){
				if(�ƺ�.��ǰҳ��){
					�ƺ�.��ǰҳ��--;
				}
			}
			if(��ť�� == HitDispNo){
				if(�ƺ�.��ǰҳ��!=19 && �ƺ�.titledata[(�ƺ�.��ǰҳ��+1)*5].flg)
				{
					�ƺ�.��ǰҳ��++;
				}
			}
			if(��ť�ر� == HitDispNo){
				DeathAction(pct);
				�ƺ�.������ʾ=FALSE;
				�ƺ�.ȷ��������ʾ=FALSE;
				return TRUE;
			}
		}
	}

	int i=0;
	int �ƺ�ͼ������;
	for(;i<5;i++){
		�ƺ�ͼ������ = �ƺ�.��ǰҳ��*5+i;
		if(�ƺ�.titledata[�ƺ�ͼ������].flg)
		{
			PutTitleText(380-�ƺ�.titledata[�ƺ�ͼ������].len/2,43+i*0x20,FONT_PRIO_FRONT,�ƺ�.titledata[�ƺ�ͼ������],0);
			char �ƺ����[128];
			sprintf_s(�ƺ����,"%03d",�ƺ�ͼ������+1);
			StockFontBufferExt(0x130,0x2D+i*0x20,1,FONT_PAL_GREEN,�ƺ����,0,19);
			if(!�ƺ�.ȷ��������ʾ){
				if(MakeHitBox(0x124,0x26+i*0x20,0x1B8,0x44+i*0x20,0x6D)==1){
					StockFontBuffer(0x123,0xD1,2,0,�ƺ�.����[�ƺ�ͼ������],0);
					if(mouse.onceState & MOUSE_LEFT_CRICK>0){
						�ƺ�.ȷ��ͼ������=�ƺ�.�ƺ�����[ �ƺ�ͼ������];
						�ƺ�.ȷ��������ʾ=TRUE;
					}
				}
			}
		}else break;
	}
	if(�ƺ�.ȷ��������ʾ){
		StockFontBuffer(0x123,0xD1,2,0,�ƺ�.����[�ƺ�.ȷ��ͼ������],0);
		StockFontBuffer(0x130,0x118,2,0,"ȷ��ʹ�øóƺ���",0);
		StockDispBuffer(0x16D,0x130,0x6C,55253,1);//ȷ�����ڵ�ͼ
		��ťID = StockDispBuffer(0x194,0x148,109,55252,2);//�ر�
		if(mouse.onceState & MOUSE_LEFT_CRICK>0){
			if(��ťID == HitDispNo){
				�ƺ�.ȷ��������ʾ=FALSE;
				�ƺ�.ȷ��ͼ������=0;
			}
		}
		��ťID = StockDispBuffer(0x148,0x148,109,55254,2);//ȷ��
		if(mouse.onceState & MOUSE_LEFT_CRICK>0){
			if(��ťID == HitDispNo){
				int checksum=0;
				char buf[1024*4];
				memset(buf,0,1024*4);
				checksum += util_mkint(buf, �ƺ�.ȷ��ͼ������);
				util_mkint(buf, checksum);
				util_SendMesg(sockfd, LSSPROTO_CHARTITLE_SEND, buf);
				�ƺ�.ȷ��������ʾ=FALSE;
				�ƺ�.ȷ��ͼ������=0;
			}
		}
	}
	return FALSE;
}
extern void getCharTitleSplit( char *str,TITLE_STR* title);
void ����ƺ����ݸ���(char *����)
{
	char ��������[126],ͼ������[1024],ͼ������[1024],���ݽ���[4000],��ʱ[126];
	memset(��������,0,126);
	memset(ͼ������,0,1024);
	memset(ͼ������,0,1024);
	memset(���ݽ���,0,4000);
	getStringFromIndexWithDelim_body((char *) ����,(char *)"#@",1,��������,126);
	getStringFromIndexWithDelim_body((char *) ��������,(char *)"|",1,��ʱ,126);
	int titleindex = atoi(��ʱ);
	extern char* FreeGetTitleStr(int id);
	if(titleindex>0) getCharTitleSplit(FreeGetTitleStr(titleindex),&�ƺ�.title);
	else memset(&�ƺ�.title,0,sizeof(TITLE_STR));
	getStringFromIndexWithDelim_body((char *) ��������,(char *)"|",2,��ʱ,126);
	int ���� = atoi(��ʱ);
	if(����!=0){
		memset(&�ƺ�.titledata,0,sizeof(�ƺ�.titledata[0])*100);
		memset(&�ƺ�.�ƺ�����,0,sizeof(int)*100);
		memset(&�ƺ�.����,0,32*100);
		getStringFromIndexWithDelim_body((char *) ����,(char *)"#@",2,ͼ������,1024);
		getStringFromIndexWithDelim_body((char *) ����,(char *)"#@",3,���ݽ���,4000);
		getStringFromIndexWithDelim_body((char *) ����,(char *)"#@",4,ͼ������,1024);
		int i=0;
		extern char* FreeGetTitleStr(int id);
		for(i;i<����;i++){
			getStringFromIndexWithDelim_body((char *)ͼ������,(char *)"|",i+1,��ʱ,126);
			titleindex = atoi(��ʱ);
			getCharTitleSplit(FreeGetTitleStr(titleindex),&�ƺ�.titledata[i]);
			getStringFromIndexWithDelim_body((char *)ͼ������,(char *)"|",i+1,��ʱ,126);
			�ƺ�.�ƺ�����[i]=atoi(��ʱ);
			getStringFromIndexWithDelim_body((char *)���ݽ���,(char *)"|",i+1,��ʱ,126);
			sprintf_s(�ƺ�.����[i],32,"%s",��ʱ);
		}
	}
}

void ��ʼ���ƺŽṹ()
{
	memset(&�ƺ�,0,sizeof(�ƺ����ݽṹ));
}
#endif



#ifdef _CHARTITLE_
extern unsigned int sockfd;
typedef struct{
	int �ƺŴ��ڽṹ;
	ACTION *�ƺŽṹ[5];
	ACTION * ��ǰ�ƺŽṹ;
	int ��ǰ�ƺ�ͼ��;
	BOOL ������ʾ;
	int ͼ��[100];
	int �ƺ�����[100];
	char ����[100][32];
	int ��ǰҳ��;
	BOOL ȷ��������ʾ;
	int ȷ��ͼ������;
}�ƺ����ݽṹ;

�ƺ����ݽṹ �ƺ�;

void �����ƺ�չʾ����()
{
	int i=0;
	for(i;i<5;i++){
		if(�ƺ�.�ƺŽṹ[i]){
			if(�ƺ�.�ƺŽṹ[i]) DeathAction(�ƺ�.�ƺŽṹ[i]);
			�ƺ�.�ƺŽṹ[i]=0;
		}					
	}
}

void �򿪳ƺŴ��ڳ�ʼ��()
{
	if(�ƺ�.������ʾ){
		�����ƺ�չʾ����();
		�ƺ�.������ʾ=FALSE;
		�ƺ�.ȷ��������ʾ=FALSE;
	}else{
		�ƺ�.��ǰҳ��=0;
		�ƺ�.������ʾ=TRUE;
		�ƺ�.ȷ��������ʾ=FALSE;
	}
}


void �ƺ�չʾ()
{

	if(�ƺ�.��ǰ�ƺ�ͼ��)
		if(!�ƺ�.��ǰ�ƺŽṹ){
			if(�ƺ�.��ǰ�ƺ�ͼ�� < 100000){
				�ƺ�.��ǰ�ƺŽṹ = 0;
				StockDispBuffer(0x7F,0x40,109,�ƺ�.��ǰ�ƺ�ͼ��,0);
			}else{
				�ƺ�.��ǰ�ƺŽṹ = MakeAnimDisp(0x7F,0x59,�ƺ�.��ǰ�ƺ�ͼ��,0);
			}
		}else if(*(int *)(�ƺ�.��ǰ�ƺŽṹ+0x140)!= �ƺ�.��ǰ�ƺ�ͼ��){
			DeathAction(�ƺ�.��ǰ�ƺŽṹ);
			if(�ƺ�.��ǰ�ƺ�ͼ�� < 100000){
				�ƺ�.��ǰ�ƺŽṹ = 0;
				StockDispBuffer(0x7F,0x40,109,�ƺ�.��ǰ�ƺ�ͼ��,0);
			}else{
				�ƺ�.��ǰ�ƺŽṹ = MakeAnimDisp(0x7F,0x59,�ƺ�.��ǰ�ƺ�ͼ��,0);
			}
		}
}

BOOL ����ƺŴ���(ACTION * pct)
{
	int x,y;
	x = pct->x;
	y = pct->y + 133;
	int ��ť��=-1;
	int ��ť��=-1;
	int ��ť�ر�=-1;
	int ��ťID;
	��ť�� = StockDispBuffer( x -55, y + 7, DISP_PRIO_IME3, 55250, 2 );
	��ť�� = StockDispBuffer( x -20, y + 7, DISP_PRIO_IME3, 55251, 2 );
	��ť�ر� = StockDispBuffer( x+40, y + 7, DISP_PRIO_IME3, 55252, 2 );
	if( mouse.onceState & MOUSE_LEFT_CRICK ){
		if(!�ƺ�.ȷ��������ʾ){
			if(��ť�� == HitDispNo){
				if(�ƺ�.��ǰҳ��){
					�ƺ�.��ǰҳ��--;
					�����ƺ�չʾ����();
				}
			}
			if(��ť�� == HitDispNo){
				if(�ƺ�.��ǰҳ��!=19 && �ƺ�.ͼ��[(�ƺ�.��ǰҳ��+1)*5]){
					�ƺ�.��ǰҳ��++;
					�����ƺ�չʾ����();
				}
			}
			if(��ť�ر� == HitDispNo){
				DeathAction(pct);
				�����ƺ�չʾ����();
				�ƺ�.������ʾ=FALSE;
				�ƺ�.ȷ��������ʾ=FALSE;
				return TRUE;
			}
		}
	}

	int i=0;
	int �ƺ�ͼ������;
	for(;i<5;i++){
		�ƺ�ͼ������ = �ƺ�.��ǰҳ��*5+i;
		if(�ƺ�.ͼ��[�ƺ�ͼ������]){
			if(!�ƺ�.�ƺŽṹ[i]){
				if(�ƺ�.ͼ��[�ƺ�ͼ������] < 100000){
					�ƺ�.�ƺŽṹ[i] = 0;
					StockDispBuffer(0x16D+20,0x35+i*0x20,109,�ƺ�.ͼ��[�ƺ�ͼ������],0);
				}else{
					�ƺ�.�ƺŽṹ[i] = MakeAnimDisp(0x16D+20,0x35+i*0x20,�ƺ�.ͼ��[�ƺ�ͼ������],0);
				}
			}else if(�ƺ�.��ǰ�ƺŽṹ==0) StockDispBuffer(0x16D,0x35+i*0x20,109,�ƺ�.ͼ��[�ƺ�ͼ������],0);
			char �ƺ����[128];
			sprintf_s(�ƺ����,"%03d",�ƺ�ͼ������+1);

			StockFontBufferExt(0x130,0x2D+i*0x20,1,FONT_PAL_GREEN,�ƺ����,0,16);
			if(!�ƺ�.ȷ��������ʾ){
				if(MakeHitBox(0x124,0x26+i*0x20,0x1B8,0x44+i*0x20,0x6D)==1){
					StockFontBuffer(0x123,0xD1,2,0,�ƺ�.����[�ƺ�ͼ������],0);
					if(mouse.onceState & MOUSE_LEFT_CRICK>0){
						�ƺ�.ȷ��ͼ������=�ƺ�.�ƺ�����[ �ƺ�ͼ������];
						�ƺ�.ȷ��������ʾ=TRUE;
					}
				}
			}
		}else break;
	}
	if(�ƺ�.ȷ��������ʾ){
		StockFontBuffer(0x123,0xD1,2,0,�ƺ�.����[�ƺ�.ȷ��ͼ������],0);
		StockFontBuffer(0x130,0x118,2,0,"ȷ��ʹ�øóƺ���",0);
		StockDispBuffer(0x16D,0x130,0x6C,55253,1);//ȷ�����ڵ�ͼ
		��ťID = StockDispBuffer(0x194,0x148,109,55252,2);//�ر�
		if(mouse.onceState & MOUSE_LEFT_CRICK>0){
			if(��ťID == HitDispNo){
				�ƺ�.ȷ��������ʾ=FALSE;
				�ƺ�.ȷ��ͼ������=0;
			}
		}
		��ťID = StockDispBuffer(0x148,0x148,109,55254,2);//ȷ��
		if(mouse.onceState & MOUSE_LEFT_CRICK>0){
			if(��ťID == HitDispNo){
				int checksum=0;
				char buf[1024*4];
				memset(buf,0,1024*4);
				checksum += util_mkint(buf, �ƺ�.ȷ��ͼ������);
				util_mkint(buf, checksum);
				util_SendMesg(sockfd, LSSPROTO_CHARTITLE_SEND, buf);
				�ƺ�.ȷ��������ʾ=FALSE;
				�ƺ�.ȷ��ͼ������=0;
			}
		}
	}
	return FALSE;
}

void ���ڽ�������(ACTION* ID)//������ʾ���� 
{
	�ƺ�.������ʾ=FALSE;
	�����ƺ�չʾ����();
	if(�ƺ�.��ǰ�ƺŽṹ) DeathAction(�ƺ�.��ǰ�ƺŽṹ);
	�ƺ�.��ǰ�ƺŽṹ=0;
	DeathAction(ID);
}

void ����ƺ����ݸ���(char *����)
{
	char ��������[126],ͼ������[1024],ͼ������[1024],���ݽ���[4000],��ʱ[126];
	memset(��������,0,126);
	memset(ͼ������,0,1024);
	memset(ͼ������,0,1024);
	memset(���ݽ���,0,4000);
	getStringFromIndexWithDelim_body((char *) ����,(char *)"#@",1,��������,126);
	getStringFromIndexWithDelim_body((char *) ��������,(char *)"|",1,��ʱ,126);
	int ֵ = atoi(��ʱ);
	if(ֵ) �ƺ�.��ǰ�ƺ�ͼ��=ֵ;
	getStringFromIndexWithDelim_body((char *) ��������,(char *)"|",2,��ʱ,126);
	int ���� = atoi(��ʱ);
	if(����!=0){
		memset(&�ƺ�.ͼ��,0,sizeof(int)*100);
		memset(&�ƺ�.�ƺ�����,0,sizeof(int)*100);
		memset(&�ƺ�.����,0,32*100);
		getStringFromIndexWithDelim_body((char *) ����,(char *)"#@",2,ͼ������,1024);
		getStringFromIndexWithDelim_body((char *) ����,(char *)"#@",3,���ݽ���,4000);
		getStringFromIndexWithDelim_body((char *) ����,(char *)"#@",4,ͼ������,1024);
		int i=0;
		for(i;i<����;i++){
			getStringFromIndexWithDelim_body((char *)ͼ������,(char *)"|",i+1,��ʱ,126);
			�ƺ�.ͼ��[i]=atoi(��ʱ);
			getStringFromIndexWithDelim_body((char *)ͼ������,(char *)"|",i+1,��ʱ,126);
			�ƺ�.�ƺ�����[i]=atoi(��ʱ);
			getStringFromIndexWithDelim_body((char *)���ݽ���,(char *)"|",i+1,��ʱ,126);
			sprintf_s(�ƺ�.����[i],32,"%s",��ʱ);
		}
	}
}

void ��ʼ���ƺŽṹ()
{
	memset(&�ƺ�,0,sizeof(�ƺ����ݽṹ));
}
#endif


