/**
*   PenNeb.cpp
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   ������ֱʼ�ĳ�����࣬��ȡȡ�����ӿ�
*======================================================
*   �汾
*   Revision 1.0	2002/11/12     ʵ�� CPenNeb ��
*/

#include "stdafx.h"
#include "..\Include\PenNeb.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


// ���� AlphaBlend �е�Alpha��ϳ���
#define AC_SRC_ALPHA	0x01

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*
*--------------------------------------------------------------------------------
*  ����: ���캯��
*  ����: HDC hDC  -	�ñʼ�滭���豸��������
*		 COLORREF crColor - �ʼ����ɫ
*		 BOOL	bAlpha - �ʼ��Ƿ�ʹ�� Alpha ���Ч��
*--------------------------------------------------------------------------------
*/
CPenNeb::CPenNeb(HDC hDC, COLORREF crColor, BOOL bAlpha)
{
	m_hDC = hDC;
	m_crPenNeb = crColor;
	m_bAlpha = bAlpha;
	m_hMemDC = NULL;
}

CPenNeb::~CPenNeb()
{
	if (m_bAlpha)
		Release();
}


/*
*--------------------------------------------------------------------------------
*  ������: InitPenNeb
*  ����  : ��ʼ���ʼ����
*  �㷨  : Ϊ���� Alpha �ʶ��裬��ΪҪ�õ����⺯�����ʲ����ù��캯�����
*--------------------------------------------------------------------------------
*/
void CPenNeb::InitPenNeb()
{
	if (m_bAlpha)
		CreateAlphaPen();
}


/*
*--------------------------------------------------------------------------------
*  ������: Apply
*  ����	 : ��ָ����������Ե�ǰ��Ч����
*  ����  : CPoint& ptPoint	-	ָ���������
*  �㷨  : ��Ч����ͨЧ���� Alpha �����Ч
*--------------------------------------------------------------------------------
*/
void CPenNeb::Apply(const CPoint &ptPoint) const
{
	if (m_bAlpha)
	{
		// Alpha �����Ч
		AlphaApply(ptPoint);
	}
	else
	{
		// Ϊ��ʧ�棬С��2�ıʿ�ֱ�ӻ����ص㣬��Ϊһ���ش�
		if (m_PenNebSize.cx <= 2 || m_PenNebSize.cy <= 2)
		{
			SetPixel(m_hDC, ptPoint.x, ptPoint.y, m_crPenNeb);
		}
		else
			NormalApply(ptPoint);
	}
}


/*
*--------------------------------------------------------------------------------
*  ������: NormalApply
*  ����	 : ��ָ�������������ͨ��Ч����
*  ����  : CPoint& ptPoint	-	ָ���������
*  �㷨  : ����ȱʡ��Ϊ���ڵ����Ե�ǰ��ɫ�����ʿ��С����Բ
*--------------------------------------------------------------------------------
*/
void CPenNeb::NormalApply(const CPoint &ptPoint) const
{
	HBRUSH hBrush = CreateSolidBrush(m_crPenNeb);
	HBRUSH hOldBrush = (HBRUSH) SelectObject(m_hDC, hBrush);
	HPEN hOldPen = (HPEN) SelectObject(m_hDC, GetStockObject(NULL_PEN));

	{
		int nX, nY;
		nX = m_PenNebSize.cx / 2;
		nY = m_PenNebSize.cy / 2;
		if (m_PenNebSize.cx == 3)
		{
			nX = 2;
		}
		if (m_PenNebSize.cy == 3)
		{
			nY = 2;
		}
		Ellipse(m_hDC, 
			ptPoint.x - nX, 
			ptPoint.y - nY, 
			ptPoint.x + nX, 
			ptPoint.y + nY);
	}

	SelectObject(m_hDC, hOldPen);
	SelectObject(m_hDC, hOldBrush);
	DeleteObject(hOldPen);
	DeleteObject(hOldBrush);
	DeleteObject(hBrush);
}


/*
*--------------------------------------------------------------------------------
*  ������: AlphaApply
*  ����	 : ��ָ���������豸���� Alpha ��Ч���
*  ����	 : CPoint& ptPoint	-	ָ���������
*  �㷨	 : ���� Alpha ��Ϻ�����ָ����������
*  ǰ������: �Ѵ����ʼ�� 32 λ DIB ͼ�񣬼�Ҫ�ȵ��� InitPen ����
*--------------------------------------------------------------------------------
*/
void CPenNeb::AlphaApply(const CPoint &ptPoint) const
{
	BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

	AlphaBlend( m_hDC, 
				ptPoint.x - m_PenNebSize.cx / 2, 
				ptPoint.y - m_PenNebSize.cy / 2, 
				m_PenNebSize.cx,
				m_PenNebSize.cy,
				m_hMemDC, 
				0, 
				0, 
				m_PenNebSize.cx, 
				m_PenNebSize.cy,
				blend);
}


