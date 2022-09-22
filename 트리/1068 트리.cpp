#include <iostream>
#include <set>
using namespace std;

#define MAXN 50
int N;
int erase;
int root;

int parent[MAXN];
set<int> tree[MAXN];


void input()
{
	cin >> N;
	int n;
	for (int i = 0; i < N; i++) {
		cin >> n;
		if (n == -1) root = i;
		else {
			tree[n].insert(i);
			parent[i] = n;
		}
	}
	cin >> erase;
	if (erase != root) tree[parent[erase]].erase(erase);
}

int dfs(int n)
{
	if (n == erase) return 0;
	if (tree[n].empty()) return 1;

	int ret = 0;

	for (int child : tree[n]) {
		ret += dfs(child);
	}

	return ret;
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