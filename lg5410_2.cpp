/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.19

 * Solution:
  重温扩展 KMP ，这玩意实在太冷门了。

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

const int maxn = 20000005;
char s[maxn], t[maxn];
int z[maxn], lcp[maxn];

void exkmp (char *S, char *T, int N, int M, int *L, int *Z) {
	int l = 0, r = 0;
	for (int i = 1; i <= N; i ++) {
		L[i] = i <= r ? std::min(r - i + 1, Z[i - l + 1]) : 0;
		while (i + L[i] <= N and 1 + L[i] <= M and
				S[i + L[i]] == T[1 + L[i]]) ++ L[i];
		// XXX: checking "i > 1" is important when S == T
		if (i > 1 and i + L[i] - 1 > r) l = i, r = i + L[i] - 1;
	}
}

int main () {
	scanf("%s%s", s + 1, t + 1);
	int n = int(strlen(s + 1));
	int m = int(strlen(t + 1));
	exkmp(t, t, m, m, z, z);
	exkmp(s, t, n, m, lcp, z);
	ll a = 0, b = 0;
	for (int i = 1; i <= m; i ++) a ^= i * ll(z[i] + 1);
	for (int i = 1; i <= n; i ++) b ^= i * ll(lcp[i] + 1);
	printf("%lld\n%lld\n", a, b);
}
