#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

#define MAXN 50
#define MAXM 100
int N, M;
int map[MAXN][MAXN];
bool map_c[MAXN][MAXN];

struct AXIS { int y, x; };
deque<AXIS> cloud;
deque<AXIS> tmp_cloud;

struct MAGIC { int d, s; };
MAGIC magic[MAXM];

const int dx[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
const int dy[] = { 0, -1, -1, -1, 0, 1, 1, 1 };


void input()
{
	cin >> N >> M;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
		}
	}
	for (int i = 0; i < M; i++) {
		cin >> magic[i].d >> magic[i].s;
		--magic[i].d;
	}
}

void move_cloud(int d, int s) //cloud에 있는 구름을 옮겨서 map_c에 표시하고 tmp_cloud에 저장
{
	for (AXIS c : cloud) {
		int nx = (c.x + dx[d] * (s % N) + N) % N;
		int ny = (c.y + dy[d] * (s % N) + N) % N;
		map[ny][nx]++; //새 구름 위치
		map_c[ny][nx] = true; //make_cloud를 위해 남겨놓기
		tmp_cloud.push_back({ ny, nx }); //bug를 위해 잠깐 tmp_cloud에 저장
	}
	cloud.clear();
}

void bug() //new_cloud에 대해 물복사 버그 시전
{
	for (AXIS c : tmp_cloud) {
		int cnt = 0;
		for (int d = 0; d < 4; d++) {
			int nd = 2 * d + 1;
			int nx = c.x + dx[nd];
			int ny = c.y + dy[nd];
			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
			if (map[ny][nx]) ++cnt;
		}
		map[c.y][c.x] += cnt;
	}
}

void make_cloud()
{
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map[y][x] >= 2 && !map_c[y][x]) {
				cloud.push_back({ y, x });
				map[y][x] -= 2;
			}
		}
	}
}

void clear_cloud() 
{
	fill(&map_c[0][0], &map_c[MAXN - 1][MAXN], false);
	tmp_cloud.clear();
}

void solve()
{
	cloud.push_back({ N - 1, 0 });
	cloud.push_back({ N - 1, 1 });
	cloud.push_back({ N - 2, 0 });
	cloud.push_back({ N - 2, 1 });

	for (int i = 0; i < M; i++) {
		move_cloud(magic[i].d, magic[i].s); //1, 2
		bug(); //4
		make_cloud(); //5
		clear_cloud(); //3
	}

	int ans = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			ans += map[y][x];
		}
	}
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}