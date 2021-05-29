#if 0
2019.07.16

朴素 DP 设 f[u][x] 表示 u 到 1 的路径上 1 ~ x 的子序列数，
g[u][x] 表示 u 的子树中 x ~ L 的子序列数（上述范围都不包括 u ），
那么经过 u 点的合法子序列数就是 f[u][val[x] - 1] * g[u][val[x] + 1] 。

考虑利用 DFS 的性质线性求出某时刻所有的 f[u][val[u] - 1], g[u][val[u] + 1] 。
观察 DFS 过程中 ff, gg 的变化，
其中 ff[x] 为 u 到 1 上 1 ~ x 的子序列数，gg[x] 是 DFS u 之前所有 DFS 结束的点 x ~ L 的子序列数。
u dfs 到 v 时，只有 ff[val[v]] 增加了 ff[val[v] - 1] ，
u dfs 结束时，回溯 u 点的影响，保证计算 u 点时只有 u 的祖先造成影响。
u dfs 结束时，只有 gg[val[u]] 增加了 CHANGE(gg[val[u] + 1])，
DFS u 前和 DFS u 后之间 gg 的改变量 CHANGE 即为 u 的子树的 x ~ L 子序列数。
通过 ff 和 gg 可以很方便求出 f, g ，不赘述。

考虑如何处理修改，利用到 fa[u] < u 以及按顺序修改这两个性质，
考虑每 n 个修改看做一轮，不难发现：
1) 这一轮 u 点修改前，u 的祖先一定已经修改，
2) 这一轮 u 的子树修改前，u 点一定已经修改。
那么每一轮记录修改前和修改后的 val 并按上述方法求出两个值的 f, g ，
那么点 u 修改后的 ans[u] 就是
ans[u - 1] + newf[u][new[x] - 1] * newg[u][new[x] + 1] - oldf[u][old[x] - 1] * oldg[u][old[x] + 1] ，
ans[0] 就是未修改时的答案，不满一轮的类似处理。

注意输入卡常，普通快读都过不了。
#endif
#include <cstdio>
#include <vector>
#define debug(...) // fprintf(stderr, __VA_ARGS__)

char s[1 << 25], *sS = s;
#define getchar() (*sS++)
size_t input_init = fread(s, 1, 1 << 25, stdin);
inline int input() {
    int ch, x;
    while (ch = getchar(), ch < '/') ;
    x = ch - '0';
    while (ch = getchar(), ch > '/')
        x = x * 10 + ch - '0';
    return x;
}
typedef long long lolong;

const int maxn = 1000005, maxq = 2000005, mod = 1000000007;
std::vector<int> G[maxn];
int ow[maxn], nw[maxn];
int v[maxq];
lolong f[maxn], g[maxn];
lolong of[maxn], nf[maxn];
lolong og[maxn], ng[maxn];

void dfs(int u) {
    of[u] = f[ow[u] - 1] % mod;
    nf[u] = f[nw[u] - 1] % mod;
    debug("f%d: %lld, %lld\n", u, of[u], nf[u]);
    f[nw[u]] += nf[u];
    lolong tmpog = g[ow[u] + 1], tmpng = g[nw[u] + 1];
    for(int to : G[u])
        dfs(to);
    (f[nw[u]] += mod - nf[u]) %= mod;
    if(tmpog == -1)
        og[u] = 1;
    else
        og[u] = (g[ow[u] + 1] - tmpog) % mod;
    if(tmpng == -1)
        ng[u] = 1;
    else
        ng[u] = (g[nw[u] + 1] - tmpng) % mod;
    debug("g%d: %lld, %lld\n", u, og[u], ng[u]);
    g[ow[u]] += og[u];
}

int main() {
    int n = input(), q = input(), L = input();
    for(int i = 2; i <= n; i ++)
        G[input()].push_back(i);
    for(int i = 1; i <= n; i ++)
        ow[i] = input();
    for(int i = 1; i <= q; i ++)
        v[i] = input();
    int times = (q + n - 1) / n;
    for(int i = q + 1; i <= n * times; i ++)
        if(i <= n)
            v[i] = ow[i];
        else
            v[i] = v[i - n];
    int p = 0;
    lolong ans = 0;
    while(times --) {
        for(int i = 1; i <= n; i ++)
            nw[i] = v[++ p];
        for(int i = 0; i <= L; i ++)
            f[i] = g[i] = 0;
        f[0] = 1;
        g[L + 1] = -1;
        dfs(1);
        p -= n;
        lolong now = g[1];
        for(int i = 1; i <= n; i ++) {
            (now += nf[i] * ng[i] - of[i] * og[i]) %= mod;
            now += mod;
            if(p + 1 <= q)
                ans += now * (++ p) % mod;
            ow[i] = nw[i];
        }
    }
    printf("%lld\n", ans % mod);
}
