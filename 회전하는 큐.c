#include <stdio.h>

int n, m;
int arr[50 + 5]; //1부터 시작
int start; int end;
int candi[50 + 5]; 
int ans;

void left(void)
{
	int tmp = arr[start];
	for (int i = start + 1; i <= end; i++) {
		arr[i - 1] = arr[i];
	}
	arr[end] = tmp;
}

void right(void)
{
	int tmp = arr[end];
	for (int i = end - 1; i >= start; i--) {
		arr[i + 1] = arr[i];
	}
	arr[start] = tmp;
}

int find_idx(int num)
{
	for (int i = start; i <= end; i++) {
		if (arr[i] == num) return i;
	}
}

void func(void)
{
	for (int i = 0; i < m; i++) {
		int idx = find_idx(candi[i]);
		int mid = (start + end + 1) / 2;

		if (idx <= mid) {
			while (arr[start] != candi[i]) {
				left(); ans++;
			}
			start++;
		}
		else {
			while (arr[start] != candi[i]) {
				right(); ans++;
			}
			start++;
		}
	}
}

int main(void)
{
	scanf("%d %d", &n, &m);
	start = 1;  end = n;
	for (int i = 0; i < m; i++) {
		scanf("%d", &candi[i]);
	}
	for (int i = 1; i <= n; i++) {
		arr[i] = i;
	}
	func();
	printf("\nans : %d", ans);
	return 0;
}
