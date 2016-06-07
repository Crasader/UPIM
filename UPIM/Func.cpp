#include "StdAfx.h"
#include "Func.h"
#include "IniFile.h"
#include <Windows.h>

#pragma  comment(lib,"Rpcrt4.lib")			//UUID��Ҫ

BOOL InitReqBufHead(IMREQBUFFER& m_reqbuf, long PacketLen , long RawLen)
{
	m_reqbuf.ReqHeader.Info.Version	= NOW_VERSION;
	m_reqbuf.ReqHeader.Priority		= 1;
	m_reqbuf.ReqHeader.PacketLen	= PacketLen;
	m_reqbuf.ReqHeader.RawLen		= RawLen;

	return TRUE;
}

// ��ȡ�������к�
WORD GetBuildNo( LPSTR lpszDateTime, const WORD wSize )
{
	static CHAR *s_MonthStr[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	static CHAR	s_szBuildDateTime[32] = "";
	static WORD	s_nBuildNo = 0;

	if ( s_nBuildNo == 0 )
	{
		CHAR szTemp[16] = {0};
		LONG nYear, nMonth, nDay, nHour, nMin,nSec;
		// ����
		strncpy( szTemp, __DATE__, 3 );
		szTemp[3] = '\0';
		for ( nMonth=1; nMonth<=12; nMonth++ )
		{
			if ( _stricmp( szTemp, s_MonthStr[nMonth-1] ) == 0 )
			{
				break;
			}
		}
		strncpy( szTemp, __DATE__+4, 2 );
		szTemp[2] = '\0';
		nDay = atoi( szTemp );
		strncpy( szTemp, __DATE__+7, 4 );
		szTemp[4] = '\0';
		nYear = atoi( szTemp );
		// ʱ��
		strncpy( szTemp, __TIME__, 2 );
		szTemp[2] = '\0';
		nHour = atoi( szTemp );
		strncpy( szTemp, __TIME__+3, 2 );
		szTemp[2] = '\0';
		nMin = atoi( szTemp );
		strncpy( szTemp, __TIME__+6, 2 );
		szTemp[2] = '\0';
		nSec = atoi( szTemp );
		// �γ������ʽ
		if ((nHour >= 9) && (nHour <= 16))
		{
			s_nBuildNo = (WORD)( nHour - 8 );
		}
		else if (nHour < 9)
		{
			s_nBuildNo = 0;
		}
		else
		{
			s_nBuildNo = 9;
		}
		s_nBuildNo += (WORD)( ( ( (nYear - VER_STARTYEAR) * 12 + nMonth) * 31 + nDay) * 10 );
		s_nBuildNo %= 10000;
		_snprintf( s_szBuildDateTime, 32, "%04d/%02d/%02d %02d:%02d:%02d", nYear, nMonth, nDay, nHour, nMin,nSec);
	}

	strncpy( lpszDateTime, s_szBuildDateTime, wSize );
	return s_nBuildNo;
}

bool GetNextMsg(FriendList_ITER iterator, RECEIVED_MSG *msg)
{
	if(iterator->pMsg && iterator->pMsg->size()!=0)
	{
		memcpy(msg, &iterator->pMsg->front(),sizeof(RECEIVED_MSG));
		iterator->pMsg->erase(iterator->pMsg->begin());
		return true;
	}
	return false;
}

bool GetNextMsg_More(vector<RECEIVED_MSG> *pMsg, RECEIVED_MSG *msg)
{
	if(pMsg && pMsg->size()!=0)
	{
		memcpy(msg, &pMsg->front(),sizeof(RECEIVED_MSG));
		pMsg->erase(pMsg->begin());
		return true;
	}
	return false;
}

void UpdateVtClientInfo(CString strUPID, int nGroupID)
{
	for (int idex=0; idex<(int)m_vtRoomClient.size(); idex++)
	{
		CString strUser = m_vtRoomClient[idex].m_szUPID;
		if (strUser.CompareNoCase(strUPID) == 0)
		{
			m_vtRoomClient[idex].m_nGroupID = nGroupID;
			return;
		}
	}
	return;
}

void UpdateGroupFlag(int nGroupID)
{
	for (int n=0; n<=USERMRG_FENZU; n++)
	{
		if (m_groupInfoStc[n].bUsed == true && m_groupInfoStc[n].nGroupID == nGroupID)
			m_groupInfoStc[n].bGetUserInfo = true;
	}
}

// ����GroupID��״̬
void SetGroupFlag(int nGroupID ,bool falg) 
{
	for (int n=0; n<=USERMRG_FENZU; n++)
	{
		if ( m_groupInfoStc[n].nGroupID == nGroupID)
		{
			m_groupInfoStc[n].bUsed = falg ;
		}
	}
}
int GetGroupIDByName(CString strGroupName)
{
	int nGroupID = -1;
	for (int n=0; n<=USERMRG_FENZU; n++)
	{
		if (strGroupName.CompareNoCase(m_groupInfoStc[n].GroupName) == 0)
			nGroupID = m_groupInfoStc[n].nGroupID;
	}
	return nGroupID;
}

int GetNowTimeHourAndMin()
{
	int nHourAndMin = 0;

	time_t thisTime = time(NULL);
	struct tm *ptm = localtime(&thisTime);

	nHourAndMin = ptm->tm_hour * 100 + ptm->tm_min;
	return nHourAndMin;
}

int GetGroupClientNums(int nGroupID )
{
	int nNums = 0;
	int nOnlineNums = 0 ; 

	for (int idex=0; idex<(int)m_vtRoomClient.size(); idex++)
	{
		if (m_vtRoomClient[idex].m_nGroupID == nGroupID)
		{
			nNums++;
			if( m_vtRoomClient[idex].m_bIsOnLine)
				nOnlineNums++ ; 
		}
	}
	return  nNums ; 
	//onlinetotalNums = nOnlineNums ; 
}
 // ��ȡ����ʦ����ĳ������ͻ��������� 
int GetRoomClientOnlineNums()
{
	int nNums = 0 ; 
	for( int idex = 0 ; idex < m_vtRoomClient.size() ;idex++)
		if( m_vtRoomClient[idex].m_bIsOnLine)
			nNums++ ;

	return nNums ; 
}
// ��ȡ���������������� 
int GetGroupClientOnlineNums(int nGroupID)
{
	int nNums = 0 ; 
	int iSize = m_vtRoomClient.size() ; 
	for( int i = 0 ; i < iSize ; i++)
	{
		if( m_vtRoomClient[i].m_nGroupID == nGroupID)
			if( m_vtRoomClient[i].m_bIsOnLine)
				nNums++ ; 
	}
	return nNums ; 
}
BOOL IsAllGroupLoad()
{
	for (int n=0; n<=USERMRG_FENZU; n++)
	{
		// WUCHAO MODIFY 20160309
		if (m_groupInfoStc[n].bUsed == true)
			if (m_groupInfoStc[n].bGetUserInfo == false)
				return FALSE;
		//if( m_groupInfoStc[n].bLoad == false )
		//	if( m_groupInfoStc[n].bGetUserInfo == false)
		//		return FALSE ; 
	}

	return TRUE;
}

BOOL IsInvtRoomClient(CString strUserID)
{
	for (int idex=0; idex<(int)m_vtRoomClient.size(); idex++)
	{
		CString strTmp1 = m_vtRoomClient[idex].m_szUPID;
		if (strUserID.CompareNoCase(strTmp1) == 0)
			return TRUE;
	}
	return FALSE;
}

CString ConvertMsgContent(LPCSTR lpMsg)
{
	CString strReturnMsg = _T("");
	CHAR *cStart = _T("[\"");
	CHAR *cEnd = _T("\"]");
	tstring strText;
	//////////////////////////////////////////////////////////////////////////
	// /c["�Զ���ͼƬ·��"] �����Լ��м�������滻Ϊ [ͼƬ]
	// /s["ϵͳ����index"] �����Լ��м�������滻Ϊ [����]
	// /f["ϵͳ����id"] �����Լ��м�������滻Ϊ [����]

	for (LPCTSTR p = lpMsg; *p != _T('\0'); p++)
	{
		if (*p == _T('/'))
		{
			if (*(p+1) == _T('/'))
			{
				strText += *p;
				p++;
				continue;
			}
			else if (*(p+1) == _T('f'))
			{
				p = _tcsstr(p+2, _T("\"]"));
				p++;

				strText += "[����]";
				continue;
			}
			else if (*(p+1) == _T('s'))
			{
				p = _tcsstr(p+2, _T("\"]"));
				p++;

				strText += "[����]";
				continue;
			}
			else if (*(p+1) == _T('c'))
			{
				p = _tcsstr(p+2, _T("\"]"));
				p++;

				strText += "[ͼƬ]";
				continue;
			}
		}
		strText += *p;
	}

	strReturnMsg = strText.c_str();
	return strReturnMsg;
}

CString ConvertMsgToChiefMsg(BYTE format, LPCSTR lpMsg)
{
	CString strReturnMsg = _T("");
	if (format == eMsgFormat_Txt)
	{
		// �����txt�ı�����ֱ�ӽ���ת��
		strReturnMsg = ConvertMsgContent(lpMsg);
	}
	else if (format == eMsgFormat_Def)
	{
		// �����xml���Ȱ�data�ֶν�������
		TiXmlDocument xmlDoc;
		xmlDoc.Parse(lpMsg);

		if(xmlDoc.Error()) 
		{
			printf( "Error in %s: %s\n", xmlDoc.Value(), xmlDoc.ErrorDesc() );
			return strReturnMsg;
		}

		CString strTmpFmt,strOld;
		TiXmlNode* pRootNode = xmlDoc.FirstChild("msg");
		if(!pRootNode) 	
			return strReturnMsg;
		TiXmlElement* pRootElm =pRootNode->ToElement();
		if(!pRootElm) 	
			return strReturnMsg;
		//////////////////////////////////////////////////////////////////////////

		TiXmlNode* pItemNode = pRootNode->FirstChild("text"); 
		if(!pItemNode) 
			return strReturnMsg;
		TiXmlNode* pTextNode = pItemNode->FirstChild();
		if(!pTextNode) 
			return strReturnMsg;
		CString strText = pTextNode->Value();

		strReturnMsg = ConvertMsgContent(strText);
	}
	else if (format == eMsgFormat_File)
	{
		strReturnMsg = _T("[�ļ�]");
	}
	return strReturnMsg;
}

//���ID�Ƿ�Ϊ�ֻ����룬�ǵĻ�������λ��*����
CString ConvertIdToNoPhonrNum(CString strID)
{
	CString strResult = "";
	// ȥ�ո�
	strID.Trim();

	// �ַ����ɴ����ֹ��ɣ�����Ҫ��
	if ( strID == strID.SpanIncluding( _T("0123456789") ) )   
	{
		// ����Ϊ11
		if (strID.GetLength() == 11)
		{
			strResult = strID.Left(7) + "****";
		}
		else
			strResult = strID;
	}
	else
		strResult = strID;

	return strResult;
}

bool CreateGUID(char * guid)
{
	UUID  id;
	if(UuidCreate(&id)!=RPC_S_OK)
		return false;
	ASSERT(sizeof(UUID) == GUID_SIZE);
	memcpy(guid,&id,sizeof(UUID));
	return true;
	/*
	UUID uuidRoute;
	RPC_STATUS st;
	if(UuidCreate(&id)!=RPC_S_OK)
		return false;
	unsigned char *pszGuid;     
	UuidToString(&uuidRoute, &pszGuid);
	_bstr_t bstrUUID = _bstr_t((char*)pszGuid);     
	RpcStringFree(&pszGuid);
	*/
}

CString MakeGuid(char* strguid)
{
	CString str;
	GUID guid;
	if(strguid==NULL) 
		CoCreateGuid(&guid);
	else	
		memcpy(&guid,strguid, GUID_SIZE);
	str.Format("%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1],
		guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5],
		guid.Data4[6], guid.Data4[7]);
	return str;
}

