/**
*   VEllipsePenneb.h		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002. All Rights Reserved.
*   ���崹ֱ��Բ�αʼ⹤��
*======================================================
*   �汾
*   Revision 1.0	2002/11/14    	 ���� CVEllipsePenNeb ��
*/
#if !defined(AFX_VELLIPSEPENNEB_H__7DED83E4_F715_11D6_95DB_000795CFF65D__INCLUDED_)
#define AFX_VELLIPSEPENNEB_H__7DED83E4_F715_11D6_95DB_000795CFF65D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PenNeb.h"


/*
*����: CVEllipsePenNeb
*˵�������崹ֱ��Բ�ʼ�Ч����
*�汾
*	Revision 1.0	2002/11/14    	 ���� CVEllipsePebNeb ��
*/
class CVEllipsePenNeb : public CPenNeb  
{
public:
	CVEllipsePenNeb(HDC hDC, int nSize, COLORREF crColor, BOOL bAlpha = FALSE);
	virtual ~CVEllipsePenNeb();


public:
	virtual void SetSize(int nSize);


protected:
	virtual void SetAlpha(BYTE * pPixel) ;
};

#endif // !defined(AFX_VELLIPSEPENNEB_H__7DED83E4_F715_11D6_95DB_000795CFF65D__INCLUDED_)
