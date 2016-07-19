#include "StdAfx.h"
#include "ProcessAns.h"
#include "globalvar.h"
#include "Func.h"
#include "MainPort.h"
#include "IniFile.h"
#include "resource.h"
#include "char2wchar.h"

int ReciveDataFromSVR(const BYTE* pData, int iLength)
{
	struct tagIMAnsHeader* pHead = (struct tagIMAnsHeader*)pData;
	if (!pHead)		return 0;
	int nLen = pHead->PacketLen;
	char* pReceive = (char*)(pHead + 1);

	USER_LOG("RecvData: iLength:%d nLen:%d Req:%d", iLength, nLen, pHead->req);

	if (pHead->ErrorCode == erError_None)
	{
		switch(pHead->req)
		{
		case UPIM_REQ_CHECKPWD:					// �û���¼��ִ
			OnCheckPwdAns(pReceive, nLen);
			break;
		case UPIM_REQ_GUSER:					// (������)������Ա��ȡ�������
			OnGUserAns(pReceive, nLen);
			break;
		case UPIM_REQ_GUSER2:					// (������)������Ա��ȡ�������_Json
			OnGUserAns2(pReceive, nLen);
			break;
		case UPIM_REQ_GLIST:					// (�ͻ�)�û������ִ
			OnGListAns(pReceive, nLen);
			break;
		case UPIM_REQ_LIST:						// (�ͻ�)ȡ�ú���
			OnListAns(pReceive, nLen);
			break;
		case UPIM_REQ_LIST2:					// (�ͻ�)ȡ�ú���_JSON
			OnListAns2(pReceive, nLen);
			break;
		case UPIM_REQ_SENDMSG:					// �û�������Ϣ��ִ
			On_SendMSG_Ans(pReceive, nLen);
			break;
		case  UPIM_REQ_S_SENDMSG:				// ����������������Ϣ
			On_S_SendMSG_Ans(pReceive, nLen);
			break;
		case UPIM_REQ_DEPT:						// ������Ϣ
			OnDeptAns(pReceive, nLen);
			break;
		case UPIM_REQ_GCINFO:					// Ⱥ����Ϣ
			OnGcInfoAns(pReceive, nLen);
			break;
		case UPIM_REQ_GCINFO2:					// Ⱥ����Ϣ_JSON
			OnGcInfoAns2(pReceive, nLen);
			break;
		case UPIM_REQ_GCGETLIST:				// �õ�Ⱥ���Ա
			OnGcGetListAns(pReceive, nLen);
			break;
		case UPIM_REQ_GCSENDMSG:				// ����Ⱥ��Ϣ�ķ�������ִ
			OnSendGcMSGAns(pReceive, nLen);
			break;
		case UPIM_REQ_GCRECVMSG:				// ��������������Ⱥ��Ϣ
			OnRecvGcMSG(pReceive, nLen);
			break;
		case UPIM_REQ_GCCREATE:					// ����Ⱥ����Ϣ
			OnGcCreateAns(pReceive, nLen);
			break;
		case UPIM_REQ_GCADD:					// ���Ⱥ��Ա��Ϣ��ִ
			OnGcAddAns(pReceive, nLen);
			break;
		case UPIM_REQ_GCKICK:					// �߳�Ⱥ��Ա��Ϣ��ִ
			OnGcKickAns(pReceive, nLen);
			break;
		case UPIM_REQ_GCLEAVE:					// �˳�Ⱥ��Ϣ��ִ
			OnGcLeaveAns(pReceive, nLen);
			break;
		case UPIM_REQ_GPUBLIC:					// ��ȡ���ںŻ�ִ
			OnGetPublicAns(pReceive, nLen);
			break;
		case UPIM_REQ_PUBLICINFO:				// ��ȡ���ں���Ϣ
			OnGetPublicInfoAns(pReceive, nLen);
			break;
		case UPIM_REQ_S_GCADD:					// �������������ı������Ϣ
			OnGetS_GCAddAns(pReceive, nLen);
			break;
		case UPIM_REQ_S_GCKICK:					// �������������ı��߳���Ϣ
			OnGetS_GCKickAns(pReceive, nLen);
			break;
		case UPIM_REQ_S_ONLINE:					// �������������Ŀͷ�������Ϣ
			OnGet_S_Online(pReceive, nLen);
			break;
		case UPIM_REQ_OFFMSG:					// ������Ϣ
			OnGetOffMSg(pReceive, nLen);
			break;
		case UPIM_REQ_KICKOFF:					// ��T��Ϣ
			OnKickOffMsg(pReceive, nLen);
			break;
		case UPIM_REQ_SVROFF:					// ��ǰ�������ر���Ϣ
			OnSvrOffMsg(pReceive, nLen);
			break;
		case UPIM_REQ_PKG:						// ���������ݰ�
			On_SendPKG_Ans(pReceive, nLen);
			break;
		case UPIM_REQ_S_PKG:					// ���ݰ�ʵ��Э��
			On_S_SendPKG_Ans(pReceive, nLen);
			break;
		case UPIM_REQ_ALLTGROOM:				// ���������
			On_GetAllTgRoom_Ans(pReceive, nLen);	
			break;
		case UPIM_REQ_ONLINE:					// ��ȡ�û�״̬
			OnGetUserState_Ans(pReceive, nLen);	
			break;
		case UPIM_REQ_RECONNECT:				// �ص�¼Э�鷵�ذ�
			OnReconnect_Ans(pReceive, nLen);	
			break;
		case UPIM_REQ_ALLTGROOMEX:				// im2.0ȡ��������������Ϣ�ķ��ذ�
			On_GetAllTgRoomEx_Ans(pReceive, nLen);	
			break;
		case UPIM_REQ_ALLROOMTOUSER:			// im2.0ȡ�÷��������пͻ���Ϣ�ķ��ذ�
			On_GetUserByRoomID_Ans(pReceive, nLen);	
			break;
		case UPIM_REQ_GETGROUP:					// im2.0�汾�з�����Ա�Զ������
			OnGetSelfGroup_Ans(pReceive, nLen);
			break;
		case UPIM_REQ_GETGUSER:					// im2.0ȡ�÷����¶�Ӧ���û��б�
			OnGetSelfGroupUsers_Ans(pReceive, nLen);
			break;
		case UPIM_REQ_ADDGROUP:					// im2.0���/�޸��Զ��������Ϣ
			OnSetSelfGroup_Ans(pReceive, nLen);
			break;
		case UPIM_REQ_MODGUSER:					// im2.0���/�޸��û��ķ���
			OnSetSelfGroupUser_Ans(pReceive, nLen);
			break;
		default:
			break;
		}
	}
	//���д�����
	else
	{
		switch( pHead->ErrorCode )
		{
		case erServer_Error:
			USER_LOG("�������쳣");
			break;
		case erServer_DBError:
			USER_LOG("���ݿ����");
			break;
		case erLogin_PswError:
			g_pFrame->pLoginDialog->m_pDialog_Errorstr->SetText("�������");
			break;
		case erLogin_IDNotExist:
			g_pFrame->pLoginDialog->m_pDialog_Errorstr->SetText("�û�������");
			break;
		case erLogin_IPNotAllow:
			g_pFrame->pLoginDialog->m_pDialog_Errorstr->SetText("��IP�������¼");
			break;
		default:
			break;
		}
	}
	return 0;
}

//UPIM_REQ_GUSER ������Ϣ
int OnGUserAns(char* pReceive, ULONG leng)
{
	guser_ans* m_guserans = (guser_ans *)pReceive;
	short nItemNum = m_guserans->rtnnum;
	EGROUPTYPE nType = (EGROUPTYPE)m_guserans->ntype;
	int nGroupid = m_guserans->ngroupid;

	USER_LOG("Recv:[UPIM_REQ_GUSER] ItemNum:%d Type:%d Groupid:%d", nItemNum, nType, nGroupid);
	if (nItemNum > 0)
	{
		guser_unit* m_rtnunit = new guser_unit[nItemNum];
		memset(m_rtnunit, 0, sizeof(guser_unit)*nItemNum);
		memcpy(m_rtnunit, m_guserans->headp, sizeof(guser_unit)*nItemNum);

		for (int nIdex = 0; nIdex<nItemNum; nIdex++)
		{
			FRIEND_INFO m_Friendunit = {0};
			COPYSTRARRAY(m_Friendunit.userid, m_rtnunit[nIdex].userid);
			COPYSTRARRAY(m_Friendunit.truename, m_rtnunit[nIdex].username);
			COPYSTRARRAY(m_Friendunit.nickname, m_rtnunit[nIdex].username);
			m_Friendunit.type = nType;
			m_Friendunit.relation = nGroupid;
			COPYSTRARRAY(m_Friendunit.sign, m_rtnunit[nIdex].signature);
			if (strlen(m_Friendunit.sign) == 0)
				COPYSTRARRAY(m_Friendunit.sign, "�ͻ�ǩ��");

			m_Friendunit.sex = (BYTE)m_rtnunit[nIdex].sex;
			m_Friendunit.online = (BYTE)m_rtnunit[nIdex].state;

			alluserNickname[m_Friendunit.userid] = m_Friendunit.nickname;
			m_vtFriendInfo.push_back(m_Friendunit);
		}
		TDEL(m_rtnunit);
		g_pFrame->PostMessage(UM_USER_ADDGROUP, 0, 0);
		g_pFrame->PostMessage(UM_USER_ADDFRIEND, 0, 0);
	}
	return 0;
}

