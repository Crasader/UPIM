/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��RegKey.cpp
* �汾��  ��V1.0
* ��Ŀ���ƣ�
* ��Ȩ������Copyright 2002-2003 LuoWei. All Rights Reserved.
* ģ��������� ��дע�����ģ���ļ�
*======================================================
* �汾�����¼:
*     
*
* 
*/

/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../include/RegKey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


LPBYTE CString_To_LPBYTE(CString str)
{
	LPBYTE lpb=new BYTE[str.GetLength()+1];
	for(int i=0;i<str.GetLength();i++)
		lpb[i]=str[i];
	lpb[str.GetLength()]=0;
	return lpb;
}

CRegKey::CRegKey()
{

}

CRegKey::~CRegKey()
{

}

//�½�����дָ���ļ�ֵ
BOOL CRegKey::WriteRegValue(UINT mainKeyName, CString SubKeyName,  CString ValueName, CString value)
{
  return WriteRegValue(GetKeyName(mainKeyName), SubKeyName, ValueName, value);
}

BOOL CRegKey::WriteRegValue(UINT mainKeyName, CString SubKeyName,  CString ValueName, DOUBLE value)
{
  return WriteRegValue(GetKeyName(mainKeyName), SubKeyName, ValueName, value);
}
BOOL CRegKey::WriteRegValue(UINT mainKeyName, CString SubKeyName,  CString ValueName, LONG value)
{
  return WriteRegValue(GetKeyName(mainKeyName), SubKeyName, ValueName, value);
}
BOOL CRegKey::WriteRegValue(UINT mainKeyName, CString SubKeyName,  CString ValueName, INT value)
{
  return WriteRegValue(GetKeyName(mainKeyName), SubKeyName, ValueName, value);
}


/*
BOOL CRegKey::WriteRegValue(HKEY mainKeyName,  CString SubKeyName, CString ValueName, BOOL value)
{ 

	CString str;
	if(value)
		str = "1";
	else
		str = "0";
    return  WriteRegValue(mainKeyName, SubKeyName,  ValueName, str);
}
*/

BOOL CRegKey::WriteRegValue(HKEY mainKeyName,  CString SubKeyName, CString ValueName, INT value)
{ 
	CString str = "0";
	str.Format("%d",value);
    return  WriteRegValue(mainKeyName, SubKeyName,  ValueName, str);
}

BOOL CRegKey::WriteRegValue(HKEY mainKeyName,  CString SubKeyName, CString ValueName, DOUBLE value)
{     	
	CString str = "0.00";
	str.Format("%f",value);
    return  WriteRegValue(mainKeyName, SubKeyName,  ValueName, str);
}

BOOL CRegKey::WriteRegValue(HKEY mainKeyName,  CString SubKeyName, CString ValueName, LONG value)
{ 
	CString str = "0";
	str.Format("%ld",value);
    return  WriteRegValue(mainKeyName, SubKeyName,  ValueName, str);
}

BOOL CRegKey::WriteRegValue(HKEY mainKeyName, CString SubKeyName,  CString ValueName, CString value)
{ 

	   HKEY hKEY;//�����йص�hKEY,�ڲ�ѯ����ʱҪ�ر�

	  //����·�� pKeyName��ص�hKEY
	  LPCTSTR pKeyName = SubKeyName;

	//����ע���hKEY�򱣴�˺������򿪵ļ��ľ��
	long ret0=(::RegOpenKeyEx(mainKeyName,pKeyName,0,KEY_WRITE,&hKEY));


	if(ret0!=ERROR_SUCCESS)//����޷���hKEY,����ֹ�����ִ��
	{
		TRACE0("�����޷����йص�hKEY");
		return FALSE;
	}

	//�����йص�����
	LPBYTE ValueStr = CString_To_LPBYTE(value);  //Ҫд���ַ���ֵ

    //��������:��������϶�Ϊ�ַ�������
// unsigned long type = REG_SZ;

	unsigned long strLen = value.GetLength() + 1;//�������ݳ���


	long ret1=::RegSetValueEx(hKEY, ValueName, NULL, REG_SZ, ValueStr, strLen);

	if(ret1!=ERROR_SUCCESS)
	{
		TRACE0("�����޷������йص�ע�����Ϣ");
		return FALSE;
	}

	::RegCloseKey(hKEY);

	if(ValueStr)
        delete ValueStr;    //@@@@@@@@@��һ�����Լӵ�,��Ϊ�������ص�ֵ��NEW�ģ���Ҫ�ͷ�,������ڴ�й©

    return TRUE;
}



