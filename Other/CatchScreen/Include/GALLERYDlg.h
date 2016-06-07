/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��GALLERYDlg.h
* �汾��  ��V1.0
* ��Ŀ���ƣ�CPH
* ��Ȩ������Copyright 2002-2003 . All Rights Reserved.
* ģ����������滭��԰[�ҵĻ���]�Ի���ͷ�ļ�
*======================================================
* �汾�����¼:
*      v1.0  2002-11-22   16��50  
*
* 
*/

/////////////////////////////////////////////////////////////////////////////


#if !defined(AFX_GALLERYDLG_H__9C7C2161_F6E6_11D6_95DA_000795D28546__INCLUDED_)
#define AFX_GALLERYDLG_H__9C7C2161_F6E6_11D6_95DA_000795D28546__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "BitmapDialog.h"
#include "ButtonST.h"
#include "ENUM.h"
#include "DefineMessage.h"
#include <afxtempl.h>
#include "viewbig.h"


//#include "FileInfo.h"
/////////////////////////////////////////////////////////////////////////////
/*
*����    : CGALLERYDlg
*˵��    : ���Ի�����
*�����¼:
*
*/
class CCPHDlg;
class CGALLERYDlg : public CBitmapDialog
{
// Construction
public:
	CGALLERYDlg(CWnd* pParent = NULL);   // standard constructor
public:
	void SetCphDlgWnd(CCPHDlg * pWnd);
	INT GetPageNum();

	CString GetResPath(UINT btnID);
	void InitButton();
	CViewBig  m_viewWnd;
	CViewBig  m_ViewShow[9];
// Dialog Data
	//{{AFX_DATA(CGALLERYDlg)
	enum { IDD = IDD_CPH_GALLERY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGALLERYDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGALLERYDlg)
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg LRESULT OnGetWndMsg(LPARAM, WPARAM);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CRect GetButtonDefaultRect(INT btnID);
	void OnExitClick();
	void OnForwardClick();
	void OnBackClick();
	void OnZoomClick();
	void OnEditClick();
	BOOL m_bZoom;
	void ShowBitmap(long PicNum,long x);
	void InitGallery();
	void CreateBTNST();
	void OnShowClick(long Number);
	
	//��ǰҳ�ϵ�ͼ�δ������
	INT m_pagenum;
    //ǰ�����߰�Ŧ
	CButtonST   m_GALForward;       
     //�󷭹��߰�Ŧ 
    CButtonST   m_GALBack;      
	 //���Ź��߰�Ŧ
    CButtonST   m_GALZoom;	
   
	CButtonST   m_GALFace;
     //�༭���߰�Ŧ 
    CButtonST   m_GALEdit;     
   //�˳����߰�Ŧ 
    CButtonST   m_GALExit;        

	//ͼƬ������
	int PicNumber;     
	//ͼƬ�ĵ�ǰҳ��
	int CurrentPage;	
	//ͼƬ������
	int TotalPage;
	CArray<CString,CString> btnbmp;       


private:
   CCPHDlg * m_pMainWnd;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GALLERYDLG_H__9C7C2161_F6E6_11D6_95DA_000795D28546__INCLUDED_)
