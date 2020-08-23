#pragma once
#ifndef _BINNODE_H_
#define _BINNODE_H_
#include "MyStack.h"
#include"MyQueue.h"
#include<iostream>
/* BinNode状态与性质的判断 */
#define stature(p) ((p)?(p)->height:-1)//宏定义会无视namespace 整个*.h文件均可见 stature(p) ((p)?(p)->height:-1)
#define IsRoot(x) (!((x).parent))// 判断x是否为根节点  x的父节点为 nullptr ，则x为 root
#define IsLChild(x) (!IsRoot(x) &&(&(x)==(x).parent->leftChild)) //判断x 是否是树的一个左节点
#define IsRChild(x) (!IsRoot(x) &&(&(x)==(x).parent->rightChild)) //判断x 是否是树的一个右节点
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).leftChild)
#define HasRChild(x) ((x).rightChild)
#define HasChild(x) (HasLChild(x)||HasRChild(x))//至少拥有一个孩子
#define HasBothChild(x) (HasLChild(x)&&HasRChild(x))//同时拥有两个孩子
#define IsLeaf(x) (! HasChild(x))
	/* 与BinNode 具有特定关系的节点及指针*/
#define sibling(p) /*兄弟*/( IsLChild(*(p)) ? (p)->parent->rightChild:(p)->parent->leftChild)
#define uncle(x) /*叔叔*/( IsLChild(*((x)->parent) ? (x)->parent->parent->rightChild:(p)->parent->parent->leftChild)
#define FromParentTo(x)/* 来自父亲的引用*/( IsRoot(x) ? _root :(IsLChild(x)?(x).parent->leftChild:(x).parent->rightChild))

namespace MyBinTree
{
	typedef enum { RB_RED, RB_BLACK } RBColor;//节点颜色
	template<typename T> struct BinNode
	{
		T data;
		BinNode<T>* parent;     //父节点
		BinNode<T>* leftChild;  //左孩子
		BinNode<T>* rightChild; //右孩子
		int height;//高度
		int npl;//Null Path Length 左式堆
		RBColor color;//红黑树 颜色
		//构造函数
		BinNode() :
			parent(nullptr), leftChild(nullptr), rightChild(nullptr), height(0), npl(0), color(RB_RED) {}
		BinNode(T e, BinNode<T>* p = nullptr, BinNode<T>* lc = nullptr, BinNode<T>* rc = nullptr, int h = 0, int l = 1, RBColor c = RB_RED) :
			data(e), parent(p), leftChild(lc), rightChild(rc), height(h), npl(l), color(c) {}
		//操作接口
		int size();//当前节点的后代总数，或称 以当前节点为根的子树规模
		BinNode<T>* insertAsLC(T const&);//左孩子插入
		BinNode<T>* insertAsRC(T const&);//右孩子插入
		BinNode<T>* succ();              //返回当前节点的直接后继  （中序遍历）
		template<typename VST> void travLevel(VST& visit);//子树层次遍历
		template<typename VST> void travPre(VST& visit);//子树先序遍历
		template<typename VST> void travIn(VST& visit);//子树中序遍历
		template<typename VST> void travPost(VST& visit);//子树后序遍历
	};//BinNode
	//操作接口
	template<typename T> BinNode<T>* BinNode<T>::insertAsLC(T const& e)
	{
		return leftChild = new BinNode(e, this);
	}//左孩子插入
	template<typename T> BinNode<T>* BinNode<T>::insertAsRC(T const& e)
	{
		return rightChild = new BinNode(e, this);
	}//右孩子插入
	template<typename T> BinNode<T>* BinNode<T>::succ()
	{
		BinNode<T>* s = this;
		if (rightChild)
		{
			s = rightChild;
			while (HasLChild(*s)) s = s->leftChild;
		}
		else
		{
			while (IsRChild(*s)) s = s->parent;//右孩子需要返回父亲的父亲，即while 先返回父亲，退出while再返回父亲的父亲
			s = s->parent;
		}
		return s;
	}
	template<typename T> int BinNode<T>::size()
	{
		int s = 1;//计入本身
		if (leftChild) s += leftChild->size();
		if (rightChild) s += rightChild->size();
		return s;
	}// size() 规模
	// 子树的遍历
	template<typename T>
	class VST
	{
	public:
		void operator() (T data)
		{
			std::cout << "data is:" << data << std::endl;
		}
	};// 遍历    VST 函数对象 
	template<typename T, typename VST>void travPre_R(BinNode<T>* x, VST& visit)
	{
		if (!x) return;
		visit(x->data);
		travPre_R(x->leftChild, visit);
		travPre_R(x->rightChild, visit);
	}//先序递归
	template<typename T, typename VST>void travPost_R(BinNode<T>* x, VST& visit)
	{
		if (!x) return;
		travPost_R(x->leftChild, visit);
		travPost_R(x->rightChild, visit);
		visit(x->data);
	}//后序递归
	template<typename T, typename VST>void travIn_R(BinNode<T>* x, VST& visit)
	{
		if (!x) return;
		travIn_R(x->leftChild, visit);
		visit(x->data);
		travIn_R(x->rightChild, visit);
	}//中序递归
	using ListStack::Liststack;
	template<typename T, typename VST> void travPre_I1(BinNode<T>* x, VST& visit)
	{
		Liststack< BinNode<T>* > S;
		if (x) S.push(x);
		while (!S.empty())
		{
			x = S.pop(); visit(x->data);
			if (HasRChild(*x)) S.push(x->rightChild);
			if (HasLChild(*x)) S.push(x->leftChild);
		}
	}// 先序迭代版本1

