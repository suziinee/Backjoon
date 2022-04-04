n = int(input())
stack = []
print_list = []

nums = []
for i in range(n) :
    nums.append(int(input()))

now = 1
flag = 0

for i in nums :
    while now <= i :
        stack.append(now)
        print_list.append("+")
        now += 1
    if stack[-1] == i :
        stack.pop()
        print_list.append("-")
    else :
        flag = 1
        break

if flag == 1 :
  print("NO")
else :
  for p in print_list :
    print(p)