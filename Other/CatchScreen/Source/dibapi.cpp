/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��DIBAPI.CPP
* �汾��  ��V1.0
* ��Ŀ���ƣ�CPH
* ��Ȩ������Copyright 2002-2003 . All Rights Reserved.
* ģ���������DIBͼ�δ���API������ģ���ļ�����
*======================================================
* �汾�����¼:
*      v1.0  2002-11-11  
*
* 
*/

 //ʹ�ϸ�����Ч
   
 
#include "stdafx.h"
#include <string.h> 
#include <stdio.h> 
#include <math.h> 
#include <io.h> 
#include <direct.h> 
#include <stdlib.h> 
#include <assert.h> 
#include <windows.h> 
#include <windowsx.h> 
#include <mmsystem.h> 
#include "..\Include\dibapi.h" 

 
/************************************************************************* 
 * ������: CreateDIB() 
 * 
 * ����: 
 * 
 * DWORD dwWidth    - ��λͼ�Ŀ��(����) 
 * DWORD dwHeight   - ��λͼ�ĸ߶�(����)  
 * WORD  wBitCount  - ��DIB��λ�� (1, 4, 8, �� 24λ) 
 * 
 * ����ֵ: 
 * 
 * HDIB             -�½�DIB �ľ��
 * 
 * ����: 
 * 
 * ���������ʹ��һ���µ�DIB�������ڴ濿���DIB��λͼ��Ϣͷ�ṹ��
 * BITMAPINFOHEADER, Ϊ��ɫ������ڴ沢Ϊ���bitmapλ�����ڴ�. 
 * ���ͷ��Ϣ����ɫ���λ���ж�λ���ڽ����ڴ����. �������ͬ
 * DDB��CreateBitmap() Windows API�������ơ� 
 * �����ɫ���λͼλû�б���ʼ������Ϊ0 
 * 
 ************************************************************************/ 

HDIB CreateDIB(DWORD dwWidth, DWORD dwHeight, WORD wBitCount) 
{ 
    // DIBλͼ�ļ���ͷ�ṹ 
    BITMAPINFOHEADER    bi;    
    // DIBλͼ��Ϣͷ�ṹ 
    LPBITMAPINFOHEADER  lpbi;      
    // �ڴ���С
    DWORD               dwLen; 

    HDIB                hDIB; 
    //ÿɨ�����ֽ���
    DWORD               dwBytesPerLine;
 
 
    //ȷ��ÿ����λ����Ч��
 
    if (wBitCount <= 1) 
        wBitCount = 1; 
    else if (wBitCount <= 4) 
        wBitCount = 4; 
    else if (wBitCount <= 8) 
        wBitCount = 8; 
    else if (wBitCount <= 24) 
        wBitCount = 24; 
    else 
        // ����Ĭ�ϵ�ֵ��4λ��16ɫ��������������Ч��
        wBitCount = 4;
 
    // ��ʼ��INFOHEADER 
     //���ṹ��С���ֽ� ��
    bi.biSize = sizeof(BITMAPINFOHEADER);   
	// λͼ�Ŀ�ȣ��������룩 
    bi.biWidth = dwWidth;				
	// λͼ�ĸ߶ȣ��������룩
    bi.biHeight = dwHeight;			
	//������1 
    bi.biPlanes = 1;				
	//���ص�λ��(��������) 
    bi.biBitCount = wBitCount;			
    //ѹ����ʽ
    bi.biCompression = BI_RGB;				
	//λͼ�����ֽ���(0ΪĬ����)
    bi.biSizeImage = 0;					
	//ˮƽ�ֱ��ʣ����ص�/�ף�
    bi.biXPelsPerMeter = 0;				
	//��ֱ�ֱ��ʣ����ص�/�ף�
    bi.biYPelsPerMeter = 0;				
    //ͼ����ʹ�õ���ɫ��
    bi.biClrUsed = 0;						
    //ͼ������Ҫ������ɫ��
    bi.biClrImportant = 0;					
 
    // �����ڴ��Ĵ�С���뱣�����DIB.�����Ӧ�����㹻���  This 
    dwBytesPerLine = WIDTHBYTES1(wBitCount * dwWidth); 
    dwLen = bi.biSize + PaletteSize((LPBYTE)&bi) + (dwBytesPerLine * dwHeight); 
 
    // �����ڴ��ͱ���λͼ
     hDIB = GlobalAlloc(GHND, dwLen); 
     if (!hDIB) 
        return NULL; 
 
    // �����ڴ��͵õ�����ָ��
 
    lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB); 
 
    //ʹ�������λͼ��Ϣ�ṹ BITMAPINFOHEADER ���DIB�ĵ�һ���� BITMAPINFOHEADER 
 
    *lpbi = bi; 
 
    // ��Ϊ���ǲ�֪�����ɫ�ʱ��λ������, 
    // �����Ƴ���Щ�հ�.  ����DIB�ڴ��ͷ���HDIB����. 
 
    GlobalUnlock(hDIB); 
 
    return hDIB; 
} 

 
/************************************************************************* 
 * ������:CreateDefaultDIB() 
 * 
 * ����: 
 * 
 * DWORD dwWidth    - ��λͼ�Ŀ��(����)  
 * DWORD dwHeight   - ��λͼ�ĸ߶�(����)   
 * 
 * ����ֵ: 
 * 
 * HDIB             - ��DIB�ľ�� 
 * 
 * ����: 
 * 
 *����������ָ��ʵ�ϵĲ�������һ���µ�DIBλͼ�����ƴ���DDB��CreateBitmap()  API����
 *DIB������ɫ������ϵͳ��ɫ����������λͼ��λ����δ����ʼ����Ϊ0
 * 
 ************************************************************************/ 
HDIB CreateDefaultDIB(DWORD dwWidth, DWORD dwHeight) 
{ 
	// �õ� DC
    HDC hDC = GetDC(NULL); 
    if (!hDC) 
        return NULL; 

	// DC bts/����
	int nDeviceBitsPixel = GetDeviceCaps(hDC, BITSPIXEL);

	//  ����DC����DIB 
	HDIB hDIB = CreateDIB(dwWidth, dwHeight, nDeviceBitsPixel);

	// DIB������
	LPBITMAPINFO lpbmi = (LPBITMAPINFO)GlobalLock(hDIB);
    LPBYTE lpDIBBits = FindDIBBits((LPBYTE)lpbmi); 
    DWORD dwBitsSize = lpbmi->bmiHeader.biHeight * BytesPerLine((LPBYTE)&(lpbmi->bmiHeader)); 

	// ���� DIB��ɫΪ��ɫ
	for (DWORD l=0; l<dwBitsSize; ++l)
		lpDIBBits[l] = 0xff;

	// ����û�е�ɫ��, ����DIB���
	if (nDeviceBitsPixel > 8)
	{
		GlobalUnlock(hDIB);
	    ReleaseDC(NULL, hDC); 
		return hDIB;
	}

	// ���ǵ�ɫ��,����ϵͳ��ɫ�嵽DIB

	// ϵͳ��ɫ���е���ɫ
    int nColors = PalEntriesOnDevice(hDC);   // ɫ����
  
    // ����ϵͳ��ɫ�嵽���ǵ��߼���ɫ��
	PALETTEENTRY pe[256];
    GetSystemPaletteEntries(hDC, 0, nColors, pe); 

	//������ɫ��
	for (int i=0; i<nColors; ++i)
	{
		lpbmi->bmiColors[i].rgbRed = pe[i].peRed;
		lpbmi->bmiColors[i].rgbGreen = pe[i].peGreen;
		lpbmi->bmiColors[i].rgbBlue = pe[i].peBlue;
		lpbmi->bmiColors[i].rgbReserved = 0;
	}

    // ���
	GlobalUnlock(hDIB);
    ReleaseDC(NULL, hDC); 

	return hDIB;
}

/************************************************************************* 
 * ������DestroyDIB () 
 * ��������
 * �������ͷ�ΪDIB������ڴ� 
 * ����ֵ���� 
 * 
 *************************************************************************/ 
void DestroyDIB(HDIB hDib) 
{ 
    GlobalFree(hDib); 
} 


/************************************************************************* 
 * ����:  ReadDIBFile () 
 * ����:
 * HANDLE hFile -ָ��DIB���ݻ������ľ��
 * 
 * ����: 
 * ��ָ����DIB�ļ����ڴ���
 * 
 * ����ֵ:  
 * �ɹ�����һ��hDIB���,���򷵻�NULL 
 * 
 * ע��: 
 * ���������֧��OS/2��DIB
 * 
 *************************************************************************/ 
HANDLE ReadDIBFile(HANDLE hFile) 
{ 
    BITMAPFILEHEADER    bmfHeader; 
    DWORD               dwBitsSize; 
     // ��ɫ��������    
    UINT             nNumColors;  
    HANDLE              hDIB;     
    // ʹ��Ϊ GlobalRealloc() //MPB 
    HANDLE              hDIBtmp; 
    LPBITMAPINFOHEADER  lpbi; 
    DWORD               offBits; 
    DWORD               dwRead; 
 
    //�����ļ�ʱ�õ�DIB�ĳ����ֽ� 
 
    dwBitsSize = GetFileSize(hFile, NULL); 
 
    // Ϊͷ & ��ɫ������ڴ�.���Ŵ��ڴ浽������Ҫ��

    hDIB = GlobalAlloc(GMEM_MOVEABLE, (DWORD)(sizeof(BITMAPINFOHEADER) + 
            256 * sizeof(RGBQUAD))); 
 
    if (!hDIB) 
        return NULL; 
 
    lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB); 
 
    if (!lpbi)  
    { 
        GlobalFree(hDIB); 
        return NULL; 
    } 
 
    // ���ļ��ж��� BITMAPFILEHEADER ͷ�ṹ 
 
    if (!ReadFile(hFile, (LPBYTE)&bmfHeader, sizeof (BITMAPFILEHEADER), 
            &dwRead, NULL)) 
        goto ErrExit; 
 
    if (sizeof (BITMAPFILEHEADER) != dwRead) 
        goto ErrExit; 
    // 'BM' 
    if (bmfHeader.bfType != 0x4d42)  
        goto ErrExit; 
 
    //����BITMAPINFOHEADER �ṹ
 
    if (!ReadFile(hFile, (LPBYTE)lpbi, sizeof(BITMAPINFOHEADER), &dwRead, 
            NULL)) 
        goto ErrExit; 
 
    if (sizeof(BITMAPINFOHEADER) != dwRead) 
        goto ErrExit; 
 
    // ����Ƿ���Windows DIB --  OS/2 DIB ���ļ�ͷ��ͷ��ṹ�ǲ�ͬ��
    // ������Windows DIB (e.g. ��ṹ���С�Ǵ����),����NULL
 
    if (lpbi->biSize == sizeof(BITMAPCOREHEADER)) 
        goto ErrExit; 
 
    // ���ھ�����ɫ��ĳߴ�Ͷ�����. 
    // ��Ϊ����ļ���fOffBitsƫ����, ��Ҫ��һЩ�ر�Ĵ����Ա�֤��Щλ
    // ֱ�Ӹ�����ɫ��
 
    if (!(nNumColors = (UINT)lpbi->biClrUsed)) 
    { 
        // 24-bit���ɫû����ɫ��,����ΪĬ�ϳߴ� 
         //(lpbi->biBitCount != 24) // ��׼��С�� 
        if (lpbi->biBitCount > 8)	
            nNumColors = 1 << lpbi->biBitCount; 
    } 
 
    // ��Ϊ0������һЩĬ��ֵ 
 
    if (lpbi->biClrUsed == 0) 
        lpbi->biClrUsed = nNumColors; 
 
    if (lpbi->biSizeImage == 0) 
    { 
        lpbi->biSizeImage = ((((lpbi->biWidth * (DWORD)lpbi->biBitCount) + 
                31) & ~31) >> 3) * lpbi->biHeight; 
    } 
 
    //Ϊͷ�õ��ʵ���С�Ļ�����,��ɫ�������λ 
 
    GlobalUnlock(hDIB); 
    hDIBtmp = GlobalReAlloc(hDIB, lpbi->biSize + nNumColors * 
            sizeof(RGBQUAD) + lpbi->biSizeImage, 0); 

    // ����ʱ���ܵ����������Ĵ�С
    if (!hDIBtmp) 
        goto ErrExitNoUnlock; //MPB 
    else 
        hDIB = hDIBtmp; 
 
    lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB); 
 
    // ������ɫ��
 
    ReadFile (hFile, (LPBYTE)(lpbi) + lpbi->biSize, 
            nNumColors * sizeof(RGBQUAD), &dwRead, NULL); 
 
    // �ӿ�ʼ��DIBͷƫ������λ 
 
    offBits = lpbi->biSize + nNumColors * sizeof(RGBQUAD); 
 
    // �� bfOffBits��ǿ�, ��ʱ����λ����ֱ�Ӹ�������ɫ���
    // ʹ�ò�����Щ����λ
 
    if (bmfHeader.bfOffBits != 0L) 
        SetFilePointer(hFile, bmfHeader.bfOffBits, NULL, FILE_BEGIN); 
 
    if (ReadFile(hFile, (LPBYTE)lpbi + offBits, lpbi->biSizeImage, &dwRead, 
            NULL)) 
        goto OKExit; 
 
ErrExit: 
    GlobalUnlock(hDIB);     
 
ErrExitNoUnlock:     
    GlobalFree(hDIB); 
    return NULL; 
 
OKExit: 
    GlobalUnlock(hDIB); 
    return hDIB; 
} 


/************************************************************************* 
 * ��������LoadDIB() 
 * ������
 * LPCTSTR lpFileName - ָ��Ҫװ�ص�DIBԴ�ļ� 
 *
 * ������
 * �������ָ����DIBԴ�ļ�,��Ϊ�������ڴ�,�Ӵ����ļ�װ�ض����ڴ��� 
 *
 * ����ֵ:
 * HANDLE - ָ��DIB���ݻ������ľ��,�������ɹ�����NULL. 
 * 
 * ע�⣺��������֧��OS/2 ��DIB;
 * 
 *************************************************************************/ 
HDIB LoadDIB(LPCTSTR lpFileName) 
{ 
    HDIB        hDIB; 
    HANDLE      hFile; 
 
    // ���õȴ�ɳ©����Ա㵼���ļ� 
 //   SetCursor(LoadCursor(NULL, IDC_WAIT)); 
     SetCursor(AfxGetApp()->LoadCursor(IDC_WAIT)); 
    if ((hFile = CreateFile(lpFileName, GENERIC_READ, FILE_SHARE_READ, NULL, 
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, 
            NULL)) != INVALID_HANDLE_VALUE) 
    { 
        hDIB = ReadDIBFile(hFile); 
        CloseHandle(hFile); 
     //   SetCursor(LoadCursor(NULL, IDC_ARROW)); 
        SetCursor(AfxGetApp()->LoadCursor(IDC_ARROW)); 
        return hDIB; 
    } 
    else 
    { 
       // SetCursor(LoadCursor(NULL, IDC_ARROW)); 
         SetCursor(AfxGetApp()->LoadCursor(IDC_ARROW)); 
        return NULL; 
    } 
} 

 
 
/************************************************************************* 
 * ����:SaveDIB() 
 * ����: 
 * HDIB hDib - Ҫ�����DIB���ڴ��� 
 * LPCTSTR lpFileName - �洢DIB���ļ�������·���� 
 *
 * ����:
 * ��ָ�����ļ����������ָ����DIB������,���ļ��Ѿ������򸲸���  
 * 
 * ����ֵ:
 * TRUE-����ɹ�
 * FALSE-����ʧ��
 * 
 *************************************************************************/ 

BOOL SaveDIB(HDIB hDib, LPCTSTR lpFileName) 
{ 
    BITMAPFILEHEADER    bmfHdr;     
    LPBITMAPINFOHEADER  lpBI;       
    HANDLE              fh;         
    DWORD               dwDIBSize; 
    DWORD               dwWritten; 
 
    if (!hDib) 
        return FALSE; 
 
    fh = CreateFile(lpFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 
            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL); 
 
    if (fh == INVALID_HANDLE_VALUE) 
        return FALSE; 
 
    //�õ�һ��ָ��DIB�ڴ��ָ��,��ʼʱ����BITMAPINFO�ṹ��Ϣ 
    lpBI = (LPBITMAPINFOHEADER)GlobalLock(hDib); 
    if (!lpBI) 
    { 
        CloseHandle(fh); 
        return FALSE; 
    } 
 
    // ����Ƿ�ʹ�� OS/2 DIB.   
    if (lpBI->biSize != sizeof(BITMAPINFOHEADER)) 
    { 
        GlobalUnlock(hDib); 
        CloseHandle(fh); 
        return FALSE; 
    } 
 
    // ����ļ�ͷ����(��λͼ��ʼ�����ֽڱ���Ϊ"BM" ) 
 
    bmfHdr.bfType = DIB_HEADER_MARKER;  // "BM" 
 
    //����DIB�ĳߴ� 
 
    // �ֲ�����
     dwDIBSize = *(LPDWORD)lpBI + PaletteSize((LPBYTE)lpBI);   
 
    //����λͼ���ݳߴ� ��REL����λͼ��
    if ((lpBI->biCompression == BI_RLE8) || (lpBI->biCompression == BI_RLE4)) 
        dwDIBSize += lpBI->biSizeImage; 
    else 
    { 
        DWORD dwBmBitsSize;  
 
        //��RLEλͼ,�ߴ�Ϊ��*�� 
 
        dwBmBitsSize = WIDTHBYTES1((lpBI->biWidth)*((DWORD)lpBI->biBitCount)) * 
                lpBI->biHeight; 
 
        dwDIBSize += dwBmBitsSize; 
        lpBI->biSizeImage = dwBmBitsSize; 
    } 
 
 
    //�����ļ��ĳߴ翿����DIB�ߴ絽(BITMAPFILEHEADER) 
                    
    bmfHdr.bfSize = dwDIBSize + sizeof(BITMAPFILEHEADER); 
    bmfHdr.bfReserved1 = 0; 
    bmfHdr.bfReserved2 = 0; 
 
    // ����λͼλ��ƫ�ƣ� λͼ�ļ�ͷ����DIBͷ������ɫ��ͷ�ߴ�. 
     
    bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + lpBI->biSize + 
            PaletteSize((LPBYTE)lpBI); 
 
    //д�ļ�ͷ 
     WriteFile(fh, (LPBYTE)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL); 
 
    // дDIBͷ��λ --ʹ���߼����꣬��˿�д������ݿ��Գ���32767�ֽ�     
    WriteFile(fh, (LPBYTE)lpBI, dwDIBSize, &dwWritten, NULL); 
 
    GlobalUnlock(hDib); 
    CloseHandle(fh); 
 
    if (dwWritten == 0) 
        return FALSE; 
    else 
        return TRUE;  
} 
 
/************************************************************************* 
 * ����:FindDIBBits() 
 * 
 * ����: 
 * LPBYTE lpDIB      - DIB �ڴ��ָ��
 * 
 * ����ֵ:
 * LPBYTE            - DIB����λָ�� 
 *
 * ����: 
 * �����������DIB����λ�ĵ�ַ�ͷ�������λ��ָ��
 * 
 ************************************************************************/ 
LPBYTE FindDIBBits(LPBYTE lpDIB) 
{ 
   return (lpDIB + *(LPDWORD)lpDIB + PaletteSize(lpDIB)); 
} 

 
/************************************************************************* 
 * ����:DIBWidth() 
 * 
 * ����: 
 * LPBYTE lpDIB      - DIB�ڴ��ָ�� 
 * 
 * ����ֵ: 
 * DWORD            - DIB �Ŀ��
 * 
 * ����: 
 * ���������BITMAPINFOHEADER�ṹ������DIB�Ŀ�� (Windows 3.0����) 
 * ���BITMAPCOREHEADER�ṹ������DIB���(OS/2����). 
 * 
 ************************************************************************/ 
DWORD DIBWidth(LPBYTE lpDIB) 
{ 
	// Win 3.0-���� DIB 
    LPBITMAPINFOHEADER   lpbmi;  
     // OS/2-����DIB 
    LPBITMAPCOREHEADER   lpbmc;  
 
    // ָ��ͷ (Win 3.0��OS/2) 
     lpbmi = (LPBITMAPINFOHEADER)lpDIB; 
     lpbmc = (LPBITMAPCOREHEADER)lpDIB; 
 
    // ����DIB���(Win 3.0 DIB) 
     if (lpbmi->biSize == sizeof(BITMAPINFOHEADER)) 
        return lpbmi->biWidth; 
    // ����DIB���( OS/2 DIB) 
    else  
        return (DWORD)lpbmc->bcWidth; 
} 


DWORD DIBWidth(HDIB hDIB) 
{ 
	LPBYTE lpDIB = (LPBYTE)GlobalLock(hDIB);
	DWORD dw = DIBWidth(lpDIB);
	GlobalUnlock(hDIB);
	return dw;
} 
 
/************************************************************************* 
 * ����:DIBHeight() 
 * 
 * ����:
 * 
 * LPBYTE lpDIB      - DIB�ڴ��ָ��
 * 
 * ����ֵ
 * DWORD            - DIB�߶�
 * 
 * ����:
 * ���������BITMAPINFOHEADER�ṹ������DIB�ĸ߶� (Windows 3.0����) 
 * ���BITMAPCOREHEADER�ṹ������DIB�߶�(OS/2����). 
 * 
 ************************************************************************/ 
