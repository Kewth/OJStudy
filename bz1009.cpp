#if 0
2019.12.25

一遍过感觉很流批。

注意到 m 很小，往这上面靠，朴素 dp 设 f[i][j] 表示考虑长度为 i 的串，
其后缀在 A 串最多匹配到 j 位，这样的 X 的方案数，
转移枚举添加字符然后 kmp 跳 fail 即可，复杂度 O(nm) 。
转移在第一维只从 i 到 i + 1 ，矩阵快速幂优化到 O(m^3logn) 。
#endif
#include <cstdio>
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

const int maxm = 22;
char s[maxm];
int fail[maxm];

struct Matrix {
	int a[maxm][maxm];
	Matrix() { memset(a, 0, sizeof a); }
};

int n, m, mod;
Matrix operator * (Matrix a, Matrix b) {
	Matrix c;
	for(int i = 0; i < m; i ++)
		for(int j = 0; j < m; j ++) {
			for(int k = 0; k < m; k ++)
				c.a[i][j] += a.a[i][k] * b.a[k][j];
			c.a[i][j] %= mod;
		}
	return c;
}

int main() {
	read(n, m, mod);
	scanf("%s", s + 1);

	fail[0] = -1;
	for(int i = 0; i < m; i ++) {
		int j = fail[i];
		while(~j and s[j + 1] != s[i + 1]) j = fail[j];
		fail[i + 1] = j + 1;
	}

	Matrix M;

	for(int i = 0; i < m; i ++) {
		for(char x = '0'; x <= '9'; x ++) {
			int j = i;
			while(~j and s[j + 1] != x) j = fail[j];
			++ M.a[i][j + 1];
		}
	}

	Matrix A;
	A.a[0][0] = 1;

	while(n) {
		if(n & 1) A = A * M;
		M = M * M;
		n >>= 1;
	}

	int ans = 0;
	for(int i = 0; i < m; i ++)
		ans += A.a[0][i];

	printf("%d\n", ans % mod);
}
