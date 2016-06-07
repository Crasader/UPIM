/*
*  class PaintBrush
*  ˵������ˢ���ʵ��
*  Copyright 2002 . All Rights Reserved.
*====================================================
*  �汾�����¼
*  Revision 1.0 2002/11/6  ����
*
*  Revision 2.0	2002/11/12   	 �������Σ�����Ч������ʼ�����
*
*  Revision 2.1	2002/11/27   	 ʹ��ˢ��С�ȱ�ıʴ����������� SetPenSize ����
*/

#include "stdafx.h"
#include "..\Include\PaintBrush.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPaintBrush::CPaintBrush(HDC hDC, int nSize, COLORREF crColor) : CAbstractPen(hDC, nSize, crColor)
{
	m_strPenName = _T("��ˢ");
//	m_hCursor = LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_PAINTBRUSH));
    //m_hCursor = AfxGetApp()->LoadCursor(IDC_PAINTBRUSH);
	// ��ˢʹ�� Alpha �ʼ�Ч��
	m_bAlpha = TRUE;

	// ��ˢ�ʴ�С�������ʵ�����
	m_nPenSize = nSize * 2;

	SetPenStyle(PS_CIRCLE);
}


CPaintBrush::~CPaintBrush()
{

}


/*
*--------------------------------------------------------------------------------
*  ������: SetPenSize
*  ����	 : ���û�ˢ�Ĵ�С
*  ����  : int  nSize	-	�ʵĴ�С
*  �㷨	 : ��ˢ��С�������ʴ�С���������ڴ˷Ŵ�
*--------------------------------------------------------------------------------
*/
void CPaintBrush::SetPenSize(int nSize)
{
	if (nSize <= 1)
		nSize = 2;

	m_nPenSize = (int)(nSize * 2);
	
	CAbstractPen::SetPenSize(m_nPenSize);
}
