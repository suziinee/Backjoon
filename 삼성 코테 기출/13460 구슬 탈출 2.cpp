#include <iostream>
#include <queue>
using namespace std;

#define MAXN 10
int N, M;
int ry, rx, by, bx;
char map[MAXN][MAXN];
bool chk[MAXN][MAXN][MAXN][MAXN];

struct STATUS {
	int ry, rx;
	int by, bx;
	int move;
};
queue<STATUS> q;

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };


void input()
{
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> map[y][x];
			if (map[y][x] == 'R') {
				ry = y; rx = x;
				map[y][x] = '.';
			}
			else if (map[y][x] == 'B') {
				by = y; bx = x;
				map[y][x] = '.';
			}
		}
	}
}

int get_yaxis(int y, int x, int d)
{
	while (map[y][x] != '#' && map[y][x] != 'O') {
		y += dy[d];
	}
	if (map[y][x] == '#') y -= dy[d];
	return y;
}

int get_xaxis(int y, int x, int d)
{
	while (map[y][x] != '#' && map[y][x] != 'O') {
		x += dx[d];
	}
	if (map[y][x] == '#') x -= dx[d];
	return x;
}

int bfs()
{
	q.push({ ry, rx, by, bx, 0 });
	chk[ry][rx][by][bx] = true;

	while (!q.empty()) {
		STATUS cur = q.front(); q.pop();
		if (cur.move > 10) return -1;
		if (map[cur.ry][cur.rx] == 'O' && map[cur.by][cur.bx] != 'O') return cur.move;

		for (int d = 0; d < 4; d++) {
			int nrx = cur.rx;
			int nry = cur.ry;
			int nbx = cur.bx;
			int nby = cur.by;

			if (d == 0 || d == 2) {
				nry = get_yaxis(cur.ry, cur.rx, d);
				nby = get_yaxis(cur.by, cur.bx, d);
			}
			else {
				nrx = get_xaxis(cur.ry, cur.rx, d);
				nbx = get_xaxis(cur.by, cur.bx, d);
			}
			if (nrx == nbx && nry == nby && map[nry][nrx] != 'O') {
				int red_dist = abs(cur.ry - nry) + abs(cur.rx - nrx);
				int blue_dist = abs(cur.by - nby) + abs(cur.bx - nbx);
				if (red_dist > blue_dist) { //더 많이 움직인 쪽이 뒤로가기
					nrx -= dx[d];
					nry -= dy[d];
				}
				else if (red_dist < blue_dist) {
					nbx -= dx[d];
					nby -= dy[d];
				}
				//같은 거리면 그냥 두기
			}

			//왔던 위치인지 체크
			if (chk[nry][nrx][nby][nbx]) continue;

			q.push({ nry, nrx, nby, nbx, cur.move + 1 });
			chk[nry][nrx][nby][nbx] = true;
		}
	}
	return -1;
}

void solve()
{
	cout << bfs();
}


int main()
{
	input();
	solve();
	return 0;
}