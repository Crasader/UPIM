// FloatDibWnd.cpp: implementation of the CFloatDibWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\Paint\resource.h"
#include "..\INCLUDE\FloatDibWnd.h"
#include "..\INCLUDE\DefineMessage.h"
#include "..\include\canvas.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern  CString g_strAppPath;        
extern  IniPaintSet g_stuPaintSet;
extern  BOOL g_createBtn;

//const COLORREF TRANSPARENT_COLOR = RGB(255, 0, 255);

//�α䰴ť��С����
const int BUTTONSIZE = 16;

//����ͼ���Ȼ�߶�С������ĳߴ�ʱ,�������ĸ���Ŧ
const int MINSIZE = 24;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*
*--------------------------------------------------------------------------------
*  ������	: CFloatDibWnd
*  ����		: ���캯��
*  ����		: HWND hParentWnd			- �����ھ��
*			  const CString strFileName - ��ͨ��ͼ�ļ���
*  ˵��		: Ϊ��ͨ��ͼ���ܶ��� 
*--------------------------------------------------------------------------------
*/
CFloatDibWnd::CFloatDibWnd(HWND hParentWnd, const CString strFileName,INT curDrawSize/*=55*/)
{
	m_curDrawSize = curDrawSize;
	m_hParentWnd = hParentWnd; 
	m_ChangeType = CT_MOVE;
	m_pDib = new CDib();
	m_pSrcDib = new CDib();
	m_pHistoryDib = NULL;
	// ��ʶΪ��ͨ��ͼ����
	m_bCartoonWnd = TRUE;
	m_dblPreRotateAngle = 0.0;

	//���ÿ�ͨͼƬ����������
   // CheckShowBtn();
	SetCartoonDib(strFileName);


}


/*
*--------------------------------------------------------------------------------
*  ������	: CFloatDibWnd
*  ����		: ���캯��
*  ����		: HWND hParentWnd			- �����ھ��
*			  const CRect& rect			- ��ѡȡ��������ڸ���������
*  �㷨		: ��������ָ�������ڵ�ͼ���Ƶ�����������
*  ˵��		: Ϊѡȡ���򸡶����ڶ���
*--------------------------------------------------------------------------------
*/
CFloatDibWnd::CFloatDibWnd(HWND hParentWnd, const CRect& rect,INT curDrawSize/*=55*/)
{
	m_curDrawSize = curDrawSize;
	m_hParentWnd = hParentWnd; 
	m_ChangeType = CT_MOVE;
	m_bCartoonWnd = FALSE;
	m_pHistoryDib = NULL;
	m_dblPreRotateAngle = 0.0;
	// �������꣬��ȷ�����ϽǺ����½�������ȷ	
	m_rcWndRect.left = rect.left <= rect.right ? rect.left : rect.right;
	m_rcWndRect.right = rect.left <= rect.right ? rect.right : rect.left;
	m_rcWndRect.top = rect.top <= rect.bottom ? rect.top : rect.bottom;
	m_rcWndRect.bottom = rect.top <= rect.bottom ? rect.bottom : rect.top;	

	// ��ָ��������ץȡָ�������ͼ�񵽴���ͼ����
	m_pDib = new CDib();	
	m_pDib->Create(m_hParentWnd, m_rcWndRect);

	// ����ԭʼͼ��
	m_pSrcDib = m_pDib->Clone();
	
    CheckShowBtn();
	// ��������
	CreateWnd();
}


/*
*--------------------------------------------------------------------------------
*  ������	: CFloatDibWnd
*  ����		: ���캯��
*  ����		: HWND hParentWnd	- �����ھ��
*			  CDib* pDib		- DIBͼ��ָ��
*  �㷨		: �½��������ڣ���������ʾ����������Ϊָ����DIBͼ��
*  ˵��     : Ϊճ��ͼ���ܶ���
*--------------------------------------------------------------------------------
*/
CFloatDibWnd::CFloatDibWnd(HWND hParentWnd, CDib* pDib,INT curDrawSize/*=55*/)
{
	ASSERT(pDib);
	m_curDrawSize = curDrawSize;
	m_hParentWnd = hParentWnd; 
	m_ChangeType = CT_MOVE;
	m_pHistoryDib = NULL;
	m_bCartoonWnd = FALSE;
	m_dblPreRotateAngle = 0.0;
	m_pDib = pDib->Clone();
	ASSERT(m_pDib);

	// ����ԭʼͼ��
	m_pSrcDib = m_pDib->Clone();
	ASSERT(m_pSrcDib);


	// ������λ����Ϊ����
	long nWidth = m_pDib->GetWidth();
	long nHeight = m_pDib->GetHeight();

	CRect rcWnd;
	::GetWindowRect(m_hParentWnd, &rcWnd);
	
	m_rcWndRect.left = rcWnd.Width() / 2 - nWidth / 2;
	m_rcWndRect.right = rcWnd.Width() / 2 + nWidth / 2;
	m_rcWndRect.top = rcWnd.Height() / 2 - nHeight / 2;
	m_rcWndRect.bottom = rcWnd.Height() / 2 + nHeight / 2;

    CheckShowBtn();

	//��������
	CreateWnd();
}


CFloatDibWnd::~CFloatDibWnd()
{
	DestroyWindow();

	if(m_pDib)
	{
	   delete m_pDib;
	    m_pDib = NULL;
	}
	if(m_pHistoryDib)
	{
	    delete m_pHistoryDib;
	    m_pHistoryDib = NULL;
	}
	if (m_pSrcDib)
		delete m_pSrcDib;
}


BEGIN_MESSAGE_MAP(CFloatDibWnd, CWnd)
	//{{AFX_MSG_MAP(CFloatDibWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_MOVE()
	ON_WM_SETCURSOR()
	ON_WM_NCHITTEST()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_MESSAGE(WM_OWNDOWNMESSAGE, OnBeginChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/*
*--------------------------------------------------------------------------------
*  ������	: OnCreate
*  ����     : ���ش���������Ϣ
*  ˵��     : ��������ʱ�����α䰴ť
*--------------------------------------------------------------------------------
*/
int CFloatDibWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CreateButton();

	return 0;
}


