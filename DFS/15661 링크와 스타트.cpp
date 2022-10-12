#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAXN 20
int N;
int map[MAXN + 1][MAXN + 1]; //1번부터 사용
int ans = 0x7fffffff;
vector<int> team[2];


void input()
{
	cin >> N;
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			cin >> map[y][x];
		}
	}
}

int get_score(int t, int n) //n번 선수를 team[t]에 넣었을 때 점수
{
	if (team[t].size() == 0) return 0;
	int ret = 0;
	for (int m : team[t]) {
		ret += map[m][n] + map[n][m];
	}
	return ret;
}

void dfs(int n, int start, int link)
{
	if (n > N) {
		if (!team[0].empty() && !team[1].empty() && abs(start - link) < ans) {
			ans = abs(start - link);
		}
		return;
	}

	for (int t = 0; t < 2; t++) {
		int score = get_score(t, n);
		team[t].push_back(n);
		dfs(n + 1, start + (t == 0 ? score : 0), link + (t == 1 ? score : 0));
		team[t].pop_back();
	}
}

void solve()
{
	dfs(1, 0, 0); //1번부터 N번까지 team[0] or team[1]에 배정
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}