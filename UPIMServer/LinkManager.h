/*
* ���ݿ����ӳ�
* Opander
* 2014��6��10��16:52:55
*/
#if !defined(__LINKMANAGER_H__)
#define __LINKMANAGER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "globalvar.h"

class CLinkManager  
{
public:
	CLinkManager();
	virtual ~CLinkManager();

public:
	BOOL		Init(); // ��ʼ��
	BOOL		Exit(); // �˳�
	LPOPLINK	GetLink(char *lpszErrMsg, int nSize, BOOL bPrimary=FALSE);// ȡ������(���ﴦ��)(����NULLΪʧ��,��Ӧ������Ϣ������lpszErrMsg��)
	LPOPLINK	GetHisMsgLink();					// ��ʷ��Ϣ�������
	LPOPLINK	GetOffMsgLink();					// ������Ϣ�������
	void		FreeLink( LPOPLINK pLink);			// �ͷ�����
	void		DisConnect( LPOPLINK pLink);		// �Ͽ�����
	void		CheckConnect(LPOPLINK pLink);

protected:
	BOOL		_Init(LPOPLINK pLinkInfo);						// ��ʼ������
	BOOL		_Connect(LPOPLINK pLink, BOOL bFailLog=TRUE);	// ��������Ĭ�����ݿ�,�������������ݿ�
	BOOL		_Connect2(LPOPLINK pLink, BOOL bFailLog=TRUE);	// �������Ӹ������ݿ�

protected:
	short			m_nDbCount;					// ���ݿ����
	short			m_nDefaultSel;				// Ĭ�����ݿ�
	DBCONFIG		m_dbConfig[MAX_DBCOUNT];

	OPLINK			m_aLinkInfo[MAX_LINK_NUM];	// ���ݿ����ӳ�
	OPLINK			m_linkHisMsg;				// ��ʷ��Ϣ�������,��Ϣ����̵߳���
	OPLINK			m_linkOffMsg;				// ������Ϣ,������Ϣ�̵߳���

	long				m_nFailCount;
	CCriticalSection	m_csLink;
};

#endif // !defined(__LINKMANAGER_H__)
