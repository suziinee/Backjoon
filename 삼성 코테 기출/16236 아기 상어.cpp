#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define MAXN 20
int N;
int map[MAXN][MAXN];

struct AXIS { int y; int x; };
AXIS shark;

struct SCAN { int y; int x; int size; int dist; }; //sort
vector<SCAN> cand;
queue<SCAN> q;
bool chk[MAXN][MAXN];

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };


void input()
{
	cin >> N;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
			if (map[y][x] == 9) {
				shark.y = y; shark.x = x;
				map[y][x] = 0;
			}
		}
	}
}

bool compare(const SCAN& s1, const SCAN& s2) 
{
	if (s1.dist == s2.dist) {
		if (s1.y == s2.y) return s1.x < s2.x;
		return s1.y < s2.y;
	}
	return s1.dist < s2.dist;
}

void bfs(int y, int x, int shark_size, int t)
{
	fill(&chk[0][0], &chk[MAXN - 1][MAXN], false);
	q = {};

	q.push({ y, x, 0, t });
	chk[y][x] = true;

	while (!q.empty()) {
		SCAN cur = q.front(); q.pop();
		for (int d = 0; d < 4; d++) {
			int nx = cur.x + dx[d];
			int ny = cur.y + dy[d];
			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
			if (chk[ny][nx]) continue;
			if (map[ny][nx] > shark_size) continue;

			chk[ny][nx] = true;
			if (map[ny][nx] < shark_size && map[ny][nx] != 0) {
				cand.push_back({ ny, nx, map[ny][nx], cur.dist + 1 });
			}
			else {
				q.push({ ny, nx, map[ny][nx], cur.dist + 1 });
			}
		}
	}
}

void solve()
{
	int time = 0;
	int shark_size = 2;
	int size_update = 0;
	bool update = true;

	while (update) {
		update = false;

		cand.clear();
		bfs(shark.y, shark.x, shark_size, 0);
		if (cand.empty()) break;
		else update = true;
		sort(cand.begin(), cand.end(), compare);

		//cand의 첫번째 물고기 잡아먹기
		map[cand[0].y][cand[0].x] = 0;
		shark.y = cand[0].y; 
		shark.x = cand[0].x;
		time += cand[0].dist;
		size_update++;
		if (size_update == shark_size) {
			shark_size++;
			size_update = 0;
		}
	}
	cout << time;
}


int main()
{
	input();
	solve();
	return 0;
}