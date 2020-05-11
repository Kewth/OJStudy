#if 0
2020.05.11

  不公平博弈的超现实数应用。
  这个游戏对应的有效状态只有 -1, -1/2, 0, 1/2, 1, star, up, down 这 8 种。
  大力分类讨论并计数，预处理一些前缀和即可。
#endif
#include <cstdio>
#include <algorithm>
#include <string>
#include <map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef size_t si;
typedef std::string str;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator str () { char x[6]; return scanf("%s", x), x; }
} read;

std::map<str, int> sn, sp;
void dfs (str s) {
	if (sn.count(s)) return;
	str l, r;
	for (si i = 0; i < 5; i ++)
		if (s[i] == '_') {
			if (i >= 1 and s[i - 1] == 'L') {
				l = s;
				std::swap(l[i - 1], l[i]);
			}
			if (i >= 2 and s[i - 1] == 'R' and s[i - 2] == 'L') {
				l = s;
				std::swap(l[i - 2], l[i]);
			}
			if (i < 4 and s[i + 1] == 'R') {
				r = s;
				std::swap(r[i + 1], r[i]);
			}
			if (i < 3 and s[i + 1] == 'L' and s[i + 2] == 'R') {
				r = s;
				std::swap(r[i + 2], r[i]);
			}
			break;
		}
	/* debug("%s ->%s,%s\n", s.c_str(), l.c_str(), r.c_str()); */
	if (l.empty() and r.empty()) return sn[s] = 0, void();
	if (l.empty()) {
		dfs(r);
		if (sn[r] & 1) sn[s] = sn[r] - 1;
		else sn[s] = sn[r] - 2;
	}
	if (r.empty()) {
		dfs(l);
		if (sn[l] & 1) sn[s] = sn[l] + 1;
		else sn[s] = sn[l] + 2;
	}
	if (!l.empty() and !r.empty()) {
		dfs(l);
		dfs(r);
		if (sn[l] < 0 and sn[r] > 0) return sn[s] = 0, void();
		if (sn[r] - sn[l] == 2) return sn[s] = (sn[l] + sn[r]) >> 1, void();
		if (sn[l] < sn[r] and sn[r] <= 0) return sn[s] = sn[r] - 2, void();
		if (0 <= sn[l] and sn[l] < sn[r]) return sn[s] = sn[l] + 2, void();
		if (sn[l] == 0 and sn[r] == 0) {
			if (sp[l] == 0 and sp[r] == 0)
				sp[s] = 1;
			if (sp[l] == 1 and sp[r] == 0)
				sp[s] = 2;
			if (sp[l] == 0 and sp[r] == 1)
				sp[s] = 3;
			if (sp[l] == 3 and sp[r] == 2)
				sp[s] = 1;
			sn[s] = 0;
			return;
		}
		debug(">>> %s\n", s.c_str());
	}
}

void force (si x, str s) {
	if (x == 5) {
		int L = 0, R = 0, _ = 0;
		for (si i = 0; i < 5; i ++) {
			if (s[i] == 'L') ++ L;
			if (s[i] == 'R') ++ R;
			if (s[i] == '_') ++ _;
		}
		if (L == 2 and R == 2 and _ == 1) dfs(s);
		/* if (L == 2 and R == 2 and _ == 1) */
		/* 	debug("%s : %d %d\n", s.c_str(), sn[s], sp[s]); */
		return;
	}
	force(x + 1, s + 'L');
	force(x + 1, s + 'R');
	force(x + 1, s + '_');
}

const int maxn = 1000005, mod = 998244353;
ll fac[maxn], ifac[maxn];
ll pre[maxn << 1], po[maxn];

inline ll power (ll x, int k) {
	if (k < 0) k += mod - 1;
	ll res = 1;
	while (k) {
		if (k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

inline ll C (int n, int m) {
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

void combinator_init (int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; i ++)
		fac[i] = fac[i - 1] * i % mod;
	ifac[n] = power(fac[n], -1);
	for (int i = n; i; i --)
		ifac[i - 1] = ifac[i] * i % mod;
}

inline ll P (int l, int r, int lim) {
	l = std::max(l, 0);
	r = std::min(r, lim);
	if (l > r) return 0;
	ll res = pre[r] - (l ? pre[l - 1] : 0);
	return res < 0 ? res + mod : res;
}

int main () {
	force(0, str());
	int N = 1000000;
	combinator_init(N);

	po[0] = 1;
	for (int i = 1; i <= N; i ++)
		po[i] = (po[i - 1] << 1) % mod;

	read.operator int();
	int T = read;
	while (T --) {
		int n = read, a = 0, b = 0, c = 0, d = 0;
		int z = 0, star = 0, up = 0, down = 0;
		for (int i = 1; i <= n; i ++) {
			str x = read;
			int k = read;
			if (sn[x] == -2) a += k;
			if (sn[x] == -1) b += k;
			if (sn[x] == +1) c += k;
			if (sn[x] == +2) d += k;
			if (sn[x] == 0) {
				if (sp[x] == 0) z += k;
				if (sp[x] == 1) star += k;
				if (sp[x] == 2) down += k;
				if (sp[x] == 3) up += k;
			}
		}

		/* debug("%d %d %d %d\n", a, b, c, d); */

		ll L = 0, R = 0, F = 0, S = 0;

		pre[0] = 1;
		for (int k = 1; k <= b + c; k ++)
			pre[k] = (pre[k - 1] + C(b + c, k)) % mod;

		for (int k = 0; k <= a + d; k ++) {
			int kk = k * 2 - a * 2 - b;
			(R += P(0, - 1 - kk, b + c) * C(a + d, k)) %= mod;
			(L += P(1 - kk, b + c, b + c) * C(a + d, k)) %= mod;
		}
		ll Z = (po[a + b + c + d] - L - R + mod * 2) % mod;
		(L *= po[z + star + up + down]) %= mod;
		(R *= po[z + star + up + down]) %= mod;

		ll s0 = 0, s1 = 0;
		for (int k = 0; k <= star; k ++)
			(k & 1 ? s1 : s0) += C(star, k);
		s0 %= mod;
		s1 %= mod;
		(Z *= po[z]) %= mod;
		(s0 *= Z) %= mod;
		(s1 *= Z) %= mod;

		pre[0] = 1;
		for (int k = 1; k <= down; k ++)
			pre[k] = (pre[k - 1] + C(down, k)) % mod;

		for (int k = 0; k <= up; k ++) {
			ll coe = C(up, k) * s0 % mod;
			(L += P(0, k - 1, down) * coe) %= mod;
			(S += P(k, k, down) * coe) %= mod;
			(R += P(k + 1, down, down) * coe) %= mod;
		}

		for (int k = 0; k <= up; k ++) {
			ll coe = C(up, k) * s1 % mod;
			(L += P(0, k - 2, down) * coe) %= mod;
			(F += P(k - 1, k + 1, down) * coe) %= mod;
			(R += P(k + 2, down, down) * coe) %= mod;
		}

		printf("%lld %lld %lld %lld\n", L, R, F, S);
	}
}
