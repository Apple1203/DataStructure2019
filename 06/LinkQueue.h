#include<assert.h>
#include<iostream>
using namespace std;

template <class T>
class LinkNode								//链表节点类的定义
{
public:
	T data;									//数据域
	LinkNode<T>* link;						//链指针域
	LinkNode(LinkNode<T>* ptr = NULL)		//仅初始化指针成员的构造函数
	{
		link = ptr;
	}
	LinkNode(const T& item, LinkNode<T>* ptr = NULL)		//初始化数据与指针成员的构造函数
	{
		data = item;
		link = ptr;
	}
};
template<class T>
class LinkedQueue 								//链式队列的类定义
{
public:
	LinkedQueue() :rear(NULL), front(NULL)			//构造函数，建立空队列 
	{}
	~LinkedQueue()									//析构函数
	{
		makeEmpty();
	}
	bool EnQueue(const T &x);				//将x加入到队列中
	bool DeQueue(T& x);						//删除队头元素，通过x返回其值
	bool getFront(T& x)const;				//查看队头元素的值
	LinkNode<T>* getFrontPoint()const		//得到头指针
	{
		return front;
	}
	LinkNode<T>* getRearPoint()const		//得到尾指针
	{
		return rear;
	}
	void makeEmpty();					//置空队列
	bool IsEmpty()const						//判队列空否
	{
		return (front == NULL) ? true : false;
	}
	int getSize()const;					//求队列元素个数
	friend ostream& operator<<<>(ostream& os, LinkedQueue<T>& Q);		//输出队列元素的重载函数

protected:
	LinkNode<T>* front, *rear;						//队头队尾指针
};
//将新元素x插入到队列的队尾
template<class T>
bool LinkedQueue<T>::EnQueue(const T& x)
{
	if (front == NULL)
	{
		front = rear = new LinkNode<T>(x);			//空队列时，新结点成为队列的第一个结点，既是队头又是队尾
		if (front == NULL)							//分配结点失败
			return false;
	}
	else
	{
		rear->link = new LinkNode<T>(x);
		if (rear->link == NULL)
			return false;
		rear = rear->link;
	}
	rear->link = NULL;
	return true;

}





//置空队列，释放链表中的所有结点
template<class T>
void LinkedQueue<T>::makeEmpty()
{
	LinkNode<T> * p;
	while (front != NULL)
	{
		p = front;
		front = front->link;
		delete p;
	}
}



//如果队列不为空，将队头结点从链式队列中删除，函数返回true,否则返回false
template<class T>
bool LinkedQueue<T>::DeQueue(T& x)
{
	if (IsEmpty() == true)
		return false;
	LinkNode<T>* p = front;
	front = front->link;
	x = p->data;
	delete p;
	return true;
}



//若队列不为空，则函数返回队头元素的值及true。若队列为空，则函数返回false
template<class T>
bool LinkedQueue<T>::getFront(T &x)const
{
	if (IsEmpty() == true)
		return false;
	x = front->data;
	return true;
}



//求队列元素的个数
template<class T>
int LinkedQueue<T>::getSize()const
{
	LinkNode* p = front;
	int count = 0;
	while (p != NULL)
	{
		count++;
		p = p->link;
	}
	return count;
}



//输出队列元素的重载函数
template<class T>
ostream& operator<<<>(ostream& os, LinkedQueue<T>& Q)
{
	LinkNode<T>* p = Q.front;
	int i = 0;
	while (p != NULL)
	{
		os << ++i << ":" << p->data << endl;
		p = p->link;
	}
	return os;
}
