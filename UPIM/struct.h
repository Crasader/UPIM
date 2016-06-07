#ifndef STRUCT_H
#define STRUCT_H
//UPIM�õ���STRUCT
//���ֽڶ���
#pragma pack(push,1)

// ������Ϣ
class CFontInfo
{
public:
	CFontInfo(void)
	{
		m_nSize = 10;
		m_clrText = RGB(0,0,0);
		m_strName = STR_DEFAULT_FONT;
		m_bBold = FALSE;
		m_bItalic = FALSE;
		m_bUnderLine = FALSE;
	}
	~CFontInfo(void){}

public:
	int			m_nSize;				// �����С
	COLORREF	m_clrText;				// ������ɫ
	string		m_strName;				// ��������
	BOOL		m_bBold;				// �Ƿ�Ӵ�
	BOOL		m_bItalic;				// �Ƿ���б
	BOOL		m_bUnderLine;			// �Ƿ���»���
};

// ���ݿ�����
typedef struct tagBKINFO
{
	int		m_nBkType;
	int		m_nBkIndex;
	DWORD	dwBackColor;
}BKINFO,*LPBKINFO;

// ���ݿ�����
typedef struct tagHOSTCFG
{
	CHAR	szSVRIP[MAX_PATH];			// ������ַ
	DWORD	dwSVRPORT;					// �����˿�
}HOSTCFG,*LPHOSTCFG;

// ����������
struct CLIENTCONFIG
{
	HOSTCFG aHostCfg[MAX_HOSTCOUNT];	// ����������
	DWORD	nMainHost;					// Ĭ�Ϸ�����

	CHAR	szHomePath[MAX_PATH];		// ����·��
	CHAR	szConfigPath[MAX_PATH];		// �����ļ�
	CHAR	szFaceConfig[MAX_PATH];		// ���������ļ�
	CHAR	szUserConfig[MAX_PATH];		// �û��Զ�������
	CHAR	szUserDir[MAX_PATH];		// �û��ļ���
	CHAR	szUserImage[MAX_PATH];		// �û�����ͼƬ
	CHAR	szUserFile[MAX_PATH];		// �û������ļ�
	CHAR	szUserHead[MAX_PATH];		// �û�ͷ��ͼƬ
	CHAR	szUserDisplay[MAX_PATH];	// ϵͳͼ��Ŀ¼
	CHAR	szLogPath[MAX_PATH];		// ��־�ļ�

	BOOL	m_bClientGrp;				// �ҵĿͻ�
	BOOL	m_bDefGroup;				// �Զ������
	BOOL	m_bDept;					// ����
	BOOL	m_bPublic;					// ���ں�Ȩ��
	BOOL	m_bEmpProduct;				// ��Ʒ
	BOOL    m_bDefGroup2;				// �Զ������2(�ͻ�����)
	BOOL	m_bHisMsg;					// sqlite����ʷ��Ϣ

	BOOL	m_bWriteLog;
	CHAR	szLogFile[MAX_PATH];		// ��־�ļ�
	DWORD	dwBuildNo;					// ����汾��
	CHAR	szBuildDateTime[32];		// ����ʱ��
	CHAR	szRunTime[MAX_PATH];		// ����ʱ��

	CHAR	szLoginName[MAX_PATH];		// ���ڵ�½�ļ����û���
	DWORD	dwMarket;					// �г�
};

// �û���������
struct USERCONFIG
{
	BOOL	m_bMsgSound;				// ����Ϣ����
	BOOL	m_bNotifySound;				// ֪ͨ��Ϣʱ����
	BOOL	m_bOnlineSound;				// ��������ʱ����
	BOOL	m_bShakeSound;				// ���ڶ���ʱ����

	int		m_nNickType;				// �����б�����ʾ������(NICKTYPE)
	BKINFO	m_bkInfo;					// ����ı���ͼƬ���/������ɫ
	CFontInfo m_fontInfo;				// ȫ��������Ϣ

	BOOL	m_bSendImage;			// �Ƿ�������ͼƬ,������ΪFALSEʱ,���ܷ���ͼƬ
	BOOL	m_bSendOffImage;		// �Ƿ�������ͼƬ,m_bSendImageΪTRUEʱ��Ч,ΪTRUEʱ����������תͼƬ��ͼƬ���ϴ���������
};

