#include <iostream>
#include <set>
#include <unordered_set>
#include <queue>
using namespace std;

int A, B, C;

struct COMP {
	bool operator()(const int& i1, const int& i2) const { return i1 < i2; }
};
set<int, COMP> ans;

struct STATUS {
	int a, b, c;
	bool operator==(const STATUS& s) const {
		return (a == s.a) && (b == s.b) && (c == s.c);
	}
};
struct HASH {
	bool operator()(const STATUS& s) const {
		return s.a ^ s.b ^ s.c;
	}
};
unordered_set<STATUS, HASH> chk;
queue<STATUS> q;


void input()
{
	cin >> A >> B >> C;
}


void bfs()
{
	q.push({ 0, 0, C });
	chk.insert({ 0, 0, C });
	ans.insert(C);

	while (!q.empty()) {
		STATUS cur = q.front(); q.pop();

		//a에서 b로
		while (true) {
			if (cur.a == 0 || cur.b == B) break;
			STATUS next; next.c = cur.c;
			if (cur.a < B - cur.b) {
				next.a = 0;
				next.b = cur.b + cur.a;
			}
			else {
				next.a = cur.a - (B - cur.b);
				next.b = B;
			}
			auto it = chk.find(next);
			if (it == chk.end()) {
				chk.insert(next);
				q.push(next);
				if (next.a == 0) ans.insert(next.c);
			}
			break;
		}
		//b에서 a로
		while (true) {
			if (cur.b == 0 || cur.a == A) break;
			STATUS next; next.c = cur.c;
			if (cur.b < A - cur.a) {
				next.b = 0;
				next.a = cur.a + cur.b;
			}
			else {
				next.b = cur.b - (A - cur.a);
				next.a = A;
			}
			auto it = chk.find(next);
			if (it == chk.end()) {
				chk.insert(next);
				q.push(next);
				if (next.a == 0) ans.insert(next.c);
			}
			break;
		}
		//a에서 c로
		while (true) {
			if (cur.a == 0 || cur.c == C) break;
			STATUS next; next.b = cur.b;
			if (cur.a < C - cur.c) {
				next.a = 0;
				next.c = cur.c + cur.a;
			}
			else {
				next.a = cur.a - (C - cur.c);
				next.c = C;
			}
			auto it = chk.find(next);
			if (it == chk.end()) {
				chk.insert(next);
				q.push(next);
				if (next.a == 0) ans.insert(next.c);
			}
			break;
		}
		//c에서 a로
		while (true) {
			if (cur.c == 0 || cur.a == A) break;
			STATUS next; next.b = cur.b;
			if (cur.c < A - cur.a) {
				next.c = 0;
				next.a = cur.a + cur.c;
			}
			else {
				next.c = cur.c - (A - cur.a);
				next.a = A;
			}
			auto it = chk.find(next);
			if (it == chk.end()) {
				chk.insert(next);
				q.push(next);
				if (next.a == 0) ans.insert(next.c);
			}
			break;
		}
		//b에서 c로
		while (true) {
			if (cur.b == 0 || cur.c == C) break;
			STATUS next; next.a = cur.a;
			if (cur.b < C - cur.c) {
				next.b = 0;
				next.c = cur.c + cur.b;
			}
			else {
				next.b = cur.b - (C - cur.c);
				next.c = C;
			}
			auto it = chk.find(next);
			if (it == chk.end()) {
				chk.insert(next);
				q.push(next);
				if (next.a == 0) ans.insert(next.c);
			}
			break;
		}
		//c에서 b로
		while (true) {
			if (cur.c == 0 || cur.b == B) break;
			STATUS next; next.a = cur.a;
			if (cur.c < B - cur.b) {
				next.c = 0;
				next.b = cur.b + cur.c;
			}
			else {
				next.c = cur.c - (B - cur.b);
				next.b = B;
			}
			auto it = chk.find(next);
			if (it == chk.end()) {
				chk.insert(next);
				q.push(next);
				if (next.a == 0) ans.insert(next.c);
			}
			break;
		}
	}
}


void solve()
{
	bfs();
	for (int n : ans) cout << n << " ";
}


int main()
{
	input();
	solve();
	return 0;
}