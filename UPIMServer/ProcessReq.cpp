#include "StdAfx.h"
#include "ProcessReq.h"
#include "globalvar.h"
#include "MainFrm.h"
#include "Func.h"
//////////////////////////////////////////////////////////////////////////
void ReqLogFilter(int nProtoco,DWORD dwConnID,int PacketLen)
{
#ifdef LOG_FILTER
	TCHAR szAddress[40];
	int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
	USHORT usPort;
	g_MySever.m_Server.GetRemoteAddress(dwConnID, szAddress, iAddressLen, usPort);
	if (nProtoco != UPIM_REQ_ONLINE)
	{
		OP_LOG_INFO("dwConnID:%d szAddress:%s usPort:%d send protocol %d PacketLen %d",dwConnID, szAddress,usPort,nProtoco,PacketLen);
	}
#endif
}

BOOL OnReceive_Ex(DWORD dwConnID, const BYTE* pData, int iLength)
{
	
	struct tagIMReqHeader* pHead = (struct tagIMReqHeader*)pData;
	int recvLength = pHead->PacketLen;
	short req = *(short*)(pHead + 1);
	char* pReceive = (char*)(pHead + 1);
	ReqLogFilter(req,dwConnID,recvLength);

	CString strTmp = _T("");
	strTmp.Format("%s session:%d Receive PKG:Э��[%d] (LEN:%d)", GetNowTime(), dwConnID, req, iLength );
	//LogMsg(strTmp);
	int sendLength = 0;
	CMainFrame* PMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	switch(req)
	{
	case UPIM_REQ_CHECKPWD:
		InterlockedExchange(&PMainFrame->m_bOnLineOrOffLine,TRUE);
		sendLength = OnCheckPwdReq(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_RECONNECT:
		InterlockedExchange(&PMainFrame->m_bOnLineOrOffLine,TRUE);
		sendLength = OnReConnectReq(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_GUSER:
		sendLength = OnGUserReq(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_GUSER2:
		sendLength = OnGUserReq2(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_GLIST:
		sendLength = OnGListReq(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_LIST:
		sendLength = OnListReq(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_LIST2:
		sendLength = OnListReq2(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_SENDMSG:
		sendLength = OnSendMSGReq(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_DEPT:
		sendLength = OnDeptReq(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_GCINFO:
		sendLength = OnGcInfoReq(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_GCINFO2:
		sendLength = OnGcInfoReq2(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_GCGETLIST:
		sendLength = OnGcGetListReq(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_GCSENDMSG:
		sendLength = OnGcSendMSGReq(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_GCCREATE:
		sendLength = OnGcCreateReq(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_GCADD:
		sendLength = OnGcAddReq(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_GCKICK:
		sendLength = OnGcKickReq(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_GCLEAVE:
		sendLength = OnGcLeaveReq(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_GPUBLIC:
		sendLength = OnGPublic(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_PUBLICINFO:
		sendLength = OnPublicInfo(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_PUBCONCLOSE:
		sendLength = OnPublicConClose(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_OLNOTIFY:
		sendLength = OnOLNotify(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_OFFMSG:
		sendLength = OnOFFMsgReq(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_PKG:
		sendLength = OnPkgReq(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_ALLTGROOM:
		sendLength = OnGetAllTgRoom(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_ALLTGROOMEX:
		sendLength = OnGetAllTgRoomEx(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_ALLROOMTOUSER:
		sendLength = OnGetAllRoomToUser(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_ONLINE:
		sendLength = OnGetUserState(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_GETGROUP:
		sendLength = OnGetSelfGroup(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_GETGUSER:
		sendLength = OnGetSelfGroupUsers(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_ADDGROUP:
		sendLength = OnSetSelfGroup(dwConnID, pReceive, recvLength);
		break;
	case UPIM_REQ_MODGUSER:
		sendLength = OnSetSelfGroupUser(dwConnID, pReceive, recvLength);
		break;
	default:
		break;
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//UPIM_REQ_CHECKPWD
int OnCheckPwdReq(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;		//�������ݷ��ͳ���
	char pSend[ANSBUFFER_LEN] = {0};
	login_req* m_req = (login_req *)pReceive;
	char szError[256] = {0};
	LPOPLINK pLinkInfo = NULL;

	int nLen = sizeof(login_ans);
	login_ans loginans = {0};
	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_CHECKPWD, nLen, nLen);
	
	pLinkInfo = g_LinkMangaer.GetLink(szError, sizeof(szError), TRUE);
	if (pLinkInfo == NULL)
	{
		m_ansbuf.AnsHeader.ErrorCode = erServer_Error;
		OP_LOG_ERROR("�������쳣");
		return nLenAll;
	}

	CString strICQID = _T("");
	CString strTruename = _T("");
	CString strRolename = _T("");
	CString strSex = _T("");
	CString strYYB = _T("");
	CString strSign = _T("");
	CString strPSWD = _T("");
	int nRole = 0;
	int nDept = 0;
	//////////////////////////////////////////////////////////////////////////
#ifdef IP_WHITELIST
	if (m_req->usertype == eLogin_Analyst)
	{
		TCHAR szAddress[40];
		int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
		USHORT usPort;
		g_MySever.m_Server.GetRemoteAddress(dwConnID, szAddress, iAddressLen, usPort);
		if(!IsWhiteIP(szAddress))
		{
			m_ansbuf.AnsHeader.ErrorCode = erLogin_IDNotExist;
			OP_LOG_INFO("ID:%s %s:���ڰ�����֮�ڣ�",m_req->userid,szAddress);
			memcpy(&(m_ansbuf.AnsBuffer), &loginans, nLen);
			nLenAll = sizeof(IMANSHEADER) + nLen;
			memcpy(pSend, &m_ansbuf, nLenAll);
			g_LinkMangaer.FreeLink(pLinkInfo);
			g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);
			return nLenAll;
		}
	}
#endif
	//////////////////////////////////////////////////////////////////////////
	if (m_req->usertype == eLogin_Emp || m_req->usertype == eLogin_Analyst)				//Ա����¼/����ʦ��¼
	{
		CADOCommand adoCmd(pLinkInfo->pAdodb, "icq_login_emp");
		adoCmd.AddInputParameter("@userid", strlen(m_req->userid), (CString)m_req->userid);
		adoCmd.AddInputParameter("@userpwd", strlen(m_req->userpwd), (CString)m_req->userpwd);

		CADORecordset adoRs(pLinkInfo->pAdodb);
		if(!adoRs.Execute(&adoCmd)) 
		{
			g_LinkMangaer.CheckConnect(pLinkInfo);
			m_ansbuf.AnsHeader.ErrorCode = erServer_DBError;
			TRACE("ִ�����ݿ�ʧ��");
		}
		else
		{
			long nRowCount = adoRs.GetRecordCount();
			if (nRowCount == 0)
			{
				m_ansbuf.AnsHeader.ErrorCode = erLogin_IDNotExist;
				TRACE("�û���������");
			}
			else
			{
				adoRs.GetFieldValue("pwd", strPSWD);				// psw

				if (_stricmp(m_req->userpwd, strPSWD) != 0)
				{
					m_ansbuf.AnsHeader.ErrorCode = erLogin_PswError;
					TRACE("�������");
				}
				else
				{
					adoRs.GetFieldValue("icqid", strICQID);			// icqid
					adoRs.GetFieldValue("truename", strTruename);	// name
					adoRs.GetFieldValue("role", nRole);				// role
					adoRs.GetFieldValue("sex", strSex);				// sex
					adoRs.GetFieldValue("yyb", strYYB);				// yyb
					adoRs.GetFieldValue("deptid", nDept);			// dept
					adoRs.GetFieldValue("sign", strSign);			// sign

					strICQID.Trim();
					strncpy(loginans.userid, strICQID, strICQID.GetLength());
					strTruename.Trim();
					strncpy(loginans.username, strTruename, strTruename.GetLength());
					loginans.role = (short)nRole;
					strncpy(loginans.useryyb, "1", 1);
					loginans.sex = (short)atoi(strSex);
					strncpy(loginans.yyb, strYYB, strYYB.GetLength());
					strncpy(loginans.signature, strSign, strSign.GetLength());
					loginans.deptid = (short)nDept;
				}
			}
		}
		memcpy(&(m_ansbuf.AnsBuffer), &loginans, nLen);
		nLenAll = sizeof(IMANSHEADER) + nLen;
		memcpy(pSend, &m_ansbuf, nLenAll);
	}
	else if (m_req->usertype == eLogin_Client)		//�ͻ���¼
	{
		//�ͻ��̶�����
		/*
		CString strPSWD = "!@#$%1234~_";
		if (_stricmp(m_req->userpwd, strPSWD) != 0)
		{
		m_ansbuf.AnsHeader.ErrorCode = erLogin_PswError;
		TRACE("�������");
		}
		*/

		CADOCommand adoCmd(pLinkInfo->pAdodb, "icq_login_client");
		adoCmd.AddInputParameter("@userid", strlen(m_req->userid), (CString)m_req->userid);

		CADORecordset adoRs(pLinkInfo->pAdodb);
		if(!adoRs.Execute(&adoCmd)) 
		{
			g_LinkMangaer.CheckConnect(pLinkInfo);
			m_ansbuf.AnsHeader.ErrorCode = erServer_DBError;
			TRACE("ִ�����ݿ�ʧ��");
		}
		else
		{
			if (!adoRs.IsOpen())
			{
				g_LinkMangaer.FreeLink(pLinkInfo);
				return 0;
			}
			long nRowCount = adoRs.GetRecordCount();
			if (nRowCount == 0)
			{
				m_ansbuf.AnsHeader.ErrorCode = erLogin_IDNotExist;
				TRACE("�û���������");
			}
			else
			{
				adoRs.GetFieldValue("icqid", strICQID);			// icqid
				adoRs.GetFieldValue("name", strTruename);		// name
				adoRs.GetFieldValue("sex", strSex);				// sex
				adoRs.GetFieldValue("yyb", strYYB);				// yyb

				strSign = "�ͻ�ǩ��";
				strICQID.Trim();
				strncpy(loginans.userid, strICQID, strICQID.GetLength());
				strTruename.Trim();
				strncpy(loginans.username, strTruename, strTruename.GetLength());
				loginans.role = (short)1;
				strncpy(loginans.useryyb, "1", 1);
				loginans.sex = (short)atoi(strSex);
				strncpy(loginans.yyb, strYYB, strYYB.GetLength());
				strncpy(loginans.signature, strSign, strSign.GetLength());
			}
		}
		memcpy(&(m_ansbuf.AnsBuffer), &loginans, nLen);
		nLenAll = sizeof(IMANSHEADER) + nLen;
		memcpy(pSend, &m_ansbuf, nLenAll);
	}
	else if (m_req->usertype == eLogin_EmpSpecial)	//��У�������Ա����¼
	{
		strICQID = m_req->userid;
		strncpy(loginans.userid, strICQID, strICQID.GetLength());
		strTruename.Trim();
		strncpy(loginans.username, strTruename, strTruename.GetLength());
		loginans.role = (short)1;
		strncpy(loginans.useryyb, "1", 1);
		loginans.sex = (short)atoi(strSex);
		strncpy(loginans.yyb, strYYB, strYYB.GetLength());
		strncpy(loginans.signature, strSign, strSign.GetLength());

		memcpy(&(m_ansbuf.AnsBuffer), &loginans, nLen);
		nLenAll = sizeof(IMANSHEADER) + nLen;
		memcpy(pSend, &m_ansbuf, nLenAll);
	}

	// ֪ͨ�û�����״̬
	if (m_ansbuf.AnsHeader.ErrorCode == erError_None)
	{
		//////////////////////////////////////////////////////////////////////////
		// �Ȳ��ҿ����û��Ƿ��Ѿ������ϣ��ڵĻ�����Ϣ������֪ͨ�����߳������Ͽ�����
		MYSTATE m_state = (MYSTATE)0;
		DWORD dwConnectID = 0;
		g_MongoDBMgr.GetUserState(m_req->userid, m_state, dwConnectID);
		TCHAR szAddress[40];
		int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
		USHORT usPort;

		CString strTmp = _T("");
#ifdef KICKMAN
		if (m_state == MYSTATE_NORMAL )
		{
			char pSend2_[ANSBUFFER_LEN] = {0};
			kickoff_msg kickmsg = {0};
			int nLen = sizeof(kickoff_msg);
			IMANSBUFFER m_ansbuf = {0};
			InitAnsBufHead(m_ansbuf, UPIM_REQ_KICKOFF, nLen, nLen);
			kickmsg.nMsg = 1;
			
			memcpy(&(m_ansbuf.AnsBuffer), &kickmsg, nLen);
			int nLenAll_ = sizeof(IMANSHEADER) + nLen;
			memcpy(pSend2_, &m_ansbuf, nLenAll_);
			g_MySever.m_Server.Send((CONNID)dwConnectID, (LPBYTE)pSend2_, nLenAll_);
			g_MySever.m_Server.GetRemoteAddress(dwConnectID, szAddress, iAddressLen, usPort);
			strTmp.Format("session:%d UserID:%s szAddress:%s usPort:%d ���߷��ˣ�",  dwConnectID, m_req->userid,szAddress,usPort);
			CMainFrame* pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
			InterlockedExchange(&pMainFrame->m_bOnLineOrOffLine,TRUE);			
			g_MongoDBMgr.UserLoginIn((DWORD)dwConnectID,"",FALSE);
			OP_LOG_INFO("%s",strTmp);
		}
#endif
		//////////////////////////////////////////////////////////////////////////
		g_pList->PushUSER(m_req->userid, MYSTATE_NORMAL);
		TCHAR chIp[32] = {0};
		int nIplen = 32;
		USHORT nPort = 0;
		g_MySever.m_Server.GetRemoteAddress(dwConnID, chIp, nIplen, nPort);
		strTmp.Format("session:%d UserID:%s szAddress:%s usPort:%d ��¼�ɹ�!", dwConnID, m_req->userid,chIp,nPort);
		OP_LOG_INFO("%s",strTmp);
		LogMsg(strTmp);
		g_MongoDBMgr.UserLoginIn(dwConnID, m_req->userid, TRUE, (LPCTSTR)chIp, nPort);
	}

	g_LinkMangaer.FreeLink(pLinkInfo);
	g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);
	return nLenAll;
}

//UPIM_REQ_RECONNECT
int OnReConnectReq(DWORD dwConnID, char* pReceive, ULONG leng)
{
	reconnect_req* m_req = (reconnect_req *)pReceive;
	BOOL bSussess = TRUE;

	char pSend1_[ANSBUFFER_LEN] = {0};
	reconnect_ans reconans = {0};
	int nLen1_ = sizeof(reconnect_ans);
	IMANSBUFFER m_ansbuf_reconnect = {0};
	InitAnsBufHead(m_ansbuf_reconnect, UPIM_REQ_RECONNECT, nLen1_, nLen1_);
	reconans.nResult = 0;

	// useridΪ�յ� ������
	if (strlen(m_req->userid) == 0)
	{
		OP_LOG_INFO("UPIM_REQ_RECONNECT userid is NULL");
		reconans.nErrorCode = erLogin_RC_IDNULL;
		bSussess = FALSE;

		memcpy(&(m_ansbuf_reconnect.AnsBuffer), &reconans, nLen1_);
		int nLenAll1_ = sizeof(IMANSHEADER) + nLen1_;
		memcpy(pSend1_, &m_ansbuf_reconnect, nLenAll1_);
		g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend1_, nLenAll1_);

		g_MySever.Disconnect(dwConnID, TRUE);
		return 0;
	}

	// IP��ַ�ڰ�����֮��ģ��������¼
#ifdef IP_WHITELIST
	if (m_req->nUsertype == eUser_UPAnalyst)
	{
		TCHAR szAddress[40];
		int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
		USHORT usPort;
		g_MySever.m_Server.GetRemoteAddress(dwConnID, szAddress, iAddressLen, usPort);
		if(!IsWhiteIP(szAddress))
		{
			OP_LOG_INFO("ID:%s dwConnID:%d %s:���ڰ�����֮�ڣ�",m_req->userid,dwConnID,szAddress);
			reconans.nErrorCode = erLogin_RC_IPNotAllow;
			bSussess = FALSE;

			memcpy(&(m_ansbuf_reconnect.AnsBuffer), &reconans, nLen1_);
			int nLenAll1_ = sizeof(IMANSHEADER) + nLen1_;
			memcpy(pSend1_, &m_ansbuf_reconnect, nLenAll1_);
			g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend1_, nLenAll1_);

			g_MySever.Disconnect(dwConnID, TRUE);
			return 0;
		}
	}
#endif

	// ������� T����
	if (bSussess)
	{
		MYSTATE m_state = (MYSTATE)0;
		DWORD dwConnectID = 0;
		g_MongoDBMgr.GetUserState(m_req->userid, m_state, dwConnectID);
		if (m_state == MYSTATE_NORMAL )
		{
			char pSend2_[ANSBUFFER_LEN] = {0};
			kickoff_msg kickmsg = {0};
			int nLen = sizeof(kickoff_msg);
			IMANSBUFFER m_ansbuf = {0};
			InitAnsBufHead(m_ansbuf, UPIM_REQ_KICKOFF, nLen, nLen);
			kickmsg.nMsg = 1;

			memcpy(&(m_ansbuf.AnsBuffer), &kickmsg, nLen);
			int nLenAll_ = sizeof(IMANSHEADER) + nLen;
			memcpy(pSend2_, &m_ansbuf, nLenAll_);
			g_MySever.m_Server.Send((CONNID)dwConnectID, (LPBYTE)pSend2_, nLenAll_);
		}

		//////////////////////////////////////////////////////////////////////////
		g_pList->PushUSER(m_req->userid, MYSTATE_NORMAL);
		CString strTmp = _T("");

		TCHAR szAddress[40];
		int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
		USHORT usPort;
		g_MySever.m_Server.GetRemoteAddress(dwConnID, szAddress, iAddressLen, usPort);
		strTmp.Format("session:%d ID:%s szAddress:%s usPort:%d �ص�¼�ɹ�!",  dwConnID, m_req->userid,szAddress ,usPort);
		OP_LOG_INFO("%s",strTmp);
		LogMsg(strTmp);

		TCHAR chIp[32] = {0};
		int nIplen = 32;
		USHORT nPort = 0;
		g_MySever.m_Server.GetRemoteAddress(dwConnID, chIp, nIplen, nPort);
		g_MongoDBMgr.UserLoginIn(dwConnID, m_req->userid, TRUE, (LPCTSTR)chIp, nPort);

		//////////////////////////////////////////////////////////////////////////
		// ���ͷ��ذ����ͻ���
		reconans.nResult = 1;
		memcpy(&(m_ansbuf_reconnect.AnsBuffer), &reconans, nLen1_);
		int nLenAll1_ = sizeof(IMANSHEADER) + nLen1_;
		memcpy(pSend1_, &m_ansbuf_reconnect, nLenAll1_);
		g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend1_, nLenAll1_);
	}

	return 0;
}

//UPIM_REQ_GUSER
int OnGUserReq(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;		//�������ݷ��ͳ���
	char pSend[ANSBUFFER_LEN] = {0};
	guser_req* m_req = (guser_req *)pReceive;
	char szError[256] = {0};
	LPOPLINK pLinkInfo = NULL;
	pLinkInfo = g_LinkMangaer.GetLink(szError, sizeof(szError), TRUE);
	if (pLinkInfo == NULL)
		return nLenAll;

	int nLen = 0;
	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_GUSER);
	char m_sendbuf[ANSBUFFER_LEN] = {0};
	guser_ans* guserans = (guser_ans *)m_sendbuf;
	guserans->ngroupid = m_req->ngroupid;
	guserans->ntype = m_req->ntype;

	CString strICQID = _T("");
	CString strTruename = _T("");
	CString strSex = _T("");
	CString strMobile = _T("");
	CString strSign = _T("");

	//////////////////////////////////////////////////////////////////////////
	//���ŷ���
	//�����ڹ�˾�ڲ����ŷ���
	if (m_req->ntype == eList_Dept)
	{
		CString strTmp = _T("");
		strTmp.Format("%s session:%d DEPT:%d-%d", GetNowTime(), dwConnID, m_req->ntype, m_req->ngroupid);
		LogMsg(strTmp);

		CADOCommand adoCmd(pLinkInfo->pAdodb, "icq_get_deptemp");
		// ȡ�Զ��岿�ŷ���ʱ��ngroupidʵ���������deptid
		adoCmd.AddInputParameter("@deptid", (int)m_req->ngroupid);
		CADORecordset adoRs(pLinkInfo->pAdodb);
		if(!adoRs.Execute(&adoCmd)) 
		{
			g_LinkMangaer.CheckConnect(pLinkInfo);
			m_ansbuf.AnsHeader.ErrorCode = erServer_DBError;
			TRACE("ִ�����ݿ�ʧ��");
			return nLenAll;
		}
		long nRowCount = adoRs.GetRecordCount();
		if (nRowCount > 0)
		{
			guserans->rtnnum = (short)nRowCount;
			guser_unit* m_unit = new guser_unit[nRowCount];
			long nStrucLen = sizeof(guser_unit)*nRowCount;
			memset(m_unit, 0, nStrucLen);

			for(long nIdx=0; nIdx<nRowCount; nIdx++,adoRs.MoveNext())	
			{
				adoRs.GetFieldValue("icqid", strICQID);			// icqid
				adoRs.GetFieldValue("truename", strTruename);	// name
				adoRs.GetFieldValue("sex", strSex);				// sex
				adoRs.GetFieldValue("mobile", strMobile);		// mobile
				adoRs.GetFieldValue("sign", strSign);			// sign

				strICQID.Trim();
				strncpy(m_unit[nIdx].userid, strICQID, strICQID.GetLength());
				strTruename.Trim();
				strncpy(m_unit[nIdx].username, strTruename, strTruename.GetLength());
				m_unit[nIdx].sex = (short)atoi(strSex);
				strMobile.Trim();
				strncpy(m_unit[nIdx].mobile, strMobile, strMobile.GetLength());
				strSign.Trim();
				strncpy(m_unit[nIdx].signature, strSign, strSign.GetLength());

				MYSTATE m_state = (MYSTATE)0;
				DWORD dwConnectID = 0;
				g_MongoDBMgr.GetUserState(strICQID, m_state, dwConnectID);
				m_unit[nIdx].state = (short)m_state;							// ����״̬��Ҫ���⴦��
			}
			memcpy(guserans->headp, m_unit, nStrucLen);
			nLen = sizeof(guser_ans) + sizeof(guser_unit)*(nRowCount-1);
			m_ansbuf.AnsHeader.PacketLen	= nLen;
			m_ansbuf.AnsHeader.RawLen		= nLen;
			TDEL(m_unit);
		}
		else	//nRowCountΪ0
		{
			guserans->rtnnum = 0;
			nLen = sizeof(guser_ans);
			m_ansbuf.AnsHeader.PacketLen	= nLen;
			m_ansbuf.AnsHeader.RawLen		= nLen;
		}
		memcpy(&(m_ansbuf.AnsBuffer), guserans, nLen);
		nLenAll = sizeof(IMANSHEADER) + nLen;
		memcpy(pSend, &m_ansbuf, nLenAll);
	}

	//////////////////////////////////////////////////////////////////////////
	//�ͻ�����
	//��relation����ȡ�ø÷�����Ա�Ŀͻ�
	else if (m_req->ntype == eList_ClientGrp)
	{
		CADOCommand adoCmd(pLinkInfo->pAdodb,"icq_get_client2");
		adoCmd.AddInputParameter("@userid", strlen(m_req->userid), (CString)m_req->userid);
		CADORecordset adoRs(pLinkInfo->pAdodb);

		if(!adoRs.Execute(&adoCmd)) 
		{
			g_LinkMangaer.CheckConnect(pLinkInfo);
			m_ansbuf.AnsHeader.ErrorCode = erServer_DBError;
			TRACE("ִ�����ݿ�ʧ��");
		}
		long nRowCount = adoRs.GetRecordCount();

		if (nRowCount > 0)
		{
			guserans->rtnnum = (short)nRowCount;
			guser_unit* m_unit = new guser_unit[nRowCount];
			long nStrucLen = sizeof(guser_unit)*nRowCount;
			memset(m_unit, 0, nStrucLen);

			for(long nIdx=0; nIdx<nRowCount; nIdx++,adoRs.MoveNext())	
			{
				adoRs.GetFieldValue("icqid", strICQID);			// icqid
				adoRs.GetFieldValue("name", strTruename);		// name
				adoRs.GetFieldValue("sex", strSex);				// sex

				strICQID.Trim();
				strncpy(m_unit[nIdx].userid, strICQID, strICQID.GetLength());
				strTruename.Trim();
				strncpy(m_unit[nIdx].username, strTruename, strTruename.GetLength());
				m_unit[nIdx].sex = (short)atoi(strSex);

				MYSTATE m_state = (MYSTATE)0;
				DWORD dwConnectID = 0;
				g_MongoDBMgr.GetUserState(strICQID, m_state, dwConnectID);
				m_unit[nIdx].state = (short)m_state;							// ����״̬��Ҫ���⴦��
			}
			memcpy(guserans->headp, m_unit, nStrucLen);
			nLen = sizeof(guser_ans) + sizeof(guser_unit)*(nRowCount-1);
			m_ansbuf.AnsHeader.PacketLen	= nLen;
			m_ansbuf.AnsHeader.RawLen		= nLen;
			TDEL(m_unit);
		}
		else	//nRowCountΪ0
		{
			guserans->rtnnum = 0;
			nLen = sizeof(guser_ans);
			m_ansbuf.AnsHeader.PacketLen	= nLen;
			m_ansbuf.AnsHeader.RawLen		= nLen;
		}
		memcpy(&(m_ansbuf.AnsBuffer), guserans, nLen);
		nLenAll = sizeof(IMANSHEADER) + nLen;
		memcpy(pSend, &m_ansbuf, nLenAll);
	}
	g_LinkMangaer.FreeLink(pLinkInfo);
	g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);
	return nLenAll;
}

//UPIM_REQ_GUSER2
int OnGUserReq2(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;		//�������ݷ��ͳ���
	char pSend[ANSBUFFER_LEN] = {0};
	guser_req* m_req = (guser_req *)pReceive;
	char szError[256] = {0};
	LPOPLINK pLinkInfo = NULL;
	pLinkInfo = g_LinkMangaer.GetLink(szError, sizeof(szError), TRUE);
	if (pLinkInfo == NULL)
		return nLenAll;

	int nLen = 0;
	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_GUSER2);

	char m_sendbuf[ANSBUFFER_LEN] = {0};
	guser_ans2* guserans = (guser_ans2 *)m_sendbuf;
	guserans->ngroupid = m_req->ngroupid;
	guserans->ntype = m_req->ntype;

	CString strICQID = _T("");
	CString strTruename = _T("");
	CString strSex = _T("");
	CString strMobile = _T("");
	CString strSign = _T("");

	// json
	Value data_value;
	
	Value array;
	FastWriter writer;
	string strdata;

	int packlen = 0;
	int nIndex = 0;

	CString strTmp = _T("");
	strTmp.Format("%s session:%d DEPT:%d-%d", GetNowTime(), dwConnID, m_req->ntype, m_req->ngroupid);
	LogMsg(strTmp);

	//////////////////////////////////////////////////////////////////////////
	//���ŷ���
	//�����ڹ�˾�ڲ����ŷ���
	if (m_req->ntype == eList_Dept)
	{
		CADOCommand adoCmd(pLinkInfo->pAdodb, "icq_get_deptemp");
		// ȡ�Զ��岿�ŷ���ʱ��ngroupidʵ���������deptid
		adoCmd.AddInputParameter("@deptid", (int)m_req->ngroupid);
		CADORecordset adoRs(pLinkInfo->pAdodb);

		if(!adoRs.Execute(&adoCmd)) 
		{
			g_LinkMangaer.CheckConnect(pLinkInfo);
			m_ansbuf.AnsHeader.ErrorCode = erServer_DBError;
			TRACE("ִ�����ݿ�ʧ��");
			return nLenAll;
		}
		//JSON
		long nRowCount = adoRs.GetRecordCount();
		if (nRowCount > 0)
		{
			for(long nIdx=0; nIdx<nRowCount; nIdx++,adoRs.MoveNext())
			{
				Value item;
				adoRs.GetFieldValue("icqid", strICQID);			// icqid
				strICQID.Trim();
				adoRs.GetFieldValue("truename", strTruename);	// name
				strTruename.Trim();
				adoRs.GetFieldValue("sex", strSex);				// sex
				adoRs.GetFieldValue("mobile", strMobile);		// mobile
				strMobile.Trim();
				adoRs.GetFieldValue("sign", strSign);			// sign
				strSign.Trim();

				item["i"] = (LPCSTR)strICQID;					// �˺�
				item["n"] = (LPCSTR)strTruename;				// ����
				item["s"] = atoi(strSex);						// �Ա�
				item["m"] = (LPCSTR)strMobile;					// �绰
				item["g"] = (LPCSTR)strSign;					// ǩ��

				MYSTATE m_state = (MYSTATE)0;
				DWORD dwConnectID = 0;
				g_MongoDBMgr.GetUserState(strICQID, m_state, dwConnectID);
				item["o"] = m_state;							// ����״̬
				array.append( item );

				data_value["ct"] = ++nIndex;					// count
				data_value["it"] = array;						// item
				strdata = writer.write(data_value);
				packlen = strdata.length();
				if ((0 == (nIdx+1) % REFRESH_GUSER_COUNT) || (nIdx+1 == nRowCount))
				{
					guserans->rtnnum = nIndex;
					guserans->nlen = packlen;
					memcpy(guserans->headp, strdata.c_str(), packlen);
					nLen = sizeof(guser_ans2) + packlen /*- sizeof(char)*/;
					m_ansbuf.AnsHeader.PacketLen	= nLen;
					m_ansbuf.AnsHeader.RawLen		= nLen;
					memcpy(&(m_ansbuf.AnsBuffer), guserans, nLen);
					nLenAll = sizeof(IMANSHEADER) + nLen;
					memcpy(pSend, &m_ansbuf, nLenAll);
					g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);

					array.clear();
					nIndex = 0;
				}
			}
		}
		else	//nRowCountΪ0
		{
			guserans->rtnnum = 0;
			nLen = sizeof(guser_ans2);
			m_ansbuf.AnsHeader.PacketLen	= nLen;
			m_ansbuf.AnsHeader.RawLen		= nLen;

			memcpy(&(m_ansbuf.AnsBuffer), guserans, nLen);
			nLenAll = sizeof(IMANSHEADER) + nLen;
			memcpy(pSend, &m_ansbuf, nLenAll);
			g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//�ͻ�����
	//��relation����ȡ�ø÷�����Ա�Ŀͻ�
	else if (m_req->ntype == eList_ClientGrp)
	{
		CADOCommand adoCmd(pLinkInfo->pAdodb, "icq_get_client2");
		adoCmd.AddInputParameter("@userid", strlen(m_req->userid), (CString)m_req->userid);
		CADORecordset adoRs(pLinkInfo->pAdodb);

		if(!adoRs.Execute(&adoCmd)) 
		{
			g_LinkMangaer.CheckConnect(pLinkInfo);
			m_ansbuf.AnsHeader.ErrorCode = erServer_DBError;
			TRACE("ִ�����ݿ�ʧ��");
		}
		//JSON
		long nRowCount = adoRs.GetRecordCount();
		if (nRowCount > 0)
		{
			for(long nIdx=0; nIdx<nRowCount; nIdx++,adoRs.MoveNext())
			{
				Value item;
				adoRs.GetFieldValue("icqid", strICQID);			// icqid
				strICQID.Trim();
				adoRs.GetFieldValue("name", strTruename);		// name
				strTruename.Trim();
				adoRs.GetFieldValue("sex", strSex);				// sex

				item["i"] = (LPCSTR)strICQID;					// �˺�
				item["n"] = (LPCSTR)strTruename;				// ����
				item["s"] = atoi(strSex);						// �Ա�
				item["m"] = "";									// �绰
				item["g"] = "";									// ǩ��

				MYSTATE m_state = (MYSTATE)0;
				DWORD dwConnectID = 0;
				g_MongoDBMgr.GetUserState(strICQID, m_state, dwConnectID);
				item["o"] = m_state;							// ����״̬

				array.append( item );

				data_value["ct"] = ++nIndex;					// count
				data_value["it"] = array;                       // item
				strdata = writer.write(data_value);
				packlen = strdata.length();
				if ((0 == (nIdx+1) % REFRESH_GUSER_COUNT) || (nIdx+1 == nRowCount))
				{
					guserans->rtnnum = nIndex;
					guserans->nlen = packlen;
					memcpy(guserans->headp, strdata.c_str(), packlen);
					nLen = sizeof(guser_ans2) + packlen /*- sizeof(char)*/;
					m_ansbuf.AnsHeader.PacketLen	= nLen;
					m_ansbuf.AnsHeader.RawLen		= nLen;
					memcpy(&(m_ansbuf.AnsBuffer), guserans, nLen);
					nLenAll = sizeof(IMANSHEADER) + nLen;
					memcpy(pSend, &m_ansbuf, nLenAll);
					g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);

					array.clear();
					nIndex = 0;
				}
			}
		}
		else	//nRowCountΪ0
		{
			guserans->rtnnum = 0;
			nLen = sizeof(guser_ans2);
			m_ansbuf.AnsHeader.PacketLen	= nLen;
			m_ansbuf.AnsHeader.RawLen		= nLen;

			memcpy(&(m_ansbuf.AnsBuffer), guserans, nLen);
			nLenAll = sizeof(IMANSHEADER) + nLen;
			memcpy(pSend, &m_ansbuf, nLenAll);
			g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);
		}
	}
	g_LinkMangaer.FreeLink(pLinkInfo);

	return nLenAll;
}

// UPIM_REQ_GLIST
int OnGListReq(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	int nLen = 0;
	char pSend[ANSBUFFER_LEN] = {0};
	glist_req* m_req = (glist_req *)pReceive;

	char m_sendbuf[ANSBUFFER_LEN] = {0};
	glist_ans* glistans = (glist_ans *)m_sendbuf;

	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_GLIST);
	if (m_req->ngrouptype == eList_SrvGroup)
	{
		glistans->rtnnum = 2;
		int nRowCount = glistans->rtnnum;
		glist_unit* m_unit = new glist_unit[nRowCount];
		long nStrucLen = sizeof(glist_unit)*nRowCount;
		memset(m_unit, 0, nStrucLen);

		m_unit[0].m_nGroupID = 1;
		COPYSTRARRAY(m_unit[0].m_szGroupName,"������");
		m_unit[0].m_ucGroupType = eList_SrvGroup;

		m_unit[1].m_nGroupID = 2;
		COPYSTRARRAY(m_unit[1].m_szGroupName,"��Ʒ����");
		m_unit[1].m_ucGroupType = eList_SrvGroup;

		memcpy(glistans->headp, m_unit, nStrucLen);
		nLen = sizeof(glist_ans) + sizeof(glist_unit)*(nRowCount-1);
		m_ansbuf.AnsHeader.PacketLen	= nLen;
		m_ansbuf.AnsHeader.RawLen		= nLen;
		TDEL(m_unit);
	}
	else if (m_req->ngrouptype == eList_ClientDefGrp)
	{
		/*
		xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
		*/
	}
	memcpy(&(m_ansbuf.AnsBuffer), glistans, nLen);
	nLenAll = sizeof(IMANSHEADER) + nLen;
	memcpy(pSend, &m_ansbuf, nLenAll);
	g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);

	return nLenAll;
}

// �õ�ĳһ����������û��б�
// UPIM_REQ_LIST
int OnListReq(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	int nLen = 0;
	char pSend[ANSBUFFER_LEN] = {0};
	list_req* m_req = (list_req *)pReceive;

	char szError[256] = {0};
	LPOPLINK pLinkInfo = NULL;
	pLinkInfo = g_LinkMangaer.GetLink(szError, sizeof(szError), TRUE);
	if (pLinkInfo == NULL)
		return nLenAll;

	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_LIST);

	char m_sendbuf[ANSBUFFER_LEN] = {0};
	list_ans* listans = (list_ans *)m_sendbuf;

	CString strICQID = _T("");
	CString strTruename = _T("");
	CString strSex = _T("");
	CString strSign = _T("");
	int nRelation = 0;

	if (m_req->ngrouptype == eList_SrvGroup)
	{
		CADOCommand adoCmd(pLinkInfo->pAdodb,"icq_get_broker");
		adoCmd.AddInputParameter("@userid", strlen(m_req->userid), (CString)m_req->userid);
		CADORecordset adoRs(pLinkInfo->pAdodb);

		if(!adoRs.Execute(&adoCmd)) 
		{
			g_LinkMangaer.CheckConnect(pLinkInfo);
			m_ansbuf.AnsHeader.ErrorCode = erServer_DBError;
			TRACE("ִ�����ݿ�ʧ��");
		}
		long nRowCount = adoRs.GetRecordCount();

		if (nRowCount > 0)
		{
			listans->rtnnum = (short)nRowCount;
			list_unit* m_unit = new list_unit[nRowCount];
			long nStrucLen = sizeof(list_unit)*nRowCount;
			memset(m_unit, 0, nStrucLen);

			for(long nIdx=0; nIdx<nRowCount; nIdx++,adoRs.MoveNext())	
			{
				adoRs.GetFieldValue("icqid", strICQID);			// icqid
				adoRs.GetFieldValue("truename", strTruename);	// name
				adoRs.GetFieldValue("relation", nRelation);		// relation
				adoRs.GetFieldValue("sex", strSex);				// sex
				adoRs.GetFieldValue("sign", strSign);			// sign

				strICQID.Trim();
				strncpy(m_unit[nIdx].userid, strICQID, strICQID.GetLength());
				strTruename.Trim();
				strncpy(m_unit[nIdx].username, strTruename, strTruename.GetLength());
				strSign.Trim();
				strncpy(m_unit[nIdx].signature, strSign, strSign.GetLength());
				m_unit[nIdx].relation = (short)nRelation;
				m_unit[nIdx].sex = (short)atoi(strSex);

				MYSTATE m_state = (MYSTATE)0;
				DWORD dwConnectID = 0;
				g_MongoDBMgr.GetUserState(strICQID, m_state, dwConnectID);
				m_unit[nIdx].state = (short)m_state;							// ����״̬��Ҫ���⴦��
			}
			memcpy(listans->headp, m_unit, nStrucLen);
			nLen = sizeof(list_ans) + sizeof(list_unit)*(nRowCount-1);
			m_ansbuf.AnsHeader.PacketLen	= nLen;
			m_ansbuf.AnsHeader.RawLen		= nLen;
			TDEL(m_unit);
		}
		else
		{
			listans->rtnnum = 0;
			nLen = sizeof(list_ans);
			m_ansbuf.AnsHeader.PacketLen	= nLen;
			m_ansbuf.AnsHeader.RawLen		= nLen;
		}
		memcpy(&(m_ansbuf.AnsBuffer), listans, nLen);
		nLenAll = sizeof(IMANSHEADER) + nLen;
		memcpy(pSend, &m_ansbuf, nLenAll);
	}
	g_LinkMangaer.FreeLink(pLinkInfo);
	g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);
	return nLenAll;
}

// UPIM_REQ_LIST2
int OnListReq2(DWORD dwConnID, char* pReceive, ULONG leng)
{
	BOOL bCount = FALSE;
	int nLenAll = 0;
	int nLen = 0;
	char pSend[ANSBUFFER_LEN] = {0};
	list_req* m_req = (list_req *)pReceive;

	char szError[256] = {0};
	LPOPLINK pLinkInfo = NULL;
	pLinkInfo = g_LinkMangaer.GetLink(szError, sizeof(szError), TRUE);
	if (pLinkInfo == NULL)
		return nLenAll;

	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_LIST2);

	char m_sendbuf[ANSBUFFER_LEN] = {0};
	list_ans2* listans = (list_ans2 *)m_sendbuf;

	CString strICQID = _T("");
	CString strTruename = _T("");
	CString strSex = _T("");
	CString strSign = _T("");
	int nRelation = 0;

	int packlen = 0;
	int nIndex = 0;
	Reader read;
	Value data_value;
	Value item;  
	Value array;
	FastWriter writer;
	string strdata;

	if (m_req->ngrouptype == eList_SrvGroup)
	{
		CADOCommand adoCmd(pLinkInfo->pAdodb,"icq_get_broker");
		adoCmd.AddInputParameter("@userid", strlen(m_req->userid), (CString)m_req->userid);
		CADORecordset adoRs(pLinkInfo->pAdodb);

		if(!adoRs.Execute(&adoCmd)) 
		{
			g_LinkMangaer.CheckConnect(pLinkInfo);
			m_ansbuf.AnsHeader.ErrorCode = erServer_DBError;
			TRACE("ִ�����ݿ�ʧ��");
		}
		long nRowCount = adoRs.GetRecordCount();
		//JSON
		if (nRowCount > 0)
		{
			for(long nIdx=0; nIdx<nRowCount; nIdx++,adoRs.MoveNext())
			{
				adoRs.GetFieldValue("icqid", strICQID);			// icqid
				adoRs.GetFieldValue("truename", strTruename);	// name
				adoRs.GetFieldValue("relation", nRelation);		// relation
				adoRs.GetFieldValue("sex", strSex);				// sex
				adoRs.GetFieldValue("sign", strSign);			// sign

				strICQID.Trim();
				strTruename.Trim();

				item["i"] = (LPCSTR)strICQID;					// �˺�
				item["n"] = (LPCSTR)strTruename;				// ����
				item["r"] = nRelation;							// ��ϵ
				item["s"] = atoi(strSex);						// �Ա�
				item["g"] = (LPCSTR)strSign;					// ǩ��
				
				MYSTATE m_state = (MYSTATE)0;
				DWORD dwConnectID = 0;
				g_MongoDBMgr.GetUserState(strICQID, m_state, dwConnectID);
				item["o"] = m_state;							// ����״̬

				array.append( item );

				data_value["ct"] = ++nIndex;					// count
				data_value["it"] = array;                       // item
				strdata = writer.write(data_value);
				packlen = strdata.length();
				if ((0 == (nIdx+1) % REFRESH_GUSER_COUNT) || (nIdx+1 == nRowCount))
				{
					listans->len = packlen;
					memcpy(listans->headp, strdata.c_str(), packlen);
					nLen = sizeof(list_ans2) + packlen /*- sizeof(char)*/;
					m_ansbuf.AnsHeader.PacketLen	= nLen;
					m_ansbuf.AnsHeader.RawLen		= nLen;
					memcpy(&(m_ansbuf.AnsBuffer), listans, nLen);
					nLenAll = sizeof(IMANSHEADER) + nLen;
					memcpy(pSend, &m_ansbuf, nLenAll);
					g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);

					array.clear();
					nIndex = 0;
				}
			}
		}
		else
		{
			listans->len = 0;
			nLen = sizeof(list_ans2);
			m_ansbuf.AnsHeader.PacketLen	= nLen;
			m_ansbuf.AnsHeader.RawLen		= nLen;

			memcpy(&(m_ansbuf.AnsBuffer), listans, nLen);
			nLenAll = sizeof(IMANSHEADER) + nLen;
			memcpy(pSend, &m_ansbuf, nLenAll);
			g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);
		}
	}
	g_LinkMangaer.FreeLink(pLinkInfo);

	return nLenAll;
}

/*
* �յ��û���������Ϣ�߼���
* �����ߵ�д������Ϣ�⣬���ҷ���SENDMSG��ִ
* ���ߵ�ֱ����Ϣ���ͣ����ݷ����������SENDMSG��ִ
*/
//UPIM_REQ_SENDMSG
//
int OnSendMSGReq(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	char pSend[ANSBUFFER_LEN] = {0};
	sendmsg_req* m_req = (sendmsg_req *)pReceive;
	time_t tmProsess = time(NULL);

	int nLen = sizeof(sendmsg_ans);
	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_SENDMSG, nLen, nLen);

	sendmsg_ans sendmsgans = {0};
	MYSTATE m_state = (MYSTATE)0;
	DWORD dwConnectID = 0;
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// �����ں���Ϣ

	if (m_req->ucMsgType == eMsgSend_Public)
	{
#ifdef PUBLICMNG
		int nPublicID = m_req->nPublicID;
		int nRouteID = m_req->nRouteID;
		char* szUserID = m_req->cFromuserid;
		// ���TouseridΪ�գ���ʾ�ǿͻ�����Ự,ҪΪ����û�����ͷ�
		if (strlen(m_req->cTouserid) == 0)
		{

			char* cSevID = g_PublicMng.GetServiceID(nPublicID, szUserID, nRouteID);
			// δȡ��������Ĭ��
			if (strlen(cSevID) == 0)
			{
				cSevID = "3150";
			}

			g_MongoDBMgr.GetUserState(cSevID, m_state, dwConnectID);
		}
		else
			g_MongoDBMgr.GetUserState(m_req->cTouserid, m_state, dwConnectID);
		//////////////////////////////////////////////////////////////////////////
		// ���� ת����3150
		char buf[MAX_SEND_BUF_LEN] = {0};
		s_sendmsg_ans *pans_sendmsg = (s_sendmsg_ans *)buf;

		IMANSBUFFER m_ansbuf2 = {0};
		InitAnsBufHead(m_ansbuf2, UPIM_REQ_S_SENDMSG);

		pans_sendmsg->ucMsgType = m_req->ucMsgType;
		COPYSTRARRAY(pans_sendmsg->innerID, m_req->innerID);
		pans_sendmsg->dwMsgSeq = m_req->dwMsgSeq;
		pans_sendmsg->format = m_req->format;
		COPYSTRARRAY(pans_sendmsg->cFromuserid, m_req->cFromuserid);
		pans_sendmsg->tmSend = tmProsess;
		pans_sendmsg->nPublicID = nPublicID;
		pans_sendmsg->msglen = m_req->msglen;
		memcpy(pans_sendmsg->msg, m_req->msg, m_req->msglen);
		int nLen2 = sizeof(s_sendmsg_ans) + pans_sendmsg->msglen/*- sizeof(char)*/;
		m_ansbuf2.AnsHeader.PacketLen	= nLen2;
		m_ansbuf2.AnsHeader.RawLen		= nLen2;

		memcpy(&(m_ansbuf2.AnsBuffer), pans_sendmsg, nLen2);
		int nLenAll2 = sizeof(IMANSHEADER) + nLen2;
		BOOL bSendSuess = g_MySever.m_Server.Send((CONNID)dwConnectID, (LPBYTE)&m_ansbuf2, nLenAll2);

		// ����ʷ��Ϣ��
		g_pList->PushHisMsg(m_req->cFromuserid, IntToStr(nPublicID), m_req->format, (long)m_req->tmSend, (const char*)m_req->msg);
#endif
	}

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// ����һ����Ϣ
	else if (m_req->ucMsgType == eMsgSend_Normal)
	{
		g_MongoDBMgr.GetUserState(m_req->cTouserid, m_state, dwConnectID);

		// д������Ϣ��
		if (m_state == MYSTATE_OFFLINE )
		{
			// ���ڶ�����������Ϣ����
			if (m_req->format == eMsgFormat_Shake)
				return nLenAll;
			
			//OP_LOG_INFO("[OFFMSG] SEQ:%08d From:%s To:%s", m_req->dwMsgSeq, m_req->cFromuserid, m_req->cTouserid);
			g_pList->PushOffMsg(m_req->cFromuserid, m_req->cTouserid, m_req->format, (long)m_req->tmSend, (const char*)m_req->msg);
			COPYSTRARRAY(sendmsgans.cTouserid, m_req->cTouserid);
			sendmsgans.nUserState = MYSTATE_OFFLINE;
			sendmsgans.dwMsgSeq = m_req->dwMsgSeq;
			sendmsgans.tmSend = tmProsess;

			memcpy(&(m_ansbuf.AnsBuffer), &sendmsgans, nLen);
			nLenAll = sizeof(IMANSHEADER) + nLen;
			memcpy(pSend, &m_ansbuf, nLenAll);
			g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);
			return nLenAll;
		}
		//////////////////////////////////////////////////////////////////////////
		// ����û����ߣ���Ϣת��
		// ���·�����Ϣת������FromUser
		long nDate=0, nTime=0;
		ConvertTimeToLong(m_req->tmSend, nDate, nTime);
		//OP_LOG_INFO("[ONLINEMSG] SEQ:%08d From:%s To:%s CONID:%d", m_req->dwMsgSeq, m_req->cFromuserid, m_req->cTouserid, dwConnectID);

		char buf[MAX_SEND_BUF_LEN] = {0};
		s_sendmsg_ans *pans_sendmsg = (s_sendmsg_ans *)buf;

		IMANSBUFFER m_ansbuf2 = {0};
		InitAnsBufHead(m_ansbuf2, UPIM_REQ_S_SENDMSG);

		pans_sendmsg->ucMsgType = m_req->ucMsgType;
		COPYSTRARRAY(pans_sendmsg->innerID, m_req->innerID);
		pans_sendmsg->dwMsgSeq = m_req->dwMsgSeq;
		pans_sendmsg->format = m_req->format;
		COPYSTRARRAY(pans_sendmsg->cFromuserid, m_req->cFromuserid);
		pans_sendmsg->tmSend = tmProsess;
		pans_sendmsg->msglen = m_req->msglen;
		memcpy(pans_sendmsg->msg, m_req->msg, m_req->msglen);
		int nLen2 = sizeof(s_sendmsg_ans) + pans_sendmsg->msglen/*- sizeof(char)*/;
		m_ansbuf2.AnsHeader.PacketLen	= nLen2;
		m_ansbuf2.AnsHeader.RawLen		= nLen2;

		memcpy(&(m_ansbuf2.AnsBuffer), pans_sendmsg, nLen2);
		int nLenAll2 = sizeof(IMANSHEADER) + nLen2;
		BOOL bSendSuess = g_MySever.m_Server.Send((CONNID)dwConnectID, (LPBYTE)&m_ansbuf2, nLenAll2);
		if (bSendSuess)
		{
			COPYSTRARRAY(sendmsgans.cTouserid, m_req->cTouserid);
			sendmsgans.nUserState = MYSTATE_NORMAL;
			sendmsgans.dwMsgSeq = m_req->dwMsgSeq;
			sendmsgans.tmSend = tmProsess;

			memcpy(&(m_ansbuf.AnsBuffer), &sendmsgans, nLen);
			nLenAll = sizeof(IMANSHEADER) + nLen;
			memcpy(pSend, &m_ansbuf, nLenAll);
			g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);
		}

		// ����ʷ��Ϣ��
		g_pList->PushHisMsg(m_req->cFromuserid, m_req->cTouserid, m_req->format, (long)m_req->tmSend, (const char*)m_req->msg);
	}
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// �����˻Ự����������Ϣ
	else if (m_req->ucMsgType == eMsgSend_Analyst)
	{
		g_MongoDBMgr.GetUserState(m_req->cTouserid, m_state, dwConnectID);

		// д������Ϣ��
		if (m_state == MYSTATE_OFFLINE )
		{
			// ���ڶ�����������Ϣ����
			if (m_req->format == eMsgFormat_Shake)
				return nLenAll;

			//OP_LOG_INFO("[OFFMSG] SEQ:%08d From:%s To:%s", m_req->dwMsgSeq, m_req->cFromuserid, m_req->cTouserid);
			g_pList->PushOffMsg(m_req->cFromuserid, m_req->cTouserid, m_req->format, (long)m_req->tmSend, (const char*)m_req->msg);
			COPYSTRARRAY(sendmsgans.cTouserid, m_req->cTouserid);
			sendmsgans.nUserState = MYSTATE_OFFLINE;
			sendmsgans.dwMsgSeq = m_req->dwMsgSeq;
			sendmsgans.tmSend = tmProsess;

			memcpy(&(m_ansbuf.AnsBuffer), &sendmsgans, nLen);
			nLenAll = sizeof(IMANSHEADER) + nLen;
			memcpy(pSend, &m_ansbuf, nLenAll);
			g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);
			return nLenAll;
		}
		//////////////////////////////////////////////////////////////////////////
		// ����û����ߣ���Ϣת��
		// ���·�����Ϣת������FromUser
		long nDate=0, nTime=0;
		ConvertTimeToLong(m_req->tmSend, nDate, nTime);
		//OP_LOG_INFO("[ONLINEMSG] SEQ:%08d From:%s To:%s CONID:%d", m_req->dwMsgSeq, m_req->cFromuserid, m_req->cTouserid, dwConnectID);

		char buf[MAX_SEND_BUF_LEN] = {0};
		s_sendmsg_ans *pans_sendmsg = (s_sendmsg_ans *)buf;

		IMANSBUFFER m_ansbuf2 = {0};
		InitAnsBufHead(m_ansbuf2, UPIM_REQ_S_SENDMSG);

		pans_sendmsg->ucMsgType = m_req->ucMsgType;
		COPYSTRARRAY(pans_sendmsg->innerID, m_req->innerID);
		pans_sendmsg->dwMsgSeq = m_req->dwMsgSeq;
		pans_sendmsg->format = m_req->format;
		COPYSTRARRAY(pans_sendmsg->cFromuserid, m_req->cFromuserid);
		pans_sendmsg->tmSend = tmProsess;
		pans_sendmsg->msglen = m_req->msglen;
		memcpy(pans_sendmsg->msg, m_req->msg, m_req->msglen);
		int nLen2 = sizeof(s_sendmsg_ans) + pans_sendmsg->msglen/*- sizeof(char)*/;
		m_ansbuf2.AnsHeader.PacketLen	= nLen2;
		m_ansbuf2.AnsHeader.RawLen		= nLen2;

		memcpy(&(m_ansbuf2.AnsBuffer), pans_sendmsg, nLen2);
		int nLenAll2 = sizeof(IMANSHEADER) + nLen2;
		BOOL bSendSuess = g_MySever.m_Server.Send((CONNID)dwConnectID, (LPBYTE)&m_ansbuf2, nLenAll2);
		if (bSendSuess)
		{
			COPYSTRARRAY(sendmsgans.cTouserid, m_req->cTouserid);
			sendmsgans.nUserState = MYSTATE_NORMAL;
			sendmsgans.dwMsgSeq = m_req->dwMsgSeq;
			sendmsgans.tmSend = tmProsess;

			memcpy(&(m_ansbuf.AnsBuffer), &sendmsgans, nLen);
			nLenAll = sizeof(IMANSHEADER) + nLen;
			memcpy(pSend, &m_ansbuf, nLenAll);
			g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);
		}

		// ����ʷ��Ϣ��
		g_pList->PushHisMsg(m_req->cFromuserid, m_req->cTouserid, m_req->format, (long)m_req->tmSend, (const char*)m_req->msg);
	}

	return nLenAll;
}

//UPIM_REQ_GCSENDMSG
int OnGcSendMSGReq(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	char pSend[ANSBUFFER_LEN] = {0};
	gcsendmsg_req* m_req = (gcsendmsg_req *)pReceive;
	time_t tmProsess = time(NULL);
	char szKhh[S_USERID_LEN] = {0}, szNickName[S_NICKNAME_LEN] = {0};

	gcsendmsg_ans gcsendmsgans = {0};

	int nLen = sizeof(gcsendmsg_ans);
	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_GCSENDMSG, nLen, nLen);

	ROOMMSG roomMsg={0};
	roomMsg.m_nRoomID = m_req->roomid;
	COPYSTRARRAY(roomMsg.m_szSrcID, m_req->cFromuserid);
	COPYSTRARRAY(szKhh, m_req->cFromuserid);
	COPYSTRARRAY(szNickName, m_req->nickname);
	roomMsg.m_ucUserType = (BYTE)m_req->nUsertype;
	roomMsg.m_tmSend = m_req->tmSend;
	roomMsg.m_ucFormat = m_req->format;
	roomMsg.m_ucRoomType = m_req->roomtype;
	memcpy(roomMsg.m_szMsg, m_req->msg, m_req->msglen);

	// ������ⲿȺ��
	if(roomMsg.m_ucRoomType == eCR_Group_Client)
	{
		g_pList->PushRoomMsg(&roomMsg);
		gcsendmsgans.RoomId = m_req->roomid;
		gcsendmsgans.Roomtype = m_req->roomtype;
		gcsendmsgans.dwMsgSeq = m_req->dwMsgSeq;
		gcsendmsgans.tmSend = tmProsess;

		memcpy(&(m_ansbuf.AnsBuffer), &gcsendmsgans, nLen);
		nLenAll = sizeof(IMANSHEADER) + nLen;
		memcpy(pSend, &m_ansbuf, nLenAll);
		g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);
	}
	// ������ڲ�Ⱥ�飬������QQȺ��
	else if(roomMsg.m_ucRoomType == eCR_Group)
	{
		//////////////////////////////////////////////////////////////////////////
		// ����û����ߣ���Ϣת��
		// ���·�����Ϣת������FromUser
		char buf[MAX_SEND_BUF_LEN] = {0};
		
		gcrecvmsg_ans *pgcrecvmsg = (gcrecvmsg_ans *)buf;

		COPYSTRARRAY(pgcrecvmsg->cFromuserid, m_req->cFromuserid);
		pgcrecvmsg->format = m_req->format;

		pgcrecvmsg->msglen = m_req->msglen;
		COPYSTRARRAY(pgcrecvmsg->nickname, m_req->nickname);
		pgcrecvmsg->nUsertype = m_req->nUsertype;
		pgcrecvmsg->roomid = m_req->roomid;
		pgcrecvmsg->roomtype = m_req->roomtype;
		pgcrecvmsg->tmSend = tmProsess;
		memcpy(pgcrecvmsg->msg, m_req->msg, m_req->msglen);
		int nLen2 = sizeof(gcrecvmsg_ans) + pgcrecvmsg->msglen/*- sizeof(char)*/;

		IMANSBUFFER m_ansbuf2 = {0};
		InitAnsBufHead(m_ansbuf2, UPIM_REQ_GCRECVMSG, nLen2, nLen2);

		memcpy(&(m_ansbuf2.AnsBuffer), pgcrecvmsg, nLen2);
		int nLenAll2 = sizeof(IMANSHEADER) + nLen2;
		memcpy(pSend, &m_ansbuf, nLenAll2);

		// �ж�Ⱥ��Ա�Ƿ����ߣ�������ֱ�����ͣ���������ѹ��Ⱥ��������Ϣ����
		vector<VUPID> vt;
		g_GroupChatMng.GetUser(roomMsg.m_nRoomID, roomMsg.m_ucRoomType, vt);
		long nError = 0;
		for(UINT i=0; i<vt.size(); i++)
		{
			if(EqualUPID(vt[i], szKhh)) 
				continue;

			MYSTATE m_state = (MYSTATE)0;
			DWORD dwConnectID = 0;
			g_MongoDBMgr.GetUserState(vt[i].m_szIMID, m_state, dwConnectID);

			// д������Ϣ��
			if (m_state == MYSTATE_OFFLINE)
			{
				g_pList->PushRoomOffMsg(szKhh, vt[i].m_szIMID, szNickName, roomMsg.m_nRoomID, roomMsg.m_ucRoomType, roomMsg.m_ucFormat, (long)roomMsg.m_tmSend, roomMsg.m_szMsg);
				continue;
			}
			else if (m_state == MYSTATE_NORMAL)
			{
				BOOL bSendSuess = g_MySever.m_Server.Send((CONNID)dwConnectID, (LPBYTE)&m_ansbuf2, nLenAll2);
			}
		}

		//////////////////////////////////////////////////////////////////////////
		// ������������
		gcsendmsgans.RoomId = m_req->roomid;
		gcsendmsgans.Roomtype = m_req->roomtype;
		gcsendmsgans.dwMsgSeq = m_req->dwMsgSeq;
		gcsendmsgans.tmSend = tmProsess;

		memcpy(&(m_ansbuf.AnsBuffer), &gcsendmsgans, nLen);
		nLenAll = sizeof(IMANSHEADER) + nLen;
		memcpy(pSend, &m_ansbuf, nLenAll);
		g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);
	}
	return 0;
}

//UPIM_REQ_DEPT
int OnDeptReq(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	int nLen = 0;
	char pSend[ANSBUFFER_LEN] = {0};
	dept_req* m_req = (dept_req *)pReceive;

	char szError[256] = {0};
	LPOPLINK pLinkInfo = NULL;
	pLinkInfo = g_LinkMangaer.GetLink(szError, sizeof(szError), TRUE);
	if (pLinkInfo == NULL)
		return nLenAll;

	char m_sendbuf[ANSBUFFER_LEN] = {0};
	dept_ans* deptans = (dept_ans *)m_sendbuf;

	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_DEPT);

	CADOCommand adoCmd(pLinkInfo->pAdodb,"icq_get_dept3");
	adoCmd.AddInputParameter("@deptid", (int)m_req->ndeptid);
	CADORecordset adoRs(pLinkInfo->pAdodb);

	if(!adoRs.Execute(&adoCmd)) 
	{
		g_LinkMangaer.CheckConnect(pLinkInfo);
		m_ansbuf.AnsHeader.ErrorCode = erServer_DBError;
		TRACE("ִ�����ݿ�ʧ��");
	}
	long nRowCount = adoRs.GetRecordCount();

	if (nRowCount > 0)
	{
		deptans->rtnnum = (short)nRowCount;
		dept_unit* m_unit = new dept_unit[nRowCount];
		long nStrucLen = sizeof(dept_unit)*nRowCount;
		memset(m_unit, 0, nStrucLen);

		int ndeptid = 0;
		CString strdeptname = _T("");
		int nparentid = 0;

		for(long nIdx=0; nIdx<nRowCount; nIdx++,adoRs.MoveNext())	
		{
			adoRs.GetFieldValue("deptid", ndeptid);			// deptid
			adoRs.GetFieldValue("deptname", strdeptname);	// deptname
			adoRs.GetFieldValue("parentid", nparentid);		// parentid

			strdeptname.Trim();
			m_unit[nIdx].deptid = ndeptid;
			m_unit[nIdx].predept = nparentid;
			strncpy(m_unit[nIdx].deptname, strdeptname, strdeptname.GetLength());
		}
		memcpy(deptans->headp, m_unit, nStrucLen);
		nLen = sizeof(dept_ans) + sizeof(dept_unit)*(nRowCount-1);
		m_ansbuf.AnsHeader.PacketLen	= nLen;
		m_ansbuf.AnsHeader.RawLen		= nLen;
		TDEL(m_unit);
	}
	else
	{
		deptans->rtnnum = 0;
		nLen = sizeof(list_ans);
		m_ansbuf.AnsHeader.PacketLen	= nLen;
		m_ansbuf.AnsHeader.RawLen		= nLen;
	}
	memcpy(&(m_ansbuf.AnsBuffer), deptans, nLen);
	nLenAll = sizeof(IMANSHEADER) + nLen;
	memcpy(pSend, &m_ansbuf, nLenAll);

	g_LinkMangaer.FreeLink(pLinkInfo);
	g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);

	return nLenAll;
}

// UPIM_REQ_GCINFO
int OnGcInfoReq(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	int nLen = 0;
	char pSend[ANSBUFFER_LEN] = {0};
	gcinfo_req* m_req = (gcinfo_req *)pReceive;

	char szError[256] = {0};
	LPOPLINK pLinkInfo = NULL;
	pLinkInfo = g_LinkMangaer.GetLink(szError, sizeof(szError), TRUE);
	if (pLinkInfo == NULL)
		return nLenAll;

	char m_sendbuf[ANSBUFFER_LEN] = {0};
	gcinfo_ans* gcinfoans = (gcinfo_ans *)m_sendbuf;

	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_GCINFO);

	long nSize = 0;
	BOOL bClient = (BOOL)m_req->type;
	long roomid = m_req->RoomId;
	short roomtype = m_req->Roomtype;

	if (0 == roomid)
	{
		if(!bClient)
		{
			// Ա�����
			vector<GROUP_CHAT_BASE> gci;
			g_GroupChatMng.GetMyChatroom2(m_req->userid, gci, pLinkInfo->pAdodb);
			nSize = gci.size();
			if (nSize > 0)
			{
				gcinfoans->rtnnum = (short)nSize;
				gcinfo_unit* m_unit = new gcinfo_unit[nSize];
				long nStrucLen = sizeof(gcinfo_unit)*nSize;
				memset(m_unit, 0, nStrucLen);

				int nIdx = 0;
				for(long i=0; i<nSize; i++)
				{
					m_unit[i].RoomId = gci[i].m_nRoomId;
					m_unit[i].Roomtype = gci[i].m_nType;

					COPYSTRARRAY(m_unit[i].masterid, gci[i].m_szMasterID);
					COPYSTRARRAY(m_unit[i].Roomname, gci[i].m_szRoomName);
					COPYSTRARRAY(m_unit[i].RoomNote, gci[i].m_szNote);
					nIdx++;
				}
				nSize = nIdx;

				//////////////////////////////////////////////////////////////////////////
				memcpy(gcinfoans->headp, m_unit, nStrucLen);
				nLen = sizeof(gcinfo_ans) + sizeof(gcinfo_unit)*(nSize-1);
				m_ansbuf.AnsHeader.PacketLen	= nLen;
				m_ansbuf.AnsHeader.RawLen		= nLen;
				TDEL(m_unit);
			}
		}
	}
	else
	{
		GROUP_CHAT_BASE chatInfo;
		chatInfo.m_nRoomId = roomid;
		chatInfo.m_nType = roomtype;
		g_GroupChatMng.GetChatroomInfo(chatInfo);
		nSize = 1;

		gcinfoans->rtnnum = (short)nSize;
		gcinfo_unit* m_unit = new gcinfo_unit;
		long nStrucLen = sizeof(gcinfo_unit);
		memset(m_unit, 0, nStrucLen);

		m_unit->RoomId = chatInfo.m_nRoomId;
		m_unit->Roomtype = chatInfo.m_nType;
		COPYSTRARRAY(m_unit->masterid, chatInfo.m_szMasterID);
		COPYSTRARRAY(m_unit->Roomname, chatInfo.m_szRoomName);
		COPYSTRARRAY(m_unit->RoomNote, chatInfo.m_szNote);

		//////////////////////////////////////////////////////////////////////////
		memcpy(gcinfoans->headp, m_unit, nStrucLen);
		nLen = sizeof(gcinfo_ans) + sizeof(gcinfo_unit)*(nSize-1);
		m_ansbuf.AnsHeader.PacketLen	= nLen;
		m_ansbuf.AnsHeader.RawLen		= nLen;
		TDEL(m_unit);
	}

	memcpy(&(m_ansbuf.AnsBuffer), gcinfoans, nLen);
	nLenAll = sizeof(IMANSHEADER) + nLen;
	memcpy(pSend, &m_ansbuf, nLenAll);

	g_LinkMangaer.FreeLink(pLinkInfo);
	g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);

	return nLenAll;
}

// UPIM_REQ_GCINFO2
int OnGcInfoReq2(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	int nLen = 0;
	char pSend[ANSBUFFER_LEN] = {0};
	gcinfo_req* m_req = (gcinfo_req *)pReceive;

	char szError[256] = {0};
	LPOPLINK pLinkInfo = NULL;
	pLinkInfo = g_LinkMangaer.GetLink(szError, sizeof(szError), TRUE);
	if (pLinkInfo == NULL)
		return nLenAll;

	char m_sendbuf[ANSBUFFER_LEN] = {0};
	gcinfo_ans2* gcinfoans = (gcinfo_ans2 *)m_sendbuf;

	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_GCINFO2);
	
	BOOL bClient = (BOOL)m_req->type;
	long roomid = m_req->RoomId;
	short roomtype = m_req->Roomtype;

	// json
	Value data_value;
	
	Value array;
	FastWriter writer;
	string strdata;
	int packlen = 0;
	int nIndex = 0;
	long nSize = 0;

	if (0 == roomid)
	{
		// Ա�����
		if(!bClient) 
		{
			vector<GROUP_CHAT_BASE> gci;
			g_GroupChatMng.GetMyChatroom2(m_req->userid, gci, pLinkInfo->pAdodb);
			nSize = gci.size();
			if (nSize > 0)
			{
				for(long nIdx=0; nIdx<nSize; nIdx++)
				{
					Value item;
					item["i"] = (long)gci[nIdx].m_nRoomId;			// ROOMID
					item["t"] = (int)gci[nIdx].m_nType;				// ROOMTYPE
					item["m"] = (LPCSTR)gci[nIdx].m_szMasterID;		// Ⱥ������ID
					item["n"] = (LPCSTR)gci[nIdx].m_szRoomName;		// Ⱥ������
					item["g"] = (LPCSTR)gci[nIdx].m_szNote;			// Ⱥ����
					item["d"] = (int)gci[nIdx].m_bDelFlag;			// Ⱥɾ�����
					array.append( item );

					data_value["ct"] = ++nIndex;					// count
					data_value["it"] = array;						// item
					strdata = writer.write(data_value);
					packlen = strdata.length();
					if ((0 == (nIdx+1) % REFRESH_GROOM_COUNT) || (nIdx+1 == nSize))
					{
						gcinfoans->rtnnum = nIndex;
						gcinfoans->nlen = packlen;
						memcpy(gcinfoans->headp, strdata.c_str(), packlen);
						nLen = sizeof(gcinfo_ans2) + packlen /*- sizeof(char)*/;
						m_ansbuf.AnsHeader.PacketLen	= nLen;
						m_ansbuf.AnsHeader.RawLen		= nLen;
						memcpy(&(m_ansbuf.AnsBuffer), gcinfoans, nLen);
						nLenAll = sizeof(IMANSHEADER) + nLen;
						memcpy(pSend, &m_ansbuf, nLenAll);
						g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);

						array.clear();
						nIndex = 0;
					}
				}
			}
		}
	}
	else
	{
		GROUP_CHAT_BASE chatInfo;
		chatInfo.m_nRoomId = roomid;
		chatInfo.m_nType = roomtype;
		g_GroupChatMng.GetChatroomInfo(chatInfo);

		Value item;
		item["i"] = (long)chatInfo.m_nRoomId;			// ROOMID
		item["t"] = (int)chatInfo.m_nType;				// ROOMTYPE
		item["m"] = (LPCSTR)chatInfo.m_szMasterID;		// Ⱥ������ID
		item["n"] = (LPCSTR)chatInfo.m_szRoomName;		// Ⱥ������
		item["g"] = (LPCSTR)chatInfo.m_szNote;			// Ⱥ����
		item["d"] = (int)chatInfo.m_bDelFlag;			// Ⱥɾ�����
		array.append( item );

		data_value["ct"] = 1;							// count
		data_value["it"] = array;						// item
		strdata = writer.write(data_value);
		packlen = strdata.length();

		gcinfoans->rtnnum = 1;
		gcinfoans->nlen = packlen;
		memcpy(gcinfoans->headp, strdata.c_str(), packlen);
		nLen = sizeof(gcinfo_ans2) + packlen /*- sizeof(char)*/;
		m_ansbuf.AnsHeader.PacketLen	= nLen;
		m_ansbuf.AnsHeader.RawLen		= nLen;
		memcpy(&(m_ansbuf.AnsBuffer), gcinfoans, nLen);
		nLenAll = sizeof(IMANSHEADER) + nLen;
		memcpy(pSend, &m_ansbuf, nLenAll);
		g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);
	}
	g_LinkMangaer.FreeLink(pLinkInfo);
	return nLenAll;
}

