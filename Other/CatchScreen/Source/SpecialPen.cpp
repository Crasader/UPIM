
/**
*  SpecialPen.cpp
*  CPH 1.0 ��
*  �������ʵĹ��ܣ���Ҷ����ͷ��դ����ˮ��)
*  Copyright 2002-2003 . All Rights Reserved.
*  ʵ��ʰɫ����
*====================================================
*  �汾�����¼
*  CPH 1.0 2002/11/13 
*
*  CPH 1.0 2002/11/14  ������ڴ�й¶����
*
*/

#include "stdafx.h"
#include "..\Paint\PaintDlg.h"
#include "..\\include\\SpecialPen.h"
#include  <math.h>


#include "..\\include\\includeres.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//Ӧ�ó�������·��,��"c:\cph\"
extern  CString g_strAppPath;        
extern  IniPaintSet g_stuPaintSet;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*
*--------------------------------------------------------------------------------
*  CSpecialPen()
*  ��Ĺ��캯��
*  Parameter :
*     ��
*  Return value:
*     ��
*====================================================
*  �汾�����¼
*  CPH 1.0 2002/11/13  ������ݵĳ�ʼ��
*
*/


CSpecialPen::CSpecialPen(CCPHDlg * pMainWnd/*==NULL*/)
{
	m_pMainWnd = pMainWnd;
	m_psDib = new CDib();
	m_speciapen = LEAF;
	
	m_memDC.CreateCompatibleDC (NULL);

    //���ó�ʼ͸����Ϊ 30%
	m_iTransparence = g_stuPaintSet.Transparence;


	//����Ĭ�������
	m_nStyle = 0;
	m_nIndex = 0;
    SetCursor(AfxGetApp()->LoadCursor(IDC_ARROW));
}

CSpecialPen::~CSpecialPen()
{
	if(m_psDib)
	{
		delete m_psDib;
		m_psDib = NULL;
	}
}

/*
*--------------------------------------------------------------------------------
*  GetWidth()
*  ȡ������ʵĿ��
*  Parameter :  
*              ��
*  Return value:
*              ��
*====================================================
*  �汾�����¼
*  CPH 1.0 2002/11/13  ȡ������ʵĿ��
*
*/

int CSpecialPen::GetWidth()
{
 //  return m_bitmap.bmWidth; 
   return m_psDib->GetWidth();
}

/*
*--------------------------------------------------------------------------------
*  GetHeight()
*  ȡ������ʵĸ߶�
*  Parameter :  
*              ��
*  Return value:
*              ��
*====================================================
*  �汾�����¼
*  CPH 1.0 2002/11/13  ȡ������ʵĸ߶�
*
*/

int CSpecialPen::GetHeight()
{
   return m_psDib->GetHeight();; 
}

/*
*--------------------------------------------------------------------------------
*  GetDibWidth()
*  ȡ��DIB����ʵĿ��
*  Parameter :  
*              ��
*  Return value:
*              ��
*====================================================
*  �汾�����¼
*  CPH 1.0 2002/11/22 ��ΰ ȡ��DIB����ʵĿ��
*
*/

int CSpecialPen::GetDibWidth()
{
   return m_psDib->GetWidth();
}

/*
*--------------------------------------------------------------------------------
*  GetDibHeight()
*  ȡ��DIB����ʵĸ߶�
*  Parameter :  
*              ��
*  Return value:
*              ��
*====================================================
*  �汾�����¼
*  CPH 1.0 2002/11/22 ��ΰ ȡ��DIB����ʵĸ߶�
*
*/

int CSpecialPen::GetDibHeight()
{
   return m_bitmap.bmHeight; 
}



/*
*--------------------------------------------------------------------------------
*  SetTransparence()
*  ����͸����
*  Parameter :  
*              [IN]    iTransparence
*                 ͸����(0��100)
*  Return value:
*              ��
*====================================================
*  �汾�����¼
*  CPH 1.0 2002/11/13  ����͸����
*
*/

