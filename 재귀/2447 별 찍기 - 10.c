#include <stdio.h>

int arr[7000][7000];

void draw(int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			arr[i][j] = 1;
		}
	}
}

void space(int y, int x, int n) //(y, x)로 시작되는 n*n에서 가운데를 비워주는 함수
{
	if (n == 1) return;

	for (int i = y + (n/3); i < y + 2 * (n/3); i++) {
		for (int j = x + (n/3); j < x + 2 * (n/3); j++) {
			arr[i][j] = 0;
		}
	}

	space(y, x, n / 3);
	space(y, x + n / 3, n / 3);
	space(y, x + n / 3 * 2, n / 3);

	space(y + n / 3, x, n / 3);
	space(y + n / 3, x + n / 3 * 2, n / 3);

	space(y + n / 3 * 2, x, n / 3);
	space(y + n / 3 * 2, x + n / 3, n / 3);
	space(y + n / 3 * 2, x + n / 3 * 2, n / 3);
}

void output(int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j] == 1) printf("*");
			else printf(" ");
		}
		printf("\n");
	}
}

int main(void)
{
	int n;
	scanf("%d", &n);
	draw(n);
	space(0, 0, n);
	output(n);
    return 0;
}
