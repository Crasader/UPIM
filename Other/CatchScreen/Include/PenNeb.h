/**
*   Penneb.h		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002. All Rights Reserved.
*   ������ֱʼ�ĳ�����࣬��ȡȡ�����ӿ�
*======================================================
*   �汾
*   Revision 1.0	2002/11/12 	 ���� CPenNeb ��
*/

#if !defined(AFX_PENNEB_H__7DED83E2_F715_11D6_95DB_000795CFF65D__INCLUDED_)
#define AFX_PENNEB_H__7DED83E2_F715_11D6_95DB_000795CFF65D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/*
*����: CPenNeb
*˵����������ֱʼ�ĳ�����࣬��ȡȡ�����ӿ�
*�汾
*	Revision 1.0	2002/11/12    	 ���� CPebNeb ��
*/
class CPenNeb  
{
protected:
	HDC m_hDC;
	BOOL m_bAlpha;
	COLORREF m_crPenNeb;
	CSize m_PenNebSize;
	HBITMAP m_hOldBrush;
	// ����ʼ�ͼ��ľ��
	HBITMAP m_hPenBrush;
	// ����ʼ�ͼ�������ڴ��豸������ľ��
	HDC m_hMemDC;


public:
	CPenNeb(HDC hDC, COLORREF crColor, BOOL bAlpha = FALSE);
	virtual ~CPenNeb();


public:
	void InitPenNeb();
	void Apply(const CPoint& pt) const;
	virtual void SetSize(int nSize) = 0;
	virtual void SetColor(COLORREF crColor);


protected:
	virtual void CreatePenNeb();
	void CreateAlphaPen();
	void Release();
	virtual void SetAlpha(BYTE * pPixel) = 0;
	void AlphaApply(const CPoint& pt) const;
	virtual void NormalApply(const CPoint& pt) const;

protected:
	void RotatePoint(double radians, const CPoint &c, CPoint& point) const;
	// �������ڻ���ת��Բ�ĺ���
	void DrawRotateEllipse(HDC hDC, const CRect& rect, double radians) const;
	void EllipseToBezier(const CRect& rect, CPoint* cCtlPt) const;
	void RotateEllipse(double radians, const CPoint& c, CPoint* vCtlPt, unsigned Cnt) const;

};

#endif // !defined(AFX_PENNEB_H__7DED83E2_F715_11D6_95DB_000795CFF65D__INCLUDED_)
