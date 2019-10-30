#if 0
2019.10.30

序列上有个神奇的 LIS 做法，维护一个 multiset ，multiset 中维护的似乎是可能的 LIS 结尾。
依次考虑序列上每个数 x ，删掉不小于 x 的最小的 y ，因为 y 结尾的 LIS 长度与 x 一致，
而之后的数能接 y 就一定能接 x ，然后再插入 x ，每一时刻 multiset 的大小就是当前 LIS 长度。

更神奇的是这个做法可以推广到树上，考虑倒过来维护 multiset ，在树上也就是从叶子到根，
那么每个时刻 multiset 对应一颗子树，用 multiset 启发式合并，并用上述方法维护，
最后根的 multiset 大小即树上 LIS 大小。
#endif
#include <cstdio>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 200005;
int head[maxn], nxt[maxn << 1], to[maxn << 1], hp;
int a[maxn], fa[maxn];

inline void add(int u, int v) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
}

std::multiset<int> set[maxn];
void dfs(int u) {
	for(int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		dfs(v);
		if(set[u].size() < set[v].size())
			std::swap(set[u], set[v]);
		for(int x : set[v])
			set[u].insert(x);
	}

	auto it = set[u].lower_bound(a[u]);
	if(it != set[u].end())
		set[u].erase(it);
	set[u].insert(a[u]);

	/* for(int x : set[u]) */
	/* 	debug(" %d", x); */
	/* debug(" in %d\n", u); */
}

int main() {
	int n = read;
	for(int i = 1; i <= n; i ++)
		read(a[i], fa[i]);

	for(int i = 2; i <= n; i ++)
		add(fa[i], i);

	dfs(1);
	printf("%lu\n", set[1].size());
}