//UPIM_REQ_GCGETLIST
int OnGcGetListReq(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	int nLen = 0;
	char pSend[ANSBUFFER_LEN] = {0};
	gcgetlist_req* m_req = (gcgetlist_req *)pReceive;

	char szError[256] = {0};
	LPOPLINK pLinkInfo = NULL;
	pLinkInfo = g_LinkMangaer.GetLink(szError, sizeof(szError), TRUE);
	if (pLinkInfo == NULL)
		return nLenAll;
	
	char m_sendbuf[ANSBUFFER_LEN] = {0};
	gcgetlist_ans* gcgetlistans = (gcgetlist_ans *)m_sendbuf;

	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_GCGETLIST);

	long nRoomID = m_req->RoomId;
	long nRoomType = m_req->Roomtype;
	int nPos = m_req->nStartPos;

	vector<VUPID> user;
	g_GroupChatMng.GetUser(nRoomID, nRoomType, user);
	int nSize = user.size();
	if (nSize > 0)
	{
		gcgetlistans->rtnnum = (short)nSize;
		gcgetlistans->RoomId = nRoomID;
		gcgetlistans->nStartPos = nPos;
		gcgetlist_unit* m_unit = new gcgetlist_unit[nSize];
		long nStrucLen = sizeof(gcgetlist_unit)*nSize;
		memset(m_unit, 0, nStrucLen);

		for (int i=0;i<nSize;i++)
		{
			if(i<nPos) continue;
			COPYSTRARRAY(m_unit[i].userid, user[i].m_szIMID);
			m_unit[i].usertype = user[i].m_nUserType;
			m_unit[i].state = 0;
		}
		//////////////////////////////////////////////////////////////////////////
		memcpy(gcgetlistans->headp, m_unit, nStrucLen);
		nLen = sizeof(gcgetlist_ans) + sizeof(gcgetlist_unit)*(nSize-1);
		m_ansbuf.AnsHeader.PacketLen	= nLen;
		m_ansbuf.AnsHeader.RawLen		= nLen;
		TDEL(m_unit);
	}

	memcpy(&(m_ansbuf.AnsBuffer), gcgetlistans, nLen);
	nLenAll = sizeof(IMANSHEADER) + nLen;
	memcpy(pSend, &m_ansbuf, nLenAll);

	g_LinkMangaer.FreeLink(pLinkInfo);
	g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);

	return nLenAll;
}

