#include<stdio.h>
#include<stdlib.h>
#include<time.h>



int **m1;
int **m2;
int **result;
unsigned long long count[2] = { 0,0 };  //standard의 count[0] = mul, count[1]= add/sub 카운트
unsigned long long count2[2] = { 0,0 }; //straseen의 count2[0] = mul, count2[1] = add/sub 카운트

// data배수의 n * n 단위행렬 생성 함수, 메모리 할당
void SetMatrix(int ***matrix, int n,int data) {
	int i;
	*matrix = (int **)malloc(sizeof(int*)*n);
	for (i = 0; i < n; i++) {
		*(*matrix+i) = (int *)malloc(sizeof(int)*n);
		int j;
		for (j = 0; j < n; j++) { 
			if( i == j) *(*(*matrix+i)+j) = data;
			else *(*(*matrix + i) + j) = 0;
		}
	}
}

//n*n행렬의 메모리 공간 해제,
void FreeMat(int **matrix,int n) {
	int i;
	for (i = 0; i < n; i++) {
		free(*(matrix+i));
	}
	free(matrix);
}

// 2^a을 반환
int Squ(int a) {
	int num = 1;
	int i;
	for (i = 0; i < a; i++) {
		num *= 2;
	}
	return num;
}

// Standard n*n행렬 곱셈. m1 * m2 = result, count는 mul, add/sub 횟수 저장
// 함수는 실행시간을 반환.
double Standard(int **m1, int **m2,int **result,int n, unsigned long long *count) {
	clock_t start_, end_;
	start_ = clock();
	int i,j,k;
	for (i = 0; i < n; i++) {
		for(j = 0; j < n; j++){
			for (k = 0; k < n; k++) {
				if (k == 0) { // 행의 첫열 계산은 곱셈만..
					result[i][j] = m1[j][k] * m2[k][j];
					count[0]++; 
				}
				else {		  // 그 외는 곱과 덧셈 함께
					result[i][j] += m1[i][k] * m2[k][j];
					count[0]++; count[1]++;
				}
			}
		}
	}
	end_ = clock();
	double exc = (double)(end_ - start_) / CLOCKS_PER_SEC; // 실행 시간 계산
	return exc;
}

//n*n행렬 덧셈 함수
void Matadd(int **m1, int **m2, int **result,int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			result[i][j] = m1[i][j] + m2[i][j];
		}
	}
}

// n*n행렬 뺄셈 함수
void Matsub(int **m1, int **m2, int **result,int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			result[i][j] = m1[i][j] - m2[i][j];
		}
	}
}

