/*
	飞机场中飞机的升降问题
*/
#include<iostream>
#include<ctime>
#include<queue>
#define maxLen 30
using namespace std;

class aeroplane
{
private:
	int Hour,Min;// 代表起飞或下降的时刻
	bool isFlight;// 代表飞机将要起飞或者下降
public:
	aeroplane(int hour, int min,  bool isflight) { Hour = hour, Min = min,  isFlight = isflight; }
	int getTime() { return Hour * 60 + Min; }
	int getHour() { return Hour; }
	int getMin() { return Min; }

	bool getFlight(){ return isFlight; }
	aeroplane(aeroplane& x) { Hour = x.getHour(), Min = x.getMin(),  isFlight = x.getFlight(); }
	aeroplane() { Hour = rand() % 25; Min = rand() % 61;  isFlight = rand() % 2; }
};

void mySwap(aeroplane *a, aeroplane *b)
{
	aeroplane temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int main()
{
	cout << "欢迎来到阿明的飞机场！" << endl;
	srand(time(0));
	int i;
	int time = 0;
	int count = 0; // a counter
	int cTotal = rand() % 100; // 总飞机数
	int currentTime;
	cout << "有" << cTotal << "架飞机要处理" << endl;
	aeroplane *m = new aeroplane[cTotal];
	int hour, min;
	cout << "时间计时：" << 0 << "时" << 0 << "分，机场开启" << endl;
	queue<aeroplane *>plane;
	queue<aeroplane *>airway;
	for (i = 0; i < cTotal-1; i++)
	{
		for (int j = cTotal - 2; j >= 0; j--)
		{
			if (m[j].getTime() > m[j + 1].getTime())
				mySwap(&m[j], &m[j + 1]);
		}
	}
	for (i = 0; i < cTotal; i++)
		plane.push(&m[i]);		//	plane存放了所有飞机的请求
	for (i = 0; i < cTotal; i++)
	{
		
		count++;
		if (count > 10)break;
		aeroplane *currentPlane=plane.front();
		if (airway.empty())
		{
			// aeroplane *currentPlane = &m[0];
			airway.push(currentPlane);		// 有飞机请求起飞/降落
			bool flight = currentPlane->getFlight();
			hour = currentPlane->getTime() / 60;
			min = currentPlane->getTime() - hour * 60;
			cout << "时间计时：" << hour << "时"
				<< min << "分  "
				<< count << "号飞机请求";
			flight == 1 ? cout << "起飞" : cout << "降落";
			currentTime = currentPlane->getTime();
			flight == 1 ? time = 5 : time = 3;
			currentTime += time;
			cout << endl;
			plane.pop();
		}
		else
		{
			if (currentTime > 1440 || currentTime == 1440)break;
			if (currentPlane->getTime() < currentTime)
			{
				bool flight = currentPlane->getFlight();
				hour = currentPlane->getTime() / 60;
				min = currentPlane->getTime() - hour * 60;
				cout << "时间计时：" << hour << "时" 
					<< min << "分  "
					<< count << "号飞机请求";
				flight == 1 ? cout << "起飞" : cout << "降落";
				cout << endl;
				cout << "跑道满了！等会！" << endl;
				hour = currentTime / 60;
				min = currentTime - hour * 60;
				cout << "时间计时：" << hour << "时"
					<< min << "分  "<< count  << "号飞机请求";
				flight == 1 ? cout << "起飞" : cout << "降落";
				cout << endl;
				currentPlane->getFlight() == 1 ? time = 5 : time = 3;
				airway.push(currentPlane);
				currentTime = currentPlane->getTime();
				currentTime += time;
				plane.pop();
				if (currentTime  > 1440 || currentTime  == 1440)break;
			}
			else
			{
				bool flight = currentPlane->getFlight();
				hour = currentPlane->getTime() / 60;
				min = currentPlane->getTime() - hour * 60;
				cout << "时间计时：" << hour << "时"<< min << "分  "
					<< count << "号飞机请求";
				flight == 1 ? cout << "起飞" : cout << "降落";
				cout << endl;
				currentPlane->getFlight() == 1 ? time = 5 : time = 3;
				airway.push(currentPlane);
				currentTime = currentPlane->getTime();
				currentTime += time;
				plane.pop();
				if (currentTime > 1440 || currentTime == 1440)break;
			}
		}
	}
	cout << "今日份航线已关闭！共处理" << count - 1 << "次飞机的起落，明天见！";
	system("pause");
}
