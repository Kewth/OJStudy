#if 0
2019.11.02

三个区间长能构成三角形等价于每个区间长都小于总长的一半。
环的话按套路把区间复制一遍，
预处理 l[i] 表示以 i 为右端点最小的合法左端点， r[i] 表示以 i 为右端点的最大合法右端点。
假设枚举 a, b ，那么 b 需要满足 b - 1 <= r[a] ，
对应的 c 需要满足 c - 1 <= r[b] 且 a + n - 1 <= r[c] 即 c + 1 >= l[a + n - 1] 。
那么对应的 c 是一段区间 [l[a + n - 1], r[b] + 1] ，贡献也是可以确定的了。
但是枚举 (a, b) 复杂度是 O(n^2) 的，考虑只枚举 a ，算所有 b 的贡献，
满足限制的 b 同样是一端区间，那么此时的贡献就是 sum(r[b] - l[a + n - 1] + 2) ，
记 r 的前缀和后就可以直接算了。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 4000005;
int a[maxn];
int l[maxn], r[maxn];
int vis[maxn];
ll sr[maxn];

int main() {
	int n = read, m = (n - 1) >> 1, N = n << 1;
	for(int i = 1; i <= n; i ++)
		a[i] = a[n + i] = read;

	l[0] = 1;
	for(int i = 1; i <= N; i ++) {
		l[i] = std::max(l[i - 1], vis[a[i]] + 1);
		l[i] = std::max(l[i], i - m + 1);
		vis[a[i]] = i;
	}

	for(int i = 1; i <= n; i ++)
		vis[i] = N + 1;

	r[N + 1] = N;
	for(int i = N; i; i --) {
		r[i] = std::min(r[i + 1], vis[a[i]] - 1);
		r[i] = std::min(r[i], i + m - 1);
		vis[a[i]] = i;
	}

	/* for(int i = 1; i <= N; i ++) */
	/* 	debug("%d %d\n", l[i], r[i]); */

	for(int i = 1; i <= N; i ++)
		sr[i] = sr[i - 1] + r[i];

	ll ans = 0;
	for(int i = 1, j = 2; i <= n; i ++) {
		if(j <= i) j = i + 1;
		while(j <= r[i] and r[j] < l[i + n - 1] - 1)
			j ++;

		if(r[j] >= l[i + n - 1] - 1) {
			/* debug("%d %d\n", r[j + 1], l[i + n - 1] - 1); */
			int L = j, R = r[i] + 1;
			ans += sr[R] - sr[L - 1];
			ans -= 1ll * (R - L + 1) * (l[i + n - 1] - 2);
			/* debug("%d : %d %d -> %lld\n", i, L, R, ans); */
		}
	}

	ans /= 3;
	printf("%lld\n", ans);
}
