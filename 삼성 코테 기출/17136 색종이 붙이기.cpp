#include <iostream>
using namespace std;

int map[10][10];
bool chk[10][10];
int cnt[6];
int ans = 0x7fffffff;


void input()
{
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			cin >> map[y][x];
		}
	}
}

bool check(int y, int x, int n)
{
	if (y + n > 10 || x + n > 10) return false;

	for (int i = y; i < y + n; i++) {
		for (int j = x; j < x + n; j++) {
			if (map[i][j] == 0 || chk[i][j]) return false;
		}
	}
	return true;
}

void attach(int y, int x, int n)
{
	for (int i = y; i < y + n; i++) {
		for (int j = x; j < x + n; j++) {
			chk[i][j] = true;
		}
	}
}

void detach(int y, int x, int n)
{
	for (int i = y; i < y + n; i++) {
		for (int j = x; j < x + n; j++) {
			chk[i][j] = false;
		}
	}
}

void dfs(int sum)
{
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			if (map[y][x] == 0 || chk[y][x]) continue;
			for (int i = 1; i <= 5; i++) {
				if (cnt[i] < 5 && check(y, x, i)) {
					attach(y, x, i);
					cnt[i] += 1;
					dfs(sum + 1);
					cnt[i] -= 1;
					detach(y, x, i);
				}
			}
			return;
		}
	}
	
	if (ans > sum) ans = sum;
}

void solve()
{
	dfs(0);
	if (ans == 0x7fffffff) cout << -1;
	else cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}