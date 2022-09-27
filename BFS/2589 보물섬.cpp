#include <iostream>
#include <queue>
using namespace std;

#define MAXNM 50
int N, M;
char map[MAXNM][MAXNM];
int chk[MAXNM][MAXNM];

struct AXIS { int y; int x; int cnt; };
queue<AXIS> q;
const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };


void input()
{
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> map[y][x];
		}
	}
}

void dfs(int y, int x, int chk_cnt)
{
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (nx < 0 || ny < 0 || nx >= M || ny >= N) continue;
		if (map[ny][nx] == 'W' || chk[ny][nx] != 0) continue;
		chk[ny][nx] = chk_cnt;
		dfs(ny, nx, chk_cnt);
	}
}

int bfs(int y, int x, const int& n)
{
	q = {};
	bool visited[MAXNM][MAXNM] = { false };
	q.push({ y, x, 0 });
	visited[y][x] = true;

	AXIS cur;
	while (!q.empty()) {
		cur = q.front(); q.pop();

		for (int d = 0; d < 4; d++) {
			int nx = cur.x + dx[d];
			int ny = cur.y + dy[d];
			if (nx < 0 || ny < 0 || nx >= M || ny >= N) continue;
			if (map[ny][nx] == 'W' || chk[ny][nx] != n || visited[ny][nx]) continue;
			visited[ny][nx] = true;
			q.push({ ny, nx, cur.cnt + 1 });
		}
	}
	return cur.cnt;
}

void solve()
{
	//육지 각 영역 표시
	int chk_cnt = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (map[y][x] == 'L' && chk[y][x] == 0) {
				chk_cnt++;
				chk[y][x] = chk_cnt;
				dfs(y, x, chk_cnt);
			}
		}
	}

	//모든 육지에서 bfs 시도
	int ans = -1;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (chk[y][x] != 0) {
				int ret = bfs(y, x, chk[y][x]);
				if (ret > ans) ans = ret;
			}
		}
	}
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}

