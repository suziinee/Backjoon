#include <iostream>
using namespace std;

#define MAXN 499
int N;
int ans;
int map[MAXN][MAXN];
int wind_dx[4][10] = {
	{1, 1, 0, 0, -2, 0, 0, -1, -1, -1},
	{-1, 1, -2, 2, 0, -1, 1, -1, 1, 0},
	{-1, -1, 0, 0, 2, 0, 0, 1, 1, 1},
	{-1, 1, -2, 2, 0, -1, 1, -1, 1, 0} };
int wind_dy[4][10] = {
	{-1, 1, -2, 2, 0, -1, 1, -1, 1, 0},
	{-1, -1, 0, 0, 2, 0, 0, 1, 1, 1},
	{-1, 1, -2, 2, 0, -1, 1, -1, 1, 0},
	{1, 1, 0, 0, -2, 0, 0, -1, -1, -1} };
int wind_pt[9] = { 1, 1, 2, 2, 5, 7, 7, 10, 10 };

const int dx[] = { -1, 0, 1, 0 }; //left down right up
const int dy[] = { 0, 1, 0, -1 };


void input()
{
	cin >> N;
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			cin >> map[y][x];
		}
	}
}

void tornado(int y, int x, int d) //(y, x)로 d 방향의 바람이 불었음
{
	int sum = 0; //a를 구하기 위해
	
	for (int i = 0; i < 9; i++) {
		int nx = x + wind_dx[d][i];
		int ny = y + wind_dy[d][i];
		int sand = (map[y][x] * wind_pt[i]) / 100;
		sum += sand;
		if (nx < 0 || ny < 0 || nx >= N || ny >= N) {
			ans += sand;
		}
		else {
			map[ny][nx] += sand;
		}
	}

	int a = map[y][x] - sum;
	int ax = x + wind_dx[d][9];
	int ay = y + wind_dy[d][9];
	if (ax < 0 || ay < 0 || ax >= N || ay >= N) {
		ans += a;
	}
	else {
		map[ay][ax] += a;
	}
	map[y][x] = 0;
}

void solve()
{
	bool chk[MAXN][MAXN] = { false };
	int y = N / 2;
	int x = N / 2;
	int d = 3;
	chk[y][x] = true;

	for (int i = 0; i < N * N - 1; i++) {
		int nd = (d + 1) % 4;
		int nx = x + dx[nd];
		int ny = y + dy[nd];
		if (chk[ny][nx]) {
			nx = x + dx[d];
			ny = y + dy[d];
			nd = d;
		}
		tornado(ny, nx, nd);
		chk[ny][nx] = true;
		x = nx;
		y = ny;
		d = nd;
	}
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}