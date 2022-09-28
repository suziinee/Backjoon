#include <iostream>
#include <vector>
using namespace std;

#define MAXN 100
int N, K;

struct STATUS {
	int dur; //내구도
	int robot; //로봇 개수
};
STATUS belt[2 * MAXN + 1]; //1번 벨트부터 2N번 벨트까지 사용
int st, en;


void input()
{
	cin >> N >> K;
	for (int i = 1; i <= 2 * N; i++) {
		cin >> belt[i].dur;
	}
	st = 1; en = N;
}

void solve()
{
	bool is_update = true;
	int ans = 0;

	while (is_update) {
		is_update = false;
		ans++;

		//회전
		st = (st == 1) ? 2 * N : (st - 1);
		en = (en == 1) ? 2 * N : (en - 1);
		/*로봇 내리기*/
		if (belt[en].robot) belt[en].robot = 0;

		//en부터 st까지 벨트 확인
		int cur = en;
		while (true) {
			int next = (cur == 2 * N) ? 1 : (cur + 1);
			if (belt[cur].robot && belt[next].dur >= 1 && belt[next].robot == 0) {
				//로봇 이동
				belt[cur].robot = 0;
				belt[next].robot = 1;
				belt[next].dur -= 1;
			}
			/*로봇 내리기*/
			if (belt[en].robot) belt[en].robot = 0;

			if (cur == st) break;
			cur = (cur == 1) ? 2 * N : (cur - 1);
		}
		/*로봇 내리기*/
		if (belt[en].robot) belt[en].robot = 0;

		//올리기
		if (belt[st].dur >= 1) {
			belt[st].dur -= 1;
			belt[st].robot = 1;
		}

		//종료조건 확인
		int cnt = 0;
		for (int i = 1; i <= 2 * N; i++) {
			if (belt[i].dur == 0) cnt++;
		}
		if (cnt >= K) is_update = false;
		else is_update = true;
	}

	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}