#pragma once

#pragma pack(push,1)
const char* GetErrorStr(int nError);
typedef map<ROOMID, GROUP_CHAT_ROOM>::iterator GCR_ITER;

class CGroupChatManage  
{
public:
	CGroupChatManage();
	virtual ~CGroupChatManage();
	
public:
	// return:E_GROUPCHAT_ERROR
	LONG Init(CADODatabase* pAdoDb);
	VOID Uninit();
	
	/************************************************************************/
	// ������������
	// return:E_GROUPCHAT_ERROR
	// ����:
	// name:Ⱥ������;type:Ⱥ����;masterid:����ԱID;pAdoDb:���ݿ�����;
	// roomid:output, Ⱥ��ID
	/************************************************************************/
	LONG CreateRoom(const char *name, int type, LPCUSERID masterid, CADODatabase* pAdoDb, ROOMID& id);
	
	/************************************************************************/
	// ����ĳ��������
	// id:������ID;roomtype:����������;icqid:����Ⱥ���û�ID;vtUpid:����Ⱥ���û�ID���� 
	/************************************************************************/
	LONG EnterRoom(ROOMID id, int roomtype, vector<VUPID>& vtUpid, CADODatabase* pAdoDb);

	// ĳ�����뿪ĳ��������
	// ��upid=-1����Ϊmasterid��ʱ��,��ɢ��Ⱥ��
 	LONG LeaveRoom(ROOMID id, int roomtype, LPCUSERID imid, CADODatabase* pAdoDb);

	// ����Ⱥ��id�õ���ǰȺ���Ա
	LONG GetUser(ROOMID id, int roomtype, vector<VUPID> & user, CADODatabase* pAdoDb=NULL);
	// nCount[in,out] in(VUPID����С),out(ʵ��VUPID����)
	LONG GetUser(ROOMID id, int roomtype, VUPID* pUser, int& nCount, CADODatabase* pAdoDb=NULL);

	// �õ��ҵ�Ⱥ��
	LONG GetMyChatroom(LPCUSERID imid, vector<GROUP_CHAT_BASE> &gci, CADODatabase* pAdoDb);
	// ����ҵ�Ⱥ��
	LONG AddMyChatroom(LPCUSERID imid, ROOMID roomid, CADODatabase* pAdoDb);
	// ɾ���ҵ�Ⱥ��
	LONG DelMyChatroom(LPCUSERID imid, ROOMID roomid, CADODatabase* pAdoDb);

	// �����û�id�õ��û����ڵĹ̶�������
	LONG GetMyChatroom2(LPCUSERID imid, vector<GROUP_CHAT_BASE>& gci, CADODatabase* pAdoDb);

	// �õ�Ⱥ���һЩ������Ϣ
	LONG GetChatroomInfo(GROUP_CHAT_BASE& chatInfo);

	// �޸�Ⱥ����
	LONG UpdateNote(ROOMID roomid, int roomtype, LPCSTR pszNote, CADODatabase* pAdoDb);

	// �޸�Ⱥ������
	LONG UpdateName(ROOMID roomid, int roomtype, LPCSTR pszName, CADODatabase* pAdoDb);

	//////////////////////////////////////////////////////////////////////////
	// ͬ������Ⱥ��
	// �õ����µ�Ⱥ����Ϣ
	LONG GetChatRoomInfo_U(CADODatabase* pAdoDb, GROUP_CHAT_BASE* pGcb, int& nSize);
	// ����Ⱥ����Ϣ
	LONG UpdateChatRoomInfo(GROUP_CHAT_BASE* pGcb, CADODatabase* pAdoDb);

private:
	// ��������������
	VOID DestroyAll();

	LONG _GetUser(ROOMID roomid, CADODatabase* pAdoDb, vector<VUPID> & user);
	LONG _GetChatRoom(ROOMID roomid, int roomtype, GCR_ITER& iter);
	LONG _GetChatRoom2(ROOMID roomid, int roomtype, GCR_ITER& iter);
	
	CCriticalSection m_cs;
	char		m_szTimeTime[32];
	LONG		m_nMaxRoomID;			// Ⱥ��ID����

	map<ROOMID, GROUP_CHAT_ROOM>	m_mapChatroom;
	map<ROOMID, GROUP_CHAT_ROOM>	m_mapTemproom;
};
#pragma pack(pop)