#if 0
2020.03.19

首先把电路网络建出树状结构，每个叶子代表原来的一个电阻，
每个非叶子节点代表一对括号内的子电路。

对于一个电路设 f(x) 表示当这个电路的整体阻值为 x 时其内部电阻和的最小值。
可以发现 f(x) 是一个正比例函数，比例系数 k 只与该电路本身有关。

考虑求出每个电路的 k 和 x 。

如果一个电路是多个子电路的串联，有 x = sum(x_i) ，那么其 k 值就是子电路的最小值。
这个时候只要找到 k_i 最小的子电路令 x_i = x ，其他子电路都有 x_i = 0 。
（ps: 如果有多个 k_i 最小值，事实上它们的 x_i 是可以在和一定的前提下随意分配的）

如果一个电路是多个子电路的并联，有 1/x = sum(1/x_i), f(x) = sum(f_i(x_i)) 。
把左边的式子代入到 f(x) 可以得到 k = sum(1 / x_i) sum(k_i x_i) 。
通过柯西不等式消掉 x_i ，得到 k >= sum(sqrt(k_i))^2 ，这个等号是可以取的，右边的值就是 k 。
而根据取等号的条件，有 k_i x_i^2 = S ，其中 S 是一个只与该电路有关的定值。
问题就是求出 S ，将所有这样的式子求和，然后用 1/x = sum(1/x_i) 代入即可消掉 x_i 。

只需判断解出来的是否是整数阻值即可。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef long double ld;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator char () { int x = getchar();
		while(x == ' ') x = getchar(); return char(x); }
} read;

const int maxn = 320005;
const ld eps = 1e-6l;
int ip;
std::vector<int> G[maxn];
int type[maxn];
ld X[maxn], K[maxn];

inline int newnode () { return type[++ ip] = 0, ip; }

int build () {
	int u = newnode();
	for(char c = read; c != ')'; c = read) {
		if(c == '*') G[u].push_back(newnode());
		if(c == '(') G[u].push_back(build());
		if(c == 'S') type[u] = 1;
		if(c == 'P') type[u] = 2;
	}
	return u;
}

void dfs1 (int u) {
	for(int v : G[u]) dfs1(v);
	if(type[u] == 0)
		K[u] = 1;
	if(type[u] == 1) {
		K[u] = 1e300l;
		for(int v : G[u])
			K[u] = std::min(K[u], K[v]);
	}
	if(type[u] == 2) {
		K[u] = 0;
		for(int v : G[u])
			K[u] += sqrtl(K[v]);
		K[u] *= K[u];
	}
}

void dfs2 (int u) {
	if(type[u] == 1) {
		int key = 0;
		for(int v : G[u])
			if(K[v] >= K[u] and K[v] <= K[u])
				key = v;
		for(int v : G[u])
			X[v] = v == key ? X[u] : 0;
	}
	if(type[u] == 2) {
		if(X[u] <= 0)
			for(int v : G[u]) X[v] = 0;
		else {
			ld alpha = 0;
			for(int v : G[u])
				alpha += sqrtl(K[v]);
			alpha *= X[u];
			for(int v : G[u])
				X[v] = alpha / sqrtl(K[v]);
		}
	}
	for(int v : G[u]) dfs2(v);
}

int main () {
	int T = read;
	while(T --) {
		ip = 0;
		int R = read, S = char(read) == '*' ? newnode() : build();
		dfs1(S);
		for(int i = 1; i <= ip; i ++)
			if(type[i] and G[i].empty())
				return 1;
		X[S] = R;
		dfs2(S);
		for(int i = 1; i <= ip; i ++)
			G[i].clear();
		for(int i = 1; i <= ip; i ++)
			if(type[i] == 0 and std::min(X[i] - floorl(X[i]), ceill(X[i]) - X[i]) > eps)
					goto fail;
		printf("REVOLTING");
		for(int i = 1; i <= ip; i ++)
			if(type[i] == 0)
				printf(" %lld", ll(X[i] + eps));
		puts("");
		continue;
fail:
		puts("LOSS");
	}
}
