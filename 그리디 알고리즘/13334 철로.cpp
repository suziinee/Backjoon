#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

int N, D;

struct POS {
	int s;
	int e;
	bool operator<(const POS& p) const { return s > p.s; } //pq에 사용할 우선순위
};
vector<POS> pos; //끝시간 기준 오름차순
priority_queue<POS> pq; //시작시간 기준 오름차순
bool compare(const POS& p1, const POS& p2) { //pos vector sort에 사용할 함수
	return p1.e < p2.e; 
}


void input()
{
	cin >> N;
	int s, e;
	for (int i = 0; i < N; i++) {
		cin >> s >> e;
		if (s > e) {
			int tmp = s;
			s = e;
			e = tmp;
		}
		pos.push_back({ s, e });
	}
	cin >> D;
}

void solve()
{
	sort(pos.begin(), pos.end(), compare);
	int ans = 0;

	for (int i = 0; i < N; i++) {
		pq.push(pos[i]);
		int d_st = pos[i].e - D;
		
		//시작시간 정렬이기 때문에 D의 앞지점보다 시작지점이 작은 것들을 빼주면 남은 것은 D 안에 들어감
		while (!pq.empty() && pq.top().s < d_st) {
			pq.pop();
		}

		if (ans < pq.size()) ans = pq.size();
	}

	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}