void CSpecialPen::SetTransparence (int iTransparence)
{
    m_iTransparence = iTransparence;
}

/*
*--------------------------------------------------------------------------------
*  chooseSpecialPen()
*  ѡ�����⻭�� 
*  Parameter :  
*              [IN]    nStyle
*                 ����(1.��Ҷ, 2.��ͷ, 3.դ��, 4.ˮ��)
*              [IN]    nIndex
*                 ���
*  Return value:
*              TRUE or FALSE
*====================================================
*  �汾�����¼
*  CPH 1.0 2002/11/13  ѡ�����⻭�ʣ����ѻ���װ���ڴ� 
*
*/

BOOL CSpecialPen::chooseSpecialPen (int nStyle, int nIndex)
{

	if (nStyle < 0 || nStyle > 3 || nIndex < 0 || nIndex >= MAX_SPECIALPEN)
		return FALSE;
	m_nStyle = nStyle;
	m_nIndex = nIndex;

	//�ж�ѡ�������ʾ���Ƿ�Ϊ��
	if (m_hBitmap[m_nStyle][m_nIndex] == NULL) 
		return FALSE;

	//��ָ��������ʾ��װ���ڴ�
	m_memDC.SelectObject (m_hBitmap[m_nStyle][m_nIndex]);
	::GetObject (m_hBitmap[m_nStyle][m_nIndex], sizeof (m_bitmap), &m_bitmap);

    m_speciapen = SPECIAPEN(nStyle);
    if(nStyle == 2 && nIndex == 1)
		m_speciapen = WOODBAR1;

    return TRUE;
}

/*
*--------------------------------------------------------------------------------
*  Draw()
*  ��������ڻ����ϻ�ͼ
*  Parameter :  
*              [IN]    hDC
*                 �滭���
*              [IN]    point
*                 �����ϵ�λ��
*  Return value:
*              ��
*====================================================
*  �汾�����¼
*  CPH 1.0 2002/11/13  �����������ڻ����ϻ�ͼ
*
*/

void CSpecialPen::Draw(HDC hDC, CPoint point)
{

	int i, j;
    CPoint currentPoint;

	//���m_nStyle����4(��ˮ��)������͸����
    if (m_nStyle == 3)
	{
		//�õ���ˮ�����ĵ�
		int iTemp = m_bitmap.bmWidth;
		currentPoint.x = point.x - iTemp / 2;
		currentPoint.y = point.y - iTemp / 2;

		//�û�����λͼ����ˮ��λͼ�в��ԵĲ���
		for (i=0; i < iTemp; i++)
			for (j=0; j<iTemp; j++)
				if (sqrt (pow ((i - iTemp / 2), 2) + pow ((j - iTemp / 2),2)) >= iTemp / 2 -1)
					m_memDC.SetPixel (i, j, GetPixel (hDC, i + currentPoint.x, j+ currentPoint.y));

        //�� Alpah ͨ��ʹˮ�ݰ�һ����͸������ʾ�ڻ�����
		BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255 * m_iTransparence / 100, 0};
		AlphaBlend (hDC,
					currentPoint.x, currentPoint.y,
					iTemp, iTemp,
					m_memDC.GetSafeHdc(), 
					0, 0,
					iTemp, iTemp,
					blend
					); 


	}
	else
		//��ʾλͼ(�����)��������
		for (i=0; i < m_bitmap.bmWidth; i++)
			 for (j=0; j < m_bitmap.bmHeight; j++)
				if (GetPixel (m_memDC,i,j) != g_stuPaintSet.tranCol)
					BitBlt (hDC, 
					        point.x - m_bitmap.bmWidth / 2 + i, point.y - m_bitmap.bmHeight / 2 + j,
					        1,1,
					        m_memDC.GetSafeHdc(),i,j,SRCCOPY); 

}


