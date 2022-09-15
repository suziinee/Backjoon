#include <iostream>
#include <vector>
using namespace std;

#define MAXN 20
int N;
int map[MAXN][MAXN];
int pick[MAXN];
int ans = 0x7fffffff;
struct STATUS { int start; int link; };


void input()
{
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
}

STATUS check(int n)
{
	int start = 0;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			start += map[pick[i]][pick[j]];
		}
	}
	
	vector<int> nonpick;
	for (int i = 0; i < N; i++) {
		int flag = 0;
		for (int j = 0; j <= n; j++) {
			if (i == pick[j]) { flag = 1; break; }
		}
		if (!flag) nonpick.push_back(i);
	}

	int link = 0;
	for (int i = 0; i < nonpick.size(); i++) {
		for (int j = 0; j < nonpick.size(); j++) {
			link += map[nonpick[i]][nonpick[j]];
		}
	}

	return { start, link };
}

void dfs(int n, int s, int diff)
{
	if (ans > diff) ans = diff;
	if (n == N - 1) return;

	for (int i = s; i < N; i++) {
		pick[n] = i;
		STATUS s = check(n);
		dfs(n + 1, i + 1, abs(s.start - s.link));
	}
}

void solve()
{
	dfs(0, 0, 0x7fffffff);
	cout << ans;
}


int main(void)
{
	input();
	solve();
	return 0;
}