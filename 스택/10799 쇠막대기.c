#include <stdio.h>
#include <string.h>

char init[100000 + 10];
char ch[100000 + 10];
int razer[100000]; int r;
int ans;

void change_razer(void)
{
	int n = strlen(init);
	for (int i = 0; i < n - 1; i++) {
		if (init[i] == '('&&init[i + 1] == ')') {
			init[i] = '0'; init[i + 1] = '0';
		}
	}
	printf("init : %s\n", init);

	int i = 0; int j = 0;
	while (init[i]) {
		if (init[i] == '0') {
			razer[r++] = j; //레이저 개수 r, 레이저 인덱스 번호 j
			ch[j++] = '0'; i += 2;
		}
		else {
			ch[j++] = init[i++];
		}
	}
	printf("ch : %s\n", ch);
}

void cut_stick(int x, int y)
{
	int cut = 1;
	for (int i = 0; i < r; i++) {
		if (razer[i] > x && razer[i] < y) cut++;
	}
	ans += cut;
}

void find_stick(void)
{
	char stack[100000 + 10] = { '\0' };
	int stack_num[100000 + 10] = { 0 };
	int s = 0; //stack index
	int n = strlen(ch);
	for (int i = 0; i < n; i++) {
		if (ch[i] == '0') continue;
		else {
			if (s == 0) {
				stack[s] = ch[i]; 
				stack_num[s] = i;
				s++; continue;
			}
			if ((stack[s - 1] == '(') && (ch[i] == ')')) {
				cut_stick(stack_num[s - 1], i);
				s--;
				stack[s] = '\0'; stack_num[s] = 0;
			}
			else {
				stack[s] = ch[i];
				stack_num[s] = i;
				s++;
			}
		}
	}
}

int main(void)
{
	scanf(" %s", init);
	change_razer();
	find_stick();
	printf("%d", ans);
	return 0;
}