void ConvertTimeToLong(time_t tmTime, long& nRetDate, long& nRetTime)
{
	struct tm *ptm = localtime(&tmTime);
	if(!ptm)
	{
		time_t thisTime = time(NULL);
		ptm = localtime(&thisTime);
	}
	nRetDate = (ptm->tm_year+1900)*10000+(ptm->tm_mon+1)*100+ptm->tm_mday;
	nRetTime = ptm->tm_hour*10000+ptm->tm_min*100+ptm->tm_sec;
}

void ConvertTimeToLong2(int date ,int time ,long& nRetTime) 
{
	CString strDate = _T("") ; 
	strDate.Format("%d" ,date) ; 
	CString strYear = _T(""),strMonth = _T(""),strDay = _T(""); 
	// ȡǰ��λ ��� 
	strYear = strDate.Left(4) ; 
	// ȡ�м���λ  �·� 
	strMonth = strDate.Mid(4 ,2) ; 
	// ȡ�����λ  �� 
	strDay = strDate.Right(2) ; 

	int nYear = atoi(strYear.GetBuffer()) ; 
	int nMonth = atoi(strMonth.GetBuffer()) ; 
	int nDay   = atoi(strDay.GetBuffer()) ; 

	CTime tempTime(nYear ,nMonth,nDay-1,0,0,0) ; 
	nRetTime = tempTime.GetTime() ; 
	//nRetTime = ( nYear ) * 10000 +  (  nMonth ) *100 + nDay ; 
	nRetTime += time ; 

}
LPSTR SafeStrcpy( LPSTR lpszDest, LPCSTR lpcszSrc, const WORD wDestSize )
{
	if(!lpszDest) return NULL;
	strncpy( lpszDest, lpcszSrc, wDestSize );
	lpszDest[wDestSize-1] = '\0';
	return lpszDest;
}

//////////////////////////////////////////////////////////////////////////
// ��ʼ��SQLITE
VOID InitSQLITE()
{
	if(g_config.m_bHisMsg)
	{
		g_SqliteOp.DBCreate();
		g_SqliteOp.DBOpen();
	}
}

