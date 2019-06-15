#if 0
2019.06.15

枚举每两个点作为 p, q 的来源，再将 p, q 连接的点用并查集连接，
并查集的集合数量即该 p, q 的答案。
#endif
#include <cstdio>
#include <algorithm>

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 55;
int x[maxn], y[maxn];
int fa[maxn];

inline int find(int u) {
	if(fa[u] == u) return u;
	return fa[u] = find(fa[u]);
}

int calc(int p, int q, int n) {
	for(int i = 1; i <= n; i ++)
		fa[i] = i;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			if(x[j] - x[i] == p and y[j] - y[i] == q)
				fa[find(i)] = find(j);
	int res = 0;
	for(int i = 1; i <= n; i ++)
		if(fa[i] == i)
			res ++;
	return res;
}

int main() {
	int n = input();
	for(int i = 1; i <= n; i ++) {
		x[i] = input();
		y[i] = input();
	}
	int ans = 1000000000;
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			ans = std::min(ans, calc(x[j] - x[i], y[j] - y[i], n));
	printf("%d\n", ans);
}
