#ifndef DEFINE_H_
#define DEFINE_H_

#pragma once
//////////////////////////////////////////////////////////////////////////
// UPIM

#define UPIM_SOFT_NAME              _T("UPIM 2015")         // �������ʱ������ 
#define UPIM_REQ_COUNT              46
#define UPIM_REQ_BASE				5000					// �����׼
#define UPIM_REQ_CHECKPWD			UPIM_REQ_BASE+1			// �û���¼ 100
#define UPIM_REQ_GUSER				UPIM_REQ_BASE+2			// ������Ա��ȡ�������(�ҵĿͻ�/����) 5830
#define UPIM_REQ_GUSER2				UPIM_REQ_BASE+3			// ������Ա��ȡ�������(�ҵĿͻ�/����)_����ģʽJson
#define UPIM_REQ_LIST				UPIM_REQ_BASE+4			// �ͻ��õ�������Ա�б� 5720
#define UPIM_REQ_LIST2				UPIM_REQ_BASE+5			// �ͻ��õ�������Ա�б�_����ģʽJson
#define UPIM_REQ_DEPT				UPIM_REQ_BASE+6			// ������Ա��ȡ�����б� 5718
#define UPIM_REQ_GCINFO				UPIM_REQ_BASE+7			// �õ��̶������� 5782
#define UPIM_REQ_GCINFO2			UPIM_REQ_BASE+8			// �õ��̶�������_����ģʽJson
#define UPIM_REQ_GLIST				UPIM_REQ_BASE+9			// �ͻ��õ���������б� 5728
#define UPIM_REQ_SENDMSG			UPIM_REQ_BASE+10		// ��Ϣ����(�ͻ�������Ϣ��������-send) 5734
#define UPIM_REQ_S_SENDMSG			UPIM_REQ_BASE+11		// ��������Ϣ(��������������Ϣ-recive) 5736
#define UPIM_REQ_GCGETLIST			UPIM_REQ_BASE+12		// Ⱥ������,�õ���ϵ���б� 5788
#define UPIM_REQ_GCGETLIST2			UPIM_REQ_BASE+13		// Ⱥ������,�õ���ϵ���б�_����ģʽJson
#define UPIM_REQ_GCSENDMSG			UPIM_REQ_BASE+14		// Ⱥ�鷢����Ϣ 5796
#define UPIM_REQ_GCRECVMSG			UPIM_REQ_BASE+15		// Ⱥ�������Ϣ 5798
#define UPIM_REQ_GCCREATE			UPIM_REQ_BASE+16		// Ⱥ������,���� 5784
#define UPIM_REQ_GCADD				UPIM_REQ_BASE+17		// Ⱥ������,��ӳ�Ա 5786
#define UPIM_REQ_GCKICK				UPIM_REQ_BASE+18		// Ⱥ������,���� 5794
#define UPIM_REQ_GCLEAVE			UPIM_REQ_BASE+19		// Ⱥ������,�뿪 5790
#define UPIM_REQ_GCANNOUNCE			UPIM_REQ_BASE+20		// Ⱥ���淢��
#define UPIM_REQ_M_USERSTATE		UPIM_REQ_BASE+21		// �����û�״̬
#define UPIM_REQ_GPUBLIC            UPIM_REQ_BASE+22		// ��ȡ���ں�
#define UPIM_REQ_PUBLICINFO			UPIM_REQ_BASE+23		// ��ȡ���ں���Ϣ�����������·�ɣ�������������ʾ
#define UPIM_REQ_PUBCONCLOSE		UPIM_REQ_BASE+24		// �ͻ����˹��ںŶϿ�
#define UPIM_REQ_CONFIG				UPIM_REQ_BASE+25		// �ӷ�������ȡUPIM�ؼ����ÿ���
#define UPIM_REQ_USERINFO			UPIM_REQ_BASE+26		// �õ��û�����
#define UPIM_REQ_M_USERINFO			UPIM_REQ_BASE+27		// �����û�����
#define UPIM_REQ_RECONNECT			UPIM_REQ_BASE+28		// �û������ӣ���Ҫ����֪ͨ������
#define UPIM_REQ_S_GCADD			UPIM_REQ_BASE+29		// Ⱥ������,��ӳ�Ա��֪ͨ���û�(����)
#define UPIM_REQ_S_GCKICK			UPIM_REQ_BASE+30		// Ⱥ������,����֮��֪ͨ���û�(����)
#define UPIM_REQ_OLNOTIFY			UPIM_REQ_BASE+31		// �û�����֪ͨ 5754
#define UPIM_REQ_ONLINE				UPIM_REQ_BASE+32		// ��ѯ��ϵ��״̬ 5756
#define UPIM_REQ_S_ONLINE			UPIM_REQ_BASE+33		// �û�����״̬�ķ��������� 5758
#define UPIM_REQ_OFFMSG				UPIM_REQ_BASE+34		// ������Ϣ 5748
#define UPIM_REQ_KICKOFF			UPIM_REQ_BASE+35		// ͬһID��ص�¼֮�󣬷�������ǰһ��ID����Ϣ����ʾ����
#define UPIM_REQ_SVROFF				UPIM_REQ_BASE+36		// �������쳣�رգ���ÿһ������ID����Ϣ��֪ͨ�ͻ�����
#define UPIM_REQ_PKG				UPIM_REQ_BASE+37		// ���Ͱ�
#define UPIM_REQ_S_PKG				UPIM_REQ_BASE+38		// ��������ת��(��������)
#define UPIM_REQ_CHECK_USERSTATE    UPIM_REQ_BASE+39		// ���������Ϳͻ���ȷ����״̬(��������)
#define UPIM_REQ_ALLTGROOM			UPIM_REQ_BASE+40		// ȡ�����е�Ͷ��������
#define UPIM_REQ_ALLTGROOMEX		UPIM_REQ_BASE+41		// im2.0ȡ�����еķ���Ŷ�Ӧ�ķ���ʦ�б�
#define UPIM_REQ_ALLROOMTOUSER		UPIM_REQ_BASE+42		// im2.0ȡ�����еķ���Ŷ�Ӧ���û��б�
#define UPIM_REQ_GETGROUP			UPIM_REQ_BASE+43		// im2.0ȡ�����е��Զ��������Ϣ
#define UPIM_REQ_GETGUSER			UPIM_REQ_BASE+44		// im2.0ȡ�÷����¶�Ӧ���û��б�
#define UPIM_REQ_ADDGROUP			UPIM_REQ_BASE+45		// im2.0���/�޸��Զ��������Ϣ
#define UPIM_REQ_MODGUSER			UPIM_REQ_BASE+46		// im2.0���/�޸��û��ķ���

