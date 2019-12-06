#if 0
2019.12.06

DP 设 f[i][j][k] 表示考虑一段前缀，三种颜色最后一次出现的位置分别为 i, j, k 的合法方案。
令 r = max(i, j, k) ，r 即当前考虑的前缀长。
检验当前状态是否合法，只需将所有右端点为 r 的限制拿出来，用 i, j, k 可以很好判断是否合法，
如果合法，枚举第 r + 1 的点的颜色进行转移即可。
#endif
#include <cstdio>
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

const int maxn = 305, mod = 1000000007;
ll f[maxn][maxn][maxn];
std::vector<int> lim[maxn];

int main() {
	int n = read, m = read;

	for(int i = 1; i <= m; i ++) {
		int l = read, r = read, x = read;
		lim[r].push_back(l * 10 + x);
	}

	f[0][0][0] = 1;
	ll ans = 0;

	for(int i = 0; i <= n; i ++) {
		for(int j = 0; j <= n; j ++) {
			for(int k = 0; k <= n; k ++) {
				int r = std::max(i, std::max(j, k));
				f[i][j][k] %= mod;

				bool ok = 1;
				for(int li : lim[r]) {
					int l = li / 10, x = li % 10;
					int y = (i >= l) + (j >= l) + (k >= l);
					if(x != y) {
						ok = 0;
						break;
					}
				}

				if(ok) {
					if(r == n) ans += f[i][j][k];
					else {
						f[r + 1][j][k] += f[i][j][k];
						f[i][r + 1][k] += f[i][j][k];
						f[i][j][r + 1] += f[i][j][k];
					}
				}
				else
					f[i][j][k] = 0;
			}
		}
	}

	ans %= mod;
	printf("%lld\n", ans);
}
