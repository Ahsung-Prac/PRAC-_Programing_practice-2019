#include<iostream>
#include<string>
#include<algorithm>
#include<queue>
using namespace std;

//기본 비교클래스.
template<class T>
struct CMP {
	bool operator()(T a,T b) {
		return a > b;
	}
};

// STL클래스 내부에 콜백함수를 넣는 방법
// 직접 Sorted클래스를 구현하여, template을 통해 콜백함수 구현

//Sorted 클래스는 항상 내부의 arr를 오름차순으로 가지고 있다.
// push_back함수를 통해서 arr이 배열에 원소를 삽입한다
// Sorted 선언시 K를 생략하면 default로 CMP클래스를 사용한다.

template<class T, class K=CMP<T>>
struct Sorted
{
	K cmp;
	int size; //현재 가진 원소 개수
	int cap;  //arr배열의 용량
	T * arr;  //삽입정렬해서 원소를 저장해놓은 배열

	//생성자
	Sorted(int cap) {
		this->cap = cap;
		size=0;
		arr = new T[cap];
	}

	//원소 삽입하면서 삽입정렬
	void push_back(T el) {
		if (size == cap) { cout << "용량 끝" << endl; return; }
	
		//마지막 원소부터 검사
		int i = size-1;
		while (i >= 0 && cmp(arr[i],el)) { //CMP클래스의 cmp객체의 operator overloading한 ()연산자로 비교
			arr[i + 1] = arr[i];
			i--;
		}
		//i번쨰 인덱스는 el보다 작거나 큰 원소 or 0보다 작아 while문에서 빠저나옴
		arr[i + 1] = el
		size++;
	}

};
//Sorted 클래스의 cout 출력 << 연산자 오버로딩
template<class T,class K>
ostream &operator<<(ostream &os, Sorted<T,K> sorted) {
	for (int i = 0; i < sorted.size; i++) {
		os << sorted.arr[i] << " ";
	}
	os << endl;
	return os;
}


//Sum 클래스의 대소관계는 sum.a와 sum.b의 합의 크기다.
struct Sum {
	int a;
	int b;
	Sum() { a = 0; b = 0; };
	Sum(int a, int b) :a(a), b(b) {}
	// '>'에 대한 오버로딩 
	bool operator >(Sum b) {
		return this->a + this->b > b.a + b.b;
	}
};
//cout의 Sum을 출력하는 << 연산자 오버로딩
ostream &operator<<(ostream &os, Sum s) {
	os << "a:" << s.a << " b:" << s.b << " ";
	return os;
}

struct CMP_Sum
{
	//"()"연산자 오버로딩, Sum클래스의 대소관계는 a와 b의 합의 크기이다.
	bool operator()(Sum a, Sum b) {
		return a.a + a.b > b.a + b.b;
	}
};

int main() {
	cout << "Sorted 클래스 삽입정렬:\n" << endl;
	Sorted<int> INT(10); //정수형 Sorted default는 CMP클래스의 연산자를 사용
	INT.push_back(55);
	INT.push_back(1);
	INT.push_back(3);
	cout << "INT : " << INT;

	Sorted<string> str(10); //문자형 Sorted default는 CMP클래스의 연산자를 사용
	str.push_back("bca");
	str.push_back("aa");
	str.push_back("ba");
	cout<< "str : "<< str;

	//--------- Sum클래스에 '>'에 대한 연산자가 오버로딩 되어있어야 돌아감 ----------------------------
	Sorted<Sum> sum(10); //sum의 대소관계는 sum.a와 sum.b의 합의 크기다. default는 CMP클래스의 연산자를 사용
	sum.push_back(Sum(3, 4));
	sum.push_back(Sum(5, 3));
	sum.push_back(Sum(1, 2));
	cout << "sum : " << sum;

	//--------- CMP_Sum클래스 안에 "()" 연산자가 오버로딩 되어있어야 돌아감 ----------------------------
	Sorted<Sum, CMP_Sum> sum2(10); //sum2의 대소관계는 sum.a와 sum.b의 합의 크기다. CMP_Sum클래스의 연산자 사용
	sum2.push_back(Sum(6, 4));
	sum2.push_back(Sum(2, 3));
	sum2.push_back(Sum(1, 6));
	cout << "sum2: " << sum2;

	//algoritm header의 sorted도 사용해보기.
	cout << "Sum클래스 algorithm header sort함수로 정렬:\n" << endl;
	CMP_Sum cmp;
	Sum sum_arr[3] = { Sum(6,4),Sum(2,3),Sum(1,6)};
	sort(sum_arr, sum_arr + 3,cmp); //Sorted 클래스에서 오름차순으로 코딩했으면 algorithm의 sort에서는 내림차순으로 정렬됨.
	for (int i = 0; i < 3; i++) {
		cout << i << ": " << sum_arr[i] << endl;
	}

	//STL priority_queue도 사용해보기.
	cout << "Sum클래스 STL의 priority_queue 사용\n" << endl;
	priority_queue<Sum, vector<Sum>, CMP_Sum> sum_pq; //Sorted 클래스에서 오름차순으로 코딩했으면 "최소힙"
	sum_pq.push(Sum(6, 4));
	sum_pq.push(Sum(2, 3));
	sum_pq.push(Sum(1, 6));

	while (!sum_pq.empty()) {
		cout << sum_pq.top() << endl;
		sum_pq.pop();
	}
}