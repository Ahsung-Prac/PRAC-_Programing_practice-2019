#include<iostream>
#include<string>
#include<algorithm>
#include<queue>
using namespace std;

//�⺻ ��Ŭ����.
template<class T>
struct CMP {
	bool operator()(T a,T b) {
		return a > b;
	}
};

// STLŬ���� ���ο� �ݹ��Լ��� �ִ� ���
// ���� SortedŬ������ �����Ͽ�, template�� ���� �ݹ��Լ� ����

//Sorted Ŭ������ �׻� ������ arr�� ������������ ������ �ִ�.
// push_back�Լ��� ���ؼ� arr�� �迭�� ���Ҹ� �����Ѵ�
// Sorted ����� K�� �����ϸ� default�� CMPŬ������ ����Ѵ�.

template<class T, class K=CMP<T>>
struct Sorted
{
	K cmp;
	int size; //���� ���� ���� ����
	int cap;  //arr�迭�� �뷮
	T * arr;  //���������ؼ� ���Ҹ� �����س��� �迭

	//������
	Sorted(int cap) {
		this->cap = cap;
		size=0;
		arr = new T[cap];
	}

	//���� �����ϸ鼭 ��������
	void push_back(T el) {
		if (size == cap) { cout << "�뷮 ��" << endl; return; }
	
		//������ ���Һ��� �˻�
		int i = size-1;
		while (i >= 0 && cmp(arr[i],el)) { //CMPŬ������ cmp��ü�� operator overloading�� ()�����ڷ� ��
			arr[i + 1] = arr[i];
			i--;
		}
		//i���� �ε����� el���� �۰ų� ū ���� or 0���� �۾� while������ ��������
		arr[i + 1] = el
		size++;
	}

};
//Sorted Ŭ������ cout ��� << ������ �����ε�
template<class T,class K>
ostream &operator<<(ostream &os, Sorted<T,K> sorted) {
	for (int i = 0; i < sorted.size; i++) {
		os << sorted.arr[i] << " ";
	}
	os << endl;
	return os;
}


//Sum Ŭ������ ��Ұ���� sum.a�� sum.b�� ���� ũ���.
struct Sum {
	int a;
	int b;
	Sum() { a = 0; b = 0; };
	Sum(int a, int b) :a(a), b(b) {}
	// '>'�� ���� �����ε� 
	bool operator >(Sum b) {
		return this->a + this->b > b.a + b.b;
	}
};
//cout�� Sum�� ����ϴ� << ������ �����ε�
ostream &operator<<(ostream &os, Sum s) {
	os << "a:" << s.a << " b:" << s.b << " ";
	return os;
}

struct CMP_Sum
{
	//"()"������ �����ε�, SumŬ������ ��Ұ���� a�� b�� ���� ũ���̴�.
	bool operator()(Sum a, Sum b) {
		return a.a + a.b > b.a + b.b;
	}
};

int main() {
	cout << "Sorted Ŭ���� ��������:\n" << endl;
	Sorted<int> INT(10); //������ Sorted default�� CMPŬ������ �����ڸ� ���
	INT.push_back(55);
	INT.push_back(1);
	INT.push_back(3);
	cout << "INT : " << INT;

	Sorted<string> str(10); //������ Sorted default�� CMPŬ������ �����ڸ� ���
	str.push_back("bca");
	str.push_back("aa");
	str.push_back("ba");
	cout<< "str : "<< str;

	//--------- SumŬ������ '>'�� ���� �����ڰ� �����ε� �Ǿ��־�� ���ư� ----------------------------
	Sorted<Sum> sum(10); //sum�� ��Ұ���� sum.a�� sum.b�� ���� ũ���. default�� CMPŬ������ �����ڸ� ���
	sum.push_back(Sum(3, 4));
	sum.push_back(Sum(5, 3));
	sum.push_back(Sum(1, 2));
	cout << "sum : " << sum;

	//--------- CMP_SumŬ���� �ȿ� "()" �����ڰ� �����ε� �Ǿ��־�� ���ư� ----------------------------
	Sorted<Sum, CMP_Sum> sum2(10); //sum2�� ��Ұ���� sum.a�� sum.b�� ���� ũ���. CMP_SumŬ������ ������ ���
	sum2.push_back(Sum(6, 4));
	sum2.push_back(Sum(2, 3));
	sum2.push_back(Sum(1, 6));
	cout << "sum2: " << sum2;

	//algoritm header�� sorted�� ����غ���.
	cout << "SumŬ���� algorithm header sort�Լ��� ����:\n" << endl;
	CMP_Sum cmp;
	Sum sum_arr[3] = { Sum(6,4),Sum(2,3),Sum(1,6)};
	sort(sum_arr, sum_arr + 3,cmp); //Sorted Ŭ�������� ������������ �ڵ������� algorithm�� sort������ ������������ ���ĵ�.
	for (int i = 0; i < 3; i++) {
		cout << i << ": " << sum_arr[i] << endl;
	}

	//STL priority_queue�� ����غ���.
	cout << "SumŬ���� STL�� priority_queue ���\n" << endl;
	priority_queue<Sum, vector<Sum>, CMP_Sum> sum_pq; //Sorted Ŭ�������� ������������ �ڵ������� "�ּ���"
	sum_pq.push(Sum(6, 4));
	sum_pq.push(Sum(2, 3));
	sum_pq.push(Sum(1, 6));

	while (!sum_pq.empty()) {
		cout << sum_pq.top() << endl;
		sum_pq.pop();
	}
}