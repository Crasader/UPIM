/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  �� BitmapDialog.cpp
* �汾��  �� V1.0
* ��Ŀ���ƣ� CPH
* ��Ȩ������ Copyright 2002-2003 . All Rights Reserved.
* ģ���������ʹ�����ɫ��Ϊ�Ի���ı���ͼ�����ɽ��Ի�����󻯣�ռ��������Ļ
*======================================================
* �汾�����¼:
*      v1.0  2002-10-30   20:30  ��ΰ  ����һЩ�ο�������ɱ���
*
* 
*/

/////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "..\Include\BitmapDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :CBitmapDialog
*  ��������     :���캯��
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*--------------------------------------------------------------------------------
*/
CBitmapDialog::CBitmapDialog()
{
	CommonConstruct();
	Init(); 
}

CBitmapDialog::CBitmapDialog(UINT uResource, CWnd* pParent /*=NULL*/)
	: CDialog(uResource, pParent)
{
	CommonConstruct();
	Init(); 
}

CBitmapDialog::CBitmapDialog(LPCTSTR pszResource, CWnd* pParent /*=NULL*/)
	: CDialog(pszResource, pParent)
{
	CommonConstruct();
	Init(); 
}

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :CommonConstruct()
*  ��������     :���õĹ��죬����һЩ�����ĳ�ʼ��
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*--------------------------------------------------------------------------------
*/
void CBitmapDialog::CommonConstruct()
{
	//Ĭ��Ϊ��������
	m_nType = BITMAP_STRETCH;
	VERIFY(m_HollowBrush.CreateStockObject(HOLLOW_BRUSH));

	//{{AFX_DATA_INIT(CBitmapDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetBitmap
*  ��������     :Ϊ�Ի�������λͼ��ͼ
*  �����������	:
*   UINT uResource��λͼ��Դ��ID��
*   int nType��      λͼ�ڶԻ����е���ʾ��ʽ��Ĭ��Ϊ����
*  ���ر���˵�� :���óɹ�����TRUE
*  �㷨����		:
*  ����˵��:
*--------------------------------------------------------------------------------
*/
BOOL CBitmapDialog :: SetBitmap(UINT uResource, int nType /*BITMAP_STRETCH*/) {
	m_nType = nType;
	ASSERT(m_nType == BITMAP_TILE || m_nType == BITMAP_STRETCH || m_nType == BITMAP_CENTER);
	return m_bmpBackground.LoadResource(uResource);
}

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetBitmap
*  ��������     :Ϊ�Ի�������λͼ��ͼ
*  �����������	:
*   LPCSTR lpszBitmap���ⲿλͼ�ļ�ָ��
*   int nType��        λͼ�ڶԻ����е���ʾ��ʽ��Ĭ��Ϊ����
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:�����˵����ǰ������������������
*--------------------------------------------------------------------------------
*/
BOOL CBitmapDialog :: SetBitmap(LPCSTR lpszBitmap, int nType /*BITMAP_STRETCH*/) {
	m_nType = nType;
	ASSERT(m_nType == BITMAP_TILE || m_nType == BITMAP_STRETCH || m_nType == BITMAP_CENTER);
	return m_bmpBackground.LoadBitmap((LPCTSTR)lpszBitmap);
}

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :DoDataExchange
*  ��������     :
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*--------------------------------------------------------------------------------
*/
void CBitmapDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBitmapDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBitmapDialog, CDialog)
	//{{AFX_MSG_MAP(CBitmapDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBitmapDialog ����Ϣ���
/////////////////////////////////////////////////////////////////////////////
/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnEraseBkgnd
*  ��������     :Ϊ�Ի������ñ���ɫ
*  �����������	:
*  CDC* pDC  ���滭�豸������
*  ���ر���˵�� :���óɹ�����TRUE
*  �㷨����		:
*  ����˵��:�����˵����ǰ������������������
*--------------------------------------------------------------------------------
*/
BOOL CBitmapDialog::OnEraseBkgnd(CDC* pDC) 
{
	if(m_bmpBackground.GetPixelPtr() != 0) {
		ASSERT(m_nType == BITMAP_TILE || m_nType == BITMAP_STRETCH || m_nType == BITMAP_CENTER);
		
		CRect rc;
		GetClientRect(rc);
		int x = 0, y = 0;

		switch(m_nType) {
			case BITMAP_CENTER:   //λͼ������ʾ
				CDialog::OnEraseBkgnd(pDC);
				x = (rc.Width() - m_bmpBackground.GetWidth()) / 2;
				y = (rc.Height() - m_bmpBackground.GetHeight()) / 2;
				m_bmpBackground.DrawDIB(pDC, x, y);
				break;

			case BITMAP_STRETCH:    //λͼ������ʾ�Ա�����������Ի���
				m_bmpBackground.DrawDIB(pDC, 0, 0, rc.Width(), rc.Height());
				break;

			default:	// ����Ի���
			
				while(y < rc.Height()) {
					while(x < rc.Width()) {
						m_bmpBackground.DrawDIB(pDC, x, y);
						x += m_bmpBackground.GetWidth();
					}
					x = 0;
					y += m_bmpBackground.GetHeight();
				}
				break;
		}
	} else
		// ��λͼʱ��ʾ����Ի���
		return CDialog::OnEraseBkgnd(pDC);

	return TRUE;
}

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnCtlColor
*  ��������     :
*  �����������	:
*      CDC* pDC��
*      CWnd* pWnd��
*      UINT nCtlColor��
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*--------------------------------------------------------------------------------
*/
HBRUSH CBitmapDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	if(m_bmpBackground.GetPixelPtr() != 0) {
		switch(nCtlColor) {
			case CTLCOLOR_STATIC:
				TCHAR lpszClassName[255];
				GetClassName(pWnd->m_hWnd, lpszClassName, 255);
				if(_tcscmp(lpszClassName, TRACKBAR_CLASS) == 0)
					return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

			case CTLCOLOR_BTN:
				pDC->SetBkMode(TRANSPARENT);
				return HBRUSH(m_HollowBrush);

			default:
				break;
		}
	}
	
	//��ʾ�������ǰ����������죬����ʹ�û�ˢ����ʵ�ָ�ǿ��Ĺ���
	return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnQueryNewPalette
*  ��������     :��ѯ�µ�ɫ��
*  �����������	:
*  ���ر���˵�� :�ɹ�����TRUE
*  �㷨����		:
*  ����˵��:
*--------------------------------------------------------------------------------
*/
BOOL CBitmapDialog::OnQueryNewPalette() 
{
	CPalette * pPal = m_bmpBackground.GetPalette();
	if( pPal != 0 && GetSafeHwnd() != 0 ) {
		CClientDC dc(this);
		CPalette * pOldPalette = dc.SelectPalette(pPal, FALSE);
		UINT nChanged = dc.RealizePalette();
		dc.SelectPalette(pOldPalette, TRUE);

		if (nChanged == 0)
			return FALSE;

		Invalidate();
		return TRUE;
	}
	return CDialog::OnQueryNewPalette();
}

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :
*  ��������     :����ɫ��仯ʱ
*  �����������	:
*   CWnd* pFocusWnd����ǰ���㴰�ڵľ��
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*--------------------------------------------------------------------------------
*/
void CBitmapDialog::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CPalette * pPal = m_bmpBackground.GetPalette();
	if( pPal != 0 && GetSafeHwnd() != 0 && pFocusWnd != this && ! IsChild(pFocusWnd) ) {
		CClientDC dc(this);
		CPalette * pOldPalette = dc.SelectPalette(pPal, TRUE);
		UINT nChanged = dc.RealizePalette();
		dc.SelectPalette(pOldPalette, TRUE);

		if( nChanged )
			Invalidate();
	} else
		CDialog::OnPaletteChanged(pFocusWnd);
}



