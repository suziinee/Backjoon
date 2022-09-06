#include <iostream>
#include <cstring>
#include <list>
#include <vector>
#include <queue>
using namespace std;

#define MAXN 100
int n, m;
list<int> adjlist[MAXN + 1];
struct REL { int n; int rel; };


void input()
{
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		adjlist[a].push_back(b);
		adjlist[b].push_back(a);
	}
}

int bfs(int s)
{
	queue<REL> q;
	int chk[MAXN + 1];
	memset(chk, 0xff, sizeof(chk));

	q.push({ s, 0 });
	chk[s] = 0;

	while (!q.empty()) {
		REL data = q.front(); q.pop();

		for (auto a : adjlist[data.n]) {
			if (chk[a] == -1) {
				q.push({ a, data.rel + 1 });
				chk[a] = data.rel + 1;
			}
		}
	}

	int sum = 0;
	for (int i = 1; i <= n; i++) {
		if (chk[i] > 0) sum += chk[i];
	}

	return sum;
}

int solve()
{
	int min = 0x7fffffff; int min_idx;

	for (int i = 1; i <= n; i++) {
		int b = bfs(i);
		if (b < min) {
			min = b;
			min_idx = i;
		}
	}

	return min_idx;
}

void output(const int& ans)
{
	cout << ans;
}


int main(void) 
{
	input();
	int ans = solve();
	output(ans);
	return 0;
}