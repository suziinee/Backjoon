#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

#define MAXN 20
int N;
int map[MAXN + 1][MAXN + 1];

struct D { int d1, d2; };


void input()
{
	cin >> N;
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			cin >> map[y][x];
		}
	}
}

int separate(int y, int x, int d1, int d2)
{
	int min = 0x7fffffff; int max = 0;
	int fifth = 0;
	bool chk[MAXN + 1][MAXN + 1] = { false, };

	//5번 선거구 - 경계선
	int r, c;
	for (r = y, c = x; r <= y + d1, c >= x - d1; r++, c--) {
		if (chk[r][c]) continue;
		fifth += map[r][c];
		chk[r][c] = true;
	}
	for (r = y, c = x; r <= y + d2, c <= x + d2; r++, c++) {
		if (chk[r][c]) continue;
		fifth += map[r][c];
		chk[r][c] = true;
	}
	for (r = y + d1, c = x - d1; r <= y + d1 + d2, c <= x - d1 + d2; r++, c++) {
		if (chk[r][c]) continue;
		fifth += map[r][c];
		chk[r][c] = true;
	}
	for (r = y + d2, c = x + d2; r <= y + d1 + d2, c >= x - d1 + d2; r++, c--) {
		if (chk[r][c]) continue;
		fifth += map[r][c];
		chk[r][c] = true;
	}

	//1번 선거구
	int sum = 0;
	for (r = 1; r < y + d1; r++) {
		for (c = 1; c <= x; c++) {
			if (chk[r][c]) break;
			sum += map[r][c];
			chk[r][c] = true;
		}
	}
	if (sum > max) max = sum;
	if (sum < min) min = sum;

	//2번 선거구
	sum = 0;
	for (r = 1; r <= y + d2; r++) {
		for (c = N; c > x; c--) {
			if (chk[r][c]) break;
			sum += map[r][c];
			chk[r][c] = true;
		}
	}
	if (sum > max) max = sum;
	if (sum < min) min = sum;

	//3번 선거구
	sum = 0;
	for (r = y + d1; r <= N; r++) {
		for (c = 1; c < x - d1 + d2; c++) {
			if (chk[r][c]) break;
			sum += map[r][c];
			chk[r][c] = true;
		}
	}
	if (sum > max) max = sum;
	if (sum < min) min = sum;

	//4번 선거구
	sum = 0;
	for (r = y + d2 + 1; r <= N; r++) {
		for (c = N; c >= x - d1 + d2; c--) {
			if (chk[r][c]) break;
			sum += map[r][c];
			chk[r][c] = true;
		}
	}
	if (sum > max) max = sum;
	if (sum < min) min = sum;

	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			if (chk[y][x] == false) fifth += map[y][x];
		}
	}
	if (fifth > max) max = fifth;
	if (fifth < min) min = fifth;

	return max - min;
}

bool check(int y, int x, int d1, int d2)
{
	if (y + d1 > N || x - d1 < 1) return false;
	if (y + d2 > N || x + d2 > N) return false;
	if (y + d1 + d2 > N || x - d1 + d2<1 || x - d1 + d2>N) return false;
	return true;
}

void solve()
{
	int end = (N % 2) ? (N / 2) : (N / 2 - 1);
	vector<D> pair;

	for (int i = 1; i <= end; i++) {
		for (int j = 1; j <= N - 1 - i; j++) {
			pair.push_back({ i, j });
		}
	}

	int ans = 0x7fffffff;
	for (D d : pair) {
		for (int y = 1; y <= N; y++) {
			for (int x = 1; x <= N; x++) {
				if (check(y, x, d.d1, d.d2)) {
					int ret = separate(y, x, d.d1, d.d2);
					if (ret < ans) ans = ret;
				}
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