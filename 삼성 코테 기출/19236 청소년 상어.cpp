#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int ans;

struct FISH { int n; int d; }; 
FISH map[4][4]; //상어에게 먹혔으면 n=0

struct SHARK { int y; int x; int d; int score; };
SHARK shark;

struct AXIS { int y; int x; };

const int dx[] = { 0, -1, -1, -1, 0, 1, 1, 1 };
const int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };


void input()
{
	int n, d;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			cin >> n >> d;
			d--;
			map[y][x] = { n, d };
		}
	}
}

void one_fish_move(FISH (*arr)[4], SHARK& cur, const int& f)
{
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (arr[y][x].n == f) {
				int d = arr[y][x].d; //현재 방향
				for (int i = 0; i < 8; i++) { //8번 시도
					int nd = (d + i) % 8;
					int nx = x + dx[nd];
					int ny = y + dy[nd];
					//상어가 없고 경계를 넘지 않는 칸으로 이동
					if (nx >= 0 && ny >= 0 && nx < 4 && ny < 4 && !(nx == cur.x && ny == cur.y)) {
						if (arr[ny][nx].n) { //물고기가 있다면 swap
							FISH tmp = arr[ny][nx];
							arr[ny][nx] = { f, nd };
							arr[y][x] = tmp;
						}
						else { //없다면 그대로 이동
							arr[ny][nx] = { f, nd };
							arr[y][x].n = 0;
						}
						return;
					}
				}
			}
		}
	}
}

void fish_move(FISH (*arr)[4], SHARK& cur) //arr를 바꿔줌
{
	//살아있는 물고기 담기
	vector<int> fish;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (arr[y][x].n) fish.push_back(arr[y][x].n);
		}
	}
	//fish 정렬 (오름차순)
	sort(fish.begin(), fish.end());

	for (int f : fish) { //오름차순의 fish에 대해
		one_fish_move(arr, cur, f);
	}
}

void dfs(FISH(*arr)[4], SHARK cur)
{
	fish_move(arr, cur);

	vector<AXIS> cand; //상어가 갈 수 있는 칸
	for (int i = 1; i <= 3; i++) {
		int nx = cur.x + i * dx[cur.d];
		int ny = cur.y + i * dy[cur.d];
		if (nx < 0 || ny < 0 || nx >= 4 || ny >= 4) continue;
		if (arr[ny][nx].n == 0) continue; //물고기가 없는 칸으로는 이동 불가
		cand.push_back({ ny, nx });
	}
	if (cand.empty()) { //ans 갱신하고 종료
		if (cur.score > ans) ans = cur.score;
		return;
	}
	else {
		for (AXIS c : cand) { //상어를 해당 칸으로 이동시키고 dfs 호출
			FISH new_arr[4][4]; //원본 유지를 해야 다음 dfs에서 올바르게 실행 가능
			copy(&arr[0][0], &arr[3][4], &new_arr[0][0]);
			FISH tmp = new_arr[c.y][c.x];
			new_arr[c.y][c.x].n = 0;
			dfs(new_arr, { c.y, c.x, tmp.d, cur.score + tmp.n });
		}
	}
}

void solve()
{
	//(0, 0) 물고기 잡아먹기
	shark.y = 0;
	shark.x = 0;
	shark.d = map[0][0].d;
	shark.score += map[0][0].n;
	map[0][0].n = 0;

	dfs(map, shark);
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}