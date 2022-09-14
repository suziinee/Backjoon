#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

#define MAXN 50
int N;
string map[MAXN];
int dp[MAXN][MAXN];

struct AXIS { int y; int x; };
queue<AXIS> q;


void input()
{
	cin >> N;
	for (int i = 0; i < N; i++) { cin >> map[i]; }
}

int bfs()
{
	static int dx[] = { 0, 1, 0, -1 };
	static int dy[] = { -1, 0, 1, 0 };

	q.push({ 0, 0 });
	dp[0][0] = 0;
	if (0 == N - 1) return 0;

	while (!q.empty()) {
		AXIS data = q.front(); q.pop();

		for (int d = 0; d < 4; d++) {
			int nx = data.x + dx[d];
			int ny = data.y + dy[d];

			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;

			if (map[ny][nx] == '1' && dp[ny][nx] > dp[data.y][data.x]) { //흰 방
				dp[ny][nx] = dp[data.y][data.x];
				q.push({ ny, nx });
			}
			else if (map[ny][nx] == '0' && dp[ny][nx] > dp[data.y][data.x] + 1) { //검은방
				dp[ny][nx] = dp[data.y][data.x] + 1;
				q.push({ ny, nx });
			}
		}
	}

	return dp[N - 1][N - 1];
}

void solve()
{
	fill(&dp[0][0], &dp[MAXN - 1][MAXN], 0x7fffffff);
	int ans = bfs();
	cout << ans;
}


int main(void)
{
	input();
	solve();
	return 0;
}