#include <iostream>
#include <vector>
using namespace std;

#define MAXN 499
int N;
int map[MAXN][MAXN];
int chk[MAXN][MAXN];
int ans;


void input()
{
	cin >> N;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cin >> map[y][x];
		}
	}
}


//(y, x)에서 (ny, nx)로 d 방향으로 토네이도가 불었다
void spread(int y, int x, int ny, int nx, int d)
{
	static int dx[] = { -1, 0, 1, 0 };
	static int dy[] = { 0, 1, 0, -1 };

	switch (d) {
	case 0: {
		int tmp = map[ny][nx];
		map[ny][nx] = 0;
		int sum = 0;
		//1%
		if (y - 1 >= 0) map[y - 1][x] += (int)(tmp * 0.01);
		else ans += (int)(tmp * 0.01);
		if (y + 1 < N) map[y + 1][x] += (int)(tmp * 0.01);
		else ans += (int)(tmp * 0.01);
		sum += (int)(tmp * 0.01) * 2;
		//7%
		if (ny - 1 >= 0) map[ny - 1][nx] += (int)(tmp * 0.07);
		else ans += (int)(tmp * 0.07);
		if (ny + 1 < N) map[ny + 1][nx] += (int)(tmp * 0.07);
		else ans += (int)(tmp * 0.07);
		sum += (int)(tmp * 0.07) * 2;
		//2%
		if (ny - 2 >= 0) map[ny - 2][nx] += (int)(tmp * 0.02);
		else ans += (int)(tmp * 0.02);
		if (ny + 2 < N) map[ny + 2][nx] += (int)(tmp * 0.02);
		else ans += (int)(tmp * 0.02);
		sum += (int)(tmp * 0.02) * 2;
		//10%
		if (ny - 1 >= 0 && nx - 1 >= 0) map[ny - 1][nx - 1] += (int)(tmp * 0.1);
		else ans += (int)(tmp * 0.1);
		if (ny + 1 < N && nx - 1 >= 0) map[ny + 1][nx - 1] += (int)(tmp * 0.1);
		else ans += (int)(tmp * 0.1);
		sum += (int)(tmp * 0.1) * 2;
		//5%
		if (nx - 2 >= 0) map[ny][nx - 2] += (int)(tmp * 0.05);
		else ans += (int)(tmp * 0.05);
		sum += (int)(tmp * 0.05);
		//a
		if (nx - 1 >= 0) map[ny][nx - 1] += (tmp - sum);
		else ans += (tmp - sum);
	}
	case 1: {
		int tmp = map[ny][nx];
		map[ny][nx] = 0;
		int sum = 0;
		//1%
		if (x - 1 >= 0)map[y][x - 1] += (int)(tmp * 0.01);
		else ans += (int)(tmp * 0.01);
		if (x + 1 < N) map[y][x + 1] += (int)(tmp * 0.01);
		else ans += (int)(tmp * 0.01);
		sum += (int)(tmp * 0.01) * 2;
		//7%
		if (nx - 1 >= 0) map[ny][nx - 1] += (int)(tmp * 0.07);
		else ans += (int)(tmp * 0.07);
		if (nx + 1 < N) map[ny][nx + 1] += (int)(tmp * 0.07);
		else ans += (int)(tmp * 0.07);
		sum += (int)(tmp * 0.07) * 2;
		//2%
		if (nx - 2 >= 0) map[ny][nx - 2] += (int)(tmp * 0.02);
		else ans += (int)(tmp * 0.02);
		if (nx + 2 < N) map[ny][nx + 2] += (int)(tmp * 0.02);
		else ans += (int)(tmp * 0.02);
		sum += (int)(tmp * 0.02) * 2;
		//10%
		if (ny + 1 < N && nx - 1 >= 0) map[ny + 1][nx - 1] += (int)(tmp * 0.1);
		else ans += (int)(tmp * 0.1);
		if (ny + 1 < N && nx + 1 < N) map[ny + 1][nx + 1] += (int)(tmp * 0.1);
		else ans += (int)(tmp * 0.1);
		sum += (int)(tmp * 0.1) * 2;
		//5%
		if (ny + 2 < N) map[ny + 2][nx] += (int)(tmp * 0.05);
		else ans += (int)(tmp * 0.05);
		sum += (int)(tmp * 0.05);
		//a
		if (ny + 1 < N) map[ny + 1][nx] += (tmp - sum);
		else ans += (tmp - sum);
	}
	case 2: {
		int tmp = map[ny][nx];
		map[ny][nx] = 0;
		int sum = 0;
		//1%
		if (y - 1 >= 0) map[y - 1][x] += (int)(tmp * 0.01);
		else ans += (int)(tmp * 0.01);
		if (y + 1 < N) map[y + 1][x] += (int)(tmp * 0.01);
		else ans += (int)(tmp * 0.01);
		sum += (int)(tmp * 0.01) * 2;
		//7%
		if (ny - 1 >= 0) map[ny - 1][nx] += (int)(tmp * 0.07);
		else ans += (int)(tmp * 0.07);
		if (ny + 1 < N) map[ny + 1][nx] += (int)(tmp * 0.07);
		else ans += (int)(tmp * 0.07);
		sum += (int)(tmp * 0.07) * 2;
		//2%
		if (ny - 2 >= 0) map[ny - 2][nx] += (int)(tmp * 0.02);
		else ans += (int)(tmp * 0.02);
		if (ny + 2 < N) map[ny + 2][nx] += (int)(tmp * 0.02);
		else ans += (int)(tmp * 0.02);
		sum += (int)(tmp * 0.02) * 2;
		//10%
		if (ny - 1 >= 0 && nx + 1 < N) map[ny - 1][nx + 1] += (int)(tmp * 0.1);
		else ans += (int)(tmp * 0.1);
		if (ny + 1 < N && nx + 1 < N) map[ny + 1][nx + 1] += (int)(tmp * 0.1);
		else ans += (int)(tmp * 0.1);
		sum += (int)(tmp * 0.1) * 2;
		//5%
		if (nx + 2 < N) map[ny][nx + 2] += (int)(tmp * 0.05);
		else ans += (int)(tmp * 0.05);
		sum += (int)(tmp * 0.05);
		//a
		if (nx + 1 < N) map[ny][nx + 1] += (tmp - sum);
		else ans += (tmp - sum);
	}
	case 3: {
		int tmp = map[ny][nx];
		map[ny][nx] = 0;
		int sum = 0;
		//1%
		if (x - 1 >= 0)map[y][x - 1] += (int)(tmp * 0.01);
		else ans += (int)(tmp * 0.01);
		if (x + 1 < N) map[y][x + 1] += (int)(tmp * 0.01);
		else ans += (int)(tmp * 0.01);
		sum += (int)(tmp * 0.01) * 2;
		//7%
		if (nx - 1 >= 0) map[ny][nx - 1] += (int)(tmp * 0.07);
		else ans += (int)(tmp * 0.07);
		if (nx + 1 < N) map[ny][nx + 1] += (int)(tmp * 0.07);
		else ans += (int)(tmp * 0.07);
		sum += (int)(tmp * 0.07) * 2;
		//2%
		if (nx - 2 >= 0) map[ny][nx - 2] += (int)(tmp * 0.02);
		else ans += (int)(tmp * 0.02);
		if (nx + 2 < N) map[ny][nx + 2] += (int)(tmp * 0.02);
		else ans += (int)(tmp * 0.02);
		sum += (int)(tmp * 0.02) * 2;
		//10%
		if (ny - 1 >= 0 && nx - 1 >= 0) map[ny - 1][nx - 1] += (int)(tmp * 0.1);
		else ans += (int)(tmp * 0.1);
		if (ny - 1 >= 0 && nx + 1 < N) map[ny - 1][nx + 1] += (int)(tmp * 0.1);
		else ans += (int)(tmp * 0.1);
		sum += (int)(tmp * 0.1) * 2;
		//5%
		if (ny - 2 >= 0) map[ny - 2][nx] += (int)(tmp * 0.05);
		else ans += (int)(tmp * 0.05);
		sum += (int)(tmp * 0.05);
		//a
		if (ny - 1 >= 0) map[ny - 1][nx] += (tmp - sum);
		else ans += (tmp - sum);
	}
	}
}


void solve()
{
	static int dx[] = { -1, 0, 1, 0 };
	static int dy[] = { 0, 1, 0, -1 };
	int x = N / 2;
	int y = N / 2;
	int d = 3;
	chk[y][x] = 1;

	for (int i = 0; i < N * N - 1; i++) {
		int nd = (d + 1) % 4;
		int nx = x + dx[nd];
		int ny = y + dy[nd];
		if (chk[ny][nx]) { //방향 유지
			nx = x + dx[d];
			ny = y + dy[d];
			spread(y, x, ny, nx, d);
			chk[ny][nx] = 1;
			x = nx; y = ny; 
		}
		else { //방향 변경 가능
			spread(y, x, ny, nx, nd);
			chk[ny][nx] = 1;
			x = nx; y = ny; d = nd;
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