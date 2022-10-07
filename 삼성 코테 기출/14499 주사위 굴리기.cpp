#include <iostream>
#include <algorithm>
using namespace std;

#define MAX 20
int N, M, sy, sx, K;
int dice[4][3];
int map[MAX][MAX];
int order[1000];


void input()
{
	cin >> N >> M >> sy >> sx >> K;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> map[y][x];
		}
	}
	for (int i = 0; i < K; i++) {
		cin >> order[i];
		order[i]--;
	}
}

void change_map(int d)
{
	int new_dice[4][3];

	switch (d) {
	case 0: {
		new_dice[1][1] = dice[1][2];
		new_dice[0][1] = dice[0][1];
		new_dice[1][0] = dice[1][1];
		new_dice[1][2] = dice[3][1];
		new_dice[2][1] = dice[2][1];
		new_dice[3][1] = dice[1][0];
		break;
	}
	case 1: {
		new_dice[1][1] = dice[1][0];
		new_dice[0][1] = dice[0][1];
		new_dice[1][0] = dice[3][1];
		new_dice[1][2] = dice[1][1];
		new_dice[2][1] = dice[2][1];
		new_dice[3][1] = dice[1][2];
		break;
	}
	case 2: {
		new_dice[1][1] = dice[0][1];
		new_dice[0][1] = dice[3][1];
		new_dice[1][0] = dice[1][0];
		new_dice[1][2] = dice[1][2];
		new_dice[2][1] = dice[1][1];
		new_dice[3][1] = dice[2][1];
		break;
	}
	case 3: {
		new_dice[1][1] = dice[2][1];
		new_dice[0][1] = dice[1][1];
		new_dice[1][0] = dice[1][0];
		new_dice[1][2] = dice[1][2];
		new_dice[2][1] = dice[3][1];
		new_dice[3][1] = dice[0][1];
		break;
	}
	}

	copy(&new_dice[0][0], &new_dice[3][3], &dice[0][0]);
}

void solve()
{
	const int dx[] = { 1, -1, 0, 0 };
	const int dy[] = { 0, 0, -1, 1 };

	for (int i = 0; i < K; i++) {
		int nx = sx + dx[order[i]];
		int ny = sy + dy[order[i]];
		if (nx < 0 || ny < 0 || nx >= M || ny >= N) continue;
		change_map(order[i]);
		if (map[ny][nx] == 0) { //주사위의 바닥면을 map에 복사
			map[ny][nx] = dice[1][1];
		}
		else { //map의 숫자를 주사위의 바닥면에 복사
			dice[1][1] = map[ny][nx];
			map[ny][nx] = 0;
		}
		sy = ny;
		sx = nx;
		cout << dice[3][1] << "\n";
	}
}


int main()
{
	input();
	solve();
	return 0;
}