
// UPIMServerView.cpp : CUPIMServerView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "UPIMServer.h"
#endif

#include "UPIMServerDoc.h"
#include "UPIMServerView.h"
#include "Func.h"
#include "globalvar.h"

// CUPIMServerView

IMPLEMENT_DYNCREATE(CUPIMServerView, CFormView)

BEGIN_MESSAGE_MAP(CUPIMServerView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CUPIMServerView ����/����

CUPIMServerView::CUPIMServerView()
	: CFormView(CUPIMServerView::IDD)
{
	// TODO: �ڴ˴���ӹ������

}

CUPIMServerView::~CUPIMServerView()
{
}

void CUPIMServerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CUPIMServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CUPIMServerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	CRect rc;
	this->GetClientRect(&rc);
	m_TabCtrl.Create(this,WS_CHILD | WS_VISIBLE, rc,  IDC_TAB_STATISTICS);
	m_TabCtrl.SetLayout(TAB_LAYOUT_BOTTOM);

	m_DlgStatistics.Create(IDD_DLG_STATISTICS,&m_TabCtrl);
	m_DlgStatistics.SetDlgCtrlID(IDD_DLG_STATISTICS);
	m_TabCtrl.Add(m_DlgStatistics,_T("ͳ��"),0);
	m_DlgStatistics.MoveWindow(CRect(rc.left,rc.top,rc.right-50,rc.bottom-20));

	m_TabCtrl.SetBehavior(TAB_BEHAVIOR_SCROLL);
	m_TabCtrl.ShowScrollButtons( true );

	CImageList imagelistSys;
	CBitmap bmpSys;
	imagelistSys.Create(14,14,ILC_COLOR24 | ILC_MASK,4,0);
	bmpSys.LoadBitmap(IDB_BTM_SYS);
	imagelistSys.Add(&bmpSys,RGB(255,0,255));
	// 
	m_TabCtrl.SetSystemImageList(&imagelistSys);
	m_TabCtrl.ShowMenuButton(FALSE);
	m_TabCtrl.ShowCloseButton(FALSE);
	m_TabCtrl.Update();

	InitChildCtrlPos();

}

void CUPIMServerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CUPIMServerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CUPIMServerView ���

#ifdef _DEBUG
void CUPIMServerView::AssertValid() const
{
	CFormView::AssertValid();
}

void CUPIMServerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CUPIMServerDoc* CUPIMServerView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUPIMServerDoc)));
	return (CUPIMServerDoc*)m_pDocument;
}
#endif //_DEBUG



void CUPIMServerView::OnSize(UINT nType, int cx, int cy)
{
	MoveWnd(cx,cy);
}

// CUPIMServerView ��Ϣ�������

void CUPIMServerView::InitChildCtrlPos()
{
	//��ʼ��ʼ���ؼ���С
	m_IsInitialed = false;
	CRect m_ClientRect;
	this->GetClientRect(&m_ClientRect);
	ScreenToClient(m_ClientRect);
	CSize m_Forsize;
	m_Forsize = GetTotalSize();//����Դ�༭���ж��ô�С�󣬳�������ʱ��С��������󻯺���С�����ô�С��Ϊͬһ��ֵ�����ͻ������ڻ������ʾ�Ĵ�С
	double m_x = (double)m_ClientRect.Width() / m_Forsize.cx;//��ȷ��򷢴���
	double m_y = (double)m_ClientRect.Height() / m_Forsize.cy;//�߶ȷ��򷢴���
	//�����ؼ��Ĵ�С
	CWnd *pWnd = NULL; 
	pWnd = GetWindow(GW_CHILD);
	while(pWnd)//�ж��Ƿ�Ϊ�գ���Ϊ�Ի��򴴽�ʱ����ô˺���������ʱ�ؼ���δ����
	{
		CRect rect;   //��ȡ�ؼ��仯ǰ��С
		pWnd->GetWindowRect(&rect);
		ScreenToClient(&rect);//���ؼ���Сת��Ϊ�ڶԻ����е���������
		m_ControlRect.insert(pair<int, CRect>(pWnd->GetDlgCtrlID(), rect));//����ؼ��ĳ�ʼ��С���Ա���OnSize�����м���ʹ��
		int width = rect.Width();
		int height = rect.Height();
		CHAR szBuf[256];
		GetClassName(pWnd->m_hWnd,szBuf,256);         
		if( _tcsicmp(szBuf,_T("Static")) == 0||_tcsicmp(szBuf,_T("edit")) == 0)   
		{ 
			//Editֻ��λ�ñ仯����Сû�б�
			rect.top = m_y * rect.top;
			rect.left = m_x * rect.left;
			rect.bottom = rect.top + height;
			rect.right = rect.left + width;
		}
		// 		else if (wcsstr(szBuf,_T("Afx:TabWnd")))
		// 		{
		// 			rect.top = m_y * rect.top - 20;
		// 			rect.left = m_x * rect.left;
		// 			rect.bottom = m_y * rect.bottom;
		// 			rect.right = m_x * rect.right;
		// 		}
		else
		{
			//�����ؼ�λ�úʹ�С���仯
			rect.top = m_y * rect.top;
			rect.left = m_x * rect.left;
			rect.bottom = m_y * rect.bottom;
			rect.right = m_x * rect.right;
		}
		pWnd->MoveWindow(&rect);//���ÿؼ���С
		pWnd = pWnd->GetWindow(GW_HWNDNEXT);
	}

	//�ؼ���ʼ������
	m_IsInitialed = true;

}

void CUPIMServerView::MoveWnd(int cx,int cy)
{
	// TODO: �ڴ˴������Ϣ����������
	CFormView::ShowScrollBar(SB_BOTH, false);//����û�й������������������
	//�ڽ��治����С�������Ѿ���ʼ�����
	if (!IsIconic() && m_IsInitialed)
	{
		CSize m_Forsize;
		m_Forsize = GetTotalSize();
		double m_x = (double)cx / m_Forsize.cx;
		double m_y = (double)cy / m_Forsize.cy;
		//��ȡ�ؼ��ĳ�ʼ��С
		map<int, CRect>::iterator pos = m_ControlRect.begin();
		for (; pos != m_ControlRect.end(); ++pos)
		{
			CRect rect = pos->second;
			int width = rect.Width();
			int height = rect.Height();
			CHAR szBuf[256];
			GetClassName(GetDlgItem(pos->first)->m_hWnd,szBuf,256);     				
			if( _tcsicmp(szBuf,_T("Static")) == 0||_tcsicmp(szBuf,_T("edit")) == 0)   
			{ 
				rect.top = m_y * rect.top;
				rect.left = m_x * rect.left;
				rect.bottom = rect.top + height;
				rect.right = rect.left + width;
			}
			// 			else if (wcsstr(szBuf,_T("Afx:TabWnd")) )
			// 			{
			// 				rect.top = m_y * rect.top -20;
			// 				rect.left = m_x * rect.left;
			// 				rect.bottom = m_y * rect.bottom;
			// 				rect.right = m_x * rect.right;
			// 
			// 			}
			else
			{
				rect.top = m_y * rect.top;
				rect.left = m_x * rect.left;
				rect.bottom = m_y * rect.bottom;
				rect.right = m_x * rect.right;
			}
			GetDlgItem(pos->first)->MoveWindow(rect);
		}
	}
}
