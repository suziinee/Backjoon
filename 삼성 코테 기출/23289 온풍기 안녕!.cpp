#include <iostream>
#include <vector>
using namespace std;

#define MAX 20
int R, C, K, W;
int map[MAX][MAX];
int wall[MAX][MAX][4];

struct AXIS { int y, x; };
vector<AXIS> check_temp;

struct HEATER { int y, x, d; };
vector<HEATER> heater;

const int dx[] = { 1, -1, 0, 0 }; //right left up down
const int dy[] = { 0, 0, -1, 1 };


void input()
{
	cin >> R >> C >> K;
	int n;
	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			cin >> n;
			if (n) {
				if (n == 5) {
					check_temp.push_back({ y, x });
				}
				else {
					--n;
					heater.push_back({ y, x, n });
				}
			}
		}
	}
	cin >> W;
	int y, x, d;
	for (int i = 0; i < W; i++) {
		cin >> y >> x >> d;
		--y; --x;
		if (d) { //(y, x)와 (y, x+1) 사이 
			wall[y][x][0] = 1;
			wall[y][x + 1][1] = 1;
		}
		else { //(y, x)와 (y-1, x) 사이
			wall[y][x][2] = 1;
			wall[y - 1][x][3] = 1;
		}
	}
}

bool wall_check(int y, int x, int dir, int d)
{
	switch (dir) {
	case 0: {
		if (d == 0) {
			if (wall[y - 1][x][0] || wall[y - 1][x][3]) return false;
		}
		else if (d == 1) {
			if (wall[y][x][0]) return false;
		}
		else if (d == 2) {
			if (wall[y + 1][x][2] || wall[y + 1][x][0]) return false;
		}
		return true;
		break;
	}
	case 1: {
		if (d == 0) {
			if (wall[y - 1][x][1] || wall[y - 1][x][3]) return false;
		}
		else if (d == 1) {
			if (wall[y][x][1]) return false;
		}
		else if (d == 2) {
			if (wall[y + 1][x][2] || wall[y + 1][x][1]) return false;
		}
		return true;
		break;
	}
	case 2: {
		if (d == 0) {
			if (wall[y][x - 1][2] || wall[y][x - 1][0]) return false;
		}
		else if (d == 1) {
			if (wall[y][x][2]) return false;
		}
		else if (d == 2) {
			if (wall[y][x + 1][1] || wall[y][x + 1][2]) return false;
		}
		return true;
		break;
	}
	case 3: {
		if (d == 0) {
			if (wall[y][x - 1][3] || wall[y][x - 1][0]) return false;
		}
		else if (d == 1) {
			if (wall[y][x][3]) return false;
		}
		else if (d == 2) {
			if (wall[y][x + 1][1] || wall[y][x + 1][3]) return false;
		}
		return true;
		break;
	}
	}
}

void dfs(int y, int x, int dir, int temp, bool(*chk)[MAX], int (*back)[MAX])
{
	static int dirx[4][3] = { {1, 1, 1}, {-1, -1, -1}, {-1, 0, 1}, {-1, 0, 1} };
	static int diry[4][3] = { {-1, 0, 1}, {-1, 0, 1}, {-1, -1, -1}, {1, 1, 1} };

	if (temp == 0) return;

	back[y][x] += temp;
	chk[y][x] = true;
	for (int d = 0; d < 3; d++) {
		int nx = x + dirx[dir][d];
		int ny = y + diry[dir][d];
		if (nx < 0 || ny < 0 || nx >= C || ny >= R) continue;
		if (chk[ny][nx]) continue;
		if (!wall_check(y, x, dir, d)) continue;
		dfs(ny, nx, dir, temp - 1, chk, back);
	}
}

void heater_spread() //온풍기에서 바람이 나옴
{
	int back[MAX][MAX] = { 0, };

	for (HEATER h : heater) {
		bool chk[MAX][MAX] = { false, };
		int x = h.x + dx[h.d]; //첫 (y, x)는 5의 위치
		int y = h.y + dy[h.d];
		int temp = 5;
		if (x < 0 || y < 0 || x >= C || y >= R) continue;
		dfs(y, x, h.d, temp, chk, back);
	}

	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			map[y][x] += back[y][x];
		}
	}
}

void temp_change() //온도 조절
{
	int back[MAX][MAX] = { 0, };

	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			for (int d = 0; d < 4; d++) {
				int nx = x + dx[d];
				int ny = y + dy[d];
				if (nx < 0 || ny < 0 || nx >= C || ny >= R) continue;
				if (map[ny][nx] >= map[y][x]) continue;
				if (wall[y][x][d]) continue;
				int diff = (map[y][x] - map[ny][nx]) / 4;
				back[y][x] -= diff;
				back[ny][nx] += diff;
			}
		}
	}

	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			map[y][x] += back[y][x];
		}
	}
}

void temp_decrease() //온도가 1 이상인 가장 바깥쪽 칸의 온도가 1씩 감소
{
	for (int x = 0; x < C; x++) {
		if (map[0][x]) map[0][x]--;
		if (map[R - 1][x]) map[R - 1][x]--;
	}
	for (int y = 1; y < R - 1; y++) { //** 꼭짓점이 2번 감소되지 않게하기
		if (map[y][0]) map[y][0]--;
		if (map[y][C - 1]) map[y][C - 1]--;
	}
}

bool complete() //조사하려는 모든 칸의 온도가 K 이상 되었는지 검사
{
	for (AXIS a : check_temp) {
		if (map[a.y][a.x] < K) return false;
	}
	return true;
}

void solve()
{
	for (int choc = 1; choc <= 100; choc++) {
		heater_spread();
		temp_change();
		temp_decrease();
		if (complete()) {
			cout << choc;
			return;
		}
	}
	cout << 101;
}


int main()
{
	input();
	solve();
	return 0;
}