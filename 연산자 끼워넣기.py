N = int(input())
nums = list(map(int, input().split()))
op = list(map(int, input().split()))

max_ans = -1e9
min_ans = 1e9

def dfs(res, idx, add, min_, mul, div) :

    global max_ans, min_ans

    # 재귀 끝내기
    if idx == N :
        max_ans = max(max_ans, res)
        min_ans = min(min_ans, res)
        return
    
    if add > 0 :
        dfs(res + nums[idx], idx + 1, add - 1, min_, mul, div)
    if min_ > 0 :
        dfs(res - nums[idx], idx + 1, add, min_ - 1, mul, div)
    if mul > 0 :
        dfs(res * nums[idx], idx + 1, add, min_, mul - 1, div)
    if div > 0 :
        dfs(int(res / nums[idx]), idx + 1, add, min_, mul, div - 1)


dfs(nums[0], 1, op[0], op[1], op[2], op[3])
print(max_ans)
print(min_ans)