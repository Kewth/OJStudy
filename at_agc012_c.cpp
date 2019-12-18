#if 0
2019.12.17

醉了，一开始有个 sb 想法，结果最坏 s 的长度可以被卡到 700+ ，就不说了。
构造，s 前半部分是 1 到 p 的排列，后半部分是 1 到 p 升序。
那么 s 满足条件的子序列数就是前半部分的上升子序列数，
从小到大构造前半部分，对于当前数 x ，加到左边会使得上升子序列 +1 ，右边会使之 x2 。
注意这样会将空集算作一个子序列，把 n + 1 即可。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef unsigned long long ull;

struct {
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 205;
int L[maxn], R[maxn], lp, rp;
int p = 0;

void work(ll n) {
	if(n == 1) return;
	if(n & 1) {
		L[++ lp] = ++ p;
		work(n ^ 1);
	} else {
		R[++ rp] = ++ p;
		work(n >> 1);
	}
}

int main() {
	work(read + 1);
	printf("%d\n", p << 1);
	for(int i = 1; i <= lp; i ++)
		printf("%d ", p - L[i] + 1);
	for(int i = rp; i; i --)
		printf("%d ", p - R[i] + 1);
	for(int i = 1; i <= p; i ++)
		printf("%d ", i);
	puts("");
}
