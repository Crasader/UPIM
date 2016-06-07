/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��RegKey.h
* �汾��  ��V1.0
* ��Ŀ���ƣ�
* ��Ȩ������Copyright 2002-2003 LuoWei. All Rights Reserved.
* ģ��������� ��дע�����ͷ�ļ�
*======================================================
* �汾�����¼:
*     
*
* 
*/

/////////////////////////////////////////////////////////////////////////////



#if !defined(_AFX_REGKEY_H_)
#define _AFX_REGKEY_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
#if !defined _WINDEF_
   #include <WinDef.h>
#endif
*/

#if !defined _WINREG_
   #include <WinReg.h>
#endif
/*����ĺ���winreg.h���Ѷ���
#define HKEY_CLASSES_ROOT           (( HKEY ) 0x80000000 )
#define HKEY_CURRENT_USER           (( HKEY ) 0x80000001 )
#define HKEY_LOCAL_MACHINE          (( HKEY ) 0x80000002 )
#define HKEY_USERS                  (( HKEY ) 0x80000003 )
#define HKEY_PERFORMANCE_DATA       (( HKEY ) 0x80000004 )
#if(WINVER >= 0x0400)
#define HKEY_CURRENT_CONFIG         (( HKEY ) 0x80000005 )
#define HKEY_DYN_DATA               (( HKEY ) 0x80000006 )
*/

//******************************************************************
#if !defined _WINNT_
   #include <winnt.h>
#endif
/*����ĺ���winnt.h���Ѷ���
#define REG_NONE                    ( 0 )   // No value type
#define REG_SZ                      ( 1 )   // Unicode nul terminated string
#define REG_EXPAND_SZ               ( 2 )   // Unicode nul terminated string
                                            // (with environment variable references)
#define REG_BINARY                  ( 3 )   // Free form binary
#define REG_DWORD                   ( 4 )   // 32-bit number
#define REG_DWORD_LITTLE_ENDIAN     ( 4 )   // 32-bit number (same as REG_DWORD)
#define REG_DWORD_BIG_ENDIAN        ( 5 )   // 32-bit number
#define REG_LINK                    ( 6 )   // Symbolic Link (unicode)
#define REG_MULTI_SZ                ( 7 )   // Multiple Unicode strings
#define REG_RESOURCE_LIST           ( 8 )   // Resource list in the resource map
#define REG_FULL_RESOURCE_DESCRIPTOR ( 9 )  // Resource list in the hardware description
#define REG_RESOURCE_REQUIREMENTS_LIST ( 10 )
*/
/////////////////////////////////////////////////////////////////////////////


// ���¼��������Ѿ���ϵͳ�ļ�<WINREG.H>�ж�����
//�����ض���ö��:�������Ա�ʹ��(��ǰ�����һ�»���)
	typedef enum KEYNAME
	{
		_HKEY_CLASSES_BOOT = 0,
		_HKEY_CURRENT_USER,
		_HKEY_LOCAL_MACHINE,
		_HKEY_USERS,
		_HKEY_CURRENT_CONFIG,
		_HKEY_DYN_DATA
	};


//��дע������
class CRegKey
{

  public:
	CRegKey();	
   ~CRegKey();

 
  private:


  protected:
    DWORD m_szStrLen;   //�ַ�������ֵ����(һ��ΪCString.GetLength()+1) ,���ڶ�ע�����
	HKEY GetKeyName(UINT mainKeyName);
  public:

	  BOOL ReadRegValue(UINT mainKeyName, CString SubKeyName, CString ValueName, CString &value);
	  BOOL ReadRegValue(UINT mainKeyName, CString SubKeyName, CString ValueName, DOUBLE &value);
	  BOOL ReadRegValue(UINT mainKeyName, CString SubKeyName, CString ValueName, LONG &value);
	  BOOL ReadRegValue(UINT mainKeyName, CString SubKeyName, CString ValueName, INT &value);

	  BOOL ReadRegValue(HKEY mainKeyName, CString SubKeyName, CString ValueName, INT &value);
	  BOOL ReadRegValue(HKEY mainKeyName, CString SubKeyName, CString ValueName, LONG &value);
	  BOOL ReadRegValue(HKEY mainKeyName, CString SubKeyName, CString ValueName, DOUBLE &value);
	  BOOL ReadRegValue(HKEY mainKeyName,  CString SubKeyName, CString ValueName, CString &value);

	  BOOL WriteRegValue(HKEY mainKeyName, CString SubKeyName,  CString ValueName, CString value);
	  BOOL WriteRegValue(HKEY mainKeyName,  CString SubKeyName, CString VlaueName, LONG value);
	  BOOL WriteRegValue(HKEY mainKeyName,  CString SubKeyName, CString VlaueName, DOUBLE value);
	  BOOL WriteRegValue(HKEY mainKeyName,  CString SubKeyName, CString VlaueName, INT value);

	  BOOL WriteRegValue(UINT mainKeyName,  CString SubKeyName, CString VlaueName, CString value);
	  BOOL WriteRegValue(UINT mainKeyName,  CString SubKeyName, CString VlaueName, INT value);
	  BOOL WriteRegValue(UINT mainKeyName,  CString SubKeyName, CString VlaueName, DOUBLE value);
	  BOOL WriteRegValue(UINT mainKeyName,  CString SubKeyName, CString VlaueName, LONG value);





};

#endif