#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "define.h"
//////////////////////////////////////////////////////////////////////////
#pragma pack(push,1)
//���ֽڶ���
typedef struct tagIMReqHeader
{
	struct
	{
		unsigned char Version;		//:4;
		unsigned char Compressed;	//:1;
		unsigned char Encrypted;	//:1;
		unsigned char Reserved;		//:2;
	}	Info;
	unsigned long  PacketLen;
	unsigned long  RawLen;
	char  Priority;
} IMREQHEADER;

typedef struct tagIMAnsHeader
{
	long		   Separator;
	unsigned long  PacketLen;
	unsigned long  RawLen;
	struct
	{
		unsigned char Version;		//:4;
		unsigned char Compressed;	//:1;
		unsigned char Encrypted;	//:1;
		unsigned char Reserved;		//:2;
	}	Info;
	char	Priority;
	long	ErrorCode;				// ������Ϣ
	long	req;
} IMANSHEADER;

#ifdef _NEW_HEADER
typedef struct tagIMReqHeader
{
	union
	{
		unsigned long dwcrc;
		char newversion[4];
	};
	struct
	{
		unsigned char Version;		//:4;
		unsigned char Compressed;	//:1;
		unsigned char Encrypted;	//:1;
		unsigned char Reserved;		//:2;
	}	Info;
	DWORD	cookie;
	long	MainID;
	long	AssisID;
	unsigned long  PacketLen;
	unsigned long  RawLen;
	char  Priority;
} IMREQHEADER;

typedef struct tagIMAnsHeader
{
	union
	{
		unsigned long dwcrc;
		char newversion[4];
	};
	long		   Separator;
	unsigned long  PacketLen;
	unsigned long  RawLen;
	struct
	{
		unsigned char Version;		//:4;
		unsigned char Compressed;	//:1;
		unsigned char Encrypted;	//:1;
		unsigned char Reserved;		//:2;
	}	Info;
	DWORD	cookie;
	long	MainID;
	long	AssisID;
	char	Priority;
	long	req;
} IMANSHEADER;
#endif // _NEW_HEADER

typedef struct 
{
	IMREQHEADER		ReqHeader;
	char			ReqBuffer[REQBUFFER_LEN];
} IMREQBUFFER;

typedef struct 
{
	IMANSHEADER		AnsHeader;
	char			AnsBuffer[ANSBUFFER_LEN];
} IMANSBUFFER;

//////////////////////////////////////////////////////////////////////////
//�û���¼(100)_req
//UPIM_REQ_CHECKPWD
struct login_req
{
	short	req;
	short	usertype;						//�û�����
	char	userid[S_USERID_LEN];			//��¼�˺�/�ͻ���
	char	userpwd[S_USERPWD_LEN];			//��¼����
};

//�û���¼(100)_ans
//UPIM_REQ_CHECKPWD
struct login_ans
{
	char	userid[S_USERID_LEN];			// �û��˺�
	char	username[S_USERNAME_LEN];		// �û�����
	short	role;							// ��ɫ
	char	useryyb[S_YYB_LEN];				// Ӫҵ��
	short	sex;							// �Ա�1��2Ů0δ֪
	char	yyb[S_YYB_LEN];					// ��ʵӪҵ��
	short	deptid;							// ����id	
	char	funcctrl[S_FUNCCTRL_LEN];		// �������Կͻ��Ĺ��ܿ���
	char	signature[S_SIGNATURE_LEN];		// ����ǩ��
};

//������Ա(5830)_req
//UPIM_REQ_GUSER
struct guser_req
{
	short	req;
	char	userid[S_USERID_LEN];			// ��¼�˺�/�ͻ���
	short   ntype;							// ����
	short	ngroupid;						// ����ID
	short	nLevel;							// **��ɾ��
	short	ndeptid;						// **��ɾ��
};

