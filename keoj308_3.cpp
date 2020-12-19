#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	/* template<class T> inline void operator () (T &x) { x = *this; } */
	/* template<class T, class ...A> inline void operator () (T &x, A &...a) */
	/* { x = *this; this -> operator () (a...); } */
} read;

const int maxk = 10, maxl = 60, maxs = 59049, mod = 998244353;
ll L[maxk], R[maxk];
ll f[maxl + 1][maxs]; // 3^K   0: 都卡 (3) 或都不卡 (0)   1: 卡下界 2:   卡上界
int bit[maxk][maxs], po[maxk + 1];
bool eq[maxk];
int sta[maxk], nsta[maxk];

int main () {
	for (int S = 0; S < maxs; S ++)
		for (int i = 0, T = S; i < maxk; i ++, T /= 3)
			bit[i][S] = T % 3;
	po[0] = 1;
	for (int i = 1; i <= maxk; i ++)
		po[i] = po[i - 1] * 3;
	int Test = read;
	while (Test --) {
		int K = read;
		/* for (int i = 0; i < K; i ++) L[i] = ll(read) - 1, R[i] = ll(read) - 1, eq[i] = 1; */
		for (int i = 0; i < K; i ++) L[i] = ll(read) - 1;
		for (int i = 0; i < K; i ++) R[i] = ll(read) - 1;
		for (int i = 0; i < K; i ++) eq[i] = 1;
		f[maxl][0] = 1;
		for (int k = maxl - 1; k >= 0; k --) {
			for (int i = 0; i < K; i ++)
				eq[i] &= (L[i] >> (k + 1) & 1) == (R[i] >> (k + 1) & 1);
			for (int S = 0; S < po[K]; S ++)
				f[k][S] = 0;
			for (int S = 0; S < po[K]; S ++)
				if (f[k + 1][S]) {
					for (int i = 0; i < K; i ++)
						sta[i] = bit[i][S] == 0 and eq[i] ? 3 : bit[i][S];
					int free0 = 0, sp = -1, T = 0;
					for (int i = 0; i < K; i ++) {
						if (!(sta[i] & 1) or !(L[i] >> k & 1)) {
							nsta[i] = sta[i] - (sta[i] & 2 and R[i] >> k & 1 ? 2 : 0);
							T += po[i] * (nsta[i] == 3 ? 0 : nsta[i]);
							++ free0;
						}
						else
							sp = i;
					}
					if (free0 == K) {
						f[k][T] += f[k + 1][S];
						for (int i = 0; i < K; i ++)
							if (!(sta[i] & 2) or R[i] >> k & 1) {
								int ns = sta[i] - (sta[i] & 1 and !(L[i] >> k & 1) ? 1 : 0);
								f[k][T -
									po[i] * (nsta[i] == 3 ? 0 : nsta[i]) +
									po[i] * (ns == 3 ? 0 : ns)] += f[k + 1][S];
							}
					} else if (free0 == K - 1) {
						int i = sp;
						if (!(sta[i] & 2) or R[i] >> k & 1) {
							int ns = sta[i] - (sta[i] & 1 and !(L[i] >> k & 1) ? 1 : 0);
							f[k][T + po[i] * (ns == 3 ? 0 : ns)] += f[k + 1][S];
						}
					}
				}
			for (int S = 0; S < po[K]; S ++)
				f[k][S] %= mod;
		}
		ll ans = 0;
		for (int S = 0; S < po[K]; S ++)
			ans += f[0][S];
		printf("%lld\n", ans % mod);
	}
}