VOID LoadConfig()
{
	g_config.dwBuildNo = GetBuildNo(g_config.szBuildDateTime, sizeof(g_config.szBuildDateTime));

	long nDate = 0, nTime = 0;
	ConvertTimeToLong(time(NULL), nDate, nTime);
	nsprintf( g_config.szRunTime, sizeof(g_config.szRunTime), "%08d-%06d", nDate, nTime);

	CHAR	szFormat[MAX_PATH] = {0}, szData[MAX_PATH] = {0};
	LONG	nData = 0;
#ifdef _EXE_MODE
	GetModuleFileName( NULL, g_config.szHomePath, sizeof(g_config.szHomePath) );
#else
	GetModuleFileName( g_hInstance, g_config.szHomePath, sizeof(g_config.szHomePath) );
#endif

	long nLen = strlen( g_config.szHomePath );
	for ( long loop=(nLen-1); loop>=0; loop-- )
	{
		if ( g_config.szHomePath[loop] == '\\' )
		{
			g_config.szHomePath[loop] = 0;
			break;
		}
	}

	CString strLogFolder = "";
	strLogFolder.Format("%s\\log\\", g_config.szHomePath);
	CreateDirectory(strLogFolder, NULL);

	nsprintf( g_config.szLogPath, sizeof(g_config.szLogPath), "%s\\log\\", g_config.szHomePath );
	nsprintf( g_config.szConfigPath, sizeof(g_config.szConfigPath), "%s\\UPIM.cfg", g_config.szHomePath );
	nsprintf( g_config.szFaceConfig, sizeof(g_config.szFaceConfig), "%s\\Face\\FaceConfig.xml", g_config.szHomePath );
	nsprintf( g_config.szUserDisplay, sizeof(g_config.szUserDisplay), "%s\\display", g_config.szHomePath );
	
	CIniFile m_IniFile;
	m_IniFile.SetFileName(g_config.szConfigPath);
	CString strTmp = "";

	//////////////////////////////////////////////////////////////////////////
	//���ݿ�����
	m_IniFile.SetAppName("IMHost");
	int nHostCount =  m_IniFile.GetInt( "HostNum",0);
	nHostCount = min(nHostCount, MAX_DBCOUNT);
	g_config.nMainHost = m_IniFile.GetInt( "PrimaryHost",0);
	char szKey[64] = {0};
	for(int i=0; i<nHostCount; i++)
	{
		// ����Դ
		sprintf(szKey,"IPAddress%02d", i+1);
		m_IniFile.GetString(strTmp, szKey, "");
		strTmp.Trim();
		SafeStrcpy(g_config.aHostCfg[i].szSVRIP, strTmp, sizeof(g_config.aHostCfg[i].szSVRIP) );
		// ���ݿ�
		sprintf(szKey,"Port%02d", i+1);
		m_IniFile.GetString(strTmp, szKey, "");
		strTmp.Trim();
		g_config.aHostCfg[i].dwSVRPORT = atoi(strTmp);
	}

	//////////////////////////////////////////////////////////////////////////
	m_IniFile.SetAppName("more");
	g_config.m_bClientGrp	=  m_IniFile.GetInt( "defgroup",	1);
	g_config.m_bEmpProduct	=  m_IniFile.GetInt( "product",		0);
	g_config.m_bDefGroup	=  m_IniFile.GetInt( "defgroup",	0);
	g_config.m_bDept		=  m_IniFile.GetInt( "dept",		1);
	g_config.m_bPublic		=  m_IniFile.GetInt( "public",		1);
	g_config.m_bDefGroup2	=  m_IniFile.GetInt( "defgroup2",	0);
	g_config.m_bHisMsg		=  m_IniFile.GetInt( "hismsg",		1);

	//////////////////////////////////////////////////////////////////////////
	m_IniFile.SetAppName("logintest");
	m_IniFile.GetString(strTmp, "upid", "");
	strTmp.Trim();
	SafeStrcpy(g_config.szLoginName, strTmp, sizeof(g_config.szLoginName));
	g_config.dwMarket = m_IniFile.GetInt( "market", 1);

	g_config.m_bWriteLog = TRUE;
	nsprintf( g_config.szLogFile, sizeof(g_config.szLogFile), "%s\\%s_log.log", g_config.szLogPath , g_config.szRunTime);

	return;
}

void LoginSuc_Ex()
{
	CString strUserFolder = "";
	strUserFolder.Format("%s\\UPIMUser\\", g_config.szHomePath);
	CreateDirectory(strUserFolder, NULL);

	// wuchao modify at 20160509 
	nsprintf( g_config.szUserDir, sizeof(g_config.szUserDir), "%s\\UPIMUser\\%s", g_config.szHomePath, /*g_MyClient.m_strUserid*/g_MyClient.m_strUserName );
	nsprintf( g_config.szUserFile, sizeof(g_config.szUserFile), "%s\\file", g_config.szUserDir );
	nsprintf( g_config.szUserImage, sizeof(g_config.szUserImage), "%s\\image", g_config.szUserDir );
	nsprintf( g_config.szUserHead, sizeof(g_config.szUserHead), "%s\\head", g_config.szUserDir );

	nsprintf( g_config.szUserConfig, sizeof(g_config.szUserConfig), "%s\\UserConfig.ini", g_config.szUserDir );
	CreateDirectory(g_config.szUserDir, NULL);
	CreateDirectory(g_config.szUserFile, NULL);
	CreateDirectory(g_config.szUserImage, NULL);
	CreateDirectory(g_config.szUserHead, NULL);

	//�û���¼�ɹ�֮�����־ д���Լ�Ŀ¼��
	//nsprintf( g_config.szLogFile, sizeof(g_config.szLogFile), "%s\\UPIM.log", g_config.szUserDir );
	InitSQLITE();

	LoadUserConfig();
}

VOID LoadUserConfig()
{
	CIniFile m_IniFile;
	m_IniFile.SetFileName(g_config.szUserConfig);
	CString strTmp = _T("");
	// ������������
	m_IniFile.SetAppName("SOUND");
	g_userconfig.m_bMsgSound = m_IniFile.GetInt("MsgSound", 1);
	g_userconfig.m_bNotifySound = m_IniFile.GetInt("NotifySound", 1);
	g_userconfig.m_bOnlineSound = m_IniFile.GetInt("OnlineSound", 1);
	g_userconfig.m_bShakeSound = m_IniFile.GetInt("ShakeSound", 1);

	// ���ر�������
	m_IniFile.SetAppName("BACKGROUND");
	g_userconfig.m_bkInfo.m_nBkType = m_IniFile.GetInt("BkType", 0);
	g_userconfig.m_bkInfo.m_nBkIndex = m_IniFile.GetInt("BkIndex", 0);
	m_IniFile.GetString(strTmp, "BkColor", "");
	g_userconfig.m_bkInfo.dwBackColor = (DWORD)_atoi64(strTmp);

	// ������������
	m_IniFile.SetAppName("FONT");
	m_IniFile.GetString(strTmp, "FontName", "΢���ź�");
	g_userconfig.m_fontInfo.m_strName = strTmp;
	g_userconfig.m_fontInfo.m_nSize = m_IniFile.GetInt("FontSize", 9);
	m_IniFile.GetString(strTmp, "FontColor", "");
	g_userconfig.m_fontInfo.m_clrText = atol(strTmp);
	g_userconfig.m_fontInfo.m_bBold = m_IniFile.GetInt("Bold", 0);
	g_userconfig.m_fontInfo.m_bItalic = m_IniFile.GetInt("Italic", 0);
	g_userconfig.m_fontInfo.m_bUnderLine = m_IniFile.GetInt("UnderLine", 0);

	g_userconfig.m_nNickType = 0;
}

