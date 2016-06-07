/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��Dib.cpp 
* �汾��  ��V1.0
* ��Ŀ���ƣ�CPH
* ��Ȩ������Copyright 2002-2003 . All Rights Reserved.
* ģ���������DIBͼ�δ�����ģ���ļ�������DibAPI.CPP�еĺ�����
*======================================================
* �汾�����¼:
*      v1.0  2002-11-11   8:30  ��ΰ  
*
* 
*/

/////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windowsx.h>		

#include "..\Include\Dib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// WIDTHBYTES��ִ��DWORDɨ��������.  �������"bits"��ɨ����(biWidth * biBitCount)λ��
// ����귵�� DWORD������Щλ�����Ҫ��λ��
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4) 

IMPLEMENT_SERIAL(CDib, CObject, 0)

////////////////////////////////////////////////////////////////////////////

/*
*--------------------------------------------------------------------------------
*  CDib()
*  ���캯��
*  Parameter :  
*                 ��
*  Return value:
*                 ��
*====================================================
*  �汾�����¼
*  CPH 1.0 2002/11/13 ��ΰ ������ݵĳ�ʼ��
*
*/

CDib::CDib()
{
	m_hDib		= NULL;
	m_hBitmap   = NULL;
	m_pPalette  = NULL;
	m_pBitmap   = NULL;
	m_pMemDC	= NULL;
}  
         
/*
*--------------------------------------------------------------------------------
*  ~CDib()
*  ��������
*  Parameter :  
*                 ��
*  Return value:
*                 ��
*====================================================
*/
                                      
CDib::~CDib()
{
	Destroy();
	if (m_pBitmap != NULL)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
	}
	if (m_pPalette != NULL)
	{
		delete m_pPalette;
		m_pPalette = NULL;
	}
	if (m_pPalette != NULL)
	{
		delete m_pPalette;
		m_pPalette = NULL;
	}
	if (m_pBitmap != NULL)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
	}

}

void CDib::Destroy()
{
	if (m_hDib != NULL)
	{
		DestroyDIB(m_hDib);
		m_hDib = NULL;
	}
}

