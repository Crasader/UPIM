#ifndef STRUCT_H
#define STRUCT_H

//UPIMSERVER�õ���STRUCT
#include "../Common/define.h"
//////////////////////////////////////////////////////////////////////////
#pragma pack(push,1)
//���ֽڶ���
//////////////////////////////////////////////////////////////////////////
// ������
class CLock
{
public:
	CLock()	{ InitializeCriticalSection(&m_cs); }
	~CLock() { DeleteCriticalSection(&m_cs); };
	VOID Lock() { EnterCriticalSection(&m_cs); };
	VOID Unlock() { LeaveCriticalSection(&m_cs); };
private:
	CRITICAL_SECTION m_cs;
};

//////////////////////////////////////////////////////////////////////////
// �Զ���
class CAutoLock
{
public:
	CAutoLock(CLock* pLock){m_pLock = pLock;pLock->Lock();}
	~CAutoLock() {m_pLock->Unlock();}
protected:
	CLock* m_pLock;
};

struct UserNode 
{
	DWORD	m_dwSessionID;			//sessionID
	CHAR	m_szUID[UID_SIZE];		//�û�ID		
	DWORD	m_dwUserStatus;			//UserStatus	
	CHAR	m_szInternetIp[24];		//�ͻ��˹���IP	
	DWORD	m_Port;					//�ͻ���Port	

	void Copy(const UserNode& other) 
	{
		m_dwSessionID = other.m_dwSessionID;
		COPYSTRARRAY(m_szUID,other.m_szUID);
		m_dwUserStatus = other.m_dwUserStatus;
		COPYSTRARRAY(m_szInternetIp,other.m_szInternetIp);
		m_Port = other.m_Port;		
	}

	BOOL operator ==(const UserNode& other) 
	{
		if(m_dwSessionID == other.m_dwSessionID &&
			0 == strcmp(m_szUID,other.m_szUID) &&
			0 == strcmp(m_szInternetIp,other.m_szInternetIp) &&
			m_Port == other.m_Port &&
			m_dwUserStatus == other.m_dwUserStatus )    
			return TRUE;
		else
			return FALSE;
	}
};

// ������Ϣ
class CADODatabase;
typedef struct tagOPLINK
{
	WORD	wServerIndex;				// ��̨���
	DWORD	dwBranchID;					// Ӫҵ������
	BOOL	bBusy;						// �Ƿ�ʹ����
	short	nSel;						// ѡ���ĸ����ݿ�
	BOOL	bConnected;					// �Ƿ�����
	long	nBusyTime;					// ��ʼæʱ���
	CADODatabase* pAdodb;
} OPLINK, *LPOPLINK;

// ���ݿ�����
typedef struct tagDBCONFIG
{
	CHAR	szDataSource[32];			// ����Դ
	CHAR	szDataBase[32];				// ���ݿ�
	CHAR	szUserName[32];				// ���ݿ��û�
	CHAR	szPassword[32];				// ���ݿ�����
}DBCONFIG,*LPDBCONFIG;

// User״̬
struct USERSTATE
{
	char	m_szToUser[USER_SIZE];		// ������ID����		
	char	m_szUSERID[USERID_SIZE];	// id
	BYTE	m_ucState;					// id��״̬
};
//������
struct IPInfo
{
	int    id;
	CHAR   IP[40];
};
//ip
struct IPWHITELIST
{
	int     num;
	IPInfo  ipinfo[MAX_IPWHITELIST];
};
// ����������
struct SVRCONFIG
{
	DWORD	dwSVRID;					// ������ID
	CHAR	szSVRIP[MAX_PATH];			// ������ַ
	DWORD	dwSVRPORT;					// �����˿�

	DWORD	dwVersion;					// ���ô���汾
	DWORD	dwMaxAnsBufLen;				// ���Ӧ�𻺳�������
	DWORD	dwMaxSafeBufLen;			// ���ȫ����������
	DWORD	dwThreadNum;				// ȫ�������߳���
	DWORD	dwBranchNum;				// Ӫҵ����

	DWORD	dwBuildNo;					// ����汾��
	CHAR	szBuildDateTime[32];		// ����ʱ��

	CHAR	szHomePath[MAX_PATH];		// ����·��
	CHAR	szConfigPath[MAX_PATH];		// �����ļ�
	CHAR	szLogFile[MAX_PATH];		// ��־�ļ�·��

