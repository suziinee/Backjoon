#include <iostream>
#include <unordered_map>
using namespace std;

struct NODE { int l; int r; };
unordered_map<int, NODE> bst;
int root = -1;


void insert_node(int d)
{
	if (root == -1) {
		bst.insert({ d, {-1, -1} });
		root = d;
		return;
	}

	int n = root; //현재 노드
	auto it = bst.find(root); //현재 노드의 정보를 가진 iter
	for (;;) {
		if (d < n) { //왼쪽에 연결
			if (it->second.l == -1) { //현재 노드의 왼쪽 자식이 없음
				//d를 왼쪽 자식에 연결
				it->second.l = d;
				//d 노드를 bst에 추가
				bst.insert({ d, {-1, -1} });
				break;
			}
			else { //현재 노드의 왼쪽 자식이 있음
				n = it->second.l;
				it = bst.find(n);
			}
		}
		else { //오른쪽 연결
			if (it->second.r == -1) {
				it->second.r = d;
				bst.insert({ d, {-1, -1} });
				break;
			}
			else {
				n = it->second.r;
				it = bst.find(n);
			}
		}
	}
}

void input()
{
	int n;
	while (cin >> n) {
		insert_node(n);
	}
}

void post(int n)
{
	if (n == -1) return;
	post(bst[n].l);
	post(bst[n].r);
	cout << n << "\n";
}

void solve()
{
	post(root);
}


int main()
{
	input();
	solve();
	return 0;
}