/*
*--------------------------------------------------------------------------------
*  ������	: CreateButton
*  ����		: ���������������ܵ��α䰴ť
*  ˵��		: ��ťλ��ͼƬ���ڣ�ÿ����ťΪ 16 ���ش�С
*--------------------------------------------------------------------------------
*/
BOOL CFloatDibWnd::CreateButton()
{	
    if(!g_createBtn)
		return FALSE;


	// ����ͼƬ���ܵ��α䰴ť
	static CString strfilename[] = {
				_T("BtnRes\\i1-2.bmp"),  _T("BtnRes\\i1-1.bmp"),
				_T("BtnRes\\i2-2.bmp"),  _T("BtnRes\\i2-1.bmp"),
				_T("BtnRes\\i3-2.bmp"),  _T("BtnRes\\i3-1.bmp"),
				_T("BtnRes\\i4-2.bmp"),  _T("BtnRes\\i4-1.bmp"),
				_T("BtnRes\\i5-2.bmp"),  _T("BtnRes\\i5-1.bmp"),
				_T("BtnRes\\i6-2.bmp"),  _T("BtnRes\\i6-1.bmp"),
				_T("BtnRes\\i7-2.bmp"),  _T("BtnRes\\i7-1.bmp"),
				_T("BtnRes\\i8-2.bmp"),  _T("BtnRes\\i8-1.bmp")
				};

	CRect rect;
	GetClientRect(&rect);

	HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_CURHAND);
//	hCursor = LoadCursor(NULL, IDC_HELP);
 //    hCursor = AfxGetApp()->LoadCursor(IDC_HELP);

		// ������С�����Ͻ�
		m_btnResize.Create("", WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, IDC_VERTOPSIZE); 
		m_btnResize.SetBitmaps(strfilename[4], g_stuPaintSet.tranCol, strfilename[5], g_stuPaintSet.tranCol); 
		m_btnResize.SetCursor(hCursor); 
		m_btnResize.SetLbuttonSendMsgStyle(1);

		// ��ת��ť�����½�
		m_btnRotate.Create("", WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, IDC_ROTATE); 
		m_btnRotate.SetBitmaps(strfilename[6], g_stuPaintSet.tranCol, strfilename[7], g_stuPaintSet.tranCol); 
		m_btnRotate.SetCursor(hCursor); 
		m_btnRotate.SetLbuttonSendMsgStyle(1);

		// ����ť�����½�
		m_btnHorMirror.Create("", WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, IDC_HORMIRROR); 
		m_btnHorMirror.SetBitmaps(strfilename[8], g_stuPaintSet.tranCol, strfilename[9], g_stuPaintSet.tranCol); 
		m_btnHorMirror.SetCursor(hCursor); 
		m_btnHorMirror.SetLbuttonSendMsgStyle(1);

		// ��ת��ť�����Ͻ�
		m_btnVerMirror.Create("", WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, IDC_VERMIRROR); 
  		m_btnVerMirror.SetBitmaps(strfilename[10], g_stuPaintSet.tranCol, strfilename[11], g_stuPaintSet.tranCol); 
		m_btnVerMirror.SetCursor(hCursor); 
		m_btnVerMirror.SetLbuttonSendMsgStyle(1);

     if(!g_createBtn)
	 {
     	m_btnRotate.ShowWindow(SW_HIDE); 
		m_btnVerMirror.ShowWindow(SW_HIDE); 
		m_btnHorMirror.ShowWindow(SW_HIDE); 
		m_btnResize.ShowWindow(SW_HIDE); 
	 }

	return TRUE;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   : OnPaint() 