// Strassen n*n행렬 곱셈, m1*m2=result, count에 단위연산 저장.
// 함수의 반환은 실행시간이다.
double strassen(int **mat1, int **mat2, int **result, int n,unsigned long long* count) {
	clock_t start_, end_;
	start_ = clock();
	if (n <= 2 ) // 효율을 살짝만 올리고자 n이 2이하일때 Standard를 사용했다.
	{
		Standard(mat1, mat2, result, n, count);
	}
	else {
		int i, j;
		int **M1[4];  //mat1이 4개로 쪼개진 (n/2) * (n/2)행렬
		int **M2[4];  //mat2이 4개로 쪼개진 (n/2) * (n/2)행렬
		int **RS[4];  //result의 4개로 나누어진 자리에 들어갈 (n/2) * (n/2)행렬
		int **MM[7];  // strassen 공식의 중간단계  교재의 m1 ~ m7까지의 n/2 행렬 7개
		int **tempM1, **tempM2;  // 행렬의 연산을 잠시 저장할 행렬.

		// 위 선언한 행렬들 메모리 할당. 0행렬로 선언.
		SetMatrix(&tempM1, n / 2, 0);
		SetMatrix(&tempM2, n / 2, 0);
		for (i = 0; i < 4; i++) {
			SetMatrix(&M1[i], n / 2, 0);
			SetMatrix(&M2[i], n / 2, 0);
			SetMatrix(&RS[i], n / 2, 0);
			SetMatrix(&MM[i], n / 2, 0);
		}
		for (i = 4; i < 7; i++) {
			SetMatrix(&MM[i], n / 2, 0);
		}

		//mat1과 mat2 각각 행렬을 4개로 쪼개어진 행렬에 값을 할당해준다.
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (i < n / 2 && j < n / 2) {
					M1[0][i][j] = mat1[i][j];
					M2[0][i][j] = mat2[i][j];
				}
				else if (i < n / 2 && j >= n / 2) {
					M1[1][i][j-(n/2)] = mat1[i][j];
					M2[1][i][j-(n/2)] = mat2[i][j];
				}
				else if (i >= n / 2 && j < n / 2) {
					M1[2][i-(n/2)][j] = mat1[i][j];
					M2[2][i-(n/2)][j] = mat2[i][j];
				}
				else if (i >= n / 2 && j >= n / 2) {
					M1[3][i-(n/2)][j - (n / 2)] = mat1[i][j];
					M2[3][i - (n / 2)][j - (n / 2)] = mat2[i][j];
				}
			}
		}
		int a_s = (n / 2)*(n / 2);  // 행렬의 덧셈 or 뺄셈은 한번당 단위연산 (n/2)제곱 만큼한다.(행렬 원소의 총 개수 만큼)

		//strassen 공식의 중간단계, 교재의 m1 ~ m7을(MM[0]~MM[6]) 구한다. 덧셈과 뺄셈은 구현한 함수로 
		// 행렬의 곱셈은 다시 strassen의 재귀함수로 수행한다
		Matadd(M1[0], M1[3], tempM1, n / 2);	count[1] += a_s;
		Matadd(M2[0], M2[3], tempM2, n / 2);	count[1] += a_s;
		strassen(tempM1, tempM2, MM[0], n / 2 , count); count[0]++;  
	
		Matadd(M1[2], M1[3], tempM1, n / 2);	count[1] += a_s;
		strassen(tempM1, M2[0], MM[1], n / 2, count);	count[0]++;
		
		Matsub(M2[2], M2[0], tempM2, n / 2);	count[1] += a_s;
		strassen( M1[3], tempM2, MM[3], n / 2, count);	count[0]++;
		
		Matsub(M2[1], M2[3], tempM2, n / 2);	count[1] += a_s;
		strassen( M1[0], tempM2, MM[2], n / 2, count);	count[0]++;
	
		Matadd( M1[0], M1[1], tempM1, n / 2);	count[1] += a_s;
		strassen(tempM1, M2[3], MM[4], n / 2, count);	count[0]++;
		
		Matsub(M1[2], M1[0], tempM1, n / 2);	count[1] += a_s;
		Matadd(M2[0], M2[1], tempM2, n / 2);	count[1] += a_s;
		strassen(tempM1, tempM2, MM[5], n / 2, count);	count[0]++;

		Matsub(M1[1], M1[3], tempM1, n / 2);	count[1] += a_s;
		Matadd(M2[2], M2[3], tempM2, n / 2);	count[1] += a_s;
		strassen(tempM1, tempM2, MM[6],  n / 2, count);	count[0]++;



		// 위 과정으로 구한 교재의 m1 ~ m7을(MM[0]~MM[6])을 이용해
		// result 4구역에 들어갈 행렬 RS[0] ~ RS[3] 행렬을 구한다.
		Matadd(MM[0], MM[3], tempM1, n / 2);	count[1] += a_s;
		Matsub(tempM1, MM[4], tempM2, n / 2);	count[1] += a_s;
		Matadd(tempM2, MM[6], RS[0], n / 2);	count[1] += a_s;

		Matadd(MM[2], MM[4], RS[1], n / 2);	count[1] += a_s;

		Matadd(MM[2], MM[3], RS[2], n / 2);	count[1] += a_s;
		
		Matadd(MM[0], MM[2], tempM1, n / 2);	count[1] += a_s;
		Matsub(tempM1, MM[1], tempM2, n / 2);	count[1] += a_s;
		Matadd(tempM2, MM[5], RS[3], n / 2);	count[1] += a_s;
	
		// RS[0] ~ RS[3]을 합쳐 result 행렬에 넣어준다.
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (i < n / 2 && j < n / 2)
				{
					result[i][j] = RS[0][i][j];
				}
				else if (i < n / 2 && j >= n / 2)
				{
					result[i][j] = RS[1][i][j- (n / 2)];

				}
				else if (i >= n / 2 && j < n / 2)
				{
					result[i][j] = RS[2][i - (n / 2)][j];

				}
				else if (i >= n / 2 && j >= n / 2)
				{
					result[i][j] = RS[3][i - (n / 2)][j - (n / 2)];
				}
			}
		}

		//다쓴 행렬의 메모리를 해제한다.
		for (i = 0; i < 4; i++) {
			FreeMat(M1[i],n/2);
			FreeMat(M2[i], n / 2);
			FreeMat(RS[i], n / 2);
			FreeMat(MM[i], n / 2);
		}
		for (i = 4; i < 7; i++) {
			FreeMat(MM[i], n / 2);
		}
		FreeMat(tempM1,n/2);
		FreeMat(tempM2,n/2);
		

	}
	end_ = clock();
	double exc = (double)(end_ - start_)/CLOCKS_PER_SEC;
	return exc; //실행시간 반환
}


int main() {
	int i;
	FILE * output;
	output = fopen("output2.txt", "wt");
	if (output == NULL) puts("파일 열기 오류");
	
	// 2^12부터는 1시간 이상씩 소요됩니다. 2^12은 사진으로 결과만 증명..출력은 2^11까지만 하겠습니다.
	for (i = 1; i < 12; i++) {
		//행렬, 단위연산 카운트 셋팅!
		int num = Squ(i);
		
		SetMatrix(&m1, num, 1);
		SetMatrix(&m2, num, 1);
		SetMatrix(&result, num, 0);
		count[0] = 0; count[1] = 0;
		count2[0] = 0; count2[1] = 0;

		double Stand_Time = Standard(m1, m2, result, num, count);
		double Stra_Time = strassen(m1, m2, result, num, count2);
		
		//모니터 출력
		printf("\n============================================");
		printf("\n2^%d          Standard          Strassen\n", i);
		
		printf("----------------------------------------------\n");
		printf("\nmul         %10llu         %10llu\n",count[0], count2[0] );
		printf("\nadd/mul     %10llu         %10llu\n", count[1], count2[1]);
		printf("\ntime        %10f         %10f\n", Stand_Time, Stra_Time);
		printf("=============================================\n");
		
		// output2.txt 파일에 출력
		fprintf(output,"\n============================================");
		fprintf(output, "\n2^%d          Standard          Strassen\n", i);

		fprintf(output,"----------------------------------------------\n");
		fprintf(output, "\nmul         %10llu         %10llu\n", count[0], count2[0]);
		fprintf(output, "\nadd/mul     %10llu         %10llu\n", count[1], count2[1]);
		fprintf(output, "\ntime        %10f         %10f\n", Stand_Time, Stra_Time);
		fprintf(output, "=============================================\n");

		FreeMat(m1, num);
		FreeMat(m2, num);
		FreeMat(result, num);
	}
	fclose(output);
}