A, B = map(int, input().split())
C = int(input())

a = C // 60
b = C % 60

if B + b >= 60 :
    if A + a >= 23 :
        print(A + a - 24 + 1, B + b - 60)
    else :
        print(A + a + 1, B + b - 60)
else :
    if A + a >= 24 :
      print(A + a - 24, B + b)
    else :
      print(A + a, B + b)