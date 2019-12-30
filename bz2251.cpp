#if 0
2019.12.30

可能 SA 比较适合做有关字典序的问题？反正这题用 SAM 的话估计会麻烦点。
考虑通过后缀排序枚举所有本质不同的子串，枚举方式是根据 sa 和 height 去重，
即枚举 sa[i] 开头的子串时跳过前面 height[i] 个子串，
因为这些子串都在 sa[i - 1] 处被统计了。
这样就可以按照字典序大小枚举所有本质不同的子串。
然后对于出现次数暴力跑 height 最小值即可，n 很小，可以接受。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 3030;
char s[maxn];
int rank[maxn], sa[maxn], hi[maxn];
int tmp[maxn], sa2[maxn], t[maxn];
int min[maxn];

int main() {
	int n = read, tot;
	scanf("%s", s + 1);

	for(int i = 1; i <= n; i ++) {
		rank[i] = s[i];
		sa2[i] = i;
	}
	for(int i = 1; i <= n; i ++) ++ t[rank[i]];
	for(int i = 1; i <= 256; i ++) t[i] += t[i - 1];
	for(int i = n; i; i --) sa[t[rank[sa2[i]]] --] = sa2[i];
	std::fill(t + 1, t + 257, 0);
	rank[sa[1]] = tot = 1;
	for(int i = 2; i <= n; i ++)
		rank[sa[i]] = s[sa[i]] == s[sa[i - 1]] ? tot : ++ tot;

	for(int m = 1; tot < n; m <<= 1) {
		int p = 0;
		for(int i = 1; i <= m; i ++) sa2[++ p] = n - m + i;
		for(int i = 1; i <= n; i ++) if(sa[i] > m) sa2[++ p] = sa[i] - m;
		for(int i = 1; i <= n; i ++) ++ t[rank[i]];
		for(int i = 1; i <= tot; i ++) t[i] += t[i - 1];
		for(int i = n; i; i --) sa[t[rank[sa2[i]]] --] = sa2[i];
		std::fill(t + 1, t + tot + 1, 0);
		std::copy(rank + 1, rank + n + 1, tmp + 1);
		rank[sa[1]] = tot = 1;
		for(int i = 2; i <= n; i ++)
			rank[sa[i]] = (tmp[sa[i]] == tmp[sa[i - 1]] and
					tmp[sa[i] + m] == tmp[sa[i - 1] + m]) ? tot : ++ tot;
	}

	for(int i = 1; i <= n; i ++) {
		int &k = hi[rank[i]] = std::max(0, hi[rank[i - 1]] - 1);
		while(s[i + k] == s[sa[rank[i] - 1] + k]) ++ k;
	}

	for(int i = 1; i <= n; i ++) {
		min[i] = 1000000000;
		for(int j = i + 1; j <= n; j ++)
			min[j] = std::min(min[j - 1], hi[j]);
		int l = hi[i] + 1, r = n - sa[i] + 1;
		int R = n;
		for(int j = l; j <= r; j ++) {
			while(min[R] < j) -- R;
			if(R > i) printf("%d\n", R - i + 1);
		}
	}
}
