#include <iostream>
#include <vector>
#include <cmath>

int n, m;
int map[100][13]; //각 집마다 치킨집과의 거리
int res[13]; //치킨집 조합
int ans = 0x7fffffff;

class AXIS 
{
public:
	int x; int y;
};
std::vector<AXIS> house;
std::vector<AXIS> chicken;


void input()
{
	std::cin >> n;
	std::cin >> m;
	int tmp; AXIS a;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			std::cin >> tmp;
			if (tmp == 1) {
				a.x = j; a.y = i;
				house.push_back(a);
			}
			else if (tmp == 2) {
				a.x = j; a.y = i;
				chicken.push_back(a);
			}
		}
	}
}

void distance(const int& h, const int& c)
{
	for (int i = 0; i < h; i++) {
		int x = house[i].x; int y = house[i].y;
		for (int j = 0; j < c; j++) {
			map[i][j] = abs(x - chicken[j].x) + abs(y - chicken[j].y);
		}
	}
}

int min_chicken(const int& h, const int& c)
{
	int sum = 0;
	for (int i = 0; i < h; i++) {
		int min = 0x7fffffff;
		for (int j = 0; j < c; j++) {
			if (min > map[i][j]) min = map[i][j];
		}
		sum += min;
	}
	return sum;
}

int dfs_chicken(const int& h)
{
	int sum = 0;
	for (int i = 0; i < h; i++) {
		int min = 0x7fffffff;
		for (int j = 0; j < m; j++) {
			if (min > map[i][res[j]]) min = map[i][res[j]];
		}
		sum += min;
	}
	return sum;
}

void dfs(int L, int beginWith, const int& c, const int& h)
{
	if (L == m) {
		int ret = dfs_chicken(h);
		if (ans > ret) ans = ret;
		return;
	}
	else {
		for (int i = beginWith; i < c; i++) {
			res[L] = i;
			dfs(L + 1, i + 1, c, h);
		}
	}
}

void solve()
{
	int h = house.size();
	int c = chicken.size();
	distance(h, c);

	if (c <= m) {
		ans = min_chicken(h, c);
	}
	else {
		dfs(0, 0, c, h);
	}
}

int main()
{
	input();
	solve();
	std::cout << ans << std::endl;
	return 0;
}
