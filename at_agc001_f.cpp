#if 0
2019.08.30

* 排列的逆，拓扑序，优化建图，线段树

对每个 a[i] = x 记 b[x] = i ，那么 a 交换的条件在 b 上就是：
交换两个相邻且权值差不小于 K 的 b 。
当 b 字典序最小时对应的 a 字典序一定最小。

那么对于权值差小于 K 的 b[i], b[j] ，它们的相对位置是不会变的。
根据这个关系建图，从 i 连边连向 j ，那么问题转换为求拓扑序。
然而边数是 O(N K) 的，无法接受。

事实上暴力连边连了许多无用边，例如 a -> b -> c 且 a -> c 中，
a -> c 这条边就毫无意义。
每个点考虑出边，假设 x 在 (x, x + k) 能连向 y1, y2, ... yy ，
那么 y1 一定能连向 y2, y3, ... yy 。
所以 x 只向 y1 连边，即向可连边集合中的最小值连边即可。
用线段树维护这个最小值。
#endif
#include <cstdio>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef std::pair<int, int> Par;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 500005;
int a[maxn], b[maxn];
int val[maxn << 2];
int head[maxn], nxt[maxn << 1], to[maxn << 1], hp;
int in[maxn];

inline void add(int u, int v) {
	/* debug("%d -> %d\n", u, v); */
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	in[v] ++;
}

void modify(int now, int l, int r, int p, int x) {
	if(l == r) {
		val[now] = x;
		return ;
	}
	int mid = (l + r) >> 1;
	if(p <= mid)
		modify(now << 1, l, mid, p, x);
	else
		modify(now << 1 | 1, mid + 1, r, p, x);
	val[now] = std::min(val[now << 1], val[now << 1 | 1]);
}

int query(int now, int L, int R, int l, int r) {
	if(r < L or l > R)
		return maxn;
	if(l <= L and R <= r)
		return val[now];
	int mid = (L + R) >> 1;
	return std::min(query(now << 1, L, mid, l, r),
			query(now << 1 | 1, mid + 1, R, l, r));
}

int main() {
	int n = input(), k = input();

	int len = 1;
	while(len < n)
		len <<= 1;

	for(int i = 1; i <= n; i ++)
		b[a[i] = input()] = i;

	for(int i = 1; i <= len; i ++)
		modify(1, 1, len, i, maxn);

	for(int i = n; i; i --) {
		int j;
		j = query(1, 1, len, b[i] - k + 1, b[i]);
		if(j < maxn)
			add(b[i], b[j]);
		j = query(1, 1, len, b[i], b[i] + k - 1);
		if(j < maxn)
			add(b[i], b[j]);
		modify(1, 1, len, b[i], i);
	}

	std::priority_queue<int> que;

	for(int i = 1; i <= n; i ++)
		if(not in[i])
			que.push(- i);

	int p = 0;
	while(not que.empty()) {
		int u = - que.top();
		que.pop();
		b[++ p] = u;
		for(int i = head[u]; i; i = nxt[i]) {
			in[to[i]] --;
			if(not in[to[i]])
				que.push(- to[i]);
		}
	}

	for(int i = 1; i <= n; i ++)
		a[b[i]] = i;

	for(int i = 1; i <= n; i ++)
		printf("%d\n", a[i]);
}
