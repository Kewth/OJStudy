#if 0
2019.11.06

NTT 可以用于求出特定位置上的点值，注意到模数 786433 = 2^18 * 3 + 1 ，一个原根为 g=10 。
将 A 填充为长为 2^18 的多项式，NTT 求点值，只能求出 10^{3k} 上的点值。
但是可以构造另外两个多项式 B(x) = A(10x) 和 C(x) = A(100x) ，
对 B 进行 NTT 可以求出 10^{3k} 在 A(10x) 上的值，即 10^{3k+1} 在 A(x) 上的值，
C 同理，那么通过 A, B, C 即可得出 1 ~ 786432 内所有点值，0 的点值需要特判。
这个方法应用到普遍情况的复杂度是 O(pk) ，其中 k 是 p 的 2 的因子个数。
但理论上仅把 A 补到足够 2 的整次幂，对 (mod - 1) / n 个多项式做 NTT ，
复杂度可以做到 O(plogn) 。
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

const int mod = 786433, len = 1 << 18;
ll a[len], b[len], c[len];
int ra[len];
ll G_len[len];
ll ans[mod];

void NTT(ll *A) {
	for(int i = 0; i < len; i ++)
		if(i < ra[i])
			std::swap(A[i], A[ra[i]]);

	for(int m = 1; m < len; m <<= 1)
		for(int i = 0; i < len; i += m << 1)
			for(int k = i; k < i + m; k ++) {
				ll A0 = A[k], A1 = A[k + m] *
					G_len[len / (m << 1) * (k - i)] % mod;
				A[k] = A0 + A1;
				A[k + m] = A0 - A1;
				if(A[k] >= mod) A[k] -= mod;
				if(A[k + m] < 0) A[k + m] += mod;
			}

}

int main() {
	for(int i = 0; i < len; i ++)
		ra[i] = ra[i >> 1] >> 1 | (len >> 1) * (i & 1);
	G_len[0] = 1;
	for(int i = 1; i < len; i ++)
		G_len[i] = G_len[i - 1] * 1000 % mod; // g * g * g
	/* debug("%lld\n", G_len[len - 1] * 1000 % mod); */

	int n = read;
	ll p1 = 1, p2 = 1, p3 = 1;
	for(int i = 0; i <= n; i ++) {
		a[i] = b[i] = c[i] = read;
		(b[i] *= p2) %= mod;
		(c[i] *= p3) %= mod;
		(p2 *= 10) %= mod;
		(p3 *= 100) %= mod;
	}
	ans[0] = a[0];

	NTT(a);
	NTT(b);
	NTT(c);

	/* for(int i = 0; i < len; i ++) */
	/* 	debug("%lld\n", a[i]); */

	for(int i = 0; i < len; i ++) {
		ans[G_len[i] * 1 % mod] = a[i];
		ans[G_len[i] * 10 % mod] = b[i];
		ans[G_len[i] * 100 % mod] = c[i];
	}

	/* for(int i = 0; i < mod; i ++) */
	/* 	debug("%lld\n", ans[i]); */

	int q = read;
	while(q --)
		printf("%lld\n", ans[read]);
}
