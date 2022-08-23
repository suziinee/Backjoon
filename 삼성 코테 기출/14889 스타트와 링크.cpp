#include <iostream>
#include <cstdlib>

int n;
int arr[20][20];
int res[10];
int min = 0x7fffffff;

void input()
{
	std::cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cin >> arr[i][j];
		}
	}
}

int in_res(const int& j)
{
	for (int i = 0; i < n/2; i++) {
		if (res[i] == j) return 1;
	}
	return 0;
}

int start() //res에 있는 것들의 합
{
	int sum = 0; 
	for (int i = 0; i < n / 2; i++) { //res[i]
		for (int j = 0; j < n; j++) {
			if (res[i] != j && in_res(j)) sum += arr[res[i]][j];
		}
	}
	return sum;
}

int link()
{
	int sum = 0;
	for (int i = 0; i < n; i++) { 
		for (int j = 0; j < n; j++) {
			if (i != j && !in_res(i) && !in_res(j)) sum += arr[i][j];
		}
	}
	return sum;
}

void dfs(const int& L, const int& BeginWith)
{
	if (L == n/2) {
		int s = start();
		int l = link();
		int tmp = s > l ? s - l : l - s;
		if (tmp < min) min = tmp;
		return;
	}
	else {
		for (int i = BeginWith; i < n; i++) {
			res[L] = i;
			dfs(L + 1, i + 1);
		}
	}
}


int main()
{
	input();
	dfs(0, 0);
	std::cout << min << std::endl;
	return 0;
}
