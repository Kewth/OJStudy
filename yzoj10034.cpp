#if 0
2019.12.30

暴力的做法是对于每个箱子构造数组 A 只有 A[0] 和 A[S] 为 1 ，
其中 S 是其包含的玩具的集合表示。
那么对于所有 A 的按位或卷积得到的 B ，B[S] 就是选出 S 集合的玩具的方案。
注意到 A 很稀疏，稀疏数组 FWT 即可，同样出现在 uoj310 。
卡 IO 可还行，scanf 换快读。
#endif
#include <cstdio>
#include <cctype>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () {
		int x = 0, c = getchar();
		while(!isdigit(c)) c = getchar();
		while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
		return x;
	}
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 1 << 20, mod = 1000000007;
inline void __a(int &a) { if(a >= mod) a -= mod; }
inline void __d(int &a) { if(a < 0) a += mod; }

void DWT(int *a, int n) {
	for(int m = 1; m < n; m <<= 1)
		for(int i = 0; i < n; i += m << 1)
			for(int k = i; k < i + m; k ++)
				__a(a[k + m] += a[k]);
}

void IDWT(int *a, int n) {
	for(int m = 1; m < n; m <<= 1)
		for(int i = 0; i < n; i += m << 1)
			for(int k = i; k < i + m; k ++)
				__d(a[k + m] -= a[k]);
}

int a[maxn], b[maxn], ans[20];
int power[maxn];

int main() {
	int n = read, m = read;

	for(int i = 1; i <= n; i ++) {
		int k = read, S = 0;
		while(k --) S |= 1 << read >> 1;
		++ a[0];
		++ a[S];
	}

	power[0] = 1;
	for(int i = 1; i <= n; i ++)
		__a(power[i] = power[i - 1] << 1);

	DWT(a, 1 << m);

	for(int x = 0; x < (1 << m); x ++)
		b[x] = power[a[x] - n];

	IDWT(b, 1 << m);

	for(int x = 0; x < (1 << m); x ++)
		__a(ans[__builtin_popcount(unsigned(x))] += b[x]);

	for(int k = 1; k <= m; k ++)
		printf("%d ", ans[k]);
	puts("");
}