DWORD DIBHeight(LPBYTE lpDIB) 
{ 

   //ָ��Win3.0-����DIB 
   LPBITMAPINFOHEADER   lpbmi;  
    //ָ��OS/2-����DIB 
   LPBITMAPCOREHEADER   lpbmc;  
 
   //ָ��ͷ (OS/2�� Win 3.0 )
    lpbmi = (LPBITMAPINFOHEADER)lpDIB; 
   lpbmc = (LPBITMAPCOREHEADER)lpDIB; 
 
    // ���� DIB�߶�(Win 3.0 DIB )
    if (lpbmi->biSize == sizeof(BITMAPINFOHEADER)) 
        return lpbmi->biHeight; 
    else  //����DIB�߶�(OS/2 DIB) 
        return (DWORD)lpbmc->bcHeight; 
} 
 
DWORD DIBHeight(HDIB hDIB) 
{ 
	LPBYTE lpDIB = (LPBYTE)GlobalLock(hDIB);
	DWORD dw = DIBHeight(lpDIB);
	GlobalUnlock(hDIB);
	return dw;
} 

 
/************************************************************************* 
 * ����:PaletteSize() 
 * 
 * ����: 
 * LPBYTE lpDIB      - DIB�ڴ��ָ��
 * 
 * ����ֵ: 
 * WORD             - DIB��ɫ��ĳߴ�
 * 
 * ����:  
 * ����������Եõ���Ҫ�����DIB�ĵ�ɫ��ĳߴ� =
 * RGBQUAD������ɫ��(Windows 3.0-���͵�DIB)
 * ������RGBTRIPLE�ĳߴ� (OS/2-���͵�DIB). 
 * 
 ************************************************************************/ 
WORD PaletteSize(LPBYTE lpDIB) 
{ 
    // ���㱻��ɫ����Ҫ�ĳߴ�
    if (IS_WIN30_DIB (lpDIB)) 
        return (DIBNumColors(lpDIB) * sizeof(RGBQUAD)); 
    else 
        return (DIBNumColors(lpDIB) * sizeof(RGBTRIPLE)); 
} 
 
WORD PaletteSize(HDIB hDIB) 
{ 
	LPBYTE lpDIB = (LPBYTE)GlobalLock(hDIB);
	WORD wSize = PaletteSize(lpDIB);
	GlobalUnlock(hDIB);
	return wSize;
} 

 
/************************************************************************* 
 * 
 * ������:DIBNumColors() 
 * 
 * ����: 
 * 
 * LPBYTE lpDIB      - ָ��һ������DIB�ڴ�Ŀ� 
 * 
 * Return Value: 
 * 
 * WORD             - ��ɫ������ɫ������
 * 
 * ����: 
 * 
 * �������������ɫ���е���ɫ���������DIB��ÿһ���أ�1: colors=2,  4: colors=16, if 8: colors=256, 
 *  ��24λλͼ����ɫ��. 
 * 
 ************************************************************************/ 
WORD DIBNumColors(LPBYTE lpDIB) 
{ 
    // DIBλ���� 
	WORD wBitCount;  
 
    // ����� Windows����DIB, ��ɫ������ɫ���е������������������  
 
    if (IS_WIN30_DIB(lpDIB)) 
    { 
        DWORD dwClrUsed; 
 
        dwClrUsed = ((LPBITMAPINFOHEADER)lpDIB)->biClrUsed; 
        if (dwClrUsed) 
 
        return (WORD)dwClrUsed; 
    } 
 
    // �������ÿ���ص���ɫ����     
    if (IS_WIN30_DIB(lpDIB)) 
        wBitCount = ((LPBITMAPINFOHEADER)lpDIB)->biBitCount; 
    else 
        wBitCount = ((LPBITMAPCOREHEADER)lpDIB)->bcBitCount; 
 
    switch (wBitCount) 
    { 
        case 1: 
            return 2; 
 
        case 4: 
            return 16; 
 
        case 8: 
            return 256; 
 
        default: 
            return 0; 
    } 
} 

/************************************************************************* 
 * 
 * ������:DIBNumColors() 
 *
 * ����: ����DIB��ɫ����
 * ����: 
 * HDIB hDIB- DIB���
 *    
 * ����ֵ��DIB��ɫ���� 
 ************************************************************************/ 
WORD DIBNumColors(HDIB hDIB) 
{ 
	LPBYTE lpDIB = (LPBYTE)GlobalLock(hDIB);
	WORD wSize = DIBNumColors(lpDIB);
	GlobalUnlock(hDIB);
	return wSize;
} 


/************************************************************************* 
 * 
 * ������:DIBBitCount() 
 *
 * ����: ����DIBͼ��λ��
 * ����: 
 * LPBYTE lpDIB- ָ��BITMAPINFOHEADER �ṹ��ָ��
 *    
 * ����ֵ��DIB��ɫ���� 
 ************************************************************************/ 
WORD DIBBitCount(LPBYTE lpDIB) 
{ 
    if (IS_WIN30_DIB(lpDIB)) 
        return ((LPBITMAPINFOHEADER)lpDIB)->biBitCount; 
    else 
        return ((LPBITMAPCOREHEADER)lpDIB)->bcBitCount; 
} 


/************************************************************************* 
 * 
 * ������:DIBBitCount() 
 *
 * ����: ����DIBλ��
 * ����: 
 * HDIB hDIB- DIB���
 *    
 * ����ֵ��DIB��ɫ���� 
 ************************************************************************/ 
WORD DIBBitCount(HDIB hDIB) 
{ 
	LPBYTE lpDIB = (LPBYTE)GlobalLock(hDIB);
	WORD wSize = DIBBitCount(lpDIB);
	GlobalUnlock(hDIB);
	return wSize;
} 
 
/************************************************************************* 
 * 
 * ������:BytesPerLine() 
 *
 * ����: ����ÿɨ���е��ֽ�λ��
 * ����: 
 * LPBYTE lpDIB - ָ��BITMAPINFOHEADER �ṹ��ָ��
 *    
 * ����ֵ��ÿɨ���е��ֽ����� 
 ************************************************************************/  
DWORD BytesPerLine(LPBYTE lpDIB) 
{ 
    return WIDTHBYTES1(((LPBITMAPINFOHEADER)lpDIB)->biWidth * ((LPBITMAPINFOHEADER)lpDIB)->biPlanes * ((LPBITMAPINFOHEADER)lpDIB)->biBitCount); 
} 

/************************************************************************* 
 * 
 * ������:BytesPerLine() 
 *
 * ����: ����ÿɨ���е��ֽ�λ��
 * ����: 
 * HDIB hDIB - DIB����
 *    
 * ����ֵ��ÿɨ���е��ֽ����� 
 ************************************************************************/ 
DWORD BytesPerLine(HDIB hDIB) 
{ 
	LPBYTE lpDIB = (LPBYTE)GlobalLock(hDIB);
	DWORD dw = BytesPerLine(lpDIB);
	GlobalUnlock(hDIB);
	return dw;
} 

/************************************************************************* 
 * 
 * ������:DIBlockSize() 
 *
 * ����: ����DIB��ÿɨ���е��ֽ�λ��
 * ����: 
 * HDIB hDIB - DIB����
 *    
 * ����ֵ��ÿɨ���е��ֽ����� 
 ************************************************************************/ 
DWORD DIBlockSize(LPBYTE lpDIB)
{
	if (((LPBITMAPINFOHEADER)lpDIB)->biSizeImage == 0)
		((LPBITMAPINFOHEADER)lpDIB)->biSizeImage = BytesPerLine(lpDIB) * ((LPBITMAPINFOHEADER)lpDIB)->biHeight;
	return ((LPBITMAPINFOHEADER)lpDIB)->biSize + PaletteSize(lpDIB) + ((LPBITMAPINFOHEADER)lpDIB)->biSizeImage;
}


/************************************************************************* 
 * 
 * ������:DIBlockSize() 
 *
 * ����: ����DIB��ÿɨ���е��ֽ�λ��
 * ����: 
 * LPBYTE lpDIB - ָ��BITMAPINFOHEADER �ṹ��ָ��
 *    
 * ����ֵ��ÿɨ���е��ֽ����� 
 ************************************************************************/
DWORD DIBlockSize(HDIB hDIB) 
{ 
	LPBYTE lpDIB = (LPBYTE)GlobalLock(hDIB);
	DWORD dw = DIBlockSize(lpDIB);
	GlobalUnlock(hDIB);
	return dw;
} 


 /************************************************************************* 
 * 
 * ������:CreateDIBPalette()  
 *
 * ����: ����DIB��ɫ��
 * ����: 
 * 
 * LPBYTE lpbi       - ָ����DIB 
 *    
 * ����ֵ�������ĵ�ɫ��
 ************************************************************************/
HPALETTE CreateDIBPalette(LPBYTE lpbi) 
{ 
    // ָ��һ���߼���ɫ���
    LPLOGPALETTE        lpPal;  
	// �߼���ɫ�����
    HANDLE              hLogPal;        
    HPALETTE            hPal = NULL;    
    // ��ɫ���е���ɫ����
    int                 i, wNumColors;  
	// ָ��BITMAPINFO�ṹ(Win3.0) 
    LPBITMAPINFO        lpbmi;  
	 // ָ��BITMAPCOREINFO�ṹ(OS/2) 
    LPBITMAPCOREINFO    lpbmc;         
    BOOL                bWinStyleDIB;  
 
    //��������д���NULL 
 
    if (! lpbi) 
        return NULL; 
 
    //�õ�BITMAPINFOָ�� (Win 3.0) 
     lpbmi = (LPBITMAPINFO)lpbi; 
 
    //�õ�BITMAPCOREINFO (OS/2 1.x)ָ�� 
     lpbmc = (LPBITMAPCOREINFO)lpbi; 
 
    // �õ�DIB��ɫ����  
     wNumColors = DIBNumColors(lpbi); 
 
    // �� Win 3.0 DIB? 
     bWinStyleDIB = IS_WIN30_DIB(lpbi); 
    if (wNumColors) 
    { 
        // Ϊ�߼���ɫ������ڴ�
         hLogPal = GlobalAlloc(GHND, sizeof(LOGPALETTE) + 
                sizeof(PALETTEENTRY) * wNumColors); 
 
        // �����㹻�ڴ� 
        if (!hLogPal) 
            return NULL; 
 
        //�����ڴ��ָ����
         lpPal = (LPLOGPALETTE)GlobalLock(hLogPal); 
 
        //���õ�ɫ��������Ͱ汾
         lpPal->palVersion = PALVERSION; 
        lpPal->palNumEntries = wNumColors; 
 
        // ����RGB(Win 3.0 DIB)�� RGB quads (if OS/2 DIB)      
        for (i = 0; i < wNumColors; i++) 
        { 
            if (bWinStyleDIB) 
            { 
                lpPal->palPalEntry[i].peRed = lpbmi->bmiColors[i].rgbRed; 
                lpPal->palPalEntry[i].peGreen = lpbmi->bmiColors[i].rgbGreen; 
                lpPal->palPalEntry[i].peBlue = lpbmi->bmiColors[i].rgbBlue; 
                lpPal->palPalEntry[i].peFlags = 0; 
            } 
            else 
            { 
                lpPal->palPalEntry[i].peRed = lpbmc->bmciColors[i].rgbtRed; 
                lpPal->palPalEntry[i].peGreen = lpbmc->bmciColors[i].rgbtGreen; 
                lpPal->palPalEntry[i].peBlue = lpbmc->bmciColors[i].rgbtBlue; 
                lpPal->palPalEntry[i].peFlags = 0; 
            } 
        } 
 
        // ������ɫ���ָ���� 
        hPal = CreatePalette(lpPal); 
        if (!hPal) 
        { 
            GlobalUnlock(hLogPal); 
            GlobalFree(hLogPal); 
            return NULL; 
        } 
    } 
 
    return hPal; 
} 
 

 /************************************************************************* 
 * 
 * ������:CreateDIBPalette()  
 *
 * ����: ����DIB��ɫ��
 * ����: 
 * 
 *  HDIB hDIB        - ָ����DIB���
 *    
 * ����ֵ�������ĵ�ɫ��
 ************************************************************************/
HPALETTE CreateDIBPalette(HDIB hDIB) 
{ 
    //��ɫ����
    HPALETTE            hPal = NULL;
    //ָ��packed-DIB 
    LPBYTE               lpbi;      
 
    if (!hDIB) 
        return NULL; 
 
    // ����DIB�ڴ沢ָ�� 
    lpbi = (LPBYTE)GlobalLock(hDIB); 
 
	hPal = CreateDIBPalette(lpbi);

	// �������
    GlobalUnlock(hDIB); 
 
    return hPal; 
} 
 

 /************************************************************************* 
 * 
 * ������:DIBToBitmap() 
 *
 * ����: DIBת��ΪBitmap
 * ����: 
 * 
 * HDIB hDIB        - ָ����Ҫת����DIB
 * 
 * HPALETTE hPal    - ָ��BitmapҪʹ�õĵ�ɫ��
 *    
 * ����ֵ��ת�����Bitmap���
 ************************************************************************/

HBITMAP DIBToBitmap(HDIB hDIB, HPALETTE hPal) 
{ 
  
	LPBYTE       lpDIBHdr, lpDIBBits;  
    HBITMAP     hBitmap;           
    HDC         hDC;                
    HPALETTE    hOldPal = NULL;    

    if (!hDIB) 
        return NULL; 
 
    lpDIBHdr = (LPBYTE)GlobalLock(hDIB); 
 
    //�õ�DIBλָ�� 
    lpDIBBits = FindDIBBits(lpDIBHdr); 
 
    //�õ�DC  
     hDC = GetDC(NULL); 
    if (!hDC) 
    { 
        GlobalUnlock(hDIB); 
        return NULL; 
    } 
 
    //ѡ��ͳ�ʼ����ɫ�� 
    if (hPal) 
	{
        hOldPal = SelectPalette(hDC, hPal, FALSE); 
	    RealizePalette(hDC); 
	}
 
    // ��DIBͷ��Ϣ��λ���ݴ���λͼ 
    hBitmap = CreateDIBitmap(hDC, 
							(LPBITMAPINFOHEADER)lpDIBHdr, 
							CBM_INIT, 
							lpDIBBits, 
							(LPBITMAPINFO)lpDIBHdr, 
							DIB_RGB_COLORS);
 
    //������ǰ�ĵ�ɫ�� 
    if (hOldPal) 
        SelectPalette(hDC, hOldPal, FALSE); 

    ReleaseDC(NULL, hDC); 
    GlobalUnlock(hDIB); 
 
    return hBitmap; 
} 
 
 /************************************************************************* 
 * 
 * ������:BitmapToDIB() 
 *
 * ����:Bitmapת��Ϊ DIB
 * ����: 
 * 
 * HBITMAP hBitmap       - ָ����Ҫת����Bitmap
 * 
 * HPALETTE hPal    - ָ��BitmapҪʹ�õĵ�ɫ��
 *    
 * ����ֵ��ת�����DIB���
 ************************************************************************/

HDIB BitmapToDIB(HBITMAP hBitmap, HPALETTE hPal) 
{ 
	// bitmap �ṹ
    BITMAP              bm;    
	 // bitmap ͷ
    BITMAPINFOHEADER    bi;   
	//BITMAPINFOHEADER ָ��
    LPBITMAPINFOHEADER  lpbi;  
	 //�ڴ��ĳߴ� 
    DWORD               dwLen;     
    HANDLE              hDIB, h;    
    HDC                 hDC; 
	//����λ
    WORD                biBits;    
 
    if (!hBitmap) 
        return NULL; 
 
    //���BITMAP�ṹ 
    if (!GetObject(hBitmap, sizeof(bm), (LPBYTE)&bm)) 
        return NULL; 
 
    // ��û��ָ����ɫ��,ʹ��Ĭ�ϵ�ɫ�� 
     if (hPal == NULL) 
        hPal = (HPALETTE)GetStockObject(DEFAULT_PALETTE); 
 
    // ����ÿ���ص�λ��
    biBits = bm.bmPlanes * bm.bmBitsPixel; 
 
    // ȷ��ÿ���ض�����Ч�� 
    if (biBits <= 1) 
        biBits = 1; 
    else if (biBits <= 4) 
        biBits = 4; 
    else if (biBits <= 8) 
        biBits = 8; 
    else 
        biBits = 24; 
 
    //��ʼ�� BITMAPINFOHEADER 
    bi.biSize = sizeof(BITMAPINFOHEADER); 
    bi.biWidth = bm.bmWidth; 
    bi.biHeight = bm.bmHeight; 
    bi.biPlanes = 1; 
    bi.biBitCount = biBits; 
    bi.biCompression = BI_RGB; 
    bi.biSizeImage = 0; 
    bi.biXPelsPerMeter = 0; 
    bi.biYPelsPerMeter = 0; 
    bi.biClrUsed = 0; 
    bi.biClrImportant = 0; 
 
    //�����ڴ��ĳߴ���뱣�� BITMAPINFO 
 
    dwLen = bi.biSize + PaletteSize((LPBYTE)&bi); 
 
    // �õ�һ��DC 
     hDC = GetDC(NULL); 
 
    // ѡ���ɫ��
     hPal = SelectPalette(hDC, hPal, FALSE); 
    RealizePalette(hDC); 
 
    //�����ڴ��Ա���λͼ
     hDIB = GlobalAlloc(GHND, dwLen); 
 
    if (!hDIB) 
    { 
      SelectPalette(hDC, hPal, TRUE); 
      RealizePalette(hDC); 
      ReleaseDC(NULL, hDC); 
      return NULL; 
    } 
 
    //�����ڴ��������
     lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB); 
 
    *lpbi = bi; 
 
    GetDIBits(hDC, hBitmap, 0, (UINT)bi.biHeight, NULL, (LPBITMAPINFO)lpbi, 
        DIB_RGB_COLORS); 
 
    bi = *lpbi; 
    GlobalUnlock(hDIB); 
 
    if (bi.biSizeImage == 0) 
        bi.biSizeImage = WIDTHBYTES1((DWORD)bm.bmWidth * biBits) * bm.bmHeight; 
 
    //���·����ڴ��Ա��������е�λ
 
    dwLen = bi.biSize + PaletteSize((LPBYTE)&bi) + bi.biSizeImage; 
 
    if (h = GlobalReAlloc(hDIB, dwLen, 0)) 
        hDIB = h; 
    else 
    {
		 GlobalFree(hDIB); 
        hDIB = NULL; 
        SelectPalette(hDC, hPal, TRUE); 
        RealizePalette(hDC); 
        ReleaseDC(NULL, hDC); 
        return NULL; 
    }
 
    lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB); 
 
    if (GetDIBits(hDC, hBitmap, 0, (UINT)bi.biHeight, (LPBYTE)lpbi + 
            (WORD)lpbi->biSize + PaletteSize((LPBYTE)lpbi), (LPBITMAPINFO)lpbi, 
            DIB_RGB_COLORS) == 0) 
    { 
        GlobalUnlock(hDIB); 
        hDIB = NULL; 
        SelectPalette(hDC, hPal, TRUE); 
        RealizePalette(hDC); 
        ReleaseDC(NULL, hDC); 
        return NULL; 
    } 
 
    bi = *lpbi; 

    GlobalUnlock(hDIB); 
    SelectPalette(hDC, hPal, TRUE); 
    RealizePalette(hDC); 
    ReleaseDC(NULL, hDC); 

    return hDIB; 
} 
 

 /************************************************************************* 
 * 
 *������: BitmapToDIB() 
 *
 * ����:Bitmapת��Ϊ DIB
 * ����: 
 * 
 * HBITMAP hBitmap       - ָ����Ҫת����Bitmap
 * 
 * HPALETTE hPal    - ָ��BitmapҪʹ�õĵ�ɫ��
 *
 * WORD wBitCount   - ָ��ת�����DIB��ɫλ
 *    
 * ����ֵ��ת�����DIB���
 ************************************************************************/
HDIB BitmapToDIB(HBITMAP hBitmap, HPALETTE hPalette, WORD wBitCount)
{ 
	HDIB hNewDib;

	if (! hBitmap)
        return NULL; 

	//�õ� bitmap ��Ϣ
	BITMAP  bm;        
	GetObject(hBitmap, sizeof(bm), (LPBYTE)&bm); 
	int biBits = bm.bmPlanes * bm.bmBitsPixel;

	if (biBits <= 1) 
		biBits = 1; 
	else if (biBits <= 4) 
		biBits = 4; 
	else if (biBits <= 8) 
		biBits = 8; 
	else 
		biBits = 24; 

	//�ӵ�ǰDIB����еõ���ǰbitmap
	HDIB hDib = BitmapToDIB(hBitmap, hPalette);
	if (! hDib)
        return NULL; 

	if (wBitCount == biBits)
		hNewDib = hDib;
	else
	{
		hNewDib = ConvertDIBFormat((HANDLE)hDib, (UINT)wBitCount, hPalette);

		GlobalFree(hDib);
	}

	return hNewDib;
} 

 /************************************************************************* 
 * 
 * ������:ChangeBitmapFormat()
 *
 * ����:ת��Bitmap��ʽ������λ��ʽ
 * ����: 
 * 
 * HBITMAP          - bitmap��� 
 * 
 * WORD             - ÿ����Ҫת����λ��
 * 
 * DWORD            - ѹ����ʽ����
 * 
 * HPALETTE         - ��ɫ���� 
 *    
 * ����ֵ��ת�����DIB���
 ************************************************************************/