BOOL CDib::Create(DWORD dwWidth, DWORD dwHeight)
{
	HDIB hDib = CreateDefaultDIB(dwWidth, dwHeight);
	if (! hDib)
		return FALSE;

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

/*
*--------------------------------------------------------------------------------
*  Create()
*  ����CDib���� 
*  Parameter :  
*              [IN]    dwWidth
*                 ���
*              [IN]    dwHeight
*                 �߶�
*              [IN]    wBitCount
*                 ����
*  Return value:
*              ����TRUE��ʾ�����ɹ�������FALSEʧ��
*====================================================
*
*/

BOOL CDib::Create(DWORD dwWidth, DWORD dwHeight, WORD wBitCount)
{
	HDIB hDib = CreateDIB(dwWidth, dwHeight, wBitCount);
	if (! hDib)
		return FALSE;

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

/*
*--------------------------------------------------------------------------------
*  Create()
*  ����CDib���� 
*  Parameter :  
*              [IN]    lpDIB
*                 CDib�ֽ�ָ��
*  Return value:
*              ����TRUE��ʾ�����ɹ�������FALSEʧ��
*===================================================
*
*/

BOOL CDib::Create(LPBYTE lpDIB)
{
	if (lpDIB == NULL)
		return FALSE;
	
	DWORD dwSize = DIBlockSize(lpDIB);

    HDIB hDib  = GlobalAlloc(GHND, dwSize); 
    // ��DIB handle is valid 
    if (! hDib) 
        return FALSE; 
 
    LPBYTE lpbi  = (LPBYTE)GlobalLock(hDib); 
	if (! lpbi)
        return FALSE; 
		
	CopyMemory(lpbi, lpDIB, dwSize);
	GlobalUnlock(hDib);

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

/*
*--------------------------------------------------------------------------------
*  Create()
*  ����CDib���� 
*  Parameter :  
*              [IN]    lpDIB
*                 CDib�ֽ�ָ��
*              [IN]    wBitCount
*                 CDib����
*  Return value:
*              ����TRUE��ʾ�����ɹ�������FALSEʧ��
*====================================================
*
*/

BOOL CDib::Create(LPBYTE lpDIB,
				  WORD  wBitCount)		// bits/pixel 
{
	if (lpDIB == NULL)
		return FALSE;
	if (! Create(lpDIB))
		return FALSE;

	WORD wBits = ((LPBITMAPINFOHEADER)lpDIB)->biBitCount;
	if (wBitCount == wBits)
		return TRUE;

	HDIB hNewDib = ConvertDIBFormat(m_hDib, wBitCount, NULL); 
	if (! hNewDib)
		return FALSE;

	Destroy();
	m_hDib = hNewDib;
	return UpdateInternal();
}

/*
*--------------------------------------------------------------------------------
*  Create()
*  ����CDib���� ��DIB Ƭ��
*  Parameter :  
*              [IN]    hBitmap
*                 λͼ���
*  Return value:
*              ����TRUE��ʾ�����ɹ�������FALSEʧ��
*====================================================
*  �汾�����¼
*
*/

BOOL CDib::Create(HBITMAP hBitmap)		
{
	if (! hBitmap)
        return FALSE; 

	HDIB hDib = DIBSectionToDIB(hBitmap); 
    if (! hDib) 
        return FALSE; 

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

/*
*--------------------------------------------------------------------------------
*  Create()
*  ����CDib���� 
*  Parameter :  
*              [IN]    hBitmap
*                 λͼ���
*              [IN]    wBitCount
*                 CDib����λ��
*  Return value:
*              ����TRUE��ʾ�����ɹ�������FALSEʧ��
*====================================================
*
*/

BOOL CDib::Create(HBITMAP hBitmap,		
				  WORD  wBitCount)		
{
	HDIB hNewDib;

	if (! hBitmap)
        return FALSE; 

	HDIB hDib = DIBSectionToDIB(hBitmap); 
    if (! hDib) 
        return FALSE; 

	DIBSECTION ds;
	GetObject(hBitmap, sizeof(DIBSECTION), &ds);

	if (wBitCount == ds.dsBmih.biBitCount)
		hNewDib = hDib;
	else
	{
		hNewDib = ConvertDIBFormat(hDib, wBitCount, NULL); 
		// cleanup hDib
		GlobalFree(hDib);
	}
	if (! hNewDib)
		return FALSE;

	Destroy();
	m_hDib = hNewDib;
	return UpdateInternal();
}

/*
*--------------------------------------------------------------------------------
*  Create()
*  ����CDib���� 
*  Parameter :  
*              [IN]    hBitmap
*                 λͼ���
*              [IN]    hPalette
*                 ��ɫ����
*  Return value:
*               ����TRUE��ʾ�����ɹ�������FALSEʧ��
*====================================================
*  �汾�����¼
*
*
*/

BOOL CDib::Create(HBITMAP hBitmap,		
			      HPALETTE hPalette)	
{
	if (! hBitmap)
        return FALSE; 

	HDIB hDib = BitmapToDIB(hBitmap, hPalette); 
    if (! hDib) 
        return FALSE; 

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

/*
*--------------------------------------------------------------------------------
*  Create()
*  ����CDib���� 
*  Parameter :  
*              [IN]    hBitmap
*                 λͼ���
*              [IN]    hPalette
*                 ��ɫ����
*              [IN]    wBitCount
*                 CDib�������
*  Return value:
*              ����TRUE��ʾ�����ɹ�������FALSEʧ��
*====================================================
*
*/

BOOL CDib::Create(HBITMAP hBitmap,		
			      HPALETTE hPalette,	
				  WORD  wBitCount)		
{
	if (! hBitmap)
        return FALSE; 

	HDIB hDib = BitmapToDIB(hBitmap, hPalette, wBitCount); 
    if (! hDib) 
        return FALSE; 

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

/*
*--------------------------------------------------------------------------------
*  Create()
*  ����CDib���� 
*  Parameter :  
*              [IN]    rcScreen
*                 ���ο�
*  Return value:
*              ����TRUE��ʾ�����ɹ�������FALSEʧ��
*====================================================
*
*/

BOOL CDib::Create(CRect rcScreen)
{
	HDIB hDib = CopyScreenToDIB(rcScreen); 
    if (! hDib) 
        return FALSE; 

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

/*
*--------------------------------------------------------------------------------
*  Create()
*  ����CDib���� 
*  Parameter :  
*              [IN]    hWnd
*                 ���ھ��
*              [IN]    fPrintArea
*                 ��ӡ����
*  Return value:
*              ����TRUE��ʾ�����ɹ�������FALSEʧ��
*====================================================
*
*/

BOOL CDib::Create(HWND hWnd, WORD fPrintArea)
{
	HDIB hDib = CopyWindowToDIB(hWnd, fPrintArea); 
    if (! hDib) 
        return FALSE; 

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

/*
*--------------------------------------------------------------------------------
*  Create()
*  ����CDib���� 
*  Parameter :  
*              [IN]    hWnd
*                 ���ھ��
*              [IN]    rcClientArea
*                 �ͻ�����
*  Return value:
*               ����TRUE��ʾ�����ɹ�������FALSEʧ��
*====================================================
*
*/

BOOL CDib::Create(HWND hWnd, CRect rcClientArea)
{
	HDIB hDib = CopyClientRectToDIB(hWnd, rcClientArea); 
    if (! hDib) 
        return FALSE; 

	Destroy();
	m_hDib = hDib;
	return UpdateInternal();
}

/*
*--------------------------------------------------------------------------------
*  Create()
*  ����CDib���� 
*  Parameter :  
*              [IN]    ar
*                 �ļ�
*  Return value:
*              ��
*====================================================
*
*/

void CDib::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	ar.Flush();
	if (ar.IsStoring())
	{
		Write(ar.GetFile());
	}
    else
    {
   		Read(ar.GetFile());
    }
}

/*
*--------------------------------------------------------------------------------
*  Load()
*  ����CDib���� 
*  Parameter :  
*              [IN]    uIDS
*                 Id��
*              [IN]    lpszDibType
*                 Dib����ָ��
*  Return value:
*            ����TRUE��ʾ����ɹ�������FALSEʧ��
*====================================================
*
*/

BOOL CDib::Load(UINT uIDS, LPCSTR lpszDibType)
{                                
	LPCSTR lpszDibRes = MAKEINTRESOURCE(uIDS);

	return Load(lpszDibRes, lpszDibType);
}

/*
*--------------------------------------------------------------------------------
*  Load()
*  ����CDib���� 
*  Parameter :  
*              [lpszDibRes]    uIDS
*                 ��Դ
*              [lpszDibType]    lpszDibType
*                 Dib����ָ��
*  Return value:
*            ����TRUE��ʾ����ɹ�������FALSEʧ��
*====================================================
*
*/
BOOL CDib::Load(LPCSTR lpszDibRes, LPCSTR lpszDibType)
{                                
	HINSTANCE hInst = AfxGetInstanceHandle();
	HRSRC   hRes    = ::FindResource(hInst, lpszDibRes, lpszDibType);
	HGLOBAL hData   = ::LoadResource(hInst, hRes);

	// ����Դ����
	if (hRes == NULL || hData == NULL)
		return FALSE;

	//�õ���Դ����
	LPBYTE lpBuf = (LPBYTE)::LockResource(hData);
	// is DIB ?
	if (((LPBITMAPFILEHEADER)lpBuf)->bfType != DIB_HEADER_MARKER/*"BM"*/)
		return FALSE;

	// ʹ��������������� CDib
	LPBYTE lpDIB = lpBuf + sizeof(BITMAPFILEHEADER);
	return Create(lpDIB);
}
/*
*--------------------------------------------------------------------------------
*  Load()
*  ����CDib���� 
*  Parameter :  
*              [IN]    lpszDibFile
*                 �ļ���
*  Return value:
*              ����TRUE��ʾ����ɹ�������FALSEʧ��
*====================================================
*  �汾�����¼
*  CPH 1.0 2002/11/13 ��ΰ  ����CDib���� 
*
*/

BOOL CDib::Load(LPCTSTR lpszDibFile)
{                                
	TRY
	{
		CFile file(lpszDibFile, CFile::modeRead|CFile::shareDenyNone);

		if (! Read(&file))
			return FALSE;
	}
	CATCH (CException, e)
	{
		return FALSE;
	}
	END_CATCH

	return TRUE;
}  
             
/*
*--------------------------------------------------------------------------------
*  Save()
*  ����CDib���� 
*  Parameter :  
*              [IN]    lpszDibFile
*                 �ļ���
*  Return value:
*             ����TRUE��ʾ����ɹ�������FALSEʧ��
*====================================================
*  �汾�����¼
*  CPH 1.0 2002/11/13 ��ΰ  ����CDib���� 
*
*/

BOOL CDib::Save(LPCSTR lpszDibFile)
{
	TRY
	{
		CFile file(lpszDibFile, CFile::modeCreate|CFile::modeWrite);

		if (! Write(&file))
			return FALSE;
	}
	CATCH (CException, e)
	{
		return FALSE;
	}
	END_CATCH

	return TRUE;
}

/*
*--------------------------------------------------------------------------------
*  Read()
*  ��CDib���� 
*  Parameter :  
*              [IN]    pFile
*                 �ļ���ָ��
*  Return value:
*             ����TRUE��ʾ����ɹ�������FALSEʧ��
*====================================================
*/

BOOL CDib::Read(CFile *pFile)
{
	WaitCursorBegin();

	LPBITMAPINFOHEADER lpbi;
	DWORD dwSize;
	TRY
	{
		// ��DIB�ļ�ͷ�ṹ
		BITMAPFILEHEADER bmfHdr;
		pFile->Read(&bmfHdr, sizeof(BITMAPFILEHEADER));

		if (bmfHdr.bfType != DIB_HEADER_MARKER/*"BM"*/)
		{
			WaitCursorEnd();
			return FALSE;
		}
		DWORD dwLength = pFile->GetLength();
		if (bmfHdr.bfSize != dwLength)
			bmfHdr.bfSize = dwLength;

		//�� DIB������
		dwSize = bmfHdr.bfSize - sizeof(BITMAPFILEHEADER);
		lpbi = (LPBITMAPINFOHEADER)GlobalAllocPtr(GHND, dwSize);
		DWORD dwCount = pFile->Read(lpbi, dwSize);
		
		if (dwCount != dwSize)
		{
			GlobalFreePtr(lpbi);
			WaitCursorEnd();
			return FALSE;
		}

		//������window DIB ���� NULL. 
	    if (lpbi->biSize != sizeof(BITMAPINFOHEADER)) 
		{
			GlobalFreePtr(lpbi);
			WaitCursorEnd();
			return FALSE;
		}
		
		//�����ɫ��
		int nNumColors = (UINT)lpbi->biClrUsed;
		if (nNumColors == 0) 
		{ 
			//24-bit DIBû����ɫ�� 
	        if (lpbi->biBitCount != 24) 
		        nNumColors = 1 << lpbi->biBitCount; // standard size table 
		} 
 
		// ������Ϊ0ʱ���һЩĬ��ֵ
	    if (lpbi->biClrUsed == 0) 
		    lpbi->biClrUsed = nNumColors; 
		if (lpbi->biSizeImage == 0) 
			lpbi->biSizeImage = ((((lpbi->biWidth * (DWORD)lpbi->biBitCount) + 31) & ~31) >> 3) * lpbi->biHeight; 
 	}
	CATCH (CException, e)
	{
		GlobalFreePtr(lpbi);
		WaitCursorEnd();
		return FALSE;
	}
	END_CATCH

	//ʹ��DIB����������CDib 
	BOOL bSuccess = Create((LPBYTE)lpbi);
	GlobalFreePtr(lpbi);
	WaitCursorEnd();

	return bSuccess;
}

/*
*--------------------------------------------------------------------------------
*  Write()
*  дCDib���� 
*  Parameter :  
*              [IN]    pFile
*                 �ļ���ָ��
*  Return value:
*             ����TRUE��ʾд�ļ��ɹ�������FALSEʧ��
*====================================================
*
*/

BOOL CDib::Write(CFile *pFile)
{
	WaitCursorBegin();
     //λͼͷ�ṹ 
    BITMAPFILEHEADER    bmfHdr;
	// ָ��һ�� DIB ��Ϣͷ�ṹָ�� 
    LPBITMAPINFOHEADER  lpBI;       
    DWORD               dwDIBSize; 

	//�õ�һ��ָ��ָ��DIB�ڴ�, ��ʼ����BITMAPINF�ṹ��Ϣ 
    lpBI = (LPBITMAPINFOHEADER)GlobalLock(m_hDib); 
    if (!lpBI) 
	{
		GlobalUnlock(m_hDib);
		WaitCursorEnd();
        return FALSE; 
	}
 
    //����Ƿ���WINDOWS DIB
    if (lpBI->biSize != sizeof(BITMAPINFOHEADER)) 
    { 
        GlobalUnlock(m_hDib); 
		WaitCursorEnd();
        return FALSE; 
    } 
 
    // ����ļ�ͷ 
 
    // ����ļ����� (ǰ�����ַ������� "BM" ����BMP�ļ�) 
 
    bmfHdr.bfType = DIB_HEADER_MARKER;  // "BM" 
 
 
    dwDIBSize = *(LPDWORD)lpBI + PaletteSize((LPBYTE)lpBI);   
 
    // ����ͼ�γߴ�
 
    if ((lpBI->biCompression == BI_RLE8) || (lpBI->biCompression == BI_RLE4)) 
        dwDIBSize += lpBI->biSizeImage; 
    else 
    { 
         //����Ϊλͼ
		DWORD dwBmBitsSize;  
 
        // ��ѹ����ʽ 
        dwBmBitsSize = WIDTHBYTES1((lpBI->biWidth)*((DWORD)lpBI->biBitCount)) * 
                lpBI->biHeight; 
 
        dwDIBSize += dwBmBitsSize; 
 
        lpBI->biSizeImage = dwBmBitsSize; 
    } 
 
 
    // �����ļ��ߴ翿�������DIB��BITMAPFILEHEADER�ṹ�ߴ� 
                    
    bmfHdr.bfSize = dwDIBSize + sizeof(BITMAPFILEHEADER); 
    bmfHdr.bfReserved1 = 0; 
    bmfHdr.bfReserved2 = 0; 
 
    // ����λͼ��ƫ���������λͼ�ļ�����DIB��ͷ�ߴ����ɫ��ߴ�  
    bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + lpBI->biSize + 
            PaletteSize((LPBYTE)lpBI); 
 
 	TRY
	{
	    // д�ļ�ͷ
		pFile->Write(&bmfHdr, sizeof(BITMAPFILEHEADER));
		//дDIB ������
		pFile->Write(lpBI, dwDIBSize);
	}
	CATCH (CException, e)
	{
        GlobalUnlock(m_hDib); 
		WaitCursorEnd();
		return FALSE;
	}
	END_CATCH

	GlobalUnlock(m_hDib); 
	WaitCursorEnd();
	
	return TRUE;
}

/*
*--------------------------------------------------------------------------------
*  Display()
*  ��ʾCDib���� 
*  Parameter :  
*              [IN]    pDC
*                 DCָ��
*              [IN]    xDest
*                 Ŀ��X
*              [IN]    yDest
*                 Ŀ��Y
*              [IN]    nWidthDest
*                 Ŀ����
*              [IN]    nHeightDest
*                 Ŀ��߶�
*              [IN]    xSrc
*                 ԴX
*              [IN]    ySrc
*                 ԴY
*              [IN]    dwRop
*                 ��ʾ��ʽ
*  Return value:
*              ����TRUE��ʾ��ʾ�ɹ�������FALSEʧ��
*====================================================
*
*/

BOOL CDib::Display(CDC* pDC, int xDest, int yDest, int nWidthDest, int nHeightDest, 
 				   int xSrc, int ySrc, DWORD dwRop)
{
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);

	CBitmap* pOldBmp = MemDC.SelectObject(m_pBitmap);

	CPalette* pOldPal = pDC->SelectPalette(m_pPalette, TRUE);
    pDC->RealizePalette();

	BOOL bSuccess = pDC->BitBlt( xDest, yDest, 
							nWidthDest, nHeightDest,
						    &MemDC, 
							xSrc, ySrc, 
							dwRop);

	MemDC.SelectObject(pOldBmp);
	pDC->SelectPalette(pOldPal, TRUE);

	return bSuccess;
}

/*
*--------------------------------------------------------------------------------
*  Display()
*  ��ʾCDib���� 
*  Parameter :  
*              [IN]    pDC
*                 DCָ��
*              [IN]    xDest
*                 Ŀ��X
*              [IN]    yDest
*                 Ŀ��Y
*              [IN]    nWidthDest
*                 Ŀ����
*              [IN]    nHeightDest
*                 Ŀ��߶�
*              [IN]    xSrc
*                 ԴX
*              [IN]    ySrc
*                 ԴY
*              [IN]    nWidthDest
*                 Դ���
*              [IN]    nHeightDest
*                 Դ���
*              [IN]    dwRop
*                 ��ʾ��ʽ
*  Return value:
*               ����TRUE��ʾ��ʾ�ɹ�������FALSEʧ��
*====================================================
*
*/

BOOL CDib::Display(CDC * pDC, int xDest, int yDest, int nWidthDest, int nHeightDest, 
				   int xSrc, int ySrc, int nWidthSrc, int nHeightSrc, DWORD dwRop)
{
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);

	CBitmap* pOldBmp = MemDC.SelectObject(m_pBitmap);

	CPalette* pOldPal = pDC->SelectPalette(m_pPalette, TRUE);
    pDC->RealizePalette();

	BOOL bSuccess = pDC->StretchBlt( xDest, yDest, 
								nWidthDest, nHeightDest,
						        &MemDC, 
								xSrc, ySrc, 
								nWidthSrc, nHeightSrc, 
								dwRop);

	MemDC.SelectObject(pOldBmp);
	pDC->SelectPalette(pOldPal, TRUE);

	return bSuccess;
}

/*
*--------------------------------------------------------------------------------
*  Display()
*  ��ʾCDib���� 
*  Parameter :  
*              [IN]    pDC
*                 DCָ��
*              [IN]    x
*                 ԴX
*              [IN]    y
*                 ԴY
*              [IN]    dwRop
*                 ��ʾ��ʽ
*  Return value:
*               ����TRUE��ʾ��ʾ�ɹ�������FALSEʧ��
*====================================================
*
*/
BOOL CDib::Display(CDC * pDC, int x, int y, DWORD dwRop)
{
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);

	CBitmap* pOldBmp = MemDC.SelectObject(m_pBitmap);

	CPalette* pOldPal = pDC->SelectPalette(m_pPalette, TRUE);
    pDC->RealizePalette();

	BOOL bSuccess = pDC->BitBlt(x, y, 
								GetWidth(), GetHeight(),
								&MemDC, 
								0, 0, 
								dwRop);

	MemDC.SelectObject(pOldBmp);
	pDC->SelectPalette(pOldPal, TRUE);

	return bSuccess;
}

/*
*--------------------------------------------------------------------------------
*  Display()
*  ��ʾCDib���� 
*  Parameter :  
*              [IN]    pDC
*                 DCָ��
*              [IN]    rcDest
*                 Ŀ���
*              [IN]    rcSrc
*                 Դ��
*              [IN]    dwRop
*                 ��ʾ��ʽ
*  Return value:
*               ����TRUE��ʾ��ʾ�ɹ�������FALSEʧ��
*====================================================
*
*/

BOOL CDib::Display(CDC* pDC, CRect rcDest, CRect rcSrc, DWORD dwRop)
{
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);

	CBitmap* pOldBmp = MemDC.SelectObject(m_pBitmap);

	CPalette* pOldPal = pDC->SelectPalette(m_pPalette, TRUE);
    pDC->RealizePalette();

	BOOL bSuccess = pDC->StretchBlt( rcDest.left, rcDest.top, 
								rcDest.Width(), rcDest.Height(),
						        &MemDC, 
								rcSrc.left, rcSrc.top, 
								rcSrc.Width(), rcSrc.Height(),
								dwRop);

	MemDC.SelectObject(pOldBmp);
	pDC->SelectPalette(pOldPal, TRUE);

	return bSuccess;
}

/*
*--------------------------------------------------------------------------------
*  BuildBitmap()
*  ����CBitmap���� 
*  Parameter :  
               ��
*  Return value:
*               ����TRUE��ʾ�����ɹ�������FALSEʧ��
*====================================================
*
*/

BOOL CDib::BuildBitmap()
{
	if (m_pBitmap != NULL)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
		m_hBitmap = NULL;
	}
	m_hBitmap = DIBToDIBSection(m_hDib);
	if (m_hBitmap == NULL)
		return FALSE;

	if (m_pBitmap)
		delete m_pBitmap;
	m_pBitmap = new CBitmap;
	m_pBitmap->Attach(m_hBitmap);
    

	return TRUE;
}

/*
*--------------------------------------------------------------------------------
*  BuildPalette()
*  ������ɫ�����  
*  Parameter :  
               ��
*  Return value:
*               ����TRUE��ʾ�����ɹ�������FALSEʧ��
*====================================================
*
*/

BOOL CDib::BuildPalette()
{
	if (m_pPalette != NULL)
	{
		delete m_pPalette;
		m_pPalette = NULL;
	}
	HPALETTE hPalette = CreateDIBPalette(m_hDib);
	if (hPalette == NULL)
		return FALSE;
	m_pPalette = new CPalette;
	m_pPalette->Attach(hPalette);

	return TRUE;
}

/*
*--------------------------------------------------------------------------------
*  UpdateInternal()
*  ����λͼ����ɫ����� 
*  Parameter :  
               ��
*  Return value:
*               ����TRUE��ʾ�ɹ�������FALSEʧ��
*====================================================
*/

BOOL CDib::UpdateInternal()
{
	BuildPalette();
	return BuildBitmap();
}

/*
*--------------------------------------------------------------------------------
*  GetPalette()
*  ������ɫ����� 
*  Parameter :  
               ��
*  Return value:
*               
*====================================================
*
*/

CPalette* CDib::GetPalette()
{
	return m_pPalette;
}

/*
*--------------------------------------------------------------------------------
*  GetBitmap()
*  ����CBitmapλͼ���� 
*  Parameter :  
               ��
*  Return value:
*              λͼ����
*====================================================
*
*/

CBitmap* CDib::GetBitmap()
{
	return m_pBitmap;
}

/*
*--------------------------------------------------------------------------------
*  IsEmpty()
*  ���CDib�����Ƿ�Ϊ��
*  Parameter :  
               ��
*  Return value:
*               ����TRUE��ʾΪ�գ�����FALSE��Ϊ��
*====================================================
*
*/

BOOL CDib::IsEmpty()
{
	if (m_hDib == NULL)
		return TRUE;

	if (! GlobalLock(m_hDib))
		return TRUE;

	GlobalUnlock(m_hDib);
	return FALSE;
}

/*
*--------------------------------------------------------------------------------
*  GetCompression()
*  ѹ��CDib���� 
*  Parameter :  
               ��
*  Return value:
*              ѹ����ָ�볤
*====================================================
*
*/

DWORD CDib::GetCompression()
{
    LPBITMAPINFOHEADER lpBI = (LPBITMAPINFOHEADER)GlobalLock(m_hDib); 
    if (!lpBI) 
	{
		GlobalUnlock(m_hDib);
        return 0; 
	}
 
	DWORD dwCompression = lpBI->biCompression;
	GlobalUnlock(m_hDib);

	return dwCompression;
}

/*
*--------------------------------------------------------------------------------
*  GetBitCount()
*  �õ�CDib�����λ��
*  Parameter :  
               ��
*  Return value:
*           CDib�����λ�� 
*====================================================
*
*/

WORD CDib::GetBitCount()
{
    LPBITMAPINFOHEADER lpBI = (LPBITMAPINFOHEADER)GlobalLock(m_hDib); 
    if (!lpBI) 
	{
		GlobalUnlock(m_hDib);
        return 0; 
	}
 
	WORD wBitCount = lpBI->biBitCount;
	GlobalUnlock(m_hDib);

	return wBitCount;
}

/*
*--------------------------------------------------------------------------------
*  GetWidth()
*  �õ�DIB����Ŀ��
*  Parameter :  
               ��
*  Return value:
*           DIB����Ŀ��   
*====================================================
*  �汾�����¼
*  CPH 1.0 2002/11/13 ��ΰ  ����CDib���� 
*
*/

LONG CDib::GetWidth()
{
	// �õ� DIB��������ָ��
    LPBYTE lpDIB = (LPBYTE)GlobalLock(m_hDib); 
	if (! lpDIB)
	{
		GlobalUnlock(m_hDib);
		return 0;
	}

	LONG lWidth = (LONG)DIBWidth(lpDIB);
	GlobalUnlock(m_hDib);

	return lWidth; 
}

/*
*--------------------------------------------------------------------------------
*  GetHeight()
*  �õ�DIB����ĸ߶�
*  Parameter :  
               ��
*  Return value:
*              DIB����ĸ߶�
*====================================================
*
*/

LONG CDib::GetHeight()
{
	// �õ� DIB��������ָ��
    LPBYTE lpDIB = (LPBYTE)GlobalLock(m_hDib); 
	if (! lpDIB)
	{
		GlobalUnlock(m_hDib);
		return 0;
	}

	LONG lHeight = (LONG)DIBHeight(lpDIB);
	GlobalUnlock(m_hDib);

	return lHeight; 
}

/*
*--------------------------------------------------------------------------------
*  GetWidthBytes()
*  �õ�DIB����Ŀ��λ��
*  Parameter :  
               ��
*  Return value:
*              DIB����Ŀ��λ��
*====================================================
*
*/

LONG CDib::GetWidthBytes()
{
	return WIDTHBYTES1((GetWidth())*((DWORD)GetBitCount()));
}

/*
*--------------------------------------------------------------------------------
*  GetPixel()
*  �õ�ָ���������ֵ
*  Parameter :  
*                [IN] x
*                   ���x����
*                [IN] y
*                   ���y����
*  Return value: 
*                RGB��ɫֵ
*====================================================
*
*/

COLORREF CDib::GetPixel(LONG x, LONG y)
{
	COLORREF cColor;
	switch (GetBitCount())
	{
		case 1 :	if (1<<(7-x%8) & 
						*(BYTE*)(GetBitsPtr()+GetPixelOffset(x, y)))
						cColor = RGB(255,255,255);
					else
						cColor = RGB(0,0,0);
					break;
		case 4 :	
				{
					PALETTEENTRY PaletteColors[16];
					m_pPalette->GetPaletteEntries(0, 16, PaletteColors);
					int nIndex = (*(BYTE*)(GetBitsPtr()+GetPixelOffset(x, y)) & 
								   (x%2 ? 0x0f : 0xf0)) >> (x%2 ? 0 : 4);
					cColor = RGB(PaletteColors[nIndex].peRed,
								 PaletteColors[nIndex].peGreen,
								 PaletteColors[nIndex].peBlue);
				}
					break;
		case 8 :	
				{
					PALETTEENTRY PaletteColors[256];
					m_pPalette->GetPaletteEntries(0, 256, PaletteColors);
					int nIndex = *(BYTE*)(GetBitsPtr()+GetPixelOffset(x, y));
					cColor = RGB(PaletteColors[nIndex].peRed,
								 PaletteColors[nIndex].peGreen,
								 PaletteColors[nIndex].peBlue);
				}
					break;
		default:	cColor = RGB(*(BYTE*)(GetBitsPtr()+GetPixelOffset(x, y)),
								 *(BYTE*)(GetBitsPtr()+GetPixelOffset(x, y)+1),
								 *(BYTE*)(GetBitsPtr()+GetPixelOffset(x, y)+2));
					break;
	}
	return cColor;
}

/*
*--------------------------------------------------------------------------------
*  GetPixelOffset()
*  �õ�CDib����ƫ�� 
*  Parameter :  
*                [IN] x
*                   ���x����
*                [IN] y
*                   ���y����
*  Return value: 
*               ƫ���� 
*====================================================
*  �汾�����¼
*  CPH 1.0 2002/11/13 ��ΰ  ����CDib���� 
*
*/

LONG CDib::GetPixelOffset(LONG x, LONG y)
{
	return (GetHeight()-y-1)*GetWidthBytes()+x/(8/GetBitCount());
}

/*
*--------------------------------------------------------------------------------
*  GetBitsPtr()
*  �õ�CDib����λ
*  Parameter :  
*                ��
*  Return value: 
*                �ֽ�ָ��
*====================================================
*
*/

LPBYTE CDib::GetBitsPtr()
{
    LPBYTE lpDIB = (LPBYTE)GlobalLock(m_hDib); 
    if (! lpDIB) 
	{
		GlobalUnlock(m_hDib);
		return NULL;
	}

	LPBYTE lpData = FindDIBBits(lpDIB);
	GlobalUnlock(m_hDib);

	return lpData;
}

/*
*--------------------------------------------------------------------------------
*  GetHandle()
*  �õ�CDib����ľ��
*  Parameter :  
*                ��
*  Return value: 
*                ������
*====================================================
*
*/

HANDLE CDib::GetHandle()
{
	return m_hDib;
}

/*
*--------------------------------------------------------------------------------
*  GetColorNumber()
*  �õ�CDib�������ɫ�� 
*  Parameter :  
*                ��
*  Return value: 
*                ��ɫλ��
*====================================================
*
*/

WORD CDib::GetColorNumber()
{
    LPBYTE lpBI = (LPBYTE)GlobalLock(m_hDib); 
    if (! lpBI) 
	{
		GlobalUnlock(m_hDib);
		return 0;
	}
 
	WORD wColors = DIBNumColors(lpBI);
	GlobalUnlock(m_hDib);

	return wColors;
}

/*
*--------------------------------------------------------------------------------
*  GetPaletteSize()
*  �õ�CDib����ĵ�ɫ��ߴ� 
*  Parameter :  
*                ��
*  Return value: 
*                ��ɫ��λ��
*====================================================
*
*/

WORD CDib::GetPaletteSize()
{
    LPBYTE lpBI = (LPBYTE)GlobalLock(m_hDib); 
    if (! lpBI) 
	{
		GlobalUnlock(m_hDib);
		return 0;
	}
 
	WORD wPalSize = PaletteSize(lpBI);
	GlobalUnlock(m_hDib);

	return wPalSize;
}

/*
*--------------------------------------------------------------------------------
*  BeginPaint
*  ׼����ʼ��CDib������ڴ�CDC���в���
*  Parameter :  
*                [IN] pDC
*                   Ҫ�������豸������ָ��
*    
*  Return value: 
*                ѡ���Ӧ�ڴ���豸������ָ��
*====================================================
*
*/

CDC* CDib::BeginPaint(CDC *pDC)
{
	if (m_pMemDC)
		delete m_pMemDC;
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(pDC);
	m_pPaletteTmp = m_pMemDC->SelectPalette(m_pPalette, TRUE);
	m_pMemDC->RealizePalette();
	m_pBitmapTmp = (CBitmap *)m_pMemDC->SelectObject(m_pBitmap);
	return m_pMemDC;
}

/*
*--------------------------------------------------------------------------------
*  EndPaint()
*  ����CDib������ڴ�CDC���в���
*  Parameter :  

*  Return value: 
*     
*====================================================
*
*/

void CDib::EndPaint()
{
	m_pMemDC->SelectObject(m_pBitmapTmp);
	m_pMemDC->SelectPalette(m_pPaletteTmp, TRUE);
	delete m_pMemDC;
	m_pMemDC = NULL;

	Create(m_hBitmap);
}

/*
*--------------------------------------------------------------------------------
*  DisplayPalette
*  ��ʾCDib���� �ĵ�ɫ��
*  Parameter :  
*                [IN] pDC
*                   Ҫ��ʾ���豸�����ľ��
*                [IN] rc
*                   ��ʾ�ľ�����
*  Return value: 
*                ����TRUE��ʾ��ʾ�ɹ�������FALSE��ʾʧ��
*====================================================
*
*/

BOOL CDib::DisplayPalette(CDC* pDC, CRect rc)
{
	return ::DisplayPalette(pDC->GetSafeHdc(), &rc, (HPALETTE)m_pPalette->GetSafeHandle());
}

/*
*--------------------------------------------------------------------------------
*  DisplayTransparent()
*  ͸����ʾָ����DIB���� 
*  Parameter :  
*
*                [IN]pDC
*                    �豸������ָ��
*                [IN] x
*                   ���x����
*                [IN] y
*                   ���y����
*				 [IN]cTransparentColor	
*					��ʾʱ���õ�͸��ɫ
*  Return value: 
*                ����TRUE��ʾ��ʾ�ɹ�������FALSE��ʾʧ��
*====================================================
*
*/

BOOL CDib::DisplayTransparent(CDC * pDC, int x, int y, COLORREF cTransparentColor)
{
	CPalette* pOldPal = pDC->SelectPalette(m_pPalette, TRUE);
    pDC->RealizePalette();

	DrawTransparentBitmap(pDC->GetSafeHdc(), 
						  m_hBitmap, 
						  x, 
						  y, 
						  cTransparentColor);

	pDC->SelectPalette(pOldPal, TRUE);

	return TRUE;
}

#define UPVALUE(x, n)	((x)/((n) ? (n) : 1) + ((x)%((n) ? (n) : 1) ? 1 : 0))

/*
*--------------------------------------------------------------------------------
*  DisplayFadeIn
*  �������ʾDIB���󣨲��ԣ�
*  Parameter :  
*
*                [IN]pDC
*                    �豸������ָ��
*                [IN] x
*                   ���x����
*                [IN] y
*                   ���y����
*				 [IN]nDeta	
*					��ʾʱ����
*				 [IN]dwDelayTime
*					��ʾʱ���ӳ�ʱ��
*  Return value: 
*                ����TRUE��ʾ��ʾ�ɹ�������FALSE��ʾʧ��
*====================================================
*
*/


BOOL CDib::DisplayFadeIn(CDC* pDC, int x, int y, int nDeta, DWORD dwDelayTime)
{
	// ���� DIB
	HDIB hDib = CopyHandle(m_hDib);

	// �õ���ɫ��
	WORD wNumColors = GetColorNumber();

	BITMAPINFO *bmi = (BITMAPINFO *)GlobalLock(m_hDib);
	BITMAPINFO *bmi0 = (BITMAPINFO *)GlobalLock(hDib);
	if (! bmi)
		return FALSE;

	BOOL bDone = FALSE;
	int nDetaR, nDetaG, nDetaB;
	// ����
	if (wNumColors)		
	{
		// ������ɫͼ��
		for (WORD i=0; i<wNumColors; ++i)
		{
			bmi->bmiColors[i].rgbRed = 0 ;
			bmi->bmiColors[i].rgbGreen = 0 ;
			bmi->bmiColors[i].rgbBlue = 0 ;
		}
		UpdateInternal();
		// ��ʼ��ʾ��ɫ
		Display(pDC, x, y, SRCCOPY);

		while (! bDone)
		{
			bDone = TRUE;
			for (WORD i=0; i<wNumColors; i++)
			{
				nDetaR = UPVALUE(bmi0->bmiColors[i].rgbRed-bmi->bmiColors[i].rgbRed, nDeta);
				nDetaG = UPVALUE(bmi0->bmiColors[i].rgbGreen-bmi->bmiColors[i].rgbGreen, nDeta);
				nDetaB = UPVALUE(bmi0->bmiColors[i].rgbBlue-bmi->bmiColors[i].rgbBlue, nDeta);
				if (! Fade(nDetaR, nDetaG, nDetaB,
						 bmi0->bmiColors[i].rgbRed,
						 bmi0->bmiColors[i].rgbGreen,
						 bmi0->bmiColors[i].rgbBlue,
						 &(bmi->bmiColors[i].rgbRed),
						 &(bmi->bmiColors[i].rgbGreen),
						 &(bmi->bmiColors[i].rgbBlue)))
					 bDone = FALSE;
			}
			UpdateInternal();
			Display(pDC, x, y, SRCCOPY);
			Delay(dwDelayTime);
			nDeta--;
		}
	}
	// �޵�ɫ��
	else	
	{
		// Ӧ��������ʾ�ٶ�
		dwDelayTime /= 10;
		// λλ��
		LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)bmi;
		LPBYTE lpBits = (LPBYTE)lpbi + lpbi->biSize;
		LPBYTE lpBits0 = (LPBYTE)bmi0 + lpbi->biSize;
		int nDelta = WIDTHBYTES1(lpbi->biBitCount*lpbi->biWidth) - lpbi->biWidth*lpbi->biBitCount/8;
		int nx, ny;

		//������ɫλͼ
		for (ny=0; ny<lpbi->biHeight; ny++)
		{
			for (nx=0; nx<lpbi->biWidth; nx++)
			{
				*lpBits++ = 0;
				*lpBits++ = 0;
				*lpBits++ = 0;
			}
			lpBits += nDelta; 
		}
		lpBits = (LPBYTE)lpbi + lpbi->biSize;
		UpdateInternal();
		// ��ʼʱ��ʾ��ɫ
		Display(pDC, x, y, SRCCOPY);

		BYTE r, g, b, r0, g0, b0;
		while (! bDone)
		{
			bDone = TRUE;
			for (ny=0; ny<lpbi->biHeight; ny++)
			{
				for (nx=0; nx<lpbi->biWidth; nx++)
				{
					b0 = (BYTE)*lpBits0++;
					g0 = (BYTE)*lpBits0++;
					r0 = (BYTE)*lpBits0++;
					b = (BYTE)*(lpBits);
					g = (BYTE)*(lpBits+1);
					r = (BYTE)*(lpBits+2);
					nDetaR = UPVALUE(r0-r, nDeta);
					nDetaG = UPVALUE(g0-g, nDeta);
					nDetaB = UPVALUE(b0-b, nDeta);
					if (! Fade(nDetaR, nDetaG, nDetaB, r0, g0, b0, &r, &g, &b))
						bDone = FALSE;
					*lpBits++ = b;
					*lpBits++ = g;
					*lpBits++ = r;
				}
				lpBits += nDelta; 
				lpBits0 += nDelta; 
			}
			lpBits = (LPBYTE)lpbi + lpbi->biSize;
			lpBits0 = (LPBYTE)bmi0 + lpbi->biSize;
			UpdateInternal();
			Display(pDC, x, y, SRCCOPY);
			Delay(dwDelayTime);
			nDeta--;
		}
	}

	//������� 
	GlobalUnlock(m_hDib);
	GlobalUnlock(hDib);

	//�ش汸�ݵ� DIB
	m_hDib = CopyHandle(hDib);
	GlobalFree(hDib);

	return TRUE;
}

/*
*--------------------------------------------------------------------------------
*  DisplayFadeOut
*  ��������ʾDIB����(����)
*  Parameter :  
*
*                [IN]pDC
*                    �豸������ָ��
*                [IN] x
*                   ���x����
*                [IN] y
*                   ���y����
*				 [IN]nDeta	
*					��ʾʱ����
*				 [IN]dwDelayTime
*					��ʾʱ���ӳ�ʱ��
*  Return value: 
*                ����TRUE��ʾ��ʾ�ɹ�������FALSE��ʾʧ��
*====================================================
*
*/

BOOL CDib::DisplayFadeOut(CDC* pDC, int x, int y, int nDeta, DWORD dwDelayTime)
{
	//һ��ʼʱ��ʾ
	Display(pDC, x, y, SRCCOPY);
	
	// ����DIB
	HDIB hDib = CopyHandle(m_hDib);

	// �õ�DIB
	WORD wNumColors = GetColorNumber();

	BITMAPINFO *bmi = (BITMAPINFO *)GlobalLock(m_hDib);
	if (! bmi)
		return FALSE;

	BOOL bDone = FALSE;
	int nDetaR, nDetaG, nDetaB;
	// �������е�ɫ�壩
	if (wNumColors)		
	{
		while (! bDone)
		{
			bDone = TRUE;
			for (WORD i=0; i<wNumColors; i++)
			{
				nDetaR = -1*UPVALUE(bmi->bmiColors[i].rgbRed, nDeta);
				nDetaG = -1*UPVALUE(bmi->bmiColors[i].rgbGreen, nDeta);
				nDetaB = -1*UPVALUE(bmi->bmiColors[i].rgbBlue, nDeta);
				if (! Fade(nDetaR, nDetaG, nDetaB,
						 0, 0, 0,
						 &(bmi->bmiColors[i].rgbRed),
						 &(bmi->bmiColors[i].rgbGreen),
						 &(bmi->bmiColors[i].rgbBlue)))
					 bDone = FALSE;
			}
			UpdateInternal();
			Display(pDC, x, y, SRCCOPY);
			Delay(dwDelayTime);
			nDeta--;
		}
	}
	//�޵�ɫ��
	else		
	{
		// ������ʾ�ٶ�
		dwDelayTime /= 10;
		//λλ�� 
		LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)bmi;
		LPBYTE lpBits = (LPBYTE)lpbi + lpbi->biSize;
		int nDelta = WIDTHBYTES1(lpbi->biBitCount*lpbi->biWidth) - lpbi->biWidth*lpbi->biBitCount/8;

		BYTE r, g, b;
		int nx, ny;
		while (! bDone)
		{
			bDone = TRUE;
			for (ny=0; ny<lpbi->biHeight; ny++)
			{
				for (nx=0; nx<lpbi->biWidth; nx++)
				{
					b = (BYTE)*(lpBits);
					g = (BYTE)*(lpBits+1);
					r = (BYTE)*(lpBits+2);
					nDetaR = -1*UPVALUE(r, nDeta);
					nDetaG = -1*UPVALUE(g, nDeta);
					nDetaB = -1*UPVALUE(b, nDeta);
					if (! Fade(nDetaR, nDetaG, nDetaB, 0, 0, 0, &r, &g, &b))
						bDone = FALSE;
					*lpBits++ = b;
					*lpBits++ = g;
					*lpBits++ = r;
				}
				lpBits += nDelta; 
			}
			lpBits = (LPBYTE)lpbi + lpbi->biSize;
			UpdateInternal();
			Display(pDC, x, y, SRCCOPY);
			Delay(dwDelayTime);
			nDeta--;
		}
	}

	//�ͷ�
	GlobalUnlock(m_hDib);

	// �ָ���ǰ���ݵ�DIB
	m_hDib = CopyHandle(hDib);
	GlobalFree(hDib);

	return TRUE;
}

