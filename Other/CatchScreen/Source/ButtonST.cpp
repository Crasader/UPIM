/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��ButtonST.cpp
* �汾��  : V1.0
* ��Ŀ���ƣ�CPH
* ��Ȩ������Copyright 2002-2003 . All Rights Reserved.
* ģ���������ͼ��(λͼ)��Ŧ�ؼ���
*======================================================
* �汾�����¼:
*
*   v1.0  2001	              Davide Calabro'		davide_calabro@yahoo.com
*   v1.1  2002-10-30   20:30  ��ΰ  
*
* 
*/

/////////////////////////////////////////////////////////////////////////////



#include "stdafx.h"
//#include "..\PaintDlg.h"
#include "..\\INCLUDE\\ButtonST.h"
#include "..\\INCLUDE\\DefineMessage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//Ӧ�ó�������·��,��"c:\cph\"
extern  CString g_strAppPath;        
extern  IniPaintSet g_stuPaintSet;

/////////////////////////////////////////////////////////////////////////////
/*
*--------------------------------------------------------------------------------
*  ��Ա������   :CBmpPalette
*  ��������     :
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
CButtonST::CButtonST()
{
	m_bMouseOnButton = FALSE;

	FreeResources(FALSE);

	// Ĭ��Ϊ��ƽ�桱���Ͱ�Ŧ
	m_bIsFlat = TRUE; 
  
	// Ĭ��Ϊ��������Ŧ�߿����Ͱ�Ŧ
	m_bDrawBorder = FALSE; 
  
	// Ĭ��ͼ��ͬ���ֱ�ǩ��ͬһ����
	m_nAlign = ST_ALIGN_HORIZ; 
  
	// Ĭ����ʾ�ı���ǩ
	m_bShowText = TRUE; 
  
	//Ĭ��Ϊƽ�水Ŧʱ,����������α߿���
	m_bDrawFlatFocus = FALSE;

	//Ĭ�ϰ�Ŧ���Ǵ����ϵ�Ĭ�ϰ�Ŧ
	m_bIsDefault = FALSE;

	//��Ŧ����CheckBox����
	m_bIsCheckBox = FALSE;
	m_nCheck = 0;

	// ��ŦĬ����ɫ
	SetDefaultColors(FALSE);

	// ��Ŧ������ʾΪNULL
	m_ToolTip.m_hWnd = NULL;

	//Ĭ�ϰ�ŦΪ��͸����
	m_bDrawTransparent =TRUE;
	m_pbmpOldBk = NULL;

	// �� URL������
	::ZeroMemory(&m_szURL, sizeof(m_szURL));

	// ��Ŧ�Ϲ�� cursorû�� ����
	m_hCursor = NULL;	// 

	//���Զ��ظ���Ϣ
	m_bAutoRepeat = FALSE;
	m_hWndAutoRepeat = NULL;
	m_nMsgAutoRepeat = WM_APP;
	m_dwPeriodAutoRepeat = 100;

   //Ĭ��Ϊ������Ϣ
    m_downmessage = LCLICK;

	//Ĭ�ϰ�Ŧ�������õ��ڿͻ���
	m_HitTestStyle = HTCLIENT;

	m_isFirst = TRUE;
	m_nIndex = -1;


} // End of CButtonST

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :~CButtonST()
*  ��������     :��������: �ͷž��
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
CButtonST::~CButtonST()
{
	// �ָ���λͼ 
	if (m_dcBk.m_hDC != NULL && m_pbmpOldBk != NULL)
	{
		m_dcBk.SelectObject(m_pbmpOldBk);
	}

	FreeResources();

	// �ͷŹ����
	if (m_hCursor != NULL) ::DestroyCursor(m_hCursor);
} // End of ~CButtonST


BEGIN_MESSAGE_MAP(CButtonST, CButton)
    //{{AFX_MSG_MAP(CButtonST)
	ON_WM_CAPTURECHANGED()
	ON_WM_SETCURSOR()
	ON_WM_KILLFOCUS()
	ON_WM_MOUSEMOVE()
	ON_WM_SYSCOLORCHANGE()
	ON_CONTROL_REFLECT_EX(BN_CLICKED, OnClicked)
	ON_WM_ACTIVATE()
	ON_WM_ENABLE()
	ON_WM_CANCELMODE()
	ON_WM_LBUTTONDOWN()
	ON_WM_NCHITTEST()
	ON_WM_SIZE()
	ON_WM_MOVING()
	ON_WM_TIMER()
	ON_WM_NCLBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetIcon
*  ��������     :Ϊ��Ŧ������̬ͼ��
*  �����������	:
*int nIconInId ������ӹ���ѹ��ʱ��Ŧ��ʾ��ͼ�����ԴID��
*int nIconOutId������뿪ʱ��̬��Ŧ��ʾ��ͼ�����ԴID��
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
DWORD CButtonST::SetIcon(int nIconInId, int nIconOutId)
{
	HICON		hIconIn;
	HICON		hIconOut;
	HINSTANCE	hInstResource;

	// ����ͼ����Դ
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nIconInId), RT_GROUP_ICON);

	// ���õ��ӹ���ѹ��ʱ��Ŧ��ʾ��ͼ��
	hIconIn = (HICON)::LoadImage(hInstResource, MAKEINTRESOURCE(nIconInId), IMAGE_ICON, 0, 0, 0);
  	//��������뿪ʱ��̬��Ŧ��ʾ��ͼ��
	hIconOut = (HICON)::LoadImage(hInstResource, MAKEINTRESOURCE(nIconOutId), IMAGE_ICON, 0, 0, 0);

	return SetIcon(hIconIn, hIconOut);
} // End of SetIcon


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetIcon
*  ��������     :Ϊ��Ŧ������̬ͼ��
*  �����������	:
*HICON nIconInId ������ӹ���ѹ��ʱ��Ŧ��ʾ��ͼ����
*HICON nIconOutId������뿪ʱ��̬��Ŧ��ʾ��ͼ����
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
DWORD CButtonST::SetIcon(HICON hIconIn, HICON hIconOut)
{
	BOOL		bRetValue;
	ICONINFO	ii;

	//�ͷ����е������Դ
	FreeResources();

	if (hIconIn != NULL)
	{
		m_csIcons[0].hIcon = hIconIn;

		//�õ�ͼ��ߴ�
		ZeroMemory(&ii, sizeof(ICONINFO));
		bRetValue = ::GetIconInfo(hIconIn, &ii);
		if (bRetValue == FALSE)
		{
			FreeResources();
			return BTNST_INVALIDRESOURCE;
		} // end if

		m_csIcons[0].dwWidth	= (DWORD)(ii.xHotspot * 2);
		m_csIcons[0].dwHeight	= (DWORD)(ii.yHotspot * 2);
		::DeleteObject(ii.hbmMask);
		::DeleteObject(ii.hbmColor);

		if (hIconOut != NULL)
		{
			m_csIcons[1].hIcon = hIconOut;

			// �õ�ͼ��ߴ�
			ZeroMemory(&ii, sizeof(ICONINFO));
			bRetValue = ::GetIconInfo(hIconOut, &ii);
			if (bRetValue == FALSE)
			{
				FreeResources();
				return BTNST_INVALIDRESOURCE;
			} //end if

			m_csIcons[1].dwWidth	= (DWORD)(ii.xHotspot * 2);
			m_csIcons[1].dwHeight	= (DWORD)(ii.yHotspot * 2);
			::DeleteObject(ii.hbmMask);
			::DeleteObject(ii.hbmColor);
		} //end  if
	} // end if

	RedrawWindow();

	return BTNST_OK;
} // End of SetIcon


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetBtnCursor
*  ��������     :����꾭����ŦʱΪ��Ŧ���ù����ʽ
*  �����������	:
*int nCursorId  :�����Դ��ID��
*  ���ر���˵�� :����TRUE���ɹ����á�
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
BOOL CButtonST::SetBtnCursor(int nCursorId)
{
	HINSTANCE hInstResource;
	// �ͷ���ǰ�Ĺ��
	if (m_hCursor != NULL) ::DestroyCursor(m_hCursor);
	m_hCursor = NULL;

	if (nCursorId != NULL)
	{
		hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nCursorId),
											RT_GROUP_CURSOR);
		// ����ICON��Դ
		m_hCursor = (HCURSOR)::LoadImage(hInstResource/*AfxGetApp()->m_hInstance*/, MAKEINTRESOURCE(nCursorId), IMAGE_CURSOR, 0, 0, 0);
		//��������FALSE
		if (m_hCursor == NULL) return FALSE;
	}

	return TRUE;
} // End of SetBtnCursor


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetFlat
*  ��������     :���ð�Ŧ�Ƿ�Ϊƽ������
*  �����������	:
*   BOOL bState��ΪTRUE��ʾҪ���ð�ŦΪƽ������
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::SetFlat(BOOL bState)
{
	m_bIsFlat = bState;
	Invalidate();
} // End of SetFlat

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetFlat
*  ��������     :�õ���Ŧ�Ƿ���ƽ������
*  �����������	:
*  ���ر���˵�� :����TRUE��ʾ��ŦΪƽ������
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
BOOL CButtonST::GetFlat()
{
	return m_bIsFlat;
} // End of GetFlat



