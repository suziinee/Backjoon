#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int N, M;
unordered_set<int> s;
vector<int> candi;


void input()
{
	cin >> N;
	for (int i = 0; i < N; i++) {
		int n;
		cin >> n;
		s.insert(n);
	}
	cin >> M;
	for (int i = 0; i < M; i++) {
		int n;
		cin >> n;
		candi.push_back(n);
	}
}


void solve()
{
	for (int n : candi) {
		auto i = s.find(n);
		if (i == s.end()) cout << "0\n";
		else cout << "1\n";
	}
}


int main(void)
{
	input();
	solve();
	return 0;
}