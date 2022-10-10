#include <iostream>
using namespace std;

#define MAX 20
int N, M, K;
int map[MAX][MAX];
int dice[7] = { 0, 6, 2, 3, 4, 5, 1 };

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };


void input()
{
	cin >> N >> M >> K;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> map[y][x];
		}
	}
}

void move_dice(int dir)
{
	int ndice[7];
	switch (dir) {
	case 0: {
		ndice[1] = dice[2];
		ndice[2] = dice[6];
		ndice[3] = dice[3];
		ndice[4] = dice[4];
		ndice[5] = dice[1];
		ndice[6] = dice[5];
		break;
	}
	case 1: {
		ndice[1] = dice[3];
		ndice[2] = dice[2];
		ndice[3] = dice[6];
		ndice[4] = dice[1];
		ndice[5] = dice[5];
		ndice[6] = dice[4];
		break;
	}
	case 2: {
		ndice[1] = dice[5];
		ndice[2] = dice[1];
		ndice[3] = dice[3];
		ndice[4] = dice[4];
		ndice[5] = dice[6];
		ndice[6] = dice[2];
		break;
	}
	case 3: {
		ndice[1] = dice[4];
		ndice[2] = dice[2];
		ndice[3] = dice[1];
		ndice[4] = dice[6];
		ndice[5] = dice[5];
		ndice[6] = dice[3];
		break;
	}
	}

	for (int i = 1; i <= 6; i++) {
		dice[i] = ndice[i];
	}
}

void dfs(int y, int x, int& cnt, int B, bool(*chk)[MAX])
{
	cnt++;
	chk[y][x] = true;
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (nx < 0 || ny < 0 || nx >= M || ny >= N) continue;
		if (map[ny][nx] != B || chk[ny][nx]) continue;
		dfs(ny, nx, cnt, B, chk);
	}
}

int get_score(int y, int x)
{
	int B = map[y][x];

	int cnt = 0;
	bool chk[MAX][MAX] = { false, };
	dfs(y, x, cnt, B, chk);
	int C = cnt;

	return B * C;
}

void solve()
{
	static int rev_dir[] = { 2, 3, 0, 1 };

	int x = 0;
	int y = 0;
	int dir = 1;
	int ans = 0;

	for (int i = 0; i < K; i++) {
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		if (nx < 0 || ny < 0 || nx >= M || ny >= N) { //방향을 반대로 해서 한칸 굴러가기
			dir = rev_dir[dir];
			nx = x + dx[dir];
			ny = y + dy[dir];
		}
		move_dice(dir);

		int A = dice[1]; //1이 언제나 바닥면
		int B = map[ny][nx];
		if (A > B) {
			dir = (dir + 1) % 4;
		}
		else if (A < B) {
			dir = (dir + 3) % 4;
		}
		ans += get_score(ny, nx);
		x = nx;
		y = ny;
	}
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}