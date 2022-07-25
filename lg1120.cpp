/*
 * Author: Kewth

 * Date:
  2022.07.07

 * Solution:
  To be updated after "Accept".

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
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int W = 50;
int rem[W + 5];
int n, len;

ll TOT = 0;
void dfs (int s, int lst) {
	if (n == 0) {
		printf("%d\n", len);
		/* debug("TOT: %lld\n", TOT); */
		exit(0);
	}
	++ TOT;
	if (s == len) s = 0, lst = W;
	for (int i = lst; i; i --)
		if (rem[i] and s + i <= len) {
			-- rem[i], -- n;
			dfs(s + i, i);
			++ rem[i], ++ n;
			if (s == 0) return;
			if (s + i == len) return;
		}
}

int main () {
	read(n);
	int sum = 0;
	for (int i = 1; i <= n; i ++) {
		int x = read;
		sum += x;
		++ rem[x];
	}
	for (int x = 1; x <= sum; x ++)
		if (sum % x == 0) {
			len = x;
			TOT = 0;
			/* debug("%d\n", x); */
			dfs(0, W);
			/* debug("TOT: %lld\n", TOT); */
		}
}
