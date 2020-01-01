#include<iostream>
#include<fstream>
#include<queue>
#define MaxWeight 0x7fffffff
#include"MinHeap.h"
#include"MinSpanTree.h"
#include"UFSets.h"
#include"LinkQueue.h"
#define DefaultVertices 30
#include<iomanip>
using namespace std;
template<class T,class E>
class Graphmtx
{
	T * VerticesList;
	E ** Edge;
	int maxVertices;	// 图中最大的顶点数
	int maxEdges;

	int numEdges;		// 当前边数
	int numVertices;	// 当前顶点数
	
	friend istream& operator >>(istream& in, Graphmtx<T, E>& G);
	friend ostream& operator <<(ostream& out, Graphmtx<T, E>& G);
public:
	int maxWeight;
	Graphmtx();
	~Graphmtx()
	{	delete[] VerticesList; delete[] Edge;	}
	T getValue(int i)
	{return i >= 0 && i < numVertices ? VerticesList[i] : NULL;}
	E getWeight(int v1,int v2)
	{return v1 != -1 && v2 != -1 ? Edge[v1][v2] : 0;}
	int getFirstNeighbor(int v);
	int getNextNeighbor(int v, int w);
	int NumberOfVertices() { return numVertices; }
	int NumberOfEdges() { return numEdges; }
	bool insertVertex(const T& vertex);
	bool insertEdge(int v1, int v2, E cost);
	bool removeVertex(int v);
	bool removeEdge(int v1, int v2);
	void printMat();
	int getVertexPos(T vertex)
	{
		for (int i = 0; i < numVertices; i++)
			if (VerticesList[i] == vertex)return i;
		return -1;
	}
};

