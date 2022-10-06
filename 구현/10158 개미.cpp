#include <iostream>
using namespace std;

int W, H;
int ax, ay;
int T;


void input()
{
	cin >> W >> H;
	cin >> ax >> ay;
	cin >> T;
}

void solve()
{
	ax += T;
	ay += T;

	if (ax > W) {
		int diff = ax - W;
		int rep = diff / W;
		int rem = diff % W;
		if (rep % 2) {
			ax = rem;
		}
		else {
			ax = W - rem;
		}
	}
	if (ay > H) {
		int diff = ay - H;
		int rep = diff / H;
		int rem = diff % H;
		if (rep % 2) {
			ay = rem;
		}
		else {
			ay = H - rem;
		}
	}

	cout << ax << " " << ay;
}


int main()
{
	input();
	solve();
	return 0;
}