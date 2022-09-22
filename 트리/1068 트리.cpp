#include <iostream>
#include <vector>
using namespace std;

#define MAXN 50
int N;
int erase;
int root;

vector<int> tree[MAXN];


void input()
{
	cin >> N;
	int n;
	for (int i = 0; i < N; i++) {
		cin >> n;
		if (n == -1) root = i;
		else tree[n].push_back(i);
	}
	cin >> erase;
}

int dfs(int n)
{
	if (tree[n].empty()) return 1;

	int ret = 0;

	for (int child : tree[n]) {
		if (child == erase) continue;
		ret += dfs(child);
	}

	if (ret) return ret;
	else return 1;
}

void solve()
{
	if (root != erase) cout << dfs(root);
	else cout << 0;
}


int main()
{
	input();
	solve();
	return 0;
}