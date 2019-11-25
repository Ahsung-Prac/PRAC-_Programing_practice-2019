#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// 정수 swap함수
void swap(int *a, int *b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;

}

// 배열 복사 함수 ( MergeSort 함수에서 사용됨)
void ArrCopy(int *Ori, int *Copy, int num) {
	int i;
	for (i = 0; i < num; i++) {
		Copy[i] = Ori[i];
	}
}

// 두 개의 정렬된 배열을 ( 각각 길이가 pre,와 post인 배열, 첫주소는 각각 a와 a+pre 이다.)
// 하나의 정렬된 배열로 합병하는 함수
int Merge(int *a, int pre, int post) {
	int i = 0; int j = pre;
	int k = 0;
	int count = 0;  //비교횟수 카운트
	int *temp = (int *)malloc(sizeof(int)*(pre + post));
	//둘중 한 배열의 끝에 도달할때까지 비교
	while (i < pre && j < pre + post) {
		if (a[i] < a[j]) {
			temp[k] = a[i];
			i++;
			count++;
		}
		else {
			temp[k] = a[j];
			j++;
			count++;
		}
		k++;
	}
	if (i >= pre) { ArrCopy(a + j, temp + k, pre + post - j); } // 나머지 복사
	if (j >= pre + post) { ArrCopy(a + i, temp + k, pre - i); }
	ArrCopy(temp, a, pre + post);  // 원래 sorting하고자 하던 함수에 복사
	free(temp);
	return count;
}

// 합병정렬 함수.
// 길이가 1 인 배열은 정렬된 함수.  반으로 나눈 후 재귀함수로 MergeSort후 두개의 정렬되 배열을 Merge함수를 통해 합병한다.
// 반환은 지금까지 비교횟수이다.
int MergSort(int *a, int len) {
	int count = 0; //비교횟수 카운트
	if (len > 1) {
		int pre = len / 2;
		int post = len - pre;
		count += MergSort(a, pre);        // 나누어진 배열의 비교횟수
		count += MergSort(a + pre, post); // 나누어진 배열의 비교횟수
		count += Merge(a, pre, post);     // 합병시 드는 비용
	}
	return count;
}
// 빠른정렬. Quicksort함수.
// 총 비교횟수를 반환.
// 한번 함수가 실행될때 피벗을 기준으로 왼쪽을 자신보다 작은 수, 오른쪽을 자신보다 큰수로 놓는 알고리즘이다.
// 피벗이 계속 정렬된 순서대로 뽑힐때 재귀함수가 최대로 돌아가는 worst_case가 된다.
int Quicksort(int *a, int left, int right) {
	int count = 0;// 비교횟수 카운트
	if (left < right) {
		int pivot = a[left];
		int i;
		int j = left; //피벗보다 작은 수들을 배열의 왼쪽부터 쌓을 때, 현재까지 쌓아놓은 마지막 인덱스
		// 피벗보다 작은 수를 찾으면 j인덱스를 하나 올리고 그 인덱스와 교환한다.
		for (i = left + 1; i <= right; i++) {
			if (a[i] < pivot) {
				j++;
				swap(&a[i], &a[j]);
			}
			count++;  //피벗 기준으로 함수를 나누는데 드는 비용 
		}
		swap(&a[left], &a[j]);
		count += Quicksort(a, left, j - 1);  //나누어진 함수의 비교횟수
		count += Quicksort(a, j + 1, right); //나누어진 함수의 비교횟수
	}
	return count;
}

