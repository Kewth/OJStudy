#if 0
2019.04.03

一看到求最大异或和我还以为是线性基。。。
把路径异或和转换成深度异或和后，枚举一个端点再在 01 Trie 树上按位贪心。

woc 码完后改了一个地方过了样例就交了，就 A 了，舒服。
#endif
#include <bits/stdc++.h>

struct edge {
	int to, val;
	edge(int to, int val): to(to), val(val) { }
};
const int maxn = 100050;
int trans[maxn * 31][2], tp;
std::vector<edge> G[maxn];
int deep[maxn];

inline void insert(int x) {
	for(int k = 31, now = 0; k >= 0; k --) {
		int &to = trans[now][x >> k & 1];
		if(not to) to = ++ tp;
		now = to;
	}
}

void dfs(int u, int fa) {
	insert(deep[u]);
	for(edge &e : G[u])
		if(e.to != fa) {
			deep[e.to] = deep[u] ^ e.val;
			dfs(e.to, u);
		}
}

int main() {
	std::ios::sync_with_stdio(false);
	int n;
	std::cin >> n;
	for(int i = 1; i < n; i ++) {
		int u, v, w;
		std::cin >> u >> v >> w;
		G[u].push_back(edge(v, w));
		G[v].push_back(edge(u, w));
	}
	dfs(1, 0);
	int ans = 0;
	for(int i = 1; i <= n; i ++) {
		int nowans = 0;
		for(int k = 31, now = 0; k >= 0; k --) {
			int cur = trans[now][deep[i] >> k & 1],
				to = trans[now][not (deep[i] >> k & 1)];
			if(to) {
				now = to;
				nowans |= 1 << k;
			} else {
				assert(cur);
				now = cur;
			}
		}
		ans = std::max(nowans, ans);
	}
	std::cout << ans << std::endl;
}
