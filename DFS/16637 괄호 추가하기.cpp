#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <deque>
using namespace std;

int N;
vector<int> nums;
vector<int> oper; //+ 0, - 1, * 2, / 3
int chk[10]; //oper 괄호 여부 확인 배열
int ans = -1 * 0x7fffffff;


void input()
{
	cin >> N;

	string s;
	cin >> s;
	for (int i = 0; i < N; i++) {
		if (i % 2) {
			if (s[i] == '+') oper.push_back(0);
			else if (s[i] == '-') oper.push_back(1);
			else if (s[i] == '*') oper.push_back(2);
			else if (s[i] == '/') oper.push_back(3);
		}
		else nums.push_back(s[i] - '0');
	}
}

int calcul()
{
	int tmp[10];
	fill(tmp, tmp + 10, -1 * 0x7fffffff);
	int nums_chk[10] = { 0 };

	for (int i = 0; i < oper.size(); i++) {
		if (chk[i]) {
			switch (oper[i]) {
			case 0: {
				tmp[i] = nums[i] + nums[i + 1]; 
				nums_chk[i] = 1; nums_chk[i + 1] = 1;
				break;
				}
			case 1: {
				tmp[i] = nums[i] - nums[i + 1];
				nums_chk[i] = 1; nums_chk[i + 1] = 1;
				break;
				}
			case 2: {
				tmp[i] = nums[i] * nums[i + 1];
				nums_chk[i] = 1; nums_chk[i + 1] = 1;
				break;
				}
			case 3: {
				tmp[i] = nums[i] / nums[i + 1];
				nums_chk[i] = 1; nums_chk[i + 1] = 1;
				break;
				}
			}
		}
	}

	for (int i = 0; i < nums.size(); i++) {
		if (!nums_chk[i]) tmp[i] = nums[i];
	}

	deque<int> dq;
	for (int i = 0; i < 10; i++) {
		if (tmp[i] != (-1 * 0x7fffffff)) dq.push_back(tmp[i]);
	}

	//q에서 하나씩 꺼내서 계산
	for (int i = 0; i < oper.size(); i++) {
		if (!chk[i]) {
			int a = dq.front(); dq.pop_front();
			int b = dq.front(); dq.pop_front();
			switch (oper[i]) {
				case 0: dq.push_front(a + b); break;
				case 1: dq.push_front(a - b); break;
				case 2: dq.push_front(a*b); break;
				case 3: dq.push_front(a / b); break;
			}
		}
	}

	return dq.front();
}

void dfs(int n)
{
	if (n >= oper.size()) {
		int sum = calcul();
		if (sum > ans) ans = sum;
		return;
	}

	//n번째 연산자 포함
	chk[n] = 1;
	dfs(n + 2);
	chk[n] = 0;

	//n번째 연산자 미포함
	chk[n] = 0;
	dfs(n + 1);
}

void solve()
{
	dfs(0);
	cout << ans;
}


int main(void)
{
	input();
	solve();
	return 0;
}