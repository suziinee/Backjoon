#include <iostream>
#include <vector>
using namespace std;

#define MAXN 40
int N, M, K;
int map[MAXN][MAXN];

struct AXIS { int y; int x; };
struct STICKER {
	int Y; int X;
	int arr[10][10];
};
vector<STICKER> stk;


//sticker 구조체의 arr 초기화
void init_arr(STICKER& s)
{
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			s.arr[y][x] = 0;
		}
	}
}

void input()
{
	cin >> N >> M >> K;
	for (int i = 0; i < K; i++) {
		STICKER s;
		init_arr(s);

		cin >> s.Y >> s.X;
		for (int y = 0; y < s.Y; y++) {
			for (int x = 0; x < s.X; x++) {
				cin >> s.arr[y][x];
			}
		}
		stk.push_back(s);
	}
}

//(y, x)로 시작하는 곳에 s를 붙일 수 있는지 탐색
bool is_possible(const int& y, const int& x, const STICKER& s) 
{
	for (int i = 0; i < s.Y; i++) {
		for (int j = 0; j < s.X; j++) {
			if (s.arr[i][j] == 1 && map[i + y][j + x] == 1) return false;
		}
	}
	return true;
}

//s를 붙일 위치를 탐색
AXIS search(const STICKER& s) 
{
	for (int y = 0; y <= N - s.Y; y++) {
		for (int x = 0; x <= M - s.X; x++) {
			bool flag = is_possible(y, x, s);
			if (flag) return { y, x };
		}
	}
	return { -1, -1 };
}

//loc에 s를 붙여줌
void attach(const AXIS& loc, const STICKER& s) 
{
	for (int y = 0; y < s.Y; y++) {
		for (int x = 0; x < s.X; x++) {
			if (s.arr[y][x] == 1) map[y + loc.y][x + loc.x] = 1;
		}
	}
}

//시계방향으로 90도 돌려줌
STICKER rotate(STICKER& s) 
{
	STICKER ret;
	ret.Y = s.X; ret.X = s.Y; //**
	init_arr(ret);

	int nx = 0;
	for (int y = 0; y < ret.Y; y++) {
		int ny = s.Y - 1;
		for (int x = 0; x < ret.X; x++) {
			ret.arr[y][x] = s.arr[ny][nx];
			ny--;
		}
		nx++;
	}
	return ret;
}


void solve()
{
	for (STICKER s : stk) {
		AXIS loc;
		for (int d = 0; d < 4; d++) {
			if (d == 0) {
				loc = search(s);
				if (loc.x != -1) {
					attach(loc, s);
					break;
				}
			}
			else {
				s = rotate(s);
				loc = search(s);
				if (loc.x != -1) {
					attach(loc, s);
					break;
				}
			}
		}
	}

	int sum = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			if (map[y][x] == 1) sum++;
		}
	}
	cout << sum;
}


int main()
{
	input();
	solve();
	return 0;
}