HDIB ChangeBitmapFormat (HBITMAP hbm, WORD biBits, DWORD biCompression, HPALETTE hpal)
{
    BITMAP               bm;
    BITMAPINFOHEADER     bi;
    LPBITMAPINFOHEADER   lpbi;
    DWORD                dwLen;
    HANDLE               hdib;
    HANDLE               h;
    HDC                  hdc;

    if (!hbm)
        return NULL;

    if (hpal == NULL)
        hpal = (HPALETTE)GetStockObject(DEFAULT_PALETTE);

    GetObject(hbm,sizeof(bm),(LPBYTE)&bm);

    if (biBits == 0)
	{
        biBits =  bm.bmPlanes * bm.bmBitsPixel;

	    if (biBits <= 1) 
		    biBits = 1; 
	    else if (biBits <= 4) 
		    biBits = 4; 
	    else if (biBits <= 8) 
		    biBits = 8; 
		else 
			biBits = 24; 
	}

    bi.biSize               = sizeof(BITMAPINFOHEADER);
    bi.biWidth              = bm.bmWidth;
    bi.biHeight             = bm.bmHeight;
    bi.biPlanes             = 1;
    bi.biBitCount           = biBits;
    bi.biCompression        = biCompression;
    bi.biSizeImage          = 0;
    bi.biXPelsPerMeter      = 0;
    bi.biYPelsPerMeter      = 0;
    bi.biClrUsed            = 0;
    bi.biClrImportant       = 0;

    dwLen  = bi.biSize + PaletteSize((LPBYTE)&bi);

    hdc = GetDC(NULL);
    HPALETTE hpalT = SelectPalette(hdc,hpal,FALSE);
    RealizePalette(hdc);

    hdib = GlobalAlloc(GHND,dwLen);

    if (!hdib)
	{
        SelectPalette(hdc,hpalT,FALSE);
        ReleaseDC(NULL,hdc);
        return NULL;
    }

    lpbi = (LPBITMAPINFOHEADER)GlobalLock(hdib);

    *lpbi = bi;


    GetDIBits(hdc, hbm, 0L, (DWORD)bi.biHeight,
        (LPBYTE)NULL, (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);

    bi = *lpbi;
    GlobalUnlock(hdib);

    if (bi.biSizeImage == 0)
	{
        bi.biSizeImage = WIDTHBYTES1((DWORD)bm.bmWidth * biBits) * bm.bmHeight;

        if (biCompression != BI_RGB)
            bi.biSizeImage = (bi.biSizeImage * 3) / 2;
    }

    ///�����㹻���ڴ�
    dwLen = bi.biSize + PaletteSize((LPBYTE)&bi) + bi.biSizeImage;
    if (h = GlobalReAlloc(hdib,dwLen,0))
        hdib = h;
    else
	{
        GlobalFree(hdib);
        hdib = NULL;

        SelectPalette(hdc,hpalT,FALSE);
        ReleaseDC(NULL,hdc);
        return hdib;
    }

    lpbi = (LPBITMAPINFOHEADER)GlobalLock(hdib);

    if (! GetDIBits(hdc,
                    hbm,
                    0L,
                    (DWORD)bi.biHeight,
                    (LPBYTE)lpbi + (WORD)lpbi->biSize + PaletteSize((LPBYTE)lpbi),
                    (LPBITMAPINFO)lpbi, 
					(DWORD)DIB_RGB_COLORS))
	{
         GlobalUnlock(hdib);
         hdib = NULL;
         SelectPalette(hdc,hpalT,FALSE);
         ReleaseDC(NULL,hdc);
         return NULL;
    }
    bi = *lpbi;
   
	GlobalUnlock(hdib);
    SelectPalette(hdc,hpalT,FALSE);
    ReleaseDC(NULL,hdc);
    return hdib;
}

 /************************************************************************* 
 * 
 * ������:ChangeDIBFormat() 
 *
 * ����:ת��DIB��ʽ������λ��ʽ
 * ����: 
 * 
 * HDIB              - DIB��� 
 * 
 * WORD             - ÿ����Ҫת����λ��
 * 
 * DWORD            - ѹ����ʽ����
 * 
 * HPALETTE         - ��ɫ���� 
 *    
 * ����ֵ��ת�����DIB���
 ************************************************************************/
HDIB ChangeDIBFormat(HDIB hDIB, WORD wBitCount, DWORD dwCompression) 
{ 

    HBITMAP            hBitmap;         
    //��DIB���
    HDIB               hNewDIB = NULL;  
    HPALETTE           hPal;			

    //���DIB�Ƿ���Ч
     if (!hDIB) 
        return NULL; 
 
    // �����DIB��ɫ��
     hPal = CreateDIBPalette(hDIB); 
    if (hPal == NULL)
        hPal = (HPALETTE)GetStockObject(DEFAULT_PALETTE);
 
    // ת����DIB��bitmap 
     hBitmap = DIBToBitmap(hDIB, hPal); 
    if (!hBitmap) 
    { 
        DeleteObject(hPal); 
        return NULL; 
    } 

	// �ı�Bitmap��ʽ
	hNewDIB = ChangeBitmapFormat(hBitmap, wBitCount, dwCompression, hPal);
 
    DeleteObject(hBitmap); 
    DeleteObject(hPal); 
 
    return hNewDIB; 
} 
 

 /************************************************************************* 
 * 
 * ������:ConvertDIBFormat () 
 *
 * ����:ת��DIB��ʽ������λ��ʽ
 * ����: 
 * 
 * LPBITMAPINFO lpSrcDIB - ��ԴCF_DIB 
 * UINT         nWidth   - ��DIB�Ŀ�� 
 * UINT         nHeight  - ��DIB�ĸ߶� 
 * UINT         nbpp     - ��DIB������ 
 * BOOL         bStretch - TRUE������Դ��FALSEͼ�ε����Ͻ� 
 * HPALETTE	 hPalSrc     - ����Դʹ�õĵ�ɫ�� 
 * DWORD		 dwSize  - ��DIB ��ָ��
 *    
 * ����ֵ��ת�����DIB���
 ************************************************************************/
HDIB ConvertDIBFormat(LPBYTE lpDIB, UINT nWidth, UINT nHeight, UINT nbpp, BOOL bStretch, HPALETTE hPalSrc) 
{ 
	LPBITMAPINFO lpSrcDIB =  (LPBITMAPINFO)lpDIB;
    LPBITMAPINFO lpbmi = NULL; 
    LPBYTE       lpSourceBits, lpTargetBits, lpResult; 
    HDC			 hDC = NULL, hSourceDC, hTargetDC; 
    HBITMAP      hSourceBitmap, hTargetBitmap, hOldTargetBitmap, hOldSourceBitmap; 
    DWORD        dwSourceBitsSize, dwTargetBitsSize, dwTargetHeaderSize, dwColorNum; 
	HDIB		 hDib;
 
    // ��������BITMAPINFO�ṹΪ�����DIB 
    if (nbpp <= 8) 
		dwColorNum = 1 << nbpp;
	else
		dwColorNum = 0;
    dwTargetHeaderSize = sizeof( BITMAPINFO ) + ( dwColorNum * sizeof( RGBQUAD ) ); 
    lpbmi = (LPBITMAPINFO)malloc( dwTargetHeaderSize ); 
    lpbmi->bmiHeader.biSize = sizeof( BITMAPINFOHEADER ); 
    lpbmi->bmiHeader.biWidth = nWidth; 
    lpbmi->bmiHeader.biHeight = nHeight; 
    lpbmi->bmiHeader.biPlanes = 1; 
    lpbmi->bmiHeader.biBitCount = nbpp; 
    lpbmi->bmiHeader.biCompression = BI_RGB; 
    lpbmi->bmiHeader.biSizeImage = 0; 
    lpbmi->bmiHeader.biXPelsPerMeter = 0; 
    lpbmi->bmiHeader.biYPelsPerMeter = 0; 
    lpbmi->bmiHeader.biClrUsed = 0; 
    lpbmi->bmiHeader.biClrImportant = 0; 
    // �����ɫ��
    if( ! CopyColorTable( lpbmi, (LPBITMAPINFO)lpSrcDIB, hPalSrc ) ) 
    { 
        free( lpbmi ); 
        return NULL; 
    } 
 
	hDC = GetDC( NULL ); 
    hTargetBitmap = CreateDIBSection( hDC, lpbmi, DIB_RGB_COLORS, (VOID **)&lpTargetBits, NULL, 0 ); 
    hSourceBitmap = CreateDIBSection( hDC, lpSrcDIB, DIB_RGB_COLORS, (VOID **)&lpSourceBits, NULL, 0 ); 
    hSourceDC = CreateCompatibleDC( hDC ); 
    hTargetDC = CreateCompatibleDC( hDC ); 
 
    // ���� DIBSection������� DIB 
    dwSourceBitsSize = lpSrcDIB->bmiHeader.biHeight * BytesPerLine((LPBYTE)&(lpSrcDIB->bmiHeader)); 
    dwTargetBitsSize = lpbmi->bmiHeader.biHeight * BytesPerLine((LPBYTE)&(lpbmi->bmiHeader)); 
    memcpy( lpSourceBits, FindDIBBits((LPBYTE)lpSrcDIB), dwSourceBitsSize ); 
    lpbmi->bmiHeader.biSizeImage = dwTargetBitsSize; 
 
    //ѡDIBSections��DCs�� 
    hOldSourceBitmap = (HBITMAP)SelectObject( hSourceDC, hSourceBitmap ); 
    hOldTargetBitmap = (HBITMAP)SelectObject( hTargetDC, hTargetBitmap ); 
 
    //ΪDIBSections������ɫ�� 
    if( lpSrcDIB->bmiHeader.biBitCount <= 8 ) 
        SetDIBColorTable( hSourceDC, 0, 1 << lpSrcDIB->bmiHeader.biBitCount, lpSrcDIB->bmiColors ); 
    if( lpbmi->bmiHeader.biBitCount <= 8 ) 
        SetDIBColorTable( hTargetDC, 0, 1 << lpbmi->bmiHeader.biBitCount, lpbmi->bmiColors ); 
 
    // ��Ҫһ���濽�� 
    if( (lpSrcDIB->bmiHeader.biWidth==lpbmi->bmiHeader.biWidth) && (lpSrcDIB->bmiHeader.biHeight==lpbmi->bmiHeader.biHeight) ) 
    { 
        BitBlt( hTargetDC, 0, 0, lpbmi->bmiHeader.biWidth, lpbmi->bmiHeader.biHeight, hSourceDC, 0, 0, SRCCOPY ); 
    } 
    else 
    { 
        // ����������
        if( bStretch ) 
        { 
            SetStretchBltMode( hTargetDC, COLORONCOLOR ); 
            StretchBlt( hTargetDC, 0, 0, lpbmi->bmiHeader.biWidth, lpbmi->bmiHeader.biHeight, hSourceDC, 0, 0, lpSrcDIB->bmiHeader.biWidth, lpSrcDIB->bmiHeader.biHeight, SRCCOPY ); 
        } 
        else 
        { 
            // ������Դ�����Ͻ�
            BitBlt( hTargetDC, 0, 0, lpbmi->bmiHeader.biWidth, lpbmi->bmiHeader.biHeight, hSourceDC, 0, 0, SRCCOPY ); 
        } 
    } 
 
    SelectObject( hSourceDC, hOldSourceBitmap ); 
    SelectObject( hTargetDC, hOldTargetBitmap ); 
    DeleteDC( hSourceDC ); 
    DeleteDC( hTargetDC ); 
    ReleaseDC( NULL, hDC ); 
 
    GdiFlush(); 
 
    // �����㹻���ڴ��Ϊ��DIB,����������λ 
    hDib = GlobalAlloc(GHND, dwTargetHeaderSize + dwTargetBitsSize ); 
    lpResult = (LPBYTE)GlobalLock(hDib); 
    memcpy( lpResult, lpbmi, dwTargetHeaderSize ); 
    memcpy( FindDIBBits( (LPBYTE)lpResult ), lpTargetBits, dwTargetBitsSize ); 

    DeleteObject( hTargetBitmap ); 
    DeleteObject( hSourceBitmap ); 
	free( lpbmi ); 
    GlobalUnlock(hDib);
 
    return hDib; 
} 

 /************************************************************************* 
 * 
 * ������:ConvertDIBFormat () 
 *
 * ����:ת��DIB��ʽ������λ��ʽ
 * ����: 
 * 
 * LPBITMAPINFO lpSrcDIB - ��ԴCF_DIB 
 * UINT         nWidth   - ��DIB�Ŀ�� 
 * UINT         nHeight  - ��DIB�ĸ߶� 
 * UINT         nbpp     - ��DIB������ 
 * BOOL         bStretch - TRUE������Դ��FALSEͼ�ε����Ͻ� 
 * HPALETTE	 hPalSrc     - ����Դʹ�õĵ�ɫ�� 
 * DWORD		 dwSize  - ��DIB ��ָ��
 *    
 * ����ֵ��ת�����DIB���
 ************************************************************************/
HDIB ConvertDIBFormat(HDIB hDIB, UINT nWidth, UINT nHeight, UINT nbpp, BOOL bStretch, HPALETTE hPalSrc)
{
    LPBITMAPINFO lpbmi = NULL; 
    LPBYTE       lpSourceBits, lpTargetBits, lpResult; 
    HDC			 hDC = NULL, hSourceDC, hTargetDC; 
    HBITMAP      hSourceBitmap, hTargetBitmap, hOldTargetBitmap, hOldSourceBitmap; 
    DWORD        dwSourceBitsSize, dwTargetBitsSize, dwTargetHeaderSize, dwColorNum; 
	HDIB		 hNewDIB;
	DWORD		 dwSize;

	// �õ�DIBָ��
	if (! hDIB)
		return NULL;
	LPBITMAPINFO lpSrcDIB = (LPBITMAPINFO)GlobalLock(hDIB);
	if (! lpSrcDIB)
		return NULL;

    // ��������BITMAPINFO�ṹΪ�����DIB 
    if (nbpp <= 8) 
		dwColorNum = 1 << nbpp;
	else
		dwColorNum = 0;
    dwTargetHeaderSize = sizeof( BITMAPINFO ) + ( dwColorNum * sizeof( RGBQUAD ) ); 
    lpbmi = (LPBITMAPINFO)malloc( dwTargetHeaderSize ); 
    lpbmi->bmiHeader.biSize = sizeof( BITMAPINFOHEADER ); 
    lpbmi->bmiHeader.biWidth = nWidth; 
    lpbmi->bmiHeader.biHeight = nHeight; 
    lpbmi->bmiHeader.biPlanes = 1; 
    lpbmi->bmiHeader.biBitCount = nbpp; 
    lpbmi->bmiHeader.biCompression = BI_RGB; 
    lpbmi->bmiHeader.biSizeImage = 0; 
    lpbmi->bmiHeader.biXPelsPerMeter = 0; 
    lpbmi->bmiHeader.biYPelsPerMeter = 0; 
    lpbmi->bmiHeader.biClrUsed = 0; 
    lpbmi->bmiHeader.biClrImportant = 0; 
    //�����ɫ��
    if( ! CopyColorTable( lpbmi, (LPBITMAPINFO)lpSrcDIB, hPalSrc ) ) 
    { 
        free( lpbmi ); 
        return NULL; 
    } 
 
	hDC = GetDC( NULL ); 
    hTargetBitmap = CreateDIBSection( hDC, lpbmi, DIB_RGB_COLORS, (VOID **)&lpTargetBits, NULL, 0 ); 
    hSourceBitmap = CreateDIBSection( hDC, lpSrcDIB, DIB_RGB_COLORS, (VOID **)&lpSourceBits, NULL, 0 ); 
    hSourceDC = CreateCompatibleDC( hDC ); 
    hTargetDC = CreateCompatibleDC( hDC ); 
 
    //������Դ DIBƬ����ƥ����ԴDIB 
    dwSourceBitsSize = lpSrcDIB->bmiHeader.biHeight * BytesPerLine((LPBYTE)&(lpSrcDIB->bmiHeader)); 
    dwTargetBitsSize = lpbmi->bmiHeader.biHeight * BytesPerLine((LPBYTE)&(lpbmi->bmiHeader)); 
    memcpy( lpSourceBits, FindDIBBits((LPBYTE)lpSrcDIB), dwSourceBitsSize ); 
    lpbmi->bmiHeader.biSizeImage = dwTargetBitsSize; 
 
    //ѡ��DIBƬ�ε� DCs 
    hOldSourceBitmap = (HBITMAP)SelectObject( hSourceDC, hSourceBitmap ); 
    hOldTargetBitmap = (HBITMAP)SelectObject( hTargetDC, hTargetBitmap ); 
 
    // ΪDIBƬ��ѡ����ɫ�� 
    if( lpSrcDIB->bmiHeader.biBitCount <= 8 ) 
        SetDIBColorTable( hSourceDC, 0, 1 << lpSrcDIB->bmiHeader.biBitCount, lpSrcDIB->bmiColors ); 
    if( lpbmi->bmiHeader.biBitCount <= 8 ) 
        SetDIBColorTable( hTargetDC, 0, 1 << lpbmi->bmiHeader.biBitCount, lpbmi->bmiColors ); 
 
    if( (lpSrcDIB->bmiHeader.biWidth==lpbmi->bmiHeader.biWidth) && (lpSrcDIB->bmiHeader.biHeight==lpbmi->bmiHeader.biHeight) ) 
    { 
        BitBlt( hTargetDC, 0, 0, lpbmi->bmiHeader.biWidth, lpbmi->bmiHeader.biHeight, hSourceDC, 0, 0, SRCCOPY ); 
    } 
    else 
    { 
        if( bStretch ) 
        { 
            SetStretchBltMode( hTargetDC, COLORONCOLOR ); 
            StretchBlt( hTargetDC, 0, 0, lpbmi->bmiHeader.biWidth, lpbmi->bmiHeader.biHeight, hSourceDC, 0, 0, lpSrcDIB->bmiHeader.biWidth, lpSrcDIB->bmiHeader.biHeight, SRCCOPY ); 
        } 
        else 
        { 
            BitBlt( hTargetDC, 0, 0, lpbmi->bmiHeader.biWidth, lpbmi->bmiHeader.biHeight, hSourceDC, 0, 0, SRCCOPY ); 
        } 
    } 
 
    SelectObject( hSourceDC, hOldSourceBitmap ); 
    SelectObject( hTargetDC, hOldTargetBitmap ); 
    DeleteDC( hSourceDC ); 
    DeleteDC( hTargetDC ); 
    ReleaseDC( NULL, hDC ); 
 
    GdiFlush(); 
 
    //�����㹻���ڴ�Ϊ��DIB
	dwSize = dwTargetHeaderSize + dwTargetBitsSize;
	hNewDIB = GlobalAlloc(GHND, dwSize);
    lpResult = (LPBYTE)GlobalLock(hNewDIB);
    memcpy( lpResult, lpbmi, dwTargetHeaderSize ); 
    memcpy( FindDIBBits( (LPBYTE)lpResult ), lpTargetBits, dwTargetBitsSize ); 

    DeleteObject( hTargetBitmap ); 
    DeleteObject( hSourceBitmap ); 
    free( lpbmi ); 
	GlobalUnlock(hDIB);
	GlobalUnlock(hNewDIB);
 
    return hNewDIB;
}


/************************************************************************* 
 *
 * ������:ConvertDIBFormat () 
 *
 * ����:ת��DIB��ʽ������λ��ʽ
 * ����: 
 * 
 * LPBYTE	lpDIB    - ��ԴCF_DIB
 * UINT         nbpp     - ��DIB������
 * HPALETTE	hPalSrc  - ����Դʹ�õĵ�ɫ�� 
 *    
 * ����ֵ��ת�����DIB���
 ************************************************************************/
HDIB ConvertDIBFormat(LPBYTE lpDIB, UINT nbpp, HPALETTE hPalSrc)
{
	LPBITMAPINFO lpSrcDIB = (LPBITMAPINFO)lpDIB;
    LPBITMAPINFO lpbmi = NULL; 
    LPBYTE       lpSourceBits, lpTargetBits, lpResult; 
    HDC			 hDC = NULL, hSourceDC, hTargetDC; 
    HBITMAP      hSourceBitmap, hTargetBitmap, hOldTargetBitmap, hOldSourceBitmap; 
    DWORD        dwSourceBitsSize, dwTargetBitsSize, dwTargetHeaderSize, dwColorNum; 
	HDIB		 hNewDIB;
	DWORD		 dwSize;
	int			 nWidth, nHeight;

	nWidth = lpSrcDIB->bmiHeader.biWidth;
	nHeight = lpSrcDIB->bmiHeader.biHeight;

    //�����㹻���ڴ�Ϊ��DIB 
    if (nbpp <= 8) 
		dwColorNum = 1 << nbpp;
	else
		dwColorNum = 0;
    dwTargetHeaderSize = sizeof( BITMAPINFO ) + ( dwColorNum * sizeof( RGBQUAD ) ); 
    lpbmi = (LPBITMAPINFO)malloc( dwTargetHeaderSize ); 
    lpbmi->bmiHeader.biSize = sizeof( BITMAPINFOHEADER ); 
    lpbmi->bmiHeader.biWidth = nWidth; 
    lpbmi->bmiHeader.biHeight = nHeight; 
    lpbmi->bmiHeader.biPlanes = 1; 
    lpbmi->bmiHeader.biBitCount = nbpp; 
    lpbmi->bmiHeader.biCompression = BI_RGB; 
    lpbmi->bmiHeader.biSizeImage = 0; 
    lpbmi->bmiHeader.biXPelsPerMeter = 0; 
    lpbmi->bmiHeader.biYPelsPerMeter = 0; 
    lpbmi->bmiHeader.biClrUsed = 0; 
    lpbmi->bmiHeader.biClrImportant = 0; 
    //�����ɫ��
    if( ! CopyColorTable( lpbmi, (LPBITMAPINFO)lpSrcDIB, hPalSrc ) ) 
    { 
        free( lpbmi ); 
        return NULL; 
    } 

	hDC = GetDC( NULL ); 
    hTargetBitmap = CreateDIBSection( hDC, lpbmi, DIB_RGB_COLORS, (VOID **)&lpTargetBits, NULL, 0 ); 
    hSourceBitmap = CreateDIBSection( hDC, lpSrcDIB, DIB_RGB_COLORS, (VOID **)&lpSourceBits, NULL, 0 ); 
    hSourceDC = CreateCompatibleDC( hDC ); 
    hTargetDC = CreateCompatibleDC( hDC ); 
 
    dwSourceBitsSize = lpSrcDIB->bmiHeader.biHeight * BytesPerLine((LPBYTE)&(lpSrcDIB->bmiHeader)); 
    dwTargetBitsSize = lpbmi->bmiHeader.biHeight * BytesPerLine((LPBYTE)&(lpbmi->bmiHeader)); 
    memcpy( lpSourceBits, FindDIBBits((LPBYTE)lpSrcDIB), dwSourceBitsSize ); 
    lpbmi->bmiHeader.biSizeImage = dwTargetBitsSize; 
 

    hOldSourceBitmap = (HBITMAP)SelectObject( hSourceDC, hSourceBitmap ); 
    hOldTargetBitmap = (HBITMAP)SelectObject( hTargetDC, hTargetBitmap ); 
 
    // ΪDIBƬ��ѡȡ��ɫ�� 
    if( lpSrcDIB->bmiHeader.biBitCount <= 8 ) 
        SetDIBColorTable( hSourceDC, 0, 1 << lpSrcDIB->bmiHeader.biBitCount, lpSrcDIB->bmiColors ); 
    if( lpbmi->bmiHeader.biBitCount <= 8 ) 
        SetDIBColorTable( hTargetDC, 0, 1 << lpbmi->bmiHeader.biBitCount, lpbmi->bmiColors ); 
 
    BitBlt( hTargetDC, 0, 0, lpbmi->bmiHeader.biWidth, lpbmi->bmiHeader.biHeight, hSourceDC, 0, 0, SRCCOPY ); 
 
    SelectObject( hSourceDC, hOldSourceBitmap ); 
    SelectObject( hTargetDC, hOldTargetBitmap ); 
    DeleteDC( hSourceDC ); 
    DeleteDC( hTargetDC ); 
    ReleaseDC( NULL, hDC ); 
 
    GdiFlush(); 
 
	dwSize = dwTargetHeaderSize + dwTargetBitsSize;
	hNewDIB = GlobalAlloc(GHND, dwSize);
    lpResult = (LPBYTE)GlobalLock(hNewDIB);
    memcpy( lpResult, lpbmi, dwTargetHeaderSize ); 
    memcpy( FindDIBBits( (LPBYTE)lpResult ), lpTargetBits, dwTargetBitsSize ); 
 
    DeleteObject( hTargetBitmap ); 
    DeleteObject( hSourceBitmap ); 
    free( lpbmi ); 
	GlobalUnlock(hNewDIB);
 
    return hNewDIB;
}




/**************************************************************************** 
*  
* ������:ConvertDIBFormat () 
*
* ����:ת��DIB��ʽ������λ��ʽ
* ����: 
*  HDIB	       hDIB      - ����Դ��DIB��� 
*  UINT         nbpp     - ��DIB������
*  HPALETTE	hPalSrc  - ����Դʹ�õĵ�ɫ�� 
* 
* ����ֵ��ת�����DIB���
* 
\****************************************************************************/ 

HDIB ConvertDIBFormat(HDIB hDIB, UINT nbpp, HPALETTE hPalSrc)
{
    LPBITMAPINFO lpbmi = NULL; 
    LPBYTE       lpSourceBits, lpTargetBits, lpResult; 
    HDC			 hDC = NULL, hSourceDC, hTargetDC; 
    HBITMAP      hSourceBitmap, hTargetBitmap, hOldTargetBitmap, hOldSourceBitmap; 
    DWORD        dwSourceBitsSize, dwTargetBitsSize, dwTargetHeaderSize, dwColorNum; 
	HANDLE		 hNewDIB;
	DWORD		 dwSize;
	int			 nWidth, nHeight;

	//�õ�DIBָ��
	if (! hDIB)
		return NULL;
	LPBITMAPINFO lpSrcDIB = (LPBITMAPINFO)GlobalLock(hDIB);
	if (! lpSrcDIB)
		return NULL;
	nWidth = lpSrcDIB->bmiHeader.biWidth;
	nHeight = lpSrcDIB->bmiHeader.biHeight;

    //�����㹻���ڴ�Ϊ��DIB
    if (nbpp <= 8) 
		dwColorNum = 1 << nbpp;
	else
		dwColorNum = 0;
    dwTargetHeaderSize = sizeof( BITMAPINFO ) + ( dwColorNum * sizeof( RGBQUAD ) ); 
    lpbmi = (LPBITMAPINFO)malloc( dwTargetHeaderSize ); 
    lpbmi->bmiHeader.biSize = sizeof( BITMAPINFOHEADER ); 
    lpbmi->bmiHeader.biWidth = nWidth; 
    lpbmi->bmiHeader.biHeight = nHeight; 
    lpbmi->bmiHeader.biPlanes = 1; 
    lpbmi->bmiHeader.biBitCount = nbpp; 
    lpbmi->bmiHeader.biCompression = BI_RGB; 
    lpbmi->bmiHeader.biSizeImage = 0; 
    lpbmi->bmiHeader.biXPelsPerMeter = 0; 
    lpbmi->bmiHeader.biYPelsPerMeter = 0; 
    lpbmi->bmiHeader.biClrUsed = 0; 
    lpbmi->bmiHeader.biClrImportant = 0; 
    //�����ɫ��
    if( ! CopyColorTable( lpbmi, (LPBITMAPINFO)lpSrcDIB, hPalSrc ) ) 
    { 
        free( lpbmi ); 
        return NULL; 
    } 
 
	hDC = GetDC( NULL ); 
    hTargetBitmap = CreateDIBSection( hDC, lpbmi, DIB_RGB_COLORS, (VOID **)&lpTargetBits, NULL, 0 ); 
    hSourceBitmap = CreateDIBSection( hDC, lpSrcDIB, DIB_RGB_COLORS, (VOID **)&lpSourceBits, NULL, 0 ); 
    hSourceDC = CreateCompatibleDC( hDC ); 
    hTargetDC = CreateCompatibleDC( hDC ); 

    dwSourceBitsSize = lpSrcDIB->bmiHeader.biHeight * BytesPerLine((LPBYTE)&(lpSrcDIB->bmiHeader)); 
    dwTargetBitsSize = lpbmi->bmiHeader.biHeight * BytesPerLine((LPBYTE)&(lpbmi->bmiHeader)); 
    memcpy( lpSourceBits, FindDIBBits((LPBYTE)lpSrcDIB), dwSourceBitsSize ); 
    lpbmi->bmiHeader.biSizeImage = dwTargetBitsSize; 
 
    //ѡȡDIBƬ�ε�DCs 
    hOldSourceBitmap = (HBITMAP)SelectObject( hSourceDC, hSourceBitmap ); 
    hOldTargetBitmap = (HBITMAP)SelectObject( hTargetDC, hTargetBitmap ); 
 
    //ΪDIBƬ��������ɫ��
    if( lpSrcDIB->bmiHeader.biBitCount <= 8 ) 
        SetDIBColorTable( hSourceDC, 0, 1 << lpSrcDIB->bmiHeader.biBitCount, lpSrcDIB->bmiColors ); 
    if( lpbmi->bmiHeader.biBitCount <= 8 ) 
        SetDIBColorTable( hTargetDC, 0, 1 << lpbmi->bmiHeader.biBitCount, lpbmi->bmiColors ); 
 
    BitBlt( hTargetDC, 0, 0, lpbmi->bmiHeader.biWidth, lpbmi->bmiHeader.biHeight, hSourceDC, 0, 0, SRCCOPY ); 
 
    SelectObject( hSourceDC, hOldSourceBitmap ); 
    SelectObject( hTargetDC, hOldTargetBitmap ); 
    DeleteDC( hSourceDC ); 
    DeleteDC( hTargetDC ); 
    ReleaseDC( NULL, hDC ); 

    GdiFlush(); 

	dwSize = dwTargetHeaderSize + dwTargetBitsSize;
	hNewDIB = GlobalAlloc(GHND, dwSize);
    lpResult = (LPBYTE)GlobalLock(hNewDIB);
    memcpy( lpResult, lpbmi, dwTargetHeaderSize ); 
    memcpy( FindDIBBits( (LPBYTE)lpResult ), lpTargetBits, dwTargetBitsSize ); 
 
    DeleteObject( hTargetBitmap ); 
    DeleteObject( hSourceBitmap ); 
    free( lpbmi ); 
	GlobalUnlock(hDIB);
	GlobalUnlock(hNewDIB);
 
    return hNewDIB;
}

 

/**************************************************************************** 
* 
* ������:CopyColorTable()
* 
*  ����:  ������ɫ���һ��DIB��������DIB. 
* 
*  ����:   LPBITMAPINFO lpTarget - Ŀ�� DIBָ�� 
*          LPBITMAPINFO lpSource - ��Դ DIBָ�� 
* 
*  ����ֵ:  ����TRUE��ʾ�ɹ�,�����ʾʧ��. 
* 
\****************************************************************************/ 
BOOL CopyColorTable( LPBITMAPINFO lpTarget, LPBITMAPINFO lpSource, HPALETTE hPalSrc ) 
{ 
    //ʹ��Ŀ����ɫ���
    switch( lpTarget->bmiHeader.biBitCount ) 
    { 
        // 8bpp - ��Ҫ256ɫ��ɫ��
        case 8: 
			if (hPalSrc)
			{ 
				PALETTEENTRY    pe[256]; 
				UINT            i; 

				GetPaletteEntries( hPalSrc, 0, 256, pe ); 
				for(i=0;i<256;i++) 
				{ 
					lpTarget->bmiColors[i].rgbRed = pe[i].peRed; 
					lpTarget->bmiColors[i].rgbGreen = pe[i].peGreen; 
					lpTarget->bmiColors[i].rgbBlue = pe[i].peBlue; 
					lpTarget->bmiColors[i].rgbReserved = 0; 
				} 
			}
			else
			{
				if( lpSource->bmiHeader.biBitCount == 8 ) 
				{ 
					memcpy( lpTarget->bmiColors, lpSource->bmiColors, 256*sizeof(RGBQUAD) ); 
				} 
				else 
				{ 
					HPALETTE        hPal; 
					HDC            hDC = GetDC( NULL ); 
					PALETTEENTRY    pe[256]; 
					UINT            i; 
 
					hPal = CreateOctreePalette((LPBYTE)lpSource, 236, 8);
					if (! hPal)	               
						hPal = CreateHalftonePalette( hDC ); 
					ReleaseDC( NULL, hDC ); 

					GetPaletteEntries( hPal, 0, 256, pe ); 
					DeleteObject( hPal ); 
					for(i=0;i<256;i++) 
					{ 
						lpTarget->bmiColors[i].rgbRed = pe[i].peRed; 
						lpTarget->bmiColors[i].rgbGreen = pe[i].peGreen; 
						lpTarget->bmiColors[i].rgbBlue = pe[i].peBlue; 
						lpTarget->bmiColors[i].rgbReserved = pe[i].peFlags; 
					} 
				}
			}
			break; // end 8bpp 
 
        // 4bpp - ��Ҫ16ɫ��ɫ��
        case 4: 
			if (hPalSrc)
			{ 
				PALETTEENTRY    pe[16]; 
				UINT            i; 

				GetPaletteEntries( hPalSrc, 0, 16, pe ); 
				for(i=0;i<16;i++) 
				{ 
					lpTarget->bmiColors[i].rgbRed = pe[i].peRed; 
					lpTarget->bmiColors[i].rgbGreen = pe[i].peGreen; 
					lpTarget->bmiColors[i].rgbBlue = pe[i].peBlue; 
					lpTarget->bmiColors[i].rgbReserved = 0; 
				} 
			}
			else
			{ 
				if( lpSource->bmiHeader.biBitCount == 4 ) 
				{ 
					memcpy( lpTarget->bmiColors, lpSource->bmiColors, 16*sizeof(RGBQUAD) ); 
				} 
				else 
				{ // != 4bpp, ʹ��ϵͳ��ɫ�� 
					HPALETTE        hPal; 
					PALETTEENTRY    pe[256]; 
					UINT            i; 
 
					hPal = (HPALETTE)GetStockObject( DEFAULT_PALETTE ); 
					GetPaletteEntries( hPal, 0, 16, pe ); 
					for(i=0;i<16;i++) 
					{ 
						lpTarget->bmiColors[i].rgbRed = pe[i].peRed; 
						lpTarget->bmiColors[i].rgbGreen = pe[i].peGreen; 
						lpTarget->bmiColors[i].rgbBlue = pe[i].peBlue; 
						lpTarget->bmiColors[i].rgbReserved = pe[i].peFlags; 
					}
                } 
			}
			break; // end 4bpp 
 
        // 1bpp - ��Ҫ2λ monoɫ��ɫ�� 
        case 1: 
            lpTarget->bmiColors[0].rgbRed = 0; 
            lpTarget->bmiColors[0].rgbGreen = 0; 
            lpTarget->bmiColors[0].rgbBlue = 0; 
            lpTarget->bmiColors[0].rgbReserved = 0; 
            lpTarget->bmiColors[1].rgbRed = 255; 
            lpTarget->bmiColors[1].rgbGreen = 255; 
            lpTarget->bmiColors[1].rgbBlue = 255; 
            lpTarget->bmiColors[1].rgbReserved = 0; 
			break; // end 1bpp 
 
        // > 8bpp ģʽ
        case 32: 
        case 24: 
        case 16: 
        default: 
	        break; 
    } 
    return TRUE; 
} 



/**************************************************************************** 
* 
* ������:DIBToDIBSection() 
* 
* ����������DIBƬ�δ�DIB
* 
* ����:   LPBYTE lpDIB - DIB���ݻ�����ָ��
* 
* ����ֵ:  HBITMAP -DIBƬ�Ͼ��, Ϊ�ձ�ʾʧ�� 
* 
\****************************************************************************/ 
HBITMAP DIBToDIBSection(LPBYTE lpDIB) 
{
    LPBYTE       lpSourceBits; 
    HDC			 hDC = NULL, hSourceDC; 
    HBITMAP      hSourceBitmap, hOldSourceBitmap; 
    DWORD        dwSourceBitsSize; 

	LPBITMAPINFO lpSrcDIB = (LPBITMAPINFO)lpDIB;
	if (! lpSrcDIB)
		return NULL;

	hDC = GetDC( NULL ); 
    hSourceBitmap = CreateDIBSection( hDC, lpSrcDIB, DIB_RGB_COLORS, (VOID **)&lpSourceBits, NULL, 0 ); 
    hSourceDC = CreateCompatibleDC( hDC ); 
 
    // �����Դ DIBƬ�ε�ƥ�����ԴDIB 
    dwSourceBitsSize = lpSrcDIB->bmiHeader.biHeight * BytesPerLine((LPBYTE)&(lpSrcDIB->bmiHeader)); 
    memcpy( lpSourceBits, FindDIBBits((LPBYTE)lpSrcDIB), dwSourceBitsSize ); 
 
    //��Դ DIBƬ�ε�DCs 
    hOldSourceBitmap = (HBITMAP)SelectObject( hSourceDC, hSourceBitmap ); 
 
    //Ϊ��Դ DIBƬ��������ɫ��
    if( lpSrcDIB->bmiHeader.biBitCount <= 8 ) 
        SetDIBColorTable( hSourceDC, 0, 1 << lpSrcDIB->bmiHeader.biBitCount, lpSrcDIB->bmiColors ); 

    // Clean up and delete the DCs 
    SelectObject( hSourceDC, hOldSourceBitmap ); 
    DeleteDC( hSourceDC ); 
    ReleaseDC( NULL, hDC ); 
 
    // Flush the GDI batch, so we can play with the bits 
    GdiFlush(); 
 
    return hSourceBitmap;
} 

/**************************************************************************** 
* 
* ������:DIBToDIBSection() 
* 
* ����������DIBƬ�δ�DIB
* 
* ����:   HIDB DIB - DIB���
* 
* ����ֵ:  HBITMAP -DIBƬ�Ͼ��, Ϊ�ձ�ʾʧ�� 
* 
\****************************************************************************/ 
HBITMAP DIBToDIBSection(HDIB hDIB) 
{
    HBITMAP      hSourceBitmap; 

	//�õ�DIBָ��
	if (! hDIB)
		return NULL;
	LPBYTE lpSrcDIB = (LPBYTE)GlobalLock(hDIB);
	if (! lpSrcDIB)
		return NULL;

	hSourceBitmap = DIBToDIBSection(lpSrcDIB);

	GlobalUnlock(hDIB);
 
    return hSourceBitmap;
} 

/**************************************************************************** 
* 
* ������: DIBSectionToDIB() 
* 
* ����:  ��DIBƬ�ϴ���DIB
* 
* ����:  HBITMAP - DIBƬ��ָ��,ΪNULL��ʾ���� 
* 
* ����ֵ:  HBITMAP hBitmap - DIB ���
* 
\****************************************************************************/ 
HDIB DIBSectionToDIB(HBITMAP hBitmap)
{
    HDC			 hDC = NULL, hSourceDC; 
	HBITMAP		 hOldSourceBitmap;
	HANDLE		 hNewDIB;
    LPBITMAPINFO lpbmi = NULL; 
	DWORD		 dwSize;
	DIBSECTION   ds;
    DWORD		 dwColorNum; 

	//�õ�DIB��Ϣ
	GetObject(hBitmap, sizeof(DIBSECTION), &ds);
    dwColorNum = ds.dsBmih.biClrUsed; 
    if (dwColorNum == 0 && ds.dsBmih.biBitCount <= 8) 
		dwColorNum = 1 << ds.dsBmih.biBitCount;

    //��BITMAPINFO �ṹ�����ڴ����DIB
	dwSize = sizeof(BITMAPINFOHEADER) + (dwColorNum * sizeof(RGBQUAD)) + ds.dsBmih.biSizeImage;
	hNewDIB = GlobalAlloc(GHND, dwSize);
	if (! hNewDIB)
		return NULL;
	lpbmi = (LPBITMAPINFO)GlobalLock(hNewDIB);
	if (! lpbmi)
		return NULL;
    lpbmi->bmiHeader.biSize = sizeof( BITMAPINFOHEADER ); 
    lpbmi->bmiHeader.biWidth = ds.dsBm.bmWidth; 
    lpbmi->bmiHeader.biHeight = ds.dsBm.bmHeight; 
    lpbmi->bmiHeader.biPlanes = 1; 
    lpbmi->bmiHeader.biBitCount = ds.dsBmih.biBitCount; 
    lpbmi->bmiHeader.biCompression = ds.dsBmih.biCompression; 
    lpbmi->bmiHeader.biSizeImage = ds.dsBmih.biSizeImage; 
    lpbmi->bmiHeader.biXPelsPerMeter = ds.dsBmih.biXPelsPerMeter; 
    lpbmi->bmiHeader.biYPelsPerMeter = ds.dsBmih.biYPelsPerMeter; 
    lpbmi->bmiHeader.biClrUsed = ds.dsBmih.biClrUsed; 
    lpbmi->bmiHeader.biClrImportant = ds.dsBmih.biClrImportant; 

	// Ϊ�����õ�DC
	hDC = GetDC( NULL ); 
 
	//�õ�DIBλ
    if (! GetDIBits(hDC,
                    hBitmap,
                    0L,
                    (DWORD)ds.dsBm.bmHeight,
                    (LPBYTE)lpbmi + (WORD)lpbmi->bmiHeader.biSize + (dwColorNum*sizeof(RGBQUAD)),
                    (LPBITMAPINFO)lpbmi, 
					(DWORD)DIB_RGB_COLORS))
	{
         GlobalUnlock(hNewDIB);
         ReleaseDC(NULL,hDC);
         return NULL;
    }

	// �ڴ�DC
    hSourceDC = CreateCompatibleDC( hDC ); 
    // ѡȡDIBƬ�ϵ�DCs 
    hOldSourceBitmap = (HBITMAP)SelectObject( hSourceDC, hBitmap ); 
 
    // ��DIBƬ���������ɫ��
    if( lpbmi->bmiHeader.biBitCount <= 8 ) 
        GetDIBColorTable( hSourceDC, 0, 1 << lpbmi->bmiHeader.biBitCount, lpbmi->bmiColors ); 
 
    SelectObject( hSourceDC, hOldSourceBitmap ); 
    DeleteDC( hSourceDC ); 
    ReleaseDC( NULL, hDC ); 
	GlobalUnlock(hNewDIB);
 
    return hNewDIB; 
}


/************************************************************************* 
 * 
 * ������:CopyScreenToBitmap() 
 * 
 * ����:������Ļ��Bitmap
 *  
 * ����: 
 * 
 * LPRECT lpRect    - ָ���Ĵ�������
 * 
 * Return Value: 
 * 
 * HDIB             - �����豸��bitmap��� 
 * 
 ************************************************************************/

HBITMAP CopyScreenToBitmap(LPRECT lpRect) 
{ 
   // ��ĻDC���ڴ�DC 
    HDC         hScrDC, hMemDC;        
   //�����豸��bitmaps 
    HBITMAP     hBitmap, hOldBitmap;    

    int         nX, nY, nX2, nY2;       
    // DIB ��Ⱥ͸߶�
    int         nWidth, nHeight;       
   // ��Ļ��
    int         xScrn, yScrn;         
 
 
    if (IsRectEmpty(lpRect)) 
      return NULL; 
 
     
    hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL); 
    hMemDC = CreateCompatibleDC(hScrDC); 
 
 
    nX = lpRect->left; 
    nY = lpRect->top; 
    nX2 = lpRect->right; 
    nY2 = lpRect->bottom; 
 
    //�õ���Ļģʽ
    xScrn = GetDeviceCaps(hScrDC, HORZRES); 
    yScrn = GetDeviceCaps(hScrDC, VERTRES); 
 
    //ȷ��λͼ�������ǿɼ���
 
    if (nX < 0) 
        nX = 0; 
    if (nY < 0) 
        nY = 0; 
    if (nX2 > xScrn) 
        nX2 = xScrn; 
    if (nY2 > yScrn) 
        nY2 = yScrn; 
 
    nWidth = nX2 - nX; 
    nHeight = nY2 - nY; 
 
    // ����һ��bitmapʹ����Ļ����ģʽ 
    hBitmap = CreateCompatibleBitmap(hScrDC, nWidth, nHeight); 
 
    // ѡȡ��λͼ���ڴ�DC 
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap); 
 
    BitBlt(hMemDC, 0, 0, nWidth, nHeight, hScrDC, nX, nY, SRCCOPY); 
 
     hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap); 
 
    DeleteDC(hScrDC); 
    DeleteDC(hMemDC); 
 
    return hBitmap; 
} 


