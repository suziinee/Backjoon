#include <iostream>
#include <vector>
using namespace std;

#define MAXN 29
int N;
int map[MAXN][MAXN];
int back[MAXN][MAXN];

struct GROUP {
	int y, x; //시작 위치
	int n; int cnt; int cur; //원래 숫자, 그룹 크기, 현재 번호
};
vector<GROUP> group;

int side_count[950][950]; //[중심 그룹][인접 그룹]
const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };


void input()
{
	cin >> N;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
		}
	}
}

void init_dfs(int y, int x, int n, int g, bool init_chk[][MAXN], int& cnt)
{
	++cnt;
	init_chk[y][x] = true;
	map[y][x] = g;
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
		if (init_chk[ny][nx] || map[ny][nx] != n) continue;
		init_dfs(ny, nx, n, g, init_chk, cnt);
	}
}

void init_group()
{
	group.clear(); //초기화
	fill(&side_count[0][0], &side_count[950 - 1][950], 0); //초기화
	copy(&map[0][0], &map[MAXN-1][MAXN], &back[0][0]); //원래 map을 back에 복사해놓기

	int g = 10;
	bool init_chk[MAXN][MAXN] = { false, };
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (init_chk[y][x]) continue;
			++g;
			int n = map[y][x]; //원래 번호
			int cnt = 0;
			init_dfs(y, x, n, g, init_chk, cnt);
			group.push_back({ y, x, n, cnt, g });
		}
	}
}

void count_close(int y, int x, int n, bool count_chk[][MAXN]) //(y, x)부터 시작해서 숫자가 n인 지점의 변 조사
{
	count_chk[y][x] = true;
	for (int d = 0; d < 4; d++) {
		int nx = x + dx[d];
		int ny = y + dy[d];
		if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
		if (map[ny][nx] != n) {
			side_count[n][map[ny][nx]]++;
		}
		else {
			if (count_chk[ny][nx]) continue;
			count_close(ny, nx, n, count_chk);
		}
	}
}

inline int get_score(int a, int b)
{
	return (group[a].cnt + group[b].cnt) * group[a].n * group[b].n * side_count[group[a].cur][group[b].cur];
}

void clockwise(int y, int x, int n, int back_map[][MAXN])
{
	int nc = x;
	for (int r = y; r < y + n; r++) {
		int nr = y + n - 1;
		for (int c = x; c < x + n; c++) {
			back_map[r][c] = back[nr][nc];
			--nr;
		}
		++nc;
	}
}

void rotate()
{
	int back_map[MAXN][MAXN] = { 0, }; //rotate 시 back을 back_map에 복사
	
	//십자 모양 반시계 회전 -> 전체를 back_map에 반시계 회전한 후 십자 모양만 사용
	int nx = 0;
	for (int y = 0; y < N; y++) {
		int ny = N - 1;
		for (int x = 0; x < N; x++) {
			back_map[ny][nx] = back[y][x];
			--ny;
		}
		++nx;
	}

	//나머지 4개 정사각형 개별적으로 시계 회전
	int n = N / 2;
	clockwise(0, 0, n, back_map);
	clockwise(0, n + 1, n, back_map);
	clockwise(n + 1, 0, n, back_map);
	clockwise(n + 1, n + 1, n, back_map);
	
	copy(&back_map[0][0], &back_map[MAXN - 1][MAXN], &map[0][0]); //back_map을 map에 복사
}

void solve()
{
	int score = 0;
	for (int turn = 0; turn < 4; turn++) {
		init_group(); //초기화 및 map을 back에 복사하고 map을 그룹 숫자로 바꿔줌
		for (const GROUP& g : group) {
			bool count_chk[MAXN][MAXN] = { false, };
			count_close(g.y, g.x, g.cur, count_chk);
		}
		for (int i = 0; i < group.size(); i++) {
			for (int j = i + 1; j < group.size(); j++) {
				score += get_score(i, j);
			}
		}
		rotate(); //back을 회전시켜서 map에 복사하며 map을 다시 원래 숫자로 바꿔줌
	}
	cout << score;
}


int main()
{
	input();
	solve();
	return 0;
}