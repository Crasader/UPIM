/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��includeres.h
* �汾��  ��V1.0
* ��Ŀ���ƣ�CPH
* ��Ȩ������Copyright 2002-2003 . All Rights Reserved.
* ģ����������滭��԰Ӧ�ó���������Ҫʹ�õ��ⲿλͼ�ļ�����̬���鶨��
*======================================================
* �汾�����¼:
*      v1.0  2002-11-8   9��50   ��ΰ
*
* 
*/

/////////////////////////////////////////////////////////////////////////////

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//#include "resource.h"		// ������Դ�ļ�

#ifndef _INCLUDERES
#define _INCLUDERES

struct tagBTNRES
{
	//�������������
   INT BarIndex;
   //��ǰ����ϵİ�Ŧ������
    INT BtnIndex;  
	//��尴Ŧ��Ӧ���ļ���
	CString resFileName[2];
	//��ǰ����ϵİ�Ŧ��Ŀ
	INT count;
};



   //�����ɫ���ϵ�12����ɫ�ؼ���IDֵ���Ա㴴����ɫ���ϵ�ȡɫ�ؼ�
	static UINT sel[16]= {IDC_SELCOLOR0,  IDC_SELCOLOR1,  IDC_SELCOLOR2,  IDC_SELCOLOR3, 
	                      IDC_SELCOLOR4,  IDC_SELCOLOR5,  IDC_SELCOLOR6,  IDC_SELCOLOR7, 
				          IDC_SELCOLOR8,  IDC_SELCOLOR9,  IDC_SELCOLOR10,  IDC_SELCOLOR11,
						  IDC_SELCOLOR12,  IDC_SELCOLOR13,  IDC_SELCOLOR14,  IDC_SELCOLOR15,
};



//	static COLORREF col[12] = {RGB(255, 0, 0), RGB(255, 255, 255), RGB(128, 128, 128), RGB(0, 0, 0), 
//		                       RGB(199, 178, 154), RGB(0, 186, 81), RGB(96, 57, 19), RGB(255, 0, 255), 
//		                       RGB(0, 0, 255), RGB(0, 255, 255), RGB(0, 255, 0), RGB(255, 0, 0)
//	};


	struct IniPaintSet
	{
		//[SET]   ��ǰȡ�ļ�����
		//����ͼ�ļ���:   ���ͺ�_img��λ��_���.bmp
		//ȫͼ�ļ���:     ���ͺ�_Pimg��λ��_���.bmp
		INT curType;
        BOOL bCartoonOrgSize; //��ͨ�����뻭��ʱ�Ƿ�Ϊԭͼ�ߴ磬Ϊ0ʱ����ʾ��Сͬ�����ڵĻ���λ���й�
		INT  Transparence;    //�����4�ڻ���������ʱ��͸���̶�(0-100)
        BOOL bAutoSave;       //�������ϵ�ͼ�����ʱ,ʱ��ʱ�Զ��ĸ����������EXE�е���ʾͼ������� 

        COLORREF tranCol;   //�ڻ�������λͼʱ��͸����ɫ(��ʼ��Ϊ�ۺ�ɫRGB(255,0,255)) 
        CString saveTmpFile;  //�����ر�ʱ,Ĭ�ϱ������ʱλͼ�ļ���(λ��Ӧ�ó���Ŀ¼)
    //    COLORREF colTran;     //�滭��͸��ɫ



		//[IMAGENUM]  //��Ӧ10�����Ŀ����ļ�����
		INT img1Num;
		INT img2Num;
		INT img3Num;
		INT img4Num;
		INT img5Num;
		INT img6Num;
		INT img7Num;
		INT img8Num;
		INT img9Num;
		INT img10Num;
        
        //10�����Ϳ�ͨͼ��Ŧ�ϵ���ʾ��Ϣ
		CString img1ToolTip;
		CString img2ToolTip;
		CString img3ToolTip;
		CString img4ToolTip;
		CString img5ToolTip;
		CString img6ToolTip;
		CString img7ToolTip;
		CString img8ToolTip;
		CString img9ToolTip;
		CString img10ToolTip;

		//����������Ķ���
		INT Speci1Num;   //��һ�����ͣ�������ѡ������
		INT Speci2Num;   //�ڶ������ͣ���갴���ƶ�ѡ�� ���ϣ��£����ң�     
		INT Speci3Num;   //���������ͣ���������ƶ�ѡ��
		INT Speci4Num;   //���������ͣ���������ƶ����ѡ��

	}INIPAINTSET;

	//����λͼλ��[��װĿ¼...]\BtnRes\  Ŀ¼��
	
    static CString btnbmp[]={_T("a1-2.bmp"), _T("a1-1.bmp"), _T("a2-2.bmp"), _T("a2-1.bmp"),     //a���� [0]---[3]
                               _T("a3-2.bmp"), _T("a3-1.bmp"), _T("a4-2.bmp"), _T("a4-1.bmp"), 	   //      [4]---[7]
	                           _T("a5-2.bmp"), _T("a5-1.bmp"), _T("a6-2.bmp"), _T("a6-1.bmp"), 	   //      [8]---[11]
                               _T("a7-2.bmp"), _T("a7-1.bmp"), _T("a8-2.bmp"), _T("a8-1.bmp"),     //      [12]---[15]
	                           _T("a9-2.bmp"), _T("a9-1.bmp"), _T("a10-2.bmp"), _T("a10-1.bmp"),   //      [16]---[19]

							   _T("b1-2.bmp"), _T("b1-1.bmp"), _T("b2-2.bmp"), _T("b2-1.bmp"),     //b���� [20]---[23]
                               _T("b3-2.bmp"), _T("b3-1.bmp"), _T("b4-2.bmp"), _T("b4-1.bmp"), 	   //      [24]---[27]
	                           _T("b5-2.bmp"), _T("b5-1.bmp"), _T("b6-2.bmp"), _T("b6-1.bmp"), 	   //      [28]---[31]

							   //C����Ϊ10�ֿ�ͨ��Ŧ�ϵ�ͼ����Щͼ���ڼ���ʱ��Ҫ���ݵ�ǰϵͳָ���Ļ�ͼ�����ػ���ָ���ļ���
							   _T("0_c1-2.bmp"), _T("0_c1-1.bmp"), _T("0_c2-2.bmp"), _T("0_c2-1.bmp"), 	   //c���� [32]---[35]
							   _T("0_c3-2.bmp"), _T("0_c3-1.bmp"), _T("0_c4-2.bmp"), _T("0_c4-1.bmp"), 	   //      [36]---[37]
							   _T("0_c5-2.bmp"), _T("0_c5-1.bmp"), _T("0_c6-2.bmp"), _T("0_c6-1.bmp"), 	   //      [40]---[43]		
							   _T("0_c7-2.bmp"), _T("0_c7-1.bmp"), _T("0_c8-2.bmp"), _T("0_c8-1.bmp"), 	   //      [44]---[47]
							   _T("0_c9-2.bmp"), _T("0_c9-1.bmp"), _T("0_c10-2.bmp"), _T("0_c10-1.bmp"),   //      [48]---[51]			
							 
                               _T("d1-2.bmp"), _T("d1-1.bmp"), _T("d2-2.bmp"), _T("d2-1.bmp"), 	   //d���� [52]---[55]
	                           _T("d3-2.bmp"), _T("d3-1.bmp"), _T("d4-2.bmp"), _T("d4-1.bmp"), 	   //      [56]---[57]
                               _T("d5-2.bmp"), _T("d5-1.bmp"), _T("d6-2.bmp"), _T("d6-1.bmp"), 	   //      [60]---[63]
	                           _T("d7-2.bmp"), _T("d7-1.bmp"), _T("d8-2.bmp"), _T("d8-1.bmp"), 	   //      [64]---[67]

							   _T("e1-2.bmp"), _T("e1-1.bmp"), _T("e2-2.bmp"), _T("e2-1.bmp"),     //e���� [68]---[71]
		                       _T("e3-2.bmp"), _T("e3-1.bmp"), _T("e4-2.bmp"), _T("e4-1.bmp"), 	   //      [72]---[75]
							   
							   _T("exit-2.bmp"), _T("exit-1.bmp"),	                           //      [76]---[79]
                               _T("d1-3.bmp"), _T("d2-3.bmp"),
	
	};  