// ��ǰѡ�нڵ���Ϣ
struct SELECTNODE
{
	char		m_szID[USERID_SIZE];	// �û��б��б�ѡ�е��˵�id����Ⱥid
	EPANELTYPE	m_nPanelType;			// ѡ��������ͣ���ʾ�Ǹ�������/������/�����ϵ��
	ENODETYPE	m_nNodeType;			// ѡ�нڵ����ͣ���ʾ�ǽڵ㣬�����û�
	EUSERTYPE	m_nSelUserType;			// ѡ���˵����ͣ�m_nNodeType=0��Ч����������У���ע�û����
	E_GROUPCHAT_TYPE m_nGroupType;		// ���ѡ�е���Ⱥ�飬����Ⱥ������
	LPVOID		lpNode;					// ѡ�нڵ��Nodeָ��
};

// ��Ϣ�����ͽṹ
typedef struct tagMSG_PKG_INFO
{
	DWORD	dwMsgSeq;					// �����
	char	guid[GUID_SIZE];			// ����Ψһ��ʶ
	char	userid[USERID_SIZE];		// ���Ľ��շ�,�����Ⱥ�飬���Ƿ��ͷ�ID
	ROOMID  nRoomID;					// Ⱥ��ID
	BYTE	ucRoomType;					// Ⱥ������ E_GROUPCHAT_TYPE
	BYTE	ucMsgType;					// ��Ϣ���� E_MSGSEND_TYPE 
	char	szInnerID[USERID_SIZE];		// �ڲ�ID
	time_t	tmSend;						// ����ʱ��
	BYTE	nSendCount;					// ���Դ��� ������Դ��� SEND_MAXCOUNT
	BYTE	ucFormat;					// ��Ϣ��ʽ EMSGTEXTFORMAT 
	int		nPublicID;					// ���ں�ID
	int		nRouteID;					// ·�����
	LPVOID  lpData;						// �����Զ���ṹ COMPLEX_MSG_DATA*
}MSG_PKG_INFO,*LPMSG_PKG_INFO;


enum EIMAGETYPE
{
	eImgType_SysFace=0,		// ϵͳ����
	eImgType_Image,			// ͼƬ
};

//richedit�е�ͼƬ��Ϣ
struct PIC_OBJECT_INFO
{
	BYTE	nType;						// ͼƬ����
	int		nTextPos;					// ���ı�����ʼλ��
	BYTE	ucState;					// ״̬
	char	szFile[48];					// �ļ���
	int		nTotalLen;					// �ܳ���
	int		nLen;						// ��ǰ����
	char*	pBuf;						// ���������
};

// ���Ͱ��İ�ͷ
struct PACKAGE_HEADER
{
	WORD	protocolid;			// Э����
	DWORD	packagelen;			// ����(��������ͷ);
	DWORD   dwReserved;			// 
	PACKAGE_HEADER()
	{
		packagelen = 0;
		dwReserved = 0;
	}
};

struct COMPLEX_MSG_DATA
{
	int nTextLen;						// �ı�����
	char* pBuf;							// �ı�����
	short sSend;						// ���Ͳ��֣�-1,׼�������ı���0--nObjCount-1������ͼƬ���
	int nObjCount;						// ͼƬ�������
	PIC_OBJECT_INFO* pObjectInfo;
};

struct GUPID
{
	char		m_szUSERID[USERID_SIZE];
	EUSERTYPE	m_nUserType;
};

typedef struct tagCGPARAM
{
	ROOMID	m_nRoomID;
	int		m_nRoomType;
	char	m_szMasterID[USERID_SIZE];
	char	m_szRoomName[ROOMNAME_SIZE];
	std::vector<GUPID>	m_vtUpID;
}CGPARAM,*LPCGPARAM;

// ��ӳ�Ա
struct GROUP_CHAT_ADD_STU
{
	ROOMID	roomid;						// ������id
	int		roomtype;					// ����������
	// attach
	int		count;
	GUPID	agUpid[REFRESH_GUSER_COUNT];
};

// ��Ϣ�����
struct  MSG_PKG_TRANSFER_REQ
{
	char guid[GUID_SIZE];			// ��Ϣguid
	short sSend;					// ͼƬ���
	char filename[48];				// �ļ���
	bool request;					// ����������ǻ�Ӧ��
	int totallength;				// �ܳ���
	int length;						// ���ݳ���
	char data[1];					// �û����͵���Ϣ
};

// ��ϢӦ���
struct MSG_PKG_TRANSFER_ANS
{
	char	guid[GUID_SIZE];		// GUID
	DWORD	dwSeq;					// �����к�
	char	filename[48];
	int		length;
};

