#include <iostream>
#include <vector>
using namespace std;

#define MAXNM 15
int N, M, D, enemy;
int map[MAXNM][MAXNM];
int pick[3];
int ans = 0;

struct AXIS { int y; int x; };


void input()
{
	cin >> N >> M >> D;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cin >> map[y][x];
			if (map[y][x]) enemy++;
		}
	}
}

AXIS attack(int m, int (*play)[MAXNM]) //(N, m)에 위치한 궁수가 쏠 수 있는 적
{
	int min_dist = 0x7fffffff;
	AXIS ret = { -1, -1 };

	int front_x = (m - (D - 1) < 0) ? 0 : (m - (D - 1));
	int after_x = (m + (D - 1) >= M) ? (M - 1) : (m + (D - 1));
	int h = ((N - 1) - (D - 1) < 0) ? 0 : ((N - 1) - (D - 1));

	//가장 왼쪽부터 탐색해야함
	for (int x = front_x; x <= after_x; x++) {
		for (int y = N - 1; y >= h; y--) {
			int dist = abs(N - y) + abs(m - x);
			if (dist > D || play[y][x] == 0) continue;
			if (dist < min_dist) {
				ret.x = x; ret.y = y;
				min_dist = dist;
			}
		}
	}
	return ret;
}

int check()
{
	int die = 0; //죽은 적의 수
	int score = 0; //궁수가 쏜 적의 수
	int play[MAXNM][MAXNM];
	copy(&map[0][0], &map[MAXNM - 1][MAXNM], &play[0][0]);

	while (die < enemy) {

		//궁수가 쏘기
		vector<AXIS> cand;
		for (int i = 0; i < 3; i++) {
			AXIS atk = attack(pick[i], play);
			if (atk.x != -1) cand.push_back(atk);
		}

		for (AXIS a : cand) {
			if (play[a.y][a.x]) { //중복 die 카운트를 방지하기 위해
				play[a.y][a.x] = 0;
				score++; 
				die++;
			}
		}

		//적들 전진
		int forward[MAXNM][MAXNM] = { 0 };
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < M; x++) {
				if (play[y][x] == 1) {
					if (y + 1 < N) forward[y + 1][x] = 1;
					else die++;
				}
			}
		}
		//forward를 play로 복사
		copy(&forward[0][0], &forward[MAXNM - 1][MAXNM], &play[0][0]);
	}

	return score;
}

void dfs(int n, int s) //궁수 3명 자리를 0~M-1 중에 뽑기
{
	if (n == 3) {
		int ret = check();
		if (ret > ans) ans = ret;
		return;
	}

	for (int i = s; i < M; i++) {
		pick[n] = i;
		dfs(n + 1, i + 1);
	}
}

void solve()
{
	dfs(0, 0);
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}