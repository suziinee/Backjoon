#include <iostream>
#include <queue>
using namespace std;

#define MAX 16
int n;
int ans;
int map[MAX + 2][MAX + 2];
struct PIPE {
	int x; int y; int dir;
};
PIPE pipe;

void input()
{
	cin >> n;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			cin >> map[y][x];
		}
	}
}

void output()
{
	cout << ans;
}

PIPE right(PIPE p)
{
	PIPE ret;
	ret.x = p.x + 1;
	ret.y = p.y;
	ret.dir = 0;
	return ret;
}

PIPE down(PIPE p)
{
	PIPE ret;
	ret.x = p.x;
	ret.y = p.y + 1;
	ret.dir = 1;
	return ret;
}

PIPE diagonal(PIPE p)
{
	PIPE ret;
	ret.x = p.x + 1;
	ret.y = p.y + 1;
	ret.dir = 2;
	return ret;
}

void bfs()
{
	queue<PIPE> q;
	q.push(pipe);

	while (!q.empty()) {
		PIPE tmp = q.front(); q.pop();
		if (tmp.x == (n-1) && tmp.y == (n-1)) {
			ans++;
			continue;
		}

		PIPE next;

		if (tmp.dir == 0) {
			//1. right
			next = right(tmp);
			if (!(next.x < 0 || next.y < 0 || next.x >= n || next.y >= n)) {
				if (map[next.y][next.x] == 0) {
					q.push(next);
				}
			}

			//2. diagonal
			next = diagonal(tmp);
			if (!(next.x < 0 || next.y < 0 || next.x >= n || next.y >= n)) {
				if (map[next.y][next.x] == 0 && map[next.y - 1][next.x] == 0 && map[next.y][next.x - 1] == 0) {
					q.push(next);
				}
			}
		}
		else if (tmp.dir == 1) {
			//1. down
			next = down(tmp);
			if (!(next.x < 0 || next.y < 0 || next.x >= n || next.y >= n)) {
				if (map[next.y][next.x] == 0) {
					q.push(next);
				}
			}

			//2. diagonal
			next = diagonal(tmp);
			if (!(next.x < 0 || next.y < 0 || next.x >= n || next.y >= n)) {
				if (map[next.y][next.x] == 0 && map[next.y - 1][next.x] == 0 && map[next.y][next.x - 1] == 0) {
					q.push(next);
				}
			}
		}
		else if (tmp.dir == 2) {
			//1. down
			next = down(tmp);
			if (!(next.x < 0 || next.y < 0 || next.x >= n || next.y >= n)) {
				if (map[next.y][next.x] == 0) {
					q.push(next);
				}
			}

			//2. right
			next = right(tmp);
			if (!(next.x < 0 || next.y < 0 || next.x >= n || next.y >= n)) {
				if (map[next.y][next.x] == 0) {
					q.push(next);
				}
			}

			//3. diagonal
			next = diagonal(tmp);
			if (!(next.x < 0 || next.y < 0 || next.x >= n || next.y >= n)) {
				if (map[next.y][next.x] == 0 && map[next.y - 1][next.x] == 0 && map[next.y][next.x - 1] == 0) {
					q.push(next);
				}
			}
		}
	}
}

void solve()
{
	pipe.y = 0;
	pipe.x = 1;
	pipe.dir = 0;
	bfs();
}


int main()
{
	input();
	solve();
	output();
	return 0;
}
