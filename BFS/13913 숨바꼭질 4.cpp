#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAX 100000
int n, k;
struct POS { int x; int time; };
queue<POS> q;
bool chk[MAX + 10];
int path[MAX + 10];


void input()
{
	cin >> n >> k;
}

int bfs()
{
	q.push({ n, 0 });
	chk[n] = true;
	path[n] = -1;
	if (n == k) return 0;

	while (!q.empty()) {
		POS data = q.front(); q.pop();
		POS ndata;

		for (int i = 0; i < 3; i++) {
			if (i == 0) ndata.x = data.x - 1;
			else if (i == 1) ndata.x = data.x + 1;
			else if (i == 2) ndata.x = data.x * 2;
			ndata.time = data.time + 1;

			if (ndata.x >= 0 && ndata.x <= MAX && chk[ndata.x] == false) {
				chk[ndata.x] = true;
				path[ndata.x] = data.x;
				q.push(ndata);
				if (ndata.x == k) return ndata.time;
			}
		}
	}
}

void print_route(int m)
{
	if (m == -1) return;
	print_route(path[m]);
	cout << m << " ";
}

void solve()
{
	int ans = bfs();
	cout << ans << "\n";
	print_route(k);
}


int main(void)
{
	input();
	solve();
	return 0;
}