//UPIM_REQ_GCCREATE
int OnGcCreateReq(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	int nLen = 0;
	char pSend[ANSBUFFER_LEN] = {0};
	char szKhh[S_USERID_LEN]={0}, szGroup[S_NICKNAME_LEN]={0};

	gccreate_req* m_req = (gccreate_req *)pReceive;
	COPYSTRARRAY(szKhh, m_req->createuserid);
	COPYSTRARRAY(szGroup, m_req->roomname);
	int nRoomParam = m_req->nroomParam;

	char szError[256] = {0};
	LPOPLINK pLinkInfo = NULL;
	pLinkInfo = g_LinkMangaer.GetLink(szError, sizeof(szError), TRUE);
	if (pLinkInfo == NULL)
		return nLenAll;

	char m_sendbuf[ANSBUFFER_LEN] = {0};
	gccreate_ans* gccreateans = (gccreate_ans *)m_sendbuf;

	nLen = sizeof(gccreate_ans);
	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_GCCREATE, nLen, nLen);
	
	ROOMID thisRoomID = 0;
	int nError = g_GroupChatMng.CreateRoom(szGroup, m_req->roomtype, szKhh, pLinkInfo->pAdodb, thisRoomID);

	TRACE("UPIM_REQ_GCCREATE:%d", nError);
	if(nError != eGCError_Success)
	{
		gccreateans->bSussess = FALSE;
		COPYSTRARRAY(gccreateans->ErrStr, GetErrorStr(nError));
	}
	else
	{
		gccreateans->bSussess = TRUE;
		gccreateans->nRoomID = thisRoomID;
	}
	gccreateans->nroomParam = nRoomParam;

	memcpy(&(m_ansbuf.AnsBuffer), gccreateans, nLen);
	nLenAll = sizeof(IMANSHEADER) + nLen;
	memcpy(pSend, &m_ansbuf, nLenAll);

	g_LinkMangaer.FreeLink(pLinkInfo);
	g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);

	return nLenAll;
}

