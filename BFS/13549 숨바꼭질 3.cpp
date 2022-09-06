#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAX 100000
int n, k;
struct POS { int x; int time; };
queue<POS> q;
int chk[MAX + 1];


void input()
{
	cin >> n >> k;
}

int bfs()
{
	fill(chk, chk + MAX + 1, 0x7fffffff);
	q.push({ n, 0 });
	chk[n] = 0;

	while (!q.empty()) {
		POS data = q.front(); q.pop();
		POS ndata;

		for (int i = 0; i < 3; i++) {
			if (i == 0) ndata.x = data.x - 1;
			else if (i == 1) ndata.x = data.x + 1;
			else if (i == 2) ndata.x = data.x * 2;

			if (ndata.x<0 || ndata.x>MAX) continue;

			ndata.time = (i == 2) ? chk[data.x] : chk[data.x] + 1;
			if (chk[ndata.x] > ndata.time) {
				chk[ndata.x] = ndata.time;
				q.push(ndata);
			}
		}
	}

	return chk[k];
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