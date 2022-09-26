#include <iostream>
#include <vector>
using namespace std;

#define MAXNM 8
int N, M;
int map[MAXNM][MAXNM];
int ans = 0x7fffffff;

struct CCTV { int n; int d; int y; int x; };
vector<CCTV> cctv;
int pick_dir[8];


void input()
{
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> map[y][x];
			if (map[y][x] != 0 && map[y][x] != 6) {
				cctv.push_back({ map[y][x], -1, y, x });
			}
		}
	}
}


void check1(int(*area)[MAXNM], CCTV& c, int dir)
{
	static int dx[] = { 1, 0, -1, 0 };
	static int dy[] = { 0, -1, 0, 1 };
	int y = c.y; int x = c.x; int i = 1;
	while (true) {
		int nx = x + i * dx[dir];
		int ny = y + i * dy[dir];
		if (nx < 0 || ny < 0 || nx >= M || ny >= N || area[ny][nx] == 6) break;
		if (area[ny][nx] == 0) area[ny][nx] = -1;
		i++;
	}
}

void check2(int(*area)[MAXNM], CCTV& c, int dir)
{
	static int dx[] = { 1, 0, -1, 0 };
	static int dy[] = { 0, -1, 0, 1 };
	int comb[2][2] = { {0, 2}, {1, 3} }; //dir 0, dir 1
	for (int d : comb[dir]) { //2번 함
		int y = c.y; int x = c.x; int i = 1;
		while (true) {
			int nx = x + i * dx[d];
			int ny = y + i * dy[d];
			if (nx < 0 || ny < 0 || nx >= M || ny >= N || area[ny][nx] == 6) break;
			if (area[ny][nx] == 0) area[ny][nx] = -1;
			i++;
		}
	}
}

void check3(int(*area)[MAXNM], CCTV& c, int dir)
{
	static int dx[] = { 1, 0, -1, 0 };
	static int dy[] = { 0, -1, 0, 1 };
	int comb[4][2] = { {0, 1}, {1, 2}, {2, 3}, {3, 0} }; //dir 0, 1, 2, 3
	for (int d : comb[dir]) { //2번 함
		int y = c.y; int x = c.x; int i = 1;
		while (true) {
			int nx = x + i * dx[d];
			int ny = y + i * dy[d];
			if (nx < 0 || ny < 0 || nx >= M || ny >= N || area[ny][nx] == 6) break;
			if (area[ny][nx] == 0) area[ny][nx] = -1;
			i++;
		}
	}
}

void check4(int(*area)[MAXNM], CCTV& c, int dir)
{
	static int dx[] = { 1, 0, -1, 0 };
	static int dy[] = { 0, -1, 0, 1 };
	int comb[4][3] = { {0, 1, 2}, {1, 2, 3}, {2, 3, 0}, {3, 0, 1} }; //dir 0, 1, 2, 3
	for (int d : comb[dir]) { //3번 함
		int y = c.y; int x = c.x; int i = 1;
		while (true) {
			int nx = x + i * dx[d];
			int ny = y + i * dy[d];
			if (nx < 0 || ny < 0 || nx >= M || ny >= N || area[ny][nx] == 6) break;
			if (area[ny][nx] == 0) area[ny][nx] = -1;
			i++;
		}
	}
}

void check5(int(*area)[MAXNM], CCTV& c, int dir)
{
	static int dx[] = { 1, 0, -1, 0 };
	static int dy[] = { 0, -1, 0, 1 };
	int comb[4] = { 0, 1, 2, 3 };
	for (int d : comb) { //4번 함
		int y = c.y; int x = c.x; int i = 1;
		while (true) {
			int nx = x + i * dx[d];
			int ny = y + i * dy[d];
			if (nx < 0 || ny < 0 || nx >= M || ny >= N || area[ny][nx] == 6) break;
			if (area[ny][nx] == 0) area[ny][nx] = -1;
			i++;
		}
	}
}


int check_area()
{
	int area[MAXNM][MAXNM] = { 0 };
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			area[y][x] = map[y][x];
		}
	}

	for (int i = 0; i < (int)cctv.size(); i++) {
		switch (cctv[i].n) {
			case 1: check1(area, cctv[i], pick_dir[i]); break;
			case 2: check2(area, cctv[i], pick_dir[i]); break;
			case 3: check3(area, cctv[i], pick_dir[i]); break;
			case 4: check4(area, cctv[i], pick_dir[i]); break;
			case 5: check5(area, cctv[i], pick_dir[i]); break;
		}
	}

	int ret = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (area[y][x] == 0) ret++;
		}
	}
	return ret;
}


void dfs(int depth, int s)
{
	if (depth == (int)cctv.size()) {
		//cctv의 방향을 모두 선택함
		int ret = check_area();
		if (ret < ans) ans = ret;
		return;
	}

	for (int i = s; i < (int)cctv.size(); i++) {
		switch (cctv[i].n) {
		case 1: {
			for (int d = 0; d < 4; d++) {
				pick_dir[depth] = d;
				dfs(depth + 1, i + 1);
			}
			break;
		}
		case 2: {
			for (int d = 0; d < 2; d++) {
				pick_dir[depth] = d;
				dfs(depth + 1, i + 1);
			}
			break;
		}
		case 3: {
			for (int d = 0; d < 4; d++) {
				pick_dir[depth] = d;
				dfs(depth + 1, i + 1);
			}
			break;
		}
		case 4: {
			for (int d = 0; d < 4; d++) {
				pick_dir[depth] = d;
				dfs(depth + 1, i + 1);
			}
			break;
		}
		case 5: {
			pick_dir[depth] = 0;
			dfs(depth + 1, i + 1);
			break;
		}
		}
	}
}


void solve()
{
	dfs_pick(0, 0);
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}