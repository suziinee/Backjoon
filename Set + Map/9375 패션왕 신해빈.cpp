#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int T, N;
unordered_map<string, int> ht;


void solve()
{	
	int ans = 1;

	for (auto it = ht.begin(); it != ht.end(); it++) {
		ans *= (it->second) + 1;
	}
	ans--;

	cout << ans << "\n";
}


void input()
{
	cin >> T;

	string name, type;
	for (int t = 0; t < T; t++) {
		cin >> N;

		ht.clear();

		for (int i = 0; i < N; i++) {
			cin >> name >> type;
			auto it = ht.find(type);
			if (it != ht.end()) {
				(it->second)++;
			}
			else {
				ht.insert({ type, 1 });
			}
		}

		solve();
	}
}


int main()
{
	input();
	return 0;
}