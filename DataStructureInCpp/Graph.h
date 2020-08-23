#pragma once
#ifndef _GRAPH_H_
#define _GRAPH_H_
#include"MyStack.h"
#include"MyQueue.h"
//#include"GraphMatrix.h"
namespace MyGraph
{
	using ListStack::Liststack;
	using ListQueue::Listqueue;

	typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;//����״̬
	typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType;//���ڱ�����������������
	template<typename Tv, typename Te> class Graph
	{
	private:
		void reset()
		{
			for (int i = 0; i < n; i++)
			{
				status(i) = UNDISCOVERED;//״̬
				dTime(i) = fTime(i) = -1;//ʱ���ǩ
				parent(i) = -1; priority(i) = INT_MAX;//(�ڱ������е�)���ڵ㣬���ȼ���
				for (int j = 0; j < n; j++)
					if (exists(i, j)) type(i, j) = UNDETERMINED;//����
			}
		}
		void BFS(int, int&);//����ͨ�򣩹�����������㷨
		void DFS(int, int&);//(��ͨ��)������������㷨
		void BCC(int, int&, Liststack<int>&);//(��ͨ��)����DFS��˫��ͨ�����ֽ��㷨
		bool TSort(int, int&, Liststack<Tv>*);//(��ͨ��)����DFS�����������㷨
		template<typename PU> void PFS(int, PU);//����ͨ�����ȼ����ؿ��
	public:
		//����
		int n;//��������
		virtual int insert(Tv const&) = 0;//���붥�㣬���ر��
		virtual Tv remove(int) = 0;//ɾ�����㼰������ߣ����ظö�����Ϣ
		virtual Tv& vertex(int) = 0;//����V�����ݣ��ö���i��ȷ���ڣ�
		virtual int inDegree(int) = 0;//����V����ȣ��ö����ȷ���ڣ�
		virtual int outDegree(int) = 0;//����V�ĳ��ȣ��ö����ȷ���ڣ�
		virtual int firstNbr(int) = 0;//����V�׸��ڽӶ���
		virtual int nextNbr(int, int) = 0;//����V�ģ�����ڶ���j�ģ���һ�ڽӶ���
		virtual VStatus& status(int) = 0;//����V��״̬
		virtual int& dTime(int) = 0;//����V��ʱ���ǩdTime
		virtual int& fTime(int) = 0;//����V��ʱ���ǩfTime
		virtual int& parent(int) = 0;//����V�ڱ������еĸ���
		virtual int& priority(int) = 0;//�����ڱ������е����ȼ�

		//�ߣ�����Լ�� ����߾�ת��Ϊ �������һ������� �Ӷ�������ͼ��������ͼ������
		int e;//������
		virtual bool exists(int, int) = 0;//�ߣ�v��u���Ƿ����
		virtual void insert(Te const&, int, int, int) = 0;//�ڶ���v��u֮�����Ȩ��Ϊw�ı�e
		virtual Te remove(int, int) = 0;//ɾ������v��u֮��ı�e�����ظñ���Ϣ
		virtual EType& type(int, int) = 0;//�ߣ�v��u��������
		virtual Te& edge(int, int) = 0;//�ߣ�v��u�������ݣ��ñ�ȷʵ���ڣ�
		virtual int& weight(int, int) = 0;//��(v,u)��Ȩ��
		//�㷨
		void bfs(int);//�����������
		void dfs(int);//�����������
		void bcc(int);//����DFS��˫��ͨ�����ֽ�
		Liststack<Tv>* tSort(int);//����DFS�����������㷨
		void prim(int);//��С֧����Prim�㷨
		void dijkstra(int);//���·��Dijkstra�㷨
		template<typename PU> void pfs(int, PU);//���ȼ��������
	};//Graph ��
	template<typename Tv,typename Te> void Graph<Tv,Te>::bfs(int s)
	{
		reset();
		int clock = 0;
		int v = s;
		do
		{
			if (UNDISCOVERED = status(v))
				BFS(v, clock);
		} while (s!=(v=(++v%n)));
	}

	template<typename Tv,typename Te>void Graph<Tv,Te>::BFS(int v,int& clock)
	{
		Listqueue<int> Q;
		status(v) = DISCOVERED;
		Q.enqueue(v);
		while(!Q.empty())
		{
			int v = Q.dequeue();
			dTime(v) = ++clock;
			for(int u=firstNbr(v��;-1<u;u=nextNbr(v,u))
			{
				if(UNDISCOVERED=status(u))
				{
					status(u)=UNDISCOVERED;
						Q.enqueue(u);
						type(v,u)=TREE;
						parent(u)=v;
				}
				else
				{
					type(v, u) = CROSS;
				}
			}
			status(v) = VISITED;
		}
	}

}//MyGraph




#endif // !_GRAPH_H_

