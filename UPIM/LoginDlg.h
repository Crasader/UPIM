#pragma once
// CLoginDlg �Ի���

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoginDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

private:
//	CDialogUI m_dlgWnd;
//	CLoginFrameWnd m_dlgWnd;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
