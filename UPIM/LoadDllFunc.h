#pragma once

// ���ؽ�ͼdll�е�PupupDialog�ӿ�
typedef void (*IUPIM_PupupDialog)(HWND m_hwnd);
extern IUPIM_PupupDialog	IUPIM_PupupDialog_;
extern HMODULE	II_mod;

typedef int(*IMInitClient)(const char *appId, const char* appName, 
	const char* deviceId, const wchar_t* localPath, const wchar_t* databasePath);         //��ʼ��
typedef int(*IMSetDeviceInfo)(const char* manufacturer, const char* model, 
	const char* osVersion, const char* network, const char* networkOperator);             //�����豸��Ϣ
typedef int(*IMConnect)(const char* token, ConnectAckListenerCallback callback,bool ipv6);  //���ӷ�����
typedef int(*IMRegisterMessageType)(const char* clazzName, const unsigned int operateBits); //ע����Ϣ����
typedef int(*IMSetMessageListener)(MessageListenerCallback callback);                       //������Ϣ����  
typedef int(*IMSetExceptionListener)(ExceptionListenerCallback callback);                   //���������쳣����
typedef int(*IMDisconnect)(int);
typedef int(*IMSaveMessage)(const char* targetId, int categoryId, const char* clazzName, 
	const char* senderId, const wchar_t* message, const char* push, const char* appData); //����Ϣǰ�洢��Ϣ
typedef int(*IMsendMessage)(const char* targetId, int categoryId, int transferType, 
	const char* clazzname, const wchar_t* message, const char* push, const char* appData,
	int messageId, PublishAckListenerCallback callback);                                   //������Ϣ
typedef void (*IMGetUserInfo)(const char* userId, UserInfoListenerCallback callback);      //��ȡ�û���Ϣ
typedef int (*IMGetUnreadCount)(const char* targetId, int categoryId);                     //��ȡδ����Ϣ��
typedef bool(*IMClearMessagesUnreadStatus)(const char* targetId, int categoryId);          //����Ự��Ϣ��δ��״̬
typedef void (*IMUploadUserInfo)(const char* name, const char* info, bool flag, TokdenListenerCallback callback);

typedef struct tagIMDLL
{
	HINSTANCE	                   m_hModule;
	IMInitClient                   m_pInitClient;
	IMSetDeviceInfo                m_pSetDeviceInfo;
	IMConnect                      m_pConnect;
	IMRegisterMessageType          m_pRegisterMessageType;
	IMSetMessageListener           m_pSetMessageListener;
	IMSetExceptionListener         m_pSetExceptionListener;
	IMDisconnect                   m_pDisconnect;
	IMSaveMessage                  m_pSaveMessage;
	IMsendMessage                  m_psendMessage;
	IMGetUserInfo                  m_pGetUserInfo;
	IMGetUnreadCount               m_pGetUnreadCount;
	IMClearMessagesUnreadStatus    m_pClearMessagesUnreadStatus;
	IMUploadUserInfo               m_pUploadUserInfo;
}IMRongCloudDLL;

extern IMRongCloudDLL g_RongCloudDll;

extern BOOL LoadDLLFunc();
extern void UnLoadDLLFunc();
extern void sendMessageCallback(const wchar_t* json_str) ;