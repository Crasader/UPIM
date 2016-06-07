// ClipBoard.cpp: implementation of the CClipBoard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\Include\ClipBoard.h"
//#include "FloatDibWnd.h"
#include "..\Include\Dib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClipBoard::CClipBoard()
{
	m_pDib = NULL;
}

CClipBoard::~CClipBoard()
{
	if (m_pDib)
		delete m_pDib;
}


/*
*--------------------------------------------------------------------------------
*  ������	: Paste
*  ����		: ճ��
*  ����		: DOUBLE angle - ��ת�Ƕ�
*  �㷨
*--------------------------------------------------------------------------------
*/
/*
CFloatDibWnd * CClipBoard::Paste(HWND hWnd, int x, int y, int flag)
{
	if (flag == 0)
	{
		// ������ʾ
		return CenterPaste(hWnd);
	}
	else
	{
	}
	return NULL;
}


CFloatDibWnd * CClipBoard::CenterPaste(HWND hWnd)
{	
	CFloatDibWnd * pFloatWnd = new CFloatDibWnd(hWnd, m_pDib);

	return pFloatWnd;
}

*/
BOOL CClipBoard::PutDibToClipBoard(CDib *pDib)
{
	ASSERT(pDib);
	if (m_pDib)
		delete m_pDib;
	m_pDib = pDib;

	return TRUE;
}

CDib* CClipBoard::GetDibFromClipBoard()
{
	return m_pDib;
}


BOOL CClipBoard::IsEmpty()
{
	return m_pDib ? FALSE : TRUE;
}
