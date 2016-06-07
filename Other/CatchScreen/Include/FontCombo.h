/**
*	File Name			:	FontCombo.h
*	Version				:	1.0
*	Project Information	:	
*	Copyright			:	Copyright 2002 . All Rights Reserved.
*	Brief Description   :	��ʾ�����б�������б����
*====================================================================================
*   �汾
*   Revision 1.0	2002/11/11	����CFontCombo��
*/


/*
*������CFontCombo
*˵��������ö�������Ѱ�װ���岢�������б����ʾ
*�汾��
*Revision     1.0     2002/11/06       ö�������Ѱ�װ���岢�������б����ʾ
*/

class CFontCombo : public CComboBox
{
// Attribute
public:
	// ������弯
	BYTE required_charset;
private:
	CString m_sSelection;


protected:

	
// Construction
public:
	CFontCombo();
	virtual ~CFontCombo();

	// ö�����в���ϵͳ����װ����������
	static int CALLBACK EnumFontFamProc(ENUMLOGFONT *lpelf, 
					NEWTEXTMETRIC *lpntm,
					int nFontType,
					LPARAM lParam);
	// �������
	void ProcessFonts(void);	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFontCombo)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	CString GetFontType();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CFontCombo)
	afx_msg void OnSelchange();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
