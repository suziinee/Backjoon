#include <iostream>
using namespace std;

#define MAXN 20
int N;
int map[MAXN][MAXN];
int team1[MAXN / 2]; int team2[MAXN / 2];
int pick[MAXN]; //1과 0으로 구분
int ans = 0x7fffffff;


void input() 
{
	cin >> N;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
		}
	}
}

void check()
{
	int t1 = 0; int t2 = 0;
	for (int i = 0; i < N; i++) {
		if (pick[i]) team1[t1++] = i;
		else team2[t2++] = i;
	}

	int sum1 = 0; int sum2 = 0;
	for (int i = 0; i < N / 2; i++) {
		for (int j = i + 1; j < N / 2; j++) {
			sum1 += map[team1[i]][team1[j]] + map[team1[j]][team1[i]];
			sum2 += map[team2[i]][team2[j]] + map[team2[j]][team2[i]];
		}
	}

	if (abs(sum1 - sum2) < ans) ans = abs(sum1 - sum2);
}

void dfs(int n, int s) 
{
	if (n == N / 2) { //pick의 1은 N/2만큼 체크되어 있어야함 (N/2개를 뽑았을 때)
		check();
		return;
	}

	for (int i = s; i < N; i++) { //i번째를 뽑아서 start에 넣는 것
		pick[i] = 1;
		dfs(n + 1, i + 1);
		pick[i] = 0;
	}
}

void solve() 
{
	dfs(0, 0);
	cout << ans;
}


int main(void)
{
	input();
	solve();
	return 0;
}