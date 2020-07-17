/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  echo -n '  ' && date +%Y.%m.%d # Just Run this (Type !!sh in Vim).

 * Solution:
  To be updated after "Accept".

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
#include <cstring>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef unsigned long long ull;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 400005;
char s[maxn], t[maxn];
ull a[maxn];

int main () {
	scanf("%s", s + 1);
	int n = int(strlen(s + 1)), ans = 0;
	while (n > 1) {
		if (s[n] == '0') -- n;
		else {
			s[++ n] = '0';
			int x = 0;
			for (int i = n; i; i --) {
				s[i] += (s[i - 1] == '1') + x;
				x = s[i] > '1';
				if (x) s[i] -= 2;
			}
			if (x) {
				for (int i = n; i; i --) s[i + 1] = s[i];
				s[1] = '1';
				++ n;
			}
			int p = n;
			while (s[p] == '1') s[p --] = '0';
			if (p == 0) {
				for (int i = n; i; i --) s[i + 1] = s[i];
				s[1] = '1';
				++ n;
			} else
				s[p] = '1';
		}
		++ ans;
		s[n + 1] = 0;
	}
	printf("%d\n", ans);
}
