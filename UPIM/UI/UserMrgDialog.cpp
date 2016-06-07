#include "stdafx.h"
#include "../Func.h"
#include "../MainPort.h"
#include "UserMrgDialog.h"
#include "RichEditUtil.h"
#include "UserMrgAddGroup.h"




const TCHAR* const kTitleControlName		= _T("general_title");
const TCHAR* const kCloseControlName		= _T("general_closebtn");
const TCHAR* const kBackgroundControlName	= _T("general_bg");
const TCHAR* const kOKButtonControlName		= _T("general_ok");
const TCHAR* const kCloseButtonControlName	= _T("general_close");

/*
 ���������
	ȫ���ͻ� fz_all
		δ����ͻ� fz_0
		�Զ������1 ~ �Զ������10 fz_1~fz_10
*/

CUserMrgDialog::CUserMrgDialog(ECREATEDIALOGTYPE m_CreateType)
	:CreateType(m_CreateType)
{
	m_pMinSysBtn = m_pMaxSysBtn = m_pRestoreSysBtn = m_pCloseSysBtn = m_pUserMrgAddBtn = NULL;
	for (int nIndex = 0; nIndex <= USERMRG_FENZU; nIndex++)
		m_pFenZu[nIndex]  = NULL;
	m_pAllClient = NULL;
	m_pFenZuList = NULL;
	nGroupIndex = 0;
	nChooseGroup = -1;
	m_pGroupList = NULL;
	m_pList = NULL;
	m_pChenkBox = NULL;
	m_pUserMrgDelBtn = NULL;
}

CUserMrgDialog::~CUserMrgDialog()
{
	return;
}

LPCTSTR CUserMrgDialog::GetWindowClassName() const
{
	return _T("UPGuiFoundation");
}

CControlUI* CUserMrgDialog::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

void CUserMrgDialog::InitWindow()
{
	//////////////////////////////////////////////////////////////////////////
	// ����
	m_pMinSysBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("general_minbtn")));
	m_pMaxSysBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("general_maxbtn")));
	m_pRestoreSysBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("general_restorebtn")));
	m_pCloseSysBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("general_closebtn")));
	m_pUserMrgAddBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("usermrg_addbtn")));
	m_pFenZuList = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("usermrg_fenzu")));
	m_pGroupList = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("usermrg_group")));
	m_pList = static_cast<CListUIEx*>(m_PaintManager.FindControl(_T("listex")));
	m_pChenkBox = static_cast<CCheckBoxUI*>(m_PaintManager.FindControl(_T("selall")));
	m_pUserMrgDelBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("usermrg_delbtn")));

	for (int nIndex = 0; nIndex <= USERMRG_FENZU; nIndex++)
	{
		CString strOptionName = "";
		strOptionName.Format("fz_%d", nIndex);
		m_pFenZu[nIndex]  = static_cast<COptionUI*>(m_PaintManager.FindControl(strOptionName));
	}
	m_pAllClient = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("fz_all")));

	//////////////////////////////////////////////////////////////////////////
	// ����ʦ�汾�Ĳ��пͻ��������Լ��ͻ�����
	if (m_pAllClient)
	{
		CString strAllUserNum = "";
		strAllUserNum.Format("ȫ���ͻ�(%d)", m_vtRoomClient.size());
		m_pAllClient->SetText(strAllUserNum);
	}

	//////////////////////////////////////////////////////////////////////////
	// �õ��������洢�ķ�����Ϣ
	// �����б�
	LoadSelfGroup();
	ShowAllClient();
}

void CUserMrgDialog::AddList(CString strUpid, CString strGroupName)
{
	//////////////////////////////////////////////////////////////////////////
	CDialogBuilder builder;
	CListContainerElementUI* pLine = (CListContainerElementUI*)(builder.Create(_T("item_sigle_list_column.xml"),(UINT)0));
	// ����xml�����õ�list�б���ʽ�����ó��Լ���Ҫ��ֵ���ٲ���

	CTextUI * pText_ID = (CTextUI *)pLine->FindSubControl(_T("list_1"));
	CTextUI * pText_Group = (CTextUI *)pLine->FindSubControl(_T("list_2"));
	if (pText_ID && pText_Group)
	{
		pText_ID->SetText(strUpid);
		pText_Group->SetText(strGroupName);

		if( pLine != NULL ) 
			m_pList->InsertItem(m_pList->GetCount(), 30, pLine);
	}
	return;
}

