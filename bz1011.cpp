#if 0
2020.05.20

  注意到误差允许的范围有 5% ，而且 a <= 0.35 ，i 和 j 的差值较大，1 / (i - j) 较小，那么
对于连续的一段数把 1 / (i - j) 这个分母换成它们的分母平均值一起算贡献即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef long double ld;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ld () { double x; return scanf("%lf", &x), ld(x); }
} read;

const int maxn = 100005;
int a[maxn];
ll b[maxn];
ld s[maxn];

int main () {
	int n = read, B = 300;
	ld x = read;

	for (int i = 1; i <= n; i ++) {
		b[i] = b[i - 1] + (a[i] = read);
		s[i] = s[i - 1] + ld(1) / i;
		int lim = int(i * x + ld(1e-6));
		int step = lim / B + 1;
		ld ans = 0;
		for (int j = 1; j <= lim; j += step) {
			int k = std::min(lim, j + step - 1);
			ans += (s[i - j] - s[i - k - 1]) / (k - j + 1) * (b[k] - b[j - 1]);
		}
		printf("%.10lf\n", double(ans * a[i]));
	}
}
