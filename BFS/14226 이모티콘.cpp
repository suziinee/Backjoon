#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXS 1000
int S;
struct EMO { int dis; int clip; int time; };
queue<EMO> q;
bool chk[MAXS + 1][MAXS + 1];


void input()
{
	cin >> S;
}

int bfs()
{
	q.push({ 1, 0, 0 });
	chk[1][0] = true;

	while (!q.empty()) {
		EMO data = q.front(); q.pop();

		//복사, 붙여넣기, 삭제
		int dis[3] = { data.dis, data.dis + data.clip, data.dis - 1 };
		int clip[3] = { data.dis, data.clip, data.clip };

		for (int i = 0; i < 3; i++) {
			if (dis[i] <= 0 || dis[i] > S || clip[i] <= 0 || clip[i] > S) continue;
			if (chk[dis[i]][clip[i]]) continue;

			q.push({ dis[i], clip[i], data.time + 1 });
			chk[dis[i]][clip[i]] = true;
			if (dis[i] == S) return data.time + 1;
		}
	}
}

void solve()
{
	int ans = bfs();
	cout << ans;
}


int main(void)
{
	input();
	solve();
	return 0;
}