/*
*--------------------------------------------------------------------------------
*  DisplayMosaicIn()
*  
*  Parameter :  
*                [IN] pDC
*                     Ҫ�������豸������ָ��
*                [IN] xx
*                   ���x����
*                [IN] yy
*                   ���y����
*                [IN] nTileSize
*                   ��ɫ��ߴ�
*                [IN] dwDelayTime
*                    ��ʾ�ӳ�ʱ��
*                [IN] dwRop
*                    
*  Return value: 
*               ����TRUE��ʾ��ʾ�ɹ�������FALSE��ʾʧ��
*====================================================
*
*/

BOOL CDib::DisplayMosaicIn(CDC *pDC, int xx, int yy, int nTileSize, DWORD dwDelayTime, DWORD dwRop)
{
    //������ɫ��ߴ�
	DWORD dwTileNum=(GetWidth()/nTileSize + ((GetWidth() % nTileSize) ? 1:0))*
					(GetHeight()/nTileSize + ((GetHeight() % nTileSize) ? 1:0));
	//���������
	POINT *point = new POINT[dwTileNum];
	if (point == NULL)
		return FALSE;

	//��ʼ��������
	LONG x=0, y=0;
	for (DWORD i=0;i<dwTileNum;++i) 
	{
		point[i].x=x;
		point[i].y=y;

		x+=nTileSize;
		if (x >= GetWidth()) 
		{
			x=0;
            y+=nTileSize;
		}
	}

	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBmp = MemDC.SelectObject(m_pBitmap);

	CPalette* pOldPal = pDC->SelectPalette(m_pPalette, TRUE);
    pDC->RealizePalette();
	
	double fMax = RAND_MAX;
	BOOL  bDone = FALSE;
	while (! bDone)
	{
		DWORD n = (DWORD)((double)dwTileNum*(double)((double)rand()/fMax));
		x = point[n].x;
		y = point[n].y;

		pDC->BitBlt(xx+x,
					yy+y,
					nTileSize,
					nTileSize,
					&MemDC,
					x,
					y,
					dwRop);

		dwTileNum--;
		bDone = !dwTileNum;

		point[n].x = point[dwTileNum].x;
		point[n].y = point[dwTileNum].y;
		Delay(dwDelayTime);
	}

	MemDC.SelectObject(pOldBmp);
	pDC->SelectPalette(pOldPal, TRUE);

	delete[] point;

	return TRUE;
}
/*
*--------------------------------------------------------------------------------
*  DisplayMosaicOut()
*  
*  Parameter :  
*                [IN] pDC
*                     Ҫ�������豸������ָ��
*                [IN] xx
*                   ���x����
*                [IN] yy
*                   ���y����
*                [IN] nTileSize
*                   �ߴ�
*                [IN] dwDelayTime
*                    ��ʾ�ӳ�ʱ��
*                    
*  Return value: 
*               ����TRUE��ʾ��ʾ�ɹ�������FALSE��ʾʧ��
*====================================================
*
*/

