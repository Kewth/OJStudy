#if 0
2020.04.09

把每个点看做一个二次函数，不难发现对于相邻两个二次函数，
如果前者对称轴比后者大，那么它们的 x 总是相同。
对于这样的相邻二次函数，把它们合并为一个二次函数，直到对称轴单调不减为止。
此时每个二次函数都可以取到最小值，就得到了一个 O(nm) 的做法。

考虑快速处理修改 a[k] = x 。
预处理出 1 ~ k - 1 和 k + 1 ~ n 的二次函数单调栈，那么相当于在两个单调栈之间插入 a[k] 。
与 a[k] 合并的一定是前面单调栈的一段后缀和后面单调栈的一段前缀。
这两段长度具有一定的单调性，可以先二分前者长度，再通过二分后者长度进行 check 。
由于为了在线回答询问，需要维护可持久化单调栈，那么一次询问的总复杂度是 3 个 log 。
是时候对于第二个二分可以放在可持久化数组（主席树）上进行，复杂度将为 2 个 log 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef __int128 big;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 100005, mod = 998244353;
ll inv[maxn * 4];

struct Func {
	ll a, b, c;
	ll val () {
		ll B = b % mod + mod;
		return (c + (mod - B) * B % mod * inv[a * 4]) % mod;
	}
	Func () { }
	Func (ll x): a(1), b(-2 * x), c(x * x % mod) { }
	Func (ll a, ll b, ll c): a(a), b(b), c(c) { }
};
inline bool operator < (Func A, Func B) { return A.b * big(-2 * B.a) < B.b * big(-2 * A.a); }
inline Func operator + (Func A, Func B) { return Func(A.a + B.a, A.b + B.b, A.c + B.c); }
inline Func operator - (Func A, Func B) { return Func(A.a - B.a, A.b - B.b, A.c - B.c); }
Func a[maxn], s[maxn];

struct Tree {
	int lti, rti;
	Func val, lval;
	ll sum;
} pool[maxn * 40];
int pp;
#define self pool[now]
#define lt pool[self.lti]
#define rt pool[self.rti]

void modify (int &now, int L, int R, int p, Func x) {
	pool[++ pp] = self;
	now = pp;
	if (L == R) return self.val = self.lval = x, self.sum = x.val(), void();
	int M = (L + R) >> 1;
	if (p <= M) modify(self.lti, L, M, p, x);
	else modify(self.rti, M + 1, R, p, x);
	self.val = lt.val + rt.val;
	self.lval = lt.lval;
	self.sum = lt.sum + rt.sum;
}

Func query1 (int now, int L, int R, int l, int r) {
	if (r < L or l > R or !now) return Func(0, 0, 0);
	if (l <= L and R <= r) return self.val;
	int M = (L + R) >> 1;
	return query1(self.lti, L, M, l, r) + query1(self.rti, M + 1, R, l, r);
}

ll query2 (int now, int L, int R, int l, int r) {
	if (r < L or l > R or !now) return 0;
	if (l <= L and R <= r) return self.sum;
	int M = (L + R) >> 1;
	return query2(self.lti, L, M, l, r) + query2(self.rti, M + 1, R, l, r);
}

int n;
inline Func at (int st, int k) { return query1(st, 1, n, k, k); }

int pre[maxn], suf[maxn];
int presp[maxn], sufsp[maxn];

void init_pre () {
	for (int i = 1; i <= n; i ++) {
		int &st = pre[i] = pre[i - 1];
		int &sp = presp[i] = presp[i - 1];
		Func now = a[i];
		while (sp and now < at(st, sp))
			now = now + at(st, sp --);
		modify(st, 1, n, ++ sp, now);
	}
}

void init_suf () {
	for (int i = n; i; i --) {
		int &st = suf[i] = suf[i + 1];
		int &sp = sufsp[i] = sufsp[i + 1];
		Func now = a[i];
		while (sp and at(st, sp) < now)
			now = now + at(st, sp --);
		modify(st, 1, n, ++ sp, now);
	}
}

Func tmp_f;
int find (int now, int L, int R, int p) {
	if (R <= p) {
		if (self.lval < tmp_f + self.val - self.lval)
			return tmp_f = tmp_f + self.val, 0;
	}
	if (L == R) return R;
	int M = (L + R) >> 1, res = 0;
	if (M + 1 <= p) res = find(self.rti, M + 1, R, p);
	if (res) return res;
	return find(self.lti, L, M, p);
}

/* int find_r (int k, int lp) { */
/* 	Func tmp = query1(pre[k - 1], 1, n, lp + 1, presp[k - 1]); */
/* 	int st = suf[k + 1], sp = sufsp[k + 1]; */
/* 	int l = 0, r = sp; */
/* 	while (l < r) { */
/* 		int mid = (l + r + 1) >> 1; */
/* 		Func now = a[k] + tmp + query1(st, 1, n, mid + 1, sp); */
/* 		if (!(at(st, mid) < now)) */
/* 			tmp_f = now, l = mid; */
/* 		else */
/* 			r = mid - 1; */
/* 	} */
/* 	if (!r) tmp_f = a[k] + tmp + query1(st, 1, n, 1, sp); */
/* 	return r; */
/* } */

int tmp_R;
Func tmp_tmp_f;
int find_l_r (int k) {
	int st = pre[k - 1], sp = presp[k - 1];
	int l = 0, r = sp;
	while (l < r) {
		int mid = (l + r + 1) >> 1;
		tmp_f = a[k] + query1(st, 1, n, mid + 1, sp);
		int R = find(suf[k + 1], 1, n, sufsp[k + 1]);
		if (!(tmp_f < at(st, mid)))
			tmp_tmp_f = tmp_f, tmp_R = R, l = mid;
		else
			r = mid - 1;
	}
	if(!l) {
		tmp_f = a[k] + s[k - 1];
		tmp_R = find(suf[k + 1], 1, n, sufsp[k + 1]);
		tmp_tmp_f = tmp_f;
	}
	return l;
}

int main () {
	read(n);
	inv[1] = 1;
	for (int i = 2; i <= n * 4; i ++)
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;

	int q = read;
	for (int i = 1; i <= n; i ++)
		a[i] = Func(read);
	for (int i = 1; i <= n; i ++)
		s[i] = s[i - 1] + a[i];

	init_pre();
	init_suf();

	/* for (int i = 1; i <= n; i ++) */
	/* 	debug(">%lld %d\n", query2(pre[i], 1, n, 1, presp[i]) % mod, presp[i]); */
	/* for (int i = n; i; i --) */
	/* 	debug(">%lld %d\n", query2(suf[i], 1, n, 1, sufsp[i]) % mod, sufsp[i]); */

	printf("%lld\n", query2(pre[n], 1, n, 1, presp[n]) % mod);

	while (q --) {
		int k = read;
		Func x(read);
		std::swap(a[k], x);
		int lp = find_l_r(k), rp = tmp_R;
		/* debug("%d %d\n", lp, rp); */
		printf("%lld\n",
				(query2(pre[k - 1], 1, n, 1, lp) +
				query2(suf[k + 1], 1, n, 1, rp) +
				tmp_tmp_f.val()) % mod);
		std::swap(a[k], x);
	}
}