*  ��������     : ���ƴ������ߴ緢���ı�ʱ�ػ�����
*  �㷨			: ͸����ʾλͼ��͸��ɫΪ g_stuPaintSet.tranCol
*  ����˵��		: ��������ʱͼ�񲢲��ı䣬��������ʾʱ�ı临��λͼ��Ȼ��������ʾ
*--------------------------------------------------------------------------------
*/
void CFloatDibWnd::OnPaint() 
{
	ASSERT(m_pDib);

	CRect rect;
	GetClientRect(&rect);

	// �õ�ǰͼ�񴴽�һ����ʱλͼ����������������ʾ���Է�ʧ��
	CDib *pTmpDib = m_pDib->Clone();
	pTmpDib->ChangeImageSize(rect.Width(), rect.Height()); 
	pTmpDib->DisplayTransparent(GetDC(), 0, 0, g_stuPaintSet.tranCol);
	delete pTmpDib;

	CWnd::OnPaint();
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   : OnNcHitTest
*  ��������     : ������ԣ����ر����������϶�����
*--------------------------------------------------------------------------------
*/
UINT CFloatDibWnd::OnNcHitTest(CPoint point) 
{
	return HTCAPTION;
}


/*
*--------------------------------------------------------------------------------
*  ������: OnMove
*  ����  : �������ƶ���Ϣ���ô���ˢ��
*  �㷨  : �����ѡ�����򴰿��ƶ�ʱ�������ԭ���Ļ�������
*--------------------------------------------------------------------------------
*/
void CFloatDibWnd::OnMove(int x, int y) 
{
	Invalidate(TRUE);
}


/*
*--------------------------------------------------------------------------------
*  ������	: SetCartoonDib
*  ����		: ���ÿ�ͨ���ڵ� Dib ͼ��
*  ����		: CString strDibFileName -	����λͼ���ļ���
*  �㷨		:
*  ǰ������ : m_pDib �ѳ�ʼ��
*  �������� : ɾ���ִ��λͼ�������µ�λͼ�������ִ洰�ڣ��½�һ�����ڲ�������ʾ
*--------------------------------------------------------------------------------
*/
void CFloatDibWnd::SetCartoonDib(CString strDibFileName)
{
    if(!FileExist(strDibFileName))
		return;

	DestroyWindow();

	if (m_pDib)
	{
		m_pDib->Destroy();
		delete m_pDib;
	}

//	Canvas * pWnd = (Canvas *)GetParent();
//	CRect wndRect = pWnd->GetCanvasWndRect();

	// ���ļ��е���ͼƬ
	m_pDib = new CDib();
	m_pDib->Load(strDibFileName);
//	m_pDib->ChangeImageSize(nWidth, nHeight);

	CRect rcWnd;
	::GetWindowRect(m_hParentWnd, &rcWnd);

	// ��ʼ��ʱ�Ĵ��ڴ�С
	long nWidth = m_pDib->GetWidth();
	long nHeight = m_pDib->GetHeight();

    double scaleXY = nWidth/nHeight;
    double scaleYX = nHeight/nWidth;
    double scaleDef = rcWnd.Width()/rcWnd.Height();

	if(scaleXY <= scaleDef)
	{
		if(nWidth > rcWnd.Width()-4)
		{

     			nWidth = rcWnd.Width()-20;
				nHeight = nWidth * scaleYX;
		}
	}
   else
   {
      if(nHeight > rcWnd.Height() - 4)
	  {
		  nHeight = rcWnd.Height() -4;
		  nWidth = nHeight * scaleXY;
	  }

   }
   
   //�����������ϻ����λ�ü���ͼ����صĴ�С
    if(g_stuPaintSet.bCartoonOrgSize)
	{
		m_rcWndRect.left = rcWnd.Width() / 2 - nWidth / 2;
		m_rcWndRect.right = rcWnd.Width() / 2 + nWidth / 2;
		m_rcWndRect.top = rcWnd.Height() / 2 - nHeight / 2;
		m_rcWndRect.bottom = rcWnd.Height() / 2 + nHeight / 2;
	}
	else
	{
        DOUBLE scale =  m_curDrawSize/110.0;
	    m_rcWndRect.left = rcWnd.Width() / 2 - DOUBLE(nWidth / 2.0)*scale;
		m_rcWndRect.right = rcWnd.Width() / 2 + DOUBLE(nWidth / 2.0)*scale;
		m_rcWndRect.top = rcWnd.Height() / 2 - DOUBLE(nHeight / 2.0)*scale;
		m_rcWndRect.bottom = rcWnd.Height() / 2 + DOUBLE(nHeight / 2.0)*scale;      

	}

	// ����ԭʼͼ��
	if (m_pSrcDib)
		delete m_pSrcDib;
	m_pSrcDib = m_pDib->Clone();

   CheckShowBtn();

	// ��������
	CreateWnd();
}


/*
*--------------------------------------------------------------------------------
*  ������	: CreateWnd
*  ����		: ������������
*--------------------------------------------------------------------------------
*/
BOOL CFloatDibWnd::CreateWnd()
{	
	DestroyWindow();
	// ��������
	return Create(NULL,
			"��ͨ����",
			WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS, 
		    m_rcWndRect, 
			CWnd::FromHandle(m_hParentWnd), 
			0x0844 );
}	


/*
*--------------------------------------------------------------------------------
*  ������	: CenterDib
*  ����		: �������������ڸ����ڵ����м�
*  �㷨		: ���ڴ�С��ͼ��ͬ����С
*  ǰ������ : m_pDib �ѳ�ʼ��
*  ˵��		: �ó��ľ�����������Ը����ڵ�����
*--------------------------------------------------------------------------------
*/
//DEL void CFloatDibWnd::CenterWnd()
//DEL {
//DEL 	long nWidth = m_pDib->GetWidth();
//DEL 	long nHeight = m_pDib->GetHeight();
//DEL 
//DEL 	CRect rcWnd;
//DEL 	::GetWindowRect(m_hParentWnd, &rcWnd);
//DEL 	
//DEL 	m_rcWndRect.left = rcWnd.Width() / 2 - nWidth / 2;
//DEL 	m_rcWndRect.right = rcWnd.Width() / 2 + nWidth / 2;
//DEL 	m_rcWndRect.top = rcWnd.Height() / 2 - nHeight / 2;
//DEL 	m_rcWndRect.bottom = rcWnd.Height() / 2 + nHeight / 2;
//DEL }


/*
*--------------------------------------------------------------------------------
*  ������	: MergeDib
*  ����		: �������ڵ�ͼ����ָ��ͼ���ں�
*  ����		: CDib* pDib	-	����ͼ���ں��ڴ�DIB֮��
*  �㷨		: �����ذ�ť��Ȼ�󽫴����ڵ�ͼ��ץȡ�������ٽ���DIB�����DIB�ں�
*--------------------------------------------------------------------------------
*/
BOOL CFloatDibWnd::MergeDib(CDib * pDib)
{	
	CDib* newDib = new CDib();
	
	// ����ȫ���α䰴ť
	if(g_createBtn)
    	HideAllButton();

	CRect rcSelf, rcParent;
	GetWindowRect(&rcSelf);
	::GetWindowRect(m_hParentWnd, &rcParent);

	// ץȡ�������ڿͻ���ͼ��
	newDib->Create(GetSafeHwnd(), CRect(0, 0, rcSelf.Width(), rcSelf.Height()) );

	// �����������
	int xStart, yStart;

	// �� 2 ����Ϊ�߿�ռ��������
	xStart = rcSelf.left - rcParent.left - 2;
	yStart = rcSelf.top - rcParent.top - 2;

	pDib->MergeDib(newDib->GetHandle(), CPoint(xStart, yStart));

	delete newDib;
	return TRUE;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnLButtonUp
*  ��������     :����������ʱ����Ϣ
*  �����������	:
*    UINT nType����������
*    CPoint point ����ǰ���������λ��
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :����ȡ��������µı�־���������Ҫ��ת�ĽǶȣ�������ת���λͼ
*--------------------------------------------------------------------------------
*/
void CFloatDibWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{       
	//�����α����
//	SetCursor(LoadCursor(NULL, IDC_ARROW));
	SetCursor(AfxGetApp()->LoadCursor(IDC_ARROW));
	switch (m_ChangeType)
	{
	case CT_ROTATE:
		{
		// ��ת�����ڵ�ͼ����ԭʼͼ��Ϊ�������󣬴˴���תҪ����������ת�Ƕ�
		double dblAngle = GetRotateAngle(PointToParentClient(point));

		// ��ת
		RotateAngle(dblAngle);

		UpdateWindow();
		break;
		}

	case CT_RESIZE:
		{
		// ����ͼ��ʱʵ����ֻ�Ǹı䴰�ڴ�С�������ı�ͼ���ʵ�ʳߴ�
		// �ı�ͼ�񼰴��ڴ�С
		CRect rect = RectToParentClient(point);
		::MoveWindow(GetSafeHwnd(), rect.left, rect.top, rect.Width(), rect.Height(), TRUE);
		break;
		}
	
	default:
		return;
	}
	m_ChangeType = CT_MOVE;

	::SendMessage(m_hParentWnd, WM_PAINT, 0, 0);
	InvalidateRect(NULL, TRUE);

	ReleaseCapture();

//	CWnd::OnLButtonUp(nFlags, point);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnMouseMove
*  ��������     :������ڴ����ƶ���Ϣ
*  �����������	:
*    UINT nType ��  ��������
*    CPoint point ����ǰ���������λ��
*  ���ر���˵�� :
*  �㷨����		:�Ծ��������ĵ�����Ϊ���������ת
*  ����˵��     :��Ҫ��������Ƕ���תͼ��ʱ���õ���ת�ĽǶ�
*--------------------------------------------------------------------------------
*/
void CFloatDibWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
    //��һ���߿򣬵���תͼƬʱ��ֻ��ת����򣬵�MouseUpʱ����ʽ��תͼ��

	HDC hDC = ::GetDC(m_hParentWnd);
	switch (m_ChangeType)
	{
	case CT_ROTATE:
		{	    	
		double dblAngle;
		dblAngle = GetRotateAngle(PointToParentClient(m_ptLast));
		DrawRotateBorder(dblAngle);

		dblAngle = GetRotateAngle(PointToParentClient(point));
        DrawRotateBorder(dblAngle);
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURROTATE));	
		
		break;
		}

	case CT_MOVE:
		break;

	case CT_RESIZE:
		// ������С	
		{
			CRect rcBorder = RectToParentClient(m_ptLast);
			DrawResizeBorder(rcBorder);				

			rcBorder = RectToParentClient(point);
			DrawResizeBorder(rcBorder);

			break;
		}

	default:
		break;
	}

	m_ptLast = point;
	CWnd::OnMouseMove(nFlags, point);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnSize
*  ��������     :���ڳߴ��С�����仯ʱ
*  �����������	:
*    UINT nType������ߴ�仯����
*    int cx    �������¿ͻ����Ŀ��
*    int cy    �������¿ͻ����ĸ߶�
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CFloatDibWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	CRect rect;
	GetClientRect(&rect);

	//�����α䰴ť��λ��
    if(g_createBtn)
	{
		m_btnResize.MoveWindow(rect.Width() - BUTTONSIZE, 0, BUTTONSIZE, BUTTONSIZE);
		m_btnRotate.MoveWindow(rect.Width() - BUTTONSIZE, rect.bottom - BUTTONSIZE, BUTTONSIZE, BUTTONSIZE);
		m_btnHorMirror.MoveWindow(0, rect.bottom - BUTTONSIZE, BUTTONSIZE, BUTTONSIZE);
		m_btnVerMirror.MoveWindow(0, 0, BUTTONSIZE, BUTTONSIZE);
	}
	Invalidate(TRUE);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnSetCursor
*  ��������     :���ù����ʽ
*  �����������	:
*		CWnd* pWnd   ��
*		UINT nHitTest��
*		UINT message ��
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
BOOL CFloatDibWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	SetCursor(LoadCursor(NULL, IDC_SIZEALL));
  //  SetCursor(AfxGetApp()->LoadCursor(IDC_SIZEALL));
	return TRUE;
}


