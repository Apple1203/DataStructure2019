/*
	第三章作业
	问题描述:算术表达式有三种形式。一般的，算术表达式采用中缀表达形式，利用栈，可以将中缀表达式
			转换为后缀表达式/前缀表达式。编写程序，完成实验要求。
	测试数据如下：
	第一组：A+B*(C-D)-E/F
	第二组：(A+B)*D+E/(F+A*D)+C
	练习要求：
			1.从文件中读取一个算术表达式字符串
			2.根据运算符的优先级，利用顺序栈或者链式栈，实现中缀表示转换为后缀表示的算法。
			3.根据运算符的优先级，利用顺序栈或者链式栈，实现中缀表示转换为前缀表示的算法。
*/
#include<iostream>
#include<stack>
#include<fstream>
#include<assert.h>
#define maxLen 30
using namespace std;

template <class T>
class LinkNode  //结点类定义
{
public:
	T data;
	LinkNode<T> * link;
	LinkNode<T>(const T&x, LinkNode<T> *p) { data = x; link = p; }
};

template <class T>

class LinkedStack 
{
public:
	LinkedStack() :top(NULL) {}
	~LinkedStack() { makeEmpty(); }
	void Push(const T& x);
	bool getTop(T& x)const;
	bool Pop(T& x);
	bool isEmpty()const { return top == NULL ? true : false; }
	int getSize()const;
	void makeEmpty();
	friend ostream& operator << (ostream& os, LinkedStack<T>& s);
private:
	LinkNode<T> *top;
};
template <class T>

void LinkedStack<T>::makeEmpty()
{
	// 逐次删去链式栈中的元素直至栈顶指针为空
	LinkNode<T> *p;
	while (top != NULL)
	{
		p = top; top = top->link; delete p;
	}
}
template <class T>
void LinkedStack<T>::Push(const T& x)
{
	top = new LinkNode<T>(x, top);
	assert(top != NULL);
}
template <class T>
bool LinkedStack<T>::Pop(T& x)
{
	if (isEmpty() == true)return false;
	LinkNode<T> *p = top;
	top = top->link;
	x = p->data; delete p;
	return true;
}
template <class T>
ostream& operator <<(ostream& os, LinkedStack<T>& s)
{
	os << "栈中元素个数 = " << s.getSize() << endl;
	LinkNode<T>* p = s.top; int i = 0;
	while (p != NULL)
		os << ++i << ":" << p->data << endl;
	return os;
}
template <class T>
bool LinkedStack<T>::getTop(T& x)const
{
	if (isEmpty() == true)return false;
	x = top->data;
	return true;
}
template <class T>
int LinkedStack<T>::getSize() const
{
	LinkNode<T> * p = top;
	int k = 0;
	while (top != NULL) { top = top->link; k++; }
	return k;
}
int ispb(char c)
{ 
		switch (c)
		{
		case'#':return 0; break;
		case '+':case '-':return 3;break;
		case '*':case '/':case '%':return 5;break;
		case '(':return 1; break;
		case ')':return 6; break;
		}
}//后缀的优先级

int icpb(char c)
{
	switch (c)
	{
	case'#':return 0; break;
	case '+':case '-':return 2; break;
	case '*':case '/':case '%':return 4; break;
	case '(':return 6; break;
	case ')':return 1; break;
	}
}//后缀的优先级
int ispp(char c)
{
	switch (c)
	{
	case'#':return 0; break;
	case '+':case '-':return 3; break;
	case '*':case '/':case '%':return 5; break;
	case '(':return 6; break;
	case ')':return 1; break;
	}

}

int icpp(char c)
{
	switch (c)
	{
	case'#':return 0; break;
	case '+':case '-':return 3; break;
	case '*':case '/':case '%':return 5; break;
	case '(':return 1; break;
	case ')':return 6; break;
	}

}

int main()
{
	LinkedStack<char> s;
	char ch = '#', ch1[maxLen],ch2,op;
	s.Push(ch);
	fstream os;
	os.open("D:\\data1.txt", ios::in);
	if (os.is_open())
	{
		os.getline(ch1, maxLen);

		int i = 0;
		while (s.isEmpty() == false)
		{
			if (isdigit(ch1[i])) { cout << ch1[i]; i++; }
			else
			{
				s.getTop(ch2);
				if (ispb(ch2) < icpb(ch1[i]))
				{
					s.Push(ch1[i]); i++;
				}
				else if (ispb(ch2) > icpb(ch1[i]))
				{
					s.Pop(op);  cout << op;
				}
				else
				{
					s.Pop(op);
					if (op == '(')
						i++;
					if (ch1[i] == '#')
						break;
				}

			}

		}
	}
	os.close();
	os.clear();
	std::cout << endl;
	int  j = 0, k = 0;
	LinkedStack<char>  s1,s2;//运算符栈S1和储存中间结果的栈S2
	char ch3[maxLen];
	fstream oss;
	oss.open("D:\\data2.txt", ios::in);
	if (oss.is_open())
	{
		oss.getline(ch3, maxLen);
			for (k=0; ch3[k] != '#'; k++);//定位到最后一位
			k --;
			while(k > 0||k==0)
			{
				if (isdigit(ch3[k])) { s2.Push(ch3[k]); k--; }
				else 
				{
					if (s1.isEmpty()||ch3[k]==')' ) { s1.Push(ch3[k]); k--;  }
					else
					{
						s1.getTop(op);
						if (ch3[k] != '(')
						{
							if (icpp(ch3[k]) > ispp(op) || icpp(ch3[k]) == ispp(op))
							{
								s1.Push(ch3[k]); k--;
							}
							else
							{
								s1.Pop(op); s2.Push(op);
							}
						}
						else 
						{
							s1.getTop(op);
							if (op != ')')
							{
								s1.Pop(op); s2.Push(op); 
							}
							else
							{
								s1.Pop(op); k--;
							}
						}
					}
				}
			}
			while (k < 0)
			{
				s1.Pop(op); s2.Push(op);
				if (s1.isEmpty())
					break;
			}
			while (!s2.isEmpty())
			{
				s2.Pop(op); 
				if(op!='('&&op!=')')std::cout << op;
			}
			
	}
	oss.close();
	oss.clear();
	std::system("pause");
}
