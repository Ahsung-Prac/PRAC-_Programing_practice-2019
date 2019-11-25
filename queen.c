#include<stdio.h>
#include<stdlib.h>


int soluNum = 0; //총 해답수
int *cal;        //column 배열!  
int n;		 // queens의 체스판 행(열)의 수


//promising 한지 검사.
int promising(int index) {
	int Sw = 1;
	int i;
	// 이전 행들과 column이 같지 않고 대각선에 겹치지 않는지 검사
	for (i = 0; i < index;i++) {
		if ((cal[i] == cal[index]) || (abs(cal[i] - cal[index]) == abs(i - index)))
		{	Sw = 0; //겹치다면 0 리턴
			break;
		}
	}
	return Sw;
}

// nQueens 백트래킹 실행!!
void queen(int index,int n){
	int i;
	//promsing 하지 않으면 함수는 아무것도 하지 않고 종료
	if (promising(index)) {	
		if (index == (n-1)) { //행의 끝까지 오면, 성공 case, column 출력!
			printf("%3d번째 방법:",++soluNum);
			for (i = 0; i < n; i++)
				printf("%d ", cal[i]+1);
			printf("\n");
		}
		//다음 행의 column을 0 ~ n-1까지 다 실행해봄, 
		for (i = 0; i < n; i++) {
			cal[index+1] = i;
			queen(index + 1,n);
		}
	}
}

int main() {
	printf(" \nn입력:");
	scanf("%d", &n);
	printf("\n@ n = %d 인 경우\n",n);
	cal = (int *)malloc(sizeof(int)*n);
	int i;
	//0이 뿌리가 아니라.. column에 포함해서
	// column[0]도 n개 실행!
	for (i = 0; i < n; i++) {
		cal[0] = i;
		queen(0,n);
	}

	printf("@ 총 가짓수 %d\n\n", soluNum);
}

