#include <iostream>
#include <vector>
using namespace std;

#define MAXN 50
int N, M;
int map[MAXN + 1][MAXN + 1];
int cloud[MAXN + 1][MAXN + 1];

struct AXIS { int y; int x; };
struct MOVE { int d; int s; };
vector<MOVE> order;


void input()
{
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
		}
	}
	int d, s;
	for (int i = 0; i < M; i++) {
		cin >> d >> s;
		order.push_back({ d, s });
	}
}

void move_cloud(MOVE m)
{
	static int dx[] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
	static int dy[] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };

	vector<AXIS> new_cloud;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (cloud[y][x]) {
				int nx = ((x + N * 100) + m.s*dx[m.d]) % N;
				int ny = ((y + N * 100) + m.s*dy[m.d]) % N;
				cloud[y][x] = 0;
				new_cloud.push_back({ ny, nx });
			}
		}
	}

	for (AXIS c : new_cloud) cloud[c.y][c.x] = 1;
}

void rain()
{
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (cloud[y][x]) map[y][x]++;
		}
	}
}

void water_copy_bug()
{
	static int dx[] = { -1, 1, 1, -1 };
	static int dy[] = { -1, -1, 1, 1 };

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (cloud[y][x]) {
				int water_cnt = 0;
				for (int dir = 0; dir < 4; dir++) {
					int nx = x + dx[dir];
					int ny = y + dy[dir];

					if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
					if (map[ny][nx] == 0) continue;

					water_cnt++;
				}
				map[y][x] += water_cnt;
			}
		}
	}
}

void make_cloud()
{
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (cloud[y][x] == 0 && map[y][x] >= 2) {
				cloud[y][x] = 1;
				map[y][x] -= 2;
			}
			else if (cloud[y][x]) { //구름이 여기서 사라짐
				cloud[y][x] = 0;
			}
		}
	}
}


void solve()
{
	cloud[N - 1][0] = 1;
	cloud[N - 1][1] = 1;
	cloud[N - 2][0] = 1;
	cloud[N - 2][1] = 1;

	for (MOVE m : order) {
		move_cloud(m);
		rain();
		water_copy_bug();
		make_cloud();
	}

	int ans = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			ans += map[y][x];
		}
	}
	cout << ans;
}


int main(void)
{
	input();
	solve();
	return 0;
}