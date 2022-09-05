#include <iostream>
#include <queue>
using namespace std;

#define MAX 1000
int n, m;
struct POS { int x; int y; int flag; int ans; };
char map[MAX + 5][MAX + 5];


void input()
{
	cin >> n >> m;
	for (int y = 1; y <= n; y++) {
		cin >> &map[y][1];
	}
}

int bfs() 
{
	queue<POS> q;
	bool chk[MAX + 5][MAX + 5][2] = { false };

	q.push({ 1, 1, 1, 1 }); //flag 초기값은 1
	chk[1][1][1] = true;

	const int dx[] = { 0, 1, 0, -1 };
	const int dy[] = { -1, 0, 1, 0 };

	while (!q.empty()) {
		POS tmp = q.front(); q.pop();
		if (tmp.x == m && tmp.y == n) return tmp.ans; //종료조건

		for (int dir = 0; dir < 4; dir++) {
			POS next;
			next.ans = tmp.ans + 1; next.flag = tmp.flag;
			next.x = tmp.x + dx[dir];
			next.y = tmp.y + dy[dir];
			
			if (next.x<1 || next.y<1 || next.x>m || next.y>n) continue;
			if (chk[next.y][next.x][next.flag] == true) continue;

			//방문하지 않은 곳이라면
			//1. 벽이 아닐 경우
			if (map[next.y][next.x] == '0') { //큐에 넣어주고 방문처리
				q.push(next);
				chk[next.y][next.x][next.flag] = true;
			}
			//2. 벽일 경우
			else if (map[next.y][next.x] == '1') {
				if (next.flag == 1) { //부술 기회가 있음 -> 부수고 큐에 넣고 방문처리
					next.flag = 0;
					q.push(next);
					chk[next.y][next.x][next.flag] = true;
				}
				else { //더 이상 부술 수 없음
					continue;
				}
			}
		}
	}

	return -1;
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


int main()
{
	input();
	int ans = solve();
	output(ans);
	return 0;
}