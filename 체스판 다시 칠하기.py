N, M = map(int, input().split())

chess = []
for i in range(N) :
    chess.append(list(input()))

def pop_chess(x, y, lst) :
    new = [list(lst[i][y:y+8]) for i in range(x, x + 8)]
    return new 

def compare_chess(new) :
    bw = [list('BWBWBWBW'), list('WBWBWBWB')]
    # case 1
    cnt1 = 0
    for i in range(8) :
        if i % 2 == 0 :
            for j in range(8) :
                if new[i][j] != bw[0][j] :
                    cnt1 += 1
        else :
            for j in range(8) :
                if new[i][j] != bw[1][j] :
                    cnt1 += 1
    # case 2
    cnt2 = 0
    for i in range(8) :
        if i % 2 == 0 :
            for j in range(8) :
                if new[i][j] != bw[1][j] :
                    cnt2 += 1
        else :
            for j in range(8) :
                if new[i][j] != bw[0][j] :
                    cnt2 += 1
    return min(cnt1, cnt2)
                
ans = []
for i in range(N - 7) :
    for j in range(M - 7) :
        ans.append(compare_chess(pop_chess(i, j, chess)))

print(min(ans))
        