// Ⱥ�鷢��
struct GROUP_CHAT_CLIENT_SEND_PKG_REQ
{
	DWORD	seq;				// �����к�
	char	guid[17];			// guid
	char	filename[44];		// �ļ���
	ROOMID	roomid;				// ������id
	int		roomtype;			// ����������
	char	tqid[USERID_SIZE];	// ���ͷ�ID
	int		totallen;			// �ܳ���
	int		original_len;		// ԭʼ����
	int		pos;				// λ��
	WORD	msglen;				// ����
	char	msg[1];				// ����
};

// Ⱥ���հ�
struct GROUP_CHAT_CLIENT_RECV_PKG_ANS
{
	char	guid[GUID_SIZE];	// guid
	char	filename[44];		// �ļ���
	ROOMID	roomid;				// ������id
	int		roomtype;			// ����������
	char	tqid[USERID_SIZE];	// ���ͷ�ID
	int		totallen;			// �ܳ���
	int		original_len;		// ԭʼ����
	DWORD	pos;				// λ��
	WORD	msglen;				// ����
	char	*msg;				// ����
};

// ��Ϣ�ṹ2.0
struct CHAT_RECORD2
{
	int		seq;						// seq��������
	char	fromid[USERID_SIZE];		// ����userid
	char	toid[USERID_SIZE];			// ����userid
	int		roomid;						// ����ID
	int		senddate;					// ���� YYYYMMDD
	int		sendtime;					// ʱ�� HHMMSS
	int		type;						// ���� E_CHATRECORD_TYPE
	int		format;						// ��ʽ EMSGTEXTFORMAT
	int		msglen;						// ��Ϣ��
	char*	msg;						// ��Ϣ����
};

// ������Ϣ���յ��ķ�����Ӧ��
typedef struct tagSENDMSG_ANS_
{
	char	m_szDesID[USERID_SIZE];
	long	m_nState;
	DWORD	m_dwSeq;
	long	m_tmSend;
	char	m_szInnerID[USERID_SIZE];
}SENDMSG_ANS_,*LPSENDMSG_ANS_;

// ���յ��ĺ�����Ϣ
struct RECEIVED_MSG
{
	char	imid[USERID_SIZE];			// ������ID
	char	nickname[S_NICKNAME_LEN];	// �ǳ�
	long	senddate;					// ��������
	long	sendtime;					// ����ʱ��
	BYTE	msgtype;					// ��Ϣ����,�Ƿ�ת����Ϣ
	char	innerID[USERID_SIZE];		// �ڲ�ID
	BYTE	format;						// ��Ϣ���ݸ�ʽ,EMSGTEXTFORMAT
	int		msglen;						// ��Ϣ����
	char*	msg;						// ����
	RECEIVED_MSG()
	{
		memset(this,0,sizeof(RECEIVED_MSG));
	}
};
typedef std::vector<RECEIVED_MSG> VECTOR_RECEIVED_MSG;

// ���յ��ĺ�����Ϣ2
// ������յ�����ת��Ϣ����m_szUSERID����Ϣ����ԭʼ���ͷ�(src),m_szInnerID����Ϣ����ת��(mid),��¼�û�Ϊ��Ϣ����תĿ�귽.
typedef struct tagRECVMSG2
{
	DWORD	m_dwSeq;					// ����
	char	m_szUSERID[USERID_SIZE];	// ������id;
	BYTE	m_ucUserType;				// �û�����
	BYTE	m_ucMsgType;				// ��Ϣ����
	char	m_szInnerID[USERID_SIZE];	// �ڲ�ID
	long	m_nSendDate;				// ��������
	long	m_nSendTime;				// ����ʱ��
	BYTE	m_ucFormat;					// ��Ϣ�ĸ�ʽ EMSGTEXTFORMAT
	int		nPublicID;					// ���ں�ID
	WORD	m_nMsglen;					// ��Ϣ��,���Ը��ı�������
	char	m_szMsg[MAX_TEXT_LEN+1];	// �û����͵���Ϣ
}RECVMSG2,*LPRECVMSG2;

// �û�������Ϣ
struct USER_GROUP_INFO
{
	BYTE	m_ucGroupType;				// EGROUPLISTTYPE ��������
	DWORD	m_nGroupID;
	char	m_szGroupName[GROUPNAME_SIZE];
	DWORD	m_nParentID;
	bool	m_bLoad;					// �Ƿ����
	bool	m_bCreateNode;				// �Ƿ񴴽��ڵ�
	short	m_nFailCount;
};

