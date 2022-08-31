#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define MAXK 10000
int n, k;
vector<int> coins;
int dp[2][MAXK + 10];
int cur;


void input()
{
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		coins.push_back(a);
	}
}


void output()
{
	cout << dp[cur][k];
}


void solve()
{
	//dp[cur] 초기화
	for (int d = 1; d <= k; d++) {
		if (d%coins[0] == 0) dp[cur][d] = 1;
		else dp[cur][d] = 0;
	}

	for (int i = 1; i < n; i++) {

		int next = (cur + 1) % 2;

		for (int d = 1; d <= k; d++) {
			if (d < coins[i]) dp[next][d] += 0 + dp[cur][d];
			else if (d == coins[i]) dp[next][d] += 1 + dp[cur][d];
			else if (d > coins[i]) dp[next][d] = dp[cur][d] + dp[next][d - coins[i]];
		}

		//cur 초기화
		memset(dp[cur], 0, sizeof(dp[cur]));
		cur = next;
	}
}


int main()
{
	input();
	solve();
	output();
	return 0;
}