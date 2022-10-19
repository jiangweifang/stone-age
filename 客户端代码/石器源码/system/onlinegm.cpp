//cyg  ʵ����һ��ϵͳ (���ϻر�ϵͳ)
#include"../systeminc/version.h"
#include"../systeminc/system.h"
#include"../systeminc/loadrealbin.h"
#include"../systeminc/loadsprbin.h"
#include"../systeminc/anim_tbl.h"
#include"../systeminc/login.h"
#include"../systeminc/menu.h"
#include"../systeminc/map.h"
#include"../systeminc/lssproto_cli.h"
#include"../systeminc/pc.h"
#include"../systeminc/netmain.h"
#include"../systeminc/handletime.h"
#include"../systeminc/character.h"
#include"../other/caryIme.h"
#include"../systeminc/ime_sa.h"
#include"../systeminc/t_music.h"
#include"../systeminc/netproc.h"
#include"../systeminc/tool.h"
#include "time.h"
#include "../wgs/descrypt.h"
#include"../systeminc/onlinegm.h"

char ProblemClass[DEF_CLASS_TOTAL][16]={
	"�쳣����",
	"һ������"
};
char ProblemC1[DEF_C1_TOTAL][30]={
	"���˿�ʯ",
    "��ҳָ��",
	"�ͷ���Ʒ�",
	"��װ�����",
	"��Ա�ʺ�",
	"��Ʒ���",		
	"��Ʒ���",
	"��Ϸ���������򼰴�ֵ",
	"�������",
	"����/�ŷ�������/�ܱ���Ʒ",
	"������/����/��·״����Ӧ",
    "��Ϸ����ѯ��",
	"�Ƿ����Ͷ��",
	"����"	
};
char ProblemC1Help[DEF_C1_TOTAL][60]={
	"��ע���쳣�ʺš����ꡢ�ص㡢����ѶϢ����ϵ",
	"���ṩ�������",
	"���Ȳ�ѯ��Ϸר����վ�Լ������ͷ�����",
	"�뾡���������ĵ����䱸",
	"������������״��",
	"���ṩ���������",
	"���ṩ���������",
	"������Ϸ���ֿ۵㲻���������ѡ���������Ϊ(��Ϸ�۵�����)",
	"",
	"���Ȳ�ѯר����ҳ��ػ",
	"",
	"���Ȳ�ѯ��ҳFAQ",
	"",
	""
};
char ProblemC2[DEF_C2_TOTAL][16]={
	"�����쳣",
	"�����쳣",
	"�����쳣",
	"��������",
	"���Ƶ���",
	"��������",
	"�����������",
	"�ףǣӿ۵�����",
	"����",  
	"��Ա����",
	"��ϵ����",	
};
//�����쳣
char ProblemC2_1[3][16]={
	"������ʧ",
	"���������쳣",
	"����"
};
//�����쳣
char ProblemC2_2[3][16]={
	"������ʧ",
	"����",
	"���߹����쳣"
};
//�����쳣
char ProblemC2_3[5][16]={
	"������ʧ",
	"�����ʼ�����",
	"�������",
	"���ﵰ����",
	"����"
};
//��������
char ProblemC2_4[2][16]={
	"���׺���ʧ",
	"����"
};
//���Ƶ���
char ProblemC2_5[2][16]={
	"���Ƶ��ò�ѯ",
	"����"
};
//��������
char ProblemC2_6[3][16]={
	"���屻��ɢ",
	"�����쳣",
	"����"
};
//��ϵ����
char ProblemC2_7[3][16]={
	"������ʧ",
	"������ʧ",
	"����"
};

//HELP��ʹ�õ���ҳ���Ͻṹ
typedef struct PAGE{
	short	desc_index;			//˵���ṹ��ʼ��������(��desc_indexΪ����seg_index��help_indexȡ��DESC�����е�index)
	int		desc_num;//BYTE	desc_num;			//˵���Ľṹ��
}*LPPAGE;

//ע������
//HELP��ʹ�õ�˵�����������Ͻṹ
typedef struct DESC{
	BYTE	color;				//��ɫ
	char	description[60];	//˵������
}*LPDESC;


// �����������ṹ cyg  
typedef struct{
	char no[20];
	char state[40];	  							
	char okdate[10];
	int  okH;
	char wrongdate[10];
	int  wrongH;
	int	 class0;
	char class1[40];
	char cont[4000];
	char answer[4000];
	char error[2000];
	BOOL delflag;
}PRODATA;


DESC Prohelp_desc1[]={
			//��ɫ��˵�� //fix				
			{ 4 , "1. ʹ��˵��"},
			{ 0 , "		������������Ϊ20�ʣ����Ѵ��������Ƚ��������ⵥɾ��������"},
			{ 0 , "		��������������ҳ�������쳣��������������������������ڡ�"},
			{ 0 , "		�� �������ⵥ����ʾ�����Ϸ���"},
			{ 4 , "2. ���ﵰ�쳣"},
			{ 0 , "		��2003/12/31�շ���������ʱ���������������ﵰ�趨�ĳ�ʽ"},
			{ 0 , "		��������ͷ����Ľ�����������ҳ��ﵰ�����쳣�����������"},
			{ 0 , "		��ĳ��ﵰ�趨���£�"},
			{ 0 , "		�� ����������ι���趨������һ��������һСʱ����������"},
			{ 0 , "		   ����������������߻���ﵰ�����ڳ���У��ٴε����"},
			{ 0 , "		   ���¼���ι����ʱ�䡣"},
			{ 4 , "3. �����ʧ"},
			{ 0 , "		��Ϸ��ʽ�趨������ͬһ�ŷ������ڣ��������ſڵ�[������Ա]"},						
};

DESC Prohelp_desc2[]={
			{ 0 , "		ȡ�أ����޷���ȡ���ṩ�������ϳ������ơ��ȼ�������ԭ����"},
			{ 0 , "		�ʺš�����������ڡ�������ʧ���ڡ�"},
			{ 4 , "4. ������ʧ"},
			{ 0 , "		��Ϸ��ʽ�趨������ͬһ�ŷ������ڣ��������ſڵ�[������Ա]"},
			{ 0 , "		ȡ�أ����޷���ȡ���ṩ�������ϳ������ơ��ȼ�������ԭ����"},
			{ 0 , "		�ʺš�����������ڡ�������ʧ���ڡ�"},
			//{ 4 , "4. ����ս������-�޷�����"},
			//{ 0 , "		������ҳ϶ȵ���20���£���ս���оͻ����ߡ���Ϊԭ��Ϸ�趨"},
			//{ 0 , "		���ͷ����Ĳ�����ظ����"},
			{ 4 , "5. ���׺���Ʒ��ʧ-���ṩ��������"},
			{ 0 , "		���׷����ʺŻ��������ơ��������ڡ����׵ĳ��������Լ��ȼ�"},
			{ 0 , "		�����������Լ�������"},
			{ 4 , "6. ������������NPC-�޷�����"},
			{ 0 , "		��Ϊԭ��Ϸ�趨���ͷ����Ĳ�����ظ��������ߡ�"},
			{ 4 , "7. �������߶�����ϵͳ���-�޷�����"},
			{ 0 , "		��Ϊԭ��Ϸ�趨���ͷ����Ĳ�����ظ��������ߣ���ҿ�����"},			
};

DESC Prohelp_desc3[]={
			{ 0 , "		Ϸ��͸�����׽���ת�ơ�"},
			{ 4 , "8. �����쳣-���ṩ��������"},
			{ 0 , "		�����쳣���峤�����ʺ�������ע���������ơ������š��쳣"},
			{ 0 , "		״��������Ϊ�����������㣬ϵͳ�Զ���ɢ�ļ��壬��ͬ������"},
			{ 0 , "		�д��ͷ������޷�����"},
			{ 0 , "		�� ���ڼ����ɢ���Ա�����δ���߶��Զ��˳������趨��ϵ"},
			{ 0 , "		   ͳÿ��᲻��ʱ��ɨ�衢��⡣"},
			{ 0 , "		�� Ŀǰ�����Ա�趨�����˳���7�����޷��ټ�����塣"},
			{ 4 , "9. ����DP�쳣-�޷�����	"},
			{ 0 , "		����DP������Ϸ�в�������Ӱ�죬���޿��Ŵ˹��ܹ���Ҳ�ѯ��"},
			{ 4 , "10. ������Ƭ��ʧ-�޷�����"},
			{ 0 , "		������Ƭ�Ķ�Ӧ����һ�Զ�����(һ������ӵ�ж�λ��ҵ���"},
			{ 0 , "		Ƭ)���������������һ����Ҳ��޷�ʹ������ȷ�����޿��Ŵ�"},
};

DESC Prohelp_desc4[]={
			{ 0 , "		���ܹ���Ҳ�ѯ��"},
			{ 4 , "11. ����&թƭ����-���ṩ��������"},
			{ 0 , "		�������ơ��ȼ��Լ��������ơ����������Ƶ������� ������Ա"},
			{ 0 , "		�ɲ�ѯ����ɾ����¼��������Ҳ�Ҫ�����������Ա�ظ�������"},
			{ 0 , "		(û�г�������Լ�ʯ��)�� ������Ա��������ṩ֮���ߡ�"},
			{ 0 , "		������в�ѯ�Ķ�����"},
			{ 4 , "12. ��ȸת���趨  2003/06/21"},
			{ 0 , "		�����֮��ȸ����ֵ����ת��������С���ɳ��ռ䣬��ԭ����"},
			{ 0 , "		ֵ���ݲ�һ����ά��ת��ǰ�ߵ㣬�ڴ��������Ҫת����ȸʱ��"},
			{ 0 , "		���ӿ��ǡ��ͷ����Ĳ�����ظ�ת��ǰ��ȸ֮����������"},
};

//DESC Prohelp_desc5[]={
//};

LPDESC Prohelp_Index[] ={
	&Prohelp_desc1[0],
	&Prohelp_desc2[0],
	&Prohelp_desc3[0],
	&Prohelp_desc4[0]
//	&Prohelp_desc5[0]
};

PAGE ProHelp_page[]={
			{ 0 , sizeof(Prohelp_desc1)/sizeof(Prohelp_desc1[0])},
			{ 0 , sizeof(Prohelp_desc2)/sizeof(Prohelp_desc2[0])},
			{ 0 , sizeof(Prohelp_desc3)/sizeof(Prohelp_desc3[0])},
			{ 0 , sizeof(Prohelp_desc4)/sizeof(Prohelp_desc4[0])}
//			{ 0 , sizeof(Prohelp_desc5)/sizeof(Prohelp_desc5[0])}
};


INPUT_HISTORY  InputHistory ;	// ��������ÿһ�е����ݣ����������������

STR_BUFFER  SubBuffer ;		//  ÿһ�д����buf

