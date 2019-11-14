#if 0
2019.11.14

scc 缩点后 DAG 上 DP 即可。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 10005, maxm = 100005;
int head[maxn], nxt[maxm], to[maxm], hp;
int a[maxn];

inline void add(int u, int v) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
}

bool vis[maxn];
int low[maxn];
int id[maxn], ip;
int stack[maxn], sp;
bool ins[maxn];
int bp;
std::vector<int> contain[maxn];
int belong[maxn];
int b[maxn];

void dfs(int u) {
	vis[u] = 1;
	stack[++ sp] = u;
	ins[u] = 1;
	low[u] = id[u] = ++ ip;

	for(int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if(!vis[v]) {
			dfs(v);
			low[u] = std::min(low[u], low[v]);
		} else if(ins[v])
			low[u] = std::min(low[u], low[v]);
	}

	if(low[u] == id[u]) {
		++ bp;
		while(stack[sp + 1] != u) {
			int x = stack[sp --];
			ins[x] = 0;
			belong[x] = bp;
			contain[bp].push_back(x);
			b[bp] += a[x];
		}
	}
}

int f[maxn];
void dp(int x) {
	if(f[x]) return;
	for(int u : contain[x])
		for(int i = head[u]; i; i = nxt[i]) {
			int y = belong[to[i]];
			if(y != x) {
				dp(y);
				f[x] = std::max(f[x], f[y]);
			}
		}
	f[x] += b[x];
}

int main() {
	int n = read, m = read;

	for(int i = 1; i <= n; i ++)
		read(a[i]);

	for(int i = 1; i <= m; i ++) {
		int u = read, v = read;
		add(u, v);
	}

	for(int i = 1; i <= n; i ++)
		if(!vis[i])
			dfs(i);

	int ans = 0;
	for(int i = 1; i <= bp; i ++) {
		dp(i);
		ans = std::max(ans, f[i]);
	}

	printf("%d\n", ans);
}
