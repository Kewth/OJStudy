#if 0
2019.12.08

不妨设 n > 1 。

如果所有 a[i] 都是奇数，那么先手操作后会有一个偶数，约分后仍然有唯一偶数，
此时后手一定可以对唯一偶数操作，所有数成为奇数，约分后同样如此，
直到所有数都为 1 ，仍然没有偶数，那么当 a[i] 全是奇数时先手必败。

更一般的，假设 n 足够大奇数足够多，如果有偶数个偶数，
先手操作后有奇数个偶数，后手一定可以对偶数操作使得状态还原至奇数个偶数，
也就是说有奇数个偶数时先手必胜，反之先手必败。

特别的是，如果有偶数个偶数且奇数唯一且该奇数大于 1 ，
此时先手对唯一奇数操作后，所有数都是偶数，
此时一定可以约分，并且约分后的结果是难以推断的。
由于这种情况一定可以约分，那么所有数至少缩小一半，也就是最多进行 O(logn) 次，
每次碰到这种情况暴力约分即可，直到转为上述可以直接判断的情况。
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

const int maxn = 100005;
int a[maxn];

bool game(int n) {
	if(n == 1) return a[1] > 1;

	int even = 0;
	for(int i = 1; i <= n; i ++)
		if(!(a[i] & 1))
			++ even;

	if(even & 1) return 1;
	if(even != n - 1) return 0;

	for(int i = 1; i <= n; i ++)
		if(a[i] & 1) {
			if(a[i] == 1) return 0;
			-- a[i];
		}

	int gcd = a[1];
	for(int i = 2; i <= n; i ++)
		gcd = std::__gcd(gcd, a[i]);

	for(int i = 1; i <= n; i ++)
		a[i] /= gcd;

	return !game(n);
}

int main() {
	int n = read;

	for(int i = 1; i <= n; i ++)
		read(a[i]);

	puts(game(n) ? "First" : "Second");
}
