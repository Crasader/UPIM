#pragma once

// �����û�״̬
extern DWORD WINAPI _AfxSendUserState(LPVOID lpParam);

// ���������Ϣ
extern DWORD WINAPI _AfxAddOffMsg(LPVOID lpParam);

// �����ʷ��Ϣ
extern DWORD WINAPI _AfxAddHisMsg(LPVOID lpParam);

// �����ⲿȺ����Ϣ
extern DWORD WINAPI _AfxSendMsg(LPVOID lpParam);

// ��ʼ�������߳�
extern DWORD WINAPI _AfxInitSvr(LPVOID lpParam);

// �̶߳�ʱ��
extern DWORD WINAPI	_AfxOnTimer(LPVOID lParam);

//////////////////////////////////////////////////////////////////////////
// �õ����ݿ���Ϣ(��)
extern BOOL	GetDBGMsg(CADODatabase* pAdoDb);
// �õ����ݿ���Ϣ(����)
extern BOOL GetDBPMsg(CADODatabase* pAdoDb);
// �õ����ݿ������Ϣ�����û�
extern BOOL GetDBGMsgUser(CADODatabase* pAdoDb, LPCTSTR pszGroupId, __int64 nSeqId, LPMSGGUSER pMsgGUser, long& nSize);
// Ⱥ����Ϣ
extern DWORD WINAPI _AfxUpdateGroupRoom(LPVOID lParam);
// �������ݿ���Ϣ
extern DWORD WINAPI _AfxSendDBMsg(LPVOID lpParam);
// д��־
extern DWORD WINAPI _AfxWriteLog(LPVOID lpParam);