BOOL CDib::DisplayMosaicOut(CDC *pDC, int xx, int yy, int nTileSize, DWORD dwDelayTime)
{
	// ��ʼ��ʾdib
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBmp = MemDC.SelectObject(m_pBitmap);

	CPalette* pOldPal = pDC->SelectPalette(m_pPalette, TRUE);
    pDC->RealizePalette();

	pDC->BitBlt(xx,	yy,
				GetWidth(),	GetHeight(),
				&MemDC,
				0, 0,
				SRCCOPY);

    // ���������
	DWORD dwTileNum=(GetWidth()/nTileSize + ((GetWidth() % nTileSize) ? 1:0))*
					(GetHeight()/nTileSize + ((GetHeight() % nTileSize) ? 1:0));
	// ���������
	POINT *point = new POINT[dwTileNum];
	if (point == NULL)
		return FALSE;

	//��ʼ��������
	LONG x=0, y=0;
	for (DWORD i=0;i<dwTileNum;++i) 
	{
		point[i].x=x;
		point[i].y=y;

		x+=nTileSize;
		if (x >= GetWidth()) 
		{
			x=0;
            y+=nTileSize;
		}
	}

	CBrush brush(GetSysColor(COLOR_WINDOW));
	CBrush* oldbrush = pDC->SelectObject(&brush);
	CPen pen(PS_SOLID,1,GetSysColor(COLOR_WINDOW));
    CPen* oldpen = pDC->SelectObject(&pen);
	
	double fMax = RAND_MAX;
	BOOL bDone = FALSE;
	while (! bDone)
	{
		DWORD n = (DWORD)((double)dwTileNum*(double)((double)rand()/fMax));
		x = point[n].x;
		y = point[n].y;

		pDC->Rectangle(	xx+x,
						yy+y,
						xx+x+nTileSize+1,
						yy+y+nTileSize+1);

		dwTileNum--;
		bDone = !dwTileNum;

		point[n].x = point[dwTileNum].x;
		point[n].y = point[dwTileNum].y;
		Delay(dwDelayTime);
	}

	MemDC.SelectObject(pOldBmp);
	pDC->SelectPalette(pOldPal, TRUE);
	pDC->SelectObject(oldbrush);
    pDC->SelectObject(oldpen);

	delete[] point;

	return TRUE;
}

