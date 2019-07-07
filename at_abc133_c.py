l, r = [int(i) for i in input().split()]
r = min(r, l + 2019) + 1
ans = 10 ** 10
for i in range(l, r):
    for j in range(i + 1, r):
        ans = min(ans, i * j % 2019)
print(ans)
