#ifndef __VERSION_H__
#define __VERSION_H__

#ifdef _WIN32
#include <crtdbg.h>
#endif


#ifdef _SA_VERSION_SPECIAL
#define _SA_VERSION_60
#define __ALBUM_47
#define _FONT_SIZE					// Robin (Ҫ��) �ɸ����ʹ�С
#define _ITEM_PILENUMS				// (�ɿ���) ANDY �����زĶѵ�
#define _ITEM_INTENSIFY				// (�ɿ�) Change �輼:ǿ������
#define _ALCHEMIST					// Robin �������� 
#define _CHAR_NEWLOGOUT				// (�ɿ���) ANDY �µǳ�����
//#define _ITEM_JIGSAW				// (�ɿ�) Change ƴͼ����
#define	_TELLCHANNEL				// (�ɿ���) ROG ADD ����Ƶ��
#define _TRADETALKWND				// (�ɿ���) Syu ADD ���������Ի����
#define _DROPPETWND					// (�ɿ���) Syu ADD ��������ȷ��
#define _TEAM_KICKPARTY				// (�ɿ���) ANDY �ӳ�����
#define _MONEYINPUT					// (�ɿ���) Syu ADD �ֶ������Ǯ��

#define _STREET_VENDOR				// ��̯����
#define _STREET_VENDOR_CHANGE_ICON	// �޸İ�̯ͼʾ
#define _NEW_MANOR_LAW				// ��ׯ԰����
#define _PETS_SELECTCON				// (�ɿ���) ANDY ����ѡ��
#define _FM_MODIFY					// ���幦���޸�
#define _CHANNEL_MODIFY				// Ƶ����������
#define _TRADELOCKBTN				// (�ɿ���) Syu ADD ����������
#define _MAILSHOWPLANET				// (�ɿ���) Syu ADD ��ʾ��Ƭ����
#define _LOCKPARTYFLOOR				// (�ɿ���) Syu ADD ���Ӳ�����ӵĵ�ͼ���
#define _LOCKHELP_OK				// (�ɿ���) Syu ADD �������ɼ���ս��
#define _JOBDAILY					// cyg ������־����
//	#define _TALK_WINDOW				// �Ի��Ӵ�
#define _SHOW_FUSION				// (�ɿ�) Change �ںϳ�����CLIENT��ֻ��ʾת����,�޸�Ϊ�ںϳ���ʾΪ�ں�
#define _ITEM_FIREWORK				// �̻���
#define _FIREWORK_SOUND				// cyg ������Ч(�̻���)
//#define _GET_HOSTNAME				// (�ɿ�) Change ȡ�õ�������
#define _NPC_MAGICCARD				// cyg ħ������Ϸ
#define _THEATER					// Terry �糡����
#define _MOVE_SCREEN				// Terry �ƶ�ӫĻ��ָ��������
#define _NPC_DANCE					// cyg ��һ��npc
#define _CHANNEL_WORLD				// ��������Ƶ��
#define _STANDBYPET					// Robin �ʹ������б�Server
#define _MAILSHOWPLANET				// (�ɿ���) Syu ADD ��ʾ��Ƭ����
#define _EXTEND_AB					// cyg ������Ƭ����
#define _ITEM_EQUITSPACE			// (�ɿ���) ANDY ����װ����λ
#define _EQUIT_ARRANGE				// (�ɿ���) ANDY ��
#define _EQUIT_NEWGLOVE				// (�ɿ���) ANDY ������λ
//#define _ALCHEMIST					// Robin �������� 
//#define _ALCHEPLUS					// Robin �������� 
//#define _NPC_ITEMUP					// (�ɿ�) Change �õ���������NPC
//#define _ITEM_COUNTDOWN				// cyg ���ߵ�������
//#define _CHATROOMPROTOCOL			// (�ɿ���) Syu ADD ������Ƶ��
//#define _FRIENDCHANNEL				// (�ɿ���) ROG ADD ����Ƶ��
//#define __ONLINEGM
#endif
//#define _BATTLE_PK_PLAYER_FOR_40		// 40��ս��
//#define  _BATTLE_PK_PLAYER_FOR_6VS6		// 6 vs 6       XIEZI ���

#ifdef _BATTLE_PK_PLAYER_FOR_40
#define BATTLESIDENUM 4					//ս����������
#define BATTLKPKPLYAERNUM 40			//����ս��ɫ��
#define MAX_BATTLE_ROW_CHARS   5		//ÿ�����ս����ɫ��
#else
#define BATTLESIDENUM 2					//ս����������
#ifdef _BATTLE_PK_PLAYER_FOR_6VS6
#define BATTLKPKPLYAERNUM 24			//����ս��ɫ��
#define MAX_BATTLE_ROW_CHARS   6		//ÿ�����ս����ɫ��
#else
#define BATTLKPKPLYAERNUM 20			//����ս��ɫ��
#define MAX_BATTLE_ROW_CHARS   5		//ÿ�����ս����ɫ��
#endif
#endif

