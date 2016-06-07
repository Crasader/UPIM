/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��ColorPen.h 
* �汾��  ��V1.0
* ��Ŀ���ƣ�CPH
* ��Ȩ������Copyright 2002-2003 . All Rights Reserved.
* ģ������������ڵ�ɫ���ϵ�ȡɫ�ؼ�
*======================================================
* �汾�����¼:
*      v1.0  2002-11-5   10:00   
*
* 
*/

/////////////////////////////////////////////////////////////////////////////


#if !defined(AFX_COLORPEN_H__56E5C364_F095_11D6_95DA_000795D2C55B__INCLUDED_)
#define AFX_COLORPEN_H__56E5C364_F095_11D6_95DA_000795D2C55B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DefineMessage.h"   //�Զ�����Ϣ
/////////////////////////////////////////////////////////////////////////////
/*
*����    : CColorPen
*˵��    : ��ɫ���ϵ�ѡɫ��Ŧ��
*�����¼:
*
*/

class CColorPen : public CWnd
{
// Construction
public:
	CColorPen();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorPen)
	//}}AFX_VIRTUAL

// Implementation
public:
	UINT m_ID;
	COLORREF m_pencolor;      //��ǰ��ѡȡ����ɫֵ
	BOOL     m_bSelect;       //�Ƿ񵥻�ѡ����
	BOOL     m_bsuckepen;      //�Ƿ�����ɫ��
	virtual ~CColorPen();

	// Generated message map functions
	void SetColor(COLORREF c1,COLORREF c2,COLORREF c3);
protected:
	//{{AFX_MSG(CColorPen)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg LRESULT OnMouseHover(WPARAM wParam,  LPARAM);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam,  LPARAM);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
protected:
	COLORREF m_OutSide;
	COLORREF m_InSide;
	COLORREF m_MiddleSide;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORPEN_H__56E5C364_F095_11D6_95DA_000795D2C55B__INCLUDED_)
