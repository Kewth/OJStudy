/*
 * Author: Kewth

 * Date:
  2020.08.24

 * Solution:

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int N = 1000005;
int nop[N + 1], pr[N + 1], pp;

void solve (int n) {
	printf("%d\n", pr[n]);
}

int main () {
	for (int i = 2; i <= N; i ++)
		if (!nop[i]) {
			pr[++ pp] = i;
			if (i <= N / i)
				for (int j = i * i; j <= N; j += i)
					nop[j] = 1;
		}

#ifdef PE
	solve(10001);
#else
	int T = read;
	while (T --) solve(read);
#endif
}
