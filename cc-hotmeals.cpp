/*
 * Author: Kewth

 * Date:
  2021.05.07

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
typedef std::pair<int, int> par;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	/* inline operator ll () { ll x; return scanf("%lld", &x), x; } */
	/* template<class T> inline void operator () (T &x) { x = *this; } */
	/* template<class T, class ...A> inline void operator () (T &x, A &...a) */
	/* { x = *this; this -> operator () (a...); } */
} read;

const int maxn = 500005;
int cnt[maxn << 2];
ll max[maxn << 2], tag[maxn << 2];
#define ls (now << 1)
#define rs (now << 1 | 1)

void update (int, int, int); // O(log)
void push (int); // O(1)
void A (int, ll); // O(1)
int Q (int, int, int, ll); // O(log)

void update (int now, int L, int R) {
	int M = (L + R) >> 1;
	cnt[now] = cnt[rs] + Q(ls, L, M, max[rs]);
	max[now] = std::max(max[ls], max[rs]);
}

void push (int now) {
	if (tag[now]) {
		A(ls, tag[now]);
		A(rs, tag[now]);
		tag[now] = 0;
	}
}

void A (int now, ll x) {
	tag[now] += x;
	max[now] += x;
}

int Q (int now, int L, int R, ll ex) {
	if (L == R) return max[now] > ex;
	int M = (L + R) >> 1;
	push(now);
	if (max[rs] > ex)
		return cnt[now] - cnt[rs] + Q(rs, M + 1, R, ex);
	return Q(ls, L, M, ex);
}

ll tmp_ex; // set it to -infinity
int query (int now, int L, int R, int l, int r) { // O(log^2)
	if (r < L or l > R) return 0;
	int res = 0;
	if (l <= L and R <= r) {
		if (max[now] > tmp_ex) {
			res += Q(now, L, R, tmp_ex);
			tmp_ex = max[now];
		}
		return res;
	}
	push(now);
	int M = (L + R) >> 1;
	res += query(rs, M + 1, R, l, r);
	res += query(ls, L, M, l, r);
	return res;
}

void add (int now, int L, int R, int l, int r, int x) { // O(log^2)
	if (r < L or l > R) return;
	if (l <= L and R <= r)
		return A(now, x);
	int M = (L + R) >> 1;
	push(now);
	add(ls, L, M, l, r, x);
	add(rs, M + 1, R, l, r, x);
	update(now, L, R);
}

ll a[maxn];
void build (int now, int L, int R) { // O(n) in fact
	if (L == R)
		return cnt[now] = 1, max[now] = a[L], void();
	int M = (L + R) >> 1;
	build(ls, L, M);
	build(rs, M + 1, R);
	update(now, L, R);
	/* debug("%d-%d : %d %lld\n", L, R, cnt[now], max[now]); */
}

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++)
		a[i] = read + n - i;
	build(1, 1, n);
	printf("%d\n", n - cnt[1]);

	int q = read;
	while (q --) {
		int o = read, l = read, r = read;
		if (o == 1) {
			tmp_ex = - 1000000000000000000;
			printf("%d\n", r - l + 1 - query(1, 1, n, l, r));
		}
		if (o == 2)
			add(1, 1, n, l, r, read);
	}
}
