#include <iostream>
#include <unordered_map>
using namespace std;

#define MAXN 20
int N, M, K;
int map[MAXN][MAXN][3];
int killed;

struct SHARK {
	int y, x, d;
	int dir[4][4];
};
unordered_map<int, SHARK> shark;


void input()
{
	cin >> N >> M >> K;
	int n;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> n;
			if (n) {
				map[y][x][0] = n;
				shark.insert({ n, {} });
				shark[n].y = y; 
				shark[n].x = x;
			}
		}
	}
	for (int i = 1; i <= M; i++) {
		cin >> n;
		--n; shark[i].d = n;
	}
	for (int i = 1; i <= M; i++) {
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				cin >> n;
				--n; shark[i].dir[y][x] = n;
			}
		}
	}
}

void spread() //모든 상어가 자신의 자리에서 냄새를 뿌림
{
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map[y][x][0]) { //상어가 존재
				map[y][x][1] = map[y][x][0];
				map[y][x][2] = K;
			}
		}
	}
}

void move_shark()
{
	static int dx[] = { 0, 0, -1, 1 };
	static int dy[] = { -1, 1, 0, 0 };

	for (int i = 1; i <= M; i++) {
		if (shark.find(i) == shark.end()) continue; //죽은 상어
		SHARK& tmp = shark[i];
		map[tmp.y][tmp.x][0] = 0;
		
		bool flag = false;
		for (int d = 0; d < 4; d++) { //1. 우선순위로 돌면서 아무 냄새 없는 칸 
			int nd = tmp.dir[tmp.d][d];
			int nx = tmp.x + dx[nd];
			int ny = tmp.y + dy[nd];
			if (nx < 0 || ny < 0 || nx >= N || ny >= N || map[ny][nx][1]) continue;
			if (map[ny][nx][0]) { //상어가 있음 -> 나중에 들어온 i가 숫자가 더 클 것이므로 못들어감 -> 현재 상어 죽음
				shark.erase(i);
				killed++;
				flag = true;
				break;
			}
			else {
				map[ny][nx][0] = i;
				tmp.y = ny;
				tmp.x = nx;
				tmp.d = nd;
				flag = true;
				break;
			}
		}
		if (!flag) { //2. 우선순위로 돌면서 자기 냄새가 있는 칸 찾기
			for (int d = 0; d < 4; d++) { 
				int nd = tmp.dir[tmp.d][d];
				int nx = tmp.x + dx[nd];
				int ny = tmp.y + dy[nd];
				if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
				if (map[ny][nx][1] != i) continue; //자신의 냄새가 아닌 방 제외
				if (map[ny][nx][0]) { //상어가 있음 -> 못들어감 -> 현재 상어 죽음
					shark.erase(i);
					killed++;
					break;
				}
				else { //들어감
					map[ny][nx][0] = i;
					tmp.y = ny;
					tmp.x = nx;
					tmp.d = nd;
					break;
				}
			}
		}
	}
}

void disappear()
{
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map[y][x][2] > 0) { //냄새가 있음
				map[y][x][2]--;
				if (map[y][x][2] == 0) {
					map[y][x][1] = 0; //냄새 주인 없애기
				}
			}
		}
	}
}

void solve()
{
	for (int t = 1; t <= 1000; t++) {
		spread();
		move_shark();
		disappear();

		if (killed == M - 1) {
			cout << t;
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