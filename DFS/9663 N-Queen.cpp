#include <iostream>
using namespace std;

#define MAXN 15
int N;
int chk[MAXN + 1];
int chess[MAXN + 1][MAXN + 1];
int ans;


void input()
{
	cin >> N;
}

bool dia_check(int r, int c)
{
	for (int rr = r - 1, cc = c + 1; rr >= 0 && cc < N; rr--, cc++) {
		if (chess[rr][cc]) return false;
	}
	for (int rr = r - 1, cc = c - 1; rr >= 0 && cc >= 0; rr--, cc--) {
		if (chess[rr][cc]) return false;
	}
	return true;
}

void dfs(int r) //r행이 놓여지는 col을 고르기
{
	if (r == N) {
		ans++;
		return;
	}

	for (int i = 0; i < N; i++) {
		if (chk[i]) continue;
		if (!dia_check(r, i)) continue;

		chk[i] = 1;
		chess[r][i] = 1;
		dfs(r + 1);
		chess[r][i] = 0;
		chk[i] = 0;
	}
}

void solve()
{
	dfs(0);
	cout << ans;
}


int main(void)
{
	input();
	solve();
	return 0;
}