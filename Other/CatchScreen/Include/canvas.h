/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��Canvas.h 
* �汾��  ��V1.0
* ��Ŀ���ƣ�CPH
* ��Ȩ������Copyright 2002-2003 . All Rights Reserved.
* ģ����������滭��������ͷ�ļ�
*======================================================
* �汾�����¼:
*      v1.0  2002-11-4   8:30  ��ΰ  
*
* 
*/

/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_Canvas_H__7FD19197_7DEB_43A7_B4E8_D67A67BEC917__INCLUDED_)
#define AFX_Canvas_H__7FD19197_7DEB_43A7_B4E8_D67A67BEC917__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include  "Dib.h"
#include "ENUM.h"
//#include "SpecialPen.h"
#include "ClipBoard.h"	// Added by ClassView
#include <list>
/////////////////////////////////////////////////////////////////////////////
/*
*����    : Canvas
*˵��    : �滭��������
*�����¼:
*
*/

class CAbstractPen;
//class CSelectTool;
//class CFloatDibWnd;


class Canvas : public CWnd
{
// Construction
public:
	Canvas();
    
// Attributes
    
private:

	// ��ǰ�ʵĴ�С���Ǿ���������Сת�������ʵ�ʱʴ�С
	int m_nPenSize;  //1-40
	int m_orgPenSize; //0-110  δת���ıʴ�С
	PEN_TRACK m_PenTrack;
	PEN_STYLE m_PenStyle;     

    //SPECIAPEN    m_speciapenType;

     //��ǰ������ɫ
	COLORREF      m_pencolor;      
    //��ǰ��ˢ���ɫ(��û��ʹ��)
	COLORREF      m_crFillColor;   
    //��ǰ������(��ö��)
	PRETOOLBAR    m_toolbarstyle;   
    //��ǰ�������ʹ���(��ö��)
	BASEPEN       m_basepen;       
   //��ǰ��������(��ö��)
	FONTSTYLE     m_fontstyle;
    //��ǰ���λ��ʹ���(��ö��)
 //   PEN_TRACK     m_shapepen;       
    //��ǰͼƬ���(��ö��)
	PICTURES      m_picture;        

  
    //��ǰ���ʳߴ�(1-100)
	INT           m_presize;        
    //�������������
	BOOL          m_bLdown;
	// ������
	CClipBoard m_ClipBoard;
	// �ж��Ƿ��ڻ����
	BOOL m_bDrawingRubber;
	// �����δ�С
	CRect m_rcRubber;
	// ����
	CFont* m_pFont;
	// ���ֱ༭�ؼ�
	CEdit m_EditText;
	// ���ʼ��
	CPoint m_ptStart;
	// �����С
	int m_nFontSize;
	// ������
	BOOL m_bBold;
	// б����
	BOOL m_bItalic;
	// �»�����
	BOOL m_bUnderline;
	// ������
	CString m_stSelection;
	// �����ݴ�
	CPoint m_pTemp;

public:    //������Ϊ������Ҫʹ�õĳ�Ա����
   //DIB����
    CDib *        m_pDib;  	   
	//����DIB֮ǰ���ݵ�һ��DIB����
	CDib *        m_tempDib;        
    //����DIB(�ݲ���)
 	CDib *        m_pDibBk;         
    //��ͨ����
//    CCartoon *    m_cartoon;       


protected:
	// �������ڣ�����ѡ����ͼ
	//CFloatDibWnd * m_pFloatDibWnd;
	// ѡȡ����ָ��
	//CSelectTool * m_pSelectTool;
	// �ʶ���ָ��
	CAbstractPen * m_pPen;

public:
	//����һ�������
	//CSpecialPen m_SpeciaPen;

private:   //�����ݹ�������
	CPoint m_strPoint;
	CPoint pointOld;
	CPoint m_endPoint;
    CDC *  m_paintDC;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Canvas)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	enum {		
		BITMAP_STRETCH=0,		// λͼ�����췽ʽ���Ի���
		BITMAP_TILE,		    // λͼ������ߴ������Ի���
		BITMAP_CENTER			//λͼ������ʾ�ڶԻ�����
	};
