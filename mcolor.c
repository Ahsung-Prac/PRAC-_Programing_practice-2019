#include<stdio.h>
#include<stdlib.h>


// n*n 이차원 배열 동적할당!
void SetMatrix(int ***matrix, int n) {
	int i;
	*matrix = (int **)malloc(sizeof(int*)*n);
	for (i = 0; i < n; i++) {
		*(*matrix + i) = (int *)malloc(sizeof(int)*n);
		int j;
		for (j = 0; j < n; j++) {
			*(*(*matrix + i) + j) = 0;
		}
	}
}

int **W;	//그래프 인접행렬!
int n;		//그래프 노드 개수	
int *color;	//n개 노드의 color 배열
int solnum = 0;	//해답의 개수
int sol_flag = 0; //최소 m을 찾았다는 플래그!

//promising 함수
int promising(int index) {
	int Sw = 1;
	int i;
	//색이 정해진 전의 노드들 중, 연결되어있는 노드와 색이 겹치지 않는지 검사.
	for (i = 0; i < index;i++){
		if (W[index][i] && (color[index] == color[i])) {
			Sw = 0; 	//겹친다면 0
			break;
		}
	}
	return Sw;
}

//m-Coloring 백트래킹 함수! m개의 색으로 칠해본다!
void mColoring(int index,int m){
	int c;
	//promising하지 않으면 함수 종료
	if (promising(index)){
		if (index == n - 1) { // 마지막 노드까지 칠하는거 성공!!
			if (!sol_flag) { 	//최소 m을 찾았다는 플래그가 없다면
				sol_flag = 1; 	//플래그를 켜준다!!. 
				printf("@ minimum m : %d\n", m); //최소 m출력
			}
			//찾은 해답을 출력해준다!!
			printf("%d번째 방법 : ",++solnum); 
			int i;
			for (i = 0; i < n; i++) {
				printf("%d ", color[i]+1);
			}
			printf("\n");
		}
		//다음 노드에 m가지 컬러를 실행해본다!
		else {
			for (c = 0; c < m; c++) {
				color[index + 1] = c;
				mColoring(index + 1, m);
			}
		}
	}
}

int main() {
	int i;
	int j;
	int m=2; // m = 2!! 노드가 두개 이상이면 적어도 2개 컬러.
	printf("input size : ");
	scanf("%d", &n);
	SetMatrix(&W,n);

	color = (int *)malloc(sizeof(int)*n);
	// 인접행렬 입력!!
	for (i = 0; i < n; i++) {
		printf("%d번째 row : ", i + 1);
		for (j = 0; j < n; j++) {
			scanf("%d", &W[i][j]);
		}
	}
	printf("\n");
	
	//m-coloring 시작!!
	while (1) {
		//첫 노드에 m가지 색 mColoring 시작!!
		for (i = 0; i < m; i++) {
			color[0] = i;
			mColoring(0, m);
			//조합의 문제이기 떄문에,
			//i=0 에서 답이 안나오면
			//나머지도 답이 없다.
			//해답플래그가 안켜지면 break
			if (!sol_flag) break;
		}
		//최소 m으로 for문을 다 돌렸다면
		//break
		if (sol_flag) break;
		//아직 최소 m을 못구했으면 m 1증가!
		m++;
	}
	
	printf("@ 총 가짓수 : %d\n",solnum);


}

