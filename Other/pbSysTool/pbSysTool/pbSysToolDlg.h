
// pbSysToolDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <vector>
#include "AddDlg.h"
#include "../GridCtrl_src/GridCtrl.h"
// CpbSysToolDlg �Ի���

class CpbSysToolDlg : public CDialog
{
// ����
public:
	CpbSysToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PBSYSTOOL_DIALOG };
	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnCbnSelchangeComboSelectTable();
	
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnBnClickedButtonDelte();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCancel();
	afx_msg void OnGridClick(NMHDR *pNotifyStruct, LRESULT* pResult);
protected:
	typedef std::vector< std::vector<CString> >  vDataContainer;
	typedef std::vector<CString>                 vGridHead;
	void    UpdateGridData(vDataContainer Data,vGridHead Head);
	LONG    GetDbData(int type,vDataContainer &Data,vGridHead& Head);
	CString GetDlgTitle(int btnop);

	LONG    GetPublicInfo(vDataContainer& vpbInfo);              //���ں���Ϣ
	LONG    GetIncode(vDataContainer& vincode);                  //��������Ϣ
	LONG    GetTpRule(vDataContainer& vtprule);                  //·�ɹ�����Ϣ
	LONG    GetPublicTpRelation(vDataContainer& Data);           //���ںŶ�Ӧ·�ɹ�ϵ��
	LONG    GetTpRelation(vDataContainer& vtprelation);          //·�ɶ�Ӧ�������ϵ��
	LONG    GetDispatchRelation(vDataContainer& vdisrelation);   //�������Ӧ�ͷ���ϵ��
	LONG    GetCustomerInfo(vDataContainer& vcustomer);

	LONG    DelPulbic(CString pa,int &ErrorNum,CString &ErrorMsg);
	LONG    DelTpRule(CString pa,int &ErrorNum,CString &ErrorMsg);
	LONG    DelIncode(CString pa,int &ErrorNum,CString &ErrorMsg);
	LONG    DelPublicRelation(CString pa1,CString pa2,int &ErrorNum,CString &ErrorMsg);
	LONG    DelTpRelation(CString pa1,CString pa2,int &ErrorNum,CString &ErrorMsg);
	LONG    DelDispatchRelation(CString pa1,CString pa2,int &ErrorNum,CString &ErrorMsg);

	static BOOL CALLBACK GridCallback(GV_DISPINFO *pDispInfo, LPARAM lParam);
	
protected:
	CADODatabase*             m_pDB;
	CGridCtrl*                m_Grid;
	vDataContainer            m_vCurTPData;
	vDataContainer            m_vCurIncodeData;
	vDataContainer            m_vCurCustData;
	vDataContainer            m_vCurPublicInfoData;
	int                       m_curComboSel;
	
	std::vector<CString>      m_vModifyHead;
	std::vector<CString>      m_vModifyData;
	CComboBox m_ComboTable;
	int                       m_iCurRow;
};
