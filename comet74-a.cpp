#if 0
2019.11.10

每个非 0 的 b[i] 对应的都是 a 中的一段区间和，并且所有区间不相交，相对顺序不变。
由于相对顺序不变，可以双指针维护，找到每个 b[i] 对应的区间，
特别的是如果一个 b[i] 对应的是长度为 1 的区间且恰为 a[i] ，这个区间对答案没有贡献。
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

const int maxn = 100005;
int a[maxn], b[maxn];

int main() {
	int T = read;
	while(T --) {
		int n = read;
		ll sa = 0, sb = 0;
		for(int i = 1; i <= n; i ++)
			sa += (a[i] = read);
		for(int i = 1; i <= n; i ++)
			sb += (b[i] = read);

		int ans = 0;
		if(sa == sb) {
			for(int i = 1, j = 0; i <= n; i ++)
				if(b[i]) {
					int now = 0;
					while(j < n and !a[j + 1]) ++ j;
					if(j + 1 == i and a[j + 1] == b[i]) {
						++ j;
						continue;
					}

					while(j < n and now < b[i])
						now += a[++ j];

					/* debug("%d : %d\n", i, j); */
					ans ++;
					if(now > b[i]) {
						/* debug("FAIL %d\n", i), */
						ans = -1;
						break;
					}
				}
		}

		else
			ans = -1;

		printf("%d\n", ans);
	}
}