/*
*--------------------------------------------------------------------------------
*  ChangeBitmapSize()
*  ��������ڻ����ϻ�ͼ
*  Parameter :  
*              [IN]    hBitmap
*                 �����λͼ���
*              [IN]    ID
                   ����ʵ�ID��(0-3)
*              [IN]    Index
*                 �����λͼ�����(0-MAX)
*              [IN]    newRect
*                 λͼ���³ߴ�
*  Return value:
*              �����ź��λͼ�ߴ�
*====================================================
*  �汾�����¼
*  CPH 1.1 2002/11/22 ��ΰ ���ӽ������λͼ�������õĳߴ�������ź���Ϊ��ǰ��ͼ�õ�λͼ
*/
HBITMAP CSpecialPen::ChangeBitmapSize(HBITMAP hBitmap, INT ID, INT index, CRect newRect)
{	
	//�����Ի����еõ���ǰ����ʵ�����
   INT presize = 100;
   
	m_speciapen = m_pMainWnd->GetSpeciaStyle();

    switch(m_speciapen)
	{
		//��Ҷ(��С20*20,���300*300)
		case LEAF:
			{
                 presize = 20 + INT(double(presize - 1) * 2.8);
                 break;
			}
		//��ͷ(��С50*50,���300*300)
		case ARROW:
			{
                 presize = 50 + INT(double(presize- 1 ) * 2.5);
                 break;
			}
		//դ��(��С�ݲ���)
		case WOODBAR:
			{
                 presize = -1;
                 break;
			}
		//ˮ��(��С����)
		case BLEB:
			{
                 presize = -1;
                 break;
			}
	}//end switch

	m_psDib->Create(CRect(0, 0, 300, 300)); 
    m_psDib->Load(m_bmpFile[ID][index]); 

    LONG windth = m_psDib->GetWidth();
	LONG hight = m_psDib->GetHeight();
	m_psDib->ChangeImageSize(presize, presize);
    windth = m_psDib->GetWidth();
	hight = m_psDib->GetHeight();
	CBitmap * bitmap = m_psDib->GetBitmap();    
	
    hBitmap = (HBITMAP)bitmap;   
	//delete m_psDib;
	//m_psDib = NULL;
	return hBitmap;	
}


/*
*--------------------------------------------------------------------------------
*  DrawDIB()
*  ��������ڻ����ϻ�ͼ
*  Parameter :  
*              [IN]    pDC
*                 Ҫ��ʾ���豸������
*              [IN]   point
*                 λͼ��ʾ��λ��
*              [IN]   ID
*                 ����ʵ�ID��(0-3)
*              [IN]   Index
*                 �ļ���������(0-MAX)
*              [IN]   size
*                 λͼ���³ߴ�
*              [IN]isChange
                 λͼ�ĳߴ��Ƿ�Ҫ�仯
*  Return value:
*              
*====================================================
*  �汾�����¼
*  CPH 1.1 2002/11/22 ��ΰ ���Ӷ�DIBͼ�ε���ʾ����
*/