int CUserMrgDialog::AddGroupInfo(CString strGroupName, int nNums)
{
	// m_pFenZu : ��߷����б�ı���  
	// nGroupIndex �����б������ 
	// m_mapGroupIdToControls nGroupIndex �� ���ݿ��з�����еķ���ID�Ķ�Ӧ��ϵ 
	// m_groupInfoStc    ����ʦ���� 
	// m_mapSelfGroups   �Զ������  nGroupIndex �� �������ֵĶ�Ӧ 
	int nReturnID = -1;
	if (nGroupIndex <= USERMRG_FENZU)
	{
		CString strAllUserNum = "";
		strAllUserNum.Format("%s(%d)", strGroupName, nNums);
		int nBtnLen = strAllUserNum.GetLength() * 7;

		m_pFenZu[nGroupIndex]->SetText(strAllUserNum);
		m_pFenZu[nGroupIndex]->SetVisible(true);
		m_pFenZu[nGroupIndex]->SetMinWidth(nBtnLen);
		nReturnID = nGroupIndex;
		//��׼ֵ35��ÿ����ť25����
		int nFixHight = 35 + 25*(nGroupIndex+1);
		m_pFenZuList->SetAttribute("height", IntToStr(nFixHight));

		if (nGroupIndex > 0)
		{
			CListLabelElementUI *pLabel = new CListLabelElementUI;
			pLabel->SetAttribute(_T("text"), strGroupName);
			pLabel->SetAttribute(_T("height"), _T("22"));
			// �����б� 
			m_pGroupList->Add(pLabel);
		}

		nGroupIndex ++;
	}
	else
	{
		::MessageBox(NULL, _T("�Զ���ͻ����鲻�ܳ���10����"), _T("��ʾ"), MB_OK);
	}
	return nReturnID;
}

void CUserMrgDialog::ShowAllClient()
{
	m_pList->RemoveAll();
	for (int nIndex = 0; nIndex< (int)m_vtRoomClient.size(); nIndex++)
	{
		CString strName,strGroup;
		strName.Format("%s", m_vtRoomClient[nIndex].m_szUPID);
		strGroup = m_mapSelfGroups[m_vtRoomClient[nIndex].m_nGroupID];

		AddList(strName, strGroup);
	}
	return;
}

void CUserMrgDialog::OnBtn_AllClient(TNotifyUI& msg)
{
	if (nChooseGroup == -1)
		return;
	nChooseGroup = -1;

	m_pChenkBox->SetCheck(false);
	ShowAllClient();
	return;
}

// ����ȫ���ͻ�����list  ��Ϣ��Ӧ  
void CUserMrgDialog::ChangeFenZu(int nIndex)
{
	if (nChooseGroup == nIndex)
		return;

	// ������ķ���ID  
	nChooseGroup = nIndex;
	
	m_pChenkBox->SetCheck(false);

	m_pList->RemoveAll();
	int nGroupID = m_mapGroupIdToControls[nIndex];
	for (int nIndex = 0; nIndex< (int)m_vtRoomClient.size(); nIndex++)
	{
		if (m_vtRoomClient[nIndex].m_nGroupID == nGroupID)
		{
			// ��������ĺ���  
			CString strName,strGroup;
			strName.Format("%s", m_vtRoomClient[nIndex].m_szUPID);
			strGroup = m_mapSelfGroups[m_vtRoomClient[nIndex].m_nGroupID];

			AddList(strName, strGroup);
		}
	}
	return;
}

void CUserMrgDialog::LoadSelfGroup()
{
	if (IsAllGroupLoad())
	{
		for (int n=0; n<=USERMRG_FENZU; n++)
		{
			if (m_groupInfoStc[n].bLoad == false && m_groupInfoStc[n].bUsed == true && m_groupInfoStc[n].bGetUserInfo == true)
			{
				int nThisGroupNum = GetGroupClientNums(m_groupInfoStc[n].nGroupID);
				int nControlID = AddGroupInfo(m_groupInfoStc[n].GroupName, nThisGroupNum);
				m_mapGroupIdToControls[nControlID] = m_groupInfoStc[n].nGroupID;
				m_groupInfoStc[n].bLoad = true;
			}
		}
	}
	return;
}

