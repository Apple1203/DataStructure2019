// Hashtable
#include<assert.h>
#include<iostream>
#include<cmath>
using namespace std;
const int defaultSize = 100;

bool isPrime(int n)
{
	int i;
	for (i = 0; i<=int(sqrt(n)); i++)
		if (n % i == 0)return false;
	return true;
}

template<class E,class K>
struct ChainNode
{
	E data;
	ChainNode<E, K> *link;
};

template<class E, class K>
class HashTable
{
private:
	int divisor; //除数 质数
	int TableSize; //容量 桶的个数
	int keyNum; // 关键码
	ChainNode<E, K>** ht;//散列表定义
	ChainNode<E, K>* FindPos(const K k1);//散列
public:
	HashTable(int d);
	~HashTable() { delete[] ht; }
	void Insert(E key);
	double ASLsucc();
	double ASLunsucc();
};
template<class E, class K>
HashTable<E, K>::HashTable(int d)
{
	// if (!isPrime(d)) { cout << "不是质数！" << endl; }
	divisor = d;
	TableSize = d + 1;
	keyNum = 0;
	ht = new ChainNode<E, K> *[TableSize];
	assert(ht != NULL);
	for (int i = 0; i < TableSize; i++)ht[i] = NULL;
}
template<class E, class K>
ChainNode<E, K>* HashTable<E, K>::FindPos(const K k1)
{
	int j = k1 % divisor;
	ChainNode<E, K> *p = ht[j];
	while (p != NULL && p->data != k1)p = p->link;
	return p;
}
template<class E, class K>
double HashTable<E, K>::ASLsucc()
{
	int i, j;
	int sum = 0;
	ChainNode<E,K> *temp;
	for (i = 0; i < divisor; i++)
	{
		temp = ht[i];
		j = 0;
		while (temp != NULL)
		{
			temp = temp->link;
			j++;
			sum += j;
		}
	}
	return 1.0*sum / keyNum;
}
template<class E, class K>
void HashTable<E, K>::Insert(E key)
{
	int j = key % divisor;
	ChainNode<E, K>* temp = FindPos(key);
	if (temp != NULL)
	{
		cout << key << "值已经存在." << endl;
	}
	else
	{
		ChainNode<E, K>* newPtr = new ChainNode<E, K>[key];
		newPtr->link = ht[j];
		ht[j] = newPtr;
		keyNum++;
	}

}
template<class E, class K>
double HashTable<E, K>::ASLunsucc()
{
	int i, j;
	int sum = 0;
	ChainNode<E, K> *temp;
	for (i = 0; i < divisor; i++)
	{
		temp = ht[i];
		j = 1;
		sum += j;
		if (temp != NULL)
		{
			while (temp != NULL)
			{
				temp = temp->link;
				j++;
			}
			sum += j;
		}
	}
	return 1.0*sum / divisor;
}
int main()
{
	int i, prime;
	const int n[3] = { 10,20,50 };
	int * str = NULL;
	cout << "从5，7，11，19中选择一个数输进去";
	cin >> prime;
	for (int j = 0; j < 3; j++)
	{
		str = new int[n[j]];
		if (str == NULL)cout << "空间分配失败" << endl, exit(1);
		cout << "得到的关键码为：";
		for (i = 0; i < n[j]; i++)
		{
			str[i] = 1 + rand() % 1000;
			cout << str[i] << ' ';
		}
		cout << endl;

		HashTable<int,int> HT(prime);
		for (i = 0; i < n[j]; i++)
			HT.Insert(str[i]);
		cout << "ASLsucc:" << HT.ASLsucc() << endl;
		cout << "ASLunsucc:" << HT.ASLunsucc() << endl;
		delete[] str;
	}
	system("pause");
}
