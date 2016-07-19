#include "stdafx.h"
#include "../Func.h"
#include "../MainPort.h"
#include "MsgNotifyDialog.h"
#include "RichEditUtil.h"
#include <algorithm> 
using namespace  std ;
const TCHAR* const kSetControlName		= _T("general_set");
const TCHAR* const kCloseControlName		= _T("general_closebtn");
const TCHAR* const kBackgroundControlName	= _T("general_bg");
const TCHAR* const kOKButtonControlName		= _T("general_ok");
const TCHAR* const kCloseButtonControlName	= _T("general_close");
const TCHAR* const KClientNameControlName   = _T("msgnotify_name") ;

const TCHAR* const KUserNameControlName     = _T("msgnotify_name") ; 
const TCHAR* const kFriendsListControlName  = _T("msgnotify_friends"); 
const TCHAR* const kIgnoreAllMsgControlName = _T("msgnotify_hlsy");    // �鿴ȫ����Ϣ  
const TCHAR* const kOpenAllMsgControlName   =  _T("msgnotify_cksy");   // ����������Ϣ 


CMsgNotifyDialog::CMsgNotifyDialog(ECREATEDIALOGTYPE m_CreateType)
	:CreateType(m_CreateType)
{
	m_pMinSysBtn = m_pMaxSysBtn = m_pRestoreSysBtn = m_pCloseSysBtn = NULL;
	m_pCloseBtn = m_pOKBtn = NULL;
	m_pSetBtn = NULL ; 
	m_pLabelClientName = NULL ; 
	m_pFriendList = NULL ;
}

CMsgNotifyDialog::~CMsgNotifyDialog()
{
	return;
}

LPCTSTR CMsgNotifyDialog::GetWindowClassName() const
{
	return _T("UPGuiFoundation");
}

CControlUI* CMsgNotifyDialog::CreateControl(LPCTSTR pstrClass)
{
	if (_tcsicmp(pstrClass, _T("MessageList")) == 0)
	{
		return new CFriendsUI(m_PaintManager);
	}

	return NULL;
}

void CMsgNotifyDialog::InitWindow()
{
	//////////////////////////////////////////////////////////////////////////
	// ����
	//m_pOKBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(kOKButtonControlName));
	m_pSetBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(kSetControlName));
	
	// title �Լ������� 
	m_pLabelUsername = static_cast<CLabelUI*>(m_PaintManager.FindControl(KClientNameControlName)) ; 
	m_pFriendList      = static_cast<CFriendsUI*>(m_PaintManager.FindControl(_T("msgnotify_friends")));
	m_pOpenAllMsgBtn   = static_cast<CButtonUI*>(m_PaintManager.FindControl(kOpenAllMsgControlName)) ;
	m_pIgnoreAllMsgBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(kIgnoreAllMsgControlName)) ;

}

void CMsgNotifyDialog::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);	
	delete this;
}

CDuiString CMsgNotifyDialog::GetSkinFile()
{
	return _T("dlg_MsgNotify.xml");
}

CDuiString CMsgNotifyDialog::GetSkinFolder()
{
	return CDuiString(CPaintManagerUI::GetInstancePath()) + _T("skin\\");
}

LRESULT CMsgNotifyDialog::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT CMsgNotifyDialog::OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT CMsgNotifyDialog::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	BOOL bZoomed = ::IsZoomed(m_hWnd);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	return 0;
}

LRESULT CMsgNotifyDialog::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// ���α�����˫����Ϣ
	if(WM_NCLBUTTONDBLCLK != uMsg)
		return __super::HandleMessage(uMsg, wParam, lParam);
	return 0;
}

LRESULT CMsgNotifyDialog::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{
			g_pFrame->m_isEnterLeave= TRUE ; 
			g_pFrame->KillMyTimer() ; 
		}
		break ; 
	case WM_MOUSELEAVE:
		{
			g_pFrame->m_isEnterLeave = FALSE ; 
			g_pFrame->AddMyTimer() ;
		}
		break ; 
	}
	return 0;
}

