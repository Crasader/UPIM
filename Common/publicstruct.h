#ifndef PUBLICSTRUCT_H
#define PUBLICSTRUCT_H
//UPIM/SERVER�õ��Ĺ���STRUCT
//���ֽڶ���
#include "../Common/define.h"
#include "../Common/protocol.h"

#pragma pack(push,1)

//////////////////////////////////////////////////////////////////////////
// ������ʹ�õ�Ⱥ��
// UPIMID
typedef struct tagSPUPIMID
{
	char	m_szUID[USERID_SIZE];
}SPUPIMID,*LPSPUPIMID;

typedef struct tagVUPID
{
	char	m_szIMID[USERID_SIZE];
	BYTE	m_nUserType;
}VUPID,*LPVUPID;

struct STATE_REFLASH_
{
	int			nCount;
	SPUPIMID	mIDVT[REFRESH_USER_COUNT];
};

// Ⱥ��
struct GROUP_CHAT_ROOM
{
	ROOMID	m_nRoomId;					// Ⱥ��id
	int		m_nType;					// Ⱥ������ E_CHATROOM_TYPE
	char	m_szMasterID[USERID_SIZE];	// ����Աid
	char	m_szRoomName[ROOMNAME_SIZE];// Ⱥ������
	char	m_szNote[NOTE_SIZE];		// Ⱥ�鹫��
	bool	m_bDelFlag;					// ɾ����־
	bool	m_bUserFlag;				// �û����ر��
	long	m_nBusy;					// ʹ��״̬

	vector<VUPID> m_vtUser;				// ��ǰȺ���û�
	CRITICAL_SECTION m_csRoom;
};

// Ⱥ�������Ϣ
struct GROUP_CHAT_BASE
{
	ROOMID	m_nRoomId;					// Ⱥ��id
	int		m_nType;					// Ⱥ������ E_CHATROOM_TYPE
	char	m_szMasterID[USERID_SIZE];	// ����Աid
	char	m_szRoomName[ROOMNAME_SIZE];// Ⱥ������
	char	m_szNote[NOTE_SIZE];		// Ⱥ�鹫��
	bool	m_bDelFlag;
};

//////////////////////////////////////////////////////////////////////////
// �ͻ���ʹ�õ�Ⱥ��
// Ⱥ�ĵ������Ϣ
// Ⱥ���û���Ϣ
struct GUSER_INFO
{
	char	m_szIMID[USERID_SIZE];		// IMIDID
	short	m_nUserType;				// �û�����
	char	nickname[S_NICKNAME_LEN];	// ����
	bool	bload;						// �û��Ƿ����б���
	BYTE	iconindex;					// ͼ��
	short	userstate;					// �û�����״̬
	bool	brefresh;					// �û���Ϣ�Ƿ�ˢ��
};

struct GROUP_CHAT_INFO
{							
	ROOMID	m_nRoomId;					// ������id
	int		m_nRoomType;				// ���������ͣ�1���̶������ң�2����ʱ������
	char	m_szMasterID[USERID_SIZE];	// �����ҹ���Աid
	char	m_szRoomName[ROOMNAME_SIZE];// ����������
	char	m_szNote[NOTE_SIZE];		// ����
	bool	m_bDelFlag;					// ɾ����־
	bool	m_bLoadFlag;				// �û����ر��
	vector<GUSER_INFO>* pVtUser;		// �û�����
};

typedef std::vector<GUSER_INFO> VECTOR_GUSER_INFO;

// ���ջ��壬����ְ���ʱ��
typedef struct tagPKGRECVINFO
{
	BOOL	bNeedRecvMore;		// ��Ҫ�ٴν���
	int		nRecvLen;			// ���ճ���
	int		nNeedRecvLen;		// ��Ҫ���ճ���
	BYTE	m_btInfo[16*1024];	// ���ջ�����16K
}PKGRECVINFO,*LPPKGRECVINFO;

typedef std::map<LONG, LPPKGRECVINFO>::iterator PKGRECV_ITER;

#pragma pack(pop,1)
#endif