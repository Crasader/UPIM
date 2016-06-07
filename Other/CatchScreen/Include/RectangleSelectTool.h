/**
*   RectangleSelectTool.h		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   �������ѡȡ����
*======================================================
*   �汾
*   Revision 1.0	2002/11/14     	  �������ѡȡ����
*/
#if !defined(AFX_RECTANGLESELECTTOOL_H__7C6DD164_F7C8_11D6_95DB_000795CFF65D__INCLUDED_)
#define AFX_RECTANGLESELECTTOOL_H__7C6DD164_F7C8_11D6_95DB_000795CFF65D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SelectTool.h"


/*
*����: CRectangleSelectTool
*˵�����������ѡȡ���ߵ���
*�汾
*	Revision 1.0	2002/11/14      ��� CRectangleSelectTool �Ļ�������
*/
class CRectangleSelectTool : public CSelectTool  
{
public:
	CRectangleSelectTool(HWND hWnd);
	virtual ~CRectangleSelectTool();


protected:
	virtual void DrawTrack(const CPoint& ptStart, const CPoint& ptEnd) const;
};

#endif // !defined(AFX_RECTANGLESELECTTOOL_H__7C6DD164_F7C8_11D6_95DB_000795CFF65D__INCLUDED_)
