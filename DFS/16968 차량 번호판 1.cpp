#include <iostream>
#include <string>
using namespace std;

string s;


void input()
{
	cin >> s;
}

int solve()
{
	int ans = 1;
	
	int tmp;
	for (int i = 0; i < s.size(); i++) {
		if (i == 0) {
			if (s[i] == 'c') ans *= 26;
			else if (s[i] == 'd') ans *= 10;
			tmp = s[i];
			continue;
		}
		
		if (tmp == s[i]) {
			if (tmp == 'c') ans *= 25;
			else if (tmp == 'd') ans *= 9;
		}
		else {
			if (s[i] == 'c') ans *= 26;
			else if (s[i] == 'd') ans *= 10;
			tmp = s[i];
		}
	}

	return ans;
}


int main(void)
{
	input();
	int ans = solve();
	cout << ans;
	return 0;
}