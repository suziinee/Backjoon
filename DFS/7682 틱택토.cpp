#include <iostream>
#include <string>
using namespace std;


bool win(int (*arr)[3], char ch)
{
	//가로
	for (int y = 0; y < 3; y++) {
		if (arr[y][0] == ch && arr[y][0] == arr[y][1] && arr[y][1] == arr[y][2]) return true;
	}
	//세로
	for (int x = 0; x < 3; x++) {
		if (arr[0][x] == ch && arr[0][x] == arr[1][x] && arr[1][x] == arr[2][x]) return true;
	}
	//대각선
	if (arr[0][0] == ch && arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2]) return true;
	if (arr[0][2] == ch && arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0]) return true;

	return false;
}

int solve(const string& s) //valid 1, invalid 0
{
	int o = 0; int x = 0;
	int arr[3][3];

	for (int i = 0; i < 9; i++) {
		if (s[i] == 'O') o++;
		else if (s[i] == 'X') x++;
		arr[i / 3][i % 3] = s[i];
	}
	
	if (x <= 5 && o <= 4) {
		//X가 이길때
		if (x == o + 1 && win(arr, 'X') && !win(arr, 'O')) return 1;
		//O가 이길때
		else if (x == o && win(arr, 'O') && !win(arr, 'X')) return 1;
		//9가 채워질 때
		else if (x == 5 && o == 4 && !win(arr, 'X') && !win(arr, 'O')) return 1;
	}

	return 0;
}

void input()
{
	string s;

	while (true) {
		cin >> s;
		if (s == "end") return;
		int ret = solve(s);
		if (ret) cout << "valid\n";
		else cout << "invalid\n";
	}
}


int main(void)
{
	input();
	return 0;
}