// UPIM_REQ_GCADD
int OnGcAddReq(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	int nLen = 0;
	char pSend[ANSBUFFER_LEN] = {0};
	gcadd_req* m_req = (gcadd_req *)pReceive;
	ROOMID nRoomID = m_req->nRoomID;
	short nRoomType = m_req->roomtype;
	long nszLen = m_req->szlen;

	char szJson[MAX_SEND_BUF_LEN] = {0};
	strncpy(szJson, m_req->szUpID, nszLen);

	//////////////////////////////////////////////////////////////////////////
	Value value;  
	Reader read;  
	if ( !read.parse( szJson,value ) )  
	{  
		return -1;  
	}
	Value val_array = value["item"];  
	int iSize = val_array.size();
	vector<VUPID> vtUPID;
	for (int nIndex=0; nIndex<iSize; nIndex++)
	{
		VUPID upid = {0};
		CString strUserType = val_array[nIndex]["tp"].asCString();
		upid.m_nUserType = atoi(strUserType);
		CString strUserID = val_array[nIndex]["id"].asCString();
		COPYSTRARRAY(upid.m_szIMID, strUserID);
		vtUPID.push_back(upid);

		// �����ӵĿͻ���ǰ���ߣ�����Ⱥ����Ϣ����
	 	MYSTATE m_state = (MYSTATE)0;
	 	DWORD dwConnectID = 0;
		g_MongoDBMgr.GetUserState(strUserID, m_state, dwConnectID);
		if (m_state == MYSTATE_NORMAL)
			OnGcAdd_ex(dwConnectID, nRoomID, nRoomType);
	}
	//////////////////////////////////////////////////////////////////////////

	char szError[256] = {0};
	LPOPLINK pLinkInfo = NULL;
	pLinkInfo = g_LinkMangaer.GetLink(szError, sizeof(szError), TRUE);
	if (pLinkInfo == NULL)
		return nLenAll;

	g_GroupChatMng.EnterRoom(nRoomID, nRoomType, vtUPID, pLinkInfo->pAdodb);

	//////////////////////////////////////////////////////////////////////////
	
	char m_sendbuf[ANSBUFFER_LEN] = {0};
	gcadd_ans gcaddans = {0};

	nLen = sizeof(gcadd_ans);
	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_GCADD, nLen, nLen);
	
	gcaddans.nRoomID = nRoomID;
	gcaddans.roomtype = nRoomType;

	memcpy(&(m_ansbuf.AnsBuffer), &gcaddans, nLen);
	nLenAll = sizeof(IMANSHEADER) + nLen;
	memcpy(pSend, &m_ansbuf, nLenAll);

	g_LinkMangaer.FreeLink(pLinkInfo);
	g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);
	
	return nLenAll;
}

