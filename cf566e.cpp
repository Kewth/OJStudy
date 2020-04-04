#if 0
2020.02.19

不妨假定有至少三个非叶子节点。
如果两个集合恰好有两个交点，那么这两个点一定相连且为非叶子节点。
用 bitset 存储集合，两两求交，即可得到非叶子节点之间的连边。

对于非叶子节点 u 处理出 g[u] 表示与 u 距离不超过 1 的非叶子节点集合。
那么对于叶子节点 x ，若与其相连的非叶子节点为 u ，则有 f[x] = g[u] 。
其中 f[x] 是与 x 距离不超过 2 的非叶子节点集合。
考虑在所有集合中找出 x 对应的集合，事实上就是包含 x 的集合中最小的那个。
#endif
#include <cstdio>
#include <algorithm>
#include <bitset>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 1005;
typedef std::bitset<maxn> set;
set a[maxn], b[maxn], tree;
bool vis[maxn];

int main() {
	int n = read;
	if(n == 1) return 0;
	if(n == 2) return puts("1 2"), 0;

	for(int i = 1; i <= n; i ++) {
		int t = read;
		while(t --)
			a[i][size_t(read)] = 1;
		for(int j = 1; j < i; j ++) {
			set s = a[i] & a[j];
			if(s.count() == 2) {
				size_t u = 0, v = 0;
				for(size_t k = 0; k < maxn; k ++)
					if(s[k])
						(u ? v : u) = k;
				if(!b[u][v]) {
					printf("%u %u\n", u, v);
					tree[u] = 1;
					tree[v] = 1;
					b[u][v] = 1;
					b[v][u] = 1;
					b[u][u] = 1;
					b[v][v] = 1;
				}
			}
		}
	}

	if(!tree.count()) {
		for(int i = 2; i <= n; i ++)
			printf("1 %d\n", i);
		return 0;
	}

	if(tree.count() == 2) {
		size_t u = 0, v = 0;
		for(size_t k = 0; k < maxn; k ++)
			if(tree[k])
				(u ? v : u) = k;
		set las;
		int p = 0;
		for(int i = 1; i <= n and p < 2; i ++)
			if(a[i].count() < size_t(n) and a[i] != las) {
				++ p;
				for(size_t k = 0; k < maxn; k ++)
					if(a[i][k] and k != u and k != v)
						printf("%u %u\n", p == 1 ? u : v, k);
				las = a[i];
			}
		return 0;
	}

	for(int i = 1; i <= n; i ++)
		if(!tree[size_t(i)]) {
			set now;
			now.set();
			for(int j = 1; j <= n; j ++)
				if(a[j][size_t(i)] and a[j].count() < now.count())
					now = a[j];
			set s = now & tree;
			for(int j = 1; j <= n; j ++)
				if(tree[size_t(j)] and s == b[j])  {
					printf("%d %d\n", i, j);
					break;
				}
		}
}
