#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAX 100
int N, M;
int board[MAX + 1];
int snake[MAX + 1];
int ladder[MAX + 1];
int dp[MAX + 1];
queue<int> q;


void input()
{
	int a, b;

	cin >> N >> M;
	for (int i = 0; i < N; i++) { //사다리 2
		cin >> a >> b;
		ladder[a] = b;
		board[a] = 2;
	}
	for (int i = 0; i < M; i++) { //뱀 1
		cin >> a >> b;
		snake[a] = b;
		board[a] = 1;
	}
}

int bfs()
{
	fill(dp, dp + MAX + 1, 0x7fffffff);

	q.push(1);
	dp[1] = 0;

	while (!q.empty()) {
		int n = q.front(); q.pop();

		for (int i = 1; i <= 6; i++) {
			int nn = n + i;

			if (nn > 100) continue;

			if (board[nn] == 1) nn = snake[nn];
			else if (board[nn] == 2) nn = ladder[nn];

			if (dp[nn] <= dp[n] + 1) continue;

			dp[nn] = dp[n] + 1;
			q.push(nn);
			if (nn == 100) return dp[nn];
		}
	}
}

void solve()
{
	int ans = bfs();
	cout << ans;
}


int main(void)
{
	input();
	solve();
	return 0;
}