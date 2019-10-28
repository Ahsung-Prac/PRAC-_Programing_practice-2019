#include<iostream>
using namespace std;

template<class T>
void quicksort(T *a, int left, int right) {
	if (left >= right) return;
	int j = left; //피벗보다 작은 원소들이 왼쪽으로 모인 마지막 인덱스
	T pivot = a[left]; //피벗은 첫원소로 시작.
	for (int i = left+1; i <= right; i++) {

		//피벗보다 작은 녀석들을 왼쪽으로 swap하면서 몰아준다.
		if (pivot < a[i]) {
			T temp = a[++j];
			a[j] = a[i];
			a[i] = temp;
		}
	}
	// j를 pivot과 교환하면
	// pivot 기준으로 좌우가 pviot보다 작고 큰 원소로 나뉜다.
	T temp = a[left];
	a[left] = a[j];
	a[j] = temp;
	quicksort(a, left, j - 1);
	quicksort(a, j + 1, right);
}

int main() {
	int a[10] = {4,5,9,1,2,5,8,3,6,0};

	quicksort(a, 0, 9);
	for (auto n : a) {
		cout << n << " ";
	}
}