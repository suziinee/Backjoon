#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;

int r, c, k;
int A[100][100];
int max_row; int max_col;


void input()
{
	cin >> r >> c >> k;
	r--; c--;
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			cin >> A[y][x];
		}
	}
	max_row = 3;
	max_col = 3;
}

bool compare(pair<int, int>& p1, pair<int, int>& p2)
{
	if (p1.second == p2.second) return p1.first < p2.first;
	return p1.second < p2.second;
}

int sort_arr(int* arr, int n, int flag) //정렬해서 넣어주고 해당 row, col cnt 리턴
{
	unordered_map<int, int> ht; //숫자, 카운트 개수
	for (int i = 0; i < 100; i++) {
		if (arr[i] == 0) continue;
		if (ht.find(arr[i]) == ht.end()) {
			ht.insert({ arr[i], 1 });
		}
		else {
			ht[arr[i]] += 1;
		}
	}

	vector<pair<int, int>> vec(ht.begin(), ht.end());
	sort(vec.begin(), vec.end(), compare);

	if (flag) {
		//n번 col clear
		for (int row = 0; row < 100; row++) A[row][n] = 0;

		//col를 정렬해서 n번 col에 넣기
		int row_cnt = 0;
		for (auto v : vec) {
			A[row_cnt++][n] = v.first;
			A[row_cnt++][n] = v.second;
			if (row_cnt >= 100) break;
		}
		return row_cnt;
	}
	else { 
		//n번 row clear
		for (int col = 0; col < 100; col++) A[n][col] = 0;

		//row를 정렬해서 n번 row에 넣기
		int col_cnt = 0;
		for (auto v : vec) {
			A[n][col_cnt++] = v.first;
			A[n][col_cnt++] = v.second;
			if (col_cnt >= 100) break;
		}
		return col_cnt;
	}
}

void solve()
{
	if (A[r][c] == k) {
		cout << 0;
		return;
	}

	for (int t = 1; t <= 100; t++) {
		if (max_row >= max_col) { //모든 행 졍렬 -> max_col 갱신
			int new_maxcol = 0;
			for (int row = 0; row < 100; row++) {
				int ret = sort_arr(A[row], row, 0);
				new_maxcol = max(ret, new_maxcol);
			}
			max_col = new_maxcol;
		}
		else { //모든 열 정렬 -> max_row 갱신
			int new_maxrow = 0;
			for (int col = 0; col < 100; col++) {
				int tmp[100] = { 0 };
				for (int row = 0; row < 100; row++) {
					tmp[row] = A[row][col];
				}
				int ret = sort_arr(tmp, col, 1);
				new_maxrow = max(ret, new_maxrow);
			}
			max_row = new_maxrow;
		}

		if (A[r][c] == k) {
			cout << t;
			return;
		}
	}
	cout << -1;
}


int main()
{
	input();
	solve();
	return 0;
}