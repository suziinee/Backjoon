N = int(input())

ans = ''
while N :
    ans += str(N % 2)
    N = N // 2
print(ans[::-1])