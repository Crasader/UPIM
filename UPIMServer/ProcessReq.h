#pragma once
//////////////////////////////////////////////////////////////////////////
// ���д����յ�����������
void ReqLogFilter(int nProtoco,DWORD dwConnID);

BOOL OnReceive_Ex(DWORD dwConnID, const BYTE* pData, int iLength);

// �û��ص�¼
int OnReConnectReq(DWORD dwConnID, char* pReceive, ULONG leng);

// �û�У��
int OnCheckPwdReq(DWORD dwConnID, char* pReceive, ULONG leng);

// ������Ա(������Ա����)
int OnGUserReq(DWORD dwConnID, char* pReceive, ULONG leng);

// ������Ա(������Ա����)(Json)
int OnGUserReq2(DWORD dwConnID, char* pReceive, ULONG leng);

// �õ������б�(�ͻ�)
int OnGListReq(DWORD dwConnID, char* pReceive, ULONG leng);

// �õ���ϵ���б�
int OnListReq(DWORD dwConnID, char* pReceive, ULONG leng);

// �õ���ϵ���б�(Json)
int OnListReq2(DWORD dwConnID, char* pReceive, ULONG leng);

// ��Ϣ����(�ͻ�������Ϣ��������)
int OnSendMSGReq(DWORD dwConnID, char* pReceive, ULONG leng);

// �����б�
int OnDeptReq(DWORD dwConnID, char* pReceive, ULONG leng);

// �õ��̶�������
int OnGcInfoReq(DWORD dwConnID, char* pReceive, ULONG leng);

// �õ��̶�������(Json)
int OnGcInfoReq2(DWORD dwConnID, char* pReceive, ULONG leng);

// Ⱥ������,�õ���ϵ���б�
int OnGcGetListReq(DWORD dwConnID, char* pReceive, ULONG leng);

// Ⱥ�鷢����Ϣ(�ͻ�������Ϣ��������)
int OnGcSendMSGReq(DWORD dwConnID, char* pReceive, ULONG leng);

// Ⱥ������,����
int OnGcCreateReq(DWORD dwConnID, char* pReceive, ULONG leng);

// Ⱥ������,��ӳ�Ա
int OnGcAddReq(DWORD dwConnID, char* pReceive, ULONG leng);

// Ⱥ�����죬���ͱ������Ϣ�������û�
int OnGcAdd_ex(DWORD dwConnID, ROOMID nRoomID, int nRoomType);

// Ⱥ������,����
int OnGcKickReq(DWORD dwConnID, char* pReceive, ULONG leng);

// Ⱥ�����죬���ͱ��߳���Ϣ�������û�
int OnGcKick_ex(DWORD dwConnID, ROOMID nRoomID, int nRoomType);

// Ⱥ������,�뿪
int OnGcLeaveReq(DWORD dwConnID, char* pReceive, ULONG leng);

// ��ȡ���ں�
int OnGPublic(DWORD dwConnID, char* pReceive, ULONG leng);

// ��ȡ���ں���Ϣ
int OnPublicInfo(DWORD dwConnID, char* pReceive, ULONG leng);

// �ͻ��Ͽ����ں�����
int OnPublicConClose(DWORD dwConnID, char* pReceive, ULONG leng);

// �ͻ�����״̬�ı���Ϣ���������б��е������û�
int OnOLNotify(DWORD dwConnID, char* pReceive, ULONG leng);

// �ͻ��ӷ�������ȡ��������Ϣ
int OnOFFMsgReq(DWORD dwConnID, char* pReceive, ULONG leng);

// �ͻ��������Ƶİ�
int OnPkgReq(DWORD dwConnID, char* pReceive, ULONG leng);

// ����û�״̬
int OnSendUserState(DWORD dwConnID, char* pReceive, ULONG leng);

// Ͷ�˻�ȡ������
int OnGetAllTgRoom(DWORD dwConnID, char* pReceive, ULONG leng);

// ��ȡ���з���Ŷ�Ӧ����ʦ�б�
int OnGetAllTgRoomEx(DWORD dwConnID, char* pReceive, ULONG leng);

// ��ȡ���з���Ŷ�Ӧ�û��б�
int OnGetAllRoomToUser(DWORD dwConnID, char* pReceive, ULONG leng);

// ��ѯ�û�����״̬
int OnGetUserState(DWORD dwConnID, char* pReceive, ULONG leng);

// im2.0�汾�з�����Ա�Զ������
int OnGetSelfGroup(DWORD dwConnID, char* pReceive, ULONG leng);

// im2.0�汾�з�����Աȡ���Զ�������µĿͻ��б�
int OnGetSelfGroupUsers(DWORD dwConnID, char* pReceive, ULONG leng);

// im2.0�汾�з�����Ա�༭�Զ������
int OnSetSelfGroup(DWORD dwConnID, char* pReceive, ULONG leng);

// im2.0�汾�з�����Ա�༭�Զ������Ŀͻ��б�
int OnSetSelfGroupUser(DWORD dwConnID, char* pReceive, ULONG leng);