void CUserMrgDialog::AddGroup(CString strGroupName ,CString strGroupID )
{
	m_mapSelfGroups.insert(map<int,CString>::value_type(atoi(strGroupID.GetBuffer()),strGroupName)) ;	
	m_groupInfoStc[nGroupIndex].bUsed = 1;
	m_groupInfoStc[nGroupIndex].nGroupID = atoi(strGroupID.GetBuffer());
	m_groupInfoStc[nGroupIndex].GroupName = strGroupName;
	m_groupInfoStc[nGroupIndex].bGetUserInfo = TRUE ; 

	int nThisGroupNum = GetGroupClientNums(m_groupInfoStc[nGroupIndex].nGroupID);
	int nControlID = AddGroupInfo(m_groupInfoStc[nGroupIndex].GroupName, nThisGroupNum);
	m_mapGroupIdToControls[nControlID] = m_groupInfoStc[nGroupIndex-1].nGroupID;
}
void CUserMrgDialog::DelGroup(CString strGroupName ,CString strGroupID ) 
{
	int groupID = atoi(strGroupID.GetBuffer()) ;
	strGroupID.ReleaseBuffer() ; 

	// �� m_mapSelfGroups���ҵ�strGroupID ��ɾ�� 
	std::map<int ,CString>::iterator itBegin,itEnd  ; 
	itBegin  = m_mapSelfGroups.begin() ; 
	while( itBegin !=  m_mapSelfGroups.end() )
	{
		if( itBegin->first == groupID )
		{
			// ɾ������ 
			m_mapSelfGroups.erase(itBegin) ;
			break ; 
		}
		else
			itBegin++ ; 
	}

	// ��m_groupInfoStc ���ҵ�strGroupName ��ɾ�� 
	for (int n=0; n<=USERMRG_FENZU; n++)
	{
		if ( m_groupInfoStc[n].bUsed == true )
		{
			if( m_groupInfoStc[n].nGroupID == groupID )
			{
				m_groupInfoStc[n].bLoad = false ;
				m_groupInfoStc[n].bUsed = false ;
				m_groupInfoStc[n].bGetUserInfo = false ; 
				m_groupInfoStc[n].bCreateNode = false ; 
				m_groupInfoStc[n].GroupName = _T("") ; 
				break ; 
			}
		}
	}
	// ����m_mapGroupIdToControls  ά��GroupID���̨���ݿ���ID֮��Ĺ�ϵ  ҲҪ����
	std::map<int, int>::iterator itMapBegin ,itMapEnd ; 
	itMapBegin =  m_mapGroupIdToControls.begin() ; 
	
	while( itMapBegin !=  m_mapGroupIdToControls.end() )
	{
		if( itMapBegin->second == groupID )
		{
			m_mapGroupIdToControls.erase(itMapBegin) ; 
			break; 
		}
		else
		{
			itMapBegin++ ;
		}
	}

	DelGroupInfo(strGroupName,0) ; 

}
void CUserMrgDialog::DelGroupInfo(CString strGroupName, int nNums) 
{
	// ���������б�
	//CDuiString str = m_pGroupList->GetText() ; 
	m_pGroupList->RemoveAll() ;
	int n = 0; 
	while( n < USERMRG_FENZU)
	{
		if( m_groupInfoStc[n].bUsed )
		{
			CString strGroupName = m_groupInfoStc[n].GroupName ; 
			CListLabelElementUI *pLabel = new CListLabelElementUI;
			pLabel->SetAttribute(_T("text"), strGroupName);
			pLabel->SetAttribute(_T("height"), _T("22"));
			// �����б� 
			m_pGroupList->Add(pLabel);
		}
		n++;
	}
	m_pGroupList->SetText(_T("δ����ͻ�")) ;
}

