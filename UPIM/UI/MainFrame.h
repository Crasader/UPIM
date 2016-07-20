#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include "SkinChangeEvent.h"
#include "UIFriends.h"
#include "UIGroups.h"
#include "GeneralDialog.h"
#include "UserMrgDialog.h"
#include <GdiplusHeaders.h>
#include "MsgNotifyDialog.h"
#include <CommCtrl.h> 

#pragma   comment(lib,   "comctl32.lib")



class MainFrame : public WindowImplBase
{
public:
	MainFrame();
	~MainFrame();

public:
	typedef enum _TrayIconMessage  // ���������ͼ������Ĳ�ͬ״̬ 
	{
		WM_MOUSE_ICON_ENTRY = 0x00F0 ,  // ���� 
		WM_MOUSE_ICON_HOVER ,           // ��ͣ 
		WM_MOUSE_ICON_LEAVE,             // �뿪 
	}TrayIconMessage;

public:
	LPCTSTR GetWindowClassName() const;	
	virtual void OnFinalMessage(HWND hWnd);
	virtual void InitWindow();
	virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual UILIB_RESOURCETYPE GetResourceType() const;
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);  
	virtual LPCTSTR GetResourceID() const;
	LRESULT MessageNotify(TrayIconMessage uMsg) ;  // �������������������¼�
	LRESULT OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void NotifyMessage(DWORD dwMessage, HICON hIcon, LPCSTR szTips);
    void SetBkColor(DWORD dwBackColor);
	void SetBkInfo();
	void SetNotifyIcon();
	void SetNotifyIcon( EUSERSTATE state ) ;  // ���ݲ�ͬ��״̬  ���ò�ͬ��ͼ��  
	void StartLogin();
	void CreatePublicUserNode(int nPID, LPCSTR szUID);	// ������Ա�յ����ں���Ϣ��ʱ����ʱ�����ڵ�
	void CreateTgRoomUserNode(int nRID, LPCSTR szUID);	// ����ʦ�յ��ͻ�������ʱ����ʱ�����ڵ�
	void OnNotifyIcon(WPARAM wParam , LPARAM lParam);
	void OnMenuClick(WPARAM wParam , LPARAM lParam);
	CDuiString	GetMainBkImage();
	DWORD GetMainBkColor();
	BOOL GetIteratorOfID(FriendList_ITER &friend_iterator, CDuiString strID, EVTTYPE eType, BOOL id = TRUE);
	BOOL SetIteratorState(CDuiString strID, EVTTYPE eType, int nState, BOOL id = TRUE);
	void OnExit();
	void CheckConnectStatus();
	int GetClientOnlineCount() ;
	std::vector<USER_ROOMCLIENT_INFO>* GetOnlineClientInfo() ; 
	void DeleteFriend(CDuiString strName) ; 
	void DeleGroup(CString strGroupName ,CString strGroupID) ;

protected:	
	void FriendNodeClick(TNotifyUI& msg);	// �����б�˫���¼�
	void GroupNodeClick(TNotifyUI& msg);	// Ⱥ��/�Զ������˫���¼�
	void RecentNodeClick(TNotifyUI& msg);	// �����ϵ�˷���˫���¼�
	void FindFriendNodeClick(TNotifyUI& msg ) ;  // wuchao add at 2016-04-06 
	void Notify(TNotifyUI& msg);
	void OnPrepare(TNotifyUI& msg);
	void OnTimer(TNotifyUI& msg);
	void OnUserListRClick(TNotifyUI& msg);
	void OnMainMenuClick(TNotifyUI& msg);
	void OnListItemClick(TNotifyUI& msg);
	void OnListItemActivate(TNotifyUI& msg);
	void OnStateMenuClick(TNotifyUI& msg);
	//////////////////////////////////////////////////////////////////////////
	// btn��Ӧ
	void OnBtn_Min(TNotifyUI& msg);					// ��С����ť
	void OnBtn_Max(TNotifyUI& msg);					// ��󻯰�ť
	void OnBtn_Restore(TNotifyUI& msg);				// ��ԭ��ť
	void OnBtn_Close(TNotifyUI& msg);				// �رհ�ť
	void OnBtn_ChangeBkSkin(TNotifyUI& msg);		// ����������ť
	void OnBtn_UserMrg(TNotifyUI& msg);				// ���ѹ�����
	void OnBtn_SearchFriend(TNotifyUI &msg) ;       // �������� 
	// menu��Ӧ
	void OnMenu_FriendOpen();
	void OnMenu_FriendInfo();
	void OnMenu_FriendHistroy();
	void OnMenu_CreateGroup();
	void OnMenu_UserOnline();						// �û�����
	void OnMenu_UserOffline();						// �û�����
	void OnMenu_UserLiKai();						// �û��뿪
	void OnMenu_GroupOpen();
	void OnMenu_GroupQuit();
	void OnMenu_CreateSubGroup();					// ��������
	void OnMenu_ModifySubGroup();					// �޸ķ���
	void OnMenu_DeleteSubGroup();					// ɾ������
	       
	// ��������Ϣʱ������ƶ�������ͼ��ʱ����ʾ����Ϣ���ѵ���Ϣ ����QQ���� 
	void OnShowNotifyDialog() ; 
	void OnCloseNotifyDialog() ;

	// �ͻ�����  ���������ڵ��λ�� 
	void ExchangeNode(CFriendsUI* friendList ,Node* firstNode ,Node* secondNode) ;
	int FindInsertNode(std::vector<USER_ROOMCLIENT_INFO> clientList,Node *pInsertNode) ; // �ں����б����ҵ�����������λ�� 
