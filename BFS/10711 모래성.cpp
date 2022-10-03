#include <iostream>
using namespace std;

#define MAX 1000
int H, W;
char map[2][MAX][MAX];
int cur;


void input()
{
	cin >> H >> W;
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			cin >> map[0][y][x];
		}
	}
}

void wave()
{
	static int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	static int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };

	int next = (cur + 1) % 2;
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			if (map[cur][y][x] == '.') {
				map[next][y][x] = '.';
				continue;
			}

			int cnt = 0;
			for (int d = 0; d < 8; d++) {
				int nx = x + dx[d];
				int ny = y + dy[d];
				if (map[cur][ny][nx] == '.') cnt++;
			}
			if (cnt >= map[cur][y][x] - '0') { //무너짐
				map[next][y][x] = '.';
			}
			else {
				map[next][y][x] = map[cur][y][x];
			}
		}
	}

	cur = next;
}

void solve()
{
	bool update = true;
	int ans = 0;

	while (update) {
		update = false;

		wave();
		ans++;

		int next = (cur + 1) % 2;
		for (int y = 0; y < H; y++) {
			for (int x = 0; x < W; x++) {
				if (map[next][y][x] != map[cur][y][x]) {
					update = true;
					break;
				}
			}
		}
	}

	cout << ans - 1;
}


int main()
{
	input();
	solve();
	return 0;
}