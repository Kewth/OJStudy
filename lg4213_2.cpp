#if 0
2019.10.15

杜教筛板题。
预处理较小的部分即可。
#endif
#include <cstdio>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 2333333, maxb = 100000;
lolong s1[maxb], s2[maxb];
lolong mu[maxn], phi[maxn];
int minp[maxn];
int w[maxb];

int n, m, s;
inline int id(int x) {
	return x <= s ? x : m - (n / x) + 1;
}

int main() {
	mu[1] = phi[1] = 1;
	for(int i = 2; i < maxn; i ++) {
		if(!minp[i]) {
			minp[i] = i;
			if(i < maxn / i)
				for(int j = i * i; j < maxn; j += i)
					if(i < minp[j] or !minp[j])
						minp[j] = i;
		}
		int x = i / minp[i];
		if(x % minp[i]) {
			mu[i] = - mu[x];
			phi[i] = phi[x] * (minp[i] - 1);
		}
		else
			phi[i] = phi[x] * minp[i];
		/* debug("%d -> %d %d %d\n", minp[i], i, mu[i], phi[i]); */
	}


	for(int i = 2; i < maxn; i ++) {
		mu[i] += mu[i - 1];
		phi[i] += phi[i - 1];
	}

	int T = input();
	while(T --) {
		n = input();
		m = 0;
		s = int(sqrt(n));
		for(int l = 1, r; l <= n; l = r + 1)
			w[++ m] = r = n / (n / l);
		for(int i = 1; i <= m; i ++) {
			if(w[i] < maxn) {
				s1[i] = phi[w[i]];
				s2[i] = mu[w[i]];
			}
			else {
				s1[i] = 1ll * w[i] * (w[i] + 1) / 2;
				s2[i] = 1;
				for(int l = 2, r; l <= w[i]; l = r + 1) {
					r = w[i] / (w[i] / l);
					s1[i] -= (r - l + 1) * s1[id(w[i] / r)];
					s2[i] -= (r - l + 1) * s2[id(w[i] / r)];
				}
			}
		}
		printf("%lld %lld\n", s1[m], s2[m]);
	}
}
