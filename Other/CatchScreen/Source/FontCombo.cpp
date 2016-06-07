/**
*	File Name			:	FontCombo.cpp
*	Version				:	1.0
*	Project Information	:	�滭��԰(1003-2002)
*	Copyright			:	Copyright 2002 . All Rights Reserved.
*	Brief Description   :	CFontCombo��ĺ���ʵ��
*====================================================================================
*   �汾
*   Revision 1.0	2002/11/11		CFontCombo��ĺ���ʵ��
*/

#include "stdafx.h"
#include "..\Include\FontCombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CFontCombo

CFontCombo::CFontCombo()
{
	// Ĭ���������弯
	required_charset = DEFAULT_CHARSET;
	m_sSelection = "8";
}

CFontCombo::~CFontCombo()
{
}


BEGIN_MESSAGE_MAP(CFontCombo, CComboBox)
	//{{AFX_MSG_MAP(CFontCombo)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, OnSelchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontCombo message handlers

/*
*--------------------------------------------------------------------------------
*  Member Name:					ProcessFonts
*  Function Description:		��ʼ����ǹ����
*  Parameter Specification:	    ��
*  Return Specification:		�� 
*   Algorithm:					��		
*   Addtion:				    
        ǰ��������				ComboBox�ؼ������ѱ�����
		����������				�õ�ϵͳ�����Ѱ�װ�����壬�����䴢����ComboBox�����˵���
*--------------------------------------------------------------------------------
*/

void CFontCombo::ProcessFonts(void)
{
	this->ResetContent();
	CClientDC dc(this);

	// Determine the size required by the font comboboxes
	// We will use the DEFAULT_GUI_FONT
	HGDIOBJ hFont = GetStockObject( DEFAULT_GUI_FONT );
	CFont font;
	font.Attach( hFont );
	dc.SelectObject( font );

	TEXTMETRIC tm;
	dc.GetTextMetrics( &tm );
	int cxChar = tm.tmAveCharWidth;
	int cyChar = tm.tmHeight + tm.tmExternalLeading;

	SetFont(&font);
	::EnumFontFamilies( dc.m_hDC, NULL, (FONTENUMPROC)EnumFontFamProc, 
				(LPARAM) this );
}

/*
*--------------------------------------------------------------------------------
*  Member Name:					EnumFontFamProc
*  Function Description:		�õ�����
*  Parameter Specification:	
        ENUMLOGFONTEX *lpelfe	-�߼���������
		NEWTEXTMETRICEX *lpntme -������������
		int	FontType			-��������
		LPARAM lParam           -EnumFontFamiliesEx �����Զ�������
*  Return Specification:		�� 
*   Algorithm:					��		
*   Addtion:				    
        ǰ��������				EnumFontFamiliesEx����������
		����������				����������洢��������
*--------------------------------------------------------------------------------
*/

int CALLBACK CFontCombo::EnumFontFamProc(ENUMLOGFONT *lpelf, NEWTEXTMETRIC *lpntm,
					int nFontType, LPARAM lParam)
{
	CFontCombo* pWnd = (CFontCombo*)lParam;

	// Add the font name to the combo
	pWnd->AddString(lpelf->elfLogFont.lfFaceName);

	return 1;		// 1 to continue enumeration
}

void CFontCombo::OnSelchange() 
{
	GetWindowText(m_sSelection);
	int cursel = SelectString(0,m_sSelection);
	SetCurSel(cursel);
    CRect wRect;
	GetWindowRect(wRect);
	AfxGetMainWnd()->InvalidateRect(wRect);	
	
}

CString CFontCombo::GetFontType()
{
	return m_sSelection;
}