// �����ӵĿͻ���ǰ���ߣ�����Ⱥ����Ϣ����
// UPIM_REQ_S_GCADD
int OnGcAdd_ex(DWORD dwConnID, ROOMID nRoomID, int nRoomType)
{
	//////////////////////////////////////////////////////////////////////////
	int nLenAll = 0;
	int nLen = 0;
	char pSend[ANSBUFFER_LEN] = {0};
	
	char m_sendbuf[ANSBUFFER_LEN] = {0};
	gc_s_add_ans* ans = (gc_s_add_ans *)m_sendbuf;

	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_S_GCADD);
	
	// json
	Value data_value;
	Value item;  
	Value array;
	FastWriter writer;
	string strdata;

	int packlen = 0;
	int nIndex = 0;
	long nSize = 0;

	GROUP_CHAT_BASE chatInfo;
	chatInfo.m_nRoomId = nRoomID;
	chatInfo.m_nType = nRoomType;
	g_GroupChatMng.GetChatroomInfo(chatInfo);

	item["i"] = (long)chatInfo.m_nRoomId;			// ROOMID
	item["t"] = (int)chatInfo.m_nType;				// ROOMTYPE
	item["m"] = (LPCSTR)chatInfo.m_szMasterID;		// Ⱥ������ID
	item["n"] = (LPCSTR)chatInfo.m_szRoomName;		// Ⱥ������
	item["g"] = (LPCSTR)chatInfo.m_szNote;			// Ⱥ����
	item["d"] = (int)chatInfo.m_bDelFlag;			// Ⱥɾ�����
	array.append( item );

	data_value["ct"] = 1;							// count
	data_value["it"] = array;						// item
	strdata = writer.write(data_value);
	packlen = strdata.length();

	ans->nlen = packlen;
	memcpy(ans->headp, strdata.c_str(), packlen);
	nLen = sizeof(gcinfo_ans2) + packlen /*- sizeof(char)*/;
	m_ansbuf.AnsHeader.PacketLen	= nLen;
	m_ansbuf.AnsHeader.RawLen		= nLen;
	memcpy(&(m_ansbuf.AnsBuffer), ans, nLen);
	nLenAll = sizeof(IMANSHEADER) + nLen;
	memcpy(pSend, &m_ansbuf, nLenAll);
	g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);

	return 0;
}

// UPIM_REQ_GCKICK
int OnGcKickReq(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	int nLen = 0;
	char szKhh[S_USERID_LEN] = {0};
	char pSend[ANSBUFFER_LEN] = {0};

	gcleave_req* m_req = (gcleave_req *)pReceive;
	ROOMID m_roomid = m_req->nRoomID;
	short m_roomtype = m_req->roomtype;
	COPYSTRARRAY(szKhh, m_req->userid);
	short m_usertype = m_req->nUsertype;

	char szError[256] = {0};
	LPOPLINK pLinkInfo = NULL;
	pLinkInfo = g_LinkMangaer.GetLink(szError, sizeof(szError), TRUE);
	if (pLinkInfo == NULL)
		return nLenAll;

	char m_sendbuf[ANSBUFFER_LEN] = {0};
	gcleave_ans* gcleaveans = (gcleave_ans *)m_sendbuf;

	nLen = sizeof(gcleave_ans);
	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead( m_ansbuf, UPIM_REQ_GCKICK, nLen, nLen);

	int nError = g_GroupChatMng.LeaveRoom(m_roomid, m_roomtype, szKhh, pLinkInfo->pAdodb);
	if (nError != eGCError_Success)
	{
		gcleaveans->bSussess = FALSE;
		gcleaveans->nRoomID = m_roomid;
		COPYSTRARRAY(gcleaveans->ErrStr, GetErrorStr(nError));
	}
	else
	{
		gcleaveans->bSussess = TRUE;
		gcleaveans->nRoomID = m_roomid;
	}
	COPYSTRARRAY(gcleaveans->userid, szKhh);
	gcleaveans->nUsertype = m_usertype;

	memcpy(&(m_ansbuf.AnsBuffer), gcleaveans, nLen);
	nLenAll = sizeof(IMANSHEADER) + nLen;
	memcpy(pSend, &m_ansbuf, nLenAll);

	g_LinkMangaer.FreeLink(pLinkInfo);
	g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);

	// �����ӵĿͻ���ǰ���ߣ�����Ⱥ����Ϣ����
	MYSTATE m_state = (MYSTATE)0;
	DWORD dwConnectID = 0;
	g_MongoDBMgr.GetUserState(szKhh, m_state, dwConnectID);
	if (m_state == MYSTATE_NORMAL)
		OnGcKick_ex(dwConnectID, m_roomid, m_roomtype);

	return nLenAll;
}