//UPIM_REQ_GUSER2 ������Ϣ
int OnGUserAns2(char* pReceive, ULONG leng)
{
	guser_ans2* m_guserans = (guser_ans2 *)pReceive;
	short nItemNum = m_guserans->rtnnum;
	EGROUPTYPE nType = (EGROUPTYPE)m_guserans->ntype;
	int nGroupid = m_guserans->ngroupid;

	char szJson[MAX_SEND_BUF_LEN] = {0};
	strncpy(szJson, m_guserans->headp, m_guserans->nlen);

	USER_LOG("Recv:[UPIM_REQ_GUSER2] ItemNum:%d Type:%d Groupid:%d", nItemNum, nType, nGroupid);
	//////////////////////////////////////////////////////////////////////////
	Value value;  
	Reader read;  
	if ( !read.parse( szJson,value ) )  
	{  
		return -1;  
	}
	int nItenNum = value["ct"].asInt();
	Value val_array = value["it"];  
	int iSize = val_array.size();
	if (nItenNum == iSize && nItenNum>0)
	{
		for (int nIndex=0; nIndex<iSize; nIndex++)
		{
			FRIEND_INFO m_Friendunit = {0};
			COPYSTRARRAY(m_Friendunit.userid, val_array[nIndex]["i"].asString().c_str());
			COPYSTRARRAY(m_Friendunit.truename, val_array[nIndex]["n"].asString().c_str());
			COPYSTRARRAY(m_Friendunit.nickname, val_array[nIndex]["n"].asString().c_str());
			COPYSTRARRAY(m_Friendunit.mobile, val_array[nIndex]["m"].asString().c_str());
			COPYSTRARRAY(m_Friendunit.sign, val_array[nIndex]["g"].asString().c_str());
			if (strlen(m_Friendunit.sign) == 0)
				COPYSTRARRAY(m_Friendunit.sign, "�ͻ�ǩ��");

			m_Friendunit.type = nType;
			m_Friendunit.relation = nGroupid;
			m_Friendunit.sex = (BYTE)val_array[nIndex]["s"].asInt();
			m_Friendunit.online = (BYTE)val_array[nIndex]["o"].asInt();

			alluserNickname[m_Friendunit.userid] = m_Friendunit.nickname;
			m_vtFriendInfo.push_back(m_Friendunit);

		}
		g_pFrame->PostMessage(UM_USER_ADDGROUP, 0, 0);
		g_pFrame->PostMessage(UM_USER_ADDFRIEND, 0, 0);
	}

	return 0;
}

//UPIM_REQ_GLIST ������Ϣ
int OnGListAns(char* pReceive, ULONG leng)
{
	glist_ans* m_glistans = (glist_ans *)pReceive;
	short nItemNum = m_glistans->rtnnum;
	USER_LOG("Recv:[UPIM_REQ_GLIST] ItemNum:%d", nItemNum);
	if (nItemNum > 0)
	{
		glist_unit* m_rtnunit = new glist_unit[nItemNum];
		memset(m_rtnunit, 0, sizeof(glist_unit)*nItemNum);
		memcpy(m_rtnunit, m_glistans->headp, sizeof(glist_unit)*nItemNum);
		for (int nIdex = 0; nIdex<nItemNum; nIdex++)
		{
			USER_GROUP_INFO m_groupunit = {0};
			m_groupunit.m_ucGroupType = m_rtnunit->m_ucGroupType;
			m_groupunit.m_nGroupID = m_rtnunit[nIdex].m_nGroupID;
			COPYSTRARRAY(m_groupunit.m_szGroupName, m_rtnunit[nIdex].m_szGroupName);

			m_vtUserGroup.push_back(m_groupunit);
		}
		TDEL(m_rtnunit);

		g_pFrame->PostMessage(UM_USER_ADDGROUP, 0, 0);

		if (g_MyClient.IsClientLoginIn())
		{
			g_MyClient.SendFriendListReq(eList_SrvGroup);
		}
	}

	return 0;
}

//UPIM_REQ_LIST ������Ϣ
int OnListAns(char* pReceive, ULONG leng)
{
	list_ans* m_listans = (list_ans*)pReceive;
	short nItemNum = m_listans->rtnnum;
	USER_LOG("Recv:[UPIM_REQ_LIST] ItemNum:%d", nItemNum);
	if (nItemNum > 0)
	{
		list_unit* m_rtnunit = new list_unit[nItemNum];
		memset(m_rtnunit, 0, sizeof(list_unit)*nItemNum);
		memcpy(m_rtnunit, m_listans->headp, sizeof(list_unit)*nItemNum);

		for (int nIdex = 0; nIdex<nItemNum; nIdex++)
		{
			FRIEND_INFO m_Friendunit = {0};
			COPYSTRARRAY(m_Friendunit.userid, m_rtnunit[nIdex].userid);
			COPYSTRARRAY(m_Friendunit.truename, m_rtnunit[nIdex].username);
			COPYSTRARRAY(m_Friendunit.nickname, m_rtnunit[nIdex].username);
			m_Friendunit.relation = m_rtnunit[nIdex].relation;
			COPYSTRARRAY(m_Friendunit.sign, m_rtnunit[nIdex].signature);
			m_Friendunit.sex = (BYTE)m_rtnunit[nIdex].sex;
			m_Friendunit.online = (BYTE)m_rtnunit[nIdex].state;

			m_vtFriendInfo.push_back(m_Friendunit);
		}
		TDEL(m_rtnunit);
		g_pFrame->PostMessage(UM_USER_ADDFRIEND, 0, 0);
	}

	return 0;
}

//UPIM_REQ_LIST2 ������Ϣ
int OnListAns2(char* pReceive, ULONG leng)
{
	list_ans2* m_listans2 = (list_ans2*)pReceive;
	char szJson[MAX_SEND_BUF_LEN] = {0};
	strncpy(szJson, m_listans2->headp, m_listans2->len);

	//////////////////////////////////////////////////////////////////////////
	Value value;  
	Reader read;  
	if ( !read.parse( szJson,value ) )  
	{  
		return -1;  
	}
	int nItenNum = value["ct"].asInt();
	Value val_array = value["it"];  
	int iSize = val_array.size();
	if (nItenNum == iSize && nItenNum>0)
	{
		for (int nIndex=0; nIndex<iSize; nIndex++)
		{
			FRIEND_INFO m_Friendunit = {0};
			COPYSTRARRAY(m_Friendunit.userid, val_array[nIndex]["i"].asString().c_str());
			COPYSTRARRAY(m_Friendunit.truename, val_array[nIndex]["n"].asString().c_str());
			COPYSTRARRAY(m_Friendunit.nickname, val_array[nIndex]["n"].asString().c_str());
			COPYSTRARRAY(m_Friendunit.sign, val_array[nIndex]["g"].asString().c_str());

			m_Friendunit.relation = val_array[nIndex]["r"].asInt();
			m_Friendunit.sex = (BYTE)val_array[nIndex]["s"].asInt();
			m_Friendunit.online = (BYTE)val_array[nIndex]["o"].asInt();

			m_vtFriendInfo.push_back(m_Friendunit);
		}
		g_pFrame->PostMessage(UM_USER_ADDFRIEND, 0, 0);
	}

	return 0;
}

//UPIM_REQ_CHECKPWD ������Ϣ
int OnCheckPwdAns(char* pReceive, ULONG leng)
{
	USER_LOG("Recv:[UPIM_REQ_CHECKPWD]");

	login_ans* m_logans = (login_ans*)pReceive;
	g_selfunit.id = m_logans->userid;
	// ���û�����֣���ID����
	if (strlen(m_logans->username) == 0)
	{
#ifndef IM_EXE_TO_UP
		COPYSTRARRAY(m_logans->username, m_logans->userid);
#else
		COPYSTRARRAY(m_logans->username, g_loginname);  // username �� userid  ��һ��  ���ܸ������ 
#endif 
	}
	g_selfunit.nick_name =  m_logans->username;
	g_selfunit.description = m_logans->signature;

	g_MyClient.m_bLoginSuccess = TRUE;
	g_MyClient.m_nDeptID = m_logans->deptid;
	g_MyClient.m_strUserid = m_logans->userid;
	g_MyClient.m_strUserName = m_logans->username;
	strncpy(g_loginname, m_logans->userid, strlen(m_logans->userid));

	USER_LOG("OnCheckPwdAns:m_strUserid = %s --m_strUserName = %s",g_MyClient.m_strUserid ,g_MyClient.m_strUserName);

	DWORD t1 = GetTickCount() ; 
	USER_LOG("��֤�����������ʼ��¼������:%d" ,t1);  
	g_pFrame->PostMessage(UM_USER_LOGIN, 0, 0);

	LoginSuc_Ex();
	OnUserLoginSuc();

	//////////////////////////////////////////////////////////////////////////
	// ������������Ϣ
	if (g_pFrame)
	{
		if (VER_UPIM_NUMS == 3 ||  VER_UPIM_NUMS == 4)
		{
			g_pFrame->UpdateMyselfInfo(&g_selfunit, "����");
			g_pFrame->PostMessage(UM_USER_SETSELFINFO, 0, 0);
		}
		else
		{
			g_pFrame->UpdateMyselfInfo(&g_selfunit, "UPIM");
			g_pFrame->PostMessage(UM_USER_SETSELFINFO, 0, 0);
		}
		if (VER_UPIM_NUMS == 4)
			g_pFrame->PostMessage(UM_USER_GETSELFPIC, 0, 0);
	}
	return 0;
}

// �ص�¼Э��ķ��ذ�
int OnReconnect_Ans(char* pReceive, ULONG leng)
{
	USER_LOG("Recv:[UPIM_REQ_RECONNECT]");
	reconnect_ans* m_reconnans = (reconnect_ans*)pReceive;
	if (m_reconnans->nResult == 1)
	{
		// ���µ�¼�ɹ�
		g_pFrame->PostMessage(UM_USER_ONLINE, 0, 0);
		USER_LOG("�û��ص�½�ɹ��� [error:%d]", m_reconnans->nErrorCode);
	}
	else
	{
		// ����ص�½ʧ�ܣ����ݱ�־�ж�ʧ������
		USER_LOG("�û��ص�½ʧ�ܣ� [error:%d]", m_reconnans->nErrorCode);
	}

	return 0;
}