#ifdef __ONLINEGM  // ȫ�ص�

char DataBuffer[500];		//  ������Ϻõ�����ر�һ�����Ĳ���
char InputBuffer[8050];		//  ������ҵ���������   
char ContentBuf[8050];		//  ������Ϻõ���������

PRODATA  Prodata[100];		//  ������������Խ�100��

int		PutKey,PushKey ; 

int		ProNoSelect;        //	������ѡ��ĵ�������
int     HistorySelect;      //  �ϴ�ѡ���ѯ�ĵ�������
BOOL	ProNoSelectFlag;	//  ��û��ѡ���ŵ����
int		ProNoIndex;			//  ���������ⵥ��
int		ProNoValue;			//  ��ʾ�м������ⵥ��

BOOL    TitleFlag ;			
int     SegmentIndex ;		//  һ��һ�����ݵ�����
int     SegmentTotal ;		//  ��¼�ܹ��м���
char    SegmentBuf[2][2500];//  ��¼ĳ�ʵ��ŵ����ݺͿͷ���Ӧ

int		okY,okM,okD,okH,wrongY,wrongM,wrongD,wrongH;
int 	ClassIndex , ClassIndex1 , ClassIndex2 ;  //  �����������

BOOL	DeleteBtnFlag;      //Ҫ��ѡ��ĳ���Ų���ɾ�������
      

//OnlineGm ��Log ר���� Begin
#ifdef _STONDEBUG_
char    inlogstr[512];
#define filename     "onlinegm.log"
#endif
//OnlineGm ��Log ר���� End

//�߻�ϵͳ ����Server IP : 10.1.0.17 

BOOL QueryOnlineGmIP(char HostName[]);
char *OnlineGmIP;	   //ʹ��domain name
//char OnlineGmIP[20];   //ʹ��ֱ��ip
#define SMSDomainName   "ingame.wayi.com.tw"//"sms.hwaei.com.tw"

int     ResultCode;  // �������������� 

static char *pContent=NULL;

BOOL ResetFlag = TRUE;
BOOL DirFlag = TRUE;
DWORD  LastTime = 0;
int  iReturnNo;  //��¼�ش��ĵ���

int	 TotalAddValue;   //��¼���Ŀǰ��������

int  ProblemType ;  //��¼�����ͼ�ʱ���ⵥ������  һ��0�쳣1
int  SendType    ;  //��¼���͸�serverǰ����������

unsigned int  ichecklooptime = 0;    //������߻�Ȧʱ��

//*************************************
//	��ʼ����
//*************************************
void InitOnlineGm( void )
{
	int i;
	
	PutKey = 0;
	PushKey = 0;
	ProNoSelectFlag = FALSE;
	ProNoSelect = 0;
	HistorySelect = 5000;  //������ ������
	ProNoIndex = 0;
	ProNoValue = 0;
	SegmentIndex =0;
	SegmentTotal = 0;
	okY=okM=okD=okH=wrongY=wrongM=wrongD=wrongH=0;
	ClassIndex = 1;
	ClassIndex1 = ClassIndex2 =0;
	
	ResetFlag = TRUE ;
	DirFlag = TRUE ;
	DeleteBtnFlag = FALSE ;

	DataBuffer[0] = '\0';
	InputBuffer[0] = '\0';
	ContentBuf[0] = '\0';

	SegmentBuf[0][0]='\0';
	SegmentBuf[1][0]='\0';

	for( i=0;i<DEF_MAX_ADD_VALUE;i++){
		Prodata[i].no[0] = '\0';
		Prodata[i].state[0] = '\0';
		Prodata[i].okdate[0] = '\0';	
	    Prodata[i].okH = 0;
		Prodata[i].wrongdate[0] = '\0';
		Prodata[i].wrongH = 0;	
		Prodata[i].class0 = 0;	
		Prodata[i].class1[0] = '\0';
		Prodata[i].cont[0] = '\0';
		Prodata[i].answer[0] = '\0';	
		Prodata[i].error[0] = '\0';
		Prodata[i].delflag = FALSE;		
	}
	LastTime = 0;
	iReturnNo = 0;
	TotalAddValue = 0;
	ProblemType = 0;
	SendType = 0;
}

//************************************************
//��ʽ : ����Log��(��Local��Ŀ¼��)��ר�ú�ʽ
//�ش�ֵ : None
//��  ע : ֻ��Debug mode����Ӳ��д��log��!!
//************************************************
#ifdef _STONDEBUG_
void WriteInLog( char cData[], char cFile[])
{
	char totals[65536];//[1024];
	struct tm nowTime;
	time_t longTime;
	time( &longTime );
	localtime_s(&nowTime, &longTime );
	sprintf_s(totals,"%02d/%02d/%02d %02d:%02d:%02d ",(nowTime.tm_year % 100), nowTime.tm_mon+1, nowTime.tm_mday,
				nowTime.tm_hour, nowTime.tm_min, nowTime.tm_sec);
	lstrcat(totals,cData);
	lstrcat(totals,"\r\n\r\n\r\n");
	FILE *fp;
	fp = fopen(filename, "a" );
	if(fp)
	{
		fprintf(fp,totals);
		fclose(fp);
	}
}
#endif

