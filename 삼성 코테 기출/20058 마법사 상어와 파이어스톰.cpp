#include <iostream>
#include <cmath>
using namespace std;

#define MAXN 64
int N, Q, LEN;
int map[2][MAXN][MAXN];
int chk[MAXN][MAXN];
int L[1000];
int cur;

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };


void input()
{
	cin >> N >> Q;
	LEN = pow(2, N);
	for (int y = 0; y < LEN; y++) {
		for (int x = 0; x < LEN; x++) {
			cin >> map[cur][y][x];
		}
	}
	for (int i = 0; i < Q; i++) {
		cin >> L[i];
	}
}

//(Y, X)에서 시작하는 길이 n인 격자 90도 회전
void rotate(const int& cur, const int& next, int Y, int X, const int& len)
{
	//cur 좌표 기준
	int nx = X + len - 1;
	for (int y = Y; y < Y + len; y++) {
		int ny = Y;
		for (int x = X; x < X + len; x++) {
			map[next][ny][nx] = map[cur][y][x];
			ny++;
		}
		nx--;
	}
}

void move_(const int& l)
{
	if (l == 0) return;

	int next = (cur + 1) % 2;
	int len = pow(2, l);
	for (int y = 0; y < LEN; y += len) {
		for (int x = 0; x < LEN; x += len) {
			rotate(cur, next, y, x, len);
		}
	}
	cur = next;
}

void decrease()
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
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (nx < 0 || ny < 0 || nx >= LEN || ny >= LEN) continue;
		if (map[cur][ny][nx] == 0) continue;
		if (chk[ny][nx]) continue;
		chk[ny][nx] = 1;
		dfs(ny, nx, cnt);
	}
}

void solve()
{
	for (int i = 0; i < Q; i++) {
		move_(L[i]);
		decrease();
	}

	int sum = 0;
	int max = 0;
	for (int y = 0; y < LEN; y++) {
		for (int x = 0; x < LEN; x++) {
			sum += map[cur][y][x];
			
			if (chk[y][x] == 0 && map[cur][y][x]) {
				int cnt = 0;
				chk[y][x] = 1;
				dfs(y, x, cnt);
				if (cnt > max) max = cnt;
			}
		}
	}
	if (max <= 1) max = 0;

	cout << sum << "\n" << max;
}


int main()
{
	input();
	solve();
	return 0;
}