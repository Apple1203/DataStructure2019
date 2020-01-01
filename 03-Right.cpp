// 1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"


/*
第二章作业

问题描述：
用单链表保存m个整数，结点的结构如下图所示
-----------------------------
|	data	  |		link	|
-----------------------------
且|data|<= n，n为正整数。设计一个时间复杂度尽可能低的算法，对于链表中data的绝对值相等
的结点，仅保留第一次出现的结点而删除其余绝对值相等的结点。

练习要求：
编写去重算法，删除链表中绝对值重复的结点

提示：
线性时间复杂度的去重算法思路：利用辅助数组Q记录已出现的数值，Q的大小为n+1，Q数组元素
初始值为0，依次遍历链表结点，同时检查Q[|data|]的值，如果为0，则保留该节点且Q[|data|]=1；
否则将该节点从链表中删除。
*/



/*
我自己学习的一点经验：
1、多练习，切忌眼高手低。不要找一本很厚的书，从头看到尾，只学理论；
2、遇到错误可以尝试自己调试一下，代码报错的地方不一定是真正有错误的地方，
   可能是其它地方的影响；
3、也可以多看看其它大神写的代码，他们的逻辑、代码习惯都很好。Github上有很多好项目，跟着他们做，先读懂代码，然后自己实现；
4、同班同学也有很多代码写的不错的地方，遇到错误可以问问他们，但是找bug确实是一件很耗时的事情。
PS：起步总是痛苦的，多做做，习惯了就好啦。
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
	LinkNode * link;
	LinkNode(int &x);
};

class List
{
private:
	LinkNode * first;
public:
	bool Insert(int i, int & x); // 插入算法
	bool Remove(LinkNode* p, int & x); // 删除算法
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
	link = NULL;
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
bool List::Remove(LinkNode* p, int &x)
{
	// 将链表中的第i个元素删去，i从1开始
	LinkNode *del, *current;
	//不可能删除第一个元素的
	if (p->link == NULL)
	{
		return true;
	}
	else
	{ 
		current = p->link;      //要删除的是p后面的元素
		p->link = current->link;
	}
	x = current->data;
	delete current;
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
	int len = Length();
	while (p)            //链表可以不知道长度，直接判断指针是否为空就可以了
	{
		cout << p->data << " ";
		p = p->link;   //这个地方出错，指针要不断后移才能输出所有结果
	}
	cout << endl;
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
	LinkNode* q = p->link;
	Q[p->data] = 1;
	int m = q->data;
	while (1)                 //控制链表退出循环可以直接检测指针的情况             
	{
		if (Q[m] == 0)
		{
			Q[m] = 1;
			q = q->link;
			p = p->link;
	    }
		else
		{
			q = q->link;
			Remove(p, x);            //这个地方原来也不对，remove前面的元素之后，后面的元素依次前移，就不再是在第i个位置了，可以直接传递指针
		}
		i++;
		if (q)
		{
			m = q->data;
		}
		else
		{
			delete[] Q;
			return true;
		}
			
		
	}
	
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