public:
	void UpdateFriendsList();
	void UpdateGroupsList();
	void UpdateRecentList();
	void CreateMsgNotifyDlg();
	void KillMyTimer() ; 
	void AddMyTimer() ; 
	// im2.0 ������ʦ���ѵ�¼ʱ�����º����б�  ����  �����ϵ��  
	void UpdateFriendsListInFxs(CDuiString strID, int nstate);
	void UpdateGroupsListInFxs(Node* pGroupNode ,CDuiString strID, int nstate);
	void UpdateRecentListInFxs(CDuiString strID, int nstate);
	void ReloadFriendList(Node *pParendNode) ; 
	void InsertFriendsIntoVector(FriendListItemInfo* m_unit);
	void UpdateMyselfInfo(FriendListItemInfo* m_unit, CDuiString AppTitle);
	void AddStdGroupNode();
	void CreateGroupNode();
	void CreatePublicNode();
	void AddPublicAccNode();
	void CreateTgRoomNode();
	void CreateTgRoomNode2();
	void CreateRoomClientNode();
	void CreateRoomAnalysNode();
	void AddTgRoomAccNode();
	void CreateDeptNode();
	void CreateFriendNode();
	void CreateRoomNode();
	void CreateTgHisNode();
	void CreatSelfGroup();
	void AddSelfGroupClientNode(int nGroupID, Node* nodeptr = NULL);
	void AddSelfGroupClientNode( int nGroupID ,CString strClientID) ; 
	void DelSelfGroupClientNode( int nGroupID ,CString strClientID) ; 
	void CreateTgRoomHisNode();
	void ModifyDisRecentInfo(CDuiString m_strUserID, CDuiString m_strUserName, CDuiString m_LastWord, int n_Lastwordtime, int nRoomID);
	void CreateRecentNode(CDuiString m_strNodeID, CDuiString m_strUserName, CDuiString m_LastWord, long n_Lastwordtime);
	void AddTgRoomClientNode(long nRoomID, Node* nodeptr = NULL);
	BOOL OpenChatDiolog(CDuiString m_strUserID, FriendList_ITER iterator);
	BOOL OpenGroupChatDiolog(CDuiString m_strRoomID, FriendList_ITER iterator);
	//BOOL OpenChatDialog() ;

	// ��jpgת����ΪHICON
	void ConvertImageToHicon(CString strFileName) ; 

	void SetAppTitle(CDuiString m_strApptitle);
	void SetSelfInfo();
	void ModifySign(CDuiString m_strSign);
	
	BOOL ProcessRecvMsg(LPRECVMSG2 lpRecvMsg, BOOL bOffMsg = FALSE);			// �յ���Ϣ����д���
	BOOL ProcessRecvMsg(LPNEWRECVMSGPUBLIC lpRecvMsg);			// �յ���Ϣ����д���
	BOOL ProcessRecvGroupMsg(GROUP_CHAT_HIS_MSG* lpHisMsg);						// �յ���ʷȺ����Ϣ����д���
	BOOL ProcessRecvGroupMsg(gcrecvmsg_ans* lpRecvMsg, BOOL bOffMsg = FALSE);	// �յ�Ⱥ����Ϣ����д���
	BOOL GCGetList(ROOMID mRoomID);
	BOOL GetPublicRoute(PUBLICID mPublicID);
	void DeleteRoomMember(ROOMID mRoomID, LPCTSTR szID, short nUserType);
	void SetControlVisable();
	BOOL SetMainFace(EUSERSTATE nstate, LPCSTR szFile = "");							//�����Լ�ͷ��
	BOOL SetMainFace2(EUSERSTATE nstate, LPCSTR szFile1 = "", LPCSTR szFile2 = "");		//�����Լ�ͷ��  
	BOOL SetAnalysNodeHead(EUSERSTATE nstate, int nRoomID, int nAnalysID, LPCSTR szFile1 = "", LPCSTR szFile2 = "");	//���ú���ͷ�� �ͻ��汾  ���÷���ʦ��ͷ�� 
	BOOL SetClientNodeHead(EUSERSTATE nstate, CString strClientID, LPCSTR szFile1 = "", LPCSTR szFile2 = "") ;//���ú���ͷ�� ����ʦ����  ���ÿͻ���ͷ��
	BOOL SetGroupClientNodeHead(EUSERSTATE nstate, USER_ROOMCLIENT_INFO userClientInfo, LPCSTR szFile1, LPCSTR szFile2 ) ; // ���÷���������ѵ�ͷ�� 
	BOOL SetAnalysNodeNickName(int nRoomID ,int onlineNums = 0 ,int totalNums = 0) ; 
	BOOL SetGroupNodeNickName( int nGroupID ,int onlineNums = 0 , int totalNums = 0 ) ; 
	void ReleaseUserData();
	void FlashAllItem();
	void StopFlashItem(CDuiString strID, EPANELTYPE e_pType);
	void InsertIntoFlashVt(CDuiString strID, EPANELTYPE e_pType);
	BOOL SendStateNotify(int nstate);
	void UserStateChange(CDuiString strID, int nstate); // ����ʦ��¼ �ͻ��������� 
	void AnalystStateChange(CDuiString strID, int nstate) ; // �ͻ���¼ ����ʦ�������� 
	void AddTimer(UINT nTimerID, UINT uElapse);
	void ImSvrOff();											// �������ر�
	void UserKickOff();											// ��ص�¼
	CString GetNotifyiconToolTip();
	void NotifyiconFlash();
	void StopNotifyiconFlash();
	void SetNotifyiconFlash();
	void GetClientRights(CString strUpID);
	CString GetUserPicURL(CString strUpID);
	BOOL DownLoadPic(CString strUrl, CString strFile);
	void OpenRightsDlg();
	void CloseWhoSendMsg() ; // �����Ϣ���ͷ� 
	void GetAllFXSState() ; 

	void SwitchTable() ; 
	void ClearFindFriendList() ; 

	LRESULT OnUIMessageLoop(WPARAM wParam, LPARAM lParam);		// UI_MessageLoop
	LRESULT OnKeyUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled); 
	LRESULT OnEnterUp() ;
	LRESULT OnUserColse(WPARAM wParam, LPARAM lParam);			// �ر�	
	LRESULT OnUserLoginIN(WPARAM wParam, LPARAM lParam);		// ��¼
	LRESULT OnUserOffLine(WPARAM wParam, LPARAM lParam);		// ����
	LRESULT OnUserOnLine(WPARAM wParam, LPARAM lParam);			// ����
	LRESULT OnUserADDGroup(WPARAM, LPARAM);
	LRESULT OnSetSelfInfo(WPARAM, LPARAM);
	LRESULT OnAddFriendInfo(WPARAM, LPARAM);
	LRESULT OnUserADDPublic(WPARAM, LPARAM);
	LRESULT OnUserADDTgRoom(WPARAM, LPARAM);
	LRESULT OnUserADDTgRoom2(WPARAM, LPARAM);
	LRESULT OnADDRoomClient(WPARAM, LPARAM);
	LRESULT OnADDRoomAnalys(WPARAM, LPARAM);
	LRESULT OnUserStateChange(WPARAM wParam, LPARAM lParam);
	LRESULT OnOpenWND(WPARAM wParam, LPARAM lParam);
	LRESULT OnSoundPlay(WPARAM wParam, LPARAM lParam);
	LRESULT OnAddRoom(WPARAM wParam, LPARAM lParam);
	LRESULT OnLeaveRoom(WPARAM wParam, LPARAM lParam);
	LRESULT OnGetUserPic(WPARAM wParam, LPARAM lParam);
	LRESULT OnCreatSelfGroup(WPARAM wParam, LPARAM lParam);
	LRESULT OnGetSelfPic(WPARAM wParam, LPARAM lParam);
	LRESULT OnOpenRight(WPARAM wParam, LPARAM lParam);
	LRESULT OnLoadRecentClientNode(WPARAM wParam, LPARAM lParam) ;  // ���������ϵ�� 
	LRESULT OnOpenChatDialog(WPARAM wParam, LPARAM lParam) ; 
	LRESULT OnFindFriends(WPARAM wParam, LPARAM lParam) ;    // wuchao add at 2016-04-05 ���Һ��� 
	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled); 
	LRESULT OnAddNewPublic(WPARAM wParam, LPARAM lParam);
	LRESULT OnAddNewLastUser(WPARAM wParam, LPARAM lParam);
public:
	SkinChangedObserver					skin_changed_observer_;
	CGeneralDialog*						pLoginDialog;

	BOOL								bLoginDialogClosed;
	map<CDuiString,bool> m_MenuCheckInfo;	//����˵���������Ϣ,Ӧ��Ϊÿ���˵�������һ��map,������ֻ����ѭ����ʽ�˵��Ĺ���
	map<CDuiString,bool> m_MenuLoopCheckInfo;
	 

	bool        m_isEnterLeave ; 
private:
	bool        m_bIsMsgDlgShow ;   // �Ƿ���ʾ��Ϣ��ʾ�� 
 	bool        m_bMouseEnter ;     // �������Ƿ��������ͼ��  
	bool		m_bIsIcon;

	int         m_nSwitchTab ;      // ��¼Tab�л���ҳ�� 

	EUSERSTATE  m_eUserState ;        // ��¼��ǰ�����û���״̬
	int			nDeirction;
	int			bk_image_index_;
	void *		m_pWave[4];	//װ����wave��Դ,��˳��ֱ���ϵͳ��Ϣ,�յ���Ϣ,�û�����
	bool								m_bSetSelfInfo;
	FriendListItemInfo					myself_info_;
	std::vector<FriendListItemInfo>     m_vecWhoSendMsg ; // wuchao add ��¼��Ϣ���ͷ�  
	vector <AnalystInfo> m_vtInfo;      // �ͻ��ķ���ʦ�б�  ��������ʦ������ 


	CDuiString							m_AppTitle;
	std::vector<FriendListItemInfo>		friends_;
	std::vector<FriendListItemInfo>		Recentfriends_;
	std::vector<FriendListItemInfo>		groups_;
	CMsgNotifyDialog m_NotifyDlg ;      // ��Ϣ��ʾ��   
	BOOL                                m_bRecvFriendsMsg ; // wuchao add �Ƿ����յ��˺��ѷ��͵���Ϣ����־����ʾMainFrame����ChatDialog
	HICON								m_hIcon ;           // ����  ͼ�� 
	HICON                               m_hOffLineIcon ;    // ����  ͼ�� 
	// �����û�ͷ��jgp��HICON֮���ת��
	Gdiplus::Bitmap   *m_hUserBitMap;

	// ������  ������Ϣʱ  ����ͼ������ 
	HICON m_hUesrIcon;
	NOTIFYICONDATA						m_noti;        // ����  
	SELECTNODE							m_MainSelectNode;
	CCriticalSection					m_csNodeFlash;
	CCriticalSection					m_csNodeFlash2;
	CCriticalSection					m_csNodeFlash3;
	CCriticalSection					m_csStateInfo;
