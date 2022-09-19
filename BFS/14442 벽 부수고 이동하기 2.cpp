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

	vector<int> candi;

	q.push({ 0, 0, 0, 1 });
	chk[0][0][0] = true;
	if (N - 1 == 0 && M - 1 == 0) return 1;

	while (!q.empty()) {
		AXIS cur = q.front(); q.pop();

		for (int d = 0; d < 4; d++) {
			AXIS next;
			next.x = cur.x + dx[d];
			next.y = cur.y + dy[d];
			next.dist = cur.dist + 1;

			if (next.x < 0 || next.y < 0 || next.x >= M || next.y >= N) continue;
			if (map[next.y][next.x] == '1' && cur.k == K) continue;
			next.k = (map[next.y][next.x] == '1') ? (cur.k + 1) : cur.k;

			if (chk[next.y][next.x][next.k] == false) {
				chk[next.y][next.x][next.k] = true;
				q.push(next);
				if (next.y == N - 1 && next.x == M - 1) return next.dist;
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