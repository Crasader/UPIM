
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "OutputWnd.h"
#include "LinkManager.h"
#include "GroupChatManage.h"
#include "PublicManage.h"
#include "CustSvrMng.h"
#include "MongoDBMgr.h"
#include <vector>
#include "FXSHDManage.h"

extern CLinkManager		g_LinkMangaer;
extern CGroupChatManage g_GroupChatMng;
extern CPublicManage	g_PublicMng;
extern CFXSHDManage     g_FxsHDManage;
extern CCustSvrMng		g_custSvrMng;
extern CMongoDBMgr		g_MongoDBMgr;
extern LONG g_MainFrmThreadState;

#define LIST_USERINFO_TIMER 1
class CMainFrame : public CFrameWndEx
{

protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
private:
	
	static PackInfo m_curPackInfo;
	HANDLE m_StatThread;
	HANDLE m_HttpThread;
	
// ����
public:
	static std::vector<int>    m_statList[5];
	HANDLE m_StartEvent;
	volatile static LONG m_bOnLineOrOffLine;
	volatile static LONG m_bStart;
// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	COutputWnd        m_wndOutput;
	int               m_iStart;// 0��ʼ 1 ֹͣ
	int               m_iStop;
	CMenu             m_sysMenu[3];

public:
	BOOL InitInst();
	BOOL ExitInst();
	VOID SendSvrOffMSG();

	CFXSHDManage     m_FxsHDManage;
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnSet();
	afx_msg void OnHelp();
	afx_msg void OnUpdateToolBar(CCmdUI* pCmdUI);
	afx_msg LRESULT OnUserInfoMsg(WPARAM wp, LPARAM lp);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
	static int StatPeakData(std::vector<int> &dList,int data);
private:
	static UINT WINAPI StatSever(LPVOID pv);
	

public:
	afx_msg void OnUpdateMenuState(CCmdUI *pCmdUI);
	afx_msg void OnMenuStart();
	afx_msg void OnMenuStop();
};


