/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.08

 * Solution:
    倒着考虑，假设处理完了后 i 个操作，设 S 表示如果 0 要获胜，前 n - i 个操作后 X 的
取值集合，对于第 n - i - 1 个操作，设 T 表示将 S 内所有数都异或 a[n - i - 1] 后的结果，
那么可以发现，如果该轮是 0 操作，有 S = S or T ，否则，有 S = S and T 。
    直接维护 S 是不现实的，事实上只需要维护一组线性基，如果 0 操作就是加入一个向量，否
则对于操作的向量 v ，如果 v 无法被线性基表出，那么 S 直接变成空集，一定无解，否则 v 能
被表出，说明 T = S ，没有影响。

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
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 205, maxk = 62;
ll bas[maxk];
ll a[maxn];
char s[maxn];

void insert (ll x) {
	for (int k = 0; k < maxk; k ++)
		if (x >> k & 1) {
			if (bas[k]) x ^= bas[k];
			else return bas[k] = x, void();
		}
}

bool query (ll x) {
	for (int k = 0; k < maxk; k ++)
		if (x >> k & 1) {
			if (bas[k]) x ^= bas[k];
			else return 0;
		}
	return 1;
}

int main () {
	int T = read;
	while (T --) {
		int n = read;
		for (int i = 1; i <= n; i ++) read(a[i]);
		std::fill(bas, bas + maxk, 0);
		scanf("%s", s + 1);
		for (int i = n; i; i --)
			if (s[i] == '0')
				insert(a[i]);
			else {
				if (!query(a[i])) {
					puts("1");
					goto fail;
				}
			}
		puts("0");
fail:;
	}
}
