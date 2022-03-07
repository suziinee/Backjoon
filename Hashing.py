L = int(input())
string = list(input())

ans = 0
M = 1234567891

for i, s in enumerate(string) :
    hash = ord(s) - ord('a') + 1
    ans += hash * (31 ** i)

print(ans % M)