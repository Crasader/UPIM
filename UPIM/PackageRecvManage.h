#pragma once

#include "struct.h"
// ��Ϣ���Ͱ�����
struct MSG_PKG_INFO2
{
    char guid[GUID_SIZE];	// ����Ψһ��ʶ
	char filename[48];		// �ļ���
	int	originallen;		// ԭʼ����
	char tqid[USERID_SIZE];	// ���Ľ��շ�,�����Ⱥ�飬���Ƿ��ͷ�ID
	int	totallength;		// �����ܳ���
	int length_recv;		// �Ѿ����յ��ĳ���
	char* data;				// ��������
};

class CClientPackage  
{
public:
	CClientPackage();
	virtual ~CClientPackage();
	int SaveToBuffer(char *p);
	LPSTR GetPkBuffer(DWORD& dwSize);

	void Cleanup();
	void Copy(CClientPackage &package);
	void SetContent(void *pContent,long len);
	void SetHeader(PACKAGE_HEADER *pHeader);
private:
	DWORD m_nLen;		// ��ͷ�����ݹ��ж೤
	PACKAGE_HEADER m_header;	// ��ͷ
	char *m_pBuf;				// ��������Ļ�����
};

class CPackageHandle
{
public:
	CPackageHandle(CClientPackage* pKg){m_pkg=pKg;}
	~CPackageHandle(){TDEL(m_pkg);}
protected:
	CClientPackage* m_pkg;
};


class CPackageRecvManage  
{
public:
	CPackageRecvManage();
	virtual ~CPackageRecvManage();

	void HandleMsgPkg(LPCUSERID tqid, MSG_PKG_TRANSFER_REQ *preq);
	void HandleGroupMsgPkg(GROUP_CHAT_CLIENT_RECV_PKG_ANS* pAns);

	void SendAnsMsgPkg(MSG_PKG_INFO2 *pinfo);
	void SendAnsMsgPkg(LPCUSERID tqid, DWORD dwSeq);
	
	void SendAnsMsg(LPRECVMSG2 pRecvMsg2);
protected:
	void ProcessMsgPkg(MSG_PKG_INFO2 *pinfo);
	void DeleteMsgPkg(char* guid, char* filename);
	void DeleteAllMsgPkg();

protected:
	std::vector<MSG_PKG_INFO2> m_vtMsgPkg;
};
