#pragma once
#ifndef _BINTREE_H_
#define _BINTREE_H_
#include "MyStack.h"
#include"BinNode.h"
#include<iostream>
namespace MyBinTree
{
	template<typename T>class  BinTree
	{//二叉树模板类
	protected:
		int _size;//树的规模
		BinNode<T>* _root;//根节点
		virtual int updateHeight(BinNode<T>* x);//更新节点x的高度
		void updateHeightAbove(BinNode<T>* x);//更新节点x及其祖先的高度
	public:
		//构造函数
		BinTree() : _size(0), _root(nullptr) {}
		~BinTree() { if (0 < _size) remove(_root); }
		// 操作接口
		int remove(BinNode<T>* x);//删除以x为根的子树，并返回被删除子树原先的规模
		int size()const { return _size; }//树的规模
		bool empty()const { return !_root; }//判空   _root==nullptr(为false),则   !_root（！false） 为true
		BinNode<T>* root() { return _root; }//树根
		BinNode<T>* insertAsRoot(T const& e);//作为根节点插入
		BinNode<T>* insertAsLC(BinNode<T>* x, T const& e);//e作为x的左孩子插入
		BinNode<T>* insertAsRC(BinNode<T>* x, T const& e);//e作为x的右孩子插入
		BinNode<T>* attachAsLC(BinNode<T>* x, BinTree<T>*& S);//S作为x的左子树接入
		BinNode<T>* attachAsRC(BinNode<T>* x, BinTree <T>*& S);//S作为x的右子树接入
		BinTree<T>* secede(BinNode<T>* x);//将子树x从当前树中摘除，并将其转化为一颗独立子树
		template<typename VST>
		void travLevel(VST& visit) { if (_root) _root->travLevel(visit); }//层次遍历
		template<typename VST>
		void travPre(VST& visit) { if (_root) _root->travPre(visit); }//先序遍历
		template<typename VST>
		void travIn(VST& visit) { if (_root) _root->travIn(visit); }//中序遍历
		template<typename VST>
		void travPost(VST& visit) { if (_root) _root->travPost(visit); }//后序遍历

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
		}//从x出发 覆盖历代祖先
	}

	//public
	template<typename T>BinNode<T>* BinTree<T>::insertAsRoot(T const& e)
	{
		_size = 1;
		return _root = new BinNode<T>(e);
	}//e当作根节点插入空的二叉树
	//子节点的插入
	template<typename T>BinNode<T>* BinTree<T>::insertAsLC(BinNode<T>* x, T const& e)
	{
		_size++;
		x->insertAsLC(e);
		updateHeightAbove(x);
		return x->leftChild;
	}//左节点插入
	template<typename T>BinNode<T>* BinTree<T>::insertAsRC(BinNode<T>* x, T const& e)
	{
		_size++;
		x->insertAsRC(e);
		updateHeightAbove(x);
		return x->rightChild;
	}//右节点插入

	// 子树的插入
	template<typename T>BinNode<T>* BinTree<T>::attachAsLC(BinNode<T>* x, BinTree<T>*& S)//T作为x的左子树接入
	{
		if (x->leftChild = S->_root) x->leftChild->parent = x;//类成员函数可以访问类对象的私有成员
		_size += S->_size;                   //这里BinTree类成员函数attachAsLC访问了其对象S的protected成员_size,_root
		updateHeightAbove(x);
		S->_root = nullptr;
		S->_size = 0;
		//release(S);//   release( )  ?
		S = nullptr;
		return x;
	}//左子树插入	
	template<typename T>BinNode<T>* BinTree<T>::attachAsRC(BinNode<T>* x, BinTree <T>*& S)//T作为x的右子树接入
	{
		if (x->rightChild = S->_root) x->rightChild->parent = x;
		_size += S->_size;
		updateHeightAbove(x);
		S->_root = nullptr;
		S->_size = 0;
		//release(S);//   release( )  ?
		S = nullptr;
		return x;
	}//右子树插入

	//子树的删除
	template<typename T>int BinTree<T>::remove(BinNode<T>* x)//删除二叉树中，x的的节点及其后代，并返回被删除的节点数
	{
		FromParentTo(*x) = nullptr;
		updateHeightAbove(x->parent);
		int n = removeAt(x);
		_size -= n;
		return n;
	}
	template<typename T>static int removeAt(BinNode<T>* x)
	{
		if (!x) return 0;//空树
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
	}//子树分离
	//


}//MyBinTree
#endif // !_BINTREE_H_