void CUserMrgDialog::OnCheckBoxSelected()
{
	bool bSelect = m_pChenkBox->GetCheck();
	int nAllClomum = m_pList->GetCount();
	if (bSelect)
	{
		for (int nListIndex = 0; nListIndex < nAllClomum; nListIndex ++)
		{
			CListContainerElementUI* pLine = m_pList->GetListItem(nListIndex);
			if (pLine)
			{
				CCheckBoxUI * pCheckBox = (CCheckBoxUI *)pLine->FindSubControl(_T("selectme"));
				CTextUI * pText_ID = (CTextUI *)pLine->FindSubControl(_T("list_1"));
				CTextUI * pText_Group = (CTextUI *)pLine->FindSubControl(_T("list_2"));
				if (pCheckBox)
				{
					pCheckBox->SetCheck(true);
				}
			}
		}
	}
	else
	{
		for (int nListIndex = 0; nListIndex < nAllClomum; nListIndex ++)
		{
			CListContainerElementUI* pLine = m_pList->GetListItem(nListIndex);
			if (pLine)
			{
				CCheckBoxUI * pCheckBox = (CCheckBoxUI *)pLine->FindSubControl(_T("selectme"));
				CTextUI * pText_ID = (CTextUI *)pLine->FindSubControl(_T("list_1"));
				CTextUI * pText_Group = (CTextUI *)pLine->FindSubControl(_T("list_2"));
				if (pCheckBox)
				{
					pCheckBox->SetCheck(false);
				}
			}
		}
	}
}

void CUserMrgDialog::OnBtn_AddGroup(TNotifyUI& msg)
{
	
	// ����������10  ��ʾ��Ϣ 
	if( nGroupIndex >= 10 )
	{
		::MessageBox(NULL, _T("�Զ���ͻ����鲻�ܳ���10����"), _T("��ʾ"), MB_OK);
		return ;
	}

	CUserMrgAddGroup* pAddGroupDialog = new CUserMrgAddGroup();
	if( pAddGroupDialog == NULL )
		return;

	pAddGroupDialog->Create(m_hWnd, "�����ϵ��", UI_WNDSTYLE_FRAME | WS_POPUP, NULL, 0, 0, 600, 800);
	pAddGroupDialog->CenterWindow();
	pAddGroupDialog->ShowModal();

	
	//////////////////////////////////////////////////////////////////////////
	if (!g_strAddGroupName.IsEmpty())
	{
		//////////////////////////////////////////////////////////////////////////
		WORD iGID = 0 ; // ��ID 
		CString strJson = _T("") ; 
		strJson.Format("{\"type\"\:\"1\" ,\"name\"\:\"\%s\",\"gID\"\:\"%d\"}",g_strAddGroupName,iGID) ; 
		string strAddGroup(strJson.GetBuffer()) ;
		strJson.ReleaseBuffer() ; 
		g_MyClient.SendSetSelfGroupReq(strAddGroup) ;
	}
	return;
}

