#pragma once
#ifndef _BINNODE_H_
#define _BINNODE_H_
#include "MyStack.h"
#include"MyQueue.h"
#include<iostream>
/* BinNode״̬�����ʵ��ж� */
#define stature(p) ((p)?(p)->height:-1)//�궨�������namespace ����*.h�ļ����ɼ� stature(p) ((p)?(p)->height:-1)
#define IsRoot(x) (!((x).parent))// �ж�x�Ƿ�Ϊ���ڵ�  x�ĸ��ڵ�Ϊ nullptr ����xΪ root
#define IsLChild(x) (!IsRoot(x) &&(&(x)==(x).parent->leftChild)) //�ж�x �Ƿ�������һ����ڵ�
#define IsRChild(x) (!IsRoot(x) &&(&(x)==(x).parent->rightChild)) //�ж�x �Ƿ�������һ���ҽڵ�
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).leftChild)
#define HasRChild(x) ((x).rightChild)
#define HasChild(x) (HasLChild(x)||HasRChild(x))//����ӵ��һ������
#define HasBothChild(x) (HasLChild(x)&&HasRChild(x))//ͬʱӵ����������
#define IsLeaf(x) (! HasChild(x))
	/* ��BinNode �����ض���ϵ�Ľڵ㼰ָ��*/
#define sibling(p) /*�ֵ�*/( IsLChild(*(p)) ? (p)->parent->rightChild:(p)->parent->leftChild)
#define uncle(x) /*����*/( IsLChild(*((x)->parent) ? (x)->parent->parent->rightChild:(p)->parent->parent->leftChild)
#define FromParentTo(x)/* ���Ը��׵�����*/( IsRoot(x) ? _root :(IsLChild(x)?(x).parent->leftChild:(x).parent->rightChild))

namespace MyBinTree
{
	typedef enum { RB_RED, RB_BLACK } RBColor;//�ڵ���ɫ
	template<typename T> struct BinNode
	{
		T data;
		BinNode<T>* parent;     //���ڵ�
		BinNode<T>* leftChild;  //����
		BinNode<T>* rightChild; //�Һ���
		int height;//�߶�
		int npl;//Null Path Length ��ʽ��
		RBColor color;//����� ��ɫ
		//���캯��
		BinNode() :
			parent(nullptr), leftChild(nullptr), rightChild(nullptr), height(0), npl(0), color(RB_RED) {}
		BinNode(T e, BinNode<T>* p = nullptr, BinNode<T>* lc = nullptr, BinNode<T>* rc = nullptr, int h = 0, int l = 1, RBColor c = RB_RED) :
			data(e), parent(p), leftChild(lc), rightChild(rc), height(h), npl(l), color(c) {}
		//�����ӿ�
		int size();//��ǰ�ڵ�ĺ����������� �Ե�ǰ�ڵ�Ϊ����������ģ
		BinNode<T>* insertAsLC(T const&);//���Ӳ���
		BinNode<T>* insertAsRC(T const&);//�Һ��Ӳ���
		BinNode<T>* succ();              //���ص�ǰ�ڵ��ֱ�Ӻ��  �����������
		template<typename VST> void travLevel(VST& visit);//������α���
		template<typename VST> void travPre(VST& visit);//�����������
		template<typename VST> void travIn(VST& visit);//�����������
		template<typename VST> void travPost(VST& visit);//�����������
	};//BinNode
	//�����ӿ�
	template<typename T> BinNode<T>* BinNode<T>::insertAsLC(T const& e)
	{
		return leftChild = new BinNode(e, this);
	}//���Ӳ���
	template<typename T> BinNode<T>* BinNode<T>::insertAsRC(T const& e)
	{
		return rightChild = new BinNode(e, this);
	}//�Һ��Ӳ���
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
			while (IsRChild(*s)) s = s->parent;//�Һ�����Ҫ���ظ��׵ĸ��ף���while �ȷ��ظ��ף��˳�while�ٷ��ظ��׵ĸ���
			s = s->parent;
		}
		return s;
	}
	template<typename T> int BinNode<T>::size()
	{
		int s = 1;//���뱾��
		if (leftChild) s += leftChild->size();
		if (rightChild) s += rightChild->size();
		return s;
	}// size() ��ģ
	// �����ı���
	template<typename T>
	class VST
	{
	public:
		void operator() (T data)
		{
			std::cout << "data is:" << data << std::endl;
		}
	};// ����    VST �������� 
	template<typename T, typename VST>void travPre_R(BinNode<T>* x, VST& visit)
	{
		if (!x) return;
		visit(x->data);
		travPre_R(x->leftChild, visit);
		travPre_R(x->rightChild, visit);
	}//����ݹ�
	template<typename T, typename VST>void travPost_R(BinNode<T>* x, VST& visit)
	{
		if (!x) return;
		travPost_R(x->leftChild, visit);
		travPost_R(x->rightChild, visit);
		visit(x->data);
	}//����ݹ�
	template<typename T, typename VST>void travIn_R(BinNode<T>* x, VST& visit)
	{
		if (!x) return;
		travIn_R(x->leftChild, visit);
		visit(x->data);
		travIn_R(x->rightChild, visit);
	}//����ݹ�
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
	}// ��������汾1

	template<typename T, typename VST>
	static void visitAlongLeftBranch(BinNode<T>* x, VST& visit, Liststack<BinNode<T>* >& S)
	{
		while (x)
		{
			visit(x->data);//���ʵ�ǰ�ڵ�
			S.push(x->rightChild);//����ǰ�ڵ���Һ��ӣ���ʵ����������ѹ�빫��ջ S����������ѹ�룩
			x = x->leftChild;//������Ȩ����x������ ֱ������Ϊ nullptr
		}
	}
	template<typename T, typename VST>
	void travPre_I2(BinNode<T>* x, VST& visit)
	{
		Liststack<BinNode<T>* > S;
		while (true)
		{
			visitAlongLeftBranch(x, visit, S);//���ʸ����������������ӣ����������ѹ�����������
			if (S.empty()) break;
			x = S.pop();//����������ȡ����
		}
	}//��������汾2

	template<typename T>
	static void goAlongLeftBranch(BinNode<T>* x, Liststack<BinNode<T>* >& S)
	{// ���ڵ� �������� ������������ ��ջ
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
	}// ��������汾1
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
	}// ��������汾2
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
	}// ��������汾3

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
	}//�������������
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
	}//��α���
	template<typename T>
	template<typename VST> void BinNode<T>::travPre(VST& visit)
	{
		switch (rand() % 3 )
		{
		case 1:travPre_I1(this, visit); break;
		case 2:travPre_I2(this, visit); break;
		default:travPre_R(this, visit); break;
		}
	}//�������
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
	}//�������
	template<typename T>
	template<typename VST> void BinNode<T>::travPost(VST& visit)
	{
		switch (rand() % 2)
		{
		case 1:travPost_I(this, visit); break;
		default:travPost_R(this, visit); break;
		}
	}//�������


};//MyBinTree
#endif // !_BINNODE_H_