static  CString tagBarFile[] = {//��״[0]--[15]
								_T("g19-2.bmp"), _T("g19-1.bmp"),
	                            _T("g18-2.bmp"), _T("g18-1.bmp"), _T("g11-2.bmp"), _T("g11-1.bmp"), 
	                            _T("g12-2.bmp"), _T("g12-1.bmp"), _T("g13-2.bmp"), _T("g13-1.bmp"), 
	                            _T("g14-2.bmp"), _T("g14-1.bmp"), _T("g15-2.bmp"), _T("g15-1.bmp"), 
                                _T("g16-2.bmp"), _T("g16-1.bmp"),  
                               //�����[16] --[23](��Щͼ��ɸ������ø����ļ������ļ���ǰ����   ���_)
                                _T("g21-2.bmp"), _T("g21-1.bmp"), _T("g22-2.bmp"), _T("g22-1.bmp"), 
	                            _T("g23-2.bmp"), _T("g23-1.bmp"), _T("g24-2.bmp"), _T("g24-1.bmp"), 
                               //����[24]-[29]
                                _T("g31-2.bmp"), _T("g31-1.bmp"), _T("g32-2.bmp"), _T("g32-1.bmp"), 
	                            _T("g33-2.bmp"), _T("g33-1.bmp"),                       
                               //��Ҷ�Ĺ�����Ŧ[30]--[33]
                               _T("g51-2.bmp"), _T("g51-1.bmp"), _T("g52-2.bmp"), _T("g52-1.bmp"), /*   _T("g51-3.bmp"), _T("g52-3.bmp"),*/
							   //Ȧѡ���߰�Ŧ[34]-[43]
							   _T("g41-2.bmp"), _T("g41-1.bmp"), _T("g42-2.bmp"), _T("g42-1.bmp"),
							   _T("g43-2.bmp"), _T("g43-1.bmp"), _T("g44-2.bmp"), _T("g44-1.bmp"),							
                         	   _T("g45-2.bmp"), _T("g45-1.bmp"),

							   //������״[44]-[45]
                         	   _T("g17-2.bmp"), _T("g17-1.bmp"),
							    
							   //�����������͵���̬[46]- [48]
                         	   _T("g31-3.bmp"), _T("g32-3.bmp"), _T("g33-3.bmp")

};


//������ļ�����ͨͼƬ��151��ͼƬimg[0]---img[150]λ��\\picture\\Ŀ¼�£���̬���ã����Լӷ�ʽ����Ԥ���徲̬���飩
               


#endif   