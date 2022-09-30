#include <iostream>
using namespace std;

#define MAXN 10
#define MAXH 30
int N, M, H;
int map[MAXH + 1][MAXN + 1];


void input()
{
	cin >> N >> M >> H;
	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		map[a][b] = 1;
	}
}

bool check()
{
	for (int i = 1; i <= N; i++) { //사다리가 아닌 세로선
		int x = i;
		int y = 1;

		while (y < H + 1) { //양옆에 있는 사다리 확인
			if (map[y][x - 1]) x--; //왼쪽 이동
			else if (map[y][x]) x++; //오른쪽 이동
			y++; //아래로 내려가는건 default
		}

		if (x != i) return false;
	}
	return true;
}

bool dfs(int n, int cnt)
{
	if (n == cnt) {
		if (check()) return true;
		return false;
	}
	
	for (int y = 1; y <= H; y++) {
		for (int x = 1; x < N; x++) {
			if (map[y][x] || map[y][x - 1] || map[y][x + 1]) continue;
			map[y][x] = 1;
			if (dfs(n + 1, cnt)) return true;
			map[y][x] = 0;
		}
	}
	return false;
}

void solve()
{
	for (int i = 0; i <= 3; i++) {
		if (dfs(0, i)) {
			cout << i;
			return;
		}
	}
	cout << -1;
}


int main()
{
	input();
	solve();
	return 0;
}