#if 0
2020.03.23

分块简单题，只是因为打 CF VP 的时候错误地想到了这个玩意，觉得有点用，就出出来了。
不过 CF 那次是准备拿来维护矩阵而不是普通的数，但本质也没啥区别。
#endif
#include <cstdio>
#include <algorithm>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 100005, maxs = 1005;
int a[maxn], tag[maxs];
ll mul[maxs], mls[maxs];
int L[maxs], R[maxs];
int bl[maxn];
int mod;

void force_pushdown (int b) {
	if (tag[b]) {
		for (int i = L[b]; i <= R[b]; i ++)
			a[i] = tag[b];
		tag[b] = 0;
	}
}

ll force_calc (int l, int r) {
	force_pushdown(bl[l]);
	ll res = a[r];
	for (int i = r - 1; i >= l; i --)
		res = a[i] * (1 + res) % mod;
	return res;
}

ll force_mul (int l, int r) {
	force_pushdown(bl[l]);
	ll res = 1;
	for (int i = l; i <= r; i ++)
		(res *= a[i]) %= mod;
	return res;
}

void force_update (int b) {
	mul[b] = force_mul(L[b], R[b]);
	mls[b] = force_calc(L[b], R[b]);
}

void force_modify (int l, int r, int x) {
	force_pushdown(bl[l]);
	for (int i = l; i <= r; i ++)
		a[i] = x;
	force_update(bl[l]);
}

int main () {
	int n = read;
	read(mod);
	for (int i = 1; i <= n; i ++)
		a[i] = read;

	int B = int(sqrt(n)), S;
	bl[1] = L[1] = R[1] = S = 1;
	for (int i = 2; i <= n; i ++)
		if (R[S] - L[S] + 1 < B)
			++ R[bl[i] = S];
		else {
			bl[i] = ++ S;
			L[S] = R[S] = i;
		}

	for (int b = 1; b <= S; b ++)
		force_update(b);

	int q = read;
	while (q --) {
		int o = read;

		if (o == 1) {
			int k = read;
			force_modify(k, k, read);
		}

		if (o == 2) {
			int l = read, r = read;
			if (bl[l] == bl[r]) printf("%lld\n", force_calc(l, r));
			else {
				ll pre = force_mul(l, R[bl[l]]), ans = force_calc(l, R[bl[l]]);
				for (int b = bl[l] + 1; b < bl[r]; b ++) {
					(ans += pre * mls[b]) %= mod;
					(pre *= mul[b]) %= mod;
				}
				(ans += pre * force_calc(L[bl[r]], r)) %= mod;
				printf("%lld\n", ans);
			}
		}

		if (o == 3) {
			int l = read, r = read, x = read;
			if (bl[l] == bl[r]) force_modify(l, r, x);
			else {
				force_modify(l, R[bl[l]], x);
				if (bl[l] + 1 <= bl[r] - 1) {
					int be = bl[l] + 1;
					force_modify(L[be], R[be], x);
					for (int b = be + 1; b < bl[r]; b ++) {
						mul[b] = mul[be];
						mls[b] = mls[be];
						tag[b] = x;
					}
				}
				force_modify(L[bl[r]], r, x);
			}
		}

		if (o == 4) {
			// TODO: 咕咕咕
		}
	}
}
