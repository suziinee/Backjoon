#include <stdio.h>

//분해합 구하는 함수
int func(int n)
{
	int sum = n;
	while (n) {
		sum += (n % 10);
		n /= 10;
	}
	return sum;
}

int main(void)
{
	int n;
	scanf("%d", &n);

	int min = 2000000; int flag = 0;
	for (int i = 1; i <= n; i++) {
		//printf("%d %d\n", i, func(i));
		if (func(i) == n) {
			flag += 1;
			if (i < min) min = i;
		}
	}

	if (flag == 0) printf("%d", 0);
	else printf("%d", min);
	return 0;
}