//�û���¼�ɹ�
void OnUserLoginSuc()
{
#ifndef VER_UPIM_RONGYUN
	// �ͻ���Ա
	if (g_MyClient.m_nUserType == eUser_Client)
	{
		g_MyClient.SendGListReq(eList_SrvGroup);

		if (g_config.m_bPublic)
		{
			// ȡ�ù��ں�
			g_MyClient.SendGetPublicReq();
		}
	}
	// ������Ա
	else if (g_MyClient.m_nUserType == eUser_Broker)
	{
		g_MyClient.SendGcInfoReq();

		// ȡ�ÿͻ�����
		if (g_config.m_bClientGrp)
		{
			USER_GROUP_INFO groupinfo = {0};
			groupinfo.m_ucGroupType = eList_ClientGrp;
			groupinfo.m_nGroupID = GROUPID_CLIENT;
			COPYSTRARRAY(groupinfo.m_szGroupName, STR_CLIENT);
			m_vtUserGroup.push_back(groupinfo);
		}
		//
		if (g_config.m_bDept)
		{
			// ȡ�ò��ŷ���
			g_MyClient.SendDeptGroupReq();
		}
		g_pFrame->AddStdGroupNode();
		if(!g_config.m_bDefGroup && !g_config.m_bDefGroup2 && !g_config.m_bDept)
		{
			// ��û�в��ŵ�ʱ�򣬳��������
			g_pFrame->PostMessageA(UM_USER_ADDGROUP, 0, 0);
			GetGroupUser();
		}
		if (g_config.m_bPublic)
		{
			// ȡ�ù��ں�
			g_MyClient.SendGetPublicReq();
		}
	}
	// Ͷ�˶˵�¼
	else if (g_MyClient.m_nUserType == eUser_UPAnalyst)
	{
		g_MyClient.SendGetAllRoomReq();
	}
	// Ƕ��ͻ��˵Ŀͻ����档dllģʽ
	else if (g_MyClient.m_nUserType == eUser_UPClient)
	{
		if (g_TGChatDialog)
			g_TGChatDialog->LoginSuccess();
	}
	// im2.0�ͻ��汾
	else if (g_MyClient.m_nUserType == eUser_UPClient2)
	{
		DWORD t1 = GetTickCount() ; 
		USER_LOG("���ͻ�ȡ���з�����Ϣ����:%d" ,t1); 
		g_MyClient.SendGetAllTgRoomReq((int)g_nMarket);
		t1 = GetTickCount() ; 
		USER_LOG("��ȡ���з�����Ϣ����:%d" ,t1);
	}
	// im2.0����ʦ�汾
	else if (g_MyClient.m_nUserType == eUser_UPAnalyst2)
	{
		g_MyClient.SendGetAllRoomReq();
	}

#elif defined VER_UPIM_RONGYUN
	GetIMDeptPublicCode();
	g_pFrame->PostMessage(UM_USER_ADDNEWPUBLIC, 0, 0);
	g_pFrame->PostMessage(UM_USER_GETSELFPIC, 0, 0);
#endif
	// ��Ӷ�ʱ������ʱ2500����ȥȡ������Ϣ
	USER_LOG("T_OFFMSG ADD");
	g_pFrame->AddTimer(T_OFFMSG, eTE_OffMsg);
	return;
}

BOOL OnFuncGList_Qs(int grouptype)
{
	switch (grouptype)
	{
	case eList_Dept:
		{
			if (g_pFrame)
			{
				g_pFrame->PostMessage(UM_USER_ADDGROUP, 0, 0);
				if (g_config.m_bDept)
					g_pFrame->PostMessage(UM_USER_ADDDEPT, 0, 0);
				GetGroupUser();
			}
		}
		break;
	default:
		break;
	}
	return TRUE;
}

int GetGroupUser()
{
	if(m_nDeptIdx<0) m_nDeptIdx = 0;
	int nIdx = m_nDeptIdx;
	while(nIdx < (int)m_vtDeptInfo.size())
	{
		if(!m_vtDeptInfo[nIdx].m_bLoad)
		{
			m_vtDeptInfo[nIdx].m_nFailCount ++;
			if(m_vtDeptInfo[nIdx].m_nFailCount > 3) 
				return FALSE;

			g_MyClient.SendGUserReq((short)m_vtDeptInfo[nIdx].m_nGroupID, eList_Dept);
		}
		nIdx++;
	}

	if(m_nGroupIdx<0) m_nGroupIdx=0;
	nIdx = m_nGroupIdx;
	while(nIdx < (int)m_vtUserGroup.size())
	{
		if(m_vtUserGroup[nIdx].m_ucGroupType == eList_SrvGroup)
		{
			nIdx++;
			continue;
		}
		if(!m_vtUserGroup[nIdx].m_bLoad)
		{
			m_vtUserGroup[nIdx].m_nFailCount ++;
			if(m_vtUserGroup[nIdx].m_nFailCount > 3) 
				return FALSE;
			g_MyClient.SendGUserReq((short)m_vtUserGroup[nIdx].m_nGroupID, m_vtUserGroup[nIdx].m_ucGroupType);
		}
		nIdx++;
	}
	return 0;
}

//UPIM_REQ_DEPT ������Ϣ
int OnDeptAns(char* pReceive, ULONG leng)
{
	dept_ans* m_deptans = (dept_ans*)pReceive;
	short nItemNum = m_deptans->rtnnum;
	USER_LOG("Recv:[UPIM_REQ_DEPT] ItemNum:%d", nItemNum);
	if (nItemNum > 0)
	{
		dept_unit* m_rtnunit = new dept_unit[nItemNum];
		memset(m_rtnunit, 0, sizeof(dept_unit)*nItemNum);
		memcpy(m_rtnunit, m_deptans->headp, sizeof(dept_unit)*nItemNum);

		m_vtDeptInfo.clear();
		m_nDeptIdx = 0;

		for (int nIdex = 0; nIdex<nItemNum; nIdex++)
		{
			USER_GROUP_INFO dept = {0};
			dept.m_ucGroupType = eList_Dept;

			dept.m_nGroupID = m_rtnunit[nIdex].deptid;
			dept.m_nParentID =  m_rtnunit[nIdex].predept;
			COPYSTRARRAY(dept.m_szGroupName, m_rtnunit[nIdex].deptname);
			m_vtDeptInfo.push_back(dept);
		}
		TDEL(m_rtnunit);

		OnFuncGList_Qs(eList_Dept);
	}
	return 0;
}

// UPIM_REQ_S_SENDMSG ������Ϣ
int On_S_SendMSG_Ans(char* pReceive, ULONG leng)
{
	RECVMSG2 recvMsg2 = {0};
	s_sendmsg_ans* m_s_sendmsg = (s_sendmsg_ans*)pReceive;
	recvMsg2.m_dwSeq = m_s_sendmsg->dwMsgSeq;
	COPY_USERID(recvMsg2.m_szUSERID, m_s_sendmsg->cFromuserid);
	ConvertTimeToLong(m_s_sendmsg->tmSend, recvMsg2.m_nSendDate, recvMsg2.m_nSendTime);
	recvMsg2.m_ucFormat = m_s_sendmsg->format;
	memcpy(recvMsg2.m_szMsg, m_s_sendmsg->msg, m_s_sendmsg->msglen);
	recvMsg2.m_nMsglen = strlen(recvMsg2.m_szMsg);
	recvMsg2.m_ucMsgType = m_s_sendmsg->ucMsgType;
	recvMsg2.nPublicID = m_s_sendmsg->nPublicID;
	COPY_USERID(recvMsg2.m_szInnerID, m_s_sendmsg->innerID);
	g_pFrame->ProcessRecvMsg(&recvMsg2, FALSE);

	if(recvMsg2.m_dwSeq>0)
		g_MyClient.m_BigPackageRecv.SendAnsMsg(&recvMsg2);

	return 0;
}

// UPIM_REQ_SENDMSG ������Ϣ��ִ
int On_SendMSG_Ans(char* pReceive, ULONG leng)
{
	sendmsg_ans* sendmsgans = (sendmsg_ans*)pReceive;
	SENDMSG_ANS_ sendMsgAns_ = {0};
	COPYSTRARRAY(sendMsgAns_.m_szDesID, sendmsgans->cTouserid);
	sendMsgAns_.m_dwSeq = sendmsgans->dwMsgSeq;
	sendMsgAns_.m_nState = sendmsgans->nUserState;
	sendMsgAns_.m_tmSend = (long)sendmsgans->tmSend;

	bool bOnline = (sendMsgAns_.m_nState == MYSTATE_OFFLINE) ? false : true;

	//////////////////////////////////////////////////////////////////////////
	// ������û�״̬�����仯,�ı�״̬(CLinkManDlg::OnFuncSendMsg)
	g_MyClient.m_BigPackageSend.ProcessMsgAns(sendMsgAns_.m_dwSeq, bOnline);

	return 0;
}

// UPIM_REQ_GCSENDMSG
int OnSendGcMSGAns(char* pReceive, ULONG leng)
{
	gcsendmsg_ans* gcsendmsgans = (gcsendmsg_ans*)pReceive;
	DWORD nSeq = (DWORD)gcsendmsgans->dwMsgSeq;
	g_MyClient.m_BigPackageSend.ProcessMsgAns(nSeq, true);
	g_MyClient.m_BigPackageSend.FeedBackMsgPkg(nSeq);
	return 0;
}

