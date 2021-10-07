'''
2021.07.04

题解咕咕咕。卡空间司马。
'''
def intinput():
    return [int(i) for i in input().split()]

n = int(input())

G = [None for i in range(n + 1)]
for i in range(n):
    fuck = intinput()
    G[fuck[0]] = fuck[2:]

root = None
hasfa = [False for i in range(n + 1)]
for u in range(1, n + 1):
    for v in G[u]:
        hasfa[v] = True
root = hasfa.index(False, 1)

# f1 = [None for i in range(n + 1)] # 包含根
f2 = [None for i in range(n + 1)] # 不含根
f = [None for i in range(n + 1)]
# g1 = [None for i in range(n + 1)]
g2 = [None for i in range(n + 1)]
g = [None for i in range(n + 1)]
def dp (u):
    det = - 10 ** 9
    g2[u] = 0
    for v in G[u]:
        dp(v)
        g2[u] += g[v]
        det = max(det, 1 + g2[v] - g[v])
    g1_u = g2[u] + det
    g[u] = max(g1_u, g2[u])
    # vv^^vv^^
    f2[u] = 1
    for v in G[u]:
        f2[u] *= f[v]
    f1_u = 0
    for v in G[u]:
        if 1 + g2[v] - g[v] == det:
            f1_u += f2[u] // f[v] * f2[v]
    f[u] = 0
    if g1_u == g[u]:
        f[u] += f1_u
    if g2[u] == g[u]:
        f[u] += f2[u]
dp(root)
print(g[root])
print(f[root])
