#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int a, b, c;


void input()
{
	cin >> a >> b >> c;
}

int bfs()
{
	if ((a + b + c) % 3 != 0) return 0;

	int comb[3][3] = { {0, 1, 2}, {0, 2, 1}, {1, 2, 0} };

	queue<vector<int>> q;
	q.push({ a, b, c });

	while (true) {
		vector<int> data = q.front(); q.pop();
		sort(data.begin(), data.end());
		if (data[0] == data[1] && data[1] == data[2]) return 1; //종료조건

		for (int i = 0; i < 3; i++) {
			int x = data[comb[i][0]];
			int y = data[comb[i][1]];
			int z = data[comb[i][2]];

			if (x == y) continue;
			if (x > y) swap(x, y);

			q.push({ x + x, y - x, z });
		}
	}
}

int solve()
{
	int ans = bfs();
	return ans;
}

void output(const int& ans)
{
	cout << ans;
}


int main(void)
{
	input();
	int ans = solve();
	output(ans);
	return 0;
}