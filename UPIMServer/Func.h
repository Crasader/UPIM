#pragma once
#include "stdafx.h"

//��־��
#define OP_LOG_DEGUB(pszFormat, ...)    g_serverlog.WriteFormatDebugLog( pszFormat, __VA_ARGS__)
#define OP_LOG_INFO(pszFormat, ...)		g_serverlog.WriteFormatInfoLog(pszFormat, __VA_ARGS__)
#define OP_LOG_TRACE(pszFormat, ...)    g_serverlog.WriteFormatTraceLog( pszFormat, __VA_ARGS__)
#define OP_LOG_WARN(pszFormat, ...)		g_serverlog.WriteFormatWarnLog( pszFormat, __VA_ARGS__)
#define OP_LOG_ERROR(pszFormat, ...)    g_serverlog.WriteFormatErrorLog( pszFormat, __VA_ARGS__)
#define OP_LOG_FATAL(pszFormat, ...)    g_serverlog.WriteFormatFatalLog( pszFormat, __VA_ARGS__)

// ��䷵��buf�ṹ
extern BOOL InitAnsBufHead(IMANSBUFFER& m_ansBuf, long req, long PacketLen = 0, long RawLen = 0);
extern VOID		LoadConfig();															// ���ط����������ļ�	
extern VOID		SaveConfig();
extern BOOL	    IsWhiteIP(CHAR* strIP);
extern WORD		GetBuildNo( LPSTR lpszDateTime, const WORD wSize );						// ��ȡ�������к�
extern CString	IntToStr(int nVal);
extern CString	LongToStr(long lVal);
extern CString	ULongToStr(unsigned long ulVal);
extern CString	DblToStr(double dblVal, int ndigits = 20);
extern CString	DblToStr(float fltVal);
extern LPCSTR	AllTrim( LPSTR lpszString );
extern LPSTR	SafeStrcpy( LPSTR lpszDest, LPCSTR lpcszSrc, const WORD wDestSize );
extern BOOL		ConnectDataBase( LPDBCONFIG lpdbConfig, CADODatabase* pAdoDb);			// �������ݿ�
extern BOOL		DisConnectDataBase( CADODatabase* pAdoDb );								// �Ͽ����ݿ�
extern BOOL		IsDBDisConn(CString strError);											// ���ݿ�״̬
extern CString	GetNowTime();
extern double   StrToOleDateTime(CString str);
extern LPCSTR   OleDateTimetoStr(double mdt,const char* pFormatstr);
extern void ConvertTimeToLong(time_t tmTime, long& nRetDate, long& nRetTime);
extern LONG ParseJsonFields(LPSTR lpszString, STATE_REFLASH_& mstu, LONG nMaxField);

//�������API ����������������ַ����� ���ַ���������Ϊԭʼ�Ķ�������
//�������������ݷ���pResultBuf,ע��nMaxResultBufLen�ĳ�������ӦΪnRawDataLen��2������
//bEncodeΪTRUE,��ʾ�˺������ڱ���,�������ڽ���
//�����������ʧ��,����-1,�ɹ��򷵻ر��������ĳ���
extern long Base64_Encode(BYTE *pRawData, long nRawDataLen, BYTE *pResultBuf, long nMaxResultBufLen, BOOL bEncode);