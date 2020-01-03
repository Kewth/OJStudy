#if 0
2020.01.02

考虑按照 n 的位置将排列分为左右两部分。
考虑左边能看到的 a 个数，除了 n 以外，
每个能看到的数和其覆盖的数构成的集合事实上构成一个圆排列，
因为这个集合的钦定了最大值在最左边。
右边同理，那么转换为组合问题就是将 n - 1 个数划分为 a - 1 + b - 1 个圆排列，
然后在这 a - 1 + b - 1 个圆排列中选 a - 1 个在 n 左边 b - 1 个在 n 右边。
用第一类斯特灵数和组合数即可解决这个问题。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 50005, maxk = 205, mod = 1000000007;
ll C[maxk][maxk];
ll s[maxn][maxk];

int main() {
	int N = 50000, K = 200;
	for(int i = 0; i <= K; i ++) {
		C[i][0] = 1;
		for(int j = 1; j <= i; j ++)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
	}
	s[0][0] = 1;
	for(int i = 1; i <= N; i ++) {
		for(int j = 1; j <= i and j <= K; j ++)
			s[i][j] = (s[i - 1][j] * (i - 1) + s[i - 1][j - 1]) % mod;
	}

	int T = read;
	while(T --) {
		int n = read, a = read, b = read;
		printf("%lld\n", C[a + b - 2][a - 1] * s[n - 1][a + b - 2] % mod);
	}
}
