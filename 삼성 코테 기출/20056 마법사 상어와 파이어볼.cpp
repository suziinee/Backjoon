#include <iostream>
#include <vector>
using namespace std;

#define MAXN 50
int N, M, K;

struct FIREBALL {
	int m, s, d;
};
vector<FIREBALL> map[MAXN][MAXN];

const int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
const int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };


void input()
{
	cin >> N >> M >> K;
	int y, x, m, s, d;
	for (int i = 1; i <= M; i++) {
		cin >> y >> x >> m >> s >> d;
		y--; x--;
		map[y][x].push_back({ m, s, d });
	}
}

void move_fireball()
{
	vector<FIREBALL> back[MAXN][MAXN];

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (!map[y][x].empty()) {
				for (FIREBALL f : map[y][x]) {
					int nx = (x + dx[f.d] * (f.s % N) + N) % N;
					int ny = (y + dy[f.d] * (f.s % N) + N) % N;
					back[ny][nx].push_back({ f });
				}
			}
		}
	}

	copy(&back[0][0], &back[MAXN - 1][MAXN], &map[0][0]);
}

void unite_fireball()
{
	vector<FIREBALL> back[MAXN][MAXN];

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map[y][x].empty()) {
				continue;
			}
			else if (map[y][x].size() == 1) {
				back[y][x].push_back(map[y][x][0]);
			}
			else {
				int sum_m = 0;
				int sum_s = 0;
				int init_d = (map[y][x][0].d % 2);
				bool flag = true;
				for (FIREBALL f : map[y][x]) {
					sum_m += f.m;
					sum_s += f.s;
					if (f.d % 2 != init_d) flag = false;
				}

				sum_m /= 5;
				if (sum_m) {
					sum_s /= map[y][x].size();
					if (flag) {
						for (int i = 0; i < 4; i++) {
							back[y][x].push_back({ sum_m, sum_s, i * 2 });
						}
					}
					else {
						for (int i = 0; i < 4; i++) {
							back[y][x].push_back({ sum_m, sum_s, i * 2 + 1 });
						}
					}
				}
			}
		}
	}

	copy(&back[0][0], &back[MAXN - 1][MAXN], &map[0][0]);
}

void solve()
{
	for (int i = 0; i < K; i++) {
		move_fireball();
		unite_fireball();
	}

	int ans = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map[y][x].empty()) continue;
			for (FIREBALL f : map[y][x]) {
				ans += f.m;
			}
		}
	}
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}