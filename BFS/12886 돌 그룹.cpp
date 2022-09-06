#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define MAX 500
int a, b, c;
queue<vector<int>> q;
int chk1[MAX * 3 + 1];
int chk2[MAX * 3 + 1];


void input()
{
	cin >> a >> b >> c;
}

int bfs()
{
	if ((a + b + c) % 3 != 0) return 0;

	int comb[3][3] = { {0, 1, 2}, {0, 2, 1}, {1, 2, 0} };

	//넣기 전 sort
	vector<int> st = { a, b, c };
	sort(st.begin(), st.end());
	q.push(st);
	chk1[st[0]] = 1;
	chk2[st[1]] = 1;

	while (true) {
		vector<int> data = q.front(); q.pop();
		if (data[0] == data[1] && data[1] == data[2]) return 1; //종료조건

		for (int i = 0; i < 3; i++) {
			int x = data[comb[i][0]];
			int y = data[comb[i][1]];
			int z = data[comb[i][2]];

			if (x == y) continue;
			if (chk1[x] == 1 && chk2[y] == 1) continue;

			//넣기 전 sort
			vector<int> ndata = { x + x, y - x, z };
			sort(ndata.begin(), ndata.end());
			q.push(ndata);
			chk1[ndata[0]] = 1; chk2[ndata[1]] = 1;
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