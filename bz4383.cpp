#if 0
2019.10.31

将 a > b 的这个关系连边 (a, b) ，区间连边用线段树优化建图，
然后对于一张图就可以记搜，搜出每个点可行的最小值，过程中有环则无解。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 100005, maxd = 700005;
int head[maxd], nxt[maxd * 10], to[maxd * 10], hp;
int f[maxd];
int id[maxn];
bool real[maxd];

inline void add(int u, int v) {
	/* debug("%d -> %d\n", u, v); */
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
}

int d = 0;
void build(int now, int L, int R) {
	if(L == R) {
		real[now] = 1;
		id[L] = now;
		d = std::max(d, now);
		return;
	}
	int M = (L + R) >> 1;
	build(now << 1, L, M);
	build(now << 1 | 1, M + 1, R);
	add(now, now << 1);
	add(now, now << 1 | 1);
}

void link(int now, int L, int R, int l, int r, int u) {
	if(r < L or l > R) return;
	if(l <= L and R <= r) return add(u, now), void();
	int M = (L + R) >> 1;
	link(now << 1, L, M, l, r, u);
	link(now << 1 | 1, M + 1, R, l, r, u);
}

void dfs(int u) {
	if(f[u]) return;
	f[u] = 1000000001;
	int max = 0;
	for(int i = head[u]; i; i = nxt[i]) {
		dfs(to[i]);
		max = std::max(max, f[to[i]]);
	}
	f[u] = max + real[u];
}

int tmp[maxn];
int main() {
	int n = read, s = read, m = read;
	build(1, 1, n);
	for(int i = 1; i <= s; i ++) {
		int p = read;
		read(f[id[p]]);
	}

	for(int i = 1; i <= m; i ++) {
		int l = read, r = read, k = read;
		for(int j = 1; j <= k; j ++)
			read(tmp[j]);
		std::sort(tmp + 1, tmp + k + 1);
		int u = ++ d;
		for(int j = 1; j <= k; j ++)
			add(id[tmp[j]], u);
		tmp[0] = l - 1;
		tmp[k + 1] = r + 1;
		for(int j = 1; j <= k + 1; j ++)
			link(1, 1, n, tmp[j - 1] + 1, tmp[j] - 1, u);
	}

	for(int i = 1; i <= d; i ++)
		dfs(i);

	/* for(int i = 1; i <= d; i ++) */
	/* 	debug("%d: %d\n", i, f[i]); */

	for(int u = 1; u <= d; u ++) {
		if(f[u] > 1000000000)
			return puts("NIE"), 0;
		for(int i = head[u]; i; i = nxt[i])
			if(f[u] < f[to[i]] + real[u])
				return puts("NIE"), 0;
	}

	puts("TAK");
	for(int i = 1; i <= n; i ++)
		printf("%d ", f[id[i]]);
	puts("");
}