bool CUserMrgDialog::DeleteFenZuBtn( int btnID ) 
{
	int i = nGroupIndex ; 

	ANALYSTGROUP_INFO temp_groupInfoStc[USERMRG_FENZU+1]; 
	//temp_groupInfoStc = m_groupInfoStc ; 
	for (int n=0; n<=USERMRG_FENZU; n++)
	{
		if (m_groupInfoStc[n].bUsed == true)
		{
			CString name = m_groupInfoStc[n].GroupName ; 

			m_groupInfoStc[n].bLoad = false ;
			m_groupInfoStc[n].bUsed = true ;
			//temp_groupInfoStc[n].GroupName = m_groupInfoStc[n].GroupName ;
			m_groupInfoStc[n].bCreateNode = true ;
			//temp_groupInfoStc[n].nGroupID = m_groupInfoStc[n].nGroupID ;
			
			m_mapGroupIdToControls[n] = m_groupInfoStc[n].nGroupID;
		}
	}
	std::map<int, int>	tempGroupIdToControls = m_mapGroupIdToControls ; 

	m_mapGroupIdToControls.clear() ; 
	//memset(m_groupInfoStc ,0,sizeof(ANALYSTGROUP_INFO)) ; 

	LoadSelfGroup() ; 
	std::map<int,int>::iterator itBegin ,itEnd ; 
	itBegin = m_mapGroupIdToControls.find(btnID) ; 
	itEnd = m_mapGroupIdToControls.end()  ; 
	if( itBegin != itEnd )
	{
		m_mapGroupIdToControls.erase(btnID) ; 

		m_groupInfoStc[btnID].bUsed = 0;
		m_groupInfoStc[btnID].bGetUserInfo = 0;
		return true ; 
	}
	return false ; 
}
// ɾ������ 
void CUserMrgDialog::OnBtn_DelGroup(TNotifyUI& msg)
{
	// ��ȡҪɾ����GroupID��name  
	// (1) GroupID 
	int nDelGroupID = m_mapGroupIdToControls[nChooseGroup]; 
	// (2) 
	
	// δ������� �� ȫ���ͻ� ����ɾ�� 
	if( nDelGroupID == 0 || nDelGroupID == -1 )
		return ; 

	// ��ȡ�����б����� 
	string strName = m_pFenZu[nChooseGroup]->GetText().GetData() ;
	int strlength = strName.length() ; 

	CString strJson = _T("") ; 
	strJson.Format("{\"type\"\:\"0\" ,\"name\"\:\"\%s\",\"gID\"\:\"%d\"}",strName.c_str(),nDelGroupID) ; 
	string strDelGroup(strJson.GetBuffer()) ;
	strJson.ReleaseBuffer() ; 
	if(!strName.empty())
	{
		// ȥ������
		int indexStart = strName.find("(") ;
		int indexEnd   = strName.find(")") ;
		string strNumInName = strName.substr(indexStart+1 ,indexEnd - indexStart-1) ; 
		int nNumInName = atoi(strNumInName.c_str()) ; 
		if( nNumInName == 0 )
		{
			// ֱ��ɾ��btn 
			m_pFenZu[nChooseGroup]->SetVisible(FALSE) ; 
		}
		nGroupIndex = nGroupIndex - 1 ; 
	}

	Reader reader ;
	Value  data_add_value ; 
	Value  data_del_value ; 
	Value  item ; 
	Value  array ; 
	FastWriter writer ; 
	string strdata ;

	// json�� { "groupID":"XXX" ,"nType":"XXX" ,"item":[{"clientID":"XXX"},...,{"clientID":"XXX"}]}
	data_add_value["groupID"] = nDelGroupID ; 
	data_add_value["nType"]   = 0 ; 

	int delNum = 0 ; 
	// ��������������ˣ���ȫ�������Ƶ�δ�������� �����·�����Ϣ���͵������� 
	for (int nIndex = 0; nIndex< (int)m_vtRoomClient.size(); nIndex++)
	{
		if (m_vtRoomClient[nIndex].m_nGroupID == nDelGroupID)
		{
			delNum++ ;
			// ��������ĺ���  
			CString strName,strGroup;
			strName.Format("%s", m_vtRoomClient[nIndex].m_szUPID);
			strGroup = m_mapSelfGroups[m_vtRoomClient[nIndex].m_nGroupID];
			AddList(strName, _T("δ����ͻ�"));
		}
	}
	m_pFenZu[nChooseGroup]->SetVisible(FALSE) ;
	
	// ��ȡδ����ͻ�  ID  
	int nContorlID = ConvertGroupIDToControl(0) ; 
	UpdateListBtnName(nContorlID,delNum,1) ;
	
	//DeleteFenZuBtn(nChooseGroup) ; 
	g_MyClient.SendSetSelfGroupReq(strDelGroup) ;
}