/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetAlign
*  ��������     :���ð�Ŧ���ı�ͬͼ��Ķ��뷽ʽ
*  �����������	:
*    int nAlign �����뷽ʽ
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::SetAlign(int nAlign)
{
	switch (nAlign)
	{    
		case ST_ALIGN_HORIZ:
		case ST_ALIGN_HORIZ_RIGHT:
		case ST_ALIGN_VERT:
			m_nAlign = nAlign;
			break;
	}
	Invalidate();
} // End of SetAlign


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetAlign()
*  ��������     :�õ���Ŧ���ı�ͬͼ��Ķ��뷽ʽ
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
int CButtonST::GetAlign()
{
	return m_nAlign;
} // End of GetAlign


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :DrawBorder
*  ��������     :���ð�Ŧ�õ�����ʱ�Ƿ�һ�߿�
*  �����������	:
*  BOOL bEnable   ��ΪTRUE��ʾ��ŦҪ���ý���߿�
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::DrawBorder(BOOL bEnable)
{
	m_bDrawBorder = bEnable;
} // End of DrawBorder

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetShowText
*  ��������     :����ͼ�갴Ŧ�Ƿ���ʾ�ı���ǩ
*  �����������	:
*  BOOL bShow     ��ΪTRUE��ʾ��Ŧͼ�����ı���ǩ����ʾ
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::SetShowText(BOOL bShow)
{
	m_bShowText = bShow;
	Invalidate();
} // End of SetShowText


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetShowText()
*  ��������     :�õ�ͼ�갴Ŧ�Ƿ���ʾ�ı���ǩ
*  �����������	:
*  ���ر���˵�� :
*  ����TRUE��ʾ��Ŧͼ�����ı���ǩ����ʾ
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
BOOL CButtonST::GetShowText()
{
	return m_bShowText;
} // End of GetShowText


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnMouseMove
*  ��������     :����ڰ�Ŧ�����ƶ�ʱ
*  �����������	:
*   UINT nFlags: ������ͬ�İ���ѹ�����
*   CPoint point:����ڴ����ϵĵ�ǰ�����
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::OnMouseMove(UINT nFlags, CPoint point)
{	
	//��Ŧ����ָ��
	CWnd* pWnd;  
    //������ָ��
	CWnd* pParent;

	CButton::OnMouseMove(nFlags, point);
    
   
	// ������ӹ���Ŧ���沢���ѹ�²����κδ���
	if (nFlags & MK_LBUTTON && m_bMouseOnButton == FALSE) return;

	CString strIndex;
	strIndex.Format("%d",m_nIndex); 
	//CCPHDlg *pParentWnd = (CCPHDlg *)GetParent(); 
	//pParentWnd->m_showHelp.ShowWindow(SW_SHOW);

	//�����һ���򴴽�һ����̬��ʾ����
	if(m_isFirst == TRUE && m_nIndex != -1)
	{
		m_nCount = 0;
		m_isFirst = FALSE;
		m_mousePoint = point;
		SetTimer(1,1000,NULL);
	}

	// ��Ŧ��ƽ�����ͷ���
	if (m_bIsFlat == FALSE) return;

	pWnd = GetActiveWindow();
	pParent = GetOwner();

	if ((GetCapture() != this) && (
		 #ifndef ST_LIKEIE
			pWnd != NULL && 
		 #endif
		pParent != NULL)) 
	{
		m_bMouseOnButton = TRUE;
		//SetFocus();	
		SetCapture();
		Invalidate();
	}
	else
	{
		POINT p2 = point;
		ClientToScreen(&p2);
		CWnd* wndUnderMouse = WindowFromPoint(p2);
//		if (wndUnderMouse != this)
		if (wndUnderMouse && wndUnderMouse->m_hWnd != this->m_hWnd)
		{
			//������뿪ʱ�ػ���Ŧ
			if (m_bMouseOnButton == TRUE)
			{

				//���Ӱ�Ŧ���ƿ�ʱ�رն�̬��ʾ��
				m_isFirst = TRUE;
				if(m_nIndex != -1 && m_nCount != -1)
                {
					if(pParentWnd->GetTextStyle() == TRUE)
						pParentWnd->m_showHelp.Show(FALSE, m_nIndex);
					if(pParentWnd->GetVoiceStyle() == TRUE)
						StopPlayTipSound();
					m_nCount = -1;
					KillTimer(1);
				}
				m_bMouseOnButton = FALSE;
				Invalidate();
			}
			//��û��ѹ���������ͷ�!
			if (!(nFlags & MK_LBUTTON)) ReleaseCapture();
		}


	}
} // End of OnMouseMove


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnKillFocus
*  ��������     :��Ŧʧȥ����ʱ
*  �����������	:
*  CWnd * pNewWnd����Ŧ�ؼ�����ָ��
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::OnKillFocus(CWnd * pNewWnd)
{
	CButton::OnKillFocus(pNewWnd);

	CancelHover();
} // End of OnKillFocus

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnLButtonDown
*  ��������     :����ڰ�Ŧ��ѹ��ʱ
*  �����������	:
*   UINT nFlags: ������ͬ�İ���ѹ�����
*   CPoint point:����ڴ����ϵĵ�ǰ�����
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::OnLButtonDown(UINT nFlags, CPoint point) 
{

CButton::OnLButtonDown(nFlags, point);

	MSG		csMsg;
	int		nButtonID;
	HWND	hWndParent;
	nButtonID = GetDlgCtrlID();
	hWndParent = GetParent()->GetSafeHwnd();

	//�رն�̬��ʾ
	if(m_nIndex != -1 && m_nCount != -1)
    {
    	CCPHDlg *pParentWnd = (CCPHDlg *)GetParent(); 
        if(pParentWnd->GetTextStyle() == TRUE)
		    pParentWnd->m_showHelp.Show(FALSE, m_nIndex);
		if(pParentWnd->GetVoiceStyle() == TRUE)
			StopPlayTipSound();
		m_nCount = -1;
		KillTimer(1);
	}

    switch(m_downmessage)
	{
	case LCLICK:
		{			
			if (m_bAutoRepeat == TRUE)
			{
				while(PeekMessage(&csMsg, m_hWnd, WM_LBUTTONUP, WM_LBUTTONUP, PM_REMOVE) == FALSE)
				{
					::SendMessage(hWndParent, WM_COMMAND, MAKEWPARAM((WORD)nButtonID, BN_CLICKED), (LPARAM)m_hWnd);
					::Sleep(m_dwPeriodAutoRepeat);
				}
				SendMessage(WM_LBUTTONUP);
			} // if
		}
	case LDOWN:		
		::SendMessage(hWndParent, WM_OWNDOWNMESSAGE, MAKEWPARAM((WORD)nButtonID, 0), (LPARAM)m_hWnd);
		break;
		//��ʾ�����˵�
    case LPOPMENU:
			::SendMessage(hWndParent,UWM_RBUTTONDOWN,(long)&point,GetDlgCtrlID());
			break;
	}

} // End of OnLButtonDown


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnActivate
*  ��������     :��ŦΪ�״̬ʱ
*  �����������	:
*  UINT nState:
*  CWnd* pWndOther:
*  BOOL bMinimized:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CButton::OnActivate(nState, pWndOther, bMinimized);
	
	if (nState == WA_INACTIVE)	CancelHover();
} // End of OnActivate

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnEnable
*  ��������     :���ð�Ŧ��Ч
*  �����������	:
*   BOOL bEnable��ΪTRUEʱ��ʾ��Ŧ��Ч�����Խ�����Ϣ
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::OnEnable(BOOL bEnable) 
{
	CButton::OnEnable(bEnable);
	
	if (bEnable == FALSE)	CancelHover();
} // End of OnEnable

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnCancelMode() 
*  ��������     :���ð�ŦΪ��겶��CancelModeģʽ
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::OnCancelMode() 
{
	CButton::OnCancelMode();
		
	CancelHover();
} // End of OnCancelMode


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnCaptureChanged
*  ��������     :��겶��CancelModeģʽʧЧ
*  �����������	:
*  CWnd *pWnd   ����겶��CancelModeģʽָ��Ĵ���ָ��
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::OnCaptureChanged(CWnd *pWnd) 
{
	if (m_bMouseOnButton == TRUE)
	{
		ReleaseCapture();
		Invalidate();
	}

	CButton::OnCaptureChanged(pWnd);
} // End of OnCaptureChanged


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :DrawItem
*  ��������     :�Ի���Ŧ����
*  �����������	:
*  LPDRAWITEMSTRUCT lpDIS��DRAWITEMSTRUCT �ṹ��ָ���Ի���Ŧ������
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);

	CPen *pOldPen;
	BOOL	bIsPressed;

	// ��Checkbox��Radiobutton���� ?
	if (m_bIsCheckBox == TRUE)
	{
		bIsPressed  =  (lpDIS->itemState & ODS_SELECTED)
					|| (m_nCheck != 0);
		//bIsPressed = TRUE;
	}
	// ���水Ŧ���������Ͱ�Ŧ���� ...
	else
	{
		bIsPressed = (lpDIS->itemState & ODS_SELECTED);
	}