/************************************************************************* 
 * 
 * ������:CopyWindowToBitmap() 
 * 
 * ����: 
 * 
 * HWND hWnd        - ָ���Ĵ��ھ�� 
 * 
 * WORD fPrintArea  - ָ���Ĵ������ 
 * 
 *  ����ֵ:  
 * 
 * HDIB          - �����豸��bitmap��� 
 * 
 * ����: ����ָ�����ڵ�Bitmap
 * 
 * 
 ************************************************************************/  
HBITMAP CopyWindowToBitmap(HWND hWnd, WORD fPrintArea) 
{ 
    
	HBITMAP     hBitmap = NULL; 
 
    //��鴰�ھ��
     if (!hWnd) 
        return NULL; 
 
    switch (fPrintArea) 
    { 
    // �����������ڳߴ�
	case PW_WINDOW:  
        { 
            RECT    rectWnd; 
 
            //���Դ��ھ�����
 
            GetWindowRect(hWnd, &rectWnd); 
 
        
            hBitmap = CopyScreenToBitmap(&rectWnd); 
            break; 
        } 
         //�����ͻ��� 
        case PW_CLIENT: 
        { 
            RECT rectClient; 
            POINT pt1, pt2; 
 
            // �õ��ͻ����ߴ�
             GetClientRect(hWnd, &rectClient); 
 
            //ת��ͻ�������Ļ�� 
             pt1.x = rectClient.left; 
            pt1.y = rectClient.top; 
            pt2.x = rectClient.right; 
            pt2.y = rectClient.bottom; 
            ClientToScreen(hWnd, &pt1); 
            ClientToScreen(hWnd, &pt2); 
            rectClient.left = pt1.x; 
            rectClient.top = pt1.y; 
            rectClient.right = pt2.x; 
            rectClient.bottom = pt2.y; 
 
            // �õ��ͻ�����λͼ             
            hBitmap = CopyScreenToBitmap(&rectClient); 
            break; 
        } 
     // ��ʼ����ӡ���
        default:    
            return NULL; 
    } 
 
   return hBitmap; 
} 
 
 
/************************************************************************* 
 * 
 * ������:CopyClientRectToBitmap() 
 * 
 * ����: 
 * 
 * HWND hWnd        - ָ���Ĵ��ھ��
 * 
 * LPRECT lpRect    - ָ��Ҫ�����Ŀͻ������
 * 
 *  ����ֵ: 
 * 
 * HDIB             - �����豸��bitmap��� 
 * 
 * ����: 
 * 
 * �����������ͻ������ݵ�bitmap. 
 * 
 ************************************************************************/ 
