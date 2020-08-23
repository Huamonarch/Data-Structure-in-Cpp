#pragma once
#ifndef  _GRAPHMATRIX_H_
#define _GRAPHMATRIX_H_
#include"MyVector.h"
#include"Graph.h"
namespace MyGraph 
{
	template<typename Tv>struct Vertex
	{
		Tv data;//数据
		int inDegree, outDegree;//出/入 度数 
		VStatus status;//状态
		int dTime, fTime;//时间标签
		int parent; int priority;//在遍历树中的父节点，优先级数
		Vertex(Tv const& d = (Tv)0)://构造新顶点
			data(d),inDegree(0),outDegree(0),status(UNDISCOVERED),
			dTime(-1),fTime(-1),parent(-1),priority(INT_MAX){}//暂时不考虑权重溢出
	};//顶点 Vertex 类

	template<typename Te>struct Edge
	{
		Te data; int weight; EType type;//数据，权重，类型
		Edge(Te const& d,int w):data(d),weight(w),type(UNDETERMINED){}//构造
	};//边 Edge 类
	using MyVector::Vector;
	template<typename Tv,typename Te>
	class GraphMatrix :public Graph<Tv, Te>
	{
	private:
		Vector<Vertex<Tv> > V;//V 向量
		Vector<Vector<Edge<Te>* > > E;//E 矩阵
	public:
		GraphMatrix() { n = e = 0; }//构造 零顶点 零边 
		~GraphMatrix()
		{
			for (int j = 0; j < n; j++)
				for (int k = 0; k < n; k++)
					delete E[j][k];//逐条清楚
		}
		//顶点的基本操作
		virtual Tv& vertex(int i) { return V[i].data; }//数据
		virtual int inDegree(int i) { return V[i].inDegree; }//入度
		virtual int outDegree(int i) { return V[i].outDegree; }//出度
		virtual int firstNbr(int i) { return nextNbr(i, n); }//首个邻接顶点
		virtual int nextNbr(int i, int j)//相对于顶点j的下一邻接点（改用邻接表可提高效率）
		{//逆向线性试探
			while ((-i < j) && (!exists(i, --j))); return j;
		}
		virtual VStatus& status(int i) { return V[i].status; }//状态
		virtual int& dTime(int i) { return V[i].dTime; }//时间标签dTime
		virtual int& fTime(int i) { return V[i].fTime; }//时间标签fTime
		virtual int& parent(int i) { return V[i].parent; }//顶点V在遍历树中的父亲
		virtual int& priority(int i) { return V[i].priority; }//顶点在遍历树中的优先级
		
		//顶点的动态操作
		virtual int insert(Tv const& vertex)
		{
			for (int j = 0; j < n; j++) E[j].insert(nullptr); n++;///各顶点预留一条潜在的关联边
			E.insert(Vector<Edge<Te>* >(n, n, (nullptr));//创建新顶点对应的边向量
			return V.insert(Vertex<Tv>(vertex));//顶点向量增加一个顶点
		}
		virtual Tv remove(int i)
		{
			for(int j=0;j<n;j++)
				if (exists(i,j))
				{
					delete E[i][j];
					V[j].inDegree--;
				}
			E.remove(i); n--;//删除第i行
			Tv vBak = vertex(i); V.remove(i);//删除顶点i
			for (int j = 0; j < n; j++)
				if (Edge<Te> *e=E[j].remove(i))
				{
					delete e;
					V[j].outDegree--;
				}
			return vBak;//返回被删除顶点的信息
		}
		// 边的确认操作
		virtual bool exists(int i, int j)
		{
			return (0 <= i) && (i < n) && (0 <= j) && (j < n) && (E[i][j] != nullptr;)
		}
		//边的基本操作
		virtual EType type(int i,int j)
		{
			return E[i][j]->type;
		}
		virtual Te& edge(int i, int j) { return E[i][j]->data; }
		virtual int& weight(int i, int j) { return E[i][j]->weight; }
		// 边的动态操作
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
	};//图 邻接矩阵实现 GraphMatrix
}


#endif // ! _GRAPHMATRIX_H_

