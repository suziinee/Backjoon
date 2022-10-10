#include <iostream>
using namespace std;

#define MAX 50
int R, C, T;
int map[2][MAX][MAX];
int cur;
int up = -1;
int down = -1;


void input()
{
	cin >> R >> C >> T;
	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			cin >> map[0][y][x];
			if (map[0][y][x] == -1) {
				if (up == -1) {
					up = y;
				}
				else {
					down = y;
				}
			}
		}
	}
}

void spread()
{
	static int dx[] = { 0, 1, 0, -1 };
	static int dy[] = { -1, 0, 1, 0 };

	int next = (cur + 1) % 2;
	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			if (map[cur][y][x] == 0 || map[cur][y][x] == -1) continue;

			int cnt = 0;
			int dirt = map[cur][y][x] / 5;
			for (int d = 0; d < 4; d++) {
				int nx = x + dx[d];
				int ny = y + dy[d];
				if (nx < 0 || ny < 0 || nx >= C || ny >= R) continue;
				if (map[cur][ny][nx] == -1) continue;
				map[next][ny][nx] += dirt;
				cnt++;
			}
			map[next][y][x] += map[cur][y][x] - dirt * cnt;
		}
	}
	map[next][up][0] = -1;
	map[next][down][0] = -1;

	//cur 0으로 초기화
	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			map[cur][y][x] = 0;
		}
	}
	cur = next;
}

void clear()
{
	//반시계
	for (int y = up - 2; y >= 0; y--) {
		map[cur][y + 1][0] = map[cur][y][0];
	}
	for (int x = 1; x < C; x++) {
		map[cur][0][x - 1] = map[cur][0][x];
	}
	for (int y = 1; y <= up; y++) {
		map[cur][y - 1][C - 1] = map[cur][y][C - 1];
	}
	for (int x = C - 2; x >= 1; x--) {
		map[cur][up][x + 1] = map[cur][up][x];
	}
	map[cur][up][1] = 0;

	//시계
	for (int y = down + 2; y < R; y++) {
		map[cur][y - 1][0] = map[cur][y][0];
	}
	for (int x = 1; x < C; x++) {
		map[cur][R - 1][x - 1] = map[cur][R - 1][x];
	}
	for (int y = R - 2; y >= down; y--) {
		map[cur][y + 1][C - 1] = map[cur][y][C - 1];
	}
	for (int x = C - 2; x >= 1; x--) {
		map[cur][down][x + 1] = map[cur][down][x];
	}
	map[cur][down][1] = 0;
}

void solve()
{
	for (int t = 1; t <= T; t++) {
		spread();
		clear();
	}

	int ans = 0;
	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			ans += map[cur][y][x];
		}
	}
	cout << ans + 2;
}


int main()
{
	input();
	solve();
	return 0;
}