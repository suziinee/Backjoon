#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAXN 100
#define MAXM 10000
int T, N, M, K;

struct CONN {
	int n; int cost; int t;
};
struct STATUS {
	int bef; int cur; int sum_cost; int sum_t;
};
struct COMP {
	bool operator()(const STATUS& s1, const STATUS& s2) const {
		return s1.sum_t > s2.sum_t;
	}
};
vector<CONN> conn[MAXN + 1];
priority_queue<STATUS, vector<STATUS>, COMP> pq;
int chk[MAXN + 1][MAXM + 1]; //도착공항(어짜피 출발 공항은 1), M원과의 차이 비용 


int bfs()
{
	pq.push({ 0, 1, 0, 0 }); //이전공항, 현재공항, sum_cost, sum_t
	chk[1][M] = 0; //도착, M원과의 차이 비용

	while (!pq.empty()) {
		STATUS data = pq.top(); pq.pop();
		if (data.cur == N) return chk[data.cur][M - data.sum_cost];

		for (CONN next : conn[data.cur]) {
			STATUS ndata;
			ndata.bef = data.cur;
			ndata.cur = next.n;
			ndata.sum_cost = data.sum_cost + next.cost;
			ndata.sum_t = chk[data.cur][M - data.sum_cost] + next.t;

			if (ndata.sum_cost > M) continue;
			if (chk[ndata.cur][M - ndata.sum_cost] <= ndata.sum_t) continue;

			chk[ndata.cur][M - ndata.sum_cost] = ndata.sum_t;
			pq.push(ndata);
		}
	}
	return -1;
}


void input()
{
	cin >> T;
	int u, v, c, d;
	for (int t = 0; t < T; t++) {
		//초기화
		pq = {};
		for (int i = 0; i < MAXN + 1; i++) conn[i].clear();
		fill(&chk[0][0], &chk[MAXN][MAXM + 1], 0x7fffffff);

		cin >> N >> M >> K;
		for (int i = 0; i < K; i++) {
			cin >> u >> v >> c >> d;
			conn[u].push_back({ v, c, d });
		}

		int ret = bfs();
		if (ret == -1) cout << "Poor KCM\n";
		else cout << ret << "\n";
	}
}


int main()
{
	input();
	return 0;
}