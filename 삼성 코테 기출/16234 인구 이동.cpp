#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 50
int map[MAXN + 5][MAXN + 5];
int chk[MAXN + 5][MAXN + 5];
int N, L, R;

struct AXIS { int y; int x; };
vector<AXIS> alli;
queue<AXIS> q;
const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };


void input()
{
	cin >> N >> L >> R;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
		}
	}
}

void map_output()
{
	cout << "\nmap\n";
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cout << map[y][x] << " ";
		}
		cout << "\n";
	}
}

void search(const int& y, const int& x)
{
	alli = {};
	q = {};
	fill(&chk[0][0], &chk[MAXN + 4][MAXN + 5], 0);
	int sum = 0;

	q.push({ y, x });

	while (!q.empty()) {
		AXIS data = q.front(); q.pop();
		int tmp = map[data.y][data.x];
		int flag = 0;

		for (int d = 0; d < 4; d++) {
			int nx = data.x + dx[d];
			int ny = data.y + dy[d];

			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
			if (chk[ny][nx]) continue;

			if (abs(tmp - map[ny][nx]) >= L && abs(tmp - map[ny][nx]) <= R) {
				flag = 1;
				alli.push_back({ ny, nx });
				chk[ny][nx] = 1;
				sum += map[ny][nx];
			}
		}

		//유효한 상하좌우가 하나라도 있으면 q에 상하좌우 모두 넣기
		if (flag) {
			for (int d = 0; d < 4; d++) {
				int nx = data.x + dx[d];
				int ny = data.y + dy[d];

				if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
				q.push({ ny, nx });
			}
		}
	}

	int divide = sum / alli.size();
	for (AXIS a : alli) {
		map[a.y][a.x] = divide;
	}
}

AXIS find()
{
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			int tmp = map[y][x];
			for (int d = 0; d < 4; d++) {
				int nx = x + dx[d];
				int ny = y + dy[d];
				if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
				if (abs(tmp - map[ny][nx]) >= L && abs(tmp - map[ny][nx]) <= R) {
					return { y, x };
				}
			}
		}
	}

	return { -1, -1 };
}


int solve()
{
	int ans = 0;

	while (true) { //연합이 될 만한 것을 찾으면 중단하고 search에 보내기
		AXIS f = find();
		if (f.y == -1) return ans;
		search(f.y, f.x);
		ans++;
		map_output();
	}
}


int main(void)
{
	input();
	int ans = solve();
	cout << ans;
	return 0;
}