/*
*  class PaintBrush
*  ˵������ˢ���ʵ��
*  Copyright 2002-2003. All Rights Reserved.
*====================================================
*  �汾�����¼
*  Revision 1.0 2002/11/6 
*
*  Revision 2.0	2002/11/12    	 �������Σ�����Ч������ʼ�����
*/

#if !defined(AFX_PAINTBRUSH_H__8584D307_6BE7_4707_848F_B1001F880E9A__INCLUDED_)
#define AFX_PAINTBRUSH_H__8584D307_6BE7_4707_848F_B1001F880E9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AbstractPen.h"


/*
*����: CPaintBrush
*˵�������廭ˢ��
*�汾
*  Revision 1.0 2002/11/6 
*
*  Revision 2.0	2002/11/12    	 �������Σ�����Ч������ʼ�����
*
*  Revision 2.1	2002/11/27    	 ʹ��ˢ��С�ȱ�ıʴ����������� SetPenSize ����
*/
class CPaintBrush : public CAbstractPen
{
public:
	CPaintBrush(HDC hDC, int nSize = 12, COLORREF crColor = RGB(0, 0, 0));
	virtual ~CPaintBrush();
	virtual void SetPenSize(int nSize);
};

#endif // !defined(AFX_PAINTBRUSH_H__8584D307_6BE7_4707_848F_B1001F880E9A__INCLUDED_)
