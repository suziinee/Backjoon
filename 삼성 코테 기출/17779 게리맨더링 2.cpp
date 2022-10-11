#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 20
int N;
int map[MAXN + 1][MAXN + 1];
int total;


void input()
{
	cin >> N;
	for (int x = 1; x <= N; x++) {
		for (int y = 1; y <= N; y++) {
			cin >> map[x][y];
			total += map[x][y];
		}
	}
}

int separate(int x, int y, int d1, int d2)
{
	int back[MAXN + 1][MAXN + 1] = { 0, }; //5의 경계선 표시
	int sum[6] = { 0, };

	//(x, y), (x+1, y-1), ..., (x+d1, y-d1)
	//(x+d2, y+d2), (x+d2+1, y+d2-1), ..., (x+d2+d1, y+d2-d1)
	for (int i = 0; i <= d1; i++) {
		back[x + i][y - i] = 5;
		back[x + d2 + i][y + d2 - i] = 5;
	}
	//(x, y), (x+1, y+1), ..., (x+d2, y+d2)
	//(x+d1, y-d1), (x+d1+1, y-d1+1), ... (x+d1+d2, y-d1+d2)
	for (int i = 0; i <= d2; i++) {
		back[x + i][y + i] = 5;
		back[x + d1 + i][y - d1 + i] = 5;
	}

	//1번 선거구: 1 ≤ r < x+d1, 1 ≤ c ≤ y
	for (int r = 1; r < x + d1; r++) {
		for (int c = 1; c <= y; c++) {
			if (back[r][c] == 5) break;
			sum[1] += map[r][c];
		}
	}
	//2번 선거구: 1 ≤ r ≤ x+d2, y < c ≤ N
	for (int r = 1; r <= x + d2; r++) {
		for (int c = N; c > y; c--) {
			if (back[r][c] == 5) break;
			sum[2] += map[r][c];
		}
	}
	//3번 선거구: x+d1 ≤ r ≤ N, 1 ≤ c < y-d1+d2
	for (int r = x + d1; r <= N; r++) {
		for (int c = 1; c < y - d1 + d2; c++) {
			if (back[r][c] == 5) break;
			sum[3] += map[r][c];
		}
	}
	//4번 선거구: x+d2 < r ≤ N, y-d1+d2 ≤ c ≤ N
	for (int r = x + d2 + 1; r <= N; r++) {
		for (int c = N; c >= y - d1 + d2; c--) {
			if (back[r][c] == 5) break;
			sum[4] += map[r][c];
		}
	}

	sum[5] = total - sum[1] - sum[2] - sum[3] - sum[4];
	int min_sum = min({ sum[1], sum[2], sum[3], sum[4], sum[5] });
	int max_sum = max({ sum[1], sum[2], sum[3], sum[4], sum[5] });
	return max_sum - min_sum;
}

void solve()
{
	int ans = 0x7fffffff;
	for (int x = 1; x <= N; x++) {
		for (int y = 1; y <= N; y++) {
			for (int d1 = 1; d1 <= N; d1++) {
				for (int d2 = 1; d2 <= N; d2++) {
					if (x + d1 + d2 > N) continue;
					if (y - d1 < 1) continue;
					if (y + d2 > N) continue;
					int ret = separate(x, y, d1, d2);
					if (ans > ret) ans = ret;
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