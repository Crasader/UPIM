/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��ButtonST.h
* �汾��  : V1.0
* ��Ŀ���ƣ�CPH
* ��Ȩ������Copyright 2002-2003 . All Rights Reserved.
* ģ���������ͼ�갴Ŧ�ؼ���ģ���ļ�
*======================================================
* �汾�����¼:
*
*   v1.0  2001	              Davide Calabro'		davide_calabro@yahoo.com
*   v1.1  2002-10-30   20:30      
*         2002-11-6    16:30  ���Ӻ���SetBitmap() Ϊ���������˷����ⲿBMP��ICO�ļ��Ĺ���
*                            
* 
*/

/////////////////////////////////////////////////////////////////////////////

//
#ifndef _BTNST_H
#define _BTNST_H

#include "DIBitmap.h"	// Added by ClassView
#include "showwnd.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//ȡ�������ע�Ϳ���ʹ��Ŧ��EXPLORE��ʽ 
//#define ST_LIKEIE

// ����ֵ
#ifndef	BTNST_OK
#define	BTNST_OK						0
#endif
#ifndef	BTNST_INVALIDRESOURCE
#define	BTNST_INVALIDRESOURCE			1
#endif
#ifndef	BTNST_FAILEDMASK
#define	BTNST_FAILEDMASK				2
#endif
#ifndef	BTNST_INVALIDINDEX
#define	BTNST_INVALIDINDEX				3
#endif

enum {LDOWN=0, LCLICK,LPOPMENU};
//////////////////////////////////////////////////////////////////////////
//#include "Cartoon.h"
/*
*����    : CButtonST
*˵��    : ��̬ͼ�갴Ŧ��
*�����¼:
*
*/
   

class CButtonST : public CButton
{
public:
    CButtonST();
	~CButtonST();
    UINT m_downmessage;
    enum {ST_ALIGN_HORIZ, ST_ALIGN_VERT, ST_ALIGN_HORIZ_RIGHT};

	enum	{	BTNST_COLOR_BK_IN	= 0,		//������ڰ�Ŧ��ʱ�ı���ɫ
				BTNST_COLOR_FG_IN,				//������ڰ�Ŧ��ʱ���ı�ɫ
				BTNST_COLOR_BK_OUT,				//������뿪��Ŧʱ�ı���ɫ
				BTNST_COLOR_FG_OUT,				//������뿪��Ŧʱ���ı�ɫ 

				BTNST_MAX_COLORS                //��������ɫ��
			};

	// ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CButtonST)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

public:
	INT GetBtnID();
	void StopPlayTipSound();
	void PlayTipSound(CString fileName);
	int m_nCount;
	void SetShowHelp (int nIndex, CRect rect);
	void SetHitTestStyle(LRESULT style);
	LRESULT m_HitTestStyle;

	BOOL m_isFirst;
	CShowWnd * pShowWnd;

	BOOL SetBtnCursor(HCURSOR hCursor);
	void SetLbuttonSendMsgStyle(INT msgstyle);
	//��ͨ��Ŧ��ӦҪ���õ�ͼ���ļ���
	CString m_strPictureFileName;
	CDIBitmap m_dibmap;
	DWORD SetBitmaps(LPCSTR strBitmapIn, COLORREF crTransColorIn, LPCSTR  strBitmapOut, COLORREF crTransColorOut);
	DWORD SetIcon(LPCSTR strIconIn, LPCSTR strIconOut);
	DWORD SetAutoRepeat(BOOL bSet, DWORD dwMilliseconds = 100);
	DWORD SetURL(LPCTSTR lpszURL);
	DWORD GetColor(BYTE byColorIndex, COLORREF* crpColor);
	DWORD SetColor(BYTE byColorIndex, COLORREF crColor, BOOL bRepaint = TRUE);
	DWORD SetDefaultColors(BOOL bRepaint = TRUE);
	int GetCheck();
	void SetCheck(int nCheck, BOOL bRepaint = TRUE);
	void DrawTransparent(BOOL bRepaint = FALSE);

	BOOL GetDefault();

	void SetTooltipText(int nId, BOOL bActivate = TRUE);
	void SetTooltipText(LPCTSTR lpszText, BOOL bActivate = TRUE);
	void ActivateTooltip(BOOL bEnable = TRUE);

