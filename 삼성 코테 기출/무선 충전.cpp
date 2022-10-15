#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int M, A, ans;
int a[100 + 1]; //a의 이동방향
int b[100 + 1]; //b의 이동방향

struct BC {
	int n, y, x, c, p;
};
BC bc[8];
vector<BC> map[10 + 1][10 + 1]; 
bool compare(const BC& b1, const BC& b2) {
	return b1.p > b2.p;
}


void init_bc(int n) //n번 bc에 대해서 map에 충전 범위 기록
{
	int cy = bc[n].y;
	int cx = bc[n].x;
	int scope = bc[n].c;
	for (int y = cy - scope; y <= cy + scope; y++) {
		for (int x = cx - scope; x <= cx + scope; x++) {
			if (x < 1 || y < 1 || x>10 || y>10) continue;
			if (abs(x - cx) + abs(y - cy) > scope) continue;
			map[y][x].push_back(bc[n]);
		}
	}
}

void dfs(int ay, int ax, int by, int bx, int time, int sum)
{
	static int dx[] = { 0, 0, 1, 0, -1 };
	static int dy[] = { 0, -1, 0, 1, 0 };

	if (time == M + 1) {
		if (ans < sum) ans = sum;
		return;
	}
	
	int nay = ay + dy[a[time]];
	int nax = ax + dx[a[time]];
	int nby = by + dy[b[time]];
	int nbx = bx + dx[b[time]];

	if (map[nay][nax].empty() && map[nby][nbx].empty()) {
		dfs(nay, nax, nby, nbx, time + 1, sum);
	}
	else if (!map[nay][nax].empty() && map[nby][nbx].empty()) {
		dfs(nay, nax, nby, nbx, time + 1, sum + map[nay][nax][0].p);
	}
	else if (map[nay][nax].empty() && !map[nby][nbx].empty()) {
		dfs(nay, nax, nby, nbx, time + 1, sum + map[nby][nbx][0].p);
	}
	else {
		int max = 0;
		for (const BC& a : map[nay][nax]) {
			for (const BC& b : map[nby][nbx]) {
				int choice = 0;
				if (a.n == b.n) {
					choice = a.p;
				}
				else {
					choice = a.p + b.p;
				}
				if (max < choice) max = choice;
			}
		}
		dfs(nay, nax, nby, nbx, time + 1, sum + max);
	}
}

void input()
{
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> M >> A;
		
		ans = 0;
		fill(a, a + 101, 0);
		fill(b, b + 101, 0);
		for (int i = 0; i < 8; i++) {
			bc[i] = {};
		}
		for (int y = 1; y <= 10; y++) {
			for (int x = 1; x <= 10; x++) {
				map[y][x].clear();
			}
		}

		for (int i = 1; i <= M; i++) {
			cin >> a[i];
		}
		for (int i = 1; i <= M; i++) {
			cin >> b[i];
		}
		for (int i = 0; i < A; i++) {
			cin >> bc[i].x >> bc[i].y >> bc[i].c >> bc[i].p;
			bc[i].n = i;
		}

		for (int i = 0; i < A; i++) {
			init_bc(i);
		}
		for (int y = 1; y <= 10; y++) {
			for (int x = 1; x <= 10; x++) {
				if (map[y][x].size() >= 2) sort(map[y][x].begin(), map[y][x].end(), compare);
			}
		}
		dfs(1, 1, 10, 10, 0, 0);
		cout << "#" << t << " " << ans << "\n";
	}
}


int main()
{
	input();
	return 0;
}