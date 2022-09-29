#include <iostream>
using namespace std;

#define MAXN 50
int N;
int pick[10]; //1번~9번 타자
int chk[10]; //n번 선수를 뽑았는지 체크하는 배열
int ans;

int inn[MAXN][10];


void input()
{
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int p = 1; p <= 9; p++) {
			cin >> inn[i][p];
		}
	}
}

int play()
{
	int score = 0;
	int p = 1; //1번 타자부터 시작
	int batter = pick[p]; //p번 타자의 선수번호
	
	for (int i = 0; i < N; i++) { //하나의 이닝
		int out = 0;
		int player[3] = { 0, 0, 0 }; //1루, 2루, 3루

		while (out < 3) {
			int res = inn[i][batter];
			switch (res) {
			case 0: {
				out++;
				break;
			}
			case 1: case 2: case 3: case 4: {
				for (int i = 2; i >= 0; i--) {
					if (player[i] == 0) continue;
					int next = i + res;
					if (next > 2) {
						score += 1;
					}
					else {
						player[next] = 1;
					}
					player[i] = 0;
				}
				if (res == 4) score++;
				else player[res - 1] = 1;
				break;
			}
			}
			p = (p == 9) ? 1 : (p + 1);
			batter = pick[p];
		}
	}

	return score;
}

void dfs(int n) //n번 타자 뽑기
{
	if (n > 4 && pick[4] != 1) return;
	if (n == 10) {
		int score = play();
		if (score > ans) ans = score;
		return;
	}

	for (int i = 1; i <= 9; i++) { //선수 i
		if (chk[i]) continue;
		chk[i] = 1;
		pick[n] = i;
		dfs(n + 1);
		chk[i] = 0;
		pick[n] = 0;
	}
}

void solve()
{
	dfs(1);
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}