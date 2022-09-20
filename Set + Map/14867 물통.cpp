#include <iostream>
#include <set>
#include <queue>
using namespace std;

struct STATUS { int a; int b; int cnt; };
STATUS st; 
STATUS en;
queue<STATUS> q;

struct CHK { int a; int b; };
struct COMP {
	bool operator()(const CHK& c1, const CHK& c2) const {
		if (c1.a == c2.a) return c1.b < c2.b;
		return c1.a < c2.a;
	}
};
set<CHK, COMP> s;


void input()
{
	cin >> st.a >> st.b >> en.a >> en.b;
	st.cnt = 0;
}


int bfs()
{
	if (0 == en.a && 0 == en.b) return 0;
	q.push({0, 0, 0});
	s.insert({ 0, 0 });

	while (!q.empty()) {
		STATUS cur = q.front(); q.pop();

		STATUS work[6] = { {st.a, cur.b, cur.cnt + 1},
								{cur.a, st.b, cur.cnt + 1},
								{0, cur.b, cur.cnt + 1},
								{cur.a, 0, cur.cnt + 1},
								{0, 0, cur.cnt + 1},
								{0, 0, cur.cnt + 1} };
		
		for (int i = 0; i < 6; i++) {
			STATUS next = work[i];
			if (i == 4) { //a에서 b로 move
				if (cur.a <= st.b - cur.b) { next.a = 0; next.b = cur.b + cur.a; }
				else { next.a = cur.a - (st.b - cur.b); next.b = st.b; }
			}
			else if (i == 5) { //b에서 a로 move
				if (cur.b <= st.a - cur.a) { next.a = cur.a + cur.b; next.b = 0; }
				else { next.a = st.a; next.b = cur.b - (st.a - cur.a); }
			}
			
			auto iter = s.find({ next.a, next.b });
			if (iter != s.end()) continue;

			if (next.a == en.a && next.b == en.b) return next.cnt;

			q.push(next);
			s.insert({ next.a, next.b });
		}
	}

	return -1;
}

void solve()
{
	cout << bfs();
}


int main()
{
	input();
	solve();
	return 0;
}