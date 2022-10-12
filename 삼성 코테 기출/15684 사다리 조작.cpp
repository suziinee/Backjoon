#include <iostream>
using namespace std;

#define MAXN 10
#define MAXH 30
int N, M, H;
int map[MAXH + 1][MAXN + 1];
int ans = 4;


void input()
{
	cin >> N >> M >> H;
	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		map[a][b] = 1;
	}
}

bool check()
{
	for (int i = 1; i <= N; i++) { //사다리가 아닌 세로선
		int x = i;

		for (int y = 1; y <= H; y++) {
			if (map[y][x - 1]) x--; //왼쪽 이동
			else if (map[y][x]) x++; //오른쪽 이동
		}

		if (x != i) return false;
	}
	return true;
}

void dfs(int cnt, int y, int x)
{
	if (cnt >= ans) return;
	if (check()) {
		ans = cnt;
		return;
	}
	if (cnt == 3) return;

	for (int i = y; i <= H; i++) {
		for (int j = x; j < N; j++) {
			if (map[i][j] || map[i][j - 1] || map[i][j + 1]) continue;
			map[i][j] = 1;
			dfs(cnt + 1, i, j);
			map[i][j] = 0;
		}
		x = 1;
	}
}

void solve()
{
	dfs(0, 1, 1);
	if (ans == 4) cout << -1;
	else cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}