#include <stdio.h>

int n;
int k;
int coin[10 + 2];
int ans;

void func(void)
{
	int idx = n - 1;
	for (int i = 0; i < n; i++) {
		if (k < coin[i]) {
			idx = i - 1;
			break;
		}
	}

	for (int i = idx; i >= 0; i--) {
		ans += (k / coin[i]);
		k %= coin[i];
	}
}


int main(void)
{
	scanf("%d %d", &n, &k);

	for (int i = 0; i < n; i++) {
		scanf("%d", &coin[i]);
	}

	func();
	printf("%d", ans);
	return 0;
}