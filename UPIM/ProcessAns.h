/*
* �˴����ڷ��������ص����ݽ��м��д���
*/
#pragma once
//�û���¼�ɹ�
void OnUserLoginSuc();

//��ȡ�����û�
int  GetGroupUser();

BOOL OnFuncGList_Qs(int grouptype);

//////////////////////////////////////////////////////////////////////////
// ȡ�÷����������������ݣ����д������
int ReciveDataFromSVR(const BYTE* pData, int iLength);

// �û�У�鷵��
int OnCheckPwdAns(char* pReceive, ULONG leng);

// ������Ա(������Ա����)����
int OnGUserAns(char* pReceive, ULONG leng);

// ������Ա(������Ա����)���أ�JSON��
int OnGUserAns2(char* pReceive, ULONG leng);

// �õ������б�(�ͻ�)����
int OnGListAns(char* pReceive, ULONG leng);

// �ͻ��õ���ϵ���б�
int OnListAns(char* pReceive, ULONG leng);

// �ͻ��õ���ϵ���б�JSON��
int OnListAns2(char* pReceive, ULONG leng);

// ��Ϣ����(�ͻ�������Ϣ��������)����
int On_SendMSG_Ans(char* pReceive, ULONG leng);

// ��Ϣ����(������������Ϣ)
int On_S_SendMSG_Ans(char* pReceive, ULONG leng);

// �����б�
int OnDeptAns(char* pReceive, ULONG leng);

// �õ��̶�������
int OnGcInfoAns(char* pReceive, ULONG leng);

// �õ��̶������ң�JSON��
int OnGcInfoAns2(char* pReceive, ULONG leng);

// Ⱥ������,�õ���ϵ���б�
int OnGcGetListAns(char* pReceive, ULONG leng);

// Ⱥ�鷢����Ϣ(�ͻ�������Ϣ��������)����
int OnSendGcMSGAns(char* pReceive, ULONG leng);

// Ⱥ�鷢�ͽ���(������������Ϣ)
int OnRecvGcMSG(char* pReceive, ULONG leng);

// Ⱥ������,����
int OnGcCreateAns(char* pReceive, ULONG leng);

// Ⱥ������,��ӳ�Ա
int OnGcAddAns(char* pReceive, ULONG leng);

// ����ӽ�Ⱥ��
int OnGetS_GCAddAns(char* pReceive, ULONG leng);

// Ⱥ������,����
int OnGcKickAns(char* pReceive, ULONG leng);

// ���߳�Ⱥ��
int OnGetS_GCKickAns(char* pReceive, ULONG leng);

// Ⱥ������,�뿪
int OnGcLeaveAns(char* pReceive, ULONG leng);

// ��ȡ���ں�
int OnGetPublicAns(char* pReceive, ULONG leng);

// ��ȡ���ں���Ϣ
int OnGetPublicInfoAns(char* pReceive, ULONG leng);

// �������������Ŀͷ�������Ϣ
int OnGet_S_Online(char* pReceive, ULONG leng);

// ������Ϣ
int OnGetOffMSg(char* pReceive, ULONG leng);

// ��ص�¼��������Ϣ
int OnKickOffMsg(char* pReceive, ULONG leng);

// �������ر���Ϣ������������Ѿ��رգ��ͻ��˻�ɵɵ������
int OnSvrOffMsg(char* pReceive, ULONG leng);

////ͼƬ����
int On_SendPKG_Ans(char* pReceive, ULONG leng);

// ��������ת���ݰ�
int On_S_SendPKG_Ans(char* pReceive, ULONG leng);

// ���������ͻ���״̬
int On_SendMsgCheck_Ans(char* pReceive, ULONG leng);

// ������ȡ����������Ϣ
int On_GetAllTgRoom_Ans(char* pReceive, ULONG leng);

// ȡ��������Ϣ
int OnGetUserState_Ans(char* pReceive, ULONG leng);

// �ص�¼Э��ķ��ذ�
int OnReconnect_Ans(char* pReceive, ULONG leng);

// im2.0ȡ��������������Ϣ�ķ��ذ�
int On_GetAllTgRoomEx_Ans(char* pReceive, ULONG leng);

// im2.0ȡ�÷��������пͻ���Ϣ�ķ��ذ�
int On_GetUserByRoomID_Ans(char* pReceive, ULONG leng);

// im2.0�汾�з�����Ա�Զ������
int OnGetSelfGroup_Ans(char* pReceive, ULONG leng);

// im2.0ȡ�÷����¶�Ӧ���û��б�
int OnGetSelfGroupUsers_Ans(char* pReceive, ULONG leng);

// im2.0���/�޸��Զ��������Ϣ
int OnSetSelfGroup_Ans(char* pReceive, ULONG leng);

// im2.0���/�޸��û��ķ���
int OnSetSelfGroupUser_Ans(char* pReceive, ULONG leng);