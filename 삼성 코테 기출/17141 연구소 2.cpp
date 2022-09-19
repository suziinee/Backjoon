#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define MAXN 50
#define MAXM 10
int N, M;
int map[MAXN][MAXN];
int ans = 0x7fffffff;

struct AXIS { int y; int x; };
vector<AXIS> virus; //2의 좌표 모음
AXIS pick[MAXM];

queue<AXIS> q;
int time[MAXN][MAXN];


void input()
{
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
			if (map[y][x] == 2) virus.push_back({ y, x });
		}
	}
}


int count_time()
{
	static int dx[] = { 0, 1, 0, -1 };
	static int dy[] = { -1, 0, 1, 0 };

	q = {};
	fill(&time[0][0], &time[MAXN - 1][MAXN], -1);
	for (int i = 0; i < M; i++) {
		q.push(pick[i]);
		time[pick[i].y][pick[i].x] = 0;
	}

	while (!q.empty()) {
		AXIS cur = q.front(); q.pop();

		for (int d = 0; d < 4; d++) {
			int nx = cur.x + dx[d];
			int ny = cur.y + dy[d];

			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
			if (map[ny][nx] == 1 || time[ny][nx] != -1) continue;
			
			time[ny][nx] = time[cur.y][cur.x] + 1;
			q.push({ ny, nx });
		}
	}

	//전부 감염되었는지 확인 
	int max_time = 0;
	bool complete = true;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map[y][x] == 0 && time[y][x] == -1) { complete = false; break; }
			max_time = max(max_time, time[y][x]);
		}
	}

	if (complete) return max_time;
	else return 0x7fffffff;
}


void dfs_virus(int s, int n)
{
	if (n == M) {
		int t = count_time();
		if (ans > t) ans = t;
		return;
	}

	for (int i = s; i < virus.size(); i++) {
		pick[n] = virus[i];
		dfs_virus(i + 1, n + 1);
	}
}


void solve()
{
	dfs_virus(0, 0);

	if (ans == 0x7fffffff) cout << -1;
	else cout << ans;
}


int main(void)
{
	input();
	solve();
	return 0;
}