
// UPIMServerView.h : CUPIMServerView ��Ľӿ�
//

#pragma once

#include "resource.h"
#include "Dlg.h"

class CUPIMServerView : public CFormView
{
protected: // �������л�����
	CUPIMServerView();
	DECLARE_DYNCREATE(CUPIMServerView)

public:
	enum{ IDD = IDD_UPIMSERVER_FORM };

// ����
public:
	CUPIMServerDoc* GetDocument() const;

// ����
public:
	CStatisticsDlg m_DlgStatistics;
protected:
	TabCtrlEx<TabCtrlStyle_base> m_TabCtrl;
	
	BOOL m_IsInitialed;
	map<int,CRect> m_ControlRect;
	int cx;
	int cy;
	
// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CUPIMServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void InitChildCtrlPos();
	void MoveWnd(int cx,int cy);

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // UPIMServerView.cpp �еĵ��԰汾
inline CUPIMServerDoc* CUPIMServerView::GetDocument() const
   { return reinterpret_cast<CUPIMServerDoc*>(m_pDocument); }
#endif