VOID SaveUserConfig()
{
	CIniFile m_IniFile;
	m_IniFile.SetFileName(g_config.szUserConfig);
	CString strTmp = _T("");
	// ������������
	m_IniFile.SetAppName("SOUND");
	m_IniFile.PutInt(g_userconfig.m_bMsgSound, "MsgSound");
	m_IniFile.PutInt(g_userconfig.m_bNotifySound, "NotifySound");
	m_IniFile.PutInt(g_userconfig.m_bOnlineSound, "OnlineSound");
	m_IniFile.PutInt(g_userconfig.m_bShakeSound, "ShakeSound");

	// ���汳������
	m_IniFile.SetAppName("BACKGROUND");
	m_IniFile.PutInt(g_userconfig.m_bkInfo.m_nBkType, "BkType");
	m_IniFile.PutInt(g_userconfig.m_bkInfo.m_nBkIndex, "BkIndex");
	strTmp.Format("%u", g_userconfig.m_bkInfo.dwBackColor);
	m_IniFile.PutString(strTmp, "BkColor");

	// ������������
	m_IniFile.SetAppName("FONT");
	m_IniFile.PutString((LPCSTR)g_userconfig.m_fontInfo.m_strName.c_str(), "FontName");
	m_IniFile.PutInt(g_userconfig.m_fontInfo.m_nSize, "FontSize");
	strTmp.Format("%u", g_userconfig.m_fontInfo.m_clrText);
	m_IniFile.PutString(strTmp, "FontColor");
	m_IniFile.PutInt(g_userconfig.m_fontInfo.m_bBold, "Bold");
	m_IniFile.PutInt(g_userconfig.m_fontInfo.m_bItalic, "Italic");
	m_IniFile.PutInt(g_userconfig.m_fontInfo.m_bUnderLine, "UnderLine");

	return;
}

//
UINT PlaySoundThread(void* l)
{
	BOOL result=FALSE;
	result = ::PlaySound((LPCSTR)l, NULL, /*SND_MEMORY*/SND_MEMORY | SND_NOSTOP);
	return result;
}

void WriteUserLog(const char *fmt, ...)
{
	if(!g_config.m_bWriteLog) 
		return;
	static char tmp[1024*4] = {0};
	SYSTEMTIME  nowtime;
	GetLocalTime( &nowtime );	
	va_list arg_ptr;
	va_start(arg_ptr, fmt);
	_vsnprintf(tmp, sizeof(tmp)-1, fmt, arg_ptr);
	va_end(arg_ptr);
	CString strTmp = _T("");
	strTmp.Format("%04d-%02d-%02d %02d:%02d:%02d,%03d %s\r\n", nowtime.wYear, nowtime.wMonth, nowtime.wDay, nowtime.wHour, nowtime.wMinute, nowtime.wSecond, nowtime.wMilliseconds, tmp);

	CFile file;
	if(!file.Open(g_config.szLogFile, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite|CFile::shareDenyNone))
		return ;
	file.SeekToEnd();
	file.Write(strTmp,strTmp.GetLength());
	file.Flush();
	file.Close();
}

void WriteUserLog_Ex(const char *fmt, ...)
{
	if(!g_config.m_bWriteLog) return;
	static char tmp[1024*4] = {0};
	SYSTEMTIME  nowtime;
	GetLocalTime( &nowtime );	
	va_list arg_ptr;
	va_start(arg_ptr,fmt);
	_vsnprintf(tmp,sizeof(tmp)-1,fmt,arg_ptr);
	va_end(arg_ptr);
	CString strTmp = _T("");
	strTmp.Format("%04d-%02d-%02d %02d:%02d:%02d,%03d %s\r\n", nowtime.wYear, nowtime.wMonth, nowtime.wDay, nowtime.wHour, nowtime.wMinute, nowtime.wSecond, nowtime.wMilliseconds, tmp);
	
	g_fileLock.Lock();
	g_fileUserLog.SeekToEnd();
	g_fileUserLog.Write(strTmp,strTmp.GetLength());
	g_fileUserLog.Flush();
	g_fileLock.Unlock();
}

bool TestFileExist(CString filename)
{
	CFile tmpFile1;
	if(!tmpFile1.Open(filename, CFile::modeRead|CFile::shareDenyNone))
		return false;
	tmpFile1.Close();
	return true;
}

CString IntToStr(int nVal)
{
	CString strRet;
	char buff[10];

	_itoa(nVal, buff, 10);
	strRet = buff;
	return strRet;
}

void MD5StringTo32(char *p, char *pRet/*32*/)
{
	MD5_CTX context;
	unsigned char digest[16];
	unsigned int len = strlen (p);
	char pRetTmp[36] = {0}; 

	MD5Init (&context);
	MD5Update (&context, (unsigned char*)p, len);
	MD5Final (digest, &context);

	for (int i = 0; i < 16; i++)
	{
		sprintf(pRetTmp + 2*i, "%02x", (unsigned char)digest[i]);
		sprintf(pRetTmp + 2*i+1, "%02x", (unsigned char)(digest[i]<<4));
	}
	strncpy(pRet, pRetTmp, 32);
	pRet[32] = 0;
	return;
}

// ��ȫ�ַ������
inline int SafeSprintf
	(
	LPSTR p_lpszString,			// [out]���������
	long p_nStringSize,			// [in]�����������С
	LPCSTR p_lpcszFormat,		// [in]�����ʽ
	...							// [in]�������
	)
{
	if ( p_nStringSize <= 0 ) return 0;
	va_list args;
	va_start( args, p_lpcszFormat );
	int nRet = _vsnprintf( p_lpszString, p_nStringSize, p_lpcszFormat, args );
	if ( (nRet < 0) || (nRet == p_nStringSize) )
	{
		p_lpszString[p_nStringSize-1] = '\0';
		nRet = p_nStringSize - 1;
	}
	va_end( args );
	return nRet;
}

void TestJson()
{
	CHAR szKhh[1024*4] = {0};
	CHAR szParam_Get[1024*4] = {0};
	memset(szParam_Get, 0x00, sizeof(szParam_Get));
	SafeSprintf( szParam_Get, sizeof(szParam_Get), 
		"{\"ErrorType\": 0, \"MsgCode\": 0, \"MsgInfo\": \"\", \"ItemNum\": 1, \"FileInfo\": [[\"KHSet\", 253, 33, 8192, 8192, 0, 1]], \"data\": [[\"31100123248,3200000003,3190000001\"]], \"Post\": -1}");
	
	TRACE("RECIVE DATA=%s\n",szParam_Get);
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(szParam_Get, value))
	{
		int i = 0;
		Json::Value data_value = value["data"];
		CString strMsg_Title	= data_value[0][0].asCString();

		SafeSprintf( szKhh, sizeof(szKhh), strMsg_Title);
		CString strKhhId;

		char seps[]   = ",";
		char *token = strtok(szKhh,seps);
		while( token != NULL )     
		{
			strKhhId.Format("%s",token);
			//////////////////////////////////////////////////////////////////////////
			token = strtok(NULL,seps); 
		}		
	}
}

int InsertVtUser(vector<GUSER_INFO> &mvt, GUSER_INFO m_info)
{
	std::vector<GUSER_INFO>::iterator iter_info;
	for (iter_info = mvt.begin(); iter_info != mvt.end(); iter_info++)
	{
		if (iter_info->m_nUserType == m_info.m_nUserType
			&& strcmp(iter_info->m_szIMID, m_info.m_szIMID) == 0)
		{
			iter_info->userstate = m_info.userstate;
			return 0;
		}
	}
	mvt.push_back(m_info);
	return 0;
}

