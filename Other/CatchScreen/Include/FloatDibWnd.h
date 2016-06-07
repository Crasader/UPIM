/**
*   FloatDibWnd.h		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   ����ѡȡ���ߵĳ������
*======================================================
*   �汾
*   Revision 1.0	2002/11/14    	  ���帡��������
*/

#if !defined(AFX_FLOATDIBWND_H__4C7B2E0E_42D4_4BB6_A954_E66A15C65264__INCLUDED_)
#define AFX_FLOATDIBWND_H__4C7B2E0E_42D4_4BB6_A954_E66A15C65264__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include  "Dib.h"
#include  "ENUM.h"
#include  "ButtonST.h"


typedef enum enuCHAGNE_TYPE
{
	CT_MOVE,			// �ƶ�
	CT_ROTATE,			// ��ת
	CT_HORMIRROR,		// ˮƽ����
	CT_VERMIRROR,		// ��ֱ����,����ת
	CT_RESIZE				// ����
}CHANGE_TYPE;



/*
*����: CFloatDibWnd
*˵�������帡��������
*�汾
*	Revision 1.0	2002/11/14     	 ��� CFloatDibWnd �Ļ�������
*/
class CFloatDibWnd : public CWnd  
{	
//	CRect     m_preRect;     //��ǰ�ͻ����������ߴ�


public:
	// �ĸ��α䰴ť
	CButtonST  m_btnRotate;	
	CButtonST  m_btnVerMirror;
	CButtonST  m_btnHorMirror;
	CButtonST  m_btnResize;


protected:
	CDib * m_pDib;			// ��ǰ��ͼDIB
	CDib * m_pSrcDib;		// ԭʼ��DIBͼ���Ա��α任ʱʧ����С
	CDib * m_pHistoryDib;   // �������ǰ��ͼ���Ա�Undo
	BOOL m_bCartoonWnd;
	
	// ����������Ը����ڵ���Ļλ��
	CRect m_rcWndRect;

	HWND m_hParentWnd;
	CHANGE_TYPE	m_ChangeType;
	CPoint m_ptLast;

	// ֧�� undo �� redo �����ݳ�Ա
	CRect m_rcHistoryWndRect;
	CHANGE_TYPE m_HistoryChangeType;


public:
	void CheckShowBtn();
	void SetCreateBtn(BOOL bCreateBtn = TRUE);
	BOOL IsCartoonWnd();
	CFloatDibWnd(HWND hParentWnd, const CString strFileName,INT curDrawSize=55);
	CFloatDibWnd(HWND hParentWnd, const CRect& rect,INT curDrawSize=55);
	CFloatDibWnd(HWND hParentWnd, CDib* pDib,INT curDrawSize=55);
	virtual ~CFloatDibWnd();
	BOOL CreateWnd();	

	void SetCartoonDib(CString strDibFileName);


	void DrawRotateBorder(double angle = 0);
	BOOL MergeDib(CDib * pDib);

	void HideAllButton();

	CDib* Copy();
	CDib* Cut();


protected:
	BOOL CreateButton();
	DOUBLE GetRotateAngle(CPoint ptEnd);
	CPoint PointToParentClient(const CPoint& point);
	CPoint GetArcEndPoint(const CPoint &ptCenter, double dwRadius, double eStartAngle, double eSweepAngle) const;
	CRect RectToParent();
	CRect RectToParent(const CPoint& point);
	CRect RectToParentClient();
	CRect RectToParentClient(const CPoint& point);
	void DrawResizeBorder(const CRect& rect) const;


protected:
	double m_dblPreRotateAngle;
	CPoint CountPoint(CPoint pointCenter, CPoint pointSide, double angle);
	BOOL RotateAngle(double angle);
	//{{AFX_MSG(CCartoon)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnMove(int x, int y);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBeginChange(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
   INT 	m_curDrawSize; //1-110
};

#endif // !defined(AFX_FLOATDIBWND_H__4C7B2E0E_42D4_4BB6_A954_E66A15C65264__INCLUDED_)
