/**
*   TriangleTrack.h		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   ���������ι켣��״���ߣ���ʼ�� m_ptTractStartPoint Ϊ�����ε����ĵ�
*======================================================
*   �汾
*   Revision 1.0	2002/11/11    	 ���� CTriangleTrack ��
*/

#if !defined(AFX_TRIANGLETrack_H__0F4DFF3C_FCBD_443F_9630_74E1623DB6D7__INCLUDED_)
#define AFX_TRIANGLETrack_H__0F4DFF3C_FCBD_443F_9630_74E1623DB6D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Track.h"


/*
*����: CTriangleTrack
*˵�������������ι켣��
*�汾
*	Revision 1.0	2002/11/11     	 ���� CTriangleTrack ��
*/
class CTriangleTrack : public CTrack  
{
public:
	CTriangleTrack(HDC hDC, COLORREF crTrackColor);
	virtual ~CTriangleTrack();


protected:
	// ���ݹ켣������ļ���
	virtual BOOL CreatePos();

	// ��������
	virtual void Draw(const CPoint& ptStart, const CPoint& ptEnd) const;
};

#endif // !defined(AFX_TRIANGLETrack_H__0F4DFF3C_FCBD_443F_9630_74E1623DB6D7__INCLUDED_)
