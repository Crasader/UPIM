/**
*   CirclePenneb.h		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   ����Բ�αʼ⹤��
*======================================================
*   �汾
*   Revision 1.0	2002/11/14   	 ���� CCirclePenNeb ��
*/
#if !defined(AFX_CIRCLEPENNEB_H__7DED83E3_F715_11D6_95DB_000795CFF65D__INCLUDED_)
#define AFX_CIRCLEPENNEB_H__7DED83E3_F715_11D6_95DB_000795CFF65D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PenNeb.h"

/*
*����: CCirclePenNeb
*˵��������Բ�αʼ�Ч����
*�汾
*	Revision 1.0	2002/11/14    	 ���� CCirclePebNeb ��
*/
class CCirclePenNeb : public CPenNeb  
{
public:
	CCirclePenNeb(HDC hDC, int nSize, COLORREF crColor, BOOL bAlpha = FALSE);
	virtual ~CCirclePenNeb();


public:
	virtual void SetSize(int nSize);


protected:
	virtual void SetAlpha(BYTE * pPixel) ;
};

#endif // !defined(AFX_CIRCLEPENNEB_H__7DED83E3_F715_11D6_95DB_000795CFF65D__INCLUDED_)
