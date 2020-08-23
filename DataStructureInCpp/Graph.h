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

	typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;//顶点状态
	typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType;//边在遍历树中所属的类型
	template<typename Tv, typename Te> class Graph
	{
	private:
		void reset()
		{
			for (int i = 0; i < n; i++)
			{
				status(i) = UNDISCOVERED;//状态
				dTime(i) = fTime(i) = -1;//时间标签
				parent(i) = -1; priority(i) = INT_MAX;//(在遍历树中的)父节点，优先级数
				for (int j = 0; j < n; j++)
					if (exists(i, j)) type(i, j) = UNDETERMINED;//类型
			}
		}
		void BFS(int, int&);//（连通域）广度优先搜索算法
		void DFS(int, int&);//(连通域)深度优先搜索算法
		void BCC(int, int&, Liststack<int>&);//(连通域)基于DFS的双连通分量分解算法
		bool TSort(int, int&, Liststack<Tv>*);//(连通域)基于DFS的拓扑排序算法
		template<typename PU> void PFS(int, PU);//（连通域）优先级搜素框架
	public:
		//顶点
		int n;//顶点总数
		virtual int insert(Tv const&) = 0;//插入顶点，返回编号
		virtual Tv remove(int) = 0;//删除顶点及其关联边，返回该顶点信息
		virtual Tv& vertex(int) = 0;//顶点V的数据（该顶点i的确存在）
		virtual int inDegree(int) = 0;//顶点V的入度（该顶点的确存在）
		virtual int outDegree(int) = 0;//顶点V的出度（该顶点的确存在）
		virtual int firstNbr(int) = 0;//顶点V首个邻接顶点
		virtual int nextNbr(int, int) = 0;//顶点V的（相对于顶点j的）下一邻接顶点
		virtual VStatus& status(int) = 0;//顶点V的状态
		virtual int& dTime(int) = 0;//顶点V的时间标签dTime
		virtual int& fTime(int) = 0;//顶点V的时间标签fTime
		virtual int& parent(int) = 0;//顶点V在遍历树中的父亲
		virtual int& priority(int) = 0;//顶点在遍历树中的优先级

		//边：这里约定 无向边均转化为 方向互逆的一对有向边 从而将无向图视作有向图的特例
		int e;//边总数
		virtual bool exists(int, int) = 0;//边（v，u）是否存在
		virtual void insert(Te const&, int, int, int) = 0;//在顶点v与u之间插入权重为w的边e
		virtual Te remove(int, int) = 0;//删除顶点v与u之间的边e，返回该边信息
		virtual EType& type(int, int) = 0;//边（v，u）的类型
		virtual Te& edge(int, int) = 0;//边（v，u）的数据（该边确实存在）
		virtual int& weight(int, int) = 0;//边(v,u)的权重
		//算法
		void bfs(int);//广度优先搜索
		void dfs(int);//深度优先搜索
		void bcc(int);//基于DFS的双连通分量分解
		Liststack<Tv>* tSort(int);//基于DFS的拓扑排序算法
		void prim(int);//最小支撑数Prim算法
		void dijkstra(int);//最短路径Dijkstra算法
		template<typename PU> void pfs(int, PU);//优先级搜索框架
	};//Graph 类
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
			for(int u=firstNbr(v）;-1<u;u=nextNbr(v,u))
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

