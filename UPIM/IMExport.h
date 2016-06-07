#pragma once

#ifdef IM_EXPORT
#define IM_FUNC_PREFIX extern "C" _declspec(dllexport)
#else
#define IM_FUNC_PREFIX extern "C" _declspec(dllimport)
#endif

#define IMFLAG_CHILD	0X00000000L		// �Ӵ���
#define IMFLAG_INDEPENT 0X00000001L		// ��������
#define IMFLAG_NOHQ		0X00000000L		// û�����齻��
#define IMFLAG_HQ		0X00000010L		// �����齻��

// Ա���˵�¼ģʽ
enum EIMLOGINMODE
{
	eIMLogin_Default	= 0,			// Ĭ��,����qq2010��¼ģʽ
	eIMLogin_Classic	= 1,			// ����ģʽ,�����Ի��������û���������,����qq����ģʽ��¼
	eIMLogin_NoCheckPwd = 2,			// ��У������,ʹ�ÿͻ��ŵ�¼,�ⲿ�Ѿ���¼
	eIMLogin_ClientWeb	= 3,			// web�ͻ���
};

#ifdef _DLL_MODE

// ��ʼ��
IM_FUNC_PREFIX BOOL UEXP_Init(const char *PubDir, const char *PriDir, const char *CfgFile);

// �˳�
IM_FUNC_PREFIX BOOL	UEXP_Uninit();

// ���õ�¼����
IM_FUNC_PREFIX void UEXP_SetLoginType(long nUserType, HWND parent, long lFeedBackMsg, long nFlag = IMFLAG_INDEPENT|IMFLAG_NOHQ, long Reserved = 0);

// ��¼
IM_FUNC_PREFIX BOOL UEXP_Login(long nMode, char Khh[51], char YYBInfo[51], char SSOCode[255], long Reserved = 0 );

// ������֯���ڴ�С
IM_FUNC_PREFIX void UEXP_Resize();

// ����������
IM_FUNC_PREFIX void UEXP_ChangeChat(DWORD roomid);

// ��ʾ������
IM_FUNC_PREFIX void UEXP_ShowMainWnd(); 

// ��Ϣ����
IM_FUNC_PREFIX BOOL	UEXP_PreTransMsg(MSG* pMsg);

// ���齻������
IM_FUNC_PREFIX BOOL UEXP_TransSpecialData(DWORD nGUID, long nReserved = 0);

#endif