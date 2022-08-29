#include <iostream>
#include <queue>
using namespace std;

int n;
int arr[20][20];
int sz; int tmp_eat;
class AXIS
{
public:
	int x; int y; int dist;
};
AXIS shark;


void input()
{
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 9) {
				shark.x = j; shark.y = i; shark.dist = 0;
				arr[i][j] = 0; sz = 2;
			}
		}
	}
}


const int dx[4] = { 0, 0, -1, 1 };
const int dy[4] = { -1, 1, 0, 0 };
int bfs(AXIS start) //최단거리에 있는 물고기 잡아먹기 
{
	int flag = 0;

	bool visited[20][20] = { false, };
	queue<AXIS> q;
	q.push(start);
	visited[start.y][start.x] = true;

	//잡아먹을 물고기 후보
	AXIS candi;
	candi.y = 20; candi.x = 20; candi.dist = -1;

	while (!q.empty()) {
		AXIS tmp = q.front(); q.pop();

		//candi가 초기값이 아니고 최소거리를 넘어섰다면 이제 bfs를 돌 필요가 없음
		if (candi.dist != -1 && tmp.dist > candi.dist) {
			shark = candi;
			arr[shark.y][shark.x] = 0;
			return flag;
		}

		if (arr[tmp.y][tmp.x] < sz&&arr[tmp.y][tmp.x] != 0) { //잡아먹을 수 있음 -> update
			flag = 1;
			if (tmp.y < candi.y || (tmp.y == candi.y&&tmp.x < candi.x)) {
				candi = tmp;
			}
		}

		for (int i = 0; i < 4; i++) { //방문 안했고 갈 수 있는 길이라면 queue에 넣기
			AXIS next;
			next.x = tmp.x + dx[i]; 
			next.y = tmp.y + dy[i];
			next.dist = tmp.dist + 1;

			if (next.y < 0 || next.x < 0 || next.y >= n || next.x >= n) continue;
			if (visited[next.y][next.x] == false && arr[next.y][next.x] <= sz) { 
				visited[next.y][next.x] = true;
				q.push(next);
			}
		}
	}

	if (flag == 1) {
		shark = candi;
		arr[shark.y][shark.x] = 0;
	}
	return flag;
}


void solve()
{
	while (true) {
		int flag = bfs(shark);
		if (flag == 0) return;
		tmp_eat++;
		if (tmp_eat == sz) {
			tmp_eat = 0;
			sz++;
		}
	}
}


int main()
{
	input();
	solve();
	cout << shark.dist;
	return 0;
}
