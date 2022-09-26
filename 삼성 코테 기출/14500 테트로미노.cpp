#include <iostream>
#include <algorithm>
using namespace std;

#define MAXNM 500
int N, M;
int map[MAXNM][MAXNM];


void input()
{
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> map[y][x];
		}
	}
}


int make_tet(const int& y, const int& x)
{
	int ret = -1;

	//l
	if (y + 3 < N) {
		int sum = 0;
		for (int i = 0; i < 4; i++) sum += map[y + i][x];
		ret = max(ret, sum);
	}
	if (x + 3 < M) {
		int sum = 0;
		for (int i = 0; i < 4; i++) sum += map[y][x + i];
		ret = max(ret, sum);
	}

	//정사각형
	if (x + 1 < M && y + 1 < N) {
		int sum = map[y][x] + map[y + 1][x] + map[y][x + 1] + map[y + 1][x + 1];
		ret = max(ret, sum);
	}

	//기역자
	if (y + 2 < N && x + 1 < M) {
		int sum = map[y][x] + map[y + 1][x] + map[y + 2][x] + map[y + 2][x + 1];
		ret = max(ret, sum);
	}
	if (y + 2 < N && x - 1 >= 0) {
		int sum = map[y][x] + map[y + 1][x] + map[y + 2][x] + map[y + 2][x - 1];
		ret = max(ret, sum);
	}
	if (y + 1 < N && x - 2 >= 0) {
		int sum = map[y][x] + map[y + 1][x] + map[y + 1][x - 1] + map[y + 1][x - 2];
		ret = max(ret, sum);
	}
	if (y + 1 < N && x + 2 < M) {
		int sum = map[y][x] + map[y + 1][x] + map[y + 1][x + 1] + map[y + 1][x + 2];
		ret = max(ret, sum);
	}
	if (y + 2 < N && x + 1 < M) {
		int sum = map[y][x] + map[y][x + 1] + map[y + 1][x + 1] + map[y + 2][x + 1];
		ret = max(ret, sum);
	}
	if (y + 2 < N && x - 1 >= 0) {
		int sum = map[y][x] + map[y][x - 1] + map[y + 1][x - 1] + map[y + 2][x - 1];
		ret = max(ret, sum);
	}
	if (y + 1 < N && x - 2 >= 0) {
		int sum = map[y][x] + map[y][x - 1] + map[y][x - 2] + map[y + 1][x - 2];
		ret = max(ret, sum);
	}
	if (y + 1 < N && x + 2 < M) {
		int sum = map[y][x] + map[y][x + 1] + map[y][x + 2] + map[y + 1][x + 2];
		ret = max(ret, sum);
	}

	//테트리스 모양
	if (y + 2 < N && x + 1 < M) {
		int sum = map[y][x] + map[y + 1][x] + map[y + 1][x + 1] + map[y + 2][x + 1];
		ret = max(ret, sum);
	}
	if (y + 2 < N && x - 1 >= 0) {
		int sum = map[y][x] + map[y + 1][x] + map[y + 1][x - 1] + map[y + 2][x - 1];
		ret = max(ret, sum);
	}
	if (y + 1 < N && x - 2 >= 0) {
		int sum = map[y][x] + map[y][x - 1] + map[y + 1][x - 1] + map[y + 1][x - 2];
		ret = max(ret, sum);
	}
	if (y + 1 < N && x + 2 < M) {
		int sum = map[y][x] + map[y][x + 1] + map[y + 1][x + 1] + map[y + 1][x + 2];
		ret = max(ret, sum);
	}

	//fuck..모양
	if (y + 1 < N && x + 2 < M) {
		int sum = map[y][x] + map[y][x + 1] + map[y][x + 2] + map[y + 1][x + 1];
		ret = max(ret, sum);
	}
	if (y - 1 >= 0 && x + 2 < M) {
		int sum = map[y][x] + map[y][x + 1] + map[y][x + 2] + map[y - 1][x + 1];
		ret = max(ret, sum);
	}
	if (y + 2 < N && x + 1 < M) {
		int sum = map[y][x] + map[y + 1][x] + map[y + 2][x] + map[y + 1][x + 1];
		ret = max(ret, sum);
	}
	if (y + 2 < N && x - 1 >= 0) {
		int sum = map[y][x] + map[y + 1][x] + map[y + 2][x] + map[y + 1][x - 1];
		ret = max(ret, sum);
	}

	return ret;
}


void solve()
{
	int ans = -1;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			int ret = make_tet(y, x);
			if (ret > ans) ans = ret;
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

