#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

//kmp를 위한 부분문자열마다
// 접두사와 접미사가 같은 최대 길이
//부분 문자열은 인덱스가 마지막 인덱스로 되는 부분문자열으로 인덱스 매핑
// 0 = 0까지 문자열  1 = 0~1문자열   2 = 0~2 문자열
vector<int> getP(string p) {
	int j = 0; //접두사의 추가되는 부분 인덱스
	
	//인덱스 = 부분문자열 마지막 인덱스 일때, 
	//KMP 접미사 = 접두사의 길이를 저장하는 배열
	vector<int> vp(p.size(), 0);
	
	//i는 접미사의 추가되는 부분 인덱스,
	for (int i = 1; i < p.size(); i++) {
	
		//i의 추가되는 인덱스와 j의 추가되는 부분이 다르다면
		//현재까지 찾은 j의 길이중에서
		//접두사와 접미사가 그나마 겹치는 부분부터 시작해본다.
		//끝까지 결국 겹치지 않는다면 j=0이고 
		//처리되지 않는다면 p[i] = 0으로 남게된다.
		while (j > 0 && p[i] != p[j])
			j = vp[j - 1]; //p[j-1]  = j-1인덱스 문자에서 접두사 = 접미사인, 접두사의 길이 = 접두사의 다음 인덱스; 
		
		if (p[i] = p[j]) vp[i] = ++j; // 부분문자열 i에서 같은 길이는 j의 길이이다.
	}
	return vp;
}

//본문 s, 찾을 패턴 p
int sfind(string s, string p) {
	auto vP = getP(p);
	int j = 0; // p의 같은 부분 찾는 인덱스
	//본문 
	for (int i = 0; i < s.size(); i++) {

		//다르다면 접두사 = 접미사인 부분부터 다시 시작한다.
		while (j > 0 && s[i] != p[j])
			j = vP[j - 1];

		//접두사 = 접미사인 길이가 0이고 s[i]와 p[j]가 다르다면 i는 다음 부분으로 넘어간다.
		if (s[i] == p[j]) j++;
		if (j == p.size()) return (i - p.size() + 1);
	}
	return -1;
}

int main() {
	string a = "abcdabcdasd";
	string s = "cda";
	cout << sfind(a, s)<<endl;
}