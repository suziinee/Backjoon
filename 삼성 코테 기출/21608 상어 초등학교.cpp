#include <iostream>
using namespace std;

#define MAXN 20
int N;
int map[MAXN][MAXN]; //앉은 학생의 번호 기록

struct STUDENT {
	int n;
	int y, x;
	int pri[4];
};
STUDENT stu[MAXN * MAXN]; //입력 순서대로

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };


void input()
{
	cin >> N;
	for (int i = 0; i < N * N; i++) {
		cin >> stu[i].n >> stu[i].pri[0] >> stu[i].pri[1] >> stu[i].pri[2] >> stu[i].pri[3];
	}
}

int get_point(int y, int x, int i) //(y, x)에 stu[i].n번 학생이 앉았을 때 가산점
{
	int ret = 0;
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
		if (map[ny][nx] == 0) {
			ret += 1;
		}
		else {
			for (int f : stu[i].pri) {
				if (map[ny][nx] == f) {
					ret += 10;
					break;
				}
			}
		}
	}
	return ret;
}

void assign(int y, int x, int i) //(y, x)에 stu[i].n번 학생 앉히기
{
	map[y][x] = stu[i].n;
	stu[i].y = y; stu[i].x = x;
}

int get_score(int i) //stu[i].n번 학생의 만족도
{
	int ret = 0;
	for (int d = 0; d < 4; d++) {
		int nx = stu[i].x + dx[d];
		int ny = stu[i].y + dy[d];
		if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
		for (int f : stu[i].pri) {
			if (map[ny][nx] == f) {
				if (ret == 0) ++ret;
				else ret *= 10;
			}
		}
	}
	return ret;
}

void solve()
{
	for (int i = 0; i < N * N; i++) {
		//stu[i].n번 학생이 앉을 자리 찾기
		int candy, candx, point = -1;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				if (map[y][x]) continue;
				int ret = get_point(y, x, i);
				if (ret > point) {
					point = ret;
					candy = y; candx = x;
				}
			}
		}
		assign(candy, candx, i);
	}

	int ans = 0;
	for (int i = 0; i < N * N; i++) {
		ans += get_score(i);
	}
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}