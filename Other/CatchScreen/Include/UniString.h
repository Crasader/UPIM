/////////////////////////////////////////////////////////////////////////////
/**
* �ļ���  ��UniString.h
* �汾��  �� V1.0
* ��Ŀ���ƣ� ˫�ֽڴ����ַ�������
* ��Ȩ������ Copyright 2005 Luowei. All Rights Reserved.
* ģ���������
*======================================================
* �汾�����¼:
*      
*      2005-3-19  v1.0 ��ΰ
*/
/////////////////////////////////////////////////////////////////////////////

#ifndef __UNISTRING_H__
#define __UNISTRING_H__

#include <iostream.h>
#include <string.h>
#include <wtypes.h>

#ifndef PASCAL
#define PASCAL      __stdcall
#endif

#define INIT_BUFFER_LEN 100

#ifndef INT_MAX
#define INT_MAX       2147483647 
#endif

#define INIT_BUFFER_LEN 100

#define _UNISTRING
#ifndef AFXAPI
	#define AFXAPI __stdcall
#endif

//����MFC֧�֣���ȥ������Ķ���ǰ��ע��

#define _MFC_SUPPORT


class CUniString
{
public:

#ifdef _MFC_SUPPORT
	  CString m_pchDebugData;

#else
	  LPCTSTR m_pchDebugData;
#endif

   long GetBufferStr(LPTSTR & bufStr, long bufSize);    //���ӣ���˫�ֽ�����ת��ΪϵͳĬ������
   int Find(int nFirst, int nEnd, CUniString findStr);  //���ӣ����ַ����в���findStr�ַ���

     // ���캯��
    CUniString( ) : m_pchData( NullString ), m_nBufferLen( -1 ) { }
    CUniString( const LPWSTR Value );
    CUniString( const LPCSTR Value );
    CUniString( const CUniString & Value );

    // ��������
    ~CUniString( ) { if( m_nBufferLen != -1 ) delete [ ] m_pchData; }

    //����MFC�е� CString �����ͷ���
    int	 GetLength( ) const { return wcslen( m_pchData ); }
	BOOL IsEmpty() const;
	void Empty();                       // free up the data
    LPWSTR GetBuffer( int MaxStrLen );
	LPWSTR GetBufferSetLength(int nNewLength);

	CUniString Mid(int nFirst, int nCount) const;
	CUniString Mid(int nFirst) const;
	CUniString Left(int nCount) const;
	CUniString Right(int nCount) const;

//����ת��
	int			UniStrToInt(CUniString str);
	CUniString  IntToUniStr(int intV);
	long		UniStrToLong(CUniString str);
	CUniString  LongToUniStr(long longV);
	double		UniStrToDouble(CUniString str);
	CUniString  DoubleToUniStr(double doubleV, int defPoint=6);	



	// ����������
    const CUniString & operator=( const CUniString & Rhs );

    const CUniString & operator=( LPWSTR Rhs );
#ifdef  _MFC_SUPPORT
	const CUniString & operator=( const CString & string );
#endif
	const CUniString & operator=( const LPCSTR Rhs );


	operator LPWSTR() const;          

     //��������ת��
	operator LPTSTR() const;         
	

    const CUniString & operator=( const WCHAR Rhs );
    const CUniString & operator+=( const WCHAR Rhs );
	const CUniString & operator+=( const LPWSTR lpsz );
	const CUniString & operator+=( const CUniString& string );

     #ifdef _MFC_SUPPORT
		const CUniString & operator+=( const CString& string );
    #endif

    WCHAR operator[ ]( int Index ) const;
    WCHAR & operator[ ]( int Index );

    // ������Ԫ����
    friend int operator ==
        ( const CUniString & Lhs, const CUniString & Rhs );
    friend int operator !=
        ( const CUniString & Lhs, const CUniString & Rhs );
    friend int operator <
        ( const CUniString & Lhs, const CUniString & Rhs );
    friend int operator >
        ( const CUniString & Lhs, const CUniString & Rhs );
    friend int operator <=
        ( const CUniString & Lhs, const CUniString & Rhs );
    friend int operator >=
        ( const CUniString & Lhs, const CUniString & Rhs );

    friend CUniString AFXAPI operator+(const CUniString& string1, const CUniString& string2);
	#ifdef _MFC_SUPPORT
		
		friend CArchive& AFXAPI operator<<(CArchive& ar, const CUniString& string);
		friend CArchive& AFXAPI operator>>(CArchive& ar, CUniString& string);
    #endif

private:
    int		m_nBufferLen;       // ��������󳤶�
    static	LPWSTR NullString;  // ʾ��ʼ������ĳ�Ա����˫�ֽ��ַ�
	void	Release();

//	#ifdef _MFC_SUPPORT
		static int PASCAL SafeStrlen(const LPWSTR lpsz);
 //    #endif

	// ��ʼ������
	void Init();
	void AllocBuffer(int nLen);
	void AllocCopy(CUniString& dest, int nCopyLen, int nCopyIndex, int nExtraLen) const;
	void ConcatInPlace(int nSrcLen, const LPWSTR lpszSrcData);

public:


	void ConcatCopy(int nSrc1Len, LPWSTR lpszSrc1Data,	int nSrc2Len, LPWSTR lpszSrc2Data);
    LPWSTR	m_pchData;			// ���������ַ������ݴ��ڴ˳�Ա������
};


istream & operator>>( istream & In, CUniString & Value );


inline int
operator==( const CUniString & Lhs, const CUniString & Rhs )
{
    return wcscmp( Lhs.m_pchData, Rhs.m_pchData ) == 0;
}

inline int
operator!=( const CUniString & Lhs, const CUniString & Rhs )
{
    return wcscmp( Lhs.m_pchData, Rhs.m_pchData ) != 0;
}

inline int
operator<( const CUniString & Lhs, const CUniString & Rhs )
{
    return wcscmp( Lhs.m_pchData, Rhs.m_pchData ) < 0;
}

inline int
operator>( const CUniString & Lhs, const CUniString & Rhs )
{
    return wcscmp( Lhs.m_pchData, Rhs.m_pchData ) > 0;
}

inline int
operator<=( const CUniString & Lhs, const CUniString & Rhs )
{
    return wcscmp( Lhs.m_pchData, Rhs.m_pchData ) <= 0;
}

inline int
operator>=( const CUniString & Lhs, const CUniString & Rhs )
{
    return wcscmp( Lhs.m_pchData, Rhs.m_pchData ) >= 0;
}

#endif // __UNISTRING_H__
