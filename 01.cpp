/*
第一章作业
问题描述：利用计算机进行数值计算时，需考虑到计算机可表示的最大数值范围。
编写程序，计算 k!*2^n 的值
练习要求：
1.确定当前计算机整数数值范围内可支持计算的最大值maxInt
2.编写计算m!的算法，当(m+1)!>maxInt时输出m和m!的结果值
3.编写计算2^n的算法，当2^(n+1)>maxInt时输出n和2^n的结果值
4.若k的取值为[0,k],实现计算k!*2^k的算法，设置数组T[n]存放计算结果，当(k+1)!*2^(k+1)>maxInt时
按照每行10个值的格式，输出k!*2^k的计算结果
*/
#include <iostream>
#include<cmath>
#define n 100
#define maxInt 0x7fffffff
using namespace std;
bool calfac(int A[], int m)    // 计算m!的算法
{
	int i, value = 1;
	if (m != 0)
	{
		for (i = 1; i <= m; ++i)
		{
			value *= i;
			A[0] = value;
			if (value > maxInt / (m+1))
				return false;
		}
	}
	return true;
}
bool calpow(int B[], int m) // 计算 2 ^ n 的算法
{
	int i, value = 1;
	if (m != 0)
	{
		for (i = 1; i <= m; ++i)
		{
			value *= 2;
			B[0] = value;
			if (value > maxInt / 2)
				return false;
		}
	}
	return true;
}
bool calfac_pow(int T[], int m)    // 计算m ! * 2 ^ m
{
	int i, value = 1;
	T[0] = value;
	if (m != 0)
	{
		for (i = 1; i < m; ++i)
		{
			
			value *= i * 2;
			T[i] = value;
			if (value > maxInt / m / 2)
				return false;
		}
	}
	return true;
}

int main()
{
	int T[n], i, j, k, p;
	for (k = 0; k < n; ++k)
	{
		if (!calfac(T, k))
		{
			cout << k << endl;
			cout << T[0] << endl;
			break;
		}
	}
	for (p = 0; p < n; ++p)
	{
		if (!calpow(T, p))
		{
			cout << p << endl;
			cout << T[0] << endl;
			break;
		}
	}
	for (i = 0; i < n; i++)
	{
		if(!calfac_pow(T, i))
		{
			cout << i << endl;
			break;
		}
	}
	int count = 0;
	for (j = 0; j < i; ++j)
	{
		cout << T[j] << " ";
		count++;
		if (count % 10 == 0)
			cout << endl;
	}
		system("pause");
}
