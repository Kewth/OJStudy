/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.07.13

 * Solution:
  首先贡献分离到每个点，问题转换为对于一个节点求它在最后被标记的概率。
  对于一个节点，每一时刻其状态可分为三种：有标记，没标记但祖先有标记，自己和祖先都没有
标记，之所以要把祖先是否有标记考虑在内，是因为一次操作后祖先的标记可能下传到当前节点，
这是需要在转移中考虑的。
  而一次操作按对于状态的改变分类，有五种不同的转移：
   a. 自己是操作节点
   c. 子树有操作节点且非 a
   d. 兄弟节点的子树有操作节点且非 a, c
   b. 祖先有操作节点且非 a, c, d
   e. 非 a, b, c, d
  对于每个节点分别计算出这五种转移的概率，然后矩阵快速幂 DP 即可。
  五种转移的概率计算较为繁琐，略去。

 * Digression:

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 400005, mod = 998244353;
ll a[maxn], b[maxn], c[maxn], d[maxn], e[maxn];
int ls[maxn], rs[maxn];
int N, M, ip = 1;

inline ll power (ll x, int k) {
	if (k < 0) k += mod - 1;
	ll res = 1;
	while (k) {
		if (k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

ll coe;
int build (int x, int l, int r) {
	/* debug("%d : %d %d\n", x, l, r); */
	c[x] = ll(r - l) * (l + N + N - r + 1) / 2 % mod * coe % mod;
	e[x] = mod + (1 - mod - a[x] - b[x] - c[x] - d[x]) % mod;
	if (l < r) {
		int m = read;
		ls[x] = ++ ip;
		rs[x] = ++ ip;
		a[ls[x]] = coe * l % mod * (r - m) % mod;
		a[rs[x]] = coe * (m + 1 - l) % mod * (N - r + 1) % mod;
		d[ls[x]] = ll(N - r + 1 + N - m) * (r - m) / 2 % mod * coe % mod;
		d[rs[x]] = ll(l + m) * (m - l + 1) / 2 % mod * coe % mod;
		b[ls[x]] = b[rs[x]] = (a[x] + b[x]) % mod;
		build(ls[x], l, m);
		build(rs[x], m + 1, r);
	}
	return x;
}

struct Matrix { ll x[3][3]; };
Matrix operator * (Matrix A, Matrix B) {
	Matrix C;
	for (int i = 0; i < 3; i ++)
		for (int j = 0; j < 3; j ++) {
			C.x[i][j] = 0;
			for (int k = 0; k < 3; k ++)
				C.x[i][j] += A.x[i][k] * B.x[k][j];
			C.x[i][j] %= mod;
		}
	return C;
}

ll Ans;
void solve (int x) {
	if (!x) return;
	/* debug("%d : %lld %lld %lld %lld %lld\n", x, */
	/* 		a[x] * power(coe, -1) % mod, */
	/* 		b[x] * power(coe, -1) % mod, */
	/* 		c[x] * power(coe, -1) % mod, */
	/* 		d[x] * power(coe, -1) % mod, */
	/* 		e[x] * power(coe, -1) % mod); */
	solve(ls[x]);
	solve(rs[x]);

	Matrix A, B;
	A.x[0][0] = 0;
	A.x[0][1] = 0;
	A.x[0][2] = 1;
	for (int i = 1; i < 3; i ++)
		for (int j = 0; j < 3; j ++)
			A.x[i][j] = 0;

	B.x[0][0] = a[x] + b[x] + d[x] + e[x];
	B.x[0][1] = 0;
	B.x[0][2] = c[x];
	B.x[1][0] = a[x] + d[x];
	B.x[1][1] = b[x] + e[x];
	B.x[1][2] = c[x];
	B.x[2][0] = a[x];
	B.x[2][1] = b[x];
	B.x[2][2] = c[x] + d[x] + e[x];
	for (int i = 0; i < 3; i ++)
		for (int j = 0; j < 3; j ++)
			B.x[i][j] %= mod;

	int k = M;
	while (k) {
		if (k & 1) A = A * B;
		B = B * B;
		k >>= 1;
	}
	Ans += A.x[0][0];
}

int main () {
	read(N, M);
	coe = power(ll(N + 1) * N / 2 % mod, -1);
	a[1] = coe;
	/* c[1] = mod + 1 - coe; */
	build(1, 1, N);
	solve(1);
	Ans %= mod;
	printf("%lld\n", Ans);
}
