/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��IniFile.cpp
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
#include "stdAfx.h"
#include "..\include\IniFile.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////
// ����/����
/////////////////////////////////////////////////////////////////////
CIniFile::CIniFile()
{
   m_bCheck = FALSE;
}
CIniFile::CIniFile(CString iniFileName)
{
   m_iniFileName = iniFileName;
}

void CIniFile::SetIniFile(CString iniFileName)
{
    m_iniFileName = iniFileName;
}


///////////////////////////////////////////////////////////////////////////////////
//�ж�ָ���ַ����Ƿ�����������
BOOL CIniFile::isNumber(CString str)
{
	BOOL bIsNumber = TRUE;
   INT count = str.GetLength();
   CString ch;
   for(INT i = 0; i < count; i++)
   {
        ch = str.Mid(i,1);
		if(ch!="0" && ch!="1" && ch!="2" && ch!="3" && ch!="4" && ch!="5" &&
			ch!="5" && ch!="6" && ch!="7" && ch!="8" && ch!="9" && ch!="." && ch!="-")
		{
			bIsNumber = FALSE;
			break;
		}
   }
   return bIsNumber;
}

//����ת������
INT CIniFile::StrToInt(CString str)
{
   if(isNumber(str))
	   return atoi(str);
   else
   {
	   TRACE("�������֣��޷�ת��\n");
	   return NULL;
   }

}
CString CIniFile::IntToStr(INT n)
{
   CString str;
   str.Format("%d",n);
   return str;

}
LONG CIniFile::StrToLong(CString str)
{
   if(isNumber(str))
	   return atol(str);
   else
   {
	   TRACE("�������֣��޷�ת��\n");
	   return NULL;
   }
}
CString CIniFile::LongToStr(LONG n)
{
   CString str;
   str.Format("%ld",n);
   return str;

}
DOUBLE CIniFile::StrToDouble(CString str)
{
   if(isNumber(str))
	   return atof(str);
   else
   {
	   TRACE("�������֣��޷�ת��\n");
	   return NULL;
   }
}
CString CIniFile::DoubleToStr(DOUBLE d,INT decimal/*=3*/)
{
   CString temp;
   CString str;
   temp.Format("%%3.%df",decimal); 
   str.Format(temp,d);
   return str;

}

// ��������תΪ�ַ���
CString CIniFile::TimeToStr(CTime time,BOOL bHasTime /*= TRUE*/)
{
   	CString sDateTime;
	if(time.GetYear() <= 0 ||time.GetMonth() <= 0)
		return "";

	CString syear,smonth,sday,shour,sminute,ssecond;
	INT year = time.GetYear();      syear.Format("%d",year);
	INT month = time.GetMonth();    smonth.Format("%d",month);
	INT day = time.GetDay();        sday.Format("%d",day);
	INT hour = time.GetHour();      shour.Format("%d",hour);
    INT minute = time.GetMinute();  sminute.Format("%d",minute);
    INT second = time.GetSecond();  ssecond.Format("%d",second);

	//������
    if(syear.GetLength() == 2)
	{
         if(year <= 99 && year >= 50)
			 syear = "19" + syear;
		 else
			 syear = "20" + syear;
	}

	//������
    if(smonth.GetLength() == 1)
	{
		smonth = "0" + smonth;
	}

	//������
    if(sday.GetLength() == 1)
	{
		sday = "0" + sday;
	}

	//����Сʱ
    if(shour.GetLength() == 1)
	{
		shour= "0" + shour;
	}

	//�����
    if(sminute.GetLength() == 1)
	{
		sminute= "0" + sminute;
	}
	//������
    if(ssecond.GetLength() == 1)
	{
		ssecond= "0" + ssecond;
	}
	else if(ssecond.GetLength() > 2)
	{
	    ssecond = ssecond.Left(2);
	}


	if(bHasTime)
	    sDateTime.Format("%s-%s-%s %s:%s:%s",syear,smonth,sday,shour,sminute,ssecond);
	else
	    sDateTime.Format("%s-%s-%s",syear,smonth,sday);
/*
	if(bHasTime)
      sDateTime  = time.Format("%Y-%B-%d %H:%M:%S");
	else
      sDateTime  = time.Format("%Y-%B-%d");
*/
	return sDateTime;
}
//�ַ�������תΪ���ڣ��ַ������ͱ�����:dddd-mm-dd hh:mm:ss��
//                                     0123-56-89 1112:1415:1718 
CTime CIniFile::StrToTime(CString str)
{
   CTime time;
   CString syear,smonth,sday,shour,sminute,ssecond,sTime;
   INT year,month,day,hour,minute,second;
   if(str.GetLength() == 19)
   {
     syear = str.Mid(0,4);  year = StrToInt(syear);
	 smonth = str.Mid(5,2); month = StrToInt(smonth);
	 sday = str.Mid(8,2);   day = StrToInt(sday);
	 shour = str.Mid(11,2); hour = StrToInt(shour);
	 sminute = str.Mid(14,2); minute =StrToInt(sminute);
	 ssecond = str.Mid(17,2); second = StrToInt(ssecond);
	 sTime.Format("%d-%d-%d %d:%d:%d",year,month,day,hour,minute,second);
	 time.Format(sTime);
   }
    return time;
}

