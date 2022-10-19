
#ifndef _ONLINEGM_
#define _ONLINEGM_

#define ONLINEGM_BACKGROUND		OLD_GRAPHICS_START+821  //����ͼ
#define ONLINEGM_YES_OR_NO      35322                   //С����ʯ�屳��ͼ 26195�������ͼ
#define ONLINEGM_CHECK_U		OLD_GRAPHICS_START+820	//��ѯ(����)
#define ONLINEGM_CHECK_D		35319					//��ѯ(����)		
#define ONLINEGM_DELETE_U		OLD_GRAPHICS_START+819	//ɾ��(����)
#define ONLINEGM_DELETE_D		35321					//ɾ��(����)
#define ONLINEGM_ENTER_U		26099					//����(����)
#define ONLINEGM_ENTER_D		35320//����(����)
#define	ONLINEGM_CLEAR_U		26298					//���(����)
#define ONLINEGM_CLEAR_D		26299					//���(����)
#define ONLINEGM_HELP_U			OLD_GRAPHICS_START+818	//ע������(����)
#define ONLINEGM_HELP_D			35318					//ע������(����)
#define ONLINEGM_QUIT			26042					    //�ر�
#define ONLINEGM_UP_U			26064					//�Ͼ�(����)
#define ONLINEGM_UP_D			26065					//�Ͼ�(����)
#define ONLINEGM_DOWN_U			26066					//�¾�(����)
#define ONLINEGM_DOWN_D			26067					//�¾�(����)
#define ONLINEGM_SURE_D			26288					//ȷ��(����)(��ɫ��)
#define ONLINEGM_SURE_U			26289					//ȷ��(����)(��ɫ��)
#define ONLINEGM_CHANCEL        26291					//ȡ��


#define DEF_UPDOWN_TOTAL        22						// ���¾�����     
#define DEF_BUTTON_TOTAL        28                      // ���ϻر�ϵͳ��ť����
#define DEF_CLASS_TOTAL         2                       // �����������
#define DEF_C1_TOTAL			14						// ���һϸ������
#define DEF_C2_TOTAL			11 						// ����ϸ������

#define DEF_MAX_ADD_VALUE     20   //Ŀǰ�趨��������20��

#define MAX_INPUT_LINE 		30 			// ����������������

#define DEF_INPUT_LINE 		4 			// ����������ʾ���� chat��20

#define MAX_INPUT_HISTORY 	20			// ???????????

const long UP_ANIM_ID[DEF_BUTTON_TOTAL]={
	ONLINEGM_CHECK_U	,
	ONLINEGM_DELETE_U	,
	ONLINEGM_ENTER_U	,
	ONLINEGM_CLEAR_U	,
	ONLINEGM_HELP_U		, 
	ONLINEGM_QUIT	,
	ONLINEGM_UP_U		,
	ONLINEGM_DOWN_U		,
	ONLINEGM_UP_U		,
	ONLINEGM_DOWN_U		,
	ONLINEGM_UP_U		,
	ONLINEGM_DOWN_U		,
	ONLINEGM_UP_U		,
	ONLINEGM_DOWN_U		,
	ONLINEGM_UP_U		,
	ONLINEGM_DOWN_U		,
	ONLINEGM_UP_U		,
	ONLINEGM_DOWN_U		,
	ONLINEGM_UP_U		,
	ONLINEGM_DOWN_U		,
	ONLINEGM_UP_U		,
	ONLINEGM_DOWN_U		,
	ONLINEGM_UP_U		,
	ONLINEGM_DOWN_U		,
	ONLINEGM_UP_U		,
	ONLINEGM_DOWN_U		,
	ONLINEGM_UP_U		,
	ONLINEGM_DOWN_U		
};
const long DOWN_ANIM_ID[DEF_BUTTON_TOTAL]={
	ONLINEGM_CHECK_D	,
	ONLINEGM_DELETE_D	,
	ONLINEGM_ENTER_D	,
	ONLINEGM_CLEAR_D	,
	ONLINEGM_HELP_D	    , 
	ONLINEGM_QUIT	    ,
	ONLINEGM_UP_D		,
	ONLINEGM_DOWN_D		,
	ONLINEGM_UP_D		,
	ONLINEGM_DOWN_D		,
	ONLINEGM_UP_D		,
	ONLINEGM_DOWN_D		,
	ONLINEGM_UP_D		,
	ONLINEGM_DOWN_D		,
	ONLINEGM_UP_D		,
	ONLINEGM_DOWN_D		,
	ONLINEGM_UP_D		,
	ONLINEGM_DOWN_D		,
	ONLINEGM_UP_D		,
	ONLINEGM_DOWN_D		,
	ONLINEGM_UP_D		,
	ONLINEGM_DOWN_D		,
	ONLINEGM_UP_D		,
	ONLINEGM_DOWN_D		,
	ONLINEGM_UP_D		,
	ONLINEGM_DOWN_D		,
	ONLINEGM_UP_D		,
	ONLINEGM_DOWN_D		
};
const short BUTTON_XY[DEF_BUTTON_TOTAL][2]={
	{584,97 },{584  ,120},{584,316},{584,  340},{584,409},{584  ,434},
	{550-100,54+100 },{530+1-100,72+100 },{550-100,366+100},{530+1-100,384+100},
	{164-100,175+100},{144+1-100,193+100},{229-100,175+100},{209+1-100,193+100},{298-100,175+100},{278+1-100,193+100},
	{468-100+21,175+100},{448+1-100+21,193+100},{530-100+21,175+100},{510+1-100+21,193+100},{593-100+21,175+100},{573+1-100+21,193+100},
	{164-100,212+100},{144+1-100,230+100},{392-100,212+100},{372+1-100,230+100},{614-100,212+100},{594+1-100,230+100}	
};

int iOnlineGmProc( void );

#endif