/////////////////////////////////////////////////////////////////////////////////
//������Ϣ��������ʵ��ȫ��Ļ��ʾ
////////////////////////////////////////////////////////////////////////////////
/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnDestroy()
*  ��������     :�Ի����ͷ�ʱ
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*--------------------------------------------------------------------------------
*/
void CBitmapDialog::OnDestroy() 
{
	//����ˢ����ʾ��ͼ
	ShowWindow(SW_SHOW);
	ShowWindow(SW_HIDE);

	CDialog::OnDestroy();
}

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :ThrowOpenDlg()
*  ��������     :ʹ�Ի�����󻯣�������windows�����ϵ�״̬��
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*--------------------------------------------------------------------------------
*/
void CBitmapDialog::ThrowOpenDlg()
{
	ZeroMemory(&m_WorkArea,sizeof(m_WorkArea));

	if(::SystemParametersInfo(SPI_GETWORKAREA,
							  0,
							  &m_WorkArea,
							  0))
	{
		::SystemParametersInfo(SPI_SETWORKAREA,
							  0,
							  NULL,
							  SPIF_SENDCHANGE);
	}

	if(!m_bIsToolBarHidden)
	{
		CWnd* pTaskBar = CWnd::FindWindow(_T("Shell_TrayWnd"),_T(""));
		if(pTaskBar && ::IsWindow(*pTaskBar))
		{
			m_bWasToolBarVisible = pTaskBar->IsWindowVisible();
			pTaskBar->ShowWindow(SW_HIDE);
			m_bIsToolBarHidden = TRUE;
		}
	}

	if(!m_bAreDisplaySettingsChanged)
	{
		DWORD dmPelsWidth = m_DlgRect.Width();
		DWORD dmPelsHeight = m_DlgRect.Height();

		m_bAreDisplaySettingsSaved = ::EnumDisplaySettings(NULL,
														   ENUM_REGISTRY_SETTINGS,
														   &m_SaveDevMode);

		BOOL bIsMaxColorDepth = FALSE;
		DEVMODE MaxColorDepthDevMode;
		ZeroMemory(&MaxColorDepthDevMode,sizeof(MaxColorDepthDevMode));
		MaxColorDepthDevMode.dmSize = sizeof(MaxColorDepthDevMode);

		BOOL bIsTheSameColorDepth = FALSE;
		DEVMODE TheSameColorDepth;
		ZeroMemory(&TheSameColorDepth,sizeof(TheSameColorDepth));
		TheSameColorDepth.dmSize = sizeof(TheSameColorDepth);

		DEVMODE TempDevMode;
		DWORD dwModeNum;

		for(dwModeNum=0;;dwModeNum++)
		{
			ZeroMemory(&TempDevMode,sizeof(TempDevMode));
			TempDevMode.dmSize = sizeof(TempDevMode);

			if(!::EnumDisplaySettings(NULL,
									  dwModeNum,
									  &TempDevMode))
				break;

			if(TempDevMode.dmPelsWidth != dmPelsWidth ||
			   TempDevMode.dmPelsHeight != dmPelsHeight)
				continue;

			if(TempDevMode.dmBitsPerPel > MaxColorDepthDevMode.dmBitsPerPel)
			{
				MaxColorDepthDevMode = TempDevMode;
				bIsMaxColorDepth = TRUE;
			}

		   if(!bIsTheSameColorDepth)
		   {
			   TheSameColorDepth = TempDevMode;
			   bIsTheSameColorDepth = TRUE;
		   }
		}

		m_bAreDisplaySettingsChanged = bIsMaxColorDepth &&
									   ::ChangeDisplaySettings(&MaxColorDepthDevMode,0) == DISP_CHANGE_SUCCESSFUL ||
									   bIsTheSameColorDepth &&
									   ::ChangeDisplaySettings(&TheSameColorDepth,0) == DISP_CHANGE_SUCCESSFUL;
	}

	ShowWindow(SW_SHOWNORMAL);

	CenterWindow();
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :WrapUpDlg()
*  ��������     :���Ѿ����ȫ����ĶԻ����ԭ��ͬʱ��ʾ�����ص�windows����״̬��
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*--------------------------------------------------------------------------------
*/
void CBitmapDialog::WrapUpDlg()
{
	if(m_bAreDisplaySettingsChanged && m_bAreDisplaySettingsSaved)
		::ChangeDisplaySettings(&m_SaveDevMode,0);

	m_bAreDisplaySettingsChanged = m_bAreDisplaySettingsSaved = FALSE;

	if(m_bIsToolBarHidden)
	{
		CWnd* pTaskBar = CWnd::FindWindow(_T("Shell_TrayWnd"),_T(""));
		if(pTaskBar && 
		   ::IsWindow(*pTaskBar) &&
		   m_bWasToolBarVisible)
			pTaskBar->ShowWindow(SW_SHOW);
	}

	if(!CRect(m_WorkArea).IsRectEmpty())
		::SystemParametersInfo(SPI_SETWORKAREA,
							  0,
							  &m_WorkArea,
							  SPIF_SENDCHANGE);

	m_bIsToolBarHidden = m_bWasToolBarVisible = FALSE;

    ShowWindow(SW_SHOWMAXIMIZED);
 
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnInitDialog() 
*  ��������     :��ʼ���Ի���
*  �����������	:
*  ���ر���˵�� :��ʼ���ɹ�����TRUE
*  �㷨����		:
*  ����˵��:
*--------------------------------------------------------------------------------
*/
BOOL CBitmapDialog::OnInitDialog() 
{
	ModifyStyle(WS_THICKFRAME |
				WS_BORDER     |
				WS_CAPTION,
				WS_SYSMENU);

	GetClientRect(m_DlgRect);

	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :Init()
*  ��������     :�Զ���Ķ����ʼ������
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*--------------------------------------------------------------------------------
*/
void CBitmapDialog::Init()
{
	m_bAreDisplaySettingsSaved = FALSE;
	m_bAreDisplaySettingsChanged = FALSE;
	m_bIsToolBarHidden = FALSE;
	m_bWasToolBarVisible = FALSE;

	ZeroMemory(&m_SaveDevMode,sizeof(m_SaveDevMode));
	m_SaveDevMode.dmSize = sizeof(m_SaveDevMode);

	ZeroMemory(&m_WorkArea,sizeof(m_WorkArea));
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnActivateApp
*  ��������     :��������Ĵ��ڵĻ���
*  �����������	:
*    BOOL bActive�������Ƿ�
*    HTASK hTask�� ������
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*--------------------------------------------------------------------------------
*/
void CBitmapDialog::OnActivateApp(BOOL bActive, HTASK hTask) 
{
	if(bActive)
		ThrowOpenDlg();
	else
		WrapUpDlg();

	CDialog::OnActivateApp(bActive, (DWORD)hTask);	
}
