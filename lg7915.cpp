/*
 * Author: Kewth

 * Date:
  2021.10.25

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
	/* inline operator ll () { ll x; return scanf("%lld", &x), x; } */
	template<class T> inline void operator () (T &x) { x = *this; }
	/* template<class T, class ...A> inline void operator () (T &x, A &...a) */
	/* { x = *this; this -> operator () (a...); } */
} read;

const int maxn = 500005;
int ar[maxn << 1];

bool ans[maxn << 1];
int per[maxn << 1];
bool solve (int n, bool rev) {
	int p = 2;
	while (ar[p] != ar[1]) ++ p;
	int a = 2, b = p - 1, c = p + 1, d = n << 1;
	per[1] = 1, per[n << 1] = p;
	for (int t = 2; t <= n; t ++) {
		int &p1 = per[t], &p2 = per[(n << 1 | 1) - t];
#define PD_1 \
			if (ar[a] == ar[b] and a < b) \
				p1 = a ++, p2 = b --; \
			else if (ar[a] == ar[c] and a <= b and c <= d) \
				p1 = a ++, p2 = c ++;
#define PD_2 \
			if (ar[d] == ar[b] and a <= b and c <= d) \
				p1 = d --, p2 = b --; \
			else if (ar[d] == ar[c] and c < d) \
				p1 = d --, p2 = c ++;
		if (rev)
			PD_2 else PD_1 else return 0;
		else
			PD_1 else PD_2 else return 0;
	}
	int l = 1, r = n << 1;
	for (int i = 1; i < (n << 1); i ++)
		if (per[i] == l)
			ans[i] = 0 ^ rev, ++ l;
		else if (per[i] == r)
			ans[i] = 1 ^ rev, -- r;
		else
			debug("ERROR");
	ans[n << 1] = 0;
	return 1;
}

int main () {
	int T = read;
	while (T --) {
		int n = read;
		for (int i = 1; i <= (n << 1); i ++)
			read(ar[i]);
		bool Ans = solve(n, 0);
		if (!Ans) {
			std::reverse(ar + 1, ar + (n << 1) + 1);
			Ans = solve(n, 1);
		}
		if (Ans) {
			for (int i = 1; i <= (n << 1); i ++) putchar("LR"[ans[i]]);
			puts("");
		}
		else
			puts("-1");
	}
}
