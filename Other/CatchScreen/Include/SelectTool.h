/**
*   SelectTool.h		
*   Version 1.0
*   CPH	�滭��԰
*   Copyright 2002 . All Rights Reserved.
*   ����ѡȡ���ߵĳ������
*======================================================
*   �汾
*   Revision 1.0	2002/11/14    	  ����ѡȡ���ߵĳ������
*/

#if !defined(AFX_SELECTTOOL_H__7C6DD163_F7C8_11D6_95DB_000795CFF65D__INCLUDED_)
#define AFX_SELECTTOOL_H__7C6DD163_F7C8_11D6_95DB_000795CFF65D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCartoon;
class CFloatDibWnd;


/*
*����: CSelectTool
*˵�����������ѡȡ���ߵĳ�����࣬��ȡȡ�����ӿ�
*�汾
*	Revision 1.0	2002/11/14     	 ��� CSelectTool �Ļ�������
*/
class CSelectTool  
{
protected:
	HWND m_hWnd;
	HDC m_hDC;
	CPoint m_ptSelectStartPoint;
	CPoint m_ptSelectEndPoint;


public:
	CSelectTool(HWND hWnd);
	virtual ~CSelectTool();


public:
	void BeginSelect(const CPoint& ptPoint);
	void ChangeSelect(const CPoint& ptPoint);
	CFloatDibWnd * EndSelect(const CPoint& ptPoint);


protected:
	virtual void DarkUnselectedRgn();
	virtual void DrawRubber(const CPoint& ptPoint) const;
	virtual void DrawTrack(const CPoint& ptStart, const CPoint& ptEnd) const = 0;
};

#endif // !defined(AFX_SELECTTOOL_H__7C6DD163_F7C8_11D6_95DB_000795CFF65D__INCLUDED_)
