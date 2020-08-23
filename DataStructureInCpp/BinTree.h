#pragma once
#ifndef _BINTREE_H_
#define _BINTREE_H_
#include "MyStack.h"
#include"BinNode.h"
#include<iostream>
namespace MyBinTree
{
	template<typename T>class  BinTree
	{//������ģ����
	protected:
		int _size;//���Ĺ�ģ
		BinNode<T>* _root;//���ڵ�
		virtual int updateHeight(BinNode<T>* x);//���½ڵ�x�ĸ߶�
		void updateHeightAbove(BinNode<T>* x);//���½ڵ�x�������ȵĸ߶�
	public:
		//���캯��
		BinTree() : _size(0), _root(nullptr) {}
		~BinTree() { if (0 < _size) remove(_root); }
		// �����ӿ�
		int remove(BinNode<T>* x);//ɾ����xΪ���������������ر�ɾ������ԭ�ȵĹ�ģ
		int size()const { return _size; }//���Ĺ�ģ
		bool empty()const { return !_root; }//�п�   _root==nullptr(Ϊfalse),��   !_root����false�� Ϊtrue
		BinNode<T>* root() { return _root; }//����
		BinNode<T>* insertAsRoot(T const& e);//��Ϊ���ڵ����
		BinNode<T>* insertAsLC(BinNode<T>* x, T const& e);//e��Ϊx�����Ӳ���
		BinNode<T>* insertAsRC(BinNode<T>* x, T const& e);//e��Ϊx���Һ��Ӳ���
		BinNode<T>* attachAsLC(BinNode<T>* x, BinTree<T>*& S);//S��Ϊx������������
		BinNode<T>* attachAsRC(BinNode<T>* x, BinTree <T>*& S);//S��Ϊx������������
		BinTree<T>* secede(BinNode<T>* x);//������x�ӵ�ǰ����ժ����������ת��Ϊһ�Ŷ�������
		template<typename VST>
		void travLevel(VST& visit) { if (_root) _root->travLevel(visit); }//��α���
		template<typename VST>
		void travPre(VST& visit) { if (_root) _root->travPre(visit); }//�������
		template<typename VST>
		void travIn(VST& visit) { if (_root) _root->travIn(visit); }//�������
		template<typename VST>
		void travPost(VST& visit) { if (_root) _root->travPost(visit); }//�������

	};//BinTree
	//protected
	int max(int a, int b)
	{
		if (a > b) return a;
		else return b;
	}
	template<typename T>int BinTree<T>::updateHeight(BinNode<T>* x)
	{
		return x->height = 1 + max(stature(x->leftChild), stature(x->rightChild));
	}
	template<typename T>void BinTree<T>::updateHeightAbove(BinNode<T>* x)
	{
		while (x)
		{
			updateHeight(x);
			x = x->parent;
		}//��x���� ������������
	}

	//public
	template<typename T>BinNode<T>* BinTree<T>::insertAsRoot(T const& e)
	{
		_size = 1;
		return _root = new BinNode<T>(e);
	}//e�������ڵ����յĶ�����
	//�ӽڵ�Ĳ���
	template<typename T>BinNode<T>* BinTree<T>::insertAsLC(BinNode<T>* x, T const& e)
	{
		_size++;
		x->insertAsLC(e);
		updateHeightAbove(x);
		return x->leftChild;
	}//��ڵ����
	template<typename T>BinNode<T>* BinTree<T>::insertAsRC(BinNode<T>* x, T const& e)
	{
		_size++;
		x->insertAsRC(e);
		updateHeightAbove(x);
		return x->rightChild;
	}//�ҽڵ����

	// �����Ĳ���
	template<typename T>BinNode<T>* BinTree<T>::attachAsLC(BinNode<T>* x, BinTree<T>*& S)//T��Ϊx������������
	{
		if (x->leftChild = S->_root) x->leftChild->parent = x;//���Ա�������Է���������˽�г�Ա
		_size += S->_size;                   //����BinTree���Ա����attachAsLC�����������S��protected��Ա_size,_root
		updateHeightAbove(x);
		S->_root = nullptr;
		S->_size = 0;
		//release(S);//   release( )  ?
		S = nullptr;
		return x;
	}//����������	
	template<typename T>BinNode<T>* BinTree<T>::attachAsRC(BinNode<T>* x, BinTree <T>*& S)//T��Ϊx������������
	{
		if (x->rightChild = S->_root) x->rightChild->parent = x;
		_size += S->_size;
		updateHeightAbove(x);
		S->_root = nullptr;
		S->_size = 0;
		//release(S);//   release( )  ?
		S = nullptr;
		return x;
	}//����������

	//������ɾ��
	template<typename T>int BinTree<T>::remove(BinNode<T>* x)//ɾ���������У�x�ĵĽڵ㼰�����������ر�ɾ���Ľڵ���
	{
		FromParentTo(*x) = nullptr;
		updateHeightAbove(x->parent);
		int n = removeAt(x);
		_size -= n;
		return n;
	}
	template<typename T>static int removeAt(BinNode<T>* x)
	{
		if (!x) return 0;//����
		int n = 1 + removeAt(x->leftChild) + removeAt(x->rightChild);
		delete x;
		x = nullptr;
		return n;
	}
	template<typename T>BinTree<T>* BinTree<T>::secede(BinNode<T>* x)
	{
		FromParentTo(*x) = nullptr;
		updateHeightAbove(x->parent);
		BinTree<T>* S = new BinTree<T>;
		S->_root = x;
		x->parent = nullptr;
		S->_size = x->size();
		_size -= S->_size;
		return S;
	}//��������
	//


}//MyBinTree
#endif // !_BINTREE_H_

