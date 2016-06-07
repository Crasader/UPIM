#pragma once

#define IMFLAG_CHILD	0X00000000L		// �Ӵ���
#define IMFLAG_INDEPENT 0X00000001L		// ��������
#define IMFLAG_NOHQ		0X00000000L		// û�����齻��
#define IMFLAG_HQ		0X00000010L		// �����齻��(��TdxW����)

#define	UM_IMFEEDBACKMSG			WM_USER + 0x988			// �ⲿ������Ϣ
// ��½ģʽ
enum EIMLOGINMODE
{
	eIMLogin_Default	= 0,			// Ĭ��,����qq2010��¼ģʽ
	eIMLogin_Classic	= 1,			// ����ģʽ,�����Ի��������û���������,����qq����ģʽ��¼
	eIMLogin_NoCheckPwd = 2,			// ��У������,ʹ�ÿͻ��ŵ�¼,�ⲿ�Ѿ���¼
	eIMLogin_ClientWeb	= 3,			// web�ͻ���
};

typedef BOOL (*UEXP_Init)(const char *PubDir, const char *PriDir, const char *CfgFile);
typedef BOOL (*UEXP_SetLoginType)(long nUserType, HWND parent, long lFeedBackMsg, long nFlag , long Reserved);
typedef BOOL (*UEXP_Login)(long nMode, char Khh[51], char YYBInfo[51], char SSOCode[255], long Reserved);
typedef BOOL (*UEXP_Resize)();
typedef BOOL (*UEXP_Uninit)();
typedef BOOL (*UEXP_ChangeChat)(DWORD roomid);

extern CString g_strHomePath;
typedef struct tagIMDLL
{
	HMODULE					m_hModule;
	UEXP_Init				m_pUEXP_Init;
	UEXP_SetLoginType		m_pUEXP_SetLoginType;
	UEXP_Login				m_pUEXP_Login;
	UEXP_Resize				m_pUEXP_Resize;
	UEXP_Uninit				m_pUEXP_Uninit;
	UEXP_ChangeChat			m_pUEXP_ChangeChat;
}IMDLL;
extern IMDLL g_infoDll;

extern BOOL LoadDLLFunc();
extern void UnLoadDLLFunc();