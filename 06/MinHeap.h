#pragma once
const int DefaultMHSize = 10;
using namespace std;
template<class T>
class MinHeap
{
private:
	T* heap;//存放最小堆中元素的数组
	int currentSize;
	int maxHeapSize;
	void siftDown(int start, int m);
	void siftUp(int start);
public:
	MinHeap(int sz = DefaultMHSize);				//构造函数：建立空堆
	MinHeap(T arr[], int n);					//构造函数：通过一个数组建堆
	~MinHeap()									//析构函数
	{
		delete[]heap;
	}
	bool Insert(T& x);					//将x插入到最小堆中
	bool RemoveMin(T& x);						//删除堆顶上的最小元素
	bool IsEmpty()const
	{
		return (currentSize == 0) ? true : false;		//判堆空否？空返回1，否则返回0
	}
	bool IsFull()const
	{
		return (currentSize == maxHeapSize) ? true : false;		//判堆满否？满则返回1，否则返回0
	}
	void MakeEmpty()							//置空堆
	{
		currentSize = 0;
	}
};

template<class T>
MinHeap<T>::MinHeap(int sz)
{
	maxHeapSize = (DefaultMHSize < sz) ? sz : DefaultMHSize;
	heap = new T[maxHeapSize];					//创建堆存储空间
	if (heap == NULL)
	{
		cerr << "堆存储分配失败！" << endl;
		exit(1);
	}
	currentSize = 0;						//创建当前大小

}
//创建最小堆的构造函数
template<class T>
MinHeap<T>::MinHeap(T arr[], int n)
{
	maxHeapSize = ((DefaultMHSize < n) ? n : DefaultMHSize);
	heap = new T[maxHeapSize];
	if (heap == NULL)
	{
		cerr << "堆存储分配失败！" << endl;
		exit(1);
	}
	for (int i = 0; i < n; i++)				//复制堆数组
		heap[i] = arr[i];
	currentSize = n;						//建立当前大小
	int currentPos = (currentSize - 2) / 2;		//找最初调整位置：最后分支节点
	while (currentPos >= 0)							//自底向上逐步扩大形成堆
	{
		siftDown(currentPos, currentSize - 1);		//局部自上向下下滑调整
		currentPos--;								//再向前换一个分直结点
	}
}
//最小堆的下滑调整算法
//私有函数：从结点start开始到m为止，自上向下比较，如果子女的值小于父结点的值，
//则关键码小的上浮，继续向下层比较，这样将一个集合局部调整为最小堆
template<class T>
void MinHeap<T>::siftDown(int start, int m)
{
	int i = start, j = 2 * i + 1;				//j是i的左子女位置
	T temp = heap[i];
	while (j <= m)									//检查是否到最后位置
	{
		if (j<m && heap[j]>heap[j + 1])	j++;		//让j指向两子女中的小者
		if (temp <= heap[j])		break;			//小则不作调整
		else
		{											//否则小者上移，i，j下降
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}
		heap[i] = temp;								//回放temp中暂存的元素
	}
}
//堆的上滑调整算法
//私有函数：从结点start开始到结点0位置，自下向上比较，如果子女的值小于父结点的值
//则相互交换，这样将集合重新调整为最小堆
template<class T>
void MinHeap<T>::siftUp(int start)
{
	int j = start, i = (j - 1) / 2;
	T temp = heap[j];
	while (j > 0)							//沿父结点路径向上直达根
	{
		if (heap[i] <= temp)	break;		//父结点值小，不调整
		else
		{									//父结点值大，调整
			heap[j] = heap[i];
			j = i;
			i = (i - 1) / 2;
		}
		heap[j] = temp;						//回送
	}
}





//插入算法
//公共函数：将x插入到最小堆中
template<class T>
bool MinHeap<T>::Insert(T& x)
{
	if (currentSize == maxHeapSize)					//堆满
	{
		cerr << "Heap Full" << endl;
		return false;
	}
	heap[currentSize] = x;							//插入
	siftUp(currentSize);							//向上调整
	currentSize++;									//堆计数加1
	return true;
}





//最小堆的删除算法
template<class T>
bool MinHeap<T>::RemoveMin(T& x)
{
	if (currentSize == 0)						//堆空
	{
		cout << "Heap Empty" << endl;
		return false;
	}
	x = heap[0];
	heap[0] = heap[currentSize - 1];			//最后元素填补到根结点
	currentSize--;
	siftDown(0, currentSize - 1);				//自上向下调整为堆
	return true;
}

