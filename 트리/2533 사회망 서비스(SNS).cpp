#include <iostream>
#include <vector>
using namespace std;

#define MAXN 1000000
int N;
vector<int> tree[MAXN + 1];
int parent[MAXN + 1]; //root 찾기 위해
int chk[MAXN + 1];
int dp[MAXN + 1][2];


void input()
{
	cin >> N;
	int u, v;
	for (int i = 0; i < N - 1; i++) {
		cin >> u >> v;
		tree[u].push_back(v);
		tree[v].push_back(u);
		parent[v] = u;
	}
}

int find_root()
{
	for (int i = 1; i <= N; i++) {
		if (parent[i] == 0) return i;
	}
}

void dfs(int n)
{
	chk[n] = 1;

	for (int child : tree[n]) {
		if (chk[child]) continue;
		dfs(child);
		//n이 얼리어답터일때 -> child는 그냥 더 작은걸로
		dp[n][1] += min(dp[child][0], dp[child][1]);
		//n이 얼리어답터가 아닐때 -> child는 무조건 얼리어답터여야함
		dp[n][0] += dp[child][1];
	}
}

void solve()
{
	//dp 배열 초기화
	for (int i = 1; i <= N; i++) {
		dp[i][1] = 1;
	}

	int root = find_root();
	dfs(root);

	cout << min(dp[root][0], dp[root][1]);
}


int main()
{
	input();
	solve();
	return 0;
}