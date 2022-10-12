#include <iostream>
#include <algorithm>
using namespace std;

struct FISH { int y, x, d; }; 
FISH fish[16 + 1]; //잡아먹힌 물고기는 d=-1
int map[4][4]; //물고기 번호 관리(잡아먹힌 물고기는 -1)
int ans;

struct SHARK { int y, x, d, score; };

const int dx[] = { 0, -1, -1, -1, 0, 1, 1, 1 };
const int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };


void input()
{
	int n, d;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			cin >> n >> d;
			--d;
			fish[n] = { y, x, d };
			map[y][x] = n;
		}
	}
}

void fish_move(FISH (*back_fish), int(*back_map)[4], SHARK& shark)
{
	for (int i = 1; i <= 16; i++) {
		if (back_fish[i].d == -1) continue; //잡아먹힌 물고기
		for (int d = 0; d < 8; d++) {
			int nd = (back_fish[i].d + d) % 8;
			int nx = back_fish[i].x + dx[nd];
			int ny = back_fish[i].y + dy[nd];
			if (nx < 0 || ny < 0 || nx >= 4 || ny >= 4) continue;
			if (nx == shark.x && ny == shark.y) continue;
			if (back_map[ny][nx] == -1) { //물고기가 없음
				back_map[back_fish[i].y][back_fish[i].x] = -1;
				back_map[ny][nx] = i;
				back_fish[i].y = ny;
				back_fish[i].x = nx;
				back_fish[i].d = nd;
			}
			else { //물고기가 있음 -> swap
				int tmp = back_map[ny][nx];
				back_fish[tmp].y = back_fish[i].y;
				back_fish[tmp].x = back_fish[i].x;
				back_map[back_fish[i].y][back_fish[i].x] = tmp;

				back_fish[i].y = ny;
				back_fish[i].x = nx;
				back_fish[i].d = nd;
				back_map[ny][nx] = i;
			}
			break;
		}
	}
}

void dfs(FISH (*fish), int(*map)[4], SHARK shark, int y, int x)
{
	int back_map[4][4];
	FISH back_fish[17];
	copy(&map[0][0], &map[3][4], &back_map[0][0]);
	copy(fish, fish + 17, back_fish);

	//(y, x)에 있는 물고기 먹기
	int n = back_map[y][x];
	shark.y = y; shark.x = x; 
	shark.d = back_fish[n].d;
	shark.score += n;
	back_fish[n].d = -1;
	back_map[y][x] = -1;

	if (ans < shark.score) ans = shark.score;

	//물고기 이동
	fish_move(back_fish, back_map, shark);

	//상어 이동
	for (int step = 1; step <= 3; step++) {
		int nx = shark.x + dx[shark.d] * step;
		int ny = shark.y + dy[shark.d] * step;
		if (nx < 0 || ny < 0 || nx >= 4 || ny >= 4) break;
		if (back_map[ny][nx] == -1) continue;
		dfs(back_fish, back_map, shark, ny, nx);
	}
}

void solve()
{
	SHARK init_shark = { 0, 0, 0, 0 };
	dfs(fish, map, init_shark, 0, 0);
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}