private:
	CButtonUI * m_pMinSysBtn, * m_pMaxSysBtn, * m_pRestoreSysBtn, * m_pCloseSysBtn ,*m_pSearchBtn ,*m_pSearchCloseBtn;
	CTabLayoutUI* m_pControlSwitch;  // wuchao add at 2016-04-06  
	CRichEditUI* m_pSearch_edit ; 
	CRichEditUI* m_pSearch_edit_friend ; 

	CFriendsUI* m_pFriendsList;   // �����б� 
	CFriendsUI* m_pSelfGroup;     // �Զ������ 
	CFriendsUI* m_pFindFriendList ;  //wuchao add at 2016-04-06 �������� 
	CGroupsUI* m_pGroupsList;     
	CGroupsUI* m_pRecentLinkList; // �����ϵ��  
	CTabLayoutUI* m_pTabControl;
	CControlUI* m_pBackground;
	CRect     m_rtMsgDlg ; 
	//TrayIconMessage trayIconMessage ; 
	POINT m_ptMouseHover ;  //�����ͣ��λ��

public:
	// �ͻ������� 
	CUserMrgDialog *m_pUserMrgDialog  ; 
};



#endif // MAINFRAME_HPP

// ��web�����ȡ�ͻ���ͷ�� 
UINT DownUserPicFromWeb(PVOID pData ) ; 
// ��web�����ȡ����ʦ��ͷ�� 
UINT DownAnalysPicFromWeb(PVOID pData) ; 