/**
*   HEllipsePenneb.h		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   ����ˮƽ��Բ�αʼ⹤��
*======================================================
*   �汾
*   Revision 1.0	2002/11/14    	 ���� CHEllipsePenNeb ��
*/
#if !defined(AFX_HELLIPSEPENNEB_H__7DED83E5_F715_11D6_95DB_000795CFF65D__INCLUDED_)
#define AFX_HELLIPSEPENNEB_H__7DED83E5_F715_11D6_95DB_000795CFF65D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PenNeb.h"


/*
*����: CHEllipsePenNeb
*˵��������ˮƽ��Բ�ʼ�Ч����
*�汾
*	Revision 1.0	2002/11/14    	 ���� CHEllipsePebNeb ��
*/
class CHEllipsePenNeb : public CPenNeb  
{
public:
	CHEllipsePenNeb(HDC hDC, int nSize, COLORREF crColor, BOOL bAlpha = FALSE);
	virtual ~CHEllipsePenNeb();


public:
	virtual void SetSize(int nSize);


protected:
	virtual void SetAlpha(BYTE * pPixel) ;
};

#endif // !defined(AFX_HELLIPSEPENNEB_H__7DED83E5_F715_11D6_95DB_000795CFF65D__INCLUDED_)
