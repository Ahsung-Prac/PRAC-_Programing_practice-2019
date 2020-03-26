#include<iostream>
using namespace std;

bool * PrimeArray;

bool*  Eratos(int n)
{
	if (n <= 1) return NULL;

	bool* PrimeArray = new bool[n + 1];

	for (int i = 2; i <= n; i++)
		PrimeArray[i] = true;

	// i ���ʰ� ������ i*i���� ����
	// i* (1 . .. i-1)�� ������ �˻������Ƿ� �ߺ��� ���� ����ȭ ��Ŵ
	//ex)
	// 2  -> 2*3, 2*4 ....
	// 3  -> 3*4 , ....
	// ������ 2*4, 3*4,�� �����Ƿ� 4�� 4*4���� �ϸ�Ǵ� ����..

	for (int i = 2; i * i <= n; i++)
	{
		if (PrimeArray[i])
			for (int j = i * i; j <= n; j += i)
				PrimeArray[j] = false;
	}

	return PrimeArray;
}

int main() {
	int n;
	cout << "Erastos �Ҽ� ���ϱ�" << endl << "���� �Է� :";
	cin >> n;

	cout << endl << n << "���� ����:" << endl;

	PrimeArray = Eratos(n);

	if (!PrimeArray) {cout << "�Ҽ� ����" << endl; return 0;
}
	for (int i = 2; i <= n; ++i)
		if (PrimeArray[i]) cout << i << " ";
}