HBITMAP CopyClientRectToBitmap(HWND hWnd, LPRECT lpRect) 
{ 
   HBITMAP     hBitmap = NULL;  
 
    if (!hWnd) 
        return NULL; 
 
    POINT   pt1, pt2; 

    pt1.x = lpRect->left; 
    pt1.y = lpRect->top; 
    pt2.x = lpRect->right; 
    pt2.y = lpRect->bottom; 
    ClientToScreen(hWnd, &pt1); 
    ClientToScreen(hWnd, &pt2); 
    lpRect->left = pt1.x; 
    lpRect->top = pt1.y; 
    lpRect->right = pt2.x; 
    lpRect->bottom = pt2.y; 

    // �õ��ͻ�����DIB
    hBitmap = CopyScreenToBitmap(lpRect); 
 
	//����lpRect
    pt1.x = lpRect->left; 
    pt1.y = lpRect->top; 
    pt2.x = lpRect->right; 
    pt2.y = lpRect->bottom; 
    ScreenToClient(hWnd, &pt1); 
    ScreenToClient(hWnd, &pt2); 
    lpRect->left = pt1.x; 
    lpRect->top = pt1.y; 
    lpRect->right = pt2.x; 
    lpRect->bottom = pt2.y; 
 
   return hBitmap; 
} 
 
/************************************************************************* 
 * 
 * ������:CopyScreenToDIB() 
 * 
 * ����:
 * 
 * LPRECT lpRect    - ָ���Ĵ�������
 * 
 *  ����ֵ:  
 * 
 * HDIB             - �����豸��bitmap��� 
 * 
 * ����:
 * 
 * ������Ļָ��������bitmap. 
 * 
 ************************************************************************/ 
HDIB CopyScreenToDIB(LPRECT lpRect) 
{ 
    HBITMAP     hBitmap;       
    HPALETTE    hPalette;       
    HDIB        hDIB = NULL;   
 
    //�õ��豸���DDB
     hBitmap = CopyScreenToBitmap(lpRect); 
 
    if (!hBitmap) 
      return NULL; 
 
    //�õ���ǰ��ɫ�� 
    hPalette = GetSystemPalette(); 
 
    // ת��DDB��DIB
     hDIB = BitmapToDIB(hBitmap, hPalette); 
 
    DeleteObject(hPalette); 
    DeleteObject(hBitmap); 
 
    return hDIB; 
} 
 
/************************************************************************* 
 * 
 * ������:CopyWindowToDIB() 
 * 
 * ����:
 * 
 * HWND hWnd        - ָ���Ĵ��ھ�� 
 * 
 * WORD fPrintArea  - ָ���Ĵ������
 * 
 * ����ֵ:  
 * 
 * HDIB             - �����豸��bitmap��� 
 * 
 * ����:
 * 
 * ��������ָ���Ĳ��ݵ�bitmap
 * 
 ************************************************************************/ 
HDIB CopyWindowToDIB(HWND hWnd, WORD fPrintArea) 
{ 
   HDIB     hDIB = NULL;  
 
    if (!hWnd) 
        return NULL; 
 
    switch (fPrintArea) 
    { 
    // ����������Ļ
	case PW_WINDOW:
        { 
            RECT    rectWnd; 
 
            //�ᵽ���ڳߴ�
             GetWindowRect(hWnd, &rectWnd); 
 
            //�õ����ڵ�DIB
            hDIB = CopyScreenToDIB(&rectWnd); 
            break; 
        } 
        // �����ͻ���
        case PW_CLIENT:
        { 
            RECT    rectClient; 
            POINT   pt1, pt2; 
 
            // �õ��ͻ������
             GetClientRect(hWnd, &rectClient); 
 
            pt1.x = rectClient.left; 
            pt1.y = rectClient.top; 
            pt2.x = rectClient.right; 
            pt2.y = rectClient.bottom; 
            ClientToScreen(hWnd, &pt1); 
            ClientToScreen(hWnd, &pt2); 
            rectClient.left = pt1.x; 
            rectClient.top = pt1.y; 
            rectClient.right = pt2.x; 
            rectClient.bottom = pt2.y; 
 
            // �ӿͻ����õ�DIB 
            hDIB = CopyScreenToDIB(&rectClient); 
            break; 
        } 
       
        default:   
            return NULL; 
    } 
 
  
   return hDIB; 
} 
 
/************************************************************************* 
 * 
 * ������:CopyClientRectToDIB() 
 * 
 * ����:
 * 
 * HWND hWnd        - ָ���Ĵ��ھ�� 
 * 
 * LPRECT lpRect    - ָ���ͻ���������
 * 
 * ����ֵ: 
 * 
 * HDIB             - �����豸��bitmap��� 
 * 
 * ����:
 * 
 *  �����ͻ�����ָ�����ݵ�bitmap
 * 
 ************************************************************************/ 
HDIB CopyClientRectToDIB(HWND hWnd, LPRECT lpRect) 
{ 
   HDIB     hDIB = NULL;  // handle to DIB 
 
    if (!hWnd) 
        return NULL; 
 
    POINT   pt1, pt2; 

    pt1.x = lpRect->left; 
    pt1.y = lpRect->top; 
    pt2.x = lpRect->right; 
    pt2.y = lpRect->bottom; 
    ClientToScreen(hWnd, &pt1); 
    ClientToScreen(hWnd, &pt2); 


	// ����������ھ��η�Χ������е�
	CRect rcWnd;
	GetWindowRect(hWnd, &rcWnd);
	pt1.x = pt1.x >= rcWnd.left ? pt1.x : rcWnd.left;
	pt1.x = pt1.x >= rcWnd.right ? rcWnd.right : pt1.x;
	pt1.y = pt1.y >= rcWnd.top ? pt1.y : rcWnd.top;
	pt1.y = pt1.y >= rcWnd.bottom ? rcWnd.bottom : pt1.y;
	pt2.x = pt2.x >= rcWnd.left ? pt2.x : rcWnd.left;
	pt2.x = pt2.x >= rcWnd.right ? rcWnd.right : pt2.x;
	pt2.y = pt2.y >= rcWnd.top ? pt2.y : rcWnd.top;
	pt2.y = pt2.y >= rcWnd.bottom ? rcWnd.bottom : pt2.y;


    lpRect->left = pt1.x; 
    lpRect->top = pt1.y; 
    lpRect->right = pt2.x; 
    lpRect->bottom = pt2.y; 

    //�õ��ͻ���DIB
    hDIB = CopyScreenToDIB(lpRect); 
 
	//��������
    pt1.x = lpRect->left; 
    pt1.y = lpRect->top; 
    pt2.x = lpRect->right; 
    pt2.y = lpRect->bottom; 
    ScreenToClient(hWnd, &pt1); 
    ScreenToClient(hWnd, &pt2); 
    lpRect->left = pt1.x; 
    lpRect->top = pt1.y; 
    lpRect->right = pt2.x; 
    lpRect->bottom = pt2.y; 
 
   return hDIB; 
} 

 
/************************************************************************* 
 * 
 * ������:PaintDIB() 
 * 
 * ����:
 * 
 * HDC hDC          - �����HDC���
 * 
 * LPRECT lpDCRect  - DC�������
 * 
 * HDIB hDIB        - �ڴ�HDIB���
 * 
 * LPRECT lpDIBRect - DIB���ε����lpDCRect 
 *
 * HPALETTE hPal    - ��ʾDIBҪʹ�õĵ�ɫ��
 *
 * DWORD dwRop      - ��ʾDIB��ROPģʽ
 * 
 * ����ֵ: 
 * 
 * BOOL             - ����TRUE��ʾDIB����ȷ�� 
 * 
 * ����: 
 *  �����DC�ϻ�DIB.  
 * 
 * 
 ************************************************************************/ 
BOOL PaintDIB(HDC hDC, LPRECT lpDCRect, HDIB hDIB, LPRECT lpDIBRect, 
        HPALETTE hPal, DWORD dwRop)
{ 
   //BITMAPINFOHEADER �ṹָ��
    LPBYTE        lpDIBHdr;          
    //DIB����λָ��
    LPBYTE        lpDIBBits;      
    // �ɹ����
    BOOL         bSuccess=FALSE;   
    // �ɵ�ɫ��
    HPALETTE     hOldPal=NULL;   
 
    // ���DIB���
    if (!hDIB) 
        return FALSE; 
    lpDIBHdr  = (LPBYTE)GlobalLock(hDIB); 
    lpDIBBits = FindDIBBits(lpDIBHdr); 
 
	// ���޵�ɫ��, ��DIB�д���һ��
    if (! hPal) 
		hPal = CreateDIBPalette(lpDIBHdr);

    // ѡȡ��ɫ�� 
    if (hPal) 
    { 
        hOldPal = SelectPalette(hDC, hPal, TRUE); 
        RealizePalette(hDC); 
    } 
  
    SetStretchBltMode(hDC, COLORONCOLOR); 
 
	bSuccess = StretchDIBits(hDC, 
							 lpDCRect->left, 
							 lpDCRect->top, 
							 RECTWIDTH(lpDCRect), 
							 RECTHEIGHT(lpDCRect), 
							 lpDIBRect->left, 
				             (int)DIBHeight(lpDIBHdr) - lpDIBRect->top - RECTHEIGHT(lpDIBRect), 
							 RECTWIDTH(lpDIBRect), 
							 RECTHEIGHT(lpDIBRect), 
							 lpDIBBits, 
							 (LPBITMAPINFO)lpDIBHdr, 
							 DIB_RGB_COLORS, 
							 SRCCOPY); 
 

    GlobalUnlock(hDIB); 
 
    if (hOldPal) 
		SelectPalette(hDC, hOldPal, FALSE); 
    return bSuccess; 
} 




/************************************************************************* 
 * 
 * ������:PaintBitmap() 
 * 
 * ����:
 * 
 * HDC hDC          - �����HDC���
 * 
 * LPRECT lpDCRect  - DC�������
 * 
 * HBITMAP hDDB     - �����豸��bitmap (DDB) 
 * 
* LPRECT lpDIBRect - DDB���ε����lpDCRect 
 *
 * HPALETTE hPal    - ��ʾDDBҪʹ�õĵ�ɫ��
 * 
 * ����ֵ:  
 * 
 * BOOL             - ����TRUE��ʾDDB����ȷ�� 
 * 
 * ����:
 * 
 *�����DC�ϻ�DDB.  
 * 
 ************************************************************************/ 
BOOL PaintBitmap(HDC hDC, LPRECT lpDCRect, HBITMAP hDDB,  LPRECT lpDDBRect,  
        HPALETTE hPal, DWORD dwRop)
{ 
    // �ڴ�DC 
    HDC         hMemDC;           
    //��ǰ��bitmap 
    HBITMAP     hOldBitmap;       
   //��ǰ�ĵ�ɫ��1 
    HPALETTE    hOldPal1 = NULL;   
   // ��ǰ�ĵ�ɫ��2
    HPALETTE    hOldPal2 = NULL; 

    BOOL        bSuccess = FALSE;  
 
    //�����ڴ�DC 
    hMemDC = CreateCompatibleDC (hDC); 
 
    if (!hMemDC) 
        return FALSE; 
 
    // �����ڵ�ɫ��,ѡȡ����ʼ���� 
     if (hPal) 
    { 
        hOldPal1 = SelectPalette(hMemDC, hPal, TRUE); 
        hOldPal2 = SelectPalette(hDC, hPal, TRUE); 
        RealizePalette(hDC); 
    } 
 
    // ѡλͼ���ڴ�DC��
     hOldBitmap = (HBITMAP)SelectObject (hMemDC, hDDB); 
 
    SetStretchBltMode (hDC, COLORONCOLOR); 
    if ((RECTWIDTH(lpDCRect)  == RECTWIDTH(lpDDBRect)) && 
            (RECTHEIGHT(lpDCRect) == RECTHEIGHT(lpDDBRect))) 
        bSuccess = BitBlt(hDC, lpDCRect->left, lpDCRect->top, 
                lpDCRect->right - lpDCRect->left, 
                lpDCRect->bottom - lpDCRect->top, hMemDC, lpDDBRect->left, 
                lpDDBRect->top, dwRop); 
    else 
        bSuccess = StretchBlt(hDC, lpDCRect->left,  lpDCRect->top,  
                lpDCRect->right - lpDCRect->left, 
                lpDCRect->bottom - lpDCRect->top, hMemDC, lpDDBRect->left,  
                lpDDBRect->top,  lpDDBRect->right - lpDDBRect->left, 
                lpDDBRect->bottom - lpDDBRect->top, dwRop); 
 
 
    SelectObject(hMemDC, hOldBitmap); 
 
    if (hOldPal1) 
        SelectPalette (hMemDC, hOldPal1, FALSE); 
 
    if (hOldPal2) 
        SelectPalette (hDC, hOldPal2, FALSE); 
 
    DeleteDC (hMemDC); 
  
    return bSuccess; 
} 

/************************************************************************* 
 * 
 * ������:DisplayPalette () 
 * 
 * ����: 
 * 
 * HDC hDC          - ��ʾ��ɫ����豸������
 * LPRECT lpRect      -��ʾ��ɫ�������
 * HPALETTE hPal     - Ҫ��ʾ�ĵ�ɫ����
 * 
 * ����ֵ: 
 * 
 * BOOL            - ����TRUE��ʾ�ɹ������� FALSE��ʾʧ��
 * 
 * ����: 
 * 
 * ��ʾ��ɫ�����豸��������ָ�������� 
 * 
 ************************************************************************/ 
BOOL DisplayPalette(HDC hDC, LPRECT lpRect, HPALETTE hPal)
{
	if (! hPal)
		return FALSE;

	int nEntries;
	PALETTEENTRY pe[256];
	nEntries = GetPaletteEntries(hPal, 0, 256, pe);
	int nSqr = (int)sqrt((double)nEntries);

	int nWidth = (lpRect->right-lpRect->left)/nSqr;
	int nHeight = (lpRect->bottom-lpRect->top)/nSqr;
	lpRect->right = lpRect->left + nWidth*nSqr;
	lpRect->bottom = lpRect->top + nHeight*nSqr;

	HPALETTE hOldPal = (HPALETTE)SelectPalette(hDC, hPal, FALSE);
	RealizePalette(hDC);

	HBRUSH hBrush, hOldBrush;
	int x, y;
	for (int i=0; i<nEntries; ++i)
	{
		x = i%nSqr;
		y = i/nSqr;
		hBrush = CreateSolidBrush(RGB(pe[i].peRed, pe[i].peGreen, pe[i].peBlue));
		hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Rectangle(hDC, 
			      lpRect->left + x*nWidth, 
				  lpRect->top + y*nHeight, 
				  lpRect->left + (x+1)*nWidth, 
				  lpRect->top + (y+1) *nHeight);
		SelectObject(hDC, hOldBrush);
		DeleteObject(hBrush);
	}
	
	SelectPalette(hDC, hOldPal, FALSE);

	return TRUE;
}

/************************************************************************* 
 * 
 * ������:CopyPalette () 
 * 
 * ����:
 * 
 * HPALETTE hPalSrc    - ��Դ��ɫ����
 * 
 *����ֵ: 
 * 
 * HPALETTE          - Ŀ�ĵ�ɫ����
 * 
 * ����:
 * 
 * ������ɫ�嵽��һ��ɫ��
 * 
 ************************************************************************/ 
HPALETTE CopyPalette(HPALETTE hPalSrc)
{
    PLOGPALETTE     plogPal;
    int             iNumEntries=0;
    HPALETTE        hPal;
	HANDLE			h;

	iNumEntries = GetPaletteEntries(hPalSrc, 0, iNumEntries, NULL);
    if (iNumEntries == 0) 
        return (HPALETTE) NULL;

	h = GlobalAlloc(GHND, sizeof(DWORD) + sizeof(PALETTEENTRY)*iNumEntries);
	if (! h)
        return (HPALETTE) NULL;
	plogPal = (PLOGPALETTE)GlobalLock(h);
    if (! plogPal) 
        return (HPALETTE) NULL;

    plogPal->palVersion = 0x300;
    plogPal->palNumEntries = (WORD) iNumEntries;
    GetPaletteEntries(hPalSrc, 0, iNumEntries, plogPal->palPalEntry);
    hPal = CreatePalette(plogPal);

    GlobalUnlock(h);
    GlobalFree(h);

    return hPal;
}
 

/************************************************************************* 
 * 
 * ������:PalEntriesOnDevice() 
 * 
 * ����:
 * 
 * HDC hDC          - �豸������
 * 
 * ����ֵ: 
 * 
 * int              - �豸��ɫ�������
 * 
 * ����:
 * 
 * �õ�ϵͳ�豸��ɫ�������
 * 
 ************************************************************************/ 
int PalEntriesOnDevice(HDC hDC) 
{ 
	//��ɫ��
    int nColors; 
 
    // ���豸�з�����ɫ��     
    nColors = (1 << (GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES))); 
 
    assert(nColors); 
    return nColors; 
} 
 
 
/************************************************************************* 
 * 
 * ������:GetSystemPalette() 
 * 
 * ����: 
 * 
 * 
 * ����ֵ:  
 * 
 * HPALETTE         - Ҫ���Ƶĵ�ǰϵͳ��ɫ�� 
 * 
 * ����:
 * 
 *�õ���ǰϵͳ��ɫ��
 * 
 ************************************************************************/ 
HPALETTE GetSystemPalette(void) 
{ 
    HDC hDC;                
    static HPALETTE hPal = NULL;   
    HANDLE hLogPal;        
    LPLOGPALETTE lpLogPal;  
    int nColors;            

     hDC = GetDC(NULL); 
 
    if (!hDC) 
        return NULL; 
    // ��ɫ������
    nColors = PalEntriesOnDevice(hDC);   
 
    //�����ڴ����ɫ�岢������
     hLogPal = GlobalAlloc(GHND, sizeof(LOGPALETTE) + nColors * 
            sizeof(PALETTEENTRY)); 
 
    if (!hLogPal) 
        return NULL; 
 
    //�õ��߼���ɫ���ָ�� 
    lpLogPal = (LPLOGPALETTE)GlobalLock(hLogPal); 
 
     lpLogPal->palVersion = PALVERSION; 
    lpLogPal->palNumEntries = nColors; 
 
    // ����ϵͳ��ɫ�嵽�߼���ɫ����
     GetSystemPaletteEntries(hDC, 0, nColors, 
            (LPPALETTEENTRY)(lpLogPal->palPalEntry)); 
 
    hPal = CreatePalette(lpLogPal); 
 
    GlobalUnlock(hLogPal); 
    GlobalFree(hLogPal); 
    ReleaseDC(NULL, hDC); 
 
    return hPal; 
} 
 
