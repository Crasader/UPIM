#ifndef GLOBALVAR_H
#define GLOBALVAR_H

#include "IMExport.h"
#include "../Common/define.h"
#include "MyClient.h"
#include "UI/MainFrame.h"
#include "UI/ChatDialog.h"
#include "sqlite/SqliteOp.h"
#include "MyThread.h"

class CMyClient;
extern CMyClient g_MyClient;	// ���ӷ�װ�࣬������Ϣ��
extern MainFrame* g_pFrame;		// ������ָ�� 
extern CSqliteOp g_SqliteOp;	// sqlite��������
extern CCharConv g_CharConv;	// �ַ�ת����������
extern ChatDialog* g_TGChatDialog;
extern CGeneralDialog* g_pCreateTG1;
extern CGeneralDialog* g_pCreateTG2;
extern CWinThread* g_pCreateThread;
extern BOOL g_UIMessageLoopStart;

extern HINSTANCE g_hInstance;	// �����DLL����Դ���¼����
extern long		g_nUserType;	// �û����� 
extern long		g_bIndepend;	// �Ƿ�����汾
extern HWND		g_hVessel;		// DLL����ģʽ�ĸ�����ָ��
extern UINT		g_hFeedBackMsg;	// DLL���ô����ģ��������ڴ������Ϣ
extern long		g_nHQ;			// �Ƿ�����鼯��

extern long		g_nLoginMode;	// ��¼ģʽ
extern BOOL		g_bLogining;	// �Ƿ����ڵ�¼
extern BOOL		g_bLogined;		// ��¼�Ƿ�ɹ�
extern long		g_nLoginSucNum;	// ��¼�ɹ�����
extern BOOL		g_bExiting;		// �Ƿ������˳�
extern BOOL		g_bUserKickOff;	// �Ƿ��ߵ�

extern long		g_nMsgSeq;		// ȫ����Ϣ���б��
extern std::map<CDuiString, LPVOID>		allopenwnd;
extern std::map<CDuiString, CDuiString>	alluserNickname;
extern std::map<CDuiString, int>		allUserState;
typedef map<CDuiString, int>::iterator UST_ITER;

extern CLIENTCONFIG	g_config;
extern USERCONFIG	g_userconfig;
extern char			g_loginname[51];
extern char         g_khID[51] ;   // wuchao add at 20160425 �ͻ���¼ʱ�Ŀͻ�ID  IM���ɵ�UP�� UP�������Ĳ��� 
extern int			g_nMarket;
extern char			g_analysheadurl[256];
// ����״̬����
extern std::vector<STATE_INFO>	m_vtStateInfo;
typedef vector<STATE_INFO>::iterator StateInfo_ITER;
// flashnode
extern std::vector<Node*>	m_vtFlashNodeInfo;
extern std::vector<Node*>	m_vtFlashNodeInfo2;
typedef vector<Node*>::iterator FlashNode_ITER;
// department
extern std::vector<USER_GROUP_INFO>	m_vtDeptInfo;
extern int		m_nDeptIdx;		
// group
extern std::vector<USER_GROUP_INFO>	m_vtUserGroup;
extern int		m_nGroupIdx;
// friend
extern std::vector<FRIEND_INFO>	m_vtFriendInfo;
extern int		m_nFriendIdx;
// roomclient
extern std::vector<USER_ROOMCLIENT_INFO>	m_vtRoomClient;
extern int		m_noomClientIdx;

////////////////////////////////////////////////////////////////
// wuchao add at 2016-03-29
// ����ʦ�� ��ǰ������Ա����ϸ��Ϣ��������Ա
////////////////////////////////////////////////////////////////
extern std::vector<USER_ROOMCLIENT_INFO>	m_vtOnlineClient;
extern std::vector<USER_ROOMCLIENT_INFO>	m_vtOfflineClient;

// room
extern std::map<ROOMID, GROUP_CHAT_INFO>	m_mapChatRoom;
typedef map<ROOMID, GROUP_CHAT_INFO>::iterator GCR_ITER;
// rights
extern std::map<int, int>	m_mapCilentRights;
extern int		m_nCilentRightsIdx;

// public
// ���ڿͻ���˵���洢�������ɼ��Ĺ��ں�
// ���ڷ�����Ա��˵���洢�������ṩ����Ĺ��ں�
extern std::map<PUBLICID, PUBLIC_INFO>		m_mapPublicInfo;
typedef map<PUBLICID, PUBLIC_INFO>::iterator PUB_ITER;

// Analyst
// ���ڷ���ʦ��˵���洢�������ṩ����ķ����
extern std::map<TGROOMID, TGROOM_INFO>		m_mapTgRoomInfo;
typedef map<TGROOMID, TGROOM_INFO>::iterator TR_ITER;

//im2.0�У��ͻ�ȡ�õ����з���ʦ��Ϣ
extern std::map<TGROOMID, ALLCLIENT_ROOM_INFO>		m_mapAllClientRoom;
typedef map<TGROOMID, ALLCLIENT_ROOM_INFO>::iterator ACRI_ITER;
extern ANALYSTGROUP_INFO m_groupInfoStc[USERMRG_FENZU+1];
extern std::map<int, CString>	m_mapSelfGroups;

extern Gdiplus::GdiplusStartupInput g_gdiplusStartupInput;
extern ULONG_PTR	g_gdiplusToken;
extern HMODULE		g_hRichEditDll;
extern FriendListItemInfo g_selfunit;

extern char g_szOpenUID[S_USERID_LEN]; //�򿪴���
extern CCriSec g_fileLock;
extern CFile  g_fileUserLog;

extern char g_chBuffer[MAX_BUF_SEND_LEN];
extern DWORD g_dwRoomID;

extern PKGRECVINFO g_strpkgrecvinfo;

extern PKGRECVINFO g_pack_info ; 
extern int iBufferIndex ; 
extern int		g_nRoomID_im2_0;	// ���赥������ʦֻ��һ�������Ȩ�� 
extern CString g_strAddGroupName;   // ���ӵķ��� 
extern CString g_strDelGroupName ;  // Ҫɾ���ķ��� 
extern BOOL g_downPicLock  ;        // ��¼�Ƿ�����ͼƬ  �߳��� 

#endif