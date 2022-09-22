#include <iostream>
#include <vector>
using namespace std;

vector<int> vec;


void input()
{
	int N;
	cin >> N;
	int n;
	for (int i = 0; i < N; i++) {
		cin >> n;
		vec.push_back(n);
	}
}

void dfs(int s, int e)
{
	if (s > e) return;
	if (s == e) {
		cout << vec[s] << "\n";
		return;
	}

	int m;
	for (m = s; m <= e; m++) {
		if (vec[s] < vec[m]) break; //나보다 큰 걸 찾으면 break (오른쪽 tree의 시작점 찾음)
	}

	dfs(s + 1, m - 1);
	dfs(m, e);
	cout << vec[s] << "\n";
}

void solve()
{
	dfs(0, vec.size() - 1);
}


int main()
{
	input();
	solve();
	return 0;
}