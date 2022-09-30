#include <iostream>
#include <cmath>
using namespace std;

int N, Q, LEN;
int map[2][64][64];
int L[1000];
int cur;

bool chk[64][64];
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

void rotate(int sy, int sx, int n, const int& next)
{
	int nx = sx;
	for (int y = sy; y < sy + n; y++) {
		int ny = sy + n - 1;
		for (int x = sx; x < sx + n; x++) {
			map[next][y][x] = map[cur][ny][nx];
			ny--;
		}
		nx++;
	}
}

void firestorm(int n)
{
	if (n == 0) return;
	int next = (cur + 1) % 2;

	for (int y = 0; y < LEN; y += n) {
		for (int x = 0; x < LEN; x += n) {
			rotate(y, x, n, next);
		}
	}

	cur = next;
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

void dfs(int y, int x, int& cnt)
{
	cnt++;
	chk[y][x] = true;
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (nx < 0 || ny < 0 || nx >= LEN || ny >= LEN) continue;
		if (map[cur][ny][nx] == 0 || chk[ny][nx]) continue;
		dfs(ny, nx, cnt);
	}
}

void solve()
{
	for (int i = 0; i < Q; i++) {
		firestorm(pow(2, L[i]));
		melt();
	}

	int sum = 0; int max_cnt = 0;
	for (int y = 0; y < LEN; y++) {
		for (int x = 0; x < LEN; x++) {
			if (map[cur][y][x]) sum += map[cur][y][x];
			if (map[cur][y][x] && chk[y][x] == false) {
				int cnt = 0;
				dfs(y, x, cnt);
				max_cnt = max(cnt, max_cnt);
			}
		}
	}
	
	cout << sum << "\n" << max_cnt;
}


int main()
{
	input();
	solve();
	return 0;
}