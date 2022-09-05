#include <iostream>
#include <queue>
using namespace std;

#define MAX 1000
int n, m;
struct POS { int x; int y; int ans; };
char map[MAX + 5][MAX + 5];
int ans = 0x7fffffff;


void input()
{
	cin >> n >> m;
	for (int y = 1; y <= n; y++) {
		cin >> &map[y][1];
	}
}

int bfs(const int& x, const int& y, int flag) //(x, y)에서부터 bfs
{
	queue<POS> q;
	bool chk[MAX + 5][MAX + 5] = { false };
	q.push({ x, y, 1 });
	chk[x][y] = true;

	const int dx[] = { 0, 1, 0, -1 };
	const int dy[] = { -1, 0, 1, 0 };

	while (!q.empty()) {
		POS tmp = q.front(); q.pop();
		POS next;
		next.ans = tmp.ans + 1;

		for (int dir = 0; dir < 4; dir++) {
			next.x = tmp.x + dx[dir];
			next.y = tmp.y + dy[dir];
			
			if (next.x<1 || next.y<1 || next.x>m || next.y>n) continue;

			if (map[next.y][next.x] == '1' && flag == 1) {
				int b = bfs(next.y, next.x, 0); //길을 못찾았을 경우 0x7fffffff
				if (b != 0x7fffffff) {
					if (next.ans + b - 1 < ans) ans = next.ans + b - 1;
				}
				continue;
			}

			if (chk[next.y][next.x] == true) continue;
			if (map[next.y][next.x] == '1' && flag == 0) continue;
			
			if (next.x == m && next.y == n) return next.ans;
			q.push(next);
			chk[next.y][next.x] = true;
		}
	}

	return 0x7fffffff;
}

void solve()
{
	bfs(1, 1, 1);
}

void output()
{
	if (ans == 0x7fffffff) cout << -1;
	else cout << ans;
}


int main()
{
	input();
	solve();
	output();
	return 0;
}