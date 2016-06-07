#pragma once
#include "globalvar.h"

//����mongo֧��
#include "mongoc.h"
#pragma comment(lib,"ws2_32.lib")
//#define USE_STATIC_LIBS_ 0

#ifdef _DEBUG
	#ifdef USE_STATIC_LIBS_
		#pragma comment(lib, "bson-static-1.0_d.lib")
		#pragma comment(lib, "mongoc-static-1.0_d.lib")
	#else
		#pragma comment(lib, "bson-1.0_d.lib")
		#pragma comment(lib, "mongoc-1.0_d.lib")
	#endif
#else
	#ifdef USE_STATIC_LIBS_
		#pragma comment(lib, "bson-static-1.0.lib")
		#pragma comment(lib, "mongoc-static-1.0.lib")
	#else
		#pragma comment(lib, "bson-1.0.lib")
		#pragma comment(lib, "mongoc-1.0.lib")
	#endif
#endif

class CMongoDBMgr
{
public:
	CMongoDBMgr();
	~CMongoDBMgr();

	BOOL InitConnect();
	BOOL UnInit();

	// �û���¼/���ߣ�����ID��¼�û���Ϣ
	void UserLoginIn(DWORD dwConnID, LPCTSTR pszUserID, BOOL nbLogin, LPCTSTR pszIp="", DWORD nPort=0);
	// �����û�ID��ѯ�������ϵ�������Ϣ
	BOOL GetUserState(LPCTSTR pszUserID, MYSTATE &m_state, DWORD &dwConnID);
	// �ⲿ���룬���������û�
	BOOL GetAllOnlineUser(vector<UserNode> &users);
	// �����û�״̬������ȷ���Ƿ�����
	BOOL UpdateUserTime(DWORD dwConnID,uint32_t time);
	// ��ȡʱ���������û�
	BOOL QueryTailTimeUser(uint32_t time, vector<LPCUSERID> &vUsers, vector<DWORD> &vDwConnID);

public:	
	mongoc_client_t * m_client;		//mongodb���ӹ���
	CCriSec			m_csFreeItem;
};

