#pragma once
#ifndef _MYLIST_H_
#define _MYLIST_H_
namespace MyList
{
	typedef int Rank;
	template<typename T>struct ListNode
	{
		//���ԣ���Ա��
		T data; ListNode<T>* pred; ListNode<T>* succ;//����  ǰ��  ���
		//���캯��
		ListNode() {};// header trailer �Ĺ���
		ListNode(T e, ListNode<T>* p = nullptr, ListNode<T>* s = nullptr) :data(e), pred(p), succ(s) {};
		//�����ӿ�
		ListNode<T>* insertAsPred(T const& e);
		ListNode<T>* insertAsSucc(T const& e);
	};//struct ListNode δ��װ����
	//�����ӿ� ʵ��
	template<typename T>ListNode<T>* ListNode<T>::insertAsPred(T const& e)
	{
		ListNode<T>* newnode = new ListNode(e, pred, this);//newnode��ǰ��ָ��this->pred;  newnode�ĺ��ָ��this
		pred->succ = newnode; pred = newnode;//this->pred->succָ��newnode;  this->predָ��newnode
		return newnode;//���ز���Ľڵ�
	}//insertAsPred
	template<typename T>ListNode<T>* ListNode<T>::insertAsSucc(T const& e)
	{
		ListNode<T>* newnode = new ListNode(e, this, succ);//newnode��ǰ��ָ��this;  newnode�ĺ��ָ��succ
		succ->pred = newnode; succ = newnode;//this->succ->predָ��newnode;  this->succָ��newnode
		return newnode;//���ز���Ľڵ�
	}//insertAsSucc

	template<typename T>class List
	{
	private:
		int _size; ListNode<T>* header; ListNode<T>* trailer;//��ģ  ͷ�ڵ�  β�ڵ�
	protected:
		void init();//�б��ʼ��
		int clear();//����������ݽڵ�  ������ͷ�ڵ� β�ڵ�
		void copyNodes(ListNode<T>* p, int n);//����list�� ��p���n��
	public:
		//���캯��
		List() { init(); }//Ĭ�Ϲ��캯��
		List(List<T> const& L);//���帴��
		List(ListNode<T>* p, int n) { copyNodes(p, n); }//����list�� ��p���n��
		List(List<T> const& L, Rank r, int n) { copyNodes(L.goToRankr(r), n); }//����list�� ��r�����n��
		//��������
		~List() { clear(); delete header; delete trailer; };//�ͷ����нڵ�  ��ɾ�����ݽڵ� ��ɾ�� ͷ β
		//ֻ�����ʽӿ�
		Rank size()const { return _size; }//��ģ
		bool empty()const { return _size <= 0; }//�п�
		T& operator[](Rank r)const;//���� [] ��Ч�ʽϵ�
		ListNode<T>* goToRankr(Rank r) const;//������Ϊr�Ľڵ�
		ListNode<T>* first()const { return header->succ; }
		ListNode<T>* last()const { return trailer->pred; }
		//��д���ʽӿ�
		ListNode<T>* insertAsFirst(T const& e) { _size++; return header->insertAsSucc(e); }//��e��Ϊlist���׽ڵ����
		ListNode<T>* insertAsLast(T const& e) { _size++; return trailer->insertAsPred(e); }//��e��Ϊlist��ĩ�ڵ����
		ListNode<T>* insertA(ListNode<T>* p, T const& e) { _size++; return p->insertAsSucc(e); }//��e��Ϊp�ĺ�̲���
		ListNode<T>* insertB(ListNode<T>* p, T const& e) { _size++; return p->insertAsSucc(e); }//��e��Ϊp��ǰ������
		T remove(ListNode<T>* p);//ɾ��p�ڵ㣬������p�ڵ�����Ӧ������
	};//List
	//protected ��Ա����ʵ��
	template<typename T>void List<T>::init()
	{
		header = new ListNode<T>;
		trailer = new ListNode<T>;
		header->succ = trailer; header->pred = nullptr;
		trailer->pred = header; trailer->succ = nullptr;
		_size = 0;
	}//list ��ʼ��
	template<typename T>int List<T>::clear()
	{
		int Oldsize = _size;
		while (_size > 0)
		{
			remove(trailer->pred);
		}
		return Oldsize;
	}// �������
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
	//pubilc ��Ա����
	//���캯��
	template<typename T>List<T>::List(List<T> const& L)
	{
		copyNodes(L.first(), L.size());
	}//���帴��

	// ֻ�����ʽӿ�
	template<typename T>T& List<T>::operator[](Rank r)const
	{
		ListNode<T>* p = header->succ;
		while (0 < r--)
		{
			p = p->succ;
		}
		return p->data;
	}// ����[] ʵ���±�����  r��ΧΪ[0,size)

	template<typename T>ListNode<T>* List<T>::goToRankr(Rank r) const
	{
		ListNode<T>* p = header->succ;
		while (0 < r--)
		{
			p = p->succ;
		}
		return p;
	}
	//��д���ʽӿ�
	template<typename T>T List<T>::remove(ListNode<T>* p)
	{
		T data = p->data;
		p->pred->succ = p->succ;
		p->succ->pred = p->pred;
		delete p;
		_size--;
		return data;
	}// ɾ��p�ڵ� ������p->data
}//MyList
#endif // !_MYLIST_H_

