#include<iostream>
using namespace std;

bool * PrimeArray;

bool*  Eratos(int n)
{
	if (n <= 1) return NULL;

	bool* PrimeArray = new bool[n + 1];

	for (int i = 2; i <= n; i++)
		PrimeArray[i] = true;

	// i 차례가 왔을때 i*i부터 시작
	// i* (1 . .. i-1)은 예전에 검사했으므로 중복을 피해 최적화 시킴
	//ex)
	// 2  -> 2*3, 2*4 ....
	// 3  -> 3*4 , ....
	// 위에서 2*4, 3*4,를 했으므로 4는 4*4부터 하면되는 이유..

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
	cout << "Erastos 소수 구하기" << endl << "숫자 입력 :";
	cin >> n;

	cout << endl << n << "까지 수소:" << endl;

	PrimeArray = Eratos(n);

	if (!PrimeArray) {cout << "소수 없음" << endl; return 0;
}
	for (int i = 2; i <= n; ++i)
		if (PrimeArray[i]) cout << i << " ";
}