#define _NEW_SYSTEM_MENU				// ��ϵͳ�˵� 2011/12/21
#define _PTTERN_SEPARATION_BIN			// ���벹������
//#define _SFUMATO						// ������Ⱦ δ���ƣ���������Դ���
#define _SPECIAL_LOGO					// �µ�½ͼ
#define _CHANNEL_ALL_SERV				// ��������Ƶ�� 2011/12/21
#define _EXTEND_FONT_PAL				// ��չ������ɫɫ�� 2011/12/22
//#define _FONT_PARAGRAPH_COLOR			// ���������ɫ 2011/12/22
#define _NEW_CLIENT_LOGIN				// ��½��¼MAC��ַ����·ѡ�� 2011/12/22
//#define _NEW_SHOP_FRAME  				// ���̵��� 2011/12/22

#define _HI_COLOR_16				// (�ɿ�) ANDY (8bit to 16bit) ��ͼ��
#define _HI_COLOR_32				// (�ɿ�) longzoro (32 bit) ��ͼ��
#define _NEW_RESOMODE				 //800 600ģʽ
#define _MOUSE_SHOW_INFO_FOR_HEAD	// (�ɿ�) longzoro �����ʾ��Ϣ
//#define _NEWLOGO				   // (�ɿ���) Syu ADD 6.0���뻭����logo Ҫ��_v4_0 
/* -------------------------------------------------------------------
* �¹��ܣ�ʯ�� 800 * 600
* ��Ա�����,����
* ˵����
*/

extern int DISPLACEMENT_X;
extern int DISPLACEMENT_Y;
extern int viewOffsetX;
extern int viewOffsetY;

//#define _NEWDRAWBATTLEMAP_FIX		   // (���ɿ�)ROG ADD ս����ͼ�޸�

// �汾�ָ�
#ifdef _SA_VERSION_85
#define _SA_VERSION_80
#endif

#ifdef _SA_VERSION_80
#define _SA_VERSION_75
#endif

#ifdef _SA_VERSION_75
#define _SA_VERSION_70
#endif

#ifdef _SA_VERSION_70
#define _SA_VERSION_60
#endif

#ifdef _SA_VERSION_60
#define _SA_VERSION_50
#endif

#ifdef _SA_VERSION_50
#define _SA_VERSION_40
#endif



/* �뽫����ר���� definition �����������
* Ȼ����� remark/unmark �����ع���
*/



/* -------------------------------------------------------------------
* ר��������ְ������幦�ܲ���
* ��Ա��С褡���ѫ��־ΰ��С��
* ˵����
*/
#define  _FMVER21                      // (�ɿ���) ����ְ�ƹ���
#define _PERSONAL_FAME                 // (�ɿ���) Arminius 8.30 �����������


// -------------------------------------------------------------------
// ר���������½��NPC��̸����
// ��Ա������
// ˵����__EDEN_EFFECT:�ĳ�������NPC'ί�н��׵�NPC
//			 __EDEN_AUCTION:ί��NPC������Ʒ����
#define __EDEN_EFFECT			// (�ɿ���) ������ʱҪ��
#define __EDEN_AUCTION		    // (�ɿ���) ������ʱҪ��

// -------------------------------------------------------------------
// ר��������������������
// ��Ա����־
// ˵����
#define __ATTACK_MAGIC

// -------------------------------------------------------------------
// ר���������޵ı���
// ��Ա������
// ˵����
#define _ITEM_FIRECREAKER

/* -------------------------------------------------------------------
* �¹��ܣ�PK��ϵ
* ��Ա����ѫ
* ˵����
*/
//#define _PKSERVER // (���ɿ���)


// -------------------------------------------------------------------
// ר���������ֻ���Ѷ����ҽ���ʵ��
// ��Ա������  (LeiBoy)
// ˵��������ҿ��Դ���Ѷ���ض���ASP��ҳ����
// ��Ҫ��ص� : PhoneMsg.cpp
// ������� : 2002��01��28��
// �������� : 2002��03��04��
// Status : Ready!
//#define __PHONEMESSAGE    
#define _FIX_URLENCODE             // WON ADD (�� �� ��) ����������Ѷ�޷��ӿո������


// -------------------------------------------------------------------
// ר���������ֻ���Ѷ�Ķ��ڹ���
// ��Ա��(ԭ��)����  (�Ӱ���δ��)
// ˵��������ҿ��Դ���Ѷ����Ƭ�к��ѵ��ֻ���
// �������� : ��ֹ����!!
// Status : ������...
//#define __CARDMESSAGE   //(����)!!


