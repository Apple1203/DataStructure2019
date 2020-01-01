/*
this is a WRONG version!!!!!
*/

/*
第二章作业

问题描述：
用单链表保存m个整数，结点的结构如下图所示
---------------------
|	data	  |		link	|
---------------------
且|data|<= n，n为正整数。设计一个时间复杂度尽可能低的算法，对于链表中data的绝对值相等
的结点，仅保留第一次出现的结点而删除其余绝对值相等的结点。

练习要求：
编写去重算法，删除链表中绝对值重复的结点

提示：
线性时间复杂度的去重算法思路：利用辅助数组Q记录已出现的数值，Q的大小为n+1，Q数组元素
初始值为0，依次遍历链表结点，同时检查Q[|data|]的值，如果为0，则保留该节点且Q[|data|]=1；
否则将该节点从链表中删除。
*/
#include<iostream>
#include<cmath>
#include<cstdlib>
#include <assert.h>
#include<ctime>
#define maxData 10
#define maxLength 10

using namespace std;

class List; // List类的前视声明

struct LinkNode  //结点类定义
{
	int data;
	LinkNode * link ;
	LinkNode(int &x);
};

class List
{
private:
	LinkNode * first;
public:
	bool Insert(int i, int & x); // 插入算法
	bool Remove(int i, int & x); // 删除算法
	int Length()const;
	LinkNode* getFirst();
	bool RemoveSame(); // 去重算法
	void show();
	LinkNode* Search(int i);
	bool IsEmpty()					//判断链表是否为空
	{
		if (first == NULL)
			return true;
		else
			return false;
	}
	List()
	{
		first = NULL;
	}
};
LinkNode::LinkNode(int &x)
{
	data = x;
}
LinkNode* List::Search(int i)
{
	if (i <= 0 || i > Length())
		return NULL;
	LinkNode* p = first;
	int count = 1;
	while (p != NULL)
	{
		if (count == i)
			return p;
		p = p->link;
		count++;
	}
}

bool List::Insert(int i, int & x)
{
	//将新元素x插入到第i个结点之后，i从1开始，i=0表示插入到第一个结点之前。
	if (first == NULL || i == 0)
	{
		LinkNode * newNode = new LinkNode(x);  // 建立一个新节点
		if (newNode == NULL)
		{
			cerr << "存储分配错误!\n";
			exit(1);
		}
		newNode->link = first;
		first = newNode;
	}
	else
	{
		LinkNode* current = first;
		for (int k = 1; k < i; k++)
			if (current == NULL)
				break;
			else current = current->link;
		if (current == NULL && first != NULL)
		{
			cerr << "无效的插入位置!\n";
			return false;
		}
		else
		{
			LinkNode* newNode = new LinkNode(x);
			if (newNode == NULL)
			{
				cerr << "存储分配错误!\n";
				exit(1);
			}
			newNode->link = current->link;
			current->link = newNode;
		}
	}
	return true;
}
LinkNode* List::getFirst()
{
	return first;
}
bool List::Remove(int i, int &x)
{
	// 将链表中的第i个元素删去，i从1开始
	LinkNode *del, *current;
	if (i <= 1)
	{
		del = first;
		first = first->link;
	}
	else
	{
		current = first;
		for (int k = 1; k < i - 1; k++)
		{
			if (current == NULL)break;
			else current = current->link;
		}
		if (current == NULL || current->link == NULL)
		{
			cerr << "无效的删除位置!\n";
			return false;
		}
		del = current->link;
		current->link = del->link;
	}
	x = del->data;
	delete del;
	return true;
}

int List::Length()const
{
	LinkNode *p = first->link;
	int count = 0;
	while (p != NULL)
	{
		p = p->link;
		count++;
	}
	return count;
}
void List::show()
{
	LinkNode *p = first;
	int i = 0;
	while (++i < Length())
	{
		cout << p->data << " ";
	}
}

bool List::RemoveSame()
{
	 int  i = 0;
	 int x;
	 int *Q = new int[maxData + 1]; //  构造辅助Q
	for (i = 0; i < maxData + 1; ++i)
		Q[i] = 0;
	    i = 0;
	LinkNode* p = first; // first 指针不能动!
	int m = p->data;
	while (1)
	{
		if (Q[m] == 0)
			Q[m] = 1;
		else
			Remove(i, x);
		i++;
		if (i == maxData + 1)break;
		cout << "$$" << i;
		p = p->link;
		//m = p->data;
		m = 1;

	}
	delete[] Q;
	return true;
}

int main()
{
	srand(time(NULL));
	int i = 0;
	List p;
	while (i < maxLength)
	{
		int x = rand() % 11;
		p.Insert(0, x);
		i++;
	}
	p.show();

	p.RemoveSame();
	p.show();
	system("pause");
}
