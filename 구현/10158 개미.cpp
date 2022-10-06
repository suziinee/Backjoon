#include <iostream>
using namespace std;

int W, H;
int ax, ay, ad;
int T;


void input()
{
	cin >> W >> H;
	cin >> ax >> ay;
	cin >> T;
	ad = 0;
}

void move() //(ax, ay)에서 ad 방향으로 한번의 움직임
{
	static int dx[] = { 1, -1, -1, 1 };
	static int dy[] = { 1, 1, -1, -1 };

	int nx = ax + dx[ad];
	int ny = ay + dy[ad];
	if (nx<0 || ny<0 || nx>W || ny>H) {
		if (ad == 0) {
			if (ax == W && ay == H) { //꼭짓점
				ad = 2;
			}
			else if (ax == W && ay != H) {
				ad = 1;
			}
			else if (ax != W && ay == H) {
				ad = 3;
			}
		}
		else if (ad == 1) {
			if (ax == 0 && ay == H) { //꼭짓점
				ad = 3;
			}
			else if (ax == 0 && ay != H) {
				ad = 0;
			}
			else if (ax != 0 && ay == H) {
				ad = 2;
			}
		}
		else if (ad == 2) {
			if (ax == 0 && ay == 0) {
				ad = 0;
			}
			else if (ax != 0 && ay == 0) {
				ad = 1;
			}
			else if (ax == 0 && ay != 0) {
				ad = 3;
			}
		}
		else if (ad == 3) {
			if (ax == W && ay == 0) {
				ad = 1;
			}
			else if (ax == W && ay != 0) {
				ad = 2;
			}
			else if (ax != W && ay == 0) {
				ad = 0;
			}
		}
		nx = ax + dx[ad];
		ny = ay + dy[ad];
	}
	ax = nx;
	ay = ny;
}

void solve()
{
	int time = 0;

	while (time < T) {
		switch (ad) {
		case 0: {
			if (W - ax < H - ay) {
				time += W - ax;
				ay += W - ax;
				ax = W;
				ad = 1;
			}
			else if (W - ax > H - ay) {
				time += H - ay;
				ax += H - ay;
				ay = H;
				ad = 3;
			}
			else if (W - ax == H - ay) {
				time += H - ay;
				ax = W;
				ay = H;
				ad = 2;
			}
			break;
		}
		case 1: {
			if (ax < H - ay) {
				time += ax;
				ay += ax;
				ax = 0;
				ad = 0;
			}
			else if (ax > H - ay) {
				time += H - ay;
				ax -= H - ay;
				ay = H;
				ad = 2;
			}
			else if (ax == H - ay) {
				time += H - ay;
				ax = 0;
				ay = H;
				ad = 3;
			}
			break;
		}
		case 2: {
			if (ax < ay) {
				time += ax;
				ay -= ax;
				ax = 0;
				ad = 3;
			}
			else if (ax > ay) {
				time += ay;
				ax -= ay;
				ay = 0;
				ad = 1;
			}
			else if (ax == ay) {
				time += ax;
				ax = 0;
				ay = 0;
				ad = 0;
			}
			break;
		}
		case 3: {
			if (W - ax < ay) {
				time += W - ax;
				ay -= W - ax;
				ax = W;
				ad = 2;
			}
			else if (W - ax > ay) {
				time += ay;
				ax += ay;
				ay = 0;
				ad = 0;
			}
			else if (W - ax == ay) {
				time += ay;
				ax = W;
				ay = 0;
				ad = 1;
			}
			break;
		}
		}
	}

	if (time == T) {
		cout << ax << " " << ay;
	}
	else { //T-time만큼 다시 back
		switch (ad) {
			case 0: ad = 2; break;
			case 1: ad = 3; break;
			case 2: ad = 0; break;
			case 3: ad = 1; break;
		}
		for (int t = 0; t < time - T; t++) {
			move();
		}
		cout << ax << " " << ay;
	}
}


int main()
{
	input();
	solve();
	return 0;
}