// UPIM_REQ_GCRECVMSG ������Ϣ
int OnRecvGcMSG(char* pReceive, ULONG leng)
{
	gcrecvmsg_ans* gcrecvmsg = (gcrecvmsg_ans*)pReceive;
	g_pFrame->ProcessRecvGroupMsg(gcrecvmsg, FALSE);
	return 0;
}

// UPIM_REQ_GCINFO
int OnGcInfoAns(char* pReceive, ULONG leng)
{
	gcinfo_ans* m_gcinfoans = (gcinfo_ans*)pReceive;
	short nItemNum = m_gcinfoans->rtnnum;
	USER_LOG("Recv:[UPIM_REQ_GCINFO] ItemNum:%d", nItemNum);

	if (nItemNum > 0 && nItemNum<100)
	{
		gcinfo_unit* m_rtnunit = new gcinfo_unit[nItemNum];
		memset(m_rtnunit, 0, sizeof(gcinfo_unit)*nItemNum);
		memcpy(m_rtnunit, m_gcinfoans->headp, sizeof(gcinfo_unit)*nItemNum);

		for (int nIdex = 0; nIdex<nItemNum; nIdex++)
		{
			GROUP_CHAT_INFO chatroom = {0};
			chatroom.m_nRoomId = m_rtnunit[nIdex].RoomId;
			chatroom.m_nRoomType = m_rtnunit[nIdex].Roomtype;

			COPYSTRARRAY(chatroom.m_szMasterID, m_rtnunit[nIdex].masterid);
			COPYSTRARRAY(chatroom.m_szRoomName, m_rtnunit[nIdex].Roomname);
			COPYSTRARRAY(chatroom.m_szNote, m_rtnunit[nIdex].RoomNote);
			if (m_rtnunit[nIdex].delflag == 0)
				chatroom.m_bDelFlag = false;
			else
				chatroom.m_bDelFlag = true;

			ROOMID mRoomID = chatroom.m_nRoomId;
			m_mapChatRoom[mRoomID] = chatroom;
		}
		TDEL(m_rtnunit);
	}

	g_pFrame->PostMessage(UM_USER_ADDROOM, 0, 0);
	return 0;
}

// �õ��̶������ң�JSON��
// UPIM_REQ_GCINFO2
int OnGcInfoAns2(char* pReceive, ULONG leng)
{
	gcinfo_ans2* m_gcinfoans = (gcinfo_ans2*)pReceive;
	short nItemNum = m_gcinfoans->rtnnum;
	char szJson[MAX_SEND_BUF_LEN] = {0};
	strncpy(szJson, m_gcinfoans->headp, m_gcinfoans->nlen);

	USER_LOG("Recv:[UPIM_REQ_GCINFO2] ItemNum:%d", nItemNum);
	//////////////////////////////////////////////////////////////////////////
	Value value;  
	Reader read;  
	if ( !read.parse( szJson,value ) )  
	{  
		return -1;  
	}
	int nItenNum = value["ct"].asInt();
	Value val_array = value["it"];  
	int iSize = val_array.size();
	if (nItenNum == iSize && nItenNum>0)
	{
		for (int nIndex=0; nIndex<iSize; nIndex++)
		{
			GROUP_CHAT_INFO chatroom = {0};
			chatroom.m_nRoomId = val_array[nIndex]["i"].asInt();
			chatroom.m_nRoomType = val_array[nIndex]["t"].asInt();

			COPYSTRARRAY(chatroom.m_szMasterID, val_array[nIndex]["m"].asString().c_str());
			COPYSTRARRAY(chatroom.m_szRoomName, val_array[nIndex]["n"].asString().c_str());
			COPYSTRARRAY(chatroom.m_szNote, val_array[nIndex]["g"].asString().c_str());
			int nDelflag = val_array[nIndex]["d"].asInt();
			if (nDelflag == 0)
				chatroom.m_bDelFlag = false;
			else
				chatroom.m_bDelFlag = true;

			ROOMID mRoomID = chatroom.m_nRoomId;
			m_mapChatRoom[mRoomID] = chatroom;
		}
	}

	g_pFrame->PostMessage(UM_USER_ADDROOM, 0, 0);
	return 0;
}

// UPIM_REQ_GCGETLIST
int OnGcGetListAns(char* pReceive, ULONG leng)
{
	gcgetlist_ans* m_gclistans = (gcgetlist_ans*)pReceive;
	short nItemNum = m_gclistans->rtnnum;
	USER_LOG("Recv:[UPIM_REQ_GCGETLIST] ItemNum:%d", nItemNum);

	if (nItemNum > 0)
	{
		ROOMID mRoomID = m_gclistans->RoomId;
		gcgetlist_unit* m_rtnunit = new gcgetlist_unit[nItemNum];
		memset(m_rtnunit, 0, sizeof(gcgetlist_unit)*nItemNum);
		memcpy(m_rtnunit, m_gclistans->headp, sizeof(gcgetlist_unit)*nItemNum);

		GCR_ITER iter_ = m_mapChatRoom.find(mRoomID);

		if(iter_->second.pVtUser == NULL)
			iter_->second.pVtUser = new VECTOR_GUSER_INFO;
		else
			iter_->second.pVtUser->clear();
		for (int nIdex = 0; nIdex<nItemNum; nIdex++)
		{
			GUSER_INFO guserinfo_ = {0};
			COPYSTRARRAY(guserinfo_.m_szIMID, m_rtnunit[nIdex].userid);
			guserinfo_.m_nUserType = (BYTE)m_rtnunit[nIdex].usertype;
			guserinfo_.userstate = m_rtnunit[nIdex].state;

			InsertVtUser(*iter_->second.pVtUser, guserinfo_);
		}
		TDEL(m_rtnunit);

		g_pFrame->GCGetList(mRoomID);
	}
	return 0;
}

// UPIM_REQ_GCCREATE
int OnGcCreateAns(char* pReceive, ULONG leng)
{
	gccreate_ans* m_gcgccreateans = (gccreate_ans*)pReceive;
	int nRoomParam = m_gcgccreateans->nroomParam;
	// ����ʧ��
	if (!m_gcgccreateans->bSussess)
	{
		g_MyClient.m_CreateGroupParam.RemoveGroupParamFromKey(nRoomParam);
		CString strErrStr = _T("");
		strErrStr.Format("����Ⱥ��ʧ�ܣ�������Ϣ��%s", m_gcgccreateans->ErrStr);
		USER_LOG(strErrStr);
	}
	// �����ɹ�
	else
	{
		LPCGPARAM pCGParam = g_MyClient.m_CreateGroupParam.GetDataFromCreateMapKey(nRoomParam);
		if(!pCGParam) return 0;

		GROUP_CHAT_INFO chatroom = {0};
		chatroom.m_nRoomId = m_gcgccreateans->nRoomID;
		chatroom.m_nRoomType = pCGParam->m_nRoomType;
		COPYSTRARRAY(chatroom.m_szMasterID, pCGParam->m_szMasterID);
		COPYSTRARRAY(chatroom.m_szRoomName, pCGParam->m_szRoomName);
		COPYSTRARRAY(chatroom.m_szNote, "");
		chatroom.m_bDelFlag = false;

		ROOMID mRoomID = chatroom.m_nRoomId;
		m_mapChatRoom[mRoomID] = chatroom;

		// ��Ⱥ�б��д�������ڵ�
		g_pFrame->PostMessage(UM_USER_ADDROOM, 0, 0);

		g_MyClient.m_CreateGroupParam.RemoveGroupParamFromKey(nRoomParam);
	}
	return 0;
}

// UPIM_REQ_GCADD
int OnGcAddAns(char* pReceive, ULONG leng)
{
	gcadd_ans* m_ans = (gcadd_ans*)pReceive;
	g_MyClient.SendGcUserListReq(m_ans->nRoomID, m_ans->roomtype, 0);
	return 0;
}

// UPIM_REQ_S_GCADD
int OnGetS_GCAddAns(char* pReceive, ULONG leng)
{
	gc_s_add_ans* m_ans = (gc_s_add_ans*)pReceive;
	char szJson[MAX_SEND_BUF_LEN] = {0};
	strncpy(szJson, m_ans->headp, m_ans->nlen);

	USER_LOG("Recv:[UPIM_REQ_S_GCADD]");
	//////////////////////////////////////////////////////////////////////////
	Value value;  
	Reader read;  
	if ( !read.parse( szJson,value ) )  
	{  
		return -1;  
	}
	int nItenNum = value["ct"].asInt();
	Value val_array = value["it"];  
	int iSize = val_array.size();
	if (nItenNum == iSize && nItenNum>0)
	{
		for (int nIndex=0; nIndex<iSize; nIndex++)
		{
			GROUP_CHAT_INFO chatroom = {0};
			chatroom.m_nRoomId = val_array[nIndex]["i"].asInt();
			chatroom.m_nRoomType = val_array[nIndex]["t"].asInt();

			COPYSTRARRAY(chatroom.m_szMasterID, val_array[nIndex]["m"].asString().c_str());
			COPYSTRARRAY(chatroom.m_szRoomName, val_array[nIndex]["n"].asString().c_str());
			COPYSTRARRAY(chatroom.m_szNote, val_array[nIndex]["g"].asString().c_str());
			int nDelflag = val_array[nIndex]["d"].asInt();
			if (nDelflag == 0)
				chatroom.m_bDelFlag = false;
			else
				chatroom.m_bDelFlag = true;

			ROOMID mRoomID = chatroom.m_nRoomId;
			m_mapChatRoom[mRoomID] = chatroom;
		}
	}

	g_pFrame->PostMessage(UM_USER_ADDROOM, 0, 0);
	return 0;
}

