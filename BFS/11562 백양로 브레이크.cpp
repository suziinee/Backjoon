#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define MAXN 250
int N, M;
int map[MAXN + 1][MAXN + 1];

int K;
struct QUS { int st; int en; };
vector<QUS> qus;

queue<int> q;
int chk[MAXN + 1];


void input()
{
	cin >> N >> M;

	int u, v, b;
	for (int i = 0; i < M; ++i) {
		cin >> u >> v >> b;
		if (b) {
			map[u][v] = 1;
			map[v][u] = 1;
		}
		else map[u][v] = 1;
	}

	cin >> K;

	int st, en;
	for (int i = 0; i < K; ++i) {
		cin >> st >> en;
		qus.push_back({ st, en });
	}
}

int bfs(int st, int en)
{
	//초기화
	q = {};
	fill(chk, chk + MAXN + 1, 0x7fffffff); //양방향으로 바꾼 최소 개수

	q.push(st);
	chk[st] = 0;
	if (st == en) return chk[st];

	while (!q.empty()) {
		int n = q.front(); q.pop();

		for (int nn = 1; nn <= N; nn++) {

			if (!map[n][nn] && !map[nn][n]) continue;

			if (map[n][nn] && chk[nn] > chk[n]) { //길이 있다면 그냥 가면 됨
				chk[nn] = chk[n];
				q.push(nn);
			}
			else if (map[nn][n] && chk[nn] > chk[n] + 1) { //길이 한방향으로만 있음
				chk[nn] = chk[n] + 1;
				q.push(nn);
			}
		}
	}
	
	return chk[en];
}


void solve()
{
	for (QUS q : qus) {
		int ret = bfs(q.st, q.en);
		cout << ret << "\n";
	}
}


int main(void)
{
	input();
	solve();
	return 0;
}