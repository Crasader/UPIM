#include "stdafx.h"
#include "..\Include\MyBitmapStatic.h"


CMyBitmapStatic::CMyBitmapStatic(void)
{
	VERIFY(m_HollowBrush.CreateStockObject(HOLLOW_BRUSH));
	m_State = -1;
}


CMyBitmapStatic::~CMyBitmapStatic(void)
{
}

BOOL CMyBitmapStatic:: SetBitmap(UINT uResource, int nType /*BITMAP_STRETCH*/) {
	m_nType = nType;
	ASSERT(m_nType == BITMAP_TILE || m_nType == BITMAP_STRETCH || m_nType == BITMAP_CENTER);
	return m_bmpBackground.LoadResource(uResource);
}

BOOL CMyBitmapStatic:: SetBitmap(LPCSTR lpszBitmap, int nType /*BITMAP_STRETCH*/) {
	m_nType = nType;
	ASSERT(m_nType == BITMAP_TILE || m_nType == BITMAP_STRETCH || m_nType == BITMAP_CENTER);
	return m_bmpBackground.LoadBitmap((LPCTSTR)lpszBitmap);
}

void CMyBitmapStatic::SetState(int state)
{
	m_State = state;
}

int CMyBitmapStatic::GetState()
{
	return m_State;
}

void CMyBitmapStatic::DoDataExchange(CDataExchange* pDX)
{
	CStatic::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBitmapDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyBitmapStatic, CStatic)
	//{{AFX_MSG_MAP(CBitmapDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CMyBitmapStatic::DestroyBitmap()
{
	m_bmpBackground.DestroyBitmap();
}

HBRUSH CMyBitmapStatic::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	pDC->SetBkMode(TRANSPARENT);
	return HBRUSH(m_HollowBrush);
	//��ʾ�������ǰ����������죬����ʹ�û�ˢ����ʵ�ָ�ǿ��Ĺ���
	//return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}

BOOL CMyBitmapStatic::OnEraseBkgnd(CDC* pDC) 
{
	if(m_bmpBackground.GetPixelPtr() != 0) {
		ASSERT(m_nType == BITMAP_TILE || m_nType == BITMAP_STRETCH || m_nType == BITMAP_CENTER);

		CRect rc;
		GetClientRect(rc);
		int x = 0, y = 0;

		switch(m_nType) {
		case BITMAP_CENTER:   //λͼ������ʾ
			CStatic::OnEraseBkgnd(pDC);
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
		return CStatic::OnEraseBkgnd(pDC);

	return TRUE;
}

void CMyBitmapStatic::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	dc.SetBkMode(TRANSPARENT);

}

void CMyBitmapStatic::OnLButtonDown(UINT nFlags, CPoint point)
{
	::PostMessage(GetParent()->GetSafeHwnd(), WM_LBUTTONDOWN, (long)this,0);
}