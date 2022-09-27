#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
vector<int> nums;


void input()
{
	cin >> N;
	int n;
	for (int i = 0; i < N; i++) {
		cin >> n; 
		nums.push_back(n);
	}
}

int bs_lower(int s, int e, int tar) //tar보다 작거나 같은 값
{
	int ret = -1; int mid;
	while (s <= e) {
		mid = (s + e) / 2;
		if (tar >= nums[mid]) {
			ret = mid;
			s = mid + 1;
		}
		else e = mid - 1;
	}
	return ret;
}

int bs_upper(int s, int e, int tar) //tar보다 크거나 같은 값
{
	int ret = -1; int mid;
	while (s <= e) {
		mid = (s + e) / 2;
		if (tar <= nums[mid]) {
			ret = mid;
			e = mid - 1;
		}
		else s = mid + 1;
	}
	return ret;
}

void solve()
{
	sort(nums.begin(), nums.end());
	int min_diff = 0x7fffffff;
	int cand[2];

	for (int i = 0; i < N; i++) {
		int lower = bs_lower(0, N - 1, -nums[i]);
		int upper = bs_upper(0, N - 1, -nums[i]);
		if (lower != -1 && lower != i) {
			if (min_diff > abs(nums[lower] + nums[i])) {
				min_diff = abs(nums[lower] + nums[i]);
				cand[0] = lower; cand[1] = i;
			}
		}
		if (upper != -1 && upper != i) {
			if (min_diff > abs(nums[upper] + nums[i])) {
				min_diff = abs(nums[upper] + nums[i]);
				cand[0] = upper; cand[1] = i;
			}
		}
	}

	if (nums[cand[0]] < nums[cand[1]]) {
		cout << nums[cand[0]] << " " << nums[cand[1]];
	}
	else {
		cout << nums[cand[1]] << " " << nums[cand[0]];
	}
}


int main()
{
	input();
	solve();
	return 0;
}