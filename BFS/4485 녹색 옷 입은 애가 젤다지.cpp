#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 125
int N;
int map[MAXN][MAXN];
int dp[MAXN][MAXN];

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };
struct AXIS { int y; int x; };
queue<AXIS> q;


int bfs()
{
	fill(&dp[0][0], &dp[MAXN - 1][MAXN], 0x7fffffff);
	
	q.push({ 0, 0 });
	dp[0][0] = map[0][0];
	
	while (!q.empty()) {
		AXIS data = q.front(); q.pop();

		for (int d = 0; d < 4; d++) {
			int nx = data.x + dx[d];
			int ny = data.y + dy[d];
			
			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
			if (dp[ny][nx] <= dp[data.y][data.x] + map[ny][nx]) continue;
			
			dp[ny][nx] = dp[data.y][data.x] + map[ny][nx];
			q.push({ ny, nx });
		}
	}

	return dp[N - 1][N - 1];
}

void input()
{
	int t = 1;
	while (true) {
		cin >> N;
		if (N == 0) return;

		//초기화
		fill(&map[0][0], &map[MAXN - 1][MAXN], 0);
		q = {};

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				cin >> map[y][x];
			}
		}

		int ans = bfs();
		printf("Problem %d: %d\n", t, ans);
		t++;
	}
}


int main(void)
{
	input();
	return 0;
}