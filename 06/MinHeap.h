#pragma once
const int DefaultMHSize = 10;
using namespace std;
template<class T>
class MinHeap
{
private:
	T* heap;//�����С����Ԫ�ص�����
	int currentSize;
	int maxHeapSize;
	void siftDown(int start, int m);
	void siftUp(int start);
public:
	MinHeap(int sz = DefaultMHSize);				//���캯���������ն�
	MinHeap(T arr[], int n);					//���캯����ͨ��һ�����齨��
	~MinHeap()									//��������
	{
		delete[]heap;
	}
	bool Insert(T& x);					//��x���뵽��С����
	bool RemoveMin(T& x);						//ɾ���Ѷ��ϵ���СԪ��
	bool IsEmpty()const
	{
		return (currentSize == 0) ? true : false;		//�жѿշ񣿿շ���1�����򷵻�0
	}
	bool IsFull()const
	{
		return (currentSize == maxHeapSize) ? true : false;		//�ж��������򷵻�1�����򷵻�0
	}
	void MakeEmpty()							//�ÿն�
	{
		currentSize = 0;
	}
};

template<class T>
MinHeap<T>::MinHeap(int sz)
{
	maxHeapSize = (DefaultMHSize < sz) ? sz : DefaultMHSize;
	heap = new T[maxHeapSize];					//�����Ѵ洢�ռ�
	if (heap == NULL)
	{
		cerr << "�Ѵ洢����ʧ�ܣ�" << endl;
		exit(1);
	}
	currentSize = 0;						//������ǰ��С

}
//������С�ѵĹ��캯��
template<class T>
MinHeap<T>::MinHeap(T arr[], int n)
{
	maxHeapSize = ((DefaultMHSize < n) ? n : DefaultMHSize);
	heap = new T[maxHeapSize];
	if (heap == NULL)
	{
		cerr << "�Ѵ洢����ʧ�ܣ�" << endl;
		exit(1);
	}
	for (int i = 0; i < n; i++)				//���ƶ�����
		heap[i] = arr[i];
	currentSize = n;						//������ǰ��С
	int currentPos = (currentSize - 2) / 2;		//���������λ�ã�����֧�ڵ�
	while (currentPos >= 0)							//�Ե������������γɶ�
	{
		siftDown(currentPos, currentSize - 1);		//�ֲ����������»�����
		currentPos--;								//����ǰ��һ����ֱ���
	}
}
//��С�ѵ��»������㷨
//˽�к������ӽ��start��ʼ��mΪֹ���������±Ƚϣ������Ů��ֵС�ڸ�����ֵ��
//��ؼ���С���ϸ����������²�Ƚϣ�������һ�����Ͼֲ�����Ϊ��С��
template<class T>
void MinHeap<T>::siftDown(int start, int m)
{
	int i = start, j = 2 * i + 1;				//j��i������Ůλ��
	T temp = heap[i];
	while (j <= m)									//����Ƿ����λ��
	{
		if (j<m && heap[j]>heap[j + 1])	j++;		//��jָ������Ů�е�С��
		if (temp <= heap[j])		break;			//С��������
		else
		{											//����С�����ƣ�i��j�½�
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}
		heap[i] = temp;								//�ط�temp���ݴ��Ԫ��
	}
}
//�ѵ��ϻ������㷨
//˽�к������ӽ��start��ʼ�����0λ�ã��������ϱȽϣ������Ů��ֵС�ڸ�����ֵ
//���໥�������������������µ���Ϊ��С��
template<class T>
void MinHeap<T>::siftUp(int start)
{
	int j = start, i = (j - 1) / 2;
	T temp = heap[j];
	while (j > 0)							//�ظ����·������ֱ���
	{
		if (heap[i] <= temp)	break;		//�����ֵС��������
		else
		{									//�����ֵ�󣬵���
			heap[j] = heap[i];
			j = i;
			i = (i - 1) / 2;
		}
		heap[j] = temp;						//����
	}
}





//�����㷨
//������������x���뵽��С����
template<class T>
bool MinHeap<T>::Insert(T& x)
{
	if (currentSize == maxHeapSize)					//����
	{
		cerr << "Heap Full" << endl;
		return false;
	}
	heap[currentSize] = x;							//����
	siftUp(currentSize);							//���ϵ���
	currentSize++;									//�Ѽ�����1
	return true;
}





//��С�ѵ�ɾ���㷨
template<class T>
bool MinHeap<T>::RemoveMin(T& x)
{
	if (currentSize == 0)						//�ѿ�
	{
		cout << "Heap Empty" << endl;
		return false;
	}
	x = heap[0];
	heap[0] = heap[currentSize - 1];			//���Ԫ����������
	currentSize--;
	siftDown(0, currentSize - 1);				//�������µ���Ϊ��
	return true;
}

