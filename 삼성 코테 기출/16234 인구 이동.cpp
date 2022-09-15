#include <iostream>
#include <queue>
using namespace std;

#define MAXN 50
int N, L, R;
int map[MAXN][MAXN];
int chk[MAXN][MAXN];

struct AXIS { int y; int x; };
queue<AXIS> q;

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };


void input()
{
	cin >> N >> L >> R;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
		}
	}
}

void bfs(int y, int x, int area_index, int& count, int& sum)
{
	q = {};

	q.push({ y, x });
	chk[y][x] = area_index;
	count++;
	sum += map[y][x];

	while (!q.empty()) {
		AXIS cur = q.front(); q.pop();

		for (int d = 0; d < 4; d++) {
			int nx = cur.x + dx[d];
			int ny = cur.y + dy[d];

			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
			if (chk[ny][nx]) continue;
			int abs_ = abs(map[ny][nx] - map[cur.y][cur.x]);
			if (abs_ < L || abs_ > R) continue;

			q.push({ ny, nx });
			chk[ny][nx] = area_index;
			count++;
			sum += map[ny][nx];
		}
	}
}

void solve()
{
	int ans = 0;
	bool is_update = true;

	while (is_update) {
		is_update = false;

		fill(&chk[0][0], &chk[MAXN - 1][MAXN], 0);

		int area_index = 0;
		int count[MAXN*MAXN / 2 + 1] = { 0 }; //area_index의 인덱스에 담길 연합구역의 나라 개수
		int sum[MAXN*MAXN / 2 + 1] = { 0 }; //area_index의 인덱스에 담길 연합구역의 인구 합

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				if (chk[y][x] == 0) {
					//연합이 있는지 확인하고 bfs 보내기
					for (int d = 0; d < 4; d++) {
						int nx = x + dx[d];
						int ny = y + dy[d];
						
						if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
						if (chk[ny][nx]) continue;

						int abs_ = abs(map[ny][nx] - map[y][x]);
						if (abs_ >= L && abs_ <= R) {
							area_index++;
							bfs(y, x, area_index, count[area_index], sum[area_index]);
							break;
						}
					}
				}
			}
		}

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				if (chk[y][x]) { //인구이동이 있었음
					int index = chk[y][x];
					int avg = sum[index] / count[index];
					map[y][x] = avg;
					is_update = true;	
				}
			}
		}

		if (is_update) ans++;
	}

	cout << ans;
}


int main(void)
{
	input();
	solve();
	return 0;
}