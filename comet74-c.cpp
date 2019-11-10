#pragma GCC optimize(3)
#if 0
2019.11.09

先不考虑修改，考虑每个数 a[i] 对答案的贡献，
如果它在攻击序列中排第 k 大，那么贡献是 a[i] / 2^k ，
这种情况的概率是 C(rank - 1, k - 1) / 2^rank ，其中 rank 是 a[i] 在 a 的大小排名。
根据二项式定理可以化简，得到贡献是 a[i] * (3 / 4)^rank / 3 。
维护 a[i] 的排序后的序列，那么每次修改可以分成两个部分：删掉原来的 a[i] 和加上新的 a[i] 。
这两个部分都会对排序后连续的一段的贡献造成影响（因为 rank 会改变），会乘或除 3/4 。
用权值线段树或者平衡树维护即可，需要支持区间乘法和整体求和。
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

const int maxn = 100005, mod = 998244353;
struct Treap {
	ll val, sum, tag;
	ll key;
	int size, weight;
	int lti, rti;
};
#define self pool[now]
#define lt pool[self.lti]
#define rt pool[self.rti]
Treap pool[maxn];

inline void mul(int now, ll x) {
	if(now) {
		(self.tag *= x) %= mod;
		(self.sum *= x) %= mod;
		(self.val *= x) %= mod;
	}
}

inline void push_down(int now) {
	if(self.tag == 1) return;
	mul(self.lti, self.tag);
	mul(self.rti, self.tag);
	self.tag = 1;
}

inline void update(int now) {
	self.sum = (lt.sum + self.val + rt.sum) % mod;
	self.size = lt.size + rt.size + 1;
}

void split(int now, ll k, int &a, int &b) {
	if(!now)
		a = b = 0;
	else {
		push_down(now);
		if(k < self.key) {
			split(self.lti, k, a, self.lti);
			b = now;
		}
		else {
			split(self.rti, k, self.rti, b);
			a = now;
		}
		update(now);
	}
}

int merge(int a, int b) {
	if(!a) return b;
	if(!b) return a;
	if(pool[a].weight > pool[b].weight) {
		push_down(a);
		pool[a].rti = merge(pool[a].rti, b);
		update(a);
		return a;
	}
	else {
		push_down(b);
		pool[b].lti = merge(a, pool[b].lti);
		update(b);
		return b;
    }
}

inline ll power(ll x, int k) {
	if(k < 0) k += mod - 1;
	ll res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

const ll quarter3 = 3 * power(4, -1) % mod;
/* const ll quarter3 = 2; */
const ll invqu = power(quarter3, -1);

int T;
void insert(int now, int x) {
	self.key = 100000000ll * x + now;
	self.sum = self.val = x;
	self.weight = rand();
	self.tag = 1;
	self.size = 1;

	int a, b;
	split(T, self.key, a, b);
	mul(a, quarter3);
	mul(now, power(quarter3, pool[b].size + 1));
	T = merge(a, merge(now, b));
}

void erase(int now) {
	int a, b, c;
	split(T, self.key, a, c);
	split(a, self.key - 1, a, b);
	mul(a, invqu);
	T = merge(a, c);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("relation.in", "r", stdin);
	freopen("relation.out", "w", stdout);
#endif

	pool[0].tag = 1;
	pool[0].weight = rand();

	int n = read;
	for(int now = 1; now <= n; now ++)
		insert(now, read);

	ll base = power(3, -1) % mod;

	printf("%lld\n", pool[T].sum * base % mod);

	int q = read;
	while(q --) {
		int p = read;
		erase(p);
		insert(p, read);
		printf("%lld\n", pool[T].sum * base % mod);

		/* for(int now = 1; now <= n; now ++) */
		/* 	debug("%d: v=%lld sum=%lld t=%lld l=%d r=%d si=%d k=%lld\n", */
		/* 			now, self.val, self.sum, self.tag, */
		/* 			self.lti, self.rti, self.size, self.key); */
	}
}
