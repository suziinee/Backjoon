#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>
using namespace std;

int N, M;
unordered_set<string> us;
vector<string> candi;


void input()
{
	cin >> N >> M;

	string str;
	for (int i = 0; i < N; i++) {
		cin >> str;
		us.insert(str);
	}
	for (int i = 0; i < M; i++) {
		cin >> str;
		candi.push_back(str);
	}
}

void solve()
{
	int ans = 0;
	for (string str : candi) {
		if (us.end() != us.find(str)) ans++;
	}
	cout << ans;
}


int main(void)
{
	input();
	solve();
	return 0;
}