//#define __NEW_CLIENT_ONLY_WRITE	//Cary(����,δ���)
//#define CHINA_VER			//Cary (����)
//#define __ALBUM_4
//#define __ALBUM_6			//Cary �����µĳ����ಾ(������)
//#define __TEST_SERVER		//Cary 3.0�Ĳ���server

#define __HELP				//Cary ����˵��
#define __NEW_PROTOCOL		//Cary �µĵײ�

#define __NEW_CLIENT_MEM	//Cary
#define __SKYISLAND			//Cary ������յ��Ĺ���
#define __HI_COLOR			//Cary ����߲ʵĹ���(debug versionר��)
#define __TALK_TO_NPC		//Cary ʹ�������npc˵��
#define __NEW_BATTLE_EFFECT	//Cary 2002.2.21 �µ�ս����Ч����:��������
#define _AFTER_TRADE_PETWAIT_	   // (�� �� ��) set pet status to wait after trade :vincent



#ifdef _SA_VERSION_40
/* -------------------------------------------------------------------
* �¹��ܣ�����4
* ��Ա��־��
* ˵����
*/
#define _FIX_DEL_MAP			   // (�ɿ���) WON ADD ������ҳ��ͼ

#define _FIX_9_FMPOINT			   // (�ɿ���) WON ADD �Ŵ�ׯ԰
#define _FIX_10_FMPOINT			//(�ɿ�) Change ʮ��ׯ԰ 20050404
#ifdef _FIX_10_FMPOINT
#define fm_point_num	10		   // ׯ԰��
#else
#define fm_point_num	9		   // (�ɿ���) WON ADD ׯ԰��
#endif

#define _ADD_POOL_ITEM				// (�ɿ���) WON ADD ���Ӽķŵ���
//#define _ADD_FAMILY_TAX				// (���ɿ�) WON ADD ����ׯ԰˰��

#define _LOST_FOREST_FOG			// (�ɿ���) the lostforest's fog. code:shan 
#define _MIND_ICON					// (�ɿ���) show icon from char mind. code:shan
#define _MAGIC_WEAKEN				// (�ɿ���) show magic(weaken). code:shan

#define _BLACK_MARKET            // (���ɿ�) a black market. code:shan 

// -------------------------------------------------------------------
// vincent define
#define _MAGIC_DEEPPOISION         // (�ɿ���) show magic(deeppoison). code:vincent
#define _MAGIC_BARRIER             // (�ɿ���) show magic(barrier). code:vincent
#define _MAGIC_NOCAST              // (�ɿ���) show magic(nocast). code:vincent
#define _ITEM_CRACKER              // (�ɿ���) ����:���� code:vincent
#define _SKILL_ROAR                // (�ɿ���) vincent  �輼:���(������)
#define _SKILL_SELFEXPLODE         // (�ɿ���) vincent  �輼:�Ա�

#define _NEW_RIDEPETS			   // (�ɿ���) �����

#define _ATTDOUBLE_ATTACK	       // (�ɿ���) ����ǿ������
#define __TOCALL_MAGIC			   // (�ɿ���) kjl 02/06/24	
#define _VARY_WOLF                 // (�ɿ���) pet skill : vary wolf. code:shan
#define _PIRATE_ANM                // (�ɿ���) monster move(������). code: shan
#define _TRADE_PETCOLOR            // (�ɿ���) Syu ADD �ı佻��ʱ����ת����ɫ
#define _FIXSHOWMPERR			   // (�ɿ���) Syu ADD ��������ʱ������ʾ����
#define _LIZARDPOSITION			   // (�ɿ���) Syu ADD ����������ʾλ�ù���


/* -------------------------------------------------------------------
* �¹��ܣ�
* ��������2002/12/18 14:00 ����
*/

#define _TEAM_KICKPARTY				// (�ɿ���) ANDY �ӳ�����
#define _MONEYINPUT					// (�ɿ���) Syu ADD �ֶ������Ǯ��

#define _PETS_SELECTCON				// (�ɿ���) ANDY ����ѡ��

#endif		// _SA_VERSION_40



