#include <iostream>
#include <queue>
using namespace std;

#define MAX 20
int R, C;
char map[MAX][MAX];
bool chk[26];
int ans = 1;

struct STATUS { int r; int c; int cnt; };
queue<STATUS> q;


void input()
{
	cin >> R >> C;
	for (int r = 0; r < R; r++) {
		for (int c = 0; c < C; c++) {
			cin >> map[r][c];
		}
	}
}

void dfs(STATUS cur)
{
	static int dr[] = { 0, 1, 0, -1 };
	static int dc[] = { -1, 0, 1, 0 };

	if (cur.cnt > ans) ans = cur.cnt;

	for (int d = 0; d < 4; d++) {
		int nr = cur.r + dr[d];
		int nc = cur.c + dc[d];

		if (nr < 0 || nc < 0 || nr >= R || nc >= C) continue;
		if (chk[map[nr][nc] - 'A']) continue;
		
		chk[map[nr][nc] - 'A'] = true;
		dfs({ nr, nc, cur.cnt + 1 });
		chk[map[nr][nc] - 'A'] = false;
	}
}

void solve()
{
	chk[map[0][0] - 'A'] = true;
	dfs({ 0, 0, 1 });
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}