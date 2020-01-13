#if 0
2020.01.12

设 f[n] 表示答案，递推式显然，但是转移系数有个 10^k 其中 k 不是定值。
但是 k 很小可以枚举，对 k 分类用不同的转移矩阵优化转移即可。
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

int mod;
struct Matrix {
	ll v[3][3];
	Matrix() { memset(v, 0, sizeof v); }
};
Matrix operator * (Matrix a, Matrix b) {
	Matrix c;
	for(int i = 0; i < 3; i ++)
		for(int j = 0; j < 3; j ++) {
			for(int k = 0; k < 3; k ++)
				c.v[i][j] += a.v[i][k] * b.v[k][j];
			c.v[i][j] %= mod;
		}
	return c;
}

int main() {
	ll n = read;
	read(mod);

	Matrix a;
	a.v[0][2] = 1;

	ll pow10 = 10;
	while(1) {
		Matrix m;
		m.v[0][0] = pow10 % mod;
		m.v[1][0] = 1;
		m.v[1][1] = 1;
		m.v[2][0] = 1;
		m.v[2][1] = 1;
		m.v[2][2] = 1;

		ll k = std::min(n, pow10 - 1) - pow10 / 10 + 1;
		while(k) {
			if(k & 1) a = a * m;
			m = m * m;
			k >>= 1;
		}

		if(n < pow10) break;
		pow10 *= 10;
	}

	printf("%lld\n", a.v[0][0]);
}