#ifdef _SA_VERSION_60
/* -------------------------------------------------------------------
* �¹��ܣ�ʯ��6.0
* ��������
*/
#define _OBJSEND_C					// (�ɿ���) ANDY 6.0
#define _ADD_SHOW_ITEMDAMAGE		// (�ɿ���) WON ADD ��ʾ���ߵ��;ö�
#define _WATERANIMATION				// (�ɿ���) Syu ADD ��֮��������
#define _NEWDRAWBATTLEMAP			// (�ɿ���) Syu ADD ˮ����ս���ر���ս����Ч 
#define _AniCharBubble				// (�ɿ���) Syu ADD �����������³�����
#define _AniCrossFrame				// (�ɿ���) Syu ADD �������ι���������
#define _AniImmobile				// (�ɿ���) Syu ADD ��������ض�����
#define _AniRandom					// (�ɿ���) Syu ADD ���������������
//#define _DELBORNPLACE				// (�ɿ���) Syu ADD 6.0 ͳһ���������ִ�
#define _NEWMUSICFILE6_0			// (�ɿ���) Syu ADD 6.0 �µ�ͼ����
#define _TRADESHOWNAME				// (�ɿ���) Syu ADD ������ʾ�Է�����
#define _TRADEINPUTMONEY			// (�ɿ���) Syu ADD �����ֶ������Ǯ
#define _TRADE_SHOWHP				// (�ɿ���) Syu ADD ������ʾѪ��
#define _CHANGETRADERULE			// (�ɿ���) Syu ADD ���׹����޶�
#define _PETSKILL_CANNEDFOOD		// (�ɿ���) ANDY ���＼�ܹ�ͷ
#define _SPECIALSPACEANIM			// (�ɿ���) Syu ADD ���ⳡ����������
#define _SHOOTCHESTNUT				// (�ɿ���) Syu ADD �輼��������
//#define _NEWLOGO				   // (�ɿ���) Syu ADD 6.0���뻭����logo Ҫ��_v4_0 
#endif		//SA_VERSION_60

#define _TRADESYSTEM2				// (�ɿ���) Syu ADD �½���ϵͳ

#ifdef _SA_VERSION_70
/* -------------------------------------------------------------------
* �¹��ܣ�ʯ��7.0
* ��������
*/
//�ѿ���
#define _SARS						// (�ɿ���) WON ADD ��ɷ����
#define _FIX_MAXGOLD			    // (�ɿ���) WON ADD ���������Ǯ����

#define _ITEM_PILENUMS				// (�ɿ���) ANDY �����زĶѵ�

#define _ITEM_EQUITSPACE			// (�ɿ���) ANDY ����װ����λ
#define _EQUIT_ARRANGE				// (�ɿ���) ANDY ��
#define _EQUIT_NEWGLOVE				// (�ɿ���) ANDY ������λ

#define _LOCKPARTYFLOOR				// (�ɿ���) Syu ADD ���Ӳ�����ӵĵ�ͼ���
#define _LOCKHELP_OK				// (�ɿ���) Syu ADD �������ɼ���ս��

#define _TRADETALKWND				// (�ɿ���) Syu ADD ���������Ի����
#define _TRADELOCKBTN				// (�ɿ���) Syu ADD ����������

#define _WAVETRACK					// (�ɿ���) Syu ADD ���������������

#define _CHAR_NEWLOGOUT				// (�ɿ���) ANDY �µǳ�����

//�¹��ܣ�����ְҵ
#define _TABLEOFSKILL				// (�ɿ���) Syu ADD 7.0 �������＼�ܱ�
//#define _NEWPANEL_71				// (�ɿ���) ROG ADD ��login����
//#define	_NEWPANEL_70				// (�ɿ���) Syu ADD ʯ��7.0 LOGIN ����
#define _CHAR_PROFESSION			// (�ɿ���) WON ADD ����ְҵ
#define _SKILLSORT					// (�ɿ���) Syu ADD ְҵ�������з���
#define _NEWREQUESTPROTOCOL			// (�ɿ���) Syu ADD ����ProtocolҪ������ϸ��
#define _OUTOFBATTLESKILL			// (�ɿ���) Syu ADD ��ս��ʱ����Protocol
#define _NEWSOUNDEFFECT				// (�ɿ���) Syu ADD ������Ч��
#define _FIXSTATUS					// (�ɿ���) Syu ADD ��ս��״̬��ʾ��ʽ
#define _ALLDOMAN					// (�ɿ���) Syu ADD ���а�NPC
#define _CHATROOMPROTOCOL			// (�ɿ���) Syu ADD ������Ƶ��
#define _FRIENDCHANNEL				// (�ɿ���) ROG ADD ����Ƶ��
#define	_TELLCHANNEL				// (�ɿ���) ROG ADD ����Ƶ��

#define _DROPPETWND					// (�ɿ���) Syu ADD ��������ȷ��

#define _MAILSHOWPLANET				// (�ɿ���) Syu ADD ��ʾ��Ƭ����
#define _MOON_FAIRYLAND				// (�ɿ���) ROG ADD ��֮�ɾ�
#define _SPECIALSPACEANIM_FIX		// (�ɿ���) ROG ADD ��������
//#define _TIMEBAR_FUNCTION			// (���ɿ�) ROG ADD ʱ��bar��ʽ


//10/23
#define _FM_MODIFY				// ���幦���޸�

#define _FIREHUNTER_SKILL			// (�ɿ���) ROG ADD ��ȸ����_������ɱ
#define _PETSKILL_ACUPUNCTURE       // (�ɿ���) Change �輼:�����Ƥ
#define _PETSKILL_DAMAGETOHP	    // (�ɿ���) Change �輼:���¿���(��Ѫ���ı���) 
#define _PETSKILL_BECOMEFOX         // (�ɿ���) Change �輼:�Ļ���
#define _PETSKILL_BECOMEPIG         // (�ɿ�) Change �輼:������


// �¹��ܣ����������Ͽ�(�¸��ѻ���)
#define _NEW_WGS_MSG				// (�ɿ�) WON ADD WGS�����Ӵ�


#define _CHANNEL_MODIFY		// Ƶ����������


#define _CHANGEGALAXY // Robin ��ϵ����
#define _ERROR301 // Robin AP�ش�301����,��Ʒ��δע��

#define _STANDBYPET // Robin �ʹ������б�Server
#endif		//SA_VERSION_70


#define	DIRECTINPUT_VERSION 0x0700	// Robin ����DirectX SDK��������

#define _CLOUD_EFFECT				// (���ɿ�) ROG ADD	�Ʋ�Ч��
//#define _NPC_WELFARE_2			// (���ɿ�) WON ADD ְҵNPC-2

//#define _NPC_SELLSTH				// (�ɿ���) ANDY ����
//#define _SYUTEST
//#define _SYUTEST2
//#define _SYUTEST3
//#define _AUCPROTOCOL				// (���ɿ�) Syu ADD ����Ƶ������Protocol

/* -------------------------------------------------------------------
* �¹��ܣ�PK������
* ��������
*/
//������
//������

//#define _PKSERVERCHARSEL			// (���ɿ�) Syu ADD PK������ѡ����ϵ����
// -------------------------------------------------------------------
// ���²��ɿ�
/* -------------------------------------------------------------------
* �¹��ܣ�real.bin��ͼ
* ��������
*/
//������F
//#define _SAHOOK				    // (���ɿ�) Syu ADD Hook��ʽ
//#define _REALDIVISION			    // (���ɿ�) Syu ADD real.bin��ͼ��Ҫ��realtxt.txt��
// -------------------------------------------------------------------
//#define _OMIT_WGS					// (���ɿ�) �Թ��ʺš�������WGS. code:shan
// -------------------------------------------------------------------
#ifdef _SA_VERSION_50
/* -------------------------------------------------------------------
* �¹��ܣ�ʯ��5.0
* ˵����
*/
//#define _CANT_ATK					// (���ɿ�) can't attack(own team). code: shan
//#define _SETTICK_COUNT			// (���ɿ�) ANDY �ظ�����
//#define _GM_MARK					// (���ɿ�) WON ADD GM ʶ��
//#define _GM_IDENTIFY		        // (���ɿ�)Rog ADD GMʶ���gmָ��

//#define _LOGINKICK				// (���ɿ�) Syu ADD ���뻭�泬��30���߻���ϵ�б�
#endif		//SA_VERSION_50
#define MALLOC(s) malloc(s)
#define CALLOC(c,s) calloc(c,s)
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#define FREE(p) free(p)

//#define _PET_TRACE_MOUSE
//#define __EDEN_DICE  				// (���ɿ�) �ĳ�����
#define _AI_OTHER						// AI��������
#define __AI							// Cary �����Զ�ս������
#ifdef _AI_OTHER
#define _AI_CAPTURE
#endif
//-----------------------
unsigned int TimeGetTime(void);

#ifdef _SA_VERSION_70
#ifdef _BACK_VERSION
#define _REMAKE_20						// ʯ�����̹��ܿ���(�����)
#define _BACK_LOGO
#define _BACK_WINDOW //���̰��Ӵ���(debug��ſɿ�,�ڲ���Աʹ��)
#define _READ16BITBMP					// Terry �ɶ��뼰��ʾ�߲�ͼ
#else
#define _ATTACK_AI						// �ڹҹ���AI
#define _AI_NEW_FIRST					// AI �״ο�����ְҵ����
#define _BATTLESKILL					// (�ɿ���) Syu ADD ս�����ܽ���
#define _NEWPANEL						// (�ɿ���) Syu ADD 7.0 ������״̬����
#endif
#endif

#ifdef _SA_VERSION_75
/* -------------------------------------------------------------------
* �¹��ܣ�ʯ��7.5
* ��������
*/

#define _ANGEL_SUMMON			// ��ʹ���л� Robin
#define _PROFESSION_ADDSKILL  // (�ɿ�) Change ׷��ְҵ����
#define _TRANS_6				// (�ɿ�) Change ����6ת
#define _PET_2TRANS			// (�ɿ�) Change ����2ת
//#define _75_LOGIN					// 7.5��login���� 
#define _STREET_VENDOR		// ��̯����
#define _NEW_MANOR_LAW		// ��ׯ԰����

#define _PETSKILL_LER			// �׶�����
//#define _PK_SERVER            //����PK�
//#define _8_TEST					//8.0����server