//	BOOL bIsPressed  = (lpDIS->itemState & ODS_SELECTED);
	BOOL bIsFocused  = (lpDIS->itemState & ODS_FOCUS);
	BOOL bIsDisabled = (lpDIS->itemState & ODS_DISABLED);

	CRect itemRect = lpDIS->rcItem;

	pDC->SetBkMode(TRANSPARENT);

	if (m_bIsFlat == FALSE)
	{
		if (bIsFocused || (GetDefault() == TRUE))
		{
			//�������ɺ�ɫ��Ϊ͸��ɫ���ݸ�Ϊ
			//ԭCBrush br(RGB(0,0,0));  
			CBrush br(RGB(0,0,0));
			pDC->FrameRect(&itemRect, &br);
			itemRect.DeflateRect(1, 1);
		}
	}

	// ׼����... �ñ���ɫ����Ŧ��
	COLORREF bgColor;
	if ((m_bMouseOnButton == TRUE) || (bIsPressed))
		bgColor = m_crColors[BTNST_COLOR_BK_IN]; 
	else
		bgColor = m_crColors[BTNST_COLOR_BK_OUT]; 

	CBrush br(bgColor);
	// ��Ŧ�Ƿ�͸��?
	if (m_bDrawTransparent == TRUE)
	{
		PaintBk(pDC);
	}
	else
	{
		pDC->FillRect(&itemRect, &br);
	}

	//CBrush br(GetSysColor(COLOR_BTNFACE));  
	//pDC->FillRect(&itemRect, &br);

	// ����ѹʽ��Ŧ
	if (bIsPressed)
	{
		if (m_bIsFlat == TRUE)
		{
			if (m_bDrawBorder == TRUE)
			{
				pDC->Draw3dRect(itemRect, ::GetSysColor(COLOR_BTNSHADOW), ::GetSysColor(COLOR_BTNHILIGHT));
			}
		}
		else    
		{
			CBrush brBtnShadow(GetSysColor(COLOR_BTNSHADOW));
			pDC->FrameRect(&itemRect, &brBtnShadow);
		}
	}
	else // ...else������ѹʽ��Ŧ
	{
		CPen penBtnHiLight(PS_SOLID, 0, GetSysColor(COLOR_BTNHILIGHT)); // White
		CPen pen3DLight(PS_SOLID, 0, GetSysColor(COLOR_3DLIGHT));       // Light gray
		CPen penBtnShadow(PS_SOLID, 0, GetSysColor(COLOR_BTNSHADOW));   // Dark gray
		CPen pen3DDKShadow(PS_SOLID, 0, GetSysColor(COLOR_3DDKSHADOW)); // Black

		if (m_bIsFlat == TRUE)
		{
			if (m_bMouseOnButton == TRUE && m_bDrawBorder == TRUE)
			{
				pDC->Draw3dRect(itemRect, ::GetSysColor(COLOR_BTNHILIGHT), ::GetSysColor(COLOR_BTNSHADOW));
			}
		}
		else
		{
			//��ɫ����
			pOldPen = pDC->SelectObject(&penBtnHiLight);
			pDC->MoveTo(itemRect.left, itemRect.bottom-1);
			pDC->LineTo(itemRect.left, itemRect.top);
			pDC->LineTo(itemRect.right, itemRect.top);
			// ��������
			pDC->SelectObject(pen3DLight);
			pDC->MoveTo(itemRect.left+1, itemRect.bottom-1);
			pDC->LineTo(itemRect.left+1, itemRect.top+1);
			pDC->LineTo(itemRect.right, itemRect.top+1);
			// ������
			pDC->SelectObject(pen3DDKShadow);
			pDC->MoveTo(itemRect.left, itemRect.bottom-1);
			pDC->LineTo(itemRect.right-1, itemRect.bottom-1);
			pDC->LineTo(itemRect.right-1, itemRect.top-1);
			//��������
			pDC->SelectObject(penBtnShadow);
			pDC->MoveTo(itemRect.left+1, itemRect.bottom-2);
			pDC->LineTo(itemRect.right-2, itemRect.bottom-2);
			pDC->LineTo(itemRect.right-2, itemRect.top);
			//
			pDC->SelectObject(pOldPen);
		}
	}

	//�õ���Ŧ�������
	CString sTitle;
	GetWindowText(sTitle);

	//������ʾ����
	if (m_bShowText == FALSE) sTitle.Empty();

	CRect captionRect = lpDIS->rcItem;

	// ��ͼ��
	if (m_csIcons[0].hIcon != NULL)
	{
		DrawTheIcon(pDC, !sTitle.IsEmpty(), &lpDIS->rcItem, &captionRect, bIsPressed, bIsDisabled);
	}

	if (m_csBitmaps[0].hBitmap != NULL)
	{
		//��������ɺ�ɫ��Ϊ͸��ɫ���ݸ�Ϊ��ɫ����
	    //ԭpDC->SetBkColor(RGB(255,255,255));
		pDC->SetBkColor(RGB(0,0,0));
		DrawTheBitmap(pDC, !sTitle.IsEmpty(), &lpDIS->rcItem, &captionRect, bIsPressed, bIsDisabled);
	} // if

	//����Ŧ�������
	if (sTitle.IsEmpty() == FALSE)
	{
		//����ŦΪ��ѹʽ��Ŧ
		if (bIsPressed && m_bIsCheckBox == FALSE)
			captionRect.OffsetRect(1, 1);
    
		// ���½�����DEBUGģʽ 
		//CBrush brBtnShadow(RGB(255, 0, 0));
		//pDC->FrameRect(&captionRect, &brBtnShadow);

		/*
		if ((m_bMouseOnButton == TRUE) || (bIsPressed)) 
		{
			pDC->SetTextColor(GetActiveFgColor());
			pDC->SetBkColor(GetActiveBgColor());
		} 
		else 
		{
			pDC->SetTextColor(GetInactiveFgColor());
			pDC->SetBkColor(GetInactiveBgColor());
		}
		*/
		// �ı�����
		CRect centerRect = captionRect;
		pDC->DrawText(sTitle, -1, captionRect, DT_WORDBREAK | DT_CENTER | DT_CALCRECT);
		captionRect.OffsetRect((centerRect.Width() - captionRect.Width())/2, (centerRect.Height() - captionRect.Height())/2);
		/* RFU
		captionRect.OffsetRect(0, (centerRect.Height() - captionRect.Height())/2);
		captionRect.OffsetRect((centerRect.Width() - captionRect.Width())-4, (centerRect.Height() - captionRect.Height())/2);
		*/

		pDC->SetBkMode(TRANSPARENT);
		/*
		pDC->DrawState(captionRect.TopLeft(), captionRect.Size(), (LPCTSTR)sTitle, (bIsDisabled ? DSS_DISABLED : DSS_NORMAL), 
						TRUE, 0, (CBrush*)NULL);
		*/
		if (bIsDisabled)
		{
			captionRect.OffsetRect(1, 1);
			pDC->SetTextColor(::GetSysColor(COLOR_3DHILIGHT));
			pDC->DrawText(sTitle, -1, captionRect, DT_WORDBREAK | DT_CENTER);
			captionRect.OffsetRect(-1, -1);
			pDC->SetTextColor(::GetSysColor(COLOR_3DSHADOW));
			pDC->DrawText(sTitle, -1, captionRect, DT_WORDBREAK | DT_CENTER);
		}
		else
		{
			if ((m_bMouseOnButton == TRUE) ||(bIsPressed)) 
			{
				pDC->SetTextColor(m_crColors[BTNST_COLOR_FG_IN]);
				pDC->SetBkColor(m_crColors[BTNST_COLOR_BK_IN]);
			} 
			else 
			{
				pDC->SetTextColor(m_crColors[BTNST_COLOR_FG_OUT]);
				pDC->SetBkColor(m_crColors[BTNST_COLOR_BK_OUT]);
			}
			pDC->DrawText(sTitle, -1, captionRect, DT_WORDBREAK | DT_CENTER);
		}
	}

	if (m_bIsFlat == FALSE || (m_bIsFlat == TRUE && m_bDrawFlatFocus == TRUE))
	{
		// ��������ο�
		if (bIsFocused)
		{
			CRect focusRect = itemRect;
			focusRect.DeflateRect(3, 3);
			pDC->DrawFocusRect(&focusRect);
		}
	}
} // End of DrawItem


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :DrawTheIcon
*  ��������     :��ͼ��
*  �����������	:
*  CDC* pDC��      �豸������
*  BOOL bHasTitle���Ƿ��б�ǩ�ı�
*  RECT* rpItem��������δ�С
*  CRect* rpTitle����ǩ�ı����δ�С
*  BOOL bIsPressed���Ƿ�����ѹʽ��Ŧ
*  BOOL bIsDisabled���Ƿ�ʧЧ
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::DrawTheIcon(CDC* pDC, BOOL bHasTitle, RECT* rpItem, CRect* rpTitle, BOOL bIsPressed, BOOL bIsDisabled)
{
	BYTE		byIndex		= 0;

	// ѡ��Ҫʹ�õ�ͼ��
	if (m_bIsCheckBox == TRUE)
	{
		if (bIsPressed == TRUE)
		{
			byIndex = 0;
		} // if
		else
		{
			if (m_csIcons[1].hIcon != NULL)
				byIndex = 1;
			else
				byIndex = 0;		// ������뿪ͼ�����
		} // else
	} // if
	else
	{
		if (m_bMouseOnButton == TRUE || bIsPressed == TRUE)
		{
			byIndex = 0;
		} // if
		else
		{
			if (m_csIcons[1].hIcon != NULL)
				byIndex = 1;
			else
				byIndex = 0;		// ������뿪ͼ�����
		} // else
	} // else

	CRect	rImage;
	PrepareImageRect(bHasTitle, rpItem, rpTitle, bIsPressed, m_csIcons[byIndex].dwWidth, m_csIcons[byIndex].dwHeight, &rImage);

	// Ole'!
	pDC->DrawState(	rImage.TopLeft(),
					rImage.Size(), 
					m_csIcons[byIndex].hIcon,
					(bIsDisabled ? DSS_DISABLED : DSS_NORMAL), 
					(CBrush*)NULL);
} // End of DrawTheIcon


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :PreSubclassWindow() 
*  ��������     :��ǰ��Ŧ��������״̬
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::PreSubclassWindow() 
{
	UINT nBS;

	nBS = GetButtonStyle();

	// ����Ƿ��Ǵ����е�Ĭ�ϰ�Ŧ
	if (nBS & BS_DEFPUSHBUTTON) m_bIsDefault = TRUE;

	// ����Ƿ���checkbox���Ͱ�Ŧ
	if (nBS & BS_CHECKBOX) m_bIsCheckBox = TRUE;

	// �����Ի����� BS_OWNERDRAW 
	SetButtonStyle(nBS | BS_OWNERDRAW);

	CButton::PreSubclassWindow();
} // End of PreSubclassWindow


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :PreTranslateMessage
*  ��������     :
*  �����������	:
*  MSG* pMsg��   ��Ϣָ��
*  ���ر���˵�� :����Ϣ���Ա����ɣ�����0,���򷵼ӷ�0

