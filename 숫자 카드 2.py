N = int(input())
cards = list(map(int, input().split()))
M = int(input())
count_cards = list(map(int, input().split()))

from collections import Counter

C = Counter(cards)

ans = ' '.join(str(C[num]) if num in C else '0' for num in count_cards)

print(ans)