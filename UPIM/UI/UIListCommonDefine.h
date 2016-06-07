#ifndef UILISTCOMMONDEFINE_HPP
#define UILISTCOMMONDEFINE_HPP

#include <math.h>

namespace DuiLib
{
	struct FriendListItemInfo
	{
		bool folder;					// �Ƿ����ļ���
		bool empty;						// �Ƿ�Ϊ��
		CDuiString id;					// id,���ܻ�����Զ����ʶ��GROUP$001����DEPT$002
		CDuiString numid;				// ��ID,ֻ�����û�ID
		CDuiString Parentid;			// ��ID
		CDuiString logo;				// ͼ��
		CDuiString nick_name;			// �ǳ�
		CDuiString showname;			// ���б�����ʾ������,������id/name/name(id)
		CDuiString description;			// ǩ��
		CDuiString groupnote;			// Ⱥ����

		int type;						// EUSERTYPE,�����û��ľ������ͣ������ϵ�˵�ʱ����EADDIDTYPE(�Ƿ��Ѿ�ΪȺ��Ա)
		int	roomtype;					// Ⱥ����
		int rusertype;					// Ⱥ���û�����,�����û���(�ͻ�/������Ա)
		int nodetype;					// �ڵ�����,����Ϣ�����������ֽڵ�(����/Ⱥ��)
		int nstate;						// �û�����״̬
		bool bRefreshUserPic;			// �Ƿ�ˢ������,��¼�ɹ���ֻˢ��һ��

		CDuiString Lastword;			// ��������¼
		CDuiString GoodAt;				// �ó�Ʒ��
		int	lastwordtime;				// ��������¼ʱ��
		bool isvip;						// �Ƿ���vip
		bool hasright;					// �Ƿ�ͨȨ��
		int totlenum;					// ������
		int onlinenum;					// ��������

		std::vector<RECEIVED_MSG> *pMsg;// ��Ϣ����
		FriendListItemInfo()
		{
			folder = false;
			empty = false;
			id = _T("");
			numid = _T("");
			Parentid = _T("");
			logo = _T("");
			nick_name = _T("");
			showname = _T("");
			description = _T("");
			groupnote = _T("");

			type = 0;
			roomtype = 0;
			rusertype = 0;
			nodetype = 0;
			nstate = 0;
			bRefreshUserPic = false;

			Lastword = _T("");
			lastwordtime = 0;
			isvip = false;
			totlenum = 0;
			onlinenum = 0;

			pMsg = NULL;
		}
		// numid ��Ψһ��  ֻҪnumidһ��  ��ô����Ϊ������ͬ 
		BOOL operator==(const FriendListItemInfo &other ) const
		{
			if( numid != other.numid )
				return false ; 
			else 
				return true ; 
		}
	};
	typedef vector<FriendListItemInfo>::iterator FriendList_ITER;

	struct NodeData
	{
		int level_;
		bool folder_;
		bool child_visible_;
		bool has_child_;
		CDuiString text_;
		CDuiString value;
		CDuiString id;
		CDuiString numid;				// ��ID,ֻ�����û�ID
		CDuiString Parentid;			// ��ID
		CDuiString nickname;

		// IM2.0
		CDuiString Lastword;			// ��������¼
		CDuiString GoodAt;				// �ó�Ʒ��
		int	lastwordtime;				// ��������¼ʱ��
		bool isvip;						// �Ƿ���vip
		bool hasright;					// �Ƿ�ͨȨ��
		int totlenum;					// ������
		int onlinenum;					// ��������

		int type;						// EUSERTYPE
		int rusertype;
		int nodetype;
		CListContainerElementUI* list_elment_;


		NodeData& operator=(NodeData nodeData_)
		{
			if( list_elment_)
			{
				delete list_elment_ ; 
				list_elment_ = NULL ;
			}
			if( this != &nodeData_)
			{
				this->level_=nodeData_.level_;
				this->folder_=nodeData_.folder_;
				this->child_visible_=nodeData_.child_visible_;
				this->has_child_=nodeData_.has_child_;
				this->text_=nodeData_.text_;
				this->value=nodeData_.value;
				this->id=nodeData_.id;
				this->numid=nodeData_.numid;				// ��ID,ֻ�����û�ID
				this->Parentid=nodeData_.Parentid;			// ��ID
				this->nickname=nodeData_.nickname;

				// IM2.0	// IM2.0
				this->Lastword=nodeData_.Lastword;			// ��������¼
				this->GoodAt=nodeData_.GoodAt;				// �ó�Ʒ��
				this->lastwordtime=nodeData_.lastwordtime;				// ��������¼ʱ��
				this->isvip=nodeData_.isvip;						// �Ƿ���vip
				this->hasright=nodeData_.hasright;					// �Ƿ�ͨȨ��
				this->totlenum=nodeData_.totlenum;					// ������
				this->onlinenum=nodeData_.onlinenum;					// ��������

				this->type=nodeData_.type;						// EUSERTYPE
				this->rusertype=nodeData_.rusertype;
				this->nodetype=nodeData_.nodetype;

				this->list_elment_ = nodeData_.list_elment_ ;  
			}
			return *this ; 
		}
	};

	double CalculateDelay(double state);

	class Node
	{
	public:
		Node();
		explicit Node(NodeData t);
		Node(NodeData t, Node* parent);
		~Node();
		NodeData& data();
		int num_children() const;
		Node* child(int i);
		Node* parent();
		bool folder() const;
		bool has_children() const;
		void add_child(Node* child);
		void remove_child(Node* child);
		Node* get_last_child();
		void SortChildren() ; 
		std::vector<Node*> GetChildList() ;
		void SetChildList(std::vector<Node*> vecChildList) ;
		Node& operator=( Node &node) ; 
	private:
		void set_parent(Node* parent);

	private:
		typedef std::vector<Node*>	Children;
		Children	children_;
		Node*		parent_;
		NodeData    data_;
	};
	int SortByName(Node*pData1 ,Node* pData2 ) ; 
} // DuiLib

#endif // UILISTCOMMONDEFINE_HPP