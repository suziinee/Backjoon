#include <iostream>
using namespace std;

int mark[4] = { 0, 0, 0, 0 };
int dice[10];
int ans;
int lut_score[33] = {
	0, 2, 4, 6, 8, 10, 12, 14, 16, 18,
	20, 22, 24, 26, 28, 30, 32, 34, 36, 38,
	40, 35, 30, 13, 16, 19, 25, 26, 27, 28,
	24, 22, 0 };
int lut_move[32][6] = {
	{0, 1, 2, 3, 4, 5}, {0, 2, 3, 4, 5, 6}, {0, 3, 4, 5, 6, 7}, {0, 4, 5, 6, 7, 8}, {0, 5, 6, 7, 8, 9},
	{0, 23, 24, 25, 26, 22}, {0, 7, 8, 9, 10, 11}, {0, 8, 9, 10, 11, 12}, {0, 9, 10, 11, 12, 13}, {0, 10, 11, 12, 13, 14},
	{0, 31, 30, 26, 22, 21}, {0, 12, 13, 14, 15, 16}, {0, 13, 14, 15, 16, 17}, {0, 14, 15, 16, 17, 18}, {0, 15, 16, 17, 18, 19},
	{0, 29, 28, 27, 26, 22}, {0, 17, 18, 19, 20, 32}, {0, 18, 19, 20, 32, 32}, {0, 19, 20, 32, 32, 32}, {0, 20, 32, 32, 32, 32},
	{0, 32, 32, 32, 32, 32}, {0, 20, 32, 32, 32, 32}, {0, 21, 20, 32, 32, 32}, {0, 24, 25, 26, 22, 21}, {0, 25, 26, 22, 21, 20},
	{0, 26, 22, 21, 20, 32}, {0, 22, 21, 20, 32, 32}, {0, 26, 22, 21, 20, 32}, {0, 27, 26, 22, 21, 20}, {0, 28, 27, 26, 22, 21},
	{0, 26, 22, 21, 20, 32}, {0, 30, 26, 22, 21, 20} };


void input()
{
	for (int i = 0; i < 10; i++) {
		cin >> dice[i];
	}
}

bool check(int idx, int tar)
{
	for (int i = 0; i < 4; i++) {
		if (i == idx) continue;
		if (mark[i] == 32) continue;
		if (mark[i] == tar) return false;
	}
	return true;
}

void dfs(int score, int n) //각 판마다 4개의 말을 움직이는 경우의 수 파생
{
	if (n == 10) {
		if (score > ans) ans = score;
		return;
	}

	for (int i = 0; i < 4; i++) { 
		if (mark[i] == 32) continue;
		int before = mark[i];
		int after = lut_move[mark[i]][dice[n]];
		if (!check(i, after)) continue;
		mark[i] = after;
		dfs(score + lut_score[after], n + 1);
		mark[i] = before;
	}
}

void solve()
{
	dfs(0, 0);
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}