// ��������תΪ�ַ���
CString CIniFile::OleDateTimeToStr(COleDateTime time,BOOL bHasTime /*= TRUE*/)
{
   	CString sDateTime;
	if(time.GetYear() <= 0 ||time.GetMonth() <= 0)
		return "";

	CString syear,smonth,sday,shour,sminute,ssecond;
	INT year = time.GetYear();      syear.Format("%d",year);
	INT month = time.GetMonth();    smonth.Format("%d",month);
	INT day = time.GetDay();        sday.Format("%d",day);
	INT hour = time.GetHour();      shour.Format("%d",hour);
    INT minute = time.GetMinute();  sminute.Format("%d",minute);
    INT second = time.GetSecond();  ssecond.Format("%d",second);

	//������
    if(syear.GetLength() == 2)
	{
         if(year <= 99 && year >= 50)
			 syear = "19" + syear;
		 else
			 syear = "20" + syear;
	}

	//������
    if(smonth.GetLength() == 1)
	{
		smonth = "0" + smonth;
	}

	//������
    if(sday.GetLength() == 1)
	{
		sday = "0" + sday;
	}

	//����Сʱ
    if(shour.GetLength() == 1)
	{
		shour= "0" + shour;
	}

	//�����
    if(sminute.GetLength() == 1)
	{
		sminute= "0" + sminute;
	}
	//������
    if(ssecond.GetLength() == 1)
	{
		ssecond= "0" + ssecond;
	}
	else if(ssecond.GetLength() > 2)
	{
	    ssecond = ssecond.Left(2);
	}


	if(bHasTime)
	    sDateTime.Format("%s-%s-%s %s:%s:%s",syear,smonth,sday,shour,sminute,ssecond);
	else
	    sDateTime.Format("%s-%s-%s",syear,smonth,sday);
/*
	if(bHasTime)
      sDateTime  = time.Format("%Y-%B-%d %H:%M:%S");
	else
      sDateTime  = time.Format("%Y-%B-%d");
*/
	return sDateTime;
}
//�ַ�������תΪ���ڣ��ַ������ͱ�����:dddd-mm-dd hh:mm:ss��
//                                     0123-56-89 1112:1415:1718 
COleDateTime CIniFile::StrToOleDateTime(CString str)
{
   COleDateTime time;
   CString syear,smonth,sday,shour,sminute,ssecond;
   INT year,month,day,hour,minute,second;
   if(str.GetLength() == 19)
   {
     syear = str.Mid(0,4);  year = StrToInt(syear);
	 smonth = str.Mid(5,2); month = StrToInt(smonth);
	 sday = str.Mid(8,2);   day = StrToInt(sday);
	 shour = str.Mid(11,2); hour = StrToInt(shour);
	 sminute = str.Mid(14,2); minute =StrToInt(sminute);
	 ssecond = str.Mid(17,2); second = StrToInt(ssecond);
	 time.SetDateTime(year,month,day,hour,minute,second);
   }
    return time;
}

 //�õ�Ӧ�ó���װ·��
CString CIniFile::GetAppPath()
{ 
	CString appPath;
	//�õ�Ӧ�ó���·��
    HINSTANCE hInst = AfxGetInstanceHandle();
    TCHAR szMyPath[_MAX_PATH];
    //ȡ��Ӧ�ó����ȫ��·���ļ�����
    ::GetModuleFileName(hInst, szMyPath, _MAX_PATH);
    appPath = CString(szMyPath);
    //ȥ��ģ����ļ���
    int nPos = appPath.ReverseFind(_T('\\'));
    //���Ӧ�ó�������Ŀ¼���磺��C:\Report��
     appPath = appPath.Left(nPos);

	 return appPath;
} 


//ָ���ļ��Ƿ����
BOOL CIniFile::FileExist(LPCTSTR szFindPath)
{
	int count = 0;
	int i = 0;
	WIN32_FIND_DATA fd;
	HANDLE hFind;
	 if(strlen((char *)szFindPath) <= 0 )
		 return TRUE;
	char path[257];
    char *pPath;
    pPath = path;
    count = strlen(szFindPath);
	if(count <=0)
		return FALSE;
    

	//��ǰ���õ�·���ַ���
	for( i = 0; i<count; i++)
	{
        if(*(szFindPath+i) == '\\')
			break;
		*(pPath+i) = *(szFindPath+i);
	}

   *(pPath+i) = '\\';
   *(pPath+i+1) = '\0';
    hFind = FindFirstFile(szFindPath, &fd );

	if ( hFind != INVALID_HANDLE_VALUE )
	{
		FindClose( hFind );
	}

	return hFind != INVALID_HANDLE_VALUE;
}


//�����ļ��Ի��򣬷����ļ�ȫ�����ļ�����Ŀ¼��
BOOL CIniFile::ShowSaveFileDialog(CString &filePathName, CString DefPath /*= ""*/, CString Filter /*= "�����ļ�(*.*)|*.*|"*/, CString Title /*= "�����ļ�"*/)
{

    CFileDialog opendlg(FALSE, NULL, DefPath, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, Filter, NULL);
    if(DefPath.IsEmpty())
	{
		DefPath = GetAppPath();
		DefPath += "\\*.ini";
	}

	    INT id = opendlg.DoModal();
		if(id == IDOK)
		{
			filePathName = opendlg.GetPathName();
			return TRUE;
		}
		else
		{
			return FALSE;
		}

		return TRUE;
}

//�򿪶Ի��򣬷����ļ�ȫ�����ļ�����Ŀ¼��
BOOL CIniFile::ShowOpenFileDialog(CString &filePathName, CString DefPath /*= ""*/, CString Filter /*= "�����ļ�(*.*)|*.*|"*/, CString Title /*= "���ļ�"*/)
{

    CFileDialog opendlg(TRUE, NULL, DefPath, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, Filter, NULL);
    if(DefPath.IsEmpty())
	{
		DefPath = GetAppPath();
		DefPath += "\\*.*";
	}

	    INT id = opendlg.DoModal();
		if(id == IDOK)
		{
			filePathName = opendlg.GetPathName();
		}
		else
		{
			return FALSE;
		}

		return TRUE;
}











////////////////////////////////////////////////////////////////////////////////////////

BOOL CIniFile::ReadIni(CString SectionTxt, CString ItemTxt, CString &strValue)
{
	char inBuf[1028];
    BOOL b =	GetPrivateProfileString(SectionTxt,ItemTxt, NULL, inBuf, 1028, m_iniFileName); 
	strValue.Format("%s",inBuf);
//	strValue=inBuf;
	return b;
}

BOOL CIniFile::ReadIni(CString SectionTxt, CString ItemTxt, INT &intValue)
{
	CString strValue;
    BOOL b = ReadIni(SectionTxt,ItemTxt, strValue);
	intValue = StrToInt(strValue);
	return b;
}

BOOL CIniFile::ReadIni(CString SectionTxt, CString ItemTxt, DOUBLE &doubleValue)
{
	CString strValue;
    BOOL b = ReadIni(SectionTxt, ItemTxt, strValue);
	doubleValue = StrToDouble(strValue);
	return b;
}

BOOL CIniFile::ReadIni(CString SectionTxt, CString ItemTxt, LONG &longValue)
{
  	CString strValue;
    BOOL b = ReadIni(SectionTxt, ItemTxt, strValue);
	longValue = StrToLong(strValue);
	return b;
}

BOOL CIniFile::ReadIni(CString SectionTxt, CString ItemTxt, COLORREF &colValue)
{
  	CString strValue;
    BOOL b = ReadIni(SectionTxt, ItemTxt, strValue);
	colValue = (COLORREF)StrToLong(strValue);
	return b;
}

BOOL CIniFile::ReadIni(CString SectionTxt, CString ItemTxt, COleDateTime &dateValue)
{
  	CString strValue;
    BOOL b = ReadIni(SectionTxt, ItemTxt, strValue);
	dateValue = StrToOleDateTime(strValue);
	return b;
}


BOOL CIniFile::WriteIni(CString SectionTxt, CString ItemTxt, CString strValue)
{
	checkIniFile();
	BOOL b = WritePrivateProfileString(SectionTxt,ItemTxt, strValue, m_iniFileName); 
	return b;
}

BOOL CIniFile::WriteIni(CString SectionTxt, CString ItemTxt, INT intValue)
{
	checkIniFile();
	CString strValue = IntToStr(intValue);
	BOOL b = WritePrivateProfileString(SectionTxt,ItemTxt, strValue, m_iniFileName); 
	return b;
}

BOOL CIniFile::WriteIni(CString SectionTxt, CString ItemTxt, DOUBLE doubleValue,INT dec/*=3*/)
{
	checkIniFile();
	CString strValue = DoubleToStr(doubleValue,dec);
	BOOL b = WritePrivateProfileString(SectionTxt,ItemTxt, strValue, m_iniFileName); 
	return b;
}

BOOL CIniFile::WriteIni(CString SectionTxt, CString ItemTxt, LONG longValue)
{
	checkIniFile();
	CString strValue = LongToStr(longValue);
	BOOL b = WritePrivateProfileString(SectionTxt,ItemTxt, strValue, m_iniFileName); 
	return b;
}


BOOL CIniFile::WriteIni(CString SectionTxt, CString ItemTxt, COLORREF colValue)
{
	checkIniFile();
	CString strValue = LongToStr(LONG(colValue));
	BOOL b = WritePrivateProfileString(SectionTxt,ItemTxt, strValue, m_iniFileName); 
	return b;
}

BOOL CIniFile::WriteIni(CString SectionTxt, CString ItemTxt, COleDateTime dateValue)
{
	checkIniFile();
	CString strValue = OleDateTimeToStr(dateValue);
	BOOL b = WritePrivateProfileString(SectionTxt,ItemTxt, strValue, m_iniFileName); 
	return b;
}



//����INI�ļ��Ƿ����,���������Ƿ�Ҫ����һ�µĿյ�INI�ļ�
void CIniFile::checkIniFile()
{
	if(m_bCheck)
		return;
    if(!FileExist(m_iniFileName)) 
	{
		CString s;
		s.Format("ϵͳ�����ļ�:'%s'û�б�����!",m_iniFileName);
        AfxMessageBox(s,MB_OKCANCEL|MB_ICONQUESTION);
		m_bCheck = TRUE;
	}
}
		