//���ѽṹ
struct guser_unit
{
	char	userid[S_USERID_LEN];			// �û��˺�
	char	username[S_USERNAME_LEN];		// �û�����
	short	sex;							// �Ա�1��2Ů0δ֪
	short	state;							// ����״̬
	char	mobile[S_MOBILE_LEN];			// �ֻ�
	char	signature[S_SIGNATURE_LEN];		// ����ǩ��
};

//������Ա(5830)_ans
//UPIM_REQ_GUSER
struct guser_ans
{
	short	rtnnum;							// ���ظ���
	short   ntype;							// ����
	short	ngroupid;						// ����ID
	struct	guser_unit headp[1];			// ��������ͷ	
};

//������Ա(5830)_ans
//UPIM_REQ_GUSER2
struct guser_ans2
{
	short	rtnnum;							// ���ظ���
	short   ntype;							// ����
	short	ngroupid;						// ����ID
	int		nlen;							// ����char����
	char	headp[1];						// ����json	
};

//��Ϣ����(5734)_req
//UPIM_REQ_SENDMSG
struct sendmsg_req
{
	short	req;
	char	cFromuserid[S_USERID_LEN];		// �������˺�
	DWORD	dwMsgSeq;						// ��Ϣ����
	short	nUsertype;						// �û�����
	char	cTouserid[S_USERID_LEN];		// �������˺�
	time_t	tmSend;							// ��Ϣ����ʱ��
	BYTE	ucMsgType;						// ��Ϣ����
	char	innerID[S_USERID_LEN];			// �ڲ�ID
	int		nPublicID;						// ���ں�ID
	int		nRouteID;						// ·�����
	int		format;							// ��Ϣ�ĸ�ʽ EMSGTEXTFORMAT
	int		msglen;							// ��Ϣ��,���Ը��ı�������
	char	msg[1];							// �û����͵���Ϣ	
};

//���ݰ����ͣ�5766��_req
//UPIM_REQ_PKG
struct send_pkg_req
{
	short	req;
	char	cFromuserid[S_USERID_LEN];		// �������˺�
	short	nUsertype;						// �û�����
	char	cTouserid[S_USERID_LEN];		// �������˺�
	int		nrequest;						// ����������ǻ�Ӧ��
	int		pkglen;							// ��Ϣ��,���Ը��ı�������
	char	pkg[1];							// �û����͵���Ϣ
};

struct s_send_pkg_ans
{
	char	cFromuserid[S_USERID_LEN];		// �������˺�
	short	nUsertype;						// �û�����
	int		nrequest;						// ����������ǻ�Ӧ��
	int		pkglen;							// ��Ϣ��,���Ը��ı�������
	char	pkg[1];							// �û����͵���Ϣ
};

// �㲥����
struct broadcast_req
{
	int	type;								// �㲥����
	char nickname[S_NICKNAME_LEN];			// �������ǳ�
	char toid[64];							// ������
	long msglen;							// ��Ϣ����
	char msg[1];							// �㲥����
};

struct sendmsg_ans
{
	char	cTouserid[S_USERID_LEN];		// �������˺�
	int		nUserState;						// �û�����״̬
	DWORD	dwMsgSeq;						// ��Ϣ����
	time_t	tmSend;							// ��Ϣ����ʱ��
};


//��������Ϣ����(5737)_req
//UPIM_REQ_S_SENDMSG
struct s_sendmsg_ans
{
	char	cFromuserid[S_USERID_LEN];		// �������˺�
	DWORD	dwMsgSeq;						// ��Ϣ����
	BYTE	ucMsgType;						// ��Ϣ����
	char	innerID[S_USERID_LEN];			// �ڲ�ID
	int		format;							// ��Ϣ�ĸ�ʽ EMSGTEXTFORMAT
	time_t	tmSend;							// ��Ϣ����ʱ��
	int		nPublicID;						// ���ں�ID
	int		msglen;							// ��Ϣ��,���Ը��ı�������
	char	msg[1];							// �û����͵���Ϣ
};

//������Ա(5827)_req
//UPIM_REQ_GLIST
struct glist_req
{
	short	req;
	char	userid[S_USERID_LEN];			// ��¼�˺�/�ͻ���
	short	ngrouptype;						// ����ID
};