//////////////////////////////////////////////////////////////////////////
// UM_MSG
#define UM_USER_LOGIN				WM_USER + 1				// �û���¼�ɹ�
#define UM_USER_CLOSE				WM_USER + 2				// ������ر�
#define UM_USER_ADDGROUP			WM_USER + 3				// �����
#define UM_USER_SETSELFINFO			WM_USER + 4				// ��ʾ������Ϣ
#define UM_USER_ADDFRIEND			WM_USER + 5				// ��Ӻ����б�
#define UM_USER_OPENWND				WM_USER + 6				// �����촰��
#define UM_USER_ADDDEPT				WM_USER + 7				// ��Ӳ���
#define	UM_SOUND_PLAY				WM_USER + 8				// ����������Ϣ
#define UM_USER_ADDROOM				WM_USER + 9				// ���������/Ⱥ/������
#define	UM_USER_ADDROOMMEMBER		WM_USER + 10			// Ϊ��������ӳ�Ա
#define	UM_USER_LEAVEROOM			WM_USER + 11			// �˳�������
#define	UM_USER_KICKOK				WM_USER + 12			// ���˳ɹ�
#define	UM_USER_ADDPUBLIC			WM_USER + 13			// ��ӹ��ں�
#define UM_USER_OFFLINE				WM_USER + 14			// �û�����
#define UM_USER_ONLINE				WM_USER + 15			// �û�����
#define UM_USER_RECVMSG				WM_USER + 16			// �򿪵Ĵ����յ���Ϣ
#define	UM_USER_PUBLICINFO			WM_USER + 17			// �յ���̨�����Ĺ��ں���Ϣ
#define UM_USER_USERSTATE			WM_USER + 18			// �û�״̬�ı�
#define	UM_USER_ADDTGROOM			WM_USER + 19			// ���Ͷ�˶˷����б�
#define	UM_USER_STATECHANGE			WM_USER + 20			// ����״̬�ı�
#define UM_USER_HISMSG				WM_USER + 21			// �򿪵Ĵ����յ���Ϣ
#define UM_USER_HISANDRECVMSG		WM_USER + 22			// �򿪵Ĵ����յ���Ϣ
#define UM_USER_SHOWRECORD			WM_USER + 23			// ��ʷ��Ϣ
#define UM_USER_UISETINITSIZE		WM_USER + 24			// �ı�UI��С
#define	UM_USER_ADDTGROOM2			WM_USER + 25			// im2.0���Ͷ�˶˷����б�
#define	UM_USER_ADDROOMCLIENT		WM_USER + 26			// im2.0���Ͷ�˶˷�������Ŀͻ�
#define	UM_USER_ADDROOMANALYS		WM_USER + 27			// im2.0��ӿͻ��˷��������Ͷ��
#define	UM_USER_GETUSERPIC			WM_USER + 28			// im2.0�������õ��û�ͷ��
#define	UM_USER_ADDSELFGROUP		WM_USER + 29			// im2.0�����Զ������
#define	UM_USER_GETSELFPIC			WM_USER + 30			// im2.0�������õ��Լ���ͷ��
#define	UM_USER_OPENRIGHTS			WM_USER + 31			// im2.0�򿪿�ͨȨ�޴���
#define UM_USER_RIGHTHISMSG			WM_USER + 32			// im2.0�Ҳര�������ʷ��Ϣ
#define UM_USER_ADDHISTORYCLENT     WM_USER + 33            // im2.0���������ϵ�� 
#define WM_USER_FINDFRIEND          WM_USER + 34            // im2.0 ������ϵ��  wuchao add at 2016-04-05 
#define	UM_USER_ADDNEWPUBLIC		WM_USER + 35			// im3.0 ��IMϵͳ��ӹ��ں�
#define UM_USER_ADDNEWLASTUSER      WM_USER + 36
#define WM_IM_USERID                WM_USER + 4317          // upͶ����ʿ�ն�  �������ʦͷ��  �������ʦ�Ի���  

