#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define MAX 1500
int R, C;
char lake[MAX][MAX];
int map[MAX][MAX];
int ans = 0x7fffffff;

struct AXIS { int y; int x; };
bool chk[MAX][MAX] = { false }; //flood fill 확인용, dfs 방문확인용
queue<AXIS> q;
AXIS st, en;

struct STATUS {
	int y;
	int x;
	int max_time;
	bool operator<(const STATUS& s) const { return max_time > s.max_time; }
};
priority_queue<STATUS> pq;

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };


void input()
{
	cin >> R >> C;
	bool flag = false;
	for (int y = 0; y < R; y++) {
		for (int x = 0; x < C; x++) {
			cin >> lake[y][x];
			if (!flag && lake[y][x] == 'L') {
				flag = true;
				st.y = y; st.x = x;
				lake[y][x] = '.';
			}
			else if (lake[y][x] == 'L') {
				en.y = y; en.x = x;
				lake[y][x] = '.';
			}
		}
	}
}

void flood_fill(int& y, int& x, int& cnt) //lake .로 바꿔주고 map에 시간 저장
{
	q = {};
	q.push({ y, x });
	chk[y][x] = true;

	while (!q.empty()) {
		AXIS cur = q.front(); q.pop();

		for (int d = 0; d < 4; d++) {
			int nx = cur.x + dx[d];
			int ny = cur.y + dy[d];
			if (nx < 0 || ny < 0 || nx >= C || ny >= R) continue;
			if (chk[ny][nx]) continue;
			chk[ny][nx] = true;
			if (lake[ny][nx] == 'X') { //얼음이면 깨고 map에 기록 
				lake[ny][nx] = '.';
				map[ny][nx] = cnt;
			}
			else { //물이면 chk하고 q에 push
				q.push({ ny, nx });
			}
		}
	}
}

int bfs()
{
	fill(&chk[0][0], &chk[MAX - 1][MAX], false);

	pq.push({ st.y, st.x, 0 });
	chk[st.y][st.x] = true;

	while (!pq.empty()) {
		STATUS cur = pq.top(); pq.pop();
		if (cur.y == en.y && cur.x == en.x) return cur.max_time;

		for (int d = 0; d < 4; d++) {
			int nx = cur.x + dx[d];
			int ny = cur.y + dy[d];
			if (nx < 0 || ny < 0 || nx >= C || ny >= R) continue;
			if (chk[ny][nx]) continue;
			STATUS next = { ny, nx, max(cur.max_time, map[ny][nx]) };
			chk[ny][nx] = true;
			pq.push(next);
		}
	}
}

void solve()
{
	bool update = true;
	int cnt = 0;
	
	while (update) {
		fill(&chk[0][0], &chk[MAX - 1][MAX], false);
		update = false;
		cnt++;
		for (int y = 0; y < R; y++) {
			for (int x = 0; x < C; x++) {
				if (chk[y][x] == false && lake[y][x] == '.') {
					flood_fill(y, x, cnt);
				}
				if (lake[y][x] == 'X') update = true;
			}
		}
	}
	
	cout << bfs();
}


int main()
{
	input();
	solve();
	return 0;
}