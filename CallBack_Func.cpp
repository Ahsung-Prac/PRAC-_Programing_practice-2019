#include<iostream>
using namespace std;

//template�� ����Ͽ� �ݹ��Լ� ����
template<class T>
void template_Show(T show) {
	cout << "template!" << endl;
	show();
}

//�Լ������͸� �̿��� �ݹ��Լ� ����
void FucPtr_Show(void (*f)()) {
	cout << "FucPtr!" << endl;
	f();
}

void test_show() {
	cout << "hello!! success Call_back Function!!" << endl;
}

void HW() {
	cout << "hello world!" << endl;
}

int main() {
	template_Show(test_show);
	cout << endl;
	FucPtr_Show(test_show);
	cout << endl; 
	template_Show(HW);
	cout << endl;
	FucPtr_Show(HW);
}