/*
*--------------------------------------------------------------------------------
*  ������: CreateAlphaPen
*  ����	 : �������� Alpha Ч���ıʼ���״DIBλͼ
*  �㷨  : ����һ��ָ����С����ɫ�ıʼ���״�� DIB ͼ�񣬲�����͸����
*  ˵��  : ������ Template Method ģʽ
*  ǰ������: �������˱ʵ� ��С��ɫ���ʼ���״
*  ��������: ����һ������Ҫ�ıʣ�������ǰ�ı�ɾ��������Ա���� m_hPenBrush ��Ϊ������ DIB ͼ��ľ��
*--------------------------------------------------------------------------------
*/
void CPenNeb::CreateAlphaPen()
{
	Release();
	
	BYTE * pBits;
	BITMAPINFO Bmi = { { sizeof(BITMAPINFOHEADER), 
						m_PenNebSize.cx, m_PenNebSize.cy,
						1, 32, BI_RGB } };

	// �����ʵ� DIB ͼ��
	m_hPenBrush = CreateDIBSection(m_hDC, &Bmi, 
								DIB_RGB_COLORS,
								(void **) &pBits, 
								NULL, NULL);

	m_hMemDC = CreateCompatibleDC(NULL);
	m_hOldBrush = (HBITMAP) SelectObject(m_hMemDC, m_hPenBrush);
	

	// ���Ѵ����� DIB ͼ���������ʼ���״��ͼ��
	{
	PatBlt(m_hMemDC, 0, 0, m_PenNebSize.cx, m_PenNebSize.cy, WHITENESS);

	HBRUSH hBrush = CreateSolidBrush(m_crPenNeb);
	HPEN hPen = CreatePen(1, 1, m_crPenNeb);
	HBRUSH hOldBrush = (HBRUSH) SelectObject(m_hMemDC, hBrush);
	HPEN hOldPen = (HPEN) SelectObject(m_hMemDC, GetStockObject(NULL_PEN));

	// �����ʼ�ͼ�񣬵�������������غ���
	CreatePenNeb();

	SelectObject(m_hMemDC, hOldPen);
	SelectObject(m_hMemDC, hOldBrush);
	DeleteObject(hPen);
	DeleteObject(hOldPen);
	DeleteObject(hOldBrush);
	DeleteObject(hBrush);
	}

	// ���ñʼ�ͼ��ÿ�����ص�� Alpha ֵ���麯��
	SetAlpha(pBits);
}


/*
*--------------------------------------------------------------------------------
*  ������: Release
*  ����	 : �ͷű���ռ�õ���Դ�����³�ʼ����Ա����
*  ��������: ɾ���Ѵ����ıʣ��ͷŸ�����Դ
*--------------------------------------------------------------------------------
*/
void CPenNeb::Release()
{
	// δ�������ʼ�
	if (m_hMemDC == NULL)
		return;

	SelectObject(m_hMemDC, m_hOldBrush);
	DeleteObject(m_hOldBrush);
	DeleteObject(m_hMemDC);
	DeleteObject(m_hPenBrush);
	
	m_hOldBrush = NULL;
	m_hMemDC = NULL;
	m_hPenBrush = NULL;
}


/*
*--------------------------------------------------------------------------------
*  ������: CreatePenNeb
*  ����	 : ������ʱ�ڱʵ�λͼ�ϻ����ʼ���״
*  ��������: �����ȱʡ��Ϊ�ǻ���һ����Բ
*--------------------------------------------------------------------------------
*/
void CPenNeb::CreatePenNeb()
{
	Ellipse(m_hMemDC, 0, 0, m_PenNebSize.cx + 1, m_PenNebSize.cy + 1);
}


/*
*--------------------------------------------------------------------------------
*  ������: SetColor
*  ����	 : ���ñʼ����ɫ
*  ����  : COLORREF crColor	-  �ʼ���ɫ
*  ��������: ���ñ�ɫ������� Alpha �������´����ʼ�ͼ��
*--------------------------------------------------------------------------------
*/
void CPenNeb::SetColor(COLORREF crColor)
{
	m_crPenNeb = crColor;

	if (m_bAlpha)
		CreateAlphaPen();
}



//-----------------------------------------------------------------------------



/*
*--------------------------------------------------------------------------------
*  ������: DrawRotateEllipse
*  ����	 : ����һ����תָ���Ƕȵ���Բ
*  ����  : HDC hDC			- �豸������
*			CRect& rect		- ��Բ�������
*			double radians	- ��ת�ĽǶ�
*  �㷨  : ͨ����������������ģ�⻭��Բ���ȼ�������� Bezier ���ߵ�
*		13�����Ƶ㣬�ٽ���Щ���Ƶ���תָ���Ƕȣ����������ߣ����
*		������Բ�ڲ�����
*--------------------------------------------------------------------------------
*/
void CPenNeb::DrawRotateEllipse(HDC hDC, const CRect& rect, double radians) const
{
	CPoint pt[13] ;		
	
	// �������Բ�ϵĿ��Ƶ�����
	EllipseToBezier(rect, pt);

	// ˳ʱ����ת 45 ��
	RotateEllipse(radians, rect.CenterPoint(), pt, 13);
	
	BeginPath(hDC);
	PolyBezier(hDC, pt, 13);
	EndPath(hDC);
	FillPath(hDC);
}


