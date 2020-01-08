#if 0
2020.01.08

将整个图染黑白两色，满足相邻两个格子颜色不同，类似于国际象棋。
那么一个骨牌覆盖的一定是两个颜色不同的格子。
设两种颜色分别有 a, b 个，答案的一个下界就是 min(a, b) ，
可以证明这个下界是一定可以达到的。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 300005;
int a[maxn];

int main() {
	int n = read;
	for(int i = 1; i <= n; i ++)
		read(a[i]);

	ll x = 0, y = 0;
	for(int i = 1; i <= n; i ++)
		if(i & 1) {
			x += a[i] >> 1;
			y += (a[i] + 1) >> 1;
		} else {
			x += (a[i] + 1) >> 1;
			y += a[i] >> 1;
		}

	printf("%lld\n", std::min(x, y));
}
