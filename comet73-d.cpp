#if 0
2019.11.10

扫描线从左到右，用 odt 维护当前扫描线上的覆盖情况，
即把执行到扫描线的操作的每个区间覆盖维护起来，
扫描线移动新增区间覆盖时，lower_bound 到它需要代替的区间并覆盖掉，
如果有区间与它有交，拆成两个区间，这样每次最坏情况增加 3 个区间，
那么每次暴力扫描被当前区间覆盖的区间并删掉，复杂度均摊下来是有保证的。
然后用树状数组维护每个时间的操作对当前扫描线上的区间覆盖的影响，
每次 odt 有区间加入或删除都在树状数组上做对应修改，
那么将查询离线挂在右端点上，扫描线扫到时直接在树状数组查一段区间和就好了。

（话说此前都不知道 odt 这玩意，yy 出来这个 set 维护连续区间的神奇做法）
#endif
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> Par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 1000005;
struct op {
	int l, r;
	ll v;
	int id;
};

ll bit[maxn];
int l[maxn], r[maxn], v[maxn];
/* std::vector<op> ve[maxn]; */
std::vector<Par> qu[maxn];
ll ans[maxn];

bool operator < (op x, op y) {
	if(x.l == y.l) return x.id < y.id;
	return x.l < y.l;
}

void modify(int k, ll x) {
	if(!k) return;
	while(k < maxn) {
		bit[k] += x;
		k += k & -k;
	}
}

ll query(int k) {
	ll res = 0;
	while(k) {
		res += bit[k];
		k -= k & -k;
	}
	return res;
}

op tmp[maxn];

int main() {
	int n = read, m = read, q = read;

	for(int i = 1; i <= n; i ++)
		read(l[i], r[i], v[i]);

	for(int i = 1; i <= q; i ++) {
		int x = read, y = read;
		qu[y].push_back(Par(x, i));
	}

	std::set<op> set;
	set.insert(op({1, m, 0, 0}));

	for(int i = 1; i <= n; i ++) {
		/* debug("%d\n", i); */

		op now({l[i], r[i], v[i], i});
		auto it = -- set.lower_bound(now);
		int tp = 0;

		while(it != set.end() and it -> l <= now.r) {
			tmp[++ tp] = *it;
			set.erase(it ++);
		}

		if(tmp[1].l < now.l) {
			set.insert(op({tmp[1].l, now.l - 1, tmp[1].v, tmp[1].id}));
			tmp[1].l = now.l;
		}

		if(tmp[tp].r > now.r) {
			set.insert(op({now.r + 1, tmp[tp].r, tmp[tp].v, tmp[tp].id}));
			tmp[tp].r = now.r;
		}

		for(int j = 1; j <= tp; j ++)
			modify(tmp[j].id, - tmp[j].v * (tmp[j].r - tmp[j].l + 1));

		set.insert(now);
		modify(now.id, now.v * (now.r - now.l + 1));

		for(auto p : qu[i])
			ans[p.second] = query(i) - query(p.first - 1);

		/* for(auto x : set) { */
		/* 	debug("%d %d %lld %d\n", x.l, x.r, x.v, x.id); */
		/* } */
	}

	for(int i = 1; i <= q; i ++)
		printf("%lld\n", ans[i]);
}
