#include <iostream>
#include <list>
#include <queue>
using namespace std;

#define MAXV 20000
int V, E, K;

struct CONN { int n; int val; };
list<CONN> conn[MAXV + 1];
int conn_min[MAXV + 1][MAXV + 1];

struct STATUS { int cur; int sum; };
struct COMP {
	bool operator()(STATUS& s1, STATUS& s2) { return s1.sum > s2.sum; }
};
priority_queue<STATUS, vector<STATUS>, COMP> pq;
int chk[MAXV + 1];


void input()
{
	cin >> V >> E >> K;

	int s, n, val;
	fill(&conn_min[0][0], &conn_min[MAXV][MAXV + 1], 0x7fffffff);

	for (int i = 0; i < E; i++) {
		cin >> s >> n >> val;
		if (conn_min[s][n] <= val) continue;
		conn[s].push_back({ n, val });
		conn_min[s][n] = val;
	}
}

void bfs()
{
	fill(chk, chk + MAXV + 1, 0x7fffffff);

	pq.push({ K, 0 });
	chk[K] = 0;

	while (!pq.empty()) {
		STATUS data = pq.top(); pq.pop();

		for (CONN c : conn[data.cur]) { //cur와 연결된 간선들
			if (chk[c.n] <= data.sum + c.val) continue;
			chk[c.n] = data.sum + c.val;
			pq.push({ c.n, chk[c.n] });
		}
	}
}

void solve()
{
	bfs();
	for (int i = 1; i <= V; i++) {
		if (chk[i] == 0x7fffffff) {
			cout << "INF\n";
			continue;
		}
		cout << chk[i] << "\n";
	}
}


int main(void)
{
	input();
	solve();
	return 0;
}