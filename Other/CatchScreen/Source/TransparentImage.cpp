/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��TransparentImage.cpp
* �汾��  : V1.0
* ��Ŀ���ƣ�
* ��Ȩ������Copyright 2002-2003 . All Rights Reserved.
* ģ���������͸��ͼ����ģ���ļ�
*======================================================
* �汾�����¼:
*
*   
* 
*/

/////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "include\TransparentImage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__ ;
#endif


CTransparentImage::CTransparentImage()
{
   m_trancol = g_stuPaintSet.tranCol;  //Ĭ��͸��ɫΪ�ۺ�ɫ
}


CTransparentImage::~CTransparentImage()
{
}


BEGIN_MESSAGE_MAP( CTransparentImage, CStatic )

	//{{AFX_MSG_MAP( CTransparentImage )
	ON_WM_PAINT()
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

//���ػ�ͼ��
void CTransparentImage::OnPaint() 
{
	HBITMAP l_hbmpBitmap = GetBitmap() ;

	if( l_hbmpBitmap == NULL )
	{
		Default() ;

		return ;
	}

	CPaintDC l_PaintDC( this ) ;

	CRect l_rcClient ;

	GetClientRect( &l_rcClient ) ;

	CDC		 l_BufferDC ;
			 l_BufferDC.CreateCompatibleDC( &l_PaintDC ) ;
	CBitmap  l_BufferBitmap ;
			 l_BufferBitmap.CreateCompatibleBitmap( &l_PaintDC, l_rcClient.Width(), l_rcClient.Height() ) ;
	CBitmap* l_pOldBufferBitmap = l_BufferDC.SelectObject( &l_BufferBitmap ) ;
	CDC		 l_MaskDC ;
			 l_MaskDC.CreateCompatibleDC( &l_PaintDC ) ;
	CBitmap  l_MaskBitmap ;
			 l_MaskBitmap.CreateBitmap( l_rcClient.Width(), l_rcClient.Height(), 1, 1, NULL ) ;
	CBitmap* l_pOldMaskBitmap = l_MaskDC.SelectObject( &l_MaskBitmap ) ;

	#define ROP4_TRANSPARENTBLIT		0xCCAA0020
	#define SRCMASK						0x00220326

	//ʹ��͸��ɫ�������
	l_BufferDC.FillSolidRect( &l_rcClient, m_trancol) ;

	//ʹ���ڴ�λͼ������ͼ��
	CDC		 l_MemoryDC ;
			 l_MemoryDC.CreateCompatibleDC( &l_PaintDC ) ;
	CBitmap* l_pOldMemoryBitmap = l_MemoryDC.SelectObject( CBitmap::FromHandle( l_hbmpBitmap ) ) ;

	l_BufferDC.BitBlt( 0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_MemoryDC, 0, 0, SRCCOPY ) ;

	l_MemoryDC.SelectObject( l_pOldMemoryBitmap ) ;

	//��������ͼ
	COLORREF l_crOldBack = l_BufferDC.SetBkColor( m_trancol) ;

	l_MaskDC.BitBlt( 0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_BufferDC, 0, 0, SRCCOPY ) ;

	l_BufferDC.SetBkColor( l_crOldBack ) ;

	//����͸��ɫ
	if( ! l_PaintDC.MaskBlt( 0, 
							 0, 
					   		 l_rcClient.Width(),
					   		 l_rcClient.Height(),
					   		 &l_BufferDC,
					   		 0,
					   		 0,
					   		 l_MaskBitmap,
					   		 0,
					   		 0,
					   		 ROP4_TRANSPARENTBLIT ) )
	{
		CDC		 l_CopyDC ;
				 l_CopyDC.CreateCompatibleDC( &l_PaintDC ) ;
		CBitmap  l_CopyBitmap ;
				 l_CopyBitmap.CreateCompatibleBitmap( &l_PaintDC, l_rcClient.Width(), l_rcClient.Height() ) ;
		CBitmap* l_pOldCopyBitmap = l_CopyDC.SelectObject( &l_CopyBitmap ) ;

		l_CopyDC.BitBlt(   0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_PaintDC,  0, 0, SRCCOPY  ) ;
		l_CopyDC.BitBlt(   0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_MaskDC,   0, 0, SRCAND   ) ;
		l_BufferDC.BitBlt( 0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_MaskDC,   0, 0, SRCMASK  ) ;
		l_CopyDC.BitBlt(   0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_BufferDC, 0, 0, SRCPAINT ) ;
		l_PaintDC.BitBlt(  0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_CopyDC,   0, 0, SRCCOPY  ) ;

		l_CopyDC.SelectObject( l_pOldCopyBitmap ) ;
	}

	//�ͷ��ڴ����
	l_MaskDC.SelectObject( l_pOldMaskBitmap ) ;
	l_BufferDC.SelectObject( l_pOldBufferBitmap ) ;
}

//����ͼ��͸��ɫ
void CTransparentImage::SetTransCol(COLORREF transCol)
{
     m_trancol = transCol;
}

//���ص�ǰ���õ�ͼ��͸��ɫ
COLORREF CTransparentImage::GetTransCol()
{
	return m_trancol;
}
