#include <iostream>
#include <queue>
using namespace std;

#define MAX 1000
int n, m;
struct POS { int x; int y; int ans; };
char map[MAX + 5][MAX + 5];


void input()
{
	cin >> n >> m;
	for (int y = 1; y <= n; y++) {
		cin >> &map[y][1];
	}
}

int bfs(const int& x, const int& y)
{
	map[y][x] = '0'; //부순 벽

	queue<POS> q;
	bool chk[MAX + 5][MAX + 5] = { false };
	q.push({ 1, 1, 1 });
	chk[1][1] = true;

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
			if (map[next.y][next.x] != '0') continue;
			if (chk[next.y][next.x] ==  true) continue;
			
			if (next.x == m && next.y == n) {
				map[y][x] = '1'; //벽 다시 복구
				return next.ans;
			}
			q.push(next);
			chk[next.y][next.x] = true;
		}
	}

	map[y][x] = '1'; //벽 다시 복구
	return 0x7fffffff;
}

int solve()
{
	int ans = bfs(0, 0); //초기값은 벽을 안부수고 이동했을 경우

	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= m; x++) {
			if (map[y][x] == '1') {
				//가지치기
				int cnt = 0;
				const int dx[] = { 0, 1, 0, -1 };
				const int dy[] = { -1, 0, 1, 0 };
				for (int dir = 0; dir < 4; dir++) {
					int nx = x + dx[dir];
					int ny = y + dy[dir];
					if (nx < 1 || ny < 1 || nx > m || ny > n) {
						cnt++; continue;
					}
					if (map[ny][nx] == '1') {
						cnt++; continue;
					}
				}
				if (cnt < 4) {
					int b = bfs(x, y);
					if (b < ans) ans = b;
				}
			}
		}
	}

	return ans;
}

void output(const int& ans)
{
	if (ans == 0x7fffffff) cout << -1;
	else cout << ans;
}


int main()
{
	input();
	int ans = solve();
	output(ans);
	return 0;
}