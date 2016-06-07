#pragma once
#include "GenericHTTPClient.h"

struct FXSData{ 
	CString AnalystId;     // ����ʦ���
	CString AnalystName;   // ����ʦ����
	BOOL operator==(const FXSData &other ) const
	{
		if(AnalystId.Compare(other.AnalystId)) return FALSE;
		else return TRUE;
	}
};

struct FXSDataEx{ 
	CString AnalystId;     // ����ʦ���
	CString AnalystName;   // ����ʦ����
	CString AnalystImg;    // ����ʦͷ��
	CString SpecialtyArea; // �ó�����
	BOOL operator==(const FXSDataEx &other ) const
	{
		if(AnalystId.Compare(other.AnalystId)) return FALSE;
		else return TRUE;
	}
};
struct FXSHouseInfo{
	CString RoomId;        // ������
	CString RoomName;      // ��������
	CString Description;   // ������
	CString ImageAddr;
	BOOL operator==(const FXSHouseInfo &other ) const
	{
		if(RoomId.Compare(other.RoomId)) return FALSE;
		else return TRUE;
	}
};

struct FXSVipHouseInfo{
	CString RoomId;        // ������
	CString RoomName;      // ��������
	CString Description;   // ������
	CString Img;
	CString Notice;
	CString VipType;
	short   IconState;
// 	FXSVipHouseInfo()
// 	{
// 		RoomId = "";
// 		RoomName = "";
// 		Description = "";
// 		Img = "";
// 		Notice = "";
// 		VipType = "";
// 	}
	BOOL operator==(const FXSVipHouseInfo &other ) const
	{
		if(RoomId.Compare(other.RoomId)) return FALSE;
		else return TRUE;
	}
};  

struct RoomAllFxsData{
	vector<FXSDataEx> FxsData;
	FXSVipHouseInfo   VipHouse;
};

typedef map<CString,vector<FXSHouseInfo>> MapFxsToHouseInfo;
typedef vector<FXSHouseInfo>              VHouseInfo;
typedef map<CString,RoomAllFxsData> MapRoomIDToFxsInfo;
typedef map<int,vector<FXSVipHouseInfo>> MapMarketToVipHouseinfo;
typedef map<int,vector<CString>> MapRoomIDToUser;
class CFXSHDManage
{
public:
	CFXSHDManage(void);
	~CFXSHDManage(void);
	
public:
	enum{
		FXSINFO,
		FXS_HOUSEINFO,
		FXS_TO_HOUSEINFO,
		ROOM_TO_FXSINFO,
		FXS_VIP_HOUSEINFO,
		ROOMRIGHT_TO_USER
	};
	int  ParseJson(CString strJson,int type,FXSHouseInfo* pFxsHouseInfo = NULL,int nMarket = 0);
	int  ParseJsonEx(CString strJson,int type,FXSVipHouseInfo* pFxsHouseInfo = NULL,int nMarket = 0);
	
	void DeleteFxsToHousInfo();
	BOOL Request(LPCTSTR szURL, LPCTSTR* aresponse,int type,void* pFxsHouseInfo = NULL,int nMarket = 0,
		int nMethod = GenericHTTPClient::RequestGetMethod, LPCTSTR szAgent = __DEFAULT_AGENT_NAME);
	
	LONG UpdateFxsDB();

	CString GetUserByRoomRight();
	CString URLEncode(const char* sIn);
	unsigned char ToHex(unsigned char x);

	MapFxsToHouseInfo*  GetFxsToHouseInfo();
	VHouseInfo*         GetHouseInfo();
	MapRoomIDToFxsInfo* GetRoomIDToFxsDataEx();
	MapMarketToVipHouseinfo* GetVipHouseInfo();
	MapRoomIDToUser* GetRoomUser();
protected:
	//����ʦ����
	CString             m_strFXSJson; 
	vector<FXSData>     m_vFXSData;
	CCriSec				m_csFreeItem;
	//����ʦ������Ϣ
	CString                   m_strHouseJson;
	VHouseInfo                m_vFXSHouse;
	MapFxsToHouseInfo         m_mapFxsToHouseInfo;
	MapRoomIDToFxsInfo        m_mapRoomIDToFxsInfo;
	MapMarketToVipHouseinfo   m_mapVipHouseInfo;	
	MapRoomIDToUser			  m_mapRoomIDUser;
public:
	GenericHTTPClient   m_httpRep;
		
};

