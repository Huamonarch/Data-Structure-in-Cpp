#pragma once
#ifndef _MYSTACK_H_
#define _MYSTACK_H_
#include"MyVector.h"
#include"MyList.h"
namespace SequenceStack
{
	template<typename T>
	class Seqstack :public MyVector::Vector<T>
	{
		typedef  MyVector::Vector<T> Mvector;
	public:
		void push(const T& e) { Mvector::insert(Mvector::size(), e); }//入栈
		T pop() { return Mvector::remove(Mvector::size() - 1); }//出栈
		T& top() { return (*this)[Mvector::size() - 1]; }//取顶
	};//Seqstack
}//SequenceStack
namespace ListStack
{
	template<typename T>
	class Liststack :public MyList::List<T>
	{
		typedef MyList::List<T> MList;
	public:
		void push(T const& e) { MList::insertAsFirst(e); }//入栈
		T pop() { return MList::remove(this->first()); }//出栈
		T& top() { return this->first()->data; }//取顶  或 return (*this)[0]
	}; //Liststack
}//ListStack
#endif // !_MYSTACK_H_

