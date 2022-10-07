#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int green[6][4];
int blue[4][6];

int N; //블록을 놓은 횟수
struct BLOCK { 
	int x, y; 
	int shape; 
};
vector<BLOCK> block;


void input()
{
	cin >> N;
	int x, y, shape;
	for (int i = 0; i < N; i++) {
		cin >> shape >> x >> y;
		block.push_back({ x, y, shape });
	}
}

void attach_blue(BLOCK& b)
{
	switch (b.shape) {
	case 1: {
		for (int y = 0; y < 5; y++) {
			if (blue[b.x][y] == 0) {
				if (blue[b.x][y + 1] == 0) continue;
				blue[b.x][y] = 1;
				return;
			}
		}
		blue[b.x][5] = 1;
		break;
	}
	case 2: {
		for (int y = 0; y < 4; y++) {
			if (blue[b.x][y] == 0 && blue[b.x][y + 1] == 0) {
				if (blue[b.x][y + 2] == 0) continue;
				blue[b.x][y] = 1;
				blue[b.x][y + 1] = 1;
				return;
			}
		}
		blue[b.x][4] = 1;
		blue[b.x][5] = 1;
		break;
	}
	case 3: {
		for (int y = 0; y < 5; y++) {
			if (blue[b.x][y] == 0 && blue[b.x + 1][y] == 0) {
				if (blue[b.x][y + 1] == 0 && blue[b.x + 1][y + 1] == 0) continue;
				blue[b.x][y] = 1;
				blue[b.x + 1][y] = 1;
				return;
			}
		}
		blue[b.x][5] = 1;
		blue[b.x + 1][5] = 1;
		break;
	}
	}
}

void attach_green(BLOCK& b)
{
	switch (b.shape) {
	case 1: {
		for (int x = 0; x < 5; x++) {
			if (green[x][b.y] == 0) {
				if (green[x + 1][b.y] == 0) continue;
				green[x][b.y] = 1;
				return;
			}
		}
		green[5][b.y] = 1;
		break;
	}
	case 2: {
		for (int x = 0; x < 5; x++) {
			if (green[x][b.y] == 0 && green[x][b.y + 1] == 0) {
				if (green[x + 1][b.y] == 0 && green[x + 1][b.y + 1] == 0) continue;
				green[x][b.y] = 1;
				green[x][b.y + 1] = 1;
				return;
			}
		}
		green[5][b.y] = 1;
		green[5][b.y + 1] = 1;
		break;
	}
	case 3: {
		for (int x = 0; x < 4; x++) {
			if (green[x][b.y] == 0 && green[x + 1][b.y] == 0) {
				if (green[x + 2][b.y] == 0) continue;
				green[x][b.y] = 1;
				green[x + 1][b.y] = 1;
				return;
			}
		}
		green[4][b.y] = 1;
		green[5][b.y] = 1;
		break;
	}
	}
}

int chk_score_push_blue()
{
	int ret = 0;
	int push[6] = { 0 };

	for (int y = 5; y >= 0; y--) {
		int cnt = 0;
		for (int x = 0; x < 4; x++) {
			if (blue[x][y]) cnt++;
		}
		if (cnt == 4) {
			ret++;
			push[y] = 1;
		}
	}

	//push가 1인 열들만 밀기 -> 그런 열들은 q에 담지 않음
	if (ret > 0) {
		for (int x = 0; x < 4; x++) {
			queue<int> q;
			for (int y = 5; y >= 0; y--) {
				if (push[y]) {
					blue[x][y] = 0;
					continue;
				}
				q.push(blue[x][y]);
				blue[x][y] = 0;
			}
			for (int y = 5; y >= 0; y--) {
				if (!q.empty()) {
					blue[x][y] = q.front(); q.pop();
				}
				else {
					blue[x][y] = 0;
				}
			}
		}
	}
	return ret;
}

int chk_score_push_green()
{
	int ret = 0;
	int push[6] = { 0 };

	for (int x = 5; x >= 0; x--) {
		int cnt = 0;
		for (int y = 0; y < 4; y++) {
			if (green[x][y]) cnt++;
		}
		if (cnt == 4) {
			ret++;
			push[x] = 1;
		}
	}

	//push가 1인 행들만 밀기 -> 그런 행들은 q에 담지 않음
	if (ret > 0) {
		for (int y = 0; y < 4; y++) {
			queue<int> q;
			for (int x = 5; x >= 0; x--) {
				if (push[x]) {
					green[x][y] = 0;
					continue;
				}
				q.push(green[x][y]);
				green[x][y] = 0;
			}
			for (int x = 5; x >= 0; x--) {
				if (!q.empty()) {
					green[x][y] = q.front(); q.pop();
				}
				else {
					green[x][y] = 0;
				}
			}
		}
	}
	return ret;
}

void chk_lightblue_area()
{
	int move = 0;
	for (int y = 0; y <= 1; y++) {
		for (int x = 0; x < 4; x++) {
			if (blue[x][y]) {
				move++;
				break;
			}
		}
	}

	while (move > 0) {
		move--;
		for (int x = 0; x < 4; x++) {
			for (int y = 4; y >= 0; y--) {
				blue[x][y + 1] = blue[x][y];
			}
			blue[x][0] = 0;
		}
	}
}

void chk_lightgreen_area()
{
	int move = 0;
	for (int x = 0; x <= 1; x++) {
		for (int y = 0; y < 4; y++) {
			if (green[x][y]) {
				move++;
				break;
			}
		}
	}

	while (move > 0) {
		move--;
		for (int y = 0; y < 4; y++) {
			for (int x = 4; x >= 0; x--) {
				green[x + 1][y] = green[x][y];
			}
			green[0][y] = 0;
		}
	}
}

int count_all()
{
	int sum = 0;
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 6; y++) {
			sum += blue[x][y];
		}
	}
	for (int x = 0; x < 6; x++) {
		for (int y = 0; y < 4; y++) {
			sum += green[x][y];
		}
	}
	return sum;
}

void solve()
{
	int ans = 0;
	for (int i = 0; i < N; i++) {
		attach_blue(block[i]);
		attach_green(block[i]);

		ans += chk_score_push_blue();
		ans += chk_score_push_green();

		chk_lightblue_area();
		chk_lightgreen_area();
	}
	
	cout << ans << "\n" << count_all();
}


int main()
{
	input();
	solve();
	return 0;
}