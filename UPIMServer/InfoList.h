/*
* ��Ϣ����
* Opander
* 2014��6��23��14:35:14
*/

#if !defined(_INFOLIST_H_)
#define _INFOLIST_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CInfoList  
{
public:
	CInfoList();
	virtual ~CInfoList();
public:
	// �û�״̬
	BOOL PushUSER(USERSTATE* pUserState);
	BOOL PushUSER(LPCSTR pszID, BYTE ucState, LPCSTR pszToUser=_T(""));
	BOOL PopUSER(USERSTATE& mUserState);
public:
	// �û�״̬
	long m_nHeaderUPID, m_nTailUPID;
	USERSTATE m_aUserState[MAX_STATE];
	CCriticalSection	m_csList;
	
public:
	// ���ݿ������Ϣ
	BOOL IsDbGMsgListFull();
	BOOL PushDBGMsg(LPDBGMSG pDBGMsg);
	BOOL PopDBGMsg(DBGMSG& dbgMsg);

	// ���ݿ������Ϣ
	BOOL IsDbPMsgListFull();
	BOOL PushDBPMsg(LPDBPMSG pDBPMsg);
	BOOL PopDBPMsg(DBPMSG& dbpMsg);

	// �ⲿȺ����Ϣ
	BOOL PushRoomMsg(LPROOMMSG pRoomMsg);
	BOOL PopRoomMsg(ROOMMSG& roomMsg);
private:
	// ���ݿ������Ϣ
	long m_nHeaderDBGMsg, m_nTailDBGMsg;
	DBGMSG	m_aDBGMsg[MAX_GMSG];
	// ���ݿ������Ϣ
	long m_nHeaderDBPMsg, m_nTailDBPMsg;
	DBGMSG	m_aDBPMsg[MAX_PMSG];
	// �ⲿȺ����Ϣ
	long m_nHeaderRoomMsg, m_nTailRoomMsg;
	ROOMMSG	m_aRoomMsg[MAX_RMSG];
	CCriticalSection	m_csMsg;

public:
	// ��ʷ��Ϣ���
	BOOL PushHisMsg(LPHISMSG pHisMsg);
	BOOL PushHisMsg(LPCUSERID pszSrcID, LPCUSERID pszDesID, BYTE ucFormat, long tmSend, LPCTSTR pszMsg);
	BOOL PushHisMsg(LPCUSERID pszSrcID, long nRoomID, long nRoomType, BYTE ucFormat, long tmSend, LPCTSTR pszMsg);
	BOOL PopHisMsg(HISMSG& hisMsg);
private:
	long	m_nHeaderHisMsg, m_nTailHisMsg;
	HISMSG	m_aHisMsg[MAX_HISMSG];
	CCriticalSection	m_csHisMsg;

public:
	// ������Ϣ
	BOOL PushOffMsg(LPOFFMSG pOffMsg);
	BOOL PushOffMsg(LPCUSERID pszSrcID, LPCUSERID pszDesID, BYTE ucFormat, long tmSend, LPCTSTR pszMsg);
	BOOL PopOffMsg(OFFMSG& offMsg);
private:
	// ������Ϣ
	long	m_nHeaderOffMsg, m_nTailOffMsg;
	OFFMSG	m_aOffMsg[MAX_OFFMSG];
	CCriticalSection	m_csOffMsg;

public:
	// ��Ʒ��Ϣ
	BOOL PushPrdtMsg(LPPRDTMSG pPrdtMsg);
	BOOL PushPrdtMsg(LPCTSTR pszPrdtID, LPCTSTR pszSrcID, BYTE ucFormat, long tmSend, LPCTSTR pszMsg);
	BOOL PopPrdtMsg(PRDTMSG& prdtMsg);
private:
	// ��Ʒ��Ϣ
	long	m_nHeaderPrdtMsg, m_nTailPrdtMsg;
	PRDTMSG	m_aPrdtMsg[MAX_PRDTMSG];
	CCriticalSection	m_csPrdtMsg;
	
public:
	// Ⱥ��������Ϣ
	BOOL PushRoomOffMsg(LPROOMOFFMSG pRoomOffMsg);
	BOOL PushRoomOffMsg(LPCTSTR pszSrcID, LPCTSTR pszDesID, LPCTSTR pszSrcName, ROOMID roomid, BYTE roomType, BYTE ucFormat, long tmSend, LPCTSTR pszMsg);
	BOOL PopRoomOffMsg(ROOMOFFMSG& roomOffMsg);
private:
	// Ⱥ��������Ϣ
	long m_nHeaderRoomOffMsg, m_nTailRoomOffMsg;
	ROOMOFFMSG m_aRoomOffMsg[MAX_ROOMOFFMSG];
	CCriticalSection	m_csRoomOffMsg;
};

#endif // !defined(_INFOLIST_H_)
