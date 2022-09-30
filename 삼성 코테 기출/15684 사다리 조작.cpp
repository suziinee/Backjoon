#include <iostream>
using namespace std;

#define MAXN 10
#define MAXH 30
int N, M, H;
int map[MAXH + 1][MAXN + 1];
int ans = 0x7fffffff;


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

void dfs(int cnt)
{
	if (cnt >= ans) return; //가지치기
	if (cnt > 3) return; //문제 조건
	if (ans > cnt && check()) ans = cnt; //최소값 갱신
	
	for (int y = 1; y <= H; y++) {
		for (int x = 1; x < N; x++) {
			if (map[y][x] || map[y][x - 1] || map[y][x + 1]) continue;
			map[y][x] = 1;
			dfs(cnt + 1);
			map[y][x] = 0;
		}
	}
}

void solve()
{
	dfs(0);
	if (ans == 0x7fffffff) cout << -1;
	else cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}