#define UM_UI_MESSAGELOOP			WM_USER + 100			// duilib��ͼ
#define UM_UI_TERM					WM_USER + 101			// duilib�رջ�ͼ

#define	UM_FEEDBACKMSG				WM_USER + 0x987			// �رս�ͼ��Ϣ
#define	UM_IMFEEDBACKMSG			WM_USER + 0x988			// �ⲿ������Ϣ
// WM_MSG
#define WM_NOTIFYICON				WM_USER + 1009			// ����ͼ����Ϣ
#define WM_MENUCLICK				WM_USER + 1010			// �������հ�ť��������Ϣ

#define WM_CHOOSEDATETIMEINHISTORYRECORD WM_USER + 1011      // ��������ɸѡ�����¼��Ϣ 


//////////////////////////////////////////////////////////////////////////
#define NOW_CVERSION		1.107			// �ͻ��˰汾��
#define NOW_VERSION			12				// Э��汾��
#define SEPARATOR_NUM		7654321
#define	VER_STARTYEAR		2015			// BuildNo��ʼ�������
#define GROUPNAME_SIZE		31				// �������ƴ�С
#define COMM_GROUP_COUNT	5				// һ��������(��ͨ�汾,����qq���ѷ���)
#define REQBUFFER_LEN		4*1024			// 4K,�������������С(20150116�޸�)
#define ANSBUFFER_LEN		32*1024			// 32K,Ӧ�����������С
#define PROXYBUFFER_LEN		4*1024			// 4K,������������
#define RICHEDIT_MAXLEN		1024			// ��������󳤶�1024

#define MAX_BUF_SEND_LEN	8*1024			// ���Ͱ���󻺴�
#define MIN_BUF_SEND_LEN	4*1024			// ���Ͱ���С����

#define MAX_LINK_NUM		30				// ���ݿ����ӳ����������
#define MAX_HOSTCOUNT		10				// ������������
#define MAX_DBCOUNT			5				// ���ݿ�������
#define MAX_IPWHITELIST     256             // IP������
#define	MAX_SERVER_NUM		20				// ��̨�������
#define MAX_MSG_LEN			2*1024			// �㲥��Ϣ��󳤶�
#define MAX_EMP_NUM			20000			// Ա��������
#define ONESECOND			1000			// 1��ĺ����������ڼ���ʾ
#define MAX_PIC_PIX			800				// ����ͼƬ���������
#define MAX_PIC_SIZE		800*1024		// ����ͼƬ������С

#define GCNT_MAX_COUNT		100				// �����¼����
#define USER_MAX_ROOM_COUNT 100				// ÿ���û���ӵ�е����Ⱥ����
#define MAX_ROOM_COUNT		100000			// �ܵ�Ⱥ����
#define REFRESH_GUSER_COUNT	50				// һ��ˢ��Ⱥ���û�����
#define REFRESH_TGUSER_COUNT 100			// һ��ˢ��Ͷ���û�����
#define REFRESH_GROOM_COUNT	10				// һ��ˢ��Ⱥ�����
#define GPUBLIC_COUNT	    10				// һ�λ�ȡ���ںŸ���

