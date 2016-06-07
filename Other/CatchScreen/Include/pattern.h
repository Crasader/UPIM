/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��pattern.h
* �汾��  ��V1.0
* ��Ŀ���ƣ�CPH
* ��Ȩ������Copyright 2002-2003 . All Rights Reserved.
* ģ�����������ͨ����ͼ���ͷ�ļ�,ʵ�ֽ������ͼƬ������ǰ�����ϣ�
*                ������ʵ�����š���ת������Ȳ���   
*======================================================
* �汾�����¼:
*      v1.0  2002-11-7   15:30  ��ΰ 
*
* 
*/

/////////////////////////////////////////////////////////////////////////////


#if !defined(AFX_PATTERN_H__F534F582_F320_11D6_95DA_000795D2C55B__INCLUDED_)
#define AFX_PATTERN_H__F534F582_F320_11D6_95DA_000795D2C55B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "..\\INCLUDE\\DIBitmap.h"   //�����DIB ͼ���֧��

/////////////////////////////////////////////////////////////////////////////
/*
*����:Cpattern
*˵����Ӧ�ó�����
*�����¼��
*
*/

class Cpattern : public CWnd
{
// Construction
public:
	Cpattern();

// Attributes
public:
	//����
	CString m_strDibName;

	//��ʼ��DIB����,�ɹ�����TRUE��ʧ�ܷ���FALSE
	BOOL InitDib();
	//���µ�ǰDIB����,�ɹ�����TRUE��ʧ�ܷ���FALSE
	BOOL UpDataDib();
	//��ʾ��ǰDIB����
	ShowDib();
	//���ص�ǰDIB����
	HideDib();
	//�ı�״̬
	ChangeDibSize();
	//�ı��С(����)
	ChangeDibZoom();
	//�õ�״̬,����ֵ��Ӧ����1-10,�ֱ��ʾ��ͬ��λͼ״̬
	INT GetStatus();
	//�õ���С
	CRect GetDibSize();
	//�õ�����ҳ��ָ��
	HANDLE GetDibPage();
	//�ı����ҳ��ָ��,���ظı���ҳ����
	HANDLE ChangeDibPage();

protected:
     //ͼ�������ļ���
	CString m_DibFileName;
	//�ļ��еĶ�������
	CPoint m_arrayFileTopPoint;
	//�ļ��еĴ�С
	CSize m_DibSize;
	//����
	CPoint m_TopPoint;
	//��С
	CSize m_size;
	//ͼ��״̬,��Ӧͼ����ǰ��״̬��0-9:10�֣�
	INT m_DibStatus;
	//ͼ����ҳ������
	HBITMAP m_arrayPages;
	//����ҳ��ָ��
	HBITMAP m_pPage;
	//��ʾ/���ر�ʶ
	BOOL m_bShowHide;
	//��ǰ��ͼ��ҳ��ָ��
	HBITMAP m_pPreDibPage;


public:
	enum {		
		BITMAP_CUSTOMIZE=0,         //λͼ��ָ����С100*100��ʾ�ڻ�������
		BITMAP_STRETCH,		       // λͼ�����췽ʽ���Ի���
		BITMAP_TILE,		       // λͼ������ߴ������Ի���
		BITMAP_CENTER			   //λͼ������ʾ�ڶԻ�����
	};

protected:
	CDIBitmap	m_picture;         //��DIBλͼ���ڻ�������
	int			m_nType;	      //DIBͼƬ�ڻ����ϵ���ʾ��ʽ
	CBrush		m_brush;         //DIB��ˢ
	
protected:
	//{{AFX_MSG(Canvas)

	//}}AFX_MSG

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cpattern)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~Cpattern();

	// Generated message map functions
protected:
	//{{AFX_MSG(Cpattern)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATTERN_H__F534F582_F320_11D6_95DA_000795D2C55B__INCLUDED_)