public:
	void LoadFile(CString filename);
	CRect rcClient;
	int scrollbar_width;
	int x_offset;
	int y_offset;
	CSize image_size;
	HBITMAP hBitmap;           
		
	void DrawBitmap();
	void SetBitmap(HBITMAP hBmp);
	void ShowFillColor();
	void ShowPenColor();

    //���ܹ��
	//HCURSOR m_hCursorPicker;  
	//�Ƿ���ñ���ͼƬ
    BOOL m_bSetBkBitmap;       

	INT m_nSelectColorMode;
	virtual ~	Canvas();
protected:
    //����DIBͼƬ��ʾ��ʽ
	int			m_nType;	
	//DIB��ˢ
	CBrush		m_HollowBrush;     
	BOOL m_bUnDo;
	BOOL m_bReDo;
	// Generated message map functions
protected:
	//{{AFX_MSG(Canvas)
	afx_msg void OnPaint();
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//afx_msg	void OnCutCanvasDibRect(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	BOOL GetModify();
	void SetModify(BOOL isChanged = TRUE);
	INT m_leafIndex;   //��Ҷ������(0-5)
	void SetLeafIndex(INT index);
	BOOL SelectToolAct(SELECT_TOOL st);
	void SetPenType(PEN_TYPE PenType);
	BOOL Paste();
	BOOL Copy();
	BOOL Cut();
    //�õ������ø�����ֵ
	//SPECIAPEN GetSpeciaPenStyle();
	INT GetPenSize();
	PICTURES GetPictureStyle();
	FONTSTYLE GetFontStyle();
	BASEPEN GetBasePenStyle();
	PRETOOLBAR GetToolBarStyle();
	COLORREF GetFillColor();
	COLORREF GetPenColor();

	//���û滭�ø�����ֵ
	void SetSpeciaPenStyle(SPECIAPEN);
	void SetPenSize(INT);
	void SetPictureStyle(PICTURES);
	void SetPenTrack(PEN_TRACK );
	void SetPenStyle(PEN_STYLE);
	void SetFontStyle(FONTSTYLE);
	void SetBasePenStyle(BASEPEN );
	void SetToolBarStyle(PRETOOLBAR);
	void SetFillColor(COLORREF);
	void SetPenColor(COLORREF);

	void CreatNewCanvas(CString strfile = _T(""), INT width=0,INT height=0 /*= CRect(0, 0, 520, 390)*/);
	
	void UnDo();
	BOOL UnNDo();
	void ReDo();
	void SaveBak();
	void SaveNBak();

	BOOL CreateNewCartoon(CString strFile);


protected:  
	BOOL CopyClientRectToDib();

//	CString m_cartoonfilename;

	afx_msg LRESULT OnReDraw(WPARAM,LPARAM);

	INT m_DrawPenStyle;
	CDC memDC;
	CBitmap* pBitmap;
	CBitmap* pOldBitmap;

private:

	// �������ֵ������غ���
	void DoDrawRubber(CDC* pDC, CRect rc);
	void StopDrawRubber();
	void StartDrawRubber(CPoint point);
	BOOL MergeText();
	void DrawRubber(CPoint point);
	BOOL PointInDib(CPoint point);
    BOOL m_bchanged;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
private:
    //+++++++++++++++++++++++++++++++++++++++++++++++++++
    CRect  m_wndRect;  //������������С(.left!=0 .top!=0)
    CRect  m_clientRect; //�����ͻ����ľ�������С(.left=0 .top=0)

	//+++++++++++++++++++++++++++++++++++++++++++++++++++
public:
	void SetFloatWndShowBtn(BOOL bCreateBtn);
	void UpdateMainWndImage();
	void InitImage(HBITMAP hBitmap);
	void InitImage(CString fileName);
	void SetNewWndRect(CRect wndRect);
	HBITMAP GetHbitmap();
	INT GetOrgPenSize();
	void MoveCanvas();
    CRect GetCanvasWndRect();
    CRect GetCanvasClientRect();

private:
	CString m_curTmpFile;
	std::list<CDib*>  m_vDib;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_Canvas_H__7FD19197_7DEB_43A7_B4E8_D67A67BEC917__INCLUDED_)