void CUserMrgDialog::OnCbo_SelChange_Group(TNotifyUI& msg)
{
	tstring strText = (TCHAR *)m_pGroupList->GetText().GetData();

	// ��ȡѡ�з����ID 
	int iGroupID = GetGroupIDByName(m_pGroupList->GetText().GetData()) ; 
	
	// nChooseGroup����ߵķ����б��е�ǰѡ�е��б�ID��Ҳ���ǽ�nChooseGroup������ѡ�е��û��ƶ���
	// IGroupIDȥ�����nChooseGroup��IGroupID����ı��ⶼҪ���¡�

	//////////////////////////////////////////////////////////////////////////
	// �����Щ��Ŀ��ѡ�е�
	int nAllClomum = m_pList->GetCount();

	// ѡ����� 
	std::vector<int> chooseItemRemove(nAllClomum,-1) ; 
	int removeCount = 0 ; 

	int nListIndex = 0 ; 

	Reader reader ;
	Value  data_add_value ; 
	Value  data_del_value ; 
	Value  item ; 
	Value  array ; 
	FastWriter writer ; 
	string strdata ; 
	int nIndex = 0 ;

	// Ϊ�˱������������50������ʱ�ͷ���socket�������� 
	int iMaxSendMsgCount = 0 ; 

	for (; nListIndex < nAllClomum; nListIndex ++)
	{
		CListContainerElementUI* pLine = m_pList->GetListItem(nListIndex);
		if (pLine)
		{
			CCheckBoxUI * pCheckBox = (CCheckBoxUI *)pLine->FindSubControl(_T("selectme"));
			CTextUI * pText_ID = (CTextUI *)pLine->FindSubControl(_T("list_1"));
			CTextUI * pText_Group = (CTextUI *)pLine->FindSubControl(_T("list_2"));
			//            Դ ��ID                ��������           �Ƴ��ĳ�Ա 
			//   �������ͣ�
			//   0 ��ʾ ���ͻ���Ա����ID���Ƴ� 
			//   1 ��ʾ ���ͻ���Ա��ӵ���ID��
			// json�� { "groupID":"XXX" ,"nType":"XXX" ,"item":[{"clientID":"XXX"},...,{"clientID":"XXX"}]}
			data_add_value["groupID"] = m_mapGroupIdToControls[nChooseGroup] ; 
			data_add_value["nType"]   = 0 ; 

			data_del_value["groupID"]   = iGroupID ; 
			data_del_value["nType"]   = 1 ;

			if (pCheckBox->GetCheck())
			{
				pText_Group->SetText(strText.c_str()) ; 
				CString strCustomID = pText_ID->GetText() ;  // �ͻ�ID 
				CString strCustomGroupName = pText_Group->GetText() ;  // ������
				// ��m_vtRoomClient�ҵ����û������ҽ�ԭ�����ڵ�list��ɾ������  
				int iSize = m_vtRoomClient.size() ;
				
 
				for( int i = 0 ; i < iSize ; i++)
				{
					if( strcmp(m_vtRoomClient[i].m_szUPID ,strCustomID.GetBuffer()) == 0 )
					{
						m_vtRoomClient[i].m_nGroupID = iGroupID ;

						item["clientID"] = (LPCSTR)(strCustomID) ; 
						array.append(item) ;

						data_add_value["item"] = array ; 
						data_del_value["item"] = array ; 

						iMaxSendMsgCount++;
						// ɾ������
						// (1) �����ȫ���ͻ����棬��ɾ���û������ǽ����������Ϊʵ�ʷ��� 
						if( nGroupIndex == -1)
						{
							pText_ID->SetText(m_pGroupList->GetText()) ;
						}
						// (2) ���� ɾ�������������Ŀͻ�
						else  
						{
							chooseItemRemove.push_back(nListIndex) ;
							removeCount++ ; 
						}

						if( iMaxSendMsgCount >= 50 )
						{
							strdata = writer.write(data_add_value) ; 
							g_MyClient.SendSetSelfGroupUserReq(strdata) ; 

							strdata.clear() ; 
							strdata = writer.write(data_del_value) ;
							g_MyClient.SendSetSelfGroupUserReq(strdata) ; 

							iMaxSendMsgCount = 0 ;
							array.clear() ;

						}

					}
				}
				pCheckBox->SetCheck(false);
			}
			else
			{
				//::MessageBox(NULL, _T("��ѡ��Ҫ�ƶ��Ŀͻ�"), _T("��ʾ"), MB_OK);
				//return ; 
			}
		}
	}

	// ����С��50�������  
	if ( iMaxSendMsgCount > 0 )
	{
		strdata = writer.write(data_add_value) ; 
		g_MyClient.SendSetSelfGroupUserReq(strdata) ; 

		strdata.clear() ; 
		strdata = writer.write(data_del_value) ;
		g_MyClient.SendSetSelfGroupUserReq(strdata) ; 
	}

	if( nGroupIndex != -1)
	{
		// ��δ�������Ƴ�
		RemoveCustomFromGroup(chooseItemRemove,removeCount) ; 
		// ������ID ת��Ϊ �ؼ���ID  
		int nContorlID = ConvertGroupIDToControl(iGroupID) ; 
		
		// ������߶�Ӧ��������ƣ� XXXX(iCustomCount) 
		if( nContorlID != -1 )
			UpdateListBtnName(nContorlID,removeCount,1) ; 
		if( nChooseGroup != -1)
			UpdateListBtnName(nChooseGroup,removeCount,0) ; 
	}
	m_pChenkBox->SetCheck(false);
	return;
}
// nType��ʾ��������ӻ����Ƴ���Ա
// 1 ��ʾ���ӳ�Ա
// 0 ��ʾ�Ƴ���Ա 
void CUserMrgDialog::UpdateListBtnName(int nBtnID,int iCustomCount,int nType)
{
	string strName = m_pFenZu[nBtnID]->GetText().GetData() ;
	int strlength = strName.length() ; 

	if(!strName.empty())
	{
		// ȥ������
		int indexStart = strName.find("(") ;
		int indexEnd   = strName.find(")") ;

		// û�ҵ� 
		if( ( indexEnd == -1 )|| ( indexStart == -1 ))
			return ; 
		
		int iCustomerInFenzu = atoi( (strName.substr(indexStart+1,indexEnd-indexStart-1)).c_str()) ; 
		string name = strName.substr(0,indexStart ) ;
		CString updateName=_T("");
		if( nType == 1 )
		{
			iCustomerInFenzu = iCustomCount + iCustomerInFenzu ; 
		}
		else if (nType == 0 )
		{
			iCustomerInFenzu = iCustomerInFenzu - iCustomCount ;
			if( iCustomerInFenzu < 0 )
				iCustomerInFenzu = 0 ; 
		}
		updateName.Format("%s(%d)",name.c_str(),iCustomerInFenzu) ; 
		m_pFenZu[nBtnID]->SetText(updateName) ; 
	}
}
void  CUserMrgDialog::RemoveCustomFromGroup(std::vector<int> vec ,int len ) 
{
	int iCount = vec.size() ; 

	for( int i = 0 ; i < iCount ;i++)
	{
		if( vec[i] != -1 )
		{
			m_pList->RemoveAt(vec[i]) ;
		}
	}
}

