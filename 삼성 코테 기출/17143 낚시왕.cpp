#include <iostream>
#include <unordered_map>
using namespace std;

#define MAX 100
int R, C, M;
int map[MAX][MAX]; //상어 번호 기록
int ans;

struct SHARK {
	int r, c;
	int s, d;
};
unordered_map<int, SHARK> shark;

const int dr[] = { -1, 1, 0, 0 }; //up down right left
const int dc[] = { 0, 0, 1, -1 };


void input()
{
	cin >> R >> C >> M;
	int r, c, s, d, z;
	for (int i = 0; i < M; i++) {
		cin >> r >> c >> s >> d >> z;
		--r; --c; --d;
		map[r][c] = z;
		shark.insert({ z, {r, c, s, d} });
	}
}

void catch_shark(int c)
{
	for (int r = 0; r < R; r++) {
		if (map[r][c]) { //해당 상어를 잡아먹음
			ans += map[r][c];
			shark.erase(map[r][c]);
			map[r][c] = 0;
			return;
		}
	}
}

void move_shark()
{
	int back[MAX][MAX] = { 0 };

	for (int size = 10000; size >= 1; size--) {
		if (shark.find(size) == shark.end()) continue; //없거나 죽은 상어
		SHARK& cur = shark[size];
		switch (cur.d) {
		case 0: {
			if (cur.r - cur.s >= 0) {
				cur.r -= cur.s;
			}
			else {
				int tmp = cur.s - cur.r;
				int a = tmp / (R - 1); //몫
				int b = tmp % (R - 1); //나머지
				if (a % 2 && b) {
					cur.r = (R - 1) - b;
				}
				else if (a % 2 && b == 0) {
					cur.d = 1;
					cur.r = R - 1;
				}
				else if (a % 2 == 0 && b) {
					cur.d = 1;
					cur.r = 0 + b;
				}
				else if (a % 2 == 0 && b == 0) {
					cur.r = 0;
				}
			}
			break;
		}
		case 1: {
			if (cur.r + cur.s < R) {
				cur.r += cur.s;
			}
			else {
				int tmp = cur.s - (R - 1 - cur.r);
				int a = tmp / (R - 1); //몫
				int b = tmp % (R - 1); //나머지
				if (a % 2 && b) {
					cur.r = 0 + b;
				}
				else if (a % 2 && b == 0) {
					cur.d = 0;
					cur.r = 0;
				}
				else if (a % 2 == 0 && b) {
					cur.d = 0;
					cur.r = (R - 1) - b;
				}
				else if (a % 2 == 0 && b == 0) {
					cur.r = R - 1;
				}
			}
			break;
		}
		case 2: {
			if (cur.c + cur.s < C) {
				cur.c += cur.s;
			}
			else {
				int tmp = cur.s - (C - 1 - cur.c);
				int a = tmp / (C - 1); //몫
				int b = tmp % (C - 1); //나머지
				if (a % 2 && b) {
					cur.c = 0 + b;
				}
				else if (a % 2 && b == 0) {
					cur.d = 3;
					cur.c = 0;
				}
				else if (a % 2 == 0 && b) {
					cur.d = 3;
					cur.c = (C - 1) - b;
				}
				else if (a % 2 == 0 && b == 0) {
					cur.c = C - 1;
				}
			}
			break;
		}
		case 3: {
			if (cur.c - cur.s >= 0) {
				cur.c -= cur.s;
			}
			else {
				int tmp = cur.s - cur.c;
				int a = tmp / (C - 1); //몫
				int b = tmp % (C - 1); //나머지
				if (a % 2 && b) {
					cur.c = (C - 1) - b;
				}
				else if (a % 2 && b == 0) {
					cur.d = 2;
					cur.c = C - 1;
				}
				else if (a % 2 == 0 && b) {
					cur.d = 2;
					cur.c = 0 + b;
				}
				else if (a % 2 == 0 && b == 0) {
					cur.c = 0;
				}
			}
			break;
		}
		}
		//그 자리에 상어가 있는지 확인 -> 큰 사이즈부터 확인했기 때문에 상어가 있으면 못들어감 -> 죽음
		if (back[cur.r][cur.c]) {
			shark.erase(size);
		}
		else {
			back[cur.r][cur.c] = size;
		}
	}
	copy(&back[0][0], &back[MAX - 1][MAX], &map[0][0]);
}

void solve()
{
	for (int c = 0; c < C; c++) {
		catch_shark(c);
		move_shark();
	}
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}