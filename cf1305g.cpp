#if 0
2020.03.21

加入一个点 0 ，不会对答案造成影响，0 可以和所有点相连，且不会产生贡献。
那么邀请可以看做连边，最后会连成一棵以 0 为根的树。
这棵树的答案就是所有点权和减去叶子点权和。
叶子点权和难以直接最优化，但是可以进行一个转换：
把边权和看做端点点权和之和，那么这棵树的答案就是边权和减去点权和。
目标变为最大化边权和，也就是求一颗最大生成树。
考虑 Kruskal 算法，从大到小枚举边权 z，然后枚举 x + y = z (x & y = 0) ，
这一步相当于枚举子集，也就是说枚举 (x, y, z) 的复杂度是 O(3^logn) 的。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 1 << 18 | 1;
int tot[maxn];
int fa[maxn];

int find (int x) {
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

int main () {
	ll ans = 0;
	int n = read;
	while (n -- ) {
		int x = read;
		++ tot[x];
		ans -= x;
	}
	++ tot[0];

	for (int i = 0; i < maxn; i ++)
		fa[i] = i;
	for (int U = maxn - 1; U >= 0; U --)
		for (int S = U; S >= 0; S --) {
			S &= U;
			int T = U ^ S;
			if (tot[S] and tot[T] and find(S) != find(T)) {
				ans += 1ll * U * (tot[S] + tot[T] - 1);
				tot[S] = tot[T] = 1;
				fa[find(S)] = find(T);
			}
		}

	printf("%lld\n", ans);
}