// -------------------------------------------------------------------
// ר�������ϻر�ϵͳ
// ��Ա���ݿ�
// ˵����
//#define __ONLINEGM
//--------------------------------------------------------------------

#define _STREET_VENDOR_CHANGE_ICON	// �޸İ�̯ͼʾ

#define _TALK_WINDOW				// �Ի��Ӵ�
#define _SHOW_FUSION				// (�ɿ�) Change �ںϳ�����CLIENT��ֻ��ʾת����,�޸�Ϊ�ںϳ���ʾΪ�ں�
#define _NPC_FUSION					// (���m��) ANDY NPC����о��

#define _FONT_SIZE					// Robin (Ҫ��) �ɸ����ʹ�С
#define _CONTRACT					// Robin (Ҫ��) ��Լ����
#define _HALLOWEEN_EFFECT			// ��ʥ����Ч
#define _ADD_STATUS_2				// ������������״̬�ڶ���
#define _PETSKILL_BATTLE_MODEL		// ���＼��ս��ģ��
#define _RACEMAN					// cyg �Գ�����npc
#define _PETSKILL_ANTINTER			// (�ɿ�) Change �輼:��֮��
#define _PETSKILL_EXPLODE			// (�ɿ�) Change �輼:���ѹ���
#define _ITEM_FIREWORK				// �̻���
#define _FIREWORK_SOUND				// cyg ������Ч(�̻���)
#define _GET_HOSTNAME				// (�ɿ�) Change ȡ�õ�������
#define _SKILL_ADDBARRIER			// (�ɿ�) Change �輼:Ϊħ�������쳣���Թ���
#define _PETSKILL_PEEL				// (�ɿ�) Change �輼:����ѿ�

//#define _MOUSE_DBL_CLICK			// Robin �����Ҽ�˫������
#endif		//SA_VERSION_75

#ifdef _SA_VERSION_80
//--------------------------------------------------------------------------------------------------------
//ר�� 8.0 ʧ������� �¼ӹ��ܶ����� ��Ա����ѫ ���� ���� �ݿ�
//--------------------------------------------------------------------------------------------------------
#define _PET_ITEM				// Terry �����װ������
#define _NPC_PICTURE			// (�ɿ�) Change �¶ĳ�����(��ʱ�����NPC)
#define _JOBDAILY				// cyg ������־����
#define _ITEM_PATH				// (�ɿ�) Change ��̤�ϲ���������ĵ���
#define _ALCHEMIST				// Robin �������� 
#define _ALCHEPLUS				// Robin �������� 
#define _EXTEND_AB				// cyg ������Ƭ����
#define _ITEM_INTENSIFY			// (�ɿ�) Change �輼:ǿ������
#define _TEACHER_SYSTEM			// Terry ��ʦϵͳ
#define _ITEM_UPINSLAY			// (�ɿ�) Change �輼:���(�õ��߿����ϸ��౦ʯ)
#define _MAG_MENU				// (�ɿ�) Change ħ�������ȡ�������������ʾ��Ϊͼʾ��
#define _NPC_MAGICCARD			// cyg ħ������Ϸ
#define _THEATER				// Terry �糡����
#define _MOVE_SCREEN			// Terry �ƶ�ӫĻ��ָ��������
//	#define _80_LOGIN				// Terry 8.0 ���뻭��
#define _8_RIDEPETS				// (�ɿ�) Change 8.0���
#define _8BATTLEMAP				// Change 8.0 ս���ر�
#define _PETKILL_COST_FAME		// Terry ���＼�ܵ�ѧ����Ҫ��������
#define _DRAGON_FUSION			// Robin ��������

#define _MACADDRESSD			// (�ɿ�) Change get MAC card
#define _NEW_EARTH				// Terry �µ���,�ɿ����ڲ�������
//#define _80_LOGIN_PLAY		// Terry 8.0 ���뻭��
//----------------------------------------------------------------------

//#define _ITEM_JIGSAW			// (�ɿ�) Change ƴͼ����

#define _NPC_DANCE				// cyg ��һ��npc
#define _ATTACK_EFFECT			// ��ɫ�������Ქ�Ź�����Ч

//#define _2005_ValentineDay		// Terry 2005 ���˽ڻ
#define _PETSKILL_ADDATTCRAZED	// (�ɿ�) Change �輼:���ұ������ӹ���
#define _PETSKILL_JUSTICE		// (�ɿ�) Change �輼:����
#define _CALLBUS				// (�ɿ�) Change �ù������б����еĹ���

//#define _NPC_ITEMUP				// (�ɿ�) Change �õ���������NPC
//#define _ITEM_COUNTDOWN			// cyg ���ߵ�������

