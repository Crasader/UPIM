/**
*   Pencil.cpp		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   ʵ��Ǧ����
*======================================================
*   �汾
*	Revision 1.0	2002/11/12   	 ���� CPencil ��
*/

#include "stdafx.h"
#include "..\Include\Pencil.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPencil::CPencil(HDC hDC, int nSize, COLORREF crColor) : CAbstractPen(hDC, nSize, crColor)
{
	m_strPenName = _T("Ǧ��");
//	m_hCursor = LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_PENCIL)); //���д�����DLL ����Ч��Ӧ�������һ�д���
   //m_hCursor = AfxGetApp()->LoadCursor(IDC_PENCIL);
}


CPencil::~CPencil()
{

}