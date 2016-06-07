#ifndef _USECBYTSDIALOG_
#define _USECBYTSDIALOG_


/////////////////////////////////////////////////////////////////////////////////////
//
// ����Ͷ�߷����Ի���  

/////////////////////////////////////////////////////////////////////
// �ͻ�Ͷ��OR���� �ṹ�� 
/////////////////////////////////////////////////////////////////////
struct ClientComment
{
	int nType ; // Ͷ��Ϊ1  ����Ϊ2 
	CString strPhoneNum ; // �绰���� 
	CString strBehavior ; // �ٱ�����ʦ����Ϊ  
	CString strMsg ;      // ����˵�� 

	ClientComment()
	{
		nType = 0 ; 
		strPhoneNum = strBehavior = strMsg = _T(" ") ; 
	}
};


class CBytsDialog : public WindowImplBase
{
public:
	CBytsDialog(CDuiString strMyselfName ,CDuiString strMyselfID ,CDuiString strAnayName ,CDuiString strAnayID);
	CBytsDialog(LPCTSTR lpMyselfName ,LPCTSTR lpMyselfID ,LPCTSTR lpAnayName ,LPCTSTR lpAnayID);
	~CBytsDialog();

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

	void OnBtnSubmit(TNotifyUI& msg) ; 
	BOOL CheckPhoneNum() ;

	// ��ʾWebҳ�� 
	CWebBrowserUI* m_pActiveX_Web ;

protected:	
	void Notify(TNotifyUI& msg);
	void OnPrepare(TNotifyUI& msg);
	void OnTimer(TNotifyUI& msg);
	void OnListItemClick(TNotifyUI& msg);
	void OnCloseBtnClick(TNotifyUI& msg);
	void OnOpenBtnClick(TNotifyUI& msg);
	void OnSelectCheckBox(TNotifyUI& msg) ;
	void SwitchInterface(int nSwitch) ; 
	void OnBtn_Min(TNotifyUI& msg) ;
	void OnBtn_Max(TNotifyUI& msg) ;

public:
	void OnExit();
private:
	CButtonUI * m_pMinSysBtn, * m_pMaxSysBtn, * m_pRestoreSysBtn, * m_pCloseSysBtn;
	CButtonUI * m_pSubmitBtn;


	CRichEditUI *m_pBCSMEdit ; // ���ﲹ��˵��Edit 
	CRichEditUI *m_pTSBCSMEdit ; // Ͷ�߲���˵��Edit

	CEditUI *m_pPhoneNumEdit ; 

	CCheckBoxUI *m_pTSCheckBox;  // Ͷ�߷���ʦ   
	CCheckBoxUI *m_pBYCheckBox;  // �������ʦ 

	CComboUI* m_pFxsBehaviorList; // �ٱ�����ʦ��Ϊ�б� 

	CTabLayoutUI* m_pControlSwitch; // �л�����ؼ� 
	CDuiString m_strMyselfName ;
	CDuiString m_strMyselfID ;
	CDuiString m_strAnayName ;
	CDuiString m_strAnayID ; 

	
	LPCTSTR m_lpMyselfName ;
	LPCTSTR m_lpMyselfID ;
	LPCTSTR m_lpAnayName ;
	LPCTSTR m_lpAnayID ;
	 
private:
	int m_nSwitch ; // ��ʾͶ�߷���ʦ���滹�Ǳ������ʦ������Ʊ���  Ĭ��Ϊ0 ��ʾͶ�߷���ʦ���� 
};

#endif // _USECBYTSDIALOG_
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////