#include <stdio.h>
#include <string.h>

char chess[2][10][10]; //0:wbwb.. 1:bwbw..
char arr[50 + 10][50 + 10];
int n, m;
int min = 100000;

void input(void)
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf(" %s", arr[i]);
	}
}

void making_chess(void)
{
	char w[] = "WBWBWBWB";
	char b[] = "BWBWBWBW";
	for (int i = 0; i < 8; i++) {
		if (i % 2 == 0) {
			strcpy(chess[0][i], "WBWBWBWB");
			strcpy(chess[1][i], "BWBWBWBW");
		}
		else {
			strcpy(chess[0][i], "BWBWBWBW");
			strcpy(chess[1][i], "WBWBWBWB");
		}
	}
}

void compare(int x, int y)
{
	int chess0 = 0; int chess1 = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (arr[i + x][j + y] != chess[0][i][j]) chess0++;
			if (arr[i + x][j + y] != chess[1][i][j]) chess1++;
		}
	}
	min = min < chess0 ? min : chess0;
	min = min < chess1 ? min : chess1;
}

int main(void)
{
	making_chess();
	input();

	for (int i = 0; i <= n - 8; i++) {
		for (int j = 0; j <= m - 8; j++) {
			compare(i, j);
		}
	}

	printf("%d", min);
	return 0;
}