/*
*--------------------------------------------------------------------------------
*  ������: EllipseToBezier
*  ����	 : �Ӹ������εõ���Բת���ɱ������ߺ�Ŀ��Ƶ�����
*  ����  : CRect & rect		- ��Բ�������
*		   CPoint * cCtlPt	- ��ת����Ŀ��Ƶ�����ָ��	
*--------------------------------------------------------------------------------
*/
void CPenNeb::EllipseToBezier(const CRect & rect, CPoint * cCtlPt) const
{
	// MAGICAL CONSTANT to map ellipse to beziers
    //  			2/3*(sqrt(2)-1) 
    const double EToBConst = 0.2761423749154; 
	
    CSize offset((int)(rect.Width() * EToBConst), (int)(rect.Height() * EToBConst));
	//  Use the following line instead for mapping systems where +ve Y is upwards
	//  CSize offset((int)(r.Width() * EToBConst), -(int)(r.Height() * EToBConst));
	
    CPoint centre((rect.left + rect.right) / 2, (rect.top + rect.bottom) / 2);
	
    cCtlPt[0].x  = rect.left;                 //------------------------/
	cCtlPt[1].x  = rect.left;                 //                        /
	cCtlPt[11].x = rect.left;                 //        2___3___4       /
	cCtlPt[12].x = rect.left;         
											  //     1             5    /
    cCtlPt[5].x  = rect.right;                //     |             |    /
	cCtlPt[6].x  = rect.right;                //     |             |    /
	cCtlPt[7].x  = rect.right;                //     0,12          6    /

    cCtlPt[2].x  = centre.x - offset.cx;      //     |             |    /
	cCtlPt[10].x = centre.x - offset.cx;      //     |             |    /

    cCtlPt[4].x  = centre.x + offset.cx;      //    11             7    /
	cCtlPt[8].x  = centre.x + offset.cx;      //       10___9___8       /

    cCtlPt[3].x  = centre.x;                  //                        /
	cCtlPt[9].x  = centre.x;                  //------------------------*
	
    cCtlPt[2].y  = rect.top;
	cCtlPt[3].y  = rect.top;
	cCtlPt[4].y  = rect.top;

    cCtlPt[8].y  = rect.bottom;
	cCtlPt[9].y  = rect.bottom;
	cCtlPt[10].y = rect.bottom;

    cCtlPt[7].y  = centre.y + offset.cy;
	cCtlPt[11].y = centre.y + offset.cy;

    cCtlPt[1].y  = centre.y - offset.cy;
	cCtlPt[5].y  = centre.y - offset.cy;

    cCtlPt[0].y  = centre.y;
	cCtlPt[12].y = centre.y;
	cCtlPt[6].y  = centre.y;
}


/*
*--------------------------------------------------------------------------------
*  ������: RotateEllipse
*  ����	 : ����һ����תָ���Ƕȵ���Բ
*  ����  : double radians	- ��Բ����ת�Ƕ�
*		   CPoint & c		- ��Բ�����ĵ�
*		   CPoint *vCtlPt	- ��Բ�ı��ȿ��Ƶ�����
*		   unsigned int Cnt	- ���Ƶ����
*--------------------------------------------------------------------------------
*/
void CPenNeb::RotateEllipse(double radians, const CPoint &c, CPoint *vCtlPt, unsigned int Cnt) const
{
    for (int i = Cnt-1; i>=0; --i)
    {
		RotatePoint(radians, c, vCtlPt[i]);
	}
}


/*
*--------------------------------------------------------------------------------
*  ������: RotatePoint
*  ����	 : ����һ���������ĵ���תָ���ǶȺ������
*  ����  : double radians	- ��ת�Ƕȣ���λΪ�Ƕ�
*		   CPoint & c		- ��ת���ĵ�
*		   CPoint & point	- ��ת�ĵ�
*--------------------------------------------------------------------------------
*/
void CPenNeb::RotatePoint(double radians, const CPoint& c, CPoint &point) const
{
    double sinAng           = sin(radians);
    double cosAng           = cos(radians);
	double xOffset, yOffset, x, y;
	xOffset = c.x - c.x * cosAng - c.y * sinAng;
	yOffset = c.y + c.x * sinAng - c.y * cosAng;


	x = point.x * cosAng + point.y * sinAng + xOffset;
	y = -point.x * sinAng + point.y * cosAng + yOffset;

	point.x = int (x + 0.5);
	point.y = int (y + 0.5);
}
