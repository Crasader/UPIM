/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��ENUM.h
* �汾��  ��V1.0
* ��Ŀ���ƣ�CPH
* ��Ȩ������Copyright 2002-2003 . All Rights Reserved.
* ģ����������滭��԰Ӧ�ó��������е�ö�ٶ���
*======================================================
* �汾�����¼:
*      v1.0  2002-11-4   14:30    
*
* 
*/

/////////////////////////////////////////////////////////////////////////////

// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_SHAPEPEN_3DBDD86701F6_INCLUDED
#define _INC_SHAPEPEN_3DBDD86701F6_INCLUDED
//////////////////////////////////////////////////////////////////////

const COLORREF COLOR_BLACK = RGB(0, 0, 0);
const COLORREF COLOR_WHITE = RGB(255, 255, 255);
const COLORREF COLOR_PINK = RGB(255, 0, 255);

const  INT COLOR_NUMBER	= 256;
const COLORREF PP_FILL_COLOR = COLOR_BLACK;         //�����ɫ
const INT PP_PEN_COLOR = 1;                        //������ɫ
const INT SHOWSCROLL =  0;                         //����ʾ������


//���嵱ǰ������������
typedef enum PRETOOLBAR
{
	PBASEPEN,    //������
	PSPECIAPEN,  //������(��û���õ�)
	PPICTURES   //ͼƬ
};

//���廭�ʹ������͵�ö��

typedef enum BASEPEN 
{
	SELRGN,		 //Ȧѡ���� 
	PEN,			//����: �켣��Ǧ�ʡ���ˢ����״����ǹ������Ͱ����Ƥ
	SUCKERPEN,		//����
	SPECIA,			//�����
	TEXT			//����
};

/*
*ö����: PEN_TYPE
*˵��  : ����ʵ����͵�ö��
*�汾
*	Revision 1.0	2002/11/21     	������ʼ����
*/
typedef enum enuPEN_TYPE
{
	PTP_PENCIL,			//Ǧ��
	PTP_RUBBER,			//��Ƥ��
	PTP_PAINTBRUSH,		//��ˢ
	PTP_AIRPEN,			//��ǹ
	PTP_PAINTTUB		//����Ͱ
}PEN_TYPE;

//////////////////////////////////////////////////////////////////
/*
*ö����: PEN_TRACK
*˵��������ʵĹ켣�������������ֹ켣
*�汾
*	Revision 1.0	2002/11/12     	������ʼ����
*/
typedef enum enuPEN_TRACK
{
	PT_RANDOM,				// ����켣
	PT_LINE,				// ֱ��
	PT_ELLIPSE,				// ��Բ
	PT_TRIANGLE,			// ������
	PT_RECTANGLE,			// ����
	PT_TETRAGON,			// �Ľ���
	PT_PENTAGON,			// �����
	PT_FIVESIDE,			// �����
	PT_POLYGON,				// �����
	PT_ARROW                // ��ͷ
} PEN_TRACK;

//////////////////////////////////////////////////////////////////
//���������ö��
enum SPECIAPEN 
{
	LEAF=0,	   //��Ҷ
	ARROW,	   //��ͷ
	WOODBAR,   //ľդ��(�˲�)
    BLEB,      //ˮ��
	WOODBAR1  //ľդ��(�в�)
};
///////////////////////////////////////////////////////////////////
//����ͼƬ��ˢ����ö��
typedef enum PICTURES 
{/*
	NATURE,        //��Ȼ����
	PEOPLE,	       //����
	ANIMAL,	       //����
	HEXABOD,	   //����
	SEAANIMAL,	    //������
	COSTERMONGER,	//ˮ��
	PLANT,	        //ֲ��
	TRAFFIC,	    //��ͨ����
	BUILDING,	    //������
	FIRMAMENT	    //̫��
*/
	IMAGE_1,        //��Ȼ����
	IMAGE_2,	       //����
	IMAGE_3,	       //����
	IMAGE_4,	   //����
	IMAGE_5,	    //������
	IMAGE_6,	//ˮ��
	IMAGE_7,	        //ֲ��
	IMAGE_8,	    //��ͨ����
	IMAGE_9,	    //������
	IMAGE_10	    //̫��
};

//////////////////////////////////////////////////////////////////////
//����ʴ�����ö��
/*
*ö����: PEN_STYLE
*˵��������ʼ���״��ö�ٳ������������ֱʼ���״
*�汾
*	Revision 1.0	2002/11/1     	������ʼ����
*/
typedef enum enuPEN_STYLE
{
	PS_CIRCLE,				// Բ�αʼ�
	PS_VELLIPSE,			// ��ֱ����Բ�ʼ�
	PS_HELLIPSE,			// ˮƽ����Բ�ʼ�
	PS_RELLIPSE,			// ������б����Բ�ʼ�
	PS_LELLIPSE		    	// ������б����Բ�ʼ�	
} PEN_STYLE;

//////////////////////////////////////////////////////////////////////
//������������ö��
typedef enum FONTSTYLE
{
   BOLD,        //�Ӵ�
   INCLINE,     //��б
   UNDERLINE    //�»���
 
};


/*
*ö����: SELECT_TOOL
*˵��������ѡ�񹤾ߵļ����ӹ���
*�汾
*	Revision 1.0	2002/11/21    	������ʼ����
*/
typedef enum enuSELECT_TOOL
{
	ST_ALL,					// ȫ��ѡ��
	ST_RECTANGLE,			// ���ο�ѡ��
	ST_CUT,					// ����
	ST_COPY,				// ����
	ST_PASTE				// ճ��
}SELECT_TOOL;




#endif /* _INC_SHAPEPEN_3DBDD86701F6_INCLUDED */
