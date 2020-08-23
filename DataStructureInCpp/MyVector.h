#pragma once
#ifndef _MYVECTOR_H_
#define _MYVECTOR_H_
namespace MyVector
{
	typedef int Rank;
	const int default_capacity = 3;
	template<typename T>class Vector
	{
	protected:
		Rank _size; int _capacity; T* _elem;//��ģ ���� ������
		void copyFrom(T const* A, Rank lo, Rank hi);//�������麯�� ����[lo,hi)
		void expand();//��̬����
		void shrink();//��̬����
	public:
		//���캯��
		Vector(int c = default_capacity, int s = 0, T v = 0)//����Ϊc, ��ģΪs�� ����Ԫ�س�ʼ��Ϊv
		{
			_elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);
		}//s<=c
		Vector(T const* A, Rank n) { copyFrom(A, 0, n); }//�������帴��
		Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }//�������临��
		Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); }//�������帴��
		Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); }//�������临��
		//��������
		~Vector() { delete[] _elem; }//�ͷ��ڲ��ռ�
	//ֻ�����ʽӿ�
		Rank size()const { return _size; }//��ģ
		bool empty()const { return !_size; }//�п� 

		//��д���ʽӿ�
		T& operator[] (Rank r)const { return _elem[r]; }//����[]��ʵ��Vector������������ʽ���ø�Ԫ��
		Vector<T>& operator= (Vector<T> const&);
		Rank insert(Rank r, const T& e);//�� e ������Ϊr����������r
		Rank insert(T const& e) { return insert(_size, e); }//Ĭ�ϲ�����ĩβ elem[size]���µ�ĩβ��size +=1
		int remove(Rank lo, Rank hi);//ɾ������[lo,hi)��Ԫ�أ������ر�ɾ����Ԫ�ظ���
		T remove(Rank r);
	};//Vector
	//��д���ʽӿ�ʵ��
	template<typename T>Vector<T>& Vector<T>::operator=(Vector<T> const& V)
	{
		if (_elem)
		{
			delete[] _elem;
		}
		copyFrom(V._elem, 0, V._size);
		return *this;
	}//����=
	template<typename T>Rank Vector<T>::insert(Rank r, T const& e)// 0<=r<=size
	{
		expand();
		for (size_t i = _size; i > r; i--)
		{
			_elem[i] = _elem[i - 1];
		}
		_elem[r] = e;
		_size++;//���¹�ģ
		return r;
	}//����
	template<typename T>int Vector<T>::remove(Rank lo, Rank hi)
	{
		if (lo == hi)return 0;
		while (hi < _size)
		{
			_elem[lo++] = _elem[hi++];
		}
		_size = lo;//����size  ��Ϊlo++��ȡlo��++  ���һ���� _elem[lo]=_elem[hi];lo++;hi++
				   // �˳�whileѭ����  lo��_elem��������±��1
		shrink();
		return hi - lo;
	}
	template<typename T>T Vector<T>::remove(Rank r)
	{
		T e = _elem[r];
		remove(r, r + 1);
		return e;
	}
	//protected ��Ա����ʵ��
	template<typename T>void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
	{
		_elem = new T[_capacity = 2 * (hi - lo)];//����ռ�
		_size = 0;//��ģ����
		while (lo < hi)//����A��_elem[0,hi-lo)
		{
			_elem[_size++] = A[lo++];
		}
	}//���
	template<typename T>void Vector<T>::expand()
	{
		if (_size < _capacity) return;
		if (_capacity < default_capacity) _capacity = default_capacity;//��������С����
		T* oldelem = _elem; _elem = new T[_capacity <<= 1];
		for (size_t i = 0; i < _size; i++)
		{
			_elem[i] = oldelem[i];
		}
		delete[] oldelem;
	}//�������ݲ���
	template<typename T>void Vector<T>::shrink()
	{
		if (_capacity > _capacity >> 1)return;
		if (_size << 2 > _capacity)return;//װ������ size/capacity>25 ��������
		T* oldelem = _elem; _elem = new T[_capacity >>= 1];
		for (size_t i = 0; i < _size; i++)
		{
			_elem[i] = oldelem[i];
		}
		delete[] oldelem;
	}//�������ݲ��� 
}//namespace MyVector

#endif // !_MYVECTOR_H_

