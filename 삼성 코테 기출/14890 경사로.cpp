#include <iostream>
using namespace std;

#define MAXN 100
int N, L;
int map1[MAXN][MAXN];
int map2[MAXN][MAXN]; //map1을 90도 회전


void input()
{
	cin >> N >> L;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map1[y][x];
		}
	}
	int nx = 0;
	for (int y = 0; y < N; y++) {
		int ny = N - 1;
		for (int x = 0; x < N; x++) {
			map2[y][x] = map1[ny][nx];
			ny--;
		}
		nx++;
	}
}

int check(int(*arr))
{
	int tmp[MAXN] = { 0, }; //유효거리 기록
	tmp[0] = 1;
	for (int i = 1; i < N; i++) {
		if (arr[i - 1] < arr[i]) { 
			if (abs(arr[i - 1] - arr[i]) > 1) return 0;
			if (tmp[i - 1] < L) return 0; //i-1번째까지 유효거리가 L 이상이어야함
			tmp[i] = 1;
		}
		else if (arr[i - 1] == arr[i]) {
			tmp[i] = tmp[i - 1] + 1;
		}
		else if (arr[i - 1] > arr[i]) {
			if (abs(arr[i - 1] - arr[i]) > 1) return 0;
			if (tmp[i - 1] < 0) return 0; //i번째부터 경사로를 쌓으면 되기 때문에 i-1이 0인건 상관 없음**
			tmp[i] = -(L - 1);
		}
	}
	if (tmp[N - 1] < 0) return 0; //마지막에 경사로를 쌓는 중이면 안됨
	return 1;
}

void solve()
{
	int ans = 0;
	for (int i = 0; i < N; i++) {
		ans += check(map1[i]);
		ans += check(map2[i]);
	}
	cout << ans;
}


int main()
{
	input();
	solve();
	return 0;
}