/************************************************************************* 
 * 
 * ������:CreateIdentifyPalette () 
 * 
 * ����: 
 * 
 * HPALETTE hPalSrc    - ��Դ��ɫ����
 * 
 * ����ֵ: 
 * 
 * HPALETTE          - Ŀ�ĵ�ɫ���� 
 * 
 * ����: 
 * 
 * ����Դ��ɫ���д���һ��Ŀ�ĵ�ɫ�� 
 * 
 ************************************************************************/ 
HPALETTE CreateIdentifyPalette(HPALETTE hPalSrc)
{
    BOOL bResult = FALSE;
    int i, iSysColors, iPalEntries;
    HPALETTE hPalette, hpalOld;

	if (! hPalSrc)
		return NULL;

	//����һ���µ�ɫ��
	hPalette = CopyPalette(hPalSrc);

    //�õ���ĻDC
    HDC hdcScreen = GetDC(NULL);
    ASSERT(hdcScreen);

    if (!(GetDeviceCaps(hdcScreen, RASTERCAPS) & RC_PALETTE)) 
	{
        TRACE("Not a palettized device");
        goto abort;
    }

    // �õ�ϵͳ��ɫ���͵�ɫ����
     iSysColors = GetDeviceCaps(hdcScreen, NUMCOLORS);
    iPalEntries = GetDeviceCaps(hdcScreen, SIZEPALETTE);

    //�򳬹�256ɫ
    if (iSysColors > 256) goto abort;
    SetSystemPaletteUse(hdcScreen, SYSPAL_NOSTATIC);
    SetSystemPaletteUse(hdcScreen, SYSPAL_STATIC);

    hpalOld = ::SelectPalette(hdcScreen,
                              hPalette, 
                              FALSE);
    ::RealizePalette(hdcScreen);
    // ����ɵĵ�ɫ��
    ::SelectPalette(hdcScreen, hpalOld, FALSE);

    PALETTEENTRY pe[256];
    GetSystemPaletteEntries(hdcScreen, 
                            0,
                            iPalEntries,
                            pe);


    for (i = 0; i < iSysColors/2; i++) {
        pe[i].peFlags = 0;
    }
    for (; i < iPalEntries-iSysColors/2; i++) {
        pe[i].peFlags = PC_NOCOLLAPSE;
    }
    for (; i < iPalEntries; i++) {
        pe[i].peFlags = 0;
    }

    ResizePalette(hPalette, iPalEntries);

    // ���µ�ɫ��
    SetPaletteEntries(hPalette, 0, iPalEntries, pe);
    bResult = TRUE;

abort:
    ::ReleaseDC(NULL, hdcScreen);
    return bResult ? hPalette : NULL;
}

/************************************************************************* 
 * 
 * ������:MapDIBColorsToPalette () 
 * 
 * ����: 
 * 
 * HDIB hDIB		    - DIB ���
 * HPALETTE hPalette    - ��ɫ����
 * 
 * ����ֵ: 
 * 
 * HPALETTE          - Ŀ�ĵ�ɫ����
 * 
 * ����: 
 * 
 * �ø����ĵ�ɫ�廭��ɫ 
 * 
 ************************************************************************/ 
BOOL MapDIBColorsToPalette(HDIB hDIB, HPALETTE hPalette)
{
    if (! hDIB)
        return FALSE;
    if (! hPalette)
        return FALSE;

    LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);
    if (! lpbi)
        return FALSE;
    LPRGBQUAD pctThis = (LPRGBQUAD)((LPBYTE)lpbi + lpbi->biSize);

    // ����һ������ת����DIB��ɫ
    BYTE imap[256];
    for (int i = 0; i < 256; i++) 
	{
        imap[i] = (BYTE)GetNearestPaletteIndex(hPalette, 
									RGB(pctThis->rgbRed,
										pctThis->rgbGreen,
										pctThis->rgbBlue));
        pctThis++;
    }
    // ��DIBλ
    LPBYTE pBits = (LPBYTE)lpbi + lpbi->biSize + PaletteSize((LPBYTE)lpbi);
    int iSize = WIDTHBYTES1(lpbi->biBitCount*lpbi->biWidth) * lpbi->biHeight;
    while (iSize--) 
	{
        *pBits = imap[*pBits];
        pBits++;
    }

    //��Э��DIB��ɫ��
    PALETTEENTRY pe[256];
    GetPaletteEntries(hPalette, 0, 256, pe);
    pctThis = (LPRGBQUAD)((LPBYTE)lpbi + lpbi->biSize);
    for (int i = 0; i < 256; i++) 
	{
        pctThis->rgbRed = pe[i].peRed;    
        pctThis->rgbGreen = pe[i].peGreen;    
        pctThis->rgbBlue = pe[i].peBlue;
        pctThis++;    
    }
	
	GlobalUnlock(hDIB);
    return TRUE;
}

/************************************************************************* 
 * 
 * ������:DrawTransparentBitmap () 
 * 
 * ����: 
 * 
 * HDC hDC          - �����CDC���
 * 
 * HBITMAP hBitmap    - ��͸��λͼ�ľ��
 * 
 * LONG xStart, yStart   - ��ʼ���������
 *
 * COLORREF cTransparentColor - ͸����ɫ��RGBֵ 
 * ����ֵ: 
 * 
 * ����: 
 *		 ��һ͸��λͼ
 * 
 ************************************************************************/ 
void DrawTransparentBitmap(HDC hdc, HBITMAP hBitmap, 
						   LONG xStart, LONG yStart, 
						   COLORREF cTransparentColor)
{
   BITMAP     bm;
   COLORREF   cColor;
   HBITMAP    bmAndBack, bmAndObject, bmAndMem, bmSave;
   HBITMAP    bmBackOld, bmObjectOld, bmMemOld, bmSaveOld;
   HDC        hdcMem, hdcBack, hdcObject, hdcTemp, hdcSave;
   POINT      ptSize;

   hdcTemp = CreateCompatibleDC(hdc);
  // ѡ��bitmap
   SelectObject(hdcTemp, hBitmap); 

   GetObject(hBitmap, sizeof(BITMAP), (LPBYTE)&bm);
   ptSize.x = bm.bmWidth;            
   ptSize.y = bm.bmHeight;           
   DPtoLP(hdcTemp, &ptSize, 1);     
                                    
   // ����һЩ DCs����ʱ����.
   hdcBack   = CreateCompatibleDC(hdc);
   hdcObject = CreateCompatibleDC(hdc);
   hdcMem    = CreateCompatibleDC(hdc);
   hdcSave   = CreateCompatibleDC(hdc);

   // Ϊÿһ��DC����bitmap�� DCs�Ǳ����ΪGDI����
   // ��ɫ DC
   bmAndBack   = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

   bmAndObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

   bmAndMem    = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
   bmSave      = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);

   // ÿ��DC����ѡȡһ��bitmap���󵽱����pixel����
   bmBackOld   = (HBITMAP)SelectObject(hdcBack, bmAndBack);
   bmObjectOld = (HBITMAP)SelectObject(hdcObject, bmAndObject);
   bmMemOld    = (HBITMAP)SelectObject(hdcMem, bmAndMem);
   bmSaveOld   = (HBITMAP)SelectObject(hdcSave, bmSave);

   //����ӳ��ģʽ
   SetMapMode(hdcTemp, GetMapMode(hdc));

   //����λͼ.
   BitBlt(hdcSave, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

   // ���ñ���ɫ
   cColor = SetBkColor(hdcTemp, cTransparentColor);
   BitBlt(hdcObject, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0,
          SRCCOPY);
   SetBkColor(hdcTemp, cColor);

   //������ת����
   BitBlt(hdcBack, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0,
          NOTSRCCOPY);

   //������DC�ı�����Ŀ����.
   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdc, xStart, yStart,
          SRCCOPY);

   //���λͼ��������
   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, SRCAND);

   BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcBack, 0, 0, SRCAND);

   BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCPAINT);

   //����Ŀ��λͼ����Ļ
   BitBlt(hdc, xStart, yStart, ptSize.x, ptSize.y, hdcMem, 0, 0,
          SRCCOPY);

   //������Դλͼ
   BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcSave, 0, 0, SRCCOPY);

   //ɾ���ڴ�DC
   DeleteObject(SelectObject(hdcBack, bmBackOld));
   DeleteObject(SelectObject(hdcObject, bmObjectOld));
   DeleteObject(SelectObject(hdcMem, bmMemOld));
   DeleteObject(SelectObject(hdcSave, bmSaveOld));

   //ɾ���ڴ� DCs.
   DeleteDC(hdcMem);
   DeleteDC(hdcBack);
   DeleteDC(hdcObject);
   DeleteDC(hdcSave);
   DeleteDC(hdcTemp);
}

/************************************************************************* 
 * 
 * ������:Fade() 
 * 
 * ����: 
 * 
 * int nDeltaR   -  ��ɫ�ı仯ֵ
 * int nDeltaG   -  ��ɫ�ı仯ֵ
 * int nDeltaB   -  ��ɫ�ı仯ֵ
 * BYTE rm		 -  ��ɫ�����ֵ
 * BYTE gm		 -  ��ɫ�����ֵ
 * BYTE bm		 -  ��ɫ�����ֵ
 * BYTE *r		 -  ��ɫֵ�仯���ֵָ��
 * BYTE *g		 -  ��ɫֵ�仯���ֵָ��
 * BYTE *b		 -  ��ɫֵ�仯���ֵָ��
 * 
 * ����ֵ: 
 *
 * BOOL          -  ����TRUE��ʾ�ɹ�������FALSE��ʾʧ��
 * 
 * ����: 
 * 
 * �仯 R, G, B��ֵ
 * 
 ************************************************************************/
BOOL Fade(int nDeltaR, int nDeltaG, int nDeltaB, 
		  BYTE rm, BYTE gm, BYTE bm,
		  BYTE *r, BYTE *g, BYTE *b)
{
	int R = *r + nDeltaR;
	int G = *g + nDeltaG;
	int B = *b + nDeltaB;

	if (nDeltaR < 0)
		*r = (BYTE)BOUND(R, rm, 255);
	else
		*r = (BYTE)BOUND(R, 0, rm);
	if (nDeltaG < 0)
		*g = (BYTE)BOUND(G, gm, 255);
	else
		*g = (BYTE)BOUND(G, 0, gm);
	if (nDeltaB < 0)
		*b = (BYTE)BOUND(B, bm, 255);
	else
		*b = (BYTE)BOUND(B, 0, bm);

	if (*r==rm && *g==gm && *b==bm)
		return TRUE;
	else
		return FALSE;
}


/************************************************************************* 
 * 
 * ������:Delay() 
 * 
 * ����: 
 * 
 * DWORD dwDelayTime   - �ӳٵĺ���
 * 
 * ����ֵ: none
 * 
 * ����: 
 * 
 * �����ӳ�ָ���ĺ����Խ�����һ��ָ����� 
 * �������������ݲ���
 ************************************************************************/ 
void Delay(DWORD dwDelayTime)
{
  // DWORD dwTimeBegin, dwTimeEnd;
  //  dwTimeBegin = timeGetTime();
  //  do
//	{
  //      dwTimeEnd = timeGetTime();
//	} while (dwTimeEnd - dwTimeBegin < dwDelayTime);
}

/************************************************************************* 
 * 
 * ������:CopyHandle() 
 * 
 * ����: 
 * 
 * HANDLE h         - ��Դ���
 * 
 * ����ֵ: 
 * 
 * HANDLE           - Ŀ����
 * 
 * ����: 
 * 
 * �����������һ�����
 ************************************************************************/ 
HANDLE CopyHandle(HANDLE h)
{
	if (h == NULL)
		return NULL;

	DWORD  dwLen = ::GlobalSize((HGLOBAL)h);
	HANDLE hCopy = ::GlobalAlloc(GHND, dwLen);
	if (hCopy == NULL)
		return NULL;

	void* lpCopy = ::GlobalLock((HGLOBAL) hCopy);
	void* lp     = ::GlobalLock((HGLOBAL) h);
	::CopyMemory(lpCopy, lp, dwLen);
	::GlobalUnlock(hCopy);
	::GlobalUnlock(h);

	return hCopy;
}

/************************************************************************* 
 * 
 * ������:CropBitmap() 
 * 
 * ����: 
 * 
 * HBITMAP hBitmap - ���ü���DDB���
 * LPRECT lpRect   - Ҫ�ü��ľ�����
 * 
 * ����ֵ: 
 * 
 * HDIB             - ��λͼ���
 * 
 * ����: 
 * 
 * �ü�ָ����DDB������, ����һ���ѱ��ü����DIB���
 * 
 ************************************************************************/ 
HBITMAP CropBitmap(HBITMAP hBitmap, LPRECT lpRect)
{
	WaitCursorBegin();

	//�õ���ǰDC
	HDC hDC = GetDC(NULL);
	// create bitmap
	HBITMAP hNewBmp = CreateCompatibleBitmap(hDC, RECTWIDTH(lpRect), RECTHEIGHT(lpRect));
	if (hNewBmp == NULL)
	{
		ReleaseDC(NULL, hDC);
		WaitCursorEnd();
		return NULL;
	}
	//�����ڴ�DC
	HDC hMemDC = CreateCompatibleDC(hDC);
	if (hMemDC == NULL)
	{
		ReleaseDC(NULL, hDC);
		DeleteObject(hNewBmp);
		WaitCursorEnd();
		return NULL;
	}
	HDC hSrcMemDC = CreateCompatibleDC(hDC);
	if (hSrcMemDC == NULL)
	{
		DeleteDC(hMemDC);
		ReleaseDC(NULL, hDC);
		DeleteObject(hNewBmp);
		WaitCursorEnd();
		return NULL;
	}

	//ѡȡ��λͼ���ڴ�DC
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hNewBmp);
	//ѡȡ��λͼ����ĻDCSrcMemDC
	HBITMAP hSrcOldBitmap = (HBITMAP)SelectObject(hSrcMemDC, hBitmap);

	//����λͼ�л���λͼ
	if (! BitBlt(hMemDC, 
				 0, 
				 0,
				 RECTWIDTH(lpRect), 
				 RECTHEIGHT(lpRect),
				 hSrcMemDC,
				 lpRect->left,
				 lpRect->top,
				 SRCCOPY))
	{
		SelectObject(hMemDC, hOldBitmap);
		SelectObject(hSrcMemDC, hSrcOldBitmap);
		DeleteDC(hMemDC);
		DeleteDC(hSrcMemDC);
		ReleaseDC(NULL, hDC);
		DeleteObject(hNewBmp);
		WaitCursorEnd();
		return NULL;
	}
	
	//�ָ�
	SelectObject(hMemDC, hOldBitmap);
	SelectObject(hSrcMemDC, hSrcOldBitmap);
	DeleteDC(hMemDC);
	DeleteDC(hSrcMemDC);
	ReleaseDC(NULL, hDC);
	WaitCursorEnd();

	return hNewBmp;
}

/************************************************************************* 
 * 
 * ������:CropDIB() 
 * 
 * ����: 
 * 
 * HDIB hDIB       - Ҫ���ü���DIB���
 * LPRECT lpRect   - ָ��Ҫ�ü�������
 * 
 * ����ֵ: 
 * 
 * HDIB             - ��DIB��� 
 * 
 * ����: 
 * 
 * �ü�ָ����DIB��ָ�����򲢷��ؾ��ü����DIB��ԴDIB���ֲ���
 * 
 ************************************************************************/ 
HDIB CropDIB(HDIB hDIB, LPRECT lpRect)
{
    LPBITMAPINFO lpbmi = NULL; 
    LPBYTE       lpSourceBits, lpTargetBits, lpResult; 
    HDC			 hDC = NULL, hSourceDC, hTargetDC; 
    HBITMAP      hSourceBitmap, hTargetBitmap, hOldTargetBitmap, hOldSourceBitmap; 
    DWORD        dwSourceBitsSize, dwTargetBitsSize, dwTargetHeaderSize; 
	int			 nWidth, nHeight;
	HDIB		 hNewDIB;
	DWORD		 dwSize;

	WaitCursorBegin();

	//�õ�DIBָ��
	if (! hDIB)
	{
		WaitCursorEnd();
		return NULL;
	}
	LPBITMAPINFO lpSrcDIB = (LPBITMAPINFO)GlobalLock(hDIB);
	if (! lpSrcDIB)
	{
		WaitCursorEnd();
		return NULL;
	}

    // ��������BITMAPINFO�ṹΪ��DIB 
    dwTargetHeaderSize = sizeof( BITMAPINFOHEADER ) + PaletteSize(lpSrcDIB); 
    lpbmi = (LPBITMAPINFO)malloc( dwTargetHeaderSize ); 
	memcpy(lpbmi, lpSrcDIB, dwTargetHeaderSize);
	nWidth = RECTWIDTH(lpRect);
	nHeight = RECTHEIGHT(lpRect);
    lpbmi->bmiHeader.biWidth = nWidth; 
    lpbmi->bmiHeader.biHeight = nHeight; 
 
	hDC = GetDC( NULL ); 
    hTargetBitmap = CreateDIBSection( hDC, lpbmi, DIB_RGB_COLORS, (VOID **)&lpTargetBits, NULL, 0 ); 
    hSourceBitmap = CreateDIBSection( hDC, lpSrcDIB, DIB_RGB_COLORS, (VOID **)&lpSourceBits, NULL, 0 ); 
    hSourceDC = CreateCompatibleDC( hDC ); 
    hTargetDC = CreateCompatibleDC( hDC ); 
 
    //������ԴDIBƬ�ε�ƥ�����ԴDIB 
    dwSourceBitsSize = lpSrcDIB->bmiHeader.biHeight * BytesPerLine((LPBYTE)&(lpSrcDIB->bmiHeader)); 
    dwTargetBitsSize = lpbmi->bmiHeader.biHeight * BytesPerLine((LPBYTE)&(lpbmi->bmiHeader)); 
    memcpy( lpSourceBits, FindDIBBits((LPBYTE)lpSrcDIB), dwSourceBitsSize ); 
    lpbmi->bmiHeader.biSizeImage = dwTargetBitsSize; 
 
    //ѡȡ��ԴDIBƬ�ε�DCs 
    hOldSourceBitmap = (HBITMAP)SelectObject( hSourceDC, hSourceBitmap ); 
    hOldTargetBitmap = (HBITMAP)SelectObject( hTargetDC, hTargetBitmap ); 
 
	//����λͼ������λͼ�� 
    BitBlt(hTargetDC, 0, 0, nWidth, nHeight, hSourceDC, lpRect->left, lpRect->top, SRCCOPY); 

    SelectObject( hSourceDC, hOldSourceBitmap ); 
    SelectObject( hTargetDC, hOldTargetBitmap ); 
    DeleteDC( hSourceDC ); 
    DeleteDC( hTargetDC ); 
    ReleaseDC( NULL, hDC ); 

    GdiFlush(); 
 
    // Ϊ��DIB�����㹻�ڴ� 
	dwSize = dwTargetHeaderSize + dwTargetBitsSize;
	hNewDIB = GlobalAlloc(GHND, dwSize);
    lpResult = (LPBYTE)GlobalLock(hNewDIB); 
    memcpy( lpResult, lpbmi, dwTargetHeaderSize ); 
    memcpy( FindDIBBits( (LPBYTE)lpResult ), lpTargetBits, dwTargetBitsSize ); 
 
    DeleteObject( hTargetBitmap ); 
    DeleteObject( hSourceBitmap ); 
    free( lpbmi ); 
	GlobalUnlock(hDIB);
	GlobalUnlock(hNewDIB);
	WaitCursorEnd();
 
    return hNewDIB;
}

/************************************************************************* 
 * 
 * ������:CutDIB() 
 * 
 * ����: 
 * 
 * HDIB hDIB       - Ҫ�����е�DIB���
 * LPRECT lpRect   - ָ�����õ�����
 * 
 * ����ֵ: 
 * 
 * HDIB             - ��DIB���
 * 
 * ����: 
 * ����DIBָ���ľ�������ԴDIB����
 * 
 * 
 ************************************************************************/ 
HDIB CutDIB(HDIB hDIB, LPRECT lpRect)
{
    LPBITMAPINFO lpbmi = NULL; 
    LPBYTE       lpTargetBits; 
    HDC			 hDC = NULL, hTargetDC; 
    HBITMAP      hTargetBitmap, hOldTargetBitmap; 
    DWORD        dwTargetBitsSize; 
	HDIB		 hNewDIB;

	WaitCursorBegin();

	// �õ���DIB���
	if (! hDIB)
	{
		WaitCursorEnd();
		return NULL;
	}
	hNewDIB = CopyHandle(hDIB);
	if (! hNewDIB)
	{
		WaitCursorEnd();
		return NULL;
	}

	hDC = GetDC( NULL ); 
    lpbmi = (LPBITMAPINFO)GlobalLock(hNewDIB); 
    hTargetBitmap = CreateDIBSection( hDC, lpbmi, DIB_RGB_COLORS, (VOID **)&lpTargetBits, NULL, 0 ); 
    hTargetDC = CreateCompatibleDC( hDC ); 
 
    //������ԴDIBƬ�ε�ƥ�����ԴDIB 
    dwTargetBitsSize = lpbmi->bmiHeader.biHeight * BytesPerLine((LPBYTE)&(lpbmi->bmiHeader)); 
    memcpy( lpTargetBits, FindDIBBits((LPBYTE)lpbmi), dwTargetBitsSize ); 

    //ѡȡ��ԴDIBƬ�ε� DCs 
    hOldTargetBitmap = (HBITMAP)SelectObject( hTargetDC, hTargetBitmap ); 
 
	//���ָ������
	HBRUSH hBrush = CreateSolidBrush(RGB(255,255,255));
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255,255,255));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hTargetDC, hBrush);
	HPEN hOldPen = (HPEN)SelectObject(hTargetDC, hPen);
	Rectangle(hTargetDC, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
	SelectObject(hTargetDC, hOldBrush);
	SelectObject(hTargetDC, hOldPen);

    SelectObject( hTargetDC, hOldTargetBitmap ); 
    DeleteDC( hTargetDC ); 
    ReleaseDC( NULL, hDC ); 
 
    GdiFlush(); 
 
    //����λ
    memcpy( FindDIBBits( (LPBYTE)lpbmi ), lpTargetBits, dwTargetBitsSize ); 

    DeleteObject( hTargetBitmap ); 
	GlobalUnlock(hNewDIB);
	WaitCursorEnd();
 
    return hNewDIB;
}

