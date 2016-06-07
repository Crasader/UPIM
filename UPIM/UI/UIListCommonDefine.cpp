#include "stdafx.h"
#include "UIListCommonDefine.h"

namespace DuiLib
{

	double CalculateDelay(double state)
	{
		return pow(state, 2);
	}

	void Node::set_parent(Node* parent)
	{
		parent_ = parent;
	}

	///////////////////////////////////////////////////////////////////////
	//��Ϊ�ײ�Ľڵ�  �����߱�������  ��Ϊ�ڵ㱾��û���Ƿ����߱�־λ��
	//�ϲ���ͨ��m_vtRoomClient�еĽڵ㰴�����ߺ�������ά����Ȼ����ÿ��FriendUIList
	//���в���ڵ�  ��һ�ν���ʵ���ǰ���һ����̬˳����в��룬����ʱ�Ѿ�����
	//���� ���²��������ʱ�� ����Ҫ�ο��ڵ���m_vtRoomClient�е�λ�� 
	// wuchao add at 2016-03-29 
	///////////////////////////////////////////////////////////////////////
	void Node::SortChildren() 
	{
		//sort(children_.begin() ,children_.end() ,SortByName) ; 
	}

	/////////////////////////////////////////////////////////////////////////
	//wuchao add at 2016-03-29
	// ��ȡ���ڵ�ĺ��ӽڵ��б�
	/////////////////////////////////////////////////////////////////////////
	std::vector<Node*> Node::GetChildList()
	{
		return children_ ;
	}
	/////////////////////////////////////////////////////////////////////////
	//wuchao add at 2016-03-29
	// ���ú��ӽڵ�  
	/////////////////////////////////////////////////////////////////////////
	void Node::SetChildList(std::vector<Node*> vecChildList) 
	{
		for (int i = 0; i < num_children(); ++i)
		{
			children_[i] = vecChildList[i]; 
		}
		//children_ = vecChildList ; 
	}
	////////////////////////////////////////////////////////////////////////
	//wuchao add at 2016-03-29 
	////////////////////////////////////////////////////////////////////////
	//Node& Node::operator=( Node &node_)
	//{
	//	if( this != &node_ )
	//	{
	//		this->parent_   = node_.parent() ; 
	//		this->children_ = (*(node_.GetChildList())) ; 
	//		this->data_     = node_.data() ; 
	//	}
	//	return (*this) ; 
	//}
	Node::Node()
		: parent_(NULL)
	{}

	Node::Node(NodeData t)
		: data_(t)
		, parent_(NULL)
	{}

	Node::Node(NodeData t, Node* parent)
		: data_ (t)
		, parent_ (parent)
	{}

	Node::~Node() 
	{
		for (int i = 0; i < num_children(); ++i)
			delete children_[i]; 
	}

	NodeData& Node::data()
	{
		return data_;
	}

	int Node::num_children() const
	{
		return static_cast<int>(children_.size());
	}

	Node* Node::child(int i)
	{
		return children_[i];
	}

	Node* Node::parent()
	{
		return ( parent_);
	}

	bool Node::has_children() const
	{
		return num_children() > 0;
	}

	bool Node::folder() const
	{
		return data_.folder_;
	}

	void Node::add_child(Node* child)
	{
		child->set_parent(this); 
		children_.push_back(child); 
	}


	void Node::remove_child(Node* child)
	{
		Children::iterator iter = children_.begin();
		for (; iter < children_.end(); ++iter)
		{
			if (*iter == child) 
			{
				children_.erase(iter);
				return;
			}
		}
	}

	Node* Node::get_last_child()
	{
		if (has_children())
		{
			return child(num_children() - 1)->get_last_child();
		}
		return this;
	}


	int SortByName(Node*pData1 ,Node* pData2 ) 
	{
		return strcmp( pData1->data().nickname ,pData2->data().nickname) < 0  ; 
	}

}