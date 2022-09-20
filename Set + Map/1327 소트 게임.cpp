#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <queue>
#include <string>
using namespace std;

int N, K;
vector<int> nums;
unordered_set<int> chk;

struct STATUS { int num; int cnt; };
queue<STATUS> q;


void input()
{
	cin >> N >> K;
	
	int n;
	for (int i = 0; i < N; i++) {
		cin >> n;
		nums.push_back(n);
	}
}

int make_init(vector<int>& vec)
{
	int ret = 0;
	for (int i = N - 1; i >= 0; i--) {
		ret += pow(10, i) * vec[N - i - 1];
	}
	return ret;
}

int make_end(vector<int>& nums)
{
	sort(nums.begin(), nums.end());
	return make_init(nums);
}

int make_next(int i, int n) //i-K+1부터 i 인덱스까지 reverse
{
	string str = to_string(n);
	string rev;
	for (int s = i - K + 1; s <= i; s++) rev += str[s];
	
	reverse(rev.begin(), rev.end());
	
	int r = 0;
	for (int s = 0; s < N; s++) {
		if (s >= i - K + 1 && s <= i) str[s] = rev[r++];
	}
	return stoi(str);
}

int bfs()
{
	int init = make_init(nums);
	int end = make_end(nums);
	q.push({ init, 0 });
	chk.insert(init);
	if (init == end) return 0;

	while (!q.empty()) {
		STATUS cur = q.front(); q.pop();

		for (int i = K - 1; i < N; i++) {
			STATUS next;
			next.num = make_next(i, cur.num);
			next.cnt = cur.cnt + 1;
			auto iter = chk.find(next.num);
			if (iter == chk.end()) { //chk에 없음
				chk.insert(next.num);
				q.push(next);
				if (next.num == end) return next.cnt;
			}
		}
	}

	return -1;
}

void solve()
{
	cout << bfs();
}


int main()
{
	input();
	solve();
	return 0;
}