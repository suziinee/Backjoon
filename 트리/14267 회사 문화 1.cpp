#include <iostream>
#include <vector>
using namespace std;

#define MAXN 100000
int N, M;
int comp[MAXN + 1];
int ans[MAXN + 1];
vector<int> tree[MAXN + 1];


void input()
{
	cin >> N >> M;
	int n;
	for (int i = 1; i <= N; i++) {
		cin >> n;
		if (n != -1) tree[n].push_back(i);
	}

	int i, w;
	for (int j = 0; j < M; j++) {
		cin >> i >> w;
		comp[i] += w;
	}
}

void dfs(int n, int sum)
{
	ans[n] = sum;

	for (int next : tree[n]) {
		dfs(next, sum + comp[next]);
	}
}

void solve()
{
	dfs(1, 0);
	for (int i = 1; i <= N; i++) {
		cout << ans[i] << " ";
	}
}


int main()
{
	input();
	solve();
	return 0;
}