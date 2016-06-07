/**
*   LEllipsePenneb.h		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   �����ϲ�����45����Բ�αʼ⹤��
*======================================================
*   �汾
*   Revision 1.0	2002/11/14    	 ���� CLEllipsePenNeb ��
*/
#if !defined(AFX_LELLIPSEPENNEB_H__7DED83E7_F715_11D6_95DB_000795CFF65D__INCLUDED_)
#define AFX_LELLIPSEPENNEB_H__7DED83E7_F715_11D6_95DB_000795CFF65D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PenNeb.h"

/*
*����: CLEllipsePenNeb
*˵���������ϲ�����45����Բ�αʼ⹤����
*�汾
*	Revision 1.0	2002/11/14    	 ���� CLEllipsePebNeb ��
*/
class CLEllipsePenNeb : public CPenNeb  
{
public:
	CLEllipsePenNeb(HDC hDC, int nSize, COLORREF crColor, BOOL bAlpha = FALSE);
	virtual ~CLEllipsePenNeb();


public:
	virtual void NormalApply(const CPoint& ptPoint) const;
	virtual void SetSize(int nSize);


protected:
	virtual void SetAlpha(BYTE * pPixel) ;
	virtual void CreatePenNeb();
};

#endif // !defined(AFX_LELLIPSEPENNEB_H__7DED83E7_F715_11D6_95DB_000795CFF65D__INCLUDED_)
