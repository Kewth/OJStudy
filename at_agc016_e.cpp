#if 0
2019.12.17

O(n^2m) 可过，我惊了。。。

朴素的想法是枚举每个 (i, j) 然后倒推判断是否可行。
具体的，记录 f[i] 表示当前 i 是否必须活着，
然后倒着考虑每个 (a, b) ，如果 f[a] & f[b] ，就不可行，因为 (a, b) 后两个至少得死一个，
否则如果 f[a] = 1 ，说明 (a, b) 后 a 必须活着，
那么此前如果 b 死了 a 就成了 (a, b) 的唯一目标，
因而需要满足 f[b] = 1 ，同理只要 f[b] = 1 也要满足 f[a] = 1 。
如果过程中不存在 f[a] & f[b] ，那么 (i, j) 就是可行的，复杂度 O(n^2m) ，可以 AC 。

但事实上每次倒推是毫无必要的，
记 f[i][k] 表示满足最后 i 活着的前提下 j 是否必须活着，
通过上述的倒推可以 O(nm) 求出 f ，
那么事实上对于 (i, j) ，如果存在 k 满足 f[i][k] & f[j][k] ，就是不可行的，
因为事实上 f[i][k] = 1 实际上是说明 i 活着需要 k 为 i 挡枪，
而 k 是无法同时为 i, j 挡枪的，如果 k 先为 i 挡了枪，那么之后就无法保证 j 的安全，反之亦然。
故据此复杂度可以做到 O(nm + n^3) 。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 404, maxm = 100005;
int a[maxm], b[maxm];
bool f[maxn][maxn], g[maxn];

int main() {
	int n = read, m = read;

	for(int i = 1; i <= m; i ++)
		read(a[i], b[i]);

	for(int i = 1; i <= n; i ++) {
		f[i][i] = 1;
		for(int j = m; j; j --) {
			if(f[i][a[j]] and f[i][b[j]]) {
				g[i] = 1;
				break;
			}
			if(f[i][a[j]] or f[i][b[j]])
				f[i][a[j]] = f[i][b[j]] = 1;
		}
	}

	int ans = 0;
	for(int i = 1; i < n; i ++)
		if(!g[i])
			for(int j = i + 1; j <= n; j ++)
				if(!g[j]) {
					for(int k = 1; k <= n; k ++)
						if(f[i][k] and f[j][k])
							goto FAIL;
					++ ans;
FAIL:;
				}

	printf("%d\n", ans);
}
