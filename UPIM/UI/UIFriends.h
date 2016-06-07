#ifndef UIFRIENDS_HPP
#define UIFRIENDS_HPP

#include "UIListCommonDefine.h"

namespace DuiLib
{

class CRecordCallBack:public IListCallbackUI
{
public:
	CRecordCallBack() ; 
	~CRecordCallBack() ;
	LPCTSTR GetItemText(CControlUI* pList, int iItem, int iSubItem) ; 
	std::vector<USER_ROOMCLIENT_INFO> GetClientRoom() ;
	void SetClientRoom(std::vector<USER_ROOMCLIENT_INFO> vec) ; 
	void SortClientRoom() ; 
private:
	 std::vector<USER_ROOMCLIENT_INFO>	m_ClientRoom ;  // ����Ľṹ�� 
};
class CFriendsUI : public CListUI
{
public:
	enum {SCROLL_TIMERID = 10};

	CFriendsUI(CPaintManagerUI& paint_manager);
	~CFriendsUI();

	bool Add(CControlUI* pControl);
	bool AddAt(CControlUI* pControl, int iIndex);
	bool Remove(CControlUI* pControl);
	bool RemoveAt(int iIndex);
	void RemoveAll();
	void DoEvent(TEventUI& event);
	Node* GetRoot();
	Node* AddNode(const FriendListItemInfo& item, Node* parent  ,int itemHeight );  // ������ʾ��Ϣ�� ר��  CMsgNotifyDialog�� 
	Node* AddNode(const FriendListItemInfo& item, Node* parent = NULL);
	void AddNode(FriendListItemInfo  item , Node *child ,Node* parent ) ;
	bool RemoveNode(Node* node);
	void SetChildVisible(Node* node, bool visible);
	bool CanExpand(Node* node) const;
	bool SelectItem(int iIndex, bool bTakeFocus = false);
	Node* SelectNodeByID(CString strUserID);
	bool SetNickNameType(int nType);
	void SetNodeFlash(Node* node, bool nFlash, int nDeirction = 0);
	void SetNodeState(Node* node, int nstate);
	void SetNodeName(Node* node ,int onlineNums = 0,int totalNums = 0 ) ;  // ���÷���ڵ���ʾ������������������ XX/XX 
	bool RemoveNodeMapInfo(Node* node);
	void SetNodeLastWord(Node* node, CString strLastWord, int nTime);
	void SetNodeNums(Node* node, int nTotleNum, int nOnlineNum);
	void SetNodePic(Node* node, CString HeadImg);
	Node* GetNodeItem(CDuiString strID ) ; 
	bool SortList(Node *pNode) ; 
	bool SortList() ;
	static int CALLBACK MyCompareProc(UINT_PTR lParam1, UINT_PTR lParam2, UINT_PTR lParamSort ) ; 

private:
	Node*	root_node_;

	LONG	delay_deltaY_;
	DWORD	delay_number_;
	DWORD	delay_left_;
	CDuiRect	text_padding_;
	int level_text_start_pos_;
	CDuiString level_expand_image_;
	CDuiString level_collapse_image_;
	CPaintManagerUI& paint_manager_;

    CDialogBuilder m_dlgBuilder;
public:
	std::map<CString, Node*> allNodeInfo;			//��NODEָ��洢�������Ա����item��Id�����ҽڵ�
	typedef map<CString, Node*>::iterator NODE_ITER;
};
	static bool CompareWithOnlineAndName(CListContainerElementUI * item1,CListContainerElementUI * item2) ;

} // DuiLib

#endif // UIFRIENDS_HPP