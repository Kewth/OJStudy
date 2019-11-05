#if 0
2019.11.04

朴素的贪心是优先选儿子数最大的点，因为这会让下一步的选择尽可能多。
但事实上只要优先选有儿子的点即可，因为每个有儿子的点都不会让选择数变少，
当前选不满了是因为上一步有些没有儿子的点必须选，
而按照朴素贪心，必须选没有儿子的点当且仅当有儿子的点数量小于 k ，
那么只要选有儿子的点不管儿子数量多少都是一样的。

根据这个贪心，再通过一些归纳证明，可以发现存在一个阀值 i ，
使得可以把贪心的过程分为两部分，前 i 步把深度不超过 i 的恰好选完，
后面除了最后一步每一步都能选恰好 k 个点。
那么有答案 f[k] = i + ceil(s[i] / k) ，其中 s[i] 表示深度大于 i 的点数。

最大化 f[k] 可以把上取整去掉，改为最大化 g[k] = i * k + s[i] ，而 f[k] = ceil(g[k] / k) 。
考虑快速求出所有 g 。
g[k] 的表达式是个一次函数，将 (i, s[i]) 看做二维平面上一个点 D[i]，
那么 g[k] 就是 y = -kx + b 在 D[i] 上的截距，也就是说事实上是要最大化截距。
最大的截距一定与所有 D 构成的凸包相切，并且随着斜率减小切点会不断右移，
根据这个单调性建凸包并维护切点即可。
#endif
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> Par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 1000005;
int a[maxn], fa[maxn];
int s[maxn];
std::vector<int> G[maxn];
int f[maxn];
int st[maxn];

void dfs(int u, int d) {
	s[d] ++;
	for(int v : G[u])
		dfs(v, d + 1);
}

inline double k(int pi, int pj) {
	return (s[pi] - s[pj]) * 1.0 / (pi - pj);
}

int main() {
	int n = read, q = read;
	for(int i = 1; i <= q; i ++)
		read(a[i]);
	for(int i = 2; i <= n; i ++)
		G[fa[i] = read].push_back(i);

	dfs(1, 0);

	for(int i = n; i >= 0; i --)
		s[i] += s[i + 1];

	int p = 2;
	st[1] = 0;
	st[2] = 1;

	for(int i = 2; s[i]; i ++) {
		while(p > 1 and k(i, st[p]) > k(st[p], st[p - 1]))
			p --;
		st[++ p] = i;
	}

	for(int i = 1, now = 1; i <= n; i ++) {
		while(now < p and st[now] + 1.0 * s[st[now]] / i <
				st[now + 1] + 1.0 * s[st[now + 1]] / i)
			now ++;
		f[i] = st[now] + (s[st[now]] + i - 1) / i;
	}

	for(int i = 1; i <= q; i ++)
		printf("%d ", f[std::min(n, a[i])]);
	puts("");
}
