#pragma once
#ifndef _MYQUEUE_H_
#define _MYQUEUE_H_
#include"MyVector.h"
#include"MyList.h"
namespace SequenceQueue
{
	template<typename T>
	class Seqqueue :public MyVector::Vector<T>
	{
		typedef MyVector::Vector<T> Mvector;
	public:
		void enqueue(T const& e) { Mvector::insert(0, e); }//���
		T dequeue() { return Mvector::remove(Mvector::size() - 1); }//����
		T& front() { return (*this)[Mvector::size() - 1]; }//ȡ��
	}; //Seqqueue
}//SequenceQueue
namespace ListQueue
{
	template<typename T>
	class Listqueue :public MyList::List<T>
	{
		typedef MyList::List<T> MList;
	public:
		void enqueue(T const& e) { MList::insertAsLast(e); }//���
		T dequeue() { return MList::remove(this->first()); }//����
		T& front() { return (*this)[0]; }//ȡ��
	}; //Listqueue
}//ListQueue
#endif // !_MYQUEUE_H_