*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
BOOL CButtonST::PreTranslateMessage(MSG* pMsg) 
{
	InitToolTip();
	m_ToolTip.RelayEvent(pMsg);
	
	return CButton::PreTranslateMessage(pMsg);
} // End of PreTranslateMessage


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :DefWindowProc
*  ��������     :
*  �����������	:
*   UINT message:ָ��ҪWINDOWS �������Ϣ
*   WPARAM wParam:��Ϣ�ж���Ĳ���
*   LPARAM lParam:��Ϣ�ж���Ĳ���
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
LRESULT CButtonST::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if (message == WM_LBUTTONDBLCLK)
	{
		message = WM_LBUTTONDOWN;
	}
	return CButton::DefWindowProc(message, wParam, lParam);
} // End of DefWindowProc

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetFlatFocus
*  ��������     :����ƽ�����Ͱ�Ŧ�Ľ���
*  �����������	:
*  BOOL bDrawFlatFocus���Ƿ�ƽ�水Ŧ
*  BOOL bRepaint      ���Ƿ��ػ�
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::SetFlatFocus(BOOL bDrawFlatFocus, BOOL bRepaint)
{
	m_bDrawFlatFocus = bDrawFlatFocus;
	
	// �ػ���Ŧ����
	if (bRepaint == TRUE) Invalidate();
} // End of SetFlatFocus


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetFlatFocus()
*  ��������     :�õ�ƽ�水Ŧ����
*  �����������	:
*  ���ر���˵�� :����TRUE��ʾ��Ŧ��ƽ�潹��
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
BOOL CButtonST::GetFlatFocus()
{
	return m_bDrawFlatFocus;
} // End of GetFlatFocus


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetBtnCursor
*  ��������     :Ϊ��Ŧ���������
*  �����������	:
*  HCURSOR hCursor  ��Ҫ���õĹ����
*  ���ر���˵�� :����TRUE��ʾ�ɹ�
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
BOOL CButtonST::SetBtnCursor(HCURSOR hCursor)
{
	// �ͷ���ǰ�Ĺ��
	if (m_hCursor != NULL) 
		::DestroyCursor(m_hCursor);
	m_hCursor = NULL;
	if (hCursor != NULL)
	{
		// ����ICON��Դ
		m_hCursor = hCursor;
		//��������FALSE
		if (m_hCursor == NULL) 
			return FALSE;
	}

	return TRUE;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnSetCursor
*  ��������     :Ϊ��Ŧ���������
*  �����������	:
*  CWnd* pWnd   ��
*  UINT nHitTest��
*  UINT message ��
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
BOOL CButtonST::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// ����걻ָ��ʹ����
	if (m_hCursor != NULL)
	{
		::SetCursor(m_hCursor);
		return TRUE;
	}

	return CButton::OnSetCursor(pWnd, nHitTest, message);
} // End of OnSetCursor

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetTooltipText
*  ��������     :Ϊ��Ŧ������ʾ��Ϣ�ı�
*  �����������	:
*   LPCTSTR lpszText����ʾ��Ϣ�ı�����
*   BOOL bActivate  ���Ƿ���ʾ��ʾ��Ϣ
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::SetTooltipText(LPCTSTR lpszText, BOOL bActivate)
{
	//�����ܿ��ı�
	if (lpszText == NULL) return;

	// ��ʼ��ToolTip
	InitToolTip();

	//��û�ж���tooltip�������Ķ���
	if (m_ToolTip.GetToolCount() == 0)
	{
		CRect rectBtn; 
		GetClientRect(rectBtn);
		m_ToolTip.AddTool(this, lpszText, rectBtn, 1);
	}

	// Ϊtooltip�����ı�
	m_ToolTip.UpdateTipText(lpszText, this, 1);
	m_ToolTip.Activate(bActivate);
} // End of SetTooltipText


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetTooltipText
*  ��������     :Ϊ��Ŧ������ʾ��Ϣ�ı�
*  �����������	:
*  int nId      ����ʾ�ı��ַ�����ԴID��
*  BOOL bActivate����ʾ��Ϣ�ı��ǲ���Ч
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::SetTooltipText(int nId, BOOL bActivate)
{
	CString sText;

	// ������ʾ�ı���Դ
	sText.LoadString(nId);
	// ���ַ�����Դ��Ϊ��
	if (sText.IsEmpty() == FALSE) SetTooltipText((LPCTSTR)sText, bActivate);
} // End of SetTooltipText


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :ActivateTooltip
*  ��������     :���ð�Ŧ��ʾ�ı���Ч
*  �����������	:
*  BOOL bActivate����Ŧ��ʾ��Ϣ�Ƿ���Ч
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::ActivateTooltip(BOOL bActivate)
{
	// ����tooltip����
	if (m_ToolTip.GetToolCount() == 0) return;

	//ʹ��ʾ�ı���Ч
	m_ToolTip.Activate(bActivate);
} // End of EnableTooltip


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetDefault()
*  ��������     :�õ���Ŧ�Ƿ��Ǵ����ϵ�Ĭ�ϰ�Ŧ
*  �����������	:
*  ���ر���˵�� :����TRUE����ŦΪ�����ϵ�Ĭ�ϰ�Ŧ
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
BOOL CButtonST::GetDefault()
{
	return m_bIsDefault;
} // End of GetDefault


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :DrawTransparent
*  ��������     :��͸����Ŧ
*  �����������	:
*  BOOL bRepaint����Ŧ�Ƿ�͸��
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::DrawTransparent(BOOL bRepaint)
{
	m_bDrawTransparent = TRUE;

	// �ָ���λͼ
	if (m_dcBk.m_hDC != NULL && m_pbmpOldBk != NULL)
	{
		m_dcBk.SelectObject(m_pbmpOldBk);
	} // if

	m_bmpBk.DeleteObject();
	m_dcBk.DeleteDC();

	// �ػ���Ŧ
	if (bRepaint == TRUE) Invalidate();
} // End of DrawTransparent


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :InitToolTip()
*  ��������     :��ʼ����Ŧ��ʾ��Ϣ
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::InitToolTip()
{
	if (m_ToolTip.m_hWnd == NULL)
	{
		// ����ToolTip�ؼ�
		m_ToolTip.Create(this);
		// �ǻ��
		m_ToolTip.Activate(FALSE);
		// ������Ч
		m_ToolTip.SendMessage(TTM_SETMAXTIPWIDTH, 0, 400);
	} // if
} // End of InitToolTip


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :PaintBk
*  ��������     :����Ŧ����
*  �����������	:
*   CDC* pDC �� �滭�豸������
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::PaintBk(CDC* pDC)
{
	CClientDC clDC(GetParent());
	CRect rect;
	CRect rect1;

	GetClientRect(rect);

	GetWindowRect(rect1);
	GetParent()->ScreenToClient(rect1);

	if (m_dcBk.m_hDC == NULL)
	{
		m_dcBk.CreateCompatibleDC(&clDC);
		m_bmpBk.CreateCompatibleBitmap(&clDC, rect.Width(), rect.Height());
		m_pbmpOldBk = m_dcBk.SelectObject(&m_bmpBk);
		m_dcBk.BitBlt(0, 0, rect.Width(), rect.Height(), &clDC, rect1.left, rect1.top, SRCCOPY);
	} // if

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcBk, 0, 0, SRCCOPY);
} // End of PaintBk

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :CtlColor
*  ��������     :
*  �����������	:
*  CDC* pDC��
*  UINT nCtlColor��
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
HBRUSH CButtonST::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	return (HBRUSH)::GetStockObject(NULL_BRUSH); 
} // End of CtlColor

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnSysColorChange
*  ��������     :��ϵͳɫ�ʱ仯ʱɾ��CBitmap����
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::OnSysColorChange() 
{
	CButton::OnSysColorChange();

	m_dcBk.DeleteDC();
	m_bmpBk.DeleteObject();	
} // End of OnSysColorChange

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnClicked()
*  ��������     :������Ŧʱ
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
BOOL CButtonST::OnClicked() 
{	
	if (m_bIsCheckBox == TRUE)
	{
		m_nCheck = !m_nCheck;
		Invalidate();
	} // if
	else
	{
		// Handle the URL (if any)
		if (::lstrlen(m_szURL) > 0)
			::ShellExecute(NULL, _T("open"), m_szURL, NULL,NULL, SW_SHOWMAXIMIZED);
	} // else

	return FALSE;
} // End of OnClicked


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetCheck
*  ��������     :��ŦΪCheckBox����ʱ���õ�ǰ��ʾ״̬
*  �����������	:
*  int nCheck��   �Ƿ�ѡ��
*  BOOL bRepaint���Ƿ��ػ�
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::SetCheck(int nCheck, BOOL bRepaint)
{
	if (m_bIsCheckBox == TRUE)
	{
		if (nCheck == 0) m_nCheck = 0;
		else m_nCheck = 1;

		if (bRepaint == TRUE) Invalidate();
	} // if
} // End of SetCheck


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetCheck()
*  ��������     :��ŦΪCheckBox����ʱ�õ���ǰ��Ŧ��CHECK״̬
*  �����������	:
*  ���ر���˵�� :
*  ����״ֵ̬
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
int CButtonST::GetCheck()
{
	return m_nCheck;
} // End of GetCheck


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :FreeResources
*  ��������     :�ͷ�������Դ
*  �����������	��
*  BOOL bCheckForNULL��
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::FreeResources(BOOL bCheckForNULL)
{
	if (bCheckForNULL == TRUE)
	{
		// �ͷŹ����Դ
		
		if (m_csIcons[0].hIcon != NULL)	::DeleteObject(m_csIcons[0].hIcon);
		if (m_csIcons[1].hIcon != NULL)	::DeleteObject(m_csIcons[1].hIcon);

		//  �ͷ�λͼ��Դ
		if (m_csBitmaps[0].hBitmap != NULL)	::DeleteObject(m_csBitmaps[0].hBitmap);
		if (m_csBitmaps[1].hBitmap != NULL)	::DeleteObject(m_csBitmaps[1].hBitmap);

		// �ͷ�mask λͼ
		if (m_csBitmaps[0].hMask != NULL)	::DeleteObject(m_csBitmaps[0].hMask);
		if (m_csBitmaps[1].hMask != NULL)	::DeleteObject(m_csBitmaps[1].hMask);
	} // end if

	::ZeroMemory(&m_csIcons, sizeof(m_csIcons));
	::ZeroMemory(&m_csBitmaps, sizeof(m_csBitmaps));
} // End of FreeResources


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetBitmaps
*  ��������     :ʹ��λͼ��Դ������ð�Ŧ����̬ͼ
*  �����������	:
*  HBITMAP hBitmapIn��       ������ڰ�Ŧ��ʱ��ʾ��λͼ���ָ��
*  COLORREF crTransColorIn�� ������ڰ�Ŧ��ʱ��ʾ��λͼ��͸��ɫ
*  HBITMAP hBitmapOut��      ������뿪��Ŧʱ��ʾ��λͼ���ָ��
*  COLORREF crTransColorOut��������뿪��Ŧʱ��ʾ��λͼ��͸��ɫ
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
DWORD CButtonST::SetBitmaps(HBITMAP hBitmapIn, COLORREF crTransColorIn, HBITMAP hBitmapOut, COLORREF crTransColorOut)
{
	int		nRetValue;
	BITMAP	csBitmapSize;

	//�ͷ����е������Դ
	FreeResources();

	if (hBitmapIn != NULL)
	{
		m_csBitmaps[0].hBitmap = hBitmapIn;
		m_csBitmaps[0].crTransparent = crTransColorIn;
		//�õ�λͼָ��
		nRetValue = ::GetObject(hBitmapIn, sizeof(csBitmapSize), &csBitmapSize);
		if (nRetValue == 0)
		{
			FreeResources();
			return BTNST_INVALIDRESOURCE;
		} //end  if
		m_csBitmaps[0].dwWidth = (DWORD)csBitmapSize.bmWidth;
		m_csBitmaps[0].dwHeight = (DWORD)csBitmapSize.bmHeight;

		// Ϊ������ڰ�Ŧ��ʱ��������λͼ
		m_csBitmaps[0].hMask = CreateBitmapMask(hBitmapIn, m_csBitmaps[0].dwWidth, m_csBitmaps[0].dwHeight, crTransColorIn);
		if (m_csBitmaps[0].hMask == NULL)
		{
			FreeResources();
			return BTNST_FAILEDMASK;
		} // end if

		if (hBitmapOut != NULL)
		{
			m_csBitmaps[1].hBitmap = hBitmapOut;
			m_csBitmaps[1].crTransparent = crTransColorOut;
			// �õ�λͼ�ߴ�
			nRetValue = ::GetObject(hBitmapOut, sizeof(csBitmapSize), &csBitmapSize);
			if (nRetValue == 0)
			{
				FreeResources();
				return BTNST_INVALIDRESOURCE;
			} // if
			m_csBitmaps[1].dwWidth = (DWORD)csBitmapSize.bmWidth;
			m_csBitmaps[1].dwHeight = (DWORD)csBitmapSize.bmHeight;

			// Ϊ������뿪��Ŧʱ��������λͼ
			m_csBitmaps[1].hMask = CreateBitmapMask(hBitmapOut, m_csBitmaps[1].dwWidth, m_csBitmaps[1].dwHeight, crTransColorOut);
			if (m_csBitmaps[1].hMask == NULL)
			{
				FreeResources();
				return BTNST_FAILEDMASK;
			} //end  if
		} // end if
	} // end if

	RedrawWindow();

	return BTNST_OK;
} // End of SetBitmaps


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetBitmaps
*  ��������     :ʹ��λͼ��Դ���ð�Ŧ����̬ͼ
*  �����������	:
*  int nBitmapIn��           ������ڰ�Ŧ��ʱ��ʾ��λͼ��ԴID��
*  COLORREF crTransColorIn�� ������ڰ�Ŧ��ʱ��ʾ��λͼ��͸��ɫ
*  int nBitmapOut��          ������뿪��Ŧʱ��ʾ��λͼ��ԴID��
*  COLORREF crTransColorOut��������뿪��Ŧʱ��ʾ��λͼ��͸��ɫ
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
DWORD CButtonST::SetBitmaps(int nBitmapIn, COLORREF crTransColorIn, int nBitmapOut, COLORREF crTransColorOut)
{
	HBITMAP		hBitmapIn	= NULL;
	HBITMAP		hBitmapOut	= NULL;
	HINSTANCE hInstResource	= NULL;
	
	//���ҵ�ǰ��Դ
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nBitmapIn), RT_BITMAP);

	//���뵱����ڰ�Ŧ��ʱ��ʾ��λͼ��Դ
	hBitmapIn = (HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(nBitmapIn), IMAGE_BITMAP, 0, 0, 0);

	// ���뵱����뿪��Ŧʱ��ʾ��λͼ��Դ
	hBitmapOut = (HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(nBitmapOut), IMAGE_BITMAP, 0, 0, 0);

	return SetBitmaps(hBitmapIn, crTransColorIn, hBitmapOut, crTransColorOut);
} // End of SetBitmaps


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :DrawTheBitmap
*  ��������     :��λͼ
*  �����������	:
*  CDC* pDC��      �滭�豸������
*  BOOL bHasTitle���Ƿ����ı���ǩ
*  RECT* rItem��    �滭������
*  CRect *rCaption���ı�������
*  BOOL bIsPressed���Ƿ�����ѹ��Ŧ
*  BOOL bIsDisabled���Ƿ�ʧЧ
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::DrawTheBitmap(CDC* pDC, BOOL bHasTitle, RECT* rItem, CRect *rCaption, BOOL bIsPressed, BOOL bIsDisabled)
{
	HDC			hdcBmpMem	= NULL;
	HBITMAP		hbmOldBmp	= NULL;
	HDC			hdcMem		= NULL;
	HBITMAP		hbmT		= NULL;

	BYTE		byIndex		= 0;

	// ѡȡҪʹ�õ�λͼ
	if (m_bIsCheckBox == TRUE)
	{
		if (bIsPressed == TRUE)
		{
			byIndex = 0;
		} // if
		else
		{
			if (m_csBitmaps[1].hBitmap != NULL)
				byIndex = 1;
			else
				byIndex = 0;		//��λͼ����
		} // else
	} // if
	else
	{
		if (m_bMouseOnButton == TRUE || bIsPressed == TRUE)
		{
			byIndex = 0;
		} // if
		else
		{
			if (m_csBitmaps[1].hBitmap != NULL)
				byIndex = 1;
			else
				byIndex = 0;		//��λͼ����
		} // else
	} // else

	CRect	rImage;
	PrepareImageRect(bHasTitle, rItem, rCaption, bIsPressed, m_csBitmaps[byIndex].dwWidth, m_csBitmaps[byIndex].dwHeight, &rImage);

	hdcBmpMem = ::CreateCompatibleDC(pDC->m_hDC);

	hbmOldBmp = (HBITMAP)::SelectObject(hdcBmpMem, m_csBitmaps[byIndex].hBitmap);

	hdcMem = ::CreateCompatibleDC(NULL);

	hbmT = (HBITMAP)::SelectObject(hdcMem, m_csBitmaps[byIndex].hMask);

	::BitBlt(pDC->m_hDC, rImage.left, rImage.top, m_csBitmaps[byIndex].dwWidth, m_csBitmaps[byIndex].dwHeight, hdcMem, 0, 0, SRCAND);

	::BitBlt(pDC->m_hDC, rImage.left, rImage.top, m_csBitmaps[byIndex].dwWidth, m_csBitmaps[byIndex].dwHeight, hdcBmpMem, 0, 0, SRCPAINT);

	::SelectObject(hdcMem, hbmT);
	::DeleteDC(hdcMem);

	::SelectObject(hdcBmpMem, hbmOldBmp);
	::DeleteDC(hdcBmpMem);
} // End of DrawTheBitmap


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :CreateBitmapMask
*  ��������     :��������λͼ
*  �����������	:
*   HBITMAP hSourceBitmap����Դλͼ���
*   DWORD dwWidth��λͼ��
*   DWORD dwHeight��λͼ��
*   COLORREF crTransColor��͸��ɫ
*  ���ر���˵�� :���ش����ɹ�������λͼ���ָ��
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
HBITMAP CButtonST::CreateBitmapMask(HBITMAP hSourceBitmap, DWORD dwWidth, DWORD dwHeight, COLORREF crTransColor)
{
	HBITMAP		hMask		= NULL;
	HDC			hdcSrc		= NULL;
	HDC			hdcDest		= NULL;
	HBITMAP		hbmSrcT		= NULL;
	HBITMAP		hbmDestT	= NULL;
	COLORREF	crSaveBk;
	COLORREF	crSaveDestText;

	hMask = ::CreateBitmap(dwWidth, dwHeight, 1, 1, NULL);
	if (hMask == NULL)	return NULL;

	hdcSrc	= ::CreateCompatibleDC(NULL);
	hdcDest	= ::CreateCompatibleDC(NULL);

	hbmSrcT = (HBITMAP)::SelectObject(hdcSrc, hSourceBitmap);
	hbmDestT = (HBITMAP)::SelectObject(hdcDest, hMask);

	crSaveBk = ::SetBkColor(hdcSrc, crTransColor);

	::BitBlt(hdcDest, 0, 0, dwWidth, dwHeight, hdcSrc, 0, 0, SRCCOPY);

	crSaveDestText = ::SetTextColor(hdcSrc, RGB(255, 255, 255));
	::SetBkColor(hdcSrc,RGB(0, 0, 0));

	::BitBlt(hdcSrc, 0, 0, dwWidth, dwHeight, hdcDest, 0, 0, SRCAND);

	SetTextColor(hdcDest, crSaveDestText);

	::SetBkColor(hdcSrc, crSaveBk);
	::SelectObject(hdcSrc, hbmSrcT);
	::SelectObject(hdcDest, hbmDestT);

	::DeleteDC(hdcSrc);
	::DeleteDC(hdcDest);

	return hMask;
} // End of CreateBitmapMask

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :PrepareImageRect
*  ��������     :׼����ͼ��������
*  �����������	:
*   BOOL bHasTitle���Ƿ����ı���ǩ
*   RECT* rpItem�����������
*   CRect* rpTitle����ǩ������
*   BOOL bIsPressed���Ƿ�����ѹ��Ŧ
*   DWORD dwWidth��ͼ����
*   DWORD dwHeight��ͼ��߶�
*   CRect* rpImage��ͼ�������
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::PrepareImageRect(BOOL bHasTitle, RECT* rpItem, CRect* rpTitle, BOOL bIsPressed, DWORD dwWidth, DWORD dwHeight, CRect* rpImage)
{
	CRect rBtn;

	rpImage->CopyRect(rpItem);

	switch (m_nAlign)
	{
		case ST_ALIGN_HORIZ:
			if (bHasTitle == FALSE /*spTitle->IsEmpty()*/)
			{
				// ͼ��ˮƽ����
				rpImage->left += ((rpImage->Width() - dwWidth)/2);
			}
			else
			{
				//ͼ���������ڽ����������
				rpImage->left += 3;  
				rpTitle->left += dwWidth + 3;
			}
			// ͼ��ֱ����
			rpImage->top += ((rpImage->Height() - dwHeight)/2);
			break;

		case ST_ALIGN_HORIZ_RIGHT:
			GetClientRect(&rBtn);
			if (bHasTitle == FALSE /*spTitle->IsEmpty()*/)
			{
				// ͼ��ˮƽ����
				rpImage->left += ((rpImage->Width() - dwWidth)/2);
			}
			else
			{
				//ͼ���������ڽ����������
				rpTitle->right = rpTitle->Width() - dwWidth - 3;
				rpTitle->left = 3;
				rpImage->left = rBtn.right - dwWidth - 3;
				// ͼ��ֱ����
				rpImage->top += ((rpImage->Height() - dwHeight)/2);
			}
			break;
		
		case ST_ALIGN_VERT:
			// ͼ��ˮƽ����
			rpImage->left += ((rpImage->Width() - dwWidth)/2);
			if (bHasTitle == FALSE /*spTitle->IsEmpty()*/)
			{
					// ͼ��ֱ����
				rpImage->top += ((rpImage->Height() - dwHeight)/2);           
			}
			else
			{
				rpImage->top = 3;
				rpTitle->top += dwHeight;
			}
			break;
	}
    
	//����Ŧ��ѹ��ͼ��Ҳ��ʾ��ӦЧ��
	if (bIsPressed == TRUE && m_bIsCheckBox == FALSE)
		rpImage->OffsetRect(1, 1);
} // End of PrepareImageRect

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetDefaultColors
*  ��������     :���û滭�õ�Ĭ����ɫ
*  �����������	:
*   BOOL bRepaint:�Ƿ��ػ�
*  ���ر���˵�� :����BTNST_OK
*
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
DWORD CButtonST::SetDefaultColors(BOOL bRepaint)
{
	m_crColors[BTNST_COLOR_BK_IN]	= ::GetSysColor(COLOR_BTNFACE);
	m_crColors[BTNST_COLOR_FG_IN]	= ::GetSysColor(COLOR_BTNTEXT);
	m_crColors[BTNST_COLOR_BK_OUT]	= ::GetSysColor(COLOR_BTNFACE);
	m_crColors[BTNST_COLOR_FG_OUT]	= ::GetSysColor(COLOR_BTNTEXT);

	if (bRepaint == TRUE)	Invalidate();

	return BTNST_OK;
} // End of SetDefaultColors



