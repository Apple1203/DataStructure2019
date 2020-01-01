#include<assert.h>
#include<iostream>
using namespace std;

template <class T>
class LinkNode								//����ڵ���Ķ���
{
public:
	T data;									//������
	LinkNode<T>* link;						//��ָ����
	LinkNode(LinkNode<T>* ptr = NULL)		//����ʼ��ָ���Ա�Ĺ��캯��
	{
		link = ptr;
	}
	LinkNode(const T& item, LinkNode<T>* ptr = NULL)		//��ʼ��������ָ���Ա�Ĺ��캯��
	{
		data = item;
		link = ptr;
	}
};
template<class T>
class LinkedQueue 								//��ʽ���е��ඨ��
{
public:
	LinkedQueue() :rear(NULL), front(NULL)			//���캯���������ն��� 
	{}
	~LinkedQueue()									//��������
	{
		makeEmpty();
	}
	bool EnQueue(const T &x);				//��x���뵽������
	bool DeQueue(T& x);						//ɾ����ͷԪ�أ�ͨ��x������ֵ
	bool getFront(T& x)const;				//�鿴��ͷԪ�ص�ֵ
	LinkNode<T>* getFrontPoint()const		//�õ�ͷָ��
	{
		return front;
	}
	LinkNode<T>* getRearPoint()const		//�õ�βָ��
	{
		return rear;
	}
	void makeEmpty();					//�ÿն���
	bool IsEmpty()const						//�ж��пշ�
	{
		return (front == NULL) ? true : false;
	}
	int getSize()const;					//�����Ԫ�ظ���
	friend ostream& operator<<<>(ostream& os, LinkedQueue<T>& Q);		//�������Ԫ�ص����غ���

protected:
	LinkNode<T>* front, *rear;						//��ͷ��βָ��
};
//����Ԫ��x���뵽���еĶ�β
template<class T>
bool LinkedQueue<T>::EnQueue(const T& x)
{
	if (front == NULL)
	{
		front = rear = new LinkNode<T>(x);			//�ն���ʱ���½���Ϊ���еĵ�һ����㣬���Ƕ�ͷ���Ƕ�β
		if (front == NULL)							//������ʧ��
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





//�ÿն��У��ͷ������е����н��
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



//������в�Ϊ�գ�����ͷ������ʽ������ɾ������������true,���򷵻�false
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



//�����в�Ϊ�գ��������ض�ͷԪ�ص�ֵ��true��������Ϊ�գ���������false
template<class T>
bool LinkedQueue<T>::getFront(T &x)const
{
	if (IsEmpty() == true)
		return false;
	x = front->data;
	return true;
}



//�����Ԫ�صĸ���
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



//�������Ԫ�ص����غ���
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