// UPIM_REQ_GCKICK
int OnGcKickAns(char* pReceive, ULONG leng)
{
	gcleave_ans* m_ans = (gcleave_ans*)pReceive;
	if (!m_ans->bSussess)
	{
		CString strErrStr = _T("");
		strErrStr.Format("�߳�Ⱥ��Աʧ�ܣ�������Ϣ��%s", m_ans->ErrStr);
		USER_LOG(strErrStr);
	}
	else
	{
		ROOMID mRoomID = m_ans->nRoomID;
		GUSER_INFO userinfo_ = {0};
		COPYSTRARRAY(userinfo_.m_szIMID, m_ans->userid);
		userinfo_.m_nUserType = m_ans->nUsertype;

		GCR_ITER iter_ = m_mapChatRoom.find(mRoomID);
		if(iter_->second.pVtUser == NULL)
			return 0;
		DeleteVtUser(*iter_->second.pVtUser, userinfo_);
		//////////////////////////////////////////////////////////////////////////
		// ɾ���򿪵�Ⱥ�Ľ��������û��ڵ�
		g_pFrame->DeleteRoomMember(mRoomID, userinfo_.m_szIMID, userinfo_.m_nUserType);
	}
	return 0;
}

// ���߳�Ⱥ��
int OnGetS_GCKickAns(char* pReceive, ULONG leng)
{
	gckick_s_ans* m_ans = (gckick_s_ans*)pReceive;

	// ��Ⱥ�б���ɾ������ڵ�
	g_pFrame->PostMessage(UM_USER_LEAVEROOM, 0, (LPARAM)m_ans->nRoomID);

	CString strMsg = _T("");
	strMsg.Format("������[%d]�ѽ�ɢ", m_ans->nRoomID);
	USER_LOG(strMsg);
	return 0;
}

// UPIM_REQ_GCLEAVE
int OnGcLeaveAns(char* pReceive, ULONG leng)
{
	gcleave_ans* m_ans = (gcleave_ans*)pReceive;
	if (!m_ans->bSussess)
	{
		CString strErrStr = _T("");
		strErrStr.Format("�˳�Ⱥ��ʧ�ܣ�������Ϣ��%s", m_ans->ErrStr);
		USER_LOG(strErrStr);
	}
	else
	{
		// ��Ⱥ�б���ɾ������ڵ�
		g_pFrame->PostMessage(UM_USER_LEAVEROOM, 0, (LPARAM)m_ans->nRoomID);
	}
	return 0;
}

// UPIM_REQ_GPUBLIC
int OnGetPublicAns(char* pReceive, ULONG leng)
{
	public_ans* m_ans = (public_ans*)pReceive;
	short nItemNum = m_ans->rtnnum;
	char szJson[MAX_SEND_BUF_LEN] = {0};
	strncpy(szJson, m_ans->headp, m_ans->len);

	USER_LOG("Recv:[UPIM_REQ_GPUBLIC] ItemNum:%d", nItemNum);
	Value value;  
	Reader read;  
	if (!read.parse(szJson, value))  
		return -1;  
	int nItenNum = value["ct"].asInt();
	Value val_array = value["it"];  
	int iSize = val_array.size();
	if (nItenNum == iSize && nItenNum>0)
	{
		for (int nIndex=0; nIndex<iSize; nIndex++)
		{
			PUBLIC_INFO m_public = {0};

			m_public.nPublicID = val_array[nIndex]["i"].asInt();
			COPYSTRARRAY(m_public.szName, val_array[nIndex]["n"].asString().c_str());
			COPYSTRARRAY(m_public.szInfo, val_array[nIndex]["c"].asString().c_str());
			COPYSTRARRAY(m_public.szWelcome, val_array[nIndex]["w"].asString().c_str());

			PUBLICID mpublicid = m_public.nPublicID;
			m_mapPublicInfo[mpublicid] = m_public;
		}

		g_pFrame->PostMessage(UM_USER_ADDPUBLIC, 0, 0);
	}

	return 0;
}

// UPIM_REQ_PUBLICINFO
int OnGetPublicInfoAns(char* pReceive, ULONG leng)
{
	publicinfo_ans* m_ans = (publicinfo_ans*)pReceive;
	short nItemNum = m_ans->rtnnum;
	PUBLICID mPublicID = m_ans->publicID;
	char szJson[MAX_SEND_BUF_LEN] = {0};
	strncpy(szJson, m_ans->headp, m_ans->len);

	USER_LOG("Recv:[UPIM_REQ_PUBLICINFO] ItemNum:%d", nItemNum);
	if (nItemNum > 0)
	{
		Value value;  
		Reader read;  
		if (!read.parse(szJson, value))  
			return -1;  
		int nItenNum = value["ct"].asInt();
		Value val_array = value["it"];  
		int iSize = val_array.size();
		if (nItenNum == iSize && nItenNum>0)
		{
			PUB_ITER iter_ = m_mapPublicInfo.find(mPublicID);

			if(iter_->second.pVtRoute == NULL)
				iter_->second.pVtRoute = new VECTOR_ROUTE_INFO;
			else
				iter_->second.pVtRoute->clear();

			for (int nIdex = 0; nIdex<nItemNum; nIdex++)
			{
				ROUTE_INFO routeinfo_ = {0};
				routeinfo_.nID = val_array[nIdex]["i"].asInt();
				COPYSTRARRAY(routeinfo_.m_RName, val_array[nIdex]["n"].asString().c_str());
				routeinfo_.nProblemtype = val_array[nIdex]["p"].asInt();

				iter_->second.pVtRoute->push_back(routeinfo_);
			}
		}
	}

	g_pFrame->GetPublicRoute(mPublicID);
	return 0;
}

// UPIM_REQ_S_ONLINE
int OnGet_S_Online(char* pReceive, ULONG leng)
{
	online_s_ans* m_ans = (online_s_ans*)pReceive;
	g_pFrame->UserStateChange(m_ans->userid, m_ans->nUserstate);
	return 0;
}

// UPIM_REQ_OFFMSG
int OnGetOffMSg(char* pReceive, ULONG leng)
{
	char szTmp[64] = {0};
	CArray<RECVMSG2, RECVMSG2&> aOffMsg;
	RECVMSG2 msg = {0};
	// ��������ڴ���Ⱥ���������Ϣ
	GROUP_CHAT_HIS_MSG roomOffMsg = {0};
	CArray<GROUP_CHAT_HIS_MSG, GROUP_CHAT_HIS_MSG&> aRoomOffmsg;
	BYTE roomType = 0;

	offmsg_ans* m_ans = (offmsg_ans*)pReceive;
	short nItemNum = m_ans->rtnnum;
	char szJson[MAX_SEND_BUF_LEN] = {0};
	strncpy(szJson, m_ans->headp, m_ans->len);

	USER_LOG("Recv:[UPIM_REQ_OFFMSG] ItemNum:%d", nItemNum);
	if (nItemNum > 0)
	{
		Value value;  
		Reader read;  
		if (!read.parse(szJson, value))  
			return -1;  
		int nItenNum = value["ct"].asInt();
		Value val_array = value["it"];  
		int iSize = val_array.size();
		if (nItenNum == iSize && nItenNum>0)
		{
			for (int nIdex = 0; nIdex<nItemNum; nIdex++)
			{
				char szMsgBase64[4*1024] = {0};
				char szMsg[4*1024] = {0};

				roomType = val_array[nIdex]["roomtype"].asInt();
				if (roomType == 0)
				{
					COPYSTRARRAY(msg.m_szUSERID, val_array[nIdex]["src_id"].asString().c_str());
					ConvertTimeToLong(val_array[nIdex]["time"].asInt64(), msg.m_nSendDate, msg.m_nSendTime);
					msg.m_ucFormat = val_array[nIdex]["format"].asInt();

					COPYSTRARRAY(szMsgBase64, val_array[nIdex]["msg"].asString().c_str());
					int	nStrLen = Base64_Encode((BYTE *)szMsgBase64, strlen(szMsgBase64), (BYTE *)szMsg, sizeof(szMsg), FALSE);
					szMsg[nStrLen] = 0;

					// �ͻ���  �յ�������Ϣ�Ĵ��� 
					if ( VER_UPIM_NUMS == 4)
					{
						// m_mapAllClientRoom �ҵ���Ӧ����ʦ�ķ���� 
						int nRoomID = WhitchRoomForAnalys(m_mapAllClientRoom,msg.m_szUSERID) ; 
						COPYSTRARRAY(msg.m_szInnerID , IntToStr(nRoomID));
						msg.m_ucMsgType = eMsgSend_Analyst;
					}
					// ����ʦ�յ���������Ϣ�Ĵ������ 
					else if ( VER_UPIM_NUMS == 3)
					{
						// ����ʦȡ����������Ϣ�������Ϊ���̶��ķ����
						COPYSTRARRAY(msg.m_szInnerID , IntToStr(g_nRoomID_im2_0));
						msg.m_ucMsgType = eMsgSend_Analyst;
					}

					COPYSTRARRAY(msg.m_szMsg, szMsg);
					msg.m_nMsglen = strlen(szMsg);
				}
				else
				{
					roomOffMsg.roomtype = roomType;
					COPYSTRARRAY(roomOffMsg.cFromuserid, val_array[nIdex]["src_id"].asString().c_str());
					roomOffMsg.tmSend = val_array[nIdex]["time"].asInt64();
					roomOffMsg.format = val_array[nIdex]["format"].asInt();
					roomOffMsg.msg = new char[MAX_TEXT_LEN + 1];
					::memset(roomOffMsg.msg, 0, MAX_TEXT_LEN +1);
					COPYSTRARRAY(szMsgBase64, val_array[nIdex]["msg"].asString().c_str());
					int	nStrLen = Base64_Encode((BYTE *)szMsgBase64, strlen(szMsgBase64), (BYTE *)szMsg, sizeof(szMsg), FALSE);
					szMsg[nStrLen] = 0;
					memcpy(roomOffMsg.msg, szMsg, nStrLen);
					roomOffMsg.msglen = strlen(szMsg);
					roomOffMsg.roomid = (ROOMID)val_array[nIdex]["roomid"].asInt64();
					COPYSTRARRAY(roomOffMsg.nickname, val_array[nIdex]["rnick"].asString().c_str());
				}
				if(roomType == 0)  
					aOffMsg.Add(msg);
				else
					aRoomOffmsg.Add(roomOffMsg);
			}

			// ������Ϣ
			if(aOffMsg.GetSize()>0 || aRoomOffmsg.GetSize()>0)
				g_pFrame->PostMessage(UM_SOUND_PLAY, IDR_WAVE_MSG);

			// ������������Ϣ
			for (int i=aOffMsg.GetSize()-1; i>=0; i--)
			{ 
				g_pFrame->ProcessRecvMsg(&aOffMsg[i], TRUE);
			}
			// ���Ⱥ��������Ϣ
			for(int i=aRoomOffmsg.GetSize()-1; i>=0; --i)
			{
				g_pFrame->ProcessRecvGroupMsg(&aRoomOffmsg[i]);
				delete[] (aRoomOffmsg[i].msg);
			}
		}
	}

	return 0;
}

