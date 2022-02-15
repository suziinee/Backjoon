N = int(input())
cards = list(map(int, input().split()))
M = int(input())
count_cards = list(map(int, input().split()))

hashMap = {}

for num in cards :
    if num in hashMap :
        hashMap[num] += 1
    else :
        hashMap[num] = 1

ans = []
for num in count_cards :
    if num in hashMap :
        ans.append(str(hashMap[num]))
    else :
        ans.append('0')

return ' '.join(ans)