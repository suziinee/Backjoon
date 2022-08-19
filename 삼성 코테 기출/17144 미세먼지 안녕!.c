#include <stdio.h>

#define MAX 1000
int r, c, t;
int arr[2][MAX + 10][MAX + 10];
int up = -1; int down = -1; //y좌표
int cur; int ans;

void input(void)
{
	scanf("%d %d %d", &r, &c, &t);
	for (int y = 0; y < r; y++) {
		for (int x = 0; x < c; x++) {
			scanf("%d", &arr[0][y][x]);
			if (arr[0][y][x] == -1) {
				if (up == -1) up = y;
				else down = y;
			}
		}
	}
}

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { -1, 0, 1, 0 };
void spread(void)
{
	int next = (cur + 1) % 2;

	for (int y = 0; y < r; y++) {
		for (int x = 0; x < c; x++) {
			if (arr[cur][y][x] == -1) continue;
			if (arr[cur][y][x] == 0) continue;
			int nx; int ny; 
			int dust = arr[cur][y][x] / 5; int discount = 0;
			for (int i = 0; i < 4; i++) {
				nx = x + dx[i];
				ny = y + dy[i];
				if (nx < 0 || ny < 0 || nx >= c || ny >= r) continue;
				if (arr[cur][ny][nx] == -1) continue;
				arr[next][ny][nx] += dust;
				discount += dust;
			}
			arr[cur][y][x] -= discount;
			arr[next][y][x] += arr[cur][y][x];
		}
	}

	//cur 배열 초기화
	for (int y = 0; y < r; y++) {
		for (int x = 0; x < c; x++) {
			if (arr[cur][y][x] == -1) {
				arr[next][y][x] = -1;
				continue;
			}
			arr[cur][y][x] = 0;
		}
	}
	cur = next;
}

void move(void)
{
	for (int y = up - 2; y >= 0; y--) {
		arr[cur][y + 1][0] = arr[cur][y][0];
	}
	for (int x = 1; x <= c - 1; x++) {
		arr[cur][0][x - 1] = arr[cur][0][x];
	}
	for (int y = 1; y <= up; y++) {
		arr[cur][y - 1][c - 1] = arr[cur][y][c - 1];
	}
	for (int x = c - 2; x >= 1; x--) {
		arr[cur][up][x + 1] = arr[cur][up][x];
	}
	arr[cur][up][1] = 0;

	for (int y = down + 2; y <= r - 1; y++) {
		arr[cur][y - 1][0] = arr[cur][y][0];
	}
	for (int x = 1; x <= c - 1; x++) {
		arr[cur][r - 1][x - 1] = arr[cur][r - 1][x];
	}
	for (int y = r - 2; y >= down; y--) {
		arr[cur][y + 1][c - 1] = arr[cur][y][c - 1];
	}
	for (int x = c - 2; x >= 1; x--) {
		arr[cur][down][x + 1] = arr[cur][down][x];
	}
	arr[cur][down][1] = 0;
}

void solve(void)
{
	for (int i = 0; i < t; i++) {
		spread(); //cur에서 cur+1로 spread
		move(); //spread에서 갱신된 cur에서 그대로 move 발생
	}

	for (int y = 0; y < r; y++) {
		for (int x = 0; x < c; x++) {
			ans += arr[cur][y][x];
		}
	}
	printf("%d", ans + 2);
}


int main(void)
{
	input();
	solve();
	return 0;
}