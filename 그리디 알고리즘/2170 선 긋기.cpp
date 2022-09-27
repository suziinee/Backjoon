#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;

struct LINE {
	int s; 
	int e;
	bool operator<(const LINE& l) const { return s < l.s; }
};
vector<LINE> line;


void input()
{
	cin >> N;
	int s, e;
	for (int i = 0; i < N; i++) {
		cin >> s >> e;
		line.push_back({ s, e });
	}
}

void solve()
{
	sort(line.begin(), line.end());

	int st = line[0].s;
	int en = line[0].e;
	int ans = en - st;

	for (int i = 1; i < N; i++) {
		if (line[i].s <= en && line[i].e > en) {
			ans += line[i].e - en;
			en = line[i].e;
		}
		else if (line[i].s > en) {
			ans += line[i].e - line[i].s;
			st = line[i].s;
			en = line[i].e;
		}
	}

	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}