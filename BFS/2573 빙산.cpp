#include <iostream>
using namespace std;

#define MAX 300
int N, M;
int map[2][MAX][MAX];
bool chk[MAX][MAX];
int cur;

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };


void input()
{
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> map[0][y][x];
		}
	}
}

void melt()
{
	int next = (cur + 1) % 2;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (map[cur][y][x] == 0) {
				map[next][y][x] = map[cur][y][x];
				continue;
			}

			int cnt = 0;
			for (int d = 0; d < 4; d++) {
				int nx = x + dx[d];
				int ny = y + dy[d];
				if (map[cur][ny][nx] == 0) cnt++;
			}

			map[next][y][x] = map[cur][y][x] - cnt;
			if (map[next][y][x] < 0) map[next][y][x] = 0;
		}
	}
	cur = next;
}

void dfs(int y, int x)
{
	chk[y][x] = true;
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (map[cur][ny][nx] == 0 || chk[ny][nx]) continue;
		dfs(ny, nx);
	}
}

void solve()
{
	int ans = 0;
	bool update = true;
	while (update) {
		update = false;
		ans++;

		melt();

		int cnt = 0;
		fill(&chk[0][0], &chk[MAX - 1][MAX], false);
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < M; x++) {
				if (map[cur][y][x] && chk[y][x] == false) {
					update = true;
					cnt++;
					dfs(y, x);
				}
			}
		}

		if (cnt >= 2) {
			cout << ans;
			return;
		}
	}
	cout << 0;
}


int main()
{
	input();
	solve();
	return 0;
}