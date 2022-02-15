N = int(input())
cards = sorted(list(map(int, input().split())))
M = int(input())
count_cards = list(map(int, input().split()))

from bisect import bisect_left, bisect_right

for i in count_cards :
    print(bisect_right(cards, i) - bisect_left(cards, i), end = ' ')