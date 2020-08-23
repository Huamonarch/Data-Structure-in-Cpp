#include<iostream>
#include"TinyDataStructure.h"
using namespace TinyDataStructure;
int main()
{
	BinTree<int> t1;
	t1.insertAsRoot(1);
	t1.insertAsLC(t1.root(), 2);
	t1.insertAsRC(t1.root(), 3);
	BinTree<int> t2;
	t2.insertAsRoot(4);
	t2.insertAsLC(t2.root(), 5);
	t2.insertAsRC(t2.root(), 6);
	BinTree<int>* pt2 = &t2;
	t1.attachAsLC(t1.root()->leftChild, pt2);
	
	VST<int> visit;
	std::cout << "t1的层次遍历：" << std::endl;
	t1.travLevel(visit);
	std::cout << "t1的先序遍历：" << std::endl;
	t1.travPre(visit);
	std::cout << "t1的中序遍历：" << std::endl;
	t1.travIn(visit);
	std::cout << "t1的后序遍历：" << std::endl;
	t1.travPost(visit);
	/*std::cout << "t1的前序遍历迭代版1：" << std::endl;
	travPre_I2(t1.root(), visit);
	std::cout << "t1的前序遍历迭代版2：" << std::endl;
	travPre_R(t1.root(), visit);
	std::cout << "t1的中序遍历递归版：" << std::endl;
	travIn_R(t1.root(), visit);
	std::cout << "t1的中序遍历迭代版1：" << std::endl;
	travIn_I1(t1.root(), visit);
	std::cout << "t1的中序遍历迭代版2：" << std::endl;
	travIn_I2(t1.root(), visit);
	std::cout << "t1的中序遍历迭代版3：" << std::endl;
	travIn_I3(t1.root(), visit);
	std::cout << "t1的后序遍历递归版：" << std::endl;
	travPost_R(t1.root(), visit);
	std::cout << "t1的后序遍历迭代版：" << std::endl;
	travPost_I(t1.root(), visit);*/
	BinTree<int> *t3=t1.secede(t1.root()->leftChild->leftChild);
	std::cout << "t1的层次遍历：" << std::endl;
	t1.travLevel(visit);
	std::cout << "t1的先序遍历：" << std::endl;
	t1.travPre(visit);
	std::cout << "t1的中序遍历：" << std::endl;
	t1.travIn(visit);
	std::cout << "t1的后序遍历：" << std::endl;
	t1.travPost(visit);
	
	std::cout << "t3的层次遍历：" << std::endl;
	t3->travLevel(visit);
	std::cout << "t3的先序遍历：" << std::endl;
	t3->travPre(visit);
	std::cout << "t3的先序遍历：" << std::endl;
	t3->travIn(visit);
	std::cout << "t3的先序遍历：" << std::endl;
	t3->travPost(visit);
	/*Seqstack<int> s;
	for (int i = 0; i < 100000;i++)
	{
		s.push(i);
	}
	for (int i = 0; i < 100000; i++)
	{
		std::cout << s.pop() << std::endl;
	}*/
	
	
	return 0;
}