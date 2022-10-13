#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 20
int N, M, K;
int map[MAXN][MAXN];

struct TEAM {
	int sy, sx;
	int ey, ex;
	int score;
};
TEAM team[5];

struct AXIS { int y, x; };
queue<AXIS> q;

int team_num[5][5] = {
	{0, 1, 2, 3, 4}, {0, 11, 22, 33, 44}, {0, 111, 222, 333, 444}, {0, 1111, 2222, 3333, 4444},
	{0, 11111, 22222, 33333, 44444}
};

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };


void input()
{
	cin >> N >> M >> K;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
		}
	}
}

void dfs(int y, int x, bool(*chk)[MAXN], int m)
{
	chk[y][x] = true;
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
		if (map[ny][nx] == 0 || chk[ny][nx]) continue;
		if (map[ny][nx] == 4) {
			dfs(ny, nx, chk, m);
		}
		else if (map[ny][nx] == 1) { //sy, sx
			team[m].sy = ny;
			team[m].sx = nx;
			map[ny][nx] = team_num[m][1];
		}
		else if (map[ny][nx] == 3) { //ey, ex
			team[m].ey = ny;
			team[m].ex = nx;
			map[ny][nx] = team_num[m][3];
		}
	}
}

void change_two(int t) //2를 팀 번호에 맞게 바꿔줌
{
	int cy = team[t].sy;
	int cx = team[t].sx;
	while (true) {
		for (int d = 0; d < 4; d++) {
			int nx = cx + dx[d];
			int ny = cy + dy[d];
			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
			if (map[ny][nx] == 2) {
				map[ny][nx] = team_num[t][2];
				cy = ny;
				cx = nx;
				break;
			}
			else if (map[ny][nx] == team_num[t][3]) {
				return;
			}
		}
	}
}

void init_team()
{
	//4를 발견하면 flood fill 진행
	bool chk[MAXN][MAXN] = { false, };
	int m = -1; //팀 번호 : 0번~M-1번
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map[y][x] == 4 && chk[y][x] == false) {
				++m;
				dfs(y, x, chk, m);
			}
		}
	}
	for (int i = 1; i < M; i++) {
		change_two(i);
	}
}

void team_move(int t)
{
	int hy = team[t].sy;
	int hx = team[t].sx;
	int ty = team[t].ey;
	int tx = team[t].ex;

	//1. head가 주변의 4로 이동
	for (int d = 0; d < 4; d++) {
		int nx = hx + dx[d];
		int ny = hy + dy[d];
		if (map[ny][nx] == 4) {
			map[ny][nx] = team_num[t][1];
			team[t].sy = ny;
			team[t].sx = nx;
			break;
		}
	}
	//2. head가 있던 자리 2로 채우기
	map[hy][hx] = team_num[t][2];
	//3. tail은 주변의 2로 이동
	for (int d = 0; d < 4; d++) {
		int nx = tx + dx[d];
		int ny = ty + dy[d];
		if (map[ny][nx] == team_num[t][2]) {
			map[ny][nx] = team_num[t][3];
			team[t].ey = ny;
			team[t].ex = nx;
			break;
		}
	}
	//4. tail 있던 곳 4로 채우기
	map[ty][tx] = 4;
}

int get_turn(int t, int y, int x) //(y, x)가 t번 팀에서 몇번째인지 찾기
{
	bool chk[MAXN][MAXN] = { false, };
	int turn = 1;
	int cy = team[t].sy;
	int cx = team[t].sx;
	chk[cy][cx] = true;
	while (!(cy == y && cx == x)) {
		for (int d = 0; d < 4; d++) {
			int nx = cx + dx[d];
			int ny = cy + dy[d];
			if (nx < 0 || ny < 0 || nx >= N || ny >= N || chk[ny][nx]) continue;
			if (map[ny][nx] == team_num[t][2] || map[ny][nx] == team_num[t][3]) {
				chk[ny][nx] = true;
				cy = ny;
				cx = nx;
				++turn;
				break;
			}
		}
	}
	return turn;
}

void head_tail_swap(int t) //t번 팀의 머리와 꼬리 바꿔주기
{
	int tmpx = team[t].sx;
	int tmpy = team[t].sy;
	team[t].sx = team[t].ex;
	team[t].sy= team[t].ey;
	team[t].ex = tmpx;
	team[t].ey = tmpy;
}

void round_sub(int y, int x) //몇번 팀인지 탐색해서 점수 올려주고 머리 꼬리 방향 바꿔줌
{
	if (map[y][x] < 10) { //1번팀
		int turn = get_turn(0, y, x);
		team[0].score += turn * turn;
		head_tail_swap(0);
	}
	else if (map[y][x] < 100) { //2번팀
		int turn = get_turn(1, y, x);
		team[1].score += turn * turn;
		head_tail_swap(1);
	}
	else if (map[y][x] < 1000) { //3번팀
		int turn = get_turn(2, y, x);
		team[2].score += turn * turn;
		head_tail_swap(2);
	}
	else if (map[y][x] < 10000) { //4번팀
		int turn = get_turn(3, y, x);
		team[3].score += turn * turn;
		head_tail_swap(3);
	}
	else if (map[y][x] < 100000) { //5번팀
		int turn = get_turn(4, y, x);
		team[4].score += turn * turn;
		head_tail_swap(4);
	}
}

void round1(int r) //r번째 행을 0번 열부터 탐색
{
	for (int x = 0; x < N; x++) {
		int n = map[r][x] % 10;
		if (n == 1 || n == 2 || n == 3) {
			round_sub(r, x);
			return;
		}
	}
}

void round3(int r) //r번째 행을 N-1번 열부터 탐색
{
	r -= 2 * N;
	r = N - 1 - r;
	for (int x = N - 1; x >= 0; x--) {
		int n = map[r][x] % 10;
		if (n == 1 || n == 2 || n == 3) {
			round_sub(r, x);
			return;
		}
	}
}

void round2(int c) //c번째 열을 N-1번째 행부터 탐색
{
	c -= N;
	for (int y = N - 1; y >= 0; y--) {
		int n = map[y][c] % 10;
		if (n == 1 || n == 2 || n == 3) {
			round_sub(y, c);
			return;
		}
	}
}

void round4(int c) //c번째 열을 0번째 행부터 탐색
{
	c -= 3 * N;
	c = N - 1 - c;
	for (int y = 0; y < N; y++) {
		int n = map[y][c] % 10;
		if (n == 1 || n == 2 || n == 3) {
			round_sub(y, c);
			return;
		}
	}
}

void solve()
{
	init_team();
	for (int i = 0; i < K; i++) {
		//팀 이동
		for (int t = 0; t < M; t++) {
			team_move(t);
		}
		//공이 던져짐
		int round = i % (4 * N);
		if (round >= 0 && round < N) round1(round);
		else if (round >= N && round < 2 * N) round2(round);
		else if (round >= 2 * N && round < 3 * N) round3(round);
		else if (round >= 3 * N && round < 4 * N) round4(round);
	}

	int ans = 0;
	for (int i = 0; i < M; i++) {
		ans += team[i].score;
	}
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}