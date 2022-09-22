#include <iostream>
#include <cstdio>
#include <vector>
#include <deque>
using namespace std;

deque<int> q1; int p1;
deque<int> q2; int p2;
deque<int> q3; int p3;
deque<int> q4; int p4;
int K;

struct ROT { int q; int d; };
vector<ROT> rot;


void input()
{
	int n;
	for (int i = 0; i < 8; i++) { scanf("%1d", &n); q1.push_back(n); }
	for (int i = 0; i < 8; i++) { scanf("%1d", &n); q2.push_back(n); }
	for (int i = 0; i < 8; i++) { scanf("%1d", &n); q3.push_back(n); }
	for (int i = 0; i < 8; i++) { scanf("%1d", &n); q4.push_back(n); }

	cin >> K;
	int q, d;
	for (int i = 0; i < K; i++) {
		cin >> q >> d;
		rot.push_back({ q, d });
	}
}


void rotation(const int& q1_f, const int& q2_f, const int& q3_f, const int& q4_f)
{
	int tmp;

	if (q1_f != 0) {
		if (q1_f == 1) {
			tmp = q1.back(); q1.pop_back(); q1.push_front(tmp);
		}
		else {
			tmp = q1.front(); q1.pop_front(); q1.push_back(tmp);
		}
	}
	if (q2_f != 0) {
		if (q2_f == 1) {
			tmp = q2.back(); q2.pop_back(); q2.push_front(tmp);
		}
		else {
			tmp = q2.front(); q2.pop_front(); q2.push_back(tmp);
		}
	}
	if (q3_f != 0) {
		if (q3_f == 1) {
			tmp = q3.back(); q3.pop_back(); q3.push_front(tmp);
		}
		else {
			tmp = q3.front(); q3.pop_front(); q3.push_back(tmp);
		}
	}
	if (q4_f != 0) {
		if (q4_f == 1) {
			tmp = q4.back(); q4.pop_back(); q4.push_front(tmp);
		}
		else {
			tmp = q4.front(); q4.pop_front(); q4.push_back(tmp);
		}
	}
}


void solve()
{
	for (ROT r : rot) {
		int q1_flag = 0;
		int q2_flag = 0;
		int q3_flag = 0;
		int q4_flag = 0;

		switch (r.q) {
		case 1: {
			q1_flag = r.d;
			if (q1[2] != q2[6]) {
				q2_flag = -1 * r.d;
				if (q2[2] != q3[6]) {
					q3_flag = r.d;
					if (q3[2] != q4[6]) q4_flag = -1 * r.d;
				}	
			}
			rotation(q1_flag, q2_flag, q3_flag, q4_flag);
			break;
		}
		case 2: {
			q2_flag = r.d;
			if (q1[2] != q2[6]) q1_flag = -1 * r.d;
			if (q2[2] != q3[6]) {
				q3_flag = -1 * r.d;
				if (q3[2] != q4[6]) q4_flag = r.d;
			}
			rotation(q1_flag, q2_flag, q3_flag, q4_flag);
			break;
		}
		case 3: {
			q3_flag = r.d;
			if (q3[2] != q4[6]) q4_flag = -1 * r.d;
			if (q3[6] != q2[2]) {
				q2_flag = -1 * r.d;
				if (q2[6] != q1[2]) q1_flag = r.d;
			}
			rotation(q1_flag, q2_flag, q3_flag, q4_flag);
			break;
		}
		case 4: {
			q4_flag = r.d;
			if (q4[6] != q3[2]) {
				q3_flag = -1 * r.d;
				if (q3[6] != q2[2]) {
					q2_flag = r.d;
					if (q2[6] != q1[2]) q1_flag = -1 * r.d;
				}
			}
			rotation(q1_flag, q2_flag, q3_flag, q4_flag);
			break;
		}
		}
	}

	int ans = 0;
	ans += (q1[0]) ? 1 : 0;
	ans += (q2[0]) ? 2 : 0;
	ans += (q3[0]) ? 4 : 0;
	ans += (q4[0]) ? 8 : 0;
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}