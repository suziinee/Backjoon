#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

#define MAXN 49
#define MAXM 100
int N, M;
int map[MAXN][MAXN];
int score[4]; //1번~3번 폭발한 구슬 개수
int sy, sx; //상어 위치(고정)

struct MAGIC {
	int d, s;
};
MAGIC magic[MAXM];

struct AXIS {
	int y, x, cnt; //폭발 시 그룹의 끝 좌표와 개수 담아놓기
};

const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };
const int inout[] = { 2, 3, 1, 0 }; //안->밖일때 다음 방향 lut
const int outin[] = { 3, 2, 0, 1 }; //밖->안일때 다음 방향 lut


void input()
{
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
		}
	}
	for (int i = 0; i < M; i++) {
		cin >> magic[i].d >> magic[i].s;
		--magic[i].d;
	}
	sy = N / 2;
	sx = N / 2;
}

void blizzard(MAGIC& m) //d방향 s칸 이하 구슬 파괴
{
	for (int step = 1; step <= m.s; step++) {
		int nx = sx + dx[m.d] * step;
		int ny = sy + dy[m.d] * step;
		if (nx < 0 || ny < 0 || nx >= N || ny >= N) return;
		map[ny][nx] = 0;
	}
}

void move(queue<int> nq) //nq의 구슬을 map에 담기
{
	fill(&map[0][0], &map[MAXN - 1][MAXN], 0); //back 사용하지 않고 map 초기화
	bool visited[MAXN][MAXN] = { false, };
	int x = sx; int y = sy; int d = 0;
	visited[y][x] = true;

	for (int i = 0; i < N * N - 1; i++) {
		int nd = inout[d];
		int nx = x + dx[nd];
		int ny = y + dy[nd];
		if (visited[ny][nx]) {
			nd = d;
			nx = x + dx[nd];
			ny = y + dy[nd];
		}
		if (!nq.empty()) {
			map[ny][nx] = nq.front(); nq.pop();
			visited[ny][nx] = true;
			y = ny; x = nx; d = nd;
		}
		else break;
	}
}

void move_gem() //안->밖으로 빈공간 제외 구슬을 nq에 담기
{
	queue<int> nq; //구슬을 담을 큐
	bool visited[MAXN][MAXN] = { false, };
	int x = sx; int y = sy; int d = 0;
	visited[y][x] = true;

	for (int i = 0; i < N * N - 1; i++) {
		int nd = inout[d];
		int nx = x + dx[nd];
		int ny = y + dy[nd];
		if (visited[ny][nx]) {
			nd = d;
			nx = x + dx[nd];
			ny = y + dy[nd];
		}
		if (map[ny][nx]) nq.push(map[ny][nx]);
		visited[ny][nx] = true;
		y = ny; x = nx; d = nd;
	}

	if (nq.empty()) return;
	move(nq);
}

void explode(stack<AXIS> end) //밖->안으로 이동하면서 끝 좌표 만나면 그때부터 cnt만큼 구슬 지우기
{
	bool visited[MAXN][MAXN] = { false, };
	int x = -1; int y = 0; int d = 3;
	int erase = 0;

	for (int i = 0; i < N * N - 1; i++) {
		int nd = d;
		int nx = x + dx[nd];
		int ny = y + dy[nd];
		if (visited[ny][nx] || nx < 0 || ny < 0 || nx >= N || ny >= N) {
			nd = outin[d];
			nx = x + dx[nd];
			ny = y + dy[nd];
		}

		if (erase) {
			map[ny][nx] = 0;
			--erase;
		}
		if (!end.empty() && ny == end.top().y && nx == end.top().x) {
			map[ny][nx] = 0;
			erase = end.top().cnt - 1;
			end.pop();
		}
		visited[ny][nx] = true;
		y = ny; x = nx; d = nd;
	}
}

bool explode_gem() //안->밖으로 이동하며 4개 이상 연속일 경우 끝 좌표를 end에 담기
{
	stack<AXIS> end; //4개 이상 그룹의 끝 좌표
	bool visited[MAXN][MAXN] = { false, };
	int x = sx; int y = sy; int d = 0;
	visited[y][x] = true;
	int tmp_num = 0; int tmp_cnt = 0;

	for (int i = 0; i < N * N - 1; i++) {
		int nd = inout[d];
		int nx = x + dx[nd];
		int ny = y + dy[nd];
		if (visited[ny][nx]) {
			nd = d;
			nx = x + dx[nd];
			ny = y + dy[nd];
		}
		if (map[ny][nx] == 0) { //**
			if (tmp_cnt >= 4) {
				score[tmp_num] += tmp_cnt;
				end.push({ y, x, tmp_cnt });
			}
			break;
		}
		if (map[ny][nx] == tmp_num) {
			++tmp_cnt;
		}
		else {
			if (tmp_cnt >= 4) {
				score[tmp_num] += tmp_cnt;
				end.push({ y, x, tmp_cnt });
			}
			tmp_num = map[ny][nx];
			tmp_cnt = 1;
		}
		visited[ny][nx] = true;
		y = ny; x = nx; d = nd;
	}

	if (end.empty()) return false;
	explode(end);
	return true;
}

void change(queue<int> gq) //안->밖으로 가며 gq를 순서대로 담기
{
	fill(&map[0][0], &map[MAXN - 1][MAXN], 0); //back 사용하지 않고 map 초기화
	bool visited[MAXN][MAXN] = { false, };
	int x = sx; int y = sy; int d = 0;
	visited[y][x] = true;

	for (int i = 0; i < N * N - 1; i++) {
		if (gq.empty()) break;
		int nd = inout[d];
		int nx = x + dx[nd];
		int ny = y + dy[nd];
		if (visited[ny][nx]) {
			nd = d;
			nx = x + dx[nd];
			ny = y + dy[nd];
		}
		
		if (!gq.empty()) {
			map[ny][nx] = gq.front(); gq.pop();
		}
		visited[ny][nx] = true;
		y = ny; x = nx; d = nd;
	}
}

void change_gem() //안->밖으로 가며 구슬그룹을 찾아 gq에 담기
{
	queue<int> gq;
	bool visited[MAXN][MAXN] = { false, };
	int x = sx; int y = sy; int d = 0;
	visited[y][x] = true;
	int tmp_num = 0; int tmp_cnt = 0;

	for (int i = 0; i < N * N - 1; i++) {
		int nd = inout[d];
		int nx = x + dx[nd];
		int ny = y + dy[nd];
		if (visited[ny][nx]) {
			nd = d;
			nx = x + dx[nd];
			ny = y + dy[nd];
		}
		if (map[ny][nx] == 0) { //**
			gq.push(tmp_cnt);
			gq.push(tmp_num);
			break;
		}
		if (map[ny][nx] == tmp_num) {
			++tmp_cnt;
		}
		else {
			if (i != 0) {
				gq.push(tmp_cnt);
				gq.push(tmp_num);
			}
			tmp_num = map[ny][nx];
			tmp_cnt = 1;
		}
		visited[ny][nx] = true;
		y = ny; x = nx; d = nd;
	}

	if (gq.empty()) return;
	change(gq);
}

void solve()
{
	for (int turn = 0; turn < M; turn++) {
		blizzard(magic[turn]);
		move_gem(); 
		while (explode_gem()) {
			move_gem();
		}
		change_gem();
	}

	int ans = 0;
	for (int i = 1; i <= 3; i++) {
		ans += i * score[i];
	}
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}