#include <iostream>
#include <queue>
using namespace std;

#define MAXN 10
int N, M, K;
int map[MAXN][MAXN];
int add[MAXN][MAXN]; //겨울에 더할 양분

struct TREE {
	int y, x, age;
	bool operator<(const TREE& t) const {
		return age > t.age;
	}
};
TREE tree[MAXN * MAXN];
priority_queue<TREE> pq[2];
queue<TREE> live;
queue<TREE> die;
int cur;


void input()
{
	cin >> N >> M >> K;
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			cin >> add[y][x];
			map[y][x] = 5;
		}
	}
	for (int i = 0; i < M; ++i) {
		cin >> tree[i].y >> tree[i].x >> tree[i].age;
		--tree[i].y; --tree[i].x;
		pq[cur].push(tree[i]);
	}
}

void spring()
{
	int next = (cur + 1) % 2;
	while (!pq[cur].empty()) {
		TREE data = pq[cur].top(); pq[cur].pop();
		if (map[data.y][data.x] < data.age) {
			die.push(data);
		}
		else {
			map[data.y][data.x] -= data.age;
			++data.age;
			live.push(data);
			pq[next].push(data);
		}
	}
}

void summer()
{
	while (!die.empty()) {
		TREE data = die.front(); die.pop();
		map[data.y][data.x] += (data.age / 2);
	}
}

void fall()
{
	static int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	static int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
	
	int next = (cur + 1) % 2;
	while (!live.empty()) {
		TREE data = live.front(); live.pop();
		if (data.age % 5) continue;
		for (int d = 0; d < 8; ++d) {
			int nx = data.x + dx[d];
			int ny = data.y + dy[d];
			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
			pq[next].push({ ny, nx, 1 });
		}
	}
}

void winter()
{
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			map[y][x] += add[y][x];
		}
	}
}

void solve()
{
	for (int year = 1; year <= K; ++year) {
		spring();
		summer();
		fall(); 
		winter();
		live = {};
		die = {};
		cur = (cur + 1) % 2;
	}
	cout << pq[cur].size();
}


int main()
{
	input();
	solve();
	return 0;
}