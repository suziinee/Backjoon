#include <iostream>
#include <queue>
using namespace std;

#define MAXN 20
#define MAXM 400
int N, M, K; //K는 초기 연료
int moved; //이동한 게스트 수
int map[MAXN][MAXN]; //벽은 -1로 변경, 게스트 번호 1~M

struct AXIS { int y; int x; };
AXIS taxi;

struct GUEST {
	int sy; int sx;
	int ey; int ex;
};
GUEST guest[MAXM + 1];

struct STATUS {
	int y; int x; int dist;
	bool operator<(const STATUS& s) const {
		if (dist == s.dist) {
			if (y == s.y) return x > s.x;
			return y > s.y;
		}
		return dist > s.dist;
	}
};
priority_queue<STATUS> cand;
queue<STATUS> q;

const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };


void input()
{
	cin >> N >> M >> K;
	for (int y = 0; y < N; ++y) {
		for (int x = 0; x < N; ++x) {
			cin >> map[y][x];
			if (map[y][x]) map[y][x] = -1;
		}
	}

	cin >> taxi.y >> taxi.x;
	taxi.y--; taxi.x--;

	int sy, sx, ey, ex;
	for (int i = 1; i <= M; i++) {
		cin >> sy >> sx >> ey >> ex;
		sy--; sx--; ey--; ex--;
		guest[i] = { sy, sx, ey, ex };
		map[sy][sx] = i; //map에 게스트 위치 표시
	}
}

STATUS find_guest() //현재 위치에서 가장 가까운 guest 찾기
{
	cand = {};
	q = {};
	bool chk[MAXN][MAXN] = { false };

	q.push({ taxi.y, taxi.x, 0 });
	chk[taxi.y][taxi.x] = true;
	if (map[taxi.y][taxi.x] > 0) return { taxi.y, taxi.x, 0 }; //현재 위치에 게스트가 있다면 바로 리턴

	int shortest = -1; //가장 가까운 게스트의 거리
	while (!q.empty()) {
		STATUS cur = q.front(); q.pop();
		for (int d = 0; d < 4; d++) {
			int nx = cur.x + dx[d];
			int ny = cur.y + dy[d];
			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
			if (chk[ny][nx] || map[ny][nx] == -1) continue;
			
			chk[ny][nx] = true;
			if (map[ny][nx] > 0) {
				if (shortest == -1) {
					shortest = cur.dist + 1;
					cand.push({ ny, nx, cur.dist + 1 });
				}
				else if (shortest == cur.dist + 1) {
					cand.push({ ny, nx, cur.dist + 1 });
				}
				else if (shortest < cur.dist + 1) break;
			}
			q.push({ ny, nx, cur.dist + 1 });
		}
	}

	if (cand.empty()) return { -1, -1, -1 }; //손님을 태울 수 없음
	else return cand.top();
}

int bfs(int n) //taxi의 현재 위치에서 guest의 목적지까지 데려다주기
{
	q = {};
	bool chk[MAXN][MAXN] = { false };

	q.push({ taxi.y, taxi.x, 0 });
	chk[taxi.y][taxi.x] = true;

	while (!q.empty()) {
		STATUS cur = q.front(); q.pop();
		for (int d = 0; d < 4; d++) {
			int nx = cur.x + dx[d];
			int ny = cur.y + dy[d];
			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
			if (chk[ny][nx] || map[ny][nx] == -1) continue;
			
			if (ny == guest[n].ey && nx == guest[n].ex) return cur.dist + 1;
			chk[ny][nx] = true;
			q.push({ ny, nx, cur.dist + 1 });
		}
	}
	return -1; //손님을 태워다 줄 수 없음
}

bool move_guest(STATUS& s) //taxi -> guest -> 목적지 / 중간에 연료가 소모되면 false 리턴
{
	int num = map[s.y][s.x];

	//taxi -> guest
	K -= s.dist;
	if (K <= 0) return false;
	map[s.y][s.x] = 0;
	taxi.y = s.y; 
	taxi.x = s.x;

	//guest -> 목적지 (bfs)
	int ret = bfs(num);
	if (ret == -1) return false;
	taxi.y = guest[num].ey;
	taxi.x = guest[num].ex;

	K -= ret;
	if (K < 0) return false;
	K += ret * 2;
	moved++;
	return true;
}

void solve()
{
	bool update = true;
	while (moved < M && update) {
		STATUS target = find_guest();

		if (target.y == -1) { //손님을 태우러 갈 수 없음
			cout << -1; 
			return;
		}

		update = move_guest(target);
	}

	if (moved == M && K >= 0) cout << K;
	else cout << -1;
}


int main()
{
	input();
	solve();
	return 0;
}