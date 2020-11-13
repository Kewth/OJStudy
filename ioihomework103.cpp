/*
 * Author: Kewth

 * Date:
  2020.11.06

 * Solution:
  In blog.

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

const int maxn = 100005;
char ans[maxn];

void work (int p, int n, int a, int b, int c) {
	for (int i = 1; i <= a; i ++)
		ans[(p += 2) % n] = 'B';
	for (int i = 1; i <= c / 2; i ++) {
		ans[(p += 2) % n] = 'B';
		ans[(p += 2) % n] = 'G';
	}
	for (int i = 1; i <= b; i ++)
		ans[(p += 2) % n] = 'G';
}

int main () {
	int n = read, a = read, b = read, c = a + b - n;
	a -= c, b -= c;
	if (a < 0 or b < 0 or c < 0 or c & 1)
		return puts("Impossible"), 0;
	/* debug("%d %d %d\n", a, b, c); */

	if (n & 1) {
		if (!c and a and b)
			return puts("Impossible"), 0;
		work(0, n, a, b, c);
	}

	else {
		if (c == 0) {
			if (a and b) {
				if (a != n / 2)
					return puts("Impossible"), 0;
				work(0, n, n / 2, 0, 0);
				work(1, n, 0, n / 2, 0);
			}
			else if (a) {
				work(0, n, n / 2, 0, 0);
				work(1, n, n / 2, 0, 0);
			} else if (b) {
				work(0, n, 0, n / 2, 0);
				work(1, n, 0, n / 2, 0);
			}
		}
		if (c == 2) {
			if (a >= n / 2) {
				work(0, n, n / 2, 0, 0);
				work(1, n, a - n / 2, b, c);
			} else if (b >= n / 2) {
				work(0, n, 0, n / 2, 0);
				work(1, n, a, b - n / 2, c);
			} else
				return puts("Impossible"), 0;
		}
		if (c >= 4) {
			if (c == n and n / 2 & 1)
				return puts("Impossible"), 0;
			int c1 = std::min(c - 2, (n / 2) - (n / 2) % 2);
			int a1 = std::min(a, n / 2 - c1), b1 = n / 2 - a1 - c1;
			work(0, n, a1, b1, c1);
			work(1, n, a - a1, b - b1, c - c1);
		}
	}

	puts(ans);
	int B = 0, G = 0;
	for (int i = 0; i < n; i ++) {
		if (ans[(i + n - 1) % n] == 'B' or ans[(i + 1) % n] == 'B')
			++ B;
		if (ans[(i + n - 1) % n] == 'G' or ans[(i + 1) % n] == 'G')
			++ G;
	}
	if (B != a + c or G != b + c) return 1;
}
