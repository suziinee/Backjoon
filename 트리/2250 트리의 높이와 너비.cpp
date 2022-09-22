#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

#define MAXN 10000
int N;
int parent[MAXN + 1];

struct NODE { int n; int l; int r; };
unordered_map<int, NODE> ht;
unordered_map<int, vector<NODE>> dep_ht;
int col[MAXN + 1]; //i의 열이 col[i]에 기록됨


void input()
{
	cin >> N;
	int p, l, r;
	for (int i = 1; i <= N; i++) {
		cin >> p >> l >> r;
		ht.insert({ p, {p, l, r} });
		parent[l] = p;
		parent[r] = p;
	}
}

int cnt = 1;
void preorder(int n, int d)
{
	if (n == -1) return;
	
	preorder(ht[n].l, d + 1);

	col[n] = cnt++; 
	auto it = dep_ht.find(d);
	if (it == dep_ht.end()) {
		dep_ht.insert({ d, {ht[n]} });
	}
	else {
		it->second.push_back(ht[n]);
	}

	preorder(ht[n].r, d + 1);
}

int find_root()
{
	for (int i = 1; i <= N; i++) {
		if (parent[i] == 0) return i;
	}
}

void solve()
{
	int root = find_root();
	preorder(root, 1);

	int ans = -1; 
	int ans_depth = 0x7fffffff;
	
	for (auto it = dep_ht.begin(); it != dep_ht.end(); it++) {

		int min = 0x7fffffff; int max = -1;
		for (NODE node : it->second) {
			if (col[node.n] < min) min = col[node.n];
			if (col[node.n] > max) max = col[node.n];
		}

		if (abs(max - min + 1) > ans) {
			ans = abs(max - min + 1);
			ans_depth = it->first;
		}
		else if (abs(max - min + 1) == ans && ans_depth > it->first) {
			ans_depth = it->first;
		}
	}

	cout << ans_depth << " " << ans;
}


int main()
{
	input();
	solve();
	return 0;
}