/*
*--------------------------------------------------------------------------------
*  ������	: DrawRotateBorder
*  ����		: ��������ת�����е���߿�
*  ����		: DOUBLE angle - ��ת�Ƕ�
*  �㷨
*--------------------------------------------------------------------------------
*/
void CFloatDibWnd::DrawRotateBorder(double angle)
{
	angle = -angle;
	CRect rect = RectToParent();
	CPoint ptCenter = rect.CenterPoint();
	double dwRadius = sqrt(pow((ptCenter.x - rect.left), 2) + pow((ptCenter.y - rect.top), 2));

	double dwStartAngle[4];
	double disX = (double)(rect.Width() / 2);
	double disY = (double) (rect.Height() / 2);	
	double dwBaseAngle = atan(disX / disY) * (180 / 3.1415926545);

	dwStartAngle[0] = 90 + dwBaseAngle;
	dwStartAngle[1] = 270 - dwBaseAngle;
	dwStartAngle[2] = 270 + dwBaseAngle;
	dwStartAngle[3] = 90 - dwBaseAngle;

	CPoint ptVertex[4];	
	ptVertex[0] = GetArcEndPoint(ptCenter, dwRadius, dwStartAngle[0], angle);
	ptVertex[1] = GetArcEndPoint(ptCenter, dwRadius, dwStartAngle[1], angle);
	ptVertex[2] = GetArcEndPoint(ptCenter, dwRadius, dwStartAngle[2], angle);
	ptVertex[3] = GetArcEndPoint(ptCenter, dwRadius, dwStartAngle[3], angle);


	HDC hDC = ::GetDC(m_hParentWnd);

	HBRUSH hOldBrush = (HBRUSH) SelectObject(hDC, GetStockObject(NULL_BRUSH));
	HPEN hPen = CreatePen(PS_DASH, 1, RGB(0x0, 0x0, 0x0));
	HPEN hOldPen = (HPEN) SelectObject(hDC, hPen);
	int nOldRop = SetROP2(hDC, R2_NOTXORPEN);

	::Polygon(hDC, ptVertex, 4);

	SetROP2(hDC, nOldRop);
	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hOldBrush);
	DeleteObject(hOldPen);
	DeleteObject(hPen);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   : GetRotateAngle
