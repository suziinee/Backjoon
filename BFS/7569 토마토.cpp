#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define MAX 100
int M, N, H; //가로, 세로, 높이
int box[MAX][MAX][MAX];

struct TOM { int h; int y; int x; int day; };
vector<TOM> ripen;
queue<TOM> q;
int yet_ripen = 0;


void input()
{
	cin >> M >> N >> H;
	for (int h = 0; h < H; h++) {
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < M; x++) {
				cin >> box[h][y][x];
				if (box[h][y][x] == 1) ripen.push_back({ h, y, x, 0 });
				if (box[h][y][x] == 0) yet_ripen++;
			}
		}
	}
}

int bfs()
{
	int max_day = -1;
	static int dx[] = { 0, 1, 0, -1, 0, 0 };
	static int dy[] = { -1, 0, 1, 0, 0, 0 };
	static int dh[] = { 0, 0, 0, 0, 1, -1 };

	for (TOM t : ripen) q.push(t);

	while (!q.empty()) {
		TOM data = q.front(); q.pop();
		if (max_day < data.day) max_day = data.day;

		for (int d = 0; d < 6; d++) {
			int nx = data.x + dx[d];
			int ny = data.y + dy[d];
			int nh = data.h + dh[d];

			if (nx < 0 || ny < 0 || nh < 0 || nx >= M || ny >= N || nh >= H) continue;
			if (box[nh][ny][nx] != 0) continue;

			box[nh][ny][nx] = 1;
			yet_ripen--;
			q.push({ nh, ny, nx, data.day + 1 });
		}
	}

	if (yet_ripen) return -1;
	else return max_day;
}

void solve()
{
	//모든 토마토가 익어있는 상태인지 체크
	if (yet_ripen == 0) {
		cout << 0;
		return;
	}

	int ans = bfs();
	cout << ans;
}


int main(void)
{
	input();
	solve();
	return 0;
}