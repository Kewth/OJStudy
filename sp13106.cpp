#if 0
date +%Y.%m.%d

暴力的做法是对于每个箱子构造数组 A 只有 A[0] 和 A[S] 为 1 ，
其中 S 是其包含的玩具的集合表示。
那么对于所有 A 的按位或卷积得到的 B ，B[2^m-1] 就是答案。
注意到 A 很稀疏，稀疏数组 FWT 即可，同样出现在 uoj310 。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
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

int a[maxn], ans[maxn];
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
		ans[x] = power[a[x] - n];

	IDWT(ans, 1 << m);
	printf("%d\n", ans[(1 << m) - 1]);
}