*  ��������     : ���������߳�������ת�ĽǶ�(�Ƕ�)��ɨ��ǣ�˳ʱ��Ϊ����
*  �����������	: CPoint ptEnd		-	��ת��ֹ����ֹ
*  ���ر���˵�� :
*  �㷨����		: �Ը������������½ǵ�Ϊ��׼�㣬������ֹ�����׼�������ˮƽ��֮��ĽǶ�
*  ����˵��     : ����������ڸ����ڿͻ��������꣬˳ʱ����תΪ����
*--------------------------------------------------------------------------------
*/
DOUBLE CFloatDibWnd::GetRotateAngle(CPoint ptEnd)
{
	// ����ת�Ƕȳ���
	const double pitoa = 180 / 3.1415926535l;

	// ���ھ���
	CRect rect;
	rect = RectToParentClient();
	
	// �����½ǵ�Ϊ��׼��
	CPoint ptCenter, ptBottomRight;


	// ��ͼ������Ϊ�Ƕȼ����׼��
	ptCenter = rect.CenterPoint();
	ptBottomRight = rect.BottomRight();

	double nx, ny, angle, dblStartAngle;

	// ������ʼ��ת��
	nx = abs(ptBottomRight.x - ptCenter.x);
	ny = abs(ptBottomRight.y - ptCenter.y);
	dblStartAngle = atan(ny / nx) * pitoa;

	// ������ת��������½ǵ������ĵ������ˮƽ�ߵļн�
	nx = abs(ptEnd.x - ptCenter.x);
	ny = abs(ptEnd.y - ptCenter.y);
	angle = atan(ny / nx) * pitoa;

	if (ptEnd.x > ptCenter.x && ptEnd.y > ptCenter.y)
	{
		// �����ޣ�Ϊ����
		angle = angle;
	}
	else if (ptEnd.x > ptCenter.x && ptEnd.y < ptCenter.y)
	{
		// һ���ޣ�Ϊ����
		angle = -angle;
	}
	else if (ptEnd.x < ptCenter.x && ptEnd.y > ptCenter.y)
	{
		// ������
		angle = 180 - angle;
	}
	else if (ptEnd.x < ptCenter.x && ptEnd.y < ptCenter.y)
	{
		// ������
		angle = 180 + angle;
	}
	else if (ptEnd.x == ptCenter.x && ptEnd.y < ptCenter.y)
	{
		// ��ֱ������
		angle = 270;
	}
	else if (ptEnd.x == ptCenter.x && ptEnd.y > ptCenter.y)
	{
		// ��ֱ�߸���
		angle = 90;
	}
	else if (ptEnd.y == ptCenter.y && ptEnd.x > ptCenter.x)
	{
		// ˮƽ������
		angle = 0;
	}
	else if (ptEnd.y == ptCenter.y && ptEnd.x < ptCenter.x)
	{
		// ˮƽ�߸���
		angle = 180;
	}
	else if (ptEnd.y == ptCenter.y && ptEnd.x == ptCenter.x)
	{
		// ԭ��
		angle = 0;
	}	

	// ͼƬ��ת�Ƕ�
	angle -= dblStartAngle;

	return angle;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :HideAllButton()
*  ��������     :�������еİ�Ŧ���������ں�λͼʱ����Ŧ�ؼ�Ҳ���뻭����ͼ����
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CFloatDibWnd::HideAllButton()
{	

	m_btnRotate.ShowWindow(SW_HIDE); 
	m_btnVerMirror.ShowWindow(SW_HIDE); 
	m_btnHorMirror.ShowWindow(SW_HIDE); 
	m_btnResize.ShowWindow(SW_HIDE); 

	//��ˢ�¸�������ˢ��������
	::SendMessage(m_hParentWnd, WM_PAINT, 0, 0);
	UpdateWindow();
}


/*
*--------------------------------------------------------------------------------
*  ������	: OnBeginChange
*  ����		: ��ʼ��ͼƬ�����α����
*  ����     :
*		WPARAM wParam	-	�α䰴ť�ؼ�ID��
*		LPARAM lParam	-	����
*--------------------------------------------------------------------------------
*/
void CFloatDibWnd::OnBeginChange(WPARAM wParam, LPARAM lParam)
{
	CRect rcSelf, rect;
	::GetWindowRect(GetSafeHwnd(), &rcSelf);
	rect = RectToParentClient();
//	::GetWindowRect(&rcParent);

	// �ؼ�ID
	WORD wCtlID = LOWORD(wParam);
	switch (wCtlID)
	{
	case IDC_ROTATE:
		m_ChangeType = CT_ROTATE;
		m_ptLast.x = rect.Width();
		m_ptLast.y = rect.Height();
//		::SetCursorPos(rcSelf.right, rcSelf.bottom);
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURROTATE));
		break;

	case IDC_VERMIRROR:
		// ��ת��ԭʼͼ��͵�ǰͼ�񶼷�ת����Ϊ��ת��������ʧ��
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURVERMIRRION));
		m_pSrcDib->FlipVert();
		m_pDib->FlipVert();
		::InvalidateRect(m_hParentWnd, NULL, FALSE);
		return;
		break;

	case IDC_HORMIRROR:
		// ����ԭʼͼ��͵�ǰͼ�񶼷�ת����Ϊ���񲻻�����ʧ��
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURHORMIRRION));
		m_pSrcDib->FlipHorz();
		m_pDib->FlipHorz();
		::InvalidateRect(m_hParentWnd, NULL, FALSE);
		return;
		break;		

	default:
		// ���ţ�������������ڸ������ڵ����꣬���Ǹ�����
		m_ChangeType = CT_RESIZE;

		// �����λ�ö������Ͻ�
		m_ptLast.x = rcSelf.Width();
		m_ptLast.y = 0;
		::SetCursorPos(rcSelf.right, rcSelf.top);
		
		DrawResizeBorder(rect);	
		break;
	}
	
	// ���������Ϣ
	if (SetCapture() != NULL)
	{
		ReleaseCapture();
		SetCapture();
	}

//	SetCursor(LoadCursor(NULL, IDC_ARROW));
     SetCursor(AfxGetApp()->LoadCursor(IDC_ARROW));
}


/*
*--------------------------------------------------------------------------------
*  ������	: DrawResizeBorder
*  ����		: ���������Ź����е���߿�
*  ����		: DOUBLE angle - ��ת�Ƕ�
*  �㷨
*--------------------------------------------------------------------------------
*/
void CFloatDibWnd::DrawResizeBorder(const CRect &rect) const
{
	HDC hDC = ::GetDC(m_hParentWnd);

	HBRUSH hOldBrush = (HBRUSH) SelectObject(hDC, GetStockObject(NULL_BRUSH));
	HPEN hPen = CreatePen(PS_DASH, 1, RGB(0x0, 0x0, 0x0));
	HPEN hOldPen = (HPEN) SelectObject(hDC, hPen);

	int nOldRop = SetROP2(hDC, R2_NOTXORPEN);
	Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
	SetROP2(hDC, nOldRop);

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hOldBrush);
	DeleteObject(hOldPen);
	DeleteObject(hPen);
}


/*
*--------------------------------------------------------------------------------
*  ������	: RectToParent
*  ����		: �õ���Ը���������Ĵ��ڱ߿��������
*  ����ֵ	: CRect	- �Ӵ�����Ը����ڵ�����
*  ˵��		: ����Ը����ڶ��Ǹ����ڿͻ�������Ϊ���������������صı߿�
*--------------------------------------------------------------------------------
*/
CRect CFloatDibWnd::RectToParent()
{
	CRect rcParent, rcSelf, rect;
	::GetWindowRect(GetSafeHwnd(), &rcSelf);
	::GetWindowRect(m_hParentWnd, &rcParent);

	// ��Ը��������ϽǶ��Ǹ����ڿͻ������Ͻǵ�����
	rect.left = rcSelf.left - rcParent.left;
	rect.top = rcSelf.top - rcParent.top;
	rect.bottom = rcSelf.top - rcParent.top + rcSelf.Height();
	rect.right = rect.left + rcSelf.Width();
	
	return rect;
}


