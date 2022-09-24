#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_map>
using namespace std;

#define MAXN (20)
int N;
int chk[MAXN * MAXN + 1]; //앉힌 사람 확인 배열
int map[MAXN + 1][MAXN + 1];

struct STU {
	int n; //자기 번호
	int fav[4]; //좋아하는 학생의 번호
};
queue<STU> q;
unordered_map<int, STU> ht;

struct STATUS {
	int y; int x;
	int fav_cnt;
	int blk_cnt;
};
const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };


void input()
{
	cin >> N;
	for (int i = 0; i < N * N; i++) {
		STU s;
		cin >> s.n >> s.fav[0] >> s.fav[1] >> s.fav[2] >> s.fav[3];
		q.push(s);
		ht.insert({ s.n, s });
	}
}


bool compare(const STATUS& s1, const STATUS& s2)
{
	if (s1.fav_cnt == s2.fav_cnt) {
		if (s1.blk_cnt == s2.blk_cnt) {
			if (s1.y == s2.y) {
				return s1.x < s2.x;
			}
			return s1.y < s2.y;
		}
		return s1.blk_cnt > s2.blk_cnt;
	}
	return s1.fav_cnt > s2.fav_cnt;
}


void bfs()
{
	int init_flag = 0;

	while (!q.empty()) {
		STU cur = q.front(); q.pop();

		if (!init_flag) {
			map[2][2] = cur.n;
			chk[cur.n] = 1;
			init_flag = 1;
		}
		else {
			vector<STATUS> cand; //blk들 확인하기
			for (int y = 1; y <= N; y++) {
				for (int x = 1; x <= N; x++) {
					if (map[y][x]) continue;

					int fav_cnt = 0; int blk_cnt = 0;
					for (int d = 0; d < 4; d++) { //빈칸에 대해서 fav_cnt, blk_cnt 구해서 cand에 넣기
						int nx = x + dx[d];
						int ny = y + dy[d];
						if (nx < 1 || ny < 1 || nx > N || ny > N) continue;
						if (map[ny][nx] == 0) blk_cnt++;
						for (int f = 0; f < 4; f++) {
							if (map[ny][nx] == cur.fav[f]) fav_cnt++;
						}
					}
					cand.push_back({ y, x, fav_cnt, blk_cnt });
				}
			}
			sort(cand.begin(), cand.end(), compare); 
			map[cand[0].y][cand[0].x] = cur.n;
			chk[cur.n] = 1;
		}
	}
}


void solve()
{
	bfs();
	int ans = 0;

	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			STU cur = ht[map[y][x]];
			int cnt = 0;
			for (int d = 0; d < 4; d++) {
				int nx = x + dx[d];
				int ny = y + dy[d];
				if (nx < 1 || ny < 1 || nx > N || ny > N) continue;
				for (int f = 0; f < 4; f++) {
					if (map[ny][nx] == cur.fav[f]) cnt++;
				}
			}
			switch (cnt) {
			case 0: break;
			case 1: ans += 1; break;
			case 2: ans += 10; break;
			case 3: ans += 100; break;
			case 4: ans += 1000; break;
			}
		}
	}

	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}