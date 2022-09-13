#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

#define MAX 10000
int T;
int st, en;
bool chk[MAX]; 
int path[MAX];
char path2[MAX];
queue<int> q;


int D(int n) { return (n * 2) % 10000; }
int S(int n) { return n == 0 ? 9999 : n - 1; }
int L(int n)
{
	int d1 = n / 1000;
	return (n - d1 * 1000) * 10 + d1;
}
int R(int n)
{
	int d4 = n % 10;
	return (n - d4) / 10 + d4 * 1000;
}

void bfs()
{
	q.push(st);
	chk[st] = true;
	path[st] = -1;

	while (!q.empty()) {
		int n = q.front(); q.pop();

		int candi[4] = { D(n), S(n), L(n), R(n) };
		char dslr[4] = { 'D', 'S', 'L', 'R' };

		for (int i = 0; i < 4; i++) {
			if (chk[candi[i]]) continue;

			q.push(candi[i]);
			chk[candi[i]] = true;
			path[candi[i]] = n;
			path2[candi[i]] = dslr[i];

			if (candi[i] == en) return;
		}
	}
}

void print_route(int n)
{
	if (n == st) return;
	print_route(path[n]);
	cout << path2[n];
}

void input()
{
	cin >> T;
	for (int t = 0; t < T; t++) {
		//초기화 - chk, path, path2, q
		fill(chk, chk + MAX, 0);
		fill(path, path + MAX, 0);
		fill(path2, path2 + MAX, 0);
		q = {};

		cin >> st >> en;
		bfs();
		print_route(en);
		cout << "\n";
	}
}


int main(void)
{
	input();
	return 0;
}