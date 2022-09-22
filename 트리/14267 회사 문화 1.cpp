#include <iostream>
using namespace std;

#define MAXN 100000
int N, M;
int par[MAXN + 1];
int comp[MAXN + 1];


void input()
{
	cin >> N >> M;
	int n;
	for (int i = 1; i <= N; i++) {
		cin >> n;
		par[i] = n;
	}
	
	int i, w;
	for (int j = 0; j < M; j++) {
		cin >> i >> w;
		comp[i] += w;
	}
}

void solve()
{
	for (int i = 2; i <= N; i++) {
		comp[i] += comp[par[i]];
	}

	for (int i = 1; i <= N; i++) {
		cout << comp[i] << " ";
	}
}


int main()
{
	input();
	solve();
	return 0;
}