// ����
struct  glist_unit
{
	DWORD	m_nGroupID;
	char	m_szGroupName[GROUPNAME_SIZE];
	BYTE	m_ucGroupType;
};

//������Ա(5827)_ans
//UPIM_REQ_GLIST
struct glist_ans
{
	short	rtnnum;							// ���ظ���
	struct	glist_unit headp[1];			// ��������ͷ	
};

//�õ���ϵ���б�(5720)_req
//UPIM_REQ_LIST
struct list_req
{
	short	req;
	char	userid[S_USERID_LEN];			// ��¼�˺�/�ͻ���
	short	ngrouptype;						// ����ID
};

//���ѽṹ
struct list_unit
{
	char	userid[S_USERID_LEN];			// �û��˺�
	char	username[S_USERNAME_LEN];		// �û�����
	short	sex;							// �Ա�1��2Ů0δ֪
	short	relation;						// ��ϵ����
	short	state;							// ����״̬
	char	signature[S_SIGNATURE_LEN];		// ����ǩ��
};

//�õ���ϵ���б�(5720)_ans
//UPIM_REQ_LIST
struct list_ans
{
	short	rtnnum;							// ���ظ���
	struct	list_unit headp[1];				// ��������ͷ	
};

struct list_ans2
{
	int  len;
	char headp[1];							// ����json	
};

//�õ������б�(5718)_req
// UPIM_REQ_DEPT
struct dept_req
{
	short	req;
	char	userid[S_USERID_LEN];			// ��¼�˺�/�ͻ���
	short	ndeptid;						// ����ID
};

//���Žṹ
struct dept_unit
{
	short	deptid;							// deptid
	char	deptname[S_USERID_LEN];			// ��������
	short	predept;						// ������
};

//�õ���ϵ���б�(5718)_ans
//UPIM_REQ_DEPT
struct dept_ans
{
	short	rtnnum;							// ���ظ���
	struct	dept_unit headp[1];				// ��������ͷ	
};

//�õ�Ⱥ���б�(5782)_req
// UPIM_REQ_GCINFO
struct gcinfo_req
{
	short	req;
	char	userid[S_USERID_LEN];			// ��¼�˺�/�ͻ���
	short	type;							// �Ƿ��ǿͻ���
	long	RoomId;							//
	short	Roomtype;						// 
};

//Ⱥ��ṹ
struct gcinfo_unit
{
	long	RoomId;							// Ⱥ��id
	short	Roomtype;						// Ⱥ������
	char	masterid[S_USERID_LEN];			// �������˺�/�ͻ���
	char	Roomname[S_USERID_LEN];			// Ⱥ������
	char	RoomNote[NOTE_SIZE];			// Ⱥ����(101����)
	short	delflag;						// ���(ɾ��)
};

//�õ�Ⱥ���б�(5782)_ans
// UPIM_REQ_GCINFO
struct gcinfo_ans
{
	short	rtnnum;							// ���ظ���
	struct	gcinfo_unit headp[1];			// ��������ͷ	
};

//�õ�Ⱥ���б�(5782)_ans_JSON
// UPIM_REQ_GCINFO2
struct gcinfo_ans2
{
	short	rtnnum;							// ���ظ���
	int		nlen;							// ����char����
	char	headp[1];						// ����json	
};

// �������Ⱥ��֮��Ĳ���
// UPIM_REQ_S_GCADD
struct gc_s_add_ans
{
	int		nlen;							// ����char����
	char	headp[1];						// ����json	
};


//�õ�Ⱥ���б�(5788)_req
// UPIM_REQ_GCGETLIST
struct gcgetlist_req
{
	short	req;
	long	RoomId;							// Ⱥ��ID
	short	Roomtype;						// Ⱥ������
	int     nStartPos;						// ��ʼ��ţ�����һ��ȡ������
};

//Ⱥ���Ա�ṹ
struct gcgetlist_unit
{
	char	userid[S_USERID_LEN];			// Ⱥ��Ա�˺�/�ͻ���
	short	usertype;						// �û�����
	short	state;							// �û�����״̬
};

