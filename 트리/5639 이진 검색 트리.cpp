#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct NODE { int l; int r; };
unordered_map<int, NODE> bst;
int root = -1;
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

void post(int n)
{
	if (n == -1) return;
	post(bst[n].l);
	post(bst[n].r);
	cout << n << "\n";
}

void search(int p, int s, int e)
{
	if (s > e) return;

	int m;
	for (m = s; m <= e; m++) {
		if (p < vec[m]) break;
	}

	if (s <= m - 1) {
		bst[p].l = vec[s];
		bst.insert({ vec[s], {-1, -1} });
		search(vec[s], s + 1, m - 1);
	}
	if (m <= e) {
		bst[p].r = vec[m];
		bst.insert({ vec[m], {-1, -1} });
		search(vec[m], m + 1, e);
	}
}

void solve()
{
	root = vec[0];
	bst.insert({ root, {-1, -1} });
	
	search(root, 1, vec.size() - 1);
	
	post(root);
}


int main()
{
	input();
	solve();
	return 0;
}