/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetColor
*  ��������     :���ð�Ŧ��ɫ
*  �����������	:
*  BYTE byColorIndex��Ҫ������ɫ��������
*  COLORREF crColor�� ���õ�����ɫ
*   BOOL bRepaint��   �Ƿ��ػ�
*  ���ر���˵�� :
*    BTNST_INVALIDINDEX��ʧ��
*    BTNST_OK��          �ɹ�
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
DWORD CButtonST::SetColor(BYTE byColorIndex, COLORREF crColor, BOOL bRepaint)
{
	if (byColorIndex >= BTNST_MAX_COLORS)	return BTNST_INVALIDINDEX;

	// ��������ɫ
	m_crColors[byColorIndex] = crColor;

	if (bRepaint == TRUE)	Invalidate();

	return BTNST_OK;
} // End of SetColor

//
// Parameters:
//		[IN]	byColorIndex
//				Index of the color to get. This index is zero-based.
//		[OUT]	crpColor
//				A pointer to a COLORREF that will receive the color.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//		BTNST_INVALIDINDEX
//			Invalid color index.
//
/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetColor
*  ��������     :�õ�ָ������ɫ
*  �����������	:
*  BYTE byColorIndex��Ҫ�õ���ɫ��������
*  COLORREF* crpColor����ɫֵ
*  ���ر���˵�� :
*    BTNST_INVALIDINDEX��ʧ��
*    BTNST_OK��          �ɹ�
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
DWORD CButtonST::GetColor(BYTE byColorIndex, COLORREF* crpColor)
{
	if (byColorIndex >= BTNST_MAX_COLORS)	return BTNST_INVALIDINDEX;

	// �õ���ɫ
	*crpColor = m_crColors[byColorIndex];

	return BTNST_OK;
} // End of GetColor