#define _PRO_KILLME				// Change ����ְ��  ʰ���յ�
#define _PETSKILL_EVOLUTION		// (�ɿ�) Change �����ܳ輼:����
#define _PETSKILL_PROVOKEFIGHT	// (�ɿ�) Change Ȯ��輼:���Ʒ���
#define _FIX_ACUPUNCTURE		// (�ɿ�) Change �����Ƥ���޸�
#define _PETSKILL_RIDE			// (�ɿ�) Change �輼:������

#endif		// _SA_VERSION_80

#ifdef _SA_VERSION_85
//--------------------------------------------------------------------------------------------------------
//ר�� 8.5 ħ���ð�� �¼ӹ��ܶ����� ��Ա������ �ݿ�
//--------------------------------------------------------------------------------------------------------
#define _PRO_ABSOLUTE_DEFENSE	// (�ɿ�) Change ����ְ��  ���Է���
#define _PRO3_ADDSKILL		// (�ɿ�) Change ׷��8.5ְҵ����
#define _NPC_DAYACTION		// cyg ÿ�ջ
#define _EVIL_KILL			// cyg �ַ�ħ��ϵͳ
#define _HUNDRED_KILL			// cyg ������˫
#define _NEW_CLOUD			// (�ɿ�) Change �µĵ�ͼ����Ч��
//#define _85_LOGIN			// (�ɿ�) Change 8.5���뻭��
//----------------------------------------------------------------------
#define _AI_SKILL_UPDATE		//��AI����
#define _TEACHER_SYSTEM_2		// cyg �µ�ʦϵͳ
#endif
#endif


/*
����������
*/
#define _FIX_MAXGOLD			    // (�ɿ���) WON ADD ���������Ǯ����
#define _MOON_FAIRYLAND				// (�ɿ���) ROG ADD ��֮�ɾ�
#define _SPECIALSPACEANIM_FIX		// (�ɿ���) ROG ADD ��������
#define _LOGINKICK					// (���ɿ�) Syu ADD ���뻭�泬��30���߻���ϵ�б�
//#define _CHECK_GAMESPEED		    // (���ɿ�) ANDY ������
#define _NEW_CLOUD					// (�ɿ�) Change �µĵ�ͼ����Ч��
#define _FIX_BATTLE_AI				// �޸�ս��AIת����BUG
#define _WIN_LUAJIT_				//����LUAJIT��չ����     ֧�����Ľӿں�����·��LUA�ļ�
#define _NEW_COLOR_					//����֧��16λRGB565�߲�ͼƬ
#define _NEW_WIN_POS_				//800����ƫ������
#define _NEW_ALPHA_					//�½���͸������
//#define _CACHE_SURFACE_				//�������
//#define _OPTIMIZATIONFLIP_  		//�Ż�Flip
#define _KEY_  "AEB3A729E71F8870D4611FBDC01D0A4B"      //���м���
//#define _NEWFONT_


#define _MO_SIGN_IN					//�ͻ���ǩ����ť
#define _CHANGE_HELP_BUTTON  		//�޸İ�����ťͼ��
#define _PETCOM_					//����ɳ��Զ�����
#define _NEW_SPEED_					//����Ϸ�ٶ�

#define _PETCOLOR_					//1�������ɫ
#define _PETKILL_COST_FAME			// Terry ���＼�ܵ�ѧ����Ҫ������
#define _AIDENGLU_					//�Զ���½
#define _ZHENGSHIKAIFU_				//��ʽ������
#define _ZENGJIASHUO_				//����һ�������ߵ�ͼ�꣬ͬʱ�����ĵ��߲���ѡ��
#define _BUDING_ "554CDB1A99DF514B2F0B09DBDA0A6E9D"       //��������
#define _TIME_GET_TIME				// ��QueryPerformanceCounterȡ��timeGetTime
#define _FAMILYBADGE_				//�������
#define _SHOWFAMILYBADGE_			//��ʾ�������
#define _NEWNET_					//�·������
//#define _LOGIP_					//��½ʱ��ȡIP
//#define _SHOWIPSLEEP_				//��ʾ��·��ʱ
//#define _MEMORYLEAK_CHECK			//�ڴ�й©���
//#define _COMFIRM_TRADE_REQUEST		//��������ȷ��
#define _DIEJIA_					//���ӹ���
#define _FANILYTEXIAOY_  45			//�������ƫ��Y Խ����Խ�����ڶ���
#define _OTHERTEXIAOY_  70			//����ͼ��ƫ��Y Խ����Խ�����ڶ���
#define _ATTACK_EFFECT				// ��ɫ�������Ქ�Ź�����Ч
#define _SA_VERSION 'N'
#define _SA_MAC_VERSION_CONTROL		//MAC�汾�ſ���
#define FAMILY_MANOR_				//ׯ԰�⻷
#define _CHAR_MANOR_                //������¹⻷
//#define _CHAR_MANOR_DEBUG                //������¹⻷DEBUG
#define _ANNOUNCEMENT_				//����ϵͳ
//#define _EFFECT_MAP_				//����Ч
#ifndef _DEBUG__
#define _VMP_						//VMP���ܿ���
//#define _NODEBUG_					//������   ���Ե�ʱ�����������ˣ���ʽʹ������������
#else
#define _CMD_MODE					//����ģʽ
//#define _STONDEBUG__PACKET_       //���Է��
//#define _MO_SHOW_FPS				//��ʾfps
#define _RELUA_						//DEBUGģʽ�����ð�������Ϣ���ض�LUA
#endif
#define SHOW_VERSION "www.shiqi.hk"
//#define _TRADE_BUG_LOG				//����bug��־
#define _SECONDARY_WINDOW_DATA_		//������������
#define LABEL_STR_                 //����ض������[��][��]

