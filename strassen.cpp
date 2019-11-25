#include<stdio.h>
#include<stdlib.h>
#include<time.h>



int **m1;
int **m2;
int **result;
unsigned long long count[2] = { 0,0 };  //standard�� count[0] = mul, count[1]= add/sub ī��Ʈ
unsigned long long count2[2] = { 0,0 }; //straseen�� count2[0] = mul, count2[1] = add/sub ī��Ʈ

// data����� n * n ������� ���� �Լ�, �޸� �Ҵ�
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

//n*n����� �޸� ���� ����,
void FreeMat(int **matrix,int n) {
	int i;
	for (i = 0; i < n; i++) {
		free(*(matrix+i));
	}
	free(matrix);
}

// 2^a�� ��ȯ
int Squ(int a) {
	int num = 1;
	int i;
	for (i = 0; i < a; i++) {
		num *= 2;
	}
	return num;
}

// Standard n*n��� ����. m1 * m2 = result, count�� mul, add/sub Ƚ�� ����
// �Լ��� ����ð��� ��ȯ.
double Standard(int **m1, int **m2,int **result,int n, unsigned long long *count) {
	clock_t start_, end_;
	start_ = clock();
	int i,j,k;
	for (i = 0; i < n; i++) {
		for(j = 0; j < n; j++){
			for (k = 0; k < n; k++) {
				if (k == 0) { // ���� ù�� ����� ������..
					result[i][j] = m1[j][k] * m2[k][j];
					count[0]++; 
				}
				else {		  // �� �ܴ� ���� ���� �Բ�
					result[i][j] += m1[i][k] * m2[k][j];
					count[0]++; count[1]++;
				}
			}
		}
	}
	end_ = clock();
	double exc = (double)(end_ - start_) / CLOCKS_PER_SEC; // ���� �ð� ���
	return exc;
}

//n*n��� ���� �Լ�
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

// n*n��� ���� �Լ�
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

// Strassen n*n��� ����, m1*m2=result, count�� �������� ����.
// �Լ��� ��ȯ�� ����ð��̴�.
double strassen(int **mat1, int **mat2, int **result, int n,unsigned long long* count) {
	clock_t start_, end_;
	start_ = clock();
	if (n <= 2 ) // ȿ���� ��¦�� �ø����� n�� 2�����϶� Standard�� ����ߴ�.
	{
		Standard(mat1, mat2, result, n, count);
	}
	else {
		int i, j;
		int **M1[4];  //mat1�� 4���� �ɰ��� (n/2) * (n/2)���
		int **M2[4];  //mat2�� 4���� �ɰ��� (n/2) * (n/2)���
		int **RS[4];  //result�� 4���� �������� �ڸ��� �� (n/2) * (n/2)���
		int **MM[7];  // strassen ������ �߰��ܰ�  ������ m1 ~ m7������ n/2 ��� 7��
		int **tempM1, **tempM2;  // ����� ������ ��� ������ ���.

		// �� ������ ��ĵ� �޸� �Ҵ�. 0��ķ� ����.
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

		//mat1�� mat2 ���� ����� 4���� �ɰ����� ��Ŀ� ���� �Ҵ����ش�.
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
		int a_s = (n / 2)*(n / 2);  // ����� ���� or ������ �ѹ��� �������� (n/2)���� ��ŭ�Ѵ�.(��� ������ �� ���� ��ŭ)

		//strassen ������ �߰��ܰ�, ������ m1 ~ m7��(MM[0]~MM[6]) ���Ѵ�. ������ ������ ������ �Լ��� 
		// ����� ������ �ٽ� strassen�� ����Լ��� �����Ѵ�
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



		// �� �������� ���� ������ m1 ~ m7��(MM[0]~MM[6])�� �̿���
		// result 4������ �� ��� RS[0] ~ RS[3] ����� ���Ѵ�.
		Matadd(MM[0], MM[3], tempM1, n / 2);	count[1] += a_s;
		Matsub(tempM1, MM[4], tempM2, n / 2);	count[1] += a_s;
		Matadd(tempM2, MM[6], RS[0], n / 2);	count[1] += a_s;

		Matadd(MM[2], MM[4], RS[1], n / 2);	count[1] += a_s;

		Matadd(MM[2], MM[3], RS[2], n / 2);	count[1] += a_s;
		
		Matadd(MM[0], MM[2], tempM1, n / 2);	count[1] += a_s;
		Matsub(tempM1, MM[1], tempM2, n / 2);	count[1] += a_s;
		Matadd(tempM2, MM[5], RS[3], n / 2);	count[1] += a_s;
	
		// RS[0] ~ RS[3]�� ���� result ��Ŀ� �־��ش�.
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

		//�پ� ����� �޸𸮸� �����Ѵ�.
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
	return exc; //����ð� ��ȯ
}


int main() {
	int i;
	FILE * output;
	output = fopen("output2.txt", "wt");
	if (output == NULL) puts("���� ���� ����");
	
	// 2^12���ʹ� 1�ð� �̻� �ҿ�˴ϴ�. 2^12�� �������� ����� ����..����� 2^11������ �ϰڽ��ϴ�.
	for (i = 1; i < 12; i++) {
		//���, �������� ī��Ʈ ����!
		int num = Squ(i);
		
		SetMatrix(&m1, num, 1);
		SetMatrix(&m2, num, 1);
		SetMatrix(&result, num, 0);
		count[0] = 0; count[1] = 0;
		count2[0] = 0; count2[1] = 0;

		double Stand_Time = Standard(m1, m2, result, num, count);
		double Stra_Time = strassen(m1, m2, result, num, count2);
		
		//����� ���
		printf("\n============================================");
		printf("\n2^%d          Standard          Strassen\n", i);
		
		printf("----------------------------------------------\n");
		printf("\nmul         %10llu         %10llu\n",count[0], count2[0] );
		printf("\nadd/mul     %10llu         %10llu\n", count[1], count2[1]);
		printf("\ntime        %10f         %10f\n", Stand_Time, Stra_Time);
		printf("=============================================\n");
		
		// output2.txt ���Ͽ� ���
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