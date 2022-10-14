#include <iostream>
#include <queue>
using namespace std;

#define MAXN 20
int N, M, K, C, killed;
int map[MAXN][MAXN];
int map_kill[MAXN][MAXN]; //제초제의 남은 년수 관리 

struct TREE {
	int y, x, cnt;
	bool operator<(const TREE& t) const {
		if (cnt == t.cnt) {
			if (y == t.y) return x > t.x;
			return y > t.y;
		}
		return cnt < t.cnt;
	}
};
priority_queue<TREE> pq;

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };
const int ddx[] = { -1, 1, 1, -1 };
const int ddy[] = { -1, -1, 1, 1 };

#define BLANK (0)
#define WALL (-1)


void input()
{
	cin >> N >> M >> K >> C;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
		}
	}
}

void grow_tree()
{
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map[y][x] <= 0) continue;
			int cnt = 0;
			for (int d = 0; d < 4; d++) {
				int nx = x + dx[d];
				int ny = y + dy[d];
				if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
				if (map_kill[ny][nx] > 0) continue;
				if (map[ny][nx] > 0) ++cnt;
			}
			map[y][x] += cnt;
		}
	}
}

void breed_tree()
{
	int back[MAXN][MAXN] = { 0, };
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map[y][x] <= 0) continue;
			int cnt = 0;
			for (int d = 0; d < 4; d++) {
				int nx = x + dx[d];
				int ny = y + dy[d];
				if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
				if (map_kill[ny][nx] > 0) continue;
				if (map[ny][nx] == BLANK) ++cnt;
			}
			if (cnt == 0) continue;
			int breed = map[y][x] / cnt;
			for (int d = 0; d < 4; d++) {
				int nx = x + dx[d];
				int ny = y + dy[d];
				if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
				if (map_kill[ny][nx] > 0) continue;
				if (map[ny][nx] == BLANK) back[ny][nx] += breed;
			}
		}
	}
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			map[y][x] += back[y][x];
		}
	}
}

TREE get_killtree()
{
	pq = {};
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map[y][x] <= 0) continue;
			int cnt = map[y][x];
			for (int d = 0; d < 4; d++) {
				for (int step = 1; step <= K; step++) {
					int nx = x + ddx[d] * step;
					int ny = y + ddy[d] * step;
					if (nx < 0 || ny < 0 || nx >= N || ny >= N) break;
					if (map[ny][nx] <= 0) break;
					cnt += map[ny][nx];
				}
			}
			if (cnt > 0) pq.push({ y, x, cnt });
		}
	}
	if (!pq.empty()) return pq.top();
	else return { -1, -1, -1 };
}

void decrease()
{
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map_kill[y][x]) {
				--map_kill[y][x];
			}
		}
	}
}

void spread(TREE& t)
{
	killed += t.cnt;
	map[t.y][t.x] = BLANK;
	map_kill[t.y][t.x] = C;
	for (int d = 0; d < 4; d++) {
		for (int step = 1; step <= K; step++) {
			int nx = t.x + ddx[d] * step;
			int ny = t.y + ddy[d] * step;
			if (nx < 0 || ny < 0 || nx >= N || ny >= N) break;
			if (map[ny][nx] == WALL) break;
			else if (map[ny][nx] == BLANK) {
				map_kill[ny][nx] = C;
				break;
			}
			map[ny][nx] = BLANK;
			map_kill[ny][nx] = C;
		}
	}
}

void solve()
{
	for (int m = 1; m <= M; m++) {
		grow_tree(); //나무의 성장
		breed_tree(); //나무의 번식
		TREE t = get_killtree(); //제초제 뿌릴 위치 선정
		decrease(); //제초제 감소
		if (t.y != -1) spread(t); //제초제 뿌리기
	}
	cout << killed;
}


int main()
{
	input();
	solve();
	return 0;
}