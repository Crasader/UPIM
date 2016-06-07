/**
*   ViewBig.h		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   ����Ŵ������ͼƬ�鿴����
*======================================================
*   �汾
*   Revision 1.0	2002/11/25    	  ����Ŵ�鿴������
*/

#if !defined(AFX_VIEWBIG_H__66EEADA8_5E99_423F_8A9F_7EBDF5EAEBFC__INCLUDED_)
#define AFX_VIEWBIG_H__66EEADA8_5E99_423F_8A9F_7EBDF5EAEBFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewBig.h : header file
//

#include "DIB.H"

// ����ͼƬ��ʾ������
const CRect CRectRECT_IMG0 =  CRect(29, 94, 29+160, 94+120);
const CRect CRectRECT_IMG1 =  CRect(214, 94, 214+160, 94+120);
const CRect CRectRECT_IMG2 =  CRect(399, 94, 399+160, 94+120);
const CRect CRectRECT_IMG3 =  CRect(29, 239, 29+160, 239+120);
const CRect CRectRECT_IMG4 =  CRect(214, 239, 214+160, 239+120);
const CRect CRectRECT_IMG5 =  CRect(399, 239, 399+160, 239+120);
const CRect CRectRECT_IMG6 =  CRect(29, 384, 29+160, 384+120);
const CRect CRectRECT_IMG7 =  CRect(214, 384, 214+160, 384+120);
const CRect CRectRECT_IMG8 =  CRect(399, 384, 399+160, 384+120);


/*
*����: CViewBig
*˵��������ͼƬ�Ŵ�鿴������
*�汾
*	Revision 1.0	2002/11/25    	 ��� CViewBig ��Ļ�������
*/
class CViewBig : public CWnd
{
public:
	BOOL m_bFirstView;
	CDib * m_srcDib;
	CDib * m_BigFrameDib;
	CDib * m_pDib;

protected:
	BOOL m_bBig;

private:
	//Ҫ���߿��ͼƬλ������
	INT m_nIndex;  
	//�Ƿ�õ����㣬�Ƿ񻭱߿�
	BOOL m_bFocus;    
	//�Ƿ��ѻ��߿�
	BOOL m_bDrawedFrm; 
	CString m_strViewFileName;
	CPoint m_point[5];

// Construction
public:
	CViewBig();
	virtual ~CViewBig();

// Implementation
public:
	void ShowWnd();
	void HideWnd();
	void DrawSmall();
	void DrawBig();
	void DrawFrame(BOOL isDraw);
	BOOL GetPreFocus();
	INT GetPrePos();
	void SetPreFocus(BOOL bFocus);
	void SetPrePos(INT index);
	void SetBig(BOOL isBig);
	void SetViewBitmap(CString strfile);

	// Generated message map functions
protected:
	//{{AFX_MSG(CViewBig)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWBIG_H__66EEADA8_5E99_423F_8A9F_7EBDF5EAEBFC__INCLUDED_)
