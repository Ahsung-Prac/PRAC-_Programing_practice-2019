#include<iostream>
using namespace std;

template<class T>
void quicksort(T *a, int left, int right) {
	if (left >= right) return;
	int j = left; //�ǹ����� ���� ���ҵ��� �������� ���� ������ �ε���
	T pivot = a[left]; //�ǹ��� ù���ҷ� ����.
	for (int i = left+1; i <= right; i++) {

		//�ǹ����� ���� �༮���� �������� swap�ϸ鼭 �����ش�.
		if (pivot < a[i]) {
			T temp = a[++j];
			a[j] = a[i];
			a[i] = temp;
		}
	}
	// j�� pivot�� ��ȯ�ϸ�
	// pivot �������� �¿찡 pviot���� �۰� ū ���ҷ� ������.
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