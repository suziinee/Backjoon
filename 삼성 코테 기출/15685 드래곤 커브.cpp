#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int N;
int map[101][101];

struct DRAW {
	int y;
	int x;
	int d;
	int g;
};
vector<DRAW> draw;


void input()
{
	cin >> N;
	int y, x, d, g;
	for (int i = 0; i < N; i++) {
		cin >> x >> y >> d >> g;
		draw.push_back({ y, x, d, g });
	}
}

void draw_curve(DRAW& order)
{
	static int lut[4] = { 1, 2, 3, 0 };
	static int dx[] = { 1, 0, -1, 0 };
	static int dy[] = { 0, -1, 0, 1 };

	//g세대만큼 그릴 방향 테이블 구하기
	int dir[1024] = { 0 };
	dir[0] = order.d;
	for (int i = 1; i <= order.g; i++) { //1세대부터 g세대까지
		int idx = pow(2, i - 1);
		for (int rev = pow(2, i - 1) - 1; rev >= 0; rev--) {
			dir[idx] = lut[dir[rev]];
			idx++;
		}
	}

	//시작점부터 그리기
	int x = order.x;
	int y = order.y;
	map[y][x] = 1;
	for (int i = 0; i < pow(2, order.g); i++) {
		int nx = x + dx[dir[i]];
		int ny = y + dy[dir[i]];
		map[ny][nx] = 1;
		x = nx; y = ny;
	}
}

void solve()
{
	for (DRAW order : draw) {
		draw_curve(order);
	}

	//사각형의 좌표 (y, x)
	int cnt = 0;
	for (int y = 0; y < 100; y++) { 
		for (int x = 0; x < 100; x++) {
			//4개는 map의 좌표
			if (map[y][x] && map[y + 1][x] && map[y][x + 1] && map[y + 1][x + 1]) cnt++;
		}
	}
	cout << cnt;
}


int main()
{
	input();
	solve();
	return 0;
}