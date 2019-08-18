#if 0
2019.08.18

DP 设 f[u][i] 表示询问 (u, i) 的答案，可以长链剖分优化到线性。
#endif
#include <cstdio>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() {
	int x = 0, c = getchar();
	while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

/* the same as the problem give */
void print(int q, long long* ans, int lim) {
    for(int i = 1; i <= q; ) {
        long long res = 0;
        for(int j = i; j <= std::min(q, i + lim - 1); j++) res ^= ans[j];
        i += lim;
        printf("%lld\n", res);
    }
    return ;
}

const int maxn = 3000000;
lolong *f[maxn], memory_pool[maxn];
int len[maxn], son[maxn];
std::vector<int> G[maxn], query[maxn];
int val[maxn];
int query_dis[maxn];
lolong ans[maxn];

void dfs(int u) {
	for(int v : G[u]) {
		dfs(v);
		if(len[v] > len[son[u]])
			son[u] = v;
	}
	len[u] = len[son[u]] + 1;
}

void dp(int u) {
	f[u][0] = val[u];
	if(son[u]) {
		f[son[u]] = f[u] + 1;
		dp(son[u]);
		f[u][0] += f[son[u]][0];
		for(int v : G[u])
			if(v != son[u]) {
				f[v] = f[u] + len[u];
				dp(v);
				f[u][0] += f[v][0];
				for(int i = 0; i < len[v]; i ++)
					f[u][i + 1] += f[v][i];
			}
	}
	/* for(int i = 0; i < len[u]; i ++) */
	/* 	debug(" %lld", f[u][i]); */
	/* debug("(%d)\n", u); */
	for(int q : query[u])
		if(query_dis[q] < len[u])
			ans[q] = f[u][query_dis[q]];
}

int main() {
	int n = input();
	for(int i = 1; i <= n; i ++)
		val[i] = input();
	for(int i = 2; i <= n; i ++)
		G[input()].push_back(i);
	int q = input();
	for(int i = 1; i <= q; i ++) {
		query[input()].push_back(i);
		query_dis[i] = input();
	}
	dfs(1);
	f[1] = memory_pool;
	dp(1);
	print(q, ans, input());
}