//�õ�Ⱥ���б�(5788)_ans
// UPIM_REQ_GCINFO
struct gcgetlist_ans
{
	long	RoomId;							// Ⱥ��id
	int		nStartPos;						// ��ʼ���
	short	rtnnum;							// ���ظ���
	struct	gcgetlist_unit headp[1];		// ��������ͷ	
};


// Ⱥ�鷢����Ϣ(�ı�)(5796)_req
// UPIM_REQ_GCSENDMSG
struct gcsendmsg_req
{
	short	req;
	DWORD	dwMsgSeq;						// �����к�
	char	cFromuserid[S_USERID_LEN];		// ������userid
	short	nUsertype;						// �û�����
	char	nickname[S_NICKNAME_LEN];		// �������ǳ�
	ROOMID	roomid;							// ������id
	int		roomtype;						// ����������
	time_t	tmSend;							// ����ʱ��
	int		format;							// ��Ϣ��ʽ
	int		msglen;							// ����
	char	msg[1];							// ����
};

// Ⱥ�������Ϣ(�ı�):����������
struct GROUP_CHAT_HIS_MSG
{
	char	cFromuserid[S_USERID_LEN];		// ������userid
	char	nickname[S_NICKNAME_LEN];		// �������ǳ�
	BYTE	usertype;						// �û�����
	ROOMID	roomid;							// ������id
	int		roomtype;						// ����������
	time_t	tmSend;							// ����ʱ��
	int		format;							// ��Ϣ��ʽ
	int		msglen;							// ����
	char	*msg;							// ����
};

// Ⱥ�鷢����Ϣ(�ı�)(5796)_ans
// UPIM_REQ_GCSENDMSG
struct gcsendmsg_ans
{
	long	RoomId;							// Ⱥ��id
	short	Roomtype;						// Ⱥ������
	DWORD	dwMsgSeq;						// ��Ϣ����
	time_t	tmSend;							// ��Ϣ����ʱ��
};

// Ⱥ�鷢����Ϣ(�ı�)(5798)_ans
// UPIM_REQ_GCRECVMSG
struct gcrecvmsg_ans
{
	char	cFromuserid[S_USERID_LEN];		// ������userid
	char	nickname[S_NICKNAME_LEN];		// �������ǳ�
	short	nUsertype;						// �û�����
	ROOMID	roomid;							// ������id
	short	roomtype;						// ����������
	time_t	tmSend;							// ����ʱ��
	int		format;							// ��Ϣ��ʽ
	int		msglen;							// ����
	char	msg[1];							// ����
};

// �����Ҵ���(5784)_req
//UPIM_REQ_GCCREATE
struct gccreate_req
{
	short	req;
	char	createuserid[S_USERID_LEN];		// ������id
	char	roomname[S_NICKNAME_LEN];		// ����������
	short	roomtype;						// ����������
	int		nroomParam;						// ��������б����
};

// �����Ҵ���(5784)_ans
//UPIM_REQ_GCCREATE
struct gccreate_ans
{
	bool	bSussess;						// �Ƿ�ɹ�
	ROOMID	nRoomID;						// �����ɹ��ķ���id
	int		nroomParam;						// ��������б����
	char	ErrStr[S_ERRSTR_LEN];			// ������Ϣ
};

// ��������ҳ�Ա(5786)_req
// UPIM_REQ_GCADD
struct gcadd_req
{
	short	req;
	ROOMID	nRoomID;						// ����id
	short	roomtype;						// ����������

	int		szlen;							// ����
	char	szUpID[1];						// ��ԱID����
};

// ��������ҳ�Ա(5786)_ans
// UPIM_REQ_GCADD
struct gcadd_ans
{
	ROOMID	nRoomID;						// ����id
	short	roomtype;						// ����������
};

