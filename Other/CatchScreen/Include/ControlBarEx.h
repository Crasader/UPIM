/////////////////////////////////////////////////////////////////////////////
/**����û�б�Ӧ�ó���ʹ�ã�����û�еõ���չ��ֻΪ����ṩ����֮�ã����������ã�����ɾ������
* �ļ���  ��ControlBarEx.h
* �汾��  ��V1.0
* ��Ŀ���ƣ�CPH
* ��Ȩ������Copyright 2002-2003 . All Rights Reserved.
* ģ����������������߿ؼ����ؼ���ͷ�ļ�
*======================================================
* �汾�����¼:
*      v1.0  2002-10-31   16��00  
*
* 
*/

/////////////////////////////////////////////////////////////////////////////


#if !defined(AFX_CONTROLBAREX_H__7E293642_EDB2_11D6_95DA_000795D2C55B__INCLUDED_)
#define AFX_CONTROLBAREX_H__7E293642_EDB2_11D6_95DA_000795D2C55B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ControlBarEx.h : header file
//

#include "BitmapDialog.h"
#include "Canvas.h"
#include "ButtonST.h"
/////////////////////////////////////////////////////////////////////////////
/*
*����    : CControlBarEx
*˵��    : ������������
*�����¼:���ݲ��ã�
*
*/

class CControlBarEx : public CBitmapDialog
{
// Construction
public:
	CControlBarEx(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CControlBarEx)
	enum { IDD = IDD_CONTROLBAR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CControlBarEx)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CControlBarEx)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROLBAREX_H__7E293642_EDB2_11D6_95DA_000795D2C55B__INCLUDED_)
