/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��BitmapDialog.h
* �汾��  ��v1.0
* ��Ŀ���ƣ�CPH
* ��Ȩ������Copyright 2002-2003 . All Rights Reserved.
* ģ�������������һ����λͼ��Ϊ�Ի��򱳾��ĶԻ������ͷ�ļ�
*                �����Ϊ�滭��԰���еĲ�ɫͼ�ζԻ���Ļ���
*======================================================
* �汾�����¼:
*      v1.0  2002-10-30   20:30   ����һЩ�ο�������ɱ���
*
* 
*/

/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BITMAPDIALOG_H__55BE67E3_17E6_11D2_9AB8_0060B0CDC13E__INCLUDED_)
#define AFX_BITMAPDIALOG_H__55BE67E3_17E6_11D2_9AB8_0060B0CDC13E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "DIBitmap.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
/*
*����    : CBitmapDialog
*˵��    : ��λͼ��Ϊ�Ի���ı�������(֧�ֵ�ͼ���졢���С�������ʾ��֧�ֶԻ������)
*�����¼:
*
*/

class  CBitmapDialog : public CDialog
{
// Construction
public:
	CBitmapDialog();         
	CBitmapDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);  //++++                    
   CBitmapDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);     //++++
	                          
protected:  
	RECT m_WorkArea;
	virtual void WrapUpDlg();
	virtual void ThrowOpenDlg();

	BOOL m_bAreDisplaySettingsChanged;
	BOOL m_bAreDisplaySettingsSaved;
	DEVMODE m_SaveDevMode;

	BOOL m_bIsToolBarHidden;
	BOOL m_bWasToolBarVisible;

	CRect m_DlgRect;

	void Init();
public:
	enum {		
		BITMAP_STRETCH=0,		// λͼ�����췽ʽ���Ի���
		BITMAP_TILE,		   // λͼ������ߴ������Ի���
		BITMAP_CENTER			//λͼ������ʾ�ڶԻ�����
	};


// Attributes
public:
	BOOL	SetBitmap(UINT uResource, int Type = CBitmapDialog::BITMAP_TILE);
	BOOL	SetBitmap(LPCSTR lpszBitmap, int Type = CBitmapDialog::BITMAP_TILE);

// Dialog Data
protected:
	//{{AFX_DATA(CBitmapDialog)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBitmapDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CDIBitmap	m_bmpBackground;
	int			m_nType;		
	CBrush		m_HollowBrush;

	// Generated message map functions
	//{{AFX_MSG(CBitmapDialog)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);

	//�������������ڶԻ�����󻯴���
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void	CommonConstruct();
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITMAPDIALOG_H__55BE67E3_17E6_11D2_9AB8_0060B0CDC13E__INCLUDED_)
