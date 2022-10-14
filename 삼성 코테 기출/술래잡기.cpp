#include <iostream>
#include <unordered_set>
using namespace std;

#define MAXN 99
int N, M, H, K, score;
unordered_set<int> map_hider[MAXN][MAXN]; //도망자 번호 기록 map
bool map_tree[MAXN][MAXN]; //나무 존재여부 map
bool visited[MAXN][MAXN]; //술래의 달팽이 모양 방문여부 map

struct TAG {
	int y, x, d;
	int dir; //0이면 밖으로 나가는 방향, 1이면 안으로 들어오는 방향
	int see; //술래의 시야 방향
};
struct HIDE {
	int y, x, d;
	bool catched;
};
TAG tagger;
HIDE hider[MAXN * MAXN];

const int dx[] = { 0, 1, 0, -1 }; //up right down left
const int dy[] = { -1, 0, 1, 0 };
const int sdx[4][3] = { //시야 4방향에 따른 3칸 위치
	{0, 0, 0}, {0, 1, 2}, {0, 0, 0}, {0, -1, -2}
};
const int sdy[4][3] = {
	{0, -1, -2}, {0, 0, 0}, {0, 1, 2}, {0, 0, 0}
};


void input()
{
	cin >> N >> M >> H >> K;
	int y, x, d;
	for (int i = 0; i < M; i++) {
		cin >> y >> x >> d;
		--y; --x;
		hider[i] = { y, x, d, false };
		map_hider[y][x].insert(i); 
	}
	for (int i = 0; i < H; i++) {
		cin >> y >> x;
		--y; --x;
		map_tree[y][x] = true;
	}
	tagger.x = N / 2;
	tagger.y = N / 2;
	tagger.d = 3;
	tagger.dir = 0;
	visited[N / 2][N / 2] = true;
}

void move_hider()
{
	for (int i = 0; i < M; i++) {
		int cy = hider[i].y;
		int cx = hider[i].x;
		int cd = hider[i].d;
		if (abs(cy - tagger.y) + abs(cx - tagger.x) > 3) continue;
		if (hider[i].catched) continue;
		
		int nx = cx + dx[cd];
		int ny = cy + dy[cd];
		if (nx < 0 || ny < 0 || nx >= N || ny >= N) { //방향을 틀어줌
			cd = (cd + 2) % 4;
			nx = cx + dx[cd];
			ny = cy + dy[cd];
		}
		if (ny == tagger.y && nx == tagger.x) continue; //술래가 있는 경우라면 움직이지 않음
		map_hider[ny][nx].insert(i);
		map_hider[cy][cx].erase(i);
		hider[i].x = nx;
		hider[i].y = ny;
		hider[i].d = cd;
	}
}

void move_tagger()
{
	if (tagger.dir == 0) { //밖으로 나가는 방향
		//(0, 0)일 경우
		if (tagger.y == 0 && tagger.x == 0) {
			fill(&visited[0][0], &visited[MAXN - 1][MAXN], false);
			tagger.y = 1;
			tagger.x = 0;
			tagger.d = 2;
			tagger.see = 2;
			tagger.dir = 1;
			visited[0][0] = true;
			visited[1][0] = true;
			return;
		}

		int nd = (tagger.d + 1) % 4;
		int nx = tagger.x + dx[nd];
		int ny = tagger.y + dy[nd];
		if (visited[ny][nx]) { //방향 바꾸지 말고 유지
			nd = tagger.d;
			nx = tagger.x + dx[nd];
			ny = tagger.y + dy[nd];
		}
		//술래의 다음 위치는 (ny, nx)
		tagger.x = nx;
		tagger.y = ny;
		tagger.d = nd;
		visited[ny][nx] = true;
		//술래가 바라보는 방향 정하기 -> 다음 위치가 visited라면 see=d, 아니라면 see=(d+1)%4
		if (tagger.x == 0 && tagger.y == 0) {
			tagger.see = 1;
			return;
		}
		int nnd = (nd + 1) % 4;
		int nnx = nx + dx[nnd];
		int nny = ny + dy[nnd];
		if (visited[nny][nnx]) tagger.see = tagger.d;
		else tagger.see = (tagger.d + 1) % 4;
	}
	else { //안으로 들어가는 방향
		//(N/2, N/2)일 경우
		if (tagger.x == N / 2 && tagger.y == N / 2) {
			fill(&visited[0][0], &visited[MAXN - 1][MAXN], false);
			tagger.y = N / 2 - 1;
			tagger.x = N / 2;
			tagger.d = 0;
			tagger.see = 1;
			tagger.dir = 0;
			visited[N / 2][N / 2] = true;
			visited[N / 2 - 1][N / 2] = true;
			return;
		}

		int nd = tagger.d;
		int nx = tagger.x + dx[nd];
		int ny = tagger.y + dy[nd];
		if (visited[ny][nx] || nx < 0 || ny < 0 || nx >= N || ny >= N) { //방향 바꾸기
			nd = (tagger.d + 3) % 4;
			nx = tagger.x + dx[nd];
			ny = tagger.y + dy[nd];
		}
		//술래의 다음 위치는 (ny, nx)
		tagger.x = nx;
		tagger.y = ny;
		tagger.d = nd;
		visited[ny][nx] = true;
		//술래가 바라보는 방향 정하기 -> 다음 위치가 visited라면 see=d, 아니라면 see=(d+3)%4
		if (tagger.x == N / 2 && tagger.y == N / 2) {
			tagger.see = 0;
			return;
		}
		int nnx = nx + dx[nd];
		int nny = ny + dy[nd];
		if (nnx < 0 || nny < 0 || nnx >= N || nny >= N || visited[nny][nnx]) tagger.see = (tagger.d + 3) % 4;
		else tagger.see = tagger.d;
	}
}

void catch_hider(int turn)
{
	int cnt = 0;
	for (int i = 0; i < 3; i++) {
		int nx = tagger.x + sdx[tagger.see][i];
		int ny = tagger.y + sdy[tagger.see][i];
		if (nx < 0 || ny < 0 || nx >= N || ny >= N) break;
		if (map_tree[ny][nx]) continue;
		if (!map_hider[ny][nx].empty()) {
			cnt += map_hider[ny][nx].size();
			for (auto it = map_hider[ny][nx].begin(); it != map_hider[ny][nx].end(); it++) {
				hider[*it].catched = true;
			}
			map_hider[ny][nx].clear();
		}
	}
	score += turn * cnt;
}

void solve()
{
	int turn = 1;
	while (turn <= K) {
		move_hider();
		move_tagger();
		catch_hider(turn);
		++turn;
	}
	cout << score;
}


int main()
{
	input();
	solve();
	return 0;
}