void CSpecialPen::DrawDIB(CDC * pDC, CPoint point, INT ID, INT index, INT size, BOOL isChange)
{
    INT w, h;	
   
 //	m_speciapen = m_pMainWnd->GetSpeciaStyle();  
      
	if(isChange)
	{  
		m_psDib->Load(m_bmpFile[ID][index]); 
  
		 switch(m_speciapen)
		{
			//��Ҷ(��С20*20,���300*300)
			case LEAF:
				{
					 size = 20 + INT(double(size- 1) * 2.8);
					 break;
				}
			//��ͷ(��С50*50,���300*300)
			case ARROW:
				{
					 size = 50 + INT(double(size- 1 ) * 2.5);
					 break;
				}
			//դ��(��С�ݲ���)
			case WOODBAR:
			case WOODBAR1:
				{
					 size = 50 + INT(double(size- 1 ) * 2.5);
					 break;
				}
			//ˮ��(��С����)
			case BLEB:
				{
					 size = -1;
					 break;
				}
		}//end switch
	}
    if(m_psDib &&  size!= -1)
	{
		//��ľդ��
		if(isChange && m_speciapen !=WOODBAR && m_speciapen !=WOODBAR1)
			m_psDib->ChangeImageSize(size, size);
		//�˲�ľդ��
		else if(m_speciapen ==WOODBAR)
			m_psDib->ChangeImageSize(size/5, size);
		//�в�ľդ��
		else if(m_speciapen ==WOODBAR1)
			m_psDib->ChangeImageSize(size*2/5, size);

		 w = m_psDib->GetWidth();
		 h = m_psDib->GetHeight(); 
	//	 m_psDib->DisplayTransparent(pDC, point.x -w/2 , point.y - h/2, RGB(255, 0, 255)); 
        m_psDib->DisplayTransparent(pDC, point.x -w/2 , point.y - h/2, g_stuPaintSet.tranCol); 


	}
}


//���ݵ�ǰϵͳ���õ������������³�ʼ����Ч��Ҫ������ļ���
void CSpecialPen::InitBmpFile(INT type)
{
   INT i;
   for(INT k=0;k<4;k++)
	   for(INT n=0;n<MAX_SPECIALPEN;n++)
            m_bmpFile[k][n] =_T("");

   //��һ�ֱ�
   for(i = 0 ; i < g_stuPaintSet.Speci1Num && i<MAX_SPECIALPEN; i++)
   {
	   m_bmpFile[0][i].Format("%s\\Picture\\%d_SpecialPen1_%d.bmp", g_strAppPath,g_stuPaintSet.curType,i);
	   m_btn1File[i].Format("%s\\Picture\\%d_SpecialBtn1_%d.bmp", g_strAppPath,g_stuPaintSet.curType,i);
   }
  //�ڶ��ֱ�
   for(i = 0 ; i < g_stuPaintSet.Speci2Num && i<MAX_SPECIALPEN; i++)
	   m_bmpFile[1][i].Format("%s\\Picture\\%d_SpecialPen2_%d.bmp", g_strAppPath,g_stuPaintSet.curType,i);
   
 //�����ֱ�
   for(i = 0 ; i < g_stuPaintSet.Speci3Num && i<MAX_SPECIALPEN; i++)
	   m_bmpFile[2][i].Format("%s\\Picture\\%d_SpecialPen3_%d.bmp", g_strAppPath,g_stuPaintSet.curType,i);

   //�����ֱ�
   for(i = 0 ; i < g_stuPaintSet.Speci4Num && i<MAX_SPECIALPEN; i++)
	   m_bmpFile[3][i].Format("%s\\Picture\\%d_SpecialPen4_%d.bmp", g_strAppPath,g_stuPaintSet.curType,i);

	//��ʼ������ʾ��
    for(i=0;i<4;i++)
		for(INT k=0;k<MAX_SPECIALPEN;k++)
		{
			if(m_bmpFile[i][k].IsEmpty())
				continue;
            m_hBitmap[i][k] = (HBITMAP) ::LoadImage (AfxGetInstanceHandle(),
											 m_bmpFile[i][k], IMAGE_BITMAP,
											 0, 0,
											 LR_LOADFROMFILE
											 );
		}

}

//�õ���һ������ʵ�������Ϊindex ���ļ���
CString CSpecialPen::GetBtnFile(INT index)
{
    CString fileName;
	if(index >= 0 && index < MAX_SPECIALPEN)
	   fileName = m_btn1File[index];
	return fileName;
}

void CSpecialPen::SetMainWnd(CCPHDlg *pWnd)
{
    m_pMainWnd = pWnd;
}

void CSpecialPen::SetPenType(INT penType)
{    
   m_speciapen = SPECIAPEN(penType);
 
}