int DeleteVtUser(vector<GUSER_INFO> &mvt, GUSER_INFO m_info)
{
	std::vector<GUSER_INFO>::iterator iter_info;
	for (iter_info = mvt.begin(); iter_info != mvt.end(); iter_info++)
	{
		if (iter_info->m_nUserType == m_info.m_nUserType
			&& strcmp(iter_info->m_szIMID, m_info.m_szIMID) == 0)
		{
			mvt.erase(iter_info);
			return 1;
		}
	}
	return 0;
}

CString UTF8Convert(CString &str,int sourceCodepage,int targetCodepage)
{
	int unicodeLen = MultiByteToWideChar(sourceCodepage, 0, str, -1, NULL, 0);
	wchar_t * pUnicode; 
	pUnicode = new wchar_t[unicodeLen+1]; 
	memset(pUnicode, 0, (unicodeLen+1) * sizeof(wchar_t)); 
	MultiByteToWideChar(sourceCodepage, 0, str, -1, (LPWSTR)pUnicode, unicodeLen); 
	BYTE * pTargetData = NULL; 
	int targetLen = 0;
	targetLen = WideCharToMultiByte(targetCodepage, 0, (LPWSTR)pUnicode, -1, (char *)pTargetData, 0, NULL, NULL); 
	pTargetData = new BYTE[targetLen+1];
	memset(pTargetData, 0, targetLen+1);
	WideCharToMultiByte(targetCodepage, 0, (LPWSTR)pUnicode, -1, (char *)pTargetData, targetLen, NULL, NULL); 
	CString rt = _T("");
	rt.Format("%s", pTargetData); 
	delete pUnicode; 
	delete pTargetData; 
	return rt; 
}


long Base64_Encode(BYTE *pRawData, long nRawDataLen, BYTE *pResultBuf, long nMaxResultBufLen, BOOL bEncode)
{
	if(nMaxResultBufLen < 0)
		return -1;
	memset(pResultBuf, 0, nMaxResultBufLen);
	int i;
	if(bEncode)
	{
		CByteArray array, res_array;
		for (i=0; i<nRawDataLen; i++)
			array.Add(pRawData[i]);

		CBase64Coding base64coding;
		if (!base64coding.Encode(array, res_array))
			return -1;
		int nRet = res_array.GetSize();
		if(nMaxResultBufLen < nRet)
			return -1;
		for (i=0; i<nRet; i++)
			pResultBuf[i] = res_array.GetAt(i);
		return nRet;
	}
	else
	{
		CByteArray array, res_array;
		for (i=0; i<nRawDataLen; i++)
			array.Add(pRawData[i]);

		CBase64Coding base64coding;
		if (!base64coding.Decode(array, res_array))
			return -1;
		int nRet = res_array.GetSize();
		if(nMaxResultBufLen<nRet)
			return -1;
		for (i=0; i<nRet; i++)
			pResultBuf[i] = res_array.GetAt(i);
		return nRet;
	}
	return -1;
}

CClientPackage * CreatePackage(unsigned short protocol)
{
	CClientPackage *p=new CClientPackage;
	if(p==NULL)	return NULL;
	PACKAGE_HEADER ich;
	ich.protocolid=protocol;
	p->SetHeader(&ich);
	return p;
}

int CaculateAshValue(int & nR, int & nG, int & nB)  
{  
	return (nR*299+nG*587+nB*114+500)/1000;   //+500��Ϊ����������  
}

BOOL CreateGrayPngFromColorPng(LPCTSTR lpColorPath, LPCTSTR lpGrayImagePath)  
{  
	if (NULL == lpColorPath || lpColorPath[0] == 0 || NULL == lpGrayImagePath)  
	{  
		return FALSE;  
	}  

	USES_CONVERSION;  
	Bitmap Bitmap(T2W(lpColorPath));  
	Status res = Bitmap.GetLastStatus();  
	if (res != Gdiplus::Ok)  
	{  
		return FALSE;  
	}  
	Color pixelColor;  
	//�޸�R,G,Bֵ  
	int nCalHeight = Bitmap.GetHeight() ;   
	int nCalWidth = Bitmap.GetWidth() ;   
	for (int y = 0; y < nCalHeight; y++)  
	{  
		for (int x = 0; x < nCalWidth; x++)  
		{  
			Bitmap.GetPixel(x, y, &pixelColor);  
			int lA = pixelColor.GetA();  
			int lR = pixelColor.GetR();  
			int lG = pixelColor.GetG();  
			int lB = pixelColor.GetB();  

			if (lA > 0)  
			{  
				int nAshValue = CaculateAshValue(lR, lG, lB);  
				COLORREF crFill = RGB(nAshValue, nAshValue, nAshValue);  
				Bitmap.SetPixel(x, y, Color::MakeARGB(lA, nAshValue, nAshValue, nAshValue));     
			}                 
		}  
	}  

	CLSID bmpClsid;  
	if (!GetEncoderClsid(L"image/png", &bmpClsid))  
	{  
		_ASSERT(FALSE);  
		return FALSE;  
	}  

	Bitmap.Save(T2W(lpGrayImagePath), &bmpClsid, NULL);  

	return TRUE;  
} 

BOOL GDIPlus_CombineImage(const WCHAR *format, WCHAR* strDestImage,	WCHAR* strSrcImage1,WCHAR* strSrcImage2)
{
	BOOL bCombine = FALSE;
	int nRet = 0;
	CLSID clsid;
	nRet= GetEncoderClsid(format,&clsid);
	if (nRet >= 0)
	{
		Bitmap srcbmp1(strSrcImage1);
		Bitmap srcbmp2(strSrcImage2);

		int nWidth = 0, nHeight = 0;
		nWidth = srcbmp1.GetWidth(); 
		nHeight= srcbmp1.GetHeight();
		//�߲��䣬��*2��ˮƽ�ϲ�
		Bitmap bmpCombine(2*nWidth,nHeight);
		Graphics * pGraphics = NULL;
		pGraphics = Graphics::FromImage(&bmpCombine);
		if (pGraphics!=NULL)
		{
			//��srcbmp1��������pGraphics��
			pGraphics->DrawImage(&srcbmp1,0,0);
			//��srcbmp2��������pGraphics��
			pGraphics->DrawImage(&srcbmp2,nWidth,0);

			//����ͼƬbmpCombine��·��strDestImage
			bmpCombine.Save(strDestImage,&clsid,NULL);
			bCombine = TRUE;
		}
	}
	return bCombine;
}

void SetPictureAlpha(LPCTSTR lpOriFilePath, LPCTSTR FileName1, float f_a)
{
	USES_CONVERSION;

	//////////////////////////////////////////////////////////////////////////
	// ����BK
	CString strBkImg = "";
	strBkImg.Format("%s\\%s", g_config.szUserDisplay, "bk.png");
	Bitmap srcbmp_bk(T2W(strBkImg));

	ColorMatrix colorMartrix = 
	{  
		1,	0,	0,	0,	0,  
		0,	1,	0,	0,	0,  
		0,	0,	1,	0,	0,  
		0,	0,	0,	f_a,0,  
		0,	0,	0,	0,	1
	};

	int nWidth = srcbmp_bk.GetWidth();
	int nHight = srcbmp_bk.GetHeight();
	Rect rect(0, 49, nWidth, nHight);

	ImageAttributes imageAtt;  
	imageAtt.SetColorMatrix(&colorMartrix);  
	
	//////////////////////////////////////////////////////////////////////////
	// ԭͼƬ
	Bitmap srcbmp_old(T2W(lpOriFilePath));
	int noldWidth = srcbmp_old.GetWidth();
	int noldHight = srcbmp_old.GetHeight();

	//////////////////////////////////////////////////////////////////////////
	// �ϲ����ͼƬ
	Bitmap bmpCombine(noldWidth,noldHight);
	Graphics* pGraphics = NULL;
	pGraphics = Graphics::FromImage(&bmpCombine);

	pGraphics->DrawImage(&srcbmp_old, 0, 0);
	pGraphics->DrawImage(&srcbmp_bk, rect, 0, 0, nWidth, nHight, UnitPixel, &imageAtt);

	CLSID bmpClsid;  
	if (!GetEncoderClsid(L"image/png", &bmpClsid))
	{  
		_ASSERT(FALSE);  
		return;  
	}  

	bmpCombine.Save(T2W(FileName1), &bmpClsid, NULL);  

	if ( NULL != pGraphics ) 
	{
		delete pGraphics;
		pGraphics = NULL;
	}
	return;   
}  

