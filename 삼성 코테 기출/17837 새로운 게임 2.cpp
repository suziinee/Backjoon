#include <iostream>
#include <stack>
#include <queue>
using namespace std;

#define MAXN 12
#define MAXK 10
int N, K;
int map[MAXN][MAXN]; //체스판 색 저장
stack<int> board[MAXN][MAXN]; //체스판에서 움직이는 말 저장

struct MARK { int y; int x; int d; };
MARK mark[MAXK + 1]; //이동을 편리하게 시키기 위해 말 위치도 따로 관리


void input()
{
	cin >> N >> K;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
		}
	}
	int y, x, d;
	for (int i = 1; i <= K; i++) { //말 번호 1~K
		cin >> y >> x >> d;
		y--; x--; d--;
		mark[i] = { y, x, d };
		board[y][x].push(i);
	}
}

void move_to_zero(MARK& m, int k, int ny, int nx)
{
	stack<int> st;
	while (board[m.y][m.x].top() != k) {
		st.push(board[m.y][m.x].top());
		board[m.y][m.x].pop();
	}
	st.push(board[m.y][m.x].top()); //k에 대해서도 수행
	board[m.y][m.x].pop();

	while (!st.empty()) {
		board[ny][nx].push(st.top());
		mark[st.top()].y = ny;
		mark[st.top()].x = nx;
		st.pop();
	}
	m.x = nx;
	m.y = ny;
}

void move_to_one(MARK& m, int k, int ny, int nx)
{
	queue<int> q;
	while (board[m.y][m.x].top() != k) {
		q.push(board[m.y][m.x].top());
		board[m.y][m.x].pop();
	}
	q.push(board[m.y][m.x].top()); //k에 대해서도 수행
	board[m.y][m.x].pop();

	while (!q.empty()) {
		board[ny][nx].push(q.front());
		mark[q.front()].y = ny;
		mark[q.front()].x = nx;
		q.pop();
	}
	m.x = nx;
	m.y = ny;
}

void move(int k) //k번째 말 움직이기
{
	static int dx[] = { 1, -1, 0, 0 }; //right left up down
	static int dy[] = { 0, 0, -1, 1 };
	static int dir[] = { 1, 0, 3, 2 };

	MARK& m = mark[k];
	int nx = m.x + dx[m.d];
	int ny = m.y + dy[m.d];

	if (map[ny][nx] == 2 || nx < 0 || ny < 0 || nx >= N || ny >= N) {
		m.d = dir[m.d];
		nx = m.x + dx[m.d];
		ny = m.y + dy[m.d];
		if (!(map[ny][nx] == 2 || nx < 0 || ny < 0 || nx >= N || ny >= N)) {
			if (map[ny][nx] == 0) {
				move_to_zero(m, k, ny, nx);
			}
			else if (map[ny][nx] == 1) {
				move_to_one(m, k, ny, nx);
			}
		}
	}
	else if (map[ny][nx] == 1) {
		move_to_one(m, k, ny, nx);
	}
	else if (map[ny][nx] == 0) {
		move_to_zero(m, k, ny, nx);
	}
}

bool check_end()
{
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (board[y][x].size() >= 4) {
				return true;
			}
		}
	}
	return false;
}

void solve()
{
	for (int t = 1; t <= 1000; t++) {
		for (int k = 1; k <= K; k++) {
			move(k);
			if (check_end()) {
				cout << t;
				return;
			}
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