	short	nInfoDBCount;				// ��Ϣ���ݿ����
	short	nInfoSel;					// ��Ϣ���ݿ�Ĭ������
	DBCONFIG aDBInfoConfig[MAX_DBCOUNT];// ��Ϣ���ݿ�����

	DWORD	dwConnTimeOut;				// ���ݿ����ӳ�ʱ
	DWORD	dwCommTimeOut;				// ���ݿ�ִ�г�ʱ
	BOOL	bHttp;						// �Ƿ�֧��HTTP����

	BOOL	bPushMsg;					// ��̨�Ƿ�������Ϣ
	BOOL	bPushPrdtMsg;				// ��̨�Ƿ����Ͳ�Ʒ��Ϣ

	BOOL	bWriteLog;					// �Ƿ��¼������־

	DWORD	dwMsgInterval;				// ���ݿ�ɨ��ʱ����,��λ:��
	DWORD	dwMsgBeginTime;				// ���ݿ���Ϣ��ʼɨ��ʱ��,��λ:��(HH*3600+MM*60+SS)
	DWORD	dwMsgEndTime;				// ���ݿ���Ϣ����ɨ��ʱ��,��λ:��(HH*3600+MM*60+SS)
	__int64	nSeqGID;					// ����Ϣ����ID
	__int64	nSeqPID;					// ������Ϣ����ID

	DWORD	dwSynBeginTime;				// Ա����Ϣͬ����ʼʱ��(һ��ͬ��һ��)
	DWORD	dwSynEndTime;				// Ա����Ϣͬ������ʱ��
	DWORD	dwSynLastDate;				// ��һ��ͬ��������	
};

// �߳���Ϣ
typedef struct tagTHREADINFO
{
	HANDLE	hUserState;							// ״̬�߳�,�����û�״̬����
	HANDLE	hOnTimer;							// ��ʱ���߳�
	HANDLE	hDBMsgSend;							// ���ݿ���Ϣ�����߳�
	HANDLE	hMsgSend;							// ��Ϣ�����߳�,������Ϣ
	HANDLE	hRoomUpdate;						// Ⱥ����Ϣ�����߳�
	HANDLE	hHisMsg;							// ��ʷ��Ϣ
	HANDLE	hOffMsg;							// ������Ϣ
	HANDLE	hInitSvr;							// ��ʼ�������߳�
	HANDLE	hWriteLog;							// д��־

	HANDLE	hEventExit;							// �˳��¼�
	BOOL	bStartExit;							// ��ʼ�˳�
	HANDLE  hEventLog;							// ��־�¼�
	HANDLE	hTsWorkSvr;							// ������ȡ����
}THREADINFO,*LPTHREADINFO;

// ������Ϣ�û�
typedef struct tagMSGGUSER
{
	__int64	m_nSeqId;
	char	m_szUSERID[USERID_SIZE];
}MSGGUSER,*LPMSGGUSER;

// �ⲿ���ݿ�����Ϣ
typedef struct tagDBGMSG
{
	__int64	m_nID;						// ��ϢID
	__int64	m_nUserSeqId;				// �û�SeqId
	BYTE	m_ucGroupType;				// ��������
	char	m_szGroupID[21];			// ����ID
	BYTE	m_ucAttr;					// ����
	long	m_nEndDate;					// ��ֹ����
	long	m_nEndTime;					// ��ֹ����
	char	m_szSrcID[USERID_SIZE];		// ������ID
	char	m_szText[MAX_MSG_LEN+1];	// ��Ϣ����
}DBGMSG,*LPDBGMSG;

// �ⲿ���ݿ������Ϣ
typedef struct tagDBPMSG
{
	__int64	m_nID;						// ��ϢID
	char	m_szUSERID[USERID_SIZE];	// Ŀ��ID
	char	m_szYyb[5];					// Ӫҵ��
	BYTE	m_ucAttr;					// ����
	BYTE	m_ucFlag;					// ���
	long	m_nEndDate;					// ��ֹ����
	long	m_nEndTime;					// ��ֹʱ��
	char	m_szSrcID[USERID_SIZE];		// ������ID
	char	m_szText[MAX_MSG_LEN+1];	// ��Ϣ����
}DBPMSG,*LPDBPMSG;