// �û�Ⱥ����Ϣ
struct USER_ROOM_INFO
{
	BYTE	m_ucGroupType;				// EGROUPLISTTYPE ��������
	DWORD	m_nGroupID;
	char	m_szGroupName[GROUPNAME_SIZE];
	DWORD	m_nParentID;
	bool	m_bLoad;					// �Ƿ����
	bool	m_bCreateNode;				// �Ƿ񴴽��ڵ�
	short	m_nFailCount;
};

// ����ʦ�����û���Ϣ
struct USER_ROOMCLIENT_INFO
{
	char	m_szUPID[USERID_SIZE];				// UP�û�ID
	char	m_szImgURL[MAX_PATH];				// �û�ͷ��url(ͨ����ҳ�ӿ�ȡ��)
	char	m_szImgName[IMG_NAME_SIZE];			// �û�ͷ���ļ���
	char	m_szLNomalImgName[IMG_NAME_SIZE];	// ����֮��ı����ļ���
	char	m_szLGrayImgName[IMG_NAME_SIZE];	// ����֮��ı����ļ���
	char	m_szNodeName[NODE_NAME_SIZE];		// �û��ڵ��������б����е�һ��
	char	m_szLastWords[LAST_WORD_SIZE];		// ���̸����

	BOOL	m_bIsImgDownLoad;
	BOOL	m_bIsOnLine;
	BOOL	m_bLoad;							// �Ƿ����
	BOOL	m_bGroupLoad;						// �Զ���ķ����Ƿ����
	int		m_nGroupID;							// �������
	BOOL	m_bCreateNode;						// �Ƿ񴴽��ڵ�
	short	m_nFailCount;						// ʧ�ܴ���
	USER_ROOMCLIENT_INFO()
	{
		COPY_USERID(m_szUPID,0) ; 

	}
	// UP���û���Ψһ  ���û�����ͬʱ ��Ϊ�����û���ͬһ���� 
	BOOL operator==( const USER_ROOMCLIENT_INFO& other )
	{
		if( strlen(m_szUPID) > 0 )
		{
			if( strcmp(m_szUPID ,other.m_szUPID) == 0 )
				return TRUE ; 
			else
				return FALSE ; 
		}
		else
			return FALSE ; 
	}
};

// bLoad 
// bUsed ������m_groupInfoStc�У���ǰ�ڵ��Ƿ�ʹ��
// bGetUserInfo �Ƿ���ظ÷���Ŀͻ� 
struct ANALYSTGROUP_INFO
{
	bool        bLoad ;                         // �Ƿ���ʾ��ť 
	bool		bUsed;							// �Ƿ�ʹ�� 
	bool		bGetUserInfo;					// �Ƿ��Ѿ������˷����µ��û���Ϣ
	bool		bCreateNode;					// �Ƿ񴴽��ڵ�
	int			nGroupID;						// ������ţ����̨���ݿ�����һ��
	CString		GroupName;						// ��������
};

// ����ʦ�����û���Ϣ
struct ROOMANALYS_INFO
{
	int		m_nAnalysID;						// ����ʦID
	char	m_szAnalysName[USERID_SIZE];		// ����ʦ����

	char	m_szGood[MAX_PATH];					// ����ʦ�ó�����
	char	m_szImgURL[MAX_PATH];				// �û�ͷ��url(ͨ����ҳ�ӿ�ȡ��)
	char	m_szImgName[IMG_NAME_SIZE];			// �û�ͷ���ļ���
	char	m_szLocalImgName[IMG_NAME_SIZE];	// ����֮��ı����ļ���

	char	m_szNodeName[NODE_NAME_SIZE];		// �û��ڵ��������б����е�һ��
	char	m_szLastWords[LAST_WORD_SIZE];		// ���̸����
	BOOL	m_bIsOnLine;
	bool	m_bLoad;							// �Ƿ����
	bool	m_bCreateNode;						// �Ƿ񴴽��ڵ�
	short	m_nFailCount;						// ʧ�ܴ���
};

