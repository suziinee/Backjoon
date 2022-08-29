#include <iostream>
#include <queue>

int n;
int arr[20][20];
int time; int size; int tmp_eat;
int input_fish; int eat_fish;
class AXIS 
{
public:
	int x; int y;
};
AXIS shark;


void input()
{
	std::cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cin >> arr[i][j];
			if (arr[i][j] == 9) {
				shark.x = j; shark.y = i;
			}
			else if (arr[i][j] != 0) input_fish++;
		}
	}
}


int dx[4] = { 0, -1, 1, 0 };
int dy[4] = { -1, 0, 0, 1 };
int bfs(AXIS now)
{
	std::queue<AXIS> q;
	q.push(now);

	int visited[20][20];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = 1;
		}
	}

	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue; //범위를 벗어나면 continue
			if (arr[ny][nx] > size) {
				visited[ny][nx] = 0;
				continue;
			} //나보다 큰 물고기가 있으면 못지나감
			if (visited[ny][nx] == 1) {
				visited[ny][nx] = visited[y][x] + 1;
				AXIS next = { nx, ny };
				q.push(next);
			}
			if (arr[ny][nx] != 0 && arr[ny][nx] < size) {
				shark.x = nx; shark.y = ny;
				arr[ny][nx] = 0;
				return visited[ny][nx] - 1;
			} //유효한 물고기가 있으면 함수 탈출
		}
	}
    return 0;
}


bool is_fish() //먹을 물고기가 남아있으면 true, 없으면 false
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j] != 0 && arr[i][j] < size) {
				return true;
			}
		}
	}
	return false;
}


void solve()
{
	arr[shark.y][shark.x] = 0;
	size = 2;

	while (1) {
		if (input_fish == eat_fish) return;
		bool boo = is_fish();
		if (!boo) return;

		int b = bfs(shark);
		time += b; tmp_eat++; eat_fish++;
		if (tmp_eat == size) {
			tmp_eat = 0;
			size++;
		}
	}
}


int main()
{
	input();
	solve();
	std::cout << time;
    return 0;
}