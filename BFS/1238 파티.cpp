#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAXN 1000
int N, M, X;

struct CONN { int n; int cost; };
vector<CONN> conn[MAXN + 1];

int chk[MAXN + 1][MAXN + 1]; //시작지점, 도착지점까지 최단거리
struct STATUS { int start; int cur; int sum_cost; };
queue<STATUS> q;

int dist[MAXN + 1]; //1~N의 오고 가는 최단거리


void input()
{
	cin >> N >> M >> X;

	int u, v, cost;
	for (int i = 0; i < M; i++) {
		cin >> u >> v >> cost;
		conn[u].push_back({ v, cost });
	}
}

void bfs() //1~N에서 1~N까지의 거리 구하기
{
	q = {};
	fill(&chk[0][0], &chk[MAXN][MAXN + 1], 0x7fffffff);

	for (int i = 1; i <= N; i++) {
		q.push({ i, i, 0 }); //start, cur, sum_cost
		chk[i][i] = 0; //start, cur
	}

	while (!q.empty()) {
		STATUS data = q.front(); q.pop();

		for (CONN c : conn[data.cur]) {
			STATUS ndata;
			ndata.start = data.start;
			ndata.cur = c.n;
			ndata.sum_cost = data.sum_cost + c.cost;
			if (chk[ndata.start][ndata.cur] <= ndata.sum_cost) continue;
			chk[ndata.start][ndata.cur] = ndata.sum_cost;
			q.push(ndata);
		}
	}
}

void solve()
{
	bfs();
	for (int i = 1; i <= N; i++) {
		dist[i] += chk[i][X]; //1~N에서 X까지
		dist[i] += chk[X][i]; //X에서 1~N까지
	}

	int max = -1;
	for (int i = 1; i <= N; i++) {
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