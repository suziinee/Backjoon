#include <iostream>
using namespace std;

#define MAXN 10
#define MAXH 30
int N, M, H;
int map[MAXH + 1][MAXN + 1];
int ans = 0x7fffffff;


void input()
{
	cin >> N >> M >> H;
	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		map[a][b] = 1;
		map[a][b + 1] = 2;
	}
}

bool check()
{
	for (int x = 1; x <= N; x++) {
		//(1, x)에서 출발)
		int curx = x; int cury = 1;
		bool down = true;

		while (cury <= H) {
			switch (map[cury][curx]) {
			case 0: {
				cury++;
				down = true;
				break;
			}
			case 1: {
				if (down) { //내려온 다음이면 오른쪽으로 가기
					down = false;
					curx++;
				}
				else { //왼쪽에서 온거면 내려가기
					cury++;
					down = true;
				}
				break;
			}
			case 2: {
				if (down) { //내려온 다음이면 왼쪽으로 가기
					down = false;
					curx--;
				}
				else { //오른쪽에서 온거면 내려가기
					cury++;
					down = true;
				}
				break;
			}
			}
		}
		if (curx != x) return false;
	}
	return true;
}

void dfs(int cnt)
{
	if (cnt >= ans) return;
	if (cnt > 3) return;
	if (check()) {
		if (ans > cnt) ans = cnt;
		return;
	}

	for (int y = 1; y <= H; y++) {
		for (int x = 1; x <= N; x++) {
			if (map[y][x]) continue; //0인 곳에 대해서
			if (x - 1 >= 1 && map[y][x - 1] == 0) { //왼쪽으로 가로선 놓기
				map[y][x] = 2;
				map[y][x - 1] = 1;
				dfs(cnt + 1);
				map[y][x] = 0;
				map[y][x - 1] = 0;
			}
			if (x + 1 <= N && map[y][x + 1] == 0) { //오른쪽으로 가로선 놓기
				map[y][x] = 1;
				map[y][x + 1] = 2;
				dfs(cnt + 1);
				map[y][x] = 0;
				map[y][x + 1] = 0;
			}
		}
	}
}

void solve()
{
	dfs(0);
	if (ans == 0x7fffffff) cout << -1;
	else cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}