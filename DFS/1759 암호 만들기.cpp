#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

#define MAX 15
int L, C;
string alpha[MAX];


void input()
{
	cin >> L >> C;
	for (int i = 0; i < C; i++) { cin >> alpha[i]; }
}

void dfs(string str, int s, int ja, int mo)
{
	if (str.size() == L) {
		if (mo >= 1 && ja >= 2) cout << str << "\n";
		return;
	}

	for (int i = s; i < C; i++) {
		if (alpha[i] == "a" || alpha[i] == "e" || alpha[i] == "i" || alpha[i] == "o" || alpha[i] == "u") {
			dfs(str + alpha[i], i + 1, ja, mo + 1);
		}
		else {
			dfs(str + alpha[i], i + 1, ja + 1, mo);
		}
	}
}

void solve()
{
	sort(alpha, alpha + C);

	dfs("", 0, 0, 0);
}


int main(void)
{
	input();
	solve();
	return 0;
}