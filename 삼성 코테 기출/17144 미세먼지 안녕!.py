import copy
dx = [-1, 0, 1, 0]
dy = [0, 1, 0, -1]

def dirt(arr) :
    new_arr = copy.deepcopy(arr)
    for i in range(1, r+1) :
        for j in range(1, c+1) :
            if (arr[i][j] != 0) and (arr[i][j] != -1) :
                cnt = 0
                for n in range(4) :
                    nx = i + dx[n]
                    ny = j + dy[n]
                    if nx<1 or ny<1 or nx>r or ny>c : continue
                    if arr[nx][ny] == -1 : continue
                    new_arr[nx][ny] += (arr[i][j] // 5)
                    cnt += 1
                new_arr[i][j] -= ((arr[i][j]//5) * cnt)
    return new_arr

def circulation(arr, x, y) :
    new_arr = [[0] * (c+1) for _ in range(r+1)]
    # (x, y)에서 시작되는 위쪽 반시게 순환
    for i in range(1, x+1) :
        for j in range(1, c+1) :
            if i==x and j==y : continue
            if arr[i][j] != 0 :
                if i==1 and j==1 : new_arr[2][1] = arr[i][j]
                elif i==x and j==1 : new_arr[x][2] = arr[i][j]
                elif i==x and j==c : new_arr[x-1][c] = arr[i][j]
                elif i==1 and j==c : new_arr[1][c-1] = arr[i][j]
                elif i==x : new_arr[i][j+1]= arr[i][j]
                elif j==c : new_arr[i-1][j] = arr[i][j]
                elif i==1 : new_arr[i][j-1] = arr[i][j]
                elif j==1 : new_arr[i+1][j] = arr[i][j]
                else :
                    new_arr[i][j] = arr[i][j]
            new_arr[x][y] = -1

    #(x+1, y)에서 시작하는 아래 시계 순환
    for i in range(x+1, r+1) :
        for j in range(1, c+1) :
            if i==(x+1) and j==y : continue
            if arr[i][j] != 0 :
                if i==x+1 and j==1 : new_arr[x+1][2] = arr[i][j]
                elif i==r and j==1 : new_arr[r-1][1] = arr[i][j]
                elif i==r and j==c : new_arr[r][c-1] = arr[i][j]
                elif i==x+1 and j==c : new_arr[x+2][c] = arr[i][j]
                elif i==x+1 : new_arr[i][j+1] = arr[i][j]
                elif j==c : new_arr[i+1][j] = arr[i][j]
                elif i==r : new_arr[i][j-1] = arr[i][j]
                elif j==1 : new_arr[i-1][j] = arr[i][j]
                else :
                    new_arr[i][j] = arr[i][j]
            new_arr[x+1][y] = -1
    return new_arr

def find_circulation() :
    for i in range(1, r+1) :
        for j in range(1, c+1) :
            if arr[i][j] == -1 : return (i, j)

# 입력 받기
r, c, t = map(int, input().split())
arr = [[0] for _ in range(r+1)]
for i in range(1, r+1) :
    arr[i].extend(list(map(int, input().split())))
x, y = find_circulation()

# t초가 지난 후 남아있는 미세먼지 양
for time in range(t) :
    arr = dirt(arr)
    arr = circulation(arr, x, y)

ans = 0
for i in range(1, r+1) :
    for j in range(1, c+1) :
        ans += arr[i][j]
print(ans + 2)
