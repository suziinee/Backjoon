#include <iostream>
#include <unordered_map>
using namespace std;

int N;
struct NODE { int l; int r; };
unordered_map<char, NODE> ht;


void input()
{
	cin >> N;

	char p, c1, c2;
	for (int i = 0; i < N; i++) {
		cin >> p >> c1 >> c2;
		ht.insert({ p, {c1, c2} });
	}
}

void pre(char c)
{
	if (c == '.') return;

	cout << c;
	pre(ht[c].l);
	pre(ht[c].r);
}

void in(char c)
{
	if (c == '.') return;

	in(ht[c].l);
	cout << c;
	in(ht[c].r);
}

void post(char c)
{
	if (c == '.') return;
	
	post(ht[c].l);
	post(ht[c].r);
	cout << c;
}

void solve()
{
	pre('A');
	cout << "\n";
	in('A');
	cout << "\n";
	post('A');
	cout << "\n";
}


int main()
{
	input();
	solve();
	return 0;
}