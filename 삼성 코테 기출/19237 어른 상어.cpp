#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>
using namespace std;

#define MAXN 20
int N, M, K;
unordered_set<int> map_sn[MAXN][MAXN]; //좌표마다 상어 번호 저장

struct SMELL { int n; int remain; };
list<SMELL> map_sml[MAXN][MAXN]; //좌표마다 냄새 저장

struct SHARK {
	int d; //현재 방향
	int y, x;
	int dir[4][4]; //[현재방향][우선순위 방향들]
};
unordered_map<int, SHARK> shark_map; //<상어번호, 상어정보>


void input()
{
	cin >> N >> M >> K;
	int n;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> n;
			if (n) {
				map_sn[y][x].insert(n); //좌표에 상어 저장
				shark_map.insert({ n, {} });
				shark_map[n].y = y;
				shark_map[n].x = x;
			}
		}
	}
	for (int i = 1; i <= M; i++) {
		cin >> n;
		n--;
		shark_map[i].d = n;
	}
	for (int i = 1; i <= M; i++) {
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				cin >> n;
				n--;
				shark_map[i].dir[y][x] = n;
			}
		}
	}
}

void spread_smell() //모든 상어가 자신의 위치에서 자신의 냄새 뿌림
{
	for (auto it = shark_map.begin(); it != shark_map.end(); it++) {
		SMELL tmp = { it->first, K };
		map_sml[(it->second).y][(it->second).x].push_back(tmp);
	}
}

void shark_move() //상어의 이동 : 빈칸 -> 자신의 냄새가 있는 칸
{
	static int dx[] = { 0, 0, -1, 1 };
	static int dy[] = { -1, 1, 0, 0 };

	for (auto it = shark_map.begin(); it != shark_map.end(); it++) {
		SHARK& tmp = it->second;

		//현재 방향 기준으로 우선순위 상하좌우 확인 -> 빈칸 있으면 바로 가기
		bool flag = false;
		for (int i = 0; i < 4; i++) {
			int nd = tmp.dir[tmp.d][i];
			int nx = tmp.x + dx[nd];
			int ny = tmp.y + dy[nd];
			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
			if (map_sml[ny][nx].empty()) { //상어 이동
				map_sn[tmp.y][tmp.x].erase(it->first);
				map_sn[ny][nx].insert(it->first);
				tmp.x = nx; 
				tmp.y = ny;
				tmp.d = nd;
				flag = true; break;
			}
		}
		if (!flag) { //빈칸을 찾지 못했음 -> 상하좌우 한번 더 확인하고 자기 냄새가 있는 칸으로 이동
			for (int i = 0; i < 4; i++) {
				int nd = tmp.dir[tmp.d][i];
				int nx = tmp.x + dx[nd];
				int ny = tmp.y + dy[nd];
				if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
				for (SMELL s : map_sml[ny][nx]) {
					if (s.n == it->first) {
						map_sn[tmp.y][tmp.x].erase(it->first);
						map_sn[ny][nx].insert(it->first);
						tmp.x = nx;
						tmp.y = ny;
						tmp.d = nd;
						flag = true; break;
					}
				}
				if (flag) break;
			}
		}
	}
}

void disappear_smell() //냄새에서 1초씩 뺀 뒤 0이 된 냄새는 제거
{
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map_sml[y][x].empty()) continue;
			for (SMELL& s : map_sml[y][x]) s.remain -= 1;
			
			auto it = map_sml[y][x].begin();
			while (it != map_sml[y][x].end()) {
				if (it->remain == 0) map_sml[y][x].erase(it++);
				else it++;
			}
		}
	}
}

void remove_shark()
{
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map_sn[y][x].empty() || map_sn[y][x].size() == 1) continue;
			vector<int> tmp;
			for (int n : map_sn[y][x]) tmp.push_back(n);
			sort(tmp.begin(), tmp.end(), greater<int>());
			for (int i = 0; i < tmp.size() - 1; i++) {
				map_sn[y][x].erase(tmp[i]);
				shark_map.erase(tmp[i]);
			}
		}
	}
}

bool end_check()
{
	//격자에 1번 상어만 남았는지 확인
	bool flag = false; //1번 상어 발견하면 true
	int cnt = 0; //상어 개수 카운트
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map_sn[y][x].empty()) continue;
			cnt += map_sn[y][x].size();
			if (map_sn[y][x].find(1) != map_sn[y][x].end()) flag = true;
		}
	}
	if (cnt == 1 && flag) return true;
	else return false;
}

void solve()
{
	for (int t = 1; t <= 1000; t++) {
		spread_smell();
		shark_move();
		disappear_smell();
		remove_shark();

		if (end_check()) { 
			cout << t; 
			return; 
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