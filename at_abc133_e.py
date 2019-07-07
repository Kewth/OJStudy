n, m = [int(i) for i in input().split()]
# n, m = 100000, 100000

G = [[] for i in range(n + 1)]
C = [m for i in range(n + 1)]
for i in range(n - 1):
    x, y = [int(i) for i in input().split()]
    # x, y = i + 1, i + 2
    G[x].append(y)
    G[y].append(x)

ans = 1
def dfs(s):
    global ans, C, G
    stack = [s]
    while len(stack):
        u = stack[len(stack) - 1]
        stack.pop()
        ans *= C[u]
        ans %= 1000000007
        # print(u, C[u], ans)
        tot = 1
        if u != 1:
            tot += 1
        for v in G[u]:
            C[v] -= tot
            G[v].remove(u)
            stack.append(v)
            tot += 1

dfs(1)
print(ans)
