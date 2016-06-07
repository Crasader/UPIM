#ifndef MSGNOTIFYDIALOG_HPP
#define MSGNOTIFYDIALOG_HPP

#include "SkinChangeEvent.h"
#include "UIFriends.h"


class CMsgNotifyDialog : public WindowImplBase
{
public:
	CMsgNotifyDialog(ECREATEDIALOGTYPE m_CreateType);
	~CMsgNotifyDialog();

public:
	LPCTSTR GetWindowClassName() const;	
	virtual void OnFinalMessage(HWND hWnd);
	virtual void InitWindow();
	virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

protected:	
	void Notify(TNotifyUI& msg);
	void OnPrepare(TNotifyUI& msg);
	void OnTimer(TNotifyUI& msg);
	void OnListItemClick(TNotifyUI& msg);
	void OnOKBtnClick(TNotifyUI& msg);
	void OnCloseBtnClick(TNotifyUI& msg);
	void OnOpenAllMsgBtnClick(TNotifyUI& msg) ; 
	void OnIgnoreAllMsgBtnClick(TNotifyUI& msg) ; 
public:
	void OnExit();
	void UpdateClientName( CDuiString strClientName ) ;
	void AddFriend(FriendListItemInfo friendInfo) ; 
	void InsertFrindToList() ; 
	void UpdateUserName(CDuiString strUserName) ; 
	void DeleteFriend(CDuiString strName) ;  
private:
	CButtonUI * m_pMinSysBtn, * m_pMaxSysBtn, * m_pRestoreSysBtn, * m_pCloseSysBtn;
	ECREATEDIALOGTYPE CreateType;
	CButtonUI *m_pCloseBtn, *m_pOKBtn ,*m_pSetBtn;
	CLabelUI  *m_pLabelClientName ; 
	CLabelUI  *m_pLabelUsername ; 

	CFriendsUI *m_pFriendList ;     // ������Ϣ���ĺ����б� 
	CButtonUI *m_pOpenAllMsgBtn ;   // �鿴������Ϣ 
	CButtonUI *m_pIgnoreAllMsgBtn ; // ����������Ϣ 

	std::vector<FriendListItemInfo> m_vecFriend ; // ������Ϣ���ĺ����б� 
	std::vector<FriendListItemInfo> friends_    ; // �Ѿ����뵽�˴��ڵĺ��� ��ֹ�ڶ��μ������� 

};

#endif // MSGNOTIFYDIALOG_HPP