#include <stdio.h>

int nums[100];
int n, m;
int res[3];
int ans = 0;

void func(int a, int b, int c)
{
	if ((a + b + c) <= m) {
		if ((a + b + c) > ans) ans = (a + b + c);
	}
}

void DFS(int L, int BeginWith)
{
	if (L == 3) {
		func(res[0], res[1], res[2]);
	}
	else {
		for (int i = BeginWith; i < n; i++) {
			res[L] = nums[i];
			DFS(L + 1, i + 1);
		}
	}
}

int main(void)
{
	
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &nums[i]);
	}

	//3장의 조합 구현
	DFS(0, 0);

	printf("%d", ans);
	return 0;
}