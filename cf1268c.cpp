#if 0
2020.01.08

过程可以分为两步：先保证 1 ~ k 相对顺序不变把它们移动到一个区间里，然后将其排序。
考虑从 f(k - 1) 到 f(k) 增加的操作次数，后者是很好计算的，一定增加 sum(p[k] + 1, n) 次，
其中 p[k] 是 k 的位置，sum(l, r) 是 [l, r] 中不超过 k 的数的个数。

对于前者，一定存在一个中心 cen ，其值为 a[cen] ，其他不超过 k 的数都向 cen 移动，
每个数 x 的操作次数就是 isum(p[x] + 1, cen - 1) 或 isum(cen + 1, p[x] - 1) ，
其中 isum(l, r) 是 [l, r] 中超过 k 的数的个数。
维护这个中心 cen ，当前 k 插入时，首先答案增加 k 到 cen 的代价，
然后对于数 x ，如果 k 在 a[cen] 和 x 之间，那么 x 到 cen 的代价会减一，
答案需要减去这样的 x 的个数。
然后考虑 cen 的移动，不难 cen 就是中位数，移动的时候维护答案即可。

维护方式只需要用树状数组维护 sum, isum 即可。
#endif
#include <cstdio>
#include <algorithm>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 200005;
int bit[maxn];

int query(int l, int r) {
	int res = 0;
	for(int k = r; k; k -= k & -k)
		res += bit[k];
	for(int k = l - 1; k; k -= k & -k)
		res -= bit[k];
	return res;
}

void modify(int p, int n) {
	for(int k = p; k <= n; k += k & -k)
		++ bit[k];
}

int a[maxn], p[maxn];
std::set<int> set;

int main() {
	int n = read;
	for(int i = 1; i <= n; i ++)
		p[a[i] = read] = i;

	int cen = p[1];
	ll ans = 0;
	modify(cen, n);
	set.insert(cen);
	printf("0");

	for(int x = 2; x <= n; x ++) {
		int np = p[x];
		modify(np, n);
		set.insert(np);
		ans += query(np + 1, n);
		int l = query(1, cen - 1), r = query(cen + 1, n);
		if(np > cen) {
			ans += np - cen + 1 - query(cen, np);
			ans -= query(np + 1, n);
			while(r > l) {
				int to = *set.upper_bound(cen);
				++ l;
				ans += 1ll * (to - cen - 1) * (l - r);
				-- r;
				cen = to;
				/* debug("%d -> %d\n", cen, to); */
			}
		}
		else {
			ans += cen - np + 1 - query(np, cen);
			ans -= query(1, np - 1);
			while(l > r) {
				int to = *(-- set.lower_bound(cen));
				++ r;
				ans += 1ll * (cen - to - 1) * (r - l);
				-- l;
				cen = to;
				/* debug("%d -> %d\n", cen, to); */
			}
		}
		printf(" %lld", ans);
		/* debug("cen = %d (%d %d)\n", cen, l, r); */
	}
	puts("");
}
