def distance(a, b, d):
    res = 0
    for i in range(d):
        res += (a[i] - b[i]) ** 2
    res **= 0.5
    return res

n, d = [int(i) for i in input().split()]
dot = []
for i in range(n):
    dot.append([int(i) for i in input().split()])
ans = 0
for i in range(n):
    for j in range(i + 1, n):
        di = distance(dot[i], dot[j], d)
        if abs(int(di) - di) < 0.0001:
            ans += 1
print(ans)
