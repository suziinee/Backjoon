#include <iostream>
#include <queue>
using namespace std;

#define MAXN 50
int N;
int en_flag; int init_flag;
char map[MAXN][MAXN];

struct WOOD { //시작위치, 방향, 단위 동작 카운트
	int y; 
	int x;
	int d;
	int cnt;
};
WOOD init;
WOOD en;
queue<WOOD> q;
bool chk[MAXN][MAXN][2]; //시작위치[y][x], 방향


void input()
{
	cin >> N;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];

			if (map[y][x] == 'B' && !init_flag) {
				init.y = y; init.x = x;
				init_flag = 1;
			}
			else if (map[y][x] == 'B' && init_flag) {
				if (y == init.y) init.d = 0;
				else if (x == init.x) init.d = 1;
			}

			if (map[y][x] == 'E' && !en_flag) {
				en.y = y; en.x = x;
				en_flag = 1;
			}
			else if (map[y][x] == 'E' && en_flag) {
				if (y == en.y) en.d = 0;
				else if (x == en.x) en.d = 1;
			}
		}
	}
}


bool move(const WOOD& w, char c)
{
	switch (c) {
	case 'U': {
		if (w.y - 1 < 0) return false;
		if (w.d == 0) {
			for (int x = w.x; x < w.x + 3; x++) {
				if (map[w.y - 1][x] == '1') return false;
			}
		}
		else {
			for (int y = w.y - 1; y < w.y - 1 + 3; y++) {
				if (map[y][w.x] == '1') return false;
			}
		}
		return true;
		break;
	}
	case 'D': {
		if (w.d == 0) {
			if (w.y + 1 >= N) return false;
			for (int x = w.x; x < w.x + 3; x++) {
				if (map[w.y + 1][x] == '1') return false;
			}
		}
		else {
			if (w.y + 2 + 1 >= N) return false;
			for (int y = w.y + 1; y < w.y + 1 + 3; y++) {
				if (map[y][w.x] == '1') return false;
			}
		}
		return true;
		break;
	}
	case 'L': {
		if (w.x - 1 < 0) return false;
		if (w.d == 0) {
			for (int x = w.x - 1; x < w.x - 1 + 3; x++) {
				if (map[w.y][x] == '1') return false;
			}
		}
		else {
			for (int y = w.y; y < w.y + 3; y++) {
				if (map[y][w.x - 1] == '1') return false;
			}
		}
		return true;
		break;
	}
	case 'R': {
		if (w.d == 0) {
			if (w.x + 2 + 1 >= N) return false;
			for (int x = w.x + 1; x < w.x + 1 + 3; x++) {
				if (map[w.y][x] == '1') return false;
			}
		}
		else {
			if (w.x + 1 >= N) return false;
			for (int y = w.y; y < w.y + 3; y++) {
				if (map[y][w.x + 1] == '1') return false;
			}
		}
		return true;
		break;
	}
	case 'T': {
		if (w.d == 0) {
			if (w.y + 1 >= N || w.y - 1 < 0) return false;
			for (int x = w.x; x < w.x + 3; x++) {
				if (map[w.y - 1][x] == '1') return false;
				if (map[w.y + 1][x] == '1') return false;
			}
		}
		else {
			if (w.x + 1 >= N || w.x - 1 < 0) return false;
			for (int y = w.y; y < w.y + 3; y++) {
				if (map[y][w.x - 1] == '1') return false;
				if (map[y][w.x + 1] == '1') return false;
			}
		}
		return true;
		break;
	}
	}
}


int bfs()
{
	q.push(init);
	chk[init.y][init.x][init.d] = true;

	while (!q.empty()) {
		WOOD cur = q.front(); q.pop();

		if (move(cur, 'U')) { //상
			WOOD next;
			next.y = cur.y - 1;
			next.x = cur.x;
			next.d = cur.d;
			next.cnt = cur.cnt + 1;
			if (chk[next.y][next.x][next.d] == false) {
				if (next.y == en.y && next.x == en.x && next.d == en.d) return next.cnt;
				chk[next.y][next.x][next.d] = true;
				q.push(next);
			}
		}
		if (move(cur, 'D')) { //하
			WOOD next;
			next.y = cur.y + 1;
			next.x = cur.x;
			next.d = cur.d;
			next.cnt = cur.cnt + 1;
			if (chk[next.y][next.x][next.d] == false) {
				if (next.y == en.y && next.x == en.x && next.d == en.d) return next.cnt;
				chk[next.y][next.x][next.d] = true;
				q.push(next);
			}
		}
		if (move(cur, 'L')) { //좌
			WOOD next;
			next.y = cur.y;
			next.x = cur.x - 1;
			next.d = cur.d;
			next.cnt = cur.cnt + 1;
			if (chk[next.y][next.x][next.d] == false) {
				if (next.y == en.y && next.x == en.x && next.d == en.d) return next.cnt;
				chk[next.y][next.x][next.d] = true;
				q.push(next);
			}
		}
		if (move(cur, 'R')) { //우
			WOOD next;
			next.y = cur.y;
			next.x = cur.x + 1;
			next.d = cur.d;
			next.cnt = cur.cnt + 1;
			if (chk[next.y][next.x][next.d] == false) {
				if (next.y == en.y && next.x == en.x && next.d == en.d) return next.cnt;
				chk[next.y][next.x][next.d] = true;
				q.push(next);
			}
		}
		if (move(cur, 'T')) { //회전
			WOOD next;
			if (cur.d == 0) {
				next.x = cur.x + 1;
				next.y = cur.y - 1;
				next.d = 1;
			}
			else {
				next.x = cur.x - 1;
				next.y = cur.y + 1;
				next.d = 0;
			}
			next.cnt = cur.cnt + 1;
			if (chk[next.y][next.x][next.d] == false) {
				if (next.y == en.y && next.x == en.x && next.d == en.d) return next.cnt;
				chk[next.y][next.x][next.d] = true;
				q.push(next);
			}
		}
	}
	return 0;
}


void solve()
{
	cout << bfs();
}


int main()
{
	input();
	solve();
	return 0;
}