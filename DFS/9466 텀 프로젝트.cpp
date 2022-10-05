#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100000
int N;
int nums[MAXN + 1];
int chk[MAXN + 1]; //0 : 아직 안함, 1 : 팀을 이룸, -1 : 팀을 못이룸


bool dfs(int st, int cur)
{
	if (st == cur) return true;
	if (cur == nums[cur]) return false;

	if (dfs(st, nums[cur])) {
		chk[cur] = 1;
		return true;
	}
	else {
		chk[cur] = -1;
		return false;
	}
}

void solve()
{
	for (int i = 1; i <= N; i++) {
		if (chk[i] != 0) continue;
		if (dfs(i, nums[i])) chk[i] = 1;
		else chk[i] = -1;
	}
	int cnt = 0;
	for (int i = 1; i <= N; i++) {
		if (chk[i] == -1) cnt++;
	}
	cout << cnt << "\n";
}

void input()
{
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> N;

		fill(nums, nums + MAXN, 0);
		fill(chk, chk + MAXN, 0);

		for (int i = 1; i <= N; i++) {
			cin >> nums[i];
		}

		solve();
	}
}


int main()
{
	input();
	return 0;
}