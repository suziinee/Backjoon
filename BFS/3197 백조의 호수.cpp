#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

#define MAX 1500
int R, C;
char lake[MAX][MAX];
int map[MAX][MAX];
int chk[MAX][MAX]; //flood fill 확인용, bfs 방문확인용

struct AXIS { 
	int y; 
	int x;  
};
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
			if (lake[y][x] != 'X') {
				if (lake[y][x] == 'L') {
					if (!flag) {
						flag = true;
						st.y = y; st.x = x;
					}
					else {
						en.y = y; en.x = x;
					}
				}
				q.push({ y, x });
				chk[y][x] = 1;
			}
		}
	}
}

void flood_fill() //map에 시간 저장
{
	while (!q.empty()) {
		AXIS cur = q.front(); q.pop();

		for (int d = 0; d < 4; d++) {
			int nx = cur.x + dx[d];
			int ny = cur.y + dy[d];
			if (nx < 0 || ny < 0 || nx >= C || ny >= R) continue;
			if (chk[ny][nx]) continue;
			if (lake[ny][nx] != 'X') continue;

			chk[ny][nx] = 1;
			map[ny][nx] = map[cur.y][cur.x] + 1;
			q.push({ ny, nx });
		}
	}
}

int bfs()
{
	fill(&chk[0][0], &chk[MAX - 1][MAX], 0x7fffffff);

	pq.push({ st.y, st.x, 0 });
	chk[st.y][st.x] = 0;

	while (!pq.empty()) {
		STATUS cur = pq.top(); pq.pop();
		if (cur.y == en.y && cur.x == en.x) return cur.max_time;

		for (int d = 0; d < 4; d++) {
			int nx = cur.x + dx[d];
			int ny = cur.y + dy[d];
			if (nx < 0 || ny < 0 || nx >= C || ny >= R) continue;
			
			STATUS next = { ny, nx, max(cur.max_time, map[ny][nx])};
			if (chk[ny][nx] <= next.max_time) continue;
			
			chk[ny][nx] = next.max_time;
			pq.push(next);
		}
	}
}

void solve()
{
	flood_fill();
	cout << bfs();
}


int main()
{
	input();
	solve();
	return 0;
}