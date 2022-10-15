#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 100
int R, C, M, ans;

struct SHARK {
	int s, d, z; //속력, 방향, 크기
};
SHARK map[MAX][MAX]; //죽은 상어는 크기가 0

const int dx[] = { -0, 0, 1, -1 };
const int dy[] = { -1, 1, 0, 0 };


void input()
{
	cin >> R >> C >> M;
	int r, c, s, d, z;
	for (int i = 0; i < M; i++) {
		cin >> r >> c >> s >> d >> z;
		--r; --c; --d;
		map[r][c] = { s, d, z };
	}
}

void catch_shark(int x)
{
	for (int y = 0; y < R; y++) {
		if (map[y][x].z) {
			ans += map[y][x].z;
			map[y][x].z = 0;
			map[y][x].s = 0;
			map[y][x].d = 0;
			return;
		}
	}
}

void move_shark()
{
	SHARK back[MAX][MAX] = { 0, };
	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			if (map[y][x].z == 0) continue;
			switch (map[y][x].d) {
			case 0: { //y 감소
				int ny = y - map[y][x].s;
				if (ny < 0) {
					int diff = map[y][x].s - y;
					int rep = diff / (R - 1);
					int rem = diff % (R - 1);
					if (rep % 2) { //방향 같음
						ny = (R - 1) - rem;
					}
					else { //방향 반대
						ny = rem;
						map[y][x].d = 1;
					}
				}
				if (back[ny][x].z && back[ny][x].z > map[y][x].z) continue;
				back[ny][x].s = map[y][x].s;
				back[ny][x].d = map[y][x].d;
				back[ny][x].z = map[y][x].z;
				break;
			}
			case 1: { //y 증가
				int ny = y + map[y][x].s;
				if (ny >= R) {
					int diff = ny - (R - 1);
					int rep = diff / (R - 1);
					int rem = diff % (R - 1);
					if (rep % 2) { //방향 같음
						ny = rem;
					}
					else { //방향 반대
						ny = (R - 1) - rem;
						map[y][x].d = 0;
					}
				}
				if (back[ny][x].z && back[ny][x].z > map[y][x].z) continue;
				back[ny][x].s = map[y][x].s;
				back[ny][x].d = map[y][x].d;
				back[ny][x].z = map[y][x].z;
				break;
			}
			case 2: { //x 증가
				int nx = x + map[y][x].s;
				if (nx >= C) {
					int diff = nx - (C - 1);
					int rep = diff / (C - 1);
					int rem = diff % (C - 1);
					if (rep % 2) { //방향 같음
						nx = rem;
					}
					else { //방향 다름
						nx = (C - 1) - rem;
						map[y][x].d = 3;
					}
				}
				if (back[y][nx].z && back[y][nx].z > map[y][x].z) continue;
				back[y][nx].s = map[y][x].s;
				back[y][nx].d = map[y][x].d;
				back[y][nx].z = map[y][x].z;
				break;
			}
			case 3: { //x 감소
				int nx = x - map[y][x].s;
				if (nx < 0) {
					int diff = map[y][x].s - x;
					int rep = diff / (C - 1);
					int rem = diff % (C - 1);
					if (rep % 2) { //방향 같음
						nx = (C - 1) - rem;
					}
					else { //방향 다름
						nx = rem;
						map[y][x].d = 2;
					}
				}
				if (back[y][nx].z && back[y][nx].z > map[y][x].z) continue;
				back[y][nx].s = map[y][x].s;
				back[y][nx].d = map[y][x].d;
				back[y][nx].z = map[y][x].z;
				break;
			}
			}
		}
	}
	copy(&back[0][0], &back[MAX - 1][MAX], &map[0][0]);
}

void solve()
{
	for (int x = 0; x < C; x++) {
		catch_shark(x);
		move_shark();
	}
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}