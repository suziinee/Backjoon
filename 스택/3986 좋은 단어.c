#include <stdio.h>

int n;
int ans;

int is_good(char *ch)
{
	char stack[10000 + 10] = { '\0' };
	int i = 0;
	while (*ch) {
		char tmp = *ch++;
		if (i == 0) {
			stack[i++] = tmp;
			continue;
		}
		if (stack[i - 1] == tmp) {
			stack[--i] = '\0';
		}
		else {
			stack[i++] = tmp;
		}
	}
	if (i == 0) return 1;
	else return 0;
}

int main(void)
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		char ch[100000 + 10] = { '\0' };
		scanf(" %s", ch);
		ans += is_good(ch);
	}
	printf("%d", ans);
	return 0;
}