#include <stdio.h>

typedef struct _st {
	int x; int y;
	int dir;
} AXIS;
AXIS head = { 1, 1, 1 };
AXIS tail = { 1, 1, 1 };
typedef struct __st {
	int t; char d;
} DIR;

int n, k, l;
AXIS apple[100 + 10];
DIR dir[100 + 10];
int body[100 + 10][100 + 10];

int time = 1; //현재까지 누적 시간
int head_cur = 1; //0 1 2 3 =  상 우 하 좌
int tail_cur = 1;
AXIS head_change[100 + 10]; int head_change_n = 0;
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { -1, 0, 1, 0 };

void input(void)
{
	scanf("%d %d", &n, &k);
	for (int i = 0; i < k; i++) {
		scanf("%d %d", &apple[i].y, &apple[i].x);
	}
	scanf("%d", &l);
	for (int i = 0; i < l; i++) {
		scanf(" %d %c", &dir[i].t, &dir[i].d);
	}
}

int is_apple(int y, int x)
{
	for (int i = 0; i < k; i++) {
		if (apple[i].y == y && apple[i].x == x) {
			apple[i].y = 0;
			apple[i].x = 0;
			return 1;
		}
	}
	return 0;
}

int dir_change(int now, char next)
{
	if (next == 'L') {
		switch (now) {
		case 1: return 0;
		case 2: return 1;
		case 3: return 2;
		case 0: return 3;
		}
	}
	else if (next == 'D') {
		switch (now) {
		case 1: return 2;
		case 2: return 3;
		case 3: return 0;
		case 0: return 1;
		}
	}
}

AXIS popleft(void) //head_change의 0번 요소를 꺼내줌
{
	AXIS ret;
	ret.x = head_change[0].x; ret.y = head_change[0].y; ret.dir = head_change[0].dir;
	return ret;
}

void push(AXIS hc, int idx)
{
	head_change[idx].x = hc.x;
	head_change[idx].y = hc.y;
	head_change[idx].dir = hc.dir;
}

void slide(void) //1번부터 n번까지 앞으로 당김
{
	for (int i = 1; i <= head_change_n; i++) {
		head_change[i - 1] = head_change[i];
	}
	head_change[head_change_n].x = 0;
	head_change[head_change_n].y = 0;
	head_change[head_change_n].dir = 0;
}

int move(int t)
{
	head.x = head.x + dx[head_cur];
	head.y = head.y + dy[head_cur];

	if (head.x<1 || head.y<1 || head.x>n || head.y>n) {
		return t;
	}
	if (body[head.y][head.x] == 1) {
		return t;
	}

	body[head.y][head.x] = 1;

	if (is_apple(head.y, head.x) == 0) {
		body[tail.y][tail.x] = 0;

		AXIS hc = popleft();
		if (hc.y == tail.y&&hc.x == tail.x) {
			tail_cur = hc.dir;
			head_change_n--;
			slide();
		}
		else {
			push(hc, 0);
		}
		tail.x = tail.x + dx[tail_cur];
		tail.y = tail.y + dy[tail_cur];
	}
	return -1;
}


int solve(void)
{
	body[1][1] = 1;

	for (int i = 0; i < l; i++) { //모든 dir에 대해서
		for (int t = time; t <= dir[i].t; t++) {
			int ret = move(t);
			if (ret != -1) return ret;
		}
		time = dir[i].t + 1;

		head_cur = dir_change(head_cur, dir[i].d);

		AXIS hc;
		hc.x = head.x; hc.y = head.y; hc.dir = head_cur;
		push(hc, head_change_n);
		head_change_n++;
	}

	for (int t = time; ; t++) {
		int ret = move(t);
		if (ret != -1) return ret;
	}
}


int main(void)
{
	input();
	int ans = solve();
	printf("%d", ans);
	return 0;
}