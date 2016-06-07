#include "StdAfx.h"
#include "MyClient.h"
#include "Func.h"
#include "ProcessAns.h"
#include "MainPort.h"

CMyClient::CMyClient(void):m_Client(this)
{
	m_nUserType = -1;
	m_bMainWndClose = FALSE;
	m_bConnect = FALSE;
	m_bLoginSuccess = FALSE;
}

CMyClient::~CMyClient(void)
{
}

//��ʼ��
void CMyClient::InitClient()
{
	m_MsgQueueSendMng.Init(this);
	return;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//��socket�ص���5���ӿ�
EnHandleResult CMyClient::OnConnect(CONNID dwConnID)
{
	TCHAR szAddress[40];
	int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
	USHORT usPort;

	m_Client.GetLocalAddress(szAddress, iAddressLen, usPort);
	return HR_OK;
}

EnHandleResult CMyClient::OnSend(CONNID dwConnID, const BYTE* pData, int iLength)
{
	return HR_OK;
}

EnHandleResult CMyClient::OnReceive(CONNID dwConnID, const BYTE* pData, int iLength)
{
#ifdef __NEW_MODE

	// wuchao add at 20160421 
	// ���һ��������  �ж���������    ճ���������  
	if( g_pack_info.bNeedRecvMore)
	{
		// ��Ҫ���յĴ�С   �ְ�  
		int nNeedRecv = g_pack_info.nNeedRecvLen - g_pack_info.nRecvLen ; 
		iBufferIndex = nNeedRecv ; 

		if( nNeedRecv <= iLength )
		{
			// ��������һ����ʣ�µ�����    
			memcpy(g_pack_info.m_btInfo + g_pack_info.nRecvLen, pData, nNeedRecv);
			g_pack_info.nRecvLen = g_pack_info.nRecvLen + nNeedRecv;
			int nProcessSuc = ReciveDataFromSVR(g_pack_info.m_btInfo, g_pack_info.nNeedRecvLen);
			memset(&g_pack_info, 0 , sizeof(PKGRECVINFO));
			USER_LOG("### ������ %d-%d", nNeedRecv, nNeedRecv);

			// ���ﻹҪ��������ʣ�µ����ݰ�    
			int nLeftPackLen = iLength - nNeedRecv ; 

			// �����������ʣ������� һֱҪ������  
			while( nLeftPackLen > 0 )
			{
				struct tagIMAnsHeader* pHead = (struct tagIMAnsHeader*)(char*)(pData + iBufferIndex)   ;  // ʣ�µ����ݰ���ʼλ��  ����һ��ƫ����
				int CompLen = pHead->PacketLen + sizeof(IMANSHEADER)  ; // һ���������ĳ���  
				// ������ 
				if( pHead->Separator != SEPARATOR_NUM) 
				{
					USER_LOG("### Packet Separator ERROR!");
					return HR_OK;
				}
				
				// �������� 
				// (1) ʣ�����С��������С  
				if( nLeftPackLen < CompLen ) 
				{
					// ���ֻ�ܽ��ղ��ְ� ��СΪrestLen  �洢��g_strpkgrecvinfo 
					g_pack_info.bNeedRecvMore = TRUE;
					g_pack_info.nRecvLen = nLeftPackLen;									// ����ʵ�ʽ��ճ���
					g_pack_info.nNeedRecvLen = pHead->PacketLen + sizeof(IMANSHEADER);
					memcpy(g_pack_info.m_btInfo, pData + iBufferIndex, nLeftPackLen); 
					iBufferIndex = iBufferIndex + nLeftPackLen ; 
					USER_LOG("С�� iBufferIndex = %d " ,iBufferIndex ) ; 
					nLeftPackLen = 0 ; 
				}
				// (2) �պ����   
				else if( nLeftPackLen == CompLen) 
				{
					int nProcessSuc = ReciveDataFromSVR(pData + iBufferIndex ,nLeftPackLen) ; 
					iBufferIndex = iBufferIndex + nLeftPackLen ;
					USER_LOG("��� iBufferIndex = %d " ,iBufferIndex ) ;
					nLeftPackLen = 0 ;
				}
				// (3) ���� 
				else if( nLeftPackLen > CompLen)
				{
					// �Ȱ����������ݶȳ�ȥ    
					int nProcessSuc = ReciveDataFromSVR(pData + iBufferIndex ,CompLen) ;
					iBufferIndex = iBufferIndex+ CompLen ; 
					USER_LOG("���� iBufferIndex = %d " ,iBufferIndex ) ;
					nLeftPackLen =  nLeftPackLen - CompLen ;
				} 
			}
		}
	}
	// �����Ҫ�ٴν���
	else if (g_strpkgrecvinfo.bNeedRecvMore)
	{
		int nNeedrecv = g_strpkgrecvinfo.nNeedRecvLen - g_strpkgrecvinfo.nRecvLen;
		// �������
		if (nNeedrecv == iLength)
		{
			memcpy(g_strpkgrecvinfo.m_btInfo + g_strpkgrecvinfo.nRecvLen, pData, iLength);
			g_strpkgrecvinfo.nRecvLen = g_strpkgrecvinfo.nRecvLen + iLength;
			int nProcessSuc = ReciveDataFromSVR(g_strpkgrecvinfo.m_btInfo, g_strpkgrecvinfo.nNeedRecvLen);
			memset(&g_strpkgrecvinfo, 0 , sizeof(PKGRECVINFO));
			USER_LOG("### bNeedRecvMore # 0, %d-%d", nNeedrecv, iLength);
		}
		// ��û�н�����
		if (nNeedrecv > iLength)
		{
			memcpy(g_strpkgrecvinfo.m_btInfo + g_strpkgrecvinfo.nRecvLen, pData, iLength);
			g_strpkgrecvinfo.nRecvLen = g_strpkgrecvinfo.nRecvLen + iLength;
			USER_LOG("### bNeedRecvMore # 1, %d-%d", nNeedrecv, iLength);
		}
		//�����H�UƟ�����յ��ĳ��ȱ�����Ҫ�Ĵ󣡣��� ���������ճ����
		if (nNeedrecv < iLength)
		{
			memcpy(g_strpkgrecvinfo.m_btInfo + g_strpkgrecvinfo.nRecvLen, pData, iLength);
			g_strpkgrecvinfo.nRecvLen = g_strpkgrecvinfo.nRecvLen + iLength;
			int nProcessSuc = ReciveDataFromSVR(g_strpkgrecvinfo.m_btInfo, g_strpkgrecvinfo.nNeedRecvLen);
			memset(&g_strpkgrecvinfo, 0 , sizeof(PKGRECVINFO));
			USER_LOG("### �����H�UƟ,�ִ����ˣ�����, %d-%d", nNeedrecv, iLength);
		}
	}
	else
	{
		// ������п����Ǹ������绷���£�һ��OnReceiveû�з��������е����ݣ��Ƿִη��͵ģ���ʱ�ҵ�pkglen>iLength,��Ҫ�ɽ��յ������ݴ������������ݵ���֮���ڴ����������ˣ�ɾ��������
		
		struct tagIMAnsHeader* pHead ; 
		/*if( iBufferIndex > 0 )
			pHead = (struct tagIMAnsHeader*)(char*)(pData+iBufferIndex);
		else*/
			pHead = (struct tagIMAnsHeader*)(char*)(pData) ; 

		// ���������������ݰ�Ӧ���������ġ���������������ôSeparator��ֵӦ��Ϊ7654321
		if (pHead->Separator != SEPARATOR_NUM)
		{
			USER_LOG("### Packet Separator ERROR!");
			return HR_OK;
		}

		int CompLen = pHead->PacketLen + sizeof(IMANSHEADER);
		if (CompLen > iLength)
		{
			if (pHead->PacketLen < ANSBUFFER_LEN)
			{
				g_strpkgrecvinfo.bNeedRecvMore = TRUE;
				g_strpkgrecvinfo.nRecvLen = iLength;									// ����ʵ�ʽ��ճ���
				g_strpkgrecvinfo.nNeedRecvLen = pHead->PacketLen + sizeof(IMANSHEADER);
				memcpy(g_strpkgrecvinfo.m_btInfo, pData, iLength);
			}
			else
			{
				USER_LOG("### PacketLen ERROR!");
			}
		}
		// �պ�һ����,��ȷ
		else if (CompLen == iLength)
		{
			int nProcessSuc = ReciveDataFromSVR(pData, iLength);
		}
		// ������˴���ճ�����󣬸��ݰ����Ƚ��н��
		else
		{
			int nIndex =0;
			int restLen = iLength;
			while (restLen > 0)
			{
				struct tagIMAnsHeader* pHead = (struct tagIMAnsHeader*)(char*)(pData+nIndex);
				if (pHead->PacketLen < ANSBUFFER_LEN && pHead->Separator == SEPARATOR_NUM)
				{
					BYTE* pAllData = new BYTE[64*1024];
					memset(pAllData, 0, 64*1024);
					int thisLength = pHead->PacketLen + sizeof(IMANSHEADER);

					if( restLen < thisLength)
					{
						// ���ֻ�ܽ��ղ��ְ� ��СΪrestLen  �洢��g_strpkgrecvinfo 
						g_pack_info.bNeedRecvMore = TRUE;
						g_pack_info.nRecvLen = restLen;									// ����ʵ�ʽ��ճ���
						g_pack_info.nNeedRecvLen = pHead->PacketLen + sizeof(IMANSHEADER);
						memcpy(g_pack_info.m_btInfo, pData + nIndex, restLen); 
						restLen = 0 ; // ��λ  
					}
					else  // ���������㹻�ռ䴢��һ�������İ� 
					{
						memcpy(pAllData, pData + nIndex, thisLength);
						int nProcessSuc = ReciveDataFromSVR(pAllData, thisLength);
						nIndex = nIndex + thisLength;
						restLen = restLen - thisLength;
						TDEL(pAllData);
					}
				}
				else
					break;
			}
		}
	}
#else
	// ������˴���ճ�����󣬸��ݰ����Ƚ��н��
	int nIndex =0;
	int restLen = iLength;
	while (restLen > 0)
	{
		struct tagIMAnsHeader* pHead = (struct tagIMAnsHeader*)(char*)(pData+nIndex);
		if (pHead->PacketLen < ANSBUFFER_LEN  && pHead->Separator == SEPARATOR_NUM)
		{
			BYTE* pAllData = new BYTE[64*1024];
			memset(pAllData, 0, 64*1024);

			int thisLength = pHead->PacketLen + sizeof(IMANSHEADER);
			memcpy(pAllData, pData + nIndex, thisLength);

			int nProcessSuc = ReciveDataFromSVR(pAllData, thisLength);
			nIndex = nIndex + thisLength;
			restLen = restLen - thisLength;
			TDEL(pAllData);
		}
		else
			break;
	}
#endif
	return HR_OK;
}

// �������ر�/�ͻ��������˳�
EnHandleResult CMyClient::OnClose(CONNID dwConnID)
{
	USER_LOG("[%s]Socket Close ConnID:%d", m_Client.GetLastErrorDesc(), dwConnID);

	m_bConnect = FALSE;
	// �����������ر�
	if (g_MyClient.m_bMainWndClose)
	{
		USER_LOG("1# CMyClient::OnClose");
	}
	// ���ӱ��������Ͽ�
	else
	{
		USER_LOG("2# CMyClient::OnClose");
		//����״̬����
		if(g_pFrame)
			g_pFrame->PostMessage(UM_USER_OFFLINE, 0, 0);
	}
	
	return HR_OK;
}

// �����쳣�ر�
EnHandleResult CMyClient::OnError(CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
{
	USER_LOG("Socket ERROR ConnID:%d ErrorCode:%d SocketOperation:%d", dwConnID, iErrorCode, enOperation);
	m_bConnect = FALSE;
	g_pFrame->PostMessage(UM_USER_OFFLINE, 0, 0);
	USER_LOG("CMyClient::OnError");
	
	return HR_OK;
}

//////////////////////////////////////////////////////////////////////////
//���ӷ�����
BOOL CMyClient::StartClient(LPCTSTR pszRemoteAddress, USHORT usPortt, BOOL bAsyncConnect /* = FALSE */)
{
	BOOL bConnect = m_Client.Start(pszRemoteAddress, usPortt, bAsyncConnect);
	if (!bConnect)
	{
		CString strErrorStr = _T("");
		strErrorStr.Format("����������ʧ��:%s", m_Client.GetLastErrorDesc());
		USER_LOG(strErrorStr);
	}
	
	::LogClientStartFail(m_Client.GetLastError(), m_Client.GetLastErrorDesc());
	return bConnect;
}

//�ֶ�ֹͣ����
BOOL CMyClient::StopClient()
{
	USER_LOG("StopClient");
	m_bConnect = FALSE;
	m_MsgQueueSendMng.Exit();
	m_CreateGroupParam.ClearMapCreate();

	return m_Client.Stop();
}

//////////////////////////////////////////////////////////////////////////
//�������ӷ������ݵ�������
BOOL CMyClient::SendClientMsg(const BYTE* pBuffer, int iLength, int iOffset /* = 0 */)
{
	if (m_Client.GetState() != SS_STARTED)
	{
		if (m_nUserType == eUser_UPClient && !g_bUserKickOff)
		{
			ReConnect();
			USER_LOG("ReConnect Start!");
		}
		// wuchao add at 20160324  IM EXEǶ�뵽UP��  �������� 
		else if( m_nUserType == eUser_UPClient2 && !g_bUserKickOff )
		{
			ReConnect();
			USER_LOG("ReConnect Start!");
		}
		// ��ֱ�ӷ��أ����Զ��������ֶ�����
		else
			return FALSE;
	}

	return m_Client.Send(pBuffer, iLength, iOffset);
}

// ���ÿͻ���Ϣ
// ����������䣬�������ļ��ж�ȡ
BOOL CMyClient::SetClientInfo(short nUserType)
{
	m_nUserType = nUserType;
	return TRUE;
}

// UPIM_REQ_CHECKPWD
// �����û���¼��Ϣ
BOOL CMyClient::SendCheckPwdReq(LPCTSTR UID, LPCTSTR PWD, short nCheckType)
{
	BOOL bSendSuc = FALSE;
	
	int nLen = sizeof(login_req);
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	login_req loginreq = {0};
	loginreq.req = UPIM_REQ_CHECKPWD ;
	strncpy(loginreq.userid, UID, sizeof(loginreq.userid));
	strncpy(loginreq.userpwd, PWD, sizeof(loginreq.userpwd));
	loginreq.usertype = nCheckType;

	memcpy(&(m_reqbuf.ReqBuffer), &loginreq, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	//USER_LOG("Send:[UPIM_REQ_CHECKPWD] UID:%s PWD:%s CheckType:%d", UID, PWD, nCheckType);
	return bSendSuc;
}

// UPIM_REQ_GUSER
// ��ȡ����/�û��б�
BOOL CMyClient::SendGUserReq(short nGroupID, short nType)
{
	BOOL bSendSuc = FALSE;
	int nLen = sizeof(guser_req);
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	guser_req guserreq = {0};
	// UPIM_REQ_GUSER����ģʽ���ṹ������ϴ󣬲�����
	// UPIM_REQ_GUSER2��Ҫ������jsonģʽ�Ĵ��䣬�ʺ��ڱ䳤�ṹ
	guserreq.req = UPIM_REQ_GUSER2 ;			
	strcpy(guserreq.userid, m_strUserid);
	guserreq.ngroupid = nGroupID;
	guserreq.ntype = nType;
	memcpy(&(m_reqbuf.ReqBuffer), &guserreq, nLen);

	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);
	USER_LOG("Send:[UPIM_REQ_GUSER] GroupID:%d Type:%d", nGroupID, nType);
	return bSendSuc;
}

// UPIM_REQ_SENDMSG
// ���͵���������Ϣ
BOOL CMyClient::SendMsgReq(sendmsg_req *preq)
{
	BOOL bSendSuc = FALSE;

	int nLen = sizeof(sendmsg_req) + preq->msglen/*- sizeof(char)*/;
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	preq->req = UPIM_REQ_SENDMSG ;
	COPY_USERID(preq->cFromuserid, m_strUserid);
	if (preq->dwMsgSeq == 0)
		preq->dwMsgSeq = InterlockedIncrement(&g_nMsgSeq);
	preq->nUsertype = eUser_Client;

	memcpy(&(m_reqbuf.ReqBuffer), preq, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	//USER_LOG("Send:[UPIM_REQ_SENDMSG] DesID:%s nLen:%d msg:%s", preq->cTouserid, nLen, preq->msg);
	return bSendSuc;
}

// UPIM_REQ_GCSENDMSG
// ����Ⱥ��Ϣ
BOOL CMyClient::SendGroupMsgReq(gcsendmsg_req *preq)
{
	BOOL bSendSuc = FALSE;
	int nLen = sizeof(gcsendmsg_req) + preq->msglen/*- sizeof(char)*/;
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	preq->req = UPIM_REQ_GCSENDMSG ;
	COPY_USERID(preq->cFromuserid, m_strUserid);
	preq->nUsertype = m_nUserType;
	COPY_NICKNAME(preq->nickname, m_strUserName);

	if (preq->dwMsgSeq == 0)
		preq->dwMsgSeq = InterlockedIncrement(&g_nMsgSeq);
	
	memcpy(&(m_reqbuf.ReqBuffer), preq, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	//USER_LOG("Send:[UPIM_REQ_GCSENDMSG] DesID:%s msg:%s", preq->cFromuserid, preq->msg);
	return bSendSuc;
}

// UPIM_REQ_GLIST
// ȡ�÷���
BOOL CMyClient::SendGListReq(short nGrouptype)
{
	BOOL bSendSuc = FALSE;
	int nLen = sizeof(glist_req);
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	glist_req glistreq = {0};
	glistreq.req = UPIM_REQ_GLIST ;
	strcpy(glistreq.userid, m_strUserid);
	glistreq.ngrouptype = nGrouptype;

	memcpy(&(m_reqbuf.ReqBuffer), &glistreq, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	USER_LOG("Send:[UPIM_REQ_GLIST] Grouptype:%d", nGrouptype);
	return bSendSuc;
}

// UPIM_REQ_LIST
// ���ݷ���ȡ�û��б�
BOOL CMyClient::SendFriendListReq(short nGrouptype)
{
	BOOL bSendSuc = FALSE;
	int nLen = sizeof(list_req);
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	list_req listreq = {0};
	// UPIM_REQ_LIST ����ģʽ���ṹ����
	// UPIM_REQ_LIST2��JSONģʽ������������json����
	listreq.req = UPIM_REQ_LIST2 ;
	strcpy(listreq.userid, m_strUserid);
	listreq.ngrouptype = nGrouptype;

	memcpy(&(m_reqbuf.ReqBuffer), &listreq, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	USER_LOG("Send:[UPIM_REQ_LIST] Grouptype:%d", nGrouptype);
	return TRUE;
}

// UPIM_REQ_DEPT
// ���ŷ����б�
BOOL CMyClient::SendDeptGroupReq()
{
	BOOL bSendSuc = FALSE;
	int nLen = sizeof(dept_req);
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	dept_req deptreq = {0};
	deptreq.req = UPIM_REQ_DEPT ;
	strcpy(deptreq.userid, m_strUserid);
	deptreq.ndeptid = m_nDeptID;

	memcpy(&(m_reqbuf.ReqBuffer), &deptreq, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	USER_LOG("Send:[UPIM_REQ_DEPT] deptid:%d", m_nDeptID);
	return TRUE;
}

// UPIM_REQ_GCINFO
// Ⱥ���б�
BOOL CMyClient::SendGcInfoReq()
{
	BOOL bSendSuc = FALSE;
	int nLen = sizeof(dept_req);
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	gcinfo_req gcinforeq = {0};
	//UPIM_REQ_GCINFOΪ�Ͻṹ��ȡȺ��Э��
	//UPIM_REQ_GCINFO2Ϊ�µ�JSON�ṹ��ȡȺ��Э��
	gcinforeq.req = UPIM_REQ_GCINFO2;
	strcpy(gcinforeq.userid, m_strUserid);
	gcinforeq.type = IsClientLoginIn();

	memcpy(&(m_reqbuf.ReqBuffer), &gcinforeq, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	USER_LOG("Send:[UPIM_REQ_GCINFO] userid:%s", m_strUserid);
	return TRUE;
}

// UPIM_REQ_GCGETLIST
// �õ�Ⱥ��Ա�б�
BOOL CMyClient::SendGcUserListReq(ROOMID nRoomID, int RoomType, int nStartPos)
{
	BOOL bSendSuc = FALSE;
	int nLen = sizeof(gcgetlist_req);
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	gcgetlist_req gcgetlistreq = {0};
	gcgetlistreq.req = UPIM_REQ_GCGETLIST;
	gcgetlistreq.Roomtype = RoomType;
	gcgetlistreq.RoomId = nRoomID;
	gcgetlistreq.nStartPos = nStartPos;

	memcpy(&(m_reqbuf.ReqBuffer), &gcgetlistreq, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	USER_LOG("Send:[UPIM_REQ_GCGETLIST] ROOMID:%d", nRoomID);
	return TRUE;
}

// UPIM_REQ_GCCREATE
// �´���Ⱥ��
BOOL CMyClient::SendCreateGroupReq(LPCTSTR strGroupName, short nGrouptype, std::vector<GUPID>* pVtFriend/* =NULL */)
{
	BOOL bSendSuc = FALSE;
	int nLen = sizeof(gccreate_req);
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	gccreate_req gccreatereq = {0};
	gccreatereq.req = UPIM_REQ_GCCREATE;
	gccreatereq.roomtype = nGrouptype;
	strcpy(gccreatereq.createuserid, m_strUserid);
	strcpy(gccreatereq.roomname, strGroupName);
	int lParam = m_CreateGroupParam.SetMapCreateGroupParam(nGrouptype, strGroupName, m_strUserid, pVtFriend);
	gccreatereq.nroomParam = lParam;

	memcpy(&(m_reqbuf.ReqBuffer), &gccreatereq, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	USER_LOG("Send:[UPIM_REQ_GCCREATE] ROOMNAME:%s", strGroupName);
	return TRUE;
}

// UPIM_REQ_GCADD
// ��Ⱥ����ӳ�Ա
BOOL CMyClient::SendGcAddReq(ROOMID groupid, short grouptype, LPCTSTR pszupid)
{
	BOOL bSendSuc = FALSE;
	int nLen = sizeof(gcadd_req);
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	gcadd_req gcaddreq = {0};
	gcaddreq.req = UPIM_REQ_GCADD;
	gcaddreq.nRoomID = groupid;
	gcaddreq.roomtype = grouptype;

	memcpy(&(m_reqbuf.ReqBuffer), &gcaddreq, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	USER_LOG("Send:[UPIM_REQ_GCADD] ROOMID:%d", groupid);
	return TRUE;
}

// UPIM_REQ_GCADD
// ��Ⱥ����ӳ�Ա
BOOL CMyClient::SendGcAddReq(GROUP_CHAT_ADD_STU m_stu)
{
	BOOL bSendSuc = FALSE;

	char buf[MAX_SEND_BUF_LEN] = {0};
	gcadd_req *gcaddreq=(gcadd_req*)buf;
	gcaddreq->req = UPIM_REQ_GCADD;
	gcaddreq->nRoomID = m_stu.roomid;
	gcaddreq->roomtype = m_stu.roomtype;

	//////////////////////////////////////////////////////////////////////////
	// JSON
	Reader read;  
	Value value;  
	value["count"] = IntToStr(m_stu.count).GetBuffer(0);  
	Value item;  
	int nType = eUser_Broker;
	Value array;  
	for (int i=0; i<m_stu.count; i++)
	{
		nType = m_stu.agUpid[i].m_nUserType;
		item["tp"] = IntToStr(nType).GetBuffer(0);  
		item["id"] = m_stu.agUpid[i].m_szUSERID;  
		array.append( item );   
	}
	value["item"] = array;  
	FastWriter writer;
	string tmp = writer.write(value);
	//////////////////////////////////////////////////////////////////////////
	gcaddreq->szlen = tmp.length();
	strncpy(gcaddreq->szUpID, tmp.c_str(), gcaddreq->szlen);

	int nLen = sizeof(gcadd_req) + gcaddreq->szlen/*- sizeof(char)*/;
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	memcpy(&(m_reqbuf.ReqBuffer), gcaddreq, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	USER_LOG("Send:[UPIM_REQ_GCADD] ROOMID:%d", m_stu.roomid);
	return TRUE;
}

// UPIM_REQ_GCKICK
// Ⱥ������,����
BOOL CMyClient::SendGcKickReq(ROOMID groupid, short grouptype, LPCUSERID upid, short nUsertype)
{
	BOOL bSendSuc = FALSE;
	int nLen = sizeof(gcleave_req);
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	gcleave_req m_req = {0};
	m_req.req = UPIM_REQ_GCKICK;
	m_req.nRoomID = groupid;
	m_req.roomtype = grouptype;
	strcpy(m_req.userid, upid);
	m_req.nUsertype = nUsertype;

	memcpy(&(m_reqbuf.ReqBuffer), &m_req, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	USER_LOG("Send:[UPIM_REQ_GCKICK] ROOMID:%d", groupid);
	return TRUE;
}

// UPIM_REQ_GCLEAVE
// Ⱥ������,�뿪
BOOL CMyClient::SendGcLeaveReq(ROOMID groupid, short grouptype)
{
	BOOL bSendSuc = FALSE;
	int nLen = sizeof(gcleave_req);
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	gcleave_req m_req = {0};
	m_req.req = UPIM_REQ_GCLEAVE;
	m_req.nRoomID = groupid;
	m_req.roomtype = grouptype;
	strcpy(m_req.userid, m_strUserid);

	memcpy(&(m_reqbuf.ReqBuffer), &m_req, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	USER_LOG("Send:[UPIM_REQ_GCKICK] ROOMID:%d", groupid);
	return TRUE;
}

// UPIM_REQ_GPUBLIC
// ��ȡ���ں�
BOOL CMyClient::SendGetPublicReq()
{
#ifdef PUBLICMNG
	BOOL bSendSuc = FALSE;
	int nLen = sizeof(public_req);
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	public_req m_req = {0};
	m_req.req = UPIM_REQ_GPUBLIC;
	strcpy(m_req.userid, m_strUserid);
	m_req.nUsertype = m_nUserType;

	memcpy(&(m_reqbuf.ReqBuffer), &m_req, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	USER_LOG("Send:[UPIM_REQ_GPUBLIC] userid:%s", m_req.userid);
#endif
	return TRUE;
}

// UPIM_REQ_PUBLICINFO
// ��ȡ���ں���Ϣ�����������·�ɣ�������������ʾ
BOOL CMyClient::SendGetPublicInfoReq(int nPublicID)
{
	BOOL bSendSuc = FALSE;
	int nLen = sizeof(publicinfo_req);
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	publicinfo_req m_req = {0};
	m_req.req = UPIM_REQ_PUBLICINFO;
	m_req.publicID = nPublicID;

	memcpy(&(m_reqbuf.ReqBuffer), &m_req, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	USER_LOG("Send:[UPIM_REQ_PUBLICINFO] PublicId:%d", m_req.publicID);
	return TRUE;
}

// UPIM_REQ_PUBCONCLOSE
// �û������ںŵĻỰ�Ͽ�
BOOL CMyClient::SendPubconCloseReq(LPCUSERID svcid, int publicID, int routeID, int closetype)
{
	BOOL bSendSuc = FALSE;
	int nLen = sizeof(pubconclose_req);
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	pubconclose_req m_req = {0};
	m_req.req = UPIM_REQ_PUBCONCLOSE;
	m_req.publicID = publicID;
	m_req.routeID = routeID;
	m_req.closeType = closetype;
	COPYSTRARRAY(m_req.SevcId, svcid);
	COPYSTRARRAY(m_req.userid, m_strUserid);

	memcpy(&(m_reqbuf.ReqBuffer), &m_req, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	USER_LOG("Send:[UPIM_REQ_PUBCONCLOSE] PublicId:%d, svcid:%s", publicID, svcid);
	return bSendSuc;
}

// UPIM_REQ_RECONNECT
// ��������֮��֪ͨ������
BOOL CMyClient::SendReconnentReq()
{
	BOOL bSendSuc = FALSE;
	int nLen = sizeof(reconnect_req);
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	if (g_MyClient.m_strUserid.IsEmpty())
		return FALSE;

	reconnect_req m_req = {0};
	m_req.req = UPIM_REQ_RECONNECT;
	strcpy(m_req.userid, m_strUserid);
	m_req.nUsertype = m_nUserType;

	memcpy(&(m_reqbuf.ReqBuffer), &m_req, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	USER_LOG("Send:[UPIM_REQ_RECONNECT] userid:%s", m_req.userid);
	return TRUE;
}

// UPIM_REQ_M_USERINFO
// �޸��û���Ϣ
BOOL CMyClient::SendModifyUserInfoReq(MODIFY_USERINFO_STU m_stu)
{
	BOOL bSendSuc = FALSE;
	char buf[MAX_SEND_BUF_LEN] = {0};
	m_userinfo_req *m_req=(m_userinfo_req*)buf;
	m_req->req = UPIM_REQ_M_USERINFO;

	//////////////////////////////////////////////////////////////////////////
	// JSON
	Reader read;  
	Value value; 
	value["userid"] = m_stu.userid;
	value["nickname"] = m_stu.nickname;
	value["sex"] = m_stu.sex;
	value["birthday"] = m_stu.birthday;

	FastWriter writer;
	string tmp = writer.write(value);
	//////////////////////////////////////////////////////////////////////////
	m_req->len = tmp.length();
	strncpy(m_req->headp, tmp.c_str(), m_req->len);

	int nLen = sizeof(m_userinfo_req) + m_req->len/*- sizeof(char)*/;
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	memcpy(&(m_reqbuf.ReqBuffer), m_req, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	USER_LOG("Send:[UPIM_REQ_M_USERINFO]");
	return TRUE;
}

// UPIM_REQ_OLNOTIFY
// ���Լ���״̬�ı����͵����ߵĺ���
BOOL CMyClient::SendStateNotifyReq(string sendid_json, int nstate)
{
	if (sendid_json.length() < 1)
		return FALSE;

	BOOL bSendSuc = FALSE;
	char buf[MAX_SEND_BUF_LEN] = {0};
	olnotify_req *m_req=(olnotify_req*)buf;
	m_req->req = UPIM_REQ_OLNOTIFY;
	strcpy(m_req->userid, m_strUserid);
	m_req->nUserstate = nstate;
	m_req->len = sendid_json.size();
	strncpy(m_req->headp, sendid_json.c_str(), m_req->len);

	int nLen = sizeof(olnotify_req) + m_req->len/*- sizeof(char)*/;
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	memcpy(&(m_reqbuf.ReqBuffer), m_req, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	USER_LOG("Send:[UPIM_REQ_OLNOTIFY] userid:%s", sendid_json.c_str());
	return TRUE;
}

// UPIM_REQ_OFFMSG
// �û�����֮��ӷ�������ȡ��������Ϣ
BOOL CMyClient::SendOFFMSGReq()
{
	BOOL bSendSuc = FALSE;
	int nLen = sizeof(offmsg_req);
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	offmsg_req m_req = {0};
	m_req.req = UPIM_REQ_OFFMSG;
	strcpy(m_req.userid, m_strUserid);
	m_req.nUsertype = m_nUserType;

	memcpy(&(m_reqbuf.ReqBuffer), &m_req, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	USER_LOG("Send:[UPIM_REQ_OFFMSG] userid:%s", m_req.userid);
	return TRUE;
}

// UPIM_REQ_PKG
// �û�����һ�û��������ݰ�
BOOL CMyClient::SendPkgReq(LPCUSERID tqid, bool request, CClientPackage *pkg)
{
	BOOL bSendSuc = FALSE;
	char buf[MAX_SEND_BUF_LEN] = {0};
	send_pkg_req *m_req = (send_pkg_req*)buf;

	CPackageHandle pkgHandle(pkg);
	DWORD dwLen = 0;						//���������ݵĳ���
	char* pBuf = pkg->GetPkBuffer(dwLen);
	if(pBuf==NULL || dwLen<=0) return FALSE;

	m_req->req = UPIM_REQ_PKG;
	COPY_USERID(m_req->cFromuserid, m_strUserid);
	COPY_USERID(m_req->cTouserid, tqid);
	m_req->pkglen = dwLen;
	m_req->nrequest = request;
	memcpy(m_req->pkg, pBuf, dwLen);
	
	int nLen = sizeof(send_pkg_req) + dwLen/*- sizeof(char)*/;
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	memcpy(&(m_reqbuf.ReqBuffer), m_req, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);
	
	return bSendSuc;
}

// UPIM_REQ_ALLTGROOM
// Ͷ�˻�ȡ������
BOOL CMyClient::SendGetAllRoomReq()
{
	BOOL bSendSuc = FALSE;
	int nLen = sizeof(alltgroom_req);
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	alltgroom_req m_req = {0};
	m_req.req = UPIM_REQ_ALLTGROOM;
	strcpy(m_req.userid, m_strUserid);
	m_req.nUsertype = m_nUserType;

	memcpy(&(m_reqbuf.ReqBuffer), &m_req, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	USER_LOG("Send:[UPIM_REQ_ALLTGROOM] userid:%s", m_req.userid);
	return TRUE;
}

// UPIM_REQ_ALLTGROOMEX
// im2.0�汾�пͻ����ܿ������еķ��䣬���еķ���ʦ
BOOL CMyClient::SendGetAllTgRoomReq(int nMarket)
{
	BOOL bSendSuc = FALSE;
	int nLen = sizeof(alltgroomEx_req);
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	alltgroomEx_req m_req = {0};
	m_req.req = UPIM_REQ_ALLTGROOMEX;
	m_req.nMarket = nMarket;
	strcpy(m_req.userid, m_strUserid);
	m_req.nUsertype = m_nUserType;

	memcpy(&(m_reqbuf.ReqBuffer), &m_req, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	USER_LOG("Send:[UPIM_REQ_ALLTGROOMEX] userid:%s market:%d", m_req.userid, nMarket);
	return TRUE;
}

// UPIM_REQ_ALLROOMTOUSER
// im2.0�汾�з�����Ա�ܿ����÷��������еĿͻ���Ϣ
BOOL CMyClient::SendGetRoomUsersReq(int nRoomID)
{
	BOOL bSendSuc = FALSE;
	int nLen = sizeof(tggetuserbyroomid_req);
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	tggetuserbyroomid_req m_req = {0};
	m_req.req = UPIM_REQ_ALLROOMTOUSER;
	m_req.roomid = nRoomID;
	strcpy(m_req.userid, m_strUserid);
	m_req.nUsertype = m_nUserType;

	memcpy(&(m_reqbuf.ReqBuffer), &m_req, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	USER_LOG("Send:[UPIM_REQ_ALLROOMTOUSER] userid:%s roomid:%d", m_req.userid, nRoomID);
	return TRUE;
}

// UPIM_REQ_GETGROUP
// im2.0�汾�з�����Ա�Զ������
BOOL CMyClient::SendGetSelfGroupReq()
{
	BOOL bSendSuc = FALSE;
	int nLen = sizeof(getgroup_req);
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	getgroup_req m_req = {0};
	m_req.req = UPIM_REQ_GETGROUP;
	strcpy(m_req.userid, m_strUserid);
	m_req.nUsertype = m_nUserType;

	memcpy(&(m_reqbuf.ReqBuffer), &m_req, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	USER_LOG("Send:[UPIM_REQ_GETGROUP] userid:%s", m_req.userid);
	return TRUE;
}

// UPIM_REQ_GETGUSER
// im2.0�汾�з�����Աȡ���Զ�������µĿͻ��б�
BOOL CMyClient::SendGetSelfGroupUsersReq(int nGroupID)
{
	BOOL bSendSuc = FALSE;
	int nLen = sizeof(getguser_req);
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	getguser_req m_req = {0};
	m_req.req = UPIM_REQ_GETGUSER;
	strcpy(m_req.userid, m_strUserid);
	m_req.nUsertype = m_nUserType;
	m_req.nGroupID = nGroupID;

	memcpy(&(m_reqbuf.ReqBuffer), &m_req, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	USER_LOG("Send:[UPIM_REQ_GETGUSER] userid:%s ngroupid:%d", m_req.userid, nGroupID);
	return TRUE;
}

// UPIM_REQ_ADDGROUP
// im2.0�汾�з�����Ա�༭�Զ������
BOOL CMyClient::SendSetSelfGroupReq(string sjson)
{
	if (sjson.length() < 1)
		return FALSE;

	BOOL bSendSuc = FALSE;
	char buf[MAX_SEND_BUF_LEN] = {0};
	addgroup_req *m_req=(addgroup_req*)buf;
	m_req->req = UPIM_REQ_ADDGROUP;
	strcpy(m_req->userid, m_strUserid);
	m_req->len = sjson.size();
	strncpy(m_req->headp, sjson.c_str(), m_req->len);

	int nLen = sizeof(addgroup_req) + m_req->len/*- sizeof(char)*/;
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	memcpy(&(m_reqbuf.ReqBuffer), m_req, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	USER_LOG("Send:[UPIM_REQ_ADDGROUP] info:%s", sjson.c_str());
	return TRUE;
}

// UPIM_REQ_MODGUSER
// im2.0�汾�з�����Ա�༭�Զ������Ŀͻ��б�
BOOL CMyClient::SendSetSelfGroupUserReq(string sjson)
{
	if (sjson.length() < 1)
		return FALSE;

	BOOL bSendSuc = FALSE;
	char buf[MAX_SEND_BUF_LEN] = {0};
	modguser_req *m_req=(modguser_req*)buf;
	m_req->req = UPIM_REQ_MODGUSER;
	strcpy(m_req->userid, m_strUserid);
	m_req->len = sjson.size();
	strncpy(m_req->headp, sjson.c_str(), m_req->len);

	int nLen = sizeof(modguser_req) + m_req->len/*- sizeof(char)*/;
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	memcpy(&(m_reqbuf.ReqBuffer), m_req, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	USER_LOG("Send:[UPIM_REQ_MODGUSER] info:%s", sjson.c_str());
	return TRUE;
}

// UPIM_REQ_ONLINE
// ������ѯ����״̬�����������,�ָ�
BOOL CMyClient::SendGetUserState(LPCUSERID userids, int nFlag /* = 0 */)
{
	BOOL bSendSuc = FALSE;
	char buf[MAX_SEND_BUF_LEN] = {0};
	userstate_req *m_req=(userstate_req*)buf;
	m_req->req = UPIM_REQ_ONLINE;
	strcpy(m_req->userid, m_strUserid);
	m_req->nUsertype = m_nUserType;
	m_req->flag = nFlag;
	strncpy(m_req->headp, userids, strlen(userids));
	m_req->len = strlen(userids);

	int nLen = sizeof(userstate_req) + m_req->len/*- sizeof(char)*/;
	IMREQBUFFER m_reqbuf = {0};
	InitReqBufHead(m_reqbuf, nLen, nLen);

	memcpy(&(m_reqbuf.ReqBuffer), m_req, nLen);
	int nLenAll = sizeof(IMREQHEADER) + nLen;
	bSendSuc = SendClientMsg((LPBYTE)&m_reqbuf, nLenAll);

	//USER_LOG("Send:[UPIM_REQ_ONLINE] userids:%s", userids);

	return TRUE;
}