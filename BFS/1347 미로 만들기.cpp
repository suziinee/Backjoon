#include <iostream>
#include <string>
using namespace std;

int N;
int map[100 + 5][100 + 5];
string s;
struct REC { int min_x; int max_x; int min_y; int max_y; };


void input()
{
	cin >> N >> s;
}

REC find()
{
	int min_y = 200; int max_y = -1;
	int min_x = 200; int max_x = -1;

	for (int y = 0; y < 105; y++) {
		for (int x = 0; x < 105; x++) {
			if (map[y][x]) {
				if (x < min_x) min_x = x;
				if (x > max_x) max_x = x;
				if (y < min_y) min_y = y;
				if (y > max_y) max_y = y;
			}
		}
	}

	return { min_x, max_x, min_y, max_y };
}

void output(REC rec)
{
	for (int y = rec.min_y; y <= rec.max_y; y++) {
		for (int x = rec.min_x; x <= rec.max_x; x++) {
			if (map[y][x] == 0) cout << "#";
			else cout << ".";
		}
		cout << "\n";
	}
}

void solve()
{
	const int dx[] = { 0, 1, 0, -1 };
	const int dy[] = { -1, 0, 1, 0 };

	int x = 50; int y = 50; int d = 2;
	map[y][x] = 1;

	for (int i = 0; i < N; i++) {
		if (s[i] == 'L') {
			d = (d + 3) % 4;
		}
		else if (s[i] == 'R') {
			d = (d + 1) % 4;
		}
		else if (s[i] == 'F') {
			int nx = x + dx[d];
			int ny = y + dy[d];
			map[ny][nx] = 1;
			x = nx; y = ny;
		}
	}

	REC rec = find();
	output(rec);
}


int main(void)
{
	input();
	solve();
	return 0;
}