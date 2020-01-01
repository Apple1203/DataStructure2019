#pragma once
#include<iostream>
using namespace std;
template<class T, class E>
class MSTEdgeNode 
{											//��С�������߽���������
													//������λ�ü����ϵ�Ȩֵ
public:
	int tail, head;
	E cost;
	MSTEdgeNode() :tail(-1), head(-1), cost(0) {}						//���캯��
	MSTEdgeNode(MSTEdgeNode<T, E>& M)
	{
		tail = M.tail;
		head = M.head;
		cost = M.cost;
	}
	void Set(int h, int t, E c)
	{
		head = h;
		tail = t;
		cost = c;
	}
	int getTail()
	{
		return tail;
	}
	int getHead()
	{
		return head;
	}
	bool operator<=(MSTEdgeNode<T, E>& R)
	{
		return cost <= R.cost;
	}

	bool operator>(MSTEdgeNode<T, E>& R)
	{
		return cost > R.cost;
	}
	MSTEdgeNode<T, E>& operator = (MSTEdgeNode<T, E>& M)
	{
		tail = M.tail;
		head = M.head;
		cost = M.cost;
		return *this;
	}
};
template<class T, class E>
ostream& operator<<(ostream& out, MSTEdgeNode<T, E>& node)
{
	out << '(' << node.head << ',' << node.tail << ',' << node.cost << ')';
	return out;
}
const int DefaultMTSize = 10;
template<class T, class E>
class MinSpanTree												//��С���������ඨ��
{
protected:
	MSTEdgeNode<T, E>* edgevalue;								//�ñ�ֵ�����ʾ��
	int maxSize, n;												//��������Ԫ�ظ����͵�ǰ����
public:
	MinSpanTree(int sz = DefaultMTSize - 1) :maxSize(sz), n(0)
	{
		edgevalue = new MSTEdgeNode<T, E>[sz];
	}
	~MinSpanTree()
	{
		delete[]edgevalue;
	}

	int Insert(MSTEdgeNode<T, E>& item)
	{
		if (n < maxSize)
		{
			edgevalue[n] = item;
			n++;
			return 1;
		}
		else
		{
			cout << "��������" << endl;
			return 0;
		}
	}
};
template<class T, class E>
ostream& operator<<(ostream& out, MinSpanTree<T, E>& MST)
{
	for (int i = 0; i < MST.n; i++)
		out << MST.edgevalue[i] << endl;
	return out;
}