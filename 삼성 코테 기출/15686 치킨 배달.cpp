#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
int ans = 0x7fffffff;

struct AXIS { int y; int x; };
vector<AXIS> house;
vector<AXIS> chicken;
AXIS pick[13];


void input()
{
	cin >> N >> M;
	int n;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> n;
			switch (n) {
			case 1: house.push_back({ y, x }); break;
			case 2: chicken.push_back({ y, x }); break;
			case 0: break;
			}
		}
	}
}

int dist_calcul()
{
	int sum = 0;
	for (AXIS h : house) {
		int min_dist = 0x7fffffff;
		for (int i = 0; i < M; i++) {
			int dist = abs(h.y - pick[i].y) + abs(h.x - pick[i].x);
			min_dist = min(dist, min_dist);
		}
		sum += min_dist;
	}
	return sum;
}

void dfs(int s, int n)
{
	if (n == M) {
		int ret = dist_calcul();
		if (ret < ans) ans = ret;
		return;
	}

	for (int i = s; i < (int)chicken.size(); i++) {
		pick[n] = chicken[i];
		dfs(i + 1, n + 1);
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