#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int N, M;
unordered_map<int, int> ht;
vector<int> candi;


void input()
{
	cin >> N;
	int n;
	for (int i = 0; i < N; i++) {
		cin >> n;
		auto iter = ht.find(n);
		if (iter != ht.end()) (iter->second)++;
		else ht.insert({ n, 1 });
	}

	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> n;
		candi.push_back(n);
	}
}


void solve()
{
	for (int n : candi) {
		auto iter = ht.find(n);
		if (iter != ht.end()) cout << iter->second << " ";
		else cout << "0 ";
	}
}


int main(void)
{
	input();
	solve();
	return 0;
}