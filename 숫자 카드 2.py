N = int(input())
cards = list(map(int, input().split()))
M = int(input())
count_cards = list(map(int, input().split()))

from collections import Counter

C = Counter(cards)

ans = []
for num in count_cards :
    if num in C :
        ans.append(str(C[num]))
    else :
        ans.append('0')

return ' '.join(ans)