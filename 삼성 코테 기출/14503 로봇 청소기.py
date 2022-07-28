n, m = map(int, input().split())
r, c, d = map(int, input().split())
arr = []

for i in range(n) :
  arr.append(list(map(int, input().split())))

# 벽은 2로 바꾸기
for i in range(n) :
  arr[i] = [2 if n==1 else 0 for n in arr[i]]

# 왼쪽으로 도는 코드
def func(r, c, d) :
  if d == 0 :
    return (r, c-1, 3)
  if d == 3 :
    return (r+1, c, 2)
  if d == 2 :
    return (r, c+1, 1)
  if d == 1 :
    return (r-1, c, 0)

# 뒤로 후진하는 코드
def back(r, c, d) :
  if d == 0 :
    return (r+1, c, 0)
  if d == 3 :
    return (r, c+1, 3)
  if d == 2 :
    return (r-1, c, 2)
  if d == 1 :
    return (r, c-1, 1)

flag = 0
colored = 0
cnt = 0
ans = 0
    
# 종료조건 : 뒤에 벽이 있고(flag = 1) 사방이 모두 칠해져 있을때(cnt = 4)
while not (flag == 1 and cnt == 4) :

  cnt = 0 # 회전 횟수 초기화
  colored = 0
  
  # 3. 비어있지 않거나 벽이면 왼쪽으로 돈다 (d는 바뀐채로 while문 돌기)
  while cnt < 4 :
    # 0. 현재가 칠해져 있지 않다면 칠하고 break
    if arr[r][c] == 0 :
      arr[r][c] = 1
      ans += 1
      break
      
    # 1. 현재가 칠해져 있거나 벽이라면 현재 있는 방향에서 왼쪽을 확인한다
    nx, ny, d = func(r, c, d)
    cnt += 1
    # 1-1. 범위를 벗어난다면 break
    if nx<0 or ny<0 or nx>=n or ny>=m : break
    # 2. 왼쪽이 비어있다면 칠하고 r, c, d 초기화
    if arr[nx][ny] == 0 :
      arr[nx][ny] = 1
      ans += 1
      r, c, d = nx, ny, d
      colored = 1
      break
    
  # 4. 모든 방향에 칠할 수 없다면(cnt=4) 뒤로 1칸 후진하여 루프를 돈다
  if cnt == 4 and colored == 0 :
    r, c, d = back(r, c, d)
    # 5. 뒤가 벽이라면 종료
    if arr[r][c] == 2 :
      flag = 1


print(ans)