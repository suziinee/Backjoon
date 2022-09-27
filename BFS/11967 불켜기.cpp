#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define MAXN 100
int T, N, M;
int cnt;

struct AXIS { int y; int x; };
vector<AXIS> map[MAXN + 1][MAXN + 1];
bool chk[MAXN + 1][MAXN + 1];
int visited[MAXN + 1][MAXN + 1]; //현재 방문한 곳에서 최대로 켤 수 있는 불

queue<AXIS> q;


void bfs()
{
	q.push({ 1, 1 });
	chk[1][1] = true;
	
	for (AXIS next : map[1][1]) {
		if (chk[next.y][next.x] == false) {
			chk[next.y][next.x] = true;
			cnt++;
		}
	}
	visited[1][1] = cnt;

	while (!q.empty()) {
		AXIS cur = q.front(); q.pop();
		
	}
}

void input()
{
	cin >> T;
	for (int t = 0; t < T; t++) {
		cin >> N >> M;

		//초기화
		for (int y = 1; y <= N; y++) {
			for (int x = 1; x <= N; x++) {
				map[y][x].clear();
				chk[y][x] = false;
				visited[y][x] = 0;
			}
		}
		cnt = 0;

		int u, v, p, q;
		for (int i = 0; i < M; i++) {
			cin >> u >> v >> p >> q;
			map[u][v].push_back({ p, q });
		}

		chk[1][1] = true; cnt++;
		dfs({ 1, 1 });
		cout << cnt;
	}
}


int main()
{
	input();
	return 0;
}