bool GetEncoderClsid(const WCHAR* pszFormat, CLSID* pClsid)
{
	UINT  unNum = 0;          // number of image encoders
	UINT  unSize = 0;         // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;

	// How many encoders are there?
	// How big (in bytes) is the array of all ImageCodecInfo objects?
	GetImageEncodersSize( &unNum, &unSize );
	if ( 0 == unSize ) {
		return false;  // Failure
	}

	// Create a buffer large enough to hold the array of ImageCodecInfo
	// objects that will be returned by GetImageEncoders.
	pImageCodecInfo = (ImageCodecInfo*)( malloc(unSize) );
	if ( !pImageCodecInfo ) {
		return false;  // Failure
	}

	// GetImageEncoders creates an array of ImageCodecInfo objects
	// and copies that array into a previously allocated buffer. 
	// The third argument, imageCodecInfos, is a pointer to that buffer. 
	GetImageEncoders( unNum, unSize, pImageCodecInfo );

	for ( UINT j = 0; j < unNum; ++j ) {
		if ( wcscmp( pImageCodecInfo[j].MimeType, pszFormat ) == 0 ) {
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			pImageCodecInfo = NULL;
			return true;  // Success
		}    
	}

	free( pImageCodecInfo );
	pImageCodecInfo = NULL;
	return false;  // Failure
}

// ������ѹ��
bool CompressImagePixel(const WCHAR* pszOriFilePath, const WCHAR* pszDestFilePah, UINT ulNewHeigth, UINT ulNewWidth, WCHAR* pszFormat/* = L"image/jpeg"*/)
{
	// Initialize GDI+.
	// ����״̬
	Status stat = GenericError;

	// Get an image from the disk.
	Image* pImage = new Image(pszOriFilePath);

	do {
		if ( NULL == pImage ) {
			break;
		}

		// ��ȡ����
		UINT unOriHeight = pImage->GetHeight();
		UINT unOriWidth = pImage->GetWidth();

		do {
			CLSID encoderClsid;
			if ( unOriWidth < 1 || unOriHeight < 1 ) {
				break;
			}

			// Get the CLSID of the JPEG encoder.
			if ( !GetEncoderClsid(pszFormat, &encoderClsid) ) {
				break;
			}

			REAL fSrcX = 0.0f;
			REAL fSrcY = 0.0f;
			REAL fSrcWidth = (REAL) unOriWidth;
			REAL fSrcHeight = (REAL) unOriHeight ;
			RectF RectDest( 0.0f, 0.0f, (REAL)ulNewWidth, (REAL)ulNewHeigth);

			Bitmap* pTempBitmap = new Bitmap( ulNewWidth, ulNewHeigth );
			Graphics* graphics = NULL;

			do {
				if ( !pTempBitmap ) {
					break;
				}

				graphics = Graphics::FromImage( pTempBitmap );
				if ( !graphics ) {
					break;
				}

				stat = graphics->SetInterpolationMode(Gdiplus::InterpolationModeHighQuality);
				if ( Ok != stat ) {
					break;
				}

				stat = graphics->SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
				if ( Ok != stat ) {
					break;
				}

				stat = graphics->DrawImage( pImage, RectDest, fSrcX, fSrcY, fSrcWidth, fSrcHeight,
					UnitPixel, NULL, NULL, NULL);
				if ( Ok != stat ) {
					break;
				}

				stat = pTempBitmap->Save( pszDestFilePah, &encoderClsid, NULL );
				if ( Ok != stat ) {
					break;
				}

			} while(0);

			if ( NULL != graphics ) {
				delete graphics;
				graphics = NULL;
			}

			if ( NULL != pTempBitmap ) {
 				delete pTempBitmap;
 				pTempBitmap = NULL;
			}
		} while(0);
	} while (0);

	if ( pImage ) 
	{
		delete pImage;
		pImage = NULL;
	}

	return ( ( Ok == stat ) ? true : false );
}

// ������ѹ��
bool CompressImageQuality(const WCHAR* pszOriFilePath, const WCHAR* pszDestFilePah, ULONG quality)
{
	// copy from http://msdn.microsoft.com/en-us/library/ms533844(v=VS.85).aspx
	// Initialize GDI+.
	Status stat = GenericError;
	// Get an image from the disk.
	Image* pImage = new Image(pszOriFilePath);

	do {
		if ( NULL == pImage ) {
			break;
		}

		// ��ȡ����
		UINT ulHeight = pImage->GetHeight();
		UINT ulWidth = pImage->GetWidth();
		if ( ulWidth < 1 || ulHeight < 1 ) {
			break;
		}

		// Get the CLSID of the JPEG encoder.
		CLSID encoderClsid;
		if ( !GetEncoderClsid(L"image/jpeg", &encoderClsid) ) {
			break;
		}

		// The one EncoderParameter object has an array of values.
		// In this case, there is only one value (of type ULONG)
		// in the array. We will let this value vary from 0 to 100.
		EncoderParameters encoderParameters;
		encoderParameters.Count = 1;
		encoderParameters.Parameter[0].Guid = EncoderQuality;
		encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
		encoderParameters.Parameter[0].NumberOfValues = 1;
		encoderParameters.Parameter[0].Value = &quality;
		stat = pImage->Save(pszDestFilePah, &encoderClsid, &encoderParameters);
	} while(0);

	if ( pImage ) {
		delete pImage;
		pImage = NULL;
	}

	return ( ( stat == Ok ) ? true : false );
}

// ����ͼ��
// 1.��������̫���ͼ���Ȱ������ؽ���ѹ��
// 2.����ѹ��֮�����ͼƬ��С����1M�����������ѹ��
bool HandleImage(LPCTSTR lpOriFilePath, LPCTSTR lpDestFilePah)
{
	USES_CONVERSION;
	Image* pImage = new Image(T2W(lpOriFilePath));
	
	UINT ulHeigth = 0, ulWidth = 0, ulNewHeigth = 0, ulNewWidth = 0;
	ulHeigth = pImage->GetHeight();
	ulWidth = pImage->GetWidth();

	if (ulHeigth == 0 || ulWidth == 0)
		return false;
	
	// ����800��MAX_PIC_PIX�����أ��ȱ�������
	if (ulHeigth > MAX_PIC_PIX || ulWidth > MAX_PIC_PIX)
	{
		if (ulHeigth > ulWidth)
		{
			ulNewHeigth = MAX_PIC_PIX;
			ulNewWidth = (UINT)(ulWidth * ulNewHeigth / ulHeigth);
			CompressImagePixel(T2W(lpOriFilePath), T2W(lpDestFilePah), ulNewHeigth, ulNewWidth);
		}
		else
		{
			ulNewWidth = MAX_PIC_PIX;
			ulNewHeigth = (UINT)(ulHeigth * ulNewWidth / ulWidth);
			CompressImagePixel(T2W(lpOriFilePath), T2W(lpDestFilePah), ulNewHeigth, ulNewWidth);
		}
	}
	// �����С����800*1024��MAX_PIC_SIZE����������������ѹ����0-100��
	else
	{
		BOOL bCopyFile = CopyFile(lpOriFilePath, lpDestFilePah, false); 
	}

	if ( pImage ) 
	{
		delete pImage;
		pImage = NULL;
	}
	return true;
}

