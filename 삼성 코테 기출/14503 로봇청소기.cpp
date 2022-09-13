#include <iostream>
using namespace std;

#define MAX 50
int N, M; //세로, 가로
int map[MAX + 2][MAX + 2];
int ans;

struct STATUS { int r; int c; int d; };
STATUS st;

const int dc[] = { 0, 1, 0, -1 }; //전진
const int dr[] = { -1, 0, 1, 0 };
const int ddc[] = { 0, -1, 0, 1 }; //후진
const int ddr[] = { 1, 0, -1, 0 };


void input()
{
	cin >> N >> M;
	cin >> st.r >> st.c >> st.d;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			cin >> map[r][c];
		}
	}
}

int solve()
{
	//초기값
	int r = st.r; int c = st.c; int d = st.d;
	int ans = 0;

	while (true) {

		int flag = 0;
		bool clean = false;

		//0. 현재 장소를 청소할 수 있다면 한다
		if (map[r][c] == 0) {
			map[r][c] = 2;
			ans++;
		}

		//1. 현재 방향부터 왼쪽으로 탐색 진행
		for (int i = 0; i < 4; i++) {
			//1-0. 왼쪽 방향
			d = (d + 3) % 4;
			int nc = c + dc[d];
			int nr = r + dr[d];

			//1-1. 좌표 유효성 및 청소 유효성
			if (nc < 0 || nr < 0 || nc >= M || nr >= N) { flag++; continue; }
			if (map[nr][nc] == 1 || map[nr][nc] == 2) { flag++; continue; }

			//1-2. 청소 가능하다면 청소하고 아래 전부 무시
			r = nr; c = nc;
			clean = true;
			break;
		}

		//2. 4방향 모두 불가하고 한번도 청소되지 않았다면 (nr, nc가 0일리가 없음)
		if (clean == false && flag == 4) {
			int nc = c + ddc[d];
			int nr = r + ddr[d];

			//2-1. 뒤가 벽이면 종료
			if (map[nr][nc] == 1 || nc < 0 || nr < 0 || nc >= M || nr >= N) return ans;

			//2-2. 아니면 한 칸 후진
			r = nr; c = nc;
		}
	}
}


int main(void)
{
	input();
	int ans = solve();
	cout << ans;
	return 0;
}