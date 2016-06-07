#pragma once
#include "afxwin.h"
#include "DIBitmap.h"
class CMyBitmapStatic :
	public CStatic
{
public:
	enum {		
		BITMAP_STRETCH=0,		// λͼ�����췽ʽ���Ի���
		BITMAP_TILE,		   // λͼ������ߴ������Ի���
		BITMAP_CENTER			//λͼ������ʾ�ڶԻ�����
	};
	CMyBitmapStatic(void);
	~CMyBitmapStatic(void);
	BOOL SetBitmap(UINT uResource, int nType = BITMAP_STRETCH);
	BOOL SetBitmap(LPCSTR lpszBitmap, int nType = BITMAP_STRETCH);
	void DestroyBitmap();
	int GetState();
	void SetState(int state);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()

protected:
	CDIBitmap	m_bmpBackground;
	int         m_nType;
	CBrush		m_HollowBrush;
	int        m_State;
};