//���ѹ������пͻ������У����ݷ���ID�õ��ؼ�btnID
int  CUserMrgDialog::ConvertGroupIDToControl(int nGroupID) 
{
	int nControlID = 0 ; 
	std::map<int,int>::iterator itBegin ,itEnd ; 

	itBegin = m_mapGroupIdToControls.begin() ;
	itEnd   = m_mapGroupIdToControls.end() ;
	while(itBegin!=itEnd)
	{
		if( (itBegin)->second == nGroupID )
		{
			nControlID = itBegin->first ;
			return nControlID ; 
		}
		itBegin++ ; 
	}
	return nControlID ; 
}

void CUserMrgDialog::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);	
	delete this;
}

CDuiString CUserMrgDialog::GetSkinFile()
{
	return _T("dlg_UserMrg.xml");
}

CDuiString CUserMrgDialog::GetSkinFolder()
{
	return CDuiString(CPaintManagerUI::GetInstancePath()) + _T("skin\\");
}

LRESULT CUserMrgDialog::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	for (int n=0; n<=USERMRG_FENZU; n++)
	{
		m_groupInfoStc[n].bLoad = false;
	}
	return 0;
}

LRESULT CUserMrgDialog::OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT CUserMrgDialog::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	BOOL bZoomed = ::IsZoomed(m_hWnd);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if (::IsZoomed(m_hWnd) != bZoomed)
	{
		if (!bZoomed)
		{
			if (m_pMaxSysBtn != NULL)
				m_pMaxSysBtn->SetVisible(false);
			if (m_pRestoreSysBtn != NULL)
				m_pRestoreSysBtn->SetVisible(true);
		}
		else 
		{
			if (m_pMaxSysBtn != NULL)
				m_pMaxSysBtn->SetVisible(true);
			if (m_pRestoreSysBtn != NULL)
				m_pRestoreSysBtn->SetVisible(false);
		}
	}
	return 0;
}

