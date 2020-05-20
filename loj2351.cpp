#if 0
2020.05.20

  如果 ? 的数量较少，直接枚举 ? 的所有取值可能。
  如果 1 的数量较少，那么枚举 1 的一个集合 S 。把 S 中的 1 看做 ? ，把 S 外的 1 看做 0
做容斥，由于转换后只剩下 0 和 ? ，相当于求个子集和之类的东西，预处理即可。
  如果 0 的数量较少，和 1 的情况类似。
  那么选数量最少的一种情况，复杂度 (n 2^n + Q 2^{floor(n/3)}) 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 20;
char s[1 << maxn | 1], t[maxn + 1];
int a[1 << maxn], b[1 << maxn];
int count[1 << maxn];

int main () {
	int n = read, q = read;
	scanf("%s", s);

	int N = 1 << n;
	for (int i = 0; i < N; i ++)
		a[i] = b[i] = s[i] - '0';
	for (int i = 1; i < N; i ++)
		count[i] = count[i & (i - 1)] + 1;

	for (int m = 1; m < N; m <<= 1)
		for (int i = 0; i < N; i += m << 1)
			for (int k = i; k < i + m; k ++) {
				a[k] += a[k + m];
				b[k + m] += b[k];
			}

	while (q --) {
		scanf("%s", t);
		std::reverse(t, t + n);
		int S0 = 0, S1 = 0, S2 = 0;
		for (int i = 0; i < n; i ++)
			if (t[i] == '0') S0 |= 1 << i;
			else if (t[i] == '1') S1 |= 1 << i;
			else if (t[i] == '?') S2 |= 1 << i;
		int min = std::min({count[S0], count[S1], count[S2]}), ans = 0;

		if (count[S0] == min)
			for (int T = S0; T >= 0; T --) {
				T &= S0;
				if (count[T] & 1) ans -= a[S1 | T];
				else ans += a[S1 | T];
			}

		else if (count[S1] == min)
			for (int T = S1; T >= 0; T --) {
				T &= S1;
				if (count[T] & 1) ans -= b[(S0 | T) ^ (N - 1)];
				else ans += b[(S0 | T) ^ (N - 1)];
			}

		else if (count[S2] == min)
			for (int T = S2; T >= 0; T --) {
				T &= S2;
				ans += s[S1 | T] - '0';
			}

		printf("%d\n", ans);
	}
}