#ifdef _SA_VERSION_25
#define _DEFAULT_PKEY "shiqi"		// Ĭ�ϵ���Կ
#define _RUNNING_KEY  "shiqi.hk"		// ��������Կ
#define _SYSTEM_SLEEP_   6  //��Ϸ�ٶ�����
#define _SURFACE_ANIM				// ��̬��������ʾ
#define _DEFENSETOOENNUM_ 5			//�޼���
#define DENGLUKEY1 "6D27AEB8326A2A8E7D04B9F9B44C59C7"
#define _LEADERRIDE	 				   // (�ɿ���) �Ĵ�����ﱩ���� Robin 0921
//#define _MO_IMAGE_EXTENSION			//������չ
#define _NEW_ITEM_					//�µ�����
#ifdef _WIN_LUAJIT_
#define _LUA_PATCH_ ".//lua"  //LUA·��
#define _LUA_KEY_ "6A68673107B8C5B829815A507FF5C274"   //LUA������Կ
#endif
#define _MAGIC_ITEM_             //��������
#define _ICONBUTTONS_				//ת��
#define _BATTLE_TIME_  99000    
#define _PET_2TRANS			// (�ɿ�) Change ����2ת
#define _DEBUGVER_    "2.2"    //DEBUG�汾��
#define _NEWSHOP_         //�̳�
#define _SHOWPETTRN_       //��ʾ����ת��
#ifdef _SA_MAC_VERSION_CONTROL
#define _SA_MAC_VERSION		"7sa2"
#endif
#define _CHANGETEAM_                //�ӳ��л�
#define SA_MUTE      "sa25.exe"
#define _NEW_CHARDATA_				//����������
#define _PETBLESS_					//����ף��
#define _RIDEPET_					//��迪��
#define DEF_APPNAME		"STONEAGE"	// ��Ϸ����
#define _RIDEQUERY_					//����ѯ
#define _CHAT_SPACING 24            //�����о����� 20
#define __EMOTION			//Cary ����ı��飬ֻ��client
//#define _PET_SKINS					//����Ƥ��
#define _PET_2TRANS			// (�ɿ�) Change ����2ת
#define	_NPC_EVENT_NOTICE			//npc������Ϣ��ʾ
#define _SHOWPETTRN_       //��ʾ����ת��
//#define _PET_VAL_COLOR_             //����������ɫ
#define _MO_CHAT_EXPRESSION			//������鹦��
#define _SA_LIAOTIAN_				//����ɾ����ť
#define _CHARTITLE_STR_             //���ֳƺ�     �óƺſ���,ͼ�γƺ�ʧЧ
#define _FONT_STYLE_                //���֘�ʽ����
#define _MESSAGE_FRONT_             //������Ϣǰ��Ӹ�����
#define _TRADITIONAL_LONG_         //����ϵͳ���������½
#define _FONTDATALEN_ 100           //������Ϣ���� 112
#define MAX_AIRPLANENUM				8
#define _FIX_CG_ATR_ICON
#define _PETSKILL_LER
//#define _CANCEL_FANTI				//ȡ�������л�
//#define _RED_MEMOY_				//���
#endif

#ifdef _MO_CHAT_EXPRESSION
#define CG_FIELD_CHAT_BTN_ON					55102
#define CG_FIELD_CHAT_BTN_OFF					55102
//#define EXPRESSION_NOID_START                   55300 //�����ͼ����ʼID
//#define EXPRESSION_NOID_END                     55421 //�����ͼ�Ž���ID
#define EXPRESSION_NOID_START                   55117 //�����ͼ����ʼID
#define EXPRESSION_NOID_END                     55215 //�����ͼ�Ž���ID
#define EXPRESSION_NOID_NUM       EXPRESSION_NOID_END-EXPRESSION_NOID_START
#define	_SUNDAY_STR_SEARCH			//SUNDAY�ַ��������㷨  ��KMP��ţ�ٶȸ�����㷨
#endif

