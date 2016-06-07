// TriangleShape.h: interface for the CTriangleShape class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRIANGLESHAPE_H__0F4DFF3C_FCBD_443F_9630_74E1623DB6D7__INCLUDED_)
#define AFX_TRIANGLESHAPE_H__0F4DFF3C_FCBD_443F_9630_74E1623DB6D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Shape.h"

class CTriangleShape : public CShape  
{
public:
	CTriangleShape();
	virtual ~CTriangleShape();


public:
	// ��ʼ�滭
	void BeginDraw(HDC hDC, const CPoint& ptPoint);
	// ���㣬���ⲿ����
	void DrawPoint(HDC hDC, const CPoint& ptPoint);
	// �����滭
	void EndDraw(HDC hDC, const CPoint& ptPoint);
private:
	BOOL AngleArcTo(HDC hDC, int X, int Y, DWORD dwRadius, FLOAT eStartAngle, FLOAT eSweepAngle);
	CPoint GetNextPoint(const CPoint& ptBegin);
	void DrawTriangle(HDC hDC, const CPoint& ptBegin);

	CPoint m_ptCenter;
};

#endif // !defined(AFX_TRIANGLESHAPE_H__0F4DFF3C_FCBD_443F_9630_74E1623DB6D7__INCLUDED_)
