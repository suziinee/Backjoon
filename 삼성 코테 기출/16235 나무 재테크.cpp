#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXN 10
int N, M, K;
int map[MAXN][MAXN];
int add[MAXN][MAXN]; //겨울에 더할 양분

struct TREE {
	int y, x, age;
};
bool compare(const TREE& t1, const TREE& t2) {
	return t1.age < t2.age;
}
TREE tree[MAXN * MAXN];
queue<TREE> q[2];
queue<TREE> live; //올해 번식 가능한 tree
queue<TREE> die; //올해 죽은 tree
queue<TREE> born; //올해 가을에 새로 태어난 tree
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
	}
	sort(tree, tree + M, compare);
	for (int i = 0; i < M; ++i) {
		q[cur].push(tree[i]);
	}
}

void spring()
{
	die = {};
	live = {};
	int next = (cur + 1) % 2;

	//born tree부터 해주기 -> 2살로 q[next]에 들어감
	while (!born.empty()) {
		TREE data = born.front(); born.pop();
		if (map[data.y][data.x] < data.age) {
			die.push(data);
		}
		else {
			map[data.y][data.x] -= data.age;
			++data.age;
			q[next].push(data);
		}
	}
	//나머지 올해 tree 해주기
	while (!q[cur].empty()) {
		TREE data = q[cur].front(); q[cur].pop();
		if (map[data.y][data.x] < data.age) {
			die.push(data);
		}
		else {
			map[data.y][data.x] -= data.age;
			++data.age;
			q[next].push(data);
			if (data.age % 5 == 0) live.push(data);
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
	
	born = {};
	int next = (cur + 1) % 2;

	while (!live.empty()) {
		TREE data = live.front(); live.pop();
		if (data.age % 5) continue;
		for (int d = 0; d < 8; ++d) {
			int nx = data.x + dx[d];
			int ny = data.y + dy[d];
			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
			born.push({ ny, nx, 1 });
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
		cur = (cur + 1) % 2;
	}
	cout << q[cur].size() + born.size();
}


int main()
{
	input();
	solve();
	return 0;
}