/************************************************************************* 
 * 
 * ������:MergeDIB() 
 * 
 * ����: 
 * 
 * HDIB hDIB1       - �ϲ�Ŀ���DIB���
 * HDIB hDIB2       - Ҫ�ϲ���DIB���
 * POINT ptTopLeft  - ��hDIB1�п�ʼ�ϲ���λ��(���Ͻ�����)
 * 
 * ����ֵ: 
 * 
 * HDIB             - �ϲ�����DIB�ľ�� 
 * 
 * ����: 
 * 
 * �ϲ��ڶ���DIB����һ��DIB���γ�һ���µ�DIB��ԴDIB����
 * 
 ************************************************************************/ 
HDIB MergeDIB(HDIB hDIB1, HDIB hDIB2, POINT ptTopLeft)
{
    LPBITMAPINFO lpbmi = NULL; 
    LPBYTE       lpSourceBits, lpTargetBits; 
    HDC			 hDC = NULL, hSourceDC, hTargetDC; 
    HBITMAP      hSourceBitmap, hTargetBitmap, hOldTargetBitmap, hOldSourceBitmap; 
    DWORD        dwTargetBitsSize, dwSourceBitsSize; 
	HDIB		 hNewDIB;
	int			 nWidth, nHeight;

	WaitCursorBegin();

	//�õ�DIBָ��
	if (! hDIB1 || ! hDIB2)
	{
		WaitCursorEnd();
		return NULL;
	}

	//��DIB
	hNewDIB = CopyHandle(hDIB1);
	if (! hNewDIB)
	{
		WaitCursorEnd();
		return NULL;
	}
    //��DIBָ��
    lpbmi = (LPBITMAPINFO)GlobalLock(hNewDIB);
	if (! lpbmi)
	{
		WaitCursorBegin();
		return NULL;
	}
	// DIB2 ������
	LPBITMAPINFO lpSrcDIB = (LPBITMAPINFO)GlobalLock(hDIB2);
	
	if (! lpSrcDIB)
	{
		GlobalUnlock(hNewDIB);
		DestroyDIB(hNewDIB);
		WaitCursorBegin();
		return NULL;
	}
	nWidth = DIBWidth(lpSrcDIB);
	nHeight = DIBHeight(lpSrcDIB);

	hDC = GetDC( NULL ); 
    hTargetBitmap = CreateDIBSection( hDC, lpbmi, DIB_RGB_COLORS, (VOID **)&lpTargetBits, NULL, 0 ); 
    hSourceBitmap = CreateDIBSection( hDC, lpSrcDIB, DIB_RGB_COLORS, (VOID **)&lpSourceBits, NULL, 0 ); 
    hSourceDC = CreateCompatibleDC( hDC ); 
    hTargetDC = CreateCompatibleDC( hDC ); 
 
    dwSourceBitsSize = lpSrcDIB->bmiHeader.biHeight * BytesPerLine((LPBYTE)&(lpSrcDIB->bmiHeader)); 
    dwTargetBitsSize = lpbmi->bmiHeader.biHeight * BytesPerLine((LPBYTE)&(lpbmi->bmiHeader)); 
    memcpy( lpSourceBits, FindDIBBits((LPBYTE)lpSrcDIB), dwSourceBitsSize ); 
    memcpy( lpTargetBits, FindDIBBits((LPBYTE)lpbmi), dwTargetBitsSize ); 

    // ѡȡ��ԴDIBƬ�ε� DCs  
    hOldSourceBitmap = (HBITMAP)SelectObject( hSourceDC, hSourceBitmap ); 
    hOldTargetBitmap = (HBITMAP)SelectObject( hTargetDC, hTargetBitmap ); 
 
	// �ϲ�
    BitBlt(hTargetDC, ptTopLeft.x, ptTopLeft.y, nWidth, nHeight, hSourceDC, 0, 0, SRCCOPY); 
 
    SelectObject( hSourceDC, hOldSourceBitmap ); 
    SelectObject( hTargetDC, hOldTargetBitmap ); 
    DeleteDC( hSourceDC ); 
    DeleteDC( hTargetDC ); 
    ReleaseDC( NULL, hDC ); 
 
 
    GdiFlush(); 
 
    // ����λ
    memcpy( FindDIBBits((LPBYTE)lpbmi), lpTargetBits, dwTargetBitsSize ); 
 
    DeleteObject( hTargetBitmap ); 
    DeleteObject( hSourceBitmap ); 
	GlobalUnlock(hDIB2);
	GlobalUnlock(hNewDIB);
	WaitCursorEnd();
 
    return hNewDIB;
}


/************************************************************************* 
 * 
 * ������:RotateBitmapNT() 
 * 
 * ����: 
 * 
 * hBitmap		- Ҫ��ת��Bitmap
 * fDegrees		- ��ת�ĽǶ�
 * clrBack		- �������ɫ����תʱ��������ԴDIB
 * 
 * ����ֵ: 
 * 
 * HBITMAP            - �����µ��Ѿ���ת��bitmap���
 * 
 * ����: 
 * 
 * ��תλͼ
 * 
 ************************************************************************/ 
HBITMAP RotateBitmapNT(HBITMAP hBitmap, double fDegrees, COLORREF clrBack)
{
	//�����ڴ�DC������ʾ 
	CDC sourceDC, destDC;
	sourceDC.CreateCompatibleDC( NULL );
	destDC.CreateCompatibleDC( NULL );

	//�õ��߼�����ֵ
	BITMAP bm;
	::GetObject( hBitmap, sizeof( bm ), &bm );
	
	// ת���Ƕ�Ϊ����
	#define PI		3.1415926535798932
	double radians = (fDegrees/90.0)*(PI/2);

	float cosine = (float)cos(radians);
	float sine = (float)sin(radians);

	//������ת���λͼ�ߴ�
	int x1 = (int)(bm.bmHeight * sine);
	int y1 = (int)(bm.bmHeight * cosine);
	int x2 = (int)(bm.bmWidth * cosine + bm.bmHeight * sine);
	int y2 = (int)(bm.bmHeight * cosine - bm.bmWidth * sine);
	int x3 = (int)(bm.bmWidth * cosine);
	int y3 = (int)(-bm.bmWidth * sine);

	int minx = min(0,min(x1, min(x2,x3)));
	int miny = min(0,min(y1, min(y2,y3)));
	int maxx = max(0,max(x1, max(x2,x3)));
	int maxy = max(0,max(y1, max(y2,y3)));

	int w = maxx - minx;
	int h = maxy - miny;

	// ����λͼ
	HBITMAP hbmResult = ::CreateCompatibleBitmap(CClientDC(NULL), w, h);

	HBITMAP hbmOldSource = (HBITMAP)::SelectObject( sourceDC.m_hDC, hBitmap );
	HBITMAP hbmOldDest = (HBITMAP)::SelectObject( destDC.m_hDC, hbmResult );

	//���仯ӳ��ģʽʱ
	HBRUSH hbrBack = CreateSolidBrush( clrBack );
	HBRUSH hbrOld = (HBRUSH)::SelectObject( destDC.m_hDC, hbrBack );
	destDC.PatBlt( 0, 0, w, h, PATCOPY );
	::DeleteObject( ::SelectObject( destDC.m_hDC, hbrOld ) );

	SetGraphicsMode(destDC.m_hDC, GM_ADVANCED);
	XFORM xform;
	xform.eM11 = cosine;
	xform.eM12 = -sine;
	xform.eM21 = sine;
	xform.eM22 = cosine;
	xform.eDx = (float)-minx;
	xform.eDy = (float)-miny;

	SetWorldTransform( destDC.m_hDC, &xform );

	destDC.BitBlt(0,0,bm.bmWidth, bm.bmHeight, &sourceDC, 0, 0, SRCCOPY );

	::SelectObject( sourceDC.m_hDC, hbmOldSource );
	::SelectObject( destDC.m_hDC, hbmOldDest );

	return hbmResult;
}

/************************************************************************* 
 * 
 * ������:RotateBitmap() 
 * 
 * ����: 
 * 
 * hBitmap		- Ҫ��ת��Bitmap
 * fDegrees		- ��ת�ĽǶ�
 * clrBack		- �������ɫ����תʱ��������ԴDIB
 * 
 * ����ֵ: 
 * 
 * HBITMAP      - �����µ��Ѿ���ת��bitmap���
 * 
 * ����: 
 * 
 * ��תλͼ
 * 
 ************************************************************************/ 
HBITMAP RotateBitmap(HBITMAP hBitmap, double fDegrees, COLORREF clrBack)
{
	//����һ���ڴ�DC������ʾ
	CDC sourceDC, destDC;
	sourceDC.CreateCompatibleDC( NULL );
	destDC.CreateCompatibleDC( NULL );

	BITMAP bm;
	::GetObject( hBitmap, sizeof( bm ), &bm );

	double radians = (fDegrees/90.0)*(PI/2);

	float cosine = (float)cos(radians);
	float sine = (float)sin(radians);


	int x1 = (int)(-bm.bmHeight * sine);
	int y1 = (int)(bm.bmHeight * cosine);
	int x2 = (int)(bm.bmWidth * cosine - bm.bmHeight * sine);
	int y2 = (int)(bm.bmHeight * cosine + bm.bmWidth * sine);
	int x3 = (int)(bm.bmWidth * cosine);
	int y3 = (int)(bm.bmWidth * sine);

	int minx = min(0,min(x1, min(x2,x3)));
	int miny = min(0,min(y1, min(y2,y3)));
	int maxx = max(x1, max(x2,x3));
	int maxy = max(y1, max(y2,y3));

	int w = maxx - minx;
	int h = maxy - miny;

	HBITMAP hbmResult = ::CreateCompatibleBitmap(CClientDC(NULL), w, h);

	HBITMAP hbmOldSource = (HBITMAP)::SelectObject( sourceDC.m_hDC, hBitmap );
	HBITMAP hbmOldDest = (HBITMAP)::SelectObject( destDC.m_hDC, hbmResult );

	HBRUSH hbrBack = CreateSolidBrush( clrBack );
	HBRUSH hbrOld = (HBRUSH)::SelectObject( destDC.m_hDC, hbrBack );
	destDC.PatBlt( 0, 0, w, h, PATCOPY );
	::DeleteObject( ::SelectObject( destDC.m_hDC, hbrOld ) );

	sourceDC.SetMapMode(MM_ISOTROPIC);
	sourceDC.SetWindowExt(1,1);
	sourceDC.SetViewportExt(1,-1);
	sourceDC.SetViewportOrg(0, bm.bmHeight-1);

	destDC.SetMapMode(MM_ISOTROPIC);
	destDC.SetWindowExt(1,1);
	destDC.SetViewportExt(1,-1);
	destDC.SetWindowOrg(minx, maxy);

	for( int y = miny; y < maxy; y++ )
	{
		for( int x = minx; x < maxx; x++ )
		{
			int sourcex = (int)(x*cosine + y*sine);
			int sourcey = (int)(y*cosine - x*sine);
			if( sourcex >= 0 && sourcex < bm.bmWidth && sourcey >= 0 
					&& sourcey < bm.bmHeight )
				destDC.SetPixel(x,y,sourceDC.GetPixel(sourcex,sourcey));
		}
	}

	::SelectObject( sourceDC.m_hDC, hbmOldSource );
	::SelectObject( destDC.m_hDC, hbmOldDest );

	return hbmResult;
}


/************************************************************************* 
 * 
 * ������:RotateDIB() 
 * 
 * ����: 
 * 
 * hDIB		     - Ҫ��ת��DIB
 * fDegrees		- ��ת�ĽǶ�
 * clrBack		- �������ɫ����תʱ��������ԴDIB
 * 
 * ����ֵ: 
 * 
 * HDIB      - �����µ��Ѿ���ת��DIB���
 * 
 * ����: 
 * 
 * ��תDIBλͼ
 * 
 ************************************************************************/ 
HDIB RotateDIB(HDIB hDIB, double fDegrees, COLORREF clrBack)
{
	WaitCursorBegin();

	//�õ���Դbitmap��Ϣ
	LPBITMAPINFO lpBmInfo = (LPBITMAPINFO)GlobalLock(hDIB);
	int bpp = lpBmInfo->bmiHeader.biBitCount;		
	
	int nColors = lpBmInfo->bmiHeader.biClrUsed ? lpBmInfo->bmiHeader.biClrUsed : 
					1 << bpp;
	int nWidth = lpBmInfo->bmiHeader.biWidth;
	int nHeight = lpBmInfo->bmiHeader.biHeight;
	int nRowBytes = ((((nWidth * bpp) + 31) & ~31) / 8);

	DWORD compression = lpBmInfo->bmiHeader.biCompression;
	if( nHeight < 0 || (compression!=BI_RGB))
	{
		GlobalUnlock(hDIB);
		WaitCursorEnd();
		return NULL;
	}

	LPBYTE lpDIBBits = FindDIBBits((LPBYTE)lpBmInfo);

	double radians = (fDegrees/90.0)*(PI/2);

	float cosine = (float)cos(radians);
	float sine = (float)sin(radians);

	int x1 = (int)(-nHeight * sine);
	int y1 = (int)(nHeight * cosine);
	int x2 = (int)(nWidth * cosine - nHeight * sine);
	int y2 = (int)(nHeight * cosine + nWidth * sine);
	int x3 = (int)(nWidth * cosine);
	int y3 = (int)(nWidth * sine);

	int minx = min(0,min(x1, min(x2,x3)));
	int miny = min(0,min(y1, min(y2,y3)));
	int maxx = max(x1, max(x2,x3));
	int maxy = max(y1, max(y2,y3));

	int w = maxx - minx;
	int h = maxy - miny;

	int nResultRowBytes = ((((w * bpp) + 31) & ~31) / 8);
	long len = nResultRowBytes * h;
	int nHeaderSize = ((LPBYTE)lpDIBBits-(LPBYTE)lpBmInfo) ;
	HANDLE hDIBResult = GlobalAlloc(GHND,len+nHeaderSize);
	//��ʼ��ͷ��Ϣ
	LPBITMAPINFO lpBmInfoResult = (LPBITMAPINFO)GlobalLock(hDIBResult);
	memcpy( (void*)lpBmInfoResult, (void*)lpBmInfo, nHeaderSize);
	lpBmInfoResult->bmiHeader.biWidth = w;
	lpBmInfoResult->bmiHeader.biHeight = h;
	lpBmInfoResult->bmiHeader.biSizeImage = len;

	LPBYTE lpDIBBitsResult = FindDIBBits((LPBYTE)lpBmInfoResult);

	// �õ�����ɫֵ(������)
	ZeroMemory( lpDIBBitsResult, len );
	DWORD dwBackColor;
	switch(bpp)
	{
	//��ɫ
	case 1:	
		if( clrBack == RGB(255,255,255) )
			memset( lpDIBBitsResult, 0xff, len );
		break;
    //������ɫ��
	case 4:
	case 8:	
		int i;
		for(i = 0; i < nColors; i++ )
		{
			if( lpBmInfo->bmiColors[i].rgbBlue ==  GetBValue(clrBack)
				&& lpBmInfo->bmiColors[i].rgbGreen ==  GetGValue(clrBack)
				&& lpBmInfo->bmiColors[i].rgbRed ==  GetRValue(clrBack) )
			{
				if(bpp==4) i = i | i<<4;
				memset( lpDIBBitsResult, i, len );
				break;
			}
		}
		// ��û�з�����Ϊ��ɫ
		break;
	case 16:
		if( *((DWORD*)lpBmInfo->bmiColors) == 0x7c00 )
		{
			dwBackColor = ((GetRValue(clrBack)>>3) << 10) + 
					((GetRValue(clrBack)>>3) << 5) +
					(GetBValue(clrBack)>>3) ;
		}
		else
		{
			dwBackColor = ((GetRValue(clrBack)>>3) << 11) + 
					((GetRValue(clrBack)>>2) << 5) +
					(GetBValue(clrBack)>>3) ;
		}
		break;
	case 24:
	case 32:
		dwBackColor = (((DWORD)GetRValue(clrBack)) << 16) | 
				(((DWORD)GetGValue(clrBack)) << 8) |
				(((DWORD)GetBValue(clrBack)));
		break;
	}

	for( int y = 0; y < h; y++ )
	{
		for( int x = 0; x < w; x++ )
		{
			int sourcex = (int)((x+minx)*cosine + (y+miny)*sine);
			int sourcey = (int)((y+miny)*cosine - (x+minx)*sine);
			if( sourcex >= 0 && sourcex < nWidth && sourcey >= 0 
				&& sourcey < nHeight )
			{
				//����Ŀ��DIB����
				switch(bpp)
				{
					BYTE mask;
				case 1:	
					mask = *((LPBYTE)lpDIBBits + nRowBytes*sourcey + 
						sourcex/8) & (0x80 >> sourcex%8);
					//����Ŀ������λͼ
					mask = mask ? (0x80 >> x%8) : 0;
					*((LPBYTE)lpDIBBitsResult + nResultRowBytes*(y) + 
								(x/8)) &= ~(0x80 >> x%8);
					*((LPBYTE)lpDIBBitsResult + nResultRowBytes*(y) + 
								(x/8)) |= mask;
					break;
				case 4:
					mask = *((LPBYTE)lpDIBBits + nRowBytes*sourcey + 
						sourcex/2) & ((sourcex&1) ? 0x0f : 0xf0);
						//����Ŀ������λͼ
					if( (sourcex&1) != (x&1) )
						mask = (mask&0xf0) ? (mask>>4) : (mask<<4);
					*((LPBYTE)lpDIBBitsResult + nResultRowBytes*(y) + 
							(x/2)) &= ~((x&1) ? 0x0f : 0xf0);
					*((LPBYTE)lpDIBBitsResult + nResultRowBytes*(y) + 
							(x/2)) |= mask;
					break;
				case 8:
					BYTE pixel ;
					pixel = *((LPBYTE)lpDIBBits + nRowBytes*sourcey + 
							sourcex);
					*((LPBYTE)lpDIBBitsResult + nResultRowBytes*(y) + 
							(x)) = pixel;
					break;
				case 16:
					DWORD dwPixel;
					dwPixel = *((LPWORD)((LPBYTE)lpDIBBits + 
							nRowBytes*sourcey + sourcex*2));
					*((LPWORD)((LPBYTE)lpDIBBitsResult + 
						nResultRowBytes*y + x*2)) = (WORD)dwPixel;
					break;
				case 24:
					dwPixel = *((LPDWORD)((LPBYTE)lpDIBBits + 
						nRowBytes*sourcey + sourcex*3)) & 0xffffff;
					*((LPDWORD)((LPBYTE)lpDIBBitsResult + 
						nResultRowBytes*y + x*3)) |= dwPixel;
					break;
				case 32:
					dwPixel = *((LPDWORD)((LPBYTE)lpDIBBits + 
						nRowBytes*sourcey + sourcex*4));
					*((LPDWORD)((LPBYTE)lpDIBBitsResult + 
						nResultRowBytes*y + x*4)) = dwPixel;
				}
			}
			else 
			{
				// ������ɫ.
				switch(bpp)
				{
				case 16:
					*((LPWORD)((LPBYTE)lpDIBBitsResult + 
						nResultRowBytes*y + x*2)) = 
						(WORD)dwBackColor;
					break;
				case 24:
					*((LPDWORD)((LPBYTE)lpDIBBitsResult + 
						nResultRowBytes*y + x*3)) |= dwBackColor;
					break;
				case 32:
					*((LPDWORD)((LPBYTE)lpDIBBitsResult + 
						nResultRowBytes*y + x*4)) = dwBackColor;
					break;
				}
			}
		}
	}

	GlobalUnlock(hDIB);
	GlobalUnlock(hDIBResult);
	WaitCursorEnd();

	return hDIBResult;
}

/************************************************************************* 
 * 
 * ������:RotateDIB() 
 * 
 * ����: 
 * 
 * hDIB		     - Ҫ��ת��DIB
 * 
 * ����ֵ: 
 * 
 * HDIB      - �����µ��Ѿ���ת��DIB���
 * 
 * ����: 
 * 
 * ��תDIBλͼ
 * 
 ************************************************************************/ 
