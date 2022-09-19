#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
vector<int> nums;
vector<int> candi;


void input()
{
	cin >> N;
	for (int i = 0; i < N; i++) {
		int n;
		cin >> n;
		nums.push_back(n);
	}
	cin >> M;
	for (int i = 0; i < M; i++) {
		int n;
		cin >> n;
		candi.push_back(n);
	}
}

int binary_search(int s, int e, const int& tar)
{
	int ret;
	while (s <= e) {
		int mid = (s + e) / 2;
		if (tar == nums[mid]) return mid;
		else if (tar > nums[mid]) s = mid + 1;
		else e = mid - 1;
	}
	return -1;
}

void solve()
{
	sort(nums.begin(), nums.end());
	for (int n : candi) {
		int index = binary_search(0, N - 1, n);

		if (index != -1) cout << "1\n";
		else cout << "0\n";
	}
}


int main(void)
{
	input();
	solve();
	return 0;
}