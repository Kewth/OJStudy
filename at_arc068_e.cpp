#if 0
2019.12.06

枚举 d ，将 m + 1 个位置每 d 个分为一段，每段的左端点是停车位置。
那么区间 [l, r] 能贡献当且仅当 l - 1 和 r 所在的段不同。
再枚举 l - 1 所在的段，然后查询 l - 1 在该段有多少区间的 r 在这段之后，
用主席树维护区间来支持这个查询即可。
复杂度是个调和级数乘上主席树的复杂度。
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

const int maxn = 300005;
int al[maxn], ar[maxn];
std::vector<int> tor[maxn];

struct Tree {
	int lti, rti;
	int val;
};
#define self pool[now]
#define lt pool[self.lti]
#define rt pool[self.rti]
Tree pool[maxn * 20];
int pp;

void lain(int &now, int L, int R, int p) {
	pool[++ pp] = self;
	now = pp;
	++ self.val;
	if(L == R) return;
	int M = (L + R) >> 1;
	if(p <= M) lain(self.lti, L, M, p);
	else lain(self.rti, M + 1, R, p);
}

int query(int now, int L, int R, int l, int r) {
	if(!now or r < L or l > R) return 0;
	if(l <= L and R <= r) return self.val;
	int M = (L + R) >> 1;
	return query(self.lti, L, M, l, r) + query(self.rti, M + 1, R, l, r);
}

int T[maxn];

int main() {
	int n = read, m = read;

	for(int i = 1; i <= n; i ++) {
		read(al[i], ar[i]);
		tor[al[i]].push_back(ar[i]);
	}

	for(int l = 0; l <= m; l ++) {
		if(l) T[l] = T[l - 1];
		for(int r : tor[l])
			lain(T[l], 0, m, r);
	}

	for(int d = 1; d <= m; d ++) {
		int ans = 0;
		for(int t = 0; t <= m / d; t ++) {
			int l = t * d + 1, r = t * d + d;
			/* for(int i = 1; i <= n; i ++) */
			/* 	if(l <= al[i] and al[i] <= r and ar[i] >= r) */
			/* 		++ ans; */
			ans += query(T[r], 0, m, r, m) - query(T[l - 1], 0, m, r, m);
		}
		printf("%d\n", ans);
	}
}
