#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define MAX 8
int N, M;
int map[MAX][MAX];
int ans = 0;

struct AXIS { int y; int x; };
vector<AXIS> blank;
vector<AXIS> virus;
AXIS pick[3];

queue<AXIS> q;
int chk[MAX][MAX];


void input()
{
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> map[y][x];
			if (map[y][x] == 0) blank.push_back({ y, x });
			else if (map[y][x] == 2) virus.push_back({ y, x });
		}
	}
}

int count_blank()
{
	static int dx[] = { 0, 1, 0, -1 };
	static int dy[] = { -1, 0, 1, 0 };

	for (AXIS a : pick) { map[a.y][a.x] = 1; };
	q = {};
	fill(&chk[0][0], &chk[MAX - 1][MAX], 0);

	for (AXIS v : virus) {
		q.push(v);
		chk[v.y][v.x] = 1;
	}

	while (!q.empty()) {
		AXIS cur = q.front(); q.pop();

		for (int d = 0; d < 4; d++) {
			int nx = cur.x + dx[d];
			int ny = cur.y + dy[d];

			if (nx < 0 || ny < 0 || nx >= M || ny >= N) continue;
			if (map[ny][nx] != 0) continue;
			if (chk[ny][nx]) continue;

			chk[ny][nx] = 1;
			q.push({ ny, nx });
		}
	}

	int sum = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (map[y][x] == 0 && chk[y][x] == 0) sum++;
		}
	}

	for (AXIS a : pick) { map[a.y][a.x] = 0; };
	return sum;
}

void dfs_blank(int s, int n) //blank 배열에서 벽 3개를 조합으로 뽑는 함수
{
	if (n == 3) {
		int c = count_blank();
		if (c > ans) ans = c;
		return;
	}

	for (int i = s; i < blank.size(); i++) {
		pick[n] = blank[i];
		dfs_blank(i + 1, n + 1);
	}
}

void solve()
{
	dfs_blank(0, 0);
	cout << ans;
}


int main(void)
{
	input();
	solve();
	return 0;
}