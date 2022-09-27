#include <iostream>
#include <queue>
using namespace std;

#define MAXD 1000
int N;
int ans;

struct TASK {
	int d;
	int w;
	bool operator<(const TASK& t) const {
		if (w == t.w) return d > t.d;
		return w < t.w;
	}
};
priority_queue<TASK> pq;
bool day[MAXD + 1];


void input()
{
	cin >> N;
	int d, w;
	for (int i = 0; i < N; i++) {
		cin >> d >> w;
		pq.push({ d, w });
	}
}

void bfs()
{
	while (!pq.empty()) {
		TASK cur = pq.top(); pq.pop();
		
		for (int d = cur.d; d >= 1; d--) {
			if (day[d] == false) {
				day[d] = true;
				ans += cur.w;
				break;
			}
		}
	}
}

void solve()
{
	bfs();
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}