HDIB RotateDIB(HDIB hDib)
{
	WaitCursorBegin();

	// ��DIB
	LPBYTE lpDIBSrc = (LPBYTE)GlobalLock(hDib);

	DWORD lSrcWidth = DIBWidth(lpDIBSrc);
	DWORD lSrcHeight = DIBHeight(lpDIBSrc);
	WORD wBitCount = ((LPBITMAPINFOHEADER)lpDIBSrc)->biBitCount;
	//λλ��
    LPBYTE lpOldBits = FindDIBBits(lpDIBSrc);

	//�õ���DIB�� bytes/pixel, bytes/��
	double fColorBytes = (double)((double)wBitCount/8.0);
	DWORD lSrcRowBytes = WIDTHBYTES1(lSrcWidth*((DWORD)wBitCount));
	DWORD lDestRowBytes = WIDTHBYTES1(lSrcHeight*((DWORD)wBitCount));

	//������DIB�ߴ�
	DWORD dwDataLength = GlobalSize(hDib);
	dwDataLength += lDestRowBytes*(lSrcWidth-1)+(DWORD)((lSrcHeight-1)*fColorBytes) - 
				  lSrcRowBytes*(lSrcHeight-1)+(DWORD)((lSrcWidth-1)*fColorBytes);
	HDIB hNewDib = GlobalAlloc(GHND, dwDataLength);
	if (! hNewDib)
	{
		WaitCursorEnd();
		return NULL;
	}
	//��DIB������
	LPBYTE lpDIB = (LPBYTE)GlobalLock(hNewDib);
	// �Ӿ�DIB����LPBITMAPINFO����DIB
	memcpy(lpDIB, lpDIBSrc, sizeof(BITMAPINFOHEADER)+PaletteSize(lpDIBSrc));
	// ������Ⱥ͸߶�
	((LPBITMAPINFOHEADER)lpDIB)->biHeight = lSrcWidth;
	((LPBITMAPINFOHEADER)lpDIB)->biWidth = lSrcHeight;
	// ������λ��λ��
	LPBYTE lpData = FindDIBBits(lpDIB);

	DWORD i, j;
	switch (wBitCount)
	{
	case 1:
		for (i=0; i<lSrcHeight; ++i)
		{
			for (j=0; j<lSrcWidth; ++j)
			{
				*(lpData+(lDestRowBytes*j+(lSrcHeight-i-1)/8)) &= ~(1<<(7-((lSrcHeight-i-1)%8)));
				*(lpData+(lDestRowBytes*j+(lSrcHeight-i-1)/8)) |= 
					((*(lpOldBits+(lSrcRowBytes*i+j/8))<<(j%8))>>7)<<(7-((lSrcHeight-i-1)%8));
			}
		}
		break;
	case 4:
		for (i=0; i<lSrcHeight; ++i)
		{
			for (j=0; j<lSrcWidth; ++j)
			{
				*(lpData+(lDestRowBytes*j+(lSrcHeight-i-1)/2)) &= ((lSrcHeight-i-1)%2) ? 0xf0 : 0x0f;
				*(lpData+(lDestRowBytes*j+(lSrcHeight-i-1)/2)) |= 
					((*(lpOldBits+(lSrcRowBytes*i+j/2))<<(j%2 ? 4 : 0))>>4)<<(((lSrcHeight-i-1)%2) ? 0 : 4);
			}
		}
		break;
	case 8:
		for (i=0; i<lSrcHeight; ++i)
		{
			for (j=0; j<lSrcWidth; ++j)
			{
				*(lpData+(lDestRowBytes*j+lSrcHeight-i-1))
					= *(lpOldBits+(lSrcRowBytes*i+j));
			}
		}
		break;
	case 24:
		for (i=0; i<lSrcHeight; ++i)
		{
			for (j=0; j<lSrcWidth; j++)
			{
				*(lpData+(lDestRowBytes*j+(lSrcHeight-i-1)*3))
					= *(lpOldBits+(lSrcRowBytes*i+j*3));
				*(lpData+(lDestRowBytes*j+(lSrcHeight-i-1)*3)+1)
					= *(lpOldBits+(lSrcRowBytes*i+j*3)+1);
				*(lpData+(lDestRowBytes*j+(lSrcHeight-i-1)*3)+2)
					= *(lpOldBits+(lSrcRowBytes*i+j*3)+2);
			}
		}
		break;
	}

	GlobalUnlock(hDib);
	GlobalUnlock(hNewDib);
	WaitCursorEnd();
	
	return hNewDib;
}

/************************************************************************* 
 * 
 * ������:FlipHorzDIB() 
 * 
 * ����: 
 * 
 * HDIB hDIB		 - Ҫ����ˮƽ�����DIB���
 * 
 * ����ֵ: 
 * 
 * HDIB             - �Ѿ�ˮƽ�����DIB��� 
 * 
 * ����: 
 * 
 * �������ؾ�ˮƽ�����DIBͼ�ξ�� ,��ԴDIB����
 * 
 ************************************************************************/ 
HDIB FlipHorzDIB(HDIB hDib)
{
	WaitCursorBegin();

	// ������DIB
	DWORD dwDataLength = GlobalSize(hDib);
	HDIB hNewDib = GlobalAlloc(GHND, dwDataLength);
	if (! hNewDib)
	{
		WaitCursorEnd();
		return NULL;
	}
	LPBYTE lpDIB = (LPBYTE)GlobalLock(hNewDib);
	if (lpDIB == NULL)
	{
		WaitCursorEnd();
		return FALSE;
	}
	// ��DIB ������
	LPBYTE lpDIBSrc = (LPBYTE)GlobalLock(hDib);

	//�Ӿ�DIB����LPBITMAPINFO����DIB
	memcpy(lpDIB, lpDIBSrc, sizeof(BITMAPINFOHEADER)+PaletteSize(lpDIBSrc));
	
	DWORD lSrcWidth = DIBWidth(lpDIBSrc);
	DWORD lSrcHeight = DIBHeight(lpDIBSrc);
	WORD wBitCount = ((LPBITMAPINFOHEADER)lpDIBSrc)->biBitCount;

	//�õ� bytes/pixel, bytes/��  
	double fColorBytes = (double)((double)wBitCount/8.0);
	DWORD lSrcRowBytes = WIDTHBYTES1(lSrcWidth*((DWORD)wBitCount));

	//λλ��
    LPBYTE lpOldBits = FindDIBBits(lpDIBSrc);
	LPBYTE lpData = FindDIBBits(lpDIB);
	DWORD i, j;
	switch (wBitCount)
	{
	case 1:
		for (i=0; i<lSrcHeight; ++i)
			for (j=0; j<lSrcWidth; ++j)
			{
				*(lpData+(lSrcRowBytes*i+(lSrcWidth-j-1)/8)) &= ~(1<<(7-((lSrcWidth-j-1)%8)));
				*(lpData+(lSrcRowBytes*i+(lSrcWidth-j-1)/8)) |= 
					((*(lpOldBits+(lSrcRowBytes*i+j/8))<<(j%8))>>7)<<(7-(lSrcWidth-j-1)%8);
			}
		break;
	case 4:
		for (i=0; i<lSrcHeight; ++i)
		{
			for (j=0; j<lSrcWidth; ++j)
			{
				*(lpData+(lSrcRowBytes*i+(lSrcWidth-j-1)/2)) &= ((lSrcWidth-j-1)%2) ? 0xf0 : 0x0f;
				*(lpData+(lSrcRowBytes*i+(lSrcWidth-j-1)/2)) |= 
					((*(lpOldBits+(lSrcRowBytes*i+j/2))<<(j%2 ? 4 : 0))>>4)<<(((lSrcWidth-j-1)%2) ? 0 : 4);
			}
		}
		break;
	case 8:
		for (i=0; i<lSrcHeight; ++i)
			for (j=0; j<lSrcWidth; ++j)
				*(lpData+(lSrcRowBytes*i+lSrcWidth-j-1))
					= *(lpOldBits+(lSrcRowBytes*i+j));
		break;
	case 24:
		for (i=0; i<lSrcHeight; ++i)
			for (j=0; j<lSrcWidth; j++)
			{
				*(lpData+(lSrcRowBytes*i+(lSrcWidth-j-1)*3))
					= *(lpOldBits+(lSrcRowBytes*i+j*3));
				*(lpData+(lSrcRowBytes*i+(lSrcWidth-j-1)*3)+1)
					= *(lpOldBits+(lSrcRowBytes*i+j*3)+1);
				*(lpData+(lSrcRowBytes*i+(lSrcWidth-j-1)*3)+2)
					= *(lpOldBits+(lSrcRowBytes*i+j*3)+2);
			}
		break;
	}

	GlobalUnlock(hDib);
	GlobalUnlock(hNewDib);
	WaitCursorEnd();

	return hNewDib;
}

/************************************************************************* 
 * 
 * ������:FlipVertDIB() 
 * 
 * ����: 
 * 
 * HDIB hDIB		 - Ҫ���д�ֱ�����DIB���
 * 
 * ����ֵ: 
 * 
 * HDIB             - �Ѿ���ֱ�����DIB��� 
 * 
 * ����: 
 * 
 * �������ؾ���ֱ�����DIBͼ�ξ�� ,��ԴDIB����
 * 
 ************************************************************************/ 
HDIB FlipVertDIB(HDIB hDib)
{
	WaitCursorBegin();

	// ������DIB
	DWORD dwDataLength = GlobalSize(hDib);
	HDIB hNewDib = GlobalAlloc(GHND, dwDataLength);
	if (! hNewDib)
	{
		WaitCursorEnd();
		return NULL;
	}
	LPBYTE lpDIB = (LPBYTE)GlobalLock(hNewDib);
	if (lpDIB == NULL)
	{
		WaitCursorEnd();
		return FALSE;
	}
	// ��DIB������
	LPBYTE lpDIBSrc = (LPBYTE)GlobalLock(hDib);

	// �Ӿ�DIB���� LPBITMAPINFO ����DIB 
	memcpy(lpDIB, lpDIBSrc, sizeof(BITMAPINFOHEADER)+PaletteSize(lpDIBSrc));
	
	DWORD lSrcWidth = DIBWidth(lpDIBSrc);
	DWORD lSrcHeight = DIBHeight(lpDIBSrc);
	WORD wBitCount = ((LPBITMAPINFOHEADER)lpDIBSrc)->biBitCount;

	//�õ��ֽ�λbytes/pixel, bytes/row  
	double fColorBytes = (double)((double)wBitCount/8.0);
	DWORD lSrcRowBytes = WIDTHBYTES1(lSrcWidth*((DWORD)wBitCount));

	// bits λ��
    LPBYTE lpOldBits = FindDIBBits(lpDIBSrc);
	LPBYTE lpData = FindDIBBits(lpDIB);

	for (DWORD i=0; i<lSrcHeight; ++i)
		for (DWORD j=0; j<lSrcRowBytes; ++j)
			*(lpData+(lSrcRowBytes*(lSrcHeight-i-1)+j))
				= *(lpOldBits+(lSrcRowBytes*i+j));

	GlobalUnlock(hDib);
	GlobalUnlock(hNewDib);
	WaitCursorEnd();

	return hNewDib;
}

/************************************************************************* 
 * 
 * ������:ChangeDIBSize() 
 * 
 * ����: 
 * 
 * HDIB hDIB				 - Ҫ�������ŵ�DIB���
 * int nWidth, int nHeight   - ���ź��DIB�ߴ�
 * 
 * ����ֵ: 
 * 
 * HDIB             - ��������DIB��� 
 * 
 * ����: 
 * 
 * ��������ָ����DIB���������ź��DIBͼ�ξ�� 
 * 
 ************************************************************************/ 
HDIB ChangeDIBSize(HDIB hDIB, int nWidth, int nHeight)
{
    LPBITMAPINFO lpbmi = NULL; 
    LPBYTE       lpSourceBits, lpTargetBits, lpResult; 
    HDC			 hDC = NULL, hSourceDC, hTargetDC; 
    HBITMAP      hSourceBitmap, hTargetBitmap, hOldTargetBitmap, hOldSourceBitmap; 
    DWORD        dwSourceBitsSize, dwTargetBitsSize, dwTargetHeaderSize; 
	HDIB		 hNewDIB;
	DWORD		 dwSize;

	WaitCursorBegin();

	//�õ�DIBָ��
	if (! hDIB)
	{
		WaitCursorEnd();
		return NULL;
	}
	LPBITMAPINFO lpSrcDIB = (LPBITMAPINFO)GlobalLock(hDIB);
	if (! lpSrcDIB)
	{
		WaitCursorEnd();
		return NULL;
	}

    //Ϊ��DIB����BITMAPINFO�ṹ 
    dwTargetHeaderSize = sizeof( BITMAPINFOHEADER ) + PaletteSize(lpSrcDIB); 
    lpbmi = (LPBITMAPINFO)malloc( dwTargetHeaderSize ); 
	memcpy(lpbmi, lpSrcDIB, dwTargetHeaderSize);
    lpbmi->bmiHeader.biWidth = nWidth; 
    lpbmi->bmiHeader.biHeight = nHeight; 
 
    //ʹ��DIBƬ�κ�BitBlt()��ת��
	hDC = GetDC( NULL ); 
    hTargetBitmap = CreateDIBSection( hDC, lpbmi, DIB_RGB_COLORS, (VOID **)&lpTargetBits, NULL, 0 ); 
    hSourceBitmap = CreateDIBSection( hDC, lpSrcDIB, DIB_RGB_COLORS, (VOID **)&lpSourceBits, NULL, 0 ); 
    hSourceDC = CreateCompatibleDC( hDC ); 
    hTargetDC = CreateCompatibleDC( hDC ); 
 
    dwSourceBitsSize = lpSrcDIB->bmiHeader.biHeight * BytesPerLine((LPBYTE)&(lpSrcDIB->bmiHeader)); 
    dwTargetBitsSize = lpbmi->bmiHeader.biHeight * BytesPerLine((LPBYTE)&(lpbmi->bmiHeader)); 
    memcpy( lpSourceBits, FindDIBBits((LPBYTE)lpSrcDIB), dwSourceBitsSize ); 
    lpbmi->bmiHeader.biSizeImage = dwTargetBitsSize; 
 
    //ѡȡDIBƬ�� ��DCs 
    hOldSourceBitmap = (HBITMAP)SelectObject( hSourceDC, hSourceBitmap ); 
    hOldTargetBitmap = (HBITMAP)SelectObject( hTargetDC, hTargetBitmap ); 
 
	//����λͼ���뵽��λͼ�� 
    SetStretchBltMode( hTargetDC, COLORONCOLOR ); 
    StretchBlt( hTargetDC, 0, 0, lpbmi->bmiHeader.biWidth, lpbmi->bmiHeader.biHeight, hSourceDC, 0, 0, lpSrcDIB->bmiHeader.biWidth, lpSrcDIB->bmiHeader.biHeight, SRCCOPY ); 

    SelectObject( hSourceDC, hOldSourceBitmap ); 
    SelectObject( hTargetDC, hOldTargetBitmap ); 
    DeleteDC( hSourceDC ); 
    DeleteDC( hTargetDC ); 
    ReleaseDC( NULL, hDC ); 
 

    GdiFlush(); 

	dwSize = dwTargetHeaderSize + dwTargetBitsSize;
	hNewDIB = GlobalAlloc(GHND, dwSize);
    lpResult = (LPBYTE)GlobalLock(hNewDIB);
    memcpy( lpResult, lpbmi, dwTargetHeaderSize ); 
    memcpy( FindDIBBits( (LPBYTE)lpResult ), lpTargetBits, dwTargetBitsSize ); 
 
    DeleteObject( hTargetBitmap ); 
    DeleteObject( hSourceBitmap ); 
    free( lpbmi ); 
	GlobalUnlock(hDIB);
	GlobalUnlock(hNewDIB);
	WaitCursorEnd();
 
    return hNewDIB;
}

/************************************************************************* 
 * 
 * ������:ChangeDIBCanvasSize() 
 * 
 * ����: 
 * 
 * HDIB hDIB				 - Ҫ�仯��DIB���
 * int nWidth, int nHeight   - DIB���»����ߴ�
 * int nPosition			 - ԴDIB���»���DIB�е�λ��
 * 
 * ����ֵ: 
 * 
 * HDIB             - ��DIB���
 * 
 * ����: 
 * 
 * ���ڸı仭���ߴ磬���ı�DIBͼ�εĳߴ磬�������趨DIB���»����ϵ�λ��
 * 
 ************************************************************************/ 
HDIB ChangeDIBCanvasSize(HDIB hDIB, int nWidth, int nHeight, int nPosition)
{
    LPBITMAPINFO lpbmi = NULL; 
    LPBYTE       lpSourceBits, lpTargetBits, lpResult; 
    HDC			 hDC = NULL, hSourceDC, hTargetDC; 
    HBITMAP      hSourceBitmap, hTargetBitmap, hOldTargetBitmap, hOldSourceBitmap; 
    DWORD        dwSourceBitsSize, dwTargetBitsSize, dwTargetHeaderSize; 
	HDIB		 hNewDIB;
	DWORD		 dwSize;

	WaitCursorBegin();

	//�õ�DIBָ��
	if (! hDIB)
	{
		WaitCursorEnd();
		return NULL;
	}
	LPBITMAPINFO lpSrcDIB = (LPBITMAPINFO)GlobalLock(hDIB);
	if (! lpSrcDIB)
	{
		WaitCursorEnd();
		return NULL;
	}

    //Ϊ��DIB����BITMAPINFO�ṹ 
    dwTargetHeaderSize = sizeof( BITMAPINFOHEADER ) + PaletteSize(lpSrcDIB); 
    lpbmi = (LPBITMAPINFO)malloc( dwTargetHeaderSize ); 
	memcpy(lpbmi, lpSrcDIB, dwTargetHeaderSize);
    lpbmi->bmiHeader.biWidth = nWidth; 
    lpbmi->bmiHeader.biHeight = nHeight; 
 
	hDC = GetDC( NULL ); 
    hTargetBitmap = CreateDIBSection( hDC, lpbmi, DIB_RGB_COLORS, (VOID **)&lpTargetBits, NULL, 0 ); 
    hSourceBitmap = CreateDIBSection( hDC, lpSrcDIB, DIB_RGB_COLORS, (VOID **)&lpSourceBits, NULL, 0 ); 
    hSourceDC = CreateCompatibleDC( hDC ); 
    hTargetDC = CreateCompatibleDC( hDC ); 
 
    dwSourceBitsSize = lpSrcDIB->bmiHeader.biHeight * BytesPerLine((LPBYTE)&(lpSrcDIB->bmiHeader)); 
    dwTargetBitsSize = lpbmi->bmiHeader.biHeight * BytesPerLine((LPBYTE)&(lpbmi->bmiHeader)); 
    memcpy( lpSourceBits, FindDIBBits((LPBYTE)lpSrcDIB), dwSourceBitsSize ); 
    lpbmi->bmiHeader.biSizeImage = dwTargetBitsSize; 
 
    //ѡȡDIBƬ�ε�DCs 
    hOldSourceBitmap = (HBITMAP)SelectObject( hSourceDC, hSourceBitmap ); 
    hOldTargetBitmap = (HBITMAP)SelectObject( hTargetDC, hTargetBitmap ); 
 
	//��λͼ����λͼ�е�λ��
	int x = 0;
	int y = 0;
	int nOldWidth = lpSrcDIB->bmiHeader.biWidth;
	int nOldHeight = lpSrcDIB->bmiHeader.biHeight; 
 	switch (nPosition)
	{
	case LEFT_UP:
		x = 0;
		y = 0;
		break;
	case CENTER_UP:
		x = (nWidth-nOldWidth)/2;
		y = 0;
		break;
	case RIGHT_UP:
		x = nWidth-nOldWidth;
		y = 0;
		break;
	case LEFT_CENTER:
		x = 0;
		y = (nHeight-nOldHeight)/2;
		break;
	case CENTER_CENTER:
		x = (nWidth-nOldWidth)/2;
		y = (nHeight-nOldHeight)/2;
		break;
	case CENTER_RIGHT:
		x = nWidth-nOldWidth;
		y = (nHeight-nOldHeight)/2;
		break;
	case LEFT_DOWN:
		x = 0;
		y = nHeight-nOldHeight;
		break;
	case CENTER_DOWN:
		x = (nWidth-nOldWidth)/2;
		y = nHeight-nOldHeight;
		break;
	case RIGHT_DOWN:
		x = nWidth-nOldWidth;
		y = nHeight-nOldHeight;
		break;
	}

	// ��ʼ�ð�ɫ�����λͼ
	HBRUSH hBrush = CreateSolidBrush(RGB(255,255,255));
	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255,255,255));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hTargetDC, hBrush);
	HPEN hOldPen = (HPEN)SelectObject(hTargetDC, hPen);
	Rectangle(hTargetDC, 0, 0, nWidth, nHeight);
	SelectObject(hTargetDC, hOldBrush);
	SelectObject(hTargetDC, hOldPen);
	//�ž�λͼ����λͼ����
    BitBlt(hTargetDC, x, y, nOldWidth, nOldHeight, hSourceDC, 0, 0, SRCCOPY); 
 
    SelectObject( hSourceDC, hOldSourceBitmap ); 
    SelectObject( hTargetDC, hOldTargetBitmap ); 
    DeleteDC( hSourceDC ); 
    DeleteDC( hTargetDC ); 
    ReleaseDC( NULL, hDC ); 
 

    GdiFlush(); 
 
    //Ϊ��λͼ�����㹻�ڴ沢����λ 
	dwSize = dwTargetHeaderSize + dwTargetBitsSize;
	hNewDIB = GlobalAlloc(GHND, dwSize);
    lpResult = (LPBYTE)GlobalLock(hNewDIB);
    memcpy( lpResult, lpbmi, dwTargetHeaderSize ); 
    memcpy( FindDIBBits( (LPBYTE)lpResult ), lpTargetBits, dwTargetBitsSize ); 
 
    DeleteObject( hTargetBitmap ); 
    DeleteObject( hSourceBitmap ); 
    free( lpbmi ); 
	GlobalUnlock(hDIB);
	GlobalUnlock(hNewDIB);
	WaitCursorEnd();
 
    return hNewDIB;
}