	BOOL SetBtnCursor(int nCursorId = NULL);

	void SetFlatFocus(BOOL bDrawFlatFocus, BOOL bRepaint = FALSE);
	BOOL GetFlatFocus();

	void SetShowText(BOOL bShow = TRUE);
	BOOL GetShowText();

	void SetAlign(int nAlign);
	int GetAlign();

	void SetFlat(BOOL bState = TRUE);
	BOOL GetFlat();

	void DrawBorder(BOOL bEnable = TRUE);
	DWORD SetIcon(int nIconInId, int nIconOutId = NULL);
	DWORD SetIcon(HICON hIconIn, HICON hIconOut = NULL);

	DWORD SetBitmaps(int nBitmapIn, COLORREF crTransColorIn, int nBitmapOut = NULL, COLORREF crTransColorOut = 0);
	DWORD SetBitmaps(HBITMAP hBitmapIn, COLORREF crTransColorIn, HBITMAP hBitmapOut = NULL, COLORREF crTransColorOut = 0);

	static short GetVersionI()		{return 31;}
	static LPCTSTR GetVersionC()	{return (LPCTSTR)_T("3.1");}

protected:
    //{{AFX_MSG(CButtonST)
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSysColorChange();
	afx_msg BOOL OnClicked();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnCancelMode();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
private:
	void CancelHover();
	void PrepareImageRect(BOOL bHasTitle, RECT* rpItem, CRect* rpTitle, BOOL bIsPressed, DWORD dwWidth, DWORD dwHeight, CRect* rpImage);
	HBITMAP CreateBitmapMask(HBITMAP hSourceBitmap, DWORD dwWidth, DWORD dwHeight, COLORREF crTransColor);
	void DrawTheBitmap(CDC* pDC, BOOL bHasTitle, RECT *rItem, CRect *rCaption, BOOL bIsPressed, BOOL bIsDisabled);
	void FreeResources(BOOL bCheckForNULL = TRUE);
	void DrawTheIcon(CDC* pDC, BOOL bHasTitle, RECT* rpItem, CRect* rpTitle, BOOL bIsPressed, BOOL bIsDisabled);
	void InitToolTip();
	void PaintBk(CDC* pDC);

	int		m_nAlign;
	BOOL	m_bShowText;
	BOOL	m_bDrawBorder;
	BOOL	m_bIsFlat;
	BOOL	m_bMouseOnButton;
	BOOL	m_bDrawFlatFocus;
	BOOL	m_bAutoRepeat;
	HWND	m_hWndAutoRepeat;
	UINT	m_nMsgAutoRepeat;
	DWORD	m_dwPeriodAutoRepeat;

	HCURSOR m_hCursor;
	CToolTipCtrl m_ToolTip;

	int       m_nIndex;
	CRect     m_rectHelp;

#pragma pack(1)
	typedef struct _STRUCT_ICONS
	{
		HICON		hIcon;			// ͼ����
		DWORD		dwWidth;		// ͼ����
		DWORD		dwHeight;		// ͼ��߶�
	} STRUCT_ICONS;
#pragma pack()

#pragma pack(1)
	typedef struct _STRUCT_BITMAPS
	{
		HBITMAP		hBitmap;		// λͼ���
		DWORD		dwWidth;		// λͼ���
		DWORD		dwHeight;		// λͼ�߶�
		HBITMAP		hMask;			// ����λͼ���
		COLORREF	crTransparent;	// ͸��ɫ
	} STRUCT_BITMAPS;
#pragma pack()

	STRUCT_ICONS	m_csIcons[2];
	STRUCT_BITMAPS	m_csBitmaps[2];

	CDC			m_dcBk;
	CBitmap		m_bmpBk;
	CBitmap*	m_pbmpOldBk;
	BOOL		m_bDrawTransparent;

	BOOL		m_bIsDefault;
	BOOL		m_bIsCheckBox;
	int			m_nCheck;

	COLORREF	m_crColors[BTNST_MAX_COLORS];

	TCHAR		m_szURL[_MAX_PATH];

protected:
	CPoint m_mousePoint;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif
