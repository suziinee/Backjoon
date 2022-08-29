#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
struct AXIS {
	int x; int y;
};
vector<AXIS> house;
vector<AXIS> chick;
int ans = 0x7fffffff;

void input()
{
	cin >> n;
	cin >> m;

	int tmp;
	AXIS t;
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			cin >> tmp;
			t.x = x; t.y = y;
			if (tmp == 1) house.push_back(t);
			if (tmp == 2) chick.push_back(t);
		}
	}
}

void output()
{
	cout << ans;
}

vector<AXIS> pick;
void dfs(int start)
{
	if (pick.size() == m) {
		int sum = 0;
		for (int i = 0; i < house.size(); i++) {
			int tmp = 0x7fffffff;
			for (int j = 0; j < m; j++) {
				tmp = min(abs(pick[j].x - house[i].x) + abs(pick[j].y - house[i].y), tmp);
			}
			sum += tmp;
		}

		if (sum < ans) ans = sum;
		return;
	}

	for (int i = start; i < chick.size(); i++) {
		pick.push_back(chick[i]);
		dfs(i + 1);
		pick.pop_back();
	}
}

void solve()
{
	dfs(0);
}


int main()
{
	input();
	solve();
	output();
	return 0;
}
