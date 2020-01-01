/*
选做任务：
问题描述：
Fibonacci数列是一个有趣的计算兔子繁殖规律的古典数学问题。即Fibonacci数列是1，1，2，3，5，8.....
编写程序计算Fibonacci数列第n项的值
实验要求：
1.实现计算[m,n]之间Fibonacci数列值的算法
2.分别利用递归法和迭代法实现，输出两种算法的每次实验结果
3.记录至少8次实验测试结果，假设n的取值分别为{10，15，20，25，30，35，40，41，42，43，44，45}
4.利用标准clock()函数，测试两种算法每次运行的时间
示例输出：
时间开销的计算方法：(double)(stop-start)/CLK_TCK
补充实验要求：测验当前使用的计算机的最大可计算的Fibonacci数列的项数。
*/
#pragma once
#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
#define M 12
long Fib_Recursion(int n)			//递归法求Fibonacci数列
{
	if (n == 2 || n == 1)
		return 1;
	else
		return Fib_Recursion(n - 1) + Fib_Recursion(n - 2);
}
long Fib_Iteration(int n)			//迭代法求Fibonacci数列
{
	int f1 = 1, f2 = 1, f3;
	if (n == 1 || n == 2)
		return 1;
	else
	{
		for (int i = 3; i <= n; i++)
		{
			f3 = f2 + f1;
			f1 = f2;
			f2 = f3;
		}
		return f3;
	}

}
void Func()
{
	int i;
	long fib_item;
	int item[M] = { 10,15,20,25,30,35,40,41,42,43,44,45 };
	clock_t start, stop;   
	double duration;
	cout << "n will be { 10,15,20,25,30,35,40,41,42,43,44,45 }\n";
	cout << endl;
	cout << "with recursion\n";
	for (i = 0; i < M; i++)
	{
		start = clock();
		fib_item = Fib_Iteration(item[i]);
		stop = clock();
		duration = ((double)(stop - start)) / CLK_TCK;
		cout << "Fib(" << item[i] << ") = " << fib_item <<"     "
			<< "time consuming:" << duration << endl;
	}
	cout << "-------------------" << endl;
	cout << "-------------------" << endl;
	cout << "with iteration\n";
	for (i = 0; i < M; i++)
	{
		start = clock();
		fib_item = Fib_Recursion(item[i]);
		stop = clock();
		duration = ((double)(stop - start)) / CLK_TCK;
		cout << "Fib(" << item[i] << ") = " << fib_item << "     "
			<< "time consuming:" << duration << endl;
	}
}
int main()
{
	Func();
	system("pause");
}