// ����߳��Ŀͻ���ǰ���ߣ�����Ⱥ����Ϣ����
// UPIM_REQ_S_GCKICK
int OnGcKick_ex(DWORD dwConnID, ROOMID nRoomID, int nRoomType)
{
	int nLenAll = 0;
	int nLen = 0;
	char pSend[ANSBUFFER_LEN] = {0};

	nLen = sizeof(gckick_s_ans);
	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_S_GCKICK, nLen, nLen);

	gckick_s_ans ans = {0};
	ans.nRoomID = nRoomID;
	ans.roomtype = nRoomType;

	memcpy(&(m_ansbuf.AnsBuffer), &ans, nLen);
	nLenAll = sizeof(IMANSHEADER) + nLen;
	memcpy(pSend, &m_ansbuf, nLenAll);

	g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);

	return 0;
}

// UPIM_REQ_GCLEAVE
int OnGcLeaveReq(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	int nLen = 0;
	char szKhh[S_USERID_LEN] = {0};
	char pSend[ANSBUFFER_LEN] = {0};

	gcleave_req* m_req = (gcleave_req *)pReceive;
	ROOMID m_roomid = m_req->nRoomID;
	short m_roomtype = m_req->roomtype;
	COPYSTRARRAY(szKhh, m_req->userid);

	char szError[256] = {0};
	LPOPLINK pLinkInfo = NULL;
	pLinkInfo = g_LinkMangaer.GetLink(szError, sizeof(szError), TRUE);
	if (pLinkInfo == NULL)
		return nLenAll;

	char m_sendbuf[ANSBUFFER_LEN] = {0};
	gcleave_ans* gcleaveans = (gcleave_ans *)m_sendbuf;

	nLen = sizeof(gcleave_ans);
	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_GCLEAVE, nLen, nLen);
	//////////////////////////////////////////////////////////////////////////
// 	m_cs.Lock();
// 	BOOL bDelRoom = FALSE;
// 	GCR_ITER iter;
// 	nError = _GetChatRoom(id, roomtype, iter);
// 	if(eGCError_Success != nError) 
// 	{
// 		m_cs.Unlock();
// 		return nError;
// 	}
// 	// ��ɢ
// 	if ( strcmp(imid, "-1")==0 || EqualUPID(imid, iter->second.m_szMasterID) )
// 	{
// 		iter->second.m_vtUser.clear();
// 		iter->second.m_bDelFlag = true;
// 		bDelRoom = TRUE;
// 	}
// 	EnterCriticalSection(&(iter->second.m_csRoom));
// 	m_cs.Unlock();

	//////////////////////////////////////////////////////////////////////////

	int nError = g_GroupChatMng.LeaveRoom(m_roomid, m_roomtype, szKhh, pLinkInfo->pAdodb);
	if (nError != eGCError_Success)
	{
		gcleaveans->bSussess = FALSE;
		gcleaveans->nRoomID = m_roomid;
		COPYSTRARRAY(gcleaveans->ErrStr, GetErrorStr(nError));
	}
	else
	{
		gcleaveans->bSussess = TRUE;
		gcleaveans->nRoomID = m_roomid;
	}

	memcpy(&(m_ansbuf.AnsBuffer), gcleaveans, nLen);
	nLenAll = sizeof(IMANSHEADER) + nLen;
	memcpy(pSend, &m_ansbuf, nLenAll);

	g_LinkMangaer.FreeLink(pLinkInfo);
	g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);

	return nLenAll;
}

// UPIM_REQ_GPUBLIC
int OnGPublic(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	int nLen = 0;
	char pSend[ANSBUFFER_LEN] = {0};
	public_req* m_req = (public_req *)pReceive;

	char szError[256] = {0};
	LPOPLINK pLinkInfo = NULL;
	pLinkInfo = g_LinkMangaer.GetLink(szError, sizeof(szError), TRUE);
	if (pLinkInfo == NULL)
		return nLenAll;

	char m_sendbuf[ANSBUFFER_LEN] = {0};
	public_ans* listans = (public_ans *)m_sendbuf;

	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_GPUBLIC);

	int publicID = 0;
	CString publicName = _T("");
	CString pcomment = _T("");
	CString welcomecontent = _T("");

	CADOCommand adoCmd(pLinkInfo->pAdodb, "public_get");
	adoCmd.AddInputParameter("@userid", strlen(m_req->userid), (CString)m_req->userid);
	adoCmd.AddInputParameter("@usertype", (int)m_req->nUsertype);

	CADORecordset adoRs(pLinkInfo->pAdodb);
	if(!adoRs.Execute(&adoCmd)) 
	{
		g_LinkMangaer.CheckConnect(pLinkInfo);
		m_ansbuf.AnsHeader.ErrorCode = erServer_DBError;
		TRACE("ִ�����ݿ�ʧ��");
	}
	long nRowCount = adoRs.GetRecordCount();
	//JSON
	if (nRowCount > 0)
	{
		int packlen = 0;
		Reader read;
		Value data_value;
		Value item;  
		Value array;
		FastWriter writer;
		string strdata;
		int nIndex = 0;
		for(long nIdx=0; nIdx<nRowCount; nIdx++,adoRs.MoveNext())
		{
			adoRs.GetFieldValue("id", publicID);						// public id
			adoRs.GetFieldValue("name", publicName);					// name
			adoRs.GetFieldValue("comment", pcomment);					// comment
			adoRs.GetFieldValue("wellcomcontent", welcomecontent);		// wellcomcontent

			item["i"] = publicID;
			item["n"] = (LPCSTR)publicName;
			item["c"] = (LPCSTR)pcomment;
			item["w"] = (LPCSTR)welcomecontent;
			array.append( item );

			data_value["ct"] = ++nIndex;						// count
			data_value["it"] = array;							// item
			strdata = writer.write(data_value);
			packlen = strdata.length();
			if ((0 == (nIdx+1) % GPUBLIC_COUNT) || (nIdx+1 == nRowCount))
			{
				listans->rtnnum = nIndex;
				listans->len = packlen;
				memcpy(listans->headp, strdata.c_str(), packlen);
				nLen = sizeof(public_ans) + packlen /*- sizeof(char)*/;
				m_ansbuf.AnsHeader.PacketLen	= nLen;
				m_ansbuf.AnsHeader.RawLen		= nLen;

				memcpy(&(m_ansbuf.AnsBuffer), listans, nLen);
				nLenAll = sizeof(IMANSHEADER) + nLen;
				memcpy(pSend, &m_ansbuf, nLenAll);
				g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);

				array.clear();
				nIndex = 0;
			}
		}
	}
	else
	{
		listans->rtnnum = 0;
		listans->len = 0;
		nLen = sizeof(public_ans);
		m_ansbuf.AnsHeader.PacketLen	= nLen;
		m_ansbuf.AnsHeader.RawLen		= nLen;

		memcpy(&(m_ansbuf.AnsBuffer), listans, nLen);
		nLenAll = sizeof(IMANSHEADER) + nLen;
		memcpy(pSend, &m_ansbuf, nLenAll);
		g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);
	}

	g_LinkMangaer.FreeLink(pLinkInfo);
	return nLenAll;
}

// UPIM_REQ_PUBLICINFO
int OnPublicInfo(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	int nLen = 0;
	char pSend[ANSBUFFER_LEN] = {0};
	publicinfo_req* m_req = (publicinfo_req *)pReceive;

	char szError[256] = {0};
	LPOPLINK pLinkInfo = NULL;
	pLinkInfo = g_LinkMangaer.GetLink(szError, sizeof(szError), TRUE);
	if (pLinkInfo == NULL)
		return nLenAll;

	char m_sendbuf[ANSBUFFER_LEN] = {0};
	publicinfo_ans* listans = (publicinfo_ans *)m_sendbuf;

	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_PUBLICINFO);
	
	int nID = 0;
	int nProblemtype = 0;
	CString tpName = _T("");

	CADOCommand adoCmd(pLinkInfo->pAdodb, "public_get_info");
	adoCmd.AddInputParameter("@publicid", (int)m_req->publicID);

	CADORecordset adoRs(pLinkInfo->pAdodb);
	if(!adoRs.Execute(&adoCmd)) 
	{
		g_LinkMangaer.CheckConnect(pLinkInfo);
		m_ansbuf.AnsHeader.ErrorCode = erServer_DBError;
		TRACE("ִ�����ݿ�ʧ��");
	}
	long nRowCount = adoRs.GetRecordCount();
	//JSON
	if (nRowCount > 0)
	{
		int packlen = 0;
		Reader read;
		Value data_value;
		Value item;  
		Value array;
		FastWriter writer;
		string strdata;
		int nIndex = 0;
		for(long nIdx=0; nIdx<nRowCount; nIdx++,adoRs.MoveNext())
		{
			adoRs.GetFieldValue("id", nID);						// id
			adoRs.GetFieldValue("tpname", tpName);				// tpname
			adoRs.GetFieldValue("problemtype", nProblemtype);	// problemtype

			item["i"] = nID;
			item["n"] = (LPCSTR)tpName;
			item["p"] = nProblemtype;
			array.append( item );
			data_value["ct"] = ++nIndex;						// count
		}
		data_value["it"] = array;								// item
		strdata = writer.write(data_value);
		packlen = strdata.length();
		// send
		listans->publicID = m_req->publicID;
		listans->rtnnum = nIndex;
		listans->len = packlen;
		memcpy(listans->headp, strdata.c_str(), packlen);
		nLen = sizeof(publicinfo_ans) + packlen /*- sizeof(char)*/;
		m_ansbuf.AnsHeader.PacketLen	= nLen;
		m_ansbuf.AnsHeader.RawLen		= nLen;
	}
	else
	{
		listans->publicID = m_req->publicID;
		listans->rtnnum = 0;
		listans->len = 0;
		nLen = sizeof(publicinfo_ans);
		m_ansbuf.AnsHeader.PacketLen	= nLen;
		m_ansbuf.AnsHeader.RawLen		= nLen;
	}

	memcpy(&(m_ansbuf.AnsBuffer), listans, nLen);
	nLenAll = sizeof(IMANSHEADER) + nLen;
	memcpy(pSend, &m_ansbuf, nLenAll);
	g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);

	g_LinkMangaer.FreeLink(pLinkInfo);
	return nLenAll;
}

// UPIM_REQ_PUBCONCLOSE
int OnPublicConClose(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	int nLen = 0;
	char pSend[ANSBUFFER_LEN] = {0};
	pubconclose_req* m_req = (pubconclose_req *)pReceive;

	// ���Ͽ���Ϣ���͵���̨PublicManage
#ifdef PUBLICMNG
	g_PublicMng.ConnectClose(m_req->userid,m_req->SevcId);
#endif
	return nLenAll;
}

// UPIM_REQ_OLNOTIFY
int OnOLNotify(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	int nLen = 0;
	char pSend[ANSBUFFER_LEN] = {0};
	olnotify_req* m_req = (olnotify_req *)pReceive;
	int nState = m_req->nUserstate;

	long nszLen = m_req->len;
	char szJson[MAX_SEND_BUF_LEN] = {0};
	strncpy(szJson, m_req->headp, nszLen);

	//////////////////////////////////////////////////////////////////////////
	Value value;  
	Reader read;  
	if ( !read.parse( szJson,value ) )  
	{  
		return -1;  
	}
	g_pList->PushUSER(m_req->userid, (BYTE)m_req->nUserstate, m_req->headp);
	//OP_LOG_INFO()
	return nLenAll;
}

// UPIM_REQ_OFFMSG
// ȡ��������ϢЭ�����json����һ�δ����������Ϣ���xml��base64����֮�����ṹ��
int OnOFFMsgReq(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	int nLen = 0;
	char pSend[ANSBUFFER_LEN] = {0};
	offmsg_req* m_req = (offmsg_req *)pReceive;

	if (strlen(m_req->userid) == 0)
		return 0;

	char szError[256] = {0};
	LPOPLINK pLinkInfo = NULL;
	pLinkInfo = g_LinkMangaer.GetLink(szError, sizeof(szError), TRUE);
	if (pLinkInfo == NULL)
		return nLenAll;

	char m_sendbuf[ANSBUFFER_LEN] = {0};
	offmsg_ans* m_ans = (offmsg_ans *)m_sendbuf;

	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_OFFMSG);
	//////////////////////////////////////////////////////////////////////////
	CADOCommand adoCmd(pLinkInfo->pAdodb, "icq_get_offmsg");
	adoCmd.AddInputParameter("@icqid", strlen(m_req->userid), (CString)m_req->userid);
	CADORecordset adoRs(pLinkInfo->pAdodb);
	if(!adoRs.Execute(&adoCmd)) 
	{
		g_LinkMangaer.CheckConnect(pLinkInfo);
		TRACE("ִ�����ݿ�ʧ��");
		return 0;
	}
	long nRowCount = adoRs.GetRecordCount();
	if (nRowCount > 0)
	{
		CString src_id = _T("");
		long nTime = 0;
		int nType = 0;
		CString strMsg = _T("");
		CString strNick = _T("");
		char szMsgBase64[4*1024] = {0};
		ROOMID roomid = 0;
		int   roomtype = 0;
		OFFMSG offMsg = {0};

		//json
		int packlen = 0;
		Reader read;
		Value data_value;
		Value item;  
		Value array;
		FastWriter writer;
		string strdata;
		int nIndex = 0;
		
		for(long nIdx=0; nIdx<nRowCount; nIdx++,adoRs.MoveNext())
		{
			adoRs.GetFieldValue("src_id", src_id);
			src_id.Trim();
			COPYSTRARRAY(offMsg.m_szDesID, m_req->userid);
			COPYSTRARRAY(offMsg.m_szSrcID, src_id);
			adoRs.GetFieldValue("time", offMsg.m_nSendTime);
			adoRs.GetFieldValue("type", nType);
			offMsg.m_ucFormat = (BYTE)nType;
			adoRs.GetFieldValue("message", strMsg);
			COPYSTRARRAY(offMsg.m_szMsg, strMsg);
			int	nBaseStrLen = Base64_Encode((BYTE *)(LPCTSTR)strMsg, strMsg.GetLength(), (BYTE *)szMsgBase64, sizeof(szMsgBase64), TRUE);
			szMsgBase64[nBaseStrLen] = 0;
			adoRs.GetFieldValue("src_name", strNick);
			strNick.Trim();
			adoRs.GetFieldValue("roomid", roomid);
			adoRs.GetFieldValue("roomtype", roomtype);

			item["roomtype"] = roomtype;
			item["src_id"] = offMsg.m_szSrcID;
			item["time"] = offMsg.m_nSendTime;
			item["format"] = offMsg.m_ucFormat;
			item["msg"] = szMsgBase64;
			item["roomid"] = roomid;
			item["rnick"] = (LPCTSTR)strNick;
			array.append( item );
			
			data_value["ct"] = ++nIndex;						// count
			data_value["it"] = array;							// item
			strdata = writer.write(data_value);
			packlen = strdata.length();
			// �����������ݰ�
			if (packlen>2048 || (nIdx+1 == nRowCount))
			{
				m_ans->rtnnum = nIndex;
				m_ans->len = packlen;
				memcpy(m_ans->headp, strdata.c_str(), packlen);
				nLen = sizeof(offmsg_ans) + packlen /*- sizeof(char)*/;
				m_ansbuf.AnsHeader.PacketLen	= nLen;
				m_ansbuf.AnsHeader.RawLen		= nLen;

				memcpy(&(m_ansbuf.AnsBuffer), m_ans, nLen);
				nLenAll = sizeof(IMANSHEADER) + nLen;
				memcpy(pSend, &m_ansbuf, nLenAll);
				g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);

				array.clear();
				nIndex = 0;
			}

			 // Ⱥ����Ϣ�Ѿ����뵽��ʷ������,����Ҫ�ٴβ�����
			if(offMsg.m_ucFormat != eMsgFormat_OutRoom && offMsg.m_ucFormat != eMsgFormat_Prdt && roomtype!=0 && strlen(offMsg.m_szDesID) > 0)
				g_pList->PushHisMsg(offMsg.m_szSrcID, offMsg.m_szDesID, offMsg.m_ucFormat, offMsg.m_nSendTime, offMsg.m_szMsg);
		}
	}
	if(nRowCount > 0)
	{
		CADOCommand adoCmd2(pLinkInfo->pAdodb, "icq_del_message");
		adoCmd2.AddInputParameter("@icqid", strlen(m_req->userid), (CString)m_req->userid);
		adoCmd2.Execute();
	}

	g_LinkMangaer.FreeLink(pLinkInfo);
	return 0;
}

