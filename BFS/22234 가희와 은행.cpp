#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct CUSTOMER {
	int p;
	int t;
	int c;
};
struct COMP {
	bool operator()(const CUSTOMER& c1, const CUSTOMER& c2) {
		return c1.c > c2.c; //도착시간 빠른 손님이 우선순위
	}
};
priority_queue<CUSTOMER, vector<CUSTOMER>, COMP> pq;

struct STATUS {
	int p;
	int t;
};
queue<STATUS> q;

int N, T, W, M;


void input()
{
	cin >> N >> T >> W;
	int p, t, c;

	for (int i = 0; i < N; i++) {
		cin >> p >> t;
		q.push({ p, t }); //도착시간이 0초인 고객들은 q에 바로 넣기
	}

	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> p >> t >> c;
		pq.push({ p, t, c });
	}
}

void bfs()
{
	int time = 0;

	while (time < W && !q.empty()) {
		//time일때 업무 처리할 손님 cur
		STATUS cur = q.front(); q.pop();

		if (cur.t > T) {
			for (int i = 0; i < T; i++) {
				cout << cur.p << "\n";
				time++;
				if (time >= W) return;
			}
			//도착시간이 time 이하인 손님들 q에 넣기
			while (!pq.empty()) {
				CUSTOMER tmp = pq.top();
				if (tmp.c > time) break;
				q.push({ tmp.p, tmp.t });
				pq.pop();
			}
			q.push({ cur.p, cur.t - T });
		}
		else {
			for (int i = 0; i < cur.t; i++) {
				cout << cur.p << "\n";
				time++;
				if (time >= W) return;
			}
			//도착시간이 time 이하인 손님들 q에 넣기
			while (!pq.empty()) {
				CUSTOMER tmp = pq.top();
				if (tmp.c > time) break;
				q.push({ tmp.p, tmp.t });
				pq.pop();
			}
		}
	}
}

void solve()
{
	bfs();
}


int main()
{
	input();
	solve();
	return 0;
}