#define S_USERID_LEN		32
#define S_NICKNAME_LEN		32
#define S_USERNAME_LEN		32
#define S_USERPWD_LEN		48
#define S_MOBILE_LEN		16
#define S_EMAIL_LEN			16
#define S_SIGNATURE_LEN		128
#define S_FUNCCTRL_LEN		64
#define S_YYB_LEN			12
#define S_GROUPGG_LEN		128
#define S_ERRSTR_LEN		64
#define S_IDVEC_LEN			64

#define USERID_SIZE			32				// USERID��С
#define GUID_SIZE			16				// GUID����
#define SEND_MAXCOUNT		3				// ����ʹ���
#define SEND_TIMEOUT		30				// ���ͳ�ʱ
#define MAX_TEXT_LEN		2*1024			// 2KB,�����ı�����󳤶�(������Ϣ�ı�)
#define COMM_TEXT_LEN		400				// ��ͨ��Ϣ����
#define GROUPNAME_SIZE		31				// �������ƴ�С
#define ROOMNAME_SIZE		31				// Ⱥ�����ƴ�С
#define NOTE_SIZE			101				// Ⱥ����
#define TG_LAOSHINUM		10				// ����ʦ�������棬���������������ʦ��
#define TG_RECORD_NUM		20				// Ͷ�˶˴򿪵�ʱ����࿴��50����ʷ��Ϣ
#define TG_DISAPLY_NUM      20              // �����¼��ÿҳ��ʾ������ 
#define IMG_NAME_SIZE		360				// �û�ͷ���ļ�������
#define NODE_NAME_SIZE		64				// �û��ڵ�������
#define LAST_WORD_SIZE		128				// ��������¼չʾ��󳤶�
#define USERMRG_FENZU		10				// IM2.0 �ͻ������� ���������

#define MAX_STATE			10000			// ״̬����
#define MAX_GMSG			1//100			// ������Ϣ����
#define MAX_PMSG			10//1000		// ������Ϣ����
#define MAX_RMSG			500				// Ⱥ����Ϣ
#define MAX_HISMSG			1500			// ��ʷ��Ϣ����
#define MAX_OFFMSG			500				// ������Ϣ����
#define MAX_PRDTMSG			500				// ��Ʒ��Ϣ
#define MAX_ROOMOFFMSG		500             // Ⱥ��������Ϣ����
#define SHAKE_TIME_SPAN		25				// ���ڶ���sleep����
#define WLEN_TO_PIX			8				// �ַ���ת���س���

//////////////////////////////////////////////////////////////////////////
#define AP_SIZE				64				// 64�ֽڵ�AP��Ϣ
#define UORG_DEFID			0				// �û�����Ĭ��ID
#define UORG_SIZE			41				// �û�������󳤶�
#define UID_SIZE			41				// �û��ʺ���󳤶�
#define UNAME_SIZE			41				// �û�������󳤶�
#define UID_GSIZE			13				// �û��ʺ���󳤶�

#define	STR_SERVICE			_T("�ҵķ���")
#define	STR_CLIENT			_T("�ҵĿͻ�")
#define	STR_PRODUCT			_T("�ҵĲ�Ʒ")
#define	STR_FRIEND			_T("�ҵĺ���")
#define	STR_STRANGER		_T("İ����")
#define	STR_BLACKLIST		_T("������")
#define	STR_NOTIFY			_T("֪ͨ��Ϣ")
#define	STR_PUBLIC			_T("���ں�")
#define	STR_DEFAULT_FONT	_T("΢���ź�")
#define STR_NOCHECKPWD		_T("UPouter@nnn027")// �ⲿ��¼��־,��У������
#define DEFAULT_NOTE		_T("��ʱû�з�������")

#define UPIM_CLIENT_MUTEX   "UP_IM_MUTEX"
typedef long	IMGROUPID;			// �û�����id
typedef long	ROOMID;				// Ⱥ��������id
typedef int		PUBLICID;			// ���ں�id
typedef int		TGROOMID;			// Ͷ�˷���id
typedef LPSTR	LPUSERID;
typedef LPCSTR	LPCUSERID;

const int	MAX_SEND_BUF_LEN = 6*1024;		// ������󻺳���
const int	REFRESH_USER_COUNT = 50;		// һ��ˢ���û�����״̬���û�����
const int	USER_SIZE = REFRESH_USER_COUNT*(USERID_SIZE+1)+100;	// �û�����
const int	GROUPUSER_COUNT = 500;			// Ⱥ���������
const int	DATA_TRANSFER_UNIT = 3*1024;	// ͼƬ���ļ����͵�Ԫ
const int	IMAGE_TIMEOUT = 50;				// ͼƬ���䳬ʱ(��)