// UPIM_REQ_KICKOFF
int OnKickOffMsg(char* pReceive, ULONG leng)
{
	USER_LOG("UPIM_REQ_KICKOFF");
	g_pFrame->UserKickOff();
	return 0;
}

// UPIM_REQ_SVROFF
int OnSvrOffMsg(char* pReceive, ULONG leng)
{
	USER_LOG("UPIM_REQ_SVROFF");
	g_pFrame->ImSvrOff();
	return 0;
}

//UPIM_REQ_PKG
int On_SendPKG_Ans(char* pReceive, ULONG leng)
{
	return 0;
}

void ProcessDeliverPackage(LPCUSERID tqid, BOOL bReq, LPSTR pBuf, DWORD dwSize)
{
	PACKAGE_HEADER h;
	memcpy(&h,pBuf,sizeof(PACKAGE_HEADER));
	char* pBufPrc = (pBuf+sizeof(PACKAGE_HEADER));
	dwSize -= sizeof(PACKAGE_HEADER);
	if(bReq) // ���շ�
	{
		if(h.protocolid==UPIM_MSG_PKG_TRANSFER)
		{
			MSG_PKG_TRANSFER_REQ *preq = (MSG_PKG_TRANSFER_REQ*)pBufPrc;
			g_MyClient.m_BigPackageRecv.HandleMsgPkg(tqid, preq);
		}
		else
		{
			//m_pLinkManDlg->ProcessDeliverPackage_Req(tqid,&h,pBufPrc,dwSize);
		}
	}
	else // ������
	{
		if(h.protocolid == UPIM_MSG_PKG_TRANSFER)
		{	
			MSG_PKG_TRANSFER_ANS *pans = (MSG_PKG_TRANSFER_ANS*)pBufPrc;
			if(pans->dwSeq > 0)
				g_MyClient.m_BigPackageSend.FeedBackMsgPkg(pans->dwSeq, NULL);
			else 
				g_MyClient.m_BigPackageSend.FeedBackMsgPkg(0, pans->guid);
		}
		else
		{
			//m_pLinkManDlg->ProcessDeliverPackage_Ans(tqid,&h,pBufPrc,dwSize);
		}
	}
}

//��������ת����
int On_S_SendPKG_Ans(char* pReceive, ULONG leng)
{
	s_send_pkg_ans* m_ans = (s_send_pkg_ans*)pReceive;
	DWORD dwSize = 0;
	char* pBuf = NULL;
	BOOL bReq = 0;
	char szTQID[USERID_SIZE]={0};
	COPY_USERID(szTQID, m_ans->cFromuserid);
	bReq = (BOOL)m_ans->nrequest;
	dwSize = m_ans->pkglen;
	pBuf = new char[dwSize+1];
	memset(pBuf, 0, dwSize+1);
	memcpy(pBuf, m_ans->pkg, dwSize);

	ProcessDeliverPackage(szTQID, bReq, pBuf, dwSize);
	TDEL(pBuf);

	return 0;
}

// UPIM_REQ_ALLTGROOM
int On_GetAllTgRoom_Ans(char* pReceive, ULONG leng)
{
	alltgroom_ans* m_ans = (alltgroom_ans*)pReceive;
	short nItemNum = m_ans->rtnnum;
	char szJson[MAX_SEND_BUF_LEN] = {0};
	strncpy(szJson, m_ans->headp, m_ans->len);

	USER_LOG("Recv:[UPIM_REQ_ALLTGROOM] ItemNum:%d", nItemNum);
	Value value;  
	Reader read;  
	if (!read.parse(szJson, value))  
		return -1;  
	int nItenNum = value["ct"].asInt();
	Value val_array = value["it"];  
	COPYSTRARRAY(g_analysheadurl, value["ia"].asString().c_str());
	int iSize = val_array.size();
	if (nItenNum == iSize && nItenNum>0)
	{
		for (int nIndex=0; nIndex<iSize; nIndex++)
		{
			TGROOM_INFO m_tgroom = {0};

			m_tgroom.nRoomID = val_array[nIndex]["i"].asInt();
			COPYSTRARRAY(m_tgroom.szName, val_array[nIndex]["n"].asString().c_str());
			COPYSTRARRAY(m_tgroom.szInfo, val_array[nIndex]["c"].asString().c_str());

			TGROOMID mroomid = m_tgroom.nRoomID;
			m_mapTgRoomInfo[mroomid] = m_tgroom;

			if (VER_UPIM_NUMS == 3)
			{
				// �ӷ�������ȥ����Ŀͻ���Ϣ 
				g_MyClient.SendGetRoomUsersReq((int)mroomid);

				//// ���ͻ���ӵ�������
				//g_pFrame->PostMessage(UM_USER_ADDROOMCLIENT, 0, 0);
				////// �յ��ͻ��б�����ȥȡ�Զ������,�ǺǺ�
				//g_MyClient.SendGetSelfGroupReq() ;  //�Ȳ�ȥ��ȡ�Զ��������Ϣ 

			}

		}

		if (VER_UPIM_NUMS == 3)
		{
			// wuchao test 
			g_pFrame->PostMessage(UM_USER_ADDTGROOM2, 0, 0);

			// ����ȡ�û�ͷ��  ���ݲ�ͬ״̬ȡ��ͬ��ͼƬ  
			g_pFrame->PostMessage(UM_USER_GETSELFPIC, 0, 0);

			g_pFrame->PostMessage(UM_USER_ADDHISTORYCLENT ,0,0) ; 
		}
		else if (VER_UPIM_NUMS == 2)
		{
			g_pFrame->PostMessage(UM_USER_ADDTGROOM, 0, 0);
		}
	}
	return 0;
}

// UPIM_REQ_ALLTGROOMEX
// im2.0ȡ��������������Ϣ
int On_GetAllTgRoomEx_Ans(char* pReceive, ULONG leng)
{
	// ������û�д��ط���ʦ�ó������� 
	alltgroom_ans* m_ans = (alltgroom_ans*)pReceive;
	short nItemNum = m_ans->rtnnum;
	char szJson[MAX_SEND_BUF_LEN] = {0};
	strncpy(szJson, m_ans->headp, m_ans->len);

	// ����JSON ������
	USER_LOG("Recv:[UPIM_REQ_ALLTGROOMEX] ItemNum:%d", nItemNum);
	Value value;  
	Reader read;  
	if (!read.parse(szJson, value))  
	{
		USER_LOG("On_GetAllTgRoomEx_Ans����JSONʧ��") ; 
		return -1;  
	}
	int nItenNum = value["ct"].asInt();
	Value val_array = value["d"];  
	int iSize = val_array.size();
	if (nItenNum == iSize && nItenNum>0)
	{
		// �����ÿ��������û���������m_mapAllClientRoom�У���ά����һ������ID�ͷ����ڲ���Ա��ӳ���ϵ
		for (int nIndex=0; nIndex<iSize; nIndex++)
		{
			ALLCLIENT_ROOM_INFO m_roomInfo = {0};
			m_roomInfo.m_nIsVip = val_array[nIndex]["ic"].asInt();
			COPYSTRARRAY(m_roomInfo.m_szRoomName, val_array[nIndex]["rn"].asString().c_str());

			CString csRoomID(val_array[nIndex]["r"].asString().c_str());
			m_roomInfo.m_nRoomID = atoi(csRoomID);

			CString csVIPID(val_array[nIndex]["vip"].asString().c_str());
			m_roomInfo.m_nVipRight = atoi(csVIPID);

			m_roomInfo.m_nAnalysNum =  val_array[nIndex]["ac"].asInt();

			// �������߷���ʦ���� 
			m_roomInfo.m_nOnLineAnalysNum = val_array[nIndex]["olc"].asInt() ; 

			if (m_roomInfo.m_nAnalysNum > 0)
			{
				m_roomInfo.pVtAnalys = new VECTOR_ROOMANALYS_INFO();
				Value val_array_2 = val_array[nIndex]["it"];
				int iSize2 = val_array_2.size();
				for (int nIndex2=0; nIndex2<iSize2; nIndex2++)
				{
					ROOMANALYS_INFO m_roomAnalyst = {0};
					m_roomAnalyst.m_nAnalysID = val_array_2[nIndex2]["i"].asInt();
					// �Ƿ����� 
					m_roomAnalyst.m_bIsOnLine = val_array_2[nIndex2]["ol"].asBool() ; 
					COPYSTRARRAY(m_roomAnalyst.m_szAnalysName, val_array_2[nIndex2]["n"].asString().c_str());
					COPYSTRARRAY(m_roomAnalyst.m_szImgURL, val_array_2[nIndex2]["ia"].asString().c_str());
					COPYSTRARRAY(m_roomAnalyst.m_szGood, val_array_2[nIndex2]["sa"].asString().c_str());
					m_roomInfo.pVtAnalys->push_back(m_roomAnalyst);
				}
				std::sort((*m_roomInfo.pVtAnalys).begin() ,(*m_roomInfo.pVtAnalys).end() ,SortByNameAndOnline) ; 
			}
			TGROOMID mroomid = m_roomInfo.m_nRoomID;
			m_mapAllClientRoom[mroomid] = m_roomInfo;
		}// end of for() ; 
		// �����ȴ�web����  download pic   ����ӷ���ʦ����  �᲻����ɺ����б������������
		DWORD t1 = GetTickCount() ; 
		USER_LOG("������ӷ���ʦ����:%d" ,t1) ; 
		g_pFrame->PostMessage(UM_USER_ADDROOMANALYS, 0, 0);
	}
	return 0;
}

