/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��PaintDraw.h 
* �汾��  ��V1.0
* ��Ŀ���ƣ�CPH
* ��Ȩ������Copyright 2002-2003 . All Rights Reserved.
* ģ���������
*======================================================
* �汾�����¼:
*      v1.0  2002-10-30   20:30    ����һЩ�ο�������ɱ���
*
* 
*/

/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAINTDRAW_H__7FD19197_7DEB_43A7_B4E8_D67A67BEC917__INCLUDED_)
#define AFX_PAINTDRAW_H__7FD19197_7DEB_43A7_B4E8_D67A67BEC917__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\\INCLUDE\\DIBitmap.h"	//���Ӷ�DIBͼ���֧��
/////////////////////////////////////////////////////////////////////////////
// CPaintDraw window

class CPaintDraw : public CWnd
{
// Construction
public:
	CPaintDraw();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaintDraw)
	//}}AFX_VIRTUAL

// Implementation
public:
	INT m_pointY;
	INT m_pointX;
	virtual ~CPaintDraw();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CPaintDraw)
	afx_msg void OnPaint();
     afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAINTDRAW_H__7FD19197_7DEB_43A7_B4E8_D67A67BEC917__INCLUDED_)
