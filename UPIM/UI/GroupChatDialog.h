#ifndef CHATDIALOG_HPP
#define CHATDIALOG_HPP

#include "SkinChangeEvent.h"
#include "UIFriends.h"
#include "FaceSelDlg.h"
#include "FaceList.h"
#include "IImageOle.h"
#include "FileDialogEx.h"
#include "UIMenu.h"
#include "PicBarDlg.h"
#include "../MsgQueueSendMng.h"
#include "RichEditUtil.h"

class CFontInfo				// ������Ϣ
{
public:
	CFontInfo(void);
	~CFontInfo(void);

public:
	int m_nSize;			// �����С
	COLORREF m_clrText;		// ������ɫ
	tstring m_strName;		// ��������
	BOOL m_bBold;			// �Ƿ�Ӵ�
	BOOL m_bItalic;			// �Ƿ���б
	BOOL m_bUnderLine;		// �Ƿ���»���
};

class ChatDialog : public WindowImplBase, public SkinChangedReceiver
{
public:
	ChatDialog(const CDuiString& bgimage, DWORD bkcolor, const FriendListItemInfo& myselft_info, const FriendListItemInfo& friend_info, bool bGroupSend=false);
	~ChatDialog();

public:
	LPCTSTR GetWindowClassName() const;	
	virtual void OnFinalMessage(HWND hWnd);
	virtual void InitWindow();
	virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual BOOL Receive(SkinChangedParam param);
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void SetTextColor(DWORD dwColor);

    void SendMsg();
	void SendMsg_More();
	COMPLEX_MSG_DATA* GetMsgData(BOOL bOnLine=TRUE,CString strFileInfo="",CString strProductName="");
	COMPLEX_MSG_DATA* GetMsgData_More(BOOL bOnLine=TRUE,CString strFileInfo="",CString strProductName="");
	void DeleteMsgData(COMPLEX_MSG_DATA*& pMsgData);
	void InsertChatHistory(RECEIVED_MSG *pMsg, LPCTSTR szSendName);
	void InsertChatHistory_More(RECEIVED_MSG *pMsg, LPCTSTR szSendName, LPCTSTR szSendId);
	BOOL ReadXmlMsgData(LPCSTR pszBuf, CRichEditUI* pRichEdit);

protected:	
	void Notify(TNotifyUI& msg);
	void OnPrepare(TNotifyUI& msg);
	void OnExit(TNotifyUI& msg);
	void OnTimer(TNotifyUI& msg);

	void OnBtn_Min(TNotifyUI& msg);
	void OnBtn_Max(TNotifyUI& msg);
	void OnBtn_Restore(TNotifyUI& msg);
	void OnBtn_Close(TNotifyUI& msg);
	void OnCbo_SelChange_FontName(TNotifyUI& msg);
	void OnCbo_SelChange_FontSize(TNotifyUI& msg);
	void OnBtn_Bold(TNotifyUI& msg);
	void OnBtn_Italic(TNotifyUI& msg);
	void OnBtn_UnderLine(TNotifyUI& msg);
	void OnBtn_Color(TNotifyUI& msg);
	void OnBtn_Font(TNotifyUI& msg);
	void OnBtn_Face(TNotifyUI& msg);
	void OnBtn_Image(TNotifyUI& msg);
	void OnBtn_Send(TNotifyUI& msg);

	void OnMenu_Cut(TNotifyUI& msg);		// �����С��˵�
	void OnMenu_Copy(TNotifyUI& msg);		// �����ơ��˵�
	void OnMenu_Paste(TNotifyUI& msg);		// ��ճ�����˵�
	void OnMenu_SelAll(TNotifyUI& msg);		// ��ȫ��ѡ�񡱲˵�
	void OnMenu_Clear(TNotifyUI& msg);		// ���������˵�
	void OnMenu_ZoomRatio(TNotifyUI& msg);	// ����ʾ�������˵�
	void OnMenu_SaveAs(TNotifyUI& msg);		// �����Ϊ���˵�
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnFaceCtrlSel(UINT uMsg, WPARAM wParam, LPARAM lParam);	// �����顱�ؼ�ѡȡ��Ϣ

	void _RichEdit_ReplaceSel(CRichEditUI * pRichEdit, LPCTSTR lpszNewText);
	void _RichEdit_ReplaceSel_More(CRichEditUI * pRichEdit, LPCTSTR lpszNewText, CFontInfo mfontInfo);
	BOOL _RichEdit_InsertFace(CRichEditUI * pRichEdit, LPCTSTR lpszFileName, int nFaceId, int nFaceIndex);
	BOOL HandleSysFaceId(CRichEditUI * pRichEdit, LPCTSTR& p, tstring& strText);
	BOOL HandleSysFaceIndex(CRichEditUI * pRichEdit, LPCTSTR& p, tstring& strText);
	BOOL HandleCustomPic(CRichEditUI * pRichEdit, LPCTSTR& p, tstring& strText);
	BOOL HandleSysFaceId_More(CRichEditUI * pRichEdit, LPCTSTR& p, tstring& strText, CFontInfo mfontInfo);
	BOOL HandleSysFaceIndex_More(CRichEditUI * pRichEdit, LPCTSTR& p, tstring& strText, CFontInfo mfontInfo);
	BOOL HandleCustomPic_More(CRichEditUI * pRichEdit, LPCTSTR& p, tstring& strText, CFontInfo mfontInfo);
	void AddMsg(CRichEditUI * pRichEdit, LPCTSTR lpText);
	void AddMsg_More(CRichEditUI * pRichEdit, LPCTSTR lpText, CFontInfo mfontInfo);
	void AddMsgToSendEdit(LPCTSTR lpText);
	void AddMsgToRecvEdit(LPCTSTR lpText);
	void AddMsgToRecvEdit_More(LPCTSTR lpText, CFontInfo mfontInfo, bool bisselfmsg=false, CDuiString sid="", CDuiString sname="", CDuiString strSendTime="");

private:
	void FontStyleChanged();
private:	
	CButtonUI * m_pMinSysBtn, * m_pMaxSysBtn, * m_pRestoreSysBtn, * m_pCloseSysBtn;
	CButtonUI * m_pFontBtn, * m_pFaceBtn, * m_pImageBtn;
	CComboUI * m_pFontNameCombo, * m_pFontSizeCombo;
	COptionUI * m_pBoldBtn, * m_pItalicBtn, * m_pUnderLineBtn;
	CButtonUI * m_pColorBtn;
	CButtonUI * m_pCloseBtn, * m_pSendBtn;
	CRichEditUI* m_pSendEdit, * m_pRecvEdit;

	CFaceSelDlg m_FaceSelDlg;
	CPicBarDlg m_PicBarDlg;

	CFaceList m_FaceList;
	CFontInfo m_fontInfo;
	POINT m_ptRBtnDown;
	tstring m_strCheckMenu;
	IImageOle * m_pLastImageOle;
	int m_cxPicBarDlg, m_cyPicBarDlg;

	bool emotion_timer_start_;

	bool bold_;
	bool italic_;
	bool underline_;
	DWORD text_color_;
	DWORD font_size_;
	CDuiString font_face_name_;

	CDuiString bgimage_;
	DWORD bkcolor_;
	FriendListItemInfo myselft_;
	FriendListItemInfo friend_;
	bool bGroupSend_;
public:
	std::vector<UPIMID> m_vtUPIMID;
};

#endif // CHARTDIALOG_HPP