/**
*   VEllipsePenneb.cpp
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   ʵ�ִ�ֱ��Բ�αʼ⹤��
*======================================================
*   �汾
*   Revision 1.0	2002/11/14     ʵ�� CVEllipsePenNeb ��
*/
#include "stdafx.h"
#include "..\Include\VEllipsePenNeb.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVEllipsePenNeb::CVEllipsePenNeb(HDC hDC, int nSize, COLORREF crColor, BOOL bAlpha) 
		: CPenNeb(hDC, crColor, bAlpha)
{
	m_PenNebSize.cx = nSize / 2;
	m_PenNebSize.cy = nSize;
}

CVEllipsePenNeb::~CVEllipsePenNeb()
{

}


/*
*--------------------------------------------------------------------------------
*  ������: SetAlpha
*  ����	 : ���ñʼ�ͼ����ÿ�����ص��Alphaֵ
*  ����  : BYTE* pPixel - �ʼ�DIBͼ�������ָ��
*  �㷨  : ��ֱ��Բ�ʼ⣬��͸�����м�Ϊ���150�������ܹ��ɵ���ȫ͸��
*  ˵��  : ���� Alpha ���ÿ�����ص����Ϊ 32 λ
*--------------------------------------------------------------------------------
*/
void CVEllipsePenNeb::SetAlpha(BYTE *pPixel)
{
	int nWidth = m_PenNebSize.cx ;
	int nHeight = m_PenNebSize.cy ;

	for (int y = 0; y < nHeight; y++)
		for (int x = 0; x < nWidth; x++, pPixel += 4)
		{
			BYTE alpha = 255;
			
			// �������ص�����ĵ�ľ��룬��Ϊ�������			
			int dis;
			dis = (int) ( sqrt( (float)(x*2-nWidth) * (x*2-nWidth)
				+ (y-nHeight/2) * (y-nHeight/2)) 
				* 150 / (max(nWidth, nHeight)/2) );
			
			alpha = (BYTE) max(min(150 - dis, 150), 0);


			pPixel[0] = pPixel[0] * alpha / 255;
			pPixel[1] = pPixel[1] * alpha / 255;
			pPixel[2] = pPixel[2] * alpha / 255;
			pPixel[3] = alpha;
		}
}


/*
*--------------------------------------------------------------------------------
*  ������	: SetSize
*  ����		: ���ñʼ�Ĵ�С
*  ����		: int nSize	-	�ʼ��С
*  �㷨		: ��ֱ��Բ�ʼ�ĸ߶�Ϊ��ȵ�����
*--------------------------------------------------------------------------------
*/
void CVEllipsePenNeb::SetSize(int nSize)
{
	m_PenNebSize.cx = nSize / 2;
	m_PenNebSize.cy = nSize;

	if (m_bAlpha)
		CreateAlphaPen();
}