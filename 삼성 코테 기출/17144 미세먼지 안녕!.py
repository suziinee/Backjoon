r, c, t = map(int, input().split())
arr = [list(map(int, input().split())) for _ in range(r)]
cur = 0

#미세먼지 좌표 찾기
flag = 0
for i in range(r) :
    for j in range(c) :
        if arr[i][j] == -1 and flag == 0 :
            up_x = i
            flag = 1
        if arr[i][j] == -1 and flag == 1 :
            down_x = i
            break

arr[up_x][0] = -1
arr[down_x][0] = -1


def circulation() :

    for i in range(up_x-2, -1, -1) :
        arr[i+1][0] = arr[i][0]
    for i in range(1, c) :
        arr[0][i-1] = arr[0][i]
    for i in range(1, up_x+1) :
        arr[i-1][c-1] = arr[i][c-1]
    for i in range(c-2, 0, -1) :
        arr[up_x][i+1] = arr[up_x][i]
    arr[up_x][1] = 0

    for j in range(down_x+2, r) :
        arr[j-1][0] = arr[j][0]
    for j in range(1, c) :
        arr[r-1][j-1] = arr[r-1][j]
    for j in range(r-2, down_x-1, -1) :
        arr[j+1][c-1] = arr[j][c-1]
    for j in range(c-2, 0, -1) :
        arr[down_x][j+1] = arr[down_x][j]
    arr[down_x][1] = 0


def dirt() :
    global up_x
    global down_x
    tmp = [[0] * (c) for _ in range(r)]
    dx = [-1, 0, 1, 0]
    dy = [0, 1, 0, -1]

    for i in range(r) :
        for j in range(c) :
            if arr[i][j] != 0 and arr[i][j] != -1 :
                discount = 0
                val = arr[i][j]//5
                for d in range(4) :
                    nx = i + dx[d]
                    ny = j + dy[d]
                    if nx<0 or ny<0 or nx>=r or ny>=c : continue
                    if arr[nx][ny] == -1 : continue
                    tmp[nx][ny] += val
                    discount += val
                tmp[i][j] += (arr[i][j] - discount)

    for i in range(r) :
        for j in range(c) :
            if arr[i][j] != -1 :
                arr[i][j] = tmp[i][j]


for time in range(t) :
    dirt()
    circulation()

ans = 0
for i in range(r) :
    for j in range(c) :
        ans += arr[i][j]
print(ans+2)