// UPIM_REQ_GCKICK
// �߳������ҳ�Ա(5794)_req
// UPIM_REQ_GCLEAVE
// �����˳�������(5790)_req
struct gcleave_req
{
	short	req;
	ROOMID	nRoomID;						// ����id
	short	roomtype;						// ����������
	char	userid[S_USERID_LEN];			// id
	short	nUsertype;						// �û�����
};

// UPIM_REQ_GCKICK
// �߳������ҳ�Ա(5794)_ans
// UPIM_REQ_GCLEAVE
// �����˳�������(5790)_ans
struct gcleave_ans
{
	bool	bSussess;						// �Ƿ�ɹ�
	ROOMID	nRoomID;						// ����id
	char	userid[S_USERID_LEN];			// id
	short	nUsertype;						// �û�����
	char	ErrStr[S_ERRSTR_LEN];			// ������Ϣ
};

// UPIM_REQ_S_GCKICK
// ���߳�������_ans
struct gckick_s_ans
{
	ROOMID	nRoomID;						// ����id
	short	roomtype;						// ����������
	char	KickId[S_USERID_LEN];			// KickId
};

// UPIM_REQ_GPUBLIC
// ��ȡ���ں�
struct public_req
{
	short   req;
	char	userid[S_USERID_LEN];			// id
	short	nUsertype;						// �û�����
};

struct public_ans
{
	int	 rtnnum;							// ���ظ���
	int  len;								// ����
	char headp[1];							// ����json	
};

// UPIM_REQ_PUBLICINFO
// ��ȡ���ں���Ϣ�����������·�ɣ�������������ʾ
struct publicinfo_req
{
	short   req;
	int		publicID;						// publicID
};

struct publicinfo_ans
{
	int		publicID;
	int		rtnnum;							// ���ظ���
	int		len;							// ����
	char	headp[1];						// ����json	
};

// UPIM_REQ_PUBCONCLOSE
// �ͻ��Ͽ��빫�ںŵĶԻ�
struct pubconclose_req
{
	short   req;
	int		publicID;						// ���ں�ID
	int		routeID;						// ·��ID
	char	userid[S_USERID_LEN];			// �Լ���ID
	char	SevcId[S_USERID_LEN];			// �ͷ���ԱID
	int		closeType;						// �ر�����(0:��ʱ�Ͽ���1:�����رգ�2:�������)
};

// UPIM_REQ_M_USERINFO
// �޸��û�����
struct m_userinfo_req
{
	short   req;
	int		len;							// ����
	char	headp[1];						// ����json	
};

// UPIM_REQ_RECONNECT
// �û��������ӷ��������跢��֪ͨ
struct reconnect_req
{
	short   req;
	char	userid[S_USERID_LEN];			// id
	short	nUsertype;						// �û�����
};

// �û��������ӷ����������ذ�
struct reconnect_ans
{
	int		nResult;						// �ص�¼���ؽ��
	int		nErrorCode;						// �û���������
};

// UPIM_REQ_S_ONLINE
// ���������͵��û�������Ϣ 
struct online_s_ans
{
	short   req;
	char	userid[S_USERID_LEN];			// id
	short	nUserstate;						// �û�״̬
};

// UPIM_REQ_OLNOTIFY
// �޸��û�״̬�ı�����
struct olnotify_req
{
	short   req;
	char	userid[S_USERID_LEN];			// id
	short	nUserstate;						// �û�״̬
	int		len;							// ����
	char	headp[1];						// ����json	
};

// UPIM_REQ_OFFMSG
// �û���¼֮��ȡ��������Ϣ
struct offmsg_req
{
	short   req;
	char	userid[S_USERID_LEN];			// id
	short	nUsertype;						// �û�����
};

// json��ʽ��������Ϣ
struct offmsg_ans
{
	int		rtnnum;							// ���ظ���
	int		len;							// ����
	char	headp[1];						// ����json	
};

// UPIM_REQ_KICKOFF
// ͬһID��ص�¼֮�󣬷�������ǰһ��ID����Ϣ����ʾ����
struct kickoff_msg
{
	int		nMsg;							// ��������
};

