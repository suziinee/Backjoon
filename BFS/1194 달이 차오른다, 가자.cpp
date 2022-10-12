#include <iostream>
#include <queue>
using namespace std;

#define MAXN 50
int N, M;
char map[MAXN][MAXN];
int sy, sx;
int key_bit[6] = {1, 2, 4, 8, 16, 32}; //a, b, c, d, e, f

struct STATUS {
	int y, x;
	int move; //이동 횟수
	int key_num; 
	bool key[6] = { false, };
};
queue<STATUS> q;
bool chk[MAXN][MAXN][64 + 1];


void input()
{
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> map[y][x];
			if (map[y][x] == '0') {
				sy = y; sx = x;
				map[y][x] = '.';
			}
		}
	}
}

int bfs()
{
	static int dx[] = { 0, 1, 0, -1 };
	static int dy[] = { -1, 0, 1, 0 };

	STATUS init;
	init.y = sy; init.x = sx; init.move = 0; 
	q.push(init);
	chk[sy][sx][0] = true;

	while (!q.empty()) {
		STATUS cur = q.front(); q.pop();
		for (int d = 0; d < 4; d++) {
			STATUS next = cur; //key를 위해 cur 일단 복사
			next.x = cur.x + dx[d];
			next.y = cur.y + dy[d];
			next.move = cur.move + 1;
			if (next.x < 0 || next.y < 0 || next.x >= M || next.y >= N) continue;
			if (map[next.y][next.x] == '#') continue;
			
			char ch = map[next.y][next.x];
			if (ch >= 'a' && ch <= 'z') { //열쇠 
				if (next.key[ch - 'a'] == false) {
					next.key[ch - 'a'] = true;
					next.key_num += key_bit[ch - 'a'];
				}
				if (chk[next.y][next.x][next.key_num]) continue;
				chk[next.y][next.x][next.key_num] = true;
				q.push(next);
			}
			else if (ch >= 'A' && ch <= 'Z') { //문 
				char k = ch + ('a' - 'A');
				if (!next.key[k - 'a'] || chk[next.y][next.x][next.key_num]) continue;
				chk[next.y][next.x][next.key_num] = true;
				q.push(next);
			}
			else if (ch == '.') { //빈칸
				if (chk[next.y][next.x][next.key_num]) continue;
				chk[next.y][next.x][next.key_num] = true;
				q.push(next);
			}
			else if (ch == '1') { //출구 
				return next.move;
			}
		}
	}
	return -1;
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