#include <iostream>
#include <queue>
using namespace std;

#define MAXRC 50
int R, C;
int cur;
char map[2][MAXRC][MAXRC]; //빈칸(.), 홍수(*), X, D 존재

struct AXIS { int r; int c; int cnt; };
AXIS S, D;
queue<AXIS> q;
const int dc[] = { 0, 1, 0, -1 };
const int dr[] = { -1, 0, 1, 0 };


void input()
{
	cin >> R >> C;

	for (int r = 0; r < R; r++) {
		for (int c = 0; c < C; c++) {
			cin >> map[cur][r][c];
			if (map[cur][r][c] == 'S') { //S는 위치만 저장하고 빈칸으로 변경
				S.r = r; S.c = c; S.cnt = 0;
				map[cur][r][c] = '.';
			}
			if (map[cur][r][c] == 'D') {
				D.r = r; D.c = c; D.cnt = 0;
			}
		}
	}
}

void flood()
{
	int next = (cur + 1) % 2;
	//next에 cur를 모두 복사해주기
	for (int r = 0; r < R; r++) {
		for (int c = 0; c < C; c++) {
			map[next][r][c] = map[cur][r][c];
		}
	}

	for (int r = 0; r < R; r++) {
		for (int c = 0; c < C; c++) {
			if (map[cur][r][c] != '*') continue;
			for (int d = 0; d < 4; d++) {
				int nc = c + dc[d];
				int nr = r + dr[d];
				if (nc < 0 || nr < 0 || nc >= C || nr >= R) continue;
				if (map[cur][nr][nc] == 'X' || map[cur][nr][nc] == 'D') continue;
				map[next][nr][nc] = '*';
			}
		}
	}

	cur = next;
}

int bfs()
{
	q = {};
	bool chk[MAXRC][MAXRC] = { false }; //갔던 곳인지 체크

	q.push(S);
	chk[S.r][S.c] = true;
	int bef_cnt = -1;

	while (!q.empty()) {
		AXIS data = q.front(); q.pop();
		if (data.cnt == bef_cnt + 1) {
			//새로운 움직임이 시작되었으므로 flood 진행
			flood();
			bef_cnt = data.cnt;
		}

		for (int d = 0; d < 4; d++) {
			int nc = data.c + dc[d];
			int nr = data.r + dr[d];
			if (nc < 0 || nr < 0 || nc >= C || nr >= R) continue;
			if (map[cur][nr][nc] == 'X' || map[cur][nr][nc] == '*') continue;
			if (chk[nr][nc]) continue;

			if (nr == D.r && nc == D.c) return data.cnt + 1;
			chk[nr][nc] = true;
			q.push({ nr, nc, data.cnt + 1 });
		}
	}
	return -1;
}

void solve()
{
	int ret = bfs();
	if (ret == -1) cout << "KAKTUS\n";
	else cout << ret << "\n";
}


int main()
{
	input();
	solve();
	return 0;
}