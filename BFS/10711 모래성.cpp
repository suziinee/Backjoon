#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;

#define MAX 1000
int H, W;
char map[2][MAX][MAX];
int cur;

struct STATUS {
	int y; int x; int wave;
	bool operator<(const STATUS& s) const {
		return wave > s.wave;
	}
	bool operator==(const STATUS& s) const {
		return (y == s.y) && (x == s.x) && (wave == s.wave);
	}
};
struct HASH {
	size_t operator()(const STATUS& s) const {
		return s.y ^ s.x ^ s.wave;
	}
};
priority_queue<STATUS> pq;
unordered_set<STATUS, HASH> chk;


void input()
{
	cin >> H >> W;
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			cin >> map[0][y][x];
			map[1][y][x] = map[0][y][x];
			if (map[0][y][x] != '.') {
				pq.push({ y, x, 1 });
				chk.insert({ y, x, 1 });
			}
		}
	}
}

void wave(int n) //cur에서 next로 기록
{
	static int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	static int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };

	int next = (cur + 1) % 2;
	while (!pq.empty()) {
		STATUS data = pq.top(); pq.pop();
		if (data.wave == n + 1) {
			pq.push(data);
			return;
		}

		int cnt = 0;
		for (int d = 0; d < 8; d++) {
			int nx = data.x + dx[d];
			int ny = data.y + dy[d];
			if (map[cur][ny][nx] == '.') cnt++;
		}
		if (cnt >= map[cur][data.y][data.x] - '0') {
			map[next][data.y][data.x] = '.';
			//8방향 모래성 모두 pq에 넣기
			for (int d = 0; d < 8; d++) {
				int nx = data.x + dx[d];
				int ny = data.y + dy[d];
				auto it = chk.find({ ny, nx, data.wave + 1 });
				if (it == chk.end() && map[cur][ny][nx] != '.') {
					pq.push({ ny, nx, data.wave + 1 });
					chk.insert({ ny, nx, data.wave + 1 });
				}
			}
		}
		else {
			pq.push({ data.y, data.x, data.wave + 1 });
		}
	}
}

void solve()
{
	bool update = true;
	int ans = 0;

	while (update) {
		update = false;

		ans++;
		wave(ans);

		int next = (cur + 1) % 2;
		for (int y = 0; y < H; y++) {
			for (int x = 0; x < W; x++) {
				if (map[next][y][x] != map[cur][y][x]) {
					update = true;
					break;
				}
			}
		}
		//next의 기록을 cur로 옮기기
		for (int y = 0; y < H; y++) {
			for (int x = 0; x < W; x++) {
				map[cur][y][x] = map[next][y][x];
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