/*
*--------------------------------------------------------------------------------
*  ������	: RectToParent
*  ����		: �õ���Ը���������Ĵ��ڱ߿��������
*  ����		: CPoint& point	-	�������Ͻ��ƶ��������
*--------------------------------------------------------------------------------
*/
CRect CFloatDibWnd::RectToParent(const CPoint& point)
{
	CRect rcSelf, rcParent, rect;
	::GetWindowRect(GetSafeHwnd(), &rcSelf);
	::GetWindowRect(m_hParentWnd, &rcParent);
	
	int nX, nY;
	nX = point.x - rcSelf.Width();
	nY = - point.y;

	// �ײ��������겻��
	if (point.x >= 0 && point.y <= rcSelf.Height())
	{
		// point ���ڵ�һ����
		rect.bottom = rcSelf.top - rcParent.top + rcSelf.Height() ;
		rect.left = rcSelf.left - rcParent.left;
		rect.top = rcSelf.top - rcParent.top - nY;
		rect.right = rect.left + rcSelf.Width() + nX;
	}
	else if (point.x >= 0 && point.y > rcSelf.Height())
	{	
		// point ���ڵ�������
		rect.bottom = rcSelf.top - rcParent.top + rcSelf.Height() + (point.y - rcSelf.Height());
		rect.left = rcSelf.left - rcParent.left;
		rect.top = rcSelf.top - rcParent.top + rcSelf.Height();
		rect.right = rect.left + rcSelf.Width() + nX;
	}
	else if (point.x < 0 && point.y <= rcSelf.Height())
	{
		// ���ڵڶ����ޣ���߱�Ϊ�ұߣ��ױ߲���
		rect.bottom = rcSelf.top - rcParent.top + rcSelf.Height() ;
		rect.left = rcSelf.left - rcParent.left - abs(point.x);
		rect.top = rcSelf.top - rcParent.top - nY;
		rect.right = rcSelf.left - rcParent.left ;
	}
	else if (point.x < 0 && point.y > rcSelf.Height())
	{
		// ���ڵ������ޣ��ϱ߱��±�
		rect.left = rcSelf.left - rcParent.left - abs(point.x);
		rect.right = rcSelf.left - rcParent.left;
		rect.top = rcSelf.top - rcParent.top + rcSelf.Height();
		rect.bottom = rcSelf.top - rcParent.top + rcSelf.Height() + (point.y - rcSelf.Height());		
	}	

	return rect;
}


/*
*--------------------------------------------------------------------------------
*  GetArcEndPoint
*  ����	- ����һ�λ����յ�����
*  ����
*	[in]  CPoint ptCenter		- ������Բ��Բ������
*	[in]  DWORD dwRadius		- ������Բ�İ뾶
*	[in]  FLOAT eStartAngle		- ������ʼ�Ƕ�
*	[in]  FLOAT eSweepAngle		- ����ɨ��Ƕ�
*  ����ֵ
*		 CPoint	 -	�����յ�����
*  �㷨
*		��ʱ����ת
*--------------------------------------------------------------------------------
*/
CPoint CFloatDibWnd::GetArcEndPoint(const CPoint &ptCenter, double dwRadius, double eStartAngle, double eSweepAngle) const
{
	// �Ƕ�ת���ȳ���
	const FLOAT piover180 = (FLOAT) 3.141592653586 / 180;

	// ȷ�����ֻ��һ��Բ
	if (eSweepAngle >= 360)
		eSweepAngle = 360;
	else if (eSweepAngle <= -360)
		eSweepAngle = -360;

	// ������ʼ�ǡ���ֹ�ǶȵĻ���
	double eEndAngle = (eStartAngle + eSweepAngle) * piover180;

	// ���������ʼ����ֹ�������
	int nXEnd, nYEnd;

	nXEnd = ptCenter.x + (int) (dwRadius * cos(eEndAngle));
	nYEnd = ptCenter.y - (int) (dwRadius * sin(eEndAngle));

	return CPoint(nXEnd, nYEnd);
}


/*
*--------------------------------------------------------------------------------
*  ������	: PointToParentClient
*  ����		: �õ���Ը����ڿͻ�������Ĵ��ڱ߿��������
*  ����		: CPoint& point	-	�������Ͻ��ƶ��������
*--------------------------------------------------------------------------------
*/
CPoint CFloatDibWnd::PointToParentClient(const CPoint &point)
{
	CRect rcSelf, rcParent;
	::GetWindowRect(GetSafeHwnd(), &rcSelf);
	::GetWindowRect(m_hParentWnd, &rcParent);

	CPoint pt;
	pt.x = rcSelf.left - rcParent.left + point.x - 2;
	pt.y = rcSelf.top - rcParent.top + point.y - 2;

	return pt;
}


//DEL BOOL CFloatDibWnd::SaveOperate()
//DEL {
//DEL 	if (m_pHistoryDib)
//DEL 		delete m_pHistoryDib;
//DEL 
//DEL 	m_pHistoryDib = m_pDib->Clone();	
//DEL 	m_HistoryChangeType = m_ChangeType;
//DEL 	m_rcHistoryWndRect = RectToParent();
//DEL 
//DEL 	return m_pHistoryDib ? TRUE: FALSE ;
//DEL } 


//DEL BOOL CFloatDibWnd::Undo()
//DEL {
//DEL 	if (!m_pHistoryDib)	
//DEL 		return FALSE;
//DEL 
//DEL 	// ����ǰDIB����ʷDIB��������֧�� Redo
//DEL 	CDib* pTmpDib = m_pDib;
//DEL 	m_pDib = m_pHistoryDib;
//DEL 	m_pHistoryDib = pTmpDib;
//DEL 
//DEL 	if (m_HistoryChangeType == CT_RESIZE)
//DEL 	{
//DEL 		::MoveWindow(GetSafeHwnd(), 
//DEL 			m_rcHistoryWndRect.left,
//DEL 			m_rcHistoryWndRect.top,
//DEL 			m_rcHistoryWndRect.Width(), 
//DEL 			m_rcHistoryWndRect.Height(), 
//DEL 			FALSE);
//DEL 	}
//DEL 
//DEL 	return TRUE;
//DEL }