//
// Parameters:
//		[IN]	lpszURL
//				Pointer to a null-terminated string that contains the URL.
//
// Return value:
//		BTNST_OK
//			Function executed successfully.
//
/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetURL
*  ��������     :�����Ӱ�Ŧ
*  �����������	:
*  LPCTSTR lpszURL���������ı��ַ���
*  ���ر���˵�� :
*    BTNST_INVALIDINDEX��ʧ��
*    BTNST_OK��          �ɹ�
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
DWORD CButtonST::SetURL(LPCTSTR lpszURL)
{
	if (lpszURL != NULL)
	{
		// ���� URL
		::lstrcpyn(m_szURL, lpszURL, _MAX_PATH);
	} // if
	else
	{
		// ת��URL
		::ZeroMemory(&m_szURL, sizeof(m_szURL));
	} // else

	return BTNST_OK;
} // End of SetURL


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :CancelHover()
*  ��������     :ʧЧ��������
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::CancelHover()
{
	// ����ƽ�水Ŧ����
	if (m_bIsFlat == FALSE) return;

	if (m_bMouseOnButton == TRUE)
	{
		m_bMouseOnButton = FALSE;
		Invalidate();
	} // if
} // End of CancelHover



/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetAutoRepeat
*  ��������     :���ð�Ŧ�Ƿ����Զ��ظ����µĹ���
*  �����������	:
*  BOOL bSet           ��Ŧ�Ƿ����Զ����ְ��µĹ���
*  DWORD dwMilliseconds����Ŧ˫�����ʱ����
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
DWORD CButtonST::SetAutoRepeat(BOOL bSet, DWORD dwMilliseconds)
{
	m_bAutoRepeat = bSet;
	m_dwPeriodAutoRepeat = dwMilliseconds;

	return BTNST_OK;
} // End of SetAutoRepeat


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetIcon
*  ��������     ��ʹ���ⲿͼ���ļ�Ϊ��Ŧ������̬ͼ��
*  �����������	:
*   LPCSTR strIconIn ��������ڰ�Ŧ��ʱҪ��ʾ��ͼ����ļ���
*   LPCSTR strIconOut��������밴ŦʱҪ��ʾ��ͼ����ļ���
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
DWORD CButtonST::SetIcon(LPCSTR strIconIn, LPCSTR strIconOut)
{
	BOOL		bRetValue;
	ICONINFO	ii;
   
	HICON hIconIn = (HICON) LoadIcon(NULL, strIconIn);
	HICON hIconOut = (HICON) LoadIcon(NULL, strIconOut);

//	hIconIn=AfxGetApp()->LoadIcon(strIconIn);
//  hIconOut=AfxGetApp()->LoadIcon(strIconOut);
	// �ͷ�������Դ
	FreeResources();

	if (hIconIn != NULL)
	{
		m_csIcons[0].hIcon = hIconIn;

		// �õ�ͼ��ߴ�
		ZeroMemory(&ii, sizeof(ICONINFO));
		bRetValue = ::GetIconInfo(hIconIn, &ii);
		if (bRetValue == FALSE)
		{
			FreeResources();
			return BTNST_INVALIDRESOURCE;
		} // if

		m_csIcons[0].dwWidth	= (DWORD)(ii.xHotspot * 2);
		m_csIcons[0].dwHeight	= (DWORD)(ii.yHotspot * 2);
		::DeleteObject(ii.hbmMask);
		::DeleteObject(ii.hbmColor);

		if (hIconOut != NULL)
		{
			m_csIcons[1].hIcon = hIconOut;

			//�õ�ͼ��ߴ�
			ZeroMemory(&ii, sizeof(ICONINFO));
			bRetValue = ::GetIconInfo(hIconOut, &ii);
			if (bRetValue == FALSE)
			{
				FreeResources();
				return BTNST_INVALIDRESOURCE;
			} //end  if

			m_csIcons[1].dwWidth	= (DWORD)(ii.xHotspot * 2);
			m_csIcons[1].dwHeight	= (DWORD)(ii.yHotspot * 2);
			::DeleteObject(ii.hbmMask);
			::DeleteObject(ii.hbmColor);
		} //end  if
	} //end if

	RedrawWindow();

    //DeleteObject(hIconIn);
    //DeleteObject(hIconOut);

	return BTNST_OK;

}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetBitmaps
*  ��������     ��ʹ���ⲿλͼ�ļ�Ϊ��Ŧ������̬ͼ��
*  �����������	:
*   LPCSTR strIconIn ��������ڰ�Ŧ��ʱҪ��ʾ��ͼ���.bmp�ļ���
*   LPCSTR strIconOut��������밴ŦʱҪ��ʾ��ͼ���.bmp�ļ���
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
DWORD CButtonST::SetBitmaps(LPCSTR strBitmapIn, COLORREF crTransColorIn, LPCSTR strBitmapOut, COLORREF crTransColorOut)
{
	int		nRetValue;

	HBITMAP hBitmapIn = (HBITMAP) LoadImage(NULL, strBitmapIn, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);

	HBITMAP hBitmapOut=(HBITMAP) LoadImage(NULL, strBitmapOut, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);

	BITMAP	csBitmapSize;

	// �ͷ�������Դ
	FreeResources();

	if (hBitmapIn != NULL)
	{
		m_csBitmaps[0].hBitmap = hBitmapIn;
		m_csBitmaps[0].crTransparent = crTransColorIn;
		//�õ�λͼ�ߴ�
		nRetValue = ::GetObject(hBitmapIn, sizeof(csBitmapSize), &csBitmapSize);
		if (nRetValue == 0)
		{
			FreeResources();
			return BTNST_INVALIDRESOURCE;
		} // if
		m_csBitmaps[0].dwWidth = (DWORD)csBitmapSize.bmWidth;
		m_csBitmaps[0].dwHeight = (DWORD)csBitmapSize.bmHeight;

		//��������ڰ�Ŧ��ʱ������λͼ
		m_csBitmaps[0].hMask = CreateBitmapMask(hBitmapIn, m_csBitmaps[0].dwWidth, m_csBitmaps[0].dwHeight, crTransColorIn);
		if (m_csBitmaps[0].hMask == NULL)
		{
			FreeResources();
			return BTNST_FAILEDMASK;
		} // if

		if (hBitmapOut != NULL)
		{
			m_csBitmaps[1].hBitmap = hBitmapOut;
			m_csBitmaps[1].crTransparent = crTransColorOut;
			// �õ�λͼ�ߴ�
			nRetValue = ::GetObject(hBitmapOut, sizeof(csBitmapSize), &csBitmapSize);
			if (nRetValue == 0)
			{
				FreeResources();
				return BTNST_INVALIDRESOURCE;
			} // if
			m_csBitmaps[1].dwWidth = (DWORD)csBitmapSize.bmWidth;
			m_csBitmaps[1].dwHeight = (DWORD)csBitmapSize.bmHeight;

		     //��������뿪��Ŧʱ������λͼ
			m_csBitmaps[1].hMask = CreateBitmapMask(hBitmapOut, m_csBitmaps[1].dwWidth, m_csBitmaps[1].dwHeight, crTransColorOut);
			if (m_csBitmaps[1].hMask == NULL)
			{
				FreeResources();
				return BTNST_FAILEDMASK;
			} //end if
		} // end if
	} // end if

	RedrawWindow();
 	RedrawWindow();   
	//DeleteObject(hBitmapIn);
	//DeleteObject(hBitmapOut);
	return BTNST_OK;

}



