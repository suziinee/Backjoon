#include <iostream>
#include <deque>
using namespace std;

#define MAXN 20
int N, M, K;
int map[MAXN][MAXN];
int ans;

struct AXIS { int y, x; };
struct TEAM {
	int dir = 1; //1이면 앞쪽이 머리, 0이면 뒤쪽이 머리
	deque<AXIS> chain;
};
TEAM team[5 + 1]; //1번~5번

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };

#define ROAD (6)
#define HEAD (7)
#define BODY (8)
#define TAIL (9)

void input()
{
	cin >> N >> M >> K;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
			if (map[y][x] == 4) map[y][x] = ROAD;
			else if (map[y][x] == 1) map[y][x] = HEAD;
			else if (map[y][x] == 2) map[y][x] = BODY;
			else if (map[y][x] == 3) map[y][x] = TAIL;
		}
	}
}

void dfs(int y, int x, int m)
{
	map[y][x] = m;
	team[m].chain.push_back({ y, x });
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
		if (map[ny][nx] == BODY) {
			dfs(ny, nx, m);
		}
		else if (map[ny][nx] == TAIL) {
			map[ny][nx] = m;
			team[m].chain.push_back({ ny, nx });
		}
	}
}

void init_team()
{
	int m = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map[y][x] != HEAD) continue;
			map[y][x] = ++m;
			team[m].chain.push_back({ y, x });
			for (int d = 0; d < 4; d++) { //body 하나 찾고 dfs 보내기
				int nx = x + dx[d];
				int ny = y + dy[d];
				if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
				if (map[ny][nx] == BODY) {
					dfs(ny, nx, m);
					break;
				}
			}
		}
	}
}

void team_move(int t) //t번 팀 이동
{
	//꼬리 자르기
	int ty, tx;
	if (team[t].dir) { //앞쪽이 머리, 뒤쪽이 꼬리
		ty = team[t].chain.back().y;
		tx = team[t].chain.back().x;
		map[ty][tx] = ROAD;
		team[t].chain.pop_back();
	}
	else { //뒤쪽이 머리, 앞쪽이 꼬리
		ty = team[t].chain.front().y;
		tx = team[t].chain.front().x;
		map[ty][tx] = ROAD;
		team[t].chain.pop_front();
	}

	//머리 추가
	int y, x;
	if (team[t].dir) { //앞쪽이 머리, 뒤쪽이 꼬리
		y = team[t].chain.front().y;
		x = team[t].chain.front().x;
	}
	else { //뒤쪽이 머리, 앞쪽이 꼬리
		y = team[t].chain.back().y;
		x = team[t].chain.back().x;
	}
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
		if (map[ny][nx] == ROAD) {
			if (team[t].dir) {
				team[t].chain.push_front({ ny, nx });
			}
			else {
				team[t].chain.push_back({ ny, nx });
			}
			map[ny][nx] = t;
			return;
		}
	}
}

void get_score(int y, int x, int t)
{
	int turn = 1;
	if (team[t].dir) { //머리부터 찾기
		for (auto it = team[t].chain.begin(); it != team[t].chain.end(); it++) {
			if (it->y == y && it->x == x) break;
			turn++;
		}
		team[t].dir = 0; //방향 바꿔주기
		ans += turn * turn;
	}
	else { //머리부터 찾은 후 꼬리까지 count
		int count = 0;
		for (auto it = team[t].chain.begin(); it != team[t].chain.end(); it++) {
			count++;
		}
		for (auto it = team[t].chain.begin(); it != team[t].chain.end(); it++) {
			if (it->y == y && it->x == x) break;
			turn++;
		}
		team[t].dir = 1;
		ans += (count - turn + 1) * (count - turn + 1);
	}
}

void round1(int r) //r번째 행을 0번 열부터 탐색
{
	for (int x = 0; x < N; x++) {
		if (map[r][x] != 0 && map[r][x] != ROAD) {
			get_score(r, x, map[r][x]);
			return;
		}
	}
}

void round3(int r) //r번째 행을 N-1번 열부터 탐색
{
	r %= N;
	r = N - 1 - r;
	for (int x = N - 1; x >= 0; x--) {
		if (map[r][x] != 0 && map[r][x] != ROAD) {
			get_score(r, x, map[r][x]);
			return;
		}
	}
}

void round2(int c) //c번째 열을 N-1번째 행부터 탐색
{
	c %= N;
	for (int y = N - 1; y >= 0; y--) {
		if (map[y][c] != 0 && map[y][c] != ROAD) {
			get_score(y, c, map[y][c]);
			return;
		}
	}
}

void round4(int c) //c번째 열을 0번째 행부터 탐색
{
	c %= N;
	c = N - 1 - c;
	for (int y = 0; y < N; y++) {
		if (map[y][c] != 0 && map[y][c] != ROAD) {
			get_score(y, c, map[y][c]);
			return;
		}
	}
}

void solve()
{
	init_team(); //dfs
	for (int i = 0; i < K; i++) {
		//팀 이동
		for (int t = 1; t <= M; t++) {
			team_move(t);
		}
		//공이 던져짐
		int round = i % (4 * N);
		if (round >= 0 && round < N) round1(round);
		else if (round >= N && round < 2 * N) round2(round);
		else if (round >= 2 * N && round < 3 * N) round3(round);
		else if (round >= 3 * N && round < 4 * N) round4(round);
	}
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}