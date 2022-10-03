#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N;

struct INFO {
	int s;
	int e;
	bool operator<(const INFO& i) const { //sort를 위한 비교함수
		return s < i.s;
	}
};
vector<INFO> info;
priority_queue<int, vector<int>, greater<int>> pq; //오름차순


void input()
{
	cin >> N;
	int s, e;
	for (int i = 0; i < N; i++) {
		cin >> s >> e;
		info.push_back({ s, e });
	}
}

void solve()
{
	sort(info.begin(), info.end());
	pq.push(info[0].e);

	for (int i = 1; i < N; i++) {
		if (info[i].s >= pq.top()) {
			pq.pop();
		}
		pq.push(info[i].e);
	}

	cout << pq.size();
}


int main()
{
	input();
	solve();
	return 0;
}