// Max는 가장 큰 원소 값, sub는 함수가 재귀하면서 적절한 값을 넣기 위한 인자.
// MergeSort의 최악의 상황은 두 정렬된 배열이 합병시, 두 배열 모두 마지막 원소까지 비교하게 되는 경우이다.
// 위 조건을 만족시키기 위해서는 합병배열의 가장큰 원소와, 두번째로 큰 원소를 합병전의 두개의 원시 배열이 각각 나누어 가져야한다.
// 나누어진 배열의 각각 첫 원소들이 위 조건을 만족하게 나누어 가진다, 그 기준이 Max와 sub이다.
// 배열을 나누는 과정에서 위 조건만 고려하게되면 나중에 합병할때 같은 수가 생길 수 있고,, 이때 가장 큰 같은 수가 3개 이상되면 worst 케이스가 되지 않는다.
// 배열의 크기는 1/2의 내림으로 계속 쪼개지므로 sub를 두배씩만 크게해줘도 모든 배열의 원소를 각기 다르게 할 수 있다.
//  ex)Max기준에서 쪼개질때마다 sub를 두배씩 하면, 반대쪽 배열에서 쪼개지고 있는 상황을 고려하지 않아도 안겹칠 수 있다.
void worstMerge(int *a, int len, int max, int sub) {
	if (len == max) a[0] = max; //가장 큰 초기값 설정..배열의 첫원소
	if (len > 1) {
		int pre = len / 2;
		int post = len - pre;
		a[pre] = max - sub; // 나누어진 뒷부분 배열의 첫원소에 두번째로 큰수를 배정해준다. 재귀함수에 들어가면 이 원소가 배열 내 가장 큰수가 된다.
		worstMerge(a, pre, max, sub * 2); // 앞부분 배열을 다시 쪼갠다.
		worstMerge(a + pre, post, max - sub, sub * 2); // 뒷부분 배열을 다시 쪼갠다. 
	}
}

// Quicksort와 MergeSort에 사용할 길이가 num인 각각의 랜덤 배열을 셋팅한다.
void Set_Array(int *Ran, int *Ran2, int num) {
	int i;
	for (i = 0; i < num; i++) {
		int ran;
		ran = Ran[i] = Ran2[i] = rand();
	}
}

// 랜덤 배열 2개와 Worst_case 배열 두가지.
int Arr[10001];
int temp[10001];
int M_Worst[10001];
int Q_Worst[10001];
int main() {
	int dnum;
	int i;
	srand(time(NULL));
	FILE * input;
	FILE * output;
	int tst;
	input = fopen("input1.txt", "rt");
	if (input == NULL) { puts("input 파일열기 오류"); return 0; }
	output = fopen("output1.txt", "wt");
	if (output == NULL) {
		puts("output 파일 열기 오류"); return 0;
	}
	printf("\n");

	fscanf(input, "%d", &dnum);
	printf("input1.txt에서 값을 가져옴\n실행 횟수 %d", dnum);
	int *data = (int *)malloc(sizeof(int) * dnum);
	for (i = 0; i < dnum; i++) {
		fscanf(input, "%d", &data[i]);
	}
	fclose(input);
	printf("\n\n");

	// QuickSort의 Worst는 이미 정렬된 배열이므로 시작전에 배열 전체크기를 셋팅해 놓는다.
	for (i = 0; i < 10001; i++) {
		Q_Worst[i] = i;
	}

	printf("          rand_Merge      worst_Merge      rand_Quick      worst_Quick      average\n");
	printf("-------------------------------------------------------------------------------------\n\n");
	fprintf(output, "          rand_Merge      worst_Merge      rand_Quick      worst_Quick      average\n");
	fprintf(output, "-------------------------------------------------------------------------------------\n\n");
	for (i = 0; i < dnum; i++) {

		Set_Array(Arr, temp, data[i]);
		worstMerge(M_Worst, data[i], data[i], 1);
		int par[4] = { MergSort(temp, data[i]), MergSort(M_Worst, data[i]), Quicksort(Arr, 0, data[i] - 1), Quicksort(Q_Worst, 0, data[i] - 1) };
		int average = par[0] + par[1] + par[2] + par[3]; average /= 4;
		printf("%d :        %6d           %6d           %6d           %8d           %8d", data[i], par[0], par[1], par[2], par[3],average);
		printf("\n\n");
		fprintf(output, "%d :       %6d           %6d           %6d           %8d           %8d\n", data[i], par[0], par[1], par[2], par[3], average);
	}
	fclose(output);
}