#include <stdio.h>

int arr[30][30];
int n;
int nums[30];
int links[30];
int res[15];
int min = 100000;

//links[i]가 res에 있는지 없는지 판별
int in_res(int x)
{
	for (int i = 0; i < (n / 2); i++) {
		if (x == res[i]) {
			return 1;
		}
	}
	return 0;
}

//start나 link의 합을 리턴해주는 함수
int sum(int a[])
{
	int ret = 0;
	for (int i = 0; i < (n / 2); i++) {
		for (int j = 0; j < (n / 2); j++) {
			if (a[i] != a[j]) ret += arr[a[i]][a[j]];
		}
	}
	return ret;
}

//res에 있는 조합(n/2개)으로 능력치 구하기
int calcul(void)
{
	int start = sum(res);

	//links를 돌면서 res에 없으면 rev_res에 추가
	int rev_res[15]; int idx = 0;
	for (int i = 0; i < n; i++) {
		if (!in_res(links[i])) {
			rev_res[idx] = links[i];
			idx += 1;
		}
	}

	int link = sum(rev_res);
	return start > link ? start - link : link - start;
}

void dfs(int l, int beginwith)
{
	if (l == (n / 2)) {
		int ret = calcul();
		if (ret < min) {
			min = ret;
		}
	}
	else {
		for (int i = beginwith; i < n; i++) {
			res[l] = nums[i];
			dfs(l + 1, i + 1);
		}
	}
}

void func(void)
{
	//nums와 links에 숫자 채워넣기
	for (int i = 0; i < n; i++) {
		nums[i] = i;
		links[i] = i;
	}
	dfs(0, 0);
}

int main(void)
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
	func();
	printf("%d", min);
	return 0;
}