// �ͻ��������Ƶİ�
int OnPkgReq(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	int nLen = 0;
	char pSend[ANSBUFFER_LEN] = {0};
	send_pkg_req* m_req = (send_pkg_req *)pReceive;

	char m_sendbuf[ANSBUFFER_LEN] = {0};
	s_send_pkg_ans* m_ans = (s_send_pkg_ans *)m_sendbuf;
	COPYSTRARRAY(m_ans->cFromuserid, m_req->cFromuserid);
	m_ans->nrequest = m_req->nrequest;
	m_ans->nUsertype = m_req->nUsertype;
	m_ans->pkglen = m_req->pkglen;
	memcpy(m_ans->pkg, m_req->pkg, m_ans->pkglen);

	nLen = sizeof(s_send_pkg_ans) + m_ans->pkglen /*- sizeof(char)*/;
	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_S_PKG, nLen, nLen);
	nLenAll = sizeof(IMANSHEADER) + nLen;

	MYSTATE m_state = (MYSTATE)0;
	DWORD dwConnectID = 0;
	g_MongoDBMgr.GetUserState(m_req->cTouserid, m_state, dwConnectID);
	if (m_state == MYSTATE_NORMAL )		//���� 
	{
		memcpy(&(m_ansbuf.AnsBuffer), m_ans, nLen);
		memcpy(pSend, &m_ansbuf, nLenAll);
		g_MySever.m_Server.Send((CONNID)dwConnectID, (LPBYTE)pSend, nLenAll);
	}

	return 0;
}

// UPIM_REQ_ALLTGROOM
int OnGetAllTgRoom(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	int nLen = 0;
	char pSend[ANSBUFFER_LEN] = {0};
	alltgroom_req* m_req = (alltgroom_req *)pReceive;

	char m_sendbuf[ANSBUFFER_LEN] = {0};
	alltgroom_ans* listans = (alltgroom_ans *)m_sendbuf;

	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_ALLTGROOM);

	//////////////////////////////////////////////////////////////////////////
	//
	//�������� ͨ���ӿ�get��������������Ϣ������json

	int packlen = 0;
	Value data_value;
	Value item;  
	Value array;
	FastWriter writer;
	string strdata;
	int nIndex = 0;
	
	MapFxsToHouseInfo* pFxsToHouseInfo = g_FxsHDManage.GetFxsToHouseInfo();
	CString FxsID(m_req->userid);
	MapFxsToHouseInfo::iterator it_FxsToHouse = pFxsToHouseInfo->find(FxsID);
	if (it_FxsToHouse!=pFxsToHouseInfo->end())
	{
		for(long nIdx=0; nIdx<(it_FxsToHouse->second).size(); nIdx++)
		{
			item["i"] = atoi((LPCTSTR)(it_FxsToHouse->second).at(nIdx).RoomId);
			item["n"] = (LPCTSTR)(it_FxsToHouse->second).at(nIdx).RoomName;
			item["c"] = (LPCTSTR)(it_FxsToHouse->second).at(nIdx).Description;
			array.append( item );
			data_value["ct"] = ++nIndex;						// count
			data_value["it"] = array;							// item
			data_value["ia"] = (LPCTSTR)(it_FxsToHouse->second).at(nIdx).ImageAddr;
		}
		strdata = writer.write(data_value);
		packlen = strdata.length();
		//JSON

		listans->rtnnum = nIndex;
		listans->len = packlen;
		memcpy(listans->headp, strdata.c_str(), packlen);
		nLen = sizeof(public_ans) + packlen /*- sizeof(char)*/;
		m_ansbuf.AnsHeader.PacketLen	= nLen;
		m_ansbuf.AnsHeader.RawLen		= nLen;

		memcpy(&(m_ansbuf.AnsBuffer), listans, nLen);
	}
	nLenAll = sizeof(IMANSHEADER) + nLen;
	memcpy(pSend, &m_ansbuf, nLenAll);
	g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);
	
	return nLenAll;
}

// UPIM_REQ_ALLTGROOMEX
int OnGetAllTgRoomEx(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	int nLen = 0;
	char pSend[ANSBUFFER_LEN] = {0};
	alltgroomEx_req* m_req = (alltgroomEx_req*)pReceive;

	char m_sendbuf[ANSBUFFER_LEN] = {0};
	alltgroom_ans* listans = (alltgroom_ans *)m_sendbuf;

	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_ALLTGROOMEX);

	//////////////////////////////////////////////////////////////////////////
	//
	//�������� ͨ���ӿ�get��������������Ϣ������json

	int packlen = 0;
	Value data_value;
	Value data_value2;
	Value item;  
	
	FastWriter writer;
	string strdata;                        
	int nIndex = 0;
	int nAnalystIndex = 0;
	short nMarket = m_req->nMarket;

	MapRoomIDToFxsInfo* pRoomIdToFxsInfo = g_FxsHDManage.GetRoomIDToFxsDataEx(); //���з����Ӧ���з���ʦ����
	MapMarketToVipHouseinfo* pVipHouseInfo = g_FxsHDManage.GetVipHouseInfo();    //����VIP������Ϣ
	vector<FXSVipHouseInfo> vFxsVipHouse = (*pVipHouseInfo)[nMarket];            //�ض��г��µķ�����Ϣ
	for (int i = 0;i<vFxsVipHouse.size();i++)
	{
		Value data_value1;
		MapRoomIDToFxsInfo::iterator itmap_RoomIDToFxs = pRoomIdToFxsInfo->find(vFxsVipHouse[i].RoomId); //һ������Ŷ�Ӧ�ķ���ʦ�뷿����Ϣ
		if (itmap_RoomIDToFxs != pRoomIdToFxsInfo->end())
		{
			RoomAllFxsData roomToFxs = itmap_RoomIDToFxs->second;
			vector<FXSDataEx> tempFxsData = roomToFxs.FxsData;
			FXSVipHouseInfo tempVipHouse = roomToFxs.VipHouse;
			Value array;
			nAnalystIndex = 0;
			int onLineCount = 0 ; 

			for(long nIdx=0; nIdx<tempFxsData.size(); nIdx++)
			{
				// �жϵ�ǰ����ʦ�Ƿ����� 
				MYSTATE m_state = (MYSTATE)0;
				DWORD dwConnectID = 0;
				g_MongoDBMgr.GetUserState(tempFxsData[nIdx].AnalystId, m_state, dwConnectID);
				if( m_state == MYSTATE_NORMAL)
				{
					// ��ǰ�������ʦ�������� 
					data_value1["olc"] = ++onLineCount ;
					item["ol"] = 1 ; // ����ʦ���� 
				}
				else
				{
					item["ol"] = 0 ; // ����ʦ���� 
				}

				// Ĭ����� Ϊ0 
				if( onLineCount == 0 )
				{
					data_value1["olc"] =  0; 
				}
				item["i"] = atoi((LPCTSTR)tempFxsData[nIdx].AnalystId);
				item["n"] = (LPCTSTR)tempFxsData[nIdx].AnalystName;
				item["ia"] = (LPCTSTR)tempFxsData[nIdx].AnalystImg;
				item["sa"] = (LPCTSTR)tempFxsData[nIdx].SpecialtyArea;
		
				array.append( item );
				data_value1["ac"] = ++nAnalystIndex;
				data_value1["it"] = array;							// item
			}
			nIndex++;
			data_value1["vip"] = (LPCTSTR)(tempVipHouse.VipType);
			data_value1["r"] = (LPCTSTR)(tempVipHouse.RoomId);
			data_value1["rn"] = (LPCTSTR)(tempVipHouse.RoomName);
			data_value1["ic"] = tempVipHouse.IconState;

			data_value.append(data_value1);
		}	
	}	
	data_value2["ct"] = nIndex;
	data_value2["d"] = data_value;
	strdata = writer.write(data_value2);
	packlen = strdata.length();
	listans->rtnnum = nIndex;
	listans->len = packlen;
	memcpy(listans->headp, strdata.c_str(), packlen);
	nLen = sizeof(public_ans) + packlen /*- sizeof(char)*/;
	m_ansbuf.AnsHeader.PacketLen	= nLen;
	m_ansbuf.AnsHeader.RawLen		= nLen;
	memcpy(&(m_ansbuf.AnsBuffer), listans, nLen);

	nLenAll = sizeof(IMANSHEADER) + nLen;
	memcpy(pSend, &m_ansbuf, nLenAll);
	g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);
	return nLenAll;
}

// UPIM_REQ_ALLROOMTOUSER
int OnGetAllRoomToUser(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	int nLen = 0;
	//char pSend[ANSBUFFER_LEN] = {0};
	tggetuserbyroomid_req* m_req = (tggetuserbyroomid_req*)pReceive;

	//char m_sendbuf[ANSBUFFER_LEN] = {0};
	//alltgroom_ans* listans = (alltgroom_ans *)m_sendbuf;

	//IMANSBUFFER m_ansbuf = {0};
	//InitAnsBufHead(m_ansbuf, UPIM_REQ_ALLROOMTOUSER);
	
	int packlen = 0;
	string strdata;

	int nIndex = 0;
	int RoomID = m_req->roomid;
	vector<CString> vUserName;
	vUserName= (*g_FxsHDManage.GetRoomUser())[RoomID];
	sort(vUserName.begin() ,vUserName.end()) ; 
	vUserName.erase(unique(vUserName.begin(),vUserName.end()),vUserName.end());
	// �����Ƿ����ߺ��������� 
	std::sort( vUserName.begin() ,vUserName.end() ,compare_by_online_name) ; 
	FastWriter writer;
	Value data_value;
	Value item;
	Value array ; 
	int nCount = vUserName.size();
	for (int j = 0;j<vUserName.size();j++)
	{
		// ����Ҫ�ж���ǰ�û��Ƿ����� ���ҽ�����״̬�����ͻ��� 
		// �жϵ�ǰ����ʦ�Ƿ����� 
		MYSTATE m_state = (MYSTATE)0;
		DWORD dwConnectID = 0;
		g_MongoDBMgr.GetUserState(vUserName[j], m_state, dwConnectID);
		int isOnline = 0 ; 

		if( m_state == MYSTATE_NORMAL)
		{
			isOnline  = 1 ; 
		}
		else
		{
			isOnline = 0 ; 
		}
		item["o"]   = isOnline ;
		item["n"] = (LPCSTR)vUserName[j] ; 
		array.append(item) ; 
		//item.append(Value(vUserName[j]));
		nIndex++;
		if(0 == (j+1)%REFRESH_TGUSER_COUNT || (j+1 == nCount))
		{

			char pSend[ANSBUFFER_LEN] = {0};
			IMANSBUFFER m_ansbuf = {0};
			InitAnsBufHead(m_ansbuf, UPIM_REQ_ALLROOMTOUSER);
			char m_sendbuf[ANSBUFFER_LEN] = {0};
			alltgroom_ans* listans = (alltgroom_ans *)m_sendbuf;

			data_value["a"] = array;
			data_value["c"] = nIndex;
			data_value["r"] = RoomID;
			strdata = writer.write(data_value);
			packlen = strdata.length();

			data_value.clear();
			item.clear();
			array.clear() ; 

			listans->rtnnum = nIndex;
			listans->len = packlen;
			memcpy(listans->headp, strdata.c_str(), packlen);
			nLen = sizeof(public_ans) + packlen /*- sizeof(char)*/;
			m_ansbuf.AnsHeader.PacketLen	= nLen;
			m_ansbuf.AnsHeader.RawLen		= nLen;
			memcpy(&(m_ansbuf.AnsBuffer), listans, nLen);

			nLenAll = sizeof(IMANSHEADER) + nLen;
			memcpy(pSend, &m_ansbuf, nLenAll);
			g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);
			nIndex = 0;
		}
	}
	return nLenAll;

}

// UPIM_REQ_GETGROUP
// im2.0�汾�з�����Ա�Զ������
int OnGetSelfGroup(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	int nLen = 0;
	char pSend[ANSBUFFER_LEN] = {0};
	getgroup_req* m_req = (getgroup_req *)pReceive;

	if (strlen(m_req->userid) == 0)
		return 0;

	char szError[256] = {0};
	LPOPLINK pLinkInfo = NULL;
	pLinkInfo = g_LinkMangaer.GetLink(szError, sizeof(szError), TRUE);
	if (pLinkInfo == NULL)
		return nLenAll;

	char m_sendbuf[ANSBUFFER_LEN] = {0};
	getgroup_ans* m_ans = (getgroup_ans *)m_sendbuf;

	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_GETGROUP);
	//////////////////////////////////////////////////////////////////////////
	CADOCommand adoCmd(pLinkInfo->pAdodb, "analys_get_group");
	adoCmd.AddInputParameter("@analysid", strlen(m_req->userid), (CString)m_req->userid);
	CADORecordset adoRs(pLinkInfo->pAdodb);
	if(!adoRs.Execute(&adoCmd)) 
	{
		g_LinkMangaer.CheckConnect(pLinkInfo);
		TRACE("ִ�����ݿ�ʧ��");
		return 0;
	}
	long nRowCount = adoRs.GetRecordCount();
	if (nRowCount > 0)
	{
		CString strGroupID = _T("");
		CString strGroupName = _T("");
		
		//json
		int packlen = 0;
		Reader read;
		Value data_value;
		Value item;  
		Value array;
		FastWriter writer;
		string strdata;
		int nIndex = 0;

		for(long nIdx=0; nIdx<nRowCount; nIdx++,adoRs.MoveNext())
		{
			adoRs.GetFieldValue("groupid", strGroupID);
			strGroupID.Trim();
			adoRs.GetFieldValue("groupname", strGroupName);
			strGroupName.Trim();

			item["gid"] = (LPCSTR)strGroupID;
			item["gname"] = (LPCSTR)strGroupName;
			item["gnum"] = nIdx+1;

			array.append( item );
			data_value["ct"] = ++ nIndex;						// count
			data_value["it"] = array;							// item
		}

		strdata = writer.write(data_value);
		packlen = strdata.length();

		m_ans->rtnnum = nIndex;
		m_ans->len = packlen;
		memcpy(m_ans->headp, strdata.c_str(), packlen);
		nLen = sizeof(getgroup_ans) + packlen /*- sizeof(char)*/;
		m_ansbuf.AnsHeader.PacketLen	= nLen;
		m_ansbuf.AnsHeader.RawLen		= nLen;

		memcpy(&(m_ansbuf.AnsBuffer), m_ans, nLen);
		nLenAll = sizeof(IMANSHEADER) + nLen;
		memcpy(pSend, &m_ansbuf, nLenAll);
		g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);
	}
	else
	{
		m_ans->rtnnum = 0;
		m_ans->len = 0;
		nLen = sizeof(getgroup_ans) /*- sizeof(char)*/;
		m_ansbuf.AnsHeader.PacketLen	= nLen;
		m_ansbuf.AnsHeader.RawLen		= nLen;

		memcpy(&(m_ansbuf.AnsBuffer), m_ans, nLen);
		nLenAll = sizeof(IMANSHEADER) + nLen;
		memcpy(pSend, &m_ansbuf, nLenAll);
		g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);
	}
	g_LinkMangaer.FreeLink(pLinkInfo);
	return 0;
}

