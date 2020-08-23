#pragma once
#ifndef _MYLIST_H_
#define _MYLIST_H_
namespace MyList
{
	typedef int Rank;
	template<typename T>struct ListNode
	{
		//属性（成员）
		T data; ListNode<T>* pred; ListNode<T>* succ;//数据  前驱  后继
		//构造函数
		ListNode() {};// header trailer 的构造
		ListNode(T e, ListNode<T>* p = nullptr, ListNode<T>* s = nullptr) :data(e), pred(p), succ(s) {};
		//操作接口
		ListNode<T>* insertAsPred(T const& e);
		ListNode<T>* insertAsSucc(T const& e);
	};//struct ListNode 未封装数据
	//操作接口 实现
	template<typename T>ListNode<T>* ListNode<T>::insertAsPred(T const& e)
	{
		ListNode<T>* newnode = new ListNode(e, pred, this);//newnode的前驱指向this->pred;  newnode的后继指向this
		pred->succ = newnode; pred = newnode;//this->pred->succ指向newnode;  this->pred指向newnode
		return newnode;//返回插入的节点
	}//insertAsPred
	template<typename T>ListNode<T>* ListNode<T>::insertAsSucc(T const& e)
	{
		ListNode<T>* newnode = new ListNode(e, this, succ);//newnode的前驱指向this;  newnode的后继指向succ
		succ->pred = newnode; succ = newnode;//this->succ->pred指向newnode;  this->succ指向newnode
		return newnode;//返回插入的节点
	}//insertAsSucc

	template<typename T>class List
	{
	private:
		int _size; ListNode<T>* header; ListNode<T>* trailer;//规模  头节点  尾节点
	protected:
		void init();//列表初始化
		int clear();//清楚所有数据节点  不包括头节点 尾节点
		void copyNodes(ListNode<T>* p, int n);//复制list中 自p起的n项
	public:
		//构造函数
		List() { init(); }//默认构造函数
		List(List<T> const& L);//整体复制
		List(ListNode<T>* p, int n) { copyNodes(p, n); }//复制list中 自p起的n项
		List(List<T> const& L, Rank r, int n) { copyNodes(L.goToRankr(r), n); }//复制list中 第r项起的n项
		//析构函数
		~List() { clear(); delete header; delete trailer; };//释放所有节点  先删除数据节点 再删除 头 尾
		//只读访问接口
		Rank size()const { return _size; }//规模
		bool empty()const { return _size <= 0; }//判空
		T& operator[](Rank r)const;//重载 [] 但效率较低
		ListNode<T>* goToRankr(Rank r) const;//返回秩为r的节点
		ListNode<T>* first()const { return header->succ; }
		ListNode<T>* last()const { return trailer->pred; }
		//可写访问接口
		ListNode<T>* insertAsFirst(T const& e) { _size++; return header->insertAsSucc(e); }//将e作为list的首节点插入
		ListNode<T>* insertAsLast(T const& e) { _size++; return trailer->insertAsPred(e); }//将e作为list的末节点插入
		ListNode<T>* insertA(ListNode<T>* p, T const& e) { _size++; return p->insertAsSucc(e); }//将e作为p的后继插入
		ListNode<T>* insertB(ListNode<T>* p, T const& e) { _size++; return p->insertAsSucc(e); }//将e作为p的前驱插入
		T remove(ListNode<T>* p);//删除p节点，并返回p节点所对应的数据
	};//List
	//protected 成员函数实现
	template<typename T>void List<T>::init()
	{
		header = new ListNode<T>;
		trailer = new ListNode<T>;
		header->succ = trailer; header->pred = nullptr;
		trailer->pred = header; trailer->succ = nullptr;
		_size = 0;
	}//list 初始化
	template<typename T>int List<T>::clear()
	{
		int Oldsize = _size;
		while (_size > 0)
		{
			remove(trailer->pred);
		}
		return Oldsize;
	}// 数据清除
	template<typename T>void List<T>::copyNodes(ListNode<T>* p, int n)
	{
		init();
		ListNode<T>* q = header;
		while (0 < n--)
		{
			q = q->insertAsSucc(p->data);
			p = p->succ;
			_size++;
		}
	}
	//pubilc 成员函数
	//构造函数
	template<typename T>List<T>::List(List<T> const& L)
	{
		copyNodes(L.first(), L.size());
	}//整体复制

	// 只读访问接口
	template<typename T>T& List<T>::operator[](Rank r)const
	{
		ListNode<T>* p = header->succ;
		while (0 < r--)
		{
			p = p->succ;
		}
		return p->data;
	}// 重载[] 实现下标索引  r范围为[0,size)

	template<typename T>ListNode<T>* List<T>::goToRankr(Rank r) const
	{
		ListNode<T>* p = header->succ;
		while (0 < r--)
		{
			p = p->succ;
		}
		return p;
	}
	//可写访问接口
	template<typename T>T List<T>::remove(ListNode<T>* p)
	{
		T data = p->data;
		p->pred->succ = p->succ;
		p->succ->pred = p->pred;
		delete p;
		_size--;
		return data;
	}// 删除p节点 并返回p->data
}//MyList
#endif // !_MYLIST_H_

