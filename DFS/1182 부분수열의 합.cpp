#include <iostream>
using namespace std;

#define MAXN 20
int N, S;
int nums[MAXN + 5];
int ans;


void input()
{
	cin >> N >> S;
	for (int i = 0; i < N; i++) {
		cin >> nums[i];
	}
}

void dfs(int n, int sum, int cnt) 
{
	if (n == N) {
		if (cnt > 0 && sum == S) ans++;
		return;
	}

	//n번째 인덱스 포함
	dfs(n + 1, sum + nums[n], cnt + 1);
	//n번째 인덱스 미포함
	dfs(n + 1, sum, cnt);
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