#pragma once
extern BOOL InitReqBufHead(IMREQBUFFER& m_reqbuf, long PacketLen, long RawLen);
extern WORD	GetBuildNo( LPSTR lpszDateTime, const WORD wSize );					// ��ȡ�������к�
extern bool CreateGUID(char * guid);											// ����һ��ȫ��Ψһ��ʶ
extern CString MakeGuid(char* strguid = NULL);									// ����һ��ȫ��Ψһ��ʶ���ַ���
extern void ConvertTimeToLong(time_t tmTime, long& nRetDate, long& nRetTime);
extern LPSTR SafeStrcpy( LPSTR lpszDest, LPCSTR lpcszSrc, const WORD wDestSize );
// date 20190204 
// time 11:10:10��ʾ��һ��ʱ��� 
void ConvertTimeToLong2(int date ,int time ,long& nRetTime) ;      // �����ں�ʱ��ת��Ϊʱ��� 

extern void LoginSuc_Ex();														// �û���¼�ɹ�֮�����
extern VOID LoadUserConfig();													// �����û������ļ�
extern VOID SaveUserConfig();													// �����û������ļ�
extern VOID LoadConfig();														// ����ϵͳ�����ļ�
extern VOID InitSQLITE();

extern UINT PlaySoundThread(void* l);											// ��������
extern void WriteUserLog(const char *fmt, ...);									// ��־
extern void WriteUserLog_Ex(const char *fmt, ...);								// ��־
extern bool TestFileExist(CString filename);									// �ļ���·���Ƿ����
extern CString IntToStr(int nVal);												// 10λ�ַ����ڵ�intתstring

//MD5����
extern void MD5StringTo32(char *p, char *pRet/*32*/);
extern int InsertVtUser(vector<GUSER_INFO> &mvt, GUSER_INFO m_info);
extern int DeleteVtUser(vector<GUSER_INFO> &mvt, GUSER_INFO m_info);

extern	CString	UTF8Convert(CString &str, int sourceCodepage, int targetCodepage);
extern	bool GetNextMsg(FriendList_ITER iterator, RECEIVED_MSG *msg);
extern	bool GetNextMsg_More(vector<RECEIVED_MSG> *pMsg, RECEIVED_MSG *msg);

extern CString ConvertIdToNoPhonrNum(CString strID);
extern void UpdateVtClientInfo(CString strUPID, int nGroupID);
extern void UpdateGroupFlag(int nGroupID);
extern void SetGroupFlag(int nGroupID ,bool falg) ;
extern BOOL IsAllGroupLoad();
extern int GetGroupClientNums(int nGroupID ); 
extern int GetRoomClientOnlineNums() ;  // ��ȡ����ʦ����ĳ������ͻ��������� 
extern int GetGroupClientOnlineNums(int nGroupID) ;  // ��ȡ���������������� 

extern int GetGroupIDByName(CString strGroupName);
extern int GetNowTimeHourAndMin();
extern CString ConvertMsgToChiefMsg(BYTE format, LPCSTR lpMsg);
extern CString ConvertMsgContent(LPCSTR lpMsg);
extern BOOL IsInvtRoomClient(CString strUserID);

//�������API ����������������ַ����� ���ַ���������Ϊԭʼ�Ķ�������
//�������������ݷ���pResultBuf,ע��nMaxResultBufLen�ĳ�������ӦΪnRawDataLen��2������
//bEncodeΪTRUE,��ʾ�˺������ڱ���,�������ڽ���
//�����������ʧ��,����-1,�ɹ��򷵻ر��������ĳ���
extern long Base64_Encode(BYTE *pRawData, long nRawDataLen, BYTE *pResultBuf, long nMaxResultBufLen, BOOL bEncode);

extern CClientPackage * CreatePackage(unsigned short protocol);

// ͼƬ�ĻҶȴ����������ߵ��û�����ͷ��һ�
extern BOOL CreateGrayPngFromColorPng(LPCTSTR lpColorPath, LPCTSTR lpGrayImagePath);
extern int CaculateAshValue(int & nR, int & nG, int & nB);
extern bool GetEncoderClsid(const WCHAR* pszFormat, CLSID* pClsid);
// �ߴ�ѹ��
extern bool CompressImagePixel(const WCHAR* pszOriFilePath, const WCHAR* pszDestFilePah, UINT ulNewHeigth, UINT ulNewWidth, WCHAR* pszFormat = L"image/jpeg");
// ����ѹ��
extern bool CompressImageQuality(const WCHAR* pszOriFilePath, const WCHAR* pszDestFilePah, ULONG quality);
// ��ȡͼ����Ϣ
extern bool HandleImage(LPCTSTR lpOriFilePath, LPCTSTR lpDestFilePah);
// ��͸����ͼ
extern void SetPictureAlpha(LPCTSTR lpOriFilePath, LPCTSTR FileName1, float f_a);
// ��ȡͼ����Ϣ
extern bool HandleHeadImage(LPCTSTR lpOriFilePath, LPCTSTR FileName1, LPCTSTR FileName2 );
// ����ͼ����Ϣ
extern bool HandleHeadImage2(LPCTSTR lpOriFilePath, LPCTSTR FileName1, LPCTSTR FileName2 );

extern bool HandleHeadImage3(LPCTSTR lpOriFilePath, LPCTSTR FileName1, LPCTSTR FileName2 ) ;

extern BOOL GDIPlus_CombineImage(const WCHAR *format, WCHAR* strDestImage,	WCHAR* strSrcImage1,WCHAR* strSrcImage2);

extern CString HrToMessage( HRESULT hr );
// ����Ȩ���б��Ƿ����
extern BOOL IsHasRights(int nRight);

// ��ȡ��ǰʱ��   
extern void GetCurrentDate(CString &year ,CString &month ,CString &day) ; 

extern BOOL SortByName(const ROOMANALYS_INFO &data1,const ROOMANALYS_INFO &data2) ; 

extern BOOL SortByNameAndOnline(const ROOMANALYS_INFO &data1,const ROOMANALYS_INFO &data2) ;

// ����ʦ�����ڿͻ����� 
extern BOOL SortByNameAndOnlineClient(const USER_ROOMCLIENT_INFO &data1,const USER_ROOMCLIENT_INFO &data2) ;

// ����ʦ�� ���ݽڵ��ID���ҽڵ� 
extern USER_ROOMCLIENT_INFO* FindClientInRoom(CString strName) ; 

// �ͻ���  �ҵ������ΪnRoomID�ķ���ʦ ���ط���ʦ�ڵ������  
extern void FindAnalysInRoom(int nRoomID ,ALLCLIENT_ROOM_INFO &retClientRoom) ;

// ���ͻ���¼��֪ͨ����ʦ�����ߣ���Ҫ����m_vtRoomClient���ÿͻ�����״̬  
extern void SetClientOnLine(CString strClientName ,bool bUserState) ; 

// ��mapRoomAnalys��Ѱ��strAnalysName�ķ���ʦ����ID 
extern int  WhitchRoomForAnalys( std::map<TGROOMID ,ALLCLIENT_ROOM_INFO> mapRoomAnalys ,CString strAnalysName) ; 

// wuchao add at 2016-03-29 
// ��ȡ�����������ߺ������û���Ϣ 
extern void GetClientInfoInGroup(Node*pGroupNode,std::vector<USER_ROOMCLIENT_INFO> &vecOnline ,std::vector<USER_ROOMCLIENT_INFO> &vecOffline ) ; 


extern int astr_ustr( const char *ansistr, WCHAR *unicodestr ) ; 

extern std::string _EncodeURL(  char *str) ; 