/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��IniFile.h
* �汾��  ��V1.0
* ��Ŀ���ƣ�
* ��Ȩ������Copyright 2007 . All Rights Reserved.
* ģ�����������д.ini�ļ������ͷ�ļ�(API��ʽ)
*======================================================
* �汾�����¼:
*     
*
* 
*/
/////////////////////////////////////////////////////////////////////////////
#ifndef _READWRETE_INIFILE_H_
#define _READWRETE_INIFILE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


///////////////////////////////////////////////////////////////////////
/*
*����    : CIniFile 
*˵��    : ��дINI�ļ�����
*�����¼:
*
*/
class CIniFile  
{
public:
	BOOL WriteIni(CString SectionTxt, CString ItemTxt, COleDateTime dateValue);
	BOOL WriteIni(CString SectionTxt, CString ItemTxt, COLORREF colValue);
	BOOL WriteIni(CString SectionTxt, CString ItemTxt, DOUBLE doubleValue,INT dec=3);
	BOOL WriteIni(CString SectionTxt, CString ItemTxt, INT intValue);
	BOOL WriteIni(CString SectionTxt, CString ItemTxt, LONG longValue);
	BOOL WriteIni(CString SectionTxt, CString ItemTxt, CString strValue);

	BOOL ReadIni(CString SectionTxt, CString ItemTxt, COleDateTime &dateValue);
	BOOL ReadIni(CString SectionTxt, CString ItemTxt, COLORREF &colValue);
	BOOL ReadIni(CString SectionTxt, CString ItemTxt, DOUBLE &doubleValue);
	BOOL ReadIni(CString SectionTxt, CString ItemTxt, LONG &longValue);
	BOOL ReadIni(CString SectionTxt, CString ItemTxt, INT &intValue);
	BOOL ReadIni(CString SectionTxt,CString ItemTxt,CString &strValue);

	void SetIniFile(CString iniFileName);
	CIniFile();	//Ĭ�Ϲ��캯��
	CIniFile(CString iniFileName);

	void checkIniFile();
    CString GetAppPath();  //�õ�Ӧ�ó���װ·��
	BOOL FileExist(LPCTSTR szFindPath); //�ļ��Ƿ����
protected:
	BOOL isNumber(CString str);
	INT StrToInt(CString str);
	CString IntToStr(INT n);
	LONG StrToLong(CString str);
	CString LongToStr(LONG n);
	DOUBLE StrToDouble(CString str);
	CString DoubleToStr(DOUBLE d,INT decimal=3);

	CString OleDateTimeToStr(COleDateTime dt,BOOL bHasTime = TRUE);
	COleDateTime StrToOleDateTime(CString str);

    CString TimeToStr(CTime time,BOOL bHasTime = TRUE);
	CTime StrToTime(CString str);

    BOOL ShowOpenFileDialog(CString &filePathName, CString DefPath = "", CString Filter = "�����ļ�(*.*)|*.*|", CString Title = "���ļ�");
	BOOL ShowSaveFileDialog(CString &filePathName, CString DefPath = "", CString Filter = "�����ļ�(*.*)|*.*|", CString Title = "�����ļ�");



private:
	CString m_iniFileName;
	BOOL  m_bCheck;
};

#endif