//************************************************
//��ʽһ : ��������ʽ��ASP�乵ͨ��ר�ú�ʽ
//�ش�ֵ :  0 --- ������� & ����ر��ɹ�
//         1 --- ����ر�����ʧ��
//         2 --- �ֻ������������(ʱ���������)
//         3 --- �ֻ�ѶϢ��������(����)
//         4 --- ��·�˴���
//         5 --- WGS����(��ͨ��)�Ѳ���!!(С�����)
//         6 --- ������ʱ(��DNSʧ��)
//         7 --- ASP�ش�����
//************************************************
// pid:id ppw:password pdb:�ڲ����� pinput:������������
int SendProblemMsg(char pid[16], char ppw[16], char pdb[] , char pinput[])
{
	char returndata[20] ;  //��¼�ش����ִ�
	int nRet,wait=1;

	if(!QueryOnlineGmIP(SMSDomainName)) return 6;
	//if((pdb[0] =='\0') || (lstrlen(pdb) != 23)) return 2;    
	//if(lstrlen(pc.name)>16)	return 3;

#ifdef _FIX_URLENCODE
		char OutTmp[8000];
		char *pOutTmp ;
		char *pInTmp ;
		char Hex[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
		//  do  encoding
		pInTmp=pinput;
		pOutTmp=OutTmp;
		while  (*pInTmp)
		{
			if ( (*pInTmp>= '0') && (*pInTmp <= '9') 
				||	(*pInTmp>= 'a') && (*pInTmp <= 'z')
				||	(*pInTmp>= 'A') && (*pInTmp <= 'Z') 
				)
				*pOutTmp++  =  *pInTmp;
			else
			{
				if(*pInTmp==0x20&&(!IsDBCSLeadByte(*pInTmp)))
					*pOutTmp++  =  '+';
				else
				{
					*pOutTmp++  =  '%';
					*pOutTmp++  =  Hex[(*pInTmp>>4)&0x0f];
					*pOutTmp++  =  Hex[(*pInTmp)&0x0f];
				}
			}
				
				pInTmp++;
				
		}
		*pOutTmp  =  '\0';
		sprintf_s(pinput,8050,"&qcontent=%s",OutTmp);
#endif

	SOCKET	hSock;
	SOCKADDR_IN		stName;
	fd_set	        rfds,wfds;
	timeval	        tmTimeOut;
	char  *result;
	int   len, cnt, ret ;
	
	tmTimeOut.tv_usec=0;
	tmTimeOut.tv_sec=5;
	if( INVALID_SOCKET != ( hSock = socket( AF_INET, SOCK_STREAM, 0) ) )
	{
		DWORD flg = 1;
		if( SOCKET_ERROR != ioctlsocket( hSock, FIONBIO, &flg))
		{
			ZeroMemory( &stName, sizeof(struct sockaddr));
			stName.sin_family = PF_INET;
			stName.sin_port = htons(80);
			stName.sin_addr.s_addr = inet_addr(OnlineGmIP);
			ret = connect( hSock, (LPSOCKADDR)&stName, sizeof(struct sockaddr) );
			if( SOCKET_ERROR != ret || WSAEWOULDBLOCK == WSAGetLastError() )
			{
				cnt = 0;
				char  buf[3000];  
				if(ProblemType==0){   
					SendType=0;		//һ������
					sprintf_s(buf,"GET //normal_check.asp?wgsid=%s&gamepwd=%s&game=1%s%s",pid,ppw,pdb,pinput);   
				}else{
					SendType=1;		//�쳣����
					sprintf_s(buf,"GET //handle_check.asp?wgsid=%s&gamepwd=%s&game=1%s%s",pid,ppw,pdb,pinput);   
				}
				strcat_s(buf," HTTP/1.1\r\nAccept: text/*\r\nUser-Agent: StoneAge\r\n");
				sprintf_s(buf,"%sHost: %s\r\n\r\n",buf,OnlineGmIP);
#ifdef _STONDEBUG_   //д��onlinegm.log
			WriteInLog( buf , filename);
#endif
				len = lstrlen(buf);
				ichecklooptime = TimeGetTime();
				while(1)
				{
					FD_ZERO( &wfds);
					FD_SET( hSock, &wfds);
					nRet = select( NULL, (fd_set*)NULL, &wfds, (fd_set*)NULL, &tmTimeOut);
					if(nRet == SOCKET_ERROR||nRet==-1){
						closesocket(hSock);
						return 4;
					}else if(nRet == 0){
						closesocket(hSock);
						return 8;
					}
					if( FD_ISSET( hSock, &wfds) ){
						ret = send( hSock, &buf[cnt], len, 0);
						cnt += ret;
						len -= ret;
						if(len<1) break;  //ok
					}
					if( TimeGetTime() - ichecklooptime > 3000 ){
						closesocket(hSock);
						return 8;
					}
				}
				Sleep(500);
				len = (InputHistory.newNo*70)+500 ; //1024;
				cnt = 0;
				ichecklooptime = TimeGetTime();  
				while(1)
				{
					if(wait>=3){
						closesocket(hSock);
						return 8;
					}
					FD_ZERO( &rfds);
					FD_SET( hSock, &rfds);
					select( NULL, &rfds, (fd_set*)NULL, (fd_set*)NULL, &tmTimeOut);
					if(nRet == SOCKET_ERROR||nRet==-1){
						closesocket(hSock);
						return 4;
					}
					if(nRet == 0){
						wait++;
						continue;
					}
					if( FD_ISSET( hSock, &rfds) ){
				 		ret = recv( hSock, &buf[cnt], len, 0);
						if(ret<0){
							closesocket(hSock);
							return 4;
						}
					}
					buf[cnt+ret] = 0;
					result = strstr( buf, "\r\n\r\n") + 4;
					getStringToken(result ,',',1,sizeof(returndata)-1,returndata);
					if(atoi(returndata)!=1){  //����ش�������ʾ����1��ʾok
						closesocket(hSock);
						return atoi(returndata);
					}else{ 
						getStringToken(result ,':',2,sizeof(returndata)-1,returndata);
						iReturnNo = atoi(returndata);  //��������
					}
					if(result)  break;
					cnt += ret;
					len -= ret;
					if( TimeGetTime() > ichecklooptime + 3000 ){
						closesocket(hSock);
						return 8;
					}
				}
			}else{
				closesocket(hSock);
				return 6;
			}
		}	
		closesocket(hSock);
		return 1;
	}
	return 4;			
}

//************************************************
// ����Ҫɾ�����ŵ�����ʽ
// �ش�ֵ :0 --- ������� & ����ɾ���ɹ�
//		   3 --- �������ݴ���
//         4 --- ��·�˴���
//         6 --- ������ʱ(��DNSʧ��)
//************************************************
int SendDeleteMsg(char pid[16], char ppw[16] , char pno[16] )
{
	int nRet;
	if(!QueryOnlineGmIP(SMSDomainName)) return 6;

	int ret,len,cnt,icheck,wait=1;
	SOCKET	hSock;
	SOCKADDR_IN		stName;
	fd_set	        rfds,wfds;
	timeval	        tmTimeOut;
	char  *result;
	tmTimeOut.tv_usec=0;
	tmTimeOut.tv_sec=5;
	if( INVALID_SOCKET != ( hSock = socket( AF_INET, SOCK_STREAM, 0) ) )
	{
		DWORD flg = 1;
		if( SOCKET_ERROR != ioctlsocket( hSock, FIONBIO, &flg))
		{
			ZeroMemory( &stName, sizeof(struct sockaddr));
			stName.sin_family = PF_INET;
			stName.sin_port = htons(80); 
			stName.sin_addr.s_addr = inet_addr(OnlineGmIP);
			ret = connect( hSock, (LPSOCKADDR)&stName, sizeof(struct sockaddr) );
			if( SOCKET_ERROR != ret || WSAEWOULDBLOCK == WSAGetLastError() )
			{
				cnt = 0;
				char  buf[1024];
				sprintf_s(buf,"GET //DelForm.asp?wgsid=%s&gamepwd=%s&rcount=1&idno=%s",pid,ppw,pno);				
				strcat_s(buf," HTTP/1.1\r\nAccept: text/*\r\nUser-Agent: StoneAge\r\n");
				sprintf_s(buf,"%sHost: %s\r\n\r\n",buf,OnlineGmIP);
				len = lstrlen(buf);
				ichecklooptime = TimeGetTime();
				while(1)
				{
					FD_ZERO( &wfds);
					FD_SET( hSock, &wfds);
					nRet = select( NULL, (fd_set*)NULL, &wfds, (fd_set*)NULL, &tmTimeOut);
					if(nRet == SOCKET_ERROR||nRet==-1){
						closesocket(hSock);
						return 4;
					}else if(nRet == 0){
						closesocket(hSock);
						return 8;
					}
					if( FD_ISSET( hSock, &wfds) ){
						ret = send( hSock, &buf[cnt], len, 0);
						cnt += ret;
						len -= ret;
						if(len<1) break;  //ok
					}
					if( TimeGetTime() > ichecklooptime + 3000 ){
						closesocket(hSock);
						return 8;
					}
				}
				Sleep(500);
				len = 1024;
				cnt = 0;
				ichecklooptime = TimeGetTime();
				while(1)
				{
					if(wait>=3){
						closesocket(hSock);
						return 8;
					}
					FD_ZERO( &rfds);
					FD_SET( hSock, &rfds);
					nRet =  select( NULL, &rfds, (fd_set*)NULL, (fd_set*)NULL, &tmTimeOut);
					if(nRet == SOCKET_ERROR||nRet==-1){
						closesocket(hSock);
						return 4;
					}
					if(nRet == 0){
						wait++;
						continue;
					}
					if( FD_ISSET( hSock, &rfds) ){
						ret = recv( hSock, &buf[cnt], len, 0);							
						if(ret<0){
							closesocket(hSock);
							return 4;
						}
						buf[cnt+ret] = 0;
						result = strstr( buf, "\r\n\r\n") + 4;
						char *sss;
						strtok_s(result,",",&sss);
						icheck=atoi(result);
						if(icheck != 1){
							closesocket(hSock);
							return icheck;
						}
						if(result)  break;
						cnt += ret;
						len -= ret;
					}
					if( TimeGetTime() > ichecklooptime + 3000 ){
						closesocket(hSock);
						return 8;
					}
				}
			}else{
				closesocket(hSock);
				return 6;
			}
		}
		closesocket(hSock);
		return 1 ;
	}
	return 4 ;
}

//************************************************
//	��ServerҪ��ҵ����ⵥ��������
//  �ش�ֵ 0: ��ȷ����
//         2: ������κ����ⵥ
//         4: ��·�˴���
//         6: ������ʱ(��DNSʧ��)
//************************************************
int SendDirMsg(char pid[16], char ppw[16] )
{
	if(!QueryOnlineGmIP(SMSDomainName)) return 6;

	int nRet,i=1;
	int wait=1,j=1;		
	char alldata[65536],getdata[6000],perdata[3000],statedata[100];  //ȫ����,ÿ��,ÿ��,����״̬
	char returndata[20] ;
	BOOL Okflag = FALSE , Firstflag = TRUE;
#ifdef _STONDEBUG_
	char logbuf[50];
#endif
	int ret,len,cnt; 
	SOCKET	hSock;
	SOCKADDR_IN		stName;
	fd_set	        rfds,wfds;
	timeval	        tmTimeOut;
	char  *result;

	tmTimeOut.tv_usec=0;
	tmTimeOut.tv_sec=5;
	memset(alldata,0,sizeof(alldata));
	if( INVALID_SOCKET != ( hSock = socket( AF_INET, SOCK_STREAM, 0) ) )
	{
		DWORD flg = 1;
		if( SOCKET_ERROR != ioctlsocket( hSock, FIONBIO, &flg))
		{
			ZeroMemory( &stName, sizeof(struct sockaddr));
			stName.sin_family = PF_INET;
			stName.sin_port = htons(80); 
			stName.sin_addr.s_addr = inet_addr(OnlineGmIP);
			ret = connect( hSock, (LPSOCKADDR)&stName, sizeof(struct sockaddr) );
			if( SOCKET_ERROR != ret || WSAEWOULDBLOCK == WSAGetLastError() )
			{
				cnt = 0;
				char  buf[65536];
				sprintf_s(buf,"GET //userFormList.asp?wgsid=%s&gamepwd=%s",pid,ppw);				
				strcat_s(buf," HTTP/1.1\r\nAccept: text/*\r\nUser-Agent: StoneAge\r\n");
				sprintf_s(buf,"%sHost: %s\r\n\r\n",buf,OnlineGmIP);
				len = lstrlen(buf);
				ichecklooptime = TimeGetTime();
				while(1)
				{
					FD_ZERO( &wfds);
					FD_SET( hSock, &wfds);
					nRet = select( NULL, (fd_set*)NULL, &wfds, (fd_set*)NULL, &tmTimeOut);
					if(nRet == SOCKET_ERROR||nRet==-1){
						closesocket(hSock);
						return -400;
					}else if(nRet == 0){
						closesocket(hSock);
						return -800;
					}
					if( FD_ISSET( hSock, &wfds) ){
						ret = send( hSock, &buf[cnt], len, 0);
						cnt += ret;
						len -= ret;
						if(len<1) break;  //ok
					}
					if( TimeGetTime() > ichecklooptime + 3000 ){
						closesocket(hSock);
						return -800;
					}
				}				
				Sleep(500);
				len = 65536;//8000;
				cnt = 0;
				ichecklooptime = TimeGetTime();
				while(1)
				{
					if(wait>=3){
						closesocket(hSock);
						return -800;
					}
					FD_ZERO( &rfds);
					FD_SET( hSock, &rfds);
					nRet = select( NULL, &rfds, (fd_set*)NULL, (fd_set*)NULL, &tmTimeOut);
					if(nRet == SOCKET_ERROR||nRet==-1){
						closesocket(hSock);
						return -400;
					}
					if(nRet == 0){
						wait++;
						continue;
					}
					if( FD_ISSET( hSock, &rfds) ){
						ret = recv( hSock, &buf[cnt], len, 0);							
						if(ret<0){
							closesocket(hSock);
							return -400;
						}								
						buf[cnt+ret] = 0;   
						result = strstr( buf, "\r\n\r\n") + 4;
						if(strcmp(result,"0")==0){
							closesocket(hSock);
							return -200;
						}
						strcpy(alldata,result);
						cnt += ret;
						len -= ret;
					}
					if(strstr(alldata,"&#")){ //ok
						break;
					}
					if( TimeGetTime() > ichecklooptime + 3000 ){
						closesocket(hSock);
						return -800;
					}
				}
				getStringToken(result ,',',1,sizeof(returndata)-1,returndata);
				if(atoi(returndata)<0){  //����ش�������ʾ���󣬴���0���Ӵ�����������ͬʱҲ��ʾok
					closesocket(hSock);
					return atoi(returndata);
				}else{
					TotalAddValue = atoi(returndata);
				}
				result = alldata;
				result = strstr( result , ",") + 1;
				strcpy(alldata,result);	
			}else{
#ifdef _STONDEBUG_
				sprintf_s(logbuf,"Get last error:%d",WSAGetLastError());
				WriteInLog( logbuf , filename);
#endif
				return -600;
			}
		}
		closesocket(hSock);
		ProNoValue = 0;
		ProNoSelectFlag = FALSE;
#ifdef _STONDEBUG_   //д��onlinegm.log
			WriteInLog( alldata , filename);
#endif
		perdata[0] = '\0';
		getdata[0] = '\0';
		//sprintf_s(alldata,"21|����|*|*|*|*|18|���˿�ʯ|�װ���ά������������лл����������Ŭ��~��л����֧���밮����Ҳ�ٴε�Ԥף���޸���죡˳�����⣡|�װ���ά������������лл����������Ŭ��~��л����֧���밮����Ҳ�ٴε�Ԥף���޸���죡˳�����⣡|&#");
		while(getStringToken( alldata,'&',i,sizeof(getdata)-1,getdata)!=1){
			while(getStringToken(getdata,'|',j,sizeof(perdata)-1,perdata)!=1){
				if( strcmp( perdata , "*")){
					switch(j){
					case 1:sprintf_s(Prodata[ProNoValue].no,"%s",perdata); break;
					case 2:
						getStringToken(perdata,'>',2,sizeof(statedata)-1,statedata);
						getStringToken(statedata,'<',1,sizeof(statedata)-1,statedata);
						if(lstrlen(statedata) == NULL)
							sprintf_s(Prodata[ProNoValue].state,"%s",perdata);
						else
							sprintf_s(Prodata[ProNoValue].state,"%s",statedata);
						break;
					case 3:sprintf_s(Prodata[ProNoValue].okdate,"%s",perdata);break;
					case 4:Prodata[ProNoValue].okH=atoi(perdata); break;
					case 5:sprintf_s(Prodata[ProNoValue].wrongdate,"%s",perdata);break;
					case 6:Prodata[ProNoValue].wrongH=atoi(perdata); break;
					case 7:Prodata[ProNoValue].class0=atoi(perdata);break;
					case 8:sprintf_s(Prodata[ProNoValue].class1,"%s",perdata);break;
					case 9:sprintf_s(Prodata[ProNoValue].cont,"%s",perdata);break;
					case 10:sprintf_s(Prodata[ProNoValue].answer,"%s",perdata);break;
					default: sprintf_s(Prodata[ProNoValue].error,"%s",perdata);break;
					}
				}
				perdata[0] = '\0';
				j++;		
			}
			getdata[0] = '\0';
			ProNoValue++;
			j=1; 
			i++;
		}
		//TotalAddValue = ProNoValue; 
		return 1 ; // ok
	}
	return 4 ;
}
//************************************************
//	��ѯ���ⵥ������
//************************************************
void vReadContent( int pno )
{
	static char *pRecv ;
	char date[10];
	char data[40];
	char classbuf1[40],classbuf2[40];
	int i=1;
		
	ClassIndex=Prodata[pno].class0 - 18;

	if(ClassIndex == 0 ){   //�쳣����
		while(getStringToken(Prodata[pno].okdate,'/',i,sizeof(date)-1,date)!=1){ 
			if( i==1 )	okY = atoi(date);
			else if( i==2)	okM = atoi(date);
			i ++;
		}
		okD = atoi(date);
		okH = Prodata[pno].okH;
		i = 1;
		date[0] = '\0';
		while(getStringToken(Prodata[pno].wrongdate,'/',i,sizeof(date)-1,date)!=1){ 
			if( i==1 )	wrongY = atoi(date);
			else if( i==2)	wrongM = atoi(date);
			i ++;
		}
		wrongD = atoi(date);
		wrongH = Prodata[pno].wrongH;
	}

	if(getStringToken(Prodata[pno].class1,',',1,sizeof(data)-1,data)!=1){ 
		sprintf_s(classbuf1,"%s",data);
		data[0] = '\0';
		if(getStringToken(Prodata[pno].class1,',',2,sizeof(data)-1,data)==1) 
			sprintf_s(classbuf2,"%s",data);
	}else{
		sprintf_s(classbuf1,"%s",data);
	}

	if(ClassIndex){ // һ������
		for(i=0;i<DEF_C1_TOTAL;i++){
			if(strcmp(ProblemC1[i],classbuf1)==NULL)
			break;
		}
		ClassIndex1 = i;
	}else{			// �쳣����
		for(i=0;i<DEF_C2_TOTAL;i++){
			if(strcmp(ProblemC2[i],classbuf1)==NULL)
			break;
		}
		ClassIndex1 = i;
		switch(ClassIndex1){
		case 0: for(i=0;i<3;i++){
					if(strcmp(ProblemC2_1[i],classbuf2)==NULL)
					break;
				}break;
		case 1: for(i=0;i<3;i++){
					if(strcmp(ProblemC2_2[i],classbuf2)==NULL)
					break;
				}break;
		case 2: for(i=0;i<5;i++){
					if(strcmp(ProblemC2_3[i],classbuf2)==NULL) 
					break;
				}break;
		case 3: for(i=0;i<2;i++){
					if(strcmp(ProblemC2_4[i],classbuf2)==NULL) 
					break;
				}break;
		case 4: for(i=0;i<2;i++){ 
					if(strcmp(ProblemC2_5[i],classbuf2)==NULL) 
					break;
				}break;
		case 5: for(i=0;i<3;i++){
					if(strcmp(ProblemC2_6[i],classbuf2)==NULL)
					break;
				}break;
		case 10:for(i=0;i<3;i++){
					if(strcmp(ProblemC2_7[i],classbuf2)==NULL)
					break;
				}break;
			default: i=0;
		}
		ClassIndex2=i;
	}
		
	if (lstrlen(Prodata[pno].cont)!=NULL){
		sprintf_s(SegmentBuf[SegmentTotal],"%s",Prodata[pno].cont);
		SegmentTotal++;
		if(lstrlen(Prodata[pno].answer)!=NULL){
			sprintf_s(SegmentBuf[SegmentTotal],"%s",Prodata[pno].answer);
			SegmentTotal++;
		}
	}
}

//************************************************
//��ʽ	: ����������λ�ĳ�ʼ����ʽ
//�ش�ֵ	: None
//************************************************
void InitOnlineGmInput(int x, int y)
{
	int i;

	HistorySelect = 5000;

	SubBuffer.buffer[0]='\0';
	SubBuffer.x = x + 20;  
	SubBuffer.y = y + 400; 
	SubBuffer.len = 70;				//����
	SubBuffer.color = FONT_PAL_AQUA;
	SubBuffer.fontPrio = FONT_PRIO_FRONT;
	SubBuffer.lineLen=70;			//ÿ�м�����
	SubBuffer.lineDist=25;		//�����м������pixel

	InputHistory.newNo = 0;
	InputHistory.nowNo = 0;
	InputHistory.addNo = 0;
	InputHistory.lockNo = 0;
	for ( i=0;i<115;i++ )  
	{
		InputHistory.str[i][0]='\0';
		InputHistory.color[i]=FALSE; 
	}

	int len = lstrlen(SubBuffer.buffer);
	if(len){
		SubBuffer.cursor = len;
		SubBuffer.cnt= len;
	}else{
		SubBuffer.cnt=0;
		SubBuffer.cursor=0;
	}
	TitleFlag = TRUE;
}

//************************************************
//��ʽ   : �������ⵥ�ŵ�����ʽ
//�ش�ֵ : None
//************************************************
void ShowProblemNo( int x, int y, int Key )
{
	int i,k,word = 0;
	int Keyid;
	char buf[100]= "/0";
	static int fontId[5];
	static char *pChar ;
	
	if (Key==1){  //�ϼ�ͷ
		ProNoIndex -- ;
		if (ProNoIndex < 0 ) 
			ProNoIndex = 0 ;
	}
	else if(Key==2){	//�¼�ͷ
		ProNoIndex ++ ;
		if (ProNoIndex == ProNoValue)
		ProNoIndex = ProNoValue-1;
	}

	for ( i=0;i<5;i++ ){ // �ܹ����� 
		if (ProNoIndex+i>=ProNoValue)
			break ;
		if (ProNoIndex+i==ProNoSelect && ProNoSelectFlag == TRUE){
			sprintf_s(buf,"%s                 %s",Prodata[ProNoIndex+i].no,Prodata[ProNoIndex+i].state);  
			fontId[i] = StockFontBuffer( x + 20 , y+7+(i*20) , FONT_PRIO_FRONT, 1 , buf , 2 );
		}else{
			sprintf_s(buf,"%s                 %s",Prodata[ProNoIndex+i].no,Prodata[ProNoIndex+i].state);  
			fontId[i] = StockFontBuffer( x + 20 , y+7+(i*20) , FONT_PRIO_FRONT, 0 , buf, 2 );
		}
		if(Prodata[ProNoIndex+i].delflag == TRUE){
			sprintf_s(buf,"��ɾ��");
			StockFontBuffer( x + 70 , y+7+(i*20) , FONT_PRIO_FRONT, 4 , buf, 2 );
		}
	}

	Keyid = selFontId( fontId, sizeof( fontId )/sizeof( int ) );
	if ( 0 <= Keyid && Keyid < 5 ){
		if (ProNoIndex + Keyid < ProNoValue){   
			//��ѯĳ�ȵ��ŵ�����
			ProNoSelectFlag = TRUE;
			ProNoSelect = ProNoIndex + Keyid;
			if ( ProNoSelect != HistorySelect ){
				HistorySelect = ProNoSelect;
				InitOnlineGmInput(x, y);
				SegmentIndex = 0;
				SegmentTotal = 0;
				SegmentBuf[0][0] = '\0';
				SegmentBuf[1][0] = '\0';
				vReadContent( ProNoSelect );
			}
		}
	}
	
	if( SegmentTotal > SegmentIndex  ){  //   �������
		InputHistory.addNo =0;  // ������������Բ��ü�
		GetKeyInputFocus(&SubBuffer);
		if( SegmentIndex %2 == 0 ){
			if(TitleFlag==TRUE){ 
				StrToNowStrBuffer1("ǰ���������ݣ�");
				for ( k=0;k<60+10;k++ )   
					StrToNowStrBuffer(" ");
				InputHistory.color[InputHistory.newNo]=TRUE;
				pContent = SegmentBuf[SegmentIndex];
				TitleFlag = FALSE;	
			}else{
				if(pContent!=NULL){
					word = StrToNowStrBuffer2(pContent);
					pContent+=word ;
					if(word<70){
						for ( k=0;k<(80-word);k++ )   
							StrToNowStrBuffer(" ");
					}
					if(*pContent == NULL){
						pContent = NULL;
						SegmentIndex++;			
						TitleFlag = TRUE;
					}				
					/*
					if (i>70){
						StrToNowStrBuffer(pContent);
						pContent+=70 ;
					}else{
						StrToNowStrBuffer(pContent);
						pContent+=i ;
						for ( k=0;k<(70-i);k++ )   //cyg ���ո�
							StrToNowStrBuffer(" ");
					}
					if(*pContent == NULL){
						pContent = NULL;
						SegmentIndex++;			
						TitleFlag = TRUE;
					}
					*/
				}
			}
		}else{
			if(TitleFlag==TRUE){ 
				StrToNowStrBuffer1("�ͷ����");
				for ( k=0;k<60+10;k++ )   //cyg ���ո�
					StrToNowStrBuffer(" ");
				InputHistory.color[InputHistory.newNo]=TRUE;
				pContent = SegmentBuf[SegmentIndex];
				TitleFlag = FALSE;
			}else{
				if(pContent!=NULL){
					word = StrToNowStrBuffer2(pContent);
					pContent+=word ;
					if(word<70){
						for ( k=0;k<(80-word);k++ ){   
							StrToNowStrBuffer(" ");
						}
					}
					if(*pContent == NULL){
						pContent = NULL;
						SegmentIndex++;			
						TitleFlag = TRUE;
					}
				}
			}
		}
	}else{ 
		if( TitleFlag == TRUE ){
			GetKeyInputFocus(&SubBuffer);
			StrToNowStrBuffer1("�����������ݣ�");
			for ( k=0;k<56+10;k++ )   
				StrToNowStrBuffer(" ");
			InputHistory.color[InputHistory.newNo]=TRUE;
			TitleFlag = FALSE;
			InputHistory.addNo = 0;
			InputHistory.lockNo = InputHistory.newNo;
			
		}
	}
}

//************************************************
//��ʽ   : ��������������λ������ʽ
//�ش�ֵ : None
//************************************************
void InputOnlineGmData( int x, int y, int Key )
{
	int Changelineflag = 0;
	int i;

	if ( InputHistory.newNo - InputHistory.nowNo <= 4)
		GetKeyInputFocus(&SubBuffer);
	else
		pNowStrBuffer = NULL ;
	
	if (Key == 1)  //�ϼ�ͷ
	{
		if (InputHistory.newNo >4 && InputHistory.nowNo ){
			InputHistory.nowNo -- ; 
			if (InputHistory.newNo - (InputHistory.nowNo+4) == 1 ){
				strcpy( InputHistory.str[ InputHistory.newNo ],SubBuffer.buffer);
				SubBuffer.buffer[0] = NULL ;
			}
		}
	}
	if (Key == 2) // �¼�ͷ
	{
		if (InputHistory.newNo >4){
			if (InputHistory.nowNo+4<InputHistory.newNo){
				InputHistory.nowNo ++ ; 
				if (InputHistory.nowNo+4==InputHistory.newNo){
				GetKeyInputFocus(&SubBuffer);
				strcpy( SubBuffer.buffer,InputHistory.str[ InputHistory.newNo ] );
				}
			}
		}
	}

	Changelineflag = StockFontBuffer3( &SubBuffer );
	if (Changelineflag){ // ���� 
		if(InputHistory.addNo < 30 ){  //0~29
			SubBuffer.cnt=0;
			SubBuffer.cursor=0;
			if (SubBuffer.y< y + 410)
				SubBuffer.y += SubBuffer.lineDist ; 
			strcpy( InputHistory.str[ InputHistory.newNo ],SubBuffer.buffer);
			SubBuffer.buffer[0]='\0';				
			InputHistory.newNo++;
			InputHistory.addNo++;
			if (InputHistory.newNo >= 5)
				InputHistory.nowNo = InputHistory.newNo -4; 
		}else{
			//SubBuffer.cursor
		}
	}
	
	for ( i=0;i<5;i++ ) // �ܹ����� 
	{
		if ((InputHistory.nowNo+i)!=InputHistory.newNo){
			if(InputHistory.color[InputHistory.nowNo+i]==FALSE)
				StockFontBuffer( SubBuffer.x , y+300+(i*(30-5)) , FONT_PRIO_FRONT, 0 ,InputHistory.str[ InputHistory.nowNo+i ], 0 );
			else
				StockFontBuffer(  SubBuffer.x , y+300+(i*(30-5)) , FONT_PRIO_FRONT, 5 ,InputHistory.str[ InputHistory.nowNo+i ], 0 );
		}
	}
}

HANDLE GMHandle;
extern char szUser[],szPassword[];
//************************************************
//��ʽ   : �����ѯ���ŵ�����ʽ
//�ش�ֵ : OL
//************************************************
DWORD WINAPI DirThread(LPVOID param)
{
	ResultCode = -1;
	char id[32], password[32];
	CopyMemory(id,szUser,32);
	ecb_crypt("f;encor1c",id,32,DES_DECRYPT);
	CopyMemory(password,szPassword,32);
	ecb_crypt("f;encor1c",password,32,DES_DECRYPT);

	ResultCode = SendDirMsg( id,password );

	switch(ResultCode)
	{
		case -200: 
			StockChatBufferLine("���κ����ⵥ��¼!!",FONT_PAL_RED);
			StockChatBufferLine("���������ⵥ!",FONT_PAL_RED);
			ProNoValue = 0;
			break;
		case -400:
			StockChatBufferLine("��·��������!!",FONT_PAL_RED);
			StockChatBufferLine("�޷���ѯ���ⵥ!",FONT_PAL_RED);
			break;
		case -600:
			StockChatBufferLine("���ϻر��������޷�����!!",FONT_PAL_RED);
			StockChatBufferLine("�����Ժ�����...",FONT_PAL_WHITE);
			break;
		case -800:
			StockChatBufferLine("��·������ʱ!!",FONT_PAL_RED);
			StockChatBufferLine("�����Ժ�����...",FONT_PAL_WHITE);
			break;
		case 1:    // ��ѯ�ɹ�
			break;
		case -999:
			StockChatBufferLine("��·æ����!!",FONT_PAL_RED);
			StockChatBufferLine("�����Ժ�����...",FONT_PAL_RED);
			break;
		default:
			StockChatBufferLine("��Ǹ��ʽ�ڲ�����!!!",FONT_PAL_RED);
			StockChatBufferLine("���ⵥ��ѯʧ��!",FONT_PAL_RED);
			break;
	}
#ifdef _STONDEBUG_   //д��onlinegm.log
	if( ResultCode != 1 ){
		sprintf_s(inlogstr,"��ѯʧ�ܴ�����%d",ResultCode);
		WriteInLog(inlogstr,filename);
	}
#endif
	CloseHandle(GMHandle);
	ExitThread(0);	
	return 0L;
}

//************************************************
//��ʽ   : ����ɾ�����ŵ�����ʽ
//�ش�ֵ : OL
//************************************************
DWORD WINAPI DeleteThread(LPVOID param)
{
	ResultCode = -1;
	char id[32], password[32] ;
	CopyMemory(id,szUser,32);
	ecb_crypt("f;encor1c",id,32,DES_DECRYPT);
	CopyMemory(password,szPassword,32);
	ecb_crypt("f;encor1c",password,32,DES_DECRYPT);
#ifdef _STONDEBUG_
	inlogstr[0] = 0;
#endif

	ResultCode = SendDeleteMsg(id,password,Prodata[ProNoSelect].no);

	switch(ResultCode)
	{
		case 4:
			StockChatBufferLine("��·��������!!",FONT_PAL_RED);
			StockChatBufferLine("�޷�ɾ�����򵥺�!",FONT_PAL_RED);
			break;
		case 6:
			StockChatBufferLine("���ϻر��������޷�����!!",FONT_PAL_RED);
			StockChatBufferLine("�����Ժ�����...",FONT_PAL_WHITE);
			break;
		case 8:
			StockChatBufferLine("��·������ʱ!!",FONT_PAL_RED);
			StockChatBufferLine("�����Ժ�����...",FONT_PAL_WHITE);
			break;
		case 1: 
			StockChatBufferLine("���ⵥ����ɾ����!",FONT_PAL_YELLOW);
			Prodata[ProNoSelect].delflag = TRUE ;
			TotalAddValue --;
			break;
		case -999:
			StockChatBufferLine("��·æ����!!",FONT_PAL_RED);
			StockChatBufferLine("�����Ժ�����...",FONT_PAL_RED);
			break;
		default:
			StockChatBufferLine("��Ǹ��ʽ�ڲ�����!!!",FONT_PAL_RED);
			StockChatBufferLine("���򵥺�ɾ��ʧ��!",FONT_PAL_RED);
			break;
	}
#ifdef _STONDEBUG_   //д��onlinegm.log
	if(	ResultCode != 1){	
		sprintf_s(inlogstr,"ɾ��ʧ�ܴ�����%d",ResultCode);
		WriteInLog(inlogstr,filename);
	}
#endif

	CloseHandle(GMHandle);
	ExitThread(0);	
	return 0L;
}

//************************************************
//��ʽ   : ����Multithread������ʽ
//�ش�ֵ : OL
//************************************************
DWORD WINAPI OnlineGmThread(LPVOID param)
{
	ResultCode = -1;
	char id[32], password[32] ,buf[50];
	CopyMemory(id,szUser,32);
	ecb_crypt("f;encor1c",id,32,DES_DECRYPT);
	CopyMemory(password,szPassword,32);
	ecb_crypt("f;encor1c",password,32,DES_DECRYPT);
#ifdef _STONDEBUG_
	inlogstr[0] = 0;
#endif
	
	ResultCode = SendProblemMsg(id,password,DataBuffer,InputBuffer);

	switch(ResultCode)
	{
		case 4:
			StockChatBufferLine("��·��������!!",FONT_PAL_RED);
			StockChatBufferLine("�޷����ͱ�������!",FONT_PAL_RED);
			break;
		case 6:
			StockChatBufferLine("���ϻر��������޷�����!!",FONT_PAL_RED);
			StockChatBufferLine("�����Ժ�����...",FONT_PAL_WHITE);
			break;
		case 8:
			StockChatBufferLine("��·������ʱ!!",FONT_PAL_RED);
			StockChatBufferLine("�����Ժ�����...",FONT_PAL_WHITE);
			break;
		case -9:
			if(SendType==0){
				StockChatBufferLine("ÿ�η���һ�����ⵥ",FONT_PAL_RED);
				StockChatBufferLine("������ʮ����лл...",FONT_PAL_RED);
			}else{
				StockChatBufferLine("ÿ�η����쳣���ⵥ",FONT_PAL_RED);
				StockChatBufferLine("����һСʱлл...",FONT_PAL_RED);
			}
			break;
		case -999:
			StockChatBufferLine("��·æ����!!",FONT_PAL_RED);
			StockChatBufferLine("�����Ժ�����...",FONT_PAL_RED);
			break;
		case 1:
			sprintf_s(buf,"���ⵥ��%d���ͳ�!",iReturnNo);
			StockChatBufferLine( buf ,FONT_PAL_YELLOW);
			TotalAddValue ++;
			ResetFlag = TRUE ; // ֻ�гɹ���reset
			DirFlag = TRUE ;
			break;
		default:
			StockChatBufferLine("��Ǹ��ʽ�ڲ�����!!!",FONT_PAL_RED);
			StockChatBufferLine("���򵥺Ŵ���ʧ��!",FONT_PAL_RED);
			break;
	}
#ifdef _STONDEBUG_   //д��onlinegm.log
	if( ResultCode != 1 ){
		sprintf_s(inlogstr,"���ⵥ����:%d ����ʧ�ܴ�����:%d",SendType,ResultCode);
		WriteInLog(inlogstr,filename);
	}
#endif
	CloseHandle(GMHandle);
	ExitThread(0);	
	return 0L;
}

extern int nServerGroup;
extern short selectServerIndex;
extern short onlinegmProcNo;
extern int sCharSide ;
//**************************************************
//����ʽ:
//�ش�ֵ:0 ��ʾ�Ӵ������� 1 ��ʾ���
//**************************************************
int iOnlineGmProc()
{
	int i , id ; 
	static DWORD dwPressTime;
	static int btnId[50] , btnState[50] , HelpId[10] , HelpidState[10] ;
	static int SureId[2];
	char buf[100]= "/0" ; // test
	static ACTION *pActOnlineGmWnd = NULL;
	static ACTION *pActSureWnd = NULL;
	static struct tm nowTime;
	time_t longTime;
	DWORD  PushdirTime;
	static LPPAGE page;
	static LPDESC desc;
	static int desc_index,page_index;
	int x, y;
	if (onlinegmProcNo == 0)
	{
		// ��һ���Ӵ�	
		if (pActOnlineGmWnd == NULL )
		{
			x = (lpDraw->xSize - 600) / 2;
			y = (lpDraw->ySize - 450) / 2;

			pActOnlineGmWnd = MakeWindowDisp(x,y,600,450,NULL,-1, FALSE);

			x = pActOnlineGmWnd->x;
			y = pActOnlineGmWnd->y;

			if(ResetFlag==TRUE){
				InitOnlineGmInput(x, y);
				InitOnlineGm(); 
				dwPressTime = 0;
				for ( i = 0 ; i < sizeof(btnId)/sizeof(int) ; i++ )
				{	
					btnId[i] = 0;
					btnState[i] = 0;
				}
				for ( i = 0 ; i < sizeof(HelpId)/sizeof(int) ; i++ )
				{
					HelpId[i] = 0;
					HelpidState[i] = 0;
				}
				time( &longTime );
				localtime_s(&nowTime, &longTime );
				wrongY = okY = nowTime.tm_year+1900 ;
				/*//fix
				wrongM = okM = nowTime.tm_mon+1 ;
				wrongD = okD = nowTime.tm_mday ;
				wrongH = okH = nowTime.tm_hour ;
				*/
				//����reset
				ProNoIndex = 0;
				desc_index = 0;
				page_index = 0; 
				PushKey = 3;  // �Զ���ѯ
			}

		}
		else	
		{
			x = pActOnlineGmWnd->x;
			y = pActOnlineGmWnd->y;

			if (DeleteBtnFlag==FALSE)
			{
				id = selGraId( btnId, sizeof( btnId )/sizeof( int ) );
				if(dwPressTime)
				{
					if( TimeGetTime()>(dwPressTime+100))
					{
						for( i = 0 ; i < DEF_BUTTON_TOTAL ; i ++ )
						{
							if(btnState[i])
							{
								btnState[i] = 0;
								switch (i)
								{
								case 0://��ѯ
									PushdirTime = TimeGetTime();
									if ( DirFlag==TRUE || (PushdirTime-LastTime)>5000 ){   //(�ر�)�в�ѯ���Ͳ����ڲ�
										LastTime = TimeGetTime();
										PushKey = 3;
										DirFlag = FALSE;
									}
									break;
								case 1://ɾ��
									if (ProNoSelectFlag){	//Ҫ��ѡ��ĳ���Ų���ɾ��
										DeleteBtnFlag = TRUE ;										
									}
									break;						
								case 2://����
									DeathAction( pActOnlineGmWnd );
									pActOnlineGmWnd = NULL;
									onlinegmProcNo = 2;
									return 0;								
								case 3://���
									InitOnlineGmInput(x, y);	break;
								case 4://ע������
									DeathAction( pActOnlineGmWnd );
									pActOnlineGmWnd = NULL;
									onlinegmProcNo = 1;
									return 0;
								case 5://�ر�
									ResetFlag = TRUE;
									DeathAction( pActOnlineGmWnd);
									pActOnlineGmWnd = NULL;
									return 1 ;
								case 6://ѶϢ���Ͼ�
									if(ProNoValue){
										PushKey = 1;
									}
									break;
								case 7://ѶϢ���¾�
									if(ProNoValue){
										PushKey = 2;
									}
									break;
								case 8:PutKey = 1;  break;//������Ͼ�
								case 9:PutKey = 2;  break;//������¾�
								case 10://���������Ͼ�
									okM--;
									if (okM<=0){  //fix
										okY--;
										okM=12;
									}
									break;
								case 11://���������¾�
									okM++;
									if (okM>12){
										okY++;
										okM=1;
									}
									break;
								case 12://�������Ͼ�
									okD--;
									if (okD<=0) okD = 31 ;   //fix
									break;
								case 13://�������¾�
									okD++;
									if (okD>31) okD = 1;
									break;
								case 14://����ʱ�Ͼ�
									okH--;
									if (okH<0)	okH = 23;
									break;
								case 15://����ʱ�¾�
									okH++;
									if (okH>23) okH=0;
									break;
								case 16://���������Ͼ�
									wrongM--;
									if (wrongM<=0){ //fix
										wrongY--;
										wrongM=12;
									}
									break;
								case 17://���������¾�
									wrongM++;
									if (wrongM>12){
										wrongY++;
										wrongM=1;
									}
									break;
								case 18://�������Ͼ�
									wrongD--;
									if (wrongD<=0) wrongD = 31;  //fix
									break;								
								case 19://�������¾�
									wrongD++;
									if (wrongD > 31) wrongD = 1;
									break;
								case 20://����ʱ�Ͼ�
									wrongH--;
									if (wrongH<0) wrongH = 23;
									break;
								case 21://����ʱ�¾�
									wrongH++;
									if (wrongH>23) wrongH = 0;
									break;
								case 22://���һ�Ͼ�
									ClassIndex -- ;
									ClassIndex1 = 0 ;
									ClassIndex2 = 0 ;
									if (ClassIndex<0) ClassIndex = DEF_CLASS_TOTAL-1;
									break;
								case 23://���һ�¾�
									ClassIndex ++ ;
									ClassIndex1 = 0 ;
									ClassIndex2 = 0 ;
									if (ClassIndex==DEF_CLASS_TOTAL) ClassIndex = 0;
									break;							
								case 24://�����Ͼ�
									ClassIndex1 -- ;
									ClassIndex2 = 0 ;
									if (ClassIndex==1){   // һ������
										if (ClassIndex1<0) ClassIndex1 = DEF_C1_TOTAL-1;
									}else{
										if (ClassIndex1<0) ClassIndex1 = DEF_C2_TOTAL-1;
									}
									break;
								case 25://�����¾�
									ClassIndex1 ++ ;
									ClassIndex2 = 0 ;
									if (ClassIndex==1){		// һ������
										if (ClassIndex1==DEF_C1_TOTAL) ClassIndex1=0;
									}else{
										if (ClassIndex1==DEF_C2_TOTAL) ClassIndex1=0;
									}
									break;
								case 26://������Ͼ�
									ClassIndex2 -- ;
									switch (ClassIndex1)
									{
									case 0:if (ClassIndex2<0) ClassIndex2=2;break;
									case 1:if (ClassIndex2<0) ClassIndex2=2;break;
									case 2:if (ClassIndex2<0) ClassIndex2=4;break;
									case 3:if (ClassIndex2<0) ClassIndex2=1;break;
									case 4:if (ClassIndex2<0) ClassIndex2=1;break;
									case 5:if (ClassIndex2<0) ClassIndex2=2;break;
									case 10:if (ClassIndex2<0) ClassIndex2=2;break;
									default: ClassIndex2=0;break;
									}
									break;
								case 27://������¾�
									ClassIndex2 ++ ;
									switch (ClassIndex1)
									{
									case 0:if (ClassIndex2>2) ClassIndex2=0;break;
									case 1:if (ClassIndex2>2) ClassIndex2=0;break;
									case 2:if (ClassIndex2>4) ClassIndex2=0;break;
									case 3:if (ClassIndex2>1) ClassIndex2=0;break;
									case 4:if (ClassIndex2>1) ClassIndex2=0;break;
									case 5:if (ClassIndex2>2) ClassIndex2=0;break;
									case 10:if (ClassIndex2>2) ClassIndex2=0;break;
									default: ClassIndex2=0;break;
									}
									break;
								}
							}
						}
						dwPressTime = 0;
					}
				}
				else
				{
					if ( 0 <= id && id < DEF_BUTTON_TOTAL )
					{
						btnState[id] = 1;
						dwPressTime = TimeGetTime(); 
					}
				}
			}else{ 
				if (pActSureWnd == NULL){
					pActSureWnd = MakeWindowDisp( 200+100+20 , 100-63 , 4-1 , 6-4 , NULL , -1);				
				}
				else if(pActSureWnd->hp > 0)
				{
					StockDispBuffer(416+15+15,100,DISP_PRIO_MENU,ONLINEGM_YES_OR_NO,1);
					MakeHitBox( 338+15+15,100,405+15+15,124, DISP_PRIO_BOX2 );
					MakeHitBox( 426+15+15,100,494+15+15,124, DISP_PRIO_BOX2 );
					selGraId( SureId, sizeof( SureId )/sizeof( int ) );
					SureId[0] = StockDispBuffer(  372+15+15 , 112 , DISP_PRIO_IME3, ONLINEGM_SURE_U , 1);
					SureId[1] = StockDispBuffer(  460+15+15 , 112 , DISP_PRIO_IME3, ONLINEGM_CHANCEL , 1);
					if(Prodata[ProNoSelect].delflag == TRUE){
						sprintf_s(buf,"�˱ʵ�����ɾ��");
						StockFontBuffer( 365+15+15 , 81 , FONT_PRIO_FRONT, 2 , buf , 0 );
					}else{
						sprintf_s(buf,"ɾ������ %s ��?",Prodata[ProNoSelect].no);
						StockFontBuffer( 355+15+15 , 81 , FONT_PRIO_FRONT, 5 , buf , 0 );
					}

					if((mouse.onceState & MOUSE_LEFT_CRICK) && HitDispNo == SureId[0]){ //ȷ��
						if(Prodata[ProNoSelect].delflag == FALSE){
							DWORD dwThreadID,dwThrdParam = 1;
							GMHandle = CreateThread(NULL, 0, DeleteThread,&dwThrdParam,0,&dwThreadID);
							if(GMHandle == NULL)
							{
								StockChatBufferLine("������ҵϵͳ��Դ�Ѳ���!!",FONT_PAL_RED);
								StockChatBufferLine("���򵥺�ɾ��ʧ��!",FONT_PAL_RED);
								ResetFlag = TRUE;
								DeathAction( pActOnlineGmWnd);
								pActOnlineGmWnd = NULL;
								return 1;
							}				
						}
						DeathAction( pActSureWnd);
						pActSureWnd = NULL;			
						DeleteBtnFlag = FALSE ;
					}
					if((mouse.onceState & MOUSE_LEFT_CRICK) && HitDispNo == SureId[1]){ //ȡ��
						DeathAction( pActSureWnd);
						pActSureWnd = NULL;			
						DeleteBtnFlag = FALSE ;
					}
				}
			}
			if (pActOnlineGmWnd->hp > 0)
			{
				x = pActOnlineGmWnd->x;
				y = pActOnlineGmWnd->y;
				if(PushKey != 3){
					ShowProblemNo(x, y, PushKey);
				}else{ //�����ѯ����
					for( i=0;i<DEF_MAX_ADD_VALUE;i++){
						Prodata[i].no[0] = '\0';
						Prodata[i].state[0] = '\0';
						Prodata[i].okdate[0] = '\0';	
						Prodata[i].okH = 0;
						Prodata[i].wrongdate[0] = '\0';
						Prodata[i].wrongH = 0;	
						Prodata[i].class0 = 0;	
						Prodata[i].class1[0] = '\0';
						Prodata[i].cont[0] = '\0';
						Prodata[i].answer[0] = '\0';	
						Prodata[i].error[0] = '\0';
						Prodata[i].delflag = FALSE;		
					}
					DWORD dwThreadID,dwThrdParam = 1;
					GMHandle = CreateThread(NULL, 0, DirThread,&dwThrdParam,0,&dwThreadID);
					if(GMHandle == NULL)
					{
						StockChatBufferLine("������ҵϵͳ��Դ�Ѳ���!!",FONT_PAL_RED);
						StockChatBufferLine("���ⵥ�Ų�ѯʧ��!",FONT_PAL_RED);
						ResetFlag = TRUE;
						DeathAction( pActOnlineGmWnd);
						pActOnlineGmWnd = NULL;
						return 1;
					}
					
				}
				PushKey = 0;


				InputOnlineGmData(x, y, PutKey);	
				PutKey = 0;
				/*  for test
				sprintf_s(buf,"new%d",InputHistory.newNo);
				StockFontBuffer( 212 , 250 , FONT_PRIO_FRONT, 1 , buf , 0 );
				sprintf_s(buf,"now%d",InputHistory.nowNo);
				StockFontBuffer( 350 , 250 , FONT_PRIO_FRONT, 1 , buf , 0 );
				sprintf_s(buf,"add%d",InputHistory.addNo);
				StockFontBuffer( 480 , 250 , FONT_PRIO_FRONT, 1 , buf , 0 );
				*/
				//sprintf_s(buf,"Total  %d",TotalAddValue);
				//StockFontBuffer( 480 , 250 , FONT_PRIO_FRONT, 1 , buf , 0 );
				/*
				sprintf_s(buf,"ProNoValue   %d",ProNoValue);
				StockFontBuffer( 490 , 250 , FONT_PRIO_FRONT, 1 , buf , 0 );
				sprintf_s(buf,"ProNoSelect  %d",ProNoSelect);
				StockFontBuffer( 350 , 250 , FONT_PRIO_FRONT, 1 , buf , 0 );
				*/
				StockDispBuffer( x + 320 , y + 228 , DISP_PRIO_MENU , ONLINEGM_BACKGROUND , 1);//����ͼ
				StockFontBuffer( x + 80, y + 180, FONT_PRIO_FRONT, 0,"    ��  ��       ��       ʱ",0);
				StockFontBuffer( x + 387+21, y + 180, FONT_PRIO_FRONT, 0,"    ��  ��      ��       ʱ",0);
				StockFontBuffer( x + 12 , y + 180, FONT_PRIO_FRONT, 5, "��������", 0 );
				StockFontBuffer( x + 315+21 ,y + 180, FONT_PRIO_FRONT, 5, "��������", 0 );
				StockFontBuffer( x + 12 , y + 215, FONT_PRIO_FRONT, 5, "�������", 0 );
				//��ʾʱ��
				sprintf_s( buf ,"%d  %02d       %02d       %02d",okY,okM,okD,okH );
				StockFontBuffer( x + 100-20 , y + 180, FONT_PRIO_FRONT, 1 , buf , 0 );
				sprintf_s( buf ,"%d  %02d      %02d       %02d",wrongY,wrongM,wrongD,wrongH );
				StockFontBuffer( x + 387+21 , y + 180, FONT_PRIO_FRONT, 1 , buf , 0 );
				//��ʾ�������
				StockFontBuffer( x + 90 , y + 215, FONT_PRIO_FRONT, 1, ProblemClass[ClassIndex], 0 );
				if (ClassIndex==1) //һ������ 
				{
					StockFontBuffer( x + 230-30, y + 215, FONT_PRIO_FRONT, 1, ProblemC1[ClassIndex1], 0 );
					StockFontBuffer(  x + 20, y + 250, FONT_PRIO_FRONT, 1, ProblemC1Help[ClassIndex1], 0 );
				}else{	//�쳣����
					StockFontBuffer( x + 230, y + 215, FONT_PRIO_FRONT, 1, ProblemC2[ClassIndex1], 0 );
					switch (ClassIndex1)
					{
					case 0:StockFontBuffer( x + 460, y + 215, FONT_PRIO_FRONT, 1, ProblemC2_1[ClassIndex2], 0 );break;
					case 1:StockFontBuffer( x + 460, y + 215, FONT_PRIO_FRONT, 1, ProblemC2_2[ClassIndex2], 0 );break;
					case 2:StockFontBuffer( x + 460, y + 215, FONT_PRIO_FRONT, 1, ProblemC2_3[ClassIndex2], 0 );break;
					case 3:StockFontBuffer( x + 460, y + 215, FONT_PRIO_FRONT, 1, ProblemC2_4[ClassIndex2], 0 );break;
					case 4:StockFontBuffer( x + 460, y + 215, FONT_PRIO_FRONT, 1, ProblemC2_5[ClassIndex2], 0 );break;
					case 5:StockFontBuffer( x + 460, y + 215, FONT_PRIO_FRONT, 1, ProblemC2_6[ClassIndex2], 0 );break;
					case 10:StockFontBuffer( x + 460, y + 215, FONT_PRIO_FRONT, 1, ProblemC2_7[ClassIndex2], 0 );break;
					default: break;
					}	
					if ((ClassIndex1==2&&ClassIndex2==0)||ClassIndex1==6)
						StockFontBuffer( x + 20,y + 250, FONT_PRIO_FRONT,1,"ѡ�����Ŀ��ע��������ȼ���",0);
				}
				//���user�а��°�ť ��ť��ʾ����
				for ( i = 0 ; i < DEF_BUTTON_TOTAL ; i ++ )
				{
					if (btnState[i]) 
						btnId[i] = StockDispBuffer(  x + BUTTON_XY[i][0], y + BUTTON_XY[i][1]  , DISP_PRIO_IME3, DOWN_ANIM_ID[i] , 2);
					else
						btnId[i] = StockDispBuffer(  x + BUTTON_XY[i][0], y + BUTTON_XY[i][1]  , DISP_PRIO_IME3, UP_ANIM_ID[i] , 2);
				}
			}
		}
	}
	else if (onlinegmProcNo == 1) // ע������
	{
		if (pActOnlineGmWnd==NULL){
			x = (lpDraw->xSize - 7*64)/2;
			y = (lpDraw->ySize - 8*48)/2;

			pActOnlineGmWnd = MakeWindowDisp( x , y , 4+3 , 6+2 ,NULL,0, FALSE);//( 210 , 120, 10 , 10 , NULL , 0 );
			pNowStrBuffer = NULL ;
		}
		else if (pActOnlineGmWnd->hp > 0)
		{
			x = pActOnlineGmWnd->x;
			y = pActOnlineGmWnd->y;
			page = &ProHelp_page[page_index];
			desc = Prohelp_Index[page_index]+page->desc_index;
			desc_index = page->desc_index;

			id = selGraId( HelpId, sizeof( HelpId )/sizeof( int ) );
			if (HelpidState[0]>=0)
				HelpId[0] = StockDispBuffer( x+207+32-160, y+352, DISP_PRIO_IME3, CG_FIELD_HELP_PREPAGE+btnState[1], 2);
			else
				StockDispBuffer( x+207+32-160, y+352, DISP_PRIO_IME3, CG_FIELD_HELP_PREPAGE+btnState[1], 1);

			if (HelpidState[1]>=0)
				HelpId[1] = StockDispBuffer( x+277+32-100, y+352, DISP_PRIO_IME3, CG_FIELD_HELP_NEXTPAGE+btnState[2], 2);
			else
				StockDispBuffer( x+277+32-100, y+352, DISP_PRIO_IME3, CG_FIELD_HELP_NEXTPAGE+btnState[2], 1);			

			HelpId[2] = StockDispBuffer( x+347+32-40, y+352, DISP_PRIO_IME3, CG_FIELD_HELP_EXIT+btnState[3], 2);

			if((mouse.onceState & MOUSE_LEFT_CRICK) && HitDispNo == HelpId[0]){  //��һҳ
				if (page_index){
					page_index--;
					page = &ProHelp_page[page_index];			//ָ����һҳ
					desc_index = page->desc_index;
					desc = Prohelp_Index[page_index]+desc_index;//ָ����һҳ��desc��ͷ
				}
			}			
			if((mouse.onceState & MOUSE_LEFT_CRICK) && HitDispNo == HelpId[1]){	//��һҳ
				if (page_index < 4-1)
				{
					page_index++;
					page = &ProHelp_page[page_index];			//ָ����һҳ
					desc_index = page->desc_index;
					desc = Prohelp_Index[page_index]+desc_index;//ָ����һҳ��desc��ͷ
				}
			}
			HelpidState[0] = page_index==0 ? -2 : 0 ;
			HelpidState[1] = page_index==4-1 ? -2 : 0 ;

			if((mouse.onceState & MOUSE_LEFT_CRICK) && HitDispNo == HelpId[2])
			{
				DeathAction( pActOnlineGmWnd);
				pActOnlineGmWnd = NULL;
				onlinegmProcNo = 0 ;
				ResetFlag = FALSE;
				return 0 ;
			}			
			for( i = 0; i < page->desc_num; i++){
				StockFontBuffer( x+30+5 , y+i*25+10, FONT_PRIO_FRONT, desc->color, desc->description, 0);			
				desc++;
			}
		}
	}
	else if (onlinegmProcNo == 2) //cyg ׼�����͵�ȷ���Ӵ�
	{
		if (pActOnlineGmWnd==NULL){
			x = (lpDraw->xSize - 5*64)/2;
			y = (lpDraw->ySize - 5*48)/2;

			pActOnlineGmWnd =  MakeWindowDisp( x , y , 5 , 5 ,NULL,0, FALSE);
			pNowStrBuffer = NULL ;
		}
		else if (pActOnlineGmWnd->hp > 0)
		{
			x = pActOnlineGmWnd->x;
			y = pActOnlineGmWnd->y;
			MakeHitBox( x + 36,y + 238-85-35,x + 40,y  + 238-85+35, DISP_PRIO_BOX );
			MakeHitBox( x + 156+18,y + 238-85-35,x  + 156+18,y  + 238-85+35, DISP_PRIO_BOX );
			id = selGraId( btnId, sizeof( btnId )/sizeof( int ) );
			int SureBtn[2];
			SureBtn[0] = StockDispBuffer(  x + 70 , y + 250-85+35 , DISP_PRIO_IME3, ONLINEGM_SURE_U , 1);
			SureBtn[1] = StockDispBuffer(  x + 190+18 , y + 250-85+35 , DISP_PRIO_IME3, ONLINEGM_CHANCEL , 1);
			sprintf_s( buf ,"����ѶϢ->");			
			StockFontBuffer( x + 20 , y+ 20+60 , FONT_PRIO_FRONT, 4 , buf , 0 );

			if( TotalAddValue >= DEF_MAX_ADD_VALUE ){  // ��û�д���󽨵���
				sprintf_s( buf ,"�������ⵥ�Ѵ�����20��!!");
				StockFontBuffer( x + 235 , y + 150 , FONT_PRIO_FRONT, 4 , buf , 0 );
				sprintf_s( buf ,"��ɾ�����ⵥ��������лл",TotalAddValue );
				StockFontBuffer( x + 235 , y + 185 , FONT_PRIO_FRONT, 4 , buf , 0 );
				if((mouse.onceState & MOUSE_LEFT_CRICK) && HitDispNo == SureBtn[0])
				{
					DeathAction( pActOnlineGmWnd);
					pActOnlineGmWnd = NULL;
					onlinegmProcNo = 0 ;
					ResetFlag = FALSE;
					return 0 ;
				}
			}else{
				if (ClassIndex==1){
					sprintf_s( buf ,"�������-> %s",ProblemClass[ClassIndex]);
					StockFontBuffer( x + 20 , y + 20+10, FONT_PRIO_FRONT, 1 , buf , 0 );
					sprintf_s( buf ,"��������-> %s",ProblemC1[ClassIndex1]);
					StockFontBuffer( x + 20 , y + 20+35, FONT_PRIO_FRONT, 1 , buf , 0 );
				}else{
					sprintf_s( buf ,"�������-> %s",ProblemClass[ClassIndex]);
					StockFontBuffer( x + 20 , y + 20+10, FONT_PRIO_FRONT, 1 , buf , 0 );
					sprintf_s( buf ,"��������-> %s",ProblemC2[ClassIndex1]);	
					StockFontBuffer( x + 20 , y + 20+35, FONT_PRIO_FRONT, 1 , buf , 0 );
					switch (ClassIndex1)
					{
					case 0: sprintf_s( buf,"����ϸ��-> %s",ProblemC2_1[ClassIndex2] );break;
					case 1: sprintf_s( buf,"����ϸ��-> %s",ProblemC2_2[ClassIndex2] );break;
					case 2: sprintf_s( buf,"����ϸ��-> %s",ProblemC2_3[ClassIndex2] );break;
					case 3: sprintf_s( buf,"����ϸ��-> %s",ProblemC2_4[ClassIndex2] );break;
					case 4: sprintf_s( buf,"����ϸ��-> %s",ProblemC2_5[ClassIndex2] );break;
					case 5: sprintf_s( buf,"����ϸ��-> %s",ProblemC2_6[ClassIndex2] );break;
					case 10: sprintf_s( buf,"����ϸ��-> %s",ProblemC2_7[ClassIndex2] );break;
					default: buf[0] = '\0'; 
					}
					StockFontBuffer( x + 220-25 , y + 120+60, FONT_PRIO_FRONT, 1 , buf , 0 );
					sprintf_s( buf ,"��������-> %4d��%02d��%02d��%02dʱ",okY,okM,okD,okH);
					StockFontBuffer( x + 220-25 , y + 120+85, FONT_PRIO_FRONT, 1 , buf , 0 );
					sprintf_s( buf ,"��������-> %4d��%02d��%02d��%02dʱ",wrongY,wrongM,wrongD,wrongH );
					StockFontBuffer( x + 220-25 , y + 120+110, FONT_PRIO_FRONT, 1 , buf , 0 );				
				}
			
				if( lstrlen(InputHistory.str[InputHistory.lockNo+1]) == 0 && lstrlen(SubBuffer.buffer) == 0 ){
					sprintf_s( buf ,"��������������");
					StockFontBuffer( x + 20 , y + 120, FONT_PRIO_FRONT, 4 , buf , 0 );
					if((mouse.onceState & MOUSE_LEFT_CRICK) && HitDispNo == SureBtn[0])
					{
						DeathAction( pActOnlineGmWnd);
						pActOnlineGmWnd = NULL;
						onlinegmProcNo = 0 ;
						ResetFlag = FALSE;
						return 0 ;
					}
				}else if(ClassIndex==0&&(!okY||!okM||!okD||!wrongY||!wrongM||!wrongD)){ //fix
					sprintf_s( buf ,"����д[��������]��[��������]");
					StockFontBuffer( x + 280-10+2 , y + 260 , FONT_PRIO_FRONT, 4 , buf , 0 );
					if((mouse.onceState & MOUSE_LEFT_CRICK) && HitDispNo == SureBtn[0])
					{
						DeathAction( pActOnlineGmWnd);
						pActOnlineGmWnd = NULL;
						onlinegmProcNo = 0 ;
						ResetFlag = FALSE;
						return 0 ;
					}
				}else{
					if((mouse.onceState & MOUSE_LEFT_CRICK) && HitDispNo == SureBtn[0])
					{
						ResetFlag = FALSE;
						ContentBuf[0] = '\0';
						for ( i=0;i<InputHistory.addNo-1;i++)
							strcat_s(ContentBuf,InputHistory.str[InputHistory.newNo-(InputHistory.addNo-1)+i]); //���ÿһ��
						strcat_s(ContentBuf,SubBuffer.buffer);
						sprintf_s( InputBuffer,"%s",ContentBuf);

						if (ClassIndex==1){  // һ������   û�����ں�ʱ��
							ProblemType=0;
							sprintf_s( DataBuffer,"&star=%s&earth=%s&qtype1=%s&msource=19",gmgroup[nServerGroup].name,gmsv[selectServerIndex].name,ProblemC1[ClassIndex1]);					
						}else{	// �쳣����
							ProblemType=1;
							char tempbuf[60]; 
							sprintf_s( tempbuf,"%s",ProblemC2[ClassIndex1]);
							switch (ClassIndex1)
							{
							case 0: sprintf_s( tempbuf,"%s,%s",tempbuf,ProblemC2_1[ClassIndex2] );break;
							case 1: sprintf_s( tempbuf,"%s,%s",tempbuf,ProblemC2_2[ClassIndex2] );break;
							case 2: sprintf_s( tempbuf,"%s,%s",tempbuf,ProblemC2_3[ClassIndex2] );break;
							case 3: sprintf_s( tempbuf,"%s,%s",tempbuf,ProblemC2_4[ClassIndex2] );break;
							case 4: sprintf_s( tempbuf,"%s,%s",tempbuf,ProblemC2_5[ClassIndex2] );break;
							case 5: sprintf_s( tempbuf,"%s,%s",tempbuf,ProblemC2_6[ClassIndex2] );break;
							case 10: sprintf_s( tempbuf,"%s,%s",tempbuf,ProblemC2_7[ClassIndex2] );break;
							default: break;
							}
#ifdef _CHAR_PROFESSION
							if(lstrlen(pc.profession_class_name) == NULL){
								strcpy(pc.profession_class_name,"��");
							}
#endif
							char side[10];
							if(sCharSide == 1)
								strcpy(side,"��");
							else
								strcpy(side,"��");
#ifdef _CHAR_PROFESSION
							sprintf_s( DataBuffer,"&SY=%d&SM=%d&SD=%d&EY=%d&EM=%d&ED=%d&datarighttime=%d&datawrongtime=%d&msource=18&exceptcont=%s&G1grade1=%d&G1grade2=%d&G1Loc1=%s&G1Job1=%s&star=%s&G1gname1=%s",okY,okM,okD,wrongY,wrongM,wrongD,okH,wrongH,tempbuf,pc.transmigration,pc.level,side,pc.profession_class_name,gmgroup[nServerGroup].name,pc.name);
#else
							sprintf_s( DataBuffer,"&SY=%d&SM=%d&SD=%d&EY=%d&EM=%d&ED=%d&datarighttime=%d&datawrongtime=%d&msource=18&exceptcont=%s&G1grade1=%d&G1grade2=%d&G1Loc1=%s&G1Job1=%s&G1gname1=%s",okY,okM,okD,wrongY,wrongM,wrongD,okH,wrongH,tempbuf,pc.transmigration,pc.level,side,gmgroup[nServerGroup].name,pc.name);
#endif
						}
						DeathAction( pActOnlineGmWnd);
						pActOnlineGmWnd = NULL;
						DWORD dwThreadID,dwThrdParam = 1;
						GMHandle = CreateThread(NULL, 0, OnlineGmThread,&dwThrdParam,0,&dwThreadID);
						if(GMHandle == NULL)
						{
							StockChatBufferLine("������ҵϵͳ��Դ�Ѳ���!!",FONT_PAL_RED);
							StockChatBufferLine("���򵥺Ŵ���ʧ��!",FONT_PAL_RED);
							ResetFlag = TRUE;
							DeathAction( pActOnlineGmWnd);
							pActOnlineGmWnd = NULL;
							return 1;
						}				
						onlinegmProcNo = 0 ;
						return 0 ;
					}	
				}
			}
			if((mouse.onceState & MOUSE_LEFT_CRICK) && HitDispNo == SureBtn[1])  //ȡ��ť
			{
				DeathAction( pActOnlineGmWnd);
				pActOnlineGmWnd = NULL;
				onlinegmProcNo = 0 ;
				ResetFlag = FALSE;
				return 0 ;
			}
		}
	}
	if(CheckMenuFlag()){
		ResetFlag = TRUE;
		DeathAction( pActOnlineGmWnd);
		pActOnlineGmWnd = NULL;
		return 1;
	}
	return 0 ;
}
//************************************************
//��ʽ   : DNSר�ú�ʽ
//�ش�ֵ : TRUE  --- ת���ɹ�
//         FALSE --- ת��ʧ��
//************************************************
BOOL QueryOnlineGmIP(char HostName[])
{
	PHOSTENT info;

//	strcpy(OnlineGmIP,"10.0.1.60");    // ֱ�Ӹ�ip,����ת��code
//	return TRUE;

	if( (info = gethostbyname(HostName)) == NULL)
		return FALSE;
	else{
		OnlineGmIP = inet_ntoa(*(struct in_addr *)*info->h_addr_list);		
	}
	return TRUE;

}
#endif
