/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��Dib.h 
* �汾��  ��V1.0
* ��Ŀ���ƣ�CPH
* ��Ȩ������Copyright 2002-2003 . All Rights Reserved.
* ģ���������DIBͼ�δ�����ͷ�ļ�������DibAPI.CPP�еĺ�����
*======================================================
* �汾�����¼:
*      v1.0  2002-11-11   8:30   
*
* 
*/

/////////////////////////////////////////////////////////////////////////////


#if !defined(AFX_DIB_H__33817561_072D_11D1_8C94_000021003EA5__INCLUDED_)
#define AFX_DIB_H__33817561_072D_11D1_8C94_000021003EA5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include "DIBAPI.H"

//��������
#define EFFECT_SCANDOWN		1
#define EFFECT_SCANUP		2
#define EFFECT_SCANRIGHT	3
#define EFFECT_SCANLEFT		4
#define EFFECT_VSPLITSCAN	5
#define EFFECT_HSPLITSCAN	6
#define EFFECT_MOVEDOWN		7
#define EFFECT_MOVEUP		8
#define EFFECT_MOVERIGHT	9
#define EFFECT_MOVELEFT		10
#define EFFECT_VSPLITMOVE	11
#define EFFECT_HSPLITMOVE	12
#define EFFECT_VCROSSMOVE	13
#define EFFECT_HCROSSMOVE	14
#define EFFECT_VRASTER		15
#define EFFECT_HRASTER		16
#define EFFECT_VBLIND		17
#define EFFECT_HBLIND		18
#define EFFECT_MOSAIC		19
#define EFFECT_FADE			20

////////////////////////////////////////////////////////////////////////////
/*
*����    :  CDib 
*˵��    : ��װȫ������DIBAPI.cpp�еĺ�����DIB���д������
*�����¼:
*
*/

class  CDib : public CObject
{                          
	DECLARE_SERIAL(CDib)

//������Ա����
public: 
	// ����
	CDib();
	// ����DIB
	BOOL	Create(DWORD dwWidth, DWORD dwHeight);
	BOOL	Create(DWORD dwWidth, DWORD dwHeight, WORD wBitCount);
	BOOL	Create(LPBYTE lpDIB);
	BOOL	Create(LPBYTE lpDIB,		
				   WORD  wBitCount);	
	BOOL	Create(HBITMAP hBitmap);
	BOOL	Create(HBITMAP hBitmap,	
				   WORD  wBitCount);	
	BOOL	Create(HBITMAP hBitmap,	
				   HPALETTE hPalette);	
	BOOL	Create(HBITMAP hBitmap,	
				   HPALETTE hPalette,
				   WORD  wBitCount);
	BOOL	Create(CRect rcScreen);
	BOOL	Create(HWND hWnd, WORD fPrintArea);
	BOOL	Create(HWND hWnd, CRect rcClientArea);
	// load/save
    BOOL	Load(UINT uIDS, LPCTSTR lpszDibType);
    BOOL	Load(LPCTSTR lpszDibRes, LPCTSTR lpszDibType);
    BOOL	Load(LPCTSTR lpszDibFile);
    BOOL	Save(LPCTSTR lpszDibFile);
	BOOL	Read(CFile *pFile);
	BOOL	Write(CFile *pFile);

	//��¡
	CDib *  Clone();

	virtual ~CDib();
	// ����
	void	Destroy();

	virtual void Serialize(CArchive &ar);
    
	// ��ʾDIB
	BOOL	Display(CDC * pDC, int xDest, int yDest, int nWidthDest, int nHeightDest, 
 				   int xSrc, int ySrc, DWORD dwRop=SRCCOPY);
	BOOL	Display(CDC * pDC, int xDest, int yDest, int nWidthDest, int nHeightDest, 
				    int xSrc, int ySrc, int nWidthSrc, int nHeightSrc, DWORD dwRop=SRCCOPY);
    BOOL	Display(CDC* pDC, int x, int y, DWORD dwRop=SRCCOPY);
	BOOL	Display(CDC* pDC, CRect rcDest, CRect rcSrc,DWORD dwRop=SRCCOPY);
	BOOL	DisplayPalette(CDC* pDC, CRect rc);

	// �滭DIB
	CDC*	BeginPaint(CDC *pDC);
	void	EndPaint();

	// DDB �͵�ɫ��
	BOOL	BuildBitmap();
	BOOL	BuildPalette();

	// ����
	BOOL	IsEmpty();
	DWORD	GetCompression();
    WORD	GetBitCount();
    LONG	GetWidth();
    LONG	GetHeight();    
	LONG	GetWidthBytes();
    WORD	GetColorNumber();
	WORD	GetPaletteSize();
    CBitmap*  GetBitmap();
	CPalette* GetPalette();
	HANDLE	GetHandle();
	LPBYTE	GetBitsPtr();
	COLORREF GetPixel(LONG x, LONG y);
	LONG    GetPixelOffset(LONG x, LONG y);

	// ͸����ʾ
	BOOL	DisplayTransparent(CDC* pDC, int x, int y, COLORREF cTransparentColor);

	//��Ч����
	BOOL	Display(int nEffect, CDC* pDC, int x, int y, int nDeta, DWORD dwDelayTime, DWORD dwRop=SRCCOPY);
	BOOL	Clear(int nEffect, CDC* pDC, int x, int y, int nDeta, DWORD dwDelayTime);

	// ת��
	HDIB	CopyRect(CRect rc);
	BOOL	CutRect(CRect rc);
	BOOL	MergeDib(HDIB hDib, CPoint ptTopLeft);
	BOOL	Crop(CRect rc);
	BOOL	Rotate(double fDegrees, COLORREF clrBack);
	BOOL	Rotate90();
	BOOL	Rotate180();
	BOOL	Rotate270();
	BOOL	FlipHorz();
	BOOL	FlipVert();
	BOOL	Zoom(double fRatioX, double fRatioY);
	BOOL	ChangeImageSize(int nWidth, int nHeight);
	BOOL	ChangeCanvasSize(int nWidth, int nHeight, int nPosition);

//˽�г�Ա����
private:
	BOOL	UpdateInternal();
	BOOL	DisplayFadeIn(CDC* pDC, int x, int y, int nDeta, DWORD dwDelayTime);
	BOOL	DisplayFadeOut(CDC* pDC, int x, int y, int nDeta, DWORD dwDelayTime);
	BOOL	DisplayMosaicIn(CDC *pDC, int x, int y, int nTileSize, DWORD dwDelayTime, DWORD dwRop=SRCCOPY);
	BOOL	DisplayMosaicOut(CDC *pDC, int x, int y, int nTileSize, DWORD dwDelayTime);

// ���г�Ա����
public:
	HBITMAP GetHBitmap();
	BOOL ChangeCanvasBit(INT colBit);
	BOOL AdjustDibBrightness(int v);
     //��DIB���
	HDIB		m_hDib;  
	// DIBƬ�Ͼ��
	HBITMAP		m_hBitmap;
    //��ɫ����
	CPalette* 	m_pPalette; 
     // ��BitMap����
	CBitmap*	m_pBitmap;
    //�ڴ�CDC(ԭΪ˽�г�Ա)
	CDC *		m_pMemDC;    

// ˽�г�Ա�������ڻ�DIBʱ
private:
     //��ʱBitMap����
	CBitmap*	m_pBitmapTmp;  
    //��ʱ��ɫ�����
	CPalette*	m_pPaletteTmp;  
protected:
	void ChangeBrightness(int nDelta, BYTE *r, BYTE *g, BYTE *b);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIB_H__33817561_072D_11D1_8C94_000021003EA5__INCLUDED_)
