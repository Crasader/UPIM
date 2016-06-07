/**
*   HEllipsePenneb.cpp		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   ʵ��ˮƽ��Բ�αʼ⹤��
*======================================================
*   �汾
*   Revision 1.0	2002/11/14     	 ʵ�� CHEllipsePenNeb ��
*/
#include "stdafx.h"
#include "..\Include\HEllipsePenNeb.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHEllipsePenNeb::CHEllipsePenNeb(HDC hDC, int nSize, COLORREF crColor, BOOL bAlpha) 
		: CPenNeb(hDC, crColor, bAlpha)
{
	m_PenNebSize.cx = nSize;
	m_PenNebSize.cy = nSize / 2;
}

CHEllipsePenNeb::~CHEllipsePenNeb()
{

}


/*
*--------------------------------------------------------------------------------
*  ������: SetAlpha
*  ����	 : ���ñʼ�ͼ����ÿ�����ص��Alphaֵ
*  ����  : BYTE* pPixel - �ʼ�DIBͼ�������ָ��
*  �㷨  : ˮƽ��Բ�ʼ⣬��͸�����м�Ϊ���150�������ܹ��ɵ���ȫ͸��
*  ˵��  : ���� Alpha ���ÿ�����ص����Ϊ 32 λ
*--------------------------------------------------------------------------------
*/
void CHEllipsePenNeb::SetAlpha(BYTE *pPixel)
{
	int nWidth = m_PenNebSize.cx ;
	int nHeight = m_PenNebSize.cy ;
	
	for (int y = 0; y < nHeight; y++)
		for (int x = 0; x < nWidth; x++, pPixel += 4)
		{
			BYTE alpha = 255;

			// �������ص�����ĵ�ľ��룬��Ϊ�ߵ�����
			int dis;			
			dis = (int) ( sqrt( (float)(x-nWidth/2) * (x-nWidth/2)
				+ (y*2-nHeight) * (y*2-nHeight)) 
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
*  �㷨		: ˮƽ��Բ�ʼ�Ŀ��Ϊ�߶ȵ�����
*--------------------------------------------------------------------------------
*/
void CHEllipsePenNeb::SetSize(int nSize)
{
	m_PenNebSize.cx = nSize;
	m_PenNebSize.cy = nSize / 2;

	if (m_bAlpha)
		CreateAlphaPen();
}

