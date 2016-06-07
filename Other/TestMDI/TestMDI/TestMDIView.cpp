
// TestMDIView.cpp : CTestMDIView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "TestMDI.h"
#endif

#include "TestMDIDoc.h"
#include "TestMDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestMDIView

IMPLEMENT_DYNCREATE(CTestMDIView, CView)

BEGIN_MESSAGE_MAP(CTestMDIView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTestMDIView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CTestMDIView ����/����

CTestMDIView::CTestMDIView()
{
	// TODO: �ڴ˴���ӹ������

}

CTestMDIView::~CTestMDIView()
{
}

BOOL CTestMDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CTestMDIView ����

void CTestMDIView::OnDraw(CDC* /*pDC*/)
{
	CTestMDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CTestMDIView ��ӡ


void CTestMDIView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

void CTestMDIView::OnInitialUpdate()
{
	if (g_infoDll.m_pUEXP_Init("", "", ""))
	{
		g_infoDll.m_pUEXP_SetLoginType(3, m_hWnd, UM_IMFEEDBACKMSG, IMFLAG_CHILD|IMFLAG_NOHQ, 0);
		char szKhh[51]={0}, szYyb[51]={0}, szSSOCode[255]={0};
		strcpy_s(szKhh, "069000003496");
		g_infoDll.m_pUEXP_Login(2, szKhh, szYyb, szSSOCode, 0);

		g_infoDll.m_pUEXP_ChangeChat(1143);
	}

	return;
}

BOOL CTestMDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CTestMDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CTestMDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CTestMDIView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTestMDIView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTestMDIView ���

#ifdef _DEBUG
void CTestMDIView::AssertValid() const
{
	CView::AssertValid();
}

void CTestMDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestMDIDoc* CTestMDIView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestMDIDoc)));
	return (CTestMDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestMDIView ��Ϣ�������


void CTestMDIView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	g_infoDll.m_pUEXP_Resize();
	
}


void CTestMDIView::OnClose()
{
	g_infoDll.m_pUEXP_Uninit();
	CView::OnClose();
}


void CTestMDIView::OnDestroy()
{
	CView::OnDestroy();

	g_infoDll.m_pUEXP_Uninit();
}
