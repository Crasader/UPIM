//////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��shockwaveflash.cpp
* �汾��  ��V1.0
* ��Ŀ���ƣ�CPH
* ��Ȩ������Copyright 2002-2003 . All Rights Reserved.
* ģ�������������Splash�ؼ�����ʾSplash�����ļ���ģ���ļ�(��CSplashWnd���е���)
*======================================================
* �汾�����¼:
*      v1.0  2002-11-24   9��00  
*
* 
*/
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\\INCLUDE\\shockwaveflash.h"

/////////////////////////////////////////////////////////////////////////////
// CShockwaveFlash

IMPLEMENT_DYNCREATE(CShockwaveFlash, CWnd)

/////////////////////////////////////////////////////////////////////////////
/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetReadyState()
*  ��������     :�õ�Flash׼��״̬
*  �����������	:
*  ���ر���˵�� :״ֵ̬
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
long CShockwaveFlash::GetReadyState()
{
	long result;
	InvokeHelper(DISPID_READYSTATE, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetTotalFrames()
*  ��������     :�õ�Ҫ���ŵ�
*  �����������	:
*  ���ر���˵�� :Flash����֡��
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
long CShockwaveFlash::GetTotalFrames()
{
	long result;
	InvokeHelper(0x7c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetPlaying()
*  ��������     :�õ��Ƿ����ڲ���Flash��״̬
*  �����������	:
*  ���ر���˵�� :����TRUE��ʾ��ǰ���ڲ���Flash
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
BOOL CShockwaveFlash::GetPlaying()
{
	BOOL result;
	InvokeHelper(0x7d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetPlaying
*  ��������     :�����Ƿ�Ҫ����Flash
*  �����������	:
*    BOOL bNewValue:��ΪTRUE��ʾ���ڲ���Flash����ΪFALSE��ʾ������Flash
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::SetPlaying(BOOL bNewValue)
{
	static BYTE parms[] = VTS_BOOL;
	InvokeHelper(0x7d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetQuality()
*  ��������     :�õ�����Flash�Ĳ�������ֵ
*  �����������	:
*  ���ر���˵�� :Flash�Ĳ�������ֵ
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
long CShockwaveFlash::GetQuality()
{
	long result;
	InvokeHelper(0x69, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetQuality
*  ��������     :���ò���Flash�Ĳ�������ֵ
*  �����������	:
*  long nNewValue�� Flash�Ĳ�������ֵ
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::SetQuality(long nNewValue)
{
	static BYTE parms[] = VTS_I4;
	InvokeHelper(0x69, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetScaleMode()
*  ��������     :�õ���ʾFlash�����ı���ģʽ
*  �����������	:
*  ���ر���˵�� :Flash�����ı���ģʽֵ
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
long CShockwaveFlash::GetScaleMode()
{
	long result;
	InvokeHelper(0x78, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetScaleMode
*  ��������     :������ʾFlash�����ı���ģʽ
*  �����������	:
*   long nNewValue�� Flash�����ı���ģʽֵ
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::SetScaleMode(long nNewValue)
{
	static BYTE parms[] = VTS_I4;
	InvokeHelper(0x78, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetAlignMode()
*  ��������     :�õ���ʾFlash�����Ķ���ģʽ
*  �����������	:
*  ���ر���˵�� :��ʾFlash�����Ķ���ģʽֵ
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
long CShockwaveFlash::GetAlignMode()
{
	long result;
	InvokeHelper(0x79, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetAlignMode
*  ��������     :������ʾFlash�����Ķ���ģʽ
*  �����������	:
*   long nNewValue����ʾFlash�����Ķ���ģʽֵ
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::SetAlignMode(long nNewValue)
{
	static BYTE parms[] = VTS_I4;
	InvokeHelper(0x79, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetBackgroundColor()
*  ��������     :�õ�����Flash����ʱ�ı���ɫ
*  �����������	:
*  ���ر���˵�� :����Flash����ʱ�ı���ɫֵ
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
long CShockwaveFlash::GetBackgroundColor()
{
	long result;
	InvokeHelper(0x7b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetBackgroundColor
*  ��������     :���ò���Flash����ʱ�ı���ɫ
*  �����������	:
*    long nNewValue:����Flash����ʱ�ı���ɫֵ
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::SetBackgroundColor(long nNewValue)
{
	static BYTE parms[] = VTS_I4;
	InvokeHelper(0x7b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetLoop()
*  ��������     :�õ���ǰ���ŵ�Flash�����Ƿ�ѭ������
*  �����������	:
*  ���ر���˵�� :����TRUE��ʾ��ǰѭ�����ţ�����FALSE��ʾ��ѭ������
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
BOOL CShockwaveFlash::GetLoop()
{
	BOOL result;
	InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetLoop
*  ��������     :���õ�ǰ���ŵ�Flash�����Ƿ�ѭ������
*  �����������	:
*     BOOL bNewValue:��ΪTRUE��ʾ��ǰѭ�����ţ���ΪFALSE��ʾ��ѭ������
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::SetLoop(BOOL bNewValue)
{
	static BYTE parms[] = VTS_BOOL;
	InvokeHelper(0x6a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetMovie()
*  ��������     :�õ����ŵ�Flash���ļ�����
*  �����������	:
*  ���ر���˵�� :��ǰ���ŵ�Flash���ļ�����
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
CString CShockwaveFlash::GetMovie()
{
	CString result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetMovie
*  ��������     :���ò��ŵ�Flash���ļ�����
*  �����������	:
*   LPCTSTR lpszNewValue:��ǰҪ���ŵ�Flash���ļ�����
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::SetMovie(LPCTSTR lpszNewValue)
{
	static BYTE parms[] = VTS_BSTR;
	InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetFrameNum()
*  ��������     :�õ���ǰ���ŵ�Flash���������
*  �����������	:
*  ���ر���˵�� :��ǰ���ŵ�Flash���������
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
long CShockwaveFlash::GetFrameNum()
{
	long result;
	InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetFrameNum
*  ��������     :���õ�ǰ���ŵ�Flash���������
*  �����������	:
*   Ҫ���õ�ǰ���ŵ�Flash���������
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::SetFrameNum(long nNewValue)
{
	static BYTE parms[] = VTS_I4;
	InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetZoomRect
*  ��������     :���õ�ǰ���ŵ�Flash��������������
*  �����������	:
*	long left����������
*	long top����������
*	long right����������
*	long bottom����������
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::SetZoomRect(long left, long top, long right, long bottom)
{
	static BYTE parms[] =		VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x6d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 left, top, right, bottom);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :Zoom
*  ��������     :ִ������
*  �����������	:
*   long factor �����ű���ֵ
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::Zoom(long factor)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x76, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 factor);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :Pan
*  ��������     :�ƶ���
*  �����������	:
*	long x ���ƶ���X����
*	long y���ƶ���Y����
*	long mode���ƶ�ģʽ
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::Pan(long x, long y, long mode)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x77, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 x, y, mode);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :Play()
*  ��������     :����Flash����
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::Play()
{
	InvokeHelper(0x70, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :Stop()
*  ��������     :��ͣ����Flash����
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::Stop()
{
	InvokeHelper(0x71, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :Back()
*  ��������     :���󲥷�Flash����
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::Back()
{
	InvokeHelper(0x72, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :Forward()
*  ��������     :��ǰ����Flash����
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::Forward()
{
	InvokeHelper(0x73, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :Rewind()
*  ��������     :���´ӿ�ͷ����Flash����
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::Rewind()
{
	InvokeHelper(0x74, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :StopPlay()
*  ��������     :ֹͣ����Flash����
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::StopPlay()
{
	InvokeHelper(0x7e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GotoFrame
*  ��������     :��ָ��������Flash����
*  �����������	:
*   long FrameNum��ָ�����������
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::GotoFrame(long FrameNum)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FrameNum);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :CurrentFrame()
*  ��������     :�õ���ǰ�����ŵ�Flash�������������
*  �����������	:
*  ���ر���˵�� :ǰ�����ŵ�Flash�������������
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
long CShockwaveFlash::CurrentFrame()
{
	long result;
	InvokeHelper(0x80, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :IsPlaying()
*  ��������     :�ж��Ƿ����ڲ���Flash����
*  �����������	:
*  ���ر���˵�� :����TRUE��ʾ���ڲ���Flash�����������ʾ��ǰû�в���
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
BOOL CShockwaveFlash::IsPlaying()
{
	BOOL result;
	InvokeHelper(0x81, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :PercentLoaded()
*  ��������     :�õ���ǰ����Flash�����Ľ��ȵİٷֱ�
*  �����������	:
*  ���ر���˵�� :��ǰ����Flash�����Ľ��ȵİٷֱ�
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
long CShockwaveFlash::PercentLoaded()
{
	long result;
	InvokeHelper(0x82, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :FrameLoaded
*  ��������     :����Ҫ�������Flash����������
*  �����������	:
*     long FrameNum��Ҫ�������Flash����������
*  ���ر���˵�� :
*   ����TRUE��ʾ���óɹ�������FALSE��ʾʧ��
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
BOOL CShockwaveFlash::FrameLoaded(long FrameNum)
{
	BOOL result;
	static BYTE parms[] = VTS_I4;
	InvokeHelper(0x83, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		FrameNum);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :FlashVersion()
*  ��������     :�õ���ǰʹ�õ�Flash���ſؼ��İ汾��
*  �����������	:
*  ���ر���˵�� :Flash���ſؼ��İ汾��
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
long CShockwaveFlash::FlashVersion()
{
	long result;
	InvokeHelper(0x84, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetWMode()
*  ��������     :�õ���ǰѡ�õĲ���ģʽ
*  �����������	:
*  ���ر���˵�� :
*     ����ģʽ����
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
CString CShockwaveFlash::GetWMode()
{
	CString result;
	InvokeHelper(0x85, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetWMode
*  ��������     :���õ�ǰѡ�õĲ���ģʽ
*  �����������	:
*   LPCTSTR lpszNewValue�� ����ģʽ����
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::SetWMode(LPCTSTR lpszNewValue)
{
	static BYTE parms[] = VTS_BSTR;
	InvokeHelper(0x85, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetSAlign()
*  ��������     :�õ�����Flash�����Ķ���ģʽ
*  �����������	:
*  ���ر���˵�� :Flash�����Ķ���ģʽ����
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
CString CShockwaveFlash::GetSAlign()
{
	CString result;
	InvokeHelper(0x86, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetSAlign
*  ��������     :���ò���Flash�����Ķ���ģʽ
*  �����������	:
*     LPCTSTR lpszNewValue��Flash�����Ķ���ģʽ����
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::SetSAlign(LPCTSTR lpszNewValue)
{
	static BYTE parms[] = VTS_BSTR;
	InvokeHelper(0x86, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetMenu()
*  ��������     :�õ��ؼ��еĲ˵��Ƿ����
*  �����������	:
*  ���ر���˵�� :����TRUE��ʾ���ã�����FALS��ʾ������
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
BOOL CShockwaveFlash::GetMenu()
{
	BOOL result;
	InvokeHelper(0x87, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetMenu
*  ��������     :���ÿؼ��еĲ˵��Ƿ����
*  �����������	:
*   BOOL bNewValue����ΪTRUE��ʾ���ã���ΪFALS��ʾ������
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::SetMenu(BOOL bNewValue)
{
	static BYTE parms[] = VTS_BOOL;
	InvokeHelper(0x87, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetBase()
*  ��������     :�õ�����Flash���ſؼ��Ļ�����Ϣ
*  �����������	:
*  ���ر���˵�� :����Flash���ſؼ��Ļ�����Ϣ
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
CString CShockwaveFlash::GetBase()
{
	CString result;
	InvokeHelper(0x88, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetBase
*  ��������     :���ù���Flash���ſؼ��Ļ�����Ϣ
*  �����������	:
*    LPCTSTR lpszNewValue: ����Flash���ſؼ��Ļ�����Ϣ
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::SetBase(LPCTSTR lpszNewValue)
{
	static BYTE parms[] = VTS_BSTR;
	InvokeHelper(0x88, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetScale()
*  ��������     :�õ����ű���
*  �����������	:
*  ���ر���˵�� :���ű���ֵ
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
CString CShockwaveFlash::GetScale()
{
	CString result;
	InvokeHelper(0x89, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetScale
*  ��������     :���ò��ű���
*  �����������	:
*   LPCTSTR lpszNewValue:���ű���ֵ
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::SetScale(LPCTSTR lpszNewValue)
{
	static BYTE parms[] = VTS_BSTR;
	InvokeHelper(0x89, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetDeviceFont()
*  ��������     :�õ��豸�Ƿ�֧�ֵ�ǰ�����õ�����
*  �����������	:
*  ���ر���˵�� :����TRUE��ʾ֧�֣�����FALSE��ʾ��֧��
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
BOOL CShockwaveFlash::GetDeviceFont()
{
	BOOL result;
	InvokeHelper(0x8a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetDeviceFont
*  ��������     :�����豸�Ƿ�֧�ֵ�ǰ�����õ�����
*  �����������	:
*    BOOL bNewValue����ΪTRUE��ʾ֧�֣���ΪFALSE��ʾ��֧��
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::SetDeviceFont(BOOL bNewValue)
{
	static BYTE parms[] = VTS_BOOL;
	InvokeHelper(0x8a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetEmbedMovie()
*  ��������     :�õ��Ƿ�Ƕ���Flash����ӰƬ
*  �����������	:
*  ���ر���˵�� :����TRUE��ʾǶ����Flash����ӰƬ������FALSE��ʾû��Ƕ��Flash����ӰƬ
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
BOOL CShockwaveFlash::GetEmbedMovie()
{
	BOOL result;
	InvokeHelper(0x8b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetEmbedMovie
*  ��������     :�����Ƿ�Ƕ���Flash����ӰƬ
*  �����������	:
*     BOOL bNewValue����ΪTRUE��ʾǶ����Flash����ӰƬ����ΪFALSE��ʾ��Ƕ��Flash����ӰƬ
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::SetEmbedMovie(BOOL bNewValue)
{
	static BYTE parms[] = VTS_BOOL;
	InvokeHelper(0x8b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetBGColor()
*  ��������     :�õ�Flash�����е������߲��õ���ɫ
*  �����������	:
*  ���ر���˵�� :Flash�����е������߲��õ���ɫֵ
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
CString CShockwaveFlash::GetBGColor()
{
	CString result;
	InvokeHelper(0x8c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetBGColor
*  ��������     :����Flash�����е������߲��õ���ɫ
*  �����������	:
*   LPCTSTR lpszNewValue��Flash�����е������߲��õ���ɫֵ
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::SetBGColor(LPCTSTR lpszNewValue)
{
	static BYTE parms[] = VTS_BSTR;
	InvokeHelper(0x8c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetQuality2()
*  ��������     :�õ�Ҫ���ŵ�Flash������Ʒ��
*  �����������	:
*  ���ر���˵�� :���ŵ�Flash������Ʒ��
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
CString CShockwaveFlash::GetQuality2()
{
	CString result;
	InvokeHelper(0x8d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetQuality2
*  ��������     :����Ҫ���ŵ�Flash������Ʒ��
*  �����������	:
*    LPCTSTR lpszNewValue�����ŵ�Flash������Ʒ��
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::SetQuality2(LPCTSTR lpszNewValue)
{
	static BYTE parms[] = VTS_BSTR;
	InvokeHelper(0x8d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :LoadMovie
*  ��������     :����ָ��λ��ָ��ͼ���Flash����ӰƬ
*  �����������	:
*    long layer:ͼ����
*    LPCTSTR url��������URLλ��
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::LoadMovie(long layer, LPCTSTR url)
{
	static BYTE parms[] = VTS_I4 VTS_BSTR;
 	InvokeHelper(0x8e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 layer, url);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :TGotoFrame
*  ��������     :ת��ָ��Ŀ��λ�õ�֡��λ��
*  �����������	:
*	LPCTSTR target:Ŀ��λ��
*	long FrameNum���������
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::TGotoFrame(LPCTSTR target, long FrameNum)
{
	static BYTE parms[] = VTS_BSTR VTS_I4;
	InvokeHelper(0x8f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 target, FrameNum);
}

/*
*--------------------------------------------------------------------------------
*  ��Ա������   :TGotoLabel
*  ��������     :ת��ָ��Ŀ��λ�õı�ǩλ��
*  �����������	:
*	LPCTSTR target:Ŀ��λ��
*	LPCTSTR label����ǩֵ
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::TGotoLabel(LPCTSTR target, LPCTSTR label)
{
	static BYTE parms[] = VTS_BSTR VTS_BSTR;
	InvokeHelper(0x90, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 target, label);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :TCurrentFrame
*  ��������     :ת��ָ��Ŀ��λ�õ�ǰ֡
*  �����������	:
*     LPCTSTR target��Ŀ��λ��
*  ���ر���˵�� :��ǰ��֡���
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
long CShockwaveFlash::TCurrentFrame(LPCTSTR target)
{
	long result;
	static BYTE parms[] = VTS_BSTR;
	InvokeHelper(0x91, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		target);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :TCurrentLabel
*  ��������     :�õ���ǰָ��Ŀ��λ�õı�ǩ
*  �����������	:
*     LPCTSTR target��Ŀ��λ��
*  ���ر���˵�� :��ǰ��ǩֵ
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
CString CShockwaveFlash::TCurrentLabel(LPCTSTR target)
{
	CString result;
	static BYTE parms[] = VTS_BSTR;
	InvokeHelper(0x92, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		target);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :TPlay
*  ��������     :��ָ��Ŀ��λ�ò���Flash����
*  �����������	:
*   LPCTSTR target��Ŀ��λ��
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::TPlay(LPCTSTR target)
{
	static BYTE parms[] = VTS_BSTR;
	InvokeHelper(0x93, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 target);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :TStopPlay
*  ��������     :��ͣ��ָ��Ŀ��λ���ϲ���Flash
*  �����������	:
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::TStopPlay(LPCTSTR target)
{
	static BYTE parms[] = VTS_BSTR;
	InvokeHelper(0x94, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 target);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetVariable
*  ��������     :����Flash�ؼ�֧�ֵı���ֵ
*  �����������	:
*    LPCTSTR name����������
*    LPCTSTR value������ֵ
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::SetVariable(LPCTSTR name, LPCTSTR value)
{
	static BYTE parms[] = VTS_BSTR VTS_BSTR;
	InvokeHelper(0x97, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 name, value);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetVariable
*  ��������     :�õ�Flash�ؼ�֧�ֵı���ֵ
*  �����������	:
*    LPCTSTR name����������
*  ���ر���˵�� :����ֵ
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
CString CShockwaveFlash::GetVariable(LPCTSTR name)
{
	CString result;
	static BYTE parms[] = VTS_BSTR;
	InvokeHelper(0x98, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		name);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :TSetProperty
*  ��������     :����Flash�ؼ�֧�ֵ�����ֵ
*  �����������	:
*    LPCTSTR target:Ŀ��λ��
*    long property������
*    LPCTSTR value������ֵ
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::TSetProperty(LPCTSTR target, long property, LPCTSTR value)
{
	static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR;
	InvokeHelper(0x99, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 target, property, value);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :TGetProperty
*  ��������     :�õ�Flash�ؼ�֧�ֵ�����ֵ
*  �����������	:
*    LPCTSTR target:Ŀ��λ��
*    long property������
*  ���ر���˵�� :����ֵ
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
CString CShockwaveFlash::TGetProperty(LPCTSTR target, long property)
{
	CString result;
	static BYTE parms[] = VTS_BSTR VTS_I4;
	InvokeHelper(0x9a, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		target, property);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :TCallFrame
*  ��������     :����ָ��Ŀ��λ�õ�ָ��֡
*  �����������	:
*	LPCTSTR target��Ŀ��λ��
*	long FrameNum��֡���
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::TCallFrame(LPCTSTR target, long FrameNum)
{
	static BYTE parms[] = VTS_BSTR VTS_I4;
	InvokeHelper(0x9b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 target, FrameNum);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :TCallLabel
*  ��������     :����ָ��Ŀ��λ�õ�ָ����ǩ��֡
*  �����������	:
*	LPCTSTR target��Ŀ��λ��
*	long FrameNum��֡��ǩ��
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::TCallLabel(LPCTSTR target, LPCTSTR label)
{
	static BYTE parms[] = VTS_BSTR VTS_BSTR;
	InvokeHelper(0x9c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 target, label);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :TSetPropertyNum
*  ��������     :����Ŀ��λ�õ�����ֵ
*  �����������	:
*	LPCTSTR target��Ŀ��λ��
*	long property������
*	double value������ֵ
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::TSetPropertyNum(LPCTSTR target, long property, double value)
{
	static BYTE parms[] = VTS_BSTR VTS_I4 VTS_R8;
	InvokeHelper(0x9d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 target, property, value);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :TGetPropertyNum
*  ��������     :�õ�Ŀ��λ�õ�����ֵ
*  �����������	:
*	LPCTSTR target��Ŀ��λ��
*	long property������
*  ���ر���˵�� :����ֵ
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
double CShockwaveFlash::TGetPropertyNum(LPCTSTR target, long property)
{
	double result;
	static BYTE parms[] = VTS_BSTR VTS_I4;
	InvokeHelper(0x9e, DISPATCH_METHOD, VT_R8, (void*)&result, parms,
		target, property);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :GetSWRemote()
*  ��������     :�õ�Flash�е�����ϸ�ڲ���
*  �����������	:
*  ���ر���˵�� :ϸ�ڲ���
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
CString CShockwaveFlash::GetSWRemote()
{
	CString result;
	InvokeHelper(0x9f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :SetSWRemote
*  ��������     :����Flash�е�����ϸ�ڲ���
*  �����������	:
*    LPCTSTR lpszNewValue��ϸ�ڲ���ֵ
*  ���ر���˵�� :
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
void CShockwaveFlash::SetSWRemote(LPCTSTR lpszNewValue)
{
	static BYTE parms[] = VTS_BSTR;
	InvokeHelper(0x9f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/*
*--------------------------------------------------------------------------------
*  ��Ա������   :PreTranslateMessage
*  ��������     :�õ�������WINDOWS��Ϣ
*  �����������	:
*    MSG* pMsg����Ϣָ��
*  ���ر���˵�� :����ɹ�����TRUE������FALSEʧ��
*  �㷨����		:
*  ����˵��     :
*--------------------------------------------------------------------------------
*/
BOOL CShockwaveFlash::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message ==WM_RBUTTONDOWN)
         return  1;
	if (pMsg->message ==WM_LBUTTONDOWN)
        Invalidate ();

	//�����ҽ�������Flash�ؼ�Ĭ�ϵĲ˵���

	return CWnd::PreTranslateMessage (pMsg);

	return true;
}