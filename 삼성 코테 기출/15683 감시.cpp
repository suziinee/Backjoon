#include <iostream>
using namespace std;

#define MAX 8
int N, M, ans;
int map[MAX][MAX];

struct CCTV {
	int y, x, type;
};
CCTV cctv[MAX];
int cctv_cnt;

#define WALL (6)
#define BLANK (0)


void input()
{
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> map[y][x];
			if (map[y][x] != WALL && map[y][x] != BLANK) {
				cctv[cctv_cnt].y = y;
				cctv[cctv_cnt].x = x;
				cctv[cctv_cnt].type = map[y][x];
				++cctv_cnt;
			}
		}
	}
}

void check(int d, CCTV& c) //(c.y, c.x)에서 d 방향으로 체크
{
	switch (d) {
	case 0: {
		for (int y = c.y - 1; y >= 0; y--) {
			if (map[y][c.x] == WALL) return;
			map[y][c.x] = -1; 
		}
		break;
	}
	case 1: {
		for (int x = c.x + 1; x < M; x++) {
			if (map[c.y][x] == WALL) return;
			map[c.y][x] = -1;
		}
		break;
	}
	case 2: {
		for (int y = c.y + 1; y < N; y++) {
			if (map[y][c.x] == WALL) return;
			map[y][c.x] = -1;
		}
		break;
	}
	case 3: {
		for (int x = c.x - 1; x >= 0; x--) {
			if (map[c.y][x] == WALL) return;
			map[c.y][x] = -1;
		}
		break;
	}
	}
}

void dfs(int n) //n번 cctv에 대한 방향 설정
{
	static int rot[] = { 0, 4, 2, 4, 4, 1 }; //1번~5번까지 몇번 회전 가능한지 

	if (n == cctv_cnt) {
		int cnt = 0;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < M; x++) {
				if (map[y][x] == BLANK) ++cnt;
			}
		}
		if (cnt < ans) ans = cnt;
		return;
	}

	int type = cctv[n].type;
	for (int d = 0; d < rot[type]; d++) {
		int back[MAX][MAX];
		copy(&map[0][0], &map[MAX - 1][MAX], &back[0][0]);
		switch (type) {
		case 1: {
			check(d, cctv[n]);
			break;
		}
		case 2: {
			check(d, cctv[n]);
			check((d + 2) % 4, cctv[n]);
			break;
		}
		case 3: {
			check(d, cctv[n]);
			check((d + 3) % 4, cctv[n]);
			break;
		}
		case 4: {
			check(d, cctv[n]);
			check((d + 3) % 4, cctv[n]);
			check((d + 2) % 4, cctv[n]);
			break;
		}
		case 5: {
			check(d, cctv[n]);
			check((d + 3) % 4, cctv[n]);
			check((d + 2) % 4, cctv[n]);
			check((d + 1) % 4, cctv[n]);
			break;
		}
		}
		dfs(n + 1);
		copy(&back[0][0], &back[MAX - 1][MAX], &map[0][0]);
	}
}

void solve()
{
	ans = 0x7fffffff;
	dfs(0);
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}