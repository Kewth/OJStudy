#if 0
2019.12.08

每个叶子 u 可以视为初始有 a[u] 个单元在上面，
单元不断向上移动，来源不同的两个单元到同一个点可以选择一起消失，
需要保证每个点 u 有恰好 a[u] + k 个单元到达过，其中 k 是在 u 点消失的对数。

从下向上考虑，对于每个点 u ，每个儿子都有若干单元到 u 点，
设此时一共有 tot 个单元，最多有 max 个来自同一个儿子。
那么需要消失的单元对数就是 k = tot - a[u] 。
设可以配对的数量为 K ，分两种情况：
1) max > tot - max: K = tot - max （配对的瓶颈在于 max 太大）
2) max <= tot - max: K = tot / 2 （配对的瓶颈在于总数的奇偶性）
配对后剩下的单元数为 tot - 2k ，向上递归即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 100005;
int head[maxn], nxt[maxn << 1], to[maxn << 1], hp = 1;
ll a[maxn];

inline void add(int u, int v) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
}

inline __attribute__((noreturn)) void shit() { puts("NO"); exit(0); }

ll dfs(int u, int fa) {
	if(!nxt[head[u]]) return a[u];

	ll tot = 0, max = 0;

	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != fa) {
			ll x = dfs(to[i], u);
			tot += x;
			max = std::max(max, x);
		}

	ll k = tot - a[u];
	ll K = max >= tot - max ? tot - max : tot >> 1;
	/* debug("%d : %d %d\n", u, tot, k); */
	if(k < 0 or k > K) shit();

	return tot - (k << 1);
}

int main() {
	int n = read;

	for(int i = 1; i <= n; i ++)
		read(a[i]);

	if(n == 2) return puts(a[1] == a[2] ? "YES" : "NO"), 0;

	for(int i = 1; i < n; i ++) {
		int u = read, v = read;
		add(u, v);
		add(v, u);
	}

	int root = 1;
	while(!nxt[head[root]])
		++ root;

	if(!dfs(root, 0)) puts("YES");
	else puts("NO");
}
