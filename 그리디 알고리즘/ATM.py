N = int(input())
p = list(map(int, input().split()))
d = {idx : v for idx, v in enumerate(p)}
d = dict(sorted(d.items(), key = lambda x : x[1]))
key_list = list(d.keys())

sums = 0
for key in key_list :
    sums += d[key]
    d[key] = sums

print(sum(d.values()))

