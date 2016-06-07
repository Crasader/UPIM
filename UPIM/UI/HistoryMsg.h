#ifndef HISTORYMSG_HPP
#define HISTORYMSG_HPP

#include "SkinChangeEvent.h"
#include "UIGroups.h"
#include "RichEditUtil.h"
#include "FaceList.h"

class CHistoryMsgDialog : public WindowImplBase, public SkinChangedReceiver
{
public:
	CHistoryMsgDialog(const CDuiString& bgimage, DWORD bkcolor);
	~CHistoryMsgDialog();

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
	virtual BOOL Receive(SkinChangedParam param);

	BOOL InsertHistoryMSG(std::vector<CHAT_RECORD2>& vtRecord, LPCTSTR szSendName, LPCTSTR szSendId);
	void AddMsg_More(CRichEditUI * pRichEdit, LPCTSTR lpText, CFontInfo mfontInfo);
	BOOL HandleSysFaceId_More(CRichEditUI * pRichEdit, LPCTSTR& p, tstring& strText, CFontInfo mfontInfo);
	void _RichEdit_ReplaceSel_More(CRichEditUI * pRichEdit, LPCTSTR lpszNewText, CFontInfo mfontInfo);
	BOOL _RichEdit_InsertFace(CRichEditUI * pRichEdit, LPCTSTR lpszFileName, int nFaceId, int nFaceIndex);
	BOOL HandleSysFaceIndex_More(CRichEditUI * pRichEdit, LPCTSTR& p, tstring& strText, CFontInfo mfontInfo);
	BOOL HandleCustomPic_More(CRichEditUI * pRichEdit, LPCTSTR& p, tstring& strText, CFontInfo mfontInfo);

	void AddMsgToHisMSGEdit(LPCTSTR lpText, CFontInfo mfontInfo, bool bisselfmsg=false, CDuiString sid="", CDuiString sname="", CDuiString strSendTime="");

	void LoadMemList();
	void CreateGroupNode();				// ����ڵ�
	void CreateDeptNode();				// ���Žڵ�
	void CreateFriendNode();			// ���ѽڵ�
	void CreateRoomNode();				// Ⱥ�Ľڵ�
	void CreateOtherNode();				// �����ڵ�
	void CreateTgRoomNode();			// ����ʦ�����ڵ�
	void AddTgRoomAccNode();			// ����ʦ�ķ���ڵ�
	void AddTgRoomClientNode(long nRoomID, Node* nodeptr = NULL);			// �������û��ڵ�
protected:	
	void Notify(TNotifyUI& msg);
	void OnPrepare(TNotifyUI& msg);
	void OnExit();
	void OnTimer(TNotifyUI& msg);
	void OnListItemClick(TNotifyUI& msg);

	void OnBtn_Min(TNotifyUI& msg);
	void OnBtn_Max(TNotifyUI& msg);
	void OnBtn_Restore(TNotifyUI& msg);
	void OnBtn_Close(TNotifyUI& msg);
private:	
	CDuiString	bgimage_;
	DWORD		bkcolor_;
	ROOMID		nRoomID; 
	CGroupsUI*	pGroupsList;
	CRichEditUI* m_pHisMsgEdit;
	CFaceList m_FaceList;
};

#endif // HISTORYMSG_HPP