// ͷ��������һ�����غõ�ͷ���ȱ��62*62���أ�Ȼ����غ�ɫ80%��͸�������ֱ��������д����ȥ
bool HandleHeadImage(LPCTSTR lpOriFilePath, LPCTSTR FileName1, LPCTSTR FileName2 )
{
	USES_CONVERSION;
	CString strTemp = "";		// 62*62
	CString strHead = "";		// ���ߵ�����ͷ��
	CString strHead2 = "";		// ����ʱ�Ļһ�ͷ��
	if (strlen(g_config.szUserHead) > 0)
	{
		strTemp.Format("%s\\temp.jpg", g_config.szUserHead);
		strHead.Format("%s\\%s", g_config.szUserHead, FileName1);
		strHead2.Format("%s\\%s", g_config.szUserHead, FileName2);
	}
	// ��һ������ԭͼ��Ϊ62*62
	CompressImagePixel(T2W(lpOriFilePath), T2W(strTemp), 62, 62, L"image/png");

	// �ڶ�������62*62���ص�ͼƬ���Ϻ�ɫ������,͸����65%
	SetPictureAlpha(strTemp, strHead, (float)0.65);

	// ��������ͷ��һ�
	CreateGrayPngFromColorPng(strHead, strHead2 );
	return true;
}

bool HandleHeadImage2(LPCTSTR lpOriFilePath, LPCTSTR FileName1, LPCTSTR FileName2 )
{
	USES_CONVERSION;
	CString strHead = "";		// 62*62���ߵ�����ͷ��
	CString strHead2 = "";		// ����ʱ�Ļһ�ͷ��
	if (strlen(g_config.szUserHead) > 0)
	{
		strHead.Format("%s\\%s", g_config.szUserHead, FileName1);
		strHead2.Format("%s\\%s", g_config.szUserHead, FileName2);
	}
	// ��һ������ԭͼ��Ϊ62*62
	CompressImagePixel(T2W(lpOriFilePath), T2W(strHead), 62, 62, L"image/png");

	// �ڶ�����ͷ��һ�
	CreateGrayPngFromColorPng(strHead, strHead2 );
	return true;
}


bool HandleHeadImage3(LPCTSTR lpOriFilePath, LPCTSTR FileName1, LPCTSTR FileName2 )
{
	USES_CONVERSION;

	// ��һ������ԭͼ��Ϊ62*62
	CompressImagePixel(T2W(lpOriFilePath), T2W(FileName1), 62, 62, L"image/png");

	// �ڶ�����ͷ��һ�
	CreateGrayPngFromColorPng(FileName1, FileName2 );
	return true;
}


CString HrToMessage( HRESULT hr )  
{  
	LPVOID lpMsgBuf;  
	CString strTmp;  
	::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER |  
		FORMAT_MESSAGE_FROM_SYSTEM,  
		NULL,  
		hr,  
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),  
		(LPTSTR) &lpMsgBuf,  
		0,  
		NULL );  
	strTmp.Format( _T("%s"), (char *) lpMsgBuf );  
	::LocalFree( lpMsgBuf );  
	return strTmp;  
}  

BOOL IsHasRights(int nRight)
{
	int nEndDate = -1;
	nEndDate = m_mapCilentRights[nRight];
	if (nEndDate < 1)
		return FALSE;
	else
	{
		SYSTEMTIME  nowtime;
		GetLocalTime( &nowtime );
		int nYear = nEndDate/10000;
		int nMonth = (nEndDate%10000)/100;
		int nDay = nEndDate%100;

		if (nowtime.wYear > nYear)
			return FALSE;
		else if (nowtime.wYear < nYear)
			return TRUE;
		else
		{
			if (nowtime.wMonth > nMonth)
				return FALSE;
			else if (nowtime.wMonth < nMonth)
				return TRUE;
			else
			{
				if (nowtime.wDay > nDay)
					return FALSE;
			}
		}
	}
	return TRUE;
}


// ��ȡ��ǰʱ��   
void GetCurrentDate(CString &year ,CString &month ,CString &day)
{
	CString str; //��ȡϵͳʱ��
	CTime tm;
	tm=CTime::GetCurrentTime();   
	str=tm.Format("%Y-%m-%d");
	year = tm.Format("%Y") ; 
	month = tm.Format("%m") ; 
	day = tm.Format("%d") ; 

}

// ������������ 
BOOL SortByName(const ROOMANALYS_INFO &data1,const ROOMANALYS_INFO &data2)
{
	if( strcmp(data1.m_szAnalysName,data2.m_szAnalysName) < 0 ) 
	{
		return TRUE ; 
	}
	else
	{
		return FALSE ; 
	}
	//return true; 
}

// ���ߵķ���ʦ�����߷���ʦǰ�棬 ���߲��ֺ����߲��ֶ������������� 
extern BOOL SortByNameAndOnline(const ROOMANALYS_INFO &data1,const ROOMANALYS_INFO &data2)
{
	int data1Online = (data1.m_bIsOnLine)?(1):(0) ; 
	int data2Online = (data2.m_bIsOnLine)?(1):(0) ;

	if( data1Online != data2Online )
	{
		if( data1Online > data2Online )
			return TRUE ; 
		else 
			return FALSE ;
	}
	else
	{
		return strcmp(data1.m_szAnalysName,data2.m_szAnalysName) < 0 ; 
	}

}

BOOL SortByNameAndOnlineClient(const USER_ROOMCLIENT_INFO &data1,const USER_ROOMCLIENT_INFO &data2) 
{
	int data1Online = (data1.m_bIsOnLine)?(1):(0) ; 
	int data2Online = (data2.m_bIsOnLine)?(1):(0) ;

	if( data1Online != data2Online )
	{
		if( data1Online > data2Online )
			return TRUE ; 
		else 
			return FALSE ;
	}
	else
	{
		return strcmp(data1.m_szUPID,data2.m_szUPID) < 0 ; 
	}

}

extern USER_ROOMCLIENT_INFO* FindClientInRoom(CString strName)
{
	std::vector<USER_ROOMCLIENT_INFO>::iterator itBegin ,itEnd ;
	USER_ROOMCLIENT_INFO* pClientNode ; 

	itBegin = m_vtRoomClient.begin() ; 
	while( itBegin != m_vtRoomClient.end() )
	{
		// �ҵ��˾��˳� 
		if( strcmp( itBegin->m_szUPID ,strName.GetBuffer()) == 0 )
		{
			pClientNode = &(*itBegin) ; 
			return pClientNode ; 
			break ; 
		}
		itBegin++ ; 
	}
	return NULL; 
}
// �ͻ���  �ҵ������ΪnRoomID�ķ���ʦ ���ط���ʦ�ڵ��ָ�� 
void FindAnalysInRoom(int nRoomID ,ALLCLIENT_ROOM_INFO &retClientRoom) 
{
	ACRI_ITER itBegin = m_mapAllClientRoom.begin() ;
	ALLCLIENT_ROOM_INFO pNode  ; 
	memset(&pNode ,0,sizeof(ALLCLIENT_ROOM_INFO)) ; 

	while( itBegin != m_mapAllClientRoom.end() )
	{
		pNode = itBegin->second ; 
		if(pNode.m_nRoomID == nRoomID )
		{
			retClientRoom = pNode ;
			break ; 
		}
		itBegin++ ; 
	} 
}

