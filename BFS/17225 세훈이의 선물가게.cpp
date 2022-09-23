#include <iostream>
#include <queue>
using namespace std;

int A, B, N;
queue<int> sangmin;
queue<int> jisu;

struct STATUS { int end_time; int color; }; //B는 1, R은 2
struct COMP {
	bool operator()(const STATUS& s1, const STATUS& s2) const {
		if (s1.end_time == s2.end_time) return s1.color > s2.color;
		return s1.end_time > s2.end_time;
	}
};
priority_queue<STATUS, vector<STATUS>, COMP> pq;


void input()
{
	cin >> A >> B >> N;

	int s, cnt; char c;
	for (int i = 0; i < N; i++) {
		cin >> s >> c >> cnt;
		if (c == 'B') {
			for (int j = 0; j < cnt; j++) sangmin.push(s);
		}
		else {
			for (int j = 0; j < cnt; j++) jisu.push(s);
		}
	}
}

void bfs()
{
	//상민
	int init = sangmin.front(); sangmin.pop();
	pq.push({ init, 1 });
	int st = init + A;

	while (!sangmin.empty()) {
		int cur = sangmin.front(); sangmin.pop();
		
		if (cur <= st) {
			pq.push({ st, 1 });
			st += A;
		}
		else {
			pq.push({ cur, 1 });
			st = cur + A;
		}
	}

	//지수
	init = jisu.front(); jisu.pop();
	pq.push({ init, 2 });
	int jt = init + B;

	while (!jisu.empty()) {
		int cur = jisu.front(); jisu.pop();

		if (cur <= jt) {
			pq.push({ jt, 2 });
			jt += B;
		}
		else {
			pq.push({ cur, 2 });
			jt = cur + B;
		}
	}
}

void solve()
{
	bfs();

	vector<int> s;
	vector<int> j;

	int cnt = 1;
	while (!pq.empty()) {
		STATUS cur = pq.top(); pq.pop();
		if (cur.color == 1) s.push_back(cnt);
		else j.push_back(cnt);
		cnt++;
	}

	cout << s.size() << "\n";
	for (int n : s) cout << n << " ";
	cout << "\n" << j.size() << "\n";
	for (int n : j) cout << n << " ";
}


int main()
{
	input();
	solve();
	return 0;
}