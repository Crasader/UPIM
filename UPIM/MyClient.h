#pragma once
#include "stdafx.h"
#include "../Socket/HP-Socket/Src/TcpClient.h"
#include "../Socket/HP-Socket/Global/helper.h"

#include "globalvar.h"
#include "PackageManage.h"
#include "MsgQueueSendMng.h"
#include "CreateGroupParam.h"
#include "PackageRecvManage.h"

//#define NEW_DEPACK 


//ϵͳ����
class CMyClient : public CTcpClientListener
{
public:
	CMyClient(void);
	virtual ~CMyClient(void);
public:
	void InitClient();
	BOOL StartClient(LPCTSTR pszRemoteAddress, USHORT usPortt, BOOL bAsyncConnect = FALSE);
	BOOL StopClient();
	BOOL SetClientInfo(short nUserType);

	BOOL SendClientMsg(const BYTE* pBuffer, int iLength, int iOffset = 0);
	BOOL IsClientLoginIn() {return m_nUserType == eUser_Client;}
	BOOL IsMyUserID(LPCUSERID imid) {return strcmp(m_strUserName.GetBuffer(0), imid)==0;}

	BOOL SendCheckPwdReq(LPCTSTR UID, LPCTSTR PWD, short nCheckType);
	BOOL SendGUserReq(short nGroupID, short nType);
	BOOL SendMsgReq(sendmsg_req *preq);
	BOOL SendGListReq(short nGrouptype);
	BOOL SendFriendListReq(short nGrouptype);
	BOOL SendDeptGroupReq();
	BOOL SendGcInfoReq();
	BOOL SendGcUserListReq(ROOMID nRoomID, int RoomType, int nStartPos);
	BOOL SendGroupMsgReq(gcsendmsg_req *preq);
	BOOL SendCreateGroupReq(LPCTSTR strGroupName, short nGrouptype, std::vector<GUPID>* pVtFriend=NULL);
	BOOL SendGcAddReq(ROOMID groupid, short grouptype, LPCTSTR pszupid);
	BOOL SendGcAddReq(GROUP_CHAT_ADD_STU m_stu);
	BOOL SendGcKickReq(ROOMID groupid, short grouptype, LPCUSERID upid, short nUsertype);
	BOOL SendGcLeaveReq(ROOMID groupid, short grouptype);
	BOOL SendGetPublicReq();
	BOOL SendGetPublicInfoReq(int nPublicID);
	BOOL SendReconnentReq();
	BOOL SendPubconCloseReq(LPCUSERID svcid, int publicID, int routeID, int closetype);
	BOOL SendModifyUserInfoReq(MODIFY_USERINFO_STU m_stu);
	BOOL SendStateNotifyReq(string sendid_json, int nstate);  // ���Լ���״̬�ı����͵����ߵĺ���
	BOOL SendOFFMSGReq();
	BOOL SendPkgReq(LPCUSERID tqid,bool request,CClientPackage *pkg);
	BOOL SendGetAllRoomReq();
	BOOL SendGetUserState(LPCUSERID userids, int nFlag = 0);
	BOOL SendGetAllTgRoomReq(int nMarket);			//im2.0�汾�пͻ����ܿ������еķ��䣬���еķ���ʦ
	BOOL SendGetRoomUsersReq(int nRoomID);			//im2.0�汾�з�����Ա�ܿ����÷��������еĿͻ���Ϣ
	BOOL SendGetSelfGroupReq();						//im2.0�汾�з�����Ա�Զ������
	BOOL SendGetSelfGroupUsersReq(int nGroupID);	//im2.0�汾�з�����Աȡ���Զ�������µĿͻ��б�
	BOOL SendSetSelfGroupReq(string sjson);			//im2.0�汾�з�����Ա�༭�Զ������
	BOOL SendSetSelfGroupUserReq(string sjson);		//im2.0�汾�з�����Ա�༭�Զ������Ŀͻ��б�

private:
	virtual EnHandleResult OnSend(CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHandleResult OnReceive(CONNID dwConnID, const BYTE* pData, int iLength);
	virtual EnHandleResult OnClose(CONNID dwConnID);
	virtual EnHandleResult OnError(CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode);
	virtual EnHandleResult OnConnect(CONNID dwConnID);

public:
	BOOL m_bLoginSuccess;
	BOOL m_bMainWndClose;
	BOOL m_bAsyncConn;
	BOOL m_bConnect;
	CTcpClient m_Client;

	CString m_strUserName;
	CString m_strUserid;
	
	CString m_strYYBid;
	short	m_nUserType;
	short	m_nDeptID;
	CPackageManage		m_BigPackageSend;		// ������Ϣ����
	CPackageRecvManage	m_BigPackageRecv;		// ��Ϣ���Ͱ����մ���
	CMsgQueueSendMng	m_MsgQueueSendMng;		// ������Ϣ���ʹ���
	CCreateGroupParam	m_CreateGroupParam;		// ����Ⱥ��ʱ��Ĵ���
};