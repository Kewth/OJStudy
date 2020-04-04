#if 0
2020.03.06

首先不考虑 [t, T] 的限制和排斥的限制，令两组学生数量分别为：
x = min(r), y = max(l) ，
如果存在可行方案则这个分组一定可行，容易通过反证法证明，略。
（关键在于如果有三个区间两两不交则一定无解）

再考虑 x + y in [t, T] 的限制，由于 x 不能增大，y 不能减小，
那么如果 x + y < t 只能增大 y ，如果 x + y > T 只能减小 x 。
如果存在可行方案这样得出来的 x, y 一定可行。

接下来就只剩排斥的限制，二分图染色即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 100005;
std::vector<int> G[maxn];
int color[maxn];
int l[maxn], r[maxn];

inline shit() { puts("IMPOSSIBLE"); exit(0); }

void dfs(int u, int c) {
	if(!color[u]) {
		color[u] = c;
		for(int v : G[u])
			dfs(v, 3 - c);
	} else if(color[u] != c)
		shit();
}

int main() {
	int L = read, R = read;
	int n = read, m = read;
	int x = 1000000000, y = 0;
	for(int i = 1; i <= n; i ++) {
		l[i] = read;
		r[i] = read;
		x = std::min(x, r[i]);
		y = std::max(y, l[i]);
	}

	for(int i = 1; i <= m; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	if(x + y < L) y = L - x;
	if(x + y > R) x = R - y;
	if(x < 0 or y < 0) shit();
	
	for(int i = 1; i <= n; i ++) {
		bool a = l[i] <= x and x <= r[i];
		bool b = l[i] <= y and y <= r[i];
		if(a and !b) dfs(i, 1);
		if(!a and b) dfs(i, 2);
		if(!a and !b) shit();
	}

	for(int i = 1; i <= n; i ++)
		if(!color[i])
			dfs(i, 1);
			
	puts("POSSIBLE");
	printf("%d %d\n", x, y);
	for(int i = 1; i <= n; i ++)
		printf("%d", color[i]);
	puts("");
}
