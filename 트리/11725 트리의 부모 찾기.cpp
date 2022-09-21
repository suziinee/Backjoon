#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define MAXN 100000
int N;
vector<int> tree[MAXN + 1];
queue<int> q;
int parent[MAXN + 1];


void input()
{
	cin >> N;
	int a, b;
	for (int i = 0; i < N - 1; i++) {
		cin >> a >> b;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}
}

void bfs()
{
	q.push(1);
	parent[1] = 1;

	while (!q.empty()) {
		int n = q.front(); q.pop();

		for (int nn : tree[n]) {
			if (parent[nn]) continue;
			parent[nn] = n;
			q.push(nn);
		}
	}
}

void solve()
{
	bfs();
	for (int i = 2; i <= N; i++) cout << parent[i] << "\n";
}


int main()
{
	input();
	solve();
	return 0;
}