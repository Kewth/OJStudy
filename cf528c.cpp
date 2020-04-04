#if 0
2020.01.28

题意杀，要求的是加尽可能少的边然后给图定向使得每个点的入度出度都为偶数。

考虑欧拉回路，满足每个点的入度等于出度，
因为考虑欧拉回路相邻两条边，会对交点的入度和出度都产生 1 的贡献。
如果把欧拉回路交替黑白染色（假定边数为偶数），那么相邻两条边就一黑一白，
将黑边反向，此时会对交点入度或出度产生 2 的贡献，不影响奇偶性。

也就是说只要一张图存在欧拉回路且边数为偶数即可。
#endif
#include <cstdio>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

struct {
	operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005, maxm = 1600005;
int head[maxn], nxt[maxm], to[maxm], hp = 1;
int deg[maxn];

inline void add(int u, int v) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	++ deg[u];
}

bool vis[maxm];
int stack[maxm], sp;
void dfs(int u) {
	for(int &i = head[u]; i; i = nxt[i])
		if(!vis[i]) {
			vis[i] = vis[i ^ 1] = 1;
			dfs(to[i]);
		}
	stack[++ sp] = u;
}

int main() {
	int n = read, m = read;

	for(int i = 1; i <= m; i ++) {
		int u = read, v = read;
		add(u, v);
		add(v, u);
	}

	int last = 0;
	for(int u = 1; u <= n; u ++)
		if(deg[u] & 1) {
			if(last) {
				add(last, u);
				add(u, last);
				last = 0;
			} else
				last = u;
		}

	if(last) return 1; // impossible

	if((hp >> 1) & 1) {
		add(1, 1);
		add(1, 1);
	}

	debug("%d\n", hp >> 1);

	dfs(1);

	printf("%d\n", sp - 1);
	for(int i = 1; i < sp; i ++)
		if(i & 1) printf("%d %d\n", stack[i], stack[i + 1]);
		else printf("%d %d\n", stack[i + 1], stack[i]);
}
