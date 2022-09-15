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

struct STATUS { int n; int cnt; };
struct COMP {
	bool operator()(STATUS& s1, STATUS& s2) { return s1.cnt > s2.cnt; }
};
priority_queue<STATUS, vector<STATUS>, COMP> pq;
int chk[MAXN + 1][MAXN + 1];


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

void bfs(int st) //st에서 갈 수 있는 모든 곳 구하기
{
	pq = {};

	pq.push({ st, 0 });
	chk[st][st] = 0;

	while (!pq.empty()) {
		STATUS data = pq.top(); pq.pop();

		for (int nn = 1; nn <= N; nn++) {

			if (!map[data.n][nn] && !map[nn][data.n]) continue;

			if (map[data.n][nn] && chk[st][nn] > data.cnt) { //길이 있다면 그냥 가면 됨
				chk[st][nn] = data.cnt;
				pq.push({ nn, data.cnt });
			}
			else if (map[nn][data.n] && chk[st][nn] > data.cnt + 1) { //길이 한방향으로만 있음
				chk[st][nn] = data.cnt + 1;
				pq.push({ nn, data.cnt + 1 });
			}
		}
	}
}

void solve()
{
	fill(&chk[0][0], &chk[MAXN][MAXN + 1], 0x7fffffff); //양방향으로 바꾼 최소 개수

	for (QUS q : qus) {
		bfs(q.st);
	}
	for (QUS q : qus) {
		cout << chk[q.st][q.en] << "\n";
	}
}


int main(void)
{
	input();
	solve();
	return 0;
}