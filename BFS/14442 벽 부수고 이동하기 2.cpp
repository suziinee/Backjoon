#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
using namespace std;

#define MAXN 1000
#define MAXK 10
int N, M, K;
string map[MAXN];

bool chk[MAXN][MAXN][MAXK + 1]; 
struct AXIS { int y; int x; int k; int dist; };
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

	q.push({ 0, 0, 0, 1 });
	chk[0][0][0] = true;
	if (N - 1 == 0 && M - 1 == 0) return 1;

	while (!q.empty()) {
		AXIS cur = q.front(); q.pop();

		for (int d = 0; d < 4; d++) {
			int nx = cur.x + dx[d];
			int ny = cur.y + dy[d];

			if (nx < 0 || ny < 0 || nx >= M || ny >= N) continue;

			if (map[ny][nx] == '0') { //0일때 그대로 이동
				if (chk[ny][nx][cur.k] == false) {
					chk[ny][nx][cur.k] = true;
					q.push({ ny, nx, cur.k, cur.dist + 1 });
					if (ny == N - 1 && nx == M - 1) return cur.dist + 1;
				}
			}
			else { //벽일때
				if (cur.k >= K) { //더이상 벽을 부술 수 없음
					continue;
				}
				else if (cur.k < K) { //벽을 부술 수 있음
					if (chk[ny][nx][cur.k + 1] == false) {
						chk[ny][nx][cur.k + 1] = true;
						q.push({ ny, nx, cur.k + 1, cur.dist + 1 });
						if (ny == N - 1 && nx == M - 1) cur.dist + 1;
					}
				}
			}
		}
	}

	return -1;
}


void solve()
{
	int ans = bfs();
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}