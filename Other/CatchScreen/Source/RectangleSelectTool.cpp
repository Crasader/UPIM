/**
*   RectangleSelectTool.cpp	
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   �������ѡȡ����
*======================================================
*   �汾
*   Revision 1.0	2002/11/14     	  ʵ�־���ѡȡ����
*/

#include "stdafx.h"
#include "..\INCLUDE\RectangleSelectTool.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRectangleSelectTool::CRectangleSelectTool(HWND hWnd) : CSelectTool(hWnd)
{

}

CRectangleSelectTool::~CRectangleSelectTool()
{

}

/*
*--------------------------------------------------------------------------------
*  ������: DrawTrack
*  ����	 : ����ѡȡʱ�����߿�
*  ����	 : CPoint& ptStart	-	��ʼѡȡ��
*		   CPoint& ptEnd	-	��ֹѡȡ��
*  �㷨  :	���غ���
*--------------------------------------------------------------------------------
*/
void CRectangleSelectTool::DrawTrack(const CPoint& ptStart, const CPoint& ptEnd) const
{
	Rectangle(m_hDC, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
}
