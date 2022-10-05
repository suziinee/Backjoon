#include <iostream>
#include <deque>
#include <queue>
using namespace std;

#define MAXNM 50
int N, M, T;
deque<int> map[MAXNM];
int cur;

struct ROT { int x; int d; int k; };
deque<ROT> rot;

struct AXIS { int y; int x; int val; };
queue<AXIS> q;


void input()
{
	cin >> N >> M >> T;
	int n;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> n;
			map[y].push_back(n);
		}
	}
	int x, d, k;
	for (int t = 0; t < T; t++) {
		cin >> x >> d >> k;
		rot.push_back({ x, d, k });
	}
}

void clock(int y)
{
	int tmp = map[y].back();
	map[y].pop_back();
	map[y].push_front(tmp);
}

void counter_clock(int y)
{
	int tmp = map[y].front();
	map[y].pop_front();
	map[y].push_back(tmp);
}

void rotate(const ROT& r) //회전
{
	for (int y = 0; y < N; y++) {
		if ((y + 1) % r.x) continue;
		if (r.d) { //반시계
			for (int k = 0; k < r.k; k++) counter_clock(y);
		}
		else { //시계
			for (int k = 0; k < r.k; k++) clock(y);
		}
	}
}

bool flood_fill(int y, int x)
{
	bool flag = false;
	q = {};

	AXIS backup = { y, x };
	int tmp = map[y][x];
	q.push({ y, x, map[y][x]});
	map[y][x] = 0;

	while (!q.empty()) {
		AXIS data = q.front(); q.pop();
		if (data.y == 0) {
			int nx, ny;
			for (int d = 0; d < 3; d++) { //right down left
				switch (d) {
				case 0: nx = (data.x + 1) % M; ny = data.y; break;
				case 1: nx = data.x; ny = data.y + 1; break;
				case 2: nx = (data.x + M - 1) % M; ny = data.y; break;
				}
				if (map[ny][nx] == data.val) {
					q.push({ ny, nx, map[ny][nx]});
					map[ny][nx] = 0;
					flag = true;
				}
			}
		}
		else if (data.y == N - 1) {
			int nx, ny;
			for (int d = 0; d < 3; d++) { //right up left
				switch (d) {
				case 0: nx = (data.x + 1) % M; ny = data.y; break;
				case 1: nx = data.x; ny = data.y - 1; break;
				case 2: nx = (data.x + M - 1) % M; ny = data.y; break;
				}
				if (map[ny][nx] == data.val) {
					q.push({ ny, nx, map[ny][nx] });
					map[ny][nx] = 0;
					flag = true;
				}
			}
		}
		else {
			int nx, ny;
			for (int d = 0; d < 4; d++) { //right down left up
				switch (d) {
				case 0: nx = (data.x + 1) % M; ny = data.y; break;
				case 1: nx = data.x; ny = data.y + 1; break;
				case 2: nx = (data.x + M - 1) % M; ny = data.y; break;
				case 3: nx = data.x; ny = data.y - 1; break;
				}
				if (map[ny][nx] == data.val) {
					q.push({ ny, nx, map[ny][nx] });
					map[ny][nx] = 0;
					flag = true;
				}
			}
		}
	}

	if (!flag) { //인접한 요소가 하나도 없었음
		map[backup.y][backup.x] = tmp;
	}
	return flag;
}

double get_avg() 
{
	int sum = 0; int cnt = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (map[y][x]) {
				sum += map[y][x];
				cnt++;
			}
		}
	}
	return (double)sum / cnt;
}

void modify() //평균 구해서 원판 수정
{
	double avg = get_avg();
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (map[y][x] == 0) continue;
			if (map[y][x] > avg) map[y][x] -= 1;
			else if (map[y][x] < avg) map[y][x] += 1;
		}
	}
}

void solve()
{
	for (ROT r : rot) {
		rotate(r);

		bool chk = false;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < M; x++) {
				if (map[y][x]) {
					bool ret = flood_fill(y, x);
					if (ret) chk = true;
				}
			}
		}
		if (!chk) modify();
	}

	int sum = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			sum += map[y][x];
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