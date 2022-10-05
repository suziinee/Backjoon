#include <iostream>
#include <deque>
#include <queue>
using namespace std;

#define MAXNM 50
int N, M, T;
deque<int> map[MAXNM];

struct ROT { int x; int d; int k; };
deque<ROT> rot;

struct AXIS { int y; int x; int val; };
queue<AXIS> q;

const int dx[] = { 1, 0, -1, 0 }; //left down right up
const int dy[] = { 0, 1, 0, -1 };


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

void flood_fill(int y, int x)
{
	q = {};
	q.push({ y, x, map[y][x] });
	map[y][x] = 0;

	while (!q.empty()) {
		AXIS cur = q.front(); q.pop();
		for (int d = 0; d < 4; d++) {
			int nx = (cur.x + dx[d] + M) % M; //x는 rotation 시켜놓음
			int ny = cur.y + dy[d];
			if (ny < 0 || ny >= N) continue; //y만 범위 확인하기
			if (map[ny][nx] == cur.val) {
				q.push({ ny, nx, map[ny][nx] });
				map[ny][nx] = 0;
			}
		}
	}
}

bool erase()
{
	bool ret = false;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (map[y][x] == 0) continue;
			for (int d = 0; d < 4; d++) {
				int nx = (x + dx[d] + M) % M; //x는 rotation 시켜놓음
				int ny = y + dy[d];
				if (ny < 0 || ny >= N) continue; //y만 범위 확인하기
				if (map[y][x] == map[ny][nx]) {
					flood_fill(y, x);
					ret = true;
					break;
				}
			}
		}
	}
	return ret;
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
		if (!erase()) modify();
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