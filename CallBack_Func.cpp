#include<iostream>
using namespace std;

//template을 사용하여 콜백함수 구현
template<class T>
void template_Show(T show) {
	cout << "template!" << endl;
	show();
}

//함수포인터를 이용한 콜백함수 구현
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