//DEL BOOL CFloatDibWnd::Redo()
//DEL {
//DEL 	if (!m_pHistoryDib)	
//DEL 		return FALSE;
//DEL 
//DEL 	// ����ǰDIB����ʷDIB��������֧�� Redo
//DEL 	CDib* pTmpDib = m_pDib;
//DEL 	m_pDib = m_pHistoryDib;
//DEL 	m_pHistoryDib = pTmpDib;
//DEL 
//DEL 	if (m_HistoryChangeType == CT_RESIZE)
//DEL 	{
//DEL 		::MoveWindow(GetSafeHwnd(), 
//DEL 			m_rcHistoryWndRect.left,
//DEL 			m_rcHistoryWndRect.top,
//DEL 			m_rcHistoryWndRect.Width(), 
//DEL 			m_rcHistoryWndRect.Height(), 
//DEL 			FALSE);
//DEL 	}
//DEL 
//DEL 	return TRUE;
//DEL }


/*
*--------------------------------------------------------------------------------
*  ������	: RectToParentClient
*  ����		: �õ���Ը����ڿͻ�������Ĵ��ڱ߿��������
*  ����ֵ	: CRect	- �Ӵ�����Ը����ڿͻ���������
*  ˵��		: ������ڸ����ڵĿͻ�������Ϊ���������������صı߿�
*--------------------------------------------------------------------------------
*/
CRect CFloatDibWnd::RectToParentClient()
{
	CRect rect = RectToParent();

	// �򸸴��ڿ�ռ�������أ���������ƽ����������
	rect.OffsetRect(-2, -2);
	//rect.InflateRect(-2, -2, -2, -2);

	return rect;
}


/*
*--------------------------------------------------------------------------------
*  ������	: RectToParentClient
*  ����		: �õ���Ը����ڿͻ�������Ĵ��ڱ߿��������
*  ����		: �������Ͻǵĵ�����
*  ����ֵ	: CRect	- �Ӵ�����Ը����ڿͻ���������
*  ˵��		: ������ڸ����ڵĿͻ�������Ϊ���������������صı߿�
*--------------------------------------------------------------------------------
*/
CRect CFloatDibWnd::RectToParentClient(const CPoint& point)
{
	CRect rect = RectToParent(point);
	rect.OffsetRect(-2, -2);

	return rect;
}


/*
*--------------------------------------------------------------------------------
*  ������: Cut
*  ����  : ���и��������е�ͼ�񣬱��浽��������
*  ����ֵ: CDib*	-   ����һ��DIBͼ���ָ��
*  �㷨  : ���д����е�DIBͼ��Ȼ�󷵻�
*  ��������: ���ٸ�������
*--------------------------------------------------------------------------------
*/
CDib* CFloatDibWnd::Cut()
{
	CDib* pRet = m_pDib->Clone();
	delete this;
	return pRet;
}


/*
*--------------------------------------------------------------------------------
*  ������: Copy
*  ����  : ���Ƹ��������е�ͼ�񣬱��浽��������
*  ����ֵ: CDib*	-   ����һ��DIBͼ���ָ��
*  �㷨  : ���ƴ����е�DIBͼ��Ȼ�󷵻�
*  ��������: �������ٸ�������
*--------------------------------------------------------------------------------
*/
CDib* CFloatDibWnd::Copy()
{
	return m_pDib->Clone();	
}