// ���ͻ���¼��֪ͨ����ʦ�����ߣ���Ҫ����m_vtRoomClient���ÿͻ�����״̬
// strClientName �ͻ����� 
// bUserState    �ͻ��Ƿ����� 
void SetClientOnLine(CString strClientName,bool bUserState) 
{
	USER_ROOMCLIENT_INFO clientInfo ; 
	memset(&clientInfo ,0,sizeof(USER_ROOMCLIENT_INFO)) ; 
	COPY_USERID(clientInfo.m_szUPID,strClientName.GetBuffer())  ; 
	std::vector<USER_ROOMCLIENT_INFO>::iterator findIt = find( m_vtRoomClient.begin() ,m_vtRoomClient.end() ,clientInfo) ; 
	if( findIt != m_vtRoomClient.end() )
	{
		// �ҵ��� 
		findIt->m_bIsOnLine = bUserState ; 
	}
}


// ��mapRoomAnalys��Ѱ��strAnalysName�ķ���ʦ����ID 
int  WhitchRoomForAnalys( std::map<TGROOMID ,ALLCLIENT_ROOM_INFO> mapRoomAnalys ,CString strAnalysName)
{
	int nRoomID = 0 ; 
	std::map<TGROOMID ,ALLCLIENT_ROOM_INFO>::iterator itBegin = m_mapAllClientRoom.begin() ; 
	while( itBegin != m_mapAllClientRoom.end())
	{
		vector<ROOMANALYS_INFO>* pVtAnalysNode = itBegin->second.pVtAnalys ;
		if( !pVtAnalysNode)
		{
			return nRoomID ; 
		}
		int iCount = pVtAnalysNode->size() ; 
		if( pVtAnalysNode)
		{
			nRoomID = itBegin->first ;
			int nAnalysID = atoi(strAnalysName.GetBuffer()) ; 

			for( int index = 0 ; index < iCount ; index++)
			{
				ROOMANALYS_INFO analysInfo = (*pVtAnalysNode).at((index)) ; 
				if( analysInfo.m_nAnalysID == nAnalysID)
					return nRoomID ; 
			}
			
		}
		itBegin++ ; 
	}
	return nRoomID ; 
}


// wuchao add at 2016-03-29 
// ��ȡ�����������ߺ������û���Ϣ 
void GetClientInfoInGroup(Node*pGroupNode,std::vector<USER_ROOMCLIENT_INFO> &vecOnline ,std::vector<USER_ROOMCLIENT_INFO> &vecOffline )
{
	int iCount = m_vtRoomClient.size() ;
	for( int index = 0 ; index < iCount ;index++)
	{
		int nGroupID = atoi( pGroupNode->data().numid.GetData()) ; 
		if( nGroupID == m_vtRoomClient[index].m_nGroupID )
		{
			if( m_vtRoomClient[index].m_bIsOnLine)
			{
				vecOnline.push_back(m_vtRoomClient[index]) ;
			}
			else
			{
				vecOffline.push_back(m_vtRoomClient[index]) ;
			}
		}
	}
}


std::string _EncodeURL(  char *str) 
{
	wchar_t *Bufw = NULL ; 
	char *Bufc = NULL ; 
	char RTV[ 1024] ; 

	long needSize = MultiByteToWideChar( CP_ACP ,NULL ,str ,-1 ,NULL ,0 ) ; 

	Bufw = new wchar_t(needSize) ; 
	if( Bufw == NULL )
	{
		TRACE("new�����ڴ�ʧ��") ;  
		return " " ; 
	}

	memset(Bufw ,0x0 ,needSize * 2 ) ; 
	MultiByteToWideChar(CP_ACP ,NULL ,str ,-1 ,Bufw,needSize) ; 

	needSize = WideCharToMultiByte(CP_UTF8 ,NULL ,Bufw ,-1 ,NULL,0,NULL,NULL) ; 
	if( needSize == 0 )
	{
		if( NULL != Bufw) 
		{
			delete []Bufw ;
			Bufw = NULL ; 
		}

		if( NULL != Bufc)
		{
			delete []Bufc ; 
			Bufc = NULL ; 
		}

		return "" ; 
	}

	Bufc = new char[needSize] ; 
	if( Bufc == NULL )
	{
		if( NULL != Bufw) 
		{
			delete []Bufw ;
			Bufw = NULL ; 
		}

		if( NULL != Bufc)
		{
			delete []Bufc ; 
			Bufc = NULL ; 
		}
		return "" ;
	}

	memset(Bufc ,0x0 ,needSize ) ; 
	WideCharToMultiByte(CP_UTF8 ,NULL ,Bufw ,-1 ,Bufc ,needSize ,NULL ,NULL) ; 
	unsigned char *pWork = (unsigned char*)Bufc ; 
	memset(RTV ,0x0,sizeof(RTV) ) ; 
	if( strlen(Bufc) > 1024)
	{
		if( NULL != Bufw) 
		{
			delete []Bufw ;
			Bufw = NULL ; 
		}

		if( NULL != Bufc)
		{
			delete []Bufc ; 
			Bufc = NULL ; 
		}
		return "" ; 
	}

	while( *pWork != 0x0 ) 
	{
		if( *pWork != '!' && *pWork != '@' && *pWork != '#' &&
			*pWork != '$' && *pWork != '&' && *pWork != '*' && 
			*pWork != '(' && *pWork != ')' && *pWork != '=' &&
			*pWork != ':' && *pWork != '/' && *pWork != ';' &&
			*pWork != '?' && *pWork != '+' && *pWork != '\'' &&
			*pWork != '.' ) 
		{
			sprintf(RTV+strlen(RTV) ,"%%%2x",*pWork)  ; 
		}
		else
		{
			sprintf(RTV+strlen(RTV) ,"%c",*pWork)  ; 
		}
		pWork++ ; 
	}

	//if( NULL != Bufc)
	//{
	//	delete []Bufc ; 
	//	Bufc = NULL ; 
	//}

	//if( NULL != Bufw) 
	//{
	//	delete []Bufw ;
	//	Bufw = NULL ; 
	//}
	return RTV ; 
}
int astr_ustr( const char *ansistr, WCHAR *unicodestr )
{
	int result = 0;
	try
	{
		//size_t len = strlen( ansistr );
		int needlen = MultiByteToWideChar( CP_OEMCP, 0, ansistr, -1, NULL, 0 );
		if( needlen < 0 )
		{
			return needlen;
		}

		result = MultiByteToWideChar( CP_OEMCP, 0, ansistr, -1, unicodestr, needlen *sizeof(wchar_t) );
		if( result < 0 )
		{
			return result;
		}
		return wcslen( unicodestr );
	}
	catch( ... )
	{
		//ShowError();
	}
}