/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��dibpal.cpp
* �汾��  ��V1.0
* ��Ŀ���ƣ�CPH
* ��Ȩ������Copyright 2002-2003. All Rights Reserved.
* ģ���������
*======================================================
* �汾�����¼:
*      v1.0  2002-10-30   20:30    ����һЩ�ο�������ɱ���
*
* 
*/

/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\Include\DIBitmap.h"
#include "..\Include\dibpal.h"

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :CBmpPalette
*  ��������     :�����ɫ�Ի���ĵ�ɫ��
*  �����������	:
*   CDIBitmap* pBmp��DIBλͼָ��
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     : 
*--------------------------------------------------------------------------------
*/
CBmpPalette::CBmpPalette( CDIBitmap* pBmp )
{
    ASSERT( pBmp );
    int cPaletteEntries = pBmp->GetPalEntries();
    int cPalette = sizeof(LOGPALETTE) +
                   sizeof(PALETTEENTRY) * cPaletteEntries;

    // ��Ϊ���LOGPALETTE �ṹ��structure�ǿ��Ը��ĵ�,���
    // ��̬������, ����ʹ��һ����ջ

    LOGPALETTE* pPal = (LOGPALETTE*)new BYTE[cPalette];
    RGBQUAD*    pColorTab = pBmp->GetColorTablePtr();
    pPal->palVersion = 0x300;
    pPal->palNumEntries = cPaletteEntries;
    // ѭ��ͨ����ɫ��,����ÿ����ɫ���߼���ɫ���� 

    for( int ndx = 0; ndx < cPaletteEntries; ndx++ )
    {
        pPal->palPalEntry[ndx].peRed   = pColorTab[ndx].rgbRed;
        pPal->palPalEntry[ndx].peGreen = pColorTab[ndx].rgbGreen;
        pPal->palPalEntry[ndx].peBlue  = pColorTab[ndx].rgbBlue;
        pPal->palPalEntry[ndx].peFlags = NULL;
    }
    VERIFY( CreatePalette( pPal ) );
    delete [] (BYTE*)pPal;
}
