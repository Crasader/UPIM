/**
*  SpecialPen.h
*  CPH 1.0 ��
*  �������ʵĹ��ܣ���Ҷ����ͷ��դ����ˮ��)
*  Copyright 2002-2003 . All Rights Reserved.
*  ʵ��ʰɫ����
*====================================================
*  �汾�����¼
*  CPH 1.0 2002/11/13 
*
*  CPH 1.0 2002/11/14  ������ڴ�й¶����
*
*/

#if !defined(AFX_SPECIALPEN_H__DA17A4C2_F6E3_11D6_95DC_000795CD4EC5__INCLUDED_)
#define AFX_SPECIALPEN_H__DA17A4C2_F6E3_11D6_95DC_000795CD4EC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "dib.h"
#include "ENUM.h"
/*
*����    : class CSpecialPen  
*˵��    : ��װ������ʵĻ滭����
*�����¼:
*          2002/11/14  ����
*
*/
class CCPHDlg;
const INT MAX_SPECIALPEN = 100;
class CSpecialPen 
{
public:
	void SetPenType(INT penType);
	void SetMainWnd(CCPHDlg *pWnd);
	CString GetBtnFile(INT index);
	void InitBmpFile(INT type);
	void DrawDIB(CDC * pDC, CPoint point, INT ID, INT index,INT size, BOOL isChange = TRUE);
	HBITMAP ChangeBitmapSize(HBITMAP hBitmap, INT ID, INT index, CRect newRect = CRect(0,0,0,0));
	CSpecialPen(CCPHDlg * pMainWnd=NULL);
	virtual ~CSpecialPen();
	int  GetWidth();
	int  GetHeight();
	int  GetDibWidth();
	int  GetDibHeight();


	void SetTransparence (int iTransparence);
	BOOL chooseSpecialPen (int nStyle, int nIndex);
	void Draw(HDC hDC, CPoint point);

	CDib * m_psDib;
    //��ǰ���������(��ö��)
	SPECIAPEN     m_speciapen; 
private:
	int     m_nStyle;
	int     m_nIndex;
	BITMAP  m_bitmap;

	HBITMAP m_hBitmap[4][MAX_SPECIALPEN];  //ÿ���������֧��20�����������
    CString  m_bmpFile[4][MAX_SPECIALPEN];  //���찴Ŧ�ϵ�ͼ���ļ�
    CString  m_btn1File[MAX_SPECIALPEN];  //�ڰ�Ŧ�ؼ��ϵ�����ͼ(ֻ�Ե�һ�����͵ı�)

	CDC     m_memDC;
	int     m_iTransparence;

    CCPHDlg *m_pMainWnd;

};

#endif // !defined(AFX_SPECIALPEN_H__DA17A4C2_F6E3_11D6_95DC_000795CD4EC5__INCLUDED_)
