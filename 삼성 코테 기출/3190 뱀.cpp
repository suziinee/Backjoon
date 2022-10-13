#include <iostream>
#include <deque>
#include <queue>
using namespace std;

#define MAXN 100
#define MAXL 100
int N, K, L;
int map[MAXN][MAXN]; //빈칸 0, 사과 1, 뱀 2

struct AXIS { int y, x; };
deque<AXIS> snake;
int dir = 1; //뱀은 처음에 오른쪽

struct ORDER { int t, d; }; //1은 왼쪽, 2는 오른쪽
queue<ORDER> oq;

#define BLANK (0)
#define APPLE (1)
#define SNAKE (2)

void input()
{
	cin >> N >> K;
	int y, x;
	for (int i = 0; i < K; i++) {
		cin >> y >> x;
		--y; --x;
		map[y][x] = APPLE;
	}
	cin >> L;
	int t; char c;
	for (int i = 0; i < L; i++) {
		cin >> t >> c;
		if (c == 'L') oq.push({ t, 1 });
		else oq.push({ t, 2 });
	}
}

void solve()
{
	static int dx[] = { 0, 1, 0, -1 };
	static int dy[] = { -1, 0, 1, 0 };

	snake.push_back({ 0, 0 });
	map[0][0] = SNAKE;
	int time = 0;
	while (true) {

		//oq가 비어있지 않다면 방향 전환
		if (!oq.empty() && oq.front().t == time) {
			if (oq.front().d == 1) { //왼쪽 회전
				dir = (dir + 3) % 4;
			}
			else { //오른쪽 회전
				dir = (dir + 1) % 4;
			}
			oq.pop();
		}

		//뱀 머리 늘이기
		int nx = snake.front().x + dx[dir];
		int ny = snake.front().y + dy[dir];
		if (nx < 0 || ny < 0 || nx >= N || ny >= N) { ++time; break; }
		if (map[ny][nx] == SNAKE) { ++time; break; }
		snake.push_front({ ny, nx });

		//사과 있으면 먹고 아니면 그대로
		if (map[ny][nx] == APPLE) {
			map[ny][nx] = SNAKE;
		}
		else if (map[ny][nx] == BLANK) {
			map[ny][nx] = SNAKE;
			int ty = snake.back().y;
			int tx = snake.back().x;
			map[ty][tx] = BLANK;
			snake.pop_back();
		}

		//시간 증가
		++time;
	}
	cout << time;
}


int main()
{
	input();
	solve();
	return 0;
}