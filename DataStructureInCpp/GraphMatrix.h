#pragma once
#ifndef  _GRAPHMATRIX_H_
#define _GRAPHMATRIX_H_
#include"MyVector.h"
#include"Graph.h"
namespace MyGraph 
{
	template<typename Tv>struct Vertex
	{
		Tv data;//����
		int inDegree, outDegree;//��/�� ���� 
		VStatus status;//״̬
		int dTime, fTime;//ʱ���ǩ
		int parent; int priority;//�ڱ������еĸ��ڵ㣬���ȼ���
		Vertex(Tv const& d = (Tv)0)://�����¶���
			data(d),inDegree(0),outDegree(0),status(UNDISCOVERED),
			dTime(-1),fTime(-1),parent(-1),priority(INT_MAX){}//��ʱ������Ȩ�����
	};//���� Vertex ��

	template<typename Te>struct Edge
	{
		Te data; int weight; EType type;//���ݣ�Ȩ�أ�����
		Edge(Te const& d,int w):data(d),weight(w),type(UNDETERMINED){}//����
	};//�� Edge ��
	using MyVector::Vector;
	template<typename Tv,typename Te>
	class GraphMatrix :public Graph<Tv, Te>
	{
	private:
		Vector<Vertex<Tv> > V;//V ����
		Vector<Vector<Edge<Te>* > > E;//E ����
	public:
		GraphMatrix() { n = e = 0; }//���� �㶥�� ��� 
		~GraphMatrix()
		{
			for (int j = 0; j < n; j++)
				for (int k = 0; k < n; k++)
					delete E[j][k];//�������
		}
		//����Ļ�������
		virtual Tv& vertex(int i) { return V[i].data; }//����
		virtual int inDegree(int i) { return V[i].inDegree; }//���
		virtual int outDegree(int i) { return V[i].outDegree; }//����
		virtual int firstNbr(int i) { return nextNbr(i, n); }//�׸��ڽӶ���
		virtual int nextNbr(int i, int j)//����ڶ���j����һ�ڽӵ㣨�����ڽӱ�����Ч�ʣ�
		{//����������̽
			while ((-i < j) && (!exists(i, --j))); return j;
		}
		virtual VStatus& status(int i) { return V[i].status; }//״̬
		virtual int& dTime(int i) { return V[i].dTime; }//ʱ���ǩdTime
		virtual int& fTime(int i) { return V[i].fTime; }//ʱ���ǩfTime
		virtual int& parent(int i) { return V[i].parent; }//����V�ڱ������еĸ���
		virtual int& priority(int i) { return V[i].priority; }//�����ڱ������е����ȼ�
		
		//����Ķ�̬����
		virtual int insert(Tv const& vertex)
		{
			for (int j = 0; j < n; j++) E[j].insert(nullptr); n++;///������Ԥ��һ��Ǳ�ڵĹ�����
			E.insert(Vector<Edge<Te>* >(n, n, (nullptr));//�����¶����Ӧ�ı�����
			return V.insert(Vertex<Tv>(vertex));//������������һ������
		}
		virtual Tv remove(int i)
		{
			for(int j=0;j<n;j++)
				if (exists(i,j))
				{
					delete E[i][j];
					V[j].inDegree--;
				}
			E.remove(i); n--;//ɾ����i��
			Tv vBak = vertex(i); V.remove(i);//ɾ������i
			for (int j = 0; j < n; j++)
				if (Edge<Te> *e=E[j].remove(i))
				{
					delete e;
					V[j].outDegree--;
				}
			return vBak;//���ر�ɾ���������Ϣ
		}
		// �ߵ�ȷ�ϲ���
		virtual bool exists(int i, int j)
		{
			return (0 <= i) && (i < n) && (0 <= j) && (j < n) && (E[i][j] != nullptr;)
		}
		//�ߵĻ�������
		virtual EType type(int i,int j)
		{
			return E[i][j]->type;
		}
		virtual Te& edge(int i, int j) { return E[i][j]->data; }
		virtual int& weight(int i, int j) { return E[i][j]->weight; }
		// �ߵĶ�̬����
		virtual void insert(Te cosnt& edge, int w, int i, int j)
		{
			if (exists(i, j)) return;
			E[i][j] = new Edge<Te>(edge, w);
			e++; V[i].outDegree++; V[j].inDegree++;
		}
		virtual Te remove(int i, int j)
		{
			Te eBar = edge(i, j);
			delete E[i][j];
			E[i][j] = nullptr;
			e--; V[i].outDegree--; V[j].inDegree--;
			return eBar;
		}
	};//ͼ �ڽӾ���ʵ�� GraphMatrix
}


#endif // ! _GRAPHMATRIX_H_

