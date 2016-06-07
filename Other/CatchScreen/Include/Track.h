/**
*   Track.h		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002. All Rights Reserved.
*   ������ֹ켣�ĳ�����࣬��ȡȡ�����ӿ�
*======================================================
*   �汾
*   Revision 1.0	2002/11/11    	 ���� CTrack ��
*/

#if !defined(AFX_Track_H__6EF81C80_A150_483E_976E_8528CB0D24A9__INCLUDED_)
#define AFX_Track_H__6EF81C80_A150_483E_976E_8528CB0D24A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

// ����켣��ɫ����
const COLORREF TRACK_PEN_COLOR = RGB(0, 0, 0);


/*
*����: CTrack
*˵����������ֹ켣�ĳ�����࣬��ȡȡ�����ӿ�
*�汾
*	Revision 1.0	2002/11/11     	 ���� CTrack ��
*/
class CTrack
{
protected:
	CString m_strTrackName;
	HDC m_hDC;
	CPoint m_ptTrackEndPoint;
	CPoint m_ptTrackStartPoint;
	CList<CPoint, CPoint&> m_listTrackPoints;


public:
	CTrack(HDC hDC, COLORREF crTrackColor);
	virtual ~CTrack();

	// ���켣���б��м���һ���㣬����ص�
	static void CALLBACK  AddPosToList(int x, int y, LPARAM lpData);

public:
	void SetTrackColor(COLORREF crTrackColor);
	// �����켣�㼯�Ϻ���
	POSITION GetHeadPosition();
	CPoint& GetNextPoint(POSITION& rPos);
	// ��������켣�㺯��
	void AddPoint(int x, int y);
	void BeginTrack(const CPoint& ptPoint);
	void DrawTrack(const CPoint& ptPoint);
	void EndTrack(const CPoint& ptPoint);


protected:
	// ��һЩ������������������ٻ�ͼ
	void PreDraw(const CPoint& ptStart, const CPoint& ptEnd) const;
	// ��һЩ������������������ټ��������켣�Ĺ켣�㼯��
	BOOL PreCreatePos();

	// ���ݹ켣������ļ���
	virtual BOOL CreatePos() = 0;

	// ���켣����
	virtual void Draw(const CPoint& ptStart, const CPoint& ptEnd) const = 0;


protected:
	COLORREF m_crTrackColor;

	// ���º�����Ϊ������ͼ����

	// ����ֱ�߷��̵ĺ���
	BOOL CalLineEquation(const CPoint & ptBegin, const CPoint & ptEnd, double * k, double * b) const;

	// ������ֱ�߽������꺯��
	void GetIntersectPoint(const CPoint& pt1Begin, const CPoint& pt1End, const CPoint &pt2Begin, const CPoint &pt2End, CPoint& ptIntersect) const;

	// �ȷ�Բ
	BOOL SplitCircle(const CPoint& ptCenter, const CPoint& ptBegin, int nCount, CPoint * ptVertex) const;

	// �õ����յ�����
	CPoint GetArcEndPoint(const CPoint& ptCenter, double dwRadius, double eStartAngle, double eSweepAngle) const;
};

#endif // !defined(AFX_Track_H__6EF81C80_A150_483E_976E_8528CB0D24A9__INCLUDED_)
