#pragma once
#define DefaultSize 10
class UFSets
{
public:
	UFSets(int sz = DefaultSize);
	~UFSets() { delete[] parent; }
	void Union(int Root1, int Root2);	//�����Ӽ��Ϻϲ�
	int Find(int x);	//��Ѱ����x�ĸ�
	void WeightedUnion(int Root1, int Root2);	//��Ȩ�ĺϲ��㷨
private:
	int *parent;
	int size;
};
UFSets::UFSets(int sz)
{
	//s�Ǽ���Ԫ�ظ�������ָ������ķ�ΧΪparent[0]~parent[size-1]
	size = sz;
	parent = new int[size];
	for (int i = 0; i < size; i++)
		parent[i] = -1;
}
int UFSets::Find(int x)
{
	//���������ذ���Ԫ��x�����ĸ�
	while (parent[x] >= 0) x = parent[x];
	return x;
}
void UFSets::Union(int Root1, int Root2)
{
	//���������ཻ���ϵĲ���
	parent[Root1] += parent[Root2];
	parent[Root2] = Root1;
}
void UFSets::WeightedUnion(int Root1, int Root2)
{
	int r1 = Find(Root1);
	int r2 = Find(Root2);
	int temp;
	if (r1 != r2)
	{
		temp = parent[r1] + parent[r2];
		if (parent[r2] < parent[r1])
		{
			parent[r1] = r2; parent[r2] = temp;
		}
		else { parent[r2] = r1; parent[r1] = temp; }
	}
}

