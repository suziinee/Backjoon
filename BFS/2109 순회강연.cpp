#include <iostream>
#include <queue>
using namespace std;

#define MAXD 10000
int N;
int day[MAXD + 1];

struct REQ {
	int p;
	int d;
	bool operator<(const REQ& r) const { return p < r.p; }
};
priority_queue<REQ> pq;


void input()
{
	cin >> N;
	int p, d;
	for (int i = 0; i < N; i++) {
		cin >> p >> d;
		pq.push({ p, d });
	}
}

int bfs()
{
	int ans = 0;

	REQ init = pq.top(); pq.pop();
	day[init.d] = 1;
	ans += init.p;

	while (!pq.empty()) {
		REQ cur = pq.top(); pq.pop();

		for (int i = cur.d; i >= 1; i--) {
			if (day[i] == 0) {
				day[i] = 1;
				ans += cur.p;
				break;
			}
		}
	}

	return ans;
}

void solve()
{
	if (N == 0) cout << 0;
	else cout << bfs();
}


int main()
{
	input();
	solve();
	return 0;
}