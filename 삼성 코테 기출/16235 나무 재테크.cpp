#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

#define MAXN 10
int N, M, K;
int material[MAXN + 1][MAXN + 1];
int map[MAXN + 1][MAXN + 1];
unordered_map<int, vector<int>> ht;


inline int get_key(int a, int b) { return a * 100 + b; }

void input()
{
	cin >> N >> M >> K;

	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			cin >> material[y][x];
			map[y][x] = 5;
		}
	}

	int y, x, age;
	for (int i = 0; i < M; i++) {
		cin >> y >> x >> age;
		vector<int> tmp = { age };
		ht.insert({ get_key(y, x), tmp });
	}
}

void spring()
{
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			int cur_key = get_key(y, x);
			auto it = ht.find(cur_key);
			if (it == ht.end()) continue;
			if ((it->second).size() == 0) continue;
			
			sort((it->second).begin(), (it->second).end());
			int idx = 0;
			for (int& tree : it->second) {
				if (map[y][x] < tree) break;
				map[y][x] -= tree;
				tree++; idx++;
			}
			for (int i = idx; i < (it->second).size(); i++) {
				(it->second)[i] *= -1; //죽은 나무는 -1이 곱해짐
			}
		}
	}
}

void summer()
{
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			int cur_key = get_key(y, x);
			auto it = ht.find(cur_key);
			if (it == ht.end()) continue;
			if ((it->second).size() == 0) continue;

			vector<int> new_trees;
			for (int tree : it->second) {
				if (tree < 0) {
					map[y][x] += (-1 * tree) / 2;
				}
				else new_trees.push_back(tree);
			}

			it->second = new_trees;
		}
	}
}

void fall()
{
	static int dx[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
	static int dy[] = { 0, -1, -1, -1, 0, 1, 1, 1 };

	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			int cur_key = get_key(y, x);
			auto it = ht.find(cur_key);
			if (it == ht.end()) continue;

			for (int tree : it->second) {
				if (tree % 5 || tree == 0) continue;
				for (int d = 0; d < 8; d++) {
					int nx = x + dx[d];
					int ny = y + dy[d];
					if (nx<1 || ny<1 || nx>N || ny>N) continue;
					
					int next_key = get_key(ny, nx);
					auto next_it = ht.find(next_key);
					if (next_it == ht.end()) {
						ht.insert({ next_key, {1} });
					}
					else {
						ht.find(next_key)->second.push_back(1);
					}
				}
			}
		}
	}
}

void winter()
{
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			map[y][x] += material[y][x];
		}
	}
}

void solve()
{	
	for (int i = 0; i < K; i++) {
		spring();
		summer();
		fall();
		winter();
	}

	int ans = 0;
	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			auto it = ht.find(get_key(y, x));
			if (it == ht.end()) continue;
			ans += (it->second).size();
		}
	}
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}