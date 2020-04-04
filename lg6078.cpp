#if 0
2020.02.07

对于白色的三元环就是三元环统计的板子。
黑色的三元环容斥计算，分别统计有至少零条/一条/两条/三条白边的三元环数量，
然后简单容斥即可得到恰有零条白边的三元环数量。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 100005;
std::vector<int> G[maxn];
bool vis[maxn];

int main() {
	int n = read, m = read;
	for(int i = 1; i <= m; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	int a = 0, c = 0;
	for(int u = 1; u <= n; u ++) {
		for(int v : G[u])
			vis[v] = 1;
		for(int v : G[u])
			for(int x : G[v]) {
				if(vis[x])
					++ a;
				if(x != u)
					++ c;
			}
		for(int v : G[u])
			vis[v] = 1;
	}
	a /= 3;
	c /= 2;

	ll b = 1ll * n * (n - 1) * (n - 2) / 6;
	b -= 1ll * m * (n - 2);
	b += c;
	b -= a;

	printf("%lld\n", a + b);
}