// UPIM_REQ_ALLROOMTOUSER
// im2.0ȡ�÷��������пͻ���Ϣ
int On_GetUserByRoomID_Ans(char* pReceive, ULONG leng)
{
	alltgroom_ans* m_ans = (alltgroom_ans*)pReceive;
	short nItemNum = m_ans->rtnnum;
	char szJson[MAX_SEND_BUF_LEN] = {0};
	strncpy(szJson, m_ans->headp, m_ans->len);

	// ����JSON ������
	USER_LOG("Recv:[UPIM_REQ_ALLROOMTOUSER] ItemNum:%d", nItemNum);
	Value value;  
	Reader read;  
	if (!read.parse(szJson, value))  
	{
		USER_LOG("%s:����JSONʧ��",__FUNCDNAME__) ; 
		return -1;  
	}
	int nRoomID = value["r"].asInt();
	int nItenNum = value["c"].asInt();
	Value val_array = value["a"];  
	int iSize = val_array.size();
	if (nItenNum == iSize && nItenNum>0)
	{
		for (int nIndex=0; nIndex<iSize; nIndex++)
		{
			USER_ROOMCLIENT_INFO m_info ;
			memset(&m_info,0,sizeof(USER_ROOMCLIENT_INFO)) ;
			//COPYSTRARRAY(m_info.m_szUPID, val_array[nIndex].asString().c_str());
			COPYSTRARRAY(m_info.m_szUPID, val_array[nIndex]["n"].asString().c_str());
			int isOnline = val_array[nIndex]["o"].asInt() ; 
			if( isOnline == 1 )
				m_info.m_bIsOnLine = TRUE ;
			else
				m_info.m_bIsOnLine = FALSE ; 

			// json�д��������û�ID���ظ��ģ����ظ��ģ����ظ��ģ�
			if (!IsInvtRoomClient(m_info.m_szUPID))
				m_vtRoomClient.push_back(m_info);
			else
			{
				USER_LOG("chongfu %s",m_info.m_szUPID);
			}
		}
		// �����Ƿ�����  ��  ����˳������ 
		//std::sort( m_vtRoomClient.begin() ,m_vtRoomClient.end() ,SortByNameAndOnlineClient) ; 
		g_pFrame->SendMessage(UM_USER_ADDROOMCLIENT, 0, 0);
	}

	// �յ��ͻ��б�����ȥȡ�Զ������,�ǺǺ�
	g_MyClient.SendGetSelfGroupReq() ;  //�Ȳ�ȥ��ȡ�Զ��������Ϣ  
	return 0;
}

// UPIM_REQ_GETGROUP
// im2.0�汾�з�����Ա�Զ������
int OnGetSelfGroup_Ans(char* pReceive, ULONG leng)
{
	getgroup_ans* m_ans = (getgroup_ans*)pReceive;
	short nItemNum = m_ans->rtnnum;
	m_mapSelfGroups.clear();

	//////////////////////////////////////////////////////////////////////////
	// �п���û�з��飬���ǻ���Ҫ����
	m_groupInfoStc[0].bUsed = 1;
	m_groupInfoStc[0].bGetUserInfo = 1;
	m_groupInfoStc[0].nGroupID = 0;
	m_groupInfoStc[0].GroupName = _T("δ����ͻ�");
	m_mapSelfGroups[0] = _T("δ����ͻ�");

	if (nItemNum > 0)
	{
		char szJson[MAX_SEND_BUF_LEN] = {0};
		strncpy(szJson, m_ans->headp, m_ans->len);

		// ����JSON ������
		USER_LOG("Recv:[UPIM_REQ_GETGROUP] ItemNum:%d", nItemNum);
		Value value;  
		Reader read;  
		if (!read.parse(szJson, value))  
			return -1;
		int nItenNum = value["ct"].asInt();
		Value val_array = value["it"];  
		int iSize = val_array.size();
		if (nItenNum == iSize && nItenNum>0)
		{
			for (int nIndex=0; nIndex<iSize; nIndex++)
			{
				CString strGroupID = val_array[nIndex]["gid"].asString().c_str();
				int nGroupID = atoi(strGroupID);
				CString strGroupName = val_array[nIndex]["gname"].asString().c_str();
				int nGNum = val_array[nIndex]["gnum"].asInt();

				m_groupInfoStc[nGNum].bUsed = 1;
				m_groupInfoStc[nGNum].nGroupID = nGroupID;
				m_groupInfoStc[nGNum].GroupName = strGroupName;
				m_mapSelfGroups[nGroupID] = strGroupName;
				g_MyClient.SendGetSelfGroupUsersReq(nGroupID);
			}
		}
	}
	else
	{
		// ���ܸ�����û�з���
		// �����⵽���еķ�����Ϣ���������ˣ����ڽ����ϸ��·���
		if (IsAllGroupLoad())
			g_pFrame->PostMessage(UM_USER_ADDSELFGROUP, 0, 0);
	}
	return 0;
}

// UPIM_REQ_GETGUSER
// im2.0ȡ�÷����¶�Ӧ���û��б�
int OnGetSelfGroupUsers_Ans(char* pReceive, ULONG leng)
{
	getguser_ans* m_ans = (getguser_ans*)pReceive;
	short nItemNum = m_ans->rtnnum;
	int nGroupID = m_ans->nGroupID;
	UpdateGroupFlag(nGroupID);

	if (nItemNum > 0)
	{
		char szJson[MAX_SEND_BUF_LEN] = {0};
		strncpy(szJson, m_ans->headp, m_ans->len);
		// ����JSON ������
		USER_LOG("Recv:[UPIM_REQ_GETGUSER] ItemNum:%d GroupId=%d", nItemNum, nGroupID);
		Value value;  
		Reader read;  
		if (!read.parse(szJson, value))  
			return -1;
		int nItenNum = value["ct"].asInt();
		Value val_array = value["it"];  
		int iSize = val_array.size();
		if (nItenNum == iSize && nItenNum>0)
		{
			for (int nIndex=0; nIndex<iSize; nIndex++)
			{
				CString strUPID = val_array[nIndex].asString().c_str();
				UpdateVtClientInfo(strUPID, nGroupID);
			}
		}
	}

	//�����⵽���еķ�����Ϣ���������ˣ����ڽ����ϸ��·���
	if (IsAllGroupLoad())
		g_pFrame->PostMessage(UM_USER_ADDSELFGROUP, 0, 0);

	return 0;
}

// UPIM_REQ_ADDGROUP
// im2.0���/�޸��Զ��������Ϣ
int OnSetSelfGroup_Ans(char* pReceive, ULONG leng)
{
	json_ans* m_ans = (json_ans*)pReceive;
	short nItemNum = m_ans->rtnnum;
	char szJson[MAX_SEND_BUF_LEN] = {0};
	strncpy(szJson, m_ans->headp, m_ans->len);
	if( szJson )
	{
		Value value;  
		Reader read;  
		if (!read.parse(szJson, value))  
			return -1;

		// ��ȡ������name  
		CString strGroupName  = _T("") ;
		CString strGroupID    = _T("") ; 

		strGroupName = value["gname"].asCString() ;
		strGroupID   = value["gid"] .asCString(); 
		int iType = atoi(value["type"].asString().c_str()) ; 

		// Ȼ������Ϣ������������ʾ���ӷ��� 
		//g_MyClient.SendGetSelfGroupReq();
		if(iType == 1 )
		{
			// ���ӷ��� 
			g_pFrame->m_pUserMrgDialog->AddGroup(strGroupName,strGroupID) ; 
		}
		else if( iType == 0 )
		{
			// ɾ������ 
			g_pFrame->m_pUserMrgDialog->DelGroup(strGroupName,strGroupID) ;
			// �����б���ɾ���������  
			g_pFrame->DeleGroup(strGroupName,strGroupID); 
		}

		//////////////////////////////////֪ͨ��������Զ������////////////////////// 
		//�����⵽���еķ�����Ϣ���������ˣ����ڽ����ϸ��·���
		if (IsAllGroupLoad())
			g_pFrame->PostMessage(UM_USER_ADDSELFGROUP, 0, 0);
	}
	return 0;
}

