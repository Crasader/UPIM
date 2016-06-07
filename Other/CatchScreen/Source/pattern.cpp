/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��pattern.cpp
* �汾��  ��V1.0
* ��Ŀ���ƣ�CPH
* ��Ȩ������Copyright 2002-2003 . All Rights Reserved.
* ģ�����������ͨ����ͼ���ͷ�ļ�,ʵ�ֽ������ͼƬ������ǰ�����ϣ�
*                ������ʵ�����š���ת������Ȳ���   
*======================================================
* �汾�����¼:
*      v1.0  2002-11-7   15:30  
*
* 
*/

/////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "..\Paint\PaintDlg.h"
#include "..\\INCLUDE\\pattern.h"
#include "..\\INCLUDE\\DIBitmap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cpattern

Cpattern::Cpattern()
{
	//ͼƬ�Զ��ƴ�С��ʾ�ڻ�������
     m_nType=BITMAP_CUSTOMIZE;
}

Cpattern::~Cpattern()
{
}


BEGIN_MESSAGE_MAP(Cpattern, CWnd)
	//{{AFX_MSG_MAP(Cpattern)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Cpattern message handlers


//��ʼ��DIB����,�ɹ�����TRUE��ʧ�ܷ���FALSE
BOOL Cpattern::InitDib()
{
	return TRUE;
}

//���µ�ǰDIB����,�ɹ�����TRUE��ʧ�ܷ���FALSE
BOOL Cpattern::UpDataDib()
{
	return TRUE;

}

//��ʾ��ǰDIB����
Cpattern::ShowDib()
{
}

//���ص�ǰDIB����
Cpattern::HideDib()
{
}

//�ı�״̬
Cpattern::ChangeDibSize()
{
}

//�ı��С(����)
Cpattern::ChangeDibZoom()
{
}

//�õ�״̬,����ֵ��Ӧ����1-10,�ֱ��ʾ��ͬ��λͼ״̬
INT Cpattern::GetStatus()
{
	return 0;
}


//�õ���С
CRect Cpattern::GetDibSize()
{
   return CRect(0,0,0,0);
}

//�õ�����ҳ��ָ��
HANDLE Cpattern::GetDibPage()
{
	HBITMAP bitmap=NULL;
	return   bitmap;
}


//�ı����ҳ��ָ��,���ظı���ҳ����
HANDLE Cpattern::ChangeDibPage()
{
	HBITMAP bitmap=NULL;
	return   bitmap;
}



/*
*--------------------------------------------------------------------------------
*  ��Ա������   :Create
*  ��������     :������ͼƬ����ʱ���޸Ĵ��ڵ�����
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*--------------------------------------------------------------------------------
*/
BOOL Cpattern::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnCreate
*  ��������     :��ʼ�����Ա������ֵ
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*--------------------------------------------------------------------------------
*/
int Cpattern::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnLButtonDown
*  ��������     :������ͼ�������Ĳ���������Ϊ�ƶ���꣬����ʼ��¼��ʼ��λ��
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*--------------------------------------------------------------------------------
*/
void Cpattern::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnLButtonDown(nFlags, point);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnLButtonUp
*  ��������     :������ͼ����Up�����Ĳ����������ƶ��зţ���¼�����λ��
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*--------------------------------------------------------------------------------
*/
void Cpattern::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnLButtonUp(nFlags, point);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnMouseMove
*  ��������     :��꾭��ͼ�������Ĳ�����������ڴ����
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵����������ڴ���߽�ʱ�����ù����ʽΪ�仯�ߴ��С�������λ�ڰ�Ŧ��ʱ������Ϊ��״
*            ����
*--------------------------------------------------------------------------------
*/
void Cpattern::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnMouseMove(nFlags, point);
}
