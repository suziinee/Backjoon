#include <iostream>
#include <algorithm>
#include <queue>
#include <deque>
using namespace std;

#define MAXN 20
int N, M;
int map[MAXN][MAXN];
bool chk_block[MAXN][MAXN];

struct BLOCKGROUP {
	int y, x;
	int rainbow;
	int size;
	bool operator<(const BLOCKGROUP& b) const {
		if (size == b.size) {
			if (rainbow == b.rainbow) {
				if (y == b.y) return x > b.x;
				return y > b.y;
			}
			return rainbow > b.rainbow;
		}
		return size > b.size;
	}
};
deque<BLOCKGROUP> bg;

struct AXIS { int y, x; };
queue<AXIS> q;

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };


void input()
{
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
		}
	}
}

void flood_fill(int y, int x, bool (*chk_block)[MAXN]) //블록그룹 만들어서 bg에 넣기
{
	q = {};
	bool chk[MAXN][MAXN] = { false, };
	int color = map[y][x];
	BLOCKGROUP b;
	b.y = y; b.x = x; b.size = 0; b.rainbow = 0;

	q.push({ y, x });
	chk[y][x] = true;
	chk_block[y][x] = true;
	b.size++;

	while (!q.empty()) {
		AXIS n = q.front(); q.pop();
		for (int d = 0; d < 4; d++) {
			int nx = n.x + dx[d];
			int ny = n.y + dy[d];
			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
			if (chk[ny][nx]) continue;
			if (!(map[ny][nx] == 0 || map[ny][nx] == color)) continue;
			
			chk[ny][nx] = true;
			q.push({ ny, nx });
			b.size++;
			if (map[ny][nx] == 0) b.rainbow++;
			else chk_block[ny][nx] = true;
		}
	}
	bg.push_back(b);
}

void erase_dfs(int y, int x, int color) //(y, x)에서 시작되는 블록그룹 지우기
{
	map[y][x] = -2;
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
		if (map[ny][nx] == 0 || map[ny][nx] == color) {
			erase_dfs(ny, nx, color);
		}
	}
}

void fall_down_small(int y1, int y2, int x) //x열의 y1~y2까지 중력 작용 (y1<y2)
{
	if (y1 == y2) return;
	queue<int> nq;
	for (int y = y2; y >= y1; y--) {
		if (map[y][x] != -2) nq.push(map[y][x]);
	}
	for (int y = y2; y >= y1; y--) {
		if (!nq.empty()) {
			map[y][x] = nq.front(); nq.pop();
		}
		else {
			map[y][x] = -2;
		}
	}
}

void fall_down()
{
	deque<int> blk;
	for (int x = 0; x < N; x++) {
		blk.clear();
		for (int y = 0; y < N; y++) {
			if (map[y][x] == -1) blk.push_back(y);
		}
		if (blk.empty()) {
			fall_down_small(0, N - 1, x);
		}
		else {
			blk.push_front(-1);
			blk.push_back(N);
			for (int i = 0; i < blk.size() - 1; i++) {
				fall_down_small(blk[i] + 1, blk[i + 1] - 1, x);
			}
		}
	}
}

void rotate()
{
	int back[MAXN][MAXN] = { 0, };
	int nx = 0;
	for (int y = 0; y < N; y++) {
		int ny = N - 1;
		for (int x = 0; x < N; x++) {
			back[ny][nx] = map[y][x];
			ny--;
		}
		nx++;
	}

	copy(&back[0][0], &back[MAXN - 1][MAXN], &map[0][0]);
}

void solve()
{
	int ans = 0;
	while (true) {
		bg.clear();
		fill(&chk_block[0][0], &chk_block[MAXN - 1][MAXN], false); //1~5 블록만 체크

		//블록 그룹 찾기
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				if (map[y][x] == 0 || map[y][x] == -1 || map[y][x] == -2 || chk_block[y][x]) continue;
				for (int d = 0; d < 4; d++) { //주변에 무지개 블록 or 색이 같은 일반 블록이 있으면 ff 보내기
					int nx = x + dx[d];
					int ny = y + dy[d];
					if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
					if (chk_block[ny][nx]) continue; 
					if (map[ny][nx] == 0 || map[ny][nx] == map[y][x]) {
						flood_fill(y, x, chk_block);
						break;
					}
				}
			}
		}

		if (bg.empty()) break;
		//블록 그룹 정렬 후 제거 -> 제거된 블록들은 map에서 -2
		sort(bg.begin(), bg.end());
		ans += bg[0].size * bg[0].size;
		erase_dfs(bg[0].y, bg[0].x, map[bg[0].y][bg[0].x]);

		//중력 작용 -> 반시계 회전 -> 중력 작용
		fall_down();
		rotate();
		fall_down();
	}
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}