#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int M, S;

struct FISH { int y, x, d; };
vector<FISH> init_fish;
vector<FISH> map[4][4];
int smell[4][4]; //냄새의 양

struct SHARK { int y, x; };
SHARK shark;

struct STATUS {
	int sum, num;
	int d[3];
	bool operator<(const STATUS& s) {
		if (sum == s.sum) return num < s.num;
		return sum > s.sum;
	}
};
vector<STATUS> cand;


void input()
{
	cin >> M >> S;
	int y, x, d;
	for (int i = 0; i < M; i++) {
		cin >> y >> x >> d;
		--y; --x; --d;
		map[y][x].push_back({ y, x, d });
	}
	cin >> shark.y >> shark.x;
	--shark.y; --shark.x;
}

void copy_start() //물고기 정보를 init_fish에 복제
{
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (map[y][x].empty()) continue;
			for (FISH f : map[y][x]) init_fish.push_back(f);
		}
	}
}

void move_fish() //init_fish를 가지고 물고기 이동
{
	const int dx[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
	const int dy[] = { 0, -1, -1, -1, 0, 1, 1, 1 };

	vector<FISH> back[4][4];
	for (FISH f : init_fish) {
		bool move = false;
		for (int i = 0; i < 8; i++) {
			int nd = (f.d - i + 8) % 8; //45도 반시계 회전
			int nx = f.x + dx[nd];
			int ny = f.y + dy[nd];
			if (nx < 0 || ny < 0 || nx >= 4 || ny >= 4) continue;
			if (smell[ny][nx]) continue;
			if (nx == shark.x && ny == shark.y) continue;
			back[ny][nx].push_back({ ny, nx, nd });
			move = true;
			break;
		}
		if (!move) back[f.y][f.x].push_back(f);
	}

	copy(&back[0][0], &back[3][4], &map[0][0]);
}

void get_sum(int d1, int d2, int d3) //d1, d2, d3로 경로 만들어서 cand에 push
{
	static int dx[] = { 0, 0, -1, 0, 1 }; //up left down right
	static int dy[] = { 0, -1, 0, 1, 0 };

	int sum = 0;
	int num = d1 * 100 + d2 * 10 + d3;
	int d[3] = { d1, d2, d3 };
	int x = shark.x;
	int y = shark.y;
	bool chk[4][4] = { false, };

	for (int i = 0; i < 3; i++) {
		int nx = x + dx[d[i]];
		int ny = y + dy[d[i]];
		if (nx < 0 || ny < 0 || nx >= 4 || ny >= 4) return;
		if (chk[ny][nx]) {
			y = ny; x = nx;
			continue;
		}
		sum += map[ny][nx].size();
		chk[ny][nx] = true;
		y = ny; x = nx;
	}

	STATUS res;
	res.sum = sum;
	res.num = num;
	res.d[0] = d[0]; res.d[1] = d[1]; res.d[2] = d[2];
	cand.push_back(res);
}

void move_shark()
{
	static int dx[] = { 0, 0, -1, 0, 1 }; //up left down right
	static int dy[] = { 0, -1, 0, 1, 0 };

	cand.clear();
	for (int d1 = 1; d1 <= 4; d1++) {
		for (int d2 = 1; d2 <= 4; d2++) {
			for (int d3 = 1; d3 <= 4; d3++) {
				get_sum(d1, d2, d3);
			}
		}
	}
	sort(cand.begin(), cand.end());

	//cand[0]이 shark가 이동할 경로
	STATUS tar = cand[0];
	for (int i = 0; i < 3; i++) {
		shark.x += dx[tar.d[i]];
		shark.y += dy[tar.d[i]];
		if (!map[shark.y][shark.x].empty()) {
			map[shark.y][shark.x].clear();
			smell[shark.y][shark.x] = 3;
		}
	}
}

void disappear_smell() //smell 배열에서 냄새 1씩 빼기
{
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (smell[y][x]) smell[y][x]--;
		}
	}
}

void copy_complete() //init_fish의 물고기들을 map에 추가
{
	for (FISH f : init_fish) {
		map[f.y][f.x].push_back(f);
	}
	init_fish.clear();
}

void solve()
{
	for (int i = 0; i < S; i++) {
		copy_start();
		move_fish();
		move_shark();
		disappear_smell();
		copy_complete();
	}

	int sum = 0;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			sum += map[y][x].size();
		}
	}
	cout << sum;
}


int main()
{
	input();
	solve();
	return 0;
}