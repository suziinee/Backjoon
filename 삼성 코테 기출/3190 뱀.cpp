#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, k, l;
struct AXIS { int y; int x; int d; };
struct MOVE { int t; int rot; }; //왼쪽은 0, 오른쪽은 1
vector<MOVE> mov;
int map[101][101]; //사과는 2, 뱀의 몸은 1
int ans;


void input()
{
	cin >> n >> k;
	for (int i = 0; i < k; i++) {
		int x, y;
		cin >> y >> x;
		map[y][x] = 2;
	}
	cin >> l;
	for (int i = 0; i < l; i++) {
		int t; char c; 
		cin >> t >> c;
		if (c == 'L') {
			mov.push_back({ t, 0 });
		}
		else {
			mov.push_back({ t, 1 });
		}
	}
	
	//계속 돌게 하기 위해 마지막 mov 추가
	mov.push_back({ 0x7fffffff, 2 });
	l += 1;
}


void output()
{
	cout << ans;
}


const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { -1, 0, 1, 0 };
void solve()
{
	queue<AXIS> q;
	AXIS head = { 1, 1, 1 };
	AXIS tail = { 1, 1, 1 };
	map[1][1] = 1;

	for (int i = 0; i < l; i++) { //모든 이동경로에 대해 탐색
		
		while (ans < mov[i].t) {
			//0. 이동 및 시간 증가
			int nx = head.x + dx[head.d];
			int ny = head.y + dy[head.d];
			ans++;

			//0-0. 범위를 벗어날 경우 게임 종료
			if (nx<1 || ny<1 || nx>n || ny>n) return;
			//0-1. 자기 자신과 부딪힐 경우 게임 종료
			if (map[ny][nx] == 1) return;

			//0-2. 종료 조건을 통과했다면 head 갱신
			head = { ny, nx, head.d };
			
			//1. 사과가 있는지 확인
			if (map[ny][nx] == 2) {
				//1-1. 사과를 먹음
				map[ny][nx] = 1;
				//1-1-0. head 갱신, tail은 그대로
				continue;
			}
			else {
				//1-2. 사과가 없다면 head가 머리 확장 + 꼬리 지우기
				map[ny][nx] = 1;
				map[tail.y][tail.x] = 0;
				
				//1-3. 꼬리가 자신의 방향으로 이동
				//1-3-0. 이때 꼬리가 방향을 전환해야 할지 판단
				if (!q.empty()) {
					AXIS tmp = q.front();
					if (tail.x == tmp.x&&tail.y == tmp.y) { //1-3-1. tail 방향 전환 후 이동, 갱신
						tail.d = tmp.d;
						tail.x = tail.x + dx[tail.d];
						tail.y = tail.y + dy[tail.d];
						q.pop();
						continue;
					}
				}
				//1-3-2. 방향 전환하지 않고 이동, 갱신
				tail.x = tail.x + dx[tail.d];
				tail.y = tail.y + dy[tail.d];
			}
		}

		//2. head 방향 전환
		if (mov[i].rot == 0) { //2-1-0. 왼쪽 회전
			switch (head.d) {
				case 0: head.d = 3; break;
				case 1: head.d = 0; break;
				case 2: head.d = 1; break;
				case 3: head.d = 2; break;
			}
		}
		else { //2-1-1. 오른쪽 회전
			switch (head.d) {
				case 0: head.d = 1; break;
				case 1: head.d = 2; break;
				case 2: head.d = 3; break;
				case 3: head.d = 0; break;
			}
		}

		//3. head가 방향 전환된 곳을 queue에 저장
		q.push({ head.y, head.x, head.d }); //3-1. 이때 dir은 전환된 다음 방향
	}
}


int main()
{
	input();
	solve();
	output();
	return 0;
}