/**
*   PentagonTrack.h		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002. All Rights Reserved.
*   ��������ǹ켣��
*======================================================
*   �汾
*   Revision 1.0	2002/11/11   	 ���� CPentagonTrack ��
*/
#if !defined(AFX_PENTAGON_H__DB58ED1A_EAA6_4785_B056_DC5064407996__INCLUDED_)
#define AFX_PENTAGON_H__DB58ED1A_EAA6_4785_B056_DC5064407996__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Track.h"


/*
*����: CPentagonTrack
*˵�������������Բ�켣��
*�汾
*	Revision 1.0	2002/11/11     	 ���� CPentagonTrack ��
*/
class CPentagonTrack : public CTrack  
{
public:
	CPentagonTrack(HDC hDC, COLORREF crTrackColor);
	virtual ~CPentagonTrack();


protected:
	// ���ݹ켣������ļ���
	virtual BOOL CreatePos();
	
	// ���������
	void Draw(const CPoint& ptStart, const CPoint& ptEnd) const;
};

#endif // !defined(AFX_PENTAGON_H__DB58ED1A_EAA6_4785_B056_DC5064407996__INCLUDED_)
