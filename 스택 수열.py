n = int(input())
stack = []
print_list = []

nums = []
for i in range(n) :
    nums.append(int(input()))

stack.append(1)
print_list.append("+")
now = 2

for i in nums :
    if not stack :
        stack.append(now)
        print_list.append("+")
        now += 1
    while stack[-1] != i and stack[-1] < i :
        stack.append(now)
        print_list.append("+")
        now += 1
    if stack[-1] == i :
        stack.pop()
        print_list.append("-")
        
if stack :
  print("NO")
else :
  for p in print_list :
    print(p)