// UPIM_REQ_GETGUSER
// im2.0�汾�з�����Աȡ���Զ�������µĿͻ��б�
int OnGetSelfGroupUsers(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	int nLen = 0;
	char pSend[ANSBUFFER_LEN] = {0};
	getguser_req* m_req = (getguser_req *)pReceive;

	if (strlen(m_req->userid) == 0)
		return 0;

	char szError[256] = {0};
	LPOPLINK pLinkInfo = NULL;
	pLinkInfo = g_LinkMangaer.GetLink(szError, sizeof(szError), TRUE);
	if (pLinkInfo == NULL)
		return nLenAll;

	char m_sendbuf[ANSBUFFER_LEN] = {0};
	getguser_ans* m_ans = (getguser_ans *)m_sendbuf;

	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_GETGUSER);
	//////////////////////////////////////////////////////////////////////////
	CADOCommand adoCmd(pLinkInfo->pAdodb, "analysgroup_get_user");
	adoCmd.AddInputParameter("@groupid", (int)m_req->nGroupID);
	adoCmd.AddInputParameter("@analysid", strlen(m_req->userid), (CString)m_req->userid);

	CADORecordset adoRs(pLinkInfo->pAdodb);
	if(!adoRs.Execute(&adoCmd)) 
	{
		g_LinkMangaer.CheckConnect(pLinkInfo);
		TRACE("ִ�����ݿ�ʧ��");
		return 0;
	}
	long nRowCount = adoRs.GetRecordCount();
	if (nRowCount > 0)
	{
		CString strClientID = _T("");
		//json
		int packlen = 0;
		Reader read;
		Value data_value;
		Value item;  
		Value array;
		FastWriter writer;
		string strdata;
		int nIndex = 0;

		for(long nIdx=0; nIdx<nRowCount; nIdx++,adoRs.MoveNext())
		{
			adoRs.GetFieldValue("clientid", strClientID);
			strClientID.Trim();

			item.append(Value((LPCSTR)strClientID));
			nIndex++;
			if(0 == (nIdx+1)%REFRESH_TGUSER_COUNT || (nIdx+1 == nRowCount))
			{
				data_value["it"] = item;
				data_value["ct"] = nIndex;
				strdata = writer.write(data_value);
				packlen = strdata.length();

				data_value.clear();
				item.clear();

				m_ans->nGroupID = m_req->nGroupID;
				m_ans->rtnnum = nIndex;
				m_ans->len = packlen;
				memcpy(m_ans->headp, strdata.c_str(), packlen);
				nLen = sizeof(getguser_ans) + packlen /*- sizeof(char)*/;
				m_ansbuf.AnsHeader.PacketLen	= nLen;
				m_ansbuf.AnsHeader.RawLen		= nLen;

				memcpy(&(m_ansbuf.AnsBuffer), m_ans, nLen);
				nLenAll = sizeof(IMANSHEADER) + nLen;
				memcpy(pSend, &m_ansbuf, nLenAll);
				g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);
				nIndex = 0;
			}
		}
	}
	else
	{
		m_ans->nGroupID = m_req->nGroupID;
		m_ans->rtnnum = 0;
		m_ans->len = 0;
		nLen = sizeof(getguser_ans) /*- sizeof(char)*/;
		m_ansbuf.AnsHeader.PacketLen	= nLen;
		m_ansbuf.AnsHeader.RawLen		= nLen;

		memcpy(&(m_ansbuf.AnsBuffer), m_ans, nLen);
		nLenAll = sizeof(IMANSHEADER) + nLen;
		memcpy(pSend, &m_ansbuf, nLenAll);
		g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);
	}
	g_LinkMangaer.FreeLink(pLinkInfo);
	return 0;
}

// UPIM_REQ_ADDGROUP
// im2.0�汾�з�����Ա�༭�Զ������
int OnSetSelfGroup(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	int nLen = 0;
	char pSend[ANSBUFFER_LEN] = {0};

	// ��ÿͻ��˷��͹��������ݰ� 
	addgroup_req* m_req = (addgroup_req*)pReceive ; 
	
	string strUserID = m_req->userid ; 
	if (strlen(m_req->userid) == 0)
		return 0;

	char szJson[MAX_SEND_BUF_LEN] = {0};
	strncpy(szJson, m_req->headp, m_req->len);

	if(!szJson)
		return 0 ; 

	// ���  ��ʽΪ{��type������ɾ��or��ӡ� ,"name":"��������","gid":"����ID"} ����ID�������᷵��һ���Զ����������ֹ�ȥ 
	Value value_get ; 
	Reader reader_get ; 
	if( !(reader_get.parse(szJson ,value_get) ))
		return 0 ; 
	int iType = atoi(value_get["type"].asString().c_str()) ; 
	string strGroupName = value_get["name"].asString() ;
	int groupID = atoi(value_get["gID"].asString().c_str()) ; 

	CString name(strGroupName.c_str());

	char szError[256] = {0};
	LPOPLINK pLinkInfo = NULL;
	pLinkInfo = g_LinkMangaer.GetLink(szError, sizeof(szError), TRUE);
	if (pLinkInfo == NULL)
		return nLenAll;

	Value value ; 
	Reader reader ;
	FastWriter writer ; 
	string strdata ; 
	int    packLen ; 

	// ����˷��͵İ�  
	char m_sendbuf[ANSBUFFER_LEN] = {0};
	addgroup_ans* m_ans = (addgroup_ans *)m_sendbuf;

	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_ADDGROUP);

	if( iType == 1 )
	{
		// ��ѯ���ݿ�  �ڶ�Ӧ�ı���в����½����飬����������ķ���ʦ�������Ϳͻ���GroupID
		//////////////////////////////////////////////////////////////////////////
		CADOCommand adoCmd(pLinkInfo->pAdodb, "analys_add_group");
		adoCmd.AddInputParameter("@analysid", strlen(m_req->userid), (CString)m_req->userid);
		adoCmd.AddInputParameter("@groupname", strlen(strGroupName.c_str()) ,name);

		CADORecordset adoRs(pLinkInfo->pAdodb);
		if(!adoRs.Execute(&adoCmd)) 
		{
			g_LinkMangaer.CheckConnect(pLinkInfo);
			TRACE("ִ�����ݿ�ʧ��");
			g_LinkMangaer.FreeLink(pLinkInfo); 
			return 0;
		}
		CString strGroupID = _T("");  
		long nRowCount = adoRs.GetRecordCount();
		if( nRowCount > 0 )
		{
			// �������ݿ�ɹ� 
			for(long nIdx=0; nIdx<nRowCount; nIdx++,adoRs.MoveNext())
			{
				adoRs.GetFieldValue("groupid", strGroupID);
				strGroupID.Trim() ; 
				value["gid"] = (LPCSTR)strGroupID ; 
				value["gname"] = (LPCSTR)name ; 
				CString strType = "1" ; 
				value["type"]  = (LPCSTR)strType ; 
			}
		}
		else
		{
			// �������ݿ�ʧ�� 
			// ��ѯ���ݿ�  �ڶ�Ӧ�ı���в����½����飬����������ķ���ʦ�������Ϳͻ���GroupID
		}
	}
	else if( iType == 0 )
	{

		// ɾ��������ɾ���÷���ʦ�����Ӧ�ķ���
		//////////////////////////////////////////////////////////////////////////
		CADOCommand adoCmd(pLinkInfo->pAdodb, "analys_del_group");
		adoCmd.AddInputParameter("@groupid",groupID );

		CADORecordset adoRs(pLinkInfo->pAdodb);
		if(!adoRs.Execute(&adoCmd)) 
		{
			g_LinkMangaer.CheckConnect(pLinkInfo);
			TRACE("ִ�����ݿ�ʧ��");
			g_LinkMangaer.FreeLink(pLinkInfo); 
			return 0;
		}

		long nRowCount = adoRs.GetRecordCount();
		if( nRowCount > 0 )
		{
			CString strGroupID = _T("") ;
			strGroupID.Format("%d",groupID) ; 
			value["gid"] = (LPCSTR)strGroupID ; 
			value["gname"] = (LPCSTR)name ; 
			CString strType = "0" ; 
			value["type"]  = (LPCSTR)strType ; 
		}
		else
		{

		}

		//// ɾ�������µ����г�Ա 
		CADOCommand adoCmd1(pLinkInfo->pAdodb, "analysgroup_del_user2");
		adoCmd1.AddInputParameter("@groupid",groupID );

		CADORecordset adoRs1(pLinkInfo->pAdodb);
		if(!adoRs1.Execute(&adoCmd1)) 
		{
			g_LinkMangaer.CheckConnect(pLinkInfo);
			TRACE("ִ�����ݿ�ʧ��");
			g_LinkMangaer.FreeLink(pLinkInfo); 
			return 0;
		}

		long nRowCount1 = adoRs1.GetRecordCount() ; 
		if( nRowCount1 > 0 )
		{

		}
		else
		{

		}
	}

	/////////////////////////////////////////////////////////////////
	// ��� ���͸��ͻ��� 
	/////////////////////////////////////////////////////////////////
	// (1)���
	strdata = writer.write(value) ; 
	packLen = strdata.length() ; 

	m_ans->flag = 1 ; 
	m_ans->rtnnum = 1 ; 
	m_ans->len    = packLen ;
	memcpy(m_ans->headp ,strdata.c_str() ,packLen) ; 

	nLen = sizeof(addgroup_ans) + packLen;
	m_ansbuf.AnsHeader.PacketLen	= nLen;
	m_ansbuf.AnsHeader.RawLen		= nLen;

	memcpy(&(m_ansbuf.AnsBuffer), m_ans, nLen);
	nLenAll = sizeof(IMANSHEADER) + nLen;
	memcpy(pSend, &m_ansbuf, nLenAll);

	// (2)���Ͱ� 
	g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);

	g_LinkMangaer.FreeLink(pLinkInfo); 
	
	return 0;
}

// UPIM_REQ_MODGUSER
// im2.0�汾�з�����Ա�༭�Զ������Ŀͻ��б�
int OnSetSelfGroupUser(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	int nLen = 0;
	char pSend[ANSBUFFER_LEN] = {0};
	modguser_req* m_req = (modguser_req *)pReceive;

	string strUserID = m_req->userid ; 
	if (strlen(m_req->userid) == 0)
		return 0;

	char szJson[MAX_SEND_BUF_LEN] = {0};
	strncpy(szJson, m_req->headp, m_req->len);

	if(!szJson)
		return 0 ; 

	char szError[256] = {0};
	LPOPLINK pLinkInfo = NULL;
	pLinkInfo = g_LinkMangaer.GetLink(szError, sizeof(szError), TRUE);
	if (pLinkInfo == NULL)
		return nLenAll;

	char m_sendbuf[ANSBUFFER_LEN] = {0};
	nLen = sizeof(modguser_ans) ; 
	modguser_ans* m_ans = (modguser_ans *)m_sendbuf;
	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_MODGUSER );
	
	int groupID = 0 ;
	int iType = -1 ;
	CString clientID = _T("") ; 

	//            Դ ��ID                ��������           �Ƴ��ĳ�Ա 
	//   �������ͣ�
	//   0 ��ʾ ���ͻ���Ա����ID���Ƴ� 
	//   1 ��ʾ ���ͻ���Ա��ӵ���ID��
	// json�� { "groupID":"XXX" ,"nType":"XXX" ,"item":[{"clientID":"XXX"},...,{"clientID":"XXX"}]}

	int packlen = 0 ; 
	Reader reader ; 
	Value value ; 
	Value data_value ; 
	FastWriter writer ; 
	string strdata ; 

	if( reader.parse(szJson,value) != NULL)
	{
		groupID = value["g"].asInt() ; 
		iType = value["T"].asInt() ; 

		Value val_array = value["i"] ; 
		int iSize = val_array.size() ; 

		for( int i = 0 ; i < iSize ; i++)
		{
			clientID = val_array[i]["c"].asCString() ;
			
			if( iType == 1)
			{
				// �����toGroupID ��ӳ�Ա 
				CADOCommand adoCmd(pLinkInfo->pAdodb, "analysgroup_add_user");
				adoCmd.AddInputParameter("@groupid", groupID) ;
				adoCmd.AddInputParameter("@clientid", strlen(clientID), clientID) ;
				adoCmd.AddInputParameter("@analysid", strlen(m_req->userid), (CString)m_req->userid);
				CADORecordset adoRs(pLinkInfo->pAdodb);
				if(!adoRs.Execute(&adoCmd)) 
				{
					g_LinkMangaer.CheckConnect(pLinkInfo);
					TRACE("ִ�����ݿ�ʧ��");
					return 0;
				}
				else
				{
				}
			}
			else if( iType == 0)
			{
				CADOCommand adoCmd(pLinkInfo->pAdodb, "analysgroup_del_user");
				adoCmd.AddInputParameter("@groupid", groupID) ;
				adoCmd.AddInputParameter("@clientid", strlen(clientID), clientID) ;
				CADORecordset adoRs(pLinkInfo->pAdodb);
				if(!adoRs.Execute(&adoCmd)) 
				{
					g_LinkMangaer.CheckConnect(pLinkInfo);
					TRACE("ִ�����ݿ�ʧ��");
					return 0;
				}
			}
		}

	}

	// ��Ҫ��ӵ��˺ͷ���Ŷ����͸��ͻ��ˣ����Զ������������·�����Ϣ����Ҫ�����Զ������������Щ�û�
	CString strdata_ ; 
	strdata_.Format("%s" ,szJson) ;  

	packlen = strdata_.GetLength() ;
	memcpy(m_ans->headp ,szJson ,packlen) ; 
	
	m_ans->len = nLen + packlen ; 
	nLen  = sizeof(addgroup_ans) + packlen ;
	m_ansbuf.AnsHeader.PacketLen = nLen ; 
	m_ansbuf.AnsHeader.RawLen    = nLen ; 
	memcpy(&(m_ansbuf.AnsBuffer) ,m_ans ,nLen) ;

	nLenAll = sizeof(IMANSHEADER) + nLen ; 
	memcpy(pSend ,&m_ansbuf ,nLenAll) ; 
	g_MySever.m_Server.Send( (CONNID)dwConnID, (LPBYTE)pSend, nLenAll ) ; 

	g_LinkMangaer.FreeLink(pLinkInfo); 
	return 0;
}

// UPIM_REQ_ONLINE
int OnGetUserState(DWORD dwConnID, char* pReceive, ULONG leng)
{
	int nLenAll = 0;
	int nLen = 0;
	char pSend[ANSBUFFER_LEN] = {0};
	userstate_req* m_req = (userstate_req *)pReceive;
	
	MYSTATE m_state = (MYSTATE)0;
	DWORD dwConnectID = 0;
	g_MongoDBMgr.GetUserState(m_req->userid, m_state, dwConnectID);
	if (m_state != MYSTATE_NORMAL)
	{
		g_pList->PushUSER(m_req->userid, MYSTATE_NORMAL);
		CString strTmp = _T("");
		strTmp.Format("%s session:%d ID:%s ����pushUser!", GetNowTime(), dwConnID, m_req->userid);
		OP_LOG_INFO("%s",strTmp);

		TCHAR chIp[32] = {0};
		int nIplen = 32;
		USHORT nPort = 0;
		g_MySever.m_Server.GetRemoteAddress(dwConnID, chIp, nIplen, nPort);
		g_MongoDBMgr.UserLoginIn(dwConnID, m_req->userid, TRUE, (LPCTSTR)chIp, nPort);
	}

	char szJson[MAX_SEND_BUF_LEN] = {0};
	strncpy(szJson, m_req->headp, m_req->len);

	char m_sendbuf[ANSBUFFER_LEN] = {0};
	userstate_ans* listans = (userstate_ans *)m_sendbuf;

	IMANSBUFFER m_ansbuf = {0};
	InitAnsBufHead(m_ansbuf, UPIM_REQ_ONLINE);
	//////////////////////////////////////////////////////////////////////////
	Value value, item, array, data_value;  
	Reader read;  
	if ( !read.parse( szJson,value ) )  
		return -1;  
	int nItenNum = value["ct"].asInt();
	Value val_array = value["it"];  
	int iSize = val_array.size();

	FastWriter writer;
	string strdata;
	int nRetrunNum = 0;
	if (nItenNum == iSize && nItenNum>0)
	{
		for (int nIndex=0; nIndex<iSize; nIndex++)
		{
			int nAnalyst = val_array[nIndex].asInt();
			CString strAnalyst = IntToStr(nAnalyst);

			MYSTATE m_state = (MYSTATE)0;
			DWORD dwConnectID = 0;
			g_MongoDBMgr.GetUserState(strAnalyst, m_state, dwConnectID);

			item["n"] = (LPCTSTR)strAnalyst;
			item["s"] = (int)m_state;
			array.append(item);

			data_value["ct"] = ++nRetrunNum;					// count
			data_value["it"] = array;							// item
		}
	}
	strdata = writer.write(data_value);
	int packlen = strdata.length();
	//JSON
	listans->rtnnum = nRetrunNum;
	listans->len = packlen;
	memcpy(listans->headp, strdata.c_str(), packlen);
	nLen = sizeof(userstate_ans) + packlen /*- sizeof(char)*/;
	m_ansbuf.AnsHeader.PacketLen	= nLen;
	m_ansbuf.AnsHeader.RawLen		= nLen;

	memcpy(&(m_ansbuf.AnsBuffer), listans, nLen);
	nLenAll = sizeof(IMANSHEADER) + nLen;
	memcpy(pSend, &m_ansbuf, nLenAll);
	g_MySever.m_Server.Send((CONNID)dwConnID, (LPBYTE)pSend, nLenAll);

	return 0;
}