// ȫ�ִ�������
enum UPIM_ERRORCODE
{
	erError_None		= 0,								// �޴���
	//SERVER
	erServer_Error		= UPIM_REQ_BASE*100 + 1,			// �������쳣
	erServer_DBError	= UPIM_REQ_BASE*100 + 2,			// ���ݿ��쳣
	//UPIM_REQ_CHECKPWD
	erLogin_IDNotExist	= UPIM_REQ_CHECKPWD*100 + 2,		// �û���������
	erLogin_PswError	= UPIM_REQ_CHECKPWD*100 + 3,		// ���벻��ȷ
	erLogin_IsLogined	= UPIM_REQ_CHECKPWD*100 + 4,		// �û��Ѿ���¼
	erLogin_IPNotAllow	= UPIM_REQ_CHECKPWD*100 + 5,		// ��IP�������¼
	//UPIM_REQ_S_SENDMSG
	erLogin_SendMsgE	= UPIM_REQ_SENDMSG*100 + 1,			// ��������������Ϣʧ��
	//UPIM_REQ_S_SENDMSG
	erLogin_S_SendMsgE	= UPIM_REQ_S_SENDMSG*100 + 1,		// ������������Ϣʧ��
	//UPIM_REQ_RECONNECT
	erLogin_RC_IDNULL	= UPIM_REQ_RECONNECT*100 + 1,		// IDΪ��
	erLogin_RC_IPNotAllow	= UPIM_REQ_RECONNECT*100 + 2,	// IP�������¼
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// ö��
enum EUSERSTATE
{
	eUSER_ONLINE = 0,
	eUSER_OFFLINE,
	eUSER_LIKAI,
};

// ��ʱ��
enum ETIMER
{
	T_FLASHICON = 10,				// ͼ����˸
	T_DOCK,							// ����ͣ��
	T_OFFMSG,						// ������Ϣ
	T_REFRESHLIST,					// ˢ����ϵ���б�
	T_REFRESHSTATUS,				// ˢ������״̬
	T_REFRESHTRANSFER,				// ˢ���ļ�����
	T_QUERYTIMEOUT,					// ��ѯ��ʱ
	T_FILTERWORDS,					// ���˹ؼ���
	T_MSG_TIMEOUT,					// ��Ϣ��ʱ
	T_FILESVR_CONN,					// �ļ�������

	T_FLASHITEM,					// ����ͼ����˸
	T_SETSELFINFO,					// ������Ϣ����
	T_USERSTATUS,					// �û�״̬
	T_CHATBOX,						// ���촰�ڼ�ʱ
	T_REFRESH,						// ���촰��ͼƬˢ��
	T_NOTIFYICON,					// ����ͼ����˸
	T_CONNECT,						// ����ʦ�����Ӽ��
	T_RECORDSHOW,					// �ͻ�����ʷ��Ϣ��ʱ

	T_TRAY_HOVER_TIMER_ID ,         // �����ͣ����������      
	T_TRAY_LEAVE_TIMER_ID ,         // ����뿪����

	T_SHOW_MSGDIALOG,               // ����뿪���� ��괦����Ϣ��ʾ��֮��ʱ��һֱ��ʾ��ʾ�� 
};

// ��ʱ�����
enum ETIMER_ELAPSE
{
	eTE_FlashIcon		= 500,
	eTE_Dock			= 100,
	eTE_OffMsg			= 2500,
	eTE_RefreshStatus	= 20*1000,
	eTE_RefreshTransfer	= 1000,
	eTE_QueryTimeout	= 3000,
	eTE_MsgTimeout		= 5000,
	eTE_FileSvr			= 2*60*1000,

