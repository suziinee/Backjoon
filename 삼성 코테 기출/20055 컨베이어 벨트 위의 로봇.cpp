#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <deque>
using namespace std;

int n, k;
vector<int> belt;


void input()
{
	cin >> n >> k;
	for (int i = 0; i < 2 * n; i++) {
		int val;
		cin >> val;
		belt.push_back(val);
	}
}

void output(const int& ans)
{
	cout << ans;
}

int solve()
{
	int ans = 0;

	int robot[200 + 10]; //로봇이 있는 벨트의 인덱스는 1
	memset(robot, 0, sizeof(robot));
	int st = 0; int en = n - 1; //처음에는 0번부터 n-1번까지 컨베이어 벨트

	while (true) {
		ans++;

		//1. 벨트 한 칸 회전
		st = (st == 0) ? 2 * n - 1 : st - 1;
		en = (en == 0) ? 2 * n - 1 : en - 1;
		//1-1. 내릴 수 있는 로봇이 있다면 내리기
		if (robot[en] == 1) robot[en] = 0;

		//2. 로봇 이동 **en부터 st의 순서로 발생
		int chk = (en == 0) ? 2 * n - 1 : en - 1;
		while (true) {
			if (robot[chk] == 1) {
				int next = (chk + 1) % (2 * n);
				if (belt[next] >= 1 && robot[next] == 0) {
					belt[next]--;
					robot[chk] = 0;
					robot[next] = 1;
				}
				//2-1. 내릴 수 있으면 바로 내리기
				if (robot[en] == 1) robot[en] = 0;
			}
			if (chk == st) break;
			chk = (chk == 0) ? (chk = 2 * n - 1) : (chk -= 1);
		}
		
		//3. 로봇 올리기
		if (belt[st] >= 1) {
			robot[st] = 1;
			belt[st]--;
		}

		//4. 벨트 체크
		int cnt = 0;
		for (auto b : belt) {
			if (b == 0) cnt++;
		}
		if (cnt >= k) break;
	}

	return ans;
}


int main()
{
	input();
	int ans = solve();
	output(ans);
	return 0;
}