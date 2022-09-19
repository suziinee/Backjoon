#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
using namespace std;

#define MAXN 1000
#define MAXK 10
int N, M, K;
string map[MAXN];

int chk[MAXN][MAXN][MAXK + 1]; //(y, x)까지 k번 벽을 부수면서 간 최단 경로 기록
struct AXIS { int y; int x; int k; };
queue<AXIS> q;


void input()
{
	cin >> N >> M >> K;
	for (int y = 0; y < N; y++) {
		cin >> map[y];
	}
}


int bfs()
{
	static int dx[] = { 0, 1, 0, -1 };
	static int dy[] = { -1, 0, 1, 0 };
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			for (int k = 0; k <= K; k++) {
				chk[y][x][k] = 0x7fffffff;
			}
		}
	}

	q.push({ 0, 0, 0 });
	chk[0][0][0] = 1;
	//if (N - 1 == 0 && M - 1 == 0) return 0;

	while (!q.empty()) {
		AXIS cur = q.front(); q.pop();

		for (int d = 0; d < 4; d++) {
			int nx = cur.x + dx[d];
			int ny = cur.y + dy[d];

			if (nx < 0 || ny < 0 || nx >= M || ny >= N) continue;

			if (map[ny][nx] == '0') { //0일때 그대로 이동
				if (chk[ny][nx][cur.k] > chk[cur.y][cur.x][cur.k] + 1) {
					chk[ny][nx][cur.k] = chk[cur.y][cur.x][cur.k] + 1;
					q.push({ ny, nx, cur.k });
				}
			}
			else { //벽일때
				if (cur.k >= K) { //더이상 벽을 부술 수 없음
					continue;
				}
				else if (cur.k < K) { //벽을 부술 수 있음
					if (chk[ny][nx][cur.k + 1] > chk[cur.y][cur.x][cur.k] + 1) {
						chk[ny][nx][cur.k + 1] = chk[cur.y][cur.x][cur.k] + 1;
						q.push({ ny, nx, cur.k + 1 });
					}
				}
			}
		}
	}

	int ret = 0x7fffffff;
	for (int k = 0; k <= K; k++) {
		ret = min(ret, chk[N - 1][M - 1][k]);
	}
	return ret;
}


void solve()
{
	int ans = bfs();

	if (ans == 0x7fffffff) cout << -1;
	else cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}