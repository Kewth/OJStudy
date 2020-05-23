#if 0
2020.05.23

  容易发现只要知道任意一个数就能得出整个序列，从 M[1][2], M[1][3], M[2][3] 中解出 A[1] 即可。
        ▁▃▄▄▄▃▃▃▃▄▶
      ▗▇▀▔    ▔▔▔▔
     ▄▛   ▃▅━━■▄▂
    ▟▊   ▐▘     ▀▙
   ▟▜▌   ▐▖   ▋  ▐▍
  ▟▘ ▜   ▝▀▇▆●▘  ▐▌
▗▟▘   ▜▃       ▁▅▛
▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔   CopyRight :)
      ▔▔▔▔▔▔
#endif
#include <cstdio>
#include <cmath>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 1005;
int M[maxn][maxn];

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++)
			read(M[i][j]);

	int x = int(sqrtl(1ll * M[1][2] * M[1][3] / M[2][3]));

	printf("%d", x);
	for (int i = 2; i <= n; i ++)
		printf(" %d", M[1][i] / x);
	puts("");
}