	template<typename T, typename VST>
	static void visitAlongLeftBranch(BinNode<T>* x, VST& visit, Liststack<BinNode<T>* >& S)
	{
		while (x)
		{
			visit(x->data);//访问当前节点
			S.push(x->rightChild);//将当前节点的右孩子（其实是右子树）压入公共栈 S（从上往下压入）
			x = x->leftChild;//将访问权交给x的左孩子 直到左孩子为 nullptr
		}
	}
	template<typename T, typename VST>
	void travPre_I2(BinNode<T>* x, VST& visit)
	{
		Liststack<BinNode<T>* > S;
		while (true)
		{
			visitAlongLeftBranch(x, visit, S);//访问根及其左子树的左孩子（左侧链），压入根的右子树
			if (S.empty()) break;
			x = S.pop();//（从下往上取出）
		}
	}//先序迭代版本2

	template<typename T>
	static void goAlongLeftBranch(BinNode<T>* x, Liststack<BinNode<T>* >& S)
	{// 根节点 及其左孩子 从上往下依次 入栈
		while (x)
		{
			S.push(x);
			x = x->leftChild;
		}
	}
	template<typename T, typename VST>
	void travIn_I1(BinNode<T>* x, VST& visit)
	{
		Liststack<BinNode<T>* > S;
		while (true)
		{
			goAlongLeftBranch(x, S);
			if (S.empty()) break;
			x = S.pop();
			visit(x->data);
			x = x->rightChild;
		}
	}// 中序迭代版本1
	template<typename T, typename VST>
	void travIn_I2(BinNode<T>* x, VST& visit)
	{
		Liststack<BinNode<T>* > S;
		while (true)
		{
			if (x)
			{
				S.push(x);
				x = x->leftChild;
			}
			else if (!S.empty())
			{
				x = S.pop();
				visit(x->data);
				x = x->rightChild;
			}
			else break;
		}
	}// 中序迭代版本2
	template<typename T, typename VST>
	void travIn_I3(BinNode<T>* x, VST& visit)
	{
		bool backtrack = false;
		while (true)
		{
			if (!backtrack && HasLChild(*x)) x = x->leftChild;
			else
			{
				visit(x->data);
				if (HasRChild(*x))
				{
					x = x->rightChild;
					backtrack = false;
				}
				else
				{
					if (!(x = x->succ())) break;
					backtrack = true;
				}
			}
		}
	}// 中序迭代版本3

	template<typename T>
	static void gotoHLVFL(Liststack<BinNode<T>* >& S)
	{
		while (BinNode<T>* x = S.top())
		{
			if (HasLChild(*x))
			{
				if (HasRChild(*x)) S.push(x->rightChild);
				S.push(x->leftChild);
			}
			else S.push(x->rightChild);
		}
		S.pop();
	}
	template<typename T, typename VST>
	void travPost_I(BinNode<T>* x, VST& visit)
	{
		Liststack<BinNode<T>* > S;
		if (x) S.push(x);
		while (!S.empty())
		{
			if (S.top() != x->parent)
			{
				gotoHLVFL(S);
			}
			x = S.pop();
			visit(x->data);
		}
	}//后序遍历迭代版
	using ListQueue::Listqueue;
	template<typename T>
	template<typename VST> void BinNode<T>::travLevel(VST& visit)
	{
		Listqueue<BinNode<T>* > Q;
		Q.enqueue(this);
		while (!Q.empty())
		{
			BinNode<T>* x = Q.dequeue();
			visit(x->data);
			if (HasLChild(*x)) Q.enqueue(x->leftChild);
			if (HasRChild(*x)) Q.enqueue(x->rightChild);
		}
	}//层次遍历
	template<typename T>
	template<typename VST> void BinNode<T>::travPre(VST& visit)
	{
		switch (rand() % 3 )
		{
		case 1:travPre_I1(this, visit); break;
		case 2:travPre_I2(this, visit); break;
		default:travPre_R(this, visit); break;
		}
	}//先序遍历
	template<typename T>
	template<typename VST> void BinNode<T>::travIn(VST& visit)
	{
		switch (rand() % 4)
		{
		case 1:travIn_I1(this, visit); break;
		case 2:travIn_I2(this, visit); break;
		case 3:travIn_I3(this, visit); break;
		default:travIn_R(this, visit); break;
		}
	}//中序遍历
	template<typename T>
	template<typename VST> void BinNode<T>::travPost(VST& visit)
	{
		switch (rand() % 2)
		{
		case 1:travPost_I(this, visit); break;
		default:travPost_R(this, visit); break;
		}
	}//后序遍历


};//MyBinTree
#endif // !_BINNODE_H_


