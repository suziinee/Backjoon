#include <iostream>
using namespace std;

#define MAXN 15
int N;
int ans = 0;

struct COUNSIL { int t; int p; };
COUNSIL coun[MAXN + 1];


void input()
{
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> coun[i].t >> coun[i].p;
	}
}

void dfs(int cur, int sum)
{
	if (sum > ans) ans = sum;
	if (cur > N) return;

	//cur날의 상담을 선택
	if (cur + coun[cur].t - 1 <= N) dfs(cur + coun[cur].t, sum + coun[cur].p);
	//cur날의 상담을 선택하지 않음
	if (cur + 1 <= N) dfs(cur + 1, sum);
}

void solve()
{
	dfs(1, 0);
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}