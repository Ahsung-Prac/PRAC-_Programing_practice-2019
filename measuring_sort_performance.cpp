#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// ���� swap�Լ�
void swap(int *a, int *b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;

}

// �迭 ���� �Լ� ( MergeSort �Լ����� ����)
void ArrCopy(int *Ori, int *Copy, int num) {
	int i;
	for (i = 0; i < num; i++) {
		Copy[i] = Ori[i];
	}
}

// �� ���� ���ĵ� �迭�� ( ���� ���̰� pre,�� post�� �迭, ù�ּҴ� ���� a�� a+pre �̴�.)
// �ϳ��� ���ĵ� �迭�� �պ��ϴ� �Լ�
int Merge(int *a, int pre, int post) {
	int i = 0; int j = pre;
	int k = 0;
	int count = 0;  //��Ƚ�� ī��Ʈ
	int *temp = (int *)malloc(sizeof(int)*(pre + post));
	//���� �� �迭�� ���� �����Ҷ����� ��
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
	if (i >= pre) { ArrCopy(a + j, temp + k, pre + post - j); } // ������ ����
	if (j >= pre + post) { ArrCopy(a + i, temp + k, pre - i); }
	ArrCopy(temp, a, pre + post);  // ���� sorting�ϰ��� �ϴ� �Լ��� ����
	free(temp);
	return count;
}

// �պ����� �Լ�.
// ���̰� 1 �� �迭�� ���ĵ� �Լ�.  ������ ���� �� ����Լ��� MergeSort�� �ΰ��� ���ĵ� �迭�� Merge�Լ��� ���� �պ��Ѵ�.
// ��ȯ�� ���ݱ��� ��Ƚ���̴�.
int MergSort(int *a, int len) {
	int count = 0; //��Ƚ�� ī��Ʈ
	if (len > 1) {
		int pre = len / 2;
		int post = len - pre;
		count += MergSort(a, pre);        // �������� �迭�� ��Ƚ��
		count += MergSort(a + pre, post); // �������� �迭�� ��Ƚ��
		count += Merge(a, pre, post);     // �պ��� ��� ���
	}
	return count;
}
// ��������. Quicksort�Լ�.
// �� ��Ƚ���� ��ȯ.
// �ѹ� �Լ��� ����ɶ� �ǹ��� �������� ������ �ڽź��� ���� ��, �������� �ڽź��� ū���� ���� �˰����̴�.
// �ǹ��� ��� ���ĵ� ������� ������ ����Լ��� �ִ�� ���ư��� worst_case�� �ȴ�.
int Quicksort(int *a, int left, int right) {
	int count = 0;// ��Ƚ�� ī��Ʈ
	if (left < right) {
		int pivot = a[left];
		int i;
		int j = left; //�ǹ����� ���� ������ �迭�� ���ʺ��� ���� ��, ������� �׾Ƴ��� ������ �ε���
		// �ǹ����� ���� ���� ã���� j�ε����� �ϳ� �ø��� �� �ε����� ��ȯ�Ѵ�.
		for (i = left + 1; i <= right; i++) {
			if (a[i] < pivot) {
				j++;
				swap(&a[i], &a[j]);
			}
			count++;  //�ǹ� �������� �Լ��� �����µ� ��� ��� 
		}
		swap(&a[left], &a[j]);
		count += Quicksort(a, left, j - 1);  //�������� �Լ��� ��Ƚ��
		count += Quicksort(a, j + 1, right); //�������� �Լ��� ��Ƚ��
	}
	return count;
}

// Max�� ���� ū ���� ��, sub�� �Լ��� ����ϸ鼭 ������ ���� �ֱ� ���� ����.
// MergeSort�� �־��� ��Ȳ�� �� ���ĵ� �迭�� �պ���, �� �迭 ��� ������ ���ұ��� ���ϰ� �Ǵ� ����̴�.
// �� ������ ������Ű�� ���ؼ��� �պ��迭�� ����ū ���ҿ�, �ι�°�� ū ���Ҹ� �պ����� �ΰ��� ���� �迭�� ���� ������ �������Ѵ�.
// �������� �迭�� ���� ù ���ҵ��� �� ������ �����ϰ� ������ ������, �� ������ Max�� sub�̴�.
// �迭�� ������ �������� �� ���Ǹ� ����ϰԵǸ� ���߿� �պ��Ҷ� ���� ���� ���� �� �ְ�,, �̶� ���� ū ���� ���� 3�� �̻�Ǹ� worst ���̽��� ���� �ʴ´�.
// �迭�� ũ��� 1/2�� �������� ��� �ɰ����Ƿ� sub�� �ι辿�� ũ�����൵ ��� �迭�� ���Ҹ� ���� �ٸ��� �� �� �ִ�.
//  ex)Max���ؿ��� �ɰ��������� sub�� �ι辿 �ϸ�, �ݴ��� �迭���� �ɰ����� �ִ� ��Ȳ�� ������� �ʾƵ� �Ȱ�ĥ �� �ִ�.
void worstMerge(int *a, int len, int max, int sub) {
	if (len == max) a[0] = max; //���� ū �ʱⰪ ����..�迭�� ù����
	if (len > 1) {
		int pre = len / 2;
		int post = len - pre;
		a[pre] = max - sub; // �������� �޺κ� �迭�� ù���ҿ� �ι�°�� ū���� �������ش�. ����Լ��� ���� �� ���Ұ� �迭 �� ���� ū���� �ȴ�.
		worstMerge(a, pre, max, sub * 2); // �պκ� �迭�� �ٽ� �ɰ���.
		worstMerge(a + pre, post, max - sub, sub * 2); // �޺κ� �迭�� �ٽ� �ɰ���. 
	}
}

// Quicksort�� MergeSort�� ����� ���̰� num�� ������ ���� �迭�� �����Ѵ�.
void Set_Array(int *Ran, int *Ran2, int num) {
	int i;
	for (i = 0; i < num; i++) {
		int ran;
		ran = Ran[i] = Ran2[i] = rand();
	}
}

// ���� �迭 2���� Worst_case �迭 �ΰ���.
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
	if (input == NULL) { puts("input ���Ͽ��� ����"); return 0; }
	output = fopen("output1.txt", "wt");
	if (output == NULL) {
		puts("output ���� ���� ����"); return 0;
	}
	printf("\n");

	fscanf(input, "%d", &dnum);
	printf("input1.txt���� ���� ������\n���� Ƚ�� %d", dnum);
	int *data = (int *)malloc(sizeof(int) * dnum);
	for (i = 0; i < dnum; i++) {
		fscanf(input, "%d", &data[i]);
	}
	fclose(input);
	printf("\n\n");

	// QuickSort�� Worst�� �̹� ���ĵ� �迭�̹Ƿ� �������� �迭 ��üũ�⸦ ������ ���´�.
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