// UPIM_REQ_SVROFF
// �������쳣�رգ���ÿһ������ID����Ϣ��֪ͨ�������ر�
struct svroff_msg
{
	int		nMsg;							// �ر�����
};

// UPIM_REQ_ALLTGROOM
// ��ȡͶ��������
struct alltgroom_req
{
	short   req;
	char	userid[S_USERID_LEN];			// id
	short	nUsertype;						// �û�����
};

// UPIM_REQ_ALLTGROOMEX
// �ͻ���IM����Ҫ��ǰ�汾�����з������з���ʦ�б�
struct alltgroomEx_req
{
	short   req;
	short   nMarket;
	char	userid[S_USERID_LEN];			// id
	short	nUsertype;						// �û�����
};

// UPIM_REQ_ALLROOMTOUSER
// Ͷ�˵�IM����Ҫ��ǰ��Ȩ�޵������û��б�
struct tggetuserbyroomid_req
{
	short   req;
	char	userid[S_USERID_LEN];			// id
	short	nUsertype;						// �û�����
	int     roomid;                         // �ͻ������
};

// UPIM_REQ_ALLTGROOMEX/UPIM_REQ_ALLROOMTOUSER ���÷���json��ʽ
// json��ʽ��Ͷ����������Ϣ
struct alltgroom_ans
{
	int		rtnnum;							// ���ظ���
	int		len;							// ����
	char	headp[1];						// ����json	
};

// UPIM_REQ_ONLINE
// ��ѯ����״̬
struct userstate_req
{
	short   req;
	char	userid[S_USERID_LEN];			// id
	short	nUsertype;						// �û�����
	int		flag;							// ��־λ
	int		len;							// ���ݳ���
	char	headp[1];						// ����	
};

// json��ʽ�ĺ���״̬��Ϣ
struct userstate_ans
{
	int		flag;							// ��־λ
	int		rtnnum;							// ���ظ���
	int		len;							// ����
	char	headp[1];						// ����json	
};

// UPIM_REQ_GETGROUP
// im2.0ȡ�����е��Զ��������Ϣ
struct getgroup_req
{
	short   req;
	char	userid[S_USERID_LEN];			// id
	short	nUsertype;						// �û�����
};

struct getgroup_ans
{
	int		flag;							// ��־λ
	int		rtnnum;							// ���ظ���
	int		len;							// ����
	char	headp[1];						// ����json	
};

// UPIM_REQ_GETGUSER
// im2.0ȡ�÷����¶�Ӧ���û��б�
struct getguser_req
{
	short   req;
	char	userid[S_USERID_LEN];			// id
	short	nUsertype;						// �û�����
	int		nGroupID;						// �Զ���ķ���ID
};

struct getguser_ans
{
	int		nGroupID;						// �Զ���ķ���ID
	int		flag;							// ��־λ
	int		rtnnum;							// ���ظ���
	int		len;							// ����
	char	headp[1];						// ����json	
};

// UPIM_REQ_ADDGROUP
// im2.0���/�޸��Զ��������Ϣ
struct addgroup_req
{
	short   req;
	char	userid[S_USERID_LEN];			// id
	int		len;							// ����
	char	headp[1];						// ����json	
};
// 
struct addgroup_ans
{
	int		flag;							// ��־λ
	int		rtnnum;							// ���ظ���
	int		len;							// ����
	char	headp[1];						// ����json	
};


// UPIM_REQ_MODGUSER

// im2.0���/�޸��û��ķ���
struct modguser_req
{
	short   req;
	char	userid[S_USERID_LEN];			// id
	int		len;							// ����
	char	headp[1];						// ����json	
};

struct modguser_ans
{
	int		flag;							// ��־λ
	int		rtnnum;							// ���ظ���
	int		len;							// ����
	char	headp[1];						// ����json	
};


struct json_ans
{
	int		flag;							// ��־λ
	int		rtnnum;							// ���ظ���
	int		len;							// ����
	char	headp[1];						// ����json	
};

#pragma pack(pop,1)
#endif