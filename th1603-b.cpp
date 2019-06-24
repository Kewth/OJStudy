#if 0
2019.06.23

怀疑题目改自 FJWC 2019 。
原题： http://218.5.5.242:9021/problem/191
题解： https://hk-cnyali.com/2019/02/28/%E3%80%8CFJWC2019%E3%80%8D%E5%AD%90%E5%9B%BE-%E5%88%86%E7%B1%BB%E8%AE%A8%E8%AE%BA-%E6%9E%9A%E4%B8%BE-%E6%9A%B4%E5%8A%9B/

不同的是每个链的贡献要算在端点上，但还是要枚举中点。
把中点相连的点列出来，再对相连的点的相连的点列到第二层（有重复），
即可考虑到所有可能的情况。
复杂度很神奇，并不是 m^2 ，而是 m^1.5 。
#endif
#include <cstdio>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

const int maxn = 100005;
std::vector<int> G[maxn];
int ans[maxn];
int have[maxn];
bool link[maxn];

inline int input() { int x; scanf("%d", &x); return x; }

inline void print(FILE *target, int n) {
	for(int u = 1; u <= n; u ++)
		fprintf(target, "%d\n", ans[u]);
}

int main() {
	int n = input(), m = input();
	for(int i = 1; i <= m; i ++) {
		int x = input(), y = input();
		G[x].push_back(y);
		G[y].push_back(x);
	}
	for(int u = 1; u <= n; u ++) {
		// 链
		int tot = 0;
		for(int v : G[u])
			for(int w : G[v])
				if(w != u)
					tot ++;
		for(int v : G[u])
			for(int w : G[v])
				if(w != u)
					ans[w] += tot - 1;
		// 菊花
		for(int v : G[u]) {
			int sz = int(G[v].size() - 1);
			if(sz < 2) continue;
			ans[u] -= sz * (sz - 1);
		}
		// 四元环
		for(int v : G[u])
			for(int w : G[v])
				if(w != u) {
					ans[u] -= 2 * have[w];
					have[w] ++;
				}
		for(int v : G[u])
			for(int w : G[v])
				if(w != u)
					have[w] --;
		// 三元环
		for(int v : G[u])
			link[v] = true;
		for(int v : G[u])
			for(int w : G[v])
				if(link[w])
					ans[u] --;
		// 三元环加一条边
		for(int v : G[u]) {
			int lazy = 0;
			for(int w : G[v])
				if(link[w]) {
					ans[v] -= int(G[v].size() - 2);
					lazy --;
					ans[w] ++;
				}
			for(int w : G[v])
				if(w != u)
					ans[w] += lazy;
		}
		for(int v : G[u])
			link[v] = false;
	}
	print(stdout, n);
}