// UPIM_REQ_MODGUSER
// im2.0���/�޸��û��ķ���
int OnSetSelfGroupUser_Ans(char* pReceive, ULONG leng)
{
	modguser_ans* m_ans = (modguser_ans*)pReceive;
	short nItemNum = m_ans->rtnnum;
	char szJson[MAX_SEND_BUF_LEN] = {0};
	strncpy(szJson, m_ans->headp, m_ans->len);
	if( !szJson)
		return 0 ; 
	Reader read ; 
	Value value ; 
	int nGroupID = -1 ; 
	int iType = -1 ; 

	if( NULL != read.parse(szJson,value))
	{
		nGroupID = value["groupID"].asInt() ;  
		iType    = value["nType"].asInt() ; 

		Value client_array = value["item"] ;
		int iSize = client_array.size() ; 
		for( int i = 0 ; i < iSize ; ++i )
		{
			CString strClientID = client_array[i]["clientID"].asCString() ;
			if( iType == 1 )
			{
				// �������������һ���ͻ�
				// g_pFrame->PostMessage(0,0,0) ; 
				// ����m_pSelfGroup�����б����ҵ�����ڵ� 
				// Ȼ���ڸ÷���ĺ����б�������ӽڵ�
				g_pFrame->AddSelfGroupClientNode(nGroupID,strClientID) ; 
			}
			else if( iType == 0 )
			{
				// ���ڴ��ڵķ�����ɾ���ͻ� 
				g_pFrame->DelSelfGroupClientNode(nGroupID ,strClientID) ;
			}
		}
	}
	//if( iType == 1 )
	//{
	//	// �������������һ���ͻ�
	//	// g_pFrame->PostMessage(0,0,0) ; 
	//	// ����m_pSelfGroup�����б����ҵ�����ڵ� 
	//	// Ȼ���ڸ÷���ĺ����б�������ӽڵ�
	//	// g_pFrame->AddSelfGroupClientNode(nGroupID,strClientID) ;
	//	g_pFrame->PostMessage(UM_USER_ADDSELFGROUP ,0,0) ; 
	//}
	//else if( iType == 0 )
	//{
	//	// ���ڴ��ڵķ�����ɾ���ͻ� 
	//	// g_pFrame->DelSelfGroupClientNode(nGroupID ,strClientID) ;
	//	g_pFrame->PostMessage(UM_USER_ADDSELFGROUP ,0,0) ;
	//}
	return 0;
}

// ȡ��������Ϣ
int OnGetUserState_Ans(char* pReceive, ULONG leng)
{
	USER_LOG("OnGetUserState_Ans") ;
	userstate_ans* m_ans = (userstate_ans*)pReceive;
	short nItemNum = m_ans->rtnnum;
	char szJson[MAX_SEND_BUF_LEN] = {0};
	strncpy(szJson, m_ans->headp, m_ans->len);
	int nFlag = m_ans->flag;

	BOOL bChange = FALSE;			// ״̬�иı�
	BOOL bNoOneOnline = TRUE;		// ��������
	Value value;  
	Reader read;  
	if (!read.parse(szJson, value))  
		return -1;  
	int nItenNum = value["ct"].asInt();
	Value val_array = value["it"];  
	int iSize = val_array.size();
	if (nItenNum == iSize && nItenNum>0)
	{
		for (int nIndex=0; nIndex<iSize; nIndex++)
		{
			CString strUid = val_array[nIndex]["n"].asString().c_str();
			int nstate =  val_array[nIndex]["s"].asInt();
			CDuiString dstr = strUid;
			int nOldState = 0;
			nOldState = allUserState[dstr];
			allUserState[dstr] = nstate;
			if (nstate == 1)
				bNoOneOnline = FALSE;
			if (nOldState != nstate)
				bChange = TRUE;

			// �ͻ���¼ʱ 
			if(VER_UPIM_NUMS == 4)
			{
				if( bChange /*&& nstate == 1*/ )
				{
					bChange = FALSE ;
					CDuiString strUID = _T("") ; 
					strUID.Format("%s" ,strUid) ; 
					g_pFrame->AnalystStateChange(strUID, nstate);
				}
			}
		}
	}
	g_pFrame->PostMessage(UM_USER_STATECHANGE, (WPARAM)bChange, (LPARAM)bNoOneOnline);
	//g_pFrame->UserStateChange(m_ans->userid, m_ans->nUserstate);
	return 0;
}


void connectCallback(const wchar_t* json_str)
{
	int err_code = -1;
	Json::Reader reader;
	Json::Value jobj;
	std::string str = txtutil::convert_wcs_to_utf8(json_str);
	if (reader.parse(str, jobj))  // reader��Json�ַ���������jobj������Json��������Ԫ��  
	{
		std::string result = jobj["result"].asString();
		std::string userId = jobj["userId"].asString();
		err_code = jobj["err_code"].asInt();
	}
	if (0 == err_code )
	{
		g_pFrame->PostMessage(UM_USER_LOGIN, 0, 0);

		LoginSuc_Ex();
		OnUserLoginSuc();

		//////////////////////////////////////////////////////////////////////////
		// ������������Ϣ
		if (g_pFrame)
		{
			g_selfunit.id = g_loginname;
			g_selfunit.nick_name =  g_usernc;
			g_selfunit.description = "";
			g_pFrame->UpdateMyselfInfo(&g_selfunit, "����");
			g_pFrame->PostMessage(UM_USER_SETSELFINFO, 0, 0);
		}
	}
};

//�쳣����
void __stdcall exception_callback(const wchar_t* json_str)
{
	std::string str = txtutil::convert_wcs_to_utf8(json_str);
	Json::Reader reader;
	Json::Value jobj;
	if (reader.parse(str, jobj))  // reader��Json�ַ���������jobj������Json��������Ԫ��  
	{

	}
}

//��Ϣ����
void __stdcall message_callback(const wchar_t* json_str)
{
	Json::Reader reader;
	Json::Value jobj;
	Json::Value msg_jobj;
	//std::string str = txtutil::convert_wcs_to_utf8(json_str);
	CString str(json_str);
	if (reader.parse(str.GetBuffer(0), jobj))  // reader��Json�ַ���������jobj������Json��������Ԫ��  
	{
		NEWRECVMSGPUBLIC recvMsg2 = {0};
		CString msgType = jobj["m_ClazzName"].asCString();
		int m_MessageId = jobj["m_MessageId"].asInt();
		CString m_SenderId = jobj["m_SenderId"].asCString();//���ں�ID
		CString m_SendTime = jobj["m_SendTime"].asCString();
		if (!msgType.Compare("RC:CmdNtf"))  //�Զ�����Ϣ 
		{
			if (reader.parse(jobj["m_Message"].asString(),msg_jobj))
			{
				Value value_ = msg_jobj["data"];
				CString saleid = value_["saleId"].asCString();//���ں���ͻ�����Ϣ�Ŀͷ���Ա
				CString msg = value_["msg"].asCString();
				recvMsg2.m_dwSeq = m_MessageId;
				COPY_USERID(recvMsg2.m_szUSERID, (LPCTSTR)saleid);
				int year,month,day,hour,minute,second;
				sscanf((LPCTSTR)m_SendTime,"%d-%d-%d %d:%d:%d",&year,&month,&day,&hour,&minute,&second);
				recvMsg2.m_nSendDate = (year+1900)*10000+(month+1)*100+day;
				recvMsg2.m_nSendTime = hour*10000+minute*100+second;
				recvMsg2.m_ucFormat = eMsgFormat_Txt;
				memcpy(recvMsg2.m_szMsg, (LPCTSTR)msg, msg.GetLength());
				recvMsg2.m_nMsglen = strlen(recvMsg2.m_szMsg);
				recvMsg2.m_ucMsgType = eMsgSend_NewPublic;
				COPYSTRARRAY(recvMsg2.nPublicID ,(LPCTSTR)m_SenderId);
				COPY_USERID(recvMsg2.m_szInnerID, NULL);

				g_pFrame->SendMessage(UM_USER_ADDNEWLASTUSER, (WPARAM)saleid.GetBuffer(saleid.GetLength()), 0);
				
			}
		}
		else if(!msgType.Compare("RC:TxtMsg")) {
			if (reader.parse(jobj["m_Message"].asString(),msg_jobj))
			{
				CString msg = msg_jobj["content"].asCString();
				recvMsg2.m_dwSeq = m_MessageId;
				COPY_USERID(recvMsg2.m_szUSERID, (LPCTSTR)m_SenderId);
				int year,month,day,hour,minute,second;
				sscanf((LPCTSTR)m_SendTime,"%d-%d-%d %d:%d:%d",&year,&month,&day,&hour,&minute,&second);
				recvMsg2.m_nSendDate = (year+1900)*10000+(month+1)*100+day;
				recvMsg2.m_nSendTime = hour*10000+minute*100+second;
				recvMsg2.m_ucFormat = eMsgFormat_Txt;
				memcpy(recvMsg2.m_szMsg, (LPCTSTR)msg, msg.GetLength());
				recvMsg2.m_nMsglen = strlen(recvMsg2.m_szMsg);
				recvMsg2.m_ucMsgType = eMsgSend_NewPublic;
				COPYSTRARRAY(recvMsg2.nPublicID ,(LPCTSTR)m_SenderId);
				COPY_USERID(recvMsg2.m_szInnerID, NULL);
			}
		}
		g_pFrame->ProcessRecvMsg(&recvMsg2);
// 		if (reader.parse(ansi_msg_json_str,msg_jobj))
// 		{
// 			wstring content_str = txtutil::convert_utf8_to_wcs(msg_jobj["content"].asString());
// 		}
	}
}

void __stdcall custom_message_callback(const wchar_t* json_str)//�Զ�����Ϣ�ص�
{
	Json::Reader reader;
	Json::Value jobj;
	Json::Value msg_jobj;
	std::string str = txtutil::convert_wcs_to_utf8(json_str);
	if (reader.parse(str, jobj))  // reader��Json�ַ���������jobj������Json��������Ԫ��  
	{
		string ansi_msg_json_str = jobj["m_Message"].asString();
		if (reader.parse(ansi_msg_json_str,msg_jobj))
		{
			wstring content_str = txtutil::convert_utf8_to_wcs(msg_jobj["content"].asString());
		}
	}
}