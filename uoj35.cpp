#if 0
2019.12.31

sa + height 模板。
#endif
#include <cstdio>
#include <algorithm>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 100005;
char s[maxn];
int rank[maxn], sa[maxn], hi[maxn];
int tmp[maxn], sa2[maxn], t[1000005];
int queue[maxn], ql, qr;

int main() {
	scanf("%s", s + 1);
	int n = int(strlen(s + 1)), tot;

	for(int i = 1; i <= n; i ++) {
		rank[i] = s[i];
		sa2[i] = i;
	}

	for(int i = 1; i <= n; i ++) ++ t[s[i]];
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
		int &l = hi[rank[i]] = std::max(0, hi[rank[i - 1]] - 1);
		while(s[i + l] == s[sa[rank[i] - 1] + l]) ++ l;
	}

	for(int i = 1; i <= n; i ++)
		printf("%d ", sa[i]);
	puts("");
	for(int i = 2; i <= n; i ++)
		printf("%d ", hi[i]);
	puts("");
}
