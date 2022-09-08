#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 8
int N;
int nums[MAXN + 3];
int chk[MAXN + 3];
int pick[MAXN + 3];
int ans = -1;


void input()
{
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> nums[i];
	}
}

void dfs(int n, int sum) //depth, sum
{
	if (n > N) {
		if (sum > ans) ans = sum;
		return;
	}

	for (int i = 1; i <= N; i++) {
		if (chk[i] == 0) {
			pick[n] = nums[i];
			chk[i] = 1;
			if (n >= 2) dfs(n + 1, sum + abs(pick[n] - pick[n - 1]));
			else dfs(n + 1, sum);
			chk[i] = 0;
		}
	}
}

void solve()
{
	dfs(1, 0);
	cout << ans << "\n";
}


int main(void)
{
	input();
	solve();
	return 0;
}