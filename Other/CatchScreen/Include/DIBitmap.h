/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��DIBitmap.h
* �汾��  ��V1.0
* ��Ŀ���ƣ�CPH
* ��Ȩ������Copyright 2002-2003 . All Rights Reserved.
* ģ���������DIBͼ�δ�������ͷ�ļ�
*======================================================
* �汾�����¼:
*      v1.0  2002-10-30   20:30  
*
* 
*/

/////////////////////////////////////////////////////////////////////////////

#ifndef DIB256_h
#define DIB256_h

////////////////////////////////////////////////////////////////////////////
/*
*����    : CDIBitmap
*˵��    : DIBͼ�β�����
*�����¼:
*
*/

class  CDIBitmap
{
	friend class CBmpPalette;

	BITMAPINFO *	m_pInfo;
	BYTE *			m_pPixels;
	CBmpPalette *	m_pPal;
	BOOL			m_bIsPadded;

	public:		//constructors
		CDIBitmap();
		virtual ~CDIBitmap();

	private:
		CDIBitmap( const CDIBitmap& dbmp );

	public:		// attributes
		BITMAPINFO *	GetHeaderPtr() const;
		BYTE *			GetPixelPtr() const;
		RGBQUAD *		GetColorTablePtr() const;
		int				GetWidth() const;
		int				GetHeight() const;
		CBmpPalette *	GetPalette() { return m_pPal; }

	public:		// operations
		BOOL			CreatePalette();	// ������ɫ�壬��Load()��CreateFromBitmap()���Զ�����
		void			ClearPalette();		// ���ٵ�ǰλͼʹ�õĵ�ɫ��
		BOOL			CreateFromBitmap( CDC *, CBitmap * );
		BOOL			LoadResource(LPCTSTR ID);
		BOOL            LoadResource(UINT ID);
		BOOL            LoadBitmap(LPCTSTR  lpsID);
		BOOL            LoadBitmap(UINT ID);
		void			DestroyBitmap();
		BOOL			DeleteObject() { DestroyBitmap(); return TRUE; }
		
	public:		// overridables


			// ��ָ����λ�û�λͼ
		virtual void	DrawDIB( CDC * pDC, int x=0, int y=0 );

			// ��ָ����λͼ��ʹ������/ѹ������ָ���ĳߴ�
		virtual void	DrawDIB( CDC * pDC, int x, int y, int width, int height );

			// ��DIBͼ�εĲ��ݵ�DC���������
		virtual int		DrawDIB( CDC * pDC, CRect & rectDC, CRect & rectDIB );

			// ���ⲿ�ļ��е���λͼ
		virtual BOOL	Load( CFile * pFile );
		virtual BOOL	Load( const CString & );

			//����DIBλͼ������
		virtual BOOL	Save( CFile * pFile );
		virtual BOOL	Save( const CString & );

	protected:
		int				GetPalEntries() const;
		int				GetPalEntries( BITMAPINFOHEADER& infoHeader ) const;
		DWORD			GetBitsPerPixel() const;
		DWORD			LastByte( DWORD BitsPerPixel, DWORD PixelCount ) const;
		DWORD			GetBytesPerLine( DWORD BitsPerPixel, DWORD Width ) const;
		BOOL			PadBits();
		BOOL			UnPadBits();
		WORD			GetColorCount() const;
};

#include "dibpal.h"

#endif	// DIB256_h