// ��ʷ��Ϣ
typedef struct tagHISMSG
{
	char	m_szSrcID[USERID_SIZE];		// ������ID,�ͻ�ID
	char	m_szDesID[USERID_SIZE];		// ������ID,�û�ID
	BYTE	m_ucMsgType;				// ��Ϣ����,0��ʾ������Ϣ,1��ʾȺ����Ϣ
	BYTE	m_ucFormat;					// ��Ϣ��ʽ
	long	m_nSendDate;				// ��������
	long	m_nSendTime;				// ����ʱ��
	char	m_szMsg[MAX_TEXT_LEN+1];	// ��Ϣ����
}HISMSG,*LPHISMSG;

// ��ʷ��Ϣ2(������)
typedef struct tagHISMSG2
{
	char	m_szSrcID[USERID_SIZE];		// ������ID,�ͻ�ID
	char	m_szDesID[USERID_SIZE];		// ������ID,�û�ID
	BYTE	m_ucMsgType;				// ��Ϣ����,0��ʾ������Ϣ,>0��ʾȺ����Ϣ
	BYTE	m_ucFormat;					// ��Ϣ��ʽ
	long	m_nSendDate;				// ��������
	long	m_nSendTime;				// ����ʱ��
	long	m_nMsgLen;					// ��Ϣ����
	char	m_szMsg[COMM_TEXT_LEN+1];	// ��Ϣ����
	char*	m_pMsgExt;					// ��Ϣ��������
}HISMSG2,*LPHISMSG2;

typedef HISMSG	OFFMSG,*LPOFFMSG;
typedef HISMSG2 OFFMSG2,*LPOFFMSG2;

// Ⱥ��������Ϣ
typedef struct tagRoomOffMsg
{
	char	m_szSrcID[USERID_SIZE];		// ������ID,�ͻ�ID
	char	m_szDesID[USERID_SIZE];		// ������ID,�û�ID
	char    m_szSrcName[S_NICKNAME_LEN]; // ����������
	ROOMID  m_nRoomid;                  // Ⱥ��id
	BYTE    m_ucRoomType;               // Ⱥ������
	BYTE	m_ucFormat;					// ��Ϣ��ʽ
	long	m_nSendDate;				// ��������
	long	m_nSendTime;				// ����ʱ��
	char	m_szMsg[COMM_TEXT_LEN+1];	// ��Ϣ����
}ROOMOFFMSG,*LPROOMOFFMSG;


// Ⱥ����Ϣ
typedef struct tagROOMMSG
{
	ROOMID	m_nRoomID;					// ����ID
	BYTE	m_ucRoomType;				// ��������
	BYTE	m_ucFormat;					// ��Ϣ��ʽ
	time_t	m_tmSend;
	BYTE	m_ucUserType;				// m_szSrcID������,0�ͻ�,1Ա��		
	char	m_szSrcID[USERID_SIZE];		// �û�ID
	char	m_szMsg[MAX_TEXT_LEN+1];
}ROOMMSG,*LPROOMMSG;

// ��Ʒ��Ϣ
typedef struct tagPRDTMSG
{
	char	m_szSrcID[USERID_SIZE];		// ������
	char	m_szPrdtID[USERID_SIZE];	// ������
	BYTE	m_ucFormat;					// ��Ϣ��ʽ
	time_t	m_tmSend;					// ����ʱ��
	char	m_szMsg[MAX_TEXT_LEN+1];	// ������Ϣ
}PRDTMSG,*LPPRDTMSG;

// ͼ����Ϣ
typedef struct tagPICINFO
{
	char	m_szPicName[40];
	char	m_szPicAttr[40];
	long	m_nPicLen;
}PICINFO,*LPPICINFO;

// �ϴ��ļ�����
// �ɰ汾
struct UPLOAD_FILE_OLD_REQ
{
	char guid[GUID_SIZE];			// �ļ���Ψһ��ʶ
	char name[128];
	long filelen;
};
// �°汾
struct UPLOAD_FILE_REQ
{
	char guid[GUID_SIZE];				// �ļ���Ψһ��ʶ
	char name[128];						// �ļ���
	long filelen;						// �ļ�����
	char innerstr[33];					// �ļ��ڲ���Ǵ�,2012.3.23 �¼ӽṹ
};

#pragma pack(pop,1)
#endif