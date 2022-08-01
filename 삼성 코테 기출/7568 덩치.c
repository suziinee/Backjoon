#include <stdio.h>

int arr[100][2];
int n;
int ans[100] = { 0 };

void func(void)
{
	for (int i = 0; i < n; i++) {
		int cnt = 1;
		for (int j = 0; j < n; j++) {
			if ((arr[i][0] < arr[j][0]) && (arr[i][1] < arr[j][1])) cnt += 1;
		}
		ans[i] = cnt;
	}
}

int main(void)
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &arr[i][0], &arr[i][1]);
	}
	func();
	for (int i = 0; i < n; i++) {
		printf("%d ", ans[i]);
	}
	return 0;
}