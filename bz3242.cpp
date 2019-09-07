#if 0
2019.09.07

一开始以为是直径的一半，打完后才发现过不了样例。
事实上，问题相当于求断掉环上的一条边得到的直径的最小值的一半。

首先 dp 求出环下子树的直径的最大值，答案一定不会低于这个值。
然后枚举断边，注意到断边后直接求直径的复杂度是 O(n^2) 的，考虑优化。

dp 出 d[x] 表示 x 的子树的最大深度。
把环上的点拉出来考虑，
假设环上有 p 个点，a[i] 表示第 i 的点 u 的 d[u] ，
b[i] 表示从第 p 个点向右走到第 i 个点的路径长。

抽象出来后，由于 1 点和 p 点相连，考虑是否用了这条边。
设 pre1[i] 表示 1 到 i 中 a[j] + b[j] 的最大值，
pre2[i] 表示 1 到 i 中两个点 a[j] + a[k] + b[j] - b[k] 的最大值。
pre1, pre2 都是前缀最大值，可以线性预处理，
事实上，为了求 pre2 还需借助 pre0[i] 表示 1 到 i 中 a[j] + b[p] - b[j] 的最大值。
同理有 suf0, suf1, suf2 表示后缀上的情况，那么假设断边 i 和 i + 1 ，
直径就是 max(pre2[i], suf2[i + 1], pre1[i] + suf1[i]) 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005;
int head[maxn], nxt[maxn << 1], to[maxn << 1], val[maxn << 1], hp = 1;

inline void add(int u, int v, int w) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	val[hp] = w;
}

int stack[maxn], sp;
int du[maxn];

void sort(int n) {
	for(int i = 1; i <= n; i ++)
		if(du[i] == 1)
			stack[++ sp] = i;

	while(sp) {
		int u = stack[sp --];
		for(int i = head[u]; i; i = nxt[i])
			if(du[to[i]]) {
				du[to[i]] --;
				du[u] --;
				if(du[to[i]] == 1)
					stack[++ sp] = to[i];
			}
	}
}

lolong ans;
lolong d[maxn];

void dp(int u, int fa) {
	lolong max = 0;
	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != fa and not du[to[i]]) {
			dp(to[i], u);
			lolong dt = d[to[i]] + val[i];
			if(dt >= d[u]) {
				max = d[u];
				d[u] = dt;
			} else if(dt >= max)
				max = dt;
		}
	ans = std::max(ans, d[u] + max);
}

int id[maxn];
lolong a[maxn], b[maxn];
lolong pre0[maxn], pre1[maxn], pre2[maxn];
lolong suf0[maxn], suf1[maxn], suf2[maxn];

int main() {
	int n = input();

	for(int i = 1; i <= n; i ++) {
		int u = input(), v = input(), w = input();
		add(u, v, w);
		add(v, u, w);
		du[u] ++;
		du[v] ++;
	}

	sort(n);

	for(int u = 1; u <= n; u ++)
		if(du[u]) {
			id[0] = u;
			dp(u, 0);
			a[0] = d[u];
		}

	int p = 0;
	bool shit = true;
	while(shit)
		for(int i = head[id[p]]; i; i = nxt[i])
			if(du[to[i]] and (not p or to[i] != id[p - 1])) {
				id[p + 1] = to[i];
				a[p + 1] = d[to[i]];
				b[p + 1] = b[p] + val[i];
				/* debug("%d -> %d : %d(%d)\n", id[p], to[i], val[i], i); */
				if(to[i] == id[0])
					shit = false;
				p ++;
				break;
			}

	for(int i = 1; i <= p; i ++) {
		pre0[i] = std::max(pre0[i - 1], b[p] - b[i] + a[i]);
		pre1[i] = std::max(pre1[i - 1], b[i] + a[i]);
		pre2[i] = std::max(pre2[i - 1], pre0[i - 1] - (b[p] - b[i]) + a[i]);
	}

	for(int i = p; i; i --) {
		suf0[i] = std::max(suf0[i + 1], b[i] + a[i]);
		suf1[i] = std::max(suf1[i + 1], b[p] - b[i] + a[i]);
		suf2[i] = std::max(suf2[i + 1], suf0[i + 1] - b[i] + a[i]);
	}

	lolong min = pre2[p];
	for(int i = 1; i < p; i ++)
		min = std::min(min, std::max(
					std::max(pre2[i], suf2[i + 1]), pre1[i] + suf1[i + 1]));

	/* for(int i = 1; i <= p; i ++) */
	/* 	debug("%lld %lld|%lld %lld %lld|%lld %lld %lld\n", */
	/* 			a[i], b[i], */
	/* 			pre0[i], pre1[i], pre2[i], */
	/* 			suf0[i], suf1[i], suf2[i]); */

	/* debug("min = %lld\n", min); */

	ans = std::max(ans, min);

	printf("%.1lf\n", ans / 2.0);
}
