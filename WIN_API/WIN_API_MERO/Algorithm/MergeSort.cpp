#include <queue>
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

// Merge Sort (폰 노이만)
// - 알고리즘 패러다임 : 분할 정복
// - 시간복잡도 : n x logn
// - 장점 : 같은 값을 가졌을 때 앞에 있던 값이 항상 같은 순서를 유지한다.
// - 단점 : 임시배열을 만들어서 복사비용 든다.

void MergeResult(vector<int>& v, int left, int mid, int right)
{
	// 처음 이 함수가 호출됬을 때는 제일 작게 쪼개져있는 상태
	int leftIndex = left;
	int rightIndex = mid + 1;

	// 임시값
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

	// 왼쪽에 있던 원소들이 temp에 다 복사가 되었다.
	// right쪽에 있는 배열들이 남아있다.
	if (leftIndex > mid)
	{
		while (rightIndex <= right)
		{
			temp.push_back(v[rightIndex]);
			rightIndex++;
		}
	}
	// left쪽에 있는 배열들이 남아있다.
	else
	{
		while (leftIndex <= mid)
		{
			temp.push_back(v[leftIndex]);
			leftIndex++;
		}
	}

	// temp는 left쪽과 right쪽 배열을 정렬해서 합친 상태
	for (int i = 0; i < temp.size(); i++)
	{
		v[left + i] = temp[i];
	}
}

void MergeSort(vector<int>& v, int left, int right)
{
	// 기저사항
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

	// 분할 정복(Divide And Conquer)

	MergeSort(v, 0, v.size() - 1);

	return 0;
}