	eTE_FlashItem		= 150,
	eTE_Setselfinfo		= 1000,
	eTE_UserStatus		= 1000,
	eTE_Chatbox			= 500,
	eTE_Refresh			= 1500,
	eTE_NotifyIcon		= 500,
	eTE_Connect			= 20*1000,
	eTE_RecordShow		= 300,
};

enum EVTTYPE
{
	eVT_Friend = 0,					// ���Ѽ���
	eVT_Group,						// Ⱥ�鼯��
	eVT_Recent,						// �����ϵ�˼���
};

enum EUITYPE
{
	eUI_Group = 0,					// Group
	eUI_Member = 1,					// Member
	eUI_Recent=2,					// Recent
};

enum NICKTYPE
{
	eNICK_nameandid=0,				// �ǳ�(ID)
	eNICK_id = 1,					// ID
	eNICK_name = 2,					// �ǳ�	
};

enum EDIALOGTYPE
{
	eDIALOG_Single = 0,				// ��������
	eDIALOG_Group = 1,				// Ⱥ������
	eDIALOG_Team = 2,				// ������
	eDIALOG_Public = 3,				// ���ں�
	eDIALOG_GroupSend = 4,			// ��ϢȺ��
	eDIALOG_ChatTG = 5,				// Ͷ�˶�-�ͻ��������
	eDIALOG_Analys = 6,				// Ͷ�˶�-����ʦ�������
	eDIALOG_RYPublic = 7,				// ��IMϵͳ-�ͻ��������
};

enum EMSGOPENTYPE
{
	eMSG_Single = 0,				// ��������
	eMSG_Group = 1,					// Ⱥ������
};

enum NEWIMCATEGORYID
{
	newMSG_PRIVATE  = 1    ,   // ����
	newMSG_DISCUSSION      ,   // ������
	newMSG_GROUP           ,   // Ⱥ��
	newMSG_CHATROOM        ,   // ������
	newMSG_CUSTOMERSERVICE ,   // �ͷ�
	newMSG_SYSTEM          ,   // ϵͳ��Ϣ
	newMSG_MC              ,   // MC��ϢӦ�ù��ڷ���
	newMSG_MP              ,   // MP��Ϣ���ڷ���ƽ̨
};
enum NEWIMTRANSFERTYPE
{
	newMSG_S = 1,  // ��Ϣ���ݷ����������棬����֤��Ϣ������շ�
	newMSG_N    ,  // ��Ϣ���ݷ��������棬���������յ�֪ͨ��Ϣ
	newMSG_P    ,  // ��Ϣ���ݷ��������棬�����������߻��յ�PUSH��Ϣ

};
// ö��
enum ECREATEDIALOGTYPE
{
	eCreate_LoginIn = 0,			// ������¼��
	eCreate_Group,					// ����Ⱥ��
	eCreate_Team,					// ����������
	eCreate_Node,					// ��������
	eCreate_Public,					// �������ں�
	eCreate_TG1,					// TG1
	eCreate_TG2,					// TG2
};

// ��¼����
enum ELOGINTYPE
{
	eLogin_Emp = 0,					// Ա����¼
	eLogin_Client = 1,				// �ͻ���¼
	eLogin_EmpSpecial=2,			// Ա�������¼(��У������)
	eLogin_ClientWeb = 3,			// �ͻ�web��¼
	eLogin_ClientNeedPwd=4,			// �����齻���汾��¼����Ҫ�����������У�� 
	eLogin_Comm = 8,				// ��ͨ��¼
	eLogin_FileSvr = 10,			// �ļ�������
	eLogin_UPClient = 11,			// up�ͻ���¼,��У������
	eLogin_Analyst = 12,			// ����ʦ��¼
	eLogin_KF = 13,					// �����¿ͻ��˵�½
};

// �û�����
enum EUSERTYPE
{
	eUser_All=-1,
	eUser_Client=0,					// �ͻ�
	eUser_Broker=1,					// Ͷ��
	eUser_Agent=2,					// ��ϯ

	eUser_UPClient=3,				// Ƕ�ڿͻ����е�Ͷ�˽���
	eUser_UPAnalyst=4,				// ����ʦ��¼

	eUser_UPClient2=5,				// im2.0�����������û�����
	eUser_UPAnalyst2=6,				// im2.0����ʦ��¼

	eUser_Product=7,				// ��Ʒ
	eUser_Comm=8,
	eUser_UPExe = 9 ,               // im2.0 ��UPͶ������ʹ��  �ṩEXE��ʽ  ����ʾ����ͼ�� 
	eUser_Unknow=10,
	eUser_UPRYExe = 11 ,               // im3.0 ��UP  �ṩEXE��ʽ  ��������
};


//����������
enum enumQuoterType
{
	Quoter_NULL=0,
	Quoter_TP=100,					//���ģ����Ϣ�������±����ã��÷����ṩ�������û�������Ϣ���ϴ���Զ�˵�״̬������
	Quoter_TS=101,					//���ģ����Ϣ�������±����ã��÷����ṩ�������û�������Ϣ�����ݴ�Զ�˵�״̬������
};

// �û�״̬
enum MYSTATE 
{
	MYSTATE_OFFLINE,				// ����
	MYSTATE_NORMAL ,				// ����
	MYSTATE_HIDE,					// ����
	MYSTATE_LEAVE,					// �뿪
};

// ��������
enum EGROUPTYPE
{
	eList_Friend		= 0,		// һ����ѷ���(ͨ�ð汾)