/*
*--------------------------------------------------------------------------------
* Display
* ��ʾָ����DIBͼ��
* Parameter :  
*                [IN] pDC
*                     Ҫ�������豸������ָ��
*                [IN] x
*                   ���x����
*                [IN] y
*                   ���y����
*                [IN] nDeta
*
*                [IN] dwDelayTime
*                    ��ʾ�ӳ�ʱ��*                 
*                [IN] dwRop
*                   ����λ��

*                    
*  Return value: 
*               ����TRUE��ʾ��ʾ�ɹ�������FALSE��ʾʧ��
*====================================================
*
*/

BOOL CDib::Display(int nEffect, CDC* pDC, int x, int y, int nDeta, DWORD dwDelayTime, DWORD dwRop)
{
	if (nEffect == EFFECT_FADE)
		return DisplayFadeIn(pDC, x, y, nDeta, dwDelayTime);
	else if (nEffect == EFFECT_MOSAIC)
		return DisplayMosaicIn(pDC, x, y, nDeta, dwDelayTime, dwRop);

	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBmp = MemDC.SelectObject(m_pBitmap);

	CPalette* pOldPal = pDC->SelectPalette(m_pPalette, TRUE);
    pDC->RealizePalette();

	LONG i = 0;
	BOOL bDone = FALSE;
	while (! bDone)
	{
		switch (nEffect)
		{
		case EFFECT_SCANDOWN:
			if (i > GetHeight())
			{
				i = GetHeight();
				bDone = TRUE;
			}
            pDC->BitBlt(x, 
						y+i,
                        GetWidth(),
						nDeta,
						&MemDC,
                        0,
						i,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_SCANUP:
			if (i > GetHeight())
			{
				i = GetHeight();
				bDone = TRUE;
			}
            pDC->BitBlt(x, 
						y+GetHeight()-i,
                        GetWidth(),
						nDeta,
						&MemDC,
                        0,
						GetHeight()-i,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_SCANRIGHT:
			if (i > GetWidth())
			{
				i = GetWidth();
				bDone = TRUE;
			}
            pDC->BitBlt(x+i, 
						y,
						nDeta,
                        GetHeight(),
						&MemDC,
						i,
                        0,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_SCANLEFT:
			if (i > GetWidth())
			{
				i = GetWidth();
				bDone = TRUE;
			}
            pDC->BitBlt(x+GetWidth()-i, 
						y,
						nDeta,
                        GetHeight(),
						&MemDC,
						GetWidth()-i,
                        0,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_VSPLITSCAN:
			if (i > GetHeight()/2)
			{
				i = GetHeight()/2;
				bDone = TRUE;
			}
			pDC->BitBlt(x,
						y+i,
						GetWidth(),
						nDeta,
						&MemDC,
						0,
						i,
						dwRop);
			pDC->BitBlt(x,
						y+GetHeight()-i,
						GetWidth(),
						i,
						&MemDC,
						0,
						GetHeight()-i,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_HSPLITSCAN:
			if (i > GetWidth()/2)
			{
				i = GetWidth()/2;
				bDone = TRUE;
			}
			pDC->BitBlt(x+i,
						y,
						nDeta,
						GetHeight(),
						&MemDC,
						i,
						0,
						dwRop);
			pDC->BitBlt(x+GetWidth()-i,
						y,
						nDeta,
						GetHeight(),
						&MemDC,
						GetWidth()-i,
						0,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_MOVEDOWN:
			if (i > GetHeight())
			{
				i = GetHeight();
				bDone = TRUE;
			}
			pDC->BitBlt(x,
						y,
						GetWidth(),
						i+nDeta,
						&MemDC,
						0,
						GetHeight()-i,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_MOVEUP:
			if (i > GetHeight())
			{
				i = GetHeight();
				bDone = TRUE;
			}
			pDC->BitBlt(x,
						y+GetHeight()-i,
						GetWidth(),
						i,
						&MemDC,
						0,
						0,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_MOVERIGHT:
			if (i > GetWidth())
			{
				i = GetWidth();
				bDone = TRUE;
			}
			pDC->BitBlt(x,
						y,
						i+nDeta,
						GetHeight(),
						&MemDC,
						GetWidth()-i,
						0,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_MOVELEFT:
			if (i > GetWidth())
			{
				i = GetWidth();
				bDone = TRUE;
			}
			pDC->BitBlt(x+GetWidth()-i,
						y,
						i,
						GetHeight(),
						&MemDC,
						0,
						0,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_VSPLITMOVE:
			if (i > GetHeight()/2)
			{
				i = GetHeight()/2;
				bDone = TRUE;
			}
			pDC->BitBlt(x,
						y,
						GetWidth(),
						i+nDeta,
						&MemDC,
						0,
						GetHeight()/2-i,
						dwRop);
			pDC->BitBlt(x,
						y+GetHeight()-i,
						GetWidth(),
						i,
						&MemDC,
						0,
						GetHeight()/2,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_HSPLITMOVE:
			if (i > GetWidth()/2)
			{
				i = GetWidth()/2;
				bDone = TRUE;
			}
			pDC->BitBlt(x,
						y,
						i+nDeta,
						GetHeight(),
						&MemDC,
						GetWidth()/2-i,
						0,
						dwRop);
			pDC->BitBlt(x+GetWidth()-i,
						y,
						i,
						GetHeight(),
						&MemDC,
						GetWidth()/2,
						0,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_VCROSSMOVE:
			if (i > GetHeight())
			{
				i = GetHeight();
				bDone = TRUE;
			}
			pDC->BitBlt(x,
						y,
						GetWidth()/2,
						i+nDeta,
						&MemDC,
						0,
						GetHeight()-i,
						dwRop);
			pDC->BitBlt(x+GetWidth()/2,
						y+GetHeight()-i,
						GetWidth(),
						i,
						&MemDC,
						GetWidth()/2,
						0,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_HCROSSMOVE:
			if (i > GetWidth())
			{
				i = GetWidth();
				bDone = TRUE;
			}
			pDC->BitBlt(x,
						y,
						i+nDeta,
						GetHeight()/2,
						&MemDC,
						GetWidth()-i,
						0,
						dwRop);
			pDC->BitBlt(x+GetWidth()-i,
						y+GetHeight()/2,
						i,
						GetHeight()/2,
						&MemDC,
						0,
						GetHeight()/2,
						dwRop);
			i += nDeta;
			break;
		case EFFECT_VRASTER:
		{
			if (i > GetHeight())
			{
				i = GetHeight();
				bDone = TRUE;
			}
			LONG j = 0;
			BOOL bQuitLoop = FALSE;
			while (! bQuitLoop)
			{
				if (j > GetWidth())
				{
					j = GetWidth();
					bQuitLoop = TRUE;
				}
				pDC->BitBlt(x+j,
							y,
							nDeta,
							i+1,
							&MemDC,
							j,
							GetHeight()-i,
							dwRop);
				j += nDeta;
				if (j > GetWidth())
				{
					j = GetWidth();
					bQuitLoop = TRUE;
				}
				pDC->BitBlt(x+j,
							y+GetHeight()-i,
							nDeta,
							i,
							&MemDC,
							j,
							0,
							dwRop);
				j += nDeta;
			}
			i++;
			break;
		}
		case EFFECT_HRASTER:
		{
			if (i > GetWidth())
			{
				i = GetWidth();
				bDone = TRUE;
			}
			LONG j = 0;
			BOOL bQuitLoop = FALSE;
			while (! bQuitLoop)
			{
				if (j > GetHeight())
				{
					j = GetHeight();
					bQuitLoop = TRUE;
				}
				pDC->BitBlt(x,
							y+j,
							i+1,
							nDeta,
							&MemDC,
							GetWidth()-i,
							j,
							dwRop);
				j += nDeta;
				if (j > GetHeight())
				{
					j = GetHeight();
					bQuitLoop = TRUE;
				}
				pDC->BitBlt(x+GetWidth()-i,
							y+j,
							i,
							nDeta,
							&MemDC,
							0,
							j,
							dwRop);
				j += nDeta;
			}
			i++;
			break;
		}
		case EFFECT_HBLIND:
		{
			if (i > nDeta)
			{
				i = nDeta;
				bDone = TRUE;
			}
			for (LONG j=i; j<GetHeight(); j+=nDeta)
				pDC->BitBlt(x,
							y+j,
							GetWidth(),
							1,
							&MemDC,
							0,
							j,
							dwRop);
			i++;
			break;
		}
		case EFFECT_VBLIND:
			if (i > nDeta)
			{
				i = nDeta;
				bDone = TRUE;
			}
			for (LONG j=i; j<GetWidth(); j+=nDeta)
				pDC->BitBlt(x+j,
							y,
							1,
							GetHeight(),
							&MemDC,
							j,
							0,
							dwRop);
			i++;
			break;
		}  // end of switch
		Delay(dwDelayTime);
	}	// end of while

	MemDC.SelectObject(pOldBmp);
	pDC->SelectPalette(pOldPal, TRUE);

	return TRUE;
}

/*
*--------------------------------------------------------------------------------
*  Clear()
*  ���������DIB���� 
*  Parameter :  
*                [IN] nEffect
*                   ���x����
*                [IN] pDC
*                   CDCָ��
*                [IN] x
*                   ���x����
*                [IN] y
*                   ���y����
*                [IN] nDeta
*                   ����λ
*                [IN] dwDelayTime
*                   �ӳٵ�ʱ��
*  Return value: 
*                ����TRUE��ʾ��ʾ�ɹ�������FALSE��ʾʧ��
*====================================================
*
*/

BOOL CDib::Clear(int nEffect, CDC* pDC, int x, int y, int nDeta, DWORD dwDelayTime)
{
	if (nEffect == EFFECT_FADE)
		return DisplayFadeOut(pDC, x, y, nDeta, dwDelayTime);
	else if (nEffect == EFFECT_MOSAIC)
		return DisplayMosaicOut(pDC, x, y, nDeta, dwDelayTime);

	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBmp = MemDC.SelectObject(m_pBitmap);

	CPalette* pOldPal = pDC->SelectPalette(m_pPalette, TRUE);
    pDC->RealizePalette();

	pDC->BitBlt(x,
				y,
				GetWidth(),
				GetHeight(),
				&MemDC,
				0,
				0,
				SRCCOPY);

	CBrush brush(GetSysColor(COLOR_WINDOW));
	CBrush* oldbrush = pDC->SelectObject(&brush);
	CPen pen(PS_SOLID,1,GetSysColor(COLOR_WINDOW));
    CPen* oldpen = pDC->SelectObject(&pen);

	LONG i = 0;
	BOOL bDone = FALSE;
	while (! bDone)
	{
		switch (nEffect)
		{
		case EFFECT_SCANDOWN:
			if (i > GetHeight())
			{
				i = GetHeight();
				bDone = TRUE;
			}
			pDC->Rectangle(x, 
						   y+i,
						   x+GetWidth(), 
						   y+nDeta);
			i += nDeta;
			break;
		case EFFECT_SCANUP:
			if (i > GetHeight())
			{
				i = GetHeight();
				bDone = TRUE;
			}
			pDC->Rectangle(x, 
						   y+GetHeight()-i,
						   x+GetWidth(), 
						   y+GetHeight()-i+nDeta);
			i += nDeta;
			break;
		case EFFECT_SCANRIGHT:
			if (i > GetWidth())
			{
				i = GetWidth();
				bDone = TRUE;
			}
			pDC->Rectangle(x+i,
						   y,
						   x+nDeta, 
						   y+GetHeight());
			i += nDeta;
			break;
		case EFFECT_SCANLEFT:
			if (i > GetWidth())
			{
				i = GetWidth();
				bDone = TRUE;
			}
			pDC->Rectangle(x+GetWidth()-i, 
						   y,
						   x+GetWidth()-i+nDeta, 
						   y+GetHeight());
			i += nDeta;
			break;
		case EFFECT_VSPLITSCAN:
			if (i > GetHeight()/2)
			{
				i = GetHeight()/2;
				bDone = TRUE;
			}
			pDC->Rectangle(x, 
						   y+i,
						   x+GetWidth(), 
						   y+i+nDeta);
			pDC->Rectangle(x, 
						   y+GetHeight()-i,
						   x+GetWidth(), 
						   y+GetHeight());
			i += nDeta;
			break;
		case EFFECT_HSPLITSCAN:
			if (i > GetWidth()/2)
			{
				i = GetWidth()/2;
				bDone = TRUE;
			}
			pDC->Rectangle(x+i, 
						   y,
						   x+i+nDeta, 
						   y+GetHeight());
			pDC->Rectangle(x+GetWidth()-i,
						   y,
						   x+GetWidth(), 
						   y+GetHeight());
			i += nDeta;
			break;
		case EFFECT_MOVEDOWN:
		{
			i += nDeta;
			if (i > GetHeight())
			{
				i = GetHeight();
				bDone = TRUE;
			}
			pDC->BitBlt(x,  		
						y+i,		
      					GetWidth(),		
						GetHeight()-i,	
						&MemDC,
						0,				
						0,		
						SRCCOPY);

			pDC->Rectangle(x, y+i-nDeta,
						   x+GetWidth(), y+i);
			break;
		}
		case EFFECT_MOVEUP:
		{
			i += nDeta;
			if (i > GetHeight())
			{
				i = GetHeight();
				bDone = TRUE;
			}
			pDC->BitBlt(x,  			
						y,	
	      				GetWidth(),		
						GetHeight()-i,	
						&MemDC,
						0,				
						i,		
						SRCCOPY);

			pDC->Rectangle( x,
							y+GetHeight()-i,
							x+GetWidth(),
							y+GetHeight());
			break;
		}
		case EFFECT_MOVERIGHT:
		{
			i += nDeta;
			if (i > GetWidth())
			{
				i = GetWidth();
				bDone = TRUE;
			}
			pDC->BitBlt(x+i,  			
						y,	
      					GetWidth()-i,	
						GetHeight(),	
						&MemDC,
						0,			
						0,		
						SRCCOPY);

			pDC->Rectangle(x+i-nDeta, y,
						   x+i, y+GetHeight());
			break;
		}
		case EFFECT_MOVELEFT:
		{
			i += nDeta;
			if (i > GetWidth())
			{
				i = GetWidth();
				bDone = TRUE;
			}
			pDC->BitBlt(x,  			
						y,		
	      				GetWidth()-i,		
						GetHeight(),	
						&MemDC,
						i,		
						0,			
						SRCCOPY);

			pDC->Rectangle( x+GetWidth()-i,
							y,
							x+GetWidth(),
							y+GetHeight());
			break;
		}
		case EFFECT_VCROSSMOVE:
		{
			i += nDeta;
			if (i > GetHeight())
			{
				i = GetHeight();
				bDone = TRUE;
			}
			pDC->BitBlt(x,  		
						y+i,	
      					GetWidth()/2,	
						GetHeight()-i,
						&MemDC,
						0,			
						0,		
						SRCCOPY);

			pDC->Rectangle(x, y+i-nDeta,
						   x+GetWidth()/2, y+i);

			pDC->BitBlt(x+GetWidth()/2,  			
						y,	
	      				GetWidth(),		
						GetHeight()-i,	
						&MemDC,
						GetWidth()/2,			
						i,		
						SRCCOPY);

			pDC->Rectangle( x+GetWidth()/2,
							y+GetHeight()-i,
							x+GetWidth(),
							y+GetHeight());
			break;
		}
		case EFFECT_HCROSSMOVE:
		{
			i += nDeta;
			if (i > GetWidth())
			{
				i = GetWidth();
				bDone = TRUE;
			}
			pDC->BitBlt(x+i,  			
						y,		
      					GetWidth()-i,	
						GetHeight()/2,
						&MemDC,
						0,			
						0,			
						SRCCOPY);

			pDC->Rectangle(x+i-nDeta, y,
						   x+i, y+GetHeight()/2);
	
			pDC->BitBlt(x,  		
						y+GetHeight()/2,
	      				GetWidth()-i,		
						GetHeight(),
						&MemDC,
						i,			
						GetHeight()/2,
						SRCCOPY);

			pDC->Rectangle( x+GetWidth()-i,
							y+GetHeight()/2,
							x+GetWidth(),
							y+GetHeight());
			break;
		}
		case EFFECT_VSPLITMOVE:
		{
			i += nDeta;
			if (i > GetHeight()/2)
			{
				i = GetHeight()/2;
				bDone = TRUE;
			}
			pDC->BitBlt(x,  		
						y,	
			  			GetWidth(),		
						GetHeight()/2-i,	
						&MemDC,
						0,				
						i,			
						SRCCOPY);

			pDC->BitBlt(x,  		
						y+GetHeight()/2+i,	
      					GetWidth(),		
						GetHeight()/2-i,	
						&MemDC,
						0,			
						GetHeight()/2,		
						SRCCOPY);

			pDC->Rectangle( x,
							y+GetHeight()/2-i,
							x+GetWidth(),
							y+GetHeight()/2+i+1);
			break;
		}
		case EFFECT_HSPLITMOVE:
		{
			i += nDeta;
			if (i > GetWidth()/2)
			{
				i = GetWidth()/2;
				bDone = TRUE;
			}
			pDC->BitBlt(x,  		
						y,	
	      				GetWidth()/2-i,		
						GetHeight(),	
						&MemDC,
						i,			
						0,				
						SRCCOPY);

			pDC->BitBlt(x+GetWidth()/2+i,  			
						y,	
      					GetWidth()/2-i,	
						GetHeight(),
						&MemDC,
						GetWidth()/2,			
						0,		
						SRCCOPY);

			pDC->Rectangle( x+GetWidth()/2-i,
							y,
							x+GetWidth()/2+i+1,
							y+GetHeight());
			break;
		}
		case EFFECT_VRASTER:
		{
			if (i > GetHeight())
			{
				i = GetHeight();
				bDone = TRUE;
			}
			LONG j = 0;
			BOOL bQuitLoop = FALSE;
			while (! bQuitLoop)
			{
				if (j > GetWidth())
				{
					j = GetWidth();
					bQuitLoop = TRUE;
				}
				pDC->BitBlt(x+j,  		
							y+i,	
      						nDeta,	
							GetHeight()-i,
							&MemDC,
							j,			
							0,		
							SRCCOPY);

				pDC->Rectangle(x+j, y+i-1,
							   x+j+nDeta, y+i);
				j += nDeta;
				if (j > GetWidth())
				{
					j = GetWidth();
					bQuitLoop = TRUE;
				}
	
				pDC->BitBlt(x+j,  			
							y,	
				  			nDeta,		
							GetHeight()-i,	
							&MemDC,
							j,		
							i,				
							SRCCOPY);

				pDC->Rectangle( x+j,
								y+GetHeight()-i,
								x+j+nDeta,
								y+GetHeight());
				j += nDeta;
			}
			i++;
			break;
		}
		case EFFECT_HRASTER:
		{
			if (i > GetWidth())
			{
				i = GetWidth();
				bDone = TRUE;
			}
			LONG j = 0;
			BOOL bQuitLoop = FALSE;
			while (! bQuitLoop)
			{
				if (j > GetHeight())
				{
					j = GetHeight();
					bQuitLoop = TRUE;
				}
				pDC->BitBlt(x+i,  			
							y+j,	
      						GetWidth()-i,	
							nDeta,	
							&MemDC,
							0,				
							j,		
							SRCCOPY);
				pDC->Rectangle(x+i-1, y+j,
							   x+i, y+j+nDeta);
				j += nDeta;
				if (j > GetHeight())
				{
					j = GetHeight();
					bQuitLoop = TRUE;
				}
				pDC->BitBlt(x,  			
							y+j,	
				  			GetWidth()-i,		
							nDeta,	
							&MemDC,
							i,		
							j,				
							SRCCOPY);
				pDC->Rectangle( x+GetWidth()-i,
								y+j,
								x+GetWidth(),
								y+j+nDeta);
				j += nDeta;
			}
			i++;
			break;
		}
		case EFFECT_HBLIND:
		{
			if (i > nDeta)
			{
				i = nDeta;
				bDone = TRUE;
			}
			for (LONG j=i; j<GetHeight(); j+=nDeta)
				pDC->Rectangle( x,
								y+j,
								x+GetWidth(),
								y+j+1);
			i++;
			break;
		}
		case EFFECT_VBLIND:
			if (i > nDeta)
			{
				i = nDeta;
				bDone = TRUE;
			}
			for (LONG j=i; j<GetWidth(); j+=nDeta)
				pDC->Rectangle( x+j,
								y,
								x+j+1,
								y+GetHeight());
			i++;
			break;
		}	// end of switch
		Delay(dwDelayTime);
	}	// end of while

	MemDC.SelectObject(pOldBmp);
	pDC->SelectPalette(pOldPal, TRUE);

	return TRUE;
}

/*
*--------------------------------------------------------------------------------
*  CopyRect()
*  ����ָ��DIB�����ָ������
*  Parameter :  
*                [IN] rc
*                   ��������
*  Return value: 
*                ����TRUE��ʾ�ɹ�������FALSE��ʾʧ��
*====================================================
*
*/

HDIB CDib::CopyRect(CRect rc)
{
	return CropDIB(m_hDib, rc);
}

/*
*--------------------------------------------------------------------------------
*  CutRect()
*  ����ָ��DIB�����ָ������
*  Parameter :  
*                [IN] rc
*                   ��������
*  Return value: 
*                ����TRUE��ʾ�ɹ�������FALSE��ʾʧ��
*====================================================
*
*/

BOOL CDib::CutRect(CRect rc)
{
	HDIB hNewDib = CutDIB(m_hDib, rc);
	if (! hNewDib)
		return FALSE;

	//�ͷ�
	Destroy();
	m_hDib = hNewDib;

	return UpdateInternal();
}

/*
*--------------------------------------------------------------------------------
*  MergeDib����
*  �ں�ָ��DIB���󵽵�ǰDIB�γ�һ�µ�DIB
*  Parameter :  
*                [IN] hDib
*                   Ҫ�ںϵ�DIB����
*                [IN] ptTopLeft
*                   �ںϵ�װ�õ����ϵ�����
*  Return value: 
*                ����TRUE��ʾ�ɹ�������FALSE��ʾʧ��
*====================================================
*
*/
BOOL CDib::MergeDib(HDIB hDib, CPoint ptTopLeft)
{
	POINT pt;
	pt.x = ptTopLeft.x;
	pt.y = ptTopLeft.y;
	HDIB hNewDib = MergeDIB(m_hDib, hDib, pt);
	if (! hNewDib)
		return FALSE;

	Destroy();
	m_hDib = hNewDib;
	
	return UpdateInternal();
}

/*
*--------------------------------------------------------------------------------
*  Crop()
*  �޼�CDib���� 
*  Parameter :  
*                [IN] rc
*                   Ҫ�޼��ľ�����
*  Return value: 
*                 ����TRUE��ʾ�ɹ�������FALSE��ʾʧ��
*====================================================
*
*/

BOOL CDib::	Crop(CRect rc)
{
	HDIB hNewDib = CropDIB(m_hDib, rc);
	if (! hNewDib)
		return FALSE;

	Destroy();
	m_hDib = hNewDib;

	return UpdateInternal();
}

/*
*--------------------------------------------------------------------------------
*  Rotate()
*  ��ָ���Ƕ���תDIB����
*  Parameter :  
*                [IN] fDegrees
*                   �Ƕ�
*                [IN] clrBack
*                   ������ɫ
*  Return value: 
*                 ����TRUE��ʾ�ɹ�������FALSE��ʾʧ��
*====================================================
*
*/

BOOL CDib::Rotate(double fDegrees, COLORREF clrBack)
{
	HDIB hNewDib = RotateDIB(m_hDib, fDegrees, clrBack);
	if (! hNewDib)
		return FALSE;

	Destroy();
	m_hDib = hNewDib;

	return UpdateInternal();
}

/*
*--------------------------------------------------------------------------------
*  Rotate90()
*  ��ת90��DIB����
*  Parameter :  
*                ��
*  Return value: 
*                ����TRUE��ʾ�ɹ�������FALSE��ʾʧ��
*====================================================
*
*/

BOOL CDib::Rotate90()
{
	HDIB hNewDib = RotateDIB(m_hDib);
	if (! hNewDib)
		return FALSE;

	Destroy();
	m_hDib = hNewDib;

	return UpdateInternal();
}

/*
*--------------------------------------------------------------------------------
*  Rotate180()
*  ��ת180��DIB����
*  Parameter :  
*                ��
*  Return value: 
*                ����TRUE��ʾ�ɹ�������FALSE��ʾʧ��
*====================================================
*
*/

BOOL CDib::Rotate180()
{
	HDIB h = RotateDIB(m_hDib);
	if (! h)
		return FALSE;
	HDIB hNewDib = RotateDIB(h);
	DestroyDIB(h);
	if (! hNewDib)
		return FALSE;

	Destroy();
	m_hDib = hNewDib;

	return UpdateInternal();
}

/*
*--------------------------------------------------------------------------------
*  Rotate270()
*  ����CDib���� 
*  Parameter :  
*                ��
*  Return value: 
*                ����TRUE��ʾ�ɹ�������FALSE��ʾʧ��
*====================================================
*
*/

BOOL CDib::Rotate270()
{
	HDIB h1 = RotateDIB(m_hDib);
	if (! h1)
		return FALSE;
	HDIB h2 = RotateDIB(h1);
	DestroyDIB(h1);
	if (! h2)
		return FALSE;
	HDIB hNewDib = RotateDIB(h2);
	DestroyDIB(h2);
	if (! hNewDib)
		return FALSE;

	Destroy();
	m_hDib = hNewDib;

	return UpdateInternal();
}

/*
*--------------------------------------------------------------------------------
*  FlipHorz()
*  ˮƽ����
*  Parameter :  
*                ��
*  Return value: 
*                ����TRUE��ʾ�ɹ�������FALSE��ʾʧ��
*====================================================
*
*/

BOOL CDib::FlipHorz()
{
	HDIB hNewDib = FlipHorzDIB(m_hDib);
	if (! hNewDib)
		return FALSE;
	Destroy();
	m_hDib = hNewDib;

	return UpdateInternal();
}

/*
*--------------------------------------------------------------------------------
*  FlipVert()
*  ��ֱ���� 
*  Parameter :  
*                ��
*  Return value: 
*                ����TRUE��ʾ�ɹ�������FALSE��ʾʧ��
*====================================================
*
*/

BOOL CDib::FlipVert()
{
	HDIB hNewDib = FlipVertDIB(m_hDib);
	if (! hNewDib)
		return FALSE;

	Destroy();
	m_hDib = hNewDib;

	return UpdateInternal();
}

/*
*--------------------------------------------------------------------------------
*  ChangeImageSize()
*  ����CDib���� 
*  Parameter :  
*                [IN] nWidth
*                   ���
*                [IN] nHeight
*                   �߶�
*  Return value: 
*                TRUE OR FALSE
*====================================================
*
*/

BOOL CDib::	ChangeImageSize(int nWidth, int nHeight)
{
	HDIB hNewDib = ChangeDIBSize(m_hDib, nWidth, nHeight);
	if (! hNewDib)
		return FALSE;

	Destroy();
	m_hDib = hNewDib;

	return UpdateInternal();
}

/*
*--------------------------------------------------------------------------------
*  Zoom()
*  ����CDib���� 
*  Parameter :  
*                [IN] fRatioX
*                   X�����
*                [IN] fRatioY
*                   Y�����
*  Return value: 
*                TRUE OR FALSE
*==================================================== 
*
*/

BOOL CDib::Zoom(double fRatioX, double fRatioY)
{
	int nWidth = (int)(fRatioX * (double)GetWidth());
	int nHeight = (int)(fRatioY * (double)GetHeight());

	HDIB hNewDib = ChangeDIBSize(m_hDib, nWidth, nHeight);
	if (! hNewDib)
		return FALSE;

	Destroy();
	m_hDib = hNewDib;

	return UpdateInternal();
}

/*
*--------------------------------------------------------------------------------
*  ChangeCanvasSize()
*  ����CDib���� 
*  Parameter :  
*                [IN] nWidth
*                   ���
*                [IN] nHeight
*                   �߶�
*                [IN] nPosition
*                   λ��
*  Return value: 
*                TRUE OR FALSE
*====================================================
*
*/

BOOL CDib::	ChangeCanvasSize(int nWidth, int nHeight, int nPosition)
{
	HDIB hNewDib = ChangeDIBCanvasSize(m_hDib, nWidth, nHeight, nPosition);
	if (! hNewDib)
		return FALSE;

	Destroy();
	m_hDib = hNewDib;

	return UpdateInternal();
}

/*
*--------------------------------------------------------------------------------
*  Clone()
*  ����CDib���� 
*  Parameter :  
*                ��
*  Return value: 
*                ָ��CDib�����ָ��
*====================================================
*
*/

CDib * CDib::Clone()
{
	if (m_hDib == NULL)
		return NULL;

	HDIB hDIB = CopyHandle(m_hDib);
	if (hDIB == NULL)
		return NULL;

  	CDib *pDib = new CDib;
	pDib->m_hDib = hDIB;
	pDib->BuildPalette();
	pDib->BuildBitmap();

	return pDib;
}


/*
*--------------------------------------------------------------------------------
*  ������	: AdjustDibBrightness
*  ����		: ����DIBλͼ������
*  ����		: [in] int v	-	�����������ֵ
*  ����ֵ	: �ɹ�Ϊ TRUE, ����Ϊ FALSE
*  �㷨		: 
*===============================================================
*/
BOOL CDib::AdjustDibBrightness(int v)
{
	ASSERT(m_hDib);

	BITMAPINFO * bmi = (BITMAPINFO *) GlobalLock(m_hDib);
	if (!bmi)
		return FALSE;

	WORD wNumColors = DIBNumColors((LPBYTE)bmi);

	if (wNumColors)
	{
		for (WORD i = 0; i < wNumColors; i++)
		{
			ChangeBrightness(v,
							&(bmi->bmiColors[i].rgbRed),
							&(bmi->bmiColors[i].rgbGreen),
							&(bmi->bmiColors[i].rgbBlue));
		}
	}
	else
	{
		LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER) bmi;
		LPBYTE lpBits = (LPBYTE)lpbi + lpbi->biSize;
		int nDelta = WIDTHBYTES(lpbi->biBitCount * lpbi->biWidth)
					- lpbi->biWidth * lpbi->biBitCount / 8;
		BYTE r, g, b;
		for (int ny = 0; ny < lpbi->biHeight; ny++)
		{
			for (int nx = 0; nx < lpbi->biWidth; nx++)
			{
				b = (BYTE) *(lpBits);
				g = (BYTE) *(lpBits + 1);
				r = (BYTE) *(lpBits + 2);
				ChangeBrightness(v, &r, &g, &b);
				*lpBits++ = b;
				*lpBits++ = g;
				*lpBits++ = r;
			}
			lpBits += nDelta;
		}
	}

	GlobalUnlock(m_hDib);

	return TRUE;
}


/*
*--------------------------------------------------------------------------------
*  ������	: ChangeBrightness
*  ����		: �������ص������
*  ����		: [in] int nDelta	-	r,g,b �����ı仯ֵ
*				[in, out] BYTE* r	-	���ص���ɫ r ����ֵ
*				[in, out] BYTE* g	-	���ص���ɫ g ����ֵ
*				[in, out] BYTE* b	-	���ص���ɫ b ����ֵ
*  �㷨		: 
*===============================================================
*/
void CDib::ChangeBrightness(int nDelta, BYTE *r, BYTE *g, BYTE *b)
{
	int R = * r + nDelta;
	int G = *g + nDelta;
	int B = *b + nDelta;

	*r = (BYTE) BOUND(R, 0, 255);
	*g = (BYTE) BOUND(G, 0, 255);
	*b = (BYTE) BOUND(B, 0, 255);
}

//�仯DIBͼ�ε���ɫλ��
BOOL CDib::ChangeCanvasBit(INT colBit)
{
	CDib newDib;
	newDib.Create(m_hBitmap,colBit);
	if(newDib.GetHandle()==NULL)
	{
		return FALSE;
	}

//	m_hDib = newDib.m_hDib;
//	return UpdateInternal();

    if(!Create(newDib.m_hBitmap, colBit))
		TRACE("������ɫλ��ʧ��\n");
    
	return UpdateInternal();

}

//�õ�λͼ��� 
HBITMAP CDib::GetHBitmap()
{
   return m_hBitmap;
}
