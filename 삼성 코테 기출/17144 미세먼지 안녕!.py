r, c, t = map(int, input().split())
arr = [ [list(map(int, input().split())) for _ in range(r)], [[0]*c for _ in range(r)] ]
cur = 0

#미세먼지 좌표 찾기
flag = 0
for i in range(r) :
    for j in range(c) :
        if arr[cur][i][j] == -1 and flag == 0 :
            up_x = i
            flag = 1
        if arr[cur][i][j] == -1 and flag == 1 :
            down_x = i
            break

arr[1][up_x][0] = -1
arr[1][down_x][0] = -1


def circulation() :
    global cur

    for i in range(up_x-2, -1, -1) :
        arr[cur][i+1][0] = arr[cur][i][0]
    for i in range(1, c) :
        arr[cur][0][i-1] = arr[cur][0][i]
    for i in range(1, up_x+1) :
        arr[cur][i-1][c-1] = arr[cur][i][c-1]
    for i in range(c-2, 0, -1) :
        arr[cur][up_x][i+1] = arr[cur][up_x][i]
    arr[cur][up_x][1] = 0

    for j in range(down_x+2, r) :
        arr[cur][j-1][0] = arr[cur][j][0]
    for j in range(1, c) :
        arr[cur][r-1][j-1] = arr[cur][r-1][j]
    for j in range(r-2, down_x-1, -1) :
        arr[cur][j+1][c-1] = arr[cur][j][c-1]
    for j in range(c-2, 0, -1) :
        arr[cur][down_x][j+1] = arr[cur][down_x][j]
    arr[cur][down_x][1] = 0


def dirt() :
    global cur
    global up_x
    global down_x
    next = (cur+1)%2
    dx = [-1, 0, 1, 0]
    dy = [0, 1, 0, -1]

    for i in range(r) :
        for j in range(c) :
            if arr[cur][i][j] != 0 and arr[cur][i][j] != -1 :
                discount = 0
                val = arr[cur][i][j]//5
                for d in range(4) :
                    nx = i + dx[d]
                    ny = j + dy[d]
                    if nx<0 or ny<0 or nx>=r or ny>=c : continue
                    if arr[cur][nx][ny] == -1 : continue
                    arr[next][nx][ny] += val
                    discount += val
                arr[next][i][j] += (arr[cur][i][j] - discount)

    # cur 초기화
    for i in range(r) :
        for j in range(c) :
            if arr[cur][i][j] != -1 :
                arr[cur][i][j] = 0

    cur = next


for time in range(t) :
    dirt()
    circulation()

ans = 0
for i in range(r) :
    for j in range(c) :
        ans += arr[cur][i][j]
print(ans+2)