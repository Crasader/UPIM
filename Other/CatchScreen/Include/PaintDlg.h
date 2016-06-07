
// PaintDlg.h : ͷ�ļ�
//

#pragma once
#include "BitmapDialog.h"
#include "colorpen.h"
#include "ColorStatic.h"
#include "FontCombo.h"
#include "MyBitmapStatic.h"
// CPaintDlg �Ի���
class CPaintDlg : public CBitmapDialog
{
// ����
public:
	CPaintDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PAINT_DIALOG };
	
public:
	void SetDlgRect(CRect rc);
	BOOL GetFontIsBold();
	void SetPenCol(COLORREF pencolor);
	void SetCanvansStyle();
	void SetDlgType(int type);
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	

// ʵ��
protected:
	//HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd,UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCbnSelchangeComboFont();
	DECLARE_MESSAGE_MAP()
protected:
	CBrush     m_hbrush;   
	CRect      m_rctDlg;
	CRect      m_rctColor[16];
	CColorPen  m_SelColor[16];
	CRect      m_CurSelColor;
	
	afx_msg LRESULT OnUwmShowpencolor1(WPARAM wParam, LPARAM lParam);
private:
	BOOL       m_bFontBold;
public:
	CMyBitmapStatic m_pen[3];
	CRect           m_penrect[3];
	CColorStatic    m_preSelColor;
//	PRETOOLBAR      m_toolbarstyle;   //��ǰ������
	COLORREF        m_pencolor;       //��ǰ������ɫ
//	BASEPEN         m_basepen;        //��ǰ�������ʹ���
//	PEN_TRACK       m_shapepen;       //��ǰ���ʹ��߹켣
	CComboBox       m_fontCombo;      //����ö�ٿ�
//	BOOL            m_bCanvas;        //�Ƿ����ڻ�����ȡɫ
	int             m_DlgType;
};
