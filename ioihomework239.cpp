/*
 * Author: Kewth

 * Date:
  2020.11.14

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
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxr = 3005, maxc = 6005;
char map[maxr << 1][maxc << 1];
int L[maxr][maxc], U[maxr][maxc], F[maxr][maxc];
int bit[maxc];
std::vector<int> lazy[maxc << 1];

inline bool has (int i, int j) { return map[i][j] and map[i][j] != ' '; }

inline void add (int p, int n, int x) {
	for (int k = p; k <= n; k += k & -k)
		bit[k] += x;
}
inline int query (int l, int r) {
	int res = 0;
	for (int k = r; k; k -= k & -k)
		res += bit[k];
	for (int k = l - 1; k; k -= k & -k)
		res -= bit[k];
	return res;
}

#define I (i * 2 - 1)
#define J (j * 2 - 1)
ll solve (int R, int C) {
	ll res = 0;
	for (int i = 1; i <= R; i ++) {
		std::fill(bit, bit + C + 1, 0);
		std::fill(lazy, lazy + C + 1, std::vector<int>());
		for (int j = 1; j <= C; j ++)
			if (map[I][J] == 'x') {
				L[i][j] = has(I, J - 1) ? L[i][j - 2] + 1 : 0;
				U[i][j] = has(I - 1, J - 1) ? U[i - 1][j - 1] + 1 : 0;
				F[i][j] = has(I - 1, J + 1) ? F[i - 1][j + 1] + 1 : 0;
				int d = std::min(L[i][j], U[i][j]);
				add(j, C, +1);
				lazy[j + F[i][j] * 2].push_back(j);
				if (j > 1)
					res += query(j - d * 2, j - 2);
				/* if (j > 1 and query(j - d * 2, j - 2)) */
				/* 	debug("%d %d : %d %d\n", i, j, d, query(j - d * 2, j - 2)); */
				for (int k : lazy[j])
					add(k, C, -1);
			} else
				L[i][j] = U[i][j] = 0;
	}
	return res;
}

int main () {
	int R = read, C = read;
	for (int i = 0; i <= R * 2 - 1; i ++) {
		int j = 0;
		while (map[i][j] != '\n')
			map[i][++ j] = char(getchar());
		map[i][j] = 0;
		/* if (i) debug("%s\n", map[i] + 1); */
	}
	ll ans1 = solve(R, C);
	/* debug("ans1 = %lld\n", ans1); */
	R |= 1;
	std::reverse(map + 1, map + R * 2);
	ll ans2 = solve(R, C);
	/* debug("ans2 = %lld\n", ans2); */
	printf("%lld\n", ans1 + ans2);
}
