#if 0
2019.12.17

令 k 为 a 的异或和。
不难发现每次操作 a[x] 等价于交换 a[x] 与 k ，
那么将 a, b, k 离散化后，判无解就很简单了，接下来假设一定有解。

对于 a[i] 和 b[i] ，如果 a[i] != b[i] ，连边 b[i] -> a[i] ，
这样建出来一个图，把 k 作为当前位置，考虑现在操作 a[x] 在图上的意义，

1) k 向 a[x] 有边，那么操作 a[x] 等价于删掉这条边并移动 k 到 a[x]
2) k 向 a[x] 无边，但存在 y 向 a[x] 有边，
那么操作 a[x] 等价于把 y -> a[x] 的一条边改为 y -> k ，并移动 k 到 a[x] 。

1) 操作后边数减一，2) 操作后边数不变，可以知道答案的一个下界就是边数，
现在的目标就是最小化 2) 操作的次数。

在有解的情况下，设 K 为 b 的异或和，任意时刻 k 的连边有两种情况：
i) k != K ，k 的出度一定比入度多 1
ii) k == K ，k 的出度恰好等于入度
原因：连边 (K, k) 后整张图所有点需要满足入度等于出度。

那么 k 没有出边当且仅当 k 是一个孤立的点且 k = K，
也就是说对于一个有 x 条边的联通块，一定可以通过 x 次 1) 操作将边删干净且 k 停留在 K 。
当 k = K 且被孤立的时候，就需要通过 2) 操作跳到另一个联通块，并且让该联通块与 K 联通。

由此就可以得到最少需要的 2) 操作次数了。
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
int a[maxn], b[maxn];
int tmp[maxn];
int tot[maxn];
int fa[maxn], size[maxn];

int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

int main() {
	int n = read;

	for(int i = 1; i <= n; i ++) {
		a[i] = read;
		a[n + 1] ^= a[i];
	}

	for(int i = 1; i <= n + 1; i ++)
		tmp[i] = a[i];
	std::sort(tmp + 1, tmp + n + 2);

	for(int i = 1; i <= n + 1; i ++) {
		a[i] = int(std::lower_bound(tmp + 1, tmp + n + 2, a[i]) - tmp);
		++ tot[a[i]];
	}

	for(int i = 1; i <= n; i ++) {
		b[i] = read;
		int x = int(std::lower_bound(tmp + 1, tmp + n + 2, b[i]) - tmp);
		if(tmp[x] != b[i] or !tot[x]) return puts("-1"), 0;
		b[i] = x;
		-- tot[x];
	}

	for(int i = 1; i <= n + 1; i ++) {
		fa[i] = i;
		size[i] = 1;
	}

	int ans = -1;
	for(int i = 1; i <= n; i ++) {
		int x = find(a[i]), y = find(b[i]);
		if(a[i] != b[i]) {
			/* debug("%d - %d\n", tmp[a[i]], tmp[b[i]]); */
			fa[x] = y;
			if(x != y)
				size[y] += size[x];
			++ ans;
		}
	}

	for(int i = 1; i <= n + 1; i ++)
		if(fa[i] == i and size[i] > 1)
			++ ans;

	if(fa[a[n + 1]] == a[n + 1] and size[a[n + 1]] == 1)
		++ ans;

	printf("%d\n", ans);
}
