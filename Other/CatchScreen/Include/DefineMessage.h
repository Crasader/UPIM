#ifndef OWN_DEFINEMESSAGE
#define OWN_DEFINEMESSAGE

//����Ϊ�Զ�����Ϣ
//
//֪ͨ��ʾ��ǰѡȡ�Ļ�����ɫ
#define UWM_SHOWPENCOLOR1 (WM_APP+0x900)
#define UWM_SHOWPENCOLOR2 (WM_APP+0x910)

//�����Ի����ж��巢����Ϣ�庯��������֪ͨ��ɫ���Ѹı�
#define UWM_REALIZEPAL    (WM_APP + 0x920)

//�ڿ�ͨ��CCartoon�е�OnMove()��OnSize()������Ϣ��������ͶԻ�������֪ͨˢ�»���
#define UWM_REDRAWCANVAS  (WM_APP + 0x930)

#define WM_OWNDOWNMESSAGE  (WM_APP + 0x940)

// ���������ƶ�ʱ���ʹ���Ϣ����֪ͨ�������е���������
#define WM_CUTCAVASDIBRECT  (WM_APP + 0x950)


//�����鰴Ŧ�������ƶ�����ʱOnMoving������Ϣ֪ͨ���Ի�����´���ͬʱ���»�����ֵ
#define WM_MOVESIZEBTN  (WM_APP + 0x960)

//�ڰ�Ŧ�ϵ������Ҽ�
#define UWM_RBUTTONDOWN  (WM_APP + 0x970)

// ���ڻ�������ʾͼ�εĴ������򻭲ᴰ���෢����Ϣ
#define UWM_GETPREPICTURE  (WM_APP + 0x980)


// �䰵δѡ������
#define WM_DARKUNSELECTEDRECT  (WM_APP + 0x990)

//������Ϣ�����õ�EXE�������壬�������е�ͼ�����ݴ���ȥ
#define WM_SENDIMAGETOEXE  (WM_APP + 0x993)

#define		UM_FEEDBACKMSG	WM_USER+0x987	// �رս�ͼ��Ϣ

#endif   // OWN_DEFINEMESSAGE