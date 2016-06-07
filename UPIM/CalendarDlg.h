// App.cpp : Defines the entry point for the application.
//
#pragma  once 
#include "stdafx.h"
class CCalendarDlg : public WindowImplBase
{
public :
	CCalendarDlg() ; 
	~CCalendarDlg() ; 

	LPCTSTR GetWindowClassName() const;	
	virtual void InitWindow();
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);
	virtual void OnFinalMessage(HWND hWnd);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

public :
	// ���ø�����  
	void SetParentWnd( HWND hWnd ) ; 
	// ��������
	void DrawCalendar(SYSTEMTIME m_sysTime) ; 

	// ����ϵͳʱ��m_sysTime�ڵ�ǰ�·��еڼ������� 
	int GetDayOfWeek(SYSTEMTIME m_sysTime) ; 

	// ������Y��M�µ����� 
	int GetMonthDays(int iY,int iM) ; 

	
	// ���ƾ���ÿ������ 
	void DrawBtnBackImage(CControlUI* pButtonUI,bool isEnable) ; 

	void SetMonth(int iMonth) ; 

	int GetMonth(CDuiString strMonth) ; 

	void SetDateTime(SYSTEMTIME sysDateTime) ;

	SYSTEMTIME& GetDateTime() ; 

protected:
	void Notify(TNotifyUI& msg) ; 
	void OnPrepare(TNotifyUI &msg ) ; 

	// ��һ�� 
	void OnBtnNextYear(TNotifyUI& msg) ; 
	// ��һ�� 
	void OnBtnPrevYear( TNotifyUI& msg ) ; 

	void OnBtnPrevMonth(TNotifyUI& msg) ; 

	// ��һ���� 
	void OnBtnNextMonth(TNotifyUI &msg) ;

	// ѡ������ 
	void OnBtnRiliClick(TNotifyUI &msg ,CString strControlName) ; 


private:
	// �����ھ�� 
	HWND pParenthWnd;
	// ϵͳʱ�� 
	SYSTEMTIME m_sysTime; 
	// 
	COleDateTime cTime;

	CString m_strDateTime ; 

	// ͨ������ѡ������� 
	SYSTEMTIME m_sysChooseDate ;

	// �·� 
	//CLabelUI *m_pMonthLabel ; 
	CTextUI *m_pMonthLabel ; 

	// ��ǰѡ������ 
	CTextUI* m_pCurrChooseYearLabel ; 

	// ��һ�� 
	CButtonUI *m_pBtnNext ;

	// ��һ�� 
	CButtonUI *m_pBtnPrev ; 

	// ��һ���� 
	CButtonUI *m_pBtnPrevMonth ;

	// ��һ���� 
	CButtonUI *m_pBtnNextMonth ; 

};