// ���з�����Ϣ
struct ALLCLIENT_ROOM_INFO
{
	int		m_nRoomID;							// ����ID
	char	m_szRoomName[USERID_SIZE];			// ��������
	int		m_nOnLineAnalysNum;					// ���ߵķ���ʦ����
	int		m_nAnalysNum;						// ����ʦ����
	int		m_nVipRight;						// Ȩ�޴�
	int		m_nIsVip;							// �Ƿ���VIP����
	bool	m_bLoad;							// �Ƿ����
	bool	m_bCreateNode;						// �Ƿ񴴽��ڵ�
	short	m_nFailCount;						// ʧ�ܴ���
	vector<ROOMANALYS_INFO>* pVtAnalys;			// �����µķ���ʦ����
};
typedef std::vector<ROOMANALYS_INFO> VECTOR_ROOMANALYS_INFO;

struct MODIFY_USERINFO_STU
{
	char	userid[S_USERID_LEN];
	char	nickname[S_NICKNAME_LEN];
	char	sex;
	long	birthday;
	char	postalcode[7];
	char	telenum[41];
	char	mobilenum[S_MOBILE_LEN];
	char	email[S_EMAIL_LEN];
	char	department[41];
	char	sign[S_SIGNATURE_LEN];
};

// ���¼�û��йص��˵���Ϣ�Ľṹ
typedef struct tagFRIEND_INFO
{
	char userid[S_USERID_LEN];			// userid
	char nickname[S_NICKNAME_LEN];		// �ǳ�
	char truename[S_USERNAME_LEN];		// ��ʵ����
	long relation;						// �����ϵ
	BYTE type;							// �������� EGROUPLISTTYPE
	BYTE sex;							// �Ա�,EGENDER
	BYTE iconindex;						// ͼ�����
	BYTE online;						// �Ƿ�����
	char mobile[S_MOBILE_LEN];			// �ƶ��绰
	char email[S_EMAIL_LEN];			// ��������	
	char sign[S_SIGNATURE_LEN];			// ǩ��
	DWORD reserved;						// ����
	bool m_bLoad;						// �Ƿ����
}FRIEND_INFO,*LPFRIEND_INFO;

// ����·�ɵ���Ϣ�ṹ
struct ROUTE_INFO
{
	int		nID;						// ID
	char	m_RName[USERID_SIZE];		// ����·������
	int		nProblemtype;				// Problemtype
};
typedef std::vector<ROUTE_INFO> VECTOR_ROUTE_INFO;

// ���ںŵ���Ϣ�ṹ
typedef struct tagPUBLIC_INFO
{
	int		nPublicID;					// ���ں�ID
	char	szName[S_NICKNAME_LEN];		// ���ں��ǳ�(32)
	char	szInfo[S_SIGNATURE_LEN];	// ���ں�˵��(128)
	char	szWelcome[S_SIGNATURE_LEN];	// ���ںŻ�ӭ��(128)
	bool	m_bLoad;					// �Ƿ����
	vector<ROUTE_INFO>* pVtRoute;		// ����·��
}PUBLIC_INFO,*LPPUBLIC_INFO;

// Ͷ�������ҵ���Ϣ�ṹ
typedef struct tagTGROOM_INFO
{
	int		nRoomID;					// ������ID
	char	szName[S_NICKNAME_LEN];		// �������ǳ�(32)
	char	szInfo[S_SIGNATURE_LEN];	// ������˵��(128)
	bool	m_bLoad;					// �Ƿ����
}TGROOM_INFO,*LPTGROOM_INFO;

struct STATE_INFO
{
	char	userid[S_USERID_LEN];		// id
	short	nUserstate;					// �û�״̬
};

struct IMAGE_INFO
{
	int nFaceNo;
	char filename[44];
	BOOL bFinish;		//ͼƬ�Ƿ���װ��
	BOOL bSend;			//���ڸ�ͼƬ�Ƿ�Ϊ���ͷ�
	time_t tmR;			//���շ�����յ���ͼʱ��
	IMAGE_INFO()
	{
		memset(this,0,sizeof(IMAGE_INFO));
		nFaceNo = -1;
	}
};

struct AnalystInfo
{
	DWORD		AnalystId;		// ����ʦID 
	CString		AnalystName;	// ����
	CString		sDescription;	// ���
	CString		sImg;			// ͷ��URL
	CString		sDownImg;		// ����ԭʼͷ��
	CString		sLocalImg;		// ���������ı���ͷ��·��
	CString		sLocalGrayImg;	// ���ص�ͷ�񱾵ش���
	BOOL		bIsImgDownLoad;	// ͷ���Ƿ��������
	BOOL		bIsShow;		// �Ƿ���ʾ
	int			bIsOnLine;		// �Ƿ�״̬
	int			nControlIndex;	// �����ؼ����
};


#pragma pack(pop,1)
#endif