LRESULT CUserMrgDialog::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// ���α�����˫����Ϣ
	if(WM_NCLBUTTONDBLCLK != uMsg)
		return __super::HandleMessage(uMsg, wParam, lParam);
	return 0;
}

LRESULT CUserMrgDialog::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT CUserMrgDialog::ResponseDefaultKeyEvent(WPARAM wParam)
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

void CUserMrgDialog::OnTimer(TNotifyUI& msg)
{
}

void CUserMrgDialog::OnExit()
{
	Close();
}

void CUserMrgDialog::OnPrepare(TNotifyUI& msg)
{
	TCHAR szBuf[MAX_PATH] = {0};

	if (CreateType == eCreate_TG1 || CreateType == eCreate_TG2)
		return;
}

void CUserMrgDialog::Notify(TNotifyUI& msg)
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
		CControlUI *pOne = static_cast<CControlUI*>(m_PaintManager.FindControl(msg.ptMouse)) ; 
		if (msg.pSender == m_pMinSysBtn)
			OnBtn_Min(msg);
		else if (msg.pSender == m_pMaxSysBtn)
			OnBtn_Max(msg);
		else if (msg.pSender == m_pRestoreSysBtn)
			OnBtn_Restore(msg);
		else if (msg.pSender == m_pCloseSysBtn)
			OnBtn_Close(msg);
		else if (msg.pSender == m_pUserMrgAddBtn)
			OnBtn_AddGroup(msg);
		else if( msg.pSender == m_pUserMrgDelBtn)
			OnBtn_DelGroup(msg) ; 
		else if (msg.pSender == m_pAllClient)
			OnBtn_AllClient(msg);

		for (int nIndex = 0; nIndex<=USERMRG_FENZU; nIndex++)
		{
			// ����Ƿ���
			if (msg.pSender == m_pFenZu[nIndex])
				ChangeFenZu(nIndex);
		}

		if (_tcsicmp(msg.pSender->GetName(), kCloseControlName) == 0)
		{
			OnExit();
		}
		else if (_tcsicmp(msg.pSender->GetName(), kCloseButtonControlName) == 0)
        {
            OnCloseBtnClick(msg);
		}
		else if (_tcsicmp(msg.pSender->GetName(), kOKButtonControlName) == 0)
		{
			OnOKBtnClick(msg);
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
		if (msg.pSender == m_pChenkBox)
		{
			// checkboxѡ��ı�
			OnCheckBoxSelected();
		}
	}
	else if (_tcsicmp(msg.sType, _T("itemselect")) == 0)
	{
		if (msg.pSender == m_pGroupList)
			OnCbo_SelChange_Group(msg);
	}
}

void CUserMrgDialog::OnBtnFenzuList(TNotifyUI& msg, CString strName)
{
	COptionUI* m_btnFenZu = static_cast<COptionUI*>(m_PaintManager.FindControl(strName));
	if( m_btnFenZu)
	{
		g_strDelGroupName = m_btnFenZu->GetText() ;
		// 
	}
}
//��С����ť
void CUserMrgDialog::OnBtn_Min(TNotifyUI& msg)
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
}

//��󻯰�ť
void CUserMrgDialog::OnBtn_Max(TNotifyUI& msg)
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
}

//��ԭ���ڰ�ť
void CUserMrgDialog::OnBtn_Restore(TNotifyUI& msg)
{
	SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
}

//�رմ��ڰ�ť
void CUserMrgDialog::OnBtn_Close(TNotifyUI& msg)
{
	Close();
}

void CUserMrgDialog::OnCloseBtnClick(TNotifyUI& msg)
{
	OnExit();
	return;
}

void CUserMrgDialog::OnOKBtnClick(TNotifyUI& msg)
{
	return;
}
