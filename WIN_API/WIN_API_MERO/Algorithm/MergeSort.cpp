#include <queue>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

// Merge Sort (�� ���̸�)
// - �˰��� �з����� : ���� ����
// - �ð����⵵ : n x logn
// - ���� : ���� ���� ������ �� �տ� �ִ� ���� �׻� ���� ������ �����Ѵ�.
// - ���� : �ӽù迭�� ���� ������ ���.

void MergeResult(vector<int>& v, int left, int mid, int right)
{
	// ó�� �� �Լ��� ȣ����� ���� ���� �۰� �ɰ����ִ� ����
	int leftIndex = left;
	int rightIndex = mid + 1;

	// �ӽð�
	vector<int> temp;

	// [3]   [4]
	// l,m      r
	// temp : 
	while (true)
	{
		if(leftIndex > mid || rightIndex > right)
			break;

		if (v[leftIndex] <= v[rightIndex])
		{
			temp.push_back(v[leftIndex]);
			leftIndex++;
		}
		else
		{
			temp.push_back(v[rightIndex]);
			rightIndex++;
		}
	}

	// [3]   [4]
	//  m    l,r
	// temp : 3

	// ���ʿ� �ִ� ���ҵ��� temp�� �� ���簡 �Ǿ���.
	// right�ʿ� �ִ� �迭���� �����ִ�.
	if (leftIndex > mid)
	{
		while (rightIndex <= right)
		{
			temp.push_back(v[rightIndex]);
			rightIndex++;
		}
	}
	// left�ʿ� �ִ� �迭���� �����ִ�.
	else
	{
		while (leftIndex <= mid)
		{
			temp.push_back(v[leftIndex]);
			leftIndex++;
		}
	}

	// temp�� left�ʰ� right�� �迭�� �����ؼ� ��ģ ����
	for (int i = 0; i < temp.size(); i++)
	{
		v[left + i] = temp[i];
	}
}

void MergeSort(vector<int>& v, int left, int right)
{
	// ��������
	if(left >= right)
		return;

	int mid = (left + right) / 2;

	// Divide
	MergeSort(v, left, mid);
	MergeSort(v, mid + 1, right);

	// Conquer
	MergeResult(v, left, mid, right);
}

int main()
{
	vector<int> v = { 55,30,15,100,1,5,70 };

	// ���� ����(Divide And Conquer)

	MergeSort(v, 0, v.size() - 1);

	return 0;
}