#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<int> v;
int ans = 0x7fffffff;


void input()
{
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		v.push_back(a);
	}
}


void output()
{
	cout << ans;
}


void solve()
{
	sort(v.begin(), v.end());

	int st = 0; int en = 0;
	for (st = 0; st < n - 1; st++) { //st에 대한 for문
		while ((v[en] - v[st] < m) && (en < n - 1)) {
			en++;
		}
		if (v[en] - v[st] >= m && ans > v[en] - v[st]) ans = v[en] - v[st];
		if (ans == m) return;
	}
}


int main()
{
	input();
	solve();
	output();
	return 0;
}