template<class T,class E>
Graphmtx<T, E>::Graphmtx()
{
	ifstream finP("D:\\point.txt", ios::in);
	ifstream finC("D:\\channel.txt",ios::in);
	if (!finP)
	{
		cerr << "顶点文件打开错误！" << endl;
		exit(1);
	}
	if (!finC)
	{
		cerr << "边集文件打开错误！" << endl;
		exit(1);
	}
	int numv, nume;
	finP >> numv;
	finC >> nume;
	maxVertices = numv;
	numVertices = 0;
	numEdges = 0;
	maxWeight = MaxWeight;
	int i, j;
	VerticesList = new T[maxVertices];				//创建顶点表数组
	Edge = new E *[maxVertices];					//创建邻接矩阵数组
	for (i = 0; i < maxVertices; i++)
		Edge[i] = new E[maxVertices];
	for (i = 0; i < maxVertices; i++)				//邻接矩阵初始化
		for (j = 0; j < maxVertices; j++)
			Edge[i][j] = (i == j) ? 0 : MaxWeight;
	char ve1, ve2;
	int v1, v2, cost;
	while (finP >> ve1)
	{

		insertVertex(ve1);
	}
	while (!finC.eof())
	{
		finC >> ve1 >> ve2 >> cost;
		v1 = getVertexPos(ve1);
		v2 = getVertexPos(ve2);
		insertEdge(v1, v2, cost);
	}
	finP.close();
	finC.close();
	
}
template<class T, class E>
void Graphmtx<T, E>::printMat()
{
	cout << "图的邻接矩阵为：" << endl << setw(6) << "|";
	for (int counter = 0; counter <= maxVertices - 1; counter++)
	{
		cout << setw(3) << VerticesList[counter];
	}

	cout << endl << setw(6) << "|";
	for (int counter = 0; counter <= maxVertices - 1; counter++)
	{
		cout << "---";
	}
	cout << endl;
	for (int counter = 0; counter <= maxVertices - 1; counter++)
	{
		cout << setw(3) << VerticesList[counter] << setw(3) << "|";
		for (int counterr = 0; counterr <= maxVertices - 1; counterr++)
		{
			if (Edge[counter][counterr] == MaxWeight)
				cout << "   ";
			else
				cout << setw(3) << Edge[counter][counterr];
		}
		cout << endl;
	}
}
template<class T,class E>
int Graphmtx<T, E>::getFirstNeighbor(int v)
{
	if (v != -1)
	{
		for (int col = 0; col < numVertices; col++)
			if (Edge[v][col] > 0 && Edge[v][col] < MaxWeight)return col;
	}
	return -1;
}
template<class T, class E>
int Graphmtx<T, E>::getNextNeighbor(int v, int w)
{
	if (v != -1 && w != -1)
	{
		for (int col = w + 1; col <= numVertices; col++)
			if (Edge[v][col] > 0 && Edge[v][col] < MaxWeight)return col;
	}
	return -1;
}
template<class T, class E>
bool Graphmtx<T, E>::insertVertex(const T& vertex)
{
	if (numVertices == maxVertices)return false;
	VerticesList[numVertices++] = vertex;
	return true;
}
template<class T, class E>
bool Graphmtx<T, E>::removeVertex(int v)
{
	if (v < 0 && v >= numVertices)return false;
	if (numVertices == 1)return false;
	int i, j;
	VerticesList[v] = VerticesList[numVertices - 1];
	for (i = 0; i < numVertices; i++)
		if (Edge[i][v] > 0 && Edge[i][v] < MaxWeight)numEdges--;
	for (i = 0; i < numVertices; i++)
		Edge[i][v] = Edge[i][numVertices - 1];
	for (j = 0; j < numVertices; j++)
		Edge[v][j] = Edge[numVertices][j];
	return true;
}
template<class T, class E>
bool Graphmtx<T, E>::insertEdge(int v1, int v2, E cost)
{
	if (v1 > -1 && v1<numVertices&&v2>-1 && v2 < numVertices&&Edge[v1][v2] == MaxWeight)
	{
		Edge[v1][v2] = Edge[v2][v1] = cost;
		numEdges++;
		return true;
	}
	else return false;
}
template<class T, class E>
bool Graphmtx<T, E>::removeEdge(int v1, int v2)
{
	if (v1 > -1 && v1<numVertices&&v2>-1 && v2 < numVertices&&Edge[v1][v2]>0
		&& Edge[v1][v2] < MaxWeight)
	{
		Edge[v1][v2] = Edge[v2][v1] = MaxWeight;
		numEdges--;
		return true;
	}
	else return false;
}
template<class T, class E>
istream& operator >> (istream& in, Graphmtx<T, E>& G)
{
	int i, j, k, n, m;
	T e1, e2;
	E weight;
	in >> n >> m;
	for (i = 0; i < n; i++)
	{
		in >> e1;
		G.insertVertex(e1);
	}
	i = 0;
	while (i < m)
	{
		in >> e1 >> e2 >> weight;
		j = G.getVertexPos(e1);
		k = G.getVertexPos(e2);
		if (j == -1 || k == -1)
			cout << "边两端点信息有误，重新输入！" << endl;
		else
			G.insertEdge(j, k, weight), i++;
	}
	return in;
}
template<class T, class E>
ostream& operator << (ostream& out, Graphmtx<T, E>& G)
{
	int i, j, n, m;
	T e1, e2;
	E w;
	n = G.NumberOfVertices();
	m = G.NumberOfEdges();
	out << n << "," << m << endl;
	for(i=0;i<n;i++)
		for (j = i + 1; j < n; j++)
		{
			w = G.getWeight(i, j);
			if (w > 0 && w < MaxWeight)
			{
				e1 = G.getValue(i);
				e2 = G.getValue(j);
				out << "(" << e1 << "," << e2 << "," << w << ")" << endl;
			}
		}
	return out;
}
template<class T,class E>
void DFS(Graphmtx<T, E>& G, const T& v)//从顶点v出发
{
	int i, loc, n = G.NumberOfVertices();
	bool *visited = new bool[n];
	for (i = 0; i < n; i++)visited[i] = false;
	loc = G.getVertexPos(v);
	DFS(G, loc, visited);
	delete[] visited;
}
template<class T, class E>
void DFS(Graphmtx<T, E>& G, int v, bool visited[])
{
	cout << G.getValue(v) << " ";
	visited[v] = true;
	int w = G.getFirstNeighbor(v);
	while (w != -1)
	{
		if (visited[w] == false)DFS(G, w, visited);
		w = G.getNextNeighbor(v, w);
	}
}