/*
*--------------------------------------------------------------------------------
*  ������	: RotateAngle
*  ����		: ��ת��������
*  ����		: double angle	-	��ת�ĽǶ�
*--------------------------------------------------------------------------------
*/
BOOL CFloatDibWnd::RotateAngle(double angle)
{
	// ��Ϊ�Ƕ�Դͼ�������ת����������Ҫ����һ����ת�Ƕ���˴���ת�Ƕȵ���
	m_dblPreRotateAngle += angle;
	if (m_dblPreRotateAngle > 360)
		m_dblPreRotateAngle -= 360;
	angle = m_dblPreRotateAngle;


	//��pDib����ʵ���Ͼ��Ƕ�m_pDib����
	HBITMAP *m_hBitmap ;
	CDib * pDib; 
	pDib = m_pSrcDib->Clone();
		
	CPoint cirpoint;
	CRect rect;
	GetClientRect(&rect);
	
	
	//ʹԴDIB���ųɵ�ǰ��������С
	pDib->ChangeImageSize(rect.Width(), rect.Height()); 
	m_pDib->ChangeImageSize(rect.Width(), rect.Height()); 
	
	//�õ�ͼ�ξ����������ĵ�����ֵ
	cirpoint.x = rect.Width()/2;
	cirpoint.y = rect.Height()/2; 
	
	
	CClientDC dc(this);
	ASSERT_VALID(&dc);	
	   
	//��������һ��Ҫ������Դ�ڴ��豸�����ģ���ͬĿ���ڴ�����������һ��
    BITMAP  srcbm;
	HBITMAP * hBitmap;
	CDC  srcDC; 
	CBitmap pBitmap;
	   
	// ����Դ�ڴ��豸�龳����Ϊ����ʧ������ѡ�������ԴDIB��
	
	srcDC.CreateCompatibleDC(NULL);  
	hBitmap=(HBITMAP *)pDib->GetBitmap()->GetSafeHandle(); 
	srcDC.SetBkMode(TRANSPARENT); 
	   
	// ��λͼѡ��Դ�ڴ��豸�龳����	   
	srcDC.SelectObject(hBitmap);
	GetObject(hBitmap, sizeof(srcbm),&srcbm);
	   
	//Ϊʹ��ת��Դ��Ŀ���豸������һ�£�����ʹĿ��DIBʹ��m_pDib
	   
	CDC *  MemDC = m_pDib->BeginPaint(&dc);
	MemDC->SetBkMode(TRANSPARENT); 
	   
	int i,j;
	BITMAP m_Bm ;
	   
	m_hBitmap = (HBITMAP *)m_pDib->GetBitmap()->GetSafeHandle();  
	   
	// ��Ŀ��λͼѡ���ڴ��豸�龳����(��ʱԴ��Ŀ��λͼ��������һ��)
	MemDC->SelectObject(m_hBitmap);
	   
	GetObject(m_hBitmap, sizeof(m_Bm),&m_Bm);
	   
	//��Ŀ���ڴ��豸�����ļ�ȫ�����Ϊ�ۺ�ɫ
	MemDC->FillSolidRect(CRect(0, 0, m_pDib->GetWidth(), m_pDib->GetHeight()),g_stuPaintSet.tranCol);
	   
	CPoint point1, point2;
	   
	point1.x = m_pDib->GetWidth()/ 2;
	point1.y = m_pDib->GetHeight()/ 2; 
	   
	//��ʼ���ڴ�DC������ת����
	   
	for (i = (int) -0.4 * m_Bm.bmWidth; i < (int) 1.4 * m_Bm.bmWidth; i++) 
		for(j = (int) -0.4 * m_Bm.bmHeight; j < (int) 1.4 * m_Bm.bmHeight; j++)
		{
			point2.x = i;
			point2.y = j;
			point2 = CountPoint(point1, point2, angle);
			if(srcDC.GetPixel(point2) != g_stuPaintSet.tranCol)
				MemDC->StretchBlt(
				cirpoint.x + i-point1.x, cirpoint.y + j-point1.y, 
				1, 1,
				&srcDC,
				point2.x, point2.y,
				1,1,
				SRCCOPY
				);
		}		
	m_pDib->EndPaint(); 

	if (pDib)
		delete pDib;
	// ���Ŵ��ڣ�������ת�����ͼ���С��ƥ��
/*	int nWidth, nHeight, left, top;
	nWidth = m_pDib->GetWidth();
	nHeight = m_pDib->GetHeight();
	CPoint ptCenter = RectToParentClient().CenterPoint();
	left = ptCenter.x - nWidth / 2;
	top = ptCenter.y - nHeight / 2;

	::MoveWindow(GetSafeHwnd(), left, top, nWidth, nHeight, TRUE);
*/	
		
	return TRUE;  
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :CountPoint
*  ��������     :����һ����pointSide��������ĵ�pointCenter��תangle�ǶȺ�ĵ������ֵ
*  �����������	:
*  CPoint pointCenter����������ĵ�����ֵ
*  CPoint pointSide��  Ҫ����ĵ������ֵ
*  angle��             Ҫ��ת�ĽǶ�   
*  ���ر���˵�� :�������ĵ������ֵ
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
CPoint CFloatDibWnd::CountPoint(CPoint pointCenter, CPoint pointSide, double angle)
{
	const double PAI = 3.1415926;
	double dR, dTemp;
	double dAngle;
	int iQuadrant;
	CPoint point;

	//�����ĵ���߿���غ��򷵻�������
	if(pointCenter == pointSide)
		return pointCenter;

	//�Ե� pointCenter Ϊ���Ĺ���һ������ϵ,����ϵ���ľ��Ƕ��������	
	pointSide.x = pointSide.x -pointCenter.x;
	pointSide.y = pointCenter.y - pointSide.y;
	//����� pointSide �� pointCenter �����ɵ�ֱ�߽Ƕ�
	dR = sqrt(pow(pointSide.x, 2) + pow(pointSide.y, 2));
	dAngle = atan((double) pointSide.y / pointSide.x);
	if(pointSide.x >= 0 && pointSide.y >= 0)  iQuadrant = 1;
	if(pointSide.x < 0 && pointSide.y > 0)  iQuadrant = 2;
	if(pointSide.x <= 0 && pointSide.y <= 0)  iQuadrant = 3;
	if(pointSide.x > 0 && pointSide.y < 0)  iQuadrant = 4;
	if(iQuadrant == 2 || iQuadrant == 3)  dAngle = dAngle + PAI;
	if(iQuadrant == 3 && pointSide.x == 0) dAngle = dAngle + PAI;
	if(iQuadrant == 4) 	dAngle = dAngle + 2 * PAI;
	dAngle = dAngle + angle * PAI / 180;
	if(dAngle > 2 * PAI) dAngle = dAngle - 2 * PAI;

    //ȡ����ת PAI / numberSide ���Ⱥ���Ǹ��������
	dTemp = (double)pointCenter.x + (double)(cos(dAngle) * dR);
	point.x = (long)(dTemp + 0.5);
	dTemp = (double)pointCenter.y - (double)(sin(dAngle) * dR);
	point.y = (long)(dTemp + 0.5);
    return point;  

}


/*
*--------------------------------------------------------------------------------
*  ������	: IsCartoonWnd
*  ����		: �ж�һ�����������Ƿ�ͨ��ͼ
*  ����ֵ	: BOOL	-	�ǿ�ͨ��ͼ���ڷ��� TRUE, ���򷵻� FALSE
*--------------------------------------------------------------------------------
*/
BOOL CFloatDibWnd::IsCartoonWnd()
{
	return m_bCartoonWnd;
}


/*
*--------------------------------------------------------------------------------
*  ������	: SetCreateBtn
*  ����		: ���ô�����������ʱ�Ƿ񴴽��ĸ���Ŧ
*  ����ֵ	: 
*--------------------------------------------------------------------------------
*/
void CFloatDibWnd::SetCreateBtn(BOOL bCreateBtn)
{ 
	if(!bCreateBtn &&  g_createBtn)
	{
      //�������Ѿ���ʾ�˵��ĸ���Ŧ
     	m_btnRotate.ShowWindow(SW_HIDE);    
		m_btnVerMirror.ShowWindow(SW_HIDE); 
		m_btnHorMirror.ShowWindow(SW_HIDE); 
		m_btnResize.ShowWindow(SW_HIDE);   
        SendMessage(WM_SIZE,0,0);
	}
	else if(bCreateBtn &&  !g_createBtn)
	{
       //����ʾ�Ѿ������˵��ĸ���Ŧ
     	m_btnRotate.ShowWindow(SW_SHOW);    
		m_btnVerMirror.ShowWindow(SW_SHOW);
		m_btnHorMirror.ShowWindow(SW_SHOW); 
		m_btnResize.ShowWindow(SW_SHOW);   
        SendMessage(WM_SIZE,0,0);
	}
   g_createBtn = bCreateBtn;
    Invalidate(); 

}


//�����Ƿ��б�Ҫ��ʾ��Ŧ(��ͼ��̫Сʱ)
void CFloatDibWnd::CheckShowBtn()
{
    if(m_rcWndRect.Width() <= MINSIZE || m_rcWndRect.Height() <= MINSIZE)
		g_createBtn = FALSE;
}
