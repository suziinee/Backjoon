n = int(input())
arr = []

for i in range(n) :
    age, name = input().split()
    arr.append([i, int(age), name])

arr = sorted(arr, key = lambda x : x[1])

for a in arr :
    print(a[1], a[2])