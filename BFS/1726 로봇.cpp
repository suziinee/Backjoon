#include <iostream>
#include <queue>
using namespace std;

#define MAX 100
int M, N;
int map[MAX + 5][MAX + 5];
bool chk[4][MAX + 5][MAX + 5];
struct AXIS { int x; int y; int dir; int order; };
AXIS st, en;
queue<AXIS> q;

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };


void input()
{
	cin >> M >> N;
	for (int y = 1; y <= M; y++) {
		for (int x = 1; x <= N; x++) {
			cin >> map[y][x];
		}
	}
	cin >> st.y >> st.x >> st.dir >> en.y >> en.x >> en.dir;

	int change_dir[5] = { 0, 1, 3, 2, 0 };
	st.dir = change_dir[st.dir];
	en.dir = change_dir[en.dir];
}

int bfs()
{
	//초기상태
	q.push(st);
	st.order = 0;
	chk[st.dir][st.y][st.x] = true;
	//초기상태 종료조건
	if (st.y == en.y&&st.x == en.x&&st.dir == en.dir) return st.order;

	while (!q.empty()) {
		AXIS n = q.front(); q.pop();

		AXIS nn = n;
		nn.order = n.order + 1;

		//앞으로 1칸~3칸
		for (int i = 1; i <= 3; i++) {
			nn.x = n.x + i * dx[nn.dir];
			nn.y = n.y + i * dy[nn.dir];

			//좌표유효셩 -> break
			if (nn.x<1 || nn.y<1 || nn.x>N || nn.y>M) break;
			if (map[nn.y][nn.x] == 1) break;

			//방문
			if (chk[nn.dir][nn.y][nn.x] == true) continue;

			//push
			chk[nn.dir][nn.y][nn.x] = true;
			q.push(nn);

			//종료조건
			if (nn.x == en.x&& nn.y == en.y&&nn.dir == en.dir) return nn.order;
		}

		nn = n;
		nn.order = n.order + 1;

		//왼쪽 오른쪽 회전
		for (int i = 0; i < 2; i++) {
			if (i == 0) nn.dir = (n.dir + 1) % 4; //오른쪽 회전
			else nn.dir = (n.dir == 0) ? 3 : n.dir - 1; //왼쪽 회전

			//방문 
			if (chk[nn.dir][nn.y][nn.x] == true) continue;

			//push
			chk[nn.dir][nn.y][nn.x] = true;
			q.push(nn);

			// 종료조건
			if (nn.x == en.x&& nn.y == en.y&&nn.dir == en.dir) return nn.order;
		}
	}
}


void solve()
{
	int ans = bfs();
	cout << ans;
}


int main(void)
{
	input();
	solve();
	return 0;
}