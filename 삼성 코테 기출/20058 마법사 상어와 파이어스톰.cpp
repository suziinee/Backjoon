#include <iostream>
#include <cmath>
using namespace std;

#define MAXN 64
#define MAXQ 1000
int N, Q, LEN;
int map[2][MAXN][MAXN];
int L[MAXQ];
int cur;

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };


void input()
{
	cin >> N >> Q;
	LEN = pow(2, N);
	for (int y = 0; y < LEN; y++) {
		for (int x = 0; x < LEN; x++) {
			cin >> map[0][y][x];
		}
	}
	for (int i = 0; i < Q; i++) {
		cin >> L[i];
	}
}

void rotate(int y, int x, int len, int tar)
{
	if (len == tar) {
		int next = (cur + 1) % 2;
		int nx = x;
		for (int i = y; i < y + tar; i++) {
			int ny = y + tar - 1;
			for (int j = x; j < x + tar; j++) {
				map[next][i][j] = map[cur][ny][nx];
				ny--;
			}
			nx++;
		}
		return;
	}

	int n = len / 2;
	rotate(y, x, n, tar);
	rotate(y + n, x, n, tar);
	rotate(y, x + n, n, tar);
	rotate(y + n, x + n, n, tar);
}

void melt()
{
	int next = (cur + 1) % 2;
	for (int y = 0; y < LEN; y++) {
		for (int x = 0; x < LEN; x++) {
			int cnt = 0;
			for (int d = 0; d < 4; d++) {
				int nx = x + dx[d];
				int ny = y + dy[d];
				if (nx < 0 || ny < 0 || nx >= LEN || ny >= LEN) continue;
				if (map[cur][ny][nx] == 0) continue;
				cnt++;
			}
			if (cnt >= 3 || map[cur][y][x] == 0) {
				map[next][y][x] = map[cur][y][x];
			}
			else {
				map[next][y][x] = map[cur][y][x] - 1;
			}
		}
	}
	cur = next;
}

void dfs(int y, int x, int& cnt, bool(*chk)[MAXN])
{
	cnt++;
	chk[y][x] = true;
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (nx < 0 || ny < 0 || nx >= LEN || ny >= LEN) continue;
		if (map[cur][ny][nx] == 0 || chk[ny][nx]) continue;
		dfs(ny, nx, cnt, chk);
	}
}

void solve()
{
	for (int i = 0; i < Q; i++) {
		rotate(0, 0, LEN, pow(2, L[i]));
		cur = (cur + 1) % 2;
		melt();
	}

	int sum = 0; int max_ice = 0;
	bool chk[MAXN][MAXN] = { false, };
	for (int y = 0; y < LEN; y++) {
		for (int x = 0; x < LEN; x++) {
			if (map[cur][y][x]) {
				sum += map[cur][y][x];
				if (chk[y][x] == false) {
					int cnt = 0;
					dfs(y, x, cnt, chk);
					if (cnt > max_ice) max_ice = cnt;
				}
			}

		}
	}
	cout << sum << "\n" << max_ice;
}


int main()
{
	input();
	solve();
	return 0;
}