template<class T, class E>
void BFS(Graphmtx<T, E>& G, const T& v)
{
	int i, w, n = G.NumberOfVertices();
	bool *visited = new bool[n];
	for (i = 0; i < n; i++)visited[i] = false;
	int loc = G.getVertexPos(v);
	cout << G.getValue(loc) << "";
	visited[loc] = true;
	LinkedQueue<int>Q;
	Q.EnQueue(loc);
	while (!Q.IsEmpty())
	{
		Q.DeQueue(loc);
		w = G.getFirstNeighbor(loc);
		while (w != -1)
		{
			if (visited[w] == false)
			{
				cout << G.getValue(w) << "";
				visited[w] = true;
				Q.EnQueue(w);
			}
			w = G.getNextNeighbor(loc, w);
		}
	}
	delete[] visited;
}

template<class T, class E>
void Kruskal(Graphmtx<T, E>& G, MinSpanTree<T, E>& MST)
{
	MSTEdgeNode<T, E>ed;
	int u, v, count;							//边结点辅助单元
	int n = G.NumberOfVertices();				//顶点数
	int m = G.NumberOfEdges();					//边数
	MinHeap<MSTEdgeNode<T, E>> H(m);			//最小堆，关键码类型为E
	UFSets F(n);								//并查集
	for (u = 0; u < n; u++)
		for (v = u + 1; v < n; v++)
			if (G.getWeight(u, v) != G.maxWeight)
			{
				ed.Set(u, v, G.getWeight(u, v));
				H.Insert(ed);
				cout << "在最小堆中插入" << ed << endl;
			}
	count = 1;									//最小生成树加入边计数
	while (count < n)							//反复执行，取n-1条边
	{
		int flag = 0;
		H.RemoveMin(ed);						//从最小堆中退出具最小权值的边ed
		cout << "在最小堆中退出" << ed << ',';
		int h = ed.getHead(), t = ed.getTail();
		u = F.Find(t);					//
		v = F.Find(h);					//取两个顶点所在集合的根u与v
		if (u != v)								//不是同一个集合，说明不连通
		{
			flag = 1;
			F.Union(u, v);						//合并，连同他们
			cout << "通过并查集合并" << G.getValue(h) << "和" << G.getValue(t) << ',';
			MST.Insert(ed);						//该边存入最小生成树
			cout << "在最小生成树中连接" << G.getValue(h) << '-' << G.getValue(t) << "路径";
			count++;
		}
		if (flag == 0)
			cout << G.getValue(h) << "与" << G.getValue(t) << "属于同一集合，不能连接";
		cout << endl;
	}
}
Graphmtx<char, int>* test = new Graphmtx<char, int>();

void func()
{
	cout << "DFS：" << endl;
	for (int i = 0; i < 6; i++)
	{
		char a = test->getValue(i);
		cout << "从" << a << "开始遍历：" << endl;
		cout << "遍历过程为:";
		DFS(*test, a);
		cout << endl;
		
	}
	cout <<endl<< "BFS：" << endl;
	for (int i = 0; i < 6; i++)
	{
		char b = test->getValue(i);
		cout << "从" << b << "开始遍历：" << endl;
		cout << "遍历过程为:";
		BFS(*test, b);
		cout << endl;
	}
}
void funcc()
{
	Graphmtx<char, int> G;
	MinSpanTree<char, int> MST;
	cout << "在Kruskal算法中，最小堆、并查集、最小生成树的变化过程为：" << endl;
	Kruskal(G, MST);
}
int main()
{
	
	test->printMat();
	cout << endl;
	func();
	cout << endl;
	funcc();
	system("pause");
	return 0;
}