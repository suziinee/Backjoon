#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 50
int N, L, R;
int map[2][MAXN + 5][MAXN + 5];
int chk_bfs[MAXN + 5][MAXN + 5];
int chk_find[MAXN + 5][MAXN + 5];
int cur = 0;

struct AXIS { int y; int x; };
vector<AXIS> alli;
queue<AXIS> q;

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };


void input()
{
	cin >> N >> L >> R;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[0][y][x];
		}
	}
}

void bfs(const int& y, const int& x)
{
	alli = {};
	q = {};
	fill(&chk_bfs[0][0], &chk_bfs[MAXN + 4][MAXN + 5], 0);
	int sum = 0;

	q.push({ y, x });

	while (!q.empty()) {
		AXIS data = q.front(); q.pop();
		int tmp = map[cur][data.y][data.x];

		for (int d = 0; d < 4; d++) {
			int nx = data.x + dx[d];
			int ny = data.y + dy[d];

			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
			if (chk_bfs[ny][nx]) continue;

			if (abs(tmp - map[cur][ny][nx]) >= L && abs(tmp - map[cur][ny][nx]) <= R) {
				q.push({ ny, nx });
				alli.push_back({ ny, nx });
				sum += map[cur][ny][nx];
				chk_bfs[ny][nx] = 1;
				chk_find[ny][nx] = 1;
			}
		}
	}

	int divide = sum / alli.size();
	int next = (cur + 1) % 2;
	for (AXIS a : alli) {
		map[next][a.y][a.x] = divide;
	}
}

int find()
{
	int flag = 0;
	fill(&chk_find[0][0], &chk_find[MAXN + 4][MAXN + 5], 0);

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			int tmp = map[cur][y][x];
			if (chk_find[y][x]) continue;

			for (int d = 0; d < 4; d++) {
				int nx = x + dx[d];
				int ny = y + dy[d];
				if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
				if (abs(tmp - map[cur][ny][nx]) >= L && abs(tmp - map[cur][ny][nx]) <= R && chk_find[ny][nx] == 0) {
					bfs(y, x);
					flag = 1;
				}
			}
		}
	}

	int next = (cur + 1) % 2;
	if (flag) {
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				if (chk_find[y][x] == 0) map[next][y][x] = map[cur][y][x];
				map[cur][y][x] = 0;
			}
		}
		cur = next;
	}
	
	return flag;
}


int solve()
{
	int ans = 0;
	
	while (true) {
		int flag = find();
		if (flag == 0) return ans;
		ans++;
	}
}


int main(void)
{
	input();
	int ans = solve();
	cout << ans;
	return 0;
}