#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAXN 1000
int N, M, X;

struct CONN { int n; int cost; };
vector<CONN> conn[MAXN + 1];
vector<CONN> conn_rev[MAXN + 1];

int chk[MAXN + 1]; //1~N에서 X까지 최단거리
int chk_rev[MAXN + 1]; //X에서 1~N까지 최단거리
struct STATUS { int cur; int sum_cost; };
queue<STATUS> q;

int dist[MAXN + 1]; //1~N의 오고 가는 최단거리


void input()
{
	cin >> N >> M >> X;

	int u, v, cost;
	for (int i = 0; i < M; i++) {
		cin >> u >> v >> cost;
		conn[u].push_back({ v, cost });
		conn_rev[v].push_back({ u, cost });
	}
}

void bfs(vector<CONN>* adj, int* chk) //X에서 1~N까지 최단거리 
{
	q = {};
	fill(chk, chk + MAXN + 1, 0x7fffffff);

	q.push({ X, 0 });
	chk[X] = 0;

	while (!q.empty()) {
		STATUS data = q.front(); q.pop();

		for (CONN c : adj[data.cur]) {
			STATUS ndata;
			ndata.cur = c.n;
			ndata.sum_cost = data.sum_cost + c.cost;
			if (chk[ndata.cur] <= ndata.sum_cost) continue;
			chk[ndata.cur] = ndata.sum_cost;
			q.push(ndata);
		}
	}
}

void solve()
{
	bfs(conn_rev, chk);
	bfs(conn, chk_rev);

	int max = -1;
	for (int i = 1; i <= N; i++) {
		dist[i] += chk[i] + chk_rev[i];
		if (dist[i] > max) max = dist[i];
	}
	cout << max;
}


int main()
{
	input();
	solve();
	return 0;
}