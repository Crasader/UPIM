#pragma once
#include "struct.h"

class CPackageManage
{
public:
	CPackageManage(void);
	virtual ~CPackageManage(void);

	// Ⱥ����Ϣ
	// groupid:Ⱥ��ID��grouptype��Ⱥ������
	// pData:COMPLEX_MSG_DATA*
	void CreateGroupMsg(int groupid, BYTE grouptype, LPVOID pData);

	// ������Ϣ
	// userid:������ID
	// pData:COMPLEX_MSG_DATA*
	// ucFormat:��Ϣ��ʽ
	// ucType:��Ϣ�������� E_MSGSEND_TYPE
	// pszInnerID:�ڲ�ID
	void CreateMsg(LPCTSTR userid, LPVOID pData, BYTE ucFormat=eMsgFormat_Def, BYTE ucType=eMsgSend_Normal, LPCTSTR pszInnerID=_T(""), int nPublicID=-1, int nRouteID=-1);

	void FeedBackMsgPkg(DWORD dwSeq, char* guid=NULL);

	// ���������Ӧ��
	void ProcessMsgAns(DWORD dwSeq, bool bOnline, long nError=0);

	BOOL CheckMsgTimeout();

	void SetAgengID(LPCTSTR pszAgentID);

protected:
	void SendGroup(char *guid);
	void SendMsgPkg(char *guid);

	void DeleteMsgPkg(char *guid);
	void DeleteMsgPkg(DWORD dwSeq);
	void DeleteAllMsgPkg();
	void DeleteMsgData(COMPLEX_MSG_DATA*& pMsgData);

	short GetFreePicInfo(LPVOID pData);
	BOOL VerifyMsgPkg(LPVOID pData);
	BOOL IsEndMsgPkg(LPVOID pData);

	BOOL SendOffImage(LPCUSERID userid, LPVOID pData, BYTE roomType=0);

protected:
	std::vector<MSG_PKG_INFO> m_vtMsgPkg;
};

