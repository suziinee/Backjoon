#include <iostream>
#include <vector>
using namespace std;

#define MAXN 10000
int N;

struct NODE { int n; int val; };
vector<NODE> tree[MAXN + 1];
int ans = -1;


void input()
{
	cin >> N;
	int u, v, val;
	for (int i = 0; i < N - 1; i++) {
		cin >> u >> v >> val;
		tree[u].push_back({ v, val });
	}
}

int dfs(int n, int sum)
{
	int max[2] = { sum, sum };

	for (NODE child : tree[n]) {
		int d = dfs(child.n, sum + child.val);
		if (d > max[1]) {
			if (d > max[0]) {
				max[1] = max[0];
				max[0] = d;
			}
			else max[1] = d;
		}
	}

	if (max[0] + max[1] - 2 * sum > ans) ans = max[0] + max[1] - 2 * sum;
	return max[0];
}
	
void solve()
{
	int ret = dfs(1, 0);
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}