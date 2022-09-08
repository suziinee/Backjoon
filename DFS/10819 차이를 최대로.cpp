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

void dfs(int n) //depth, sum
{
	if (n > N) {
		int sum = 0; 
		int new_arr[MAXN + 3] = { 0 };
		for (int i = 1; i <= N; i++) { new_arr[pick[i]] = nums[i]; }
		for (int i = 2; i <= N; i++) { sum += abs(new_arr[i] - new_arr[i - 1]); }
		if (sum > ans) ans = sum;
		return;
	}

	for (int i = 1; i <= N; i++) { 
		if (chk[i] == 0) {
			pick[n] = i;
			chk[i] = 1;
			dfs(n + 1);
			chk[i] = 0;
		}
	}
}

void solve()
{
	dfs(1);
	cout << ans << "\n";
}


int main(void)
{
	input();
	solve();
	return 0;
}