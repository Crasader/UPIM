/**
*	File Name			:	AirPen.cpp
*	Version				:	1.0
*	Project Information	:	�滭��԰(1003-2002)
*	Copyright			:	Copyright 2002 . All Rights Reserved.
*	Brief Description   :	CAirPen��ĺ���ʵ��
*====================================================================================
*   �汾
*   Revision 1.0	2002/11/06		CAirPen��ĺ���ʵ��
*
*	Revision 2.0	2002/11/13	
*			�޸Ĺ��캯���������޸����õ����ھ������Ӧ����
*/

#include "stdafx.h"
#include "..\\include\\AirPen.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// ��ʼ����ǹ��ɫΪ��ɫ
COLORREF CAirPen::g_crPenColor = RGB(0, 0, 0);
// ��ʼ����ǹ�Ĵ�СΪ18������
int CAirPen::g_nPenSize = 18;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*
*--------------------------------------------------------------------------------
*  CAirPen
*  ���ܣ����캯��
*  ����
*		HWND hWnd - ��ͼ�����ھ��
*  ˵��
*		����ǹ�õ���ʱ������Ҫ���ھ����Ϊ����
*		�豸��������ɴ˴��ھ������		    
*--------------------------------------------------------------------------------
*/
CAirPen::CAirPen(HWND hWnd, int nSize, COLORREF crColor) : CAbstractPen(GetDC(hWnd), nSize, crColor)
{
	m_hWnd = hWnd;
	m_strPenName = _T("��ǹ");
	g_nPenSize = nSize;
	g_crPenColor = crColor;
//	m_hCursor = LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_AIRPEN));
    m_hCursor = AfxGetApp()->LoadCursor(IDC_AIRPEN);
}


CAirPen::~CAirPen()
{

}


/*
*--------------------------------------------------------------------------------
*  Member Name:					SetPenColor
*  Function Description:		������ǹ����ɫ
*  Parameter Specification:	
        COLORREF	crColor		-Ҫ�趨����ɫ
*  Return Specification:		�� 
*   Algorithm:					��		
*   Addtion:				    
        ǰ��������				��
		����������				��ǹ���趨Ϊָ����ɫ
*--------------------------------------------------------------------------------
*/

void CAirPen::SetPenColor(COLORREF crColor)
{
	g_crPenColor = crColor;
}

/*
*--------------------------------------------------------------------------------
*  Member Name:					SetPenStyle
*  Function Description:		�޹���
*  Parameter Specification:	
        PEN_STYLE   PenStyle	-������
*  Return Specification:		�� 
*   Algorithm:					��		
*   Addtion:				    
        ǰ��������				��
		����������				��
		������ǹ�ڹ̶�Բ�������в�����ɢ�ĵ㣬���Ըú�������Ϊ
*--------------------------------------------------------------------------------
*/

//DEL void CAirPen::SetPenStyle(PEN_STYLE PenStyle)
//DEL {
//DEL }

/*
*--------------------------------------------------------------------------------
*  Member Name:					SetPenSize
*  Function Description:		������ǹ��������Χ
*  Parameter Specification:	
          int  nSize			-��ǹ������Բ������İ뾶
*  Return Specification:		�� 
*   Algorithm:					��		
*   Addtion:				    
        ǰ��������				��ǹ�ѱ���ʼ��
		����������				��������Ϊָ����С��Բ��
*--------------------------------------------------------------------------------
*/

void CAirPen::SetPenSize(int nSize)
{
	CAirPen::g_nPenSize = nSize;
}

/*
*--------------------------------------------------------------------------------
*  Member Name:					BiginDraw
*  Function Description:		��ʼ���
*  Parameter Specification:	
        HDC hDC					-��ǰ��ͼ�����豸�����ľ�� 
		CPoint &ptPoint         -��ǰ�������λ�õ��߼�����
*  Return Specification:		�� 
*   Algorithm:					��		
*   Addtion:				    
        ǰ��������				��ͼ���ѱ���������ǹ���ѱ�����
		����������				����Ļָ��������ʾ��
*--------------------------------------------------------------------------------
*/
void CAirPen::BeginDraw(const CPoint &ptPoint)
{
	::SetTimer(m_hWnd, 1, 1, (TIMERPROC) & TimerProc);
}


/*
*--------------------------------------------------------------------------------
*  Member Name:					TimerProc
*  Function Description:		�ص����������Ļ���
*  Parameter Specification:	
        HWND     hWnd		    -���ڵľ�� 
		UINT     uMsg           -WM_TIMER��Ϣ
        UINT_PTR idEvent		-��ʱ����
		DWORD    dwTime			-��ǰϵͳʱ��
*  Return Specification:		�� 
*   Algorithm:					����㷨		
*   Addtion:				    
        ǰ��������				��ʱ���ɹ���ʼ��
		����������				��ÿ55����30�����������ƶ�������������
*--------------------------------------------------------------------------------
*/
VOID CALLBACK CAirPen::TimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, 
		                           DWORD dwTime)
{
	CPoint CurPoint;
	::GetCursorPos(&CurPoint);
	::ScreenToClient(hWnd, &CurPoint);
    
    int x, y, ratius = g_nPenSize;
	ratius = g_nPenSize;
	TRACE("size = %d\t", g_nPenSize);
	HDC hDC = ::GetDC(hWnd);

    for(int i = 0; i < 30; i++)
	{
		int irand = rand();
	    float Temp = (float)ratius * irand * 2 / RAND_MAX;
	    x = (int)(Temp - ratius +0.5);
	
		irand = rand();
        Temp = (float)ratius * irand * 2 / RAND_MAX;
	    y = (int)(Temp - ratius + 0.5);
	
    
        // �������Բ�������ڣ��򻭵�
	    if (((x * x) + (y * y)) < (ratius * ratius))
			::SetPixel(hDC, (CurPoint.x + x), (CurPoint.y + y), g_crPenColor);
	}
}


/*
*--------------------------------------------------------------------------------
*  Member Name:					DrawPoint
*  Function Description:		����Ϊ
*  Parameter Specification:	
        HDC hDC					-��ǰ��ͼ�����豸�����ľ�� 
		CPoint &ptPoint         -��ǰ�������λ�õ��߼�����
*  Return Specification:		�� 
*   Algorithm:					��		
*   Addtion:				    
        ǰ��������				���ʶ����ѱ���������ȷ��ʼ��
		����������				��
*--------------------------------------------------------------------------------
*/
void CAirPen::DrawPoint(const CPoint &ptPoint)
{
}


/*
*--------------------------------------------------------------------------------
*  Member Name:					EndDraw
*  Function Description:		�������
*  Parameter Specification:	
        HDC hDC					-��ǰ��ͼ�����豸�����ľ�� 
		CPoint &ptPoint         -��ǰ�������λ�õ��߼�����
*  Return Specification:		�� 
*   Algorithm:					��		
*   Addtion:				    
        ǰ��������				��ʱ���ѱ���������ʼ����
		����������				��ֹ��ʱ����ʱ
*--------------------------------------------------------------------------------
*/
void CAirPen::EndDraw(const CPoint &ptPoint)
{	
	::KillTimer(m_hWnd, 1);
}