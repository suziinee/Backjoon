#include <iostream>
#include <queue>
using namespace std;

#define MAX 1000
int H, W;
int map[MAX][MAX];

struct STATUS { int y; int x; int wave; };
queue<STATUS> q;


void input()
{
	cin >> H >> W;
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			char c;
			cin >> c;
			if (c == '.') {
				map[y][x] = 0;
			}
			else {
				map[y][x] = c - '0';
			}
		}
	}
}

int bfs() 
{
	static int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	static int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };

	for (int y = 0; y < H; y++) { //영향을 줄 수 있는 파도의 위치를 담기
		for (int x = 0; x < W; x++) {
			if (map[y][x] == 0) {
				q.push({ y, x, 0 });
			}
		}
	}

	STATUS cur;
	while (!q.empty()) {
		cur = q.front(); q.pop();

		for (int d = 0; d < 8; d++) {
			int nx = cur.x + dx[d];
			int ny = cur.y + dy[d];
			if (nx < 0 || ny < 0 || nx >= W || ny >= H) continue;
			if (map[ny][nx]) {
				map[ny][nx]--;
				if (map[ny][nx] == 0) { //무너졌다면 현재 위치를 큐에 넣기
					q.push({ ny, nx, cur.wave + 1 });
				}
			}
		}
	}
	return cur.wave;
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