LRESULT CMsgNotifyDialog::ResponseDefaultKeyEvent(WPARAM wParam)
{
	if (wParam == VK_RETURN)
	{
		return FALSE;
	}
	else if (wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	return FALSE;
}

void CMsgNotifyDialog::OnTimer(TNotifyUI& msg)
{
}

void CMsgNotifyDialog::OnExit()
{
	Close();
}

void CMsgNotifyDialog::OnPrepare(TNotifyUI& msg)
{
	TCHAR szBuf[MAX_PATH] = {0};

	if (CreateType == eCreate_TG1 || CreateType == eCreate_TG2)
		return;
}

void CMsgNotifyDialog::Notify(TNotifyUI& msg)
{
	if (_tcsicmp(msg.sType, _T("windowinit")) == 0)
	{
		OnPrepare(msg);
	}
	else if (_tcsicmp(msg.sType, _T("killfocus")) == 0)
	{

	}
	else if (_tcsicmp(msg.sType, _T("click")) == 0)
	{
		if(_tcsicmp(msg.pSender->GetName(), kOpenAllMsgControlName) == 0)
		{
			OnOpenAllMsgBtnClick(msg) ; 
		}
		else if(_tcsicmp(msg.pSender->GetName(), kIgnoreAllMsgControlName) == 0)
		{
			OnIgnoreAllMsgBtnClick(msg) ; 
		}
	}
    else if( _tcsicmp(msg.sType, _T("return")) == 0 ) 
    {
    }
	else if (_tcsicmp(msg.sType, _T("timer")) == 0)
	{
		return OnTimer(msg);
	}
	else if (_tcsicmp(msg.sType, _T("selectchanged")) == 0)
	{
	}
	else if (_tcsicmp(msg.sType, _T("itemselect")) == 0)
	{
	}
	else if (_tcsicmp(msg.sType, _T("itemclick")) == 0)
	{
		OnListItemClick(msg);
	}

}

void CMsgNotifyDialog::OnCloseBtnClick(TNotifyUI& msg)
{
	OnExit();
	return;
}


// ����ȫ����Ϣ    
void CMsgNotifyDialog::OnIgnoreAllMsgBtnClick(TNotifyUI& msg)
{
	// 1 ֹͣ�����б��е�ͷ������
	std::vector<FriendListItemInfo>::iterator itBegin = m_vecFriend.begin() ; 
	while( itBegin != m_vecFriend.end() )
	{
		CDuiString strName = itBegin->id ; 
		g_pFrame->StopFlashItem(strName ,ePanel_Single) ;  
		itBegin++ ; 
	}
	// 2 �ر���Ϣ��ʾ�� 
	this->ShowWindow(false) ;
	// 3 ������Ϣ��ʾ��  

	g_pFrame->StopNotifyiconFlash() ;
	itBegin = m_vecFriend.begin() ; 
	while( itBegin != m_vecFriend.end() )
	{
		CDuiString strNumID = itBegin->numid ;
		g_pFrame->DeleteFriend(strNumID) ; 
		itBegin++ ; 
	}
	m_vecFriend.clear() ; 

}

// �鿴������Ϣ 
void CMsgNotifyDialog::OnOpenAllMsgBtnClick(TNotifyUI& msg)
{
	// �����еĺ�������Ի���  
	std::vector<FriendListItemInfo>::iterator itBegin = m_vecFriend.begin() ; 
	while( itBegin != m_vecFriend.end() )
	{
		CDuiString strName = itBegin->id ; 
		g_pFrame->OpenChatDiolog(strName ,itBegin) ;
		itBegin++;
	}
	// �ر���Ϣ��ʾ�� 
	this->ShowWindow(false) ;
	// ֹ֪ͨͣ��������  
	g_pFrame->StopNotifyiconFlash() ;

	itBegin = m_vecFriend.begin() ; 
	while( itBegin != m_vecFriend.end() )
	{
		CDuiString strNumID = itBegin->numid ;
		g_pFrame->DeleteFriend(strNumID) ; 
		itBegin++ ; 
	}
	m_vecFriend.clear() ; 

}

void CMsgNotifyDialog::OnOKBtnClick(TNotifyUI& msg)
{
	return;
}

void CMsgNotifyDialog::UpdateClientName( CDuiString strClientName ) 
{
	//if( m_pLabelClientName )
	//{
	//	m_pLabelClientName->SetText(strClientName) ; 
	//}
}

void CMsgNotifyDialog::UpdateUserName(CDuiString strUserName)
{
	if( m_pLabelUsername)
	{
		m_pLabelUsername->SetText(strUserName) ;
	}
}
///////////////////////////////////////////////////////////////////////
//��m_vecFriend�б���ɾ��һ������ 
///////////////////////////////////////////////////////////////////////
void CMsgNotifyDialog::DeleteFriend(CDuiString strName) 
{
	std::vector<FriendListItemInfo>::iterator itBegin = m_vecFriend.begin() ; 
	while( itBegin != m_vecFriend.end())
	{
		if( itBegin->numid == strName )
		{
			itBegin = m_vecFriend.erase(itBegin) ; 
		}
		else
			itBegin++ ; 
	}

	std::vector<FriendListItemInfo>::iterator itBeginFriend = friends_.begin() ; 
	while( itBeginFriend != friends_.end())
	{
		if( itBeginFriend->numid == strName )
		{
			itBeginFriend = friends_.erase(itBeginFriend) ; 
		}
		else
			itBeginFriend++ ; 
	}
}
///////////////////////////////////////////////////////////////////////
//��m_vecFriend�б������һ������ 
///////////////////////////////////////////////////////////////////////
void CMsgNotifyDialog::AddFriend(FriendListItemInfo friendInfo)
{
	std::vector<FriendListItemInfo>::iterator itBegin  = m_vecFriend.begin(); 
	bool isAdd = TRUE ; 
	while( itBegin != m_vecFriend.end())
	{
		if( friendInfo.numid == itBegin->numid)
		{
			itBegin->Lastword = friendInfo.Lastword ; 
			isAdd = FALSE ; 
			break ; 
		}
		itBegin++ ; 
	}
	if( isAdd)
		m_vecFriend.push_back(friendInfo) ; 
}

///////////////////////////////////////////////////////////////////////
// ��CMsgNotifyDialog �����в�������Ϣ�ĺ��ѣ���ֹһ������ 
///////////////////////////////////////////////////////////////////////
void CMsgNotifyDialog::InsertFrindToList()
{
	const int nItemHeight = 50 ; 
	if( !m_pFriendList )
		return ; 
	Node* retrunptr = NULL;
	FriendListItemInfo friendInfo ; 
	int iSize = m_vecFriend.size() ;

	std::vector<FriendListItemInfo>::iterator itBegin = m_vecFriend.begin() ; 
	m_pFriendList->RemoveAll() ; 

	while( itBegin != m_vecFriend.end())
	{
		friendInfo = *itBegin ; 
		retrunptr = m_pFriendList->AddNode( friendInfo ,NULL,nItemHeight) ;
		if(retrunptr)
		{
			m_pFriendList->SetChildVisible(retrunptr,true) ; 

			BOOL isInsertNode = TRUE ; 
			std::vector<FriendListItemInfo>::iterator itBeginFriend  = friends_.begin();
			while( itBeginFriend != friends_.end())
			{
				if( itBeginFriend->numid == friendInfo.numid)
				{
					itBeginFriend->Lastword = friendInfo.Lastword ; 
					isInsertNode = FALSE ; 
				}
				itBeginFriend++ ;
			}
			if(isInsertNode)
				friends_.push_back(friendInfo) ;
		}
		itBegin++ ; 
	}

#if 0 
	if( iSize)
	{
		// ȥ���һ��  ���� 
		friendInfo = m_vecFriend.at( iSize - 1 ) ;
		retrunptr = m_pFriendList->AddNode( friendInfo ,NULL,nItemHeight) ;
		if(retrunptr)
		{
			m_pFriendList->SetChildVisible(retrunptr,true) ; 
			
			BOOL isInsertNode = TRUE ; 
			std::vector<FriendListItemInfo>::iterator itBegin  = friends_.begin();
			while( itBegin != friends_.end())
			{
				if( itBegin->numid == friendInfo.numid)
				{
					itBegin->Lastword = friendInfo.Lastword ; 
					isInsertNode = FALSE ; 
				}
				itBegin++ ;
			}
			if(isInsertNode)
				friends_.push_back(friendInfo) ;
		}
	}
#endif 
}
///////////////////////////////////////////////////////////////////////
//����б�������ú������� 
///////////////////////////////////////////////////////////////////////
void CMsgNotifyDialog::OnListItemClick(TNotifyUI& msg)
{
	// ��ȡ������Ϣ 
	if( _tcsicmp(msg.pSender->GetClass() ,_T("ListContainerElementUI") ) == 0  )
	{
		Node* pNode = (Node*)(msg.pSender->GetTag()) ; 
		CDuiString strName =  pNode->data().id ; 
		
		// ��Node�ڵ��m_pFriendList�б���ɾ�� 
		Node* pSelectNode = m_pFriendList->SelectNodeByID(strName.GetData()); 
		if( !pSelectNode)
			return ; 
		CDuiString strNumID = pNode->data().numid ; 
// 		DeleteFriend(strNumID) ; 
// 		g_pFrame->DeleteFriend(strNumID) ; 
		//�����Լ����� 
		this->ShowWindow(false) ; 
		
		//m_vecFriend
		std::vector<FriendListItemInfo>::iterator itBegin = m_vecFriend.begin() ; 
		while( itBegin != m_vecFriend.end())
		{
			if( itBegin->numid == pNode->data().numid )
			{
				break; 
			}
			itBegin++ ; 
		}
		// �������ڴ򿪶Ի��� 
		g_pFrame->OpenChatDiolog(strName ,itBegin) ;
		m_pFriendList->RemoveNode(pSelectNode) ; 
		// ����ͼ��ֹͣ���� 
		if( m_vecFriend.size() == 0 )
			g_pFrame->StopNotifyiconFlash() ; 
		DeleteFriend(strNumID) ; 
		g_pFrame->DeleteFriend(strNumID) ; 

	}
 
}