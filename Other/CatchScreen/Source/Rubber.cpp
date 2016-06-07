/**
*   Rubber.h		
*   Version 1.0
*   CPH	�滭��԰
*	Copyright 2002 . All Rights Reserved.
*   ������Ƥ��
*======================================================
*   �汾
*   Revision 1.0	2002/11/4    	 ʵ�� CRubber ��
*/
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\include\Rubber.h"
#include "..\include\Track.h"

#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRubber::CRubber(HDC hDC, int nSize, COLORREF crColor) : CAbstractPen(hDC, nSize, crColor)
{
	m_strPenName = _T("��Ƥ��");
//	m_hCursor = LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_RUBBER));
    m_hCursor = AfxGetApp()->LoadCursor(IDC_RUBBER);
	//��Ƥ��ɫ�̶�Ϊ����ɫ
	m_crPenColor = RGB(0xFF, 0xFF, 0xFF);
	m_pPenTrack->SetTrackColor(crColor);
}

CRubber::~CRubber()
{

}


/*
*--------------------------------------------------------------------------------
*  ������: SetPenColor
*  ����	 : ������Ƥ����ɫ
*  ����  : COLORREF crColor	-  �ʵ���ɫ
*  �㷨	 : ��Ƥ��ɫ�̶�Ϊ����ɫ����ֱ�ӷ���
*--------------------------------------------------------------------------------
*/
void CRubber::SetPenColor(COLORREF crColor)
{
	m_crTrackColor = crColor;
	m_pPenTrack->SetTrackColor(crColor);
	return;
}


/*
*--------------------------------------------------------------------------------
*  ������: SetPenTrack
*  ����	 : ���ñʵĹ켣
*  ����  : [in]  PEN_TRACK PenTrack	- �ʵĹ켣��״
*  ����ֵ: ����켣���ͺϷ����� TRUE�����򷵻� FALSE
*  �㷨  : ��Ƥ�ı�ɫʼ��Ϊ����ɫ�����켣ɫҪ�䶯���������ش˺���
*			�ڴ�ֻ����ʱ�滻��ɫΪ�켣�������ٻ�����
*--------------------------------------------------------------------------------
*/
BOOL CRubber::SetPenTrack(PEN_TRACK PenTrack)
{	
	COLORREF crTemp = m_crPenColor;
	m_crPenColor = m_crTrackColor;
	
	CAbstractPen::SetPenTrack(PenTrack);

	m_crPenColor = crTemp;

	return m_pPenTrack ? TRUE : FALSE;
}