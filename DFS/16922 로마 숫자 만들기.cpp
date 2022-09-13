#include <iostream>
using namespace std;

#define MAXN 20
int N;
int chk[MAXN * 50 + 1];
int nums[4] = { 1, 5, 10, 50 };
int ans;


void input()
{
	cin >> N;
}

void dfs(int n, int s, int sum)
{
	if (n >= N) {
		if (chk[sum] == 0) {
			chk[sum] = 1; ans++;
		}
		return;
	}

	for (int i = s; i < 4; i++) {
		dfs(n + 1, i, sum + nums[i]);
	}
}

void solve()
{
	dfs(0, 0, 0);
	cout << ans;
}


int main(void)
{
	input();
	solve();
	return 0;
}