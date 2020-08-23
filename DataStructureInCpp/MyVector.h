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
		Rank _size; int _capacity; T* _elem;//规模 容量 数据区
		void copyFrom(T const* A, Rank lo, Rank hi);//复制数组函数 区间[lo,hi)
		void expand();//动态扩容
		void shrink();//动态缩容
	public:
		//构造函数
		Vector(int c = default_capacity, int s = 0, T v = 0)//容量为c, 规模为s， 所有元素初始化为v
		{
			_elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);
		}//s<=c
		Vector(T const* A, Rank n) { copyFrom(A, 0, n); }//数组整体复制
		Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }//数组区间复制
		Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); }//向量整体复制
		Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); }//向量区间复制
		//析构函数
		~Vector() { delete[] _elem; }//释放内部空间
	//只读访问接口
		Rank size()const { return _size; }//规模
		bool empty()const { return !_size; }//判空 

		//可写访问接口
		T& operator[] (Rank r)const { return _elem[r]; }//重载[]，实现Vector的类似数组形式引用各元素
		Vector<T>& operator= (Vector<T> const&);
		Rank insert(Rank r, const T& e);//将 e 插入秩为r处，并返回r
		Rank insert(T const& e) { return insert(_size, e); }//默认插入至末尾 elem[size]是新的末尾，size +=1
		int remove(Rank lo, Rank hi);//删除区间[lo,hi)的元素，并返回被删除的元素个数
		T remove(Rank r);
	};//Vector
	//可写访问接口实现
	template<typename T>Vector<T>& Vector<T>::operator=(Vector<T> const& V)
	{
		if (_elem)
		{
			delete[] _elem;
		}
		copyFrom(V._elem, 0, V._size);
		return *this;
	}//重载=
	template<typename T>Rank Vector<T>::insert(Rank r, T const& e)// 0<=r<=size
	{
		expand();
		for (size_t i = _size; i > r; i--)
		{
			_elem[i] = _elem[i - 1];
		}
		_elem[r] = e;
		_size++;//更新规模
		return r;
	}//插入
	template<typename T>int Vector<T>::remove(Rank lo, Rank hi)
	{
		if (lo == hi)return 0;
		while (hi < _size)
		{
			_elem[lo++] = _elem[hi++];
		}
		_size = lo;//更新size  因为lo++是取lo再++  最后一次是 _elem[lo]=_elem[hi];lo++;hi++
				   // 退出while循环后  lo比_elem数组最大下标大1
		shrink();
		return hi - lo;
	}
	template<typename T>T Vector<T>::remove(Rank r)
	{
		T e = _elem[r];
		remove(r, r + 1);
		return e;
	}
	//protected 成员函数实现
	template<typename T>void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
	{
		_elem = new T[_capacity = 2 * (hi - lo)];//分配空间
		_size = 0;//规模清零
		while (lo < hi)//复制A至_elem[0,hi-lo)
		{
			_elem[_size++] = A[lo++];
		}
	}//深复制
	template<typename T>void Vector<T>::expand()
	{
		if (_size < _capacity) return;
		if (_capacity < default_capacity) _capacity = default_capacity;//不低于最小容量
		T* oldelem = _elem; _elem = new T[_capacity <<= 1];
		for (size_t i = 0; i < _size; i++)
		{
			_elem[i] = oldelem[i];
		}
		delete[] oldelem;
	}//倍增扩容策略
	template<typename T>void Vector<T>::shrink()
	{
		if (_capacity > _capacity >> 1)return;
		if (_size << 2 > _capacity)return;//装填因子 size/capacity>25 则不用缩容
		T* oldelem = _elem; _elem = new T[_capacity >>= 1];
		for (size_t i = 0; i < _size; i++)
		{
			_elem[i] = oldelem[i];
		}
		delete[] oldelem;
	}//减半缩容策略 
}//namespace MyVector

#endif // !_MYVECTOR_H_