	eList_TopGroup		= 1,		// �ö���(�ͻ��汾)
	eList_YybGroup		= 2,		// Ӫҵ������(�ͻ��汾)
	eList_SrvGroup		= 3,		// �������(�ͻ��汾�ķ������)

	eList_Dept			= 4,		// ����Ա������(����汾�д���,������Ѷ���Ա��)
	eList_ClientDefGrp	= 5,		// �ͻ��Զ�����(����汾�д���,������Ѷ��ǿͻ�)
	eList_ClientGrp		= 6,		// �ͻ�����(����汾��ֱ�ӴӶ�Ӧ��ϵ��ȡ����ά��,������Ѷ��ǿͻ�)
	eList_ClientDefGrp2 = 9,		// �ͻ��Զ�����(����汾��ֱ�ӴӶ�Ӧ��ϵ��ȡ����ά��,������Ѷ��ǿͻ�,relation2�ֶ���ʾ�ͻ��ķ���ID)

	eList_ProductGrp	= 7,		// ��Ʒ����
	eList_Agent			= 8,		// ��ϯ�汾��ȡ��ϯ����
	eList_Public		= 10,		// ���ں�
};

// ����ID
enum GROUP_INDEX 
{
	GROUP_FRIEND = 1,				// �ҵĺ���
	GROUP_STRANGER = 2,				// İ����
	GROUP_BLACKLIST = 3,			// ������
	GROUPID_BEGIN = 3,
	GROUPID_END = GROUPID_BEGIN+COMM_GROUP_COUNT,

	GROUPID_CLIENT = 9,				// �ҵĿͻ� 9
	GROUPID_SERVICE = 10,			// �ҵķ���
	GROUPID_AGENT = 11,				// ��ϯ����
	GROUPID_PRODUCT = 20,			// �ҵĲ�Ʒ 20
};


// Ⱥ������
enum E_GROUPCHAT_TYPE
{
	eCR_None = 0,					// ��Ⱥ������,����
	eCR_Group = 1,					// �ڲ�Ⱥ��(Ա��Ⱥ��),��QQȺ��һ��
	eCR_Group_Client = 2,			// �ⲿȺ��(�ͻ�Ⱥ��)
};

// ��Ϣ��������
enum E_MSGSEND_TYPE
{
	eMsgSend_Normal=0,				// ��ͨ����
	eMsgSend_Shift=1,				// ��Ϣת��( A-->B,B(A)-->C ,A��B������Ϣ��B��A����Ϣת��C)
	eMsgSend_Public=2,				// ���ں���Ϣ
	eMsgSend_Prdt=7,				// ��Ʒ��Ϣ
	eMsgSend_PrdtFile=8,			// ��Ʒ�ļ�
	eMsgSend_Analyst=9,				// ����ʦ��Ϣ���뷿�����
	eMsgSend_NewPublic=10
};

//֪ͨ��Ϣ������
enum ENOTIFY_TYPE
{
	eMsg_System_Notify=0,			// ϵͳ֪ͨ
	eMsg_PDb,						// �������ݿ���Ϣ
	eMsg_GDb,						// �����ݿ���Ϣ
};

// ��Ϣ�ı���ʽ
enum EMSGTEXTFORMAT
{
	eMsgFormat_Txt=0,				// ���ı�txt
	eMsgFormat_Def=2,				// �Զ����ʽ(�Զ���xml)
	eMsgFormat_File=3,				// �ļ���Ϣ
	eMsgFormat_DbMsg=4,				// ���ݿ���Ϣ
	eMsgFormat_OutRoom=5,			// �ⲿȺ����Ϣ
	eMsgFormat_System=6,			// ϵͳ��Ϣ(��ʾ�ڸ�������Ի�������)
	eMsgFormat_Shake=7,				// ���ڶ���
	eMsgFormat_PrdtFile=8,			// ��Ʒ�ļ�
	eMsgFormat_OffimageReceipt=9,   // ��ͼ��ִ(���ڷ���������Ϣ��,ʹ���ܹ��鿴������ͼ)
	eMsgFormat_Prdt=10,				// ��Ʒ��Ϣ
	eMsgFormat_AutoReply=11,        // �뿪״̬���Զ��ظ�
	eMsgFormat_FileBtSend=12,		// ��Ʒ����Ⱥ����Ʒ�ļ�		
};

enum E_CHATRECORD_TYPE
{
	eRecord_Single=0,				// ������Ϣ
	eRecord_Group,					// Ⱥ����Ϣ
	eRecord_Sys,					// ϵͳ��Ϣ
	eRecord_GS,						// ��ʽ
	eRecord_BM,						// ����
	eRecord_GPC,					// ��Ʊ��
	eRecord_JYXH,					// �����ź�
	eRecord_Public,					// ���ں���Ϣ
	eRecord_TgRoom,					// Ͷ����������Ϣ
	eRecord_NewPublic,					// ���ں���Ϣ
};

// �������
enum EPANELTYPE
{
	ePanel_Single=0,				// �ͻ�
	ePanel_Group=1,					// Ⱥ��
	ePanel_Recent=2,				// �����ϵ��
};

// �ڵ�����
enum ENODETYPE
{
	eNode_Node=0,					// �ڵ�
	eNode_None,						// �ǽڵ�

	eNode_Single,					// ����
	eNode_Group,					// Ⱥ��
	eNode_Recent,					// �����ϵ��
	eNode_Public,					// ���ں�
	eNode_Analyst,					// ����ʦ����
	eNode_RYPublic,					// ���ƹ��ں�
};

// �ڵ�����
enum EADDIDTYPE
{
	eAdd_No=0,						// 
	eAdd_Exist,						// �Ѵ��ڵ�
	eAdd_New,						// �¼����
};

enum EMSGDATAERROR
{
	eMsgData_Suc = 0,		
	eMsgData_Null = 1,				// Ϊ��
	eMsgData_TextMax = 2,			// �ı�̫��
	eMsgData_ImgMax = 3,			// ͼƬ��������
	eMsgData_Xml=4,					// ����xml����
	eMsgData_OfflineImg=5,			// ���߲��ܷ���ͼƬ
};


enum E_GROUPCHAT_ERROR
{
	eGCError_NoDefine = -9999,		// δ����Ĵ�������
	eGCError_Success = 0,			// �ɹ�
	eGCError_DbCon = -1,			// û�п��õ����ݿ�����	 
	eGCError_DbExe = -2,			// ���ݿ�ִ��ʧ��
	eGCError_DbOp = -3,				// ���ݿ����ʧ��
	eGCError_RoomType = -4,			// �޴�Ⱥ������
	eGCError_UpUserMax = -5,		// Ⱥ��������
	eGCError_Delete = -6,			// ��Ⱥ�ѱ�ɾ��
	eGCError_RsClose = -7,			// ��¼���ѹر�
	eGCError_RsNULL = -8,			// ��¼��Ϊ��
	eGCError_DbClose = -9           // ���ݿ�ر�
};


enum  UPIM_PROTOCOL
{
	UPIM_FILE_TRANSFER = 2,			// �ͻ��������ļ�
	UPIM_FILE_TRANSFER_DATA = 3,	// �����ļ�����
	UPIM_FILE_TRANSFER_CANCEL = 4,	// ȡ���ļ�����
	UPIM_FILE_QUERY = 5,			// ��ѯ�������

	UPIM_MSG_PKG_TRANSFER = 9,		// ������Ϣ����Э��(����ͼ��)
	UPIM_TRADE_TRANS = 10,			// ���ײ�ѯ����(�����˲�ѯ�ͻ��ֲ�,��ѡ�ɵ�)
	UPIM_TRADE_TRANS_DATA = 11,		// ���ײ�ѯ����
	UPIM_TRADE_REJECT = 13,			// ���ײ�ѯ�ܾ�

	UPIM_BROKER_SPEC_DATA = 12,		// �������������ݴ���(��������ͻ����͹�Ʊ��,���׼ƻ���)

	//�����������Э��
	UPIM_PICTURE_CHANGE = 30,		// ֪ͨ��ϵ�˸ı��˸�������
	UPIM_CHECK_PICTURE = 31,		// ��ѯ��ϵ�˵ĸ��������Ƿ������
	UPIM_SEND_MYPICTURE = 32,		// �����ҵĸ����������ϵ��

	//////////////////////////////////////////////////////////////////////////
	// ֱ�������������
	UPIM_OFFFILE = 61,				// �����ļ�����
	UPIM_OFFFILE_DATA = 62,			// �����ļ���������
	UPIM_OFFFILE_CANCEL = 63,			// �����ļ�ȡ��
	UPIM_OFFFILE_DEL = 64,			// �����ļ�ɾ��
};

#endif