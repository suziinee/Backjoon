#include <iostream>
#include <queue>
using namespace std;

#define MAX 100000
int n, k;
struct POS { int x; int t; };


void input()
{
	cin >> n >> k;
}

int bfs()
{
	queue<POS> q;
	bool chk[MAX + 10] = { false };

	q.push({ n, 0 });
	chk[n] = true;

	while (!q.empty()) {
		POS tmp = q.front(); q.pop();

		if (tmp.x - 1 >= 0 && tmp.x - 1 <= MAX && chk[tmp.x - 1] == false) {
			if (tmp.x - 1 == k) return tmp.t + 1;
			q.push({ tmp.x - 1, tmp.t + 1 });
			chk[tmp.x - 1] = true;
		}
		if (tmp.x + 1 >= 0 && tmp.x + 1 <= MAX && chk[tmp.x + 1] == false) {
			if (tmp.x + 1 == k) return tmp.t + 1;
			q.push({ tmp.x + 1, tmp.t + 1 });
			chk[tmp.x + 1] = true;
		}
		if (2 * tmp.x >= 1 && 2 * tmp.x <= MAX && chk[2 * tmp.x] == false) {
			if (tmp.x * 2 == k) return tmp.t + 1;
			q.push({ 2 * tmp.x, tmp.t + 1 });
			chk[2 * tmp.x] = true;
		}
	}

	return 0;
}

int solve()
{
	int ans = bfs();
	return ans;
}

void output(const int& ans)
{
	cout << ans;
}


int main()
{
	input();
	int ans = solve();
	output(ans);
	return 0;
}