BOOL CRegKey::ReadRegValue(HKEY mainKeyName, CString SubKeyName, CString ValueName, CString &value)
{
	HKEY hKEY;//�����йص�hKEY,�ڲ�ѯ����ʱҪ�ر�

	//����·�� data_Set��ص�hKEY
	LPCTSTR data_Set = SubKeyName;
	//����ע���hKEY�򱣴�˺������򿪵ļ��ľ��
	long ret0=(::RegOpenKeyEx(mainKeyName,data_Set,0,KEY_READ,&hKEY));
	if(ret0!=ERROR_SUCCESS)//����޷���hKEY,����ֹ�����ִ��
	{
		TRACE0("�����޷����йص�hKEY\n");
		return FALSE;
	}

	//��ѯ�йص�����
	LPBYTE pValue = new BYTE[1028];  //����õ�ֵ��ָ��
	unsigned long Vtype = REG_SZ;            //������������
	unsigned long strLen = 1028;               //�������ݳ���

	long ret1=::RegQueryValueEx(hKEY, ValueName, NULL, &Vtype, pValue, &strLen);
	if(ret1!=ERROR_SUCCESS)
	{
		TRACE0("�����޷���ѯ�йص�ע�����Ϣ\n");
		return FALSE;
	}

	//��ʾ��Ϣ
	value = CString(pValue);
	delete[] pValue;

	//����������رմ򿪵�hKEY
	::RegCloseKey(hKEY);

    return TRUE;
}



BOOL CRegKey::ReadRegValue(HKEY mainKeyName, CString SubKeyName, CString ValueName, DOUBLE &value)
{  
	CString str;
	ReadRegValue(mainKeyName, SubKeyName, ValueName, str);
    try{ value = atof(str);}
	catch(...)
	{value = 0.00;}
    return TRUE;
}

BOOL CRegKey::ReadRegValue(HKEY mainKeyName, CString SubKeyName, CString ValueName, LONG &value)
{
 	CString str;
	ReadRegValue(mainKeyName, SubKeyName, ValueName, str);
    try{ value = atol(str);}
	catch(...)
	{value = 0;}
    return TRUE;
}

BOOL CRegKey::ReadRegValue(HKEY mainKeyName, CString SubKeyName, CString ValueName, INT &value)
{  
  	CString str;
	ReadRegValue(mainKeyName, SubKeyName, ValueName, str);
    try{ value = atoi(str);}
	catch(...)
	{value = 0;}
    return TRUE;

}



BOOL CRegKey::ReadRegValue(UINT mainKeyName, CString SubKeyName, CString ValueName, CString &value)
{
  return ReadRegValue(GetKeyName(mainKeyName), SubKeyName, ValueName, value);
}
BOOL CRegKey::ReadRegValue(UINT mainKeyName, CString SubKeyName, CString ValueName, DOUBLE &value)
{
  return ReadRegValue(GetKeyName(mainKeyName), SubKeyName, ValueName, value);
}
BOOL CRegKey::ReadRegValue(UINT mainKeyName, CString SubKeyName, CString ValueName, LONG &value)
{
  return ReadRegValue(GetKeyName(mainKeyName), SubKeyName, ValueName, value);
}
BOOL CRegKey::ReadRegValue(UINT mainKeyName, CString SubKeyName, CString ValueName, INT &value)
{
  return ReadRegValue(GetKeyName(mainKeyName), SubKeyName, ValueName, value);
}








HKEY CRegKey::GetKeyName(UINT mainKeyName)
{
     HKEY mainKEY;//�����йص�hKEY,�ڲ�ѯ����ʱҪ�ر�
	switch(mainKeyName)
	{
	case _HKEY_CLASSES_BOOT:
        mainKEY = HKEY_CLASSES_ROOT;
		break;
	case _HKEY_CURRENT_USER:
        mainKEY =HKEY_CURRENT_USER;
		break;

	case _HKEY_LOCAL_MACHINE:
        mainKEY =HKEY_LOCAL_MACHINE;
		break;

	case _HKEY_USERS:
        mainKEY = HKEY_USERS;
		break;

	case _HKEY_CURRENT_CONFIG:
        mainKEY = HKEY_CURRENT_CONFIG;
		break;

	case _HKEY_DYN_DATA:
        mainKEY = HKEY_DYN_DATA;
		break;
    default:
       mainKEY =NULL;

	}
	return mainKEY;
}
