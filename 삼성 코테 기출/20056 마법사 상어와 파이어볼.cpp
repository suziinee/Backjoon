#include <iostream>
#include <vector>
using namespace std;

#define MAXN 50
int N, M, K;

struct FIREBALL { int m; int s; int d; };
vector<FIREBALL> map[2][MAXN][MAXN];
int cur = 0;


void input()
{
	cin >> N >> M >> K;
	int y, x, m, s, d;
	for (int i = 0; i < M; i++) {
		cin >> y >> x >> m >> s >> d;
		y--; x--; 
		map[cur][y][x].push_back({ m, s, d });
	}
}


void move()
{
	static int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	static int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };

	int next = (cur + 1) % 2;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map[cur][y][x].empty()) continue;
			for (FIREBALL f : map[cur][y][x]) {
				int nx = (x + (f.s % N) * dx[f.d] + N) % N;
				int ny = (y + (f.s % N) * dy[f.d] + N) % N;
				if (nx<0 || ny<0 || nx>=N || ny>=N) continue;
				map[next][ny][nx].push_back({ f.m, f.s, f.d });
			}
		}
	}

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			map[cur][y][x].clear();
		}
	}

	cur = next;
}


void join_and_divide()
{
	int next = (cur + 1) % 2;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map[cur][y][x].size() < 2) {
				if (map[cur][y][x].empty()) continue;
				else map[next][y][x].push_back(map[cur][y][x][0]);
				continue;
			}

			int m_sum = 0;
			int s_sum = 0;
			int s_cnt = 0;
			vector<int> f_dir;
			for (FIREBALL f : map[cur][y][x]) {
				m_sum += f.m;
				s_sum += f.s;
				s_cnt++;
				f_dir.push_back(f.d);
			}
			
			int m = m_sum / 5;
			if (m) {
				int s = s_sum / s_cnt;

				int same_flag = 1;
				int tmp = f_dir[0] % 2;
				for (int i = 1; i < s_cnt; i++) {
					if (f_dir[i] % 2 != tmp) {
						same_flag = 0; break;
					}
				}

				if (same_flag) {  //0, 2, 4, 6
					for (int i = 0; i < 4; i++) {
						map[next][y][x].push_back({ m, s, i * 2 });
					}
				}
				else { //1, 3, 5, 7
					for (int i = 0; i < 4; i++) {
						map[next][y][x].push_back({ m, s, i * 2 + 1 });
					}
				}
			}
		}
	}

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			map[cur][y][x].clear();
		}
	}

	cur = next;
}


void solve()
{
	for (int i = 0; i < K; i++) {
		move();
		join_and_divide();
	}

	int sum = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map[cur][y][x].empty()) continue;
			for (FIREBALL f : map[cur][y][x]) {
				sum += f.m;
			}
		}
	}

	cout << sum;
}


int main()
{
	input();
	solve();
	return 0;
}