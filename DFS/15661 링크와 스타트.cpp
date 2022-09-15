#include <iostream>
using namespace std;

#define MAXN 20
int N;
int map[MAXN][MAXN];
int team1[MAXN]; int team2[MAXN];
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

int check()
{
	int t1 = 0; int t2 = 0;
	for (int i = 0; i < N; i++) {
		if (pick[i]) team1[t1++] = i;
		else team2[t2++] = i;
	}

	int sum1 = 0; int sum2 = 0;
	for (int i = 0; i < t1; i++) {
		for (int j = i + 1; j < t1; j++) {
			sum1 += map[team1[i]][team1[j]] + map[team1[j]][team1[i]];
		}
	}
	for (int i = 0; i < t2; i++) {
		for (int j = i + 1; j < t2; j++) {
			sum2 += map[team2[i]][team2[j]] + map[team2[j]][team2[i]];
		}
	}

	return abs(sum1 - sum2);
}

void dfs(int n, int s, int diff) 
{
	if (diff < ans) ans = diff;
	if (n == N - 1) return;

	for (int i = s; i < N; i++) { //i번째를 뽑아서 start에 넣는 것
		pick[i] = 1;
		dfs(n + 1, i + 1, check());
		pick[i] = 0;
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