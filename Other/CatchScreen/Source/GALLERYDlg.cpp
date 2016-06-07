/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��GALLERYDlg.cpp
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



#include "stdafx.h"
#include <math.h>
#include "..\Paint\PaintDlg.h"
#include "..\\CPHDlg.h"
#include "..\\include\\GALLERYDlg.h"

#include "winuser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//Ӧ�ó�������·��,��"c:\cph\"
extern  CString g_strAppPath;        
extern  IniPaintSet g_stuPaintSet;
/////////////////////////////////////////////////////////////////////////////
// CGALLERYDlg dialog
/*--------------------------------------------------------------------------------
*  ��Ա������   :CGALLERYDlg
*  ��������     :���캯��
*  �����������	:
*    CWnd* pParent����������
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*-----------------------------------------------------------------------------------
*/

CGALLERYDlg::CGALLERYDlg(CWnd* pParent /*=NULL*/)
	: CBitmapDialog(CGALLERYDlg::IDD, pParent)
{
	m_pMainWnd = (CCPHDlg *)pParent;
	//{{AFX_DATA_INIT(CGALLERYDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_bZoom = FALSE;
	CurrentPage = 0;
	m_pagenum = 0;
	//}}AFX_DATA_INIT
}

/*--------------------------------------------------------------------------------
*  ��Ա������   :DoDataExchange
*  ��������     :�Ի������ݹ�����
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*-----------------------------------------------------------------------------------
*/
void CGALLERYDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGALLERYDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGALLERYDlg, CBitmapDialog)
	//{{AFX_MSG_MAP(CGALLERYDlg)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_GAL_EXIT, OnExitClick)
	ON_BN_CLICKED(IDC_GAL_FORWARD, OnForwardClick)
	ON_BN_CLICKED(IDC_GAL_BACK, OnBackClick)
	ON_BN_CLICKED(IDC_GAL_ZOOM, OnZoomClick)
	ON_BN_CLICKED(IDC_GAL_EDIT, OnEditClick)

    ON_MESSAGE(UWM_GETPREPICTURE, OnGetWndMsg)  //++�Զ�����Ϣ
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGALLERYDlg message handlers
////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------------
*  ��Ա������   :OnInitDialog()
*  ��������     :�Ի����ʼ��
*  �����������	:
*  ���ر���˵�� :����TRUE��ʾ��ʼ���ɹ������򷵻�FALSE��ʾ��ʼ��ʧ��
*  �㷨����		:
*  ����˵��:
*-----------------------------------------------------------------------------------
*/
BOOL CGALLERYDlg::OnInitDialog() 
{

    CRect rect;
    GetClientRect(&rect);
	CBitmapDialog::OnInitDialog();
    //SetWindowPos(NULL,0,0,800,600,SWP_NOMOVE);
    
	CRect frect;
	m_pMainWnd->GetWindowRect(&frect);
	MoveWindow(frect.left, frect.top, frect.Width(), frect.Height(), FALSE);	
   

	 //DestroyWindow();

    //�Ի��������
    //CenterWindow(); 
	//���öԻ��򴰿ڵ�ͼ

    CString faceFile = g_strAppPath + "\\UseRes\\Face_manage.bmp";
	if(!SetBitmap(faceFile))
	    return FALSE; 
    //��ʼ���Ի����ϵİ�Ŧ
	InitButton();
	//��ʼ���Ի����ϵ�9��ͼ�󴰿�
	InitGallery();
	m_viewWnd.CreateEx(WS_EX_TOPMOST, NULL, "", WS_CHILD | WS_TABSTOP ,0, 70, 592, 458, m_hWnd, NULL);
	
	CreateBTNST();
	PicNumber = btnbmp.GetSize(); 
	if(PicNumber > 9)
		m_pagenum = 9;
	else
		m_pagenum = PicNumber%9;
	m_GALForward.ShowWindow(SW_HIDE);
	TotalPage = PicNumber/9 ;
	if(PicNumber<=9)
	{
		
		for(int i=0;i<PicNumber;i++)
			ShowBitmap(CurrentPage*9+i,i);
		m_GALBack.ShowWindow(SW_HIDE);
	}
	else
	{
		for(int i=0;i<9;i++)
			ShowBitmap(CurrentPage*9+i,i);
      //m_GALBack.ShowWindow(SW_HIDE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/*--------------------------------------------------------------------------------
*  ��Ա������   :OnCreate
*  ��������     :�������Ի���ʱ�ı�Ի����������
*  �����������	:
*   LPCREATESTRUCT lpCreateStruct���������ͽṹ����
*  ���ر���˵�� :����0��ʾ�ɹ��������壬����-1��ʾ���屻����
*  �㷨����		:
*  ����˵��:
*-----------------------------------------------------------------------------------
*/
int CGALLERYDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBitmapDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
// 	CRect frect;
//  CCPHDlg * maindlg = (CCPHDlg *)AfxGetMainWnd(); 
//	maindlg->GetWindowRect(&frect);
//	SetWindowPos(&wndTop, frect.left, frect.top, frect.Width(), frect.Height(), SWP_SHOWWINDOW);
    CenterWindow();

	return 0;
}

/*--------------------------------------------------------------------------------
*  ��Ա������   :OnPaint()
*  ��������     :���Ի���ӵ�WM_PAINT��Ϣʱ���»��ƴ���
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*-----------------------------------------------------------------------------------
*/
void CGALLERYDlg::OnPaint() 
{
	CPaintDC dc(this); 
    if (IsIconic())
	{
	    SendMessage(WM_ICONERASEBKGND,  (WPARAM) dc.GetSafeHdc(), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
       //Invalidate();
	}
	else
	{
			CBitmapDialog::OnPaint();
	}
//	m_viewWnd.Invalidate();
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   : GetButtonDefaultRect
*  ��������     : �õ�����������Ҫ��̬������ͼ�갴Ŧ��Ĭ�Ͼ�����
*  �����������	:
*      INT btnID:Ҫ��̬�����İ�Ŧ�������ؼ���ID��
*  ���ر���˵�� :����Ҫ�����ؼ���ָ���ľ���
*  �㷨����		:
*  ����˵��:
*--------------------------------------------------------------------------------
*/
CRect CGALLERYDlg::GetButtonDefaultRect(INT btnID)
{   
   	CRect rect;

    switch(btnID)
	{	
		//ǰ��ҳ��Ŧ
		case IDC_GAL_FORWARD:
			{ 
				rect.SetRect(28, 528, 28 + 70, 528 + 26); 
				break;  
			}  
		//��ҳ��Ŧ
		case IDC_GAL_BACK:                                  
			  {
				  rect.SetRect(490, 528, 490 + 70, 528 + 26);
				  break; 
			  }
        //���Ű�Ŧ
		case IDC_GAL_ZOOM:                      
			  {
				  rect.SetRect(659, 89, 659 + 123, 89 + 141);  
				  break;
			  }
        //�༭��Ŧ
		case IDC_GAL_EDIT:                            
			  { 
				  rect.SetRect(659, 249, 659 + 123, 249 + 141);
				  break; 
			  }
        //�˳���Ŧ
		case IDC_GAL_EXIT:                  
			  { 
				  rect.SetRect(658, 410, 658 + 142, 410 + 190);
				  break; 
			  }
		//��һ��ͼƬ����
		case IDC_GAL_SHOW0:                  
			  { 
				  rect.SetRect(29, 94, 29 + 160, 94 + 120);
				  break; 
			  }
		//�ڶ���ͼƬ����
		case IDC_GAL_SHOW1:                  
			  { 
				  rect.SetRect(210, 94, 219 + 160, 94 + 120);
				  break; 
			  }
		//������ͼƬ����
		case IDC_GAL_SHOW2:                  
			  { 
				  rect.SetRect(399, 94, 399 + 160, 94 + 120);
				  break; 
			  }
		//���ĸ�ͼƬ����
		case IDC_GAL_SHOW3:                  
			  { 
				  rect.SetRect(29, 239, 29 + 160, 239 + 120);
				  break; 
			  }
		//�����ͼƬ����
		case IDC_GAL_SHOW4:                  
			  { 
				  rect.SetRect(210, 239, 219 + 160, 239 + 120);
				  break; 
			  }
		//������ͼƬ����
		case IDC_GAL_SHOW5:                  
			  { 
				  rect.SetRect(399, 239, 399 + 160, 239 + 120);
				  break; 
			  }
		//���߸�ͼƬ����
		case IDC_GAL_SHOW6:                  
			  { 
				  rect.SetRect(29, 384, 29 + 160, 384 + 120);
				  break; 
			  }
		//�ڰ˸�ͼƬ����
		case IDC_GAL_SHOW7:                  
			  { 
				  rect.SetRect(210, 384, 219 + 160, 384 + 120);
				  break; 
			  }
		//�ھŸ�ͼƬ����
		case IDC_GAL_SHOW8:                  
			  { 
				  rect.SetRect(399, 384, 399 + 160, 384 + 120);
				  break; 
			  }
		//�Ŵ���ʾʱ�Ĵ���
		case IDC_GAL_SHOWBIG:                  
			  { 
				  rect.SetRect(36, 106, 36 + 520, 106 + 390);
				  break; 
			  }
		default:

			{  rect.SetRect(0, 0, 0, 0); }
		}//end switch

	return rect;
}


/*--------------------------------------------------------------------------------
*  ��Ա������   :GetResPath
*  ��������     :�õ���Դ�ļ����ڵ�Ŀ¼·��
*  �����������	:
*   UINT pathID: Ҫȡ�õ�·����ID��
*  ���ر���˵�� :�ļ����ڵľ���·��
*  �㷨����		:
*  ����˵��:
*-----------------------------------------------------------------------------------
*/
CString CGALLERYDlg::GetResPath(UINT pathID)
{
	CString strpath=_T("");
	switch(pathID)
	{
	case 0:
		strpath=g_strAppPath + _T("\\BtnRes\\");
		break;
    case 1:
		strpath=g_strAppPath + _T("\\MyPicture\\*.bmp");
        break;
	case 2:
		strpath=g_strAppPath + _T("\\MyPicture\\");
		break;
	default:
		break;
	}
   return strpath;
}


/*--------------------------------------------------------------------------------
*  ��Ա������   :InitButton()
*  ��������     :��ʼ���Ի����ϵ�ȫ����Ŧ
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*-----------------------------------------------------------------------------------
*/
void CGALLERYDlg::InitButton()
{  
	CString strBtnBmpPath=_T("");
	strBtnBmpPath = GetResPath(0);

	//����λͼλ��[��װĿ¼...]\BtnRes\  Ŀ¼��
    static CString btnbmp[]={_T("h1-2.bmp"), _T("h1-1.bmp"), _T("h2-2.bmp"), _T("h2-1.bmp"),     //h���� [0]---[3]
                               _T("h3-2.bmp"), _T("h3-1.bmp"), _T("h32-2.bmp"), _T("h32-1.bmp"), 	   //      [4]---[7]
	                           _T("h4-2.bmp"), _T("h4-1.bmp"), _T("h5-2.bmp"), _T("h5-1.bmp"), 	   //      [8]---[11]	
							};  
     
 	  //��ʼ����ǰ��Ŧ
	  m_GALForward.Create("", WS_VISIBLE|WS_TABSTOP, GetButtonDefaultRect(IDC_GAL_FORWARD), 
		            this, IDC_GAL_FORWARD); 
      m_GALForward.SetBitmaps(strBtnBmpPath + btnbmp[0], RGB(100, 0, 100), 
		                strBtnBmpPath + btnbmp[1], NULL); 
	  m_GALForward.SetTooltipText(_T("��һҳ"));

      //��ʼ�����Ŧ(a1)
  	  m_GALBack.Create("", WS_VISIBLE|WS_TABSTOP, GetButtonDefaultRect(IDC_GAL_BACK), this, IDC_GAL_BACK); 
      m_GALBack.SetBitmaps(strBtnBmpPath + btnbmp[2], RGB(100, 0, 100), strBtnBmpPath + btnbmp[3], NULL); 
  	  m_GALBack.SetTooltipText(_T("��һҳ"));
   
	  //��ʼ�����Ű�Ŧ(a2)
	  m_GALZoom.Create("", WS_VISIBLE|WS_TABSTOP, GetButtonDefaultRect(IDC_GAL_ZOOM), this, IDC_GAL_ZOOM); 
      m_GALZoom.SetBitmaps(strBtnBmpPath + btnbmp[4], RGB(100, 0, 100), strBtnBmpPath + btnbmp[5], NULL); 
  	  m_GALZoom.SetTooltipText(_T("�Ŵ�"));
	  m_bZoom = FALSE;

	 //��ʼ���༭��Ŧ(a3)
	  m_GALEdit.Create("", WS_VISIBLE|WS_TABSTOP, GetButtonDefaultRect(IDC_GAL_EDIT), this, IDC_GAL_EDIT); 
      m_GALEdit.SetBitmaps(strBtnBmpPath + btnbmp[8], RGB(100, 0, 100), strBtnBmpPath + btnbmp[9], NULL); 
  	  m_GALEdit.SetTooltipText(_T("�༭"));

      //��ʼ���˳���Ŧ(a4)
	  m_GALExit.Create("", WS_VISIBLE|WS_TABSTOP, GetButtonDefaultRect(IDC_GAL_EXIT), this, IDC_GAL_EXIT); 
      m_GALExit.SetBitmaps(strBtnBmpPath + btnbmp[10], RGB(100, 0, 100), strBtnBmpPath + btnbmp[11], NULL); 
  	  m_GALExit.SetTooltipText(_T("�˳�"));

	 

}

/*
*--------------------------------------------------------------------------------
*  ��Ա������   : OnExit()
*  ��������     : ������[�˳�]��Ŧʱ���˳�Ӧ�ó������Ϣ����
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*--------------------------------------------------------------------------------
*/
void CGALLERYDlg::OnExitClick() 
{
	EndDialog(0);
	SetCurrentDirectory(g_strAppPath);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :OnForwardClick() 
*  ��������     :��ǰ��ҳ
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*--------------------------------------------------------------------------------
*/
void CGALLERYDlg::OnForwardClick() 
{
	int PicYU = PicNumber % 9;
	m_pagenum = 9;
	m_GALBack.ShowWindow(SW_SHOW);
	for(int i=0;i<9;i++)
		m_ViewShow[i].ShowWindow(SW_SHOW);
	if(CurrentPage>0)
	{
		CurrentPage--;
		for(int i=0;i<9;i++)
			ShowBitmap(CurrentPage*9+i,i);
		if(CurrentPage==0)
			m_GALForward.ShowWindow(SW_HIDE);
	}	
}

/*--------------------------------------------------------------------------------
*  ��Ա������   :OnBackClick() 
*  ��������     :���ҳ
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*-----------------------------------------------------------------------------------
*/
void CGALLERYDlg::OnBackClick() 
{
	//�õ���ǰҳ������������ǰҳ���е�ͼ������
	int PicYU = PicNumber % 9;
	m_pagenum = PicYU;
	m_GALForward.ShowWindow(SW_SHOW);

	//��ʾ��ǰҳ
	if (CurrentPage<TotalPage-1)
	{
		CurrentPage++;
		for(int i=0;i<9;i++)
			ShowBitmap(CurrentPage*9+i,i);
		if((CurrentPage==TotalPage-1)&&(PicYU==0))
			m_GALBack.ShowWindow(SW_HIDE);
	}

	//���һҳ
	else if((CurrentPage==TotalPage-1)&&(PicYU!=0))
	{
		CurrentPage++;
		for(int i=0;i<PicYU;i++)
			ShowBitmap(CurrentPage*9+i,i);
		for(int j=PicYU;j<9;j++)
			m_ViewShow[j].ShowWindow(SW_HIDE);
		m_GALBack.ShowWindow(SW_HIDE);
	}
}


/*--------------------------------------------------------------------------------
*  ��Ա������   :OnEditClick()
*  ��������     :�༭��ǰѡ�е�ͼ��
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:�ڻ滭���д�ѡ��ͼ�󲢹رջ���Ի���
*-----------------------------------------------------------------------------------
*/

void CGALLERYDlg::OnEditClick() 
{
	if(PicNumber == 0)
		return;
		 for(int i = 0; i < 9; i++)
		{	
			if(m_ViewShow[i].GetPreFocus())
		    break;
		}
	 //DestroyWindow();
     m_pMainWnd->EditMyPicture(m_ViewShow[i].m_srcDib); 
     OnExitClick();

     
}


/*--------------------------------------------------------------------------------
*  ��Ա������   :InitGallery()
*  ��������     :��ʼ���Ի����ϵ�9��������ʾͼ�ε��Ӵ���
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*-----------------------------------------------------------------------------------
*/
void CGALLERYDlg::InitGallery()
{
	CString strBtnBmpPath=_T("");
	strBtnBmpPath = GetResPath(1);

	WIN32_FIND_DATA wfd;
	HANDLE hFind;
	bool bFind = true;
	//����\\MyPicture\\    Ŀ¼�µ�ȫ���ļ�
	hFind = FindFirstFile(strBtnBmpPath, &wfd);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		
		FindClose(hFind);
	}
	else
	{
		btnbmp.Add(wfd.cFileName);
		int i=1;
		
		while(bFind)
		{	
			if(FindNextFile(hFind, &wfd))
				bFind = TRUE;
			else
				bFind = FALSE;
			if(bFind)
				btnbmp.Add(wfd.cFileName);
			i++;
		}
		FindClose(hFind);
	}
}		

/*--------------------------------------------------------------------------------
*  ��Ա������   :OnZoomClick()
*  ��������     :���ŵ�ǰѡ�е�ͼƬ
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*-----------------------------------------------------------------------------------
*/
void CGALLERYDlg::OnZoomClick()
{	
	if(PicNumber == 0)
		return;
	CRect rect[9];
	rect[0] = CRectRECT_IMG0;
 	rect[1] = CRectRECT_IMG1;  
	rect[2] = CRectRECT_IMG2;
 	rect[3] = CRectRECT_IMG3;  
	rect[4] = CRectRECT_IMG4;
 	rect[5] = CRectRECT_IMG5;  
	rect[6] = CRectRECT_IMG6;
 	rect[7] = CRectRECT_IMG7;  
 	rect[8] = CRectRECT_IMG8;  

	CString strBtnBmpPath1=_T("");
	strBtnBmpPath1= GetResPath(0);
    INT focus = 0;
	//����λͼλ��[��װĿ¼...]\BtnRes\  Ŀ¼��
    static CString btnbmp1[]={_T("h1-2.bmp"), _T("h1-1.bmp"), 
		                      _T("h2-2.bmp"), _T("h2-1.bmp"),     //h���� [0]---[3]
                              _T("h3-2.bmp"), _T("h3-1.bmp"),
							  _T("h32-2.bmp"), _T("h32-1.bmp")   //[4]---[7]
							}; 
//����С
	if(m_bZoom)
	{
        for(focus = 0; focus< 9; focus++)
		{	if(m_ViewShow[focus].GetPreFocus())
		    break;
		}


		m_ViewShow[focus].SetWindowPos(&wndTop, rect[focus].left, rect[focus].top,
				                                    rect[focus].Width(), rect[focus].Height(),
													SWP_SHOWWINDOW); 

        for(int k = 0; k < focus; k++)
		{
				m_ViewShow[k].SetWindowPos(&wndTop, rect[k].left, rect[k].top,
				                                    rect[k].Width(), rect[k].Height(),
													SWP_SHOWWINDOW);   
		}

		for(int m = focus + 1; m < m_pagenum ; m++)
				m_ViewShow[m].SetWindowPos(&wndTop, rect[m].left, rect[m].top,
				                                    rect[m].Width(), rect[m].Height(),
													SWP_SHOWWINDOW);      
     
	    m_ViewShow[focus].SetBig(TRUE); 
	    m_ViewShow[focus].DrawSmall(); 

         m_bZoom = !m_bZoom;
	
		m_GALZoom.SetBitmaps(strBtnBmpPath1 + btnbmp1[4], g_stuPaintSet.tranCol, strBtnBmpPath1 + btnbmp1[5], NULL); 
  		m_GALZoom.SetTooltipText(_T("�Ŵ�"));
	}
	//�ǷŴ�
	else
	{
	  for(focus = 0; focus< 9; focus++)
		{	if(m_ViewShow[focus].GetPreFocus())
		    break;
		}

       for(int k = 0; k < focus; k++)
				m_ViewShow[k].SetWindowPos(&wndBottom, rect[k].left, rect[k].top,
				                                      rect[k].Width(), rect[k].Height(),
													  SWP_SHOWWINDOW);      

		for(int m = focus + 1; m < 9; m++)
				m_ViewShow[m].SetWindowPos(&wndBottom, rect[m].left, rect[m].top,
				                                    rect[m].Width(), rect[m].Height(),
													SWP_SHOWWINDOW);    

	   m_ViewShow[focus].SetBig(FALSE); 
	   //�Ŵ󽹵�ͼ
       m_ViewShow[focus].DrawBig(); 

       m_bZoom = !m_bZoom;

	   m_GALZoom.SetBitmaps(strBtnBmpPath1 + btnbmp1[6], g_stuPaintSet.tranCol, strBtnBmpPath1 + btnbmp1[7], NULL); 
  	   m_GALZoom.SetTooltipText(_T("��С"));    

	}

}

/*--------------------------------------------------------------------------------
*  ��Ա������   :ShowBitmap
*  ��������     :�ڶԻ����е�9��������ʾ����Ӧ��ͼ��
*  �����������	:
*    long PicNum:ö�ٳ���ͼ������
*    long number:��ǰҳ���ͼ�δ���λ�����
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*-----------------------------------------------------------------------------------
*/
void CGALLERYDlg::ShowBitmap(long PicNum,long number)
{
	CString strBtnBmpPath1=_T("");
	strBtnBmpPath1= GetResPath(2);
	m_ViewShow[number].SetPrePos(number);  
	switch(number)
	{
	case 0:	
		m_ViewShow[0].SetViewBitmap(strBtnBmpPath1 + btnbmp[PicNum]); 
		m_ViewShow[0].ShowWindow(SW_SHOW);
		m_ViewShow[0].SetPreFocus(TRUE); 
        m_ViewShow[0].Invalidate(TRUE); 

		break;
	case 1:
		m_ViewShow[1].SetViewBitmap(strBtnBmpPath1 + btnbmp[PicNum]); 
		m_ViewShow[1].ShowWindow(SW_SHOW);
	    m_ViewShow[1].Invalidate(TRUE); 
		break;
	case 2:
		m_ViewShow[2].SetViewBitmap(strBtnBmpPath1 + btnbmp[PicNum]); 
		m_ViewShow[2].ShowWindow(SW_SHOW);

        m_ViewShow[2].Invalidate(TRUE); 
		break;
	case 3:
		m_ViewShow[3].SetViewBitmap(strBtnBmpPath1 + btnbmp[PicNum]); 
		m_ViewShow[3].ShowWindow(SW_SHOW);
        m_ViewShow[3].Invalidate(TRUE); 
		break;
	case 4:
		m_ViewShow[4].SetViewBitmap(strBtnBmpPath1 + btnbmp[PicNum]); 
		m_ViewShow[4].ShowWindow(SW_SHOW);
		m_ViewShow[4].Invalidate(TRUE); 
		break;
	case 5:
		m_ViewShow[5].SetViewBitmap(strBtnBmpPath1 + btnbmp[PicNum]); 
		m_ViewShow[5].ShowWindow(SW_SHOW);
		m_ViewShow[5].Invalidate(TRUE);
		break;
	case 6:
		m_ViewShow[6].SetViewBitmap(strBtnBmpPath1 + btnbmp[PicNum]); 
		m_ViewShow[6].ShowWindow(SW_SHOW);
		m_ViewShow[6].Invalidate(TRUE);
		break;
	case 7:
		m_ViewShow[7].SetViewBitmap(strBtnBmpPath1 + btnbmp[PicNum]); 
		m_ViewShow[7].ShowWindow(SW_SHOW);
		m_ViewShow[7].Invalidate(TRUE);
		break;
	case 8:
		m_ViewShow[8].SetViewBitmap(strBtnBmpPath1 + btnbmp[PicNum]); 
		m_ViewShow[8].ShowWindow(SW_SHOW);
		m_ViewShow[8].Invalidate(TRUE);
		break;
	default:
		break;
	}
}


/*--------------------------------------------------------------------------------
*  ��Ա������   :CreateBTNST()
*  ��������     :�ڶԻ����ϴ���9��������ʾͼ�εĴ������
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*-----------------------------------------------------------------------------------
*/
void CGALLERYDlg::CreateBTNST()
{
	m_ViewShow[0].CreateEx(WS_EX_TOPMOST, NULL, "",WS_CHILD | WS_TABSTOP ,29, 94, 160, 120, m_hWnd, NULL);
	m_ViewShow[0].SetPrePos(0); 
	m_ViewShow[1].CreateEx(WS_EX_TOPMOST, NULL, "",WS_CHILD | WS_TABSTOP ,214, 94, 160, 120, m_hWnd, NULL);
	m_ViewShow[1].SetPrePos(1); 
	m_ViewShow[2].CreateEx(WS_EX_TOPMOST, NULL, "",WS_CHILD | WS_TABSTOP ,399, 94, 160, 120, m_hWnd, NULL);
	m_ViewShow[2].SetPrePos(2); 
	m_ViewShow[3].CreateEx(WS_EX_TOPMOST, NULL, "",WS_CHILD | WS_TABSTOP ,29, 239, 160, 120, m_hWnd, NULL);
	m_ViewShow[3].SetPrePos(3); 
	m_ViewShow[4].CreateEx(WS_EX_TOPMOST, NULL, "",WS_CHILD | WS_TABSTOP ,214, 239, 160, 120, m_hWnd, NULL);
	m_ViewShow[4].SetPrePos(4); 
	m_ViewShow[5].CreateEx(WS_EX_TOPMOST, NULL, "",WS_CHILD | WS_TABSTOP ,399, 239, 160, 120, m_hWnd, NULL);
	m_ViewShow[5].SetPrePos(5); 
	m_ViewShow[6].CreateEx(WS_EX_TOPMOST, NULL, "",WS_CHILD | WS_TABSTOP ,29, 384, 160, 120, m_hWnd, NULL);
	m_ViewShow[6].SetPrePos(6); 
	m_ViewShow[7].CreateEx(WS_EX_TOPMOST, NULL, "",WS_CHILD | WS_TABSTOP ,214, 384, 160, 120, m_hWnd, NULL);
	m_ViewShow[7].SetPrePos(7); 
	m_ViewShow[8].CreateEx(WS_EX_TOPMOST, NULL, "",WS_CHILD | WS_TABSTOP ,399, 384, 160, 120, m_hWnd, NULL);
	m_ViewShow[8].SetPrePos(8); 

}



/*--------------------------------------------------------------------------------
*  ��Ա������   :OnShowClick
*  ��������     :����ʾѡ�е�ͼƬʱ
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*-----------------------------------------------------------------------------------
*/
void CGALLERYDlg::OnShowClick(long Number)
{
	CString strBtnBmpPath1=_T("");
	strBtnBmpPath1= GetResPath(0);

	//����λͼλ��[��װĿ¼...]\BtnRes\  Ŀ¼��
    static CString btnbmp1[]={_T("h1-2.bmp"), _T("h1-1.bmp"), _T("h2-2.bmp"), _T("h2-1.bmp"),     //h���� [0]---[3]
                               _T("h3-2.bmp"), _T("h3-1.bmp"), _T("h32-2.bmp"), _T("h32-1.bmp"), 	   //      [4]---[7]
							};

	m_GALZoom.SetBitmaps(strBtnBmpPath1 + btnbmp1[5], RGB(100, 0, 100), strBtnBmpPath1 + btnbmp1[6], NULL); 
  	m_GALZoom.SetTooltipText(_T("��С"));

	SendMessage(WM_PAINT);
	int PicNum = CurrentPage*9 + Number;

}



/*--------------------------------------------------------------------------------
*  ��Ա������   :OnGetWndMsg
*  ��������     :�õ���ǰͼ���ӵ������Ų�����ǰ�ӱ߿�ͬʱ����󻯵�ǰͼ�Σ���������ͼ��
*  �����������	:
*    LPARAM wParam����ǰͼ�δ���ľ��
*    WPARAM nevent����Ϣ��ʶ��
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
//����   LPARAM=0  ��ʾ��ǰͼ�δ��ڻ��߿������������б߿���ȡ���߿�ͬʱȡ����������Ľ���״̬
//       LPARAM=1  ��ʾ��ǰͼ�δ���Ҫ�ָ�����������ͬʱ��ʾ
//       LPARAM=2  ��ʾ��ǰͼ�δ���Ҫ��󻯣���������������
//       LPARAM=3  ��ûʹ��*
*-----------------------------------------------------------------------------------
*/
LRESULT CGALLERYDlg::OnGetWndMsg(LPARAM wParam, WPARAM nevent)
{
     CViewBig * pCurrentWnd= (CViewBig*) wParam ;
     INT index = pCurrentWnd->GetPrePos(); 
     m_ViewShow[index].SetPreFocus(TRUE); 
   

	 switch(nevent)
	 {
		 case 0:
			 {  
				 m_ViewShow[index].DrawFrame(TRUE);
                 for(int i = 0; i < index; i++)
				 {
                    m_ViewShow[i].DrawFrame(FALSE);
                    m_ViewShow[i].SetPreFocus(FALSE);  
				 }
                 for(int k = index + 1; k < 9; k++)
				 {
					 m_ViewShow[k].DrawFrame(FALSE);	
                     m_ViewShow[k].SetPreFocus(FALSE);  					 
				 }
				 break;
			 
			 }
		 case 1:
			 { 
				 for(int i = 0; i < index; i++)
						m_ViewShow[i].ShowWindow(SW_SHOW);
				 for(int k = index + 1; k < 9; k++)
						m_ViewShow[k].ShowWindow(SW_SHOW);				 
				 break;
			 }
		 
		 case 2:
			 {
				 for(int i = 0; i < index; i++)
						m_ViewShow[i].ShowWindow(SW_HIDE);
				 for(int k = index + 1; k < 9; k++)
						m_ViewShow[k].ShowWindow(SW_HIDE);				 
				 break;
			 
			 }
			 case 3:
			 {
                 switch(index)
				 {
					 case 0:
						 { 
							m_ViewShow[0].MoveWindow(CRect(29, 94, 160, 120),TRUE); 		 
							break;
						 } 
					 case 1:
						 {
							m_ViewShow[1].MoveWindow(CRect(214, 94, 160, 120),TRUE); 	
							break;
						 }
					 case 2:
						 {
							m_ViewShow[2].MoveWindow(CRect(399, 94, 160, 120),TRUE); 	
							break;
						 }
					 case 3:
						 {
							m_ViewShow[3].MoveWindow(CRect(29, 239, 160, 120),TRUE); 	
							break;
						 }
					 case 4:
						 {
							m_ViewShow[4].MoveWindow(CRect(214, 239, 160, 120),TRUE); 
							break;
						 }					
					 case 5:
						 {
							m_ViewShow[5].MoveWindow(CRect(399, 239, 160, 120),TRUE); 
							break;
						 }
					 case 6:
						 {
							m_ViewShow[6].MoveWindow(CRect(29, 384, 160, 120),TRUE); 
							break;
						 }					
					 case 7:
						 {
							m_ViewShow[7].MoveWindow(CRect(214, 384, 160, 120),TRUE); 
							break;
						 }
		
					 case 8:
						 {
							m_ViewShow[8].MoveWindow(CRect(399, 384, 160, 120),TRUE); 
							break;
						 }
					 default:
						 break;
				 }//end switch
			 }

		 default:
			 break;
	 }//END switch

     return 0;
}

/*--------------------------------------------------------------------------------
*  ��Ա������   :GetPageNum()
*  ��������     :�õ���ǰѡ���ͼ�����
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��:
*-----------------------------------------------------------------------------------
*/
//���ص�ǰҳ�ϵĿ���ͼ������
INT CGALLERYDlg::GetPageNum()
{
	return m_pagenum;

}


/*--------------------------------------------------------------------------------
*  ��Ա������   : OnOK
*  ��������     : ���ػ����麯������ֹ�ûس����˳�����
*-----------------------------------------------------------------------------------
*/
void CGALLERYDlg::OnOK() 
{
	//EditMyPicture(m_DrawRect.m_pDib);
}


/*--------------------------------------------------------------------------------
*  ��Ա������   : OnCancel
*  ��������     : ���ػ����麯������ֹ��Escasp���˳�����
*-----------------------------------------------------------------------------------
*/
void CGALLERYDlg::OnCancel() 
{
}

void CGALLERYDlg::SetCphDlgWnd(CCPHDlg *pWnd)
{
   m_pMainWnd = pWnd;
}
