#include <iostream>
#include <vector>
using namespace std;

#define MAXN 100000
int N, R, Q;
int cnt[MAXN + 1]; //chk 배열로도 사용

vector<int> query;
vector<int> graph[MAXN + 1];


void input()
{
	cin >> N >> R >> Q;

	int u, v;
	for (int i = 0; i < N - 1; i++) {
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	int q;
	for (int i = 0; i < Q; i++) {
		cin >> q;
		query.push_back(q);
	}
}

int dfs(int n)
{
	cnt[n] = 1;

	for (int nn : graph[n]) {
		if (cnt[nn]) continue;
		cnt[n] += dfs(nn);
	}

	return cnt[n];
}

void solve()
{
	dfs(R);
	for (int q : query) cout << cnt[q] << "\n";
}


int main()
{
	input();
	solve();
	return 0;
}