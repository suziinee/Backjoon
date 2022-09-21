#include <iostream>
#include <cstdio>
using namespace std;

#define MAXN 26
int N;
int tree[MAXN][2];


void input()
{
	cin >> N;

	char p, c1, c2;
	for (int i = 0; i < N; i++) {
		cin >> p >> c1 >> c2;
		tree[p - 'A'][0] = (c1 == '.') ? -1 : (c1 - 'A');
		tree[p - 'A'][1] = (c2 == '.') ? -1 : (c2 - 'A');
	}
}

void pre(int n)
{
	if (n == -1) return;

	printf("%c", 'A' + n);
	pre(tree[n][0]);
	pre(tree[n][1]);
}

void in(int n)
{
	if (n == -1) return;

	in(tree[n][0]);
	printf("%c", 'A' + n);
	in(tree[n][1]);
}

void post(int n)
{
	if (n == -1) return;
	
	post(tree[n][0]);
	post(tree[n][1]);
	printf("%c", 'A' + n);
}

void solve()
{
	pre(0);
	cout << "\n";
	in(0);
	cout << "\n";
	post(0);
	cout << "\n";
}


int main()
{
	input();
	solve();
	return 0;
}