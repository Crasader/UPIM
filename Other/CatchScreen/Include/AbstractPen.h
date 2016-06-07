/**
*   AbstractPen.h		
*   Version 2.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   ������ֻ��ʵĳ�����࣬��ȡȡ�����ӿ�
*======================================================
*   �汾
*   Revision 1.0	2002/11/1     	 ���� CAbstractPen �࣬���� PEN_STYLE ö������
*	
*	Revision 2.0	2002/11/12    	 ���� PEN_TRACK ö�����ͣ������ʼ���켣����
*/

#if !defined(AFX_PEN_H__AC1A111F_077C_4E6E_B998_90E7FDEDC4FD__INCLUDED_)
#define AFX_PEN_H__AC1A111F_077C_4E6E_B998_90E7FDEDC4FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\resource.h"
#include "ENUM.h"


class CTrack;
class CPenNeb;


/*
*����: CAbstractPen
*˵����������ֻ��ʵĳ�����࣬��ȡȡ�����ӿ�
*�汾
*	Revision 1.0	2002/11/1     	 ��� CAbstractPen �Ļ�������
*
*	Revision 2.0	2002/11/12   	 ���� PEN_TRACK ö�����ͣ������ʼ���켣����
*/
class CAbstractPen  
{
protected:
	PEN_TRACK   m_PenTrack;
	CPenNeb   * m_pPenNeb;
	CTrack    * m_pPenTrack;
	BOOL        m_bAlpha;
	// �ñʻ滭���豸��������
	HDC         m_hDC;

	CString     m_strPenName;
	COLORREF    m_crPenColor;
	// �ʵĴ�С
	int         m_nPenSize;

	// �ʵĹ��ͼ��
	HCURSOR     m_hCursor;


public:
	CAbstractPen(HDC hDC, int nSize = 12, COLORREF crColor = RGB(0, 0, 0));
	virtual ~CAbstractPen();


public:		
	//���ñ����Ժ���
	virtual BOOL SetPenTrack(PEN_TRACK PenTrack);
	virtual void SetPenColor(COLORREF crColor);
	virtual void SetPenStyle(PEN_STYLE PenStyle);
	virtual void SetPenSize(int nSize);

	// �滭����
	virtual void BeginDraw(const CPoint& ptPoint);
	virtual void DrawPoint(const CPoint& ptPoint);
	virtual void EndDraw(const CPoint& ptPoint);

	// ���رʵĹ����
	HCURSOR GetCursor() const;


protected:
	// ���켣�ϵĵ�
	void FillTrack();
	// ��ָ�������ϻ��
	virtual void Apply(const CPoint& ptPoint) const;
};

#endif // !defined(AFX_PEN_H__AC1A111F_077C_4E6E_B998_90E7FDEDC4FD__INCLUDED_)
