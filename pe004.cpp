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
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

std::set<int> set;
void solve (int n) {
	printf("%d\n", *(-- set.lower_bound(n)));
}

int main () {
	set.insert(0);
	for (int x = 100; x < 1000; x ++)
		for (int y = (100000 + x - 1) / x; y < 1000; y ++) {
			int a = x * y, b[6];
			for (int i = 0, p = 1; i < 6; i ++, p *= 10)
				b[i] = a % (p * 10) / p;
			if (b[0] == b[5] and b[1] == b[4] and b[2] == b[3])
				set.insert(a);
		}

#ifdef PE
	solve(10000000);
#else
	int T = read;
	while (T --) solve(read);
#endif
}