/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetLbuttonSendMsgStyle
*  ��������     �����ð�Ŧ���ظ����������ĵ�����Ϣ����
*  �����������	:
*     INT msgstyle����Ϣ����
                    LDOWN���������
					LCLICK�������¼�
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::SetLbuttonSendMsgStyle(INT msgstyle)
{
  if(msgstyle == 0)
      m_downmessage = LCLICK;
  else if(msgstyle == 1)
	  m_downmessage = LDOWN;
  else if(msgstyle==2)
	  m_downmessage = LPOPMENU;
}

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnNcHitTest
*  ��������     �����ð�Ŧ���ظ����������ĵ�����Ϣ����
*  �����������	:
*   CPoint point:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/

UINT CButtonST::OnNcHitTest(CPoint point) 
{
	 return m_HitTestStyle;

//	return CButton::OnNcHitTest(point);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetHitTestStyle
*  ��������     �����ð�Ŧ���ظ����������ĵ�����Ϣ����
*  �����������	:
*   LRESULT style:Ҫ���õ�����ڴ����ϵ�ģʽ���� 
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/

void CButtonST::SetHitTestStyle(LRESULT style)
{
	m_HitTestStyle = style;
    //�����鲻��Ӧ˫��
	if(m_HitTestStyle == HTCAPTION) 
	{

   	    SetAutoRepeat(FALSE,5000) ;
	
	}


}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnSize
*  ��������     �����ð�Ŧ�ߴ����ʱ�丸�Ӵ���ҲҪ��Ӧ����
*  �����������	:
*  UINT nType:
*  int x:
*  int cy:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::OnSize(UINT nType, int cx, int cy) 
{
	CButton::OnSize(nType, cx, cy);
	if(m_HitTestStyle != HTCLIENT)
	{
		CRect crect;
		GetClientRect(&crect);
		CRect prect;

		int		nButtonID;
		HWND	hWndParent;
		nButtonID = GetDlgCtrlID();
		hWndParent = GetParent()->GetSafeHwnd();
		::SendMessage(hWndParent, WM_SIZE, 0, 0);
		
		MoveWindow(CRect(0,0,16,16),TRUE);
	}
	
	
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnMoving
*  ��������     �����ð�Ŧ�ߴ����ʱ�丸�Ӵ���ҲҪ��Ӧ����
*  �����������	:
*  UINT fwSide:�����ƶ�ʱ�ı�Ե
*  LPRECT pRect:�����ƶ�ʱ�����ľ�������Сָ��
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::OnMoving(UINT fwSide, LPRECT pRect) 
{
   CRect frect;
   CCPHDlg * maindlg = (CCPHDlg *)GetParent();  
   maindlg->GetWindowRect(&frect);
   /*
   if(frect.left < 680)
         frect.left = 680;
   if(frect.left > 790)
         frect.left = 790;
   MoveWindow(frect.left, 399, frect.left + 10, 399 + 16);
   */
    pRect->top = 394 + frect.top;
	pRect->bottom = pRect->top + 16;
	if(pRect->left < (680 + frect.left))
		pRect->left= 680 + frect.left;
	else if(pRect->left > (790 + frect.left))
		pRect->left = 790 + frect.left;
	
//	CButton::OnMoving(fwSide, pRect);
   // CCPHDlg *pParent = (CCPHDlg *)GetParent();
   //pParent->MoveSizeScroll(pRect); 
	::PostMessage(GetParent()->GetSafeHwnd(), WM_MOVESIZEBTN, pRect->left - frect.left, 0);
	
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetShowHelp
*  ��������     ��������ʾ������ͼ�󴰿�
*  �����������	:
*    int nIndex :Ҫ���õİ���ͼƬ��������
*    CRect rect :ͼƬ��ʾ�ľ�����
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
* �汾�����¼:
*
*   v1.1  2002-11-24  9:30     
*/
void CButtonST::SetShowHelp(int nIndex, CRect rect)
{
	const int helpWidth = 100, helpHeight = 70;
	m_nIndex = nIndex;
    if(nIndex < 11)
	{
		m_rectHelp.left  = rect.right - helpWidth / 3;
		m_rectHelp.right = rect.right + helpWidth * 2 / 3;
		m_rectHelp.top   = rect.bottom - helpHeight / 4;
		m_rectHelp.bottom = rect.bottom + helpHeight * 3 / 4;
	}
	if(nIndex >= 11 && m_nIndex <17) 
	{
		m_rectHelp.left  = rect.right - helpWidth  / 4;
		m_rectHelp.right = rect.right + helpWidth * 3 / 4;
		m_rectHelp.top   = rect.top - helpHeight;
		m_rectHelp.bottom = rect.top;
	}
	if(m_nIndex >= 17) 
	{
		m_rectHelp.left  = rect.right - helpWidth / 2;
		m_rectHelp.right = rect.right + helpWidth / 2;
		m_rectHelp.top   = rect.top - helpHeight * 2 / 3;
		m_rectHelp.bottom = rect.top + helpHeight / 3;
	}


}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnTimer
*  ��������     ��������ʾ����ͼ�󴰿ڵĿ�ʼ������ʱ��
*  �����������	:
*    UINT nIDEvent��ʱ���¼���
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
* �汾�����¼:
*
*   v1.1  2002-11-24  9:30     
*/
void CButtonST::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CString mp3File;
	if(nIDEvent != 1 || m_nCount == -1) return;
    m_nCount ++;
	CCPHDlg *pParent = (CCPHDlg *)GetParent(); 
    if(m_nCount == 1)
	{
        if(pParent->GetTextStyle() == TRUE)
		{
			pParent->m_showHelp.MoveWindow(m_rectHelp,TRUE); 
		/*	CRect rect;
			rect.left = m_mousePoint.x;
			rect.right = m_mousePoint.x + m_rectHelp.Width();
			rect.top = m_mousePoint.y + m_rectHelp.Width();
	         pParent->m_showHelp.MoveWindow(rect,TRUE);*/
			pParent->m_showHelp.Show(TRUE,m_nIndex);
		}
		if(pParent->GetVoiceStyle() == TRUE)
		{
			CString str;
			if (m_nIndex > 9)
				str.Format("%2d", m_nIndex);
			else 
				str.Format("%1d", m_nIndex);
			str += _T(".mp3");
			TRACE("%s",str);
            mp3File = g_strAppPath + "\\Sounds\\" + str;
			PlayTipSound(mp3File);	
		}
		
	}
	if(m_nCount == 5)
	{
		m_nCount = -1;
		//�رռ�����
		KillTimer(1);
		//�رն�̬��ʾ��
        if(pParent->GetTextStyle() == TRUE)
		    pParent->m_showHelp.Show(FALSE, m_nIndex);
		if(pParent->GetVoiceStyle() == TRUE)
			StopPlayTipSound();
	}		

}

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnNcLButtonDblClk
*  ��������     ���Ի�������˫����Ŧ��Ϣ
*  �����������	:
*   UINT nHitTest  :�����������
*   CPoint point��˫���������
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
void CButtonST::OnNcLButtonDblClk(UINT nHitTest, CPoint point) 
{
	if(m_HitTestStyle == HTCAPTION)
		return;	

}
/////////////////��///////////////////
//������ڰ�Ŧ��ͣ��2��ʱ����һ��ʾ����
void CButtonST::PlayTipSound(CString fileName)
{

}
// ֹͣ����һ��ʾ����
void CButtonST::StopPlayTipSound()
{

}

//��ʾһ�����˵�
void CButtonST::OnRButtonDown(UINT nFlags, CPoint point) 
{
	INT id = GetDlgCtrlID();

	::SendMessage(GetParent()->GetSafeHwnd(),UWM_RBUTTONDOWN,(long)&point,id);
	CButton::OnRButtonDown(nFlags, point);
}

//���ڵõ���ǰ�ؼ���ID��
INT CButtonST::GetBtnID()
{
  return GetDlgCtrlID();
}



#undef ST_LIKEIE












