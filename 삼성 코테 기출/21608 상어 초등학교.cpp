#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

#define MAXN 20
int N;
int map[MAXN][MAXN]; //앉은 학생의 번호 기록

struct STUDENT {
	int n;
	int pri[4];
};
vector<STUDENT> student;
unordered_map<int, STUDENT*> ht;

struct STATUS {
	int fav; //인접한 칸 중 좋아하는 학생이 앉은 칸
	int blk; //인접한 칸 중 비어있는 칸
	int y, x;
	bool operator<(const STATUS& s) const {
		if (fav == s.fav) {
			if (blk == s.blk) {
				if (y == s.y) {
					return x < s.x;
				}
				return y < s.y;
			}
			return blk > s.blk;
		}
		return fav > s.fav;
	}
};


void input()
{
	cin >> N;
	int n, p1, p2, p3, p4;
	for (int i = 0; i < N * N; i++) {
		cin >> n >> p1 >> p2 >> p3 >> p4;
		student.push_back({ n, {p1, p2, p3, p4} });
	}
	for (int i = 0; i < N * N; i++) {
		ht.insert({ student[i].n, &student[i] });
	}
}

void assign(STUDENT& s)
{
	static int dx[] = { 0, 1, 0, -1 };
	static int dy[] = { -1, 0, 1, 0 };

	vector<STATUS> st;

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			if (map[y][x]) continue;
			int fav = 0; int blk = 0;
			for (int d = 0; d < 4; d++) {
				int nx = x + dx[d];
				int ny = y + dy[d];
				if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
				if (map[ny][nx] == 0) blk++;
				for (int n : s.pri) {
					if (map[ny][nx] == n) { fav++; break; }
				}
			}
			st.push_back({ fav, blk, y, x });
		}
	}
	
	sort(st.begin(), st.end());
	map[st[0].y][st[0].x] = s.n;
}

int get_score()
{
	static int dx[] = { 0, 1, 0, -1 };
	static int dy[] = { -1, 0, 1, 0 };

	int sum = 0;
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			int cnt = 0;
			for (int d = 0; d < 4; d++) {
				int nx = x + dx[d];
				int ny = y + dy[d];
				if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
				for (int n : ht[map[y][x]] -> pri) {
					if (map[ny][nx] == n) { cnt++; break; }
				}
			}
			switch (cnt) {
			case 0: break;
			case 1: sum += 1; break;
			case 2: sum += 10; break;
			case 3: sum += 100; break;
			case 4: sum += 1000; break;
			}
		}
	}
	return sum;
}

void solve()
{
	map[1][1] = student[0].n;
	for (int i = 1; i < N * N; i++) {
